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
 * @param cluster_desc Pointer to the touchlink_commissioning cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_touchlink_commissioning_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                                uint16_t               attr_id,
                                                                const void            *value);

/**
 * @brief Create an touchlink_commissioning cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the touchlink_commissioning cluster configuration structure, refer to
 * ezb_zcl_touchlink_commissioning_cluster_server_config_t or ezb_zcl_touchlink_commissioning_cluster_client_config_t or NULL
 * (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_touchlink_commissioning_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the TouchlinkCommissioning cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_touchlink_commissioning_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the TouchlinkCommissioning cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_touchlink_commissioning_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_TOUCHLINK_COMMISSIONING_CLIENT_ROLE_INIT ezb_zcl_touchlink_commissioning_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_TOUCHLINK_COMMISSIONING_SERVER_ROLE_INIT ezb_zcl_touchlink_commissioning_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
