/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/color_control_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Direction for the MoveToHue command.
 * @anchor ezb_zcl_color_control_move_to_hue_direction_t
 */
typedef enum {
    EZB_ZCL_COLOR_CONTROL_MOVE_TO_HUE_SHORTEST_DISTANCE, /*!< Move to hue with shortest distance */
    EZB_ZCL_COLOR_CONTROL_MOVE_TO_HUE_LONGEST_DISTANCE,  /*!< Move to hue with longest distance */
    EZB_ZCL_COLOR_CONTROL_MOVE_TO_HUE_UP,                /*!< Move to hue up */
    EZB_ZCL_COLOR_CONTROL_MOVE_TO_HUE_DOWN,              /*!< Move to hue down */
} ezb_zcl_color_control_move_to_hue_direction_t;

/**
 * @brief Enumeration for the options attribute
 *
 * When set, color commands may be executed even if the OnOff cluster is off.
 */
typedef enum {
    EZB_ZCL_COLOR_CONTROL_OPTIONS_EXECUTE_IF_OFF = 0,
} ezb_zcl_color_control_options_t;

/**
 * @brief Moving mode for continuous color change (up/down or stop).
 * @anchor ezb_zcl_color_control_move_mode_t
 */
typedef enum {
    EZB_ZCL_COLOR_CONTROL_MOVE_MODE_STOP     = 0x00U, /*!< Stop the movement */
    EZB_ZCL_COLOR_CONTROL_MOVE_MODE_UP       = 0x01U, /*!< Move up */
    EZB_ZCL_COLOR_CONTROL_MOVE_MODE_RESERVED = 0x02U, /*!< Reserved */
    EZB_ZCL_COLOR_CONTROL_MOVE_MODE_DOWN     = 0x03U, /*!< Move down */
} ezb_zcl_color_control_move_mode_t;

/**
 * @brief Enumeration for the step mode color control cluster
 * @anchor ezb_zcl_color_control_step_mode_t
 *
 * Indicates whether to add (up) or subtract (down) the step from the current value.
 */
typedef enum {
    EZB_ZCL_COLOR_CONTROL_STEP_MODE_RESERVED0 = 0x00U, /*!< Reserved */
    EZB_ZCL_COLOR_CONTROL_STEP_MODE_UP        = 0x01U, /*!< Move up */
    EZB_ZCL_COLOR_CONTROL_STEP_MODE_RESERVED2 = 0x02U, /*!< Reserved */
    EZB_ZCL_COLOR_CONTROL_STEP_MODE_DOWN      = 0x03U, /*!< Move down */
} ezb_zcl_color_control_step_mode_t;

/**
 * @brief Update flags for the ColorLoopSet command.
 */
typedef enum {
    EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_SET_UPDATE_ACTION    = 1 << 0, /*!< Update action */
    EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_SET_UPDATE_DIRECTION = 1 << 1, /*!< Update direction */
    EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_SET_UPDATE_TIME      = 1 << 2, /*!< Update time */
    EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_SET_UPDATE_START_HUE = 1 << 3, /*!< Update start hue */
} ezb_zcl_color_control_color_loop_set_update_flags_t;

/**
 * @brief Enumeration for the action of ColorLoopSet
 *
 * Deactivate stops the loop; Activate options define the starting hue for the loop.
 */
typedef enum {
    EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_SET_ACTION_DEACTIVATE = 0x00, /*!< Deactivate */
    EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_SET_ACTION_ACTIVATE_FROM_START_ENHANCED_HUE =
        0x01, /*!< Activate from start enhanced hue */
    EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_SET_ACTION_ACTIVATE_FROM_ENHANCED_CURRENT_HUE =
        0x02, /*!< Activate from enhanced current hue */
} ezb_zcl_color_control_color_loop_set_action_t;

/**
 * @brief Direction for the ColorLoopSet command.
 */
typedef enum {
    EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_SET_DIRECTION_UP   = 0x00, /*!< Up */
    EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_SET_DIRECTION_DOWN = 0x01, /*!< Down */
} ezb_zcl_color_control_color_loop_set_direction_t;

