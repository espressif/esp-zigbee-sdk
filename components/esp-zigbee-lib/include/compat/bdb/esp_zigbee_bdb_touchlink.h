/*
 * SPDX-FileCopyrightText: 2022-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/touchlink.h" instead!"

#include <ezbee/touchlink.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ZB_TOUCHLINK_ACTION_START_NEW_NETWORK EZB_TOUCHLINK_ACTION_START_NEW_NETWORK
#define ESP_ZB_TOUCHLINK_ACTION_JOIN_ROUTER       EZB_TOUCHLINK_ACTION_JOIN_ROUTER
#define ESP_ZB_TOUCHLINK_ACTION_JOIN_ED           EZB_TOUCHLINK_ACTION_JOIN_ED
typedef ezb_touchlink_action_t esp_zb_touchlink_action_t;

#define ESP_ZB_TOUCHLINK_MASTER_KEY        EZB_TOUCHLINK_KEY_BITMASK_MASTER
#define ESP_ZB_TOUCHLINK_CERTIFICATION_KEY EZB_TOUCHLINK_KEY_BITMASK_CERTIFICATION
typedef ezb_touchlink_key_bitmask_t esp_zb_touchlink_key_bitmask_t;

typedef bool (*esp_zb_touchlink_action_allowed_callback_t)(uint8_t action);

typedef void (*esp_zb_zll_identify_req_callback_t)(bool identify_on);

esp_err_t esp_zb_touchlink_action_check_register(esp_zb_touchlink_action_allowed_callback_t callback);
void      esp_zb_zll_identify_req_handler_register(esp_zb_zll_identify_req_callback_t cb);

#define esp_zb_touchlink_clear_factory_new()
#define esp_zb_zdo_touchlink_target_set_timeout(timeout)        TO_ESP_ERR(ezb_touchlink_set_target_timeout(timeout))
#define esp_zb_zdo_touchlink_set_key_bitmask(bitmask)           TO_ESP_ERR(ezb_touchlink_set_key_bitmask(bitmask))
#define esp_zb_zdo_touchlink_set_master_key(key)                TO_ESP_ERR(ezb_touchlink_set_master_key(key))
#define esp_zb_zdo_touchlink_set_rssi_threshold(rssi_threshold) TO_ESP_ERR(ezb_touchlink_set_rssi_threshold(rssi_threshold))
#define esp_zb_zdo_touchlink_get_rssi_threshold()               ezb_touchlink_get_rssi_threshold()

#ifdef __cplusplus
}
#endif

#else
#error "This file is for compatibility, please include "ezbee/touchlink.h"!"
#endif
