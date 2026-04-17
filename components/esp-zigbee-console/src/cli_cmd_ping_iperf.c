/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_zigbee_console.h"
#include "cli_cmd.h"
#include "zb_data/zb_custom_clusters/ping_iperf_test.h"

#define TAG "cli_cmd_ping_iperf"

static void cli_ping_finish_callback(ezb_err_t result) { esp_zb_console_notify_result(result); }

static void cli_iperf_finish_callback(void) { esp_zb_console_notify_result(EZB_ERR_NONE); }

static ezb_err_t cli_ping(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_addr_t *dst_addr;
        arg_u8_t   *dst_ep;
        arg_u8_t   *src_ep;
        arg_u16_t  *payload_len;
        arg_u32_t  *timeout;
        arg_end_t  *end;
    } argtable = {
        .dst_addr    = arg_addrn("d", "dst-addr", "<addr:ADDR>", 1, 1, "destination address"),
        .dst_ep      = arg_u8n(NULL, "dst-ep", "<u8:EID>", 1, 1, "destination endpoint id"),
        .src_ep      = arg_u8n("e", "src-ep", "<u8:EID>", 1, 1, "source endpoint id"),
        .payload_len = arg_u16n("l", "payload-len", "<u16:DATA>", 1, 1, "payload len of the command"),
        .timeout     = arg_u32n("t", "timeout", "<u32:DATA>", 0, 1, "time to wait for response in millisecond, default: 2000"),
        .end         = arg_end(2),
    };

    ezb_err_t ret = EZB_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    ezb_ping_req_info_t ping_info = {
        .dst_short_addr = argtable.dst_addr->addr[0].u.addr16,
        .dst_ep         = argtable.dst_ep->val[0],
        .payload_len    = argtable.payload_len->val[0],
        .src_ep         = argtable.src_ep->val[0],
        .timeout        = 2000,
    };
    if (argtable.timeout->count > 0) {
        ping_info.timeout = argtable.timeout->val[0];
    }
    EXIT_ON_ERROR(ezb_zcl_ping_iperf_test_cluster_ping_req(&ping_info, cli_ping_finish_callback));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_iperf_start(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_addr_t *dst_addr;
        arg_u8_t   *dst_ep;
        arg_u8_t   *src_ep;
        arg_u16_t  *iperf_duration;
        arg_u16_t  *iperf_interval;
        arg_u16_t  *payload_len;
        arg_end_t  *end;
    } argtable = {
        .dst_addr       = arg_addrn("d", "dst-addr", "<addr:ADDR>", 1, 1, "destination address"),
        .dst_ep         = arg_u8n(NULL, "dst-ep", "<u8:EID>", 1, 1, "destination endpoint id"),
        .src_ep         = arg_u8n("e", "src-ep", "<u8:EID>", 1, 1, "source endpoint id"),
        .iperf_duration = arg_u16n("t", "iperf-time", "<u16:TIME>", 1, 1, "iperf duration time in second"),
        .iperf_interval = arg_u16n("i", "iperf-interval", "<u16:TIME>", 0, 1, "iperf interval in millisecond, default: 20"),
        .payload_len    = arg_u16n("l", "payload-len", "<u16:DATA>", 1, 1, "payload len of the command"),
        .end            = arg_end(2),
    };

    ezb_err_t ret = EZB_ERR_NOT_FINISHED;

    uint16_t iperf_interval = 20;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.iperf_interval->count > 0) {
        iperf_interval = argtable.iperf_interval->val[0];
    }
    ezb_iperf_req_info_t iperf_req_info = {
        .direction      = EZB_ZCL_CMD_DIRECTION_TO_SRV,
        .dst_address    = argtable.dst_addr->addr[0].u.addr16,
        .dst_endpoint   = argtable.dst_ep->val[0],
        .iperf_duration = argtable.iperf_duration->val[0],
        .iperf_interval = iperf_interval,
        .payload_len    = argtable.payload_len->val[0],
        .src_endpoint   = argtable.src_ep->val[0],
    };
    EXIT_ON_ERROR(ezb_zcl_ping_iperf_set_iperf_info(&iperf_req_info));
    EXIT_ON_ERROR(ezb_zcl_ping_iperf_test_cluster_iperf_req(&iperf_req_info, cli_iperf_finish_callback));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_iperf_result(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t *role;
        arg_u8_t  *src_ep;
        arg_end_t *end;
    } argtable = {
        .role   = arg_strn("r", "role", "<sc:C|S>", 1, 1, "role of the iperf cluster"),
        .src_ep = arg_u8n("e", "src-ep", "<u8:EID>", 1, 1, "source endpoint id"),
        .end    = arg_end(2),
    };

    ezb_err_t ret = EZB_ERR_NONE;

    uint8_t role = EZB_ZCL_CLUSTER_SERVER;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    switch (argtable.role->sval[0][0]) {
    case 'C':
    case 'c':
        role = EZB_ZCL_CLUSTER_CLIENT;
        break;
    case 'S':
    case 's':
        role = EZB_ZCL_CLUSTER_SERVER;
        break;
    default:
        EXIT_ON_ERROR(EZB_ERR_INV_ARG, cli_output_line("invalid argument to option -r"));
        break;
    }
    float throughput = ezb_zcl_ping_iperf_get_iperf_result(argtable.src_ep->val[0], role);
    cli_output("iperf test throughput: %.3f kbps\n", throughput);

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

DECLARE_ESP_ZB_CLI_CMD(ping, cli_ping, , "Ping over Zigbee");

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(iperf, "Iperf over Zigbee",
    ESP_ZB_CLI_SUBCMD(start, cli_iperf_start, "Start iperf test"),
    ESP_ZB_CLI_SUBCMD(result, cli_iperf_result, "Print iperf result"),
);
