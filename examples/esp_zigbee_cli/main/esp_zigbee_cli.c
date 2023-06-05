/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee CLI Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "ha/esp_zigbee_ha_standard.h"
#include "esp_zigbee_cli_config.h"

#if CONFIG_ZB_ZCZR
#include "cli/zb_esp_cli.h"
#endif
#if !CONFIG_ZB_ZCZR
#error Coordinator/Router role is not compiled!
#endif

static const char *TAG = "ESP_ZB_CLI";

uint8_t esp_zb_cli_agent_handler(uint8_t bufid)
{
    if (esp_zb_cli_agent_ep_handler_general_cmd(bufid) == true) {
        return true;
    }
    if (esp_zb_cli_agent_ep_handler_attr(bufid) == true) {
        return true;
    }

    if (esp_zb_cli_agent_ep_handler_report(bufid) == true) {
        return true;
    }

    if (esp_zb_cli_agent_ep_handler_ping(bufid) == true) {
        return true;
    }

    return false;
}

static void bdb_start_top_level_commissioning_cb(uint8_t mode_mask)
{
    ESP_ERROR_CHECK(esp_zb_bdb_start_top_level_commissioning(mode_mask));
}


void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p                    = signal_struct->p_app_signal;
    esp_err_t err_status                = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type    = *p_sg_p;
    esp_zb_nwk_device_type_t  role      = esp_zb_get_network_device_role();
    esp_zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;
    esp_zb_zdo_signal_leave_indication_params_t *leave_ind_params = NULL;
    switch (sig_type) {
    case ESP_ZB_ZDO_SIGNAL_LEAVE:
        /* The ESP Zigbee CLI Agent will not attempt to rejoin the network after it receives the LEAVE command. */
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "leave network, status: %s", esp_err_to_name(err_status));
        } else {
            ESP_LOGE(TAG, "Unable to leave network, status: %s", esp_err_to_name(err_status));
        }
        break;
    case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
        esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_INITIALIZATION);
        break;
    case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
        if (err_status == ESP_OK) {
            if (role != ESP_ZB_DEVICE_TYPE_COORDINATOR) {
                esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_STEERING);
            } else {
                esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_FORMATION);
            }
        } else {
            ESP_LOGE(TAG, "Failed to initialize Zigbee stack");
        }
        break;
    case ESP_ZB_BDB_SIGNAL_FORMATION:
        if (err_status == ESP_OK) {
            esp_zb_ieee_addr_t extended_pan_id;
            esp_zb_get_extended_pan_id(extended_pan_id);
            ESP_LOGI(TAG, "Formed network successfully (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, Channel:%d)",
                     extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4],
                     extended_pan_id[3], extended_pan_id[2], extended_pan_id[1], extended_pan_id[0],
                     esp_zb_get_pan_id(), esp_zb_get_current_channel());
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_STEERING);
        } else {
            ESP_LOGI(TAG, "Restart network formation");
            esp_zb_scheduler_alarm((esp_zb_callback_t)bdb_start_top_level_commissioning_cb, ESP_ZB_BDB_MODE_NETWORK_FORMATION, 1000);
        }
        break;
    case ESP_ZB_BDB_SIGNAL_STEERING:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Joined network successfully");
        } else {
            esp_zb_scheduler_alarm((esp_zb_callback_t)bdb_start_top_level_commissioning_cb, ESP_ZB_BDB_MODE_NETWORK_STEERING, 1000);
        }
        break;
    case ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE:
        dev_annce_params = (esp_zb_zdo_signal_device_annce_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->device_short_addr);
        break;
    case ESP_ZB_ZDO_SIGNAL_LEAVE_INDICATION:
        leave_ind_params = (esp_zb_zdo_signal_leave_indication_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        if (!leave_ind_params->rejoin) {
            ESP_LOGI(TAG, "Zigbee Node is leaving network: 0x%x", leave_ind_params->short_addr);
        }
        break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type,
                 esp_err_to_name(err_status));
        break;
    }
}

void zigbee_stack_init(void)
{
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZC_CONFIG();
    esp_zb_init(&zb_nwk_cfg);
    ESP_ERROR_CHECK(esp_zb_set_primary_network_channel_set(1 << ZIGBEE_CHANNEL));
    esp_zb_nvram_erase_at_start(true);
    /* Set ESP Zigbee endpoint to CLI*/
    zb_cli_set_endpoint(ESP_ZIGBEE_CLI_ENDPOINT);
    /* set the configuration tool device config */
    esp_zb_configuration_tool_cfg_t config_tool_cfg = ESP_ZB_DEFAULT_CONFIGURATION_TOOL_CONFIG();
    esp_zb_ep_list_t *esp_zb_configuration_tool_ep = esp_zb_configuration_tool_ep_create(ESP_ZIGBEE_CLI_ENDPOINT, &config_tool_cfg);
    esp_zb_device_register(esp_zb_configuration_tool_ep);
    /* Register cluster response handler for ESP Zigbee CLI endpoint */
    esp_zb_add_cli_resp_handler_cb(ESP_ZIGBEE_CLI_ENDPOINT, esp_zb_cli_agent_handler);
}

void zb_main_loop_task(void *arg)
{
    while (true) {
        if (zb_cli_is_stack_started()) {
            esp_zb_cli_main_loop_iteration();
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));

    zb_cli_console_init();
    zigbee_stack_init();

    xTaskCreate(zb_cli_console_task, "zb_cli_console_task", 4096, NULL, 9, NULL);
    xTaskCreate(zb_main_loop_task, "zb_main_loop_task", 4096, NULL, 10, NULL);
}
