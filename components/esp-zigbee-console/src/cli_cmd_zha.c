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
#include "zb_data/ha.h"

#define TAG "cli_cmd_zha"

typedef struct cli_zha_device_params_s {
    uint8_t ep_id;
    uint16_t device_id;
    const char *device_name;
} cli_zha_device_params_t;

static esp_err_t zha_add_device(esp_zb_ep_list_t *ep_list, cli_zha_device_params_t *device_params)
{
    esp_err_t ret = ESP_OK;
    EXIT_ON_FALSE(device_params->device_name != NULL, ESP_OK);
    EXIT_ON_FALSE(ep_list, ESP_ERR_NOT_SUPPORTED, cli_output_line("Data model has been registered"));
    esp_zb_cluster_list_t *cluster_list = esp_zb_ep_create_ha_default(device_params->device_id);

    EXIT_ON_FALSE(cluster_list, ESP_ERR_NOT_SUPPORTED,
                  cli_output("Unsupported device %s\n", device_params->device_name));

    /* Add created endpoint (cluster_list) to endpoint list */
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = device_params->ep_id,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = device_params->device_id,
        .app_device_version = 0
    };
    EXIT_ON_ERROR(esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config),
                  cli_output_line("Fail to add the device to endpoint list"));

    ESP_LOGI(TAG, "%s created with endpoint_id %d", device_params->device_name, device_params->ep_id);

exit:
    return ret;
}

static void cli_output_device_name(void)
{
    int idx = 0;
    const char *empty = "";
    const char *name;
    cli_output_line("\nSupported device:");
    while (empty != (name = esp_zb_get_device_name_by_idx(idx++))) {
        if (esp_zb_is_device_supported(esp_zb_get_device_id_by_name(name))) {
            cli_output_line(name);
        }
    }
}

static esp_err_t cli_zha_add_parse_params(int argc, char *argv[], cli_zha_device_params_t *dev_param)
{
    struct {
        arg_int_t *ep_id;
        arg_str_t *device;
        arg_end_t *end;
    } argtable = {
        .ep_id  = arg_int1(NULL, NULL, "<u8:EID>", "set the endpoint id of the added device"),
        .device = arg_str1(NULL, NULL, "<DEVICE>", "HA standard device to be added"),
        .end    = arg_end(2),
    };

    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]);cli_output_device_name());
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    int ep_id = argtable.ep_id->ival[0];
    uint16_t device_id = esp_zb_get_device_id_by_name(argtable.device->sval[0]);

    EXIT_ON_FALSE((0 < ep_id && ep_id < 255), ESP_ERR_INVALID_ARG,
                  cli_output("<endpoint_id> should in range 1 - 254, got %d\n", ep_id));
    EXIT_ON_FALSE((device_id != 0xFFFF), ESP_ERR_INVALID_ARG,
                  cli_output("Unknown <DEVICE>, got %s\n", argtable.device->sval[0]);
                  cli_output_device_name());

    dev_param->device_id = device_id;
    dev_param->ep_id = ep_id;
    dev_param->device_name = esp_zb_get_device_name_by_id(device_id);

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_zha_add(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    esp_err_t ret = ESP_OK;
    cli_zha_device_params_t device_params = { 0 };
    esp_zb_ep_list_t *ep_list = CLI_CTX().ep_list;
    EXIT_ON_ERROR(cli_zha_add_parse_params(argc, argv, &device_params));
    EXIT_ON_ERROR(zha_add_device(ep_list, &device_params));

exit:
    return ret;
}

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(zha, "ZigBee Home Automation Profile",
    ESP_ZB_CLI_SUBCMD(add, cli_zha_add, "Add device by device type name"),
);
