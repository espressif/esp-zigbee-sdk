/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/electrical_measurement_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Profile interval period.
 */
typedef enum {
    EZB_ZCL_ELECTRICAL_MEASUREMENT_DAILY       = 0, /*!< Daily. */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_60_MINUTES  = 1, /*!< 60 minutes. */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_30_MINUTES  = 2, /*!< 30 minutes. */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_15_MINUTES  = 3, /*!< 15 minutes. */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_10_MINUTES  = 4, /*!< 10 minutes. */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_7_5_MINUTES = 5, /*!< 7.5 minutes. */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_5_MINUTES   = 6, /*!< 5 minutes. */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_2_5_MINUTES = 7, /*!< 2.5 minutes. */
} ezb_zcl_electrical_measurement_profile_interval_period_t;

/**
 * @brief Get measurement profile response status.
 * @anchor ezb_zcl_electrical_measurement_status_e
 */
typedef enum {
    EZB_ZCL_ELECTRICAL_MEASUREMENT_STATUS_SUCCESS             = 0x00, /*!< Success. */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_STATUS_UNSUPPORTED_PROFILE = 0x01, /*!< Attribute profile not supported. */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_STATUS_INVALID_START_TIME  = 0x02, /*!< Invalid start time. */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_STATUS_NO_MORE_INTERVALS   = 0x03, /*!< More intervals requested than can be returned. */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_STATUS_NO_INTERVALS        = 0x04, /*!< No intervals available for the requested time. */
} ezb_zcl_electrical_measurement_status_t;

/**
 * @brief Payload for the ZCL ElectricalMeasurement GetMeasurementProfile command.
 */
typedef struct ezb_zcl_electrical_measurement_get_meas_prof_payload_s {
    uint16_t attr_id;          /*!< Attribute ID. */
    uint32_t start_time;       /*!< Start time. */
    uint8_t  num_of_intervals; /*!< Number of intervals. */
} ezb_zcl_electrical_measurement_get_meas_prof_payload_t;

/**
 * @brief Payload for the ZCL ElectricalMeasurement GetProfileInfo response.
 */
typedef struct ezb_zcl_electrical_measurement_get_prof_info_rsp_payload_s {
    uint8_t   prof_count;           /*!< Total number of supported profiles. */
    uint8_t   prof_interval_period; /*!< Profile interval period. */
    uint8_t   max_num_of_intervals; /*!< Maximum number of intervals. */
    uint16_t *list_of_attributes;   /*!< List of attribute IDs. */
} ezb_zcl_electrical_measurement_get_prof_info_rsp_payload_t;

/**
 * @brief Payload for the ZCL ElectricalMeasurement GetMeasurementProfile response.
 */
typedef struct ezb_zcl_electrical_measurement_get_meas_prof_rsp_payload_s {
    uint32_t start_time;                 /*!< Start time. */
    uint8_t  status;                     /*!< Status of the command, see @ref ezb_zcl_electrical_measurement_status_e. */
    uint8_t  prof_interval_period;       /*!< Profile interval period. */
    uint8_t  num_of_intervals_delivered; /*!< Number of intervals delivered. */
    uint16_t attr_id;                    /*!< Attribute ID. */
    uint8_t *intervals;                  /*!< Array of attribute values. */
} ezb_zcl_electrical_measurement_get_meas_prof_rsp_payload_t;

/**
 * @brief Structure for the ZCL ElectricalMeasurement GetProfileInfo command request.
 */
typedef struct ezb_zcl_electrical_measurement_get_prof_info_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
} ezb_zcl_electrical_measurement_get_prof_info_cmd_t;

/**
 * @brief Structure for the ZCL ElectricalMeasurement GetMeasurementProfile command request.
 */
typedef struct ezb_zcl_electrical_measurement_get_meas_prof_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                             cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_electrical_measurement_get_meas_prof_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_electrical_measurement_get_meas_prof_cmd_t;

/**
 * @brief Message for the ZCL ElectricalMeasurement GetProfileInfo.
 */
typedef struct ezb_zcl_electrical_measurement_get_prof_info_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
    } in;                                /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t                                            result;  /*!< Status of processing in application. */
        ezb_zcl_electrical_measurement_get_prof_info_rsp_payload_t *payload; /*!< Payload from GetProfileInfo response. */
        uint8_t               num_of_attr_being_profiled;                    /*!< Number of attributes being profiled. */
        ezb_zcl_cmd_cnf_ctx_t cnf_ctx; /*!< Command confirmation context, triggered when response is confirmed. */
    } out;                             /*!< Output: result to send back. */
} ezb_zcl_electrical_measurement_get_prof_info_message_t;

/**
 * @brief Message for the ZCL ElectricalMeasurement GetMeasurementProfile.
 */
typedef struct ezb_zcl_electrical_measurement_get_meas_prof_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                                /*!< ZCL command header information.
                                                                             See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_electrical_measurement_get_meas_prof_payload_t payload; /*!< Payload from GetMeasurementProfile command. */
    } in;                                                               /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
        ezb_zcl_electrical_measurement_get_meas_prof_rsp_payload_t
                             *payload; /*!< Payload from GetMeasurementProfile response. */
        ezb_zcl_cmd_cnf_ctx_t cnf_ctx; /*!< Command confirmation context, triggered when response is confirmed. */
    } out;                             /*!< Output: result to send back. */
} ezb_zcl_electrical_measurement_get_meas_prof_message_t;

/**
 * @brief Message for the ZCL ElectricalMeasurement GetProfileInfo response.
 */
typedef struct ezb_zcl_electrical_measurement_get_prof_info_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                                    /*!< ZCL command header information.
                                                                                 See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_electrical_measurement_get_prof_info_rsp_payload_t payload; /*!< Payload from GetProfileInfo response. */
    } in;                                                                   /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_electrical_measurement_get_prof_info_rsp_message_t;

/**
 * @brief Message for the ZCL ElectricalMeasurement GetMeasurementProfile response.
 */
typedef struct ezb_zcl_electrical_measurement_get_meas_prof_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                                    /*!< ZCL command header information.
                                                                                 See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_electrical_measurement_get_meas_prof_rsp_payload_t payload; /*!< Payload from GetMeasurementProfile response. */
    } in;                                                                   /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_electrical_measurement_get_meas_prof_rsp_message_t;

/**
 * @brief Send ZCL ElectricalMeasurement GetProfileInfo command request.
 *
 * @param cmd_req Pointer to the GetProfileInfo command request structure, @ref
 * ezb_zcl_electrical_measurement_get_prof_info_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_electrical_measurement_get_prof_info_cmd_req(
    const ezb_zcl_electrical_measurement_get_prof_info_cmd_t *cmd_req);

/**
 * @brief Send ZCL ElectricalMeasurement GetMeasurementProfile command request.
 *
 * @param cmd_req Pointer to the GetMeasurementProfile command request structure, @ref
 * ezb_zcl_electrical_measurement_get_meas_prof_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_electrical_measurement_get_meas_prof_cmd_req(
    const ezb_zcl_electrical_measurement_get_meas_prof_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
