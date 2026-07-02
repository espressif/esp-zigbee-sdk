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
   ALARMS Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the alarms cluster implementation */
#define EZB_ZCL_ALARMS_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the alarms server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_ALARMS_ALARM_COUNT_ID        = 0x0000U, /*!< AlarmCount attribute. */
    EZB_ZCL_ATTR_ALARMS_ALARM_TABLE_SIZE_ID   = 0xeffeU, /*!< AlarmTableSize attribute. */
    EZB_ZCL_ATTR_ALARMS_ALARM_TABLE_HANDLE_ID = 0xefffU, /*!< AlarmTableHandle attribute. */
} ezb_zcl_alarms_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the Alarms server cluster.
 */
typedef struct ezb_zcl_alarms_cluster_server_config_s {
    uint16_t alarm_table_size; /*!< Configurable mandatory AlarmTableSize attribute */
} ezb_zcl_alarms_cluster_server_config_t;

/** @brief Default value of AlarmCount in Alarms cluster */
#define EZB_ZCL_ALARMS_ALARM_COUNT_DEFAULT_VALUE (0x00000)

/** @brief Minimum value of AlarmCount in Alarms cluster */
#define EZB_ZCL_ALARMS_ALARM_COUNT_MIN_VALUE (0x0000)

/** @brief Maximum value of AlarmCount in Alarms cluster */
#define EZB_ZCL_ALARMS_ALARM_COUNT_MAX_VALUE (0x00ff)
/** @brief Default value of AlarmTableSize in Alarms cluster */
#define EZB_ZCL_ALARMS_ALARM_TABLE_SIZE_DEFAULT_VALUE (0x000f)

/**
 * @brief Received Command identifiers for the Alarms cluster.
 */
typedef enum {
    EZB_ZCL_CMD_ALARMS_RESET_ALARM_ID      = 0x00U, /*!< ResetAlarm command. */
    EZB_ZCL_CMD_ALARMS_RESET_ALL_ALARMS_ID = 0x01U, /*!< ResetAllAlarms command. */
    EZB_ZCL_CMD_ALARMS_GET_ALARM_ID        = 0x02U, /*!< GetAlarm command. */
    EZB_ZCL_CMD_ALARMS_RESET_ALARM_LOG_ID  = 0x03U, /*!< ResetAlarmLog command. */
} ezb_zcl_alarms_server_cmd_id_t;

/**
 * @brief Received Command identifiers for the Alarms cluster.
 */
typedef enum {
    EZB_ZCL_CMD_ALARMS_ALARM_ID              = 0x00U, /*!< Alarm command. */
    EZB_ZCL_CMD_ALARMS_GET_ALARM_RESPONSE_ID = 0x01U, /*!< GetAlarmResponse command. */
} ezb_zcl_alarms_client_cmd_id_t;

typedef ezb_zcl_alarms_cluster_server_config_t ezb_zcl_alarms_cluster_config_t;

/**
 * @brief Add an attribute to an alarms cluster descriptor.
 *
 * @param[in] cluster_desc The alarms cluster descriptor.
 * @param[in] attr_id      The identifier of the attribute to be added to @p cluster_desc.
 * @param[in] value        The pointer to the initial value of the attribute.
 * @return Error code.
 */
ezb_err_t ezb_zcl_alarms_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an alarms cluster descriptor.
 *
 * @param[in] cluster_cfg  The pointer to the alarms cluster configuration structure.
                           Use ezb_zcl_alarms_cluster_server_config_t for EZB_ZCL_CLUSTER_SERVER,
                           use ezb_zcl_alarms_cluster_client_config_t for EZB_ZCL_CLUSTER_CLIENT,
                           or use NULL for default configuration of the stack based on the @p role_mask.
 * @param[in] role_mask    The role of the cluster to create.
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_alarms_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the Alarms cluster client role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs initialization.
 */
void ezb_zcl_alarms_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the Alarms cluster server role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs de-initialization.
 */
void ezb_zcl_alarms_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_ALARMS_CLIENT_ROLE_INIT ezb_zcl_alarms_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_ALARMS_SERVER_ROLE_INIT ezb_zcl_alarms_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
