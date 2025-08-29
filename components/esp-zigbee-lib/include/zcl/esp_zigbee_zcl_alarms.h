/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "esp_zigbee_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Alarms cluster attribute identifiers */
typedef enum esp_zb_zcl_alarms_attr_e {
  ESP_ZB_ZCL_ATTR_ALARMS_ALARM_COUNT_ID      = 0x0000, /*!< AlarmCount attribute */
  ESP_ZB_ZCL_ATTR_ALARMS_ALARM_TABLE_SIZE_ID = 0xEFFE, /*!< Internal AlarmTable size attribute */
  ESP_ZB_ZCL_ATTR_ALARMS_ALARM_TABLE_ID      = 0xEFFF, /*!< Internal AlarmTable attribute */
} esp_zb_zcl_alarms_attr_t;

/** @brief Minimum value for AlarmCount attribute */
#define ESP_ZB_ZCL_ALARMS_ALARM_COUNT_MIN_VALUE      (0x0000)
/** @brief Maximum value for AlarmCount attribute */
#define ESP_ZB_ZCL_ALARMS_ALARM_COUNT_MAX_VALUE      (0x00FF)
/** @brief Default value for AlarmCount attribute */
#define ESP_ZB_ZCL_ALARMS_ALARM_COUNT_DEFAULT_VALUE  (0x0000)

/** @brief Default value for AlarmTableSize attribute */
#define ESP_ZB_ZCL_ALARMS_ALARM_TABLE_SIZE_DEFAULT_VALUE  (0x000F)

/** @brief Alarms cluster command identifiers */
typedef enum esp_zb_zcl_alarms_cmd_req_e {
  ESP_ZB_ZCL_CMD_ALARMS_RESET_ALARM_ID         = 0x00, /*!< Reset alarm command. */
  ESP_ZB_ZCL_CMD_ALARMS_RESET_ALL_ALARMS_ID    = 0x01, /*!< Reset all alarms command. */
  ESP_ZB_ZCL_CMD_ALARMS_GET_ALARM_ID           = 0x02, /*!< Get alarms command. */
  ESP_ZB_ZCL_CMD_ALARMS_RESET_ALARM_LOG_ID     = 0x03  /*!< Reset alarm log command. */
} esp_zb_zcl_alarms_cmd_req_t;

/** @brief Alarms cluster command identifiers */
typedef enum esp_zb_zcl_alarms_cmd_resp_e {
  ESP_ZB_ZCL_CMD_ALARMS_ALARM_ID             = 0x00, /*!< Alarm command. */
  ESP_ZB_ZCL_CMD_ALARMS_GET_ALARM_RESP_ID    = 0x01, /*!< Get alarm response command. */
} esp_zb_zcl_alarms_cmd_resp_t;

/**
 * @brief Alarm cluster server initialization
 * 
 */
void esp_zb_zcl_alarms_init_server(void);

/**
 * @brief Alarm cluster client initialization
 * 
 */
void esp_zb_zcl_alarms_init_client(void);

#define ESP_ZB_ZCL_CLUSTER_ID_ALARMS_SERVER_ROLE_INIT esp_zb_zcl_alarms_init_server
#define ESP_ZB_ZCL_CLUSTER_ID_ALARMS_CLIENT_ROLE_INIT esp_zb_zcl_alarms_init_client

#ifdef __cplusplus
}
#endif
