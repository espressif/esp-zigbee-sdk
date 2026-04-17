/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/time_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Time server rank for synchronization priority.
 *
 * Devices SHALL synchronize to a Time server with the highest rank according to the following rules:
 * 1. A server with the Superseding bit set SHALL be chosen over a server without the bit set.
 * 2. A server with the Master bit SHALL be chosen over a server without the bit set.
 * 3. A coordinator with the Superseding and Master bits set SHALL be chosen over a server without the bits set.
 * 4. The server with the lower short address SHALL be chosen.
 *
 * Higher enum values indicate higher priority.
 */
typedef enum {
    EZB_ZCL_TIME_SERVER_RANK_UNSYNCHRONIZED                 = 0, /*!< Not synchronized. */
    EZB_ZCL_TIME_SERVER_RANK_SYNCHRONIZED                   = 1, /*!< Synchronized. */
    EZB_ZCL_TIME_SERVER_RANK_MASTER                         = 2, /*!< Master. */
    EZB_ZCL_TIME_SERVER_RANK_SUPERSEDING                    = 3, /*!< Superseding. */
    EZB_ZCL_TIME_SERVER_RANK_SUPERSEDING_MASTER             = 4, /*!< Superseding and Master. */
    EZB_ZCL_TIME_SERVER_RANK_COORDINATOR_SUPERSEDING_MASTER = 5, /*!< Coordinator with Superseding and Master. */
} ezb_zcl_time_server_rank_t;

/**
 * @brief Structure for the Time interface.
 * @note The time interface is used to get and set the current UTC time on the device.
 */
typedef struct ezb_zcl_time_interface_s {
    /**
     * @brief Get the current UTC time from the device.
     *
     * @return The current UTC time in seconds since the epoch.
     */
    uint32_t (*get_utc_time)(void);
    /**
     * @brief Set the current UTC time on the device.
     *
     * @param utc_time The UTC time in seconds since the epoch.
     */
    void (*set_utc_time)(uint32_t utc_time);

} ezb_zcl_time_interface_t;

/**
 * @brief Callback function for time server selection during synchronization.
 *
 * @param status The synchronization status/error code (e.g. EZB_ERR_NONE on success, EZB_ERR_TIMEOUT on timeout).
 */
typedef void (*ezb_zcl_time_server_sync_callback_t)(ezb_err_t status);

/**
 * @brief Register the time interface for ZCL Time server.
 *
 * @param ep_id     The endpoint ID.
 * @param interface The time interface.
 * @return Error code.
 */
ezb_err_t ezb_zcl_time_server_interface_register(uint8_t ep_id, ezb_zcl_time_interface_t interface);

/**
 * @brief Synchronize time from other time servers.
 *
 * @param ep_id             The endpoint ID of the time cluster.
 * @param timeout_seconds   The timeout in seconds.
 * @param callback          Callback to be called when time server selection completes.
 * @param expected_rank    The expected rank of the time server to synchronize to.
 * @return Error code.
 */
ezb_err_t ezb_zcl_time_server_synchronize_time(uint8_t                             ep_id,
                                               uint8_t                             timeout_seconds,
                                               ezb_zcl_time_server_sync_callback_t callback,
                                               ezb_zcl_time_server_rank_t          expected_rank);

#ifdef __cplusplus
} /* extern "C" */
#endif
