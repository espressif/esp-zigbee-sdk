/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>

#include "esp_zigbee.h"

#ifdef __cplusplus
extern "C" {
#endif
#define EZB_ZCL_CLUSTER_ID_PING_IPERF_TEST 0xff01

typedef struct ezb_ping_iperf_test_cluster_config_s {
    float    throughput;
    uint16_t iperf_duration;
    uint16_t iperf_data_len;
    uint16_t iperf_interval;
} ezb_ping_iperf_test_cluster_config_t;

typedef struct ezb_ping_req_info {
    uint32_t timeout;
    uint16_t payload_len;
    uint16_t dst_short_addr;
    uint8_t  dst_ep;
    uint8_t  src_ep;
} ezb_ping_req_info_t;

typedef struct ezb_ipref_req_info {
    uint16_t dst_address;
    uint16_t payload_len;
    uint16_t iperf_interval;
    uint16_t iperf_duration;
    uint8_t  src_endpoint;
    uint8_t  dst_endpoint;
    uint8_t  direction;
} ezb_iperf_req_info_t;

typedef enum {
    EZB_ZCL_CMD_PING_IPERF_TEST_ECHO = 0,           /* Ping command: Used to test network connectivity. The client sends
                                                       a ping request to the server, and the server should respond with
                                                       the same data */
    EZB_ZCL_CMD_PING_IPERF_TEST_IPERF_START = 1,    /* iPerf start command: Sent by the client to the server to initiate
                                                       the iPerf test */
    EZB_ZCL_CMD_PING_IPERF_TEST_IPERF_PROCESS = 2,  /* iPerf continuous transmission command: Used during the test to
                                                       continuously send data packets from the client to the server for
                                                       throughput measurement */
} ezb_ping_iperf_test_cluster_cmd_t;

typedef enum {
    EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_THROUGHPUT = 0, /* iPerf throughput attribute (unit: kbps): Used to store the network
                                                          throughput result of the test */
    EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DURATION = 1,   /* iPerf test duration attribute (unit: seconds): Used to configure and
                                                          indicate the total duration of the test */
    EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_DATA_LEN = 2,   /* iPerf data length attribute (unit: bytes): Used to configure the size
                                                          of each data packet to be sent, corresponding to
                                                          ezb_zcl_custom_cluster_cmd_t.data.size */
    EZB_ZCL_ATTR_PING_IPERF_TEST_IPERF_INTERVAL = 3,   /* iPerf transmission interval attribute (unit: milliseconds): Used to
                                                          configure the time interval between sending data packets */
} ezb_ping_iperf_test_cluster_attr_t;

typedef void (*ping_finish_callback_t)(ezb_err_t);
typedef void (*iperf_finish_callback_t)(void);

ezb_zcl_cluster_desc_t ezb_zcl_ping_iperf_test_create_cluster_desc(ezb_ping_iperf_test_cluster_config_t *ping_iperf_test_cfg,
                                                                    uint8_t                           role_mask);

ezb_err_t ezb_zcl_ping_iperf_test_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value_p);

ezb_err_t ezb_zcl_ping_iperf_test_cluster_iperf_req(const ezb_iperf_req_info_t *info, iperf_finish_callback_t iperf_finish_cb);

ezb_err_t ezb_zcl_ping_iperf_test_cluster_ping_req(const ezb_ping_req_info_t *info, ping_finish_callback_t ping_finish_cb);

ezb_err_t ezb_zcl_ping_iperf_set_iperf_info(const ezb_iperf_req_info_t *info);

float ezb_zcl_ping_iperf_get_iperf_result(uint8_t endpoint, uint8_t cluster_role);

#ifdef __cplusplus
}
#endif
