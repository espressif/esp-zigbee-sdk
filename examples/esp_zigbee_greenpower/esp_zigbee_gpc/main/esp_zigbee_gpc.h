/*
 * SPDX-FileCopyrightText: 2021-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee Green Power combo Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include "esp_zigbee_core.h"
#include "light_driver.h"
#include "switch_driver.h"

/* Zigbee configuration */
#define MAX_CHILDREN 10                         /*!< The max amount of connected devices */
#define INSTALLCODE_POLICY_ENABLE false         /*!< Enable the install code policy for security */
#define HA_LIGHT_ENDPOINT 10                    /*!< HA light endpoint */
#define ESP_ZB_PRIMARY_CHANNEL_MASK (1l << 24)  /*!< Zigbee primary channel mask use in the example */

/* ZGP combo configuration */
#define ZGP_COMBO_PROXY_ENABLED 1                /*!< Enable combo(proxy + sink) proxy functionality */
#define ZGP_MAX_MAPPING_TABLE_ENTRIES 10         /*!< ZGP sink mapping table size*/
#define ESP_ZGP_GPSB_FUNCTIONALITY 0x9ac3f       /*!< GPS functionality, refer to esp_zgp_gps_functionality_t */
#define ESP_ZGP_GPBB_FUNCTIONALITY 0x9ac3f       /*!< GPP functionality, refer to esp_zgp_gpp_functionality_t */
#define ESP_ZGP_ACTIVE_FUNCTIONALITY_ID 0xFFFFFF /*!< Active GP functionality */

/* Zigbee coordinator configuration */
#define ESP_ZB_ZC_CONFIG()                                              \
    {                                                                   \
        .esp_zb_role = ESP_ZB_DEVICE_TYPE_COORDINATOR,                  \
        .install_code_policy = INSTALLCODE_POLICY_ENABLE,               \
        .nwk_cfg.zczr_cfg = {                                           \
            .max_children = MAX_CHILDREN,                               \
        },                                                              \
    }

#define ESP_ZB_DEFAULT_RADIO_CONFIG()                           \
    {                                                           \
        .radio_mode = ZB_RADIO_MODE_NATIVE,                     \
    }

#define ESP_ZB_DEFAULT_HOST_CONFIG()                            \
    {                                                           \
        .host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE,   \
    }
