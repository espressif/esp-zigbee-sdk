/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "esp_err.h"
#include "esp_zigbee_type.h"

/*!< Minimum commissioning period */
#define ESP_ZB_BDB_MIN_COMMISSIONING_TIME 180U

/**
 * @brief Mask bit of the Base Device Behavior commissioning mode
 *
 */
 typedef enum esp_zb_bdb_commissioning_mode_mask_s {
    ESP_ZB_BDB_INITIALIZATION          = 0x00,  /*!< BDB commissioning initialization bit */
    ESP_ZB_BDB_TOUCHLINK_COMMISSIONING = 0x01,  /*!< BDB Touchlink commissioning bit */
    ESP_ZB_BDB_NETWORK_STEERING        = 0x02,  /*!< BDB commissioning network steering bit */
    ESP_ZB_BDB_NETWORK_FORMATION       = 0x04,  /*!< BDB commissioning network formation bit */
    ESP_ZB_BDB_FINDING_N_BINDING       = 0x08,  /*!< BDB commissioning finding & binding bit */
    ESP_ZB_BDB_TOUCHLINK_TARGET        = 0x40,  /*!< BDB Touchlink commissioning target bit */
} esp_zb_bdb_commissioning_mode_mask_t;

/**
 * @brief Enumeration of the typical Base Device Behavior (BDB) mode
 *
 */
 typedef enum {
    ESP_ZB_BDB_MODE_INITIALIZATION          = ESP_ZB_BDB_INITIALIZATION,            /*!< BDB initialization mode */
    ESP_ZB_BDB_MODE_TOUCHLINK_COMMISSIONING = ESP_ZB_BDB_TOUCHLINK_COMMISSIONING,   /*!< BDB touchlink commissioning mode */
    ESP_ZB_BDB_MODE_NETWORK_STEERING        = ESP_ZB_BDB_NETWORK_STEERING,          /*!< BDB network steering mode */
    ESP_ZB_BDB_MODE_NETWORK_FORMATION       = ESP_ZB_BDB_NETWORK_FORMATION,         /*!< BDB network formation mode */
    ESP_ZB_BDB_MODE_TOUCHLINK_TARGET        = ESP_ZB_BDB_TOUCHLINK_TARGET,          /*!< BDB network touchlink target mode */
} esp_zb_bdb_commissioning_mode_t;

/**
 * @brief BDB commissioning status
 *
 */
typedef enum esp_zb_bdb_commissioning_status_s
{
    ESP_ZB_BDB_STATUS_SUCCESS = 0,                 /*!< The commissioning sub-procedure was successful. */
    ESP_ZB_BDB_STATUS_IN_PROGRESS,                 /*!< One of the commissioning sub-procedures has started but is not yet complete. */
    ESP_ZB_BDB_STATUS_NOT_AA_CAPABLE,              /*!< The initiator is not address assignment capable during touchlink. */
    ESP_ZB_BDB_STATUS_NO_NETWORK,                  /*!< A network has not been found during network steering or touchlink. */
    ESP_ZB_BDB_STATUS_TARGET_FAILURE,              /*!< A node has not joined a network when requested during touchlink. */
    ESP_ZB_BDB_STATUS_FORMATION_FAILURE,           /*!< A network could not be formed during network formation. */
    ESP_ZB_BDB_STATUS_NO_IDENTIFY_QUERY_RESPONSE,  /*!< No response to an identify query command has been received during finding and binding. */
    ESP_ZB_BDB_STATUS_BINDING_TABLE_FULL,          /*!< A binding table entry could not be created due to insufficient space in the binding table during finding and binding. */
    ESP_ZB_BDB_STATUS_NO_SCAN_RESPONSE,            /*!< No response to a scan request inter-PAN command has been received during touchlink. */
    ESP_ZB_BDB_STATUS_NOT_PERMITTED,               /*!< A touchlink (steal) attempt was made when a node is already connected to a centralized security network.
                                                     A node was instructed to form a network when it did not have a logical type of either Zigbee coordinator or Zigbee router. */
    ESP_ZB_BDB_STATUS_TCLK_EX_FAILURE,             /*!< The Trust Center link key exchange procedure has failed attempting to join a centralized security network. */
    ESP_ZB_BDB_STATUS_NOT_ON_A_NETWORK,            /*!< A commissioning procedure was forbidden since the node was not currently on a network. */
    ESP_ZB_BDB_STATUS_ON_A_NETWORK,                /*!< A commissioning procedure was forbidden since the node was currently on a network. */
    ESP_ZB_BDB_STATUS_CANCELLED,                   /*!< The current operation (steering or formation) was cancelled by an app */
    ESP_ZB_BDB_STATUS_DEV_ANNCE_SEND_FAILURE       /*!< A device announce sending has been failed (e.g. device announce haven't acked by parent router). */
} esp_zb_bdb_commissioning_status_t;

