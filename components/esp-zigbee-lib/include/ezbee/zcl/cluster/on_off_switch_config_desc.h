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
   ON_OFF_SWITCH_CONFIG Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the on_off_switch_config cluster implementation */
#define EZB_ZCL_ON_OFF_SWITCH_CONFIG_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the on_off_switch_config server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_ON_OFF_SWITCH_CONFIG_SWITCH_TYPE_ID    = 0x0000U, /*!< SwitchType attribute. */
    EZB_ZCL_ATTR_ON_OFF_SWITCH_CONFIG_SWITCH_ACTIONS_ID = 0x0010U, /*!< SwitchActions attribute. */
} ezb_zcl_on_off_switch_config_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the OnOffSwitchConfig server cluster.
 */
typedef struct ezb_zcl_on_off_switch_config_cluster_server_config_s {
    uint8_t switch_type;    /*!< Configurable mandatory SwitchType attribute */
    uint8_t switch_actions; /*!< Configurable mandatory SwitchActions attribute */
} ezb_zcl_on_off_switch_config_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL SwitchType attribute of OnOffSwitchConfig.
 */
typedef enum {
    EZB_ZCL_ON_OFF_SWITCH_CONFIG_SWITCH_TYPE_TOGGLE        = 0x00U, /*!< Toggle */
    EZB_ZCL_ON_OFF_SWITCH_CONFIG_SWITCH_TYPE_MOMENTARY     = 0x01U, /*!< Momentary */
    EZB_ZCL_ON_OFF_SWITCH_CONFIG_SWITCH_TYPE_MULTIFUNCTION = 0x02U, /*!< Multifunction */
} ezb_zcl_on_off_switch_config_server_switch_type_t;

/**
 * @brief Enumeration for ZCL SwitchActions attribute of OnOffSwitchConfig.
 */
typedef enum {
    EZB_ZCL_ON_OFF_SWITCH_CONFIG_SWITCH_ACTIONS_ON     = 0x00U, /*!< On */
    EZB_ZCL_ON_OFF_SWITCH_CONFIG_SWITCH_ACTIONS_OFF    = 0x01U, /*!< Off */
    EZB_ZCL_ON_OFF_SWITCH_CONFIG_SWITCH_ACTIONS_TOGGLE = 0x02U, /*!< Toggle */
} ezb_zcl_on_off_switch_config_server_switch_actions_t;

/** @brief Default value of SwitchActions in OnOffSwitchConfig cluster */
#define EZB_ZCL_ON_OFF_SWITCH_CONFIG_SWITCH_ACTIONS_DEFAULT_VALUE (0x00)

typedef ezb_zcl_on_off_switch_config_cluster_server_config_t ezb_zcl_on_off_switch_config_cluster_config_t;

/**
 * @brief Add an attribute to an on_off_switch_config cluster descriptor.
 *
 * @param cluster_desc Pointer to the on_off_switch_config cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_on_off_switch_config_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                             uint16_t               attr_id,
                                                             const void            *value);

/**
 * @brief Create an on_off_switch_config cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the on_off_switch_config cluster configuration structure, refer to
 * ezb_zcl_on_off_switch_config_cluster_server_config_t or ezb_zcl_on_off_switch_config_cluster_client_config_t or NULL (default
 * config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_on_off_switch_config_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the OnOffSwitchConfig cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_on_off_switch_config_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the OnOffSwitchConfig cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_on_off_switch_config_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_ON_OFF_SWITCH_CONFIG_CLIENT_ROLE_INIT ezb_zcl_on_off_switch_config_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_ON_OFF_SWITCH_CONFIG_SERVER_ROLE_INIT ezb_zcl_on_off_switch_config_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
