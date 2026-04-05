/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <ezbee/zcl/zcl_type.h>

#include "esp_timer.h"
#include "esp_check.h"

#include "cli_util.h"
#include "ping_iperf_test.h"

#define TAG                        "ping_iperf_test"
#define IS_ADDRESS_BROADCAST(addr) ((addr) >= 0xfff8)

typedef struct iperf_context {
    iperf_finish_callback_t iperf_finish_cb;
    ezb_zcl_custom_cmd_t   *message_to_iperf;
    uint64_t                iperf_duration;
    int64_t                 iperf_start_time;
    uint64_t                iperf_packet_count;
    int64_t                 iperf_end_time;
    uint32_t                iperf_interval;
    uint16_t                iperf_data_len;
    uint8_t                 iperf_endpoint;
    bool                    client_in_progress;
    esp_timer_handle_t      iperf_timer;
} iperf_context_t;

typedef struct ping_context {
    ping_finish_callback_t ping_finish_cb;
    int64_t                ping_start_time;
    uint32_t               timeout;
    uint8_t                ping_tsn;
    bool                   is_in_progress;
    bool                   is_broadcast;
    esp_timer_handle_t     timeout_timer;
} ping_context_t;

static ezb_zcl_status_t zb_ping_iperf_set_iperf_attribute_val(uint8_t  endpoint,
                                                              uint8_t  cluster_role,
                                                              uint16_t attr_id,
                                                              void    *value_p);

static void ping_timeout_handler(void *arg);

static ping_context_t  ping_ctx  = {0};
static iperf_context_t iperf_ctx = {0};

static ezb_zcl_status_t ezb_zcl_ping_iperf_test_cluster_process_cmd_handler(const ezb_zcl_cmd_hdr_t *header,
                                                                            const uint8_t           *payload,
                                                                            uint16_t                 payload_length);

void ezb_zcl_ping_iperf_test_cluster_init(uint8_t ep_id)
{
    ezb_zcl_custom_cluster_handlers_t server_handlers = {
        .cluster_id     = EZB_ZCL_CLUSTER_ID_PING_IPERF_TEST,
        .cluster_role   = EZB_ZCL_CLUSTER_SERVER,
        .check_value_cb = NULL,
        .write_attr_cb  = NULL,
        .cmd_disc_cb    = NULL,
        .process_cmd_cb = ezb_zcl_ping_iperf_test_cluster_process_cmd_handler,
    };

    ezb_zcl_custom_cluster_handlers_t client_handlers = {
        .cluster_id     = EZB_ZCL_CLUSTER_ID_PING_IPERF_TEST,
        .cluster_role   = EZB_ZCL_CLUSTER_CLIENT,
        .check_value_cb = NULL,
        .write_attr_cb  = NULL,
        .cmd_disc_cb    = NULL,
        .process_cmd_cb = ezb_zcl_ping_iperf_test_cluster_process_cmd_handler,
    };
    ezb_zcl_custom_cluster_handlers_register(&server_handlers);
    ezb_zcl_custom_cluster_handlers_register(&client_handlers);
}

void ezb_zcl_ping_iperf_test_cluster_deinit(uint8_t ep_id) { (void)ep_id; }

ezb_zcl_cluster_desc_t ezb_zcl_ping_iperf_test_create_cluster_desc(ezb_ping_iperf_test_cluster_config_t *ping_iperf_test_cfg,
                                                                   uint8_t                               role_mask)
{
    ezb_zcl_cluster_desc_t               cluster_desc = NULL;
    ezb_ping_iperf_test_cluster_config_t cfg          = {0};
    ezb_zcl_custom_cluster_config_t      custom_cfg   = {
               .cluster_id  = EZB_ZCL_CLUSTER_ID_PING_IPERF_TEST,
               .init_func   = ezb_zcl_ping_iperf_test_cluster_init,
               .deinit_func = ezb_zcl_ping_iperf_test_cluster_deinit,
    };
    cluster_desc = ezb_zcl_custom_create_cluster_desc(&custom_cfg, role_mask);
    if (ping_iperf_test_cfg != NULL) {
        memcpy(&cfg, ping_iperf_test_cfg, sizeof(ezb_ping_iperf_test_cluster_config_t));
    }
    ezb_zcl_ping_iperf_test_cluster_desc_add_attr(cluster_desc, EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_THROUGHPUT, &cfg.throughput);
    ezb_zcl_ping_iperf_test_cluster_desc_add_attr(cluster_desc, EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DURATION,
                                                  &cfg.iperf_duration);
    ezb_zcl_ping_iperf_test_cluster_desc_add_attr(cluster_desc, EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DATA_LEN,
                                                  &cfg.iperf_data_len);
    ezb_zcl_ping_iperf_test_cluster_desc_add_attr(cluster_desc, EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_INTERVAL,
                                                  &cfg.iperf_interval);
    return cluster_desc;
}

