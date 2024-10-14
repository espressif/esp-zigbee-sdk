/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>

#include "esp_check.h"
#include "esp_zigbee_core.h"

#include "esp_zigbee_console.h"
#include "cli_cmd.h"
#include "cmdline_parser.h"

#define TAG "cli_cmd_bdb"

typedef struct cli_bdb_context_s {
    bool    distributed;
    bool    ic_only;
} cli_bdb_context_t;

static cli_bdb_context_t s_bdb_ctx = {
    .distributed = true,
    .ic_only = false,
};

static esp_err_t cli_role(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    static const char *role_string[] = {
        [ESP_ZB_DEVICE_TYPE_COORDINATOR] = "zc",
        [ESP_ZB_DEVICE_TYPE_ROUTER] = "zr",
        [ESP_ZB_DEVICE_TYPE_ED] = "zed",
        [ESP_ZB_DEVICE_TYPE_NONE] = "unknown",
    };
    struct {
        arg_str_t *role;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .role = arg_str0(NULL, NULL, "<sc:zc|zr|zed>", "role of the node"),
        .help = arg_lit0(NULL, "help", "print this help message"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.role->count > 0) {
        for (esp_zb_nwk_device_type_t role = ESP_ZB_DEVICE_TYPE_COORDINATOR; role < ESP_ZB_DEVICE_TYPE_NONE; role++) {
            if (!strcmp(argtable.role->sval[0], role_string[role])) {
                EXIT_NOW(ret = esp_zb_set_network_device_role(role));
            }
        }
        cli_output("unknown device role: %s\n", argtable.role->sval[0]);
        ret = ESP_ERR_NOT_SUPPORTED;
    } else {
        cli_output_line(role_string[esp_zb_get_network_device_role()]);
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_panid(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_lit_t  *extended;
        arg_addr_t *address;
        arg_lit_t  *help;
        arg_end_t  *end;
    } argtable = {
        .extended = arg_lit0("x",   NULL, "operate on extended PAN ID"),
        .address  = arg_addrn(NULL, NULL, "<addr:ADDR>", 0, 1, "(extended) PAN ID"),
        .help     = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.extended->count > 0) {
        if (argtable.address->count > 0) {
            EXIT_ON_FALSE(argtable.address->addr[0].addr_type == ESP_ZB_ZCL_ADDR_TYPE_IEEE, ESP_ERR_INVALID_ARG);
            esp_zb_set_extended_pan_id(argtable.address->addr[0].u.ieee_addr);
        } else {
            esp_zb_ieee_addr_t ext_pan_id;
            esp_zb_get_extended_pan_id(ext_pan_id);
            cli_output("0x%016" PRIx64 "\n", *(uint64_t *)&ext_pan_id);
        }
    } else {
        if (argtable.address->count > 0) {
            EXIT_ON_FALSE(argtable.address->addr[0].addr_type == ESP_ZB_ZCL_ADDR_TYPE_SHORT, ESP_ERR_INVALID_ARG);
            esp_zb_set_pan_id(argtable.address->addr[0].u.short_addr);
        } else {
            cli_output("0x%04hx\n", esp_zb_get_pan_id());
        }
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_address(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_lit_t  *extended;
        arg_addr_t *address;
        arg_lit_t  *help;
        arg_end_t  *end;
    } argtable = {
        .extended = arg_lit0("x",   NULL, "operate on extended address"),
        .address  = arg_addrn(NULL, NULL, "<addr:ADDR>", 0, 1, "(extended) address"),
        .help     = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.extended->count > 0) {
        if (argtable.address->count > 0) {
            EXIT_ON_FALSE(argtable.address->addr[0].addr_type == ESP_ZB_ZCL_ADDR_TYPE_IEEE, ESP_ERR_INVALID_ARG);
            EXIT_ON_ERROR(esp_zb_set_long_address(argtable.address->addr[0].u.ieee_addr));
        } else {
            esp_zb_ieee_addr_t ext_pan_id;
            esp_zb_get_long_address(ext_pan_id);
            cli_output("0x%016" PRIx64 "\n", *(uint64_t *)&ext_pan_id);
        }
    } else {
        if (argtable.address->count > 0) {
            EXIT_ON_FALSE(0, ESP_ERR_NOT_SUPPORTED, cli_output_line("set short address is not supported"));
        } else {
            cli_output("0x%04hx\n", esp_zb_get_short_address());
        }
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_channel(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_lit_t *mask;
        arg_u32_t *channel;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .mask    = arg_lit0("m",  NULL, "use channel mask"),
        .channel = arg_u32n(NULL, NULL, "<u32:CHANNEL>", 0, 1, "allowed channel (mask)"),
        .help    = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    /* Handle set / get */
    if (argc > 1) {
        uint32_t channel_mask = 0;
        if (argtable.channel->count > 0) {
            channel_mask = argtable.channel->val[0];
        }
        if (argtable.mask->count == 0) {
            channel_mask = 1 << channel_mask;
        }
        EXIT_ON_ERROR(esp_zb_set_channel_mask(channel_mask));
        /* Also set the channels for BDB commissioning */
        EXIT_ON_ERROR(esp_zb_set_primary_network_channel_set(channel_mask));
        EXIT_ON_ERROR(esp_zb_set_secondary_network_channel_set(channel_mask));
    } else {
        cli_output("Allowed Channel: 0x%08" PRIx32 "\n", esp_zb_get_channel_mask());
        cli_output("Current Channel: %d\n", esp_zb_get_current_channel());
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Sub-commands of `network` */

static esp_err_t cli_nwk_type(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t *role;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .role = arg_str0(NULL, NULL, "<sc:d|c>", "set the network type. Default: c"),
        .help = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.role->count > 0) {
        switch (argtable.role->sval[0][0]){
            case 'd':
                s_bdb_ctx.distributed = true;
                break;
            case 'c':
                s_bdb_ctx.distributed = false;
                break;
            default:
                EXIT_ON_ERROR(ESP_ERR_INVALID_ARG, cli_output("unknown network type: %s\n", argtable.role->sval[0]));
                break;
        }
    } else {
        cli_output("setting: %s\n", s_bdb_ctx.distributed ? "distributed" : "centralized");
        if (esp_zb_bdb_dev_joined()) {
            cli_output("current on: %s\n", esp_zb_network_is_distributed() ? "distributed" : "centralized");
        }
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_nwk_legacy(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    esp_err_t ret = ESP_OK;

    if (argc < 2) {
        /* TODO: Add support to get the SDK status. */
        cli_output_line("Get the legacy support status is not supported");
        ret = ESP_ERR_NOT_SUPPORTED;
    } else if (argc > 3) {
        ret = ESP_ERR_INVALID_ARG;
    } else if (!strcmp(argv[1], "enable")) {
        esp_zb_secur_link_key_exchange_required_set(true);
    } else if (!strcmp(argv[1], "disable")) {
        esp_zb_secur_link_key_exchange_required_set(false);
    } else {
        cli_output("Invalid option: %s, use \"enable\" or \"disable\"\n", argv[1]);
        ret = ESP_ERR_INVALID_ARG;
    }

    return ret;
}

static esp_err_t cli_nwk_key(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_hex_t *key;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .key = arg_hexn(NULL, NULL, "<key128:KEY>", 0, 1, "network key, in HEX format"),
        .help = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.key->count > 0) {
        EXIT_ON_FALSE(argtable.key->hsize[0] == 16, ESP_ERR_INVALID_ARG);
        EXIT_ON_ERROR(esp_zb_secur_network_key_set(argtable.key->hval[0]));
    } else {
        uint8_t key[ESP_ZB_CCM_KEY_SIZE];
        EXIT_ON_ERROR(esp_zb_secur_primary_network_key_get(key), cli_output_line("Fail to get network key."));
        cli_output_buffer(key, ESP_ZB_CCM_KEY_SIZE);
    }

exit:
    arg_hex_free(argtable.key);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_nwk_childmax(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u8_t  *childmax;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .childmax = arg_u8n(NULL, NULL, "<u8:CHILD_NUM>", 0, 1, "max children number"),
        .help = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.childmax->count > 0) {
        esp_zb_nwk_set_max_children(argtable.childmax->val[0]);
    } else {
        cli_output("%d\n", esp_zb_nwk_get_max_children());
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_nwk_open(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u8_t  *timeout;
        arg_end_t *end;
    } argtable = {
        .timeout = arg_u8n("t", NULL, "<u8:TIMEOUT>", 1, 1, "timeouts in second for opening"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_ERROR(esp_zb_bdb_open_network(argtable.timeout->val[0]), cli_output_line("Fail to open network."));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_nwk_close(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    esp_err_t ret = ESP_OK;

    EXIT_ON_FALSE(argc == 1, ESP_ERR_INVALID_ARG);

    EXIT_ON_ERROR(esp_zb_bdb_close_network(), cli_output_line("Fail to close network."));

exit:
    return ret;
}

static void cli_output_active_scan_results(esp_zb_network_descriptor_t *nwk_descriptor, uint16_t count)
{
    static const char *titles[] = {"Chnl", "PanID", "ExtPanID", "Status", "Cap"};
    static const uint8_t widths[] = {4, 8, 20, 7, 3};

    cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
    for (int i = 0; i < count; i++) {
        cli_output("| %2d | 0x%04hx | 0x%016" PRIx64 " | %5s | %c%c|\n",
                   nwk_descriptor[i].logic_channel,
                   nwk_descriptor[i].short_pan_id,
                   *(uint64_t *)nwk_descriptor[i].extended_pan_id,
                   nwk_descriptor[i].permit_joining ? "Open" : "Close",
                   nwk_descriptor[i].router_capacity ? 'R' : ' ',
                   nwk_descriptor[i].end_device_capacity ? 'E' : ' ');
    }
}

static void cli_nwk_scan_cb(esp_zb_zdp_status_t status, uint8_t count, esp_zb_network_descriptor_t *nwk_descriptor)
{
    esp_err_t ret = ESP_OK;
    EXIT_ON_FALSE(status == ESP_ZB_ZDP_STATUS_SUCCESS, ESP_FAIL,
                  cli_output("ED Scan failed: %d\n", status));

    cli_output_active_scan_results(nwk_descriptor, count);

exit:
    esp_zb_console_notify_result(ret);
}

static esp_err_t cli_nwk_scan(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_lit_t *mask;
        arg_u32_t *channel;
        arg_u8_t  *duration;
        arg_end_t *end;
    } argtable = {
        .mask     = arg_lit0("m",  NULL, "use channel mask"),
        .channel  = arg_u32n(NULL, NULL, "<u32:CHANNEL>", 1, 1, "channel (mask) to perform scan on"),
        .duration = arg_u8n("t",   NULL, "<u8:TIMEOUT>",  0, 1, "timeout in sec of scan, default: 1s"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    uint32_t channel_mask = 0;
    if (argtable.channel->count > 0) {
        channel_mask = argtable.channel->val[0];
    }
    if (argtable.mask->count == 0) {
        channel_mask = 1 << channel_mask;
    }
    esp_zb_zdo_active_scan_request(channel_mask,
                                   argtable.duration->count > 0 ? argtable.duration->val[0] : 1,
                                   cli_nwk_scan_cb);

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static void cli_output_ed_scan_results(esp_zb_energy_detect_channel_info_t *channel_info, uint16_t count)
{
    static const char *titles[] = {"Chnl", "RSSI"};
    static const uint8_t widths[] = {4, 6};

    cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
    for (int i = 0; i < count; i++) {
        cli_output("| %2d | %4d |\n", channel_info[i].channel_number, channel_info[i].energy_detected);
    }
}

static void cli_nwk_ed_scan_cb(esp_zb_zdp_status_t status, uint16_t count,
                               esp_zb_energy_detect_channel_info_t *channel_info)
{
    esp_err_t ret = ESP_OK;
    EXIT_ON_FALSE(status == ESP_ZB_ZDP_STATUS_SUCCESS, ESP_FAIL,
                  cli_output("ED Scan failed: %d\n", status));

    cli_output_ed_scan_results(channel_info, count);

exit:
    esp_zb_console_notify_result(ret);
}

static esp_err_t cli_nwk_ed_scan(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_lit_t *mask;
        arg_u32_t *channel;
        arg_u8_t  *duration;
        arg_end_t *end;
    } argtable = {
        .mask     = arg_lit0("m",  NULL, "use channel mask"),
        .channel  = arg_u32n(NULL, NULL, "<u32:CHANNEL>", 1, 1, "channel (mask) to perform scan on"),
        .duration = arg_u8n("t",   NULL, "<u8:TIMEOUT>",  0, 1, "timeout in sec of scan, default: 1s"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    uint32_t channel_mask = 0;
    if (argtable.channel->count > 0) {
        channel_mask = argtable.channel->val[0];
    }
    if (argtable.mask->count == 0) {
        channel_mask = 1 << channel_mask;
    }
    esp_zb_zdo_energy_detect_request(channel_mask,
                                     argtable.duration->count > 0 ? argtable.duration->val[0] : 1,
                                     cli_nwk_ed_scan_cb);

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Sub-commands of `ic` */

static esp_err_t cli_ic_add(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_addr_t *add_addr;
        arg_hex_t  *ic_code;
        arg_end_t  *end;
    } argtable = {
        .add_addr = arg_addrn(NULL, NULL, "<EUI64>",  1, 1, "IEEE address of the device"),
        .ic_code  = arg_hexn(NULL, NULL,  "<hex:IC>", 1, 1, "install code"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;
    uint8_t ic_type;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(esp_zb_is_started(), ESP_ERR_INVALID_SIZE, cli_output_line("Please start Zigbee stack first"));
    EXIT_ON_FALSE(argtable.add_addr->addr->addr_type == ESP_ZB_ZCL_ADDR_TYPE_IEEE, ESP_ERR_INVALID_ARG,
                  cli_output_line("IEEE address is required."));

    switch (argtable.ic_code->hsize[0]) {
      case 8: ic_type = ESP_ZB_IC_TYPE_48; break;
      case 10: ic_type = ESP_ZB_IC_TYPE_64; break;
      case 14: ic_type = ESP_ZB_IC_TYPE_96; break;
      case 18: ic_type = ESP_ZB_IC_TYPE_128; break;
      default:
        EXIT_NOW(ret = ESP_ERR_INVALID_ARG; cli_output("Install code incorrect length %d\n", argtable.ic_code->hsize[0]));
        break;
    }

    EXIT_ON_ERROR(esp_zb_secur_ic_add(argtable.add_addr->addr[0].u.ieee_addr, ic_type, argtable.ic_code->hval[0]),
                  cli_output_line("Fail to add install code."));

exit:
    arg_hex_free(argtable.ic_code);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_ic_remove(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_addr_t *add_addr;
        arg_end_t  *end;
    } argtable = {
        .add_addr = arg_addrn(NULL, NULL, "<eui64:EUI64>", 1, 1, "IEEE address of the device"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(argtable.add_addr->addr->addr_type == ESP_ZB_ZCL_ADDR_TYPE_IEEE, ESP_ERR_INVALID_ARG,
                  cli_output_line("IEEE address is required."));
    EXIT_ON_ERROR(esp_zb_secur_ic_remove_req(argtable.add_addr->addr->u.ieee_addr),
                  cli_output_line("Fail to remove install code."));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_ic_set(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_hex_t *ic_code;
        arg_end_t *end;
    } argtable = {
        .ic_code = arg_hexn(NULL, NULL, "<hex:IC>", 1, 1, "install code"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;
    uint8_t ic_type;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    switch (argtable.ic_code->hsize[0]) {
      case 8: ic_type = ESP_ZB_IC_TYPE_48; break;
      case 10: ic_type = ESP_ZB_IC_TYPE_64; break;
      case 14: ic_type = ESP_ZB_IC_TYPE_96; break;
      case 18: ic_type = ESP_ZB_IC_TYPE_128; break;
      default:
        EXIT_NOW(ret = ESP_ERR_INVALID_ARG; cli_output("Install code incorrect length %d\n", argtable.ic_code->hsize[0]));
        break;
    }

    EXIT_ON_ERROR(esp_zb_secur_ic_set(ic_type, argtable.ic_code->hval[0]), cli_output_line("Fail to set install code\n"));

exit:
    arg_hex_free(argtable.ic_code);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_ic_get(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    esp_err_t ret = ESP_OK;
    EXIT_ON_FALSE(argc == 1, ESP_ERR_INVALID_ARG);

    uint8_t ic_size[] = { 8, 10, 14, 18 };
    uint8_t ic_type = ESP_ZB_IC_TYPE_MAX;
    uint8_t *ic = esp_zb_secur_ic_get(&ic_type);

    if (ic == NULL) {
        cli_output_line("No install code configured.");
    } else {
        cli_output_buffer(ic, ic_size[ic_type]);
    }

exit:
    return ret;
}

/* Sub-commands of `bdb_comm` */

static esp_err_t cli_bdb_channel(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_lit_t  *mask;
        arg_u32_t  *primary_chn;
        arg_u32_t  *secondary_chn;
        arg_lit_t  *help;
        arg_end_t  *end;
    } argtable = {
        .mask          = arg_lit0("m",  NULL, "use channel mask"),
        .primary_chn   = arg_u32n(NULL, NULL, "<u32:PRIMARY>", 0, 1, "primary channel (mask)"),
        .secondary_chn = arg_u32n(NULL, NULL, "<u32:SECONDARY>", 0, 1, "secondary channel (mask)"),
        .help          = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    /* Handle set / get */
    if (argc > 1) {
        uint32_t primary_channel_mask = 0;
        uint32_t secondary_channel_mask = 0;
        if (argtable.primary_chn->count > 0) {
            primary_channel_mask = argtable.primary_chn->val[0];
        }
        if (argtable.secondary_chn->count > 0) {
            secondary_channel_mask = argtable.secondary_chn->val[0];
        }
        if (argtable.mask->count == 0) {
            primary_channel_mask = 1 << primary_channel_mask;
            secondary_channel_mask = 1 << secondary_channel_mask;
        }
        EXIT_ON_ERROR(esp_zb_set_primary_network_channel_set(primary_channel_mask));
        EXIT_ON_ERROR(esp_zb_set_secondary_network_channel_set(secondary_channel_mask));
    } else {
        cli_output("Primary Channel: 0x%08" PRIx32 "\n", esp_zb_get_primary_network_channel_set());
        cli_output("Secondary Channel: 0x%08" PRIx32 "\n", esp_zb_get_secondary_network_channel_set());
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_bdb_mode(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    esp_err_t ret = ESP_OK;

    EXIT_ON_FALSE(argc == 1, ESP_ERR_INVALID_ARG);

    cli_output("0x%02hx\n", (uint8_t)esp_zb_get_bdb_commissioning_mode());

exit:
    return ret;
}

static esp_err_t cli_bdb_start(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t *mode;
        arg_rem_t *rem_mode;
        arg_end_t *end;
    } argtable = {
        .mode = arg_strn(NULL, NULL, "<MODE>", 1, 4, "bdb commissioning mode"),
        .rem_mode = arg_rem("", "steer|form|bind|initiator|target"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    esp_zb_bdb_commissioning_mode_t bdb_comm_mode = ESP_ZB_BDB_MODE_INITIALIZATION;

    if (argtable.mode->count > 0) {
        for (int i = 0; i < argtable.mode->count; i++) {
            if (!strcmp(argtable.mode->sval[i], "steer")) {
                if (s_bdb_ctx.distributed) {
                    esp_zb_enable_joining_to_distributed(true);
                }
                bdb_comm_mode = bdb_comm_mode | ESP_ZB_BDB_NETWORK_STEERING;
            } else if (!strcmp(argtable.mode->sval[i], "form")) {
                if (s_bdb_ctx.distributed) {
                    esp_zb_enable_distributed_network(true);
                    esp_zb_zdo_setup_network_as_distributed();
                    esp_zb_tc_policy_set_distributed_security(true);
                }
                bdb_comm_mode = bdb_comm_mode | ESP_ZB_BDB_NETWORK_FORMATION;
            } else if (!strcmp(argtable.mode->sval[i], "bind")) {
                bdb_comm_mode = bdb_comm_mode | ESP_ZB_BDB_FINDING_N_BINDING;
            } else if (!strcmp(argtable.mode->sval[i], "initiator")) {
                uint32_t channel_mask = esp_zb_get_primary_network_channel_set();
                if (channel_mask != ESP_ZB_TRANSCEIVER_ALL_CHANNELS_MASK) {
                    esp_zb_zdo_touchlink_set_nwk_channel(__builtin_ctz(channel_mask));
                } else {
                    esp_zb_zdo_touchlink_set_nwk_channel(0);
                }
                bdb_comm_mode = bdb_comm_mode | ESP_ZB_BDB_TOUCHLINK_COMMISSIONING;
            } else if (!strcmp(argtable.mode->sval[i], "target")) {
                esp_zb_set_channel_mask(esp_zb_get_primary_network_channel_set());
                bdb_comm_mode = ESP_ZB_BDB_TOUCHLINK_TARGET;
            } else {
                cli_output("Skip %s bdb commissioning mode: %s\n", "unknown", argtable.mode->sval[i]);
            }
        }
    }

    if (!esp_zb_is_started()) {
        EXIT_ON_ERROR(esp_zb_start(false), cli_output_line("Fail to start Zigbee stack."));
    }

    EXIT_ON_ERROR(esp_zb_bdb_start_top_level_commissioning(bdb_comm_mode),
                  cli_output_line("Fail to start bdb top level commissioning."));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_bdb_cancel(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t *mode;
        arg_end_t *end;
    } argtable = {
        .mode = arg_strn(NULL, NULL, "<steer|form|target>", 1, 1, "commissioning mode to cancel"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.mode->count > 0) {
        if (!strcmp(argtable.mode->sval[0], "steer")) {
            ret = esp_zb_bdb_cancel_steering();
        } else if (!strcmp(argtable.mode->sval[0], "form")) {
            ret = esp_zb_bdb_cancel_formation();
        } else if (!strcmp(argtable.mode->sval[0], "target")) {
            ret = esp_zb_bdb_cancel_touchlink_target();
        } else {
            cli_output("%s mode for cancelling:%s\n", "unsupported", argtable.mode->sval[0]);
        }
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Sub-commands of `tl` */

static esp_err_t cli_tl_timeout(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u32_t *timeout;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .timeout = arg_u32n(NULL, NULL, "<u32:TIMEOUT>", 0, 1, "touchlink target timeout, in second"),
        .help = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.timeout->count > 0) {
        esp_zb_zdo_touchlink_target_set_timeout(argtable.timeout->val[0]);
    } else {
        EXIT_ON_ERROR(ESP_ERR_NOT_SUPPORTED, cli_output_line("Get value is not supported."));
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_tl_rssi(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_int_t *rssi;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .rssi = arg_intn(NULL, NULL, "<int:RSSI>", 0, 1, "touchlink target rssi threshold"),
        .help = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.rssi->count > 0) {
        esp_zb_zdo_touchlink_set_rssi_threshold(argtable.rssi->ival[0]);
    } else {
        cli_output("%d\n", esp_zb_zdo_touchlink_get_rssi_threshold());
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_tl_key(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_hex_t *key;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .key = arg_hexn(NULL, NULL, "<hex:KEY128>", 0, 1, "network key, in HEX format"),
        .help = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.key->count > 0) {
        EXIT_ON_FALSE(argtable.key->hsize[0] == 16, ESP_ERR_INVALID_ARG);
        esp_zb_zdo_touchlink_set_master_key(argtable.key->hval[0]);
    } else {
        EXIT_ON_ERROR(ESP_ERR_NOT_SUPPORTED, cli_output_line("Get value is not supported."));
    }

exit:
    arg_hex_free(argtable.key);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

DECLARE_ESP_ZB_CLI_CMD(role,    cli_role,,    "Get/Set the Zigbee role of a device");
DECLARE_ESP_ZB_CLI_CMD(panid,   cli_panid,,   "Get/Set the (extended) PAN ID of the node");
DECLARE_ESP_ZB_CLI_CMD(address, cli_address,, "Get/Set the (extended) address of the node");
DECLARE_ESP_ZB_CLI_CMD(channel, cli_channel,,  "Get/Set 802.15.4 channels for network");
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(network, "Network configuration",
    ESP_ZB_CLI_SUBCMD(type,     cli_nwk_type,     "Get/Set the network type"),
    ESP_ZB_CLI_SUBCMD(key,      cli_nwk_key,      "Get/Set the network key"),
    ESP_ZB_CLI_SUBCMD(legacy,   cli_nwk_legacy,   "Enable/Disable legacy device support"),
    ESP_ZB_CLI_SUBCMD(childmax, cli_nwk_childmax, "Get/Set max children number"),
    ESP_ZB_CLI_SUBCMD(open,     cli_nwk_open,     "Open local network"),
    ESP_ZB_CLI_SUBCMD(close,    cli_nwk_close,    "Close local network"),
    ESP_ZB_CLI_SUBCMD(scan,     cli_nwk_scan,     "Scan for network"),
    ESP_ZB_CLI_SUBCMD(ed_scan,  cli_nwk_ed_scan,  "Scan for energy detect on channels"),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(ic, "Install code configuration",
    ESP_ZB_CLI_SUBCMD(add,    cli_ic_add,    "Add install code for a device"),
    ESP_ZB_CLI_SUBCMD(remove, cli_ic_remove, "Remove install code for a device"),
    ESP_ZB_CLI_SUBCMD(set,    cli_ic_set,    "Set install code on device"),
    ESP_ZB_CLI_SUBCMD(get,    cli_ic_get,    "Get install code on device"),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(bdb_comm, "Perform BDB Commissioning",
    ESP_ZB_CLI_SUBCMD(channel, cli_bdb_channel, "Get/Set channels to perform commissioning"),
    ESP_ZB_CLI_SUBCMD(mode,    cli_bdb_mode,    "Get current mode of commissioning"),
    ESP_ZB_CLI_SUBCMD(start,   cli_bdb_start,   "Start bdb commissioning"),
    ESP_ZB_CLI_SUBCMD(cancel,  cli_bdb_cancel,  "Cancel commissioning process"),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(tl, "TouchLink configuration",
    ESP_ZB_CLI_SUBCMD(timeout, cli_tl_timeout, "Get/Set touchlink target timeout"),
    ESP_ZB_CLI_SUBCMD(rssi,    cli_tl_rssi,    "Get/Set touchlink target rssi threshold"),
    ESP_ZB_CLI_SUBCMD(key,     cli_tl_key,     "Get/Set touchlink master key"),
);