/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include "ezbee/zdo.h"

#include "esp_zigbee_console.h"
#include "cli_cmd.h"

#define TAG "cli_cmd_zdo"

#define EZB_ADDR_IS_BROADCAST(addr) (addr >= 0xFFF8U)

static inline void cli_output_request_status(const char *request_name, uint16_t dest_addr, ezb_zdp_status_t status)
{
    cli_output("%s request to [addr:0x%04x] status: %d\n", request_name, dest_addr, status);
}

static inline bool zdo_req_is_multi_resp(uint16_t cluster_id)
{
    /* Require to add the broadcast request with multi-response here */
    switch (cluster_id) {
    case EZB_ZDO_CMD_MATCH_DESC_REQ:
    case EZB_ZDO_CMD_MGMT_NWK_UPDATE_REQ:
    case EZB_ZDO_CMD_PARENT_ANNCE:
        return true;
    default:
        return false;
        break;
    }
}

static inline void cli_notify_result(uint16_t    dst_nwk_addr,
                                     uint16_t    cluster_id,
                                     void       *user_ctx,
                                     const void *rsp,
                                     ezb_err_t   error)
{
    bool is_free = true;

    if (EZB_ADDR_IS_BROADCAST(dst_nwk_addr)) {
        if (zdo_req_is_multi_resp(cluster_id) && rsp != NULL) {
            is_free = false;
        }
    }

    if (is_free) {
        esp_zb_console_notify_result(error);
        free(user_ctx);
    }
}

static ezb_zdp_status_t cli_zdo_get_status(ezb_err_t error, uint8_t status, void *rsp)
{
    /* Status:
     * result->error == EZB_ERR_NONE: status = result->rsp ? result->rsp->status : SUCCESS
     * result->error == EZB_ERR_TIMEOUT: status = TIMEOUT
     * result->error == others: status = INV_REQUESTTYPE
     */
    if (error == EZB_ERR_NONE) {
        return rsp ? status : EZB_ZDP_STATUS_SUCCESS;
    } else if (error == EZB_ERR_TIMEOUT) {
        return EZB_ZDP_STATUS_TIMEOUT;
    } else {
        return EZB_ZDP_STATUS_INV_REQUESTTYPE;
    }
}

// /* Implementation of "zdo request" command */
static void cli_zdo_node_desc_cb(const ezb_zdo_node_desc_req_result_t *result, void *user_ctx)
{
    static const char *request_name = "node_desc";
    uint16_t           dst_nwk_addr = ((ezb_zdo_node_desc_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t   status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);
    if (status == EZB_ZDP_STATUS_SUCCESS && result->rsp) {
        cli_output_buffer(&result->rsp->node_desc, sizeof(ezb_af_node_desc_t));
    }

    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_NODE_DESC_REQ, user_ctx, result->rsp, result->error);
}

static void cli_zdo_power_desc_cb(const ezb_zdo_power_desc_req_result_t *result, void *user_ctx)
{
    static const char *request_name = "power_desc";
    uint16_t           dst_nwk_addr = ((ezb_zdo_power_desc_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t   status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);
    if (status == EZB_ZDP_STATUS_SUCCESS && result->rsp) {
        cli_output_buffer(&result->rsp->power_desc, sizeof(ezb_af_node_power_desc_t));
    }

    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_POWER_DESC_REQ, user_ctx, result->rsp, result->error);
}

static void cli_zdo_simple_desc_cb(const ezb_zdo_simple_desc_req_result_t *result, void *user_ctx)
{
    static const char *request_name = "simple_desc";
    uint16_t           dst_nwk_addr = ((ezb_zdo_simple_desc_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t   status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);
    if (status == EZB_ZDP_STATUS_SUCCESS && result->rsp) {
        cli_output("ep:%d profile:0x%04hx dev:0x%0hx dev_ver:0x%0x\n", result->rsp->desc.ep_id,
                   result->rsp->desc.app_profile_id, result->rsp->desc.app_device_id, result->rsp->desc.app_device_version);
        cli_output_array_u16("in", &(result->rsp->desc.app_cluster_list[0]), result->rsp->desc.app_input_cluster_count,
                             "0x%04x");
        cli_output_array_u16("out", &(result->rsp->desc.app_cluster_list[0]) + result->rsp->desc.app_input_cluster_count,
                             result->rsp->desc.app_output_cluster_count, "0x%04x");
    }

    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_SIMPLE_DESC_REQ, user_ctx, result->rsp, result->error);
}

