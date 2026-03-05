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
 * @param ep_id      Endpoint ID.
 * @param cluster_id Cluster identifier.
 * @param role       Cluster role: @ref EZB_ZCL_CLUSTER_SERVER or @ref EZB_ZCL_CLUSTER_CLIENT.
 * @return Pointer to the cluster descriptor on success, NULL if cluster is not found.
 */
ezb_zcl_cluster_desc_t ezb_zcl_get_cluster_desc(uint8_t ep_id, uint16_t cluster_id, uint8_t role);

/**
 * @brief Free a Zigbee cluster descriptor.
 *
 * This function frees the memory allocated for a cluster descriptor and all associated attribute descriptors.
 *
 * @param cluster_desc Pointer to the cluster descriptor to free.
 */
void ezb_zcl_free_cluster_desc(ezb_zcl_cluster_desc_t cluster_desc);

/**
 * @brief Get the cluster ID of a Zigbee cluster descriptor.
 *
 * @param cluster_desc Pointer to the cluster descriptor. Must not be NULL.
 * @return The cluster ID, or 0xFFFF if cluster_desc is invalid.
 */
uint16_t ezb_zcl_cluster_desc_get_id(ezb_zcl_cluster_desc_t cluster_desc);

/**
 * @brief Get the cluster role of a Zigbee cluster descriptor.
 *
 * @param cluster_desc Pointer to the cluster descriptor. Must not be NULL.
 * @return The cluster role: @ref EZB_ZCL_CLUSTER_SERVER or @ref EZB_ZCL_CLUSTER_CLIENT, or 0xFF if invalid.
 */
uint8_t ezb_zcl_cluster_desc_get_role(ezb_zcl_cluster_desc_t cluster_desc);

/**
 * @brief Get the manufacturer code of a Zigbee cluster descriptor.
 *
 * @param cluster_desc Pointer to the cluster descriptor. Must not be NULL.
 * @return The manufacturer code.
 */
uint16_t ezb_zcl_cluster_desc_get_manuf_code(ezb_zcl_cluster_desc_t cluster_desc);

/**
 * @brief Get an attribute descriptor for a given endpoint, cluster, role, and attribute.
 *
 * This function searches for an attribute descriptor matching the specified criteria.
 * For manufacturer-specific attributes, the manuf_code must match exactly.
 *
 * @param ep_id      Endpoint ID.
 * @param cluster_id Cluster identifier.
 * @param role       Cluster role: @ref EZB_ZCL_CLUSTER_SERVER or @ref EZB_ZCL_CLUSTER_CLIENT.
 * @param attr_id    Attribute identifier.
 * @param manuf_code Manufacturer code. Use @ref EZB_ZCL_STD_MANUF_CODE for standard attributes.
 * @return Pointer to the attribute descriptor on success, NULL if attribute is not found.
 */
ezb_zcl_attr_desc_t ezb_zcl_get_attr_desc(uint8_t  ep_id,
                                          uint16_t cluster_id,
                                          uint8_t  role,
                                          uint16_t attr_id,
                                          uint16_t manuf_code);

/**
 * @brief Get the attribute ID of a Zigbee attribute descriptor.
 *
 * @param attr_desc Pointer to the attribute descriptor. Must not be NULL.
 * @return The attribute ID, or 0xFFFF if attr_desc is invalid.
 */
