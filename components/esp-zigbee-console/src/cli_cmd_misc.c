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

#include "esp_zigbee_console.h"
#include "cli_cmd.h"

#define TAG "cli_cmd_misc"

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

DECLARE_ESP_ZB_CLI_CMD(factoryreset, cli_factoryreset,, "Reset the device to factory new immediately");
DECLARE_ESP_ZB_CLI_CMD(reboot,       cli_reboot,,       "Reboot the device immediately");
DECLARE_ESP_ZB_CLI_CMD(radio,        cli_radio,,        "Enable/Disable the radio");
DECLARE_ESP_ZB_CLI_CMD(start,        cli_start,,        "Start Zigbee stack");
