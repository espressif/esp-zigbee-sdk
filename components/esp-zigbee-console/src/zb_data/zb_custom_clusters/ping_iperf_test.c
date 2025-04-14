/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include "esp_timer.h"
#include "esp_check.h"
#include "ping_iperf_test.h"

#define TAG "ping_iperf_test"
#define IS_ADDRESS_BROADCAST(addr) ((addr) >= 0xfff8)

typedef struct iperf_context {
    iperf_finish_callback_t iperf_finish_cb;
    esp_zb_zcl_custom_cluster_cmd_t *message_to_iperf;
    uint64_t iperf_duration;
    int64_t iperf_start_time;
    uint64_t iperf_packet_count;
    int64_t iperf_end_time;
    uint32_t iperf_interval;
    uint16_t iperf_data_len;
    uint8_t iperf_endpoint;
    bool is_in_progress;
} iperf_context_t;

typedef struct ping_context {
    ping_finish_callback_t ping_finish_cb;
    int64_t ping_start_time;
    uint32_t timeout;
    uint8_t ping_tsn;
    bool is_in_progress;
    bool is_broadcast;
} ping_context_t;

static esp_zb_zcl_status_t zb_ping_iperf_set_iperf_attribute_val(uint8_t endpoint, uint8_t cluster_role, uint16_t attr_id, void *value_p);

static esp_zb_zcl_attr_t *zb_ping_iperf_get_iperf_attribute_val(uint8_t endpoint, uint8_t cluster_role, uint16_t attr_id);

static void ping_timeout_handler(uint8_t param);

static ping_context_t ping_ctx = {0};
static iperf_context_t iperf_ctx = {0};

esp_err_t esp_zb_cluster_list_add_ping_iperf_test_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask)
{
    return esp_zb_cluster_list_add_custom_cluster(cluster_list, attr_list, role_mask);
}

esp_zb_attribute_list_t *esp_zb_ping_iperf_test_cluster_create(esp_zb_ping_iperf_test_cluster_cfg_t *custom_cfg)
{
    esp_zb_ping_iperf_test_cluster_cfg_t cluster_cfg = {0};
    if (custom_cfg != NULL) {
        memcpy(&cluster_cfg, custom_cfg, sizeof(esp_zb_ping_iperf_test_cluster_cfg_t));
    }
    esp_zb_attribute_list_t *esp_zb_custom_cluster_attr_list = esp_zb_zcl_attr_list_create(ESP_ZB_ZCL_CLUSTER_ID_PING_IPERF_TEST);
    esp_zb_ping_iperf_test_cluster_add_attr(esp_zb_custom_cluster_attr_list, ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_THROUGHPUT, &(cluster_cfg.throughput));
    esp_zb_ping_iperf_test_cluster_add_attr(esp_zb_custom_cluster_attr_list, ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DURATION, &(cluster_cfg.iperf_duration));
    esp_zb_ping_iperf_test_cluster_add_attr(esp_zb_custom_cluster_attr_list, ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DATA_LEN, &(cluster_cfg.iperf_data_len));
    esp_zb_ping_iperf_test_cluster_add_attr(esp_zb_custom_cluster_attr_list, ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_INTERVAL, &(cluster_cfg.iperf_interval));

    return esp_zb_custom_cluster_attr_list;
}

esp_err_t esp_zb_ping_iperf_test_cluster_add_attr(esp_zb_attribute_list_t *attr_list, uint16_t attr_id, void *value_p)
{
    uint8_t attr_type = ESP_ZB_ZCL_ATTR_TYPE_INVALID;
    uint8_t attr_access = ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE;
    switch (attr_id) {
        case ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_THROUGHPUT:
            attr_type = ESP_ZB_ZCL_ATTR_TYPE_SINGLE;
            attr_access = ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE | ESP_ZB_ZCL_ATTR_ACCESS_REPORTING;
            break;
        case ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DATA_LEN:
        case ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DURATION:
        case ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_INTERVAL:
            attr_type = ESP_ZB_ZCL_ATTR_TYPE_U16;
            break;
        default:
            ESP_RETURN_ON_FALSE(false, ESP_ERR_INVALID_ARG, TAG, "incorrect/unsupported attribute_id!");
    }
    
    return esp_zb_custom_cluster_add_custom_attr(attr_list, attr_id, attr_type, attr_access, value_p);
}

static void finish_ping(esp_err_t result) {
    ping_ctx.is_in_progress = false;
    if (ping_ctx.ping_finish_cb) {
        ping_ctx.ping_finish_cb(result);
        ping_ctx.ping_finish_cb = NULL;
    }
}

