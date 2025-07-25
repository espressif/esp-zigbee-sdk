/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "esp_check.h"
#include "esp_console.h"

#include "cli_cmd.h"
#include "cli_cmd_zcl.h"
#include "esp_zigbee_console.h"

#define TAG "esp-zigbee-console"

typedef struct esp_zigbee_console_context_s {
    esp_zb_cli_context_t cli_ctx;
    esp_console_repl_t *repl;
    TaskHandle_t repl_task_hdl;
} esp_zigbee_console_context_t;

static esp_zigbee_console_context_t *s_console_ctx = NULL;

static esp_err_t esp_zb_console_init_ctx(void)
{
    s_console_ctx = calloc(1, sizeof(esp_zigbee_console_context_t));
    ESP_RETURN_ON_FALSE(s_console_ctx, ESP_ERR_NO_MEM, TAG, "No memory for console context");
    return ESP_OK;
}

static esp_err_t esp_zb_console_core_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
{
    esp_err_t ret = ESP_ERR_NOT_SUPPORTED;
    const esp_zb_zcl_status_t *status = message;

    ESP_LOGI(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
    ESP_GOTO_ON_FALSE(message, ESP_FAIL, exit, TAG, "Empty message");
    ESP_GOTO_ON_FALSE(!(*status), ESP_ERR_INVALID_ARG, exit, TAG, "Message: error status(%d)", *status);

    ret = cli_zcl_core_action_handler(callback_id, message);

exit:
    return ret;
}

esp_zb_cli_context_t *esp_zb_console_get_cli_ctx(void)
{
    return &s_console_ctx->cli_ctx;
}

esp_err_t esp_zb_console_manage_ep_list(esp_zb_ep_list_t *ep_list)
{
    esp_err_t ret = ESP_OK;
    ESP_GOTO_ON_FALSE(s_console_ctx, ESP_ERR_INVALID_STATE, exit, TAG, "Console is not initialized");

    esp_zb_cli_context_t *cli_ctx = &s_console_ctx->cli_ctx;
    ESP_GOTO_ON_FALSE(!(cli_ctx->ep_list), ESP_ERR_INVALID_STATE, exit, TAG, "Already has managed endpoint list");

    if (ep_list == NULL) {
        cli_ctx->ep_list = esp_zb_ep_list_create();
    } else {
        cli_ctx->ep_list = ep_list;
    }

exit:
    return ret;
}

/* This function is used to block the REPL task to wait for
 * the result of asynchronous operation. It is expected to
 * be called only from the REPL task.
 */
static esp_err_t esp_zb_console_wait_result(void) {
    esp_err_t ret = ESP_OK;
    if (unlikely(s_console_ctx->repl_task_hdl == NULL)) {
        s_console_ctx->repl_task_hdl = xTaskGetCurrentTaskHandle();
    }
    if (xTaskNotifyWait(0, ULONG_MAX, (uint32_t*)&ret, portMAX_DELAY) != pdPASS) {
        ret = ESP_FAIL;
    }
    return ret;
}

/* This function is used to notify the blocked the REPL task of
 * the result of asynchronous operation. It is expected to be
 * called only from the Zigbee Main task (by callbacks of requests).
 */
esp_err_t esp_zb_console_notify_result(esp_err_t result) {
    esp_err_t ret = ESP_OK;
    ESP_RETURN_ON_FALSE(s_console_ctx->repl_task_hdl, ESP_ERR_INVALID_STATE, TAG, "Task handle is NULL");
    if (xTaskNotify(s_console_ctx->repl_task_hdl, result, eSetValueWithOverwrite) != pdPASS) {
        ret = ESP_FAIL;
    }

    return ret;
}

static esp_err_t esp_zb_console_cmd_handler(int argc, char **argv)
{
    extern const esp_zb_cli_cmd_t _esp_zb_cli_cmd_array_start;
    extern const esp_zb_cli_cmd_t _esp_zb_cli_cmd_array_end;

    esp_err_t ret = ESP_ERR_NOT_FOUND;
    for (const esp_zb_cli_cmd_t *cmd = &_esp_zb_cli_cmd_array_start; cmd != &_esp_zb_cli_cmd_array_end; cmd++) {
        if (!strcmp(argv[0], cmd->name)) {
            esp_zb_lock_acquire(portMAX_DELAY);
            ret = esp_zb_cli_process_cmd((esp_zb_cli_cmd_t *)cmd, argc, argv);
            esp_zb_lock_release();
            if (ret == ESP_ERR_NOT_FINISHED) {
                ret = esp_zb_console_wait_result();
            }
            break;
        }
    }

    return ret;
}

static esp_err_t esp_zb_console_cmd_register_all(void)
{
    extern const esp_zb_cli_cmd_t _esp_zb_cli_cmd_array_start;
    extern const esp_zb_cli_cmd_t _esp_zb_cli_cmd_array_end;

    ESP_LOGI(TAG, "List of ESP Zigbee Console commands:");
    for (const esp_zb_cli_cmd_t *cmd = &_esp_zb_cli_cmd_array_start; cmd != &_esp_zb_cli_cmd_array_end; cmd++) {
        esp_console_cmd_t command = {
            .command = cmd->name,
            .help = cmd->help,
            .func = esp_zb_console_cmd_handler,
        };
        ESP_RETURN_ON_ERROR(esp_console_cmd_register(&command), TAG, "Unable to register %s cmd", cmd->name);
        ESP_LOGI(TAG, "  - Command '%s'", cmd->name);
    }

    return ESP_OK;
}

static esp_err_t esp_zb_console_repl_init(void)
{
/* Task name used by esp_console for REPL task creation.
 * The name MUST be aligned with esp_console_repl.c
 */
#define REPL_TASK_NAME "console_repl"

    esp_err_t ret = ESP_OK;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();

    repl_config.max_cmdline_length = CONFIG_ZB_CONSOLE_MAX_LINE_LENGTH;

    /* Install console REPL environment */
#if defined(CONFIG_ESP_CONSOLE_UART_DEFAULT) || defined(CONFIG_ESP_CONSOLE_UART_CUSTOM)
    esp_console_dev_uart_config_t hw_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    ESP_GOTO_ON_ERROR(esp_console_new_repl_uart(&hw_config, &repl_config, &s_console_ctx->repl), exit,
                      TAG, "Fail to install console REPL environment");
#elif defined(CONFIG_ESP_CONSOLE_USB_CDC)
    esp_console_dev_usb_cdc_config_t hw_config = ESP_CONSOLE_DEV_CDC_CONFIG_DEFAULT();
    ESP_GOTO_ON_ERROR(esp_console_new_repl_usb_cdc(&hw_config, &repl_config, &s_console_ctx->repl), exit,
                      TAG, "Fail to install console REPL environment");
#elif defined(CONFIG_ESP_CONSOLE_USB_SERIAL_JTAG)
    esp_console_dev_usb_serial_jtag_config_t hw_config = ESP_CONSOLE_DEV_USB_SERIAL_JTAG_CONFIG_DEFAULT();
    ESP_GOTO_ON_ERROR(esp_console_new_repl_usb_serial_jtag(&hw_config, &repl_config, &s_console_ctx->repl), exit,
                      TAG, "Fail to install console REPL environment");
#else
#error Unsupported console type
#endif

    s_console_ctx->repl_task_hdl = xTaskGetHandle(REPL_TASK_NAME);
    ESP_GOTO_ON_FALSE(s_console_ctx->repl_task_hdl, ESP_FAIL, exit,
                      TAG, "Fail to get REPL task handle by name: %s", REPL_TASK_NAME);

exit:
    return ret;
}

esp_err_t esp_zb_console_start(void)
{
    ESP_RETURN_ON_FALSE(s_console_ctx, ESP_ERR_INVALID_STATE, TAG, "Console is not initialized");
    return esp_console_start_repl(s_console_ctx->repl);
}

esp_err_t esp_zb_console_init(void)
{
    esp_err_t ret = ESP_OK;

    ESP_GOTO_ON_ERROR(esp_zb_console_init_ctx(), exit, TAG, "Fail to init console context");
    ESP_GOTO_ON_ERROR(esp_zb_console_cmd_register_all(), exit, TAG, "Fail to register all commands");
    ESP_GOTO_ON_ERROR(esp_zb_console_repl_init(), exit, TAG, "Fail to init console REPL");
    esp_zb_core_action_handler_register(esp_zb_console_core_action_handler);

exit:
    return ret;
}

esp_err_t esp_zb_console_deinit(void)
{
    esp_err_t ret = ESP_OK;
    ESP_GOTO_ON_FALSE(s_console_ctx, ESP_ERR_INVALID_STATE, exit, TAG, "Console is not initialized");
    ESP_GOTO_ON_ERROR(s_console_ctx->repl->del(s_console_ctx->repl), exit, TAG, "Fail to deinit console");
    s_console_ctx->repl = NULL;
    s_console_ctx->repl_task_hdl = NULL;
    free(s_console_ctx);
    s_console_ctx = NULL;

exit:
    return ret;
}
