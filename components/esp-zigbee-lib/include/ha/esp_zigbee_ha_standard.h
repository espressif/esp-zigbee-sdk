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

/**
 * @brief Zigbee HA standard color dimmable light device default config value.
 *
 */
#define ESP_ZB_DEFAULT_COLOR_DIMMABLE_LIGHT_CONFIG()                                                \
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
        .level_cfg =                                                                                \
            {                                                                                       \
                .current_level = ESP_ZB_ZCL_LEVEL_CONTROL_CURRENT_LEVEL_DEFAULT_VALUE,              \
            },                                                                                      \
        .color_cfg =                                                                                \
            {                                                                                       \
                .current_x = ESP_ZB_ZCL_COLOR_CONTROL_CURRENT_X_DEF_VALUE,                          \
                .current_y = ESP_ZB_ZCL_COLOR_CONTROL_CURRENT_Y_DEF_VALUE,                          \
                .color_mode = ESP_ZB_ZCL_COLOR_CONTROL_COLOR_MODE_DEFAULT_VALUE,                    \
                .options = ESP_ZB_ZCL_COLOR_CONTROL_OPTIONS_DEFAULT_VALUE,                          \
                .enhanced_color_mode = ESP_ZB_ZCL_COLOR_CONTROL_ENHANCED_COLOR_MODE_DEFAULT_VALUE,  \
                .color_capabilities = 0x0008,                                                       \
            },                                                                                      \
    }

/**
 * @brief Zigbee HA standard color dimmable switch device default config value.
 *
 */
#define ESP_ZB_DEFAULT_COLOR_DIMMABLE_SWITCH_CONFIG()                                               \
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

/**
 * @brief Zigbee HA standard mains power outlet device default config value.
 *
 */
#define ESP_ZB_DEFAULT_MAINS_POWER_OUTLET_CONFIG()                                                  \
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
                .on_off = ESP_ZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE,                                       \
            },                                                                                      \
    }

/**
 * @brief Zigbee HA standard shade device default config value.
 *
 */
#define ESP_ZB_DEFAULT_SHADE_CONFIG()                                                               \
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
        .level_cfg =                                                                                \
            {                                                                                       \
            .current_level = ESP_ZB_ZCL_LEVEL_CONTROL_CURRENT_LEVEL_DEFAULT_VALUE,                  \
            },                                                                                      \
        .shade_cfg =                                                                                \
            {                                                                                       \
                .status = ESP_ZB_ZCL_SHADE_CONFIG_STATUS_DEFAULT_VALUE,                             \
                .closed_limit = ESP_ZB_ZCL_SHADE_CONFIG_CLOSED_LIMIT_DEFAULT_VALUE,                 \
                .mode = ESP_ZB_ZCL_SHADE_CONFIG_MODE_DEFAULT_VALUE,                                 \
            },                                                                                      \
    }

/**
 * @brief Zigbee HA standard shade controller device default config value.
 *
 */
#define ESP_ZB_DEFAULT_SHADE_CONTROLLER_CONFIG()                                                    \
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

/**
 * @brief Zigbee HA standard door lock device default config value.
 *
 */
#define ESP_ZB_DEFAULT_DOOR_LOCK_CONFIG()                                                           \
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
        .door_lock_cfg =                                                                            \
            {                                                                                       \
                .lock_state = ESP_ZB_ZCL_ATTR_DOOR_LOCK_LOCK_STATE_DEFAULT_VALUE,                   \
                .lock_type = ESP_ZB_ZCL_ATTR_DOOR_LOCK_LOCK_TYPE_DEFAULT_VALUE,                     \
                .actuator_enabled = ESP_ZB_ZCL_ATTR_DOOR_LOCK_ACTUATOR_ENABLED_DEFAULT_VALUE,       \
            },                                                                                      \
    }

/**
 * @brief Zigbee HA standard door lock controller device default config value.
 *
 */
#define ESP_ZB_DEFAULT_DOOR_LOCK_CONTROLLER_CONFIG()                                                \
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

/**
 * @brief Zigbee HA standard temperature sensor device default config value.
 *
 */
#define ESP_ZB_DEFAULT_TEMPERATURE_SENSOR_CONFIG()                                                  \
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
        .temp_meas_cfg =                                                                            \
            {                                                                                       \
                .measured_value = ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_VALUE_UNKNOWN,                   \
                .min_value = ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_MIN_VALUE_INVALID,                    \
                .max_value = ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_MAX_VALUE_INVALID,                    \
            },                                                                                      \
    }

/**
 * @brief Zigbee HA standard configuration tool device default config value.
 *
 */
#define ESP_ZB_DEFAULT_CONFIGURATION_TOOL_CONFIG()                                                  \
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

/***************************** ZCL HA device standard cluster list ********************************/