static void cli_zdo_active_ep_cb(const ezb_zdo_active_ep_req_result_t *result, void *user_ctx)
{
    static const char *request_name = "active_ep";
    uint16_t           dst_nwk_addr = ((ezb_zdo_active_ep_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t   status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);
    if (status == EZB_ZDP_STATUS_SUCCESS && result->rsp) {
        cli_output_array_u8("active ep", result->rsp->active_ep_list, result->rsp->active_ep_count, "%hhu");
    }

    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_ACTIVE_EP_REQ, user_ctx, result->rsp, result->error);
}

static void cli_zdo_nwk_addr_cb(const ezb_zdo_addr_req_result_t *result, void *arg)
{
    static const char *request_name = "nwk_addr";
    uint16_t           dst_nwk_addr = ((ezb_zdo_nwk_addr_req_t *)arg)->dst_nwk_addr;
    ezb_zdp_status_t   status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);
    if (status == EZB_ZDP_STATUS_SUCCESS && result->rsp) {
        cli_output("nwk address: 0x%04" PRIx16 "\n", result->rsp->nwk_addr_remote_dev);
    }
    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_NWK_ADDR_REQ, arg, result->rsp, result->error);
}

static void cli_zdo_ieee_addr_cb(const ezb_zdo_ieee_addr_req_result_t *result, void *user_ctx)
{
    static const char *request_name = "ieee_addr";
    uint16_t           dst_nwk_addr = ((ezb_zdo_ieee_addr_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t   status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);
    if (status == EZB_ZDP_STATUS_SUCCESS && result->rsp) {
        cli_output("ieee address: 0x%016" PRIx64 "\n", *(uint64_t *)result->rsp->ieee_addr_remote_dev.u8);
    }

    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_IEEE_ADDR_REQ, user_ctx, result->rsp, result->error);
}

static void cli_output_neighbor_table(const ezb_zdp_nwk_mgmt_lqi_rsp_field_t *table_info)
{
    static const char   *titles[]        = {"Index", "ExtPanID", "NwkAddr", "MacAddr", "Type", "Rel", "Depth", "LQI"};
    static const uint8_t widths[]        = {5, 20, 8, 20, 5, 3, 5, 5};
    static const char   *dev_type_name[] = {
          [EZB_NWK_DEVICE_TYPE_COORDINATOR] = "ZC",
          [EZB_NWK_DEVICE_TYPE_ROUTER]      = "ZR",
          [EZB_NWK_DEVICE_TYPE_END_DEVICE]  = "ZED",
          [EZB_NWK_DEVICE_TYPE_NONE]        = "UNK",
    };
    static const char rel_name[] = {
        [EZB_NWK_RELATIONSHIP_PARENT]            = 'P', /* Parent */
        [EZB_NWK_RELATIONSHIP_CHILD]             = 'C', /* Child */
        [EZB_NWK_RELATIONSHIP_SIBLING]           = 'S', /* Sibling */
        [EZB_NWK_RELATIONSHIP_NONE_OF_THE_ABOVE] = 'O', /* Others */
        [4]                                      = 'c', /* Previous Child */
        [5]                                      = 'u', /* Unauthenticated Child */
    };

    uint8_t start_idx = table_info->start_index;
    cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
    for (int i = 0; i < table_info->neighbor_table_list_count; i++) {
        ezb_zdp_nwk_mgmt_lqi_neighbor_table_entry_t *record = &table_info->neighbor_table_list[i];

        cli_output("| %3d | 0x%016" PRIx64 " | 0x%04hx | 0x%016" PRIx64 " |", start_idx + i, record->extended_pan_id.u64,
                   record->nwk_addr, record->extended_addr.u64);
        cli_output(" %-s%s | %c |", dev_type_name[record->device_type],
                   record->permit_joining ? "*" : (record->device_type <= EZB_NWK_DEVICE_TYPE_ROUTER ? " " : ""),
                   rel_name[record->affinity]);
        cli_output(" %3d | %3d |", record->device_depth, record->lqa);
        cli_output("\n");
    }
}