static void ping_timeout_handler_cancel(esp_err_t result)
{
    esp_zb_scheduler_alarm_cancel(ping_timeout_handler, 0);
    finish_ping(result);
}

static void zb_ping_iperf_test_cluster_ping_req_send_status_callback(esp_zb_zcl_command_send_status_message_t message)
{
    if (message.status != ESP_OK){
        ESP_LOGE(TAG, "Ping request failed, error: %d tsn: %d", message.status, ping_ctx.ping_tsn);
        ping_timeout_handler_cancel(ESP_FAIL);
    } else {
        ESP_LOGI(TAG, "Ping request success, tsn: %d", ping_ctx.ping_tsn);
    }
    esp_zb_zcl_command_send_status_handler_register(NULL);
}

static void ping_timeout_handler(uint8_t param)
{
    esp_zb_zcl_command_send_status_handler_register(NULL);
    if (!ping_ctx.is_broadcast) {
        ESP_LOGE(TAG, "No ping response received, tsn: %d", ping_ctx.ping_tsn);
        finish_ping(ESP_FAIL);
    } else {
        ESP_LOGI(TAG, "Ping broadcast done, tsn: %d", ping_ctx.ping_tsn);
        finish_ping(ESP_OK);
    }
}

esp_err_t esp_zb_ping_iperf_test_cluster_ping_req(const esp_zb_ping_req_info_t *info, ping_finish_callback_t ping_finish_cb)
{
    ESP_RETURN_ON_FALSE(!ping_ctx.is_in_progress, ESP_ERR_INVALID_STATE, TAG, "Consecutive ping operations are not allowed");
    ping_ctx.ping_tsn++;
    esp_zb_zcl_custom_cluster_cmd_t req = {
        .address_mode     = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
        .profile_id       = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id       = ESP_ZB_ZCL_CLUSTER_ID_PING_IPERF_TEST,
        .dis_defalut_resp = 1,
        .custom_cmd_id    = ESP_ZB_ZCL_CMD_PING_IPERF_TEST_ECHO,
        .direction        = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
    };
    req.zcl_basic_cmd.dst_addr_u.addr_short = info->dst_short_addr;
    req.zcl_basic_cmd.src_endpoint = info->src_ep;
    req.zcl_basic_cmd.dst_endpoint = info->dst_ep;
    req.data.type = ESP_ZB_ZCL_ATTR_TYPE_SET;
    req.data.size = info->payload_len;
    req.data.value = malloc(req.data.size);
    ESP_RETURN_ON_FALSE(req.data.value, ESP_ERR_NO_MEM, TAG, "malloc ping req data failed");
    memset(req.data.value, 1, req.data.size);
    uint8_t *value_ptr = (uint8_t *)req.data.value;
    value_ptr[0] = ping_ctx.ping_tsn;

    ping_ctx.is_broadcast = IS_ADDRESS_BROADCAST(info->dst_short_addr);
    ping_ctx.ping_start_time = esp_timer_get_time();
    ping_ctx.timeout = info->timeout;
    ping_ctx.ping_finish_cb = ping_finish_cb;

    esp_zb_zcl_command_send_status_handler_register(zb_ping_iperf_test_cluster_ping_req_send_status_callback);

    esp_zb_zcl_custom_cluster_cmd_req(&req);
    esp_zb_scheduler_alarm(ping_timeout_handler, 0, ping_ctx.timeout);
    ping_ctx.is_in_progress = true;
    ESP_LOGI(TAG, "Request to ping address: 0x%04x", req.zcl_basic_cmd.dst_addr_u.addr_short);
    free(req.data.value);

    return ESP_OK;
}

static esp_err_t zb_ping_iperf_test_cluster_ping_test_request_handler(const esp_zb_zcl_custom_cluster_command_message_t *message)
{
    ESP_LOGI(TAG, "RECEIVE PING REQUEST");
    esp_zb_zcl_custom_cluster_cmd_t resp = {0};
    resp.zcl_basic_cmd.src_endpoint = message->info.dst_endpoint;
    resp.zcl_basic_cmd.dst_endpoint = message->info.src_endpoint;
    resp.zcl_basic_cmd.dst_addr_u.addr_short = message->info.src_address.u.short_addr;
    resp.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    resp.profile_id = ESP_ZB_AF_HA_PROFILE_ID;
    resp.cluster_id = ESP_ZB_ZCL_CLUSTER_ID_PING_IPERF_TEST;
    resp.direction = 1 - message->info.command.direction;
    resp.custom_cmd_id = ESP_ZB_ZCL_CMD_PING_IPERF_TEST_ECHO;
    resp.dis_defalut_resp = 1;
    resp.data.type = ESP_ZB_ZCL_ATTR_TYPE_SET;
    resp.data.size = message->data.size;
    resp.data.value = message->data.value;
    esp_zb_zcl_custom_cluster_cmd_req(&resp);
    ESP_LOGI(TAG, "Response to ping address: 0x%04x", resp.zcl_basic_cmd.dst_addr_u.addr_short);

    return ESP_OK;
}

