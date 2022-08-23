/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_api_core.h"
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Zigbee standard mandatory attribute for basic cluster.
 *
 */
typedef struct esp_zb_basic_cluster_cfg_s{
    uint8_t  zcl_version;
    uint8_t  power_source;
} esp_zb_basic_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for identify cluster.
 *
 */
typedef struct esp_zb_identify_cluster_cfg_s{
    uint16_t  identify_time;
} esp_zb_identify_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for groups cluster.
 *
 */
typedef struct esp_zb_groups_cluster_cfg_s{
    uint8_t  groups_name_support_id;
} esp_zb_groups_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for scenes cluster.
 *
 */
typedef struct esp_zb_scenes_cluster_cfg_s{
    uint8_t  scenes_count;
    uint8_t  current_scene;
    uint16_t current_group;
    bool  scene_valid;
    uint8_t  name_support;
} esp_zb_scenes_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for on_off cluster.
 *
 */
typedef struct esp_zb_on_off_cluster_cfg_s{
    bool  on_off;
} esp_zb_on_off_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for level cluster.
 *
 */
typedef struct esp_zb_level_cluster_cfg_s{
    uint8_t  current_level;
} esp_zb_level_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for color cluster.
 *
 */
typedef struct esp_zb_color_cluster_cfg_s{
    uint16_t current_x;
    uint16_t current_y;
    uint8_t  color_mode;
    uint8_t  options;
    uint8_t  enhanced_color_mode;
    uint16_t color_capabilities;
} esp_zb_color_cluster_cfg_t;

/**
 * @brief Zigbee HA standard on-off light device clusters.
 *
 */
typedef struct esp_zb_on_off_light_cfg_s{
    esp_zb_basic_cluster_cfg_t      basic_cfg;
    esp_zb_identify_cluster_cfg_t   identify_cfg;
    esp_zb_groups_cluster_cfg_t     groups_cfg;
    esp_zb_scenes_cluster_cfg_t     scenes_cfg;
    esp_zb_on_off_cluster_cfg_t     on_off_cfg;
} esp_zb_on_off_light_cfg_t;

/**
 * @brief Zigbee HA standard on-off switch device clusters.
 *
 */
typedef struct esp_zb_on_off_switch_cfg_s{
    esp_zb_basic_cluster_cfg_t      basic_cfg;
    esp_zb_identify_cluster_cfg_t   identify_cfg;
} esp_zb_on_off_switch_cfg_t;

/**
 * @brief Zigbee HA standard color dimmable light device clusters.
 *
 */
typedef struct esp_zb_color_dimmable_light_cfg_s{
    esp_zb_basic_cluster_cfg_t      basic_cfg;
    esp_zb_identify_cluster_cfg_t   identify_cfg;
    esp_zb_groups_cluster_cfg_t     groups_cfg;
    esp_zb_scenes_cluster_cfg_t     scenes_cfg;
    esp_zb_on_off_cluster_cfg_t     on_off_cfg;
    esp_zb_level_cluster_cfg_t      level_cfg;
    esp_zb_color_cluster_cfg_t      color_cfg;
} esp_zb_color_dimmable_light_cfg_t;

/**
 * @brief Zigbee HA standard color dimmable switch device clusters.
 *
 */
typedef struct esp_zb_color_dimmable_switch_cfg_s{
    esp_zb_basic_cluster_cfg_t      basic_cfg;
    esp_zb_identify_cluster_cfg_t   identify_cfg;
} esp_zb_color_dimmable_switch_cfg_t;

/**
 * @brief Zigbee HA standard on-off light device default config value.
 *
 */
#define ESP_ZB_DEFAULT_ON_OFF_LIGHT_CONFIG()                                \
    {                                                                       \
        .basic_cfg =                                                        \
            {                                                               \
                .zcl_version = ZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,      \
                .power_source = ZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,    \
            },                                                              \
        .identify_cfg =                                                     \
            {                                                               \
                .identify_time = ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,\
            },                                                              \
        .groups_cfg =                                                       \
            {                                                               \
                .groups_name_support_id = 0,                                \
            },                                                              \
        .scenes_cfg =                                                       \
            {                                                               \
                .scenes_count = ZB_ZCL_SCENES_SCENE_COUNT_DEFAULT_VALUE,    \
                .current_scene = ZB_ZCL_SCENES_CURRENT_SCENE_DEFAULT_VALUE, \
                .current_group = ZB_ZCL_SCENES_CURRENT_GROUP_DEFAULT_VALUE, \
                .scene_valid = ZB_ZCL_SCENES_SCENE_VALID_DEFAULT_VALUE,     \
                .name_support = 0,                                          \
            },                                                              \
        .on_off_cfg =                                                       \
            {                                                               \
                .on_off = ZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE,               \
            },                                                              \
    }

/**
 * @brief Zigbee HA standard on-off switch device default config value.
 *
 */
#define ESP_ZB_DEFAULT_ON_OFF_SWITCH_CONFIG()                               \
    {                                                                       \
        .basic_cfg =                                                        \
            {                                                               \
                .zcl_version = ZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,      \
                .power_source = ZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,    \
            },                                                              \
        .identify_cfg =                                                     \
            {                                                               \
                .identify_time = ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,\
            },                                                              \
    }

/**
 * @brief Zigbee HA standard color dimmable light device default config value.
 *
 */