/**
 * @brief Payload for the ZCL Color Control MoveToHue command.
 */
typedef struct {
    uint8_t  hue;             /*!< The Hue field specifies the hue to be moved to. */
    uint8_t  direction;       /*!< The Direction field, see @ref ezb_zcl_color_control_move_to_hue_direction_t */
    uint16_t transition_time; /*!< The Transition Time field specifies, in 1/10ths of a second, the time that SHALL be taken
                                 to move to the new hue.*/
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_move_to_hue_cmd_payload_t;

/**
 * @brief Structure for the MovetoHue command request of ZCL ColorControl cluster.
 */
typedef struct ezb_zcl_color_control_move_to_hue_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                      cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_move_to_hue_cmd_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_color_control_move_to_hue_cmd_t;

/**
 * @brief Payload for the ZCL Color Control EnhancedMoveToHue command.
 */
typedef struct {
    uint16_t enhanced_hue;     /*!< Target enhanced hue. */
    uint8_t  direction;        /*!< Direction. see @ref ezb_zcl_color_control_move_to_hue_direction_t */
    uint16_t transition_time;  /*!< Time to reach the new hue, in 1/10 s. */
    uint8_t  options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t  options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_enhanced_move_to_hue_cmd_payload_t;

/**
 * @brief Structure for the ZCL Color Control EnhancedMoveToHue command request.
 */
typedef struct ezb_zcl_color_control_enhanced_move_to_hue_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                               cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_enhanced_move_to_hue_cmd_payload_t payload;  /*!< The payload field */
} ezb_zcl_color_control_enhanced_move_to_hue_cmd_t;

/**
 * @brief Payload for the ZCL Color Control MoveToHueAndSaturation command.
 */
typedef struct {
    uint8_t  hue;             /*!< The Hue field specifies the hue to be moved to. */
    uint8_t  saturation;      /*!< The Saturation field specifies the saturation to be moved to. */
    uint16_t transition_time; /*!< The Transition Time field specifies, in 1/10ths of a second, the time that SHALL be taken
                                 to move to the new value.*/
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_move_to_hue_and_saturation_cmd_payload_t;

/**
 * @brief Structure for the MovetoHueSaturation command request of ZCL ColorControl cluster.
 */
typedef struct ezb_zcl_color_control_move_to_hue_and_saturation_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                                     cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_move_to_hue_and_saturation_cmd_payload_t payload;  /*!< The payload field */
} ezb_zcl_color_control_move_to_hue_and_saturation_cmd_t;

/**
 * @brief Payload for the ZCL Color Control EnhancedMoveToHueAndSaturation command.
 */
typedef struct {
    uint16_t enhanced_hue;     /*!< Target enhanced hue. */
    uint8_t  saturation;       /*!< Target saturation. */
    uint16_t transition_time;  /*!< Time to reach the new value, in 1/10 s. */
    uint8_t  options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t  options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_enhanced_move_to_hue_and_saturation_cmd_payload_t;

/**
 * @brief Structure for the EnhancedMovetoHueSaturation command request of ZCL ColorControl cluster.
 */
typedef struct ezb_zcl_color_control_enhanced_move_to_hue_and_saturation_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_enhanced_move_to_hue_and_saturation_cmd_payload_t payload; /*!< Payload of the command. */
} ezb_zcl_color_control_enhanced_move_to_hue_and_saturation_cmd_t;

/**
 * @brief Payload for the ZCL Color Control Move Hue/Saturation command.
 */
typedef struct {
    uint8_t move_mode;        /*!< Direction of movement: up, down, or stop. see @ref ezb_zcl_color_control_move_mode_t */
    uint8_t rate;             /*!< The Rate field specifies the rate of movement in steps per second. */
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_move_hs_cmd_payload_t;

/**
 * @brief Structure for the Move HueOrSaturation command request of ZCL ColorControl cluster.
 */
typedef struct {
    ezb_zcl_cluster_cmd_ctrl_t                  cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_move_hs_cmd_payload_t payload;  /*!< The payload field,
                                                               see @ref ezb_zcl_color_control_move_hs_cmd_payload_t */
} ezb_zcl_color_control_move_hs_cmd_t;

/**
 * @brief Payload for the ZCL Color Control MoveHue command.
 * @anchor ezb_zcl_color_control_move_hue_cmd_payload_t
 */
typedef ezb_zcl_color_control_move_hs_cmd_payload_t ezb_zcl_color_control_move_hue_cmd_payload_t;

/**
 * @brief Structure for ZCL Color Control MoveHue command request.
 * @anchor ezb_zcl_color_control_move_hue_cmd_t
 */
typedef ezb_zcl_color_control_move_hs_cmd_t ezb_zcl_color_control_move_hue_cmd_t;

/**
 * @brief Payload for the ZCL Color Control EnhancedMoveHue command.
 */
typedef struct {
    uint8_t  move_mode;        /*!< Move mode. see @ref ezb_zcl_color_control_move_mode_t */
    uint16_t rate;             /*!< Rate of movement in steps per second. */
    uint8_t  options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t  options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_enhanced_move_hue_cmd_payload_t;

/**
 * @brief Structure for ZCL Color Control EnhancedMoveHue command request.
 */
typedef struct {
    ezb_zcl_cluster_cmd_ctrl_t                            cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_enhanced_move_hue_cmd_payload_t payload;  /*!< The payload field */
} ezb_zcl_color_control_enhanced_move_hue_cmd_t;

/**
 * @brief Structure for the format of the Step HueOrSaturation Command Payload
 */
typedef struct {
    uint8_t  step_mode;       /*!< The Step Mode field, see @ref ezb_zcl_color_control_step_mode_t */
    uint8_t  step_size;       /*!< The change to be added to (or subtracted from) the current value of the device’s value. */
    uint16_t transition_time; /*!< The Transition Time field specifies, in 1/10ths of a second, the time that SHALL be taken to
                                   perform the step.*/
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_step_hs_cmd_payload_t;

/**
 * @brief Structure for the ZCL Color Control Step Hue/Saturation command request.
 */
typedef struct ezb_zcl_color_control_step_hs_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_step_hs_cmd_payload_t
        payload; /*!< The payload field, see @ref ezb_zcl_color_control_step_hs_cmd_payload_t */
} ezb_zcl_color_control_step_hs_cmd_t;

/**
 * @brief Structure for the format of the StepHue Command Payload
 */
typedef ezb_zcl_color_control_step_hs_cmd_payload_t ezb_zcl_color_control_step_hue_cmd_payload_t;

/**
 * @brief Structure for the ZCL Color Control StepHue command request.
 * @anchor ezb_zcl_color_control_step_hue_cmd_t
 */
typedef ezb_zcl_color_control_step_hs_cmd_t ezb_zcl_color_control_step_hue_cmd_t;

/**
 * @brief Structure for the format of the StepSaturation Command Payload
 * @anchor ezb_zcl_color_control_step_saturation_cmd_payload_t
 */
typedef ezb_zcl_color_control_step_hs_cmd_payload_t ezb_zcl_color_control_step_saturation_cmd_payload_t;

/**
 * @brief Structure for the ZCL Color Control StepSaturation command request.
 * @anchor ezb_zcl_color_control_step_saturation_cmd_t
 */
typedef ezb_zcl_color_control_step_hs_cmd_t ezb_zcl_color_control_step_saturation_cmd_t;

/**
 * @brief Payload for the ZCL Color Control EnhancedStepHue command.
 */
typedef struct {
    uint8_t  step_mode; /*!< The Step Mode field, see @ref ezb_zcl_color_control_step_mode_t */
    uint16_t step_size; /*!< The change to be added to (or subtracted from) the current value of the device’s enhanced hue. */
    uint16_t transition_time; /*!< The Transition Time field specifies, in 1/10ths of a second, the time that SHALL be taken to
                                   perform the step.*/
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_enhanced_step_hue_cmd_payload_t;

/**
 * @brief Structure for ZCL Color Control EnhancedStepHue command request.
 */
typedef struct ezb_zcl_color_control_enhanced_step_hue_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                            cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_enhanced_step_hue_cmd_payload_t payload;  /*!< The payload field */
} ezb_zcl_color_control_enhanced_step_hue_cmd_t;

/**
 * @brief Payload for the ZCL Color Control MoveToSaturation command.
 */
typedef struct {
    uint8_t  saturation;      /*!< The saturation field specifies the saturation to be moved to. */
    uint16_t transition_time; /*!< The Transition Time field specifies, in 1/10ths of a second, the time that SHALL be taken
                                 to move to the new hue.*/
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_move_to_saturation_cmd_payload_t;

/**
 * @brief Structure for ZCL Color Control MoveToSaturation command request.
 */
typedef struct ezb_zcl_color_control_move_to_saturation_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                             cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_move_to_saturation_cmd_payload_t payload;  /*!< The payload field */
} ezb_zcl_color_control_move_to_saturation_cmd_t;

/**
 * @brief Payload for the ZCL Color Control MoveSaturation command.
 * @anchor ezb_zcl_color_control_move_saturation_cmd_payload_t
 */
typedef ezb_zcl_color_control_move_hs_cmd_payload_t ezb_zcl_color_control_move_saturation_cmd_payload_t;

/**
 * @brief Structure for ZCL Color Control MoveSaturation command request.
 * @anchor ezb_zcl_color_control_move_saturation_cmd_t
 */
typedef ezb_zcl_color_control_move_hs_cmd_t ezb_zcl_color_control_move_saturation_cmd_t;

/**
 * @brief Payload for the ZCL Color Control MoveToColor command.
 */
typedef struct {
    uint16_t color_x;         /*!< The color x field specifies the color x to be moved to. */
    uint16_t color_y;         /*!< The color y field specifies the color y to be moved to. */
    uint16_t transition_time; /*!< The Transition Time field specifies, in 1/10ths of a second, the time that SHALL be taken
                                 to move to the color space.*/
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_move_to_color_cmd_payload_t;

/**
 * @brief Structure for the MoveColor command request of ZCL ColorControl cluster.
 */
typedef struct ezb_zcl_color_control_move_to_color_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                        cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_move_to_color_cmd_payload_t payload;  /*!< The payload field */
} ezb_zcl_color_control_move_to_color_cmd_t;

/**
 * @brief Payload for the ZCL Color Control MoveColor command.
 */
typedef struct {
    uint16_t rate_x;          /*!< The RateX field specifies the rate of movement in steps per second. */
    uint16_t rate_y;          /*!< The RateY field specifies the rate of movement in steps per second. */
    uint8_t  options_mask;    /*!< The Options Mask field specifies which bits of the EZB_ZCL_ATTR_COLOR_CONTROL_OPTIONS_ID
                                 attribute on the server should be checked. */
    uint8_t options_override; /*!< The Options Override field specifies which bits indicated by @p options_mask should be
                                 overwritten in the EZB_ZCL_ATTR_COLOR_CONTROL_OPTIONS_ID attribute of the server. */
} ezb_zcl_color_control_move_color_cmd_payload_t;

/**
 * @brief Structure for the MoveColor command request of ZCL ColorControl cluster.
 */
typedef struct ezb_zcl_color_control_move_color_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                     cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_move_color_cmd_payload_t payload;  /*!< The payload field */
} ezb_zcl_color_control_move_color_cmd_t;

/**
 * @brief Payload for the ZCL Color Control StepColor command.
 */
typedef struct {
    uint8_t  step_x;          /*!< The StepX fields specify the change to be added to the device's CurrentX attribute. */
    uint8_t  step_y;          /*!< The StepY fields specify the change to be added to the device's CurrentYu attribute. */
    uint16_t transition_time; /*!< The Transition Time field specifies, in 1/10ths of a second, the time that SHALL be taken to
                                   perform the step.*/
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_step_color_cmd_payload_t;

/**
 * @brief Structure for the StepColor command request of ZCL ColorControl cluster.
 */
typedef struct ezb_zcl_color_control_step_color_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                     cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_step_color_cmd_payload_t payload;  /*!< The payload field */
} ezb_zcl_color_control_step_color_cmd_t;

/**
 * @brief Payload for the ZCL Color Control MoveToColorTemperature command.
 */
typedef struct {
    uint16_t color_temperature_mireds; /*!< The color temperature field specifies the color x to be moved to. */
    uint16_t transition_time; /*!< The Transition Time field specifies, in 1/10ths of a second, the time that SHALL be taken
                                 to move to the color space.*/
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_move_to_color_temperature_cmd_payload_t;

/**
 * @brief Structure for the MovetoColorTemperature command request of ZCL ColorControl cluster.
 */
typedef struct ezb_zcl_color_control_move_to_color_temperature_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                                    cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_move_to_color_temperature_cmd_payload_t payload;  /*!< The payload field */
} ezb_zcl_color_control_move_to_color_temperature_cmd_t;

/**
 * @brief Payload for the ZCL Color Control MoveColorTemperature command.
 */
typedef struct {
    uint8_t  move_mode; /*!< Up (increase mireds) or down (decrease). see @ref ezb_zcl_color_control_move_mode_t */
    uint16_t rate;      /*!< Rate of movement in steps per second. */
    uint16_t color_temperature_min_mireds; /*!< The Color Temperature Minimum Mireds field is 16-bits in length and specifies a
                                              lower bound on the ColorTemperatureMireds attribute. */
    uint16_t color_temperature_max_mireds; /*!< The Color Temperature Maximum Mireds field is 16-bits in length and specifies an
                                              upper bound on the ColorTemperatureMireds attribute. */
    uint8_t options_mask;                  /*!< Bits of Options attribute to check. */
    uint8_t options_override;              /*!< Values to override for those bits. */
} ezb_zcl_color_control_move_color_temperature_cmd_payload_t;

/**
 * @brief Structure for the MoveColorTemperature command request of ZCL ColorControl cluster.
 */
typedef struct ezb_zcl_color_control_move_color_temperature_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                                 cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_move_color_temperature_cmd_payload_t payload;  /*!< The payload field */
} ezb_zcl_color_control_move_color_temperature_cmd_t;

/**
 * @brief Payload for the ZCL Color Control StepColorTemperature command.
 */
typedef struct {
    uint8_t  step_mode;                    /*!< Up or down. see @ref ezb_zcl_color_control_step_mode_t */
    uint16_t step_size;                    /*!< Change in ColorTemperatureMireds to add or subtract. */
    uint16_t color_temperature_min_mireds; /*!< The Color Temperature Minimum Mireds field is 16-bits in length and specifies a
                                          lower bound on the ColorTemperatureMireds attribute. */
    uint16_t color_temperature_max_mireds; /*!< The Color Temperature Maximum Mireds field is 16-bits in length and specifies an
                                              upper bound on the ColorTemperatureMireds attribute. */
    uint16_t transition_time; /*!< The Transition Time field specifies, in 1/10ths of a second, the time that SHALL be taken to
                                   perform the step.*/
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_step_color_temperature_cmd_payload_t;

/**
 * @brief Structure for the StepColorTemperature command request of ZCL ColorControl cluster.
 */
typedef struct ezb_zcl_color_control_step_color_temperature_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                                 cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_step_color_temperature_cmd_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_color_control_step_color_temperature_cmd_t;

/**
 * @brief Payload for the ZCL Color Control StopMoveStep command.
 */
typedef struct {
    uint8_t options_mask;     /*!< Bits of Options attribute to check. */
    uint8_t options_override; /*!< Values to override for those bits. */
} ezb_zcl_color_control_stop_move_step_cmd_payload_t;

/**
 * @brief Structure for the ZCL Color Control StopMoveStep command request.
 */
typedef struct ezb_zcl_color_control_stop_move_step_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                         cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_stop_move_step_cmd_payload_t payload;  /*!< The payload field */
} ezb_zcl_color_control_stop_move_step_cmd_t;

/**
 * @brief Structure for the format of the ColorLoopSet Command Payload
 */
typedef struct {
    uint8_t update_flags; /*!< The Update Flags field specifies which color loop attributes to update before the color loop is
                             started.*/
    uint8_t action; /*!< The Action field specifies the action to take for the color loop if the Update Action sub-field of the
                       Update Flags field is set to 1. */
    uint8_t direction; /*!< The Direction field specifies the direction for the color loop if the Update Direction field of the
                          Update Flags field is set to 1. */
    uint16_t time;     /*!< The Time field specifies the number of seconds over which to perform a full color loop if the Update
                          Time field of the Update Flags field is set to 1. */
    uint16_t start_hue;   /*!< The Start Hue field is 16 bits in length and specifies the starting hue to use for the color loop
                             if the Update Start Hue field of the Update Flags field is set to 1. */
    uint8_t options_mask; /*!< The Options Mask field specifies which bits of the EZB_ZCL_ATTR_COLOR_CONTROL_OPTIONS_ID
                             attribute on the server should be checked. */
    uint8_t options_override; /*!< The Options Override field specifies which bits indicated by @p options_mask should be
                                 overwritten in the EZB_ZCL_ATTR_COLOR_CONTROL_OPTIONS_ID attribute of the server. */
} ezb_zcl_color_control_color_loop_set_cmd_payload_t;

/**
 * @brief Structure for the ZCL Color Control ColorLoopSet command request.
 */
typedef struct ezb_zcl_color_control_color_loop_set_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                         cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_color_control_color_loop_set_cmd_payload_t payload;  /*!< The payload field */
} ezb_zcl_color_control_color_loop_set_cmd_t;

