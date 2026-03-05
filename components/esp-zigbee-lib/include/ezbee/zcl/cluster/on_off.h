/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/on_off_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure for the ZCL OnOff command request (On, Off, or Toggle).
 */
typedef struct ezb_zcl_on_off_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
} ezb_zcl_on_off_cmd_t;

/**
 * @brief Structure for the ZCL OnOff OffWithEffect command request.
 */
typedef struct ezb_zcl_on_off_off_with_effect_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint8_t effect_id;      /*!< Effect identifier to use. */
        uint8_t effect_variant; /*!< Variant of the effect to trigger. */
    } payload;                  /*!< Payload of the command. */
} ezb_zcl_on_off_off_with_effect_cmd_t;

/**
 * @brief Structure for the ZCL OnOff OnWithTimedOff command request.
 */
typedef struct ezb_zcl_on_off_on_with_timed_off_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint8_t  on_off_control; /*!< On/Off control. */
        uint16_t on_time;        /*!< On time in 1/10th seconds. */
        uint16_t off_wait_time;  /*!< Off wait time in 1/10th seconds. */
    } payload;                   /*!< Payload of the command. */
} ezb_zcl_on_off_on_with_timed_off_cmd_t;

/**
 * @brief Message for the ZCL OnOff OffWithEffect message.
 */
typedef struct ezb_zcl_on_off_off_with_effect_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        uint8_t effect_id;      /*!< Effect identifier to use. */
        uint8_t effect_variant; /*!< Variant of the effect to trigger. */
    } in;                       /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_on_off_off_with_effect_message_t;

/** Break Change: separate on/off command */
/**
 * @brief Send ZCL OnOff Off command request.
 *
 * @param cmd_req Pointer to the Off command request structure, @ref ezb_zcl_on_off_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_on_off_off_cmd_req(const ezb_zcl_on_off_cmd_t *cmd_req);

/**
 * @brief Send ZCL OnOff On command request.
 *
 * @param cmd_req Pointer to the On command request structure, @ref ezb_zcl_on_off_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_on_off_on_cmd_req(const ezb_zcl_on_off_cmd_t *cmd_req);

/**
 * @brief Send ZCL OnOff Toggle command request.
 *
 * @param cmd_req Pointer to the Toggle command request structure, @ref ezb_zcl_on_off_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_on_off_toggle_cmd_req(const ezb_zcl_on_off_cmd_t *cmd_req);

/**
 * @brief Send ZCL OnOff OffWithEffect command request.
 *
 * @param cmd_req Pointer to the OffWithEffect command request structure, @ref ezb_zcl_on_off_off_with_effect_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_on_off_off_with_effect_cmd_req(const ezb_zcl_on_off_off_with_effect_cmd_t *cmd_req);

/**
 * @brief Send ZCL OnOff OnWithRecallGlobalScene command request.
 *
 * @param cmd_req Pointer to the On command request structure, @ref ezb_zcl_on_off_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_on_off_on_with_recall_global_scene_cmd_req(const ezb_zcl_on_off_cmd_t *cmd_req);

/**
 * @brief Send ZCL OnOff OnWithTimedOff command request.
 *
 * @param cmd_req Pointer to the OnWithTimedOff command request structure, @ref ezb_zcl_on_off_on_with_timed_off_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_on_off_on_with_timed_off_cmd_req(const ezb_zcl_on_off_on_with_timed_off_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