static void cli_zdo_neighbor_table_cb(const ezb_zdo_nwk_mgmt_lqi_req_result_t *result, void *user_ctx)
{
    static const char          *request_name = "neighbors";
    bool                        done         = true;
    uint16_t                    dst_nwk_addr = ((ezb_zdo_nwk_mgmt_lqi_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t            status       = EZB_ZDP_STATUS_SUCCESS;
    ezb_zdo_nwk_mgmt_lqi_req_t *req          = user_ctx;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);
    if (status == EZB_ZDP_STATUS_SUCCESS && result->rsp) {
        cli_output_neighbor_table(result->rsp);
        if (result->rsp->start_index + result->rsp->neighbor_table_list_count < result->rsp->neighbor_table_entries) {
            /* There are unreported neighbor table entries, request for them. */
            req->field.start_index = result->rsp->start_index + result->rsp->neighbor_table_list_count;
            ezb_zdo_nwk_mgmt_lqi_req(req);
            done = false;
        }
    }

    if (done) {
        cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_MGMT_LQI_REQ, user_ctx, result->rsp, result->error);
    }
}

static void cli_output_bind_table(const ezb_zdp_nwk_mgmt_bind_rsp_field_t *table_info)
{
    static const char   *titles[] = {"Index", "Src_Addr", "Src_EP", "Cluster", "Dst_Addr", "Dst_EP"};
    static const uint8_t widths[] = {5, 20, 5, 8, 20, 5};

    uint8_t                              start_idx = table_info->start_index;
    ezb_zdp_nwk_mgmt_bind_table_entry_t *record    = table_info->binding_table_list;
    cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
    for (int i = 0; i < table_info->binding_table_list_count; i++) {
        cli_output("| %3d | 0x%016" PRIx64 " | %3d | 0x%04hx ", start_idx + i, record->src_addr.u64, record->src_ep,
                   record->cluster_id);
        switch (record->dst_addr_mode) {
        case EZB_APS_ADDR_MODE_16_GROUP_ENDP_NOT_PRESENT:
            cli_output("|       0x%04hx       | %3s |", record->dst_addr.group_addr.group, "N/A");
            break;
        case EZB_APS_ADDR_MODE_64_ENDP_PRESENT:
            cli_output("| 0x%016" PRIx64 " | %3d |", record->dst_addr.extended_addr.u64, record->dst_ep);
            break;
        default:
            /* Never reached */
            break;
        }
        cli_output("\n");
        record++;
    }
}

static void cli_zdo_bind_table_cb(const ezb_zdo_nwk_mgmt_bind_req_result_t *result, void *user_ctx)
{
    static const char           *request_name = "bindings";
    bool                         done         = true;
    uint16_t                     dst_nwk_addr = ((ezb_zdo_nwk_mgmt_bind_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t             status       = EZB_ZDP_STATUS_SUCCESS;
    ezb_zdo_nwk_mgmt_bind_req_t *req          = user_ctx;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);
    if (status == EZB_ZDP_STATUS_SUCCESS && result->rsp) {
        cli_output_bind_table(result->rsp);
        if (result->rsp->start_index + result->rsp->binding_table_list_count < result->rsp->binding_table_entries) {
            /* There are unreported binding table entries, request for them. */
            req->field.start_index = result->rsp->start_index + result->rsp->binding_table_list_count;
            ezb_zdo_nwk_mgmt_bind_req(req);
            done = false;
        }
    }

    if (done) {
        cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_MGMT_BIND_REQ, user_ctx, result->rsp, result->error);
    }
}