#define ESP_ZB_DEFAULT_COLOR_DIMMABLE_LIGHT_CONFIG()                                            \
    {                                                                                           \
        .basic_cfg =                                                                            \
            {                                                                                   \
                .zcl_version = ZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,                          \
                .power_source = ZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,                        \
            },                                                                                  \
        .identify_cfg =                                                                         \
            {                                                                                   \
                .identify_time = ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,                   \
            },                                                                                  \
        .groups_cfg =                                                                           \
            {                                                                                   \
                .groups_name_support_id = 0,                                                    \
            },                                                                                  \
        .scenes_cfg =                                                                           \
            {                                                                                   \
                .scenes_count = ZB_ZCL_SCENES_SCENE_COUNT_DEFAULT_VALUE,                        \
                .current_scene = ZB_ZCL_SCENES_CURRENT_SCENE_DEFAULT_VALUE,                     \
                .current_group = ZB_ZCL_SCENES_CURRENT_GROUP_DEFAULT_VALUE,                     \
                .scene_valid = ZB_ZCL_SCENES_SCENE_VALID_DEFAULT_VALUE,                         \
                .name_support = 0,                                                              \
            },                                                                                  \
        .on_off_cfg =                                                                           \
            {                                                                                   \
                .on_off = ZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE,                                   \
            },                                                                                  \
        .level_cfg =                                                                            \
            {                                                                                   \
                .current_level = ZB_ZCL_LEVEL_CONTROL_CURRENT_LEVEL_DEFAULT_VALUE,              \
            },                                                                                  \
        .color_cfg =                                                                            \
            {                                                                                   \
                .current_x = ZB_ZCL_COLOR_CONTROL_CURRENT_X_DEF_VALUE,                          \
                .current_y = ZB_ZCL_COLOR_CONTROL_CURRENT_Y_DEF_VALUE,                          \
                .color_mode = ZB_ZCL_COLOR_CONTROL_COLOR_MODE_DEFAULT_VALUE,                    \
                .options = ZB_ZCL_COLOR_CONTROL_OPTIONS_DEFAULT_VALUE,                          \
                .enhanced_color_mode = ZB_ZCL_COLOR_CONTROL_ENHANCED_COLOR_MODE_DEFAULT_VALUE,  \
                .color_capabilities = 0x0008,                                                   \
            },                                                                                  \
    }

/**
 * @brief Zigbee HA standard color dimmable switch device default config value.
 *
 */
#define ESP_ZB_DEFAULT_COLOR_DIMMABLE_SWITCH_CONFIG()                       \
    {                                                                       \
        .basic_cfg =                                                        \
            {                                                               \
                .zcl_version = ZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,      \
                .power_source = ZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,    \
            },                                                              \
        .identify_cfg =                                                     \
            {                                                               \
                .identify_time = ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,\
            },                                                              \
    }

/********************* Declare functions **************************/
/* ZCL standard attribute list template */

/**
 * @brief  Create a standard basic cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] basic_cfg  Configuration parameters for this cluster defined by @ref esp_zb_basic_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_basic_cluster_create(esp_zb_basic_cluster_cfg_t *basic_cfg);

/**
 * @brief  Create a standard identify cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] identify_cfg  Configuration parameters for this cluster defined by @ref esp_zb_identify_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_identify_cluster_create(esp_zb_identify_cluster_cfg_t *identify_cfg);

/**
 * @brief  Create a standard group cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] group_cfg  Configuration parameters for this cluster defined by @ref esp_zb_groups_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_groups_cluster_create(esp_zb_groups_cluster_cfg_t *group_cfg);

/**
 * @brief  Create a standard scenes cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] scene_cfg  Configuration parameters for this cluster defined by @ref esp_zb_scenes_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_scenes_cluster_create(esp_zb_scenes_cluster_cfg_t *scene_cfg);

/**
 * @brief  Create a standard on-off cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] on_off_cfg  Configuration parameters for this cluster defined by @ref esp_zb_on_off_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_on_off_cluster_create(esp_zb_on_off_cluster_cfg_t *on_off_cfg);

/**
 * @brief  Create a standard level cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] level_cfg  Configuration parameters for this cluster defined by @ref esp_zb_level_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_level_cluster_create(esp_zb_level_cluster_cfg_t *level_cfg);

/**
 * @brief  Create a standard color cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] color_cfg  Configuration parameters for this cluster defined by @ref esp_zb_color_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_color_control_cluster_create(esp_zb_color_cluster_cfg_t *color_cfg);

/* ZCL standard cluster list template */

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

/* ZCL standard ep list template */

/**
 * @brief  Create a standard single HA on off light endpoint.
 *
 * @param[in] endpoint_id The specific endpoint
 * @param[in] light_cfg  Configuration parameters for this cluster lists defined by @ref esp_zb_on_off_light_cfg_s
 *
 * @note This function adds a single endpoint to a cluster list. To add several endpoints to the cluster list use @ref esp_zb_ep_list_add_ep.
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
 * @note This function adds a single endpoint to a cluster list. To add several endpoints to the cluster list use @ref esp_zb_ep_list_add_epp.
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
 * @note This function adds a single endpoint to a cluster list. To add several endpoints to the cluster list use @ref esp_zb_ep_list_add_ep.
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
 * @note This function adds a single endpoint to a cluster list. To add several endpoints to the cluster list use @ref esp_zb_ep_list_add_ep.
 *
 * @return Pointer to esp_zb_ep_list_t @ref esp_zb_ep_list_s
 *
 */
esp_zb_ep_list_t *esp_zb_color_dimmable_switch_ep_create(uint8_t endpoint_id, esp_zb_color_dimmable_switch_cfg_t *switch_cfg);
#ifdef __cplusplus
}
#endif
