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
   IAS_WD Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the ias_wd cluster implementation */
#define EZB_ZCL_IAS_WD_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the ias_wd server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_IAS_WD_MAX_DURATION_ID = 0x0000U, /*!< MaxDuration attribute. */
} ezb_zcl_ias_wd_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the IasWd server cluster.
 */
typedef struct ezb_zcl_ias_wd_cluster_server_config_s {
    uint16_t max_duration; /*!< Configurable mandatory MaxDuration attribute */
} ezb_zcl_ias_wd_cluster_server_config_t;

/** @brief Default value of MaxDuration in IasWd cluster */
#define EZB_ZCL_IAS_WD_MAX_DURATION_DEFAULT_VALUE (0x00f0)

/** @brief Minimum value of MaxDuration in IasWd cluster */
#define EZB_ZCL_IAS_WD_MAX_DURATION_MIN_VALUE (0x0000)

/** @brief Maximum value of MaxDuration in IasWd cluster */
#define EZB_ZCL_IAS_WD_MAX_DURATION_MAX_VALUE (0xfffe)

/**
 * @brief Received Command identifiers for the IasWd cluster.
 */
typedef enum {
    EZB_ZCL_CMD_IAS_WD_START_WARNING_ID = 0x00U, /*!< StartWarning command. */
    EZB_ZCL_CMD_IAS_WD_SQUAWK_ID        = 0x01U, /*!< Squawk command. */
} ezb_zcl_ias_wd_server_cmd_id_t;

typedef ezb_zcl_ias_wd_cluster_server_config_t ezb_zcl_ias_wd_cluster_config_t;

/**
 * @brief Add an attribute to an ias_wd cluster descriptor.
 *
 * @param[in] cluster_desc The ias_wd cluster descriptor.
 * @param[in] attr_id      The identifier of the attribute to be added to @p cluster_desc.
 * @param[in] value        The pointer to the initial value of the attribute.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_wd_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an ias_wd cluster descriptor.
 *
 * @param[in] cluster_cfg  The pointer to the ias_wd cluster configuration structure.
                           Use ezb_zcl_ias_wd_cluster_server_config_t for EZB_ZCL_CLUSTER_SERVER,
                           use ezb_zcl_ias_wd_cluster_client_config_t for EZB_ZCL_CLUSTER_CLIENT,
                           or use NULL for default configuration of the stack based on the @p role_mask.
 * @param[in] role_mask    The role of the cluster to create.
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_ias_wd_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the IasWd cluster client role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs initialization.
 */
void ezb_zcl_ias_wd_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the IasWd cluster server role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs de-initialization.
 */
void ezb_zcl_ias_wd_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_IAS_WD_CLIENT_ROLE_INIT ezb_zcl_ias_wd_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_IAS_WD_SERVER_ROLE_INIT ezb_zcl_ias_wd_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
