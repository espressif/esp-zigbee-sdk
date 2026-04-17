/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "esp_zigbee.h"

#include "cli_cmd.h"

#define TAG "cli_cmd_misc"

extern void mac_add_visible_device(const ezb_extaddr_t *extaddr);
extern void mac_add_invisible_short(ezb_shortaddr_t shortaddr);
extern void mac_clear_filters(void);

static ezb_err_t cli_factoryreset(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    if (argc > 1) {
        return EZB_ERR_INV_ARG;
    }

    cli_output_line("Erase NVRAM of Zigbee stack and reboot the device");
    esp_zigbee_factory_reset();

    /* Never reached, esp_zigbee_factory_reset() are not expect to return. */
    return EZB_ERR_FAIL;
}

static ezb_err_t cli_reboot(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    if (argc > 1) {
        return EZB_ERR_INV_ARG;
    }
    cli_output_line("Reboot the device");
    esp_restart();

    /* Never reached, esp_restart are not expect to return. */
    return EZB_ERR_FAIL;
}

static ezb_err_t cli_start(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    if (argc > 1) {
        return EZB_ERR_INV_ARG;
    }
    cli_output_line("Start Zigbee stack");

    return esp_zigbee_start(false);
}

static ezb_err_t cli_radio(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    return EZB_ERR_NOT_SUPPORTED;
}

static ezb_err_t cli_trace(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    return EZB_ERR_NOT_SUPPORTED;
}

static ezb_err_t cli_macfilter_add(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    struct {
        arg_lit_t  *invisible;
        arg_addr_t *addr;
        arg_end_t  *end;
    } argtable = {
        .invisible = arg_lit0("i", "invisible", "address is to be filtered out"),
        .addr = arg_addrn(NULL, NULL, "<addr:ADDR>", 1, 1, "device address for filtering"),
        .end = arg_end(2),
    };

    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    cli_addr_t *addr = &argtable.addr->addr[0];
    /* only supports short address for invisible and ieee address for visible setting. */
    bool is_correct_addr_type = !((argtable.invisible->count > 0) ^ (addr->addr_type == CLI_ADDR_TYPE_16BIT));
    EXIT_ON_FALSE(is_correct_addr_type, EZB_ERR_INV_ARG,
                  cli_output("Only %s address is supported!\n", argtable.invisible->count > 0 ? "short" : "ieee"));

    if (argtable.invisible->count > 0) {
        mac_add_invisible_short(addr->u.addr16);
    } else {
        mac_add_visible_device(&(ezb_extaddr_t){.u64 = addr->u.addr64});
    }

exit:
    return ret;
}

static ezb_err_t cli_macfilter_clear(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    if (argc > 1) {
        return EZB_ERR_INV_ARG;
    }

    mac_clear_filters();

    return EZB_ERR_NONE;
}

static ezb_err_t cli_memory_diag(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t *memory_type;
        arg_end_t *end;
    } argtable = {
        .memory_type = arg_strn(NULL, NULL, "<heap|stack>", 1, 1, "Memory type"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (!strcmp(argtable.memory_type->sval[0], "heap")) {
        cli_output("Cur Free Heap: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
        cli_output("Min Free Heap: %d bytes\n", heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT));
        cli_output("Max Free Heap: %d bytes\n", heap_caps_get_total_size(MALLOC_CAP_DEFAULT));
    } else if (!strcmp(argtable.memory_type->sval[0], "stack")) {
        const char *task_name = "Zigbee_main";
        TaskHandle_t task_handle;
        EXIT_ON_FALSE((task_handle = xTaskGetHandle(task_name)) != NULL, ESP_ERR_NOT_FOUND);
        cli_output("Min Free Stack: %d bytes\n", uxTaskGetStackHighWaterMark(task_handle));
    } else {
        EXIT_ON_ERROR(EZB_ERR_INV_ARG);
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

DECLARE_ESP_ZB_CLI_CMD(factoryreset, cli_factoryreset,, "Reset the device to factory new immediately");
DECLARE_ESP_ZB_CLI_CMD(reboot,       cli_reboot,,       "Reboot the device immediately");
DECLARE_ESP_ZB_CLI_CMD(radio,        cli_radio,,        "Enable/Disable the radio");
DECLARE_ESP_ZB_CLI_CMD(start,        cli_start,,        "Start Zigbee stack");
DECLARE_ESP_ZB_CLI_CMD(trace,        cli_trace,,        "Configure Zigbee stack trace log");
DECLARE_ESP_ZB_CLI_CMD(memdiag,      cli_memory_diag,,  "Diagnose memory usages");
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(macfilter, "Zigbee stack mac filter management",
    ESP_ZB_CLI_SUBCMD(add,      cli_macfilter_add,      "Add device ieee addr for filter in"),
    ESP_ZB_CLI_SUBCMD(clear,    cli_macfilter_clear,    "Clear all entries in the filter"),
);
