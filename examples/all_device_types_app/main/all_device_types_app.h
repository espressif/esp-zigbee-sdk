/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#pragma once

#include "esp_zigbee.h"
#include "esp_zigbee_console.h"

#define MAX_CHILDREN                    10          /* the max amount of connected devices */
#define INSTALLCODE_POLICY_ENABLE       false       /* enable the install code policy for security */

#define ESP_ZIGBEE_NVS_PART_NAME     "zb_storage"
#define ESP_ZIGBEE_ALL_CHANNELS_MASK (0x07FFF800U)

#define ESP_ZIGBEE_ZR_CONFIG()                                          \
    {                                                                   \
        .device_type = EZB_NWK_DEVICE_TYPE_ROUTER,                      \
        .install_code_policy = INSTALLCODE_POLICY_ENABLE,               \
        .zczr_config = {                                                \
            .max_children = MAX_CHILDREN,                               \
        },                                                              \
    }

#if CONFIG_SOC_IEEE802154_SUPPORTED
#define ESP_ZIGBEE_DEFAULT_RADIO_CONFIG()                               \
    {                                                                   \
        .radio_mode = ESP_ZIGBEE_RADIO_MODE_NATIVE,                     \
    }
#else
#error "CLI example for Gateway is not ready!"
#endif

#define ESP_ZIGBEE_DEFAULT_PLATFORM_CONFIG()                            \
    {                                                                   \
        .storage_partition_name = ESP_ZIGBEE_NVS_PART_NAME,             \
        .radio_config           = ESP_ZIGBEE_DEFAULT_RADIO_CONFIG(),    \
    }

#define ESP_ZIGBEE_DEFAULT_CONFIG()                                     \
    {                                                                   \
        .platform_config = ESP_ZIGBEE_DEFAULT_PLATFORM_CONFIG(),        \
        .device_config   = ESP_ZIGBEE_ZR_CONFIG(),                      \
    }
