/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#pragma once

#include "esp_zigbee.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Definition of Customized data stream cluster server */
#define ESP_ZIGBEE_CUSTOMIZED_DATA_PRODUCER_DEVICE_ID (0xff01)

#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_CLUSTER_ID (0xff00)

#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_DEVICE_NAME_ATTR_ID (0x0000)
#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_DATA_LENGTH_ATTR_ID (0x0001)
#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_DATA_BEGIN_ATTR_ID  (0x0002)

#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_QUERY_DATA_REQ_CMD_ID (0x00)
#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_QUERY_DATA_RSP_CMD_ID (0x01)

#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_DEVICE_NAME "\x0e""DATA_PRODUCER"
#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_DATA_LENGTH_DEFAULT_VALUE (256)
#define ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_DATA_BEGIN_DEFAULT_VALUE  (0)

void esp_zigbee_zcl_customized_data_stream_server_init(uint8_t ep_id);

void esp_zigbee_zcl_customized_data_stream_server_deinit(uint8_t ep_id);

#ifdef __cplusplus
} /* extern "C" */
#endif
