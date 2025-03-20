/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include "esp_zigbee_core.h"
#include "ping_iperf_test.h"

#ifdef __cplusplus
extern "C"
{
#endif

esp_err_t esp_zb_custom_clusters_command_handler(const esp_zb_zcl_custom_cluster_command_message_t *message);

#ifdef __cplusplus
}
#endif
