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
   IAS_ACE Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the ias_ace cluster implementation */
#define EZB_ZCL_IAS_ACE_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the ias_ace server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_IAS_ACE_ZONE_TABLE_SIZE_ID   = 0xeff0U, /*!< ZoneTableSize attribute. */
    EZB_ZCL_ATTR_IAS_ACE_ZONE_TABLE_HANDLE_ID = 0xeff1U, /*!< ZoneTableHandle attribute. */
} ezb_zcl_ias_ace_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the IasAce server cluster.
 */
typedef struct ezb_zcl_ias_ace_cluster_server_config_s {
    uint8_t zone_table_size; /*!< Configurable mandatory ZoneTableSize attribute */
} ezb_zcl_ias_ace_cluster_server_config_t;

/** @brief Default value of ZoneTableSize in IasAce cluster */
#define EZB_ZCL_IAS_ACE_ZONE_TABLE_SIZE_DEFAULT_VALUE (0xff)

/** @brief Minimum value of ZoneTableSize in IasAce cluster */
#define EZB_ZCL_IAS_ACE_ZONE_TABLE_SIZE_MIN_VALUE (0x00)

/** @brief Maximum value of ZoneTableSize in IasAce cluster */
#define EZB_ZCL_IAS_ACE_ZONE_TABLE_SIZE_MAX_VALUE (0xff)

/**
 * @brief Received Command identifiers for the IasAce cluster.
 */
typedef enum {
    EZB_ZCL_CMD_IAS_ACE_ARM_ID                    = 0x00U, /*!< Arm command. */
    EZB_ZCL_CMD_IAS_ACE_BYPASS_ID                 = 0x01U, /*!< Bypass command. */
    EZB_ZCL_CMD_IAS_ACE_EMERGENCY_ID              = 0x02U, /*!< Emergency command. */
    EZB_ZCL_CMD_IAS_ACE_FIRE_ID                   = 0x03U, /*!< Fire command. */
    EZB_ZCL_CMD_IAS_ACE_PANIC_ID                  = 0x04U, /*!< Panic command. */
    EZB_ZCL_CMD_IAS_ACE_GET_ZONE_ID_MAP_ID        = 0x05U, /*!< GetZoneIdMap command. */
    EZB_ZCL_CMD_IAS_ACE_GET_ZONE_INFO_ID          = 0x06U, /*!< GetZoneInfo command. */
    EZB_ZCL_CMD_IAS_ACE_GET_PANEL_STATUS_ID       = 0x07U, /*!< GetPanelStatus command. */
    EZB_ZCL_CMD_IAS_ACE_GET_BYPASSED_ZONE_LIST_ID = 0x08U, /*!< GetBypassedZoneList command. */
    EZB_ZCL_CMD_IAS_ACE_GET_ZONE_STATUS_ID        = 0x09U, /*!< GetZoneStatus command. */
} ezb_zcl_ias_ace_server_cmd_id_t;

/**
 * @brief Received Command identifiers for the IasAce cluster.
 */
typedef enum {
    EZB_ZCL_CMD_IAS_ACE_ARM_RESPONSE_ID                  = 0x00U, /*!< ArmResponse command. */
    EZB_ZCL_CMD_IAS_ACE_GET_ZONE_ID_MAP_RESPONSE_ID      = 0x01U, /*!< GetZoneIDMapResponse command. */
    EZB_ZCL_CMD_IAS_ACE_GET_ZONE_INFORMATION_RESPONSE_ID = 0x02U, /*!< GetZoneInformationResponse command. */
    EZB_ZCL_CMD_IAS_ACE_ZONE_STATUS_CHANGED_ID           = 0x03U, /*!< ZoneStatusChanged command. */
    EZB_ZCL_CMD_IAS_ACE_PANEL_STATUS_CHANGED_ID          = 0x04U, /*!< PanelStatusChanged command. */
    EZB_ZCL_CMD_IAS_ACE_GET_PANEL_STATUS_RESPONSE_ID     = 0x05U, /*!< GetPanelStatusResponse command. */
    EZB_ZCL_CMD_IAS_ACE_SET_BYPASSED_ZONE_LIST_ID        = 0x06U, /*!< SetBypassedZoneList command. */
    EZB_ZCL_CMD_IAS_ACE_BYPASS_RESPONSE_ID               = 0x07U, /*!< BypassResponse command. */
    EZB_ZCL_CMD_IAS_ACE_GET_ZONE_STATUS_RESPONSE_ID      = 0x08U, /*!< GetZoneStatusResponse command. */
} ezb_zcl_ias_ace_client_cmd_id_t;

typedef ezb_zcl_ias_ace_cluster_server_config_t ezb_zcl_ias_ace_cluster_config_t;

/**
 * @brief Add an attribute to an ias_ace cluster descriptor.
 *
 * @param cluster_desc Pointer to the ias_ace cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an ias_ace cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the ias_ace cluster configuration structure, refer to ezb_zcl_ias_ace_cluster_server_config_t
 * or ezb_zcl_ias_ace_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_ias_ace_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the IasAce cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_ias_ace_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the IasAce cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_ias_ace_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_IAS_ACE_CLIENT_ROLE_INIT ezb_zcl_ias_ace_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_IAS_ACE_SERVER_ROLE_INIT ezb_zcl_ias_ace_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
