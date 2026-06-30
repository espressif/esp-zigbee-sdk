/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/zcl_common.h>
#include <ezbee/zcl/zcl_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------------------------------------------*
   TOUCHLINK_COMMISSIONING Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the touchlink_commissioning cluster implementation */
#define EZB_ZCL_TOUCHLINK_COMMISSIONING_CLUSTER_REVISION (3)

/**
 * @brief Received Command identifiers for the TouchlinkCommissioning cluster.
 */
typedef enum {
    EZB_ZCL_CMD_TOUCHLINK_COMMISSIONING_GET_GROUP_IDENTIFIERS_REQUEST_ID = 0x41U, /*!< GetGroupIdentifiersRequest command. */
    EZB_ZCL_CMD_TOUCHLINK_COMMISSIONING_GET_ENDPOINT_LIST_REQUEST_ID     = 0x42U, /*!< GetEndpointListRequest command. */
} ezb_zcl_touchlink_commissioning_server_cmd_id_t;

/**
 * @brief Received Command identifiers for the TouchlinkCommissioning cluster.
 */
typedef enum {
    EZB_ZCL_CMD_TOUCHLINK_COMMISSIONING_ENDPOINT_INFORMATION_ID           = 0x40U, /*!< EndpointInformation command. */
    EZB_ZCL_CMD_TOUCHLINK_COMMISSIONING_GET_GROUP_IDENTIFIERS_RESPONSE_ID = 0x41U, /*!< GetGroupIdentifiersResponse command. */
    EZB_ZCL_CMD_TOUCHLINK_COMMISSIONING_GET_ENDPOINT_LIST_RESPONSE_ID     = 0x42U, /*!< GetEndpointListResponse command. */
} ezb_zcl_touchlink_commissioning_client_cmd_id_t;

/**
 * @brief Cluster configuration for the TouchlinkCommissioning cluster.
 */
typedef struct ezb_zcl_touchlink_commissioning_cluster_config_s {
    int _unused; /*!< Unused. */
} ezb_zcl_touchlink_commissioning_cluster_config_t;

/**
 * @brief Add an attribute to an touchlink_commissioning cluster descriptor.
 *
 * @param[in] cluster_desc The touchlink_commissioning cluster descriptor.
 * @param[in] attr_id      The identifier of the attribute to be added to @p cluster_desc.
 * @param[in] value        The pointer to the initial value of the attribute.
 * @return Error code.
 */
ezb_err_t ezb_zcl_touchlink_commissioning_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                                uint16_t               attr_id,
                                                                const void            *value);

/**
 * @brief Create an touchlink_commissioning cluster descriptor.
 *
 * @param[in] cluster_cfg  The pointer to the touchlink_commissioning cluster configuration structure.
                           Use ezb_zcl_touchlink_commissioning_cluster_server_config_t for EZB_ZCL_CLUSTER_SERVER,
                           use ezb_zcl_touchlink_commissioning_cluster_client_config_t for EZB_ZCL_CLUSTER_CLIENT,
                           or use NULL for default configuration of the stack based on the @p role_mask.
 * @param[in] role_mask    The role of the cluster to create.
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_touchlink_commissioning_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the TouchlinkCommissioning cluster client role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs initialization.
 */
void ezb_zcl_touchlink_commissioning_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the TouchlinkCommissioning cluster server role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs de-initialization.
 */
void ezb_zcl_touchlink_commissioning_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_TOUCHLINK_COMMISSIONING_CLIENT_ROLE_INIT ezb_zcl_touchlink_commissioning_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_TOUCHLINK_COMMISSIONING_SERVER_ROLE_INIT ezb_zcl_touchlink_commissioning_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
