/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "data_stream_client.h"

esp_zigbee_customized_data_consumer_callback_t s_data_consumer_cb = NULL;

#define CMD_HDR_TO_RSP(header)                                                                                              \
    {                                                                                                                       \
        .dst_addr = header->src_addr, .dst_ep = header->src_ep, .src_ep = header->dst_ep, .cluster_id = header->cluster_id, \
        .manuf_code = header->manuf_code,                                                                                   \
        .fc         = {.manuf_specific  = EZB_ZCL_CMD_FC_IS_MANUF_SPEC(header->fc),                                         \
                       .direction       = (EZB_ZCL_CMD_FC_IS_TO_CLI_DIRECTION(header->fc) ? EZB_ZCL_CMD_DIRECTION_TO_SRV    \
                                                                                          : EZB_ZCL_CMD_DIRECTION_TO_CLI),  \
                       .dis_default_rsp = true},                                                                            \
    }

static ezb_err_t zcl_default_rsp_cmd_req(const ezb_zcl_cmd_hdr_t *header, ezb_zcl_status_t status)
{
    assert(header);
    if (EZB_ZCL_CMD_FC_IS_DIS_DEFAULT_RSP(header->fc)) {
        return EZB_ERR_NONE;
    }
    ezb_zcl_default_rsp_cmd_t cmd_req = {
        .cmd_ctrl = CMD_HDR_TO_RSP(header),
        .payload =
            {
                .rsp_to_cmd  = header->cmd_id,
                .tsn         = header->tsn,
                .status_code = status,
            },
    };
    return ezb_zcl_default_rsp_cmd_req(&cmd_req);
}

static ezb_zcl_status_t customized_data_stream_client_cmd_handler(const ezb_zcl_cmd_hdr_t *header,
                                                                  const uint8_t           *payload,
                                                                  uint16_t                 payload_length)
{
    ezb_zcl_status_t ret = EZB_ZCL_STATUS_SUCCESS;
    assert(header);

    if (header->cluster_id != ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_CLUSTER_ID) {
        ret = EZB_ZCL_STATUS_UNSUPPORTED_CLUSTER;
        goto exit;
    }
    if (!EZB_ZCL_CMD_FC_IS_TO_CLI_DIRECTION(header->fc)) {
        ret = EZB_ZCL_STATUS_INVALID_FIELD;
        goto exit;
    }
    switch (header->cmd_id) {
    case ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_QUERY_DATA_RSP_CMD_ID: {
        if (s_data_consumer_cb) {
            s_data_consumer_cb(payload, payload_length);
        }
    } break;
    default:
        ret = EZB_ZCL_STATUS_UNSUP_CMD;
        break;
    }

exit:
    if (ret != EZB_ZCL_STATUS_SUCCESS) {
        ret = zcl_default_rsp_cmd_req(header, ret) == EZB_ERR_NONE ? EZB_ZCL_STATUS_SUCCESS : EZB_ZCL_STATUS_FAIL;
    }
    return ret;
}

#define CUSTOMIZED_DATA_PRODUCER_CLI_SUPPORT_RECV_CMD_LIST       \
    {                                                            \
        ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_QUERY_DATA_RSP_CMD_ID, \
    }

#define CUSTOMIZED_DATA_PRODUCER_CLI_SUPPORT_SEND_CMD_LIST       \
    {                                                            \
        ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_QUERY_DATA_REQ_CMD_ID, \
    }

static uint8_t customized_data_stream_client_disc_cmd_handler(bool is_recv, uint8_t **list)
{
    static uint8_t recv_cmd_list[] = CUSTOMIZED_DATA_PRODUCER_CLI_SUPPORT_RECV_CMD_LIST;
    static uint8_t send_cmd_list[] = CUSTOMIZED_DATA_PRODUCER_CLI_SUPPORT_SEND_CMD_LIST;

    *list = is_recv ? recv_cmd_list : send_cmd_list;
    return is_recv ? sizeof(recv_cmd_list) / sizeof(recv_cmd_list[0]) : sizeof(send_cmd_list) / sizeof(send_cmd_list[0]);
}

void esp_zigbee_zcl_customized_data_stream_client_init(uint8_t ep_id)
{
    ezb_zcl_custom_cluster_handlers_t handlers = {
        .cluster_id     = ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_CLUSTER_ID,
        .cluster_role   = EZB_ZCL_CLUSTER_CLIENT,
        .process_cmd_cb = customized_data_stream_client_cmd_handler,
        .check_value_cb = NULL,
        .write_attr_cb  = NULL,
        .cmd_disc_cb    = customized_data_stream_client_disc_cmd_handler,
    };
    ezb_zcl_custom_cluster_handlers_register(&handlers);
}

void esp_zigbee_zcl_customized_data_stream_client_deinit(uint8_t ep_id) { (void)ep_id; }

ezb_err_t esp_zigbee_zcl_customized_data_stream_get_data_cmd_req(ezb_zcl_custom_cluster_cmd_t *cmd_req)
{
    return ezb_zcl_custom_cluster_cmd_req(cmd_req);
}

ezb_err_t esp_zigbee_zcl_customized_data_stream_client_set_data_customer(esp_zigbee_customized_data_consumer_callback_t cb)
{
    s_data_consumer_cb = cb;
    return EZB_ERR_NONE;
}
