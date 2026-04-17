/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#pragma once

#include <stdint.h>
#include "esp_zigbee.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Definition of Customized data stream cluster client */
#define ESP_ZIGBEE_CUSTOMIZED_DATA_CONSUMER_DEVICE_ID (0xff02)

#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_CLUSTER_ID (0xff00)

#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_DEVICE_NAME_ATTR_ID (0x0000)

#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_QUERY_DATA_REQ_CMD_ID (0x00)
#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_QUERY_DATA_RSP_CMD_ID (0x01)

void esp_zigbee_zcl_customized_data_stream_client_init(uint8_t ep_id);

void esp_zigbee_zcl_customized_data_stream_client_deinit(uint8_t ep_id);

typedef void (*esp_zigbee_customized_data_consumer_callback_t)(const uint8_t *data, uint16_t data_length);

ezb_err_t esp_zigbee_zcl_customized_data_stream_get_data_cmd_req(ezb_zcl_custom_cluster_cmd_t *cmd_req);

ezb_err_t esp_zigbee_zcl_customized_data_stream_client_set_data_customer(esp_zigbee_customized_data_consumer_callback_t cb);

#ifdef __cplusplus
} /* extern "C" */
#endif
