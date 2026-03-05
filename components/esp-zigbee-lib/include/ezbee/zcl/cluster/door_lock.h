/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/door_lock_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure for the ZCL DoorLock LockDoor command request.
 */
typedef struct ezb_zcl_door_lock_lock_door_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl;          /*!< Control information for the ZCL command. */
    bool                       aps_secur_enabled; /*!< APS security enabled transmission. */
} ezb_zcl_door_lock_lock_door_cmd_t;

/**
 * @brief Structure for the ZCL DoorLock UnlockDoor command request.
 * @anchor ezb_zcl_door_lock_unlock_door_cmd_t
 */
typedef ezb_zcl_door_lock_lock_door_cmd_t ezb_zcl_door_lock_unlock_door_cmd_t;

/**
 * @brief Message for the ZCL DoorLock LockDoor.
 */
typedef struct ezb_zcl_door_lock_lock_door_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
    } in;                                /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_door_lock_lock_door_message_t;

/**
 * @brief Message for the ZCL DoorLock UnlockDoor.
 * @anchor ezb_zcl_door_lock_unlock_door_message_t
 */
typedef ezb_zcl_door_lock_lock_door_message_t ezb_zcl_door_lock_unlock_door_message_t;

/**
 * @brief Message for the ZCL DoorLock LockDoor response.
 */
typedef struct ezb_zcl_door_lock_lock_door_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_status_t req_status; /*!< Status of the request command (indicates if the message was received successfully). */
    } in;                            /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_door_lock_lock_door_rsp_message_t;

/**
 * @brief Message for the ZCL DoorLock UnlockDoor response.
 * @anchor ezb_zcl_door_lock_unlock_door_rsp_message_t
 */
typedef ezb_zcl_door_lock_lock_door_rsp_message_t ezb_zcl_door_lock_unlock_door_rsp_message_t;

/**
 * @brief Send ZCL DoorLock LockDoor command request.
 *
 * @param cmd_req Pointer to the LockDoor command request structure, @ref ezb_zcl_door_lock_lock_door_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_door_lock_lock_door_cmd_req(const ezb_zcl_door_lock_lock_door_cmd_t *cmd_req);

/**
 * @brief Send ZCL DoorLock UnlockDoor command request.
 *
 * @param cmd_req Pointer to the UnlockDoor command request structure, @ref ezb_zcl_door_lock_unlock_door_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_door_lock_unlock_door_cmd_req(const ezb_zcl_door_lock_unlock_door_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
