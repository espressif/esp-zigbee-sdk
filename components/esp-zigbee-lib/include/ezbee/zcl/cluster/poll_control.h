/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/poll_control_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief CheckInInterval value meaning no check-in.
 */
#define EZB_ZCL_POLL_CONTROL_CHECK_IN_INTERVAL_NO_CHECK_IN_VALUE (0x00000000)

/**
 * @brief Default value of manufacturer-specific predefined check-in timeout in milliseconds.
 */
#define EZB_ZCL_POLL_CONTROL_PREDEFINED_CHECK_IN_TIMEOUT_DEFAULT_VALUE (500)

/**
 * @brief Structure for the ZCL Poll Control CheckIn command request.
 */
typedef struct ezb_zcl_poll_control_check_in_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl;          /*!< Control information for the ZCL command. */
} ezb_zcl_poll_control_check_in_cmd_t;

/**
 * @brief Structure for the ZCL Poll Control FastPollStop command request.
 */
typedef struct ezb_zcl_poll_control_fast_poll_stop_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
} ezb_zcl_poll_control_fast_poll_stop_cmd_t;

/**
 * @brief Structure for the ZCL Poll Control SetLongPollInterval command request.
 */
typedef struct ezb_zcl_poll_control_set_long_poll_interval_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl;           /*!< Control information for the ZCL command. */
    uint32_t                   long_poll_interval; /*!< Long poll interval (quarter-seconds). */
} ezb_zcl_poll_control_set_long_poll_interval_cmd_t;

/**
 * @brief Structure for the ZCL Poll Control SetShortPollInterval command request.
 */
typedef struct ezb_zcl_poll_control_set_short_poll_interval_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl;            /*!< Control information for the ZCL command. */
    uint16_t                   short_poll_interval; /*!< Short poll interval (quarter-seconds). */
} ezb_zcl_poll_control_set_short_poll_interval_cmd_t;

/**
 * @brief Message for the ZCL Poll Control CheckIn message.
 */
typedef struct ezb_zcl_poll_control_check_in_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
    } in;                                /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result;            /*!< Status of processing in application. */
        uint16_t         fast_poll_timeout; /*!< Fast poll timeout (quarter-seconds). */
    } out;                                  /*!< Output: result to send back. */
} ezb_zcl_poll_control_check_in_message_t;

/**
 * @brief Send ZCL Poll Control CheckIn command request.
 *
 * @param cmd_req Pointer to the CheckIn command request structure, @ref ezb_zcl_poll_control_check_in_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_poll_control_check_in_cmd_req(const ezb_zcl_poll_control_check_in_cmd_t *cmd_req);

/**
 * @brief Send ZCL Poll Control FastPollStop command request.
 *
 * @param cmd_req Pointer to the FastPollStop command request structure, @ref ezb_zcl_poll_control_fast_poll_stop_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_poll_control_fast_poll_stop_cmd_req(const ezb_zcl_poll_control_fast_poll_stop_cmd_t *cmd_req);

/**
 * @brief Send ZCL Poll Control SetLongPollInterval command request.
 *
 * @param cmd_req Pointer to the SetLongPollInterval command request structure, @ref
 * ezb_zcl_poll_control_set_long_poll_interval_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_poll_control_set_long_poll_interval_cmd_req(const ezb_zcl_poll_control_set_long_poll_interval_cmd_t *cmd_req);

/**
 * @brief Send ZCL Poll Control SetShortPollInterval command request.
 *
 * @param cmd_req Pointer to the SetShortPollInterval command request structure, @ref
 * ezb_zcl_poll_control_set_short_poll_interval_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_poll_control_set_short_poll_interval_cmd_req(
    const ezb_zcl_poll_control_set_short_poll_interval_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
