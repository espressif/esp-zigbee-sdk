/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_zigbee.h"

#include "cli_cmd.h"

#define TAG "cli_cmd_zgp"

static ezb_err_t cli_zgp_proxy(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    return EZB_ERR_NOT_SUPPORTED;
}

static ezb_err_t cli_zgp_sink(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    return EZB_ERR_NOT_SUPPORTED;
}

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(zgp, "ZigBee Green Power Profile management",
    ESP_ZB_CLI_SUBCMD(proxy, cli_zgp_proxy, "Get/Set green power proxy"),
    ESP_ZB_CLI_SUBCMD(sink,  cli_zgp_sink,  "Get/Set green power sink"),
);
