/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/thermostat_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Maximum number of transitions for weekly schedule of ZCL Thermostat cluster.
 */
#define EZB_ZCL_THERMOSTAT_WEEKLY_SCHEDULE_MAX_TRANSITION_NUM 10

/**
 * @brief Unit of setpoint raise or lower amount of ZCL Thermostat cluster.
 */
#define EZB_ZCL_THERMOSTAT_SETPOINT_RAISE_LOWER_AMOUNT_UNIT 10

/**
 * @brief Enumeration for setpoint mode of ZCL Thermostat cluster.
 * @anchor ezb_zcl_thermostat_setpoint_mode_t
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_SETPOINT_MODE_HEAT, /*!< Heat mode */
    EZB_ZCL_THERMOSTAT_SETPOINT_MODE_COOL, /*!< Cool mode */
    EZB_ZCL_THERMOSTAT_SETPOINT_MODE_BOTH, /*!< Both mode */
} ezb_zcl_thermostat_setpoint_mode_t;

/**
 * @brief Mode for the SetWeeklySchedule command.
 * @anchor ezb_zcl_thermostat_set_weekly_schedule_mode_t
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_SET_WEEKLY_SCHEDULE_MODE_HEAT_SETPOINT = 1 << 0, /*!< Heat setpoint mode for sequence */
    EZB_ZCL_THERMOSTAT_SET_WEEKLY_SCHEDULE_MODE_COOL_SETPOINT = 1 << 1, /*!< Cool setpoint mode for sequence */
} ezb_zcl_thermostat_set_weekly_schedule_mode_t;

/**
 * @brief Payload for the ZCL Thermostat SetpointRaiseOrLower command.
 */
typedef struct ezb_zcl_thermostat_setpoint_raise_or_lower_payload_s {
    uint8_t mode;   /*!< Which setpoint to configure (HEAT/COOL/BOTH). see @ref ezb_zcl_thermostat_setpoint_mode_t */
    int8_t  amount; /*!< Amount to increase/decrease setpoint(s), in steps of 0.1°C. */
} ezb_zcl_thermostat_setpoint_raise_or_lower_payload_t;

/**
 * @brief Structure for the ZCL Thermostat SetpointRaiseOrLower command request.
 */
typedef struct ezb_zcl_thermostat_setpoint_raise_or_lower_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                           cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_thermostat_setpoint_raise_or_lower_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_thermostat_setpoint_raise_or_lower_cmd_t;

/**
 * @brief Structure for ZCL Thermostat WeeklySchedule transition.
 */
typedef struct ezb_zcl_thermostat_weekly_schedule_transition_s {
    uint16_t start_time;    /*!< Start time of the schedule transition for the day. */
    int16_t  heat_setpoint; /*!< Heat setpoint (0.01°C resolution), if heat bit set in mode. */
    int16_t  cool_setpoint; /*!< Cool setpoint (0.01°C resolution), if cool bit set in mode. */
} ezb_zcl_thermostat_weekly_schedule_transition_t;

/**
 * @brief Payload for the ZCL Thermostat SetWeeklySchedule command.
 */
typedef struct ezb_zcl_thermostat_set_weekly_schedule_payload_s {
    uint8_t                                          num_of_trans; /*!< Number of transitions in this sequence. */
    uint8_t                                          day_of_week;  /*!< Day of week for all transitions in this payload. */
    uint8_t                                          mode_for_req; /*!< How to decode setpoint fields of each transition. */
    ezb_zcl_thermostat_weekly_schedule_transition_t *transitions;  /*!< Sequence of transitions to apply. */
} ezb_zcl_thermostat_set_weekly_schedule_payload_t;

/**
 * @brief Structure for the entry of Thermostat Weekly Schedule
 */
typedef struct ezb_zcl_thermostat_weekly_schedule_entry_s {
    uint8_t                                         mode_of_transition; /*!< Mode of the transition. */
    uint8_t                                         num_of_transition;  /*!< Number of transitions in the entry. */
    ezb_zcl_thermostat_weekly_schedule_transition_t *transitions;       /*!< Transitions in the entry. */
} ezb_zcl_thermostat_weekly_schedule_entry_t;

/**
 * @brief Payload for the ZCL Thermostat GetWeeklySchedule response.
 */
typedef ezb_zcl_thermostat_set_weekly_schedule_payload_t ezb_zcl_thermostat_get_weekly_schedule_rsp_payload_t;

/**
 * @brief Structure for the ZCL Thermostat SetWeeklySchedule command request.
 */
typedef struct ezb_zcl_thermostat_set_weekly_schedule_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                       cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_thermostat_set_weekly_schedule_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_thermostat_set_weekly_schedule_cmd_t;

/**
 * @brief Payload for the ZCL Thermostat GetWeeklySchedule command.
 */