ezb_err_t ezb_zcl_ping_iperf_test_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value_p)
{
    ezb_err_t ret         = EZB_ERR_NONE;
    uint8_t   attr_type   = EZB_ZCL_ATTR_TYPE_UNK;
    uint8_t   attr_access = EZB_ZCL_ATTR_ACCESS_READ_WRITE;
    switch (attr_id) {
    case EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_THROUGHPUT:
        attr_type   = EZB_ZCL_ATTR_TYPE_SINGLE;
        attr_access = EZB_ZCL_ATTR_ACCESS_READ_WRITE | EZB_ZCL_ATTR_ACCESS_REPORTING;
        break;
    case EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DATA_LEN:
    case EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DURATION:
    case EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_INTERVAL:
        attr_type = EZB_ZCL_ATTR_TYPE_UINT16;
        break;
    default:
        EXIT_ON_FALSE(0, EZB_ERR_INV_ARG);
    }
    EXIT_ON_ERROR(ezb_zcl_custom_cluster_desc_add_manuf_attr(cluster_desc, attr_id, attr_type, attr_access,
                                                             EZB_ZCL_STD_MANUF_CODE, value_p));
exit:
    return ret;
}

static void finish_ping(ezb_err_t result)
{
    ping_ctx.is_in_progress = false;
    if (ping_ctx.ping_finish_cb) {
        ping_ctx.ping_finish_cb(result);
        ping_ctx.ping_finish_cb = NULL;
    }
}

static void ping_timeout_handler_cancel(ezb_err_t result)
{
    if (ping_ctx.timeout_timer != NULL) {
        esp_timer_stop(ping_ctx.timeout_timer);
        esp_timer_delete(ping_ctx.timeout_timer);
        ping_ctx.timeout_timer = NULL;
    }
    finish_ping(result);
}

static void ping_timeout_handler(void *arg)
{
    esp_timer_handle_t timer = ping_ctx.timeout_timer;
    ping_ctx.timeout_timer   = NULL;
    if (timer != NULL) {
        esp_timer_delete(timer);
    }
    if (!ping_ctx.is_broadcast) {
        ESP_LOGE(TAG, "No ping response received, tsn: %d", ping_ctx.ping_tsn);
        finish_ping(EZB_ERR_FAIL);
    } else {
        ESP_LOGI(TAG, "Ping broadcast done, tsn: %d", ping_ctx.ping_tsn);
        finish_ping(EZB_ERR_NONE);
    }
}

static void ping_req_send_status_callback(ezb_zcl_cmd_cnf_t *info, void *data)
{
    if (info->status != EZB_ZCL_STATUS_SUCCESS) {
        ESP_LOGE(TAG, "Ping request failed, error: %d tsn: %d", info->status, ping_ctx.ping_tsn);
        ping_timeout_handler_cancel(EZB_ERR_FAIL);
    } else {
        ESP_LOGI(TAG, "Ping request success, tsn: %d", ping_ctx.ping_tsn);
    }
}

