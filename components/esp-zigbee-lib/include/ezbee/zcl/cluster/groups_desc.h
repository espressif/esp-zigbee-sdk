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
   GROUPS Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the groups cluster implementation */
#define EZB_ZCL_GROUPS_CLUSTER_REVISION (3)

/**
 * @brief Attribute identifiers for the groups server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_GROUPS_NAME_SUPPORT_ID = 0x0000U, /*!< NameSupport attribute. */
} ezb_zcl_groups_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the Groups server cluster.
 */
typedef struct ezb_zcl_groups_cluster_server_config_s {
    uint8_t name_support; /*!< Configurable mandatory NameSupport attribute */
} ezb_zcl_groups_cluster_server_config_t;

/**
 * @brief Bitmap for ZCL NameSupport attribute of Groups.
 */
typedef enum {
    EZB_ZCL_GROUPS_NAME_SUPPORT_SUPPORTED = 0x80U, /*!< Supported */
} ezb_zcl_groups_server_name_support_t;

/** @brief Default value of NameSupport in Groups cluster */
#define EZB_ZCL_GROUPS_NAME_SUPPORT_DEFAULT_VALUE (0x00)

/**
 * @brief Received Command identifiers for the Groups cluster.
 */
typedef enum {
    EZB_ZCL_CMD_GROUPS_ADD_GROUP_ID                = 0x00U, /*!< AddGroup command. */
    EZB_ZCL_CMD_GROUPS_VIEW_GROUP_ID               = 0x01U, /*!< ViewGroup command. */
    EZB_ZCL_CMD_GROUPS_GET_GROUP_MEMBERSHIP_ID     = 0x02U, /*!< GetGroupMembership command. */
    EZB_ZCL_CMD_GROUPS_REMOVE_GROUP_ID             = 0x03U, /*!< RemoveGroup command. */
    EZB_ZCL_CMD_GROUPS_REMOVE_ALL_GROUPS_ID        = 0x04U, /*!< RemoveAllGroups command. */
    EZB_ZCL_CMD_GROUPS_ADD_GROUP_IF_IDENTIFYING_ID = 0x05U, /*!< AddGroupIfIdentifying command. */
} ezb_zcl_groups_server_cmd_id_t;

/**
 * @brief Received Command identifiers for the Groups cluster.
 */
typedef enum {
    EZB_ZCL_CMD_GROUPS_ADD_GROUP_RESPONSE_ID            = 0x00U, /*!< AddGroupResponse command. */
    EZB_ZCL_CMD_GROUPS_VIEW_GROUP_RESPONSE_ID           = 0x01U, /*!< ViewGroupResponse command. */
    EZB_ZCL_CMD_GROUPS_GET_GROUP_MEMBERSHIP_RESPONSE_ID = 0x02U, /*!< GetGroupMembershipResponse command. */
    EZB_ZCL_CMD_GROUPS_REMOVE_GROUP_RESPONSE_ID         = 0x03U, /*!< RemoveGroupResponse command. */
} ezb_zcl_groups_client_cmd_id_t;

typedef ezb_zcl_groups_cluster_server_config_t ezb_zcl_groups_cluster_config_t;

/**
 * @brief Add an attribute to an groups cluster descriptor.
 *
 * @param cluster_desc Pointer to the groups cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_groups_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an groups cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the groups cluster configuration structure, refer to ezb_zcl_groups_cluster_server_config_t or
 * ezb_zcl_groups_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_groups_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the Groups cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_groups_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the Groups cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_groups_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_GROUPS_CLIENT_ROLE_INIT ezb_zcl_groups_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_GROUPS_SERVER_ROLE_INIT ezb_zcl_groups_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