/**
 * @brief Color value used in Color Control cluster callbacks (e.g. mode change).
 *
 * The active member depends on @p mode: Hue/Saturation, xy (CurrentX/CurrentY), or color temperature.
 */
typedef struct {
    uint8_t mode; /*!< Current color mode; determines which union member is valid. */
    union {
        struct {
            union {
                uint16_t enhanced_hue; /*!< Enhanced hue */
                uint8_t  hue;          /*!< Hue */
            };                         /*!< Enhanced hue or hue */
            uint8_t saturation;        /*!< Saturation */
        };                             /*!< Enhanced hue and saturation */
        struct {
            uint16_t x; /*!< Color X */
            uint16_t y; /*!< Color Y */
        };              /*!< Color X and Y */
        struct {
            uint16_t color_temperature; /*!< Color temperature */
        };                              /*!< Color temperature */
    };                                  /*!< Color field */
} ezb_zcl_color_control_color_t;

/**
 * @brief Application message when Color Control server color mode changes.
 *
 * Application may set @p out.result and @p out.color to influence the final color.
 */
typedef struct ezb_zcl_color_control_color_mode_change_message_s {
    ezb_zcl_message_info_t info; /*!< Common information for Zigbee device callback. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        uint8_t old_mode; /*!< The original color mode */
        uint8_t new_mode; /*!< The new color mode */
    } in;                 /*!< Input: old mode and new mode */
    struct {
        ezb_zcl_status_t              result; /*!< Status of processing in application. */
        ezb_zcl_color_control_color_t color;  /*!< If the @p result is EZB_ZCL_STATUS_SUCCESS, the color will be used to set the
                                                 related color attribute. */
    } out;                                    /*!< Output: result to send back. */
} ezb_zcl_color_control_color_mode_change_message_t;

