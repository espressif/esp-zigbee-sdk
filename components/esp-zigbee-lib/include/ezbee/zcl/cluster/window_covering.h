/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/window_covering_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Payload for the ZCL WindowCovering movement command (lift/tilt value or percentage).
 */
typedef union ezb_zcl_window_covering_cmd_payload_u {
    uint8_t  lift_percentage; /*!< Lift percentage (for GoToLiftPercentage). */
    uint8_t  tilt_percentage; /*!< Tilt percentage (for GoToTiltPercentage). */
    uint16_t lift_value;      /*!< Lift value (for GoToLiftValue). */
    uint16_t tilt_value;      /*!< Tilt value (for GoToTiltValue). */
} ezb_zcl_window_covering_cmd_payload_t;

/**
 * @brief Structure for the ZCL WindowCovering movement command request.
 */
typedef struct ezb_zcl_window_covering_movement_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t              cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_window_covering_server_cmd_id_t cmd_id;   /*!< Window covering command ID. */
    ezb_zcl_window_covering_cmd_payload_t   payload;  /*!< Payload of the command. */
} ezb_zcl_window_covering_movement_cmd_t;

/**
 * @brief Message for the ZCL WindowCovering movement.
 */
typedef struct ezb_zcl_window_covering_movement_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;              /*!< ZCL command header information.
                                                           See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_window_covering_cmd_payload_t   payload; /*!< Payload from the command. */
    } in;                                                /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_window_covering_movement_message_t;

/**
 * @brief Send ZCL WindowCovering movement command request.
 *
 * @param cmd_req Pointer to the movement command request structure, @ref ezb_zcl_window_covering_movement_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_window_covering_movement_cmd_req(const ezb_zcl_window_covering_movement_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
