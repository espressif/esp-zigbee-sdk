/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_type.h"

/** @brief Flow measurement cluster attribute identifiers */
typedef enum {
    ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_VALUE_ID        = 0x0000, /*!< MeasuredValue attribute */
    ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_MIN_VALUE_ID    = 0x0001, /*!< MinMeasuredValue attribute */
    ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_MAX_VALUE_ID    = 0x0002, /*!< MaxMeasuredValue attribute */
    ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_TOLERANCE_ID    = 0x0003, /*!< Tolerance attribute */
} esp_zb_zcl_flow_measurement_attr_t;

/** @brief MeasuredValue attribute unknown value */
#define ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_VALUE_UNKNOWN                  ((uint16_t)0xffff)

/** @brief MinMeasuredValue attribute minimum value */
#define ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_MIN_VALUE_MIN_VALUE            ((uint16_t)0x0000)

/** @brief MinMeasuredValue attribute maximum value */
#define ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_MIN_VALUE_MAX_VALUE            ((uint16_t)0xfffd)

/** @brief MinMeasuredValue attribute invalid value */
#define ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_MIN_VALUE_INVALID              ((uint16_t)0xffff)

/** @brief MaxMeasuredValue attribute minimum value */
#define ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_MAX_VALUE_MIN_VALUE            ((uint16_t)0x0001)

/** @brief MaxMeasuredValue attribute maximum value */
#define ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_MAX_VALUE_MAX_VALUE            ((uint16_t)0xfffe)

/** @brief MaxMeasuredValue attribute invalid value */
#define ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_MAX_VALUE_INVALID              ((uint16_t)0xffff)

/** @brief Tolerance attribute minimum value */
#define ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_TOLERANCE_MIN_VALUE            ((uint16_t)0x0000)

/** @brief Tolerance attribute maximum value */
#define ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_TOLERANCE_MAX_VALUE            ((uint16_t)0x0800)

/** @brief Default value for MeasuredValue attribute */
#define ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_VALUE_DEFAULT_VALUE            ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_VALUE_UNKNOWN

/** @brief Default value for MinMeasuredValue attribute */
#define ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_MIN_VALUE_DEFAULT_VALUE        ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_MIN_VALUE_INVALID

/** @brief Default value for MaxMeasuredValue attribute */
#define ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_MAX_VALUE_DEFAULT_VALUE        ESP_ZB_ZCL_ATTR_FLOW_MEASUREMENT_MAX_VALUE_INVALID

void esp_zb_zcl_flow_measurement_init_server(void);
void esp_zb_zcl_flow_measurement_init_client(void);
#define ESP_ZB_ZCL_CLUSTER_ID_FLOW_MEASUREMENT_SERVER_ROLE_INIT esp_zb_zcl_flow_measurement_init_server
#define ESP_ZB_ZCL_CLUSTER_ID_FLOW_MEASUREMENT_CLIENT_ROLE_INIT esp_zb_zcl_flow_measurement_init_client

#ifdef __cplusplus
}
#endif