static ezb_err_t cli_zdo_request(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t  *request;
        arg_rem_t  *rem_req;
        arg_addr_t *address;
        arg_u8_t   *endpoint;
        arg_end_t  *end;
    } argtable = {
        .request  = arg_strn(NULL, NULL, "<INFO>", 1, 1, "information to request"),
        .rem_req  = arg_rem("", "node_desc|power_desc|simple_desc|active_ep|nwk_addr|ieee_addr|neighbors|routes|bindings"),
        .address  = arg_addrn("d", "dst-addr", "<addr:ADDR>", 1, 1, "address of interest"),
        .endpoint = arg_u8n("e", "endpoint", "<u8:EID>", 0, 1, "endpoint ID of interest"),
        .end      = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (!strcmp(argtable.request->sval[0], "nwk_addr")) {
        EXIT_ON_FALSE(argtable.address->addr->addr_type == CLI_ADDR_TYPE_64BIT, EZB_ERR_INV_ARG,
                      cli_output("%s %s:only ieee address is supported\n", argv[0], argv[1]));
    } else {
        EXIT_ON_FALSE(argtable.address->addr->addr_type == CLI_ADDR_TYPE_16BIT, EZB_ERR_INV_ARG,
                      cli_output("%s %s:only short address is supported\n", argv[0], argv[1]));
    }

    if (!strcmp(argtable.request->sval[0], "node_desc")) {
        ezb_zdo_node_desc_req_t *node_req    = malloc(sizeof(ezb_zdo_node_desc_req_t));
        node_req->dst_nwk_addr               = argtable.address->addr[0].u.addr16;
        node_req->field.nwk_addr_of_interest = node_req->dst_nwk_addr;
        node_req->cb                         = cli_zdo_node_desc_cb;
        node_req->user_ctx                   = node_req;
        ret                                  = ezb_zdo_node_desc_req(node_req);
    } else if (!strcmp(argtable.request->sval[0], "power_desc")) {
        ezb_zdo_power_desc_req_t *power_req   = malloc(sizeof(ezb_zdo_power_desc_req_t));
        power_req->dst_nwk_addr               = argtable.address->addr[0].u.addr16;
        power_req->field.nwk_addr_of_interest = power_req->dst_nwk_addr;
        power_req->cb                         = cli_zdo_power_desc_cb;
        power_req->user_ctx                   = power_req;
        ret                                   = ezb_zdo_power_desc_req(power_req);
    } else if (!strcmp(argtable.request->sval[0], "simple_desc")) {
        ezb_zdo_simple_desc_req_t *simple_req  = malloc(sizeof(ezb_zdo_simple_desc_req_t));
        simple_req->field.nwk_addr_of_interest = argtable.address->addr[0].u.addr16,
        simple_req->dst_nwk_addr               = argtable.address->addr[0].u.addr16;
        simple_req->field.endpoint             = argtable.endpoint->val[0];
        simple_req->cb                         = cli_zdo_simple_desc_cb;
        simple_req->user_ctx                   = simple_req;
        ret                                    = ezb_zdo_simple_desc_req(simple_req);
    } else if (!strcmp(argtable.request->sval[0], "active_ep")) {
        ezb_zdo_active_ep_req_t *active_req    = malloc(sizeof(ezb_zdo_active_ep_req_t));
        active_req->field.nwk_addr_of_interest = argtable.address->addr[0].u.addr16;
        active_req->dst_nwk_addr               = argtable.address->addr[0].u.addr16;
        active_req->cb                         = cli_zdo_active_ep_cb;
        active_req->user_ctx                   = active_req;
        ret                                    = ezb_zdo_active_ep_req(active_req);
    } else if (!strcmp(argtable.request->sval[0], "nwk_addr")) {
        ezb_zdo_nwk_addr_req_t *nwk_addr_req = malloc(sizeof(ezb_zdo_nwk_addr_req_t));
        nwk_addr_req->dst_nwk_addr           = 0xFFFD; /* Broadcast to all devices which macRxOnIdle = True. */
        memcpy(&nwk_addr_req->field.ieee_addr_of_interest, argtable.address->addr[0].u.u8, sizeof(ezb_extaddr_t));
        nwk_addr_req->field.request_type = 0;
        nwk_addr_req->field.start_index  = 0;
        nwk_addr_req->cb                 = cli_zdo_nwk_addr_cb;
        nwk_addr_req->user_ctx           = nwk_addr_req;
        ret                              = ezb_zdo_nwk_addr_req(nwk_addr_req);
    } else if (!strcmp(argtable.request->sval[0], "ieee_addr")) {
        ezb_zdo_ieee_addr_req_t *ieee_addr_req    = malloc(sizeof(ezb_zdo_ieee_addr_req_t));
        ieee_addr_req->dst_nwk_addr               = argtable.address->addr[0].u.addr16;
        ieee_addr_req->field.nwk_addr_of_interest = ieee_addr_req->dst_nwk_addr;
        ieee_addr_req->field.request_type         = 0;
        ieee_addr_req->field.start_index          = 0;
        ieee_addr_req->cb                         = cli_zdo_ieee_addr_cb;
        ieee_addr_req->user_ctx                   = ieee_addr_req;
        ret                                       = ezb_zdo_ieee_addr_req(ieee_addr_req);
    } else if (!strcmp(argtable.request->sval[0], "neighbors")) {
        ezb_zdo_nwk_mgmt_lqi_req_t *lqi_req = malloc(sizeof(ezb_zdo_nwk_mgmt_lqi_req_t));
        lqi_req->field.start_index          = 0;
        lqi_req->dst_nwk_addr               = argtable.address->addr[0].u.addr16;
        lqi_req->cb                         = cli_zdo_neighbor_table_cb;
        lqi_req->user_ctx                   = lqi_req;
        ret                                 = ezb_zdo_nwk_mgmt_lqi_req(lqi_req);
    } else if (!strcmp(argtable.request->sval[0], "routes")) {
        ret = EZB_ERR_NOT_SUPPORTED;
    } else if (!strcmp(argtable.request->sval[0], "bindings")) {
        ezb_zdo_nwk_mgmt_bind_req_t *bind_table_req = malloc(sizeof(ezb_zdo_nwk_mgmt_bind_req_t));
        bind_table_req->dst_nwk_addr                = argtable.address->addr[0].u.addr16;
        bind_table_req->field.start_index           = 0;
        bind_table_req->cb                          = cli_zdo_bind_table_cb;
        bind_table_req->user_ctx                    = bind_table_req;
        ret                                         = ezb_zdo_nwk_mgmt_bind_req(bind_table_req);
    } else {
        ret = EZB_ERR_NOT_FOUND;
    }

    if (ret == EZB_ERR_NOT_SUPPORTED) {
        cli_output("%s info type: %s\n", "unsupported", argtable.request->sval[0]);
    } else if (ret == EZB_ERR_NOT_FOUND) {
        cli_output("%s info type: %s\n", "unknown", argtable.request->sval[0]);
    } else if (ret == EZB_ERR_NONE) {
        /* Result SHALL be returned in zdo request callback */
        ret = EZB_ERR_NOT_FINISHED;
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static void cli_zdo_parent_annce_cb(const ezb_zdo_parent_annce_req_result_t *result, void *user_ctx)
{
    static const char          *request_name = "parent_annce";
    uint16_t                    dst_nwk_addr = ((ezb_zdo_parent_annce_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t            status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);
    if (status == EZB_ZDP_STATUS_SUCCESS && result->rsp) {
        cli_output_buffer(result->rsp->child_info, (sizeof(ezb_extaddr_t) * result->rsp->num_of_children));
    }

    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_PARENT_ANNCE, user_ctx, result->rsp, result->error);
}

static void cli_zdo_device_annce_cb(const ezb_zdo_device_annce_req_result_t *result, void *user_ctx)
{
    static const char          *request_name = "device_annce";
    uint16_t                    dst_nwk_addr = 0xFFFD;
    ezb_zdp_status_t            status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, EZB_ZDP_STATUS_SUCCESS, NULL);
    cli_output_request_status(request_name, dst_nwk_addr, status);
    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_PARENT_ANNCE, user_ctx, NULL, result->error);
}

