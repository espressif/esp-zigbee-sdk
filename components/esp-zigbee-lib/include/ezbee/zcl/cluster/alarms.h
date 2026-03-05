/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/alarms_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure for the ZCL Alarms command request with no payload.
 */
typedef struct ezb_zcl_alarms_cmd_with_no_payload_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
} ezb_zcl_alarms_cmd_with_no_payload_t;

/**
 * @brief Payload for the ZCL Alarms ResetAlarm command.
 */
typedef struct ezb_zcl_alarms_reset_alarm_payload_s {
    uint8_t  alarm_code; /*!< Alarm code. */
    uint16_t cluster_id; /*!< Cluster ID. */
} ezb_zcl_alarms_reset_alarm_payload_t;

typedef ezb_zcl_alarms_reset_alarm_payload_t ezb_zcl_alarms_alarm_payload_t;

/**
 * @brief Payload for the ZCL Alarms GetAlarm response.
 */
typedef struct ezb_zcl_alarms_get_alarm_rsp_payload_s {
    uint8_t  status;     /*!< Status. */
    uint8_t  alarm_code; /*!< Alarm code. */
    uint16_t cluster_id; /*!< Cluster ID. */
    uint32_t timestamp;  /*!< Timestamp. */
} ezb_zcl_alarms_get_alarm_rsp_payload_t;

/**
 * @brief Structure for the ZCL Alarms ResetAlarm command request.
 */
typedef struct ezb_zcl_alarms_reset_alarm_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t           cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_alarms_reset_alarm_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_alarms_reset_alarm_cmd_t;

/**
 * @brief Structure for the ZCL Alarms ResetAllAlarms command request.
 * @anchor ezb_zcl_alarms_reset_all_alarms_cmd_t
 */
typedef ezb_zcl_alarms_cmd_with_no_payload_t ezb_zcl_alarms_reset_all_alarms_cmd_t;

/**
 * @brief Structure for the ZCL Alarms GetAlarm command request.
 * @anchor ezb_zcl_alarms_get_alarm_cmd_t
 */
typedef ezb_zcl_alarms_cmd_with_no_payload_t ezb_zcl_alarms_get_alarm_cmd_t;

/**
 * @brief Structure for the ZCL Alarms ResetAlarmLog command request.
 * @anchor ezb_zcl_alarms_reset_alarm_log_cmd_t
 */
typedef ezb_zcl_alarms_cmd_with_no_payload_t ezb_zcl_alarms_reset_alarm_log_cmd_t;

/**
 * @brief Structure for the ZCL Alarms Alarm command request.
 */
typedef struct ezb_zcl_alarms_alarm_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t     cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_alarms_alarm_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_alarms_alarm_cmd_t;

/**
 * @brief Message for the ZCL Alarms ResetAlarm message.
 */
typedef struct ezb_zcl_alarms_reset_alarm_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;             /*!< ZCL command header information.
                                                          See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_alarms_reset_alarm_payload_t payload; /*!< Payload from the ResetAlarm command. */
    } in;                                             /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_alarms_reset_alarm_message_t;

/**
 * @brief Message for the ZCL Alarms ResetAllAlarms message.
 */
typedef struct ezb_zcl_alarms_reset_all_alarms_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;             /*!< ZCL command header information.
                                                          See @ref ezb_zcl_cmd_hdr_s. */
    } in;                                             /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_alarms_reset_all_alarms_message_t;

/**
 * @brief Message for the ZCL Alarms Alarm command message.
 */
typedef struct ezb_zcl_alarms_alarm_cmd_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;             /*!< ZCL command header information.
                                                          See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_alarms_alarm_payload_t payload; /*!< Payload from the Alarm command. */
    } in;                                       /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_alarms_alarm_cmd_message_t;

/**
 * @brief Message for the ZCL Alarms GetAlarm response message.
 */
typedef struct ezb_zcl_alarms_get_alarm_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;               /*!< ZCL command header information.
                                                            See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_alarms_get_alarm_rsp_payload_t payload; /*!< Payload from the GetAlarm response. */
    } in;                                               /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_alarms_get_alarm_rsp_message_t;

/**
 * @brief Send ZCL Alarms ResetAlarm command request.
 *
 * @param cmd_req Pointer to the ResetAlarm command request structure, @ref ezb_zcl_alarms_reset_alarm_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_alarms_reset_alarm_cmd_req(const ezb_zcl_alarms_reset_alarm_cmd_t *cmd_req);

/**
 * @brief Send ZCL Alarms ResetAllAlarms command request.
 *
 * @param cmd_req Pointer to the ResetAllAlarms command request structure, @ref ezb_zcl_alarms_reset_all_alarms_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_alarms_reset_all_alarms_cmd_req(const ezb_zcl_alarms_reset_all_alarms_cmd_t *cmd_req);

/**
 * @brief Send ZCL Alarms GetAlarm command request.
 *
 * @param cmd_req Pointer to the GetAlarm command request structure, @ref ezb_zcl_alarms_get_alarm_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_alarms_get_alarm_cmd_req(const ezb_zcl_alarms_get_alarm_cmd_t *cmd_req);

/**
 * @brief Send ZCL Alarms ResetAlarmLog command request.
 *
 * @param cmd_req Pointer to the ResetAlarmLog command request structure, @ref ezb_zcl_alarms_reset_alarm_log_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_alarms_reset_alarm_log_cmd_req(const ezb_zcl_alarms_reset_alarm_log_cmd_t *cmd_req);

/**
 * @brief Send ZCL Alarms Alarm command request.
 *
 * @param cmd_req Pointer to the Alarm command request structure, @ref ezb_zcl_alarms_alarm_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_alarms_alarm_cmd_req(const ezb_zcl_alarms_alarm_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
