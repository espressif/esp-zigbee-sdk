/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_core.h"
#include "esp_zigbee_console.h"

#define MAX_CHILDREN                    10          /* the max amount of connected devices */
#define INSTALLCODE_POLICY_ENABLE       false       /* enable the install code policy for security */

#define ESP_ZB_ZR_CONFIG()                                                              \
    {                                                                                   \
        .esp_zb_role = ESP_ZB_DEVICE_TYPE_ROUTER,                                       \
        .install_code_policy = INSTALLCODE_POLICY_ENABLE,                               \
        .nwk_cfg.zczr_cfg = {                                                           \
            .max_children = MAX_CHILDREN,                                               \
        },                                                                              \
    }

#define ESP_ZB_DEFAULT_HOST_CONFIG()                            \
    {                                                           \
        .host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE,   \
    }

#if CONFIG_SOC_IEEE802154_SUPPORTED
#define ESP_ZB_DEFAULT_RADIO_CONFIG()                         \
    {                                                         \
        .radio_mode = ZB_RADIO_MODE_NATIVE,                   \
    }

#else
#error "CLI example for RCP is not ready!"
#endif