/* Implementation of "zdo annce" command */

static ezb_err_t cli_zdo_annce(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_lit_t *parent;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .parent = arg_lit0("p", "parent", "Parent annce"),
        .help   = arg_lit0(NULL, "help", "Print this help message"),
        .end    = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(ezb_bdb_dev_joined(), EZB_ERR_INV_STATE, cli_output_line("Not on a network"));
    if (argtable.parent->count > 0) {
        ezb_zdo_parent_annce_req_t *req = malloc(sizeof(ezb_zdo_parent_annce_req_t));
        req->dst_nwk_addr               = 0xFFFC;
        req->cb                         = cli_zdo_parent_annce_cb;
        req->user_ctx                   = req;
        EXIT_ON_ERROR(ezb_zdo_parent_annce_req(req));
    } else {
        ezb_zdo_device_annce_req_t *req = malloc(sizeof(ezb_zdo_device_annce_req_t));
        req->cb                         = cli_zdo_device_annce_cb;
        req->user_ctx                   = req;
        EXIT_ON_ERROR(ezb_zdo_device_annce_req(req));
    }

exit:
    return ret;
}

/* Implementation of "zdo match" command */

static void cli_zdo_match_desc_cb(const ezb_zdo_match_desc_req_result_t *result, void *user_ctx)
{
    static const char *request_name = "match";
    uint16_t           dst_nwk_addr = ((ezb_zdo_match_desc_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t   status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);
    if (status == EZB_ZDP_STATUS_SUCCESS && result->rsp) {
        cli_output("matched device: nwk_addr: 0x%04hx, matched ep list: \n", result->rsp->nwk_addr_of_interest);
        cli_output("matched ep list: ");
        for (uint8_t i = 0; i < result->rsp->match_length; i++) {
            cli_output("%d ", result->rsp->match_list[i]);
        }
        cli_output_line("\n");
    }

    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_MATCH_DESC_REQ, user_ctx, result->rsp, result->error);
}

