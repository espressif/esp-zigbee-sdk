/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "esp_host_zb.h"

#include "esp_zigbee_ha_standard.h"
#include "esp_zigbee_zcl_command.h"

esp_zb_ep_list_t *esp_zb_on_off_light_ep_create(uint8_t endpoint_id, esp_zb_on_off_light_cfg_t *light_cfg)
{
    uint16_t outputCluster[] = {ESP_ZB_ZCL_CLUSTER_ID_BASIC, ESP_ZB_ZCL_CLUSTER_ID_IDENTIFY, ESP_ZB_ZCL_CLUSTER_ID_GROUPS, ESP_ZB_ZCL_CLUSTER_ID_SCENES, ESP_ZB_ZCL_CLUSTER_ID_ON_OFF};
    esp_host_zb_endpoint_t host_endpoint = {
        .endpoint = endpoint_id,
        .profileId = ESP_ZB_AF_HA_PROFILE_ID,
        .deviceId = ESP_ZB_HA_ON_OFF_LIGHT_DEVICE_ID,
        .appFlags = 0,
        .inputClusterCount = 0,
        .inputClusterList = NULL,
        .outputClusterCount = sizeof(outputCluster) / sizeof(outputCluster[0]),
        .outputClusterList = outputCluster,
    };

    esp_host_zb_ep_create(&host_endpoint);

    return NULL;
}

esp_zb_ep_list_t *esp_zb_on_off_switch_ep_create(uint8_t endpoint_id, esp_zb_on_off_switch_cfg_t *switch_cfg)
{
    uint16_t inputCluster[] = {ESP_ZB_ZCL_CLUSTER_ID_IDENTIFY, ESP_ZB_ZCL_CLUSTER_ID_ON_OFF};
    uint16_t outputCluster[] = {ESP_ZB_ZCL_CLUSTER_ID_BASIC, ESP_ZB_ZCL_CLUSTER_ID_IDENTIFY};
    esp_host_zb_endpoint_t host_endpoint = {
        .endpoint = endpoint_id,
        .profileId = ESP_ZB_AF_HA_PROFILE_ID,
        .deviceId = ESP_ZB_HA_ON_OFF_SWITCH_DEVICE_ID,
        .appFlags = 0,
        .inputClusterCount = sizeof(inputCluster) / sizeof(inputCluster[0]),
        .inputClusterList = inputCluster,
        .outputClusterCount = sizeof(outputCluster) / sizeof(outputCluster[0]),
        .outputClusterList = outputCluster,
    };

    esp_host_zb_ep_create(&host_endpoint);

    return NULL;
}