/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_type.h"

/**
 * @brief BDB commissioning mode mask bits
 *
 */
typedef enum esp_zb_bdb_commissioning_mode_mask_s {
    ESP_ZB_BDB_TOUCHLINK_COMMISSIONING = 0x01,  /*!< if bit is set, attempt Touchlink commissioning */
    ESP_ZB_BDB_NETWORK_STEERING        = 0x02,  /*!< if bit is set, attempt network steering */
    ESP_ZB_BDB_NETWORK_FORMATION       = 0x04,  /*!< if bit is set, attempt to form a network, according to device type */
    ESP_ZB_BDB_FINDING_N_BINDING       = 0x08,  /*!< if bit is set, attempt finding and binding */
    ESP_ZB_BDB_TOUCHLINK_TARGET        = 0x40,  /*!< if bit is set, attempt become touchlink target */
} esp_zb_bdb_commissioning_mode_mask_t;

/** @brief Enumeration of touchlink actions, that should be approved by end user application.
 *
 */
typedef enum esp_zb_touchlink_action_s {
    ESP_ZB_TOUCHLINK_ACTION_START_NEW_NETWORK,
    ESP_ZB_TOUCHLINK_ACTION_JOIN_ROUTER,
    ESP_ZB_TOUCHLINK_ACTION_JOIN_ED
} esp_zb_touchlink_action_t;

/** Touchlink action callback
 *
 * @brief Touchlink action
 *
 * @param[in] action action of the touchlink, refer to esp_zb_touchlink_action_t
 * @return
 *      -   True: allow
 *      -   False: reject
 *
 */
typedef bool (*esp_zb_touchlink_action_allowed_callback_t)(uint8_t action);

/**
 * @brief Register the Zigbee touchlink action check handler
 *
 * @param[in] callback A callback that allow the user to determine whether the touchlink device
 *                     can start a network or join as a router/end device, refer to esp_zb_touchlink_action_allowed_callback_t.
 *
 */
esp_err_t esp_zb_touchlink_action_check_register(esp_zb_touchlink_action_allowed_callback_t callback);
/**
 * @brief BDB touchlink network parameter information
 *
 */
typedef struct esp_zb_bdb_signal_touchlink_nwk_params_s {
    esp_zb_ieee_addr_t device_ieee_addr; /*!< address of device that started the network */
    uint8_t endpoint;                    /*!< endpoint of device that started the network */
    uint16_t profile_id;                 /*!< profile_id of device that started the network */
} esp_zb_bdb_signal_touchlink_nwk_params_t;

/** Touchlink clear factory new
 *
 * @brief Clear the factory new state
 *
 */
void esp_zb_touchlink_clear_factory_new(void);

#ifdef __cplusplus
}
#endif
