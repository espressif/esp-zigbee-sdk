/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>

#include "esp_check.h"

#include "esp_zigbee_console.h"
#include "aps/esp_zigbee_aps.h"
#include "cmdline_parser.h"
#include "cli_cmd_aps.h"

#define TAG "cli_cmd_aps"

void esp_zb_cli_fill_aps_argtable(esp_zb_cli_aps_argtable_t *aps)
{
    aps->dst_addr = arg_addrn("d", "dst-addr", "<addr:ADDR>", 0, 1, "destination address");
    aps->dst_ep   = arg_u8n(NULL,  "dst-ep",   "<u8:EID>",    0, 1, "destination endpoint id");
    aps->src_ep   = arg_u8n("e",   "src-ep",   "<u8:EID>",    1, 1, "source endpoint id");
    aps->profile  = arg_u16n(NULL, "profile",  "<u16:PID>",   0, 1, "profile id of the command");
    aps->cluster  = arg_u16n("c",  "cluster",  "<u16:CID>",   1, 1, "cluster id of the command");
}

esp_err_t esp_zb_cli_parse_aps_dst(esp_zb_cli_aps_argtable_t *parsed_argtable, esp_zb_addr_u *dst_addr_u,
                                   uint8_t *dst_endpoint, esp_zb_aps_address_mode_t *address_mode,
                                   uint8_t *src_endpoint, uint16_t *cluster_id, uint16_t *profile_id)
{
    esp_err_t ret = ESP_OK;
    /* Fill "dst_addr", "dst_ep" and "addr_mode" */
    if (parsed_argtable->dst_addr->count > 0) {
        esp_zb_zcl_addr_t *dst_addr = &parsed_argtable->dst_addr->addr[0];
        esp_zb_aps_address_mode_t address_mode_select[][2] = {
            [ESP_ZB_ZCL_ADDR_TYPE_SHORT][0] = ESP_ZB_APS_ADDR_MODE_16_GROUP_ENDP_NOT_PRESENT,
            [ESP_ZB_ZCL_ADDR_TYPE_IEEE][0]  = ESP_ZB_APS_ADDR_MODE_64_PRESENT_ENDP_NOT_PRESENT,
            [ESP_ZB_ZCL_ADDR_TYPE_SHORT][1] = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
            [ESP_ZB_ZCL_ADDR_TYPE_IEEE][1]  = ESP_ZB_APS_ADDR_MODE_64_ENDP_PRESENT,
        };
        /* Copy parse address */
        memcpy(dst_addr_u, &dst_addr->u, sizeof(esp_zb_addr_u));
        
        if (parsed_argtable->dst_ep->count > 0) {
            *dst_endpoint = parsed_argtable->dst_ep->val[0];
        }
        *address_mode = address_mode_select[dst_addr->addr_type][parsed_argtable->dst_ep->count > 0 ? 1 : 0];
        EXIT_ON_FALSE(*address_mode !=  ESP_ZB_APS_ADDR_MODE_64_PRESENT_ENDP_NOT_PRESENT,
                      ESP_ERR_NOT_SUPPORTED, cli_output_line("Unsupported address mode, dst-ep is required"));
    }

    if (parsed_argtable->profile->count > 0 && profile_id) {
        *profile_id = parsed_argtable->profile->val[0];
    }
    if (parsed_argtable->src_ep->count > 0 && src_endpoint) {
        *src_endpoint = parsed_argtable->src_ep->val[0];
    }
    if (parsed_argtable->cluster->count > 0 && cluster_id) {
        *cluster_id = parsed_argtable->cluster->val[0];
    }

exit:
    return ret;
}

static void zb_apsde_data_confirm_handler(esp_zb_apsde_data_confirm_t confirm)
{
    if (confirm.status == 0x00) {
        cli_output_line("Send aps data frame successful"); 
        esp_zb_console_notify_result(ESP_OK);
    } else {
        cli_output("Send aps data frame failed, status: %d\n", confirm.status);
        esp_zb_console_notify_result(ESP_FAIL);
    }
    esp_zb_aps_data_confirm_handler_register(NULL);
}

static bool zb_apsde_data_indication_handler(esp_zb_apsde_data_ind_t ind)
{
    if (ind.status == 0x00) {
        cli_output("Received aps data frame successful, src ep %d src addr 0x%04x -> dst ep %d dst addr 0x%04x\n", 
                   ind.src_endpoint, ind.src_short_addr, ind.dst_endpoint, ind.dst_short_addr); 
        if (ind.asdu_length > 0) {
            cli_output_buffer(ind.asdu, ind.asdu_length);
        }
    } else {
        cli_output("Received aps data frame failed, status: %d\n", ind.status);
    }
    return false;
}

static esp_err_t cli_aps_send_raw(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        esp_zb_cli_aps_argtable_t aps;
        arg_hex_t  *payload;
        arg_u8_t   *radius;
        arg_end_t  *end;
    } argtable = {
        .payload = arg_hexn("p", "payload", "<hex:DATA>",  0, 1, "APS payload of the command, raw HEX data"),
        .radius  = arg_u8n("r",  "radius",  "<u8:RADIUS>", 0, 1, "Maximum transmission hops"),
        .end = arg_end(2),
    };

    esp_zb_cli_fill_aps_argtable(&argtable.aps);

    esp_err_t ret = ESP_ERR_NOT_FINISHED;
    /* Default request settings */
     esp_zb_apsde_data_req_t req_params = {
        .dst_addr_mode = ESP_ZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .tx_options = ESP_ZB_APSDE_TX_OPT_ACK_TX | ESP_ZB_APSDE_TX_OPT_FRAG_PERMITTED,
        .use_alias  = false,
        .radius     = 15,
    };

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));
    
    esp_zb_aps_address_mode_t addr_mode_temp = ESP_ZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT;
    EXIT_ON_ERROR(esp_zb_cli_parse_aps_dst(&argtable.aps,
                                           &req_params.dst_addr,
                                           &req_params.dst_endpoint,
                                           &addr_mode_temp,
                                           &req_params.src_endpoint,
                                           &req_params.cluster_id,
                                           &req_params.profile_id));

    req_params.dst_addr_mode = (uint8_t)addr_mode_temp; 

    if (argtable.payload->count > 0) {
        req_params.asdu_length = argtable.payload->hsize[0];
        req_params.asdu = argtable.payload->hval[0];
    }
    if (argtable.radius->count > 0) {
        req_params.radius = argtable.radius->val[0];
    }

    EXIT_ON_ERROR(esp_zb_aps_data_request(&req_params));
    esp_zb_aps_data_confirm_handler_register(&zb_apsde_data_confirm_handler);
    
exit:
    arg_hex_free(argtable.payload);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_aps_dump(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t *flag;
        arg_end_t *end;
    } argtable = {
        .flag = arg_strn(NULL, NULL, "<open|close>", 1, 1, "flag of dump aps indication frame"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (!strcmp(argtable.flag->sval[0], "open")) {
        esp_zb_aps_data_indication_handler_register(&zb_apsde_data_indication_handler);
    } else if (!strcmp(argtable.flag->sval[0], "close")) {
        esp_zb_aps_data_indication_handler_register(NULL);
    } else {
        EXIT_ON_ERROR(ESP_ERR_INVALID_ARG, cli_output_line("invalid arg for dump"));
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(aps, "Zigbee Application Support management",
    ESP_ZB_CLI_SUBCMD(send_raw, cli_aps_send_raw, "Send aps raw command"),
    ESP_ZB_CLI_SUBCMD(dump, cli_aps_dump, "Dump APS traffic"),
);
