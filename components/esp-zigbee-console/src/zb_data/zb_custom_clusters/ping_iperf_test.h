/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include "esp_zigbee_core.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define ESP_ZB_ZCL_CLUSTER_ID_PING_IPERF_TEST 0xff01

typedef struct esp_zb_ping_iperf_test_cluster_cfg_s {
    float throughput;
    uint16_t iperf_duration;
    uint16_t iperf_data_len;
    uint16_t iperf_interval;
} esp_zb_ping_iperf_test_cluster_cfg_t;

typedef struct esp_zb_ping_req_info {
    uint16_t dst_short_addr;
    uint8_t dst_ep;
    uint8_t src_ep;
    uint16_t payload_len;
} esp_zb_ping_req_info_t;

typedef struct esp_zb_ipref_req_info {
    uint8_t src_endpoint;
    uint8_t dst_endpoint;
    uint8_t direction;
    uint16_t dst_address;
    uint16_t payload_len;
    uint16_t iperf_interval;
    uint16_t iperf_duration;
} esp_zb_iperf_req_info_t;

typedef enum {
    ESP_ZB_ZCL_CMD_PING_IPERF_TEST_ECHO                = 0,   /* Ping command: Used to test network connectivity. The client sends a ping request to the server, and the server should respond with the same data */
    ESP_ZB_ZCL_CMD_PING_IPERF_TEST_IPERF_START         = 1,   /* iPerf start command: Sent by the client to the server to initiate the iPerf test*/
    ESP_ZB_ZCL_CMD_PING_IPERF_TEST_IPERF_PROCESS       = 2,   /* iPerf continuous transmission command: Used during the test to continuously send data packets from the client to the server for throughput measurement */
} esp_zb_ping_iperf_test_cluster_cmd_t;

typedef enum {
    ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_THROUGHPUT   = 0,   /* iPerf throughput attribute (unit: kbps): Used to store the network throughput result of the test */
    ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DURATION     = 1,   /* iPerf test duration attribute (unit: seconds): Used to configure and indicate the total duration of the test */
    ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DATA_LEN     = 2,   /* iPerf data length attribute (unit: bytes): Used to configure the size of each data packet to be sent, corresponding to esp_zb_zcl_custom_cluster_cmd_t.data.size */
    ESP_ZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_INTERVAL     = 3,   /* iPerf transmission interval attribute (unit: milliseconds): Used to configure the time interval between sending data packets */
} esp_zb_ping_iperf_test_cluster_attr_t;

esp_err_t esp_zb_cluster_list_add_ping_iperf_test_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

esp_zb_attribute_list_t *esp_zb_ping_iperf_test_cluster_create(esp_zb_ping_iperf_test_cluster_cfg_t *ping_iperf_test_cfg);

esp_err_t esp_zb_ping_iperf_test_cluster_add_attr(esp_zb_attribute_list_t *attr_list, uint16_t attr_id, void *value_p);

esp_err_t esp_zb_ping_iperf_test_cluster_iperf_req(const esp_zb_iperf_req_info_t *info);

esp_err_t esp_zb_ping_iperf_test_cluster_ping_req(const esp_zb_ping_req_info_t *info);

esp_err_t esp_zb_ping_iperf_set_iperf_info(const esp_zb_iperf_req_info_t *info);

esp_err_t zb_ping_iperf_test_cluster_command_handler(const esp_zb_zcl_custom_cluster_command_message_t *message);

float esp_zb_ping_iperf_get_iperf_result(uint8_t endpoint, uint8_t cluster_role);

#ifdef __cplusplus
}
#endif
