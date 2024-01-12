/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include "esp_zigbee_zcl_command.h"

/* ZCL color control cluster list command */

uint8_t esp_zb_zcl_color_move_to_hue_cmd_req(esp_zb_zcl_color_move_to_hue_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t hue;                                        /*!< current value of hue */
        uint8_t direction;                                  /*!< direction */
        uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
    } __attribute__ ((packed)) esp_zb_zcl_move_to_hue_t;

    esp_zb_zcl_move_to_hue_t value = {
        .hue = cmd_req->hue,
        .direction = cmd_req->direction,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_MOVE_TO_HUE,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U32,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_move_hue_cmd_req(esp_zb_zcl_color_move_hue_cmd_t *cmd_req)
{
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_MOVE_HUE,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U16,
        .data.value = &cmd_req->move_mode,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_step_hue_cmd_req(esp_zb_zcl_color_step_hue_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t step_mode;                                  /*!< step mode */
        uint8_t step_size;                                  /*!< step size */
        uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
    } __attribute__ ((packed)) esp_zb_zcl_step_hue_t;

    esp_zb_zcl_step_hue_t value = {
        .step_mode = cmd_req->step_mode,
        .step_size = cmd_req->step_size,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_STEP_HUE,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U32,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_move_to_saturation_cmd_req(esp_zb_zcl_color_move_to_saturation_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t saturation;                                 /*!< current value of saturation */
        uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
    } __attribute__ ((packed)) esp_zb_zcl_move_to_saturation_t;

    esp_zb_zcl_move_to_saturation_t value = {
        .saturation = cmd_req->saturation,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_MOVE_TO_SATURATION,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U32,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_move_saturation_cmd_req(esp_zb_zcl_color_move_saturation_cmd_t *cmd_req)
{
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_MOVE_SATURATION,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U16,
        .data.value = &cmd_req->move_mode,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_step_saturation_cmd_req(esp_zb_zcl_color_step_saturation_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t step_mode;                                  /*!< step mode */
        uint8_t step_size;                                  /*!< step size */
        uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
    } __attribute__ ((packed)) esp_zb_zcl_step_saturation_t;

    esp_zb_zcl_step_saturation_t value = {
        .step_mode = cmd_req->step_mode,
        .step_size = cmd_req->step_size,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_STEP_SATURATION,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U32,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_move_to_hue_and_saturation_cmd_req(esp_zb_color_move_to_hue_saturation_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t hue;                                        /*!< current value of hue */
        uint8_t saturation;                                 /*!< current value of saturation */
        uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
    } __attribute__ ((packed)) esp_zb_zcl_move_to_hue_and_saturation_t;

    esp_zb_zcl_move_to_hue_and_saturation_t value = {
        .hue = cmd_req->hue,
        .saturation = cmd_req->saturation,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_MOVE_TO_HUE_SATURATION,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U32,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_move_to_color_cmd_req(esp_zb_zcl_color_move_to_color_cmd_t *cmd_req)
{
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_MOVE_TO_COLOR,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U48,
        .data.value = &cmd_req->color_x,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_move_color_cmd_req(esp_zb_zcl_color_move_color_cmd_t *cmd_req)
{
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_MOVE_COLOR,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U32,
        .data.value = &cmd_req->rate_x,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_step_color_cmd_req(esp_zb_zcl_color_step_color_cmd_t *cmd_req)
{
    typedef struct {
        int16_t step_x;                                     /*!< specifies the change to be added to color x */
        int16_t step_y;                                     /*!< specifies the change to be added to color x */
        uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
    } __attribute__ ((packed)) esp_zb_zcl_step_color_t;

    esp_zb_zcl_step_color_t value = {
        .step_x = cmd_req->step_x,
        .step_y = cmd_req->step_y,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_STEP_COLOR,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U48,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_stop_move_step_cmd_req(esp_zb_zcl_color_stop_move_step_cmd_t *cmd_req)
{
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_STOP_MOVE_STEP,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_NULL,
        .data.value = NULL,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_move_to_color_temperature_cmd_req(esp_zb_zcl_color_move_to_color_temperature_cmd_t *cmd_req)
{
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_MOVE_TO_COLOR_TEMPERATURE,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U32,
        .data.value = &cmd_req->color_temperature,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_enhanced_move_to_hue_cmd_req(esp_zb_zcl_color_enhanced_move_to_hue_cmd_t *cmd_req)
{
    typedef struct {
        uint16_t enhanced_hue;                  /*!< The field specifies the target enhanced hue for the lamp */
        uint8_t direction;                      /*!< The direction */
        uint16_t transition_time;               /*!< The time wants to transition tenths of a second */
    } __attribute__ ((packed)) esp_zb_zcl_enhanced_move_to_hue_t;

    esp_zb_zcl_enhanced_move_to_hue_t value = {
        .enhanced_hue = cmd_req->enhanced_hue,
        .direction = cmd_req->direction,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_ENHANCED_MOVE_TO_HUE,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U40,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_enhanced_move_hue_cmd_req(esp_zb_zcl_color_enhanced_move_hue_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t move_mode;                      /*!< The Move Mode, If the Move Mode field is equal to 0x00 (Stop), the Rate field SHALL be ignored */
        uint16_t rate;                          /*!< The field specifies the rate of movement in steps per second */
    } __attribute__ ((packed)) esp_zb_zcl_enhanced_move_hue_t;

    esp_zb_zcl_enhanced_move_hue_t value = {
        .move_mode = cmd_req->move_mode,
        .rate = cmd_req->rate,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_ENHANCED_MOVE_HUE,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U24,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_enhanced_step_hue_cmd_req(esp_zb_zcl_color_enhanced_step_hue_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t step_mode;                      /*!< The Step Mode */
        uint16_t step_size;                     /*!< The Step Size specifies the change to be added to the current value of the device’s enhanced hue.*/
        uint16_t transition_time;               /*!< The time wants to transition tenths of a second  */
    } __attribute__ ((packed)) esp_zb_zcl_enhanced_step_hue_t;

    esp_zb_zcl_enhanced_step_hue_t value = {
        .step_mode = cmd_req->step_mode,
        .step_size = cmd_req->step_size,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_ENHANCED_STEP_HUE,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U56,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_enhanced_move_to_hue_saturation_cmd_req(esp_zb_zcl_color_enhanced_move_to_hue_saturation_cmd_t *cmd_req)
{
    typedef struct {
        uint16_t enhanced_hue;                  /*!< The Enhanced Hue specifies the target extended hue for the lamp */
        uint8_t saturation;                     /*!< The value of Saturation */
        uint16_t transition_time;               /*!< The time wants to transition tenths of a second */
    } __attribute__ ((packed)) esp_zb_zcl_move_to_hue_saturation_t;

    esp_zb_zcl_move_to_hue_saturation_t value = {
        .enhanced_hue = cmd_req->enhanced_hue,
        .saturation = cmd_req->saturation,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_ENHANCED_MOVE_TO_HUE_SATURATION,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U56,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_color_loop_set_cmd_req(esp_zb_zcl_color_color_loop_set_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t update_flags;                   /*!< The Update Flags field specifies which color loop attributes to update before the color loop is started */
        uint8_t action;                         /*!< The Action field specifies the action to take for the color loop,
                                                    if the Update Action sub-field of the Update Flags field is set to 1. */
        uint8_t direction;                      /*!< The Direction field of the color loop set command */
        uint16_t time;                          /*!< The Time field specifies the number of seconds over which to perform a full color loop,
                                                    if the Update Time field of the Update Flags field is set to 1. */
        uint16_t start_hue;                     /*!< The field specifies the starting hue to use for the color loop if the Update Start Hue field of the Update Flags field is set to 1 */
    } __attribute__ ((packed)) esp_zb_zcl_color_loop_set_t;

    esp_zb_zcl_color_loop_set_t value = {
        .update_flags = cmd_req->update_flags,
        .action = cmd_req->action,
        .direction = cmd_req->direction,
        .time = cmd_req->time,
        .start_hue = cmd_req->start_hue,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_COLOR_LOOP_SET,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U56,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_move_color_temperature_cmd_req(esp_zb_zcl_color_move_color_temperature_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t move_mode;                      /*!< The Move Mode field of the Move Hue command, if the Move Mode field is equal to 0x00, the Rate field SHALL be ignored. */
        uint16_t rate;                          /*!< The Rate field specifies the rate of movement in steps per second */
        uint16_t color_temperature_minimum;     /*!< The field specifies a lower bound on the Color-Temperature attribute */
        uint16_t color_temperature_maximum;     /*!< The field specifies a upper bound on the Color-Temperature attribute */
    } __attribute__ ((packed)) esp_zb_zcl_move_color_temperature_t;

    esp_zb_zcl_move_color_temperature_t value = {
        .move_mode = cmd_req->move_mode,
        .rate = cmd_req->rate,
        .color_temperature_minimum = cmd_req->color_temperature_minimum,
        .color_temperature_maximum = cmd_req->color_temperature_maximum,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_MOVE_COLOR_TEMPERATURE,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U56,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_color_step_color_temperature_cmd_req(esp_zb_zcl_color_step_color_temperature_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t move_mode;                      /*!< The Move Mode field of the Step Hue command, If the Move Mode field is equal to 0x00, the Rate field SHALL be ignored. */
        uint16_t step_size;                     /*!< The Step Size field specifies the change to be added to (or subtracted from) the current
                                                    value of the device’s color temperature.*/
        uint16_t transition_time;               /*!< The time wants to transition tenths of a second  */
        uint16_t color_temperature_minimum;     /*!< The field specifies a lower bound on the Color-Temperature attribute*/
        uint16_t color_temperature_maximum;     /*!< The field specifies a upper bound on the Color-Temperature attribute*/
    } __attribute__ ((packed)) esp_zb_zcl_step_color_temperature_t;

    esp_zb_zcl_step_color_temperature_t value = {
        .move_mode = cmd_req->move_mode,
        .step_size = cmd_req->step_size,
        .transition_time = cmd_req->transition_time,
        .color_temperature_minimum = cmd_req->color_temperature_minimum,
        .color_temperature_maximum = cmd_req->color_temperature_maximum,
    };

    uint8_t data_value[11] = {0x09, 0x00};
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_COLOR_CONTROL_STEP_COLOR_TEMPERATURE,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_ARRAY,
        .data.value = data_value,
    };
    memcpy(&data_value[2], &value, sizeof(esp_zb_zcl_step_color_temperature_t));

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}