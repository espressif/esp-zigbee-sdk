/*
 * SPDX-FileCopyrightText: 2025-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/mac.h" instead!"

#include <ezbee/mac.h>

#ifdef __cplusplus
extern "C" {
#endif

#define esp_zb_mac_set_transaction_persistence_time(us) TO_ESP_ERR(ezb_mac_set_transaction_persistence_time(us))
#define esp_zb_mac_get_transaction_persistence_time()   ezb_mac_get_transaction_persistence_time()

typedef struct {
    uint8_t csma_min_be;
    uint8_t csma_max_be;
    uint8_t csma_max_backoffs;
} esp_zb_platform_mac_config_t;

#define esp_zb_platform_mac_config_set(config) TO_ESP_ERR(ezb_mac_set_csma_ca_params((ezb_mac_csma_ca_params_t *)config))
#define esp_zb_platform_mac_config_get(config) TO_ESP_ERR(ezb_mac_get_csma_ca_params((ezb_mac_csma_ca_params_t *)config))

#ifdef __cplusplus
}
#endif

#else
#error "This file is for compatibility, please include "ezbee/mac.h"!"
#endif
