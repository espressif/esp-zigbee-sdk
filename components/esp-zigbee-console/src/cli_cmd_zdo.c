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
#include "zb_data/zcl.h"

#define TAG "cli_cmd_zdo"

static inline void cli_output_request_status(const char *request_name, uint16_t dest_addr, esp_zb_zdp_status_t status)
{
    cli_output("%s request to [addr:0x%04x] status: %d\n", request_name, dest_addr, status);
}

/* Implementation of "zdo request" command */

static void cli_zdo_node_desc_cb(esp_zb_zdp_status_t zdo_status, uint16_t addr, esp_zb_af_node_desc_t *node_desc, void *user_ctx)
{
    static const char *request_name = "node_desc";
    esp_zb_zdo_node_desc_req_param_t *req = user_ctx;
    cli_output_request_status(request_name, req->dst_nwk_addr, zdo_status);
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        cli_output_buffer(node_desc, sizeof(esp_zb_af_node_desc_t));
    }
    esp_zb_console_notify_result(ESP_OK);
    free(req);
}

static void cli_zdo_simple_desc_cb(esp_zb_zdp_status_t zdo_status, esp_zb_af_simple_desc_1_1_t *simple_desc, void *user_ctx)
{
    static const char *request_name = "simple_desc";
    esp_zb_zdo_simple_desc_req_param_t *req = user_ctx;
    cli_output_request_status(request_name, req->addr_of_interest, zdo_status);
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        cli_output("ep:%d profile:0x%04hx dev:0x%0hx dev_ver:0x%0hx\n", simple_desc->endpoint,
                                                                        simple_desc->app_profile_id,
                                                                        simple_desc->app_device_id,
                                                                        simple_desc->app_device_version);
#pragma GCC diagnostic push
#if __GNUC__ >= 9
#pragma GCC diagnostic ignored "-Waddress-of-packed-member"
#endif
        cli_output_array_u16("in", &(simple_desc->app_cluster_list[0]), simple_desc->app_input_cluster_count, "0x%04x");
        cli_output_array_u16("out", &(simple_desc->app_cluster_list[0]) + simple_desc->app_input_cluster_count,
                             simple_desc->app_output_cluster_count, "0x%04x");
#pragma GCC diagnostic pop
    }
    esp_zb_console_notify_result(ESP_OK);
    free(req);
}

static void cli_zdo_active_ep_cb(esp_zb_zdp_status_t zdo_status, uint8_t ep_count, uint8_t *ep_id_list, void *user_ctx)
{
    static const char *request_name = "active_ep";
    esp_zb_zdo_active_ep_req_param_t *req = user_ctx;
    cli_output_request_status(request_name, req->addr_of_interest, zdo_status);
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        cli_output_array_u8("active ep", ep_id_list, ep_count, "%hhu");
    }
    esp_zb_console_notify_result(ESP_OK);
    free(req);
}

static void cli_zdo_nwk_addr_cb(esp_zb_zdp_status_t zdo_status, uint16_t nwk_addr, void *user_ctx)
{
    static const char *request_name = "nwk_addr";
    esp_zb_zdo_ieee_addr_req_param_t *req = user_ctx;
    cli_output_request_status(request_name, req->addr_of_interest, zdo_status);
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        cli_output("nwk address: 0x%04" PRIx16 "\n", nwk_addr);
    }
    esp_zb_console_notify_result(ESP_OK);
    free(req);
}

static void cli_zdo_ieee_addr_cb(esp_zb_zdp_status_t zdo_status, esp_zb_ieee_addr_t ieee_addr, void *user_ctx)
{
    static const char *request_name = "ieee_addr";
    esp_zb_zdo_ieee_addr_req_param_t *req = user_ctx;
    cli_output_request_status(request_name, req->addr_of_interest, zdo_status);
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        cli_output("ieee address: 0x%016" PRIx64 "\n", *(uint64_t *)ieee_addr);
    }
    esp_zb_console_notify_result(ESP_OK);
    free(req);
}

