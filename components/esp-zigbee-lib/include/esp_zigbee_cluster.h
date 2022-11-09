/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "esp_zigbee_type.h"

/**
 * @brief  Create an empty cluster list.
 *
 * @note  This cluster list is ready to add / update cluster refer to esp_zb_cluster_list_add_xxx_cluster() and esp_zb_cluster_list_update_xxx_cluster().
 * @return pointer to  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t *esp_zb_zcl_cluster_list_create(void);

/**
 * @brief  Get ZCL cluster descriptor.
 *
 * @note  Getting the local cluster from the specific endpoint.
 *
 * @param[in] endpoint The endpoint
 * @param[in] cluster_id The cluster id for attribute list refer to esp_zb_zcl_cluster_id
 * @param[in] cluster_role The cluster role of this cluster, either server or client role refer to esp_zb_zcl_cluster_role
 *
 * @return pointer to  @ref esp_zb_zcl_cluster_s
 *
 */
esp_zb_zcl_cluster_t *esp_zb_zcl_get_cluster(uint8_t endpoint, uint16_t cluster_id, uint8_t cluster_role);

/********************************* ZCL HA standard cluster ********************************/

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

/**
 * @brief  Create a standard time cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] time_cfg  Configuration parameters for this cluster defined by @ref esp_zb_time_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_time_cluster_create(esp_zb_time_cluster_cfg_t *time_cfg);

/**
 * @brief  Create a standard shade config cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] shade_cfg  Configuration parameters for this cluster defined by @ref esp_zb_shade_config_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_shade_config_cluster_create(esp_zb_shade_config_cluster_cfg_t *shade_cfg);

/**
 * @brief  Create a standard door lock cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] lock_cfg  Configuration parameters for this cluster defined by @ref esp_zb_door_lock_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_door_lock_cluster_create(esp_zb_door_lock_cluster_cfg_t *lock_cfg);

/**
 * @brief  Create a standard temperature measurement cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] temperature_cfg  Configuration parameters for this cluster defined by @ref esp_zb_temperature_meas_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_temperature_meas_cluster_create(esp_zb_temperature_meas_cluster_cfg_t *temperature_cfg);

/**************************************** ADD CLUSTER ***********************************/
/**
 * @brief Add basic cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_basic_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Add identify cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_identify_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Add groups cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_groups_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Add scenes cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_scenes_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Add on_off cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_on_off_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Add level cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_level_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Add color_control cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_color_control_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Add Time cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_time_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Add Shade Config cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_shade_config_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Add Door Lock cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_door_lock_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Add Temperature measurement cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_temperature_meas_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
* @brief Add customised cluster (attribute list) in a cluster list.
*
* @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
* @param[in] attr_list An attribute list which wants to add
* @param[in] role_mask A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
*
* @note The customized cluster id should not be same as already existing zcl cluster id refer to zb_zcl_common.h
*
* @return
* - ESP_OK on success
* - ESP_ERR_INVALID_ARG if cluster list not initialized
*
*/
esp_err_t esp_zb_cluster_list_add_custom_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**************************************** UPDATE CLUSTER ***********************************/
/**
 * @brief Update basic cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_basic_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Update identify cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_identify_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Update groups cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_groups_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Update scenes cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_scenes_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Update on_off cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_on_off_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Update level cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_level_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Update color control cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_color_control_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Update Time cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_time_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Update Shade Config cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_shade_config_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Update Door Lock cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_door_lock_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Update temperature measurement cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_temperature_meas_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Update Customised cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_custom_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

#ifdef __cplusplus
}
#endif
