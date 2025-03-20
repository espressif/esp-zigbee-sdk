/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>

#include "esp_check.h"
#include "esp_zigbee_console.h"
#include "cli_cmd.h"
#include "zb_data/zb_custom_clusters/custom_common.h"

#define TAG "cli_cmd_ping_iperf"

static esp_err_t cli_ping(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_addr_t *dst_addr;
        arg_u8_t   *dst_ep;
        arg_u8_t   *src_ep;
        arg_u16_t  *payload_len;
        arg_end_t  *end;
    } argtable = {
        .dst_addr      = arg_addrn("d", "dst-addr",    "<addr:ADDR>", 1, 1, "destination address"),
        .dst_ep        = arg_u8n(NULL,  "dst-ep",      "<u8:EID>",    1, 1, "destination endpoint id"),
        .src_ep        = arg_u8n("e",   "src-ep",      "<u8:EID>",    1, 1, "source endpoint id"),
        .payload_len   = arg_u16n("l",  "payload-len", "<u16:DATA>",  1, 1, "payload len of the command"),
        .end = arg_end(2),
    };

    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    esp_zb_ping_req_info_t ping_info = {
        .dst_short_addr = argtable.dst_addr->addr[0].u.short_addr,
        .dst_ep         = argtable.dst_ep->val[0],
        .payload_len    = argtable.payload_len->val[0],
        .src_ep         = argtable.src_ep->val[0]
    };

    ret = esp_zb_ping_iperf_test_cluster_ping_req(&ping_info);
    
exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_iperf_start(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
        .dst_addr       = arg_addrn("d", "dst-addr",       "<addr:ADDR>", 1, 1, "destination address"),
        .dst_ep         = arg_u8n(NULL,  "dst-ep",         "<u8:EID>",    1, 1, "destination endpoint id"),
        .src_ep         = arg_u8n("e",   "src-ep",         "<u8:EID>",    1, 1, "source endpoint id"),
        .iperf_duration = arg_u16n("t",  "iperf-time",     "<u16:TIME>",  1, 1, "iperf duration time in second"),
        .iperf_interval = arg_u16n("i",  "iperf-interval", "<u16:TIME>",  0, 1, "iperf interval in millisecond, default: 20"),
        .payload_len    = arg_u16n("l",  "payload-len",    "<u16:DATA>",  1, 1, "payload len of the command"),
        .end = arg_end(2),
    };

    esp_err_t ret = ESP_OK;

    uint16_t iperf_interval = 20;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.iperf_interval->count > 0) {
        iperf_interval = argtable.iperf_interval->val[0];
    }
    esp_zb_iperf_req_info_t iperf_req_info = {
        .direction      = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .dst_address    = argtable.dst_addr->addr[0].u.short_addr,
        .dst_endpoint   = argtable.dst_ep->val[0],
        .iperf_duration = argtable.iperf_duration->val[0],
        .iperf_interval = iperf_interval,
        .payload_len    = argtable.payload_len->val[0],
        .src_endpoint   = argtable.src_ep->val[0],
    };
    EXIT_ON_ERROR(esp_zb_ping_iperf_set_iperf_info(&iperf_req_info));

    ret = esp_zb_ping_iperf_test_cluster_iperf_req(&iperf_req_info);

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_iperf_result(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t *role;
        arg_u8_t  *src_ep;
        arg_end_t *end;
    } argtable = {
        .role   = arg_strn("r", "role",   "<sc:C|S>", 1, 1, "role of the iperf cluster"),
        .src_ep = arg_u8n("e",  "src-ep", "<u8:EID>", 1, 1, "source endpoint id"),
        .end = arg_end(2),
    };

    esp_err_t ret = ESP_OK;

    esp_zb_zcl_cluster_role_t role = ESP_ZB_ZCL_CLUSTER_SERVER_ROLE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    switch (argtable.role->sval[0][0]) {
        case 'C':
        case 'c':
            role = ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE;
            break;
        case 'S':
        case 's':
            role = ESP_ZB_ZCL_CLUSTER_SERVER_ROLE;
            break;
        default:
            EXIT_ON_ERROR(ESP_ERR_INVALID_ARG, cli_output_line("invalid argument to option -r"));
            break;
    }
    float throughput = esp_zb_ping_iperf_get_iperf_result(argtable.src_ep->val[0], role);
    cli_output("iperf test throughput: %.3f kbps\n", throughput);
    
exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}


DECLARE_ESP_ZB_CLI_CMD(ping, cli_ping,, "Ping over Zigbee");

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(iperf, "Iperf over Zigbee",
    ESP_ZB_CLI_SUBCMD(start,    cli_iperf_start,  "Start iperf test"),
    ESP_ZB_CLI_SUBCMD(result,   cli_iperf_result, "Print iperf result"),
);
