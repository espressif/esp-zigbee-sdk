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

/** @brief Temperature Measurement cluster attribute identifiers
*/
typedef enum {
    ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_VALUE_ID         = 0x0000,  /*!< MeasuredValue */
    ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_MIN_VALUE_ID     = 0x0001,  /*!< MinMeasuredValue*/
    ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_MAX_VALUE_ID     = 0x0002,  /*!< MaxMeasuredValue */
    ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_TOLERANCE_ID     = 0x0003,  /*!< Tolerance */
} esp_zb_zcl_temp_measurement_attr_t;

/** @brief Default value for Value attribute */
#define ESP_ZB_ZCL_TEMP_MEASUREMENT_VALUE_DEFAULT_VALUE ((int16_t)0x8000)

/** @brief Default value for MinValue attribute */
#define ESP_ZB_ZCL_TEMP_MEASUREMENT_MIN_VALUE_DEFAULT_VALUE ((int16_t)0x8000)

/** @brief Default value for MaxValue attribute */
#define ESP_ZB_ZCL_TEMP_MEASUREMENT_MAX_VALUE_DEFAULT_VALUE ((int16_t)0x8000)

#define ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_VALUE_UNKNOWN ESP_ZB_ZCL_TEMP_MEASUREMENT_VALUE_DEFAULT_VALUE

#define ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_MIN_VALUE_INVALID ESP_ZB_ZCL_TEMP_MEASUREMENT_MIN_VALUE_DEFAULT_VALUE

#define ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_MAX_VALUE_INVALID ESP_ZB_ZCL_TEMP_MEASUREMENT_MAX_VALUE_DEFAULT_VALUE

#ifdef __cplusplus
}
#endif