/**
 * @brief Send ZCL Color Control MoveToHue command request.
 *
 * @param cmd_req Pointer to the MoveToHue command request structure, @ref ezb_zcl_color_control_move_to_hue_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_move_to_hue_cmd_req(const ezb_zcl_color_control_move_to_hue_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control EnhancedMoveToHue command request.
 *
 * @param cmd_req Pointer to the EnhancedMoveToHue command request structure, @ref
 * ezb_zcl_color_control_enhanced_move_to_hue_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_enhanced_move_to_hue_cmd_req(const ezb_zcl_color_control_enhanced_move_to_hue_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control MoveHue command request.
 *
 * @param cmd_req Pointer to the MoveHue command request structure, @ref ezb_zcl_color_control_move_hue_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_move_hue_cmd_req(const ezb_zcl_color_control_move_hue_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control EnhancedMoveHue command request.
 *
 * @param cmd_req Pointer to the EnhancedMoveHue command request structure, @ref ezb_zcl_color_control_enhanced_move_hue_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_enhanced_move_hue_cmd_req(const ezb_zcl_color_control_enhanced_move_hue_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control StepHue command request.
 *
 * @param cmd_req Pointer to the StepHue command request structure, @ref ezb_zcl_color_control_step_hue_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_step_hue_cmd_req(const ezb_zcl_color_control_step_hue_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control EnhancedStepHue command request.
 *
 * @param cmd_req Pointer to the EnhancedStepHue command request structure, @ref ezb_zcl_color_control_enhanced_step_hue_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_enhanced_step_hue_cmd_req(const ezb_zcl_color_control_enhanced_step_hue_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control MoveToSaturation command request.
 *
 * @param cmd_req Pointer to the MoveToSaturation command request structure, @ref
 * ezb_zcl_color_control_move_to_saturation_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_move_to_saturation_cmd_req(const ezb_zcl_color_control_move_to_saturation_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control MoveSaturation command request.
 *
 * @param cmd_req Pointer to the MoveSaturation command request structure, @ref ezb_zcl_color_control_move_saturation_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_move_saturation_cmd_req(const ezb_zcl_color_control_move_saturation_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control StepSaturation command request.
 *
 * @param cmd_req Pointer to the StepSaturation command request structure, @ref ezb_zcl_color_control_step_saturation_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_step_saturation_cmd_req(const ezb_zcl_color_control_step_saturation_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control MoveToHueAndSaturation command request.
 *
 * @param cmd_req Pointer to the MoveToHueAndSaturation command request structure, @ref
 * ezb_zcl_color_control_move_to_hue_and_saturation_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_move_to_hue_and_saturation_cmd_req(
    const ezb_zcl_color_control_move_to_hue_and_saturation_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control EnhancedMoveToHueAndSaturation command request.
 *
 * @param cmd_req Pointer to the EnhancedMoveToHueAndSaturation command request structure, @ref
 * ezb_zcl_color_control_enhanced_move_to_hue_and_saturation_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_enhanced_move_to_hue_and_saturation_cmd_req(
        const ezb_zcl_color_control_enhanced_move_to_hue_and_saturation_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control MoveToColor command request.
 *
 * @param cmd_req Pointer to the MoveToColor command request structure, @ref ezb_zcl_color_control_move_to_color_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_move_to_color_cmd_req(const ezb_zcl_color_control_move_to_color_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control MoveColor command request.
 *
 * @param cmd_req Pointer to the MoveColor command request structure, @ref ezb_zcl_color_control_move_color_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_move_color_cmd_req(const ezb_zcl_color_control_move_color_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control StepColor command request.
 *
 * @param cmd_req Pointer to the StepColor command request structure, @ref ezb_zcl_color_control_step_color_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_step_color_cmd_req(const ezb_zcl_color_control_step_color_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control MoveToColorTemperature command request.
 *
 * @param cmd_req Pointer to the MoveToColorTemperature command request structure, @ref
 * ezb_zcl_color_control_move_to_color_temperature_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_move_to_color_temperature_cmd_req(
    const ezb_zcl_color_control_move_to_color_temperature_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control MoveColorTemperature command request.
 *
 * @param cmd_req Pointer to the MoveColorTemperature command request structure, @ref
 * ezb_zcl_color_control_move_color_temperature_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_move_color_temperature_cmd_req(
    const ezb_zcl_color_control_move_color_temperature_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control StepColorTemperature command request.
 *
 * @param cmd_req Pointer to the StepColorTemperature command request structure, @ref
 * ezb_zcl_color_control_step_color_temperature_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_step_color_temperature_cmd_req(
    const ezb_zcl_color_control_step_color_temperature_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control StopMoveStep command request.
 *
 * @param cmd_req Pointer to the StopMoveStep command request structure, @ref ezb_zcl_color_control_stop_move_step_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_stop_move_step_cmd_req(const ezb_zcl_color_control_stop_move_step_cmd_t *cmd_req);

/**
 * @brief Send ZCL Color Control ColorLoopSet command request.
 *
 * @param cmd_req Pointer to the ColorLoopSet command request structure, @ref ezb_zcl_color_control_color_loop_set_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_color_loop_set_cmd_req(const ezb_zcl_color_control_color_loop_set_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