ezb_err_t ezb_zcl_ping_iperf_test_cluster_ping_req(const ezb_ping_req_info_t *info, ping_finish_callback_t ping_finish_cb)
{
    ezb_err_t            ret = EZB_ERR_NONE;
    ezb_zcl_custom_cmd_t req = {0};
    EXIT_ON_FALSE(!ping_ctx.is_in_progress, EZB_ERR_INV_STATE);
    ping_ctx.ping_tsn++;

    req.cmd_ctrl.dst_addr.addr_mode    = EZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    req.cmd_ctrl.dst_addr.u.short_addr = info->dst_short_addr;
    req.cmd_ctrl.src_ep                = info->src_ep;
    req.cmd_ctrl.dst_ep                = info->dst_ep;
    req.cmd_ctrl.cluster_id            = EZB_ZCL_CLUSTER_ID_PING_IPERF_TEST;
    req.cmd_ctrl.fc.direction          = EZB_ZCL_CMD_DIRECTION_TO_SRV;
    req.cmd_ctrl.fc.dis_default_rsp    = 1;
    req.cmd_ctrl.cnf_ctx.cb            = ping_req_send_status_callback;
    req.cmd_ctrl.cnf_ctx.user_ctx      = &ping_ctx;
    req.cmd_id                         = EZB_ZCL_CMD_PING_IPERF_TEST_ECHO;
    req.data_length                    = info->payload_len;
    req.data                           = malloc(info->payload_len);
    EXIT_ON_FALSE(req.data, EZB_ERR_NO_MEM);
    memset(req.data, 1, info->payload_len);
    ((uint8_t *)req.data)[0] = ping_ctx.ping_tsn;

    ping_ctx.is_broadcast    = IS_ADDRESS_BROADCAST(info->dst_short_addr);
    ping_ctx.ping_start_time = esp_timer_get_time();
    ping_ctx.timeout         = info->timeout;
    ping_ctx.ping_finish_cb  = ping_finish_cb;
    ping_ctx.timeout_timer   = NULL;
    ezb_zcl_custom_cmd_req(&req);

    const esp_timer_create_args_t timer_args = {.callback = &ping_timeout_handler, .arg = NULL, .name = "ping_timeout"};
    EXIT_ON_ERROR(esp_timer_create(&timer_args, &ping_ctx.timeout_timer));
    EXIT_ON_ERROR(esp_timer_start_once(ping_ctx.timeout_timer, ping_ctx.timeout * 1000ULL));
    ping_ctx.is_in_progress = true;
    ESP_LOGI(TAG, "Request to ping address: 0x%04x", req.cmd_ctrl.dst_addr.u.short_addr);

exit:
    if (req.data) {
        free(req.data);
    }
    if (ret != EZB_ERR_NONE && ping_ctx.timeout_timer) {
        esp_timer_delete(ping_ctx.timeout_timer);
        ping_ctx.timeout_timer = NULL;
    }
    return ret;
}

static ezb_zcl_status_t zb_ping_iperf_test_cluster_ping_test_request_handler(const ezb_zcl_cmd_hdr_t *header,
                                                                             const uint8_t           *payload,
                                                                             uint16_t                 payload_length)
{
    ESP_LOGI(TAG, "RECEIVE PING REQUEST");

    ezb_zcl_custom_cmd_t rsp           = {0};
    rsp.cmd_ctrl.dst_addr.addr_mode    = EZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    rsp.cmd_ctrl.dst_addr.u.short_addr = header->src_addr.u.short_addr;
    rsp.cmd_ctrl.src_ep                = header->dst_ep;
    rsp.cmd_ctrl.dst_ep                = header->src_ep;
    rsp.cmd_ctrl.cluster_id            = EZB_ZCL_CLUSTER_ID_PING_IPERF_TEST;
    rsp.cmd_ctrl.fc.direction          = EZB_ZCL_CMD_FC_IS_TO_CLI_DIRECTION(header->fc) ? EZB_ZCL_CMD_DIRECTION_TO_SRV
                                                                                        : EZB_ZCL_CMD_DIRECTION_TO_CLI;
    rsp.cmd_ctrl.fc.dis_default_rsp    = 1;
    rsp.cmd_id                         = EZB_ZCL_CMD_PING_IPERF_TEST_ECHO;
    rsp.data_length                    = payload_length;
    rsp.data                           = (uint8_t *)payload;
    ezb_zcl_custom_cmd_req(&rsp);
    ESP_LOGI(TAG, "Response to ping address: 0x%04x", rsp.cmd_ctrl.dst_addr.u.short_addr);
    return EZB_ZCL_STATUS_SUCCESS;
}

