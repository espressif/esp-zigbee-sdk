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
   ON_OFF Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the on_off cluster implementation */
#define EZB_ZCL_ON_OFF_CLUSTER_REVISION (2)

/**
 * @brief Attribute identifiers for the on_off server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_ON_OFF_ON_OFF_ID               = 0x0000U, /*!< OnOff attribute. */
    EZB_ZCL_ATTR_ON_OFF_GLOBAL_SCENE_CONTROL_ID = 0x4000U, /*!< GlobalSceneControl attribute. */
    EZB_ZCL_ATTR_ON_OFF_ON_TIME_ID              = 0x4001U, /*!< OnTime attribute. */
    EZB_ZCL_ATTR_ON_OFF_OFF_WAIT_TIME_ID        = 0x4002U, /*!< OffWaitTime attribute. */
    EZB_ZCL_ATTR_ON_OFF_START_UP_ON_OFF_ID      = 0x4003U, /*!< StartUpOnOff attribute. */
    EZB_ZCL_ATTR_ON_OFF_ON_OFF_TIMER_CONTEXT_ID = 0xeff0U, /*!< OnOffTimerContext attribute. */
} ezb_zcl_on_off_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the OnOff server cluster.
 */
typedef struct ezb_zcl_on_off_cluster_server_config_s {
    bool on_off; /*!< Configurable mandatory OnOff attribute */
} ezb_zcl_on_off_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL StartUpOnOff attribute of OnOff.
 */
typedef enum {
    EZB_ZCL_ON_OFF_START_UP_ON_OFF_SET_ON_OFF_TO_OFF      = 0x00U, /*!< SetOnOffToOff */
    EZB_ZCL_ON_OFF_START_UP_ON_OFF_SET_ON_OFF_TO_ON       = 0x01U, /*!< SetOnOffToOn */
    EZB_ZCL_ON_OFF_START_UP_ON_OFF_TOGGLE_PREVIOUS_ON_OFF = 0x02U, /*!< TogglePreviousOnOff */
    EZB_ZCL_ON_OFF_START_UP_ON_OFF_SET_PREVIOUS_ON_OFF    = 0xffU, /*!< SetPreviousOnOff */
} ezb_zcl_on_off_server_start_up_on_off_t;

/** @brief Default value of OnOff in OnOff cluster */
#define EZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE (0x00)

/** @brief Minimum value of OnOff in OnOff cluster */
#define EZB_ZCL_ON_OFF_ON_OFF_MIN_VALUE (0x00)

/** @brief Maximum value of OnOff in OnOff cluster */
#define EZB_ZCL_ON_OFF_ON_OFF_MAX_VALUE (0x01)
/** @brief Default value of GlobalSceneControl in OnOff cluster */
#define EZB_ZCL_ON_OFF_GLOBAL_SCENE_CONTROL_DEFAULT_VALUE (0x01)

/** @brief Minimum value of GlobalSceneControl in OnOff cluster */
#define EZB_ZCL_ON_OFF_GLOBAL_SCENE_CONTROL_MIN_VALUE (0x00)

/** @brief Maximum value of GlobalSceneControl in OnOff cluster */
#define EZB_ZCL_ON_OFF_GLOBAL_SCENE_CONTROL_MAX_VALUE (0x01)
/** @brief Default value of OnTime in OnOff cluster */
#define EZB_ZCL_ON_OFF_ON_TIME_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of OnTime in OnOff cluster */
#define EZB_ZCL_ON_OFF_ON_TIME_MIN_VALUE (0x0000)

/** @brief Maximum value of OnTime in OnOff cluster */
#define EZB_ZCL_ON_OFF_ON_TIME_MAX_VALUE (0xffff)
/** @brief Default value of OffWaitTime in OnOff cluster */
#define EZB_ZCL_ON_OFF_OFF_WAIT_TIME_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of OffWaitTime in OnOff cluster */
#define EZB_ZCL_ON_OFF_OFF_WAIT_TIME_MIN_VALUE (0x0000)

/** @brief Maximum value of OffWaitTime in OnOff cluster */
#define EZB_ZCL_ON_OFF_OFF_WAIT_TIME_MAX_VALUE (0xffff)
/** @brief Default value of StartUpOnOff in OnOff cluster */
#define EZB_ZCL_ON_OFF_START_UP_ON_OFF_DEFAULT_VALUE (0x00)

/**
 * @brief Received Command identifiers for the OnOff cluster.
 */
typedef enum {
    EZB_ZCL_CMD_ON_OFF_OFF_ID                         = 0x00U, /*!< Off command. */
    EZB_ZCL_CMD_ON_OFF_ON_ID                          = 0x01U, /*!< On command. */
    EZB_ZCL_CMD_ON_OFF_TOGGLE_ID                      = 0x02U, /*!< Toggle command. */
    EZB_ZCL_CMD_ON_OFF_OFF_WITH_EFFECT_ID             = 0x40U, /*!< OffWithEffect command. */
    EZB_ZCL_CMD_ON_OFF_ON_WITH_RECALL_GLOBAL_SCENE_ID = 0x41U, /*!< OnWithRecallGlobalScene command. */
    EZB_ZCL_CMD_ON_OFF_ON_WITH_TIMED_OFF_ID           = 0x42U, /*!< OnWithTimedOff command. */
} ezb_zcl_on_off_server_cmd_id_t;

typedef ezb_zcl_on_off_cluster_server_config_t ezb_zcl_on_off_cluster_config_t;

/**
 * @brief Add an attribute to an on_off cluster descriptor.
 *
 * @param cluster_desc Pointer to the on_off cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_on_off_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an on_off cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the on_off cluster configuration structure, refer to ezb_zcl_on_off_cluster_server_config_t or
 * ezb_zcl_on_off_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_on_off_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the OnOff cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_on_off_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the OnOff cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_on_off_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_ON_OFF_CLIENT_ROLE_INIT ezb_zcl_on_off_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_ON_OFF_SERVER_ROLE_INIT ezb_zcl_on_off_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
