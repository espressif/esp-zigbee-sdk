/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include "esp_zigbee_core.h"
#include "ping_iperf_test.h"

#define ESP_ZB_HA_CUSTOM_TEST_TOOL_DEVICE_ID 0xfff3

#ifdef __cplusplus
extern "C"
{
#endif

esp_err_t esp_zb_custom_clusters_command_handler(const esp_zb_zcl_custom_cluster_command_message_t *message);

esp_zb_cluster_list_t *esp_zb_custom_test_tool_clusters_create(void *test_tool_cfg);

#ifdef __cplusplus
}
#endif
