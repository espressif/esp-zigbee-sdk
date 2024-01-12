/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_zigbee_zcl_command.h"

/* ZCL identify cluster list command */

uint8_t esp_zb_zcl_identify_cmd_req(esp_zb_zcl_identify_cmd_t *cmd_req)
{
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_IDENTIFY,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_IDENTIFY_IDENTIFY_ID,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U16,
        .data.value = &cmd_req->identify_time,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_identify_trigger_effect_cmd_req(esp_zb_zcl_identify_trigger_effect_cmd_t *cmd_req)
{
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_IDENTIFY,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_IDENTIFY_TRIGGER_EFFECT_ID,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_U16,
        .data.value = &cmd_req->effect_id,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}

uint8_t esp_zb_zcl_identify_query_cmd_req(esp_zb_zcl_identify_query_cmd_t *cmd_req)
{
    esp_zb_zcl_custom_cluster_cmd_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_IDENTIFY,
        .custom_cmd_id = ESP_ZB_ZCL_CMD_IDENTIFY_IDENTIFY_QUERY_ID,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .data.type = ESP_ZB_ZCL_ATTR_TYPE_NULL,
        .data.value = NULL,
    };

    esp_zb_zcl_custom_cluster_cmd_req(&zcl_data);

    return ESP_OK;
}