static ezb_zcl_status_t zb_ping_iperf_test_cluster_ping_test_response_handler(const ezb_zcl_cmd_hdr_t *header,
                                                                              const uint8_t           *payload,
                                                                              uint16_t                 payload_length)
{
    if (!ping_ctx.is_in_progress) {
        return EZB_ZCL_STATUS_SUCCESS;
    }

    uint8_t req_tsn = ((uint8_t *)payload)[0];
    ESP_LOGI(TAG, "RECEIVE PING RESPONSE, TSN: %d, ping_tsn: %d", req_tsn, ping_ctx.ping_tsn);
    if (req_tsn == ping_ctx.ping_tsn) {
        int64_t ping_rtt = (esp_timer_get_time() - ping_ctx.ping_start_time) / 1000;
        ESP_LOGI(TAG, "RECEIVE PING RESPONSE from 0x%04x with %d bytes, rtt: %lld ms", header->src_addr.u.short_addr,
                 payload_length, ping_rtt);
        if (!ping_ctx.is_broadcast) {
            ping_timeout_handler_cancel(EZB_ERR_NONE);
        }
    }

    return EZB_ZCL_STATUS_SUCCESS;
}

static ezb_zcl_status_t zb_ping_iperf_test_cluster_ping_test_handler(const ezb_zcl_cmd_hdr_t *header,
                                                                     const uint8_t           *payload,
                                                                     uint16_t                 payload_length)
{
    ezb_zcl_status_t ret = EZB_ZCL_STATUS_SUCCESS;
    uint8_t          dir = EZB_ZCL_CMD_FC_IS_TO_CLI_DIRECTION(header->fc) ? EZB_ZCL_CMD_DIRECTION_TO_CLI : EZB_ZCL_CMD_DIRECTION_TO_SRV;
    switch (dir) {
    case EZB_ZCL_CMD_DIRECTION_TO_SRV:
        ret = zb_ping_iperf_test_cluster_ping_test_request_handler(header, payload, payload_length);
        break;
    case EZB_ZCL_CMD_DIRECTION_TO_CLI:
        ret = zb_ping_iperf_test_cluster_ping_test_response_handler(header, payload, payload_length);
        break;
    default:
        break;
    }

    return ret;
}

/**
 * @brief Implementation of the iperf test.
 *
 *                       +-------------------+                 +------------------+
 *                       |      Client       |                 |      Server      |
 *                       +-------------------+                 +------------------+
 *                                | req1: command: IPERF_START           |
 *                save start time |------------------------------------->| get iperf start time
 *                                | req2: command: IPERF_PROCESS         |
 * calculate throughput when send |------------------------------------->| calculate throughput
 * successfully                   | req3: command: IPERF_PROCESS         |
 * calculate throughput when send |------------------------------------->| calculate throughput
 * successfully                   |             .                        |
 *                                |             .                        |
 *                                |             .                        |
 *                                | reqn: command: IPERF_PROCESS         |
 * calculate throughput when send |------------------------------------->| calculate throughput
 * successfully                   |                                      |
 *
 * The purpose of this implementation is to continuously measure the network throughput between the client
 * and the server during the test period and store the final test result for further analysis and verification.
 */
