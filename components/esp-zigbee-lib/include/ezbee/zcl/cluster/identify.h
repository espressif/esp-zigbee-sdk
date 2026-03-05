/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/identify_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure for the ZCL Identify Identify command request.
 */
typedef struct ezb_zcl_identify_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint16_t identify_time; /*!< Identify time in seconds. */
    } payload;                  /*!< Payload of the command. */
} ezb_zcl_identify_cmd_t;

/**
 * @brief Structure for the ZCL Identify IdentifyQuery command request.
 */
typedef struct ezb_zcl_identify_query_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
} ezb_zcl_identify_query_cmd_t;

/**
 * @brief Structure for the ZCL Identify TriggerEffect command request.
 */
typedef struct ezb_zcl_identify_trigger_effect_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint8_t effect_id;      /*!< Effect identifier to use. */
        uint8_t effect_variant; /*!< Variant of the effect to trigger. */
    } payload;                  /*!< Payload of the command. */
} ezb_zcl_identify_trigger_effect_cmd_t;

/**
 * @brief Message for the ZCL Identify TriggerEffect request.
 */
typedef struct ezb_zcl_identify_effect_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        uint8_t effect_id;               /*!< Effect identifier to use. */
        uint8_t effect_variant;          /*!< Variant of the effect to trigger. */
    } in;                                /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_identify_effect_message_t;

/**
 * @brief Send ZCL Identify Identify command request.
 *
 * @param cmd_req Pointer to the Identify command request structure, @ref ezb_zcl_identify_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_identify_identify_cmd_req(const ezb_zcl_identify_cmd_t *cmd_req);

/**
 * @brief Send ZCL Identify IdentifyQuery command request.
 *
 * @param cmd_req Pointer to the Identify Query command request structure, @ref ezb_zcl_identify_query_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_identify_identify_query_cmd_req(const ezb_zcl_identify_query_cmd_t *cmd_req);

/**
 * @brief Send ZCL Identify TriggerEffect command request.
 *
 * @param cmd_req Pointer to the TriggerEffect command request structure, @ref ezb_zcl_identify_trigger_effect_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_identify_trigger_effect_cmd_req(const ezb_zcl_identify_trigger_effect_cmd_t *cmd_req);

/**
 * @brief Check if the device is in identifying state.
 *
 * @param ep_id Endpoint ID of the device.
 * @return true if the device is in identifying state, false otherwise.
 */
bool ezb_zcl_is_identifying(uint8_t ep_id);

#ifdef __cplusplus
} /* extern "C" */
#endif
