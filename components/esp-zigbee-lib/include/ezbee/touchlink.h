/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/core.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration bitmask for Touchlink key.
 */
typedef enum {
    EZB_TOUCHLINK_KEY_BITMASK_DEVELOPMENT   = (1U << 0),  /*!< Development key. */
    EZB_TOUCHLINK_KEY_BITMASK_MASTER        = (1U << 4),  /*!< Master key. */
    EZB_TOUCHLINK_KEY_BITMASK_CERTIFICATION = (1U << 15), /*!< Certification key. */
} ezb_touchlink_key_bitmask_t;

/**
 * @brief Enumeration actions for Touchlink.
 */
enum {
    EZB_TOUCHLINK_ACTION_SELECTED_TARGET,   /*!< Select target */
    EZB_TOUCHLINK_ACTION_START_NEW_NETWORK, /*!< Start new network */
    EZB_TOUCHLINK_ACTION_JOIN_ROUTER,       /*!< Join router */
    EZB_TOUCHLINK_ACTION_JOIN_ED,           /*!< Join end device */
};

/**
 * @brief Touchlink action permission type
 * @anchor ezb_touchlink_action_t
 *
 * For a Touchlink initiator:
 * - EZB_TOUCHLINK_ACTION_SELECTED_TARGET: The target is selected by the initiator.
 * - EZB_TOUCHLINK_ACTION_START_NEW_NETWORK: The initiator intends to start a new network with the selected target.
 * - EZB_TOUCHLINK_ACTION_JOIN_ROUTER: The initiator intends for the selected target (router) to join the network.
 * - EZB_TOUCHLINK_ACTION_JOIN_ED: The initiator intends for the selected target (end device) to join the network.
 *
 * For a Touchlink target:
 * - EZB_TOUCHLINK_ACTION_SELECTED_TARGET: Never used.
 * - EZB_TOUCHLINK_ACTION_START_NEW_NETWORK: The target receives a request from the initiator to start a new network.
 * - EZB_TOUCHLINK_ACTION_JOIN_ROUTER: The target receives a request from the initiator to join as a router.
 * - EZB_TOUCHLINK_ACTION_JOIN_ED: The target receives a request from the initiator to join as an end device.
 */
typedef uint8_t ezb_touchlink_action_t;

/**
 * @brief A callback for Touchlink action permission
 *
 * @param action The action, @ref ezb_touchlink_action_t
 * @param ieee_addr The IEEE address of the paired device
 *
 * @return True if the action is permitted, false otherwise
 */
typedef bool (*ezb_touchlink_action_permission_callback_t)(ezb_touchlink_action_t action, const ezb_extaddr_t *ieee_addr);

/**
 * @brief A callback for Touchlink identify
 *
 * @param duration The identify duration in seconds.
 */
typedef void (*ezb_touchlink_identify_callback_t)(uint16_t duration);

/**
 * @brief Register a callback for Touchlink query.
 *
 * @param cb The callback function.
 *
 * @return Error code.
 */
ezb_err_t ezb_touchlink_action_permission_handler_register(ezb_touchlink_action_permission_callback_t cb);

/**
 * @brief Register a callback for Touchlink identify
 *
 * @param cb The callback function.
 *
 * @return Error code.
 */
ezb_err_t ezb_touchlink_identify_handler_register(ezb_touchlink_identify_callback_t cb);

/**
 * @brief Set the master key for Touchlink commissioning (Initiator or Target).
 *
 * @param key The 128-bit master key.
 *
 * @return Error code.
 */
ezb_err_t ezb_touchlink_set_master_key(const uint8_t *key);

/**
 * @brief Get the master key for Touchlink commissioning (Initiator or Target).
 *
 * @param key Buffer for the 128-bit master key.
 *
 * @return Error code.
 */
ezb_err_t ezb_touchlink_get_master_key(uint8_t *key);

/**
 * @brief Set the key bitmask for Touchlink commissioning (Initiator or Target).
 *
 * @param key_bitmask The bitmask for the keys to be used.
 *
 * @return Error code.
 */
ezb_err_t ezb_touchlink_set_key_bitmask(uint16_t key_bitmask);

/**
 * @brief Get the key bitmask for Touchlink commissioning (Initiator or Target).
 *
 * @return The key bitmask.
 */
uint16_t ezb_touchlink_get_key_bitmask(void);

/**
 * @brief Set the commissioning timeout for Touchlink Target.
 *
 * @param second The target timeout in seconds.
 *
 * @return Error code.
 */
ezb_err_t ezb_touchlink_set_target_timeout(uint16_t second);

/**
 * @brief Get the commissioning timeout for Touchlink Target.
 *
 * @return The target timeout in seconds.
 */
uint16_t ezb_touchlink_get_target_timeout(void);

/**
 * @brief Set the RSSI threshold for Touchlink Initiator.
 *
 * If the RSSI of the device is less than the threshold, the device will not be selected as the target.
 *
 * @param rssi_threshold The RSSI threshold.
 * @return Error code.
 */
ezb_err_t ezb_touchlink_set_rssi_threshold(int8_t rssi_threshold);

/**
 * @brief Get the RSSI threshold for Touchlink Initiator.
 *
 * @return The RSSI threshold.
 */
int8_t ezb_touchlink_get_rssi_threshold(void);

/**
 * @brief Get the Touchlink channel.
 *
 * @return The device channel.
 */
uint8_t ezb_touchlink_get_channel(void);

/**
 * @brief Set the Touchlink channel.
 *
 * For a Touchlink initiator:
 * - The channel is used to determine the network channel during commissioning if the device is factory-new.
 * For a Touchlink target:
 * - The channel determines which channel the device stays on while waiting for commissioning.
 *   If the device is factory-new, this channel is also used to propose the network channel.
 * 
 * If not set, it will be randomly selected from the sets configured by
 *   bdb_comm_set_primary_channel_set() and bdb_comm_set_secondary_channel_set().
 *
 * @param channel The Touchlink channel.
 *
 * @return Error code.
 */
ezb_err_t ezb_touchlink_set_channel(uint8_t channel);

/**
 * @brief Send the identify request for Touchlink.
 *
 * @param duration The identify duration in seconds.
 * @param ieee_addr The IEEE address of the target.
 *
 * @return Error code.
 */
ezb_err_t ezb_touchlink_send_identify_req(uint16_t duration, const ezb_extaddr_t *ieee_addr);

/**
 * @brief Send the reset to factory new request for Touchlink.
 *
 * @param ieee_addr The IEEE address of the target.
 *
 * @return Error code.
 */
ezb_err_t ezb_touchlink_send_reset_to_factory_new_req(const ezb_extaddr_t *ieee_addr);

#ifdef __cplusplus
} /* extern "C" */
#endif