/**
 * @brief BDB find & binding commissioning callback state
 *
 */
typedef enum esp_zb_bdb_commissioning_binding_cb_state_e {
    ESP_ZB_BDB_COMM_BIND_SUCCESS  = 0,  /*!< Previously user applied bind finished successfully */
    ESP_ZB_BDB_COMM_BIND_FAIL     = 1,  /*!< Previously user applied bind failed */
    ESP_ZB_BDB_COMM_BIND_ASK_USER = 2,  /*!< Ask user whether to perform binding */
} esp_zb_bdb_commissioning_binding_cb_state_t;

/**
 * @brief A callback for the application to determine which clusters should be bound to the device during BDB finding & binding.
 *
 * @param[in] status     The status of the callback. See @ref esp_zb_bdb_commissioning_binding_cb_state_t.
 * @param[in] ieee_addr  The IEEE address where the cluster is located.
 * @param[in] ep_id      The endpoint identifier where the cluster is located.
 *
 * @return true if the cluster should be bound; false otherwise.
 */
typedef bool (*esp_zb_bdb_binding_initiator_callback_t)(int16_t status, esp_zb_ieee_addr_t ieee_addr, uint8_t ep_id, uint16_t cluster_id);

/**
 * @brief Start the endpoint in BDB Finding & Binding target commissioning mode.
 *
 * @param[in] ep_id     The endpoint identifier to be started in BDB F&B target mode.
 * @param[in] duration  The duration (in seconds, ≥ ESP_ZB_BDB_MIN_COMMISSIONING_TIME) during which the BDB Finding and Binding target mode remains active.
 *
 * @return
 *          - ESP_OK: Success.
 *          - ESP_ERR_INVALID_ARG: Invalid argument; either the ep_id is not registered or the duration is out of range.
 *          - ESP_ERR_INVALID_STATE: Invalid state; the device is not connected to a network.
 *          - ESP_FAIL: Failure.
 */
esp_err_t esp_zb_bdb_finding_binding_start_target(uint8_t ep_id, uint16_t duration);

/**
 * @brief Cancel the endpoint from BDB Finding & Binding target commissioning mode.
 *
 * @param[in] ep_id The endpoint identifier to be cancel from BDB F&B target mode.
 *
 * @return
 *          - ESP_OK: Success, otherwise, failure.
 */
esp_err_t esp_zb_bdb_finding_binding_cancel_target(uint8_t ep_id);

/**
 * @brief Start the endpoint in BDB Finding & Binding initiator commissioning mode.
 *
 * @param[in] ep_id The endpoint identifier to be start in BDB F&B initiator mode.
 * @param[in] cb    The callback to be invoked when attempting to bind to a F&B target, See @ref esp_zb_bdb_binding_initiator_callback_t.
 *
 * @return
 *          - ESP_OK: Success.
 *          - ESP_ERR_INVALID_STATE: Invalid state; the device is not connected to a network.
 *          - ESP_FAIL: Failure.
 */
esp_err_t esp_zb_bdb_finding_binding_start_initiator(uint8_t ep_id, esp_zb_bdb_binding_initiator_callback_t cb);

/**
 * @brief Cancel the endpoint from BDB Finding & Binding initiator commissioning mode.
 * 
 * @return
 *          - ESP_OK: Success, otherwise, failure.
 */
esp_err_t esp_zb_bdb_finding_binding_cancel_initiator(void);

#ifdef __cplusplus
}
#endif
