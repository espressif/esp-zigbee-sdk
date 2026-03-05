/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_BDB_H
#define ESP_ZIGBEE_BDB_H

#include <ezbee/core.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Base Device Behavior (BDB) commissioning capability.
 *
 */
typedef enum ezb_bdb_comm_capability_e {
    EZB_BDB_COMM_CAPABILITY_NONE                = 0x00, /*!< No commissioning capability */
    EZB_BDB_COMM_CAPABILITY_NETWORK_STEERING    = 0x01, /*!< Network steering capability */
    EZB_BDB_COMM_CAPABILITY_NETWORK_FORMATION   = 0x02, /*!< Network formation capability */
    EZB_BDB_COMM_CAPABILITY_FINDING_N_BINDING   = 0x04, /*!< Finding & binding capability */
    EZB_BDB_COMM_CAPABILITY_TOUCHLINK           = 0x08, /*!< Touchlink commissioning capability */
} ezb_bdb_comm_capability_t;

/**
 * @brief Base Device Behavior (BDB) operation mode.
 *
 */
 typedef enum ezb_bdb_comm_mode_e {
    EZB_BDB_MODE_INITIALIZATION      = 0x01,    /*!< BDB initialization mode */
    EZB_BDB_MODE_TOUCHLINK_INITIATOR = 0x02,    /*!< BDB touchlink initiator mode */
    EZB_BDB_MODE_NETWORK_STEERING    = 0x04,    /*!< BDB network steering mode */
    EZB_BDB_MODE_NETWORK_FORMATION   = 0x08,    /*!< BDB network formation mode */
    EZB_BDB_MODE_FINDING_N_BINDING   = 0x10,    /*!< BDB finding & binding mode */
    EZB_BDB_MODE_TOUCHLINK_TARGET    = 0x20,    /*!< BDB touchlink target mode */
} ezb_bdb_comm_mode_t;

typedef uint8_t ezb_bdb_comm_mode_mask_t;

/**
 * @brief Base Device Behavior (BDB) commissioning status.
 *
 */
enum ezb_bdb_comm_status_e {
    EZB_BDB_STATUS_SUCCESS = 0,                 /*!< The commissioning sub-procedure was successful. */
    EZB_BDB_STATUS_IN_PROGRESS,                 /*!< One of the commissioning sub-procedures has started but is not yet complete. */
    EZB_BDB_STATUS_NOT_AA_CAPABLE,              /*!< The initiator is not address assignment capable during touchlink. */
    EZB_BDB_STATUS_NO_NETWORK,                  /*!< A network has not been found during network steering or touchlink. */
    EZB_BDB_STATUS_TARGET_FAILURE,              /*!< A node has not joined a network when requested during touchlink. */
    EZB_BDB_STATUS_FORMATION_FAILURE,           /*!< A network could not be formed during network formation. */
    EZB_BDB_STATUS_NO_IDENTIFY_QUERY_RESPONSE,  /*!< No response to an identify query command has been received during finding and binding. */
    EZB_BDB_STATUS_BINDING_TABLE_FULL,          /*!< A binding table entry could not be created due to insufficient space in the binding table during finding and binding. */
    EZB_BDB_STATUS_NO_SCAN_RESPONSE,            /*!< No response to a scan request inter-PAN command has been received during touchlink. */
    EZB_BDB_STATUS_NOT_PERMITTED,               /*!< A touchlink (steal) attempt was made when a node is already connected to a centralized security network.
                                                     A node was instructed to form a network when it did not have a logical type of either Zigbee coordinator or Zigbee router. */
    EZB_BDB_STATUS_TCLK_EX_FAILURE,             /*!< The Trust Center link key exchange procedure has failed attempting to join a centralized security network. */
    EZB_BDB_STATUS_NOT_ON_A_NETWORK,            /*!< A commissioning procedure was forbidden since the node was not currently on a network. */
    EZB_BDB_STATUS_ON_A_NETWORK,                /*!< A commissioning procedure was forbidden since the node was currently on a network. */

    EZB_BDB_STATUS_CANCELLED,                   /*!< The current operation (steering or formation) was cancelled by an app */
    EZB_BDB_STATUS_DEV_ANNCE_SEND_FAILURE       /*!< A device announce sending has been failed (e.g. device announce haven't acked by parent router). */
};

typedef uint8_t ezb_bdb_comm_status_t;

/**
 * @brief Set the BDB primary channel mask.
 *
 * @note This function should be run AFTER @ref ezb_core_init is called and before @ref ezb_dev_start.
 *       These masks define the allowable channels on which the device may attempt to form or join a
 *       network on startup. It will scan all channels by default.
 *
 * @param[in] channel_mask  Valid channel mask is from 0x00000800 (only channel 11) to 0x07FFF800 (all channels from 11 to 26)
 *
 * @return  - EZB_ERR_NONE on success
 *          - EZB_ERR_INV_ARG if the channel mask is out of range
 */