static void cli_output_neigbor_table(const esp_zb_zdo_mgmt_lqi_rsp_t *table_info)
{
    static const char *titles[] = {"Index", "ExtPanID", "NwkAddr", "MacAddr", "Type", "Rel", "Depth", "LQI"};
    static const uint8_t widths[] = {5, 20, 8, 20, 5, 3, 5, 5};
    static const char *dev_type_name[] = {
        [ESP_ZB_DEVICE_TYPE_COORDINATOR] = "ZC",
        [ESP_ZB_DEVICE_TYPE_ROUTER]      = "ZR",
        [ESP_ZB_DEVICE_TYPE_ED]          = "ZED",
        [ESP_ZB_DEVICE_TYPE_NONE]        = "UNK",
    };
    static const char rel_name[] = {
        [ESP_ZB_NWK_RELATIONSHIP_PARENT]                = 'P', /* Parent */
        [ESP_ZB_NWK_RELATIONSHIP_CHILD]                 = 'C', /* Child */
        [ESP_ZB_NWK_RELATIONSHIP_SIBLING]               = 'S', /* Sibling */
        [ESP_ZB_NWK_RELATIONSHIP_NONE_OF_THE_ABOVE]     = 'O', /* Others */
        [ESP_ZB_NWK_RELATIONSHIP_PREVIOUS_CHILD]        = 'c', /* Previous Child */
        [ESP_ZB_NWK_RELATIONSHIP_UNAUTHENTICATED_CHILD] = 'u', /* Unauthenticated Child */
    };

    uint8_t start_idx = table_info->start_index;
    cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
    for (int i = 0; i < table_info->neighbor_table_list_count; i++) {
        esp_zb_zdo_neighbor_table_list_record_t *record = &table_info->neighbor_table_list[i];

        cli_output("| %3d | 0x%016" PRIx64 " | 0x%04hx | 0x%016" PRIx64 " |",
                    start_idx + i, *(uint64_t *)record->extended_pan_id, record->network_addr, *(uint64_t *)record->extended_addr);
        cli_output(" %-s%s | %c |", dev_type_name[record->device_type],
                   record->permit_join ? "*" : (record->device_type <= ESP_ZB_DEVICE_TYPE_ROUTER ? " " : ""),
                   rel_name[record->relationship]);
        cli_output(" %3d | %3d |", record->depth, record->lqi);
        cli_output("\n");
    }
}

static void cli_zdo_neigbor_table_cb(const esp_zb_zdo_mgmt_lqi_rsp_t *table_info, void *user_ctx)
{
    static const char *request_name = "neighbors";
    bool done = true;
    esp_zb_zdo_mgmt_lqi_req_param_t *req = user_ctx;
    esp_zb_zdp_status_t zdo_status = table_info->status;
    cli_output_request_status(request_name, req->dst_addr, zdo_status);
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        cli_output_neigbor_table(table_info);

        if (table_info->start_index + table_info->neighbor_table_list_count < table_info->neighbor_table_entries) {
            /* There are unreported neighbor table entries, request for them. */
            req->start_index = table_info->start_index + table_info->neighbor_table_list_count;
            esp_zb_zdo_mgmt_lqi_req(req, cli_zdo_neigbor_table_cb, req);
            done = false;
        }
    }

    if (done) {
        esp_zb_console_notify_result(ESP_OK);
        free(req);
    }
}

static void cli_output_binding_table(const esp_zb_zdo_binding_table_info_t *table_info)
{
    static const char *titles[] = {"Index", "Src_Addr", "Src_EP", "Cluster", "Dst_Addr", "Dst_EP"};
    static const uint8_t widths[] = {5, 20, 5, 8, 20, 5};

    uint8_t start_idx = table_info->index;
    esp_zb_zdo_binding_table_record_t *record = table_info->record;
    cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
    for (int i = 0; i < table_info->count; i++) {
        cli_output("| %3d | 0x%016" PRIx64 " | %3d | 0x%04hx ",
                    start_idx + i, *(uint64_t *)record->src_address, record->src_endp, record->cluster_id);
        switch (record->dst_addr_mode) {
            case ESP_ZB_APS_ADDR_MODE_16_GROUP_ENDP_NOT_PRESENT:
                cli_output("|       0x%04hx       | %3s |", record->dst_address.addr_short, "N/A");
                break;
            case ESP_ZB_APS_ADDR_MODE_64_ENDP_PRESENT:
                cli_output("| 0x%016" PRIx64 " | %3d |", *(uint64_t*)record->dst_address.addr_long, record->dst_endp);
                break;
            default:
                /* Never reached */
                break;
        }
        cli_output("\n");

        record = record->next;
    }
}