uint16_t ezb_zcl_attr_desc_get_id(ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Get the value size of a Zigbee attribute descriptor.
 *
 * @param attr_desc Pointer to the attribute descriptor.
 * @return The value size, or UINT16_MAX if attr_desc is invalid.
 */
uint16_t ezb_zcl_attr_desc_get_value_size(ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Get the value pointer of a Zigbee attribute descriptor.
 *
 * This function returns a pointer to the attribute's value buffer. The caller
 * should not modify this value directly; use ezb_zcl_set_attr_value() instead.
 *
 * @param[in] attr_desc Pointer to the attribute descriptor.
 * @param[out] value    Pointer to get the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_attr_desc_get_value(ezb_zcl_attr_desc_t attr_desc, void *value);

/**
 * @brief Get the data type of a Zigbee attribute descriptor.
 *
 * @param attr_desc Pointer to the attribute descriptor. Must not be NULL.
 * @return The attribute data type. See @ref ezb_zcl_attr_type_t..
 */
ezb_zcl_attr_type_t ezb_zcl_attr_desc_get_type(ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Get the access control flags of a Zigbee attribute descriptor.
 *
 * @param attr_desc Pointer to the attribute descriptor. Must not be NULL.
 * @return The access control flags. See @ref ezb_zcl_attr_access_t.
 *         Multiple flags can be combined with bitwise OR.
 */
ezb_zcl_attr_access_t ezb_zcl_attr_desc_get_access(ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Get the manufacturer code of a Zigbee attribute descriptor.
 *
 * @param attr_desc Pointer to the attribute descriptor. Must not be NULL.
 * @return The manufacturer code. Returns @ref EZB_ZCL_STD_MANUF_CODE if invalid.
 */
uint16_t ezb_zcl_attr_desc_get_manuf_code(ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Get an attribute descriptor from a cluster descriptor.
 *
 * @param cluster_desc Pointer to cluster descriptor.
 * @param attr_id      Attribute identifier.
 * @param manuf_code   Manufacturer code.
 * @return Pointer to the attribute descriptor, or NULL if not found.
 */
ezb_zcl_attr_desc_t ezb_zcl_cluster_get_attr_desc(const ezb_zcl_cluster_desc_t cluster_desc,
                                                  uint16_t                     attr_id,
                                                  uint16_t                     manuf_code);

/**
 * @brief Create a Zigbee attribute descriptor.
 *
 * This function allocates and initializes a new attribute descriptor structure.
 *
 * @param id         Attribute identifier.
 * @param type       Attribute data type.
 * @param access     Attribute access control.
 * @param manuf_code Manufacturer code if manufacturer-specific.
 * @param data_p     Pointer to attribute data.
 * @return Pointer to the created attribute descriptor, or NULL on failure.
 */
ezb_zcl_attr_desc_t ezb_zcl_create_attr_desc(uint16_t id, uint8_t type, uint8_t access, uint16_t manuf_code, const void *data_p);

/**
 * @brief Free a Zigbee attribute descriptor.
 *
 * This function frees the memory allocated for a attribute descriptor.
 *
 * @param attr_desc Pointer to the attribute descriptor to free.
 */
void ezb_zcl_free_attr_desc(ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Add an attribute descriptor to a Zigbee cluster descriptor.
 *
 * This function links an attribute descriptor to a cluster descriptor, allowing the cluster to manage multiple attributes.
 *
 * @param cluster_desc Pointer to the cluster descriptor.
 * @param attr_desc    Pointer to the attribute descriptor to add.
 * @return Error code.
 */
ezb_err_t ezb_zcl_cluster_add_attr_desc(ezb_zcl_cluster_desc_t cluster_desc, ezb_zcl_attr_desc_t attr_desc);

/**
 * @brief Add a manufacturer-specific attribute to a Zigbee cluster descriptor.
 *
 * @param cluster_desc Pointer to the cluster descriptor.
 * @param attr_id      Attribute identifier.
 * @param attr_type    Attribute type, See @ref ezb_zcl_attr_type_t.
 * @param attr_access  Attribute access, See @ref ezb_zcl_attr_access_t.
 * @param manuf_code   Manufacturer code for the attribute.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_cluster_desc_add_manuf_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                              uint16_t               attr_id,
                                              uint8_t                attr_type,
                                              uint8_t                attr_access,
                                              uint16_t               manuf_code,
                                              const void             *value);

/**
 * @brief Get the next attribute descriptor from a Zigbee cluster descriptor.
 *
 * @param cluster_desc Pointer to the cluster descriptor. Must not be NULL.
 * @param attr_desc    Pointer to the attribute descriptor. Must not be NULL.
 * @return Next attribute descriptor
 */
ezb_zcl_attr_desc_t ezb_zcl_cluster_get_next_attr_desc(const ezb_zcl_cluster_desc_t cluster_desc, const ezb_zcl_attr_desc_t attr_desc);

#ifdef __cplusplus
} /*  extern "C" */
#endif
