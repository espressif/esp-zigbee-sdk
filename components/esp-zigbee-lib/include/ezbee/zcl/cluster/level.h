/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/level_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Bitmap for the Level cluster Options attribute.
 *
 * When ExecuteIfOff is set, level commands may run even if the OnOff cluster is off.
 */
typedef enum {
    EZB_ZCL_LEVEL_OPTIONS_EXECUTE_IF_OFF = 0, /*!< ExecuteIfOff bit */
    EZB_ZCL_LEVEL_OPTIONS_RESERVED       = 1, /*!< Reserved bit */
} ezb_zcl_level_options_t;

/**
 * @brief Direction for Move commands (continuous level change).
 * @anchor ezb_zcl_level_move_mode_t
 */
typedef enum {
    EZB_ZCL_LEVEL_FADE_MODE_UP   = 0x00, /*!< Up mode */
    EZB_ZCL_LEVEL_FADE_MODE_DOWN = 0x01, /*!< Down mode */
} ezb_zcl_level_move_mode_t;

/**
 * @brief Payload for the ZCL Level MoveToLevel command.
 */
typedef struct ezb_zcl_level_move_to_level_cmd_payload_s {
    uint8_t  level;            /*!< Target level (0-254). */
    uint16_t transition_time;  /*!< Time to reach level, in 1/10 s. 0xFFFF = use OnOff transition time. */
    uint8_t  options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t  options_override; /*!< Values to override for those bits. */
} ezb_zcl_level_move_to_level_cmd_payload_t;

/**
 * @brief Structure for the ZCL Level MoveToLevel command request.
 */
typedef struct ezb_zcl_level_move_to_level_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_level_move_to_level_cmd_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_level_move_to_level_cmd_t;

/**
 * @brief Structure for the ZCL Level MoveToLevelWithOnOff command request.
 * @anchor ezb_zcl_level_move_to_level_with_on_off_cmd_t
 */
typedef ezb_zcl_level_move_to_level_cmd_t ezb_zcl_level_move_to_level_with_on_off_cmd_t;

/**
 * @brief Payload for the ZCL Level Move command.
 */
