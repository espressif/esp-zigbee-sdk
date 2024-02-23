/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_core.h"

/**
 * @brief Zigbee HA standard on-off light device default config value.
 *
 */
#define ESP_ZB_DEFAULT_ON_OFF_LIGHT_CONFIG()                                                        \
    {                                                                                               \
        .basic_cfg =                                                                                \
            {                                                                                       \
                .zcl_version = ESP_ZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,                          \
                .power_source = ESP_ZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,                        \
            },                                                                                      \
        .identify_cfg =                                                                             \
            {                                                                                       \
                .identify_time = ESP_ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,                   \
            },                                                                                      \
        .groups_cfg =                                                                               \
            {                                                                                       \
                .groups_name_support_id = ESP_ZB_ZCL_GROUPS_NAME_SUPPORT_DEFAULT_VALUE,             \
            },                                                                                      \
        .scenes_cfg =                                                                               \
            {                                                                                       \
                .scenes_count = ESP_ZB_ZCL_SCENES_SCENE_COUNT_DEFAULT_VALUE,                        \
                .current_scene = ESP_ZB_ZCL_SCENES_CURRENT_SCENE_DEFAULT_VALUE,                     \
                .current_group = ESP_ZB_ZCL_SCENES_CURRENT_GROUP_DEFAULT_VALUE,                     \
                .scene_valid = ESP_ZB_ZCL_SCENES_SCENE_VALID_DEFAULT_VALUE,                         \
                .name_support = ESP_ZB_ZCL_SCENES_NAME_SUPPORT_DEFAULT_VALUE,                       \
            },                                                                                      \
        .on_off_cfg =                                                                               \
            {                                                                                       \
                .on_off = ESP_ZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE,                                   \
            },                                                                                      \
    }

/**
 * @brief Zigbee HA standard on-off switch device default config value.
 *
 */
#define ESP_ZB_DEFAULT_ON_OFF_SWITCH_CONFIG()                                                       \
    {                                                                                               \
        .basic_cfg =                                                                                \
            {                                                                                       \
                .zcl_version = ESP_ZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,                          \
                .power_source = ESP_ZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,                        \
            },                                                                                      \
        .identify_cfg =                                                                             \
            {                                                                                       \
                .identify_time = ESP_ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,                   \
            },                                                                                      \
    }

/********************************* Declare functions **************************************/

/****************************** ZCL HA device standard endpoint list ********************************/

/**
 * @brief  Create a standard single HA on off light endpoint.
 *
 * @param[in] endpoint_id The specific endpoint
 * @param[in] light_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_on_off_light_cfg_s
 *
 * @note This function adds a single endpoint to a cluster list.
 *
 * @return Pointer to esp_zb_ep_list_t @ref esp_zb_ep_list_s
 *
 */
esp_zb_ep_list_t *esp_zb_on_off_light_ep_create(uint8_t endpoint_id, esp_zb_on_off_light_cfg_t *light_cfg);

/**
 * @brief  Create a standard single HA on off switch endpoint.
 *
 * @param[in] endpoint_id The specific endpoint
 * @param[in] switch_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_on_off_switch_cfg_s
 *
 * @note This function adds a single endpoint to a cluster list.
 *
 * @return Pointer to esp_zb_ep_list_t @ref esp_zb_ep_list_s
 *
 */
esp_zb_ep_list_t *esp_zb_on_off_switch_ep_create(uint8_t endpoint_id, esp_zb_on_off_switch_cfg_t *switch_cfg);

#ifdef __cplusplus
}
#endif
