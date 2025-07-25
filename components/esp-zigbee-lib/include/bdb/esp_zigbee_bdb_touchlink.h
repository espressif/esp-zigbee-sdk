/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include "esp_err.h"
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_type.h"

/** @brief Enumeration of touchlink actions, that should be approved by end user application.
 *
 */
typedef enum esp_zb_touchlink_action_s {
    ESP_ZB_TOUCHLINK_ACTION_START_NEW_NETWORK,
    ESP_ZB_TOUCHLINK_ACTION_JOIN_ROUTER,
    ESP_ZB_TOUCHLINK_ACTION_JOIN_ED
} esp_zb_touchlink_action_t;

/** @brief Enumeration of touchlink key bitmask
 *
 */
typedef enum esp_zb_touchlink_key_bitmask_s {
  ESP_ZB_TOUCHLINK_MASTER_KEY           = (1U << 4),  /*!< Master key is a secret shared by all certified touchlink devices */
  ESP_ZB_TOUCHLINK_CERTIFICATION_KEY    = (1U << 15), /*!< Certification key is is used to allow testing of the security mechanisms */
} esp_zb_touchlink_key_bitmask_t;

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
 * @brief Zll identify callback
 *
 * @param[in] identify_on An indication that needs start or stop identify
 */
typedef void (*esp_zb_zll_identify_req_callback_t)(bool identify_on);

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

/**
 * @brief Set the timeout for Touchlink target
 *
 * @param[in] timeout The waiting time for the device to exit the Touchlink target mode
 *
 */
void esp_zb_zdo_touchlink_target_set_timeout(uint32_t timeout);

/**
 * @brief Set the key bitmask for Touchlink commissioning
 *
 * Configures the key bitmask used for Touchlink commissioning. The network key will be encrypted
 * using one of the key types specified in the bitmask. Higher priority is given to keys with higher
 * bits. By default, the certification and master keys are included in the bitmask.
 *
 * @param[in] bitmask The bitmask to be applied for Touchlink commissioning
 *
 */
void esp_zb_zdo_touchlink_set_key_bitmask(esp_zb_touchlink_key_bitmask_t bitmask);

/**
 * @brief Set the master key for Touchlink
 *
 * @param[in] key The master key that will be utilized for the Touchlink network
 *
 */
void esp_zb_zdo_touchlink_set_master_key(uint8_t *key);

/**
 * @brief Set the RSSI threshold for the Touchlink target
 *
 * @note The default value for the RSSI threshold is set to -64
 * @param[in] rssi_threshold The RSSI threshold determines whether the Touchlink target responds to the initiator
 *
 */
void esp_zb_zdo_touchlink_set_rssi_threshold(int8_t rssi_threshold);

/**
 * @brief Get the RSSI threshold of Touchlink target
 *
 * @return The value of RSSI threshold
 *
 */
int8_t esp_zb_zdo_touchlink_get_rssi_threshold(void);

/**
 * @brief Schedule to cancel touchlink target commissioning procedure
 *
 * @return
 *    - RET_OK: On success
 *    - RET_ERROR: Not in touchlink target procedure
 */
esp_err_t esp_zb_bdb_cancel_touchlink_target(void);

/**
 * @brief Register ZLL identify request handler
 *
 * @param[in] cb A callback for zll identify notification, refer to esp_zb_zll_identify_req_callback_t
 */
void esp_zb_zll_identify_req_handler_register(esp_zb_zll_identify_req_callback_t cb);

#ifdef __cplusplus
}
#endif