typedef struct ezb_zcl_thermostat_get_weekly_schedule_payload_s {
    uint8_t days_to_return; /*!< Number of days to return in the response. */
    uint8_t mode_to_return; /*!< Mode to return in the response. see @ref ezb_zcl_thermostat_setpoint_mode_t */
} ezb_zcl_thermostat_get_weekly_schedule_payload_t;

/**
 * @brief Structure for the ZCL Thermostat GetWeeklySchedule command request.
 */
typedef struct ezb_zcl_thermostat_get_weekly_schedule_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                       cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_thermostat_get_weekly_schedule_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_thermostat_get_weekly_schedule_cmd_t;

/**
 * @brief Structure for the ZCL Thermostat ClearWeeklySchedule command request.
 */
typedef struct ezb_zcl_thermostat_clear_weekly_schedule_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
} ezb_zcl_thermostat_clear_weekly_schedule_cmd_t;

/**
 * @brief Message for ZCL Thermostat setpoint (heat/cool).
 */
typedef struct ezb_zcl_thermostat_setpoint_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        uint8_t mode; /*!< Which setpoint is configured (HEAT/COOL/BOTH). see @ref ezb_zcl_thermostat_setpoint_mode_t */
        int16_t setpoint_cool; /*!< Cool setpoint (0.01°C resolution) to apply. */
        int16_t setpoint_heat; /*!< Heat setpoint (0.01°C resolution) to apply. */
    } in;                      /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_thermostat_setpoint_message_t;

/**
 * @brief Message for ZCL Thermostat SetWeeklySchedule.
 */
typedef struct ezb_zcl_thermostat_set_weekly_schedule_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t                          *header;  /*!< Header of the command. */
        ezb_zcl_thermostat_set_weekly_schedule_payload_t *payload; /*!< Payload of the command. */
    } in;                                                          /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_thermostat_set_weekly_schedule_message_t;

/**
 * @brief Message for ZCL Thermostat GetWeeklySchedule response.
 */
typedef struct ezb_zcl_thermostat_get_weekly_schedule_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Common information for Zigbee device callback. */
    struct {
        const ezb_zcl_cmd_hdr_t                              *header;  /*!< Header of the command. */
        ezb_zcl_thermostat_get_weekly_schedule_rsp_payload_t *payload; /*!< Response payload. */
    } in;                                                              /*!< Input: parsed fields from the response. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_thermostat_get_weekly_schedule_rsp_message_t;

/**
 * @brief Send ZCL Thermostat SetpointRaiseOrLower command request.
 *
 * @param cmd_req Pointer to the SetpointRaiseOrLower command request structure, @ref
 * ezb_zcl_thermostat_setpoint_raise_or_lower_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_thermostat_setpoint_raise_or_lower_cmd_req(const ezb_zcl_thermostat_setpoint_raise_or_lower_cmd_t *cmd_req);

/**
 * @brief Send ZCL Thermostat SetWeeklySchedule command request.
 *
 * @param cmd_req Pointer to the SetWeeklySchedule command request structure, @ref ezb_zcl_thermostat_set_weekly_schedule_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_thermostat_set_weekly_schedule_cmd_req(const ezb_zcl_thermostat_set_weekly_schedule_cmd_t *cmd_req);

/**
 * @brief Send ZCL Thermostat GetWeeklySchedule command request.
 *
 * @param cmd_req Pointer to the GetWeeklySchedule command request structure, @ref ezb_zcl_thermostat_get_weekly_schedule_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_thermostat_get_weekly_schedule_cmd_req(const ezb_zcl_thermostat_get_weekly_schedule_cmd_t *cmd_req);

/**
 * @brief Send ZCL Thermostat ClearWeeklySchedule command request.
 *
 * @param cmd_req Pointer to the ClearWeeklySchedule command request structure, @ref
 * ezb_zcl_thermostat_clear_weekly_schedule_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_thermostat_clear_weekly_schedule_cmd_req(const ezb_zcl_thermostat_clear_weekly_schedule_cmd_t *cmd_req);

/**
 * @brief Start the weekly schedule loop.
 *
 * @param ep_id Endpoint ID of the thermostat.
 */
void ezb_zcl_thermostat_weekly_schedule_loop_start(uint8_t ep_id);

/**
 * @brief Stop the weekly schedule loop.
 *
 * @param ep_id Endpoint ID of the thermostat.
 */
void ezb_zcl_thermostat_weekly_schedule_loop_stop(uint8_t ep_id);

/**
 * @brief Get the weekly schedule entry for a given day of week.
 *
 * @param ep_id Endpoint ID of the thermostat.
 * @param day_of_week Day of week to get the entry for.
 * @return Pointer to the weekly schedule entry for @p day_of_week, NULL if not found.
 */
const ezb_zcl_thermostat_weekly_schedule_entry_t *ezb_zcl_thermostat_get_weekly_schedule_entry(uint8_t ep_id, uint8_t day_of_week);

#ifdef __cplusplus
} /* extern "C" */
#endif
