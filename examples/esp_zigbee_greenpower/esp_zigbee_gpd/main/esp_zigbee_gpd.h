/*
 * SPDX-FileCopyrightText: 2021-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee Green Power device Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */
#include "esp_zigbee_core.h"
#include "switch_driver.h"

#define ESP_ZB_ZGPD_SRC_ID (0x12345678)         /*!< ZGPD source id */
#define ESP_ZB_ZGPD_FRAMER_COUNTER (0xaac3)     /*!< Framer counter */
#define ESP_ZB_ZGPD_CHANNEL (24)                /*!< Channel */

/* ZGPD app_info(info_length + info) */
#define ESP_ZB_ZGPD_APP_INFO_CMD \
    {                            \
        0x03, 0x20, 0x21, 0x22   \
    }

/* Security key */
#define ESP_ZB_ZGPD_SECURITY_KEY                                                                       \
    {                                                                                                  \
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00 \
    }

#define ESP_ZB_DEFAULT_RADIO_CONFIG()                           \
    {                                                           \
        .radio_mode = ZB_RADIO_MODE_NATIVE,                     \
    }

#define ESP_ZB_DEFAULT_HOST_CONFIG()                            \
    {                                                           \
        .host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE,   \
    }
