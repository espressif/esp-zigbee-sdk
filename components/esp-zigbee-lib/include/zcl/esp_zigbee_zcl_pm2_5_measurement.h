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

/** @brief PM2.5 Measurement cluster attribute identifiers */
typedef enum {
    ESP_ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MEASURED_VALUE_ID     = 0x0000, /*!< MeasuredValue attribute */
    ESP_ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MIN_MEASURED_VALUE_ID = 0x0001, /*!< MinMeasuredValue attribute */
    ESP_ZB_ZCL_ATTR_PM2_5_MEASUREMENT_MAX_MEASURED_VALUE_ID = 0x0002, /*!< MaxMeasuredValue attribute */
    ESP_ZB_ZCL_ATTR_PM2_5_MEASUREMENT_TOLERANCE_ID          = 0x0003, /*!< Tolerance attribute */
} esp_zb_zcl_pm2_5_measurement_attr_t;

/** @brief Default value for MeasuredValue attribute */
#define ESP_ZB_ZCL_PM2_5_MEASUREMENT_MEASURED_VALUE_DEFAULT_VALUE (.0 / .0)

/** @brief Default value for MinMeasuredValue attribute */
#define ESP_ZB_ZCL_PM2_5_MEASUREMENT_MIN_MEASURED_VALUE_DEFAULT_VALUE (.0 / .0)

/** @brief Default value for MaxMeasuredValue attribute */
#define ESP_ZB_ZCL_PM2_5_MEASUREMENT_MAX_MEASURED_VALUE_DEFAULT_VALUE (.0 / .0)

/** @brief MeasuredValue attribute unknown */
#define ESP_ZB_ZCL_PM2_5_MEASUREMENT_MEASURED_VALUE_UNKNOWN (.0 / .0)

/** @brief MinMeasuredValue attribute undefined */
#define ESP_ZB_ZCL_PM2_5_MEASUREMENT_MIN_MEASURED_VALUE_UNDEFINED (.0 / .0)

/** @brief MaxMeasuredValue attribute undefined */
#define ESP_ZB_ZCL_PM2_5_MEASUREMENT_MAX_MEASURED_VALUE_UNDEFINED (.0 / .0)

/** @brief MinMeasuredValue attribute minimum value */
#define ESP_ZB_ZCL_PM2_5_MEASUREMENT_MIN_MEASURED_VALUE_MIN_VALUE 0.0

/** @brief MaxMeasuredValue attribute maximum value */
#define ESP_ZB_ZCL_PM2_5_MEASUREMENT_MAX_MEASURED_VALUE_MAX_VALUE 1.0

#ifdef __cplusplus
}
#endif
