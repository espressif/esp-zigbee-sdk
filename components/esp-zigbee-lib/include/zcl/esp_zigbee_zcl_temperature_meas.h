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
    ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_VALUE_ID         = 0x0000,  /*!< @brief MeasuredValue, ZCL spec 4.4.2.2.1.1 */
    ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_MIN_VALUE_ID     = 0x0001,  /*!< @brief MinMeasuredValue, ZCL spec 4.4.2.2.1.2 */
    ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_MAX_VALUE_ID     = 0x0002,  /*!< @brief MaxMeasuredValue, ZCL spec 4.4.2.2.1.3 */
    ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_TOLERANCE_ID     = 0x0003,  /*!< @brief Tolerance, ZCL spec 4.4.2.2.1.4 */
} esp_zb_zcl_temp_measurement_attr_t;

/** @brief Default value for Value attribute */
#define ESP_ZB_ZCL_TEMP_MEASUREMENT_VALUE_DEFAULT_VALUE ((int16_t)0x8000)

/** @brief Default value for MinValue attribute */
#define ESP_ZB_ZCL_TEMP_MEASUREMENT_MIN_VALUE_DEFAULT_VALUE ((int16_t)0x8000)

/** @brief Default value for MaxValue attribute */
#define ESP_ZB_ZCL_TEMP_MEASUREMENT_MAX_VALUE_DEFAULT_VALUE ((int16_t)0x8000)

#ifdef __cplusplus
}
#endif
