/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "sdkconfig.h"
#include "esp_err.h"

#define ESP_ZIGBEE_PRIMARY_CHANNEL_MASK   (1U << CONFIG_ZB_EXAMPLE_PRIMARY_CHANNEL)
#define ESP_ZIGBEE_SECONDARY_CHANNEL_MASK CONFIG_ZB_EXAMPLE_SECONDARY_CHANNEL_MASK

#define ESP_ZIGBEE_HA_THERMOSTAT_EP_ID         1
#define ESP_ZIGBEE_HA_TEMPERATURE_SENSOR_EP_ID 10

#define ESP_ZIGBEE_STORAGE_V1_PART_NAME   "zb_storage"
#if CONFIG_ZB_EXAMPLE_RUNTIME_NVS_PARTITION
#define ESP_ZIGBEE_STORAGE_PARTITION_NAME "zb_storage_v2"
#define ESP_ZIGBEE_STORAGE_PARTITION_SIZE 0x4000 /* 16KB */
#else
#define ESP_ZIGBEE_STORAGE_PARTITION_NAME "nvs"
#endif

#define ESP_MANUFACTURER_NAME "\x09""ESPRESSIF"
#define ESP_MODEL_IDENTIFIER  "\x07"CONFIG_IDF_TARGET

#if CONFIG_SOC_IEEE802154_SUPPORTED
#define ESP_ZIGBEE_DEFAULT_RADIO_CONFIG()           \
    {                                               \
        .radio_mode = ESP_ZIGBEE_RADIO_MODE_NATIVE, \
    }
#else
#warning "The example is not for IEEE 802.15.4-disabled SoC usage, please refer to esp_zigbee_gateway for RCP configuration"
#endif

#define ESP_ZIGBEE_DEFAULT_PLATFORM_CONFIG()                         \
    {                                                                \
        .storage_partition_name = ESP_ZIGBEE_STORAGE_PARTITION_NAME, \
        .radio_config           = ESP_ZIGBEE_DEFAULT_RADIO_CONFIG(), \
    }

#define ESP_ZIGBEE_ZC_CONFIG()                          \
    {                                                   \
        .device_type = EZB_NWK_DEVICE_TYPE_COORDINATOR, \
        .install_code_policy = false,                   \
        .zczr_config = {                                \
            .max_children = 10,                         \
        },                                              \
    }

#define ESP_ZIGBEE_DEFAULT_CONFIG()                              \
    {                                                            \
        .platform_config = ESP_ZIGBEE_DEFAULT_PLATFORM_CONFIG(), \
        .device_config   = ESP_ZIGBEE_ZC_CONFIG(),               \
    }

esp_err_t esp_zigbee_setup_zcl_model(void);
