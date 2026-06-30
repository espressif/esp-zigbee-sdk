/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/core_types.h>

#include <ezbee/zcl/zcl_type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup zcl_descriptors ZCL Descriptors
 * @{
 */

/**
 * @brief Zigbee attribute descriptor (opaque type).
 *
 * This type represents an attribute descriptor that contains attribute metadata
 * including ID, type, access control, and value pointer. Use the accessor functions
 * to get/set attribute properties.
 */
typedef void *ezb_zcl_attr_desc_t;

/**
 * @brief Invalid attribute descriptor.
 */
#define EZB_INVALID_ZCL_ATTR_DESC EZB_INVALID_DESC

/**
 * @brief Zigbee cluster descriptor (opaque type).
 *
 * This type represents a cluster descriptor that contains cluster metadata
 * including cluster ID, role, manufacturer code, and associated attributes.
 */
typedef void *ezb_zcl_cluster_desc_t;

/**
 * @brief Invalid cluster descriptor.
 */
#define EZB_INVALID_ZCL_CLUSTER_DESC EZB_INVALID_DESC

/**
 * @brief Linked list node for a Zigbee attribute list (opaque type).
 *
 * This type represents a list of attributes associated with a cluster.
 */
typedef void *ezb_zcl_attr_list_t;

/**
 * @brief Invalid attribute list.
 */
#define EZB_INVALID_ZCL_ATTR_LIST EZB_INVALID_DESC

/**
 * @brief Linked list node for a Zigbee cluster list (opaque type).
 *
 * This type represents a list of clusters associated with an endpoint.
 */
typedef void *ezb_zcl_cluster_list_t;

/**
 * @brief Invalid cluster list.
 */
#define EZB_INVALID_ZCL_CLUSTER_LIST EZB_INVALID_DESC

/** @} */

/**
 * @brief Get a cluster descriptor for a given endpoint, cluster, and role.
 *
 * This function retrieves the cluster descriptor for a specific cluster on an endpoint.
 * The cluster must have been previously added to the endpoint.
 *
 * @param[in] ep_id      The identifier of the endpoint to search in.
 * @param[in] cluster_id The identifier of the cluster to search for.
 * @param[in] role       The role of the cluster to search for, either @ref EZB_ZCL_CLUSTER_SERVER or @ref EZB_ZCL_CLUSTER_CLIENT.
 * @return The matching cluster descriptor, or @ref EZB_INVALID_ZCL_CLUSTER_DESC if not found.
 */
ezb_zcl_cluster_desc_t ezb_zcl_get_cluster_desc(uint8_t ep_id, uint16_t cluster_id, uint8_t role);

/**
 * @brief Free a Zigbee cluster descriptor.
 *
 * This function frees the memory allocated for a cluster descriptor and all associated attribute descriptors.
 *
 * @param[in] cluster_desc Cluster descriptor to free.
 */
void ezb_zcl_free_cluster_desc(ezb_zcl_cluster_desc_t cluster_desc);

/**
 * @brief Get the cluster ID of a Zigbee cluster descriptor.
 *
 * @param[in] cluster_desc The cluster descriptor.
 * @return The identifier of the cluster.
 */
uint16_t ezb_zcl_cluster_desc_get_id(ezb_zcl_cluster_desc_t cluster_desc);

/**
 * @brief Get the cluster role of a Zigbee cluster descriptor.
 *
 * @param[in] cluster_desc The cluster descriptor.
 * @return Role of the cluster, either @ref EZB_ZCL_CLUSTER_SERVER or @ref EZB_ZCL_CLUSTER_CLIENT, or 0xFF if invalid.
 */
uint8_t ezb_zcl_cluster_desc_get_role(ezb_zcl_cluster_desc_t cluster_desc);

/**
 * @brief Get the manufacturer code of a Zigbee cluster descriptor.
 *
 * @param[in] cluster_desc The cluster descriptor.
 * @return The manufacturer code.
 */
uint16_t ezb_zcl_cluster_desc_get_manuf_code(ezb_zcl_cluster_desc_t cluster_desc);

/**
 * @brief Get the matching attribute descriptor.
 *
 * This function searches for an attribute descriptor matching the specified criteria.
 * For manufacturer-specific attributes, the manuf_code must match exactly.
 *
 * @param[in] ep_id      The identifier of the endpoint to search in.
 * @param[in] cluster_id The identifier of the cluster to search in.
 * @param[in] role       The role of the cluster to search for, either @ref EZB_ZCL_CLUSTER_SERVER or @ref EZB_ZCL_CLUSTER_CLIENT.
 * @param[in] attr_id    The identifier of the attribute to search for.
 * @param[in] manuf_code The manufacturer code to search for. Use @ref EZB_ZCL_STD_MANUF_CODE for standard attributes.
 * @return The matching attribute descriptor on success, EZB_INVALID_ZCL_ATTR_DESC if attribute is not found.
 */
ezb_zcl_attr_desc_t ezb_zcl_get_attr_desc(uint8_t  ep_id,
                                          uint16_t cluster_id,
                                          uint8_t  role,
                                          uint16_t attr_id,
                                          uint16_t manuf_code);

/**
 * @brief Get the attribute ID of a Zigbee attribute descriptor.
 *
 * @param[in] attr_desc The attribute descriptor.
 * @return The identifier of the attribute.
 */
uint16_t ezb_zcl_attr_desc_get_id(ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Get the value size of a Zigbee attribute descriptor.
 *
 * @param[in] attr_desc The attribute descriptor.
 * @return The size of the attribute value in bytes.
 */
uint16_t ezb_zcl_attr_desc_get_value_size(ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Get the value pointer of a Zigbee attribute descriptor.
 *
 * @param[in] attr_desc The attribute descriptor.
 * @param[out] value    The pointer to the buffer where the attribute value will be copied.
 * @return The error code. See @ref ezb_err_t.
 */
ezb_err_t ezb_zcl_attr_desc_get_value(ezb_zcl_attr_desc_t attr_desc, void *value);

/**
 * @brief Set the value of a Zigbee attribute descriptor.
 *
 * @param[in] attr_desc The attribute descriptor.
 * @param[in] value     The pointer to the value to be set to the attribute.
 * @return The error code. See @ref ezb_err_t.
 */
ezb_err_t ezb_zcl_attr_desc_set_value(ezb_zcl_attr_desc_t attr_desc, const void *value);

/**
 * @brief Get the data type of a Zigbee attribute descriptor.
 *
 * @param[in] attr_desc The attribute descriptor.
 * @return The type of the attribute. See @ref ezb_zcl_attr_type_t.
 */
ezb_zcl_attr_type_t ezb_zcl_attr_desc_get_type(ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Get the access control flags of a Zigbee attribute descriptor.
 *
 * @param[in] attr_desc The attribute descriptor.
 * @return The access control flags. See @ref ezb_zcl_attr_access_t.
 */
ezb_zcl_attr_access_t ezb_zcl_attr_desc_get_access(ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Set the access control flags of a Zigbee attribute descriptor.
 *
 * @param[in] attr_desc The attribute descriptor.
 * @param[in] access    The access control flags. See @ref ezb_zcl_attr_access_t.
 * @return The error code. See @ref ezb_err_t.
 */
ezb_err_t ezb_zcl_attr_desc_set_access(ezb_zcl_attr_desc_t attr_desc, ezb_zcl_attr_access_t access);

/**
 * @brief Get the manufacturer code of a Zigbee attribute descriptor.
 *
 * @param[in] attr_desc The attribute descriptor.
 * @return The manufacturer code.
 */
uint16_t ezb_zcl_attr_desc_get_manuf_code(ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Set the manufacturer code of a Zigbee attribute descriptor.
 *
 * @param[in] attr_desc The attribute descriptor.
 * @param[in] manuf_code The manufacturer code to set.
 * @return The error code. See @ref ezb_err_t.
 */
ezb_err_t ezb_zcl_attr_desc_set_manuf_code(ezb_zcl_attr_desc_t attr_desc, uint16_t manuf_code);

/**
 * @brief Get an attribute descriptor from a cluster descriptor.
 *
 * @param[in] cluster_desc The cluster descriptor to search in.
 * @param[in] attr_id      The attribute identifier to search for.
 * @param[in] manuf_code   The manufacturer code to search for.
 * @return The matching attribute descriptor on success, EZB_INVALID_ZCL_ATTR_DESC if attribute is not found.
 */
ezb_zcl_attr_desc_t ezb_zcl_cluster_get_attr_desc(const ezb_zcl_cluster_desc_t cluster_desc,
                                                  uint16_t                     attr_id,
                                                  uint16_t                     manuf_code);

/**
 * @brief Create a Zigbee attribute descriptor.
 *
 * This function allocates and initializes a new attribute descriptor structure.
 *
 * @param[in] id         The attribute identifier.
 * @param[in] type       The attribute type.
 * @param[in] access     The attribute access control.
 * @param[in] manuf_code The manufacturer code if manufacturer-specific.
 * @param[in] data_p     The pointer to the attribute data.
 * @return The created attribute descriptor, or @ref EZB_INVALID_ZCL_ATTR_DESC if failed.
 */
ezb_zcl_attr_desc_t ezb_zcl_create_attr_desc(uint16_t    id,
                                             uint8_t     type,
                                             uint8_t     access,
                                             uint16_t    manuf_code,
                                             const void *data_p);

/**
 * @brief Free a Zigbee attribute descriptor.
 *
 * This function frees the memory allocated for a attribute descriptor.
 *
 * @param[in] attr_desc The attribute descriptor to free.
 */
void ezb_zcl_free_attr_desc(ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Add an attribute descriptor to a Zigbee cluster descriptor.
 *
 * @param[in] cluster_desc The cluster descriptor.
 * @param[in] attr_desc    The attribute descriptor to be added to @p cluster_desc.
 * @return The error code. See @ref ezb_err_t.
 */
ezb_err_t ezb_zcl_cluster_add_attr_desc(ezb_zcl_cluster_desc_t cluster_desc, ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Remove an attribute descriptor from a Zigbee cluster descriptor.
 *
 * @param[in] cluster_desc The cluster descriptor.
 * @param[in] attr_id      The attribute identifier is used to identify the attribute to remove.
 * @param[in] manuf_code   The manufacturer code is used to identify the manufacturer of the attribute to remove.
 * @return The removed attribute descriptor, or @ref EZB_INVALID_ZCL_ATTR_DESC if not found.
 */
ezb_zcl_attr_desc_t ezb_zcl_cluster_remove_attr_desc(ezb_zcl_cluster_desc_t cluster_desc,
                                                     uint16_t               attr_id,
                                                     uint16_t               manuf_code);

/**
 * @brief Add a manufacturer-specific attribute to a Zigbee cluster descriptor.
 *
 * @param[in] cluster_desc The cluster descriptor.
 * @param[in] attr_id      The identifier of the attribute.
 * @param[in] attr_type    The type of the attribute. See @ref ezb_zcl_attr_type_t.
 * @param[in] attr_access  The access control flags of the attribute. See @ref ezb_zcl_attr_access_t.
 * @param[in] manuf_code   The manufacturer code for the attribute.
 * @param[in] value        The pointer to the attribute value.
 * @return The error code. See @ref ezb_err_t.
 */
ezb_err_t ezb_zcl_cluster_desc_add_manuf_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                              uint16_t               attr_id,
                                              uint8_t                attr_type,
                                              uint8_t                attr_access,
                                              uint16_t               manuf_code,
                                              const void            *value);

/**
 * @brief Get the next attribute descriptor in a Zigbee cluster descriptor.
 *
 * @param[in] cluster_desc The cluster descriptor to search in.
 * @param[in] attr_desc    The attribute descriptor to start the search from.
 * @return The next attribute descriptor, or @ref EZB_INVALID_ZCL_ATTR_DESC if no more attributes are found.
 */
ezb_zcl_attr_desc_t ezb_zcl_cluster_get_next_attr_desc(const ezb_zcl_cluster_desc_t cluster_desc,
                                                       const ezb_zcl_attr_desc_t    attr_desc);

#ifdef __cplusplus
} /*  extern "C" */
#endif