typedef struct ezb_zcl_level_move_cmd_payload_s {
    uint8_t move_mode;        /*!< Up (0) or down (1). @ref ezb_zcl_level_move_mode_t */
    uint8_t rate;             /*!< Rate of change in units per second; 0xFF = use default. */
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_level_move_cmd_payload_t;

/**
 * @brief Structure for the ZCL Level Move command request.
 */
typedef struct ezb_zcl_level_move_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t       cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_level_move_cmd_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_level_move_cmd_t;

/**
 * @brief Structure for the ZCL Level MoveWithOnOff command request.
 * @anchor ezb_zcl_level_move_with_on_off_cmd_t
 */
typedef ezb_zcl_level_move_cmd_t ezb_zcl_level_move_with_on_off_cmd_t;

/**
 * @brief Payload for the ZCL Level Step command.
 */
typedef struct ezb_zcl_level_step_cmd_payload_s {
    uint8_t  step_mode;        /*!< Up (0) or down (1). */
    uint8_t  step_size;        /*!< Change in level (1-254). */
    uint16_t transition_time;  /*!< Time for the step, in 1/10 s. */
    uint8_t  options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t  options_override; /*!< Values to override for those bits. */
} ezb_zcl_level_step_cmd_payload_t;

/**
 * @brief Structure for the ZCL Level Step command request.
 */
typedef struct ezb_zcl_level_step_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t       cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_level_step_cmd_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_level_step_cmd_t;

/**
 * @brief Structure for the ZCL Level StepWithOnOff command request.
 * @anchor ezb_zcl_level_step_with_on_off_cmd_t
 */
typedef ezb_zcl_level_step_cmd_t ezb_zcl_level_step_with_on_off_cmd_t;

/**
 * @brief Payload for the ZCL Level Stop command.
 */
typedef struct ezb_zcl_level_stop_cmd_payload_s {
    uint8_t move_mode;        /*!< Up (0) or down (1). */
    uint8_t rate;             /*!< Rate of change in units per second. */
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_level_stop_cmd_payload_t;

/**
 * @brief Structure for the ZCL Level Stop command request.
 */
typedef struct ezb_zcl_level_stop_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t       cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_level_stop_cmd_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_level_stop_cmd_t;

/**
 * @brief Structure for the ZCL Level StopWithOnOff command request.
 * @anchor ezb_zcl_level_stop_with_on_off_cmd_t
 */
typedef ezb_zcl_level_stop_cmd_t ezb_zcl_level_stop_with_on_off_cmd_t;

/**
 * @brief Payload for the ZCL Level MoveToClosestFrequency command.
 */
typedef struct ezb_zcl_level_move_to_closest_frequency_cmd_payload_s {
    uint16_t frequency; /*!< Target frequency in Hz. */
} ezb_zcl_level_move_to_closest_frequency_cmd_payload_t;

/**
 * @brief Structure for the ZCL Level MoveToClosestFrequency command request.
 */
typedef struct ezb_zcl_level_move_to_closest_frequency_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                            cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_level_move_to_closest_frequency_cmd_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_level_move_to_closest_frequency_cmd_t;

/**
 * @brief Send ZCL Level MoveToLevel command request.
 *
 * @param cmd_req Pointer to the MoveToLevel command request structure, @ref ezb_zcl_level_move_to_level_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_level_move_to_level_cmd_req(const ezb_zcl_level_move_to_level_cmd_t *cmd_req);

/**
 * @brief Send ZCL Level MoveToLevelWithOnOff command request.
 *
 * @param cmd_req Pointer to the MoveToLevelWithOnOff command request structure, @ref
 * ezb_zcl_level_move_to_level_with_on_off_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_level_move_to_level_with_on_off_cmd_req(const ezb_zcl_level_move_to_level_cmd_t *cmd_req);

/**
 * @brief Send ZCL Level Move command request.
 *
 * @param cmd_req Pointer to the Move command request structure, @ref ezb_zcl_level_move_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_level_move_cmd_req(const ezb_zcl_level_move_cmd_t *cmd_req);

/**
 * @brief Send ZCL Level MoveWithOnOff command request.
 *
 * @param cmd_req Pointer to the MoveWithOnOff command request structure, @ref ezb_zcl_level_move_with_on_off_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_level_move_with_on_off_cmd_req(const ezb_zcl_level_move_cmd_t *cmd_req);

/**
 * @brief Send ZCL Level Step command request.
 *
 * @param cmd_req Pointer to the Step command request structure, @ref ezb_zcl_level_step_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_level_step_cmd_req(const ezb_zcl_level_step_cmd_t *cmd_req);

/**
 * @brief Send ZCL Level StepWithOnOff command request.
 *
 * @param cmd_req Pointer to the StepWithOnOff command request structure, @ref ezb_zcl_level_step_with_on_off_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_level_step_with_on_off_cmd_req(const ezb_zcl_level_step_cmd_t *cmd_req);

/**
 * @brief Send ZCL Level Stop command request.
 *
 * @param cmd_req Pointer to the Stop command request structure, @ref ezb_zcl_level_stop_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_level_stop_cmd_req(const ezb_zcl_level_stop_cmd_t *cmd_req);

/**
 * @brief Send ZCL Level StopWithOnOff command request.
 *
 * @param cmd_req Pointer to the StopWithOnOff command request structure, @ref ezb_zcl_level_stop_with_on_off_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_level_stop_with_on_off_cmd_req(const ezb_zcl_level_stop_cmd_t *cmd_req);

/**
 * @brief Send ZCL Level MoveToClosestFrequency command request.
 *
 * @param cmd_req Pointer to the MoveToClosestFrequency command request structure, @ref
 * ezb_zcl_level_move_to_closest_frequency_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_level_move_to_closest_frequency_cmd_req(const ezb_zcl_level_move_to_closest_frequency_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
