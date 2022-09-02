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
 * @param[in] cluster_id The cluster id for attribute list
 * @param[in] cluster_role The cluster role of this cluster, either server or client role
 *
 * @return pointer to  @ref esp_zb_zcl_cluster_s
 *
 */
esp_zb_zcl_cluster_t *esp_zb_zcl_get_cluster(uint8_t endpoint, uint16_t cluster_id, uint8_t cluster_role);

/**
 * @brief Add basic cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
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
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
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
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
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
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
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
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
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
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
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
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_color_control_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

/**
 * @brief Update basic cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
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
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
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
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
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
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
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
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
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
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
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
 * @param[in] role_mask  A role of server or client for this cluster (attribute list)
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_color_control_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

#ifdef __cplusplus
}
#endif
