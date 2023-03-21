/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_type.h"

/** @brief Identify cluster attribute identifier
*/
typedef enum {
    ESP_ZB_ZCL_ATTR_IDENTIFY_IDENTIFY_TIME_ID = 0x0000  /*!< Identify time attribute */
} esp_zb_zcl_identify_attr_t;

/** @brief Default value for Identify attribute */
#define ESP_ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE 0x0000

/** @brief Command identifiers for "Identify" cluster
*/
typedef enum {
    ESP_ZB_ZCL_CMD_IDENTIFY_IDENTIFY_ID           = 0x00,  /*!< Identify command */
    ESP_ZB_ZCL_CMD_IDENTIFY_IDENTIFY_QUERY_ID     = 0x01,  /*!< Identify query command */
    ESP_ZB_ZCL_CMD_IDENTIFY_TRIGGER_EFFECT_ID     = 0x40,  /*!< "Trigger effect" command identifier. */
    ESP_ZB_ZCL_CMD_IDENTIFY_IDENTIFY_QUERY_RSP_ID = 0x00   /*!< Identify query response */
} esp_zb_zcl_identify_cmd_id_t;

#ifdef __cplusplus
}
#endif
