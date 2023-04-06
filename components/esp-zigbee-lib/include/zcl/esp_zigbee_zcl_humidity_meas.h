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

/** @brief Water Content Measurement cluster attribute identifiers
*/
typedef enum {
    ESP_ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_VALUE_ID     = 0x0000,  /*!<  MeasuredValue */
    ESP_ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_MIN_VALUE_ID = 0x0001,  /*!<  MinMeasuredValue Attribute */
    ESP_ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_MAX_VALUE_ID = 0x0002,  /*!<  MaxMeasuredValue Attribute */
    ESP_ZB_ZCL_ATTR_REL_HUMIDITY_TOLERANCE_ID             = 0x0003,  /*!<  The Tolerance attribute SHALL indicate the magnitude of the possible error that is associated with MeasuredValue, using the same units and resolution.*/
} esp_zb_zcl_rel_humidity_measurement_attr_t;

/** @brief MeasuredValue attribute default value */
#define ESP_ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_VALUE_DEFAULT        0xFFFF

/** @brief MinMeasuredValue attribute minimum value */
#define ESP_ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_MIN_VALUE_MIN_VALUE  0x0000

/** @brief MinMeasuredValue attribute maximum value */
#define ESP_ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_MIN_VALUE_MAX_VALUE  0x270F

/** @brief MinMeasuredValue attribute default value */
#define ESP_ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_MIN_VALUE_DEFAULT  0xFFFF

/** @brief MaxMeasuredValue attribute minimum value */
#define ESP_ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_MAX_VALUE_MIN_VALUE  0x0001

/** @brief MaxMeasuredValue attribute maximum value */
#define ESP_ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_MAX_VALUE_MAX_VALUE  0x2710

/** @brief MaxMeasuredValue attribute default value */
#define ESP_ZB_ZCL_ATTR_REL_HUMIDITY_MEASUREMENT_MAX_VALUE_DEFAULT  0xFFFF

#ifdef __cplusplus
}
#endif