static void cli_zdo_binding_table_cb(const esp_zb_zdo_binding_table_info_t *table_info, void *user_ctx)
{
    static const char *request_name = "bindings";
    bool done = true;
    esp_zb_zdo_mgmt_bind_param_t *req = user_ctx;
    esp_zb_zdp_status_t zdo_status = table_info->status;
    cli_output_request_status(request_name, req->dst_addr, zdo_status);
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        cli_output_binding_table(table_info);

        if (table_info->index + table_info->count < table_info->total) {
            /* There are unreported binding table entries, request for them. */
            req->start_index = table_info->index + table_info->count;
            esp_zb_zdo_binding_table_req(req, cli_zdo_binding_table_cb, req);
            done = false;
        }
    }

    if (done) {
        esp_zb_console_notify_result(ESP_OK);
        free(req);
    }
}

static esp_err_t cli_zdo_request(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t  *request;
        arg_rem_t  *rem_req;
        arg_addr_t *address;
        arg_u8_t   *endpoint;
        arg_end_t  *end;
    } argtable = {
        .request  = arg_strn(NULL, NULL, "<INFO>", 1, 1, "information to request"),
        .rem_req  = arg_rem("", "node_desc|simple_desc|active_ep|nwk_addr|ieee_addr|neighbors|routes|bindings"),
        .address  = arg_addrn("d", "dst-addr", "<addr:ADDR>", 1, 1, "address of interest"),
        .endpoint = arg_u8n("e",   "endpoint", "<u8:EID>",    0, 1, "endpoint ID of interest"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (!strcmp(argtable.request->sval[0], "nwk_addr")) {
        EXIT_ON_FALSE(argtable.address->addr->addr_type == ESP_ZB_ZCL_ADDR_TYPE_IEEE, ESP_ERR_INVALID_ARG,
                    cli_output("%s %s:only ieee address is supported\n", argv[0], argv[1]));
    } else {
        EXIT_ON_FALSE(argtable.address->addr->addr_type == ESP_ZB_ZCL_ADDR_TYPE_SHORT, ESP_ERR_INVALID_ARG,
                    cli_output("%s %s:only short address is supported\n", argv[0], argv[1]));
    }

    if (!strcmp(argtable.request->sval[0], "node_desc")) {
        esp_zb_zdo_node_desc_req_param_t *nd_req = malloc(sizeof(esp_zb_zdo_node_desc_req_param_t));
        nd_req->dst_nwk_addr = argtable.address->addr[0].u.short_addr;
        esp_zb_zdo_node_desc_req(nd_req, cli_zdo_node_desc_cb, nd_req);
    } else if (!strcmp(argtable.request->sval[0], "simple_desc")) {
        esp_zb_zdo_simple_desc_req_param_t *sd_req = malloc(sizeof(esp_zb_zdo_simple_desc_req_param_t));
        sd_req->addr_of_interest = argtable.address->addr[0].u.short_addr,
        sd_req->endpoint = argtable.endpoint->val[0];
        esp_zb_zdo_simple_desc_req(sd_req, cli_zdo_simple_desc_cb, sd_req);
    } else if (!strcmp(argtable.request->sval[0], "active_ep")) {
        esp_zb_zdo_active_ep_req_param_t *ae_req = malloc(sizeof(esp_zb_zdo_active_ep_req_param_t));
        ae_req->addr_of_interest = argtable.address->addr[0].u.short_addr;
        esp_zb_zdo_active_ep_req(ae_req, cli_zdo_active_ep_cb, ae_req);
    } else if (!strcmp(argtable.request->sval[0], "nwk_addr")) {
        esp_zb_zdo_nwk_addr_req_param_t *na_req = malloc(sizeof(esp_zb_zdo_nwk_addr_req_param_t));
        na_req->dst_nwk_addr = 0xFFFD; /* Broadcast to all devices which macRxOnIdle = True. */
        memcpy(na_req->ieee_addr_of_interest, argtable.address->addr[0].u.ieee_addr, sizeof(esp_zb_ieee_addr_t));
        na_req->request_type = 0;
        na_req->start_index = 0;
        esp_zb_zdo_nwk_addr_req(na_req, cli_zdo_nwk_addr_cb, na_req);
    } else if (!strcmp(argtable.request->sval[0], "ieee_addr")) {
        esp_zb_zdo_ieee_addr_req_param_t *ia_req = malloc(sizeof(esp_zb_zdo_ieee_addr_req_param_t));
        ia_req->dst_nwk_addr = argtable.address->addr[0].u.short_addr;
        ia_req->addr_of_interest = ia_req->dst_nwk_addr;
        ia_req->request_type = 0;
        ia_req->start_index = 0;
        esp_zb_zdo_ieee_addr_req(ia_req, cli_zdo_ieee_addr_cb, ia_req);
    } else if (!strcmp(argtable.request->sval[0], "neighbors")) {
        esp_zb_zdo_mgmt_lqi_req_param_t *ml_req = malloc(sizeof(esp_zb_zdo_mgmt_lqi_req_param_t));
        ml_req->dst_addr = argtable.address->addr[0].u.short_addr;
        ml_req->start_index = 0;
        esp_zb_zdo_mgmt_lqi_req(ml_req, cli_zdo_neigbor_table_cb, ml_req);
    } else if (!strcmp(argtable.request->sval[0], "routes")) {
        ret = ESP_ERR_NOT_SUPPORTED;
    } else if (!strcmp(argtable.request->sval[0], "bindings")) {
        esp_zb_zdo_mgmt_bind_param_t *mb_req = malloc(sizeof(esp_zb_zdo_mgmt_bind_param_t));
        mb_req->dst_addr = argtable.address->addr[0].u.short_addr;
        mb_req->start_index = 0;
        esp_zb_zdo_binding_table_req(mb_req, cli_zdo_binding_table_cb, mb_req);
    } else {
        ret = ESP_ERR_NOT_FOUND;
    }

    if (ret == ESP_ERR_NOT_SUPPORTED) {
        cli_output("%s info type: %s\n", "unsupported", argtable.request->sval[0]);
    } else if (ret == ESP_ERR_NOT_FOUND) {
        cli_output("%s info type: %s\n", "unknown", argtable.request->sval[0]);
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Implementation of "zdo annce" command */

static esp_err_t cli_zdo_annce(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    esp_err_t ret = ESP_OK;
    EXIT_ON_FALSE(argc == 1, ESP_ERR_INVALID_ARG);
    EXIT_ON_FALSE(esp_zb_bdb_dev_joined(), ESP_ERR_INVALID_STATE, cli_output_line("Not on a network"));
    esp_zb_zdo_device_announcement_req();

exit:
    return ret;
}

/* Implementation of "zdo match" command */

static void cli_zdo_match_desc_cb(esp_zb_zdp_status_t zdo_status, uint16_t addr, uint8_t endpoint, void *user_ctx)
{
    static const char *request_name = "match";
    esp_zb_zdo_match_desc_req_param_t *req = user_ctx;
    cli_output_request_status(request_name, req->addr_of_interest, zdo_status);
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        cli_output("matched device: 0x%04hx:%d\n", addr, endpoint);
    }
    esp_zb_console_notify_result(ESP_OK);
    free(req);
}

static esp_err_t cli_zdo_match(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u16_t  *in_cluster;
        arg_u16_t  *out_cluster;
        arg_u16_t  *profile_id;
        arg_addr_t *address;
        arg_end_t  *end;
    } argtable = {
        .in_cluster  = arg_u16n("i",  "in",       "<u16:CID>",   0, 10, "in cluster ID"),
        .out_cluster = arg_u16n("o",  "out",      "<u16:CID>",   0, 10, "out cluster ID"),
        .profile_id  = arg_u16n("p",  "profile",  "<u16:PID>",   0, 1,  "profile id (PID) to match, default: HA"),
        .address     = arg_addrn("d", "dst-addr", "<addr:ADDR>", 1, 1,  "network address this request is to"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(argtable.address->addr->addr_type == ESP_ZB_ZCL_ADDR_TYPE_SHORT, ESP_ERR_INVALID_ARG);

    esp_zb_zdo_match_desc_req_param_t *req = malloc(sizeof(esp_zb_zdo_match_desc_req_param_t));
    uint8_t in_num = argtable.in_cluster->count;
    uint8_t out_num = argtable.out_cluster->count;

    req->profile_id = ESP_ZB_AF_HA_PROFILE_ID;
    req->num_in_clusters = in_num;
    req->num_out_clusters = out_num;
    req->cluster_list = malloc(in_num + out_num);
    memcpy(req->cluster_list, argtable.in_cluster->val, in_num);
    memcpy(req->cluster_list + in_num, argtable.out_cluster->val, out_num);
    if (argtable.profile_id->count > 0) {
        req->profile_id = argtable.profile_id->val[0];
    }
    req->dst_nwk_addr = argtable.address->addr[0].u.short_addr;
    req->addr_of_interest = req->dst_nwk_addr;
    EXIT_ON_ERROR(esp_zb_zdo_match_cluster(req, cli_zdo_match_desc_cb, req));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Implementation of "zdo nwk_open" command */

static void cli_zdo_permit_join_cb(esp_zb_zdp_status_t zdo_status, void *user_ctx)
{
    static const char *request_name = "permit_join";
    esp_zb_zdo_permit_joining_req_param_t *req = user_ctx;
    cli_output_request_status(request_name, req->dst_nwk_addr, zdo_status);
    esp_zb_console_notify_result(ESP_OK);
    free(req);
}

static esp_err_t cli_zdo_nwk_open(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u8_t   *timeout;
        arg_addr_t *address;
        arg_end_t  *end;
    } argtable = {
        .timeout = arg_u8n("t",   "timeout",  "<u8:TIMEOUT>", 0, 1, "timeout in seconds for network opening, default: 60"),
        .address = arg_addrn("d", "dst-addr", "<addr:ADDR>",  1, 1, "network address this request is to"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(argtable.address->addr->addr_type == ESP_ZB_ZCL_ADDR_TYPE_SHORT, ESP_ERR_INVALID_ARG);

    esp_zb_zdo_permit_joining_req_param_t *req = malloc(sizeof(esp_zb_zdo_permit_joining_req_param_t));
    req->permit_duration = 60;
    if (argtable.timeout->count > 0) {
        req->permit_duration = argtable.timeout->val[0];
    }
    req->tc_significance = 0x01;  /* This field should always be '0x01'. */
    req->dst_nwk_addr = argtable.address->addr[0].u.short_addr;
    esp_zb_zdo_permit_joining_req(req, cli_zdo_permit_join_cb, req);

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Implementation of "zdo nwk_leave" command */

static void cli_zdo_leave_cb(esp_zb_zdp_status_t zdo_status, void *user_ctx)
{
    static const char *request_name = "leave";
    esp_zb_zdo_mgmt_leave_req_param_t *req = user_ctx;
    cli_output_request_status(request_name, req->dst_nwk_addr, zdo_status);
    esp_zb_console_notify_result(ESP_OK);
    free(req);
}

static esp_err_t cli_zdo_nwk_leave(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_lit_t  *remove;
        arg_lit_t  *rejoin;
        arg_addr_t *address;
        arg_end_t  *end;
    } argtable = {
        .remove  = arg_lit0("c", "remove", "Remove children"),
        .rejoin  = arg_lit0("r", "rejoin", "Rejoin after leave"),
        .address = arg_addrn("d", "dst-addr", "<addr:ADDR>", 1, 1, "network address this request is to"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(argtable.address->addr->addr_type == ESP_ZB_ZCL_ADDR_TYPE_SHORT, ESP_ERR_INVALID_ARG);

    esp_zb_zdo_mgmt_leave_req_param_t *req = calloc(1, sizeof(esp_zb_zdo_mgmt_leave_req_param_t));
    if (argtable.rejoin->count > 0) {
        req->rejoin = 1;
    }
    if (argtable.remove->count > 0) {
        req->remove_children = 1;
    }
    req->dst_nwk_addr = argtable.address->addr[0].u.short_addr;
    esp_zb_zdo_device_leave_req(req, cli_zdo_leave_cb, req);

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Implementation of "zdo bind" command */

static void cli_zdo_bind_cb(esp_zb_zdp_status_t zdo_status, void *user_ctx)
{
    static const char *request_name = "bind";
    esp_zb_zdo_bind_req_param_t *req = user_ctx;
    cli_output_request_status(request_name, req->req_dst_addr, zdo_status);
    esp_zb_console_notify_result(ESP_OK);
    free(req);
}

static void cli_zdo_unbind_cb(esp_zb_zdp_status_t zdo_status, void *user_ctx)
{
    static const char *request_name = "unbind";
    esp_zb_zdo_bind_req_param_t *req = user_ctx;
    cli_output_request_status(request_name, req->req_dst_addr, zdo_status);
    esp_zb_console_notify_result(ESP_OK);
    free(req);
}

static esp_err_t cli_zdo_bind(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_lit_t  *remove;
        arg_u16_t  *cluster;
        arg_u8_t   *src_ep;
        arg_u8_t   *dst_ep;
        arg_addr_t *src_addr;
        arg_addr_t *dst_addr;
        arg_end_t  *end;
    } argtable = {
        .remove   = arg_lit0("r",  "remove", "Remove the binding"),
        .cluster  = arg_u16n("c",  "cluster",   "<u16:CID>",   1, 1, "cluster id of binding"),
        .src_ep   = arg_u8n("S",   "src-ep",    "<u8:EID>",    1, 1, "endpoint id of binding source"),
        .src_addr = arg_addrn("s", "src-addr",  "<addr:ADDR>", 1, 1, "address of binding source"),
        .dst_ep   = arg_u8n("D",   "dst-ep",    "<u8:EID>",    0, 1, "endpoint id of binding destination"),
        .dst_addr = arg_addrn("d", "dst-addr",  "<addr:ADDR>", 1, 1, "address of binding destination"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    esp_zb_zdo_bind_req_param_t *req = malloc(sizeof(esp_zb_zdo_bind_req_param_t));
    req->cluster_id = argtable.cluster->val[0];
    /* Populate dst information of binding */
    if (argtable.dst_addr->addr[0].addr_type == ESP_ZB_ZCL_ADDR_TYPE_SHORT) {
        req->dst_endp = 0;
        req->dst_addr_mode = ESP_ZB_ZDO_BIND_DST_ADDR_MODE_16_BIT_GROUP;
        req->dst_address_u.addr_short = argtable.dst_addr->addr[0].u.short_addr;
    } else {
        EXIT_ON_FALSE(argtable.dst_ep->count > 0, ESP_ERR_INVALID_ARG, cli_output("dst-ep is required\n"));
        req->dst_endp = argtable.dst_ep->val[0];
        req->dst_addr_mode = ESP_ZB_ZDO_BIND_DST_ADDR_MODE_64_BIT_EXTENDED;
        memcpy(req->dst_address_u.addr_long, argtable.dst_addr->addr[0].u.ieee_addr, sizeof(esp_zb_ieee_addr_t));
    }

    /* Populate src information of binding */
    req->src_endp = argtable.src_ep->val[0];
    if (argtable.src_addr->addr[0].addr_type == ESP_ZB_ZCL_ADDR_TYPE_SHORT) {
        req->req_dst_addr = argtable.src_addr->addr[0].u.short_addr;
    } else {
        req->req_dst_addr = esp_zb_address_short_by_ieee(argtable.src_addr->addr[0].u.ieee_addr);
    }
    EXIT_ON_ERROR(esp_zb_ieee_address_by_short(req->req_dst_addr, req->src_address));
    if (argtable.remove->count > 0) {
        esp_zb_zdo_device_unbind_req(req, cli_zdo_unbind_cb, req);
    } else {
        esp_zb_zdo_device_bind_req(req, cli_zdo_bind_cb, req);
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(zdo, "Zigbee Device Object management",
    ESP_ZB_CLI_SUBCMD(request,   cli_zdo_request,   "Request information from node"),
    ESP_ZB_CLI_SUBCMD(annce,     cli_zdo_annce,     "Announce current node"),
    ESP_ZB_CLI_SUBCMD(match,     cli_zdo_match,     "Get matched devices"),
    ESP_ZB_CLI_SUBCMD(bind,      cli_zdo_bind,      "Request the node to bind to device"),
    ESP_ZB_CLI_SUBCMD(nwk_open,  cli_zdo_nwk_open,  "Request the node to open the network"),
    ESP_ZB_CLI_SUBCMD(nwk_leave, cli_zdo_nwk_leave, "Request the node to leave the network"),
);
