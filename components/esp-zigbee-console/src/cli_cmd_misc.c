/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "esp_check.h"
#include "esp_zigbee_core.h"
#include "zboss_api.h"

#include "esp_zigbee_console.h"
#include "cli_cmd.h"

#define TAG "cli_cmd_misc"

extern void mac_add_visible_device(zb_ieee_addr_t long_addr);
extern void mac_add_invisible_short(zb_uint16_t addr);
extern void mac_clear_filters(void);

static esp_err_t cli_factoryreset(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    if (argc > 1) {
        return ESP_ERR_INVALID_ARG;
    }
    cli_output("Erasing NVRAM of Zigbee stack ... ");
    esp_zb_zcl_reset_nvram_to_factory_default();
    cli_output_line("Done");
    cli_output_line("Reboot the device");
    esp_restart();

    /* Never reached, esp_restart are not expect to return. */
    return ESP_FAIL;
}

static esp_err_t cli_reboot(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    if (argc > 1) {
        return ESP_ERR_INVALID_ARG;
    }
    cli_output_line("Reboot the device");
    esp_restart();

    /* Never reached, esp_restart are not expect to return. */
    return ESP_FAIL;
}

static esp_err_t cli_start(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    if (argc > 1) {
        return ESP_ERR_INVALID_ARG;
    }
    cli_output_line("Start Zigbee stack");

    return esp_zb_start(false);
}

static esp_err_t cli_radio(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    return ESP_ERR_NOT_SUPPORTED;
}

static esp_err_t cli_trace(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    esp_err_t ret = ESP_ERR_NOT_SUPPORTED;
#if defined(CONFIG_ESP_ZB_TRACE_ENABLE) || defined (CONFIG_ZB_DEBUG_MODE)
    struct {
        arg_int_t *level;
        arg_u32_t *mask;
        arg_end_t *end;
    } argtable = {
        .level = arg_intn(NULL, NULL, "<LEVEL>", 1, 1, "trace log level"),
        .mask  = arg_u32n(NULL, NULL,  "<MASK>", 1, 1, "trace mask"),
        .end = arg_end(2),
    };

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    esp_zb_set_trace_level_mask(argtable.level->ival[0], argtable.mask->val[0]);
    ret = ESP_OK;

exit:
#endif
    return ret;
}

static esp_err_t cli_macfilter_add(esp_zb_cli_cmd_t *self, int argc, char *argv[])
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

    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    esp_zb_zcl_addr_t *addr = &argtable.addr->addr[0];
    /* only supports short address for invisible and ieee address for visible setting. */
    bool is_correct_addr_type = !((argtable.invisible->count > 0) ^ (addr->addr_type == ESP_ZB_ZCL_ADDR_TYPE_SHORT));
    EXIT_ON_FALSE(is_correct_addr_type, ESP_ERR_INVALID_ARG,
                  cli_output("Only %s address is supported!\n", argtable.invisible->count > 0 ? "short" : "ieee"));

    if (argtable.invisible->count > 0) {
        mac_add_invisible_short(addr->u.short_addr);
    } else {
        mac_add_visible_device(addr->u.ieee_addr);
    }

exit:
    return ret;
}

static esp_err_t cli_macfilter_clear(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    if (argc > 1) {
        return ESP_ERR_INVALID_ARG;
    }

    mac_clear_filters();

    return ESP_OK;
}

DECLARE_ESP_ZB_CLI_CMD(factoryreset, cli_factoryreset,, "Reset the device to factory new immediately");
DECLARE_ESP_ZB_CLI_CMD(reboot,       cli_reboot,,       "Reboot the device immediately");
DECLARE_ESP_ZB_CLI_CMD(radio,        cli_radio,,        "Enable/Disable the radio");
DECLARE_ESP_ZB_CLI_CMD(start,        cli_start,,        "Start Zigbee stack");
DECLARE_ESP_ZB_CLI_CMD(trace,        cli_trace,,        "Configure Zigbee stack trace log");
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(macfilter, "Zigbee stack mac filter management",
    ESP_ZB_CLI_SUBCMD(add,      cli_macfilter_add,      "Add device ieee addr for filter in"),
    ESP_ZB_CLI_SUBCMD(clear,    cli_macfilter_clear,    "Clear all entries in the filter"),
);