/**
 * @brief  Create a standard HA on-off light cluster list.
 *
 * @note This contains basic, identify, groups, scenes, on-off cluster as server side.
 * @param[in] light_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_on_off_light_cfg_s
 *
 * @return Pointer to cluster list  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t  *esp_zb_on_off_light_clusters_create(esp_zb_on_off_light_cfg_t *light_cfg);

/**
 * @brief  Create a standard HA on-off switch cluster list.
 *
 * @note This contains basic, identify, as server side. And identify, on-off cluster as client side.
 * @param[in] switch_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_on_off_switch_cfg_s
 *
 * @return Pointer to cluster list  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t  *esp_zb_on_off_switch_clusters_create(esp_zb_on_off_switch_cfg_t *switch_cfg);

/**
 * @brief  Create a standard HA color dimmable light cluster list.
 *
 * @note This contains basic, identify, groups, scenes, on-off, level, color cluster as server side.
 * @param[in] light_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_color_dimmable_light_cfg_s
 *
 * @return Pointer to cluster list  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t  *esp_zb_color_dimmable_light_clusters_create(esp_zb_color_dimmable_light_cfg_t *light_cfg);

/**
 * @brief  Create a standard HA color dimmable switch cluster list.
 *
 * @note This contains basic, identify, as server side. And identify, on-off, level, color cluster as client side.
 * @param[in] switch_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_color_dimmable_switch_cfg_s
 *
 * @return Pointer to cluster list  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t  *esp_zb_color_dimmable_switch_clusters_create(esp_zb_color_dimmable_switch_cfg_t *switch_cfg);

/**
 * @brief  Create a standard HA mains power outlet cluster list.
 *
 * @note This contains basic, identify, groups, scenes, on-off, level control and shade config cluster as server side.
 * @param[in] outlet_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_mains_power_outlet_cfg_s
 *
 * @return Pointer to cluster list  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t  *esp_zb_mains_power_outlet_clusters_create(esp_zb_mains_power_outlet_cfg_t *outlet_cfg);

/**
 * @brief  Create a standard HA shade cluster list.
 *
 * @note This contains basic, identify, groups, scenes, on-off cluster as server side.
 * @param[in] shade_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_shade_cfg_s
 *
 * @return Pointer to cluster list  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t  *esp_zb_shade_clusters_create(esp_zb_shade_cfg_t *shade_cfg);

/**
 * @brief  Create a standard HA shade controller cluster list.
 *
 * @note This contains basic, identify cluster as server side. Identify, on-off and level control cluster as client side.
 * @param[in] shade_controller_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_shade_controller_cfg_s
 *
 * @return Pointer to cluster list  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t  *esp_zb_shade_controller_clusters_create(esp_zb_shade_controller_cfg_t *shade_controller_cfg);

/**
 * @brief  Create a standard HA door lock cluster list.
 *
 * @note This contains basic, identify, groups, scenes, door lock cluster as server side.
 * @param[in] door_lock  Configuration parameters for this cluster lists defined by @ref esp_zb_door_lock_cfg_s
 *
 * @return Pointer to cluster list  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t  *esp_zb_door_lock_clusters_create(esp_zb_door_lock_cfg_t *door_lock);

/**
 * @brief  Create a standard HA door lock controller cluster list.
 *
 * @note This contains basic, identify cluster as server side. Identify, scenes, groups and door lock cluster as client side.
 * @param[in] door_lock_controller  Configuration parameters for this cluster lists defined by @ref esp_zb_door_lock_controller_cfg_s
 *
 * @return Pointer to cluster list  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t  *esp_zb_door_lock_controller_clusters_create(esp_zb_door_lock_controller_cfg_t *door_lock_controller);

/**
 * @brief  Create a standard HA temperature sensor cluster list.
 *
 * @note This contains basic, identify cluster and temperature measurement as server side. Identify cluster as client side.
 * @param[in] temperature_sensor  Configuration parameters for this cluster lists defined by @ref esp_zb_temperature_sensor_cfg_s
 *
 * @return Pointer to cluster list  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t  *esp_zb_temperature_sensor_clusters_create(esp_zb_temperature_sensor_cfg_t *temperature_sensor);

/**
 * @brief  Create a standard HA configuration tool cluster list.
 *
 * @note This contains basic, identify cluster as server side. Identify, scenes, groups and door lock cluster as client side.
 * @param[in] configuration_tool  Configuration parameters for this cluster lists defined by @ref esp_zb_configuration_tool_cfg_s
 *
 * @return Pointer to cluster list  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t  *esp_zb_configuration_tool_clusters_create(esp_zb_configuration_tool_cfg_t *configuration_tool);

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

/**
 * @brief  Create a standard single HA color dimmable light endpoint.
 *
 * @param[in] endpoint_id The specific endpoint
 * @param[in] light_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_color_dimmable_light_cfg_s
 *
 * @note This function adds a single endpoint to a cluster list.
 *
 * @return Pointer to esp_zb_ep_list_t @ref esp_zb_ep_list_s
 *
 */