ezb_err_t ezb_zcl_ping_iperf_set_iperf_info(const ezb_iperf_req_info_t *info)
{
    ezb_err_t        ret            = EZB_ERR_NONE;
    ezb_zcl_status_t result         = EZB_ZCL_STATUS_SUCCESS;
    uint16_t         payload_len    = info->payload_len;
    uint16_t         iperf_interval = info->iperf_interval;
    uint16_t         iperf_duration = info->iperf_duration;
    result                          = zb_ping_iperf_set_iperf_attribute_val(info->src_endpoint, EZB_ZCL_CLUSTER_CLIENT,
                                                                            EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DURATION, &iperf_duration);
    ESP_RETURN_ON_FALSE(result == EZB_ZCL_STATUS_SUCCESS, EZB_ERR_FAIL, TAG, "Iperf has not been registered or is unavailable");
    result = zb_ping_iperf_set_iperf_attribute_val(info->src_endpoint, EZB_ZCL_CLUSTER_CLIENT,
                                                   EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DATA_LEN, &payload_len);
    ESP_RETURN_ON_FALSE(result == EZB_ZCL_STATUS_SUCCESS, EZB_ERR_FAIL, TAG,
                        "Error occurred while writing the data len attribute of iperf, status: %d", result);
    result = zb_ping_iperf_set_iperf_attribute_val(info->src_endpoint, EZB_ZCL_CLUSTER_CLIENT,
                                                   EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_INTERVAL, &iperf_interval);
    ESP_RETURN_ON_FALSE(result == EZB_ZCL_STATUS_SUCCESS, EZB_ERR_FAIL, TAG,
                        "Error occurred while writing the interval attribute of iperf, status: %d", result);

    return ret;
}

static ezb_zcl_status_t zb_ping_iperf_test_cluster_calculate_iperf(uint8_t endpoint, uint8_t cluster_role)
{
    ezb_zcl_status_t ret = EZB_ZCL_STATUS_SUCCESS;
    float     throughput = ((float)(iperf_ctx.iperf_packet_count) * (float)(iperf_ctx.iperf_data_len) * 8 * 1000) /
                       ((float)(iperf_ctx.iperf_end_time - iperf_ctx.iperf_start_time));
    ezb_zcl_status_t result = zb_ping_iperf_set_iperf_attribute_val(endpoint, cluster_role,
                                                                    EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_THROUGHPUT, &throughput);
    ESP_LOGI(TAG, "throughput: %.3f kbps, count: %llu", throughput, iperf_ctx.iperf_packet_count);
    ESP_RETURN_ON_FALSE(result == EZB_ZCL_STATUS_SUCCESS, result, TAG, "Fail to write throughput attribute: %d", result);

    return ret;
}

static void ipref_req_send_status_callback(ezb_zcl_cmd_cnf_t *info, void *data)
{
    (void)data;
    if (info->status == EZB_ZCL_STATUS_SUCCESS) {
        iperf_ctx.iperf_packet_count++;
        iperf_ctx.iperf_end_time = esp_timer_get_time();
        zb_ping_iperf_test_cluster_calculate_iperf(info->src_ep, EZB_ZCL_CLUSTER_CLIENT);
    } else {
        ESP_LOGE(TAG, "Fail to send: error: %d tsn: %d", info->status, info->tsn);
    }
}

static void do_iperf(void *arg)
{
    if (esp_timer_get_time() - iperf_ctx.iperf_start_time < iperf_ctx.iperf_duration) {
        ezb_zcl_custom_cmd_req(iperf_ctx.message_to_iperf);
        iperf_ctx.message_to_iperf->cmd_id = EZB_ZCL_CMD_PING_IPERF_TEST_IPERF_PROCESS;
        esp_timer_start_once(iperf_ctx.iperf_timer, iperf_ctx.iperf_interval * 1000ULL);
    } else {
        if (iperf_ctx.iperf_timer != NULL) {
            esp_timer_stop(iperf_ctx.iperf_timer);
            esp_timer_delete(iperf_ctx.iperf_timer);
            iperf_ctx.iperf_timer = NULL;
        }
        if (iperf_ctx.message_to_iperf) {
            free(iperf_ctx.message_to_iperf->data);
            iperf_ctx.message_to_iperf->data = NULL;
            free(iperf_ctx.message_to_iperf);
            iperf_ctx.message_to_iperf = NULL;
        }
        iperf_ctx.client_in_progress = false;
        if (iperf_ctx.iperf_finish_cb) {
            iperf_ctx.iperf_finish_cb();
            iperf_ctx.iperf_finish_cb = NULL;
        }
    }
}

static ezb_zcl_status_t zb_ping_iperf_set_iperf_attribute_val(uint8_t  endpoint,
                                                              uint8_t  cluster_role,
                                                              uint16_t attr_id,
                                                              void    *value_p)
{
    return ezb_zcl_set_attr_value(endpoint, EZB_ZCL_CLUSTER_ID_PING_IPERF_TEST, cluster_role, attr_id, EZB_ZCL_STD_MANUF_CODE,
                                  (uint8_t *)value_p, false);
}

