/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_zigbee_zcl_command.h"

/* ZCL level control cluster list command */

uint8_t esp_zb_zcl_level_move_to_level_cmd_req(esp_zb_zcl_move_to_level_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t level;                                      /*!< level wants to move to */
        uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
    } __attribute__ ((packed)) esp_zb_zcl_move_to_level_t;
                
    esp_zb_zcl_move_to_level_t value = {
        .level = cmd_req->level,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_LEVEL_CONTROL_MOVE_TO_LEVEL,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U24,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_level_move_to_level_with_onoff_cmd_req(esp_zb_zcl_move_to_level_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t level;                                      /*!< level wants to move to */
        uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
    } __attribute__ ((packed)) esp_zb_zcl_move_to_level_t;
                
    esp_zb_zcl_move_to_level_t value = {
        .level = cmd_req->level,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_LEVEL_CONTROL_MOVE_TO_LEVEL_WITH_ON_OFF,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U24,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_level_move_cmd_req(esp_zb_zcl_level_move_cmd_t *cmd_req)
{
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_LEVEL_CONTROL_MOVE,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U16,
        .data.value = &cmd_req->move_mode,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_level_move_with_onoff_cmd_req(esp_zb_zcl_level_move_cmd_t *cmd_req)
{
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_LEVEL_CONTROL_MOVE_WITH_ON_OFF,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U16,
        .data.value = &cmd_req->move_mode,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_level_step_cmd_req(esp_zb_zcl_level_step_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t step_mode;                                  /*!< step mode either up or down */
        uint8_t step_size;                                  /*!< step size wants to change*/
        uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
    } __attribute__ ((packed)) esp_zb_zcl_step_t;

    esp_zb_zcl_step_t value = {
        .step_mode = cmd_req->step_mode,
        .step_size = cmd_req->step_size,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_LEVEL_CONTROL_STEP,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U32,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_level_step_with_onoff_cmd_req(esp_zb_zcl_level_step_cmd_t *cmd_req)
{
    typedef struct {
        uint8_t step_mode;                                  /*!< step mode either up or down */
        uint8_t step_size;                                  /*!< step size wants to change*/
        uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
    } __attribute__ ((packed)) esp_zb_zcl_step_t;

    esp_zb_zcl_step_t value = {
        .step_mode = cmd_req->step_mode,
        .step_size = cmd_req->step_size,
        .transition_time = cmd_req->transition_time,
    };

    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_LEVEL_CONTROL_STEP_WITH_ON_OFF,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U32,
        .data.value = &value,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_level_stop_cmd_req(esp_zb_zcl_level_stop_cmd_t *cmd_req)
{
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_LEVEL_CONTROL_STOP,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_NULL,
        .data.value = NULL,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}
