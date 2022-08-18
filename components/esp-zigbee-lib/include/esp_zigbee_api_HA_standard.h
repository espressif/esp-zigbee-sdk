/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_api_core.h"
/**
 * @brief Zigbee standard mandatory attribute for basic cluster.
 *
 */
typedef struct esp_zb_basic_cluster_cfg_s{
    uint8_t  zcl_version;                       /*!<  ZCL version */
    uint8_t  power_source;                      /*!<  The sources of power available to the device */
} esp_zb_basic_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for identify cluster.
 *
 */
typedef struct esp_zb_identify_cluster_cfg_s{
    uint16_t  identify_time;                    /*!<  The remaining length of the time that identify itself */
} esp_zb_identify_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for groups cluster.
 *
 */
typedef struct esp_zb_groups_cluster_cfg_s{
    uint8_t  groups_name_support_id;            /*!<  The indication of group names are supported or not */
} esp_zb_groups_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for scenes cluster.
 *
 */
typedef struct esp_zb_scenes_cluster_cfg_s{
    uint8_t  scenes_count;                      /*!<  The number of scenes currently in the scene table */
    uint8_t  current_scene;                     /*!<  Scene ID that invoked */
    uint16_t current_group;                     /*!<  Group ID that invoked */
    bool  scene_valid;                          /*!<  Indication of the associated with current scene and group valid or not*/
    uint8_t  name_support;                      /*!<  The indication of group names are supported or not */
} esp_zb_scenes_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for on_off cluster.
 *
 */
typedef struct esp_zb_on_off_cluster_cfg_s{
    bool  on_off;                               /*!<  On Off state of the device */
} esp_zb_on_off_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for level cluster.
 *
 */
typedef struct esp_zb_level_cluster_cfg_s{
    uint8_t  current_level;                     /*!<  Current level of the device */
} esp_zb_level_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for color cluster.
 *
 */
typedef struct esp_zb_color_cluster_cfg_s{
    uint16_t current_x;                         /*!<  The current value of the normalized chromaticity value x */
    uint16_t current_y;                         /*!<  The current value of the normalized chromaticity value y */
    uint8_t  color_mode;                        /*!<  The mode which attribute determines the color of the device */
    uint8_t  options;                           /*!<  The bitmap determines behavior of some cluster commands */
    uint8_t  enhanced_color_mode;               /*!<  The enhanced-mode which attribute determines the color of the device */
    uint16_t color_capabilities;                /*!<  Specifying the color capabilities of the device support the color control cluster */
} esp_zb_color_cluster_cfg_t;

/**
 * @brief Zigbee HA standard on-off light device clusters.
 *
 */
typedef struct esp_zb_on_off_light_cfg_s{
    esp_zb_basic_cluster_cfg_t      basic_cfg;      /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t   identify_cfg;   /*!<  Identify cluster configuration */
    esp_zb_groups_cluster_cfg_t     groups_cfg;     /*!<  Groups cluster configuration */
    esp_zb_scenes_cluster_cfg_t     scenes_cfg;     /*!<  Scenes cluster configuration */
    esp_zb_on_off_cluster_cfg_t     on_off_cfg;     /*!<  On off cluster configuration */
} esp_zb_on_off_light_cfg_t;

/**
 * @brief Zigbee HA standard on-off switch device clusters.
 *
 */
typedef struct esp_zb_on_off_switch_cfg_s{
    esp_zb_basic_cluster_cfg_t      basic_cfg;      /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t   identify_cfg;   /*!<  Identify cluster configuration */
} esp_zb_on_off_switch_cfg_t;

/**
 * @brief Zigbee HA standard color dimmable light device clusters.
 *
 */
typedef struct esp_zb_color_dimmable_light_cfg_s{
    esp_zb_basic_cluster_cfg_t      basic_cfg;      /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t   identify_cfg;   /*!<  Identify cluster configuration */
    esp_zb_groups_cluster_cfg_t     groups_cfg;     /*!<  Groups cluster configuration */
    esp_zb_scenes_cluster_cfg_t     scenes_cfg;     /*!<  Scenes cluster configuration */
    esp_zb_on_off_cluster_cfg_t     on_off_cfg;     /*!<  On off cluster configuration */
    esp_zb_level_cluster_cfg_t      level_cfg;      /*!<  Level cluster configuration */
    esp_zb_color_cluster_cfg_t      color_cfg;      /*!<  Color cluster configuration */
} esp_zb_color_dimmable_light_cfg_t;

/**
 * @brief Zigbee HA standard color dimmable switch device clusters.
 *
 */
typedef struct esp_zb_color_dimmable_switch_cfg_s{
    esp_zb_basic_cluster_cfg_t      basic_cfg;      /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t   identify_cfg;   /*!<  Identify cluster configuration */
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
 * @note This function adds a single endpoint to a cluster list. To add several endpoints to the cluster list use @ref esp_zb_ep_list_add_ep.
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
