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
   IDENTIFY Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the identify cluster implementation */
#define EZB_ZCL_IDENTIFY_CLUSTER_REVISION (2)

/**
 * @brief Attribute identifiers for the identify server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_IDENTIFY_IDENTIFY_TIME_ID          = 0x0000U, /*!< IdentifyTime attribute. */
    EZB_ZCL_ATTR_IDENTIFY_IDENTIFY_TIMER_CONTEXT_ID = 0xeff0U, /*!< IdentifyTimerContext attribute. */
} ezb_zcl_identify_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the Identify server cluster.
 */
typedef struct ezb_zcl_identify_cluster_server_config_s {
    uint16_t identify_time; /*!< Configurable mandatory IdentifyTime attribute */
} ezb_zcl_identify_cluster_server_config_t;

/** @brief Default value of IdentifyTime in Identify cluster */
#define EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of IdentifyTime in Identify cluster */
#define EZB_ZCL_IDENTIFY_IDENTIFY_TIME_MIN_VALUE (0x0000)

/** @brief Maximum value of IdentifyTime in Identify cluster */
#define EZB_ZCL_IDENTIFY_IDENTIFY_TIME_MAX_VALUE (0xffff)

/**
 * @brief Received Command identifiers for the Identify cluster.
 */
typedef enum {
    EZB_ZCL_CMD_IDENTIFY_IDENTIFY_ID       = 0x00U, /*!< Identify command. */
    EZB_ZCL_CMD_IDENTIFY_IDENTIFY_QUERY_ID = 0x01U, /*!< IdentifyQuery command. */
    EZB_ZCL_CMD_IDENTIFY_TRIGGER_EFFECT_ID = 0x40U, /*!< TriggerEffect command. */
} ezb_zcl_identify_server_cmd_id_t;

/**
 * @brief Received Command identifiers for the Identify cluster.
 */
typedef enum {
    EZB_ZCL_CMD_IDENTIFY_IDENTIFY_QUERY_RESPONSE_ID = 0x00U, /*!< IdentifyQueryResponse command. */
} ezb_zcl_identify_client_cmd_id_t;

typedef ezb_zcl_identify_cluster_server_config_t ezb_zcl_identify_cluster_config_t;

/**
 * @brief Add an attribute to an identify cluster descriptor.
 *
 * @param cluster_desc Pointer to the identify cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_identify_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an identify cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the identify cluster configuration structure, refer to
 * ezb_zcl_identify_cluster_server_config_t or ezb_zcl_identify_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_identify_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the Identify cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_identify_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the Identify cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_identify_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_IDENTIFY_CLIENT_ROLE_INIT ezb_zcl_identify_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_IDENTIFY_SERVER_ROLE_INIT ezb_zcl_identify_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