static ezb_zcl_attr_desc_t zb_ping_iperf_get_iperf_attribute_val(uint8_t endpoint, uint8_t cluster_role, uint16_t attr_id)
{
    return ezb_zcl_get_attr_desc(endpoint, EZB_ZCL_CLUSTER_ID_PING_IPERF_TEST, cluster_role, attr_id, EZB_ZCL_STD_MANUF_CODE);
}

static ezb_err_t iperf_message_set(const ezb_iperf_req_info_t *info)
{
    ezb_err_t ret              = EZB_ERR_NONE;
    iperf_ctx.message_to_iperf = malloc(sizeof(ezb_zcl_custom_cmd_t));
    ESP_RETURN_ON_FALSE(iperf_ctx.message_to_iperf, EZB_ERR_FAIL, TAG, "Failed to allocate memory for iperf request data");
    iperf_ctx.message_to_iperf->cmd_ctrl.dst_ep                = info->dst_endpoint;
    iperf_ctx.message_to_iperf->cmd_ctrl.src_ep                = info->src_endpoint;
    iperf_ctx.message_to_iperf->cmd_ctrl.dst_addr.addr_mode    = EZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    iperf_ctx.message_to_iperf->cmd_ctrl.dst_addr.u.short_addr = info->dst_address;
    iperf_ctx.message_to_iperf->cmd_ctrl.cluster_id            = EZB_ZCL_CLUSTER_ID_PING_IPERF_TEST;
    iperf_ctx.message_to_iperf->cmd_ctrl.fc.direction          = info->direction;
    iperf_ctx.message_to_iperf->cmd_ctrl.fc.dis_default_rsp    = 1;
    iperf_ctx.message_to_iperf->cmd_ctrl.cnf_ctx.cb            = ipref_req_send_status_callback;
    iperf_ctx.message_to_iperf->cmd_ctrl.cnf_ctx.user_ctx      = NULL;
    ezb_zcl_attr_desc_t attr = zb_ping_iperf_get_iperf_attribute_val(info->src_endpoint, EZB_ZCL_CLUSTER_CLIENT,
                                                                     EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DATA_LEN);
    uint16_t data_len = 0;
    ezb_zcl_attr_desc_get_value(attr, &data_len);
    if (data_len == 0) {
        ESP_LOGE(TAG, "The length of the iperf payload should not be zero.");
        free(iperf_ctx.message_to_iperf);
        iperf_ctx.message_to_iperf = NULL;
        return EZB_ERR_FAIL;
    }
    iperf_ctx.message_to_iperf->data_length = data_len;
    iperf_ctx.iperf_data_len                = data_len;
    iperf_ctx.message_to_iperf->data        = calloc(1, iperf_ctx.message_to_iperf->data_length);
    if (iperf_ctx.message_to_iperf->data == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for iperf request data");
        free(iperf_ctx.message_to_iperf);
        iperf_ctx.message_to_iperf = NULL;
        return EZB_ERR_FAIL;
    }
    memset(iperf_ctx.message_to_iperf->data, 1, iperf_ctx.message_to_iperf->data_length);

    return ret;
}

