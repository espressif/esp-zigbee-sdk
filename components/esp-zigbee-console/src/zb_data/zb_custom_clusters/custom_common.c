/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include "esp_check.h"
#include "custom_common.h"

#define TAG "custom_common"

esp_err_t esp_zb_custom_clusters_command_handler(const esp_zb_zcl_custom_cluster_command_message_t *message)
{
    esp_err_t ret = ESP_OK;
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);

    switch (message->info.cluster) {
        case ESP_ZB_ZCL_CLUSTER_ID_PING_IPERF_TEST:
            ret = zb_ping_iperf_test_cluster_command_handler(message);
            break;
        default:
            break;
    }

    return ret;
}
