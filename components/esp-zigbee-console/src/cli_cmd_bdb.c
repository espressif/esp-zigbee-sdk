/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include "ezbee/nwk.h"
#include "ezbee/bdb.h"
#include "ezbee/touchlink.h"

#include "esp_zigbee_console.h"
#include "cli_cmd.h"

#define TAG "cli_cmd_bdb"

static ezb_err_t cli_role(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    static const char *role_string[] = {
        [EZB_NWK_DEVICE_TYPE_COORDINATOR] = "zc",
        [EZB_NWK_DEVICE_TYPE_ROUTER] = "zr",
        [EZB_NWK_DEVICE_TYPE_END_DEVICE] = "zed",
        [EZB_NWK_DEVICE_TYPE_NONE] = "unknown",
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
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.role->count > 0) {
        for (ezb_nwk_device_type_t role = EZB_NWK_DEVICE_TYPE_COORDINATOR; role < EZB_NWK_DEVICE_TYPE_NONE; role++) {
            if (!strcmp(argtable.role->sval[0], role_string[role])) {
                EXIT_NOW(ret = ezb_nwk_set_device_type(role));
            }
        }
        cli_output("unknown device role: %s\n", argtable.role->sval[0]);
        ret = EZB_ERR_NOT_SUPPORTED;
    } else {
        cli_output_line(role_string[ezb_nwk_get_device_type()]);
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_panid(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.extended->count > 0) {
        if (argtable.address->count > 0) {
            EXIT_ON_FALSE(argtable.address->addr[0].addr_type == CLI_ADDR_TYPE_64BIT, EZB_ERR_INV_ARG);
            ezb_set_use_extended_panid(&(ezb_extpanid_t){.u64 = argtable.address->addr[0].u.addr64});
        } else {
            ezb_extpanid_t extpanid;
            ezb_get_extended_panid(&extpanid);
            cli_output("0x%016" PRIx64 "\n", extpanid.u64);
        }
    } else {
        if (argtable.address->count > 0) {
            EXIT_ON_FALSE(argtable.address->addr[0].addr_type == CLI_ADDR_TYPE_16BIT, EZB_ERR_INV_ARG);
            ezb_set_panid(argtable.address->addr[0].u.addr16);
        } else {
            cli_output("0x%04hx\n", ezb_get_panid());
        }
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_address(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.extended->count > 0) {
        if (argtable.address->count > 0) {
            EXIT_ON_FALSE(argtable.address->addr[0].addr_type == CLI_ADDR_TYPE_64BIT, EZB_ERR_INV_ARG);
            ezb_set_extended_address(&(ezb_extaddr_t){.u64 = argtable.address->addr[0].u.addr64});
        } else {
            ezb_extaddr_t extaddr;
            ezb_get_extended_address(&extaddr);
            cli_output("0x%016" PRIx64 "\n", extaddr.u64);
        }
    } else {
        if (argtable.address->count > 0) {
            ezb_set_short_address(argtable.address->addr[0].u.addr16);
        } else {
            cli_output("0x%04hx\n", ezb_get_short_address());
        }
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_channel(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    /* Handle set / get */
    if (argc > 1) {
        uint32_t channel_mask = 0;
        if (argtable.channel->count > 0) {
            channel_mask = argtable.channel->val[0];
        }
        if (argtable.mask->count == 0) {
            channel_mask = 1 << channel_mask;
        }
        EXIT_ON_ERROR(ezb_set_channel_mask(channel_mask));
        /* Also set the channels for BDB commissioning */
        EXIT_ON_ERROR(ezb_bdb_set_primary_channel_set(channel_mask));
        EXIT_ON_ERROR(ezb_bdb_set_secondary_channel_set(channel_mask));
    } else {
        cli_output("Allowed Channel: 0x%08" PRIx32 "\n", ezb_get_channel_mask());
        cli_output("Current Channel: %d\n", ezb_get_current_channel());
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_rx_mode(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u8_t  *rx_on;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .rx_on = arg_u8n(NULL, NULL, "<RxMode>", 0, 1, "RxOnWhenIdle, 1: enable, 0: disable. Default: 1"),
        .help = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    /* Handle set / get */
    if (argc > 1) {
        ezb_set_rx_on_when_idle(argtable.rx_on->val[0] == 1);
    } else {
        cli_output("RxOnWhenIdle: %s\n", ezb_get_rx_on_when_idle() ? "enabled" : "disabled");
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Sub-commands of `network` */

static ezb_err_t cli_nwk_type(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.role->count > 0) {
        switch (argtable.role->sval[0][0]){
            case 'd':
                ezb_aps_secur_enable_distributed_security(true);
                break;
            case 'c':
                ezb_aps_secur_enable_distributed_security(false);
                break;
            default:
                EXIT_ON_ERROR(EZB_ERR_INV_ARG, cli_output("unknown network type: %s\n", argtable.role->sval[0]));
                break;
        }
    } else {
        cli_output("setting: %s\n", ezb_aps_secur_is_distributed_security() ? "distributed" : "centralized");
        if (ezb_bdb_dev_joined()) {
            cli_output("current on: %s\n", ezb_aps_secur_is_distributed_security() ? "distributed" : "centralized");
        }
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_nwk_legacy(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    ezb_err_t ret = EZB_ERR_NONE;

    if (argc < 2) {
        /* TODO: Add support to get the SDK status. */
        cli_output_line("Get the legacy support status is not supported");
        ret = EZB_ERR_NOT_SUPPORTED;
    } else if (argc > 3) {
        ret = EZB_ERR_INV_ARG;
    } else if (!strcmp(argv[1], "enable")) {
        ezb_secur_set_tclk_exchange_required(false);
    } else if (!strcmp(argv[1], "disable")) {
        ezb_secur_set_tclk_exchange_required(true);
    } else {
        cli_output("Invalid option: %s, use \"enable\" or \"disable\"\n", argv[1]);
        ret = EZB_ERR_INV_ARG;
    }

    return ret;
}

static ezb_err_t cli_nwk_key(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.key->count > 0) {
        EXIT_ON_FALSE(argtable.key->hsize[0] == EZB_CCM_KEY_SIZE, EZB_ERR_INV_ARG);
        EXIT_ON_ERROR(ezb_secur_set_network_key(argtable.key->hval[0]));
    } else {
        uint8_t key[EZB_CCM_KEY_SIZE];
        EXIT_ON_ERROR(ezb_secur_get_network_key(key), cli_output_line("Fail to get network key."));
        cli_output_buffer(key, EZB_CCM_KEY_SIZE);
    }

exit:
    arg_hex_free(argtable.key);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_nwk_childmax(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.childmax->count > 0) {
        ezb_nwk_set_max_children(argtable.childmax->val[0]);
    } else {
        cli_output("%d\n", ezb_nwk_get_max_children());
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_nwk_open(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u8_t  *timeout;
        arg_end_t *end;
    } argtable = {
        .timeout = arg_u8n("t", NULL, "<u8:TIMEOUT>", 1, 1, "timeouts in second for opening"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_ERROR(ezb_bdb_open_network(argtable.timeout->val[0]), cli_output_line("Fail to open network."));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_nwk_close(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    ezb_err_t ret = EZB_ERR_NONE;

    EXIT_ON_FALSE(argc == 1, EZB_ERR_INV_ARG);

    EXIT_ON_ERROR(ezb_bdb_close_network(), cli_output_line("Fail to close network."));

exit:
    return ret;
}

static void cli_nwk_scan_cb(ezb_nwk_active_scan_result_t *result, void *user_ctx)
{
    static bool print_header = true;
    static const char *titles[] = {"Chnl", "PanID", "ExtPanID", "Router", "Status", "Cap"};
    static const uint8_t widths[] = {4, 8, 20, 8, 7, 3};

    if (print_header) {
        cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
        print_header = false;
    }

    if (result != NULL) {
        cli_output("| %2d | 0x%04hx | 0x%016" PRIx64 " | 0x%04hx | %5s | %c%c|\n",
            result->channel_number, result->panid, result->extpanid.u64, result->shortaddr,
            result->permit_join ? "Open" : "Close",
            result->router_capacity ? 'R' : ' ',
            result->enddev_capacity ? 'E' : ' ');
    } else {
        print_header = true;
        esp_zb_console_notify_result(EZB_ERR_NONE);
    }
}

static ezb_err_t cli_nwk_scan(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    uint32_t channel_mask = 0;
    if (argtable.channel->count > 0) {
        channel_mask = argtable.channel->val[0];
    }
    if (argtable.mask->count == 0) {
        channel_mask = 1 << channel_mask;
    }

    ezb_nwk_scan_req_t active_scan_req = {
        .scan_type = EZB_NWK_SCAN_TYPE_ACTIVE,
        .scan_duration = argtable.duration->count > 0 ? argtable.duration->val[0] : 3,
        .scan_channels = channel_mask,
        .active_scan_cb = cli_nwk_scan_cb,
    };
    EXIT_ON_ERROR(ezb_nwk_scan(&active_scan_req));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static void cli_nwk_ed_scan_cb(ezb_nwk_ed_scan_result_t *result, void *user_ctx)
{
    static bool print_header = true;
    static const char *titles[] = {"Chnl", "RSSI"};
    static const uint8_t widths[] = {4, 6};

    if (print_header) {
        cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
        print_header = false;
    }

    if (result != NULL) {
        cli_output("| %2d | %4d |\n", result->channel_number, result->max_rssi);
    } else {
        print_header = true;
        esp_zb_console_notify_result(EZB_ERR_NONE);
    }
}

static ezb_err_t cli_nwk_ed_scan(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    uint32_t channel_mask = 0;
    if (argtable.channel->count > 0) {
        channel_mask = argtable.channel->val[0];
    }
    if (argtable.mask->count == 0) {
        channel_mask = 1 << channel_mask;
    }

    ezb_nwk_scan_req_t energy_detect_req = {
        .scan_type = EZB_NWK_SCAN_TYPE_ED,
        .scan_duration = argtable.duration->count > 0 ? argtable.duration->val[0] : 3,
        .scan_channels = channel_mask,
        .ed_scan_cb = cli_nwk_ed_scan_cb,
    };
    EXIT_ON_ERROR(ezb_nwk_scan(&energy_detect_req));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Sub-commands of `linkkey` */

typedef enum linkkey_op_s {
    LKO_add,
    LKO_remove,
    LKO_set,
} linkkey_op_t;

static ezb_err_t cli_linkkey_op(linkkey_op_t op, esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t *type;
        arg_hex_t *key;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .type = arg_str0("t", "type", "<type:d|c>", "link key type: d: distributed, c: default global TC link key), default: c"),
        .key = arg_hexn(NULL, NULL, "<key128:KEY>", 1, 1, "link key, in HEX format"),
        .help = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;
    bool centralized = true; // true if type: c

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(argtable.key->hsize[0] == EZB_CCM_KEY_SIZE, EZB_ERR_INV_ARG);

    if (argtable.type->count > 0) {
        switch (argtable.type->sval[0][0]) {
            case 'd':
            case 'D':
                centralized = false;
                break;
            case 'c':
            case 'C':
                centralized = true;
                break;
            default:
                EXIT_ON_ERROR(EZB_ERR_INV_ARG, cli_output("%s: invalid argument to option --type\n", argv[0]));
                break;
        }
    }

    (void)centralized;

    switch (op) {
        case LKO_set:
            ezb_secur_set_global_link_key(argtable.key->hval[0]);
            break;
        case LKO_add:
        case LKO_remove:
            ret = EZB_ERR_NOT_SUPPORTED;
            break;
    }

exit:
    arg_hex_free(argtable.key);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_linkkey_add(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    return cli_linkkey_op(LKO_add, self, argc, argv);
}

static ezb_err_t cli_linkkey_remove(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    return cli_linkkey_op(LKO_remove, self, argc, argv);
}

static ezb_err_t cli_linkkey_set(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    return cli_linkkey_op(LKO_set, self, argc, argv);
}

/* Sub-commands of `ic` */

static ezb_err_t cli_ic_policy(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_int_t  *ic_policy;
        arg_end_t  *end;
    } argtable = {
        .ic_policy = arg_intn(NULL, NULL,  "<int:IC Policy>", 1, 1, "install code policy\n"
                                                                    "0 - Not support\n"
                                                                    "1 - Support\n"
                                                                    "2 - IC Required\n"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    switch (argtable.ic_policy->ival[0]) {
        case 0:
            ret = EZB_ERR_NOT_SUPPORTED;
            break;
        case 1:
            EXIT_ON_ERROR(ezb_secur_set_ic_required(false));
            break;
        case 2:
            EXIT_ON_ERROR(ezb_secur_set_ic_required(true));
            break;
        default:
            EXIT_NOW(ret = EZB_ERR_INV_ARG; cli_output("Unknown policy value: %d\n", argtable.ic_policy->ival[0]));
            break;
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_ic_add(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NONE;
    uint8_t ic_type;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(esp_zigbee_is_started(), EZB_ERR_INV_SIZE, cli_output_line("Please start Zigbee stack first"));
    EXIT_ON_FALSE(argtable.add_addr->addr->addr_type == CLI_ADDR_TYPE_64BIT, EZB_ERR_INV_ARG,
                  cli_output_line("IEEE address is required."));

    switch (argtable.ic_code->hsize[0]) {
      case 8:  ic_type = EZB_SECUR_IC_TYPE_48;  break;
      case 10: ic_type = EZB_SECUR_IC_TYPE_64;  break;
      case 14: ic_type = EZB_SECUR_IC_TYPE_96;  break;
      case 18: ic_type = EZB_SECUR_IC_TYPE_128; break;
      default:
        EXIT_NOW(ret = EZB_ERR_INV_ARG; cli_output("Install code incorrect length %d\n", argtable.ic_code->hsize[0]));
        break;
    }

    EXIT_ON_ERROR(ezb_secur_ic_add(&(ezb_extaddr_t){.u64 = argtable.add_addr->addr->u.addr64},
                                   ic_type, argtable.ic_code->hval[0]),
                  cli_output_line("Fail to add install code."));

exit:
    arg_hex_free(argtable.ic_code);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_ic_remove(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_addr_t *add_addr;
        arg_end_t  *end;
    } argtable = {
        .add_addr = arg_addrn(NULL, NULL, "<eui64:EUI64>", 1, 1, "IEEE address of the device"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(argtable.add_addr->addr->addr_type == CLI_ADDR_TYPE_64BIT, EZB_ERR_INV_ARG,
                  cli_output_line("IEEE address is required."));
    EXIT_ON_ERROR(ezb_secur_ic_remove(&(ezb_extaddr_t){.u64 = argtable.add_addr->addr->u.addr64}),
                  cli_output_line("Fail to remove install code."));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_ic_set(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_hex_t *ic_code;
        arg_end_t *end;
    } argtable = {
        .ic_code = arg_hexn(NULL, NULL, "<hex:IC>", 1, 1, "install code"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;
    uint8_t ic_type;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    switch (argtable.ic_code->hsize[0]) {
      case 8:  ic_type = EZB_SECUR_IC_TYPE_48;  break;
      case 10: ic_type = EZB_SECUR_IC_TYPE_64;  break;
      case 14: ic_type = EZB_SECUR_IC_TYPE_96;  break;
      case 18: ic_type = EZB_SECUR_IC_TYPE_128; break;
      default:
        EXIT_NOW(ret = EZB_ERR_INV_ARG; cli_output("Install code incorrect length %d\n", argtable.ic_code->hsize[0]));
        break;
    }

    EXIT_ON_ERROR(ezb_secur_ic_set(ic_type, argtable.ic_code->hval[0]), cli_output_line("Fail to set install code\n"));

exit:
    arg_hex_free(argtable.ic_code);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_ic_get(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    ezb_err_t ret = EZB_ERR_NONE;
    EXIT_ON_FALSE(argc == 1, EZB_ERR_INV_ARG);

    uint8_t ic_size[] = { 8, 10, 14, 18 };
    uint8_t ic[18];
    uint8_t ic_type = EZB_SECUR_IC_TYPE_MAX_NR;

    if (ezb_secur_ic_get(ic, &ic_type) == EZB_ERR_NONE) {
        cli_output_buffer(ic, ic_size[ic_type]);
    } else {
        cli_output_line("No install code configured.");
    }

exit:
    return ret;
}

/* Sub-commands of `bdb_comm` */

static ezb_err_t cli_bdb_channel(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

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
        EXIT_ON_ERROR(ezb_bdb_set_primary_channel_set(primary_channel_mask));
        EXIT_ON_ERROR(ezb_bdb_set_secondary_channel_set(secondary_channel_mask));
    } else {
        cli_output("Primary Channel: 0x%08" PRIx32 "\n", ezb_bdb_get_primary_channel_set());
        cli_output("Secondary Channel: 0x%08" PRIx32 "\n", ezb_bdb_get_secondary_channel_set());
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_bdb_mode(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    ezb_err_t ret = EZB_ERR_NONE;

    EXIT_ON_FALSE(argc == 1, EZB_ERR_INV_ARG);

    cli_output("0x%02hx\n", (uint8_t)ezb_bdb_get_commissioning_mode());

exit:
    return ret;
}

static ezb_err_t cli_bdb_start(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t *mode;
        arg_rem_t *rem_mode;
        arg_end_t *end;
    } argtable = {
        .mode = arg_strn(NULL, NULL, "<MODE>", 1, 4, "bdb commissioning mode"),
        .rem_mode = arg_rem("", "init|steer|form|bind|initiator|target"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    ezb_bdb_comm_mode_mask_t bdb_comm_mode = 0;

    if (argtable.mode->count > 0) {
        for (int i = 0; i < argtable.mode->count; i++) {
            if (!strcmp(argtable.mode->sval[i], "init")) {
                bdb_comm_mode |= EZB_BDB_MODE_INITIALIZATION;
            } else if (!strcmp(argtable.mode->sval[i], "steer")) {
                bdb_comm_mode |= EZB_BDB_MODE_NETWORK_STEERING;
            } else if (!strcmp(argtable.mode->sval[i], "form")) {
                bdb_comm_mode |= EZB_BDB_MODE_NETWORK_FORMATION;
            } else if (!strcmp(argtable.mode->sval[i], "bind")) {
                bdb_comm_mode |= EZB_BDB_MODE_FINDING_N_BINDING;
            } else if (!strcmp(argtable.mode->sval[i], "initiator")) {
                bdb_comm_mode |= EZB_BDB_MODE_TOUCHLINK_INITIATOR;
            } else if (!strcmp(argtable.mode->sval[i], "target")) {
                bdb_comm_mode |= EZB_BDB_MODE_TOUCHLINK_TARGET;
            } else {
                cli_output("Skip %s bdb commissioning mode: %s\n", "unknown", argtable.mode->sval[i]);
            }
        }
    }

    if (!esp_zigbee_is_started()) {
        EXIT_ON_ERROR(esp_zigbee_start(false), cli_output_line("Fail to start Zigbee stack."));
    }

    EXIT_ON_ERROR(ezb_bdb_start_top_level_commissioning(bdb_comm_mode),
                  cli_output_line("Fail to start bdb top level commissioning."));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_bdb_cancel(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t *mode;
        arg_end_t *end;
    } argtable = {
        .mode = arg_strn(NULL, NULL, "<steer|form|target>", 1, 1, "commissioning mode to cancel"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.mode->count > 0) {
        if (!strcmp(argtable.mode->sval[0], "steer")) {
            ret = ezb_bdb_cancel_steering();
        } else if (!strcmp(argtable.mode->sval[0], "form")) {
            ret = ezb_bdb_cancel_formation();
        } else if (!strcmp(argtable.mode->sval[0], "target")) {
            ret = ezb_bdb_cancel_touchlink_target();
        } else {
            cli_output("%s mode for cancelling:%s\n", "unsupported", argtable.mode->sval[0]);
        }
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Sub-commands of `tl` */
static ezb_err_t cli_tl_timeout(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.timeout->count > 0) {
        ezb_touchlink_set_target_timeout(argtable.timeout->val[0]);
    } else {
        cli_output("%d\n", ezb_touchlink_get_target_timeout());
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_tl_rssi(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.rssi->count > 0) {
        ezb_touchlink_set_rssi_threshold(argtable.rssi->ival[0]);
    } else {
        cli_output("%d\n", ezb_touchlink_get_rssi_threshold());
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_tl_key(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.key->count > 0) {
        EXIT_ON_FALSE(argtable.key->hsize[0] == 16, EZB_ERR_INV_ARG);
        ezb_touchlink_set_master_key(argtable.key->hval[0]);
    } else {
        uint8_t key[EZB_CCM_KEY_SIZE];
        EXIT_ON_ERROR(ezb_touchlink_get_master_key(key), cli_output_line("Fail to get master key."));
        cli_output_buffer(key, EZB_CCM_KEY_SIZE);
    }

exit:
    arg_hex_free(argtable.key);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_tl_keymask(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u16_t  *keymask;
        arg_lit_t *help;
        arg_end_t  *end;
    } argtable = {
        .keymask = arg_u16n(NULL, NULL,   "<u16:mask>", 1, 1, "Touchlink key mask\n"
                                                              "1 << 4  - master key\n"
                                                              "1 << 15 - certification key\n"),
        .help    = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    ezb_touchlink_set_key_bitmask(argtable.keymask->val[0]);

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

DECLARE_ESP_ZB_CLI_CMD(role,    cli_role,,    "Get/Set the Zigbee role of a device");
DECLARE_ESP_ZB_CLI_CMD(panid,   cli_panid,,   "Get/Set the (extended) PAN ID of the node");
DECLARE_ESP_ZB_CLI_CMD(address, cli_address,, "Get/Set the (extended) address of the node");
DECLARE_ESP_ZB_CLI_CMD(channel, cli_channel,, "Get/Set 802.15.4 channels for network");
DECLARE_ESP_ZB_CLI_CMD(rx_mode, cli_rx_mode,, "Get/Set RxOnWhenIdle");
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
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(linkkey, "Link Key Configuration",
    ESP_ZB_CLI_SUBCMD(add,    cli_linkkey_add,     "Add additional global link key"),
    ESP_ZB_CLI_SUBCMD(remove, cli_linkkey_remove,  "Remove additional global link key"),
    ESP_ZB_CLI_SUBCMD(set,    cli_linkkey_set,     "Set default global link key"),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(ic, "Install code configuration",
    ESP_ZB_CLI_SUBCMD(policy, cli_ic_policy, "Set install code policy"),
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
    ESP_ZB_CLI_SUBCMD(keymask, cli_tl_keymask, "Set touchlink master key mask"),
);
