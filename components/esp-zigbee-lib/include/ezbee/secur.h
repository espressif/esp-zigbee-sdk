/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_SECUR_H
#define ESP_ZIGBEE_SECUR_H

#include <ezbee/core.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enum of the Zigbee Security Level
 * @anchor ezb_secur_seclevel_e
 */
enum ezb_secur_seclevel_e {
    EZB_SECUR_SECLEVEL_NONE       = 0x00, /*!< No security */
    EZB_SECUR_SECLEVEL_MIC32      = 0x01, /*!< 32-bit MIC */
    EZB_SECUR_SECLEVEL_MIC64      = 0x02, /*!< 64-bit MIC */
    EZB_SECUR_SECLEVEL_MIC128     = 0x03, /*!< 128-bit MIC */
    EZB_SECUR_SECLEVEL_ENC_ONLY   = 0x04, /*!< Only encryption */
    EZB_SECUR_SECLEVEL_ENC_MIC32  = 0x05, /*!< 32-bit MIC + encryption */
    EZB_SECUR_SECLEVEL_ENC_MIC64  = 0x06, /*!< 64-bit MIC + encryption */
    EZB_SECUR_SECLEVEL_ENC_MIC128 = 0x07, /*!< 128-bit MIC + encryption */
    EZB_SECUR_SECLEVEL_MAX_NR,            /*!< Unknown security level */
};

/**
 * @brief Represents the Zigbee security level, @ref ezb_secur_seclevel_e
 */
typedef uint8_t ezb_secur_seclevel_t;

/**
 * @brief Enum of the Zigbee install code type
 * @anchor ezb_secur_ic_type_e
 * @note The format of the install code compliant with BDB specification, which is
 *       48/64/96/128 bits number + 16 bits CRC (CCITT-16: x^16 + x^12 + x^5 + 1).
 */
enum ezb_secur_ic_type_e {
    EZB_SECUR_IC_TYPE_48  = 0x00,    /*!< Install code total of 8 bytes length */
    EZB_SECUR_IC_TYPE_64,            /*!< Install code total of 10 bytes length */
    EZB_SECUR_IC_TYPE_96,            /*!< Install code total of 14 bytes length */
    EZB_SECUR_IC_TYPE_128,           /*!< Install code total of 18 bytes length */
    EZB_SECUR_IC_TYPE_MAX_NR,        /*!< Unknown type */
};

/**
 * @brief Represents the Zigbee install code type, @ref ezb_secur_ic_type_e
 */
typedef uint8_t ezb_secur_ic_type_t;

/**
 * @brief Enable Trust Center to require install code for joining.
 *
 * @param[in] required  A boolean indicating whether the install code is required for joining.
 *
 * @return - EZB_ERR_NONE: on success; failed otherwise.
 */
ezb_err_t ezb_secur_set_ic_required(bool required);

/**
 * @brief Trust Center: Add the install code for remote device with type.
 *
 * @param[in] address  The pointer to the 64-bit extended address of the remote device.
 * @param[in] ic_type  The install code type, @ref ezb_secur_ic_type_e.
 * @param[in] ic       The pointer to the data of install code.
 *
 * @return - EZB_ERR_NONE: on success; failed otherwise.
 */
ezb_err_t ezb_secur_ic_add(const ezb_extaddr_t *address, ezb_secur_ic_type_t ic_type, const uint8_t *ic);

/**
 * @brief Trust Center: Remove the install code of a remote device.
 *
 * @param[in] address The pointer to the 64-bit extended address of the remote device.
 *
 * @return - EZB_ERR_NONE: on success; failed otherwise.
 */
ezb_err_t ezb_secur_ic_remove(const ezb_extaddr_t *address);

 /**
  * @brief Trust Center: Remove the install code of all joiner devices.
  *
  * @return - EZB_ERR_NONE: on success; failed otherwise.
  */
ezb_err_t ezb_secur_ic_remove_all(void);

/**
 * @brief Joiner: Set the install code for joining.
 *
 * @param[in] ic_type  The install code type @ref ezb_secur_ic_type_e
 * @param[in] ic       The pointer to the data of install code.
 *
 * @return - EZB_ERR_NONE: on success; failed otherwise.
 */
ezb_err_t ezb_secur_ic_set(ezb_secur_ic_type_t ic_type, const uint8_t *ic);

/**
 * @brief Joiner: Get current install code.
 *
 * @param[out] ic       The pointer to the data of install code.
 * @param[out] ic_type  The pointer to install code type.

 * @return - EZB_ERR_NONE: on success; failed otherwise.
 */
ezb_err_t ezb_secur_ic_get(uint8_t *ic, ezb_secur_ic_type_t *ic_type);

/**
 * @brief Set if the TC-link key exchange is required for joining.
 *
 * @note The ZigBee router/end device without @p required will not request key from the ZigBee coordinator.
 *       The ZigBee coordinator without @p required allows the router/end device to stay in network without
 *       a TC-link key exchange.
 *
 * @param[in] required  A boolean indicating whether the link key exchange is required for joining.
 *
 * @return - EZB_ERR_NONE: on success; failed otherwise.
 */
ezb_err_t ezb_secur_set_tclk_exchange_required(bool required);

/**
 * @brief Set the global link key for the ZigBee network.
 *
 * @param[in] key  A pointer to the global link key.
 */
void ezb_secur_set_global_link_key(const uint8_t *key);

/**
 * @brief Set the security level for the ZigBee network.
 *
 * @param[in] level  The security level, @ref ezb_secur_seclevel_e. Default is EZB_SECUR_SECLEVEL_ENC_MIC32.
 *
 * @return - EZB_ERR_NONE: on success; failed otherwise.
 */
ezb_err_t ezb_secur_set_security_level(ezb_secur_seclevel_t level);

/**
 * @brief Get the current security level for the ZigBee network.
 *
 * @return The security level, @ref ezb_secur_seclevel_e
 */
ezb_secur_seclevel_t ezb_secur_get_security_level(void);

/**
 * @brief Set the current network key of the ZigBee network.
 *
 * @param[in] key The pointer to the key data.
 *
 * @return - EZB_ERR_NONE: on success; failed otherwise.
 */
ezb_err_t ezb_secur_set_network_key(const uint8_t *key);

/**
 * @brief Get the current network key of the ZigBee network.
 *
 * @return - EZB_ERR_NONE: on success; failed otherwise.
 */
ezb_err_t ezb_secur_get_network_key(uint8_t *key);

/**
 * @brief Broadcast a new network key to the network.
 *
 * @param[in] key      A 16-byte security network key to be broadcast.
 * @param[in] key_seq  The sequence number associated with the network key.
 *
 * @return
 *      - EZB_ERR_NONE: Success
 *      - EZB_ERR_NO_MEM: Insufficient memory to process the request
 *      - EZB_ERR_NOT_SUPPORTED: The current Zigbee role does not support sending this command
 *      - EZB_ERR_INV_ARG: The provided key value is invalid
 *      - Otherwise: Failure
 */
ezb_err_t ezb_secur_broadcast_network_key(const uint8_t *key, uint8_t key_seq);

/**
 * @brief Broadcast the network requesting to switch to a new network key.
 *
 * @param[in] key_seq The sequence number associated with the network key.
 *
 * @return
 *      - EZB_ERR_NONE: Success
 *      - EZB_ERR_NO_MEM: Insufficient memory to process the request
 *      - EZB_ERR_NOT_SUPPORTED: The current Zigbee role does not support sending this command
 *      - Otherwise: Failure
 */
ezb_err_t ezb_secur_broadcast_switch_network_key(uint8_t key_seq);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_SECUR_H */
