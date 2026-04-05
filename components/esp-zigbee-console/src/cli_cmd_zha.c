/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define TAG "cli_cmd_zha"

#include <string.h>

#include <ezbee/af.h>

#include "zb_data/ha.h"
#include "cli_cmd.h"
#include "esp_zigbee_console.h"

#define DEV_CTX() (CLI_CTX().ep_list)

typedef struct cli_zha_device_params_s {
    uint8_t     ep_id;
    uint16_t    device_id;
    const char *device_name;
} cli_zha_device_params_t;

static ezb_err_t zha_add_device(ezb_af_device_desc_t dev_desc, cli_zha_device_params_t *device_params)
{
    ezb_err_t ret = EZB_ERR_NONE;
    EXIT_ON_FALSE(device_params->device_name != NULL, EZB_ERR_NONE);
    EXIT_ON_FALSE(dev_desc, EZB_ERR_NOT_SUPPORTED, cli_output_line("Data model has been registered"));
    ezb_af_ep_desc_t endpoint = ezb_ep_create_ha_default(device_params->ep_id, device_params->device_id);
    EXIT_ON_FALSE(endpoint, EZB_ERR_NOT_SUPPORTED, cli_output("Unsupported device %s\n", device_params->device_name));

    EXIT_ON_ERROR(ezb_af_device_add_endpoint_desc(dev_desc, endpoint),
                  cli_output_line("Fail to add the device to endpoint list"));
    cli_output("%s created with endpoint_id %d\n", device_params->device_name, device_params->ep_id);

exit:
    return ret;
}

static void cli_output_device_name(void)
{
    int         idx   = 0;
    const char *empty = "";
    const char *name;
    cli_output_line("\nSupported device:");
    while (empty != (name = ezb_get_device_name_by_idx(idx++))) {
        if (ezb_is_device_supported(ezb_get_device_id_by_name(name))) {
            cli_output_line(name);
        }
    }
}

static ezb_err_t cli_zha_add_parse_params(int argc, char *argv[], cli_zha_device_params_t *dev_param)
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

    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]); cli_output_device_name());
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    int      ep_id     = argtable.ep_id->ival[0];
    uint16_t device_id = ezb_get_device_id_by_name(argtable.device->sval[0]);

    EXIT_ON_FALSE((0 < ep_id && ep_id < 255), EZB_ERR_INV_ARG,
                  cli_output("<endpoint_id> should in range 1 - 254, got %d\n", ep_id));
    EXIT_ON_FALSE((device_id != 0xFFFF), EZB_ERR_INV_ARG, cli_output("Unknown <DEVICE>, got %s\n", argtable.device->sval[0]);
                  cli_output_device_name());

    dev_param->device_id   = device_id;
    dev_param->ep_id       = ep_id;
    dev_param->device_name = ezb_get_device_name_by_id(device_id);

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_zha_add(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    ezb_err_t               ret           = EZB_ERR_NONE;
    cli_zha_device_params_t device_params = {0};

    EXIT_ON_ERROR(cli_zha_add_parse_params(argc, argv, &device_params));
    EXIT_ON_ERROR(zha_add_device(DEV_CTX(), &device_params));

exit:
    return ret;
}

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(zha, "ZigBee Home Automation Profile",
    ESP_ZB_CLI_SUBCMD(add, cli_zha_add, "Add device by device type name"),
);