ezb_err_t ezb_bdb_set_primary_channel_set(uint32_t channel_mask);

/**
 * @brief Get the BDB primary channel mask
 *
 * @return A 32-bit channel mask
 */
uint32_t ezb_bdb_get_primary_channel_set(void);

/**
 * @brief   Set the BDB secondary channel mask.
 *
 * Beacon request will be sent on these channels for the BDB energy scan, if no network found after energy scan on the primary channels.
 *
 * @param[in] channel_mask Valid channel mask is from 0x00000800 (only channel 11) to 0x07FFF800 (all channels from 11 to 26)
 * @return  - EZB_ERR_NONE on success
            - EZB_ERR_INV_ARG if the channel mask is out of range
 */
ezb_err_t ezb_bdb_set_secondary_channel_set(uint32_t channel_mask);

/**
 * @brief Get the BDB secondary channel mask
 *
 * @return A 32-bit channel mask
 */
uint32_t ezb_bdb_get_secondary_channel_set(void);

/**
 * @brief Set the scan duration time
 * @anchor ezb_bdb_set_scan_duration
 *
 * @param[in] duration  The scan duration time is in beacon intervals, defined as ((1 << duration) + 1) * 15.36 ms
 */
 void ezb_bdb_set_scan_duration(uint8_t duration);

/**
 * @brief Get the scan duration time
 *
 * @return Scan duration, see @ref ezb_bdb_set_scan_duration
 */
uint8_t ezb_bdb_get_scan_duration(void);

/**
 * @brief Check if device has joined network or not
 *
 * @return
 *      - true: device is joined
 *      - false: device is not joined
 */
bool ezb_bdb_dev_joined(void);

/**
 * @brief  Set BDB commissioning mode.
 *
 * @param[in] commissioning_mode commissioning mode that refer to ezb_bdb_commissioning_mode_mask_t.
 *
 */
void ezb_bdb_set_commissioning_mode(ezb_bdb_comm_mode_mask_t commissioning_mode);

/**
 * @brief Set BDB commissioning mode
 *
 * @return commissioning mode, refer to ezb_bdb_commissioning_mode_mask_t
 */
ezb_bdb_comm_mode_mask_t ezb_bdb_get_commissioning_mode(void);

/**
 * @brief Get bdb_commissioning_status
 *
 * @return commissioning_status refer to ezb_bdb_commissioning_status_t
 *
 */
ezb_bdb_comm_status_t ezb_bdb_get_commissioning_status(void);

/**
 * @brief  Start top level commissioning procedure with specified mode mask.
 *
 * @param[in] mode_mask commissioning modes refer to ezb_bdb_commissioning_mode
 *
 * @return - EZB_ERR_NONE on success
 *
 */
ezb_err_t ezb_bdb_start_top_level_commissioning(ezb_bdb_comm_mode_mask_t mode_mask);

/**
 * @brief Schedule to cancel Steering procedure for a node not on a network
 *
 * @return
 *      - EZB_ERR_NONE: on success
 *      - EZB_ERR_FAIL: on failed
 */
ezb_err_t ezb_bdb_cancel_steering(void);

/**
 * @brief Schedule to cancel Formation procedure
 *
 * @return
 *      - EZB_ERR_NONE: on success
 *      - EZB_ERR_FAIL: on failed
 */
ezb_err_t ezb_bdb_cancel_formation(void);

/**
 * @brief Schedule to cancel touchlink target commissioning procedure
 *
 * @return
 *    - RET_OK: On success
 *    - RET_ERROR: Not in touchlink target procedure
 */
ezb_err_t ezb_bdb_cancel_touchlink_target(void);

/**
 * @brief Open Zigbee network
 *
 * @param[in] permit_duration Zigbee network open time
 * @return
 *      - EZB_ERR_NONE: on success
 *      - EZB_ERR_NO_MEM: not memory
 *      - EZB_ERR_FAILED: on failed
 */
ezb_err_t ezb_bdb_open_network(uint8_t permit_duration);

/**
 * @brief Close Zigbee network
 *
 * @return
 *      - EZB_ERR_NONE: on success
 *      - EZB_ERR_FAIL: on failure
 */
ezb_err_t ezb_bdb_close_network(void);

/**
 * @brief Perform `local reset` procedure
 * @note This only takes effect when the device is on a network. The device will leave the current network and
 *       clear all Zigbee persistent data, except the outgoing NWK frame counter. It will be in nearly the same
 *       state as when it left the factory. A `ZB_ZDO_SIGNAL_LEAVE` signal with `EZB_NWK_LEAVE_TYPE_RESET`
 *       will be triggered to indicate the end of the procedure.
 */
void ezb_bdb_reset_via_local_action(void);

/**
 * @brief   Check if device is factory new.
 *
 * @return - True factory new.
 *
 */
bool ezb_bdb_is_factory_new(void);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_BDB_H */