ezb_err_t ezb_zcl_ping_iperf_test_cluster_iperf_req(const ezb_iperf_req_info_t *info, iperf_finish_callback_t iperf_finish_cb)
{
    ezb_err_t           ret  = EZB_ERR_NONE;
    ezb_zcl_attr_desc_t attr = NULL;

    EXIT_ON_FALSE(!iperf_ctx.client_in_progress, EZB_ERR_FAIL);
    attr = zb_ping_iperf_get_iperf_attribute_val(info->src_endpoint, EZB_ZCL_CLUSTER_CLIENT,
                                                 EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DURATION);
    EXIT_ON_FALSE(attr, EZB_ERR_NOT_FOUND);
    uint16_t duration = 0;
    ezb_zcl_attr_desc_get_value(attr, &duration);
    EXIT_ON_FALSE(duration != 0, EZB_ERR_FAIL);
    iperf_ctx.iperf_duration = duration * 1000 * 1000;

    attr = zb_ping_iperf_get_iperf_attribute_val(info->src_endpoint, EZB_ZCL_CLUSTER_CLIENT,
                                                 EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_INTERVAL);
    uint16_t interval = 0;
    EXIT_ON_ERROR(ret = ezb_zcl_attr_desc_get_value(attr, &interval));
    EXIT_ON_FALSE(interval != 0, EZB_ERR_FAIL);
    iperf_ctx.iperf_interval     = interval;
    iperf_ctx.iperf_start_time   = esp_timer_get_time();
    iperf_ctx.iperf_packet_count = 0;
    iperf_ctx.iperf_finish_cb    = iperf_finish_cb;

    EXIT_ON_ERROR(iperf_message_set(info));

    const esp_timer_create_args_t timer_args = {.callback = &do_iperf, .arg = NULL, .name = "iperf_interval"};
    EXIT_ON_ERROR(esp_timer_create(&timer_args, &iperf_ctx.iperf_timer));

    iperf_ctx.client_in_progress       = true;
    iperf_ctx.message_to_iperf->cmd_id = EZB_ZCL_CMD_PING_IPERF_TEST_IPERF_START;

    do_iperf(NULL);

exit:
    if (ret != EZB_ERR_NONE) {
        if (iperf_ctx.iperf_timer != NULL) {
            esp_timer_delete(iperf_ctx.iperf_timer);
            iperf_ctx.iperf_timer = NULL;
        }
        if (iperf_ctx.message_to_iperf != NULL) {
            if (iperf_ctx.message_to_iperf->data != NULL) {
                free(iperf_ctx.message_to_iperf->data);
            }
            free(iperf_ctx.message_to_iperf);
            iperf_ctx.message_to_iperf = NULL;
        }
        iperf_ctx.client_in_progress = false;
    }
    return ret;
}

static ezb_zcl_status_t ezb_zcl_ping_iperf_test_cluster_process_cmd_handler(const ezb_zcl_cmd_hdr_t *header,
                                                                            const uint8_t           *payload,
                                                                            uint16_t                 payload_length)
{
    ezb_zcl_status_t ret = EZB_ZCL_STATUS_SUCCESS;
    assert(header);
    switch (header->cmd_id) {
    case EZB_ZCL_CMD_PING_IPERF_TEST_ECHO:
        ret = zb_ping_iperf_test_cluster_ping_test_handler(header, payload, payload_length);
        break;
    case EZB_ZCL_CMD_PING_IPERF_TEST_IPERF_START:
        iperf_ctx.iperf_data_len     = payload_length;
        iperf_ctx.iperf_packet_count = 1;
        iperf_ctx.iperf_start_time   = esp_timer_get_time();
        ESP_LOGI(TAG, "IPERF START, TSN: %d", header->tsn);
        break;
    case EZB_ZCL_CMD_PING_IPERF_TEST_IPERF_PROCESS:
        iperf_ctx.iperf_packet_count++;
        iperf_ctx.iperf_end_time = esp_timer_get_time();
        ESP_LOGI(TAG, "time cost: %.3f s", (float)(iperf_ctx.iperf_end_time - iperf_ctx.iperf_start_time) / 1000000.0);
        ret = zb_ping_iperf_test_cluster_calculate_iperf(header->dst_ep, EZB_ZCL_CLUSTER_SERVER);
        break;
    default:
        break;
    }

    return ret;
}

float ezb_zcl_ping_iperf_get_iperf_result(uint8_t endpoint, uint8_t cluster_role)
{
    float               throughput = 0;
    ezb_zcl_attr_desc_t attr       = ezb_zcl_get_attr_desc(endpoint, EZB_ZCL_CLUSTER_ID_PING_IPERF_TEST, cluster_role,
                                                           EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_THROUGHPUT, EZB_ZCL_STD_MANUF_CODE);
    if (!attr) {
        ESP_LOGE(TAG, "IPERF_THROUGHPUT not found, register ping_iperf_test cluster before test");
        return 0;
    }
    ezb_zcl_attr_desc_get_value(attr, &throughput);
    return throughput;
}