static esp_err_t zb_ping_iperf_test_cluster_ping_test_response_handler(const esp_zb_zcl_custom_cluster_command_message_t *message)
{
    if (!ping_ctx.is_in_progress) {
        return ESP_OK;
    }
    uint8_t req_tsn = ((uint8_t *)message->data.value)[0];
    if (req_tsn == ping_ctx.ping_tsn) {
        int64_t ping_rtt = (esp_timer_get_time() - ping_ctx.ping_start_time) / 1000;
        ESP_LOGI(TAG, "RECEIVE PING RESPONSE from 0x%04x with %d bytes, rtt: %lld ms", message->info.src_address.u.short_addr, message->data.size, ping_rtt);
        if (!ping_ctx.is_broadcast) {
            ping_timeout_handler_cancel(ESP_OK);
        }
    }

    return ESP_OK;
}

static esp_err_t zb_ping_iperf_test_cluster_ping_test_handler(const esp_zb_zcl_custom_cluster_command_message_t *message)
{
    esp_err_t ret = ESP_OK;
    switch (message->info.command.direction) {
        case ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV:
            ret = zb_ping_iperf_test_cluster_ping_test_request_handler(message);
            break;
        case ESP_ZB_ZCL_CMD_DIRECTION_TO_CLI:
            ret = zb_ping_iperf_test_cluster_ping_test_response_handler(message);
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
esp_err_t esp_zb_ping_iperf_set_iperf_info(const esp_zb_iperf_req_info_t *info)
{
    esp_err_t ret = ESP_OK;
    esp_zb_zcl_status_t result;
    uint16_t payload_len = info->payload_len;
    uint16_t iperf_interval = info->iperf_interval;
    uint16_t iperf_duration = info->iperf_duration;
    result = zb_ping_iperf_set_iperf_attribute_val(info->src_endpoint, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE, ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DURATION, &iperf_duration);
    ESP_RETURN_ON_FALSE(result == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_FAIL, TAG, "Iperf has not been registered or is unavailable");
    result = zb_ping_iperf_set_iperf_attribute_val(info->src_endpoint, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE, ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DATA_LEN, &payload_len);
    ESP_RETURN_ON_FALSE(result == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_FAIL, TAG, "Error occurred while writing the data len attribute of iperf, status: %d", result);
    result = zb_ping_iperf_set_iperf_attribute_val(info->src_endpoint, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE, ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_INTERVAL, &iperf_interval);
    ESP_RETURN_ON_FALSE(result == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_FAIL, TAG, "Error occurred while writing the interval attribute of iperf, status: %d", result);
    
    return ret;
}

static esp_err_t zb_ping_iperf_test_cluster_calculate_iperf(uint8_t endpoint, uint8_t cluster_role)
{
    esp_err_t ret = ESP_OK;
    float throughput = ((float)(iperf_ctx.iperf_packet_count) * (float)(iperf_ctx.iperf_data_len) * 8 * 1000) / ((float)(iperf_ctx.iperf_end_time - iperf_ctx.iperf_start_time));
    esp_zb_zcl_status_t result = zb_ping_iperf_set_iperf_attribute_val(endpoint, cluster_role, ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_THROUGHPUT, &throughput);
    ESP_LOGI(TAG, "throughput: %.3f kbps, count: %llu", throughput, iperf_ctx.iperf_packet_count);
    ESP_RETURN_ON_FALSE(result == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_FAIL, TAG, "Fail to write throughput attribute: %d", result);

    return ret;
}

static void zb_ping_iperf_test_cluster_ipref_req_send_status_callback(esp_zb_zcl_command_send_status_message_t message)
{
    if (message.status == ESP_OK){
        iperf_ctx.iperf_packet_count++;
        iperf_ctx.iperf_end_time = esp_timer_get_time();
        zb_ping_iperf_test_cluster_calculate_iperf(message.src_endpoint, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);
    } else {
        ESP_LOGE(TAG, "Fail to send: error: %d tsn: %d", message.status, message.tsn);
    }
}

static void do_iperf(uint8_t param)
{
    if (esp_timer_get_time() - iperf_ctx.iperf_start_time < iperf_ctx.iperf_duration){
        esp_zb_zcl_custom_cluster_cmd_req(iperf_ctx.message_to_iperf);
        esp_zb_scheduler_alarm(do_iperf, 0, iperf_ctx.iperf_interval);
        iperf_ctx.message_to_iperf->custom_cmd_id = ESP_ZB_ZCL_CMD_PING_IPERF_TEST_IPERF_PROCESS;
    } else {
        if (iperf_ctx.message_to_iperf) {
            free(iperf_ctx.message_to_iperf->data.value);
            iperf_ctx.message_to_iperf->data.value = NULL;
            free(iperf_ctx.message_to_iperf);
            iperf_ctx.message_to_iperf = NULL;
        }
        iperf_ctx.is_in_progress = false;
        if (iperf_ctx.iperf_finish_cb) {
            iperf_ctx.iperf_finish_cb();
            iperf_ctx.iperf_finish_cb = NULL;
        }
    }
}

static esp_zb_zcl_status_t zb_ping_iperf_set_iperf_attribute_val(uint8_t endpoint, uint8_t cluster_role, uint16_t attr_id, void *value_p)
{
    return esp_zb_zcl_set_manufacturer_attribute_val(endpoint,
                                                     ESP_ZB_ZCL_CLUSTER_ID_PING_IPERF_TEST,
                                                     cluster_role,
                                                     ESP_ZB_ZCL_ATTR_NON_MANUFACTURER_SPECIFIC,
                                                     attr_id,
                                                     value_p,
                                                     false);
}

static esp_zb_zcl_attr_t *zb_ping_iperf_get_iperf_attribute_val(uint8_t endpoint, uint8_t cluster_role, uint16_t attr_id)
{
    return esp_zb_zcl_get_manufacturer_attribute(endpoint,
                                                 ESP_ZB_ZCL_CLUSTER_ID_PING_IPERF_TEST,
                                                 cluster_role,
                                                 attr_id,
                                                 ESP_ZB_ZCL_ATTR_NON_MANUFACTURER_SPECIFIC);
}

static esp_err_t iperf_message_set(const esp_zb_iperf_req_info_t *info)
{
    esp_err_t ret = ESP_OK;
    iperf_ctx.message_to_iperf = malloc(sizeof(esp_zb_zcl_custom_cluster_cmd_t));
    ESP_RETURN_ON_FALSE(iperf_ctx.message_to_iperf, ESP_FAIL, TAG, "Failed to allocate memory for iperf request data");
    iperf_ctx.message_to_iperf->zcl_basic_cmd.src_endpoint = info->src_endpoint;
    iperf_ctx.message_to_iperf->zcl_basic_cmd.dst_endpoint = info->dst_endpoint;
    iperf_ctx.message_to_iperf->zcl_basic_cmd.dst_addr_u.addr_short = info->dst_address;
    iperf_ctx.message_to_iperf->address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    iperf_ctx.message_to_iperf->profile_id = ESP_ZB_AF_HA_PROFILE_ID;
    iperf_ctx.message_to_iperf->cluster_id = ESP_ZB_ZCL_CLUSTER_ID_PING_IPERF_TEST;
    iperf_ctx.message_to_iperf->direction = info->direction;
    iperf_ctx.message_to_iperf->dis_defalut_resp = 1;

    esp_zb_zcl_attr_t *attr = zb_ping_iperf_get_iperf_attribute_val(info->src_endpoint,
                                                                    ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE,
                                                                    ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DATA_LEN);

    if (!attr || (*(uint16_t *)(attr->data_p)) == 0) {
        ESP_LOGE(TAG, "The length of the iperf payload should not be zero.");
        free(iperf_ctx.message_to_iperf);
        return ESP_FAIL;
    }
    iperf_ctx.message_to_iperf->data.type = ESP_ZB_ZCL_ATTR_TYPE_SET;
    iperf_ctx.message_to_iperf->data.size = *(uint16_t *)(attr->data_p);
    iperf_ctx.iperf_data_len = *(uint16_t *)(attr->data_p);
    iperf_ctx.message_to_iperf->data.value = calloc(1, iperf_ctx.message_to_iperf->data.size);
    if (iperf_ctx.message_to_iperf->data.value == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for iperf request data.value");
        free(iperf_ctx.message_to_iperf);
        return ESP_FAIL;
    }

    return ret;
}

esp_err_t esp_zb_ping_iperf_test_cluster_iperf_req(const esp_zb_iperf_req_info_t *info, iperf_finish_callback_t iperf_finish_cb)
{
    ESP_RETURN_ON_FALSE(!iperf_ctx.is_in_progress, ESP_FAIL, TAG, "Please wait for the previous iperf process to complete.");
    esp_err_t ret = ESP_OK;
    esp_zb_zcl_attr_t *attr;
    attr = zb_ping_iperf_get_iperf_attribute_val(info->src_endpoint,
                                                 ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE,
                                                 ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DURATION);
    ESP_RETURN_ON_FALSE(attr, ESP_ERR_NOT_FOUND, TAG, "Attribute IPERF_DURATION not found, register ping_iperf_test cluster before test");
    ESP_RETURN_ON_FALSE((*(uint16_t *)(attr->data_p))!= 0, ESP_FAIL, TAG, "iperf duration time should not be zero");
    iperf_ctx.iperf_duration = (*(uint16_t *)(attr->data_p)) * 1000 * 1000;

    attr = zb_ping_iperf_get_iperf_attribute_val(info->src_endpoint,
                                                 ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE,
                                                 ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_INTERVAL);
    ESP_RETURN_ON_FALSE(attr && (*(uint16_t *)(attr->data_p))!= 0, ESP_FAIL, TAG, "iperf interval should not be zero");
    iperf_ctx.iperf_interval = *(uint16_t *)(attr->data_p);
    iperf_ctx.iperf_start_time = esp_timer_get_time();
    iperf_ctx.iperf_packet_count = 0;
    iperf_ctx.iperf_finish_cb = iperf_finish_cb;

    esp_zb_zcl_command_send_status_handler_register(zb_ping_iperf_test_cluster_ipref_req_send_status_callback);
    ESP_RETURN_ON_FALSE(iperf_message_set(info) == ESP_OK, ESP_FAIL, TAG, "fail to set iperf test data");
    do_iperf(0);
    iperf_ctx.is_in_progress = true;
    iperf_ctx.message_to_iperf->custom_cmd_id = ESP_ZB_ZCL_CMD_PING_IPERF_TEST_IPERF_START;

    return ret;
}

esp_err_t zb_ping_iperf_test_cluster_command_handler(const esp_zb_zcl_custom_cluster_command_message_t *message)
{
    esp_err_t ret = ESP_OK;
    switch (message->info.command.id){
        case ESP_ZB_ZCL_CMD_PING_IPERF_TEST_ECHO:
            ret = zb_ping_iperf_test_cluster_ping_test_handler(message);
            break;
        case ESP_ZB_ZCL_CMD_PING_IPERF_TEST_IPERF_START:
            iperf_ctx.iperf_data_len = message->data.size;
            iperf_ctx.iperf_packet_count = 1;
            iperf_ctx.is_in_progress = true;
            iperf_ctx.iperf_start_time = esp_timer_get_time();
            ESP_LOGI(TAG, "IPERF START, TSN: %d", message->info.header.tsn);
            break;
        case ESP_ZB_ZCL_CMD_PING_IPERF_TEST_IPERF_PROCESS:
            if (iperf_ctx.is_in_progress) {
                iperf_ctx.iperf_packet_count++;
                iperf_ctx.iperf_end_time = esp_timer_get_time();
                ESP_LOGI(TAG, "time cost: %.3f s", (float)(iperf_ctx.iperf_end_time - iperf_ctx.iperf_start_time) / 1000000.0);
                ret = zb_ping_iperf_test_cluster_calculate_iperf(message->info.dst_endpoint, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
            }
            break;
        default:
            break;
    }

    return ret;
}

float esp_zb_ping_iperf_get_iperf_result(uint8_t endpoint, uint8_t cluster_role) 
{
    float throughput = 0;
    esp_zb_zcl_attr_t *attr = zb_ping_iperf_get_iperf_attribute_val(endpoint, cluster_role, ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_THROUGHPUT);
    if (!attr) {
        ESP_LOGE(TAG, "IPERF_DURATION not found, register ping_iperf_test cluster before test");
        return throughput;
    }
    throughput = *(float *)(attr->data_p);
    esp_zb_zcl_command_send_status_handler_register(NULL);

    return throughput;
}
