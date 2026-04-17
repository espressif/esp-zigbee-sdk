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
   SCENES Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the scenes cluster implementation */
#define EZB_ZCL_SCENES_CLUSTER_REVISION (3)

/**
 * @brief Attribute identifiers for the scenes server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_SCENES_SCENE_COUNT_ID        = 0x0000U, /*!< SceneCount attribute. */
    EZB_ZCL_ATTR_SCENES_CURRENT_SCENE_ID      = 0x0001U, /*!< CurrentScene attribute. */
    EZB_ZCL_ATTR_SCENES_CURRENT_GROUP_ID      = 0x0002U, /*!< CurrentGroup attribute. */
    EZB_ZCL_ATTR_SCENES_SCENE_VALID_ID        = 0x0003U, /*!< SceneValid attribute. */
    EZB_ZCL_ATTR_SCENES_NAME_SUPPORT_ID       = 0x0004U, /*!< NameSupport attribute. */
    EZB_ZCL_ATTR_SCENES_LAST_CONFIGURED_BY_ID = 0x0005U, /*!< LastConfiguredBy attribute. */
    EZB_ZCL_ATTR_SCENES_SCENE_TABLE_SIZE_ID   = 0xeff0U, /*!< SceneTableSize attribute. */
    EZB_ZCL_ATTR_SCENES_SCENE_TABLE_ID        = 0xeff1U, /*!< SceneTable attribute. */
} ezb_zcl_scenes_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the Scenes server cluster.
 */
typedef struct ezb_zcl_scenes_cluster_server_config_s {
    uint8_t  scene_count;      /*!< Configurable mandatory SceneCount attribute */
    uint8_t  current_scene;    /*!< Configurable mandatory CurrentScene attribute */
    uint16_t current_group;    /*!< Configurable mandatory CurrentGroup attribute */
    bool     scene_valid;      /*!< Configurable mandatory SceneValid attribute */
    uint8_t  name_support;     /*!< Configurable mandatory NameSupport attribute */
    uint8_t  scene_table_size; /*!< Configurable mandatory SceneTableSize attribute */
} ezb_zcl_scenes_cluster_server_config_t;

/**
 * @brief Bitmap for ZCL NameSupport attribute of Scenes.
 */
typedef enum {
    EZB_ZCL_SCENES_NAME_SUPPORT_SCENE_NAMES_SUPPORTED = 8U, /*!< SceneNamesSupported */
} ezb_zcl_scenes_server_name_support_t;

/** @brief Default value of SceneCount in Scenes cluster */
#define EZB_ZCL_SCENES_SCENE_COUNT_DEFAULT_VALUE (0x00)

/** @brief Default value of CurrentScene in Scenes cluster */
#define EZB_ZCL_SCENES_CURRENT_SCENE_DEFAULT_VALUE (0x00)

/** @brief Default value of CurrentGroup in Scenes cluster */
#define EZB_ZCL_SCENES_CURRENT_GROUP_DEFAULT_VALUE (0x0000)

/** @brief Default value of SceneValid in Scenes cluster */
#define EZB_ZCL_SCENES_SCENE_VALID_DEFAULT_VALUE (false)

/** @brief Default value of NameSupport in Scenes cluster */
#define EZB_ZCL_SCENES_NAME_SUPPORT_DEFAULT_VALUE (0x00)

/** @brief Default value of SceneTableSize in Scenes cluster */
#define EZB_ZCL_SCENES_SCENE_TABLE_SIZE_DEFAULT_VALUE (0x0f)

/** @brief Minimum value of SceneTableSize in Scenes cluster */
#define EZB_ZCL_SCENES_SCENE_TABLE_SIZE_MIN_VALUE (0x01)

/** @brief Maximum value of SceneTableSize in Scenes cluster */
#define EZB_ZCL_SCENES_SCENE_TABLE_SIZE_MAX_VALUE (0xff)