static ezb_err_t cli_zdo_match(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u16_t  *in_cluster;
        arg_u16_t  *out_cluster;
        arg_u16_t  *profile_id;
        arg_addr_t *address;
        arg_end_t  *end;
    } argtable = {
        .in_cluster  = arg_u16n("i", "in", "<u16:CID>", 0, 10, "in cluster ID"),
        .out_cluster = arg_u16n("o", "out", "<u16:CID>", 0, 10, "out cluster ID"),
        .profile_id  = arg_u16n("p", "profile", "<u16:PID>", 0, 1, "profile id (PID) to match, default: HA"),
        .address     = arg_addrn("d", "dst-addr", "<addr:ADDR>", 1, 1, "network address this request is to"),
        .end         = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(argtable.address->addr->addr_type == CLI_ADDR_TYPE_16BIT, EZB_ERR_INV_ARG);

    ezb_zdo_match_desc_req_t *req     = malloc(sizeof(ezb_zdo_match_desc_req_t));
    uint8_t                   in_num  = argtable.in_cluster->count;
    uint8_t                   out_num = argtable.out_cluster->count;

    req->field.profile_id       = EZB_AF_HA_PROFILE_ID;
    req->field.num_in_clusters  = in_num;
    req->field.num_out_clusters = out_num;
    req->field.cluster_list     = malloc((in_num + out_num) * sizeof(uint16_t));
    memcpy(req->field.cluster_list, argtable.in_cluster->val, in_num * sizeof(uint16_t));
    memcpy(req->field.cluster_list + in_num, argtable.out_cluster->val, out_num * sizeof(uint16_t));
    if (argtable.profile_id->count > 0) {
        req->field.profile_id = argtable.profile_id->val[0];
    }
    req->dst_nwk_addr               = argtable.address->addr[0].u.addr16;
    req->field.nwk_addr_of_interest = req->dst_nwk_addr;
    req->cb                         = cli_zdo_match_desc_cb;
    req->user_ctx                   = req;
    EXIT_ON_ERROR(ezb_zdo_match_desc_req(req));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Implementation of "zdo nwk_open" command */

static void cli_zdo_permit_join_cb(const ezb_zdo_nwk_mgmt_permit_joining_req_result_t *result, void *user_ctx)
{
    static const char *request_name = "permit_join";
    uint16_t           dst_nwk_addr = ((ezb_zdo_nwk_mgmt_permit_joining_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t   status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);
    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_MGMT_PERMIT_JOINING_REQ, user_ctx, result->rsp, result->error);
}

static ezb_err_t cli_zdo_permit_join(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u8_t   *timeout;
        arg_addr_t *address;
        arg_end_t  *end;
    } argtable = {
        .timeout = arg_u8n("t", "timeout", "<u8:TIMEOUT>", 0, 1, "timeout in seconds for network opening, default: 60"),
        .address = arg_addrn("d", "dst-addr", "<addr:ADDR>", 1, 1, "network address this request is to"),
        .end     = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(argtable.address->addr->addr_type == CLI_ADDR_TYPE_16BIT, EZB_ERR_INV_ARG);

    ezb_zdo_nwk_mgmt_permit_joining_req_t *req = malloc(sizeof(ezb_zdo_nwk_mgmt_permit_joining_req_t));
    req->field.permit_duration                 = 60;
    if (argtable.timeout->count > 0) {
        req->field.permit_duration = argtable.timeout->val[0];
    }
    req->field.tc_significance = 0x01; /* This field should always be '0x01'. */
    req->dst_nwk_addr          = argtable.address->addr[0].u.addr16;
    req->cb                    = cli_zdo_permit_join_cb;
    req->user_ctx              = req;
    EXIT_ON_ERROR(ezb_zdo_nwk_mgmt_permit_joining_req(req));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Implementation of "zdo nwk_leave" command */
static void cli_zdo_leave_cb(const ezb_zdo_nwk_mgmt_leave_req_result_t *result, void *user_ctx)
{
    static const char *request_name = "leave";
    uint16_t           dst_nwk_addr = ((ezb_zdo_nwk_mgmt_leave_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t   status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);

    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_MGMT_LEAVE_REQ, user_ctx, result->rsp, result->error);
}

static ezb_err_t cli_zdo_nwk_leave(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
        .end     = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(argtable.address->addr->addr_type == CLI_ADDR_TYPE_16BIT, EZB_ERR_INV_ARG);

    ezb_zdo_nwk_mgmt_leave_req_t *req = calloc(1, sizeof(ezb_zdo_nwk_mgmt_leave_req_t));
    if (argtable.rejoin->count > 0) {
        req->field.rejoin = 1;
    }
    if (argtable.remove->count > 0) {
        req->field.remove_children = 1;
    }
    req->dst_nwk_addr = argtable.address->addr[0].u.addr16;
    req->cb           = cli_zdo_leave_cb;
    req->user_ctx     = req;
    EXIT_ON_ERROR(ezb_zdo_nwk_mgmt_leave_req(req));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Implementation of "zdo bind" command */
static void cli_zdo_bind_cb(const ezb_zdp_bind_req_result_t *result, void *user_ctx)
{
    static const char *request_name = "bind";
    uint16_t           dst_nwk_addr = ((ezb_zdo_bind_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t   status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);

    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_BIND_REQ, user_ctx, result->rsp, result->error);
}

static void cli_zdo_unbind_cb(const ezb_zdp_bind_req_result_t *result, void *user_ctx)
{
    static const char *request_name = "unbind";
    uint16_t           dst_nwk_addr = ((ezb_zdo_unbind_req_t *)user_ctx)->dst_nwk_addr;
    ezb_zdp_status_t   status       = EZB_ZDP_STATUS_SUCCESS;

    assert(result);
    status = cli_zdo_get_status(result->error, result->rsp ? result->rsp->status : EZB_ZDP_STATUS_SUCCESS, result->rsp);
    cli_output_request_status(request_name, dst_nwk_addr, status);

    cli_notify_result(dst_nwk_addr, EZB_ZDO_CMD_UNBIND_REQ, user_ctx, result->rsp, result->error);
}

static ezb_err_t cli_zdo_bind(esp_zb_cli_cmd_t *self, int argc, char **argv)
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
        .remove   = arg_lit0("r", "remove", "Remove the binding"),
        .cluster  = arg_u16n("c", "cluster", "<u16:CID>", 1, 1, "cluster id of binding"),
        .src_ep   = arg_u8n("S", "src-ep", "<u8:EID>", 1, 1, "endpoint id of binding source"),
        .src_addr = arg_addrn("s", "src-addr", "<addr:ADDR>", 1, 1, "address of binding source"),
        .dst_ep   = arg_u8n("D", "dst-ep", "<u8:EID>", 0, 1, "endpoint id of binding destination"),
        .dst_addr = arg_addrn("d", "dst-addr", "<addr:ADDR>", 1, 1, "address of binding destination"),
        .end      = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NOT_FINISHED;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    ezb_zdo_bind_req_t *req = malloc(sizeof(ezb_zdo_bind_req_t));
    req->field.cluster_id   = argtable.cluster->val[0];
    /* Populate dst information of binding */
    if (argtable.dst_addr->addr[0].addr_type == CLI_ADDR_TYPE_16BIT) {
        req->field.dst_ep                    = 0;
        req->field.dst_addr_mode             = EZB_APS_ADDR_MODE_16_GROUP_ENDP_NOT_PRESENT;
        req->field.dst_addr.group_addr.group = argtable.dst_addr->addr[0].u.addr16;
    } else {
        EXIT_ON_FALSE(argtable.dst_ep->count > 0, EZB_ERR_INV_ARG, cli_output("dst-ep is required\n"));
        req->field.dst_ep        = argtable.dst_ep->val[0];
        req->field.dst_addr_mode = EZB_APS_ADDR_MODE_64_ENDP_PRESENT;
        memcpy(req->field.dst_addr.extended_addr.u8, argtable.dst_addr->addr[0].u.u8, sizeof(ezb_extaddr_t));
    }

    /* Populate src information of binding */
    req->field.src_ep = argtable.src_ep->val[0];
    if (argtable.src_addr->addr[0].addr_type == CLI_ADDR_TYPE_16BIT) {
        req->dst_nwk_addr = argtable.src_addr->addr[0].u.addr16;
    } else {
        ezb_extaddr_t extaddr = {0};
        memcpy(&extaddr, argtable.src_addr->addr[0].u.u8, sizeof(ezb_extaddr_t));
        ezb_address_short_by_extended(&extaddr, &req->dst_nwk_addr);
    }
    EXIT_ON_ERROR(ezb_address_extended_by_short(req->dst_nwk_addr, &req->field.src_addr));
    if (argtable.remove->count > 0) {
        ezb_zdo_unbind_req_t *unbind_req = (ezb_zdo_unbind_req_t *)req;
        unbind_req->cb                   = cli_zdo_unbind_cb;
        unbind_req->user_ctx             = unbind_req;
        EXIT_ON_ERROR(ezb_zdo_unbind_req(unbind_req));
    } else {
        req->cb       = (ezb_zdo_bind_req_callback_t)cli_zdo_bind_cb;
        req->user_ctx = req;
        EXIT_ON_ERROR(ezb_zdo_bind_req(req));
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_power_desc(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u16_t *power_desc;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .power_desc = arg_u16n(NULL, NULL, "<u16:DESC>", 0, 1, "Power descriptor of the device"),
        .help       = arg_lit0(NULL, "help", "Print this help message"),
        .end        = arg_end(2),
    };

    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.power_desc->count > 0) {
        ezb_af_node_power_desc_t power_desc;
        memcpy(&power_desc, &argtable.power_desc->val[0], sizeof(power_desc));
        ezb_af_set_node_power_desc(&power_desc);
    } else {
        cli_output_buffer((void *)ezb_af_get_node_power_desc(), sizeof(ezb_af_node_power_desc_t));
    }

exit:
    return ret;
}

static ezb_err_t cli_node_desc(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u16_t *node_flags;
        arg_u8_t  *mac_capability_flags;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .node_flags           = arg_u16n("n", "node-flags", "<u16:FLAGS>", 0, 1, "Node flags of the device"),
        .mac_capability_flags = arg_u8n("m", "mac-capability-flags", "<u8:FLAGS>", 0, 1, "MAC capability flags of the device"),
        .help                 = arg_lit0(NULL, "help", "Print this help message"),
        .end                  = arg_end(2),
    };

    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(argtable.help->count == 0, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    ezb_af_node_desc_t node_desc = {0};
    memcpy(&node_desc, ezb_af_get_node_desc(), sizeof(ezb_af_node_desc_t));
    if (argtable.node_flags->count == 0 && argtable.mac_capability_flags->count == 0) {
        cli_output_buffer((void *)&node_desc, sizeof(ezb_af_node_desc_t));
    } else {
        ret = EZB_ERR_NOT_SUPPORTED;
    }

exit:
    return ret;
}

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(zdo, "Zigbee Device Object management",
    ESP_ZB_CLI_SUBCMD(request, cli_zdo_request, "Request information from node"),
    ESP_ZB_CLI_SUBCMD(annce, cli_zdo_annce, "Announce current node"),
    ESP_ZB_CLI_SUBCMD(match, cli_zdo_match, "Get matched devices"),
    ESP_ZB_CLI_SUBCMD(bind, cli_zdo_bind, "Request the node to bind to device"),
    ESP_ZB_CLI_SUBCMD(nwk_open, cli_zdo_permit_join, "Request the node to open the network"),
    ESP_ZB_CLI_SUBCMD(nwk_leave, cli_zdo_nwk_leave, "Request the node to leave the network"),
);

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(descriptors, "Configure Device descriptors",
    ESP_ZB_CLI_SUBCMD(power, cli_power_desc, "Get/Set node power descriptor"),
    ESP_ZB_CLI_SUBCMD(node, cli_node_desc, "Get/Set node descriptor"),
);