esp_zb_ep_list_t *esp_zb_color_dimmable_light_ep_create(uint8_t endpoint_id, esp_zb_color_dimmable_light_cfg_t *light_cfg);

/**
 * @brief  Create a standard single HA color dimmable switch endpoint.
 *
 * @param[in] endpoint_id The specific endpoint
 * @param[in] switch_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_color_dimmable_switch_cfg_s
 *
 * @note This function adds a single endpoint to a cluster list.
 *
 * @return Pointer to esp_zb_ep_list_t @ref esp_zb_ep_list_s
 *
 */
esp_zb_ep_list_t *esp_zb_color_dimmable_switch_ep_create(uint8_t endpoint_id, esp_zb_color_dimmable_switch_cfg_t *switch_cfg);

/**
 * @brief  Create a standard single HA mains power outlet endpoint.
 *
 * @param[in] endpoint_id The specific endpoint
 * @param[in] outlet_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_mains_power_outlet_cfg_s
 *
 * @note This function adds a single endpoint to a cluster list.
 *
 * @return Pointer to esp_zb_ep_list_t @ref esp_zb_ep_list_s
 *
 */
esp_zb_ep_list_t *esp_zb_mains_power_outlet_ep_create(uint8_t endpoint_id, esp_zb_mains_power_outlet_cfg_t *outlet_cfg);

/**
 * @brief  Create a standard single HA shade endpoint.
 *
 * @param[in] endpoint_id The specific endpoint
 * @param[in] shade_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_shade_cfg_s
 *
 * @note This function adds a single endpoint to a cluster list.
 *
 * @return Pointer to esp_zb_ep_list_t @ref esp_zb_ep_list_s
 *
 */
esp_zb_ep_list_t *esp_zb_shade_ep_create(uint8_t endpoint_id, esp_zb_shade_cfg_t *shade_cfg);

/**
 * @brief  Create a standard single HA shade controller endpoint.
 *
 * @param[in] endpoint_id The specific endpoint
 * @param[in] shade_controller_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_shade_controller_cfg_s
 *
 * @note This function adds a single endpoint to a cluster list.
 *
 * @return Pointer to esp_zb_ep_list_t @ref esp_zb_ep_list_s
 *
 */
esp_zb_ep_list_t *esp_zb_shade_controller_ep_create(uint8_t endpoint_id, esp_zb_shade_controller_cfg_t *shade_controller_cfg);

/**
 * @brief  Create a standard single HA door lock endpoint.
 *
 * @param[in] endpoint_id The specific endpoint
 * @param[in] door_lock  Configuration parameters for this cluster lists defined by @ref esp_zb_door_lock_cfg_s
 *
 * @note This function adds a single endpoint to a cluster list.
 *
 * @return Pointer to esp_zb_ep_list_t @ref esp_zb_ep_list_s
 *
 */
esp_zb_ep_list_t *esp_zb_door_lock_ep_create(uint8_t endpoint_id, esp_zb_door_lock_cfg_t *door_lock);

/**
 * @brief  Create a standard single HA door lock controller endpoint.
 *
 * @param[in] endpoint_id The specific endpoint
 * @param[in] door_lock_controller  Configuration parameters for this cluster lists defined by @ref esp_zb_door_lock_controller_cfg_s
 *
 * @note This function adds a single endpoint to a cluster list.
 *
 * @return Pointer to esp_zb_ep_list_t @ref esp_zb_ep_list_s
 *
 */
esp_zb_ep_list_t *esp_zb_door_lock_controller_ep_create(uint8_t endpoint_id, esp_zb_door_lock_controller_cfg_t *door_lock_controller);

/**
 * @brief  Create a standard single HA temperature sensor endpoint.
 *
 * @param[in] endpoint_id The specific endpoint
 * @param[in] temperature_sensor  Configuration parameters for this cluster lists defined by @ref esp_zb_temperature_sensor_cfg_s
 *
 * @note This function adds a single endpoint to a cluster list.
 *
 * @return Pointer to esp_zb_ep_list_t @ref esp_zb_ep_list_s
 *
 */
esp_zb_ep_list_t *esp_zb_temperature_sensor_ep_create(uint8_t endpoint_id, esp_zb_temperature_sensor_cfg_t *temperature_sensor);

/**
 * @brief  Create a standard single HA configuration tool endpoint.
 *
 * @param[in] endpoint_id The specific endpoint
 * @param[in] configuration_tool  Configuration parameters for this cluster lists defined by @ref esp_zb_configuration_tool_cfg_s
 *
 * @note This function adds a single endpoint to a cluster list.
 *
 * @return Pointer to esp_zb_ep_list_t @ref esp_zb_ep_list_s
 *
 */
esp_zb_ep_list_t *esp_zb_configuration_tool_ep_create(uint8_t endpoint_id, esp_zb_configuration_tool_cfg_t *configuration_tool);

#ifdef __cplusplus
}
#endif