/**
 * @brief Received Command identifiers for the Scenes cluster.
 */
typedef enum {
    EZB_ZCL_CMD_SCENES_ADD_SCENE_ID            = 0x00U, /*!< AddScene command. */
    EZB_ZCL_CMD_SCENES_VIEW_SCENE_ID           = 0x01U, /*!< ViewScene command. */
    EZB_ZCL_CMD_SCENES_REMOVE_SCENE_ID         = 0x02U, /*!< RemoveScene command. */
    EZB_ZCL_CMD_SCENES_REMOVE_ALL_SCENES_ID    = 0x03U, /*!< RemoveAllScenes command. */
    EZB_ZCL_CMD_SCENES_STORE_SCENE_ID          = 0x04U, /*!< StoreScene command. */
    EZB_ZCL_CMD_SCENES_RECALL_SCENE_ID         = 0x05U, /*!< RecallScene command. */
    EZB_ZCL_CMD_SCENES_GET_SCENE_MEMBERSHIP_ID = 0x06U, /*!< GetSceneMembership command. */
    EZB_ZCL_CMD_SCENES_ENHANCED_ADD_SCENE_ID   = 0x40U, /*!< EnhancedAddScene command. */
    EZB_ZCL_CMD_SCENES_ENHANCED_VIEW_SCENE_ID  = 0x41U, /*!< EnhancedViewScene command. */
    EZB_ZCL_CMD_SCENES_COPY_SCENE_ID           = 0x42U, /*!< CopyScene command. */
} ezb_zcl_scenes_server_cmd_id_t;

/**
 * @brief Received Command identifiers for the Scenes cluster.
 */
typedef enum {
    EZB_ZCL_CMD_SCENES_ADD_SCENE_RESPONSE_ID            = 0x00U, /*!< AddSceneResponse command. */
    EZB_ZCL_CMD_SCENES_VIEW_SCENE_RESPONSE_ID           = 0x01U, /*!< ViewSceneResponse command. */
    EZB_ZCL_CMD_SCENES_REMOVE_SCENE_RESPONSE_ID         = 0x02U, /*!< RemoveSceneResponse command. */
    EZB_ZCL_CMD_SCENES_REMOVE_ALL_SCENES_RESPONSE_ID    = 0x03U, /*!< RemoveAllScenesResponse command. */
    EZB_ZCL_CMD_SCENES_STORE_SCENE_RESPONSE_ID          = 0x04U, /*!< StoreSceneResponse command. */
    EZB_ZCL_CMD_SCENES_GET_SCENE_MEMBERSHIP_RESPONSE_ID = 0x06U, /*!< GetSceneMembershipResponse command. */
    EZB_ZCL_CMD_SCENES_ENHANCED_ADD_SCENE_RESPONSE_ID   = 0x40U, /*!< EnhancedAddSceneResponse command. */
    EZB_ZCL_CMD_SCENES_ENHANCED_VIEW_SCENE_RESPONSE_ID  = 0x41U, /*!< EnhancedViewSceneResponse command. */
    EZB_ZCL_CMD_SCENES_COPY_SCENE_RESPONSE_ID           = 0x42U, /*!< CopySceneResponse command. */
} ezb_zcl_scenes_client_cmd_id_t;

typedef ezb_zcl_scenes_cluster_server_config_t ezb_zcl_scenes_cluster_config_t;

/**
 * @brief Add an attribute to an scenes cluster descriptor.
 *
 * @param cluster_desc Pointer to the scenes cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_scenes_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an scenes cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the scenes cluster configuration structure, refer to ezb_zcl_scenes_cluster_server_config_t or
 * ezb_zcl_scenes_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_scenes_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the Scenes cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_scenes_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the Scenes cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_scenes_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_SCENES_CLIENT_ROLE_INIT ezb_zcl_scenes_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_SCENES_SERVER_ROLE_INIT ezb_zcl_scenes_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
