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

/** @brief Dehumidification Control cluster attribute identifiers */
typedef enum esp_zb_zcl_dehumidification_control_attr_e {
    ESP_ZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_ID           = 0x0000, /*!< The RelativeHumidity attribute is an 8-bit value that represents the
                                                                                           current relative humidity (in %) measured by a local or remote sensor. */
    ESP_ZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_COOLING_ID    = 0x0001, /*!< Dehumidification Cooling attribute */
    ESP_ZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_RHDEHUMIDIFICATION_SETPOINT_ID = 0x0010, /*!< RHDehumidification Setpoint attribute */
    ESP_ZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_MODE_ID      = 0x0011, /*!< The RelativeHumidityMode attribute is an 8-bit value that specifies
                                                                                           how the RelativeHumidity value is being updated. */
    ESP_ZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_LOCKOUT_ID    = 0x0012, /*!< The DehumidificationLockout attribute is an 8-bit value that specifies
                                                                                           whether dehumidification is allowed or not. */
    ESP_ZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_HYSTERESIS_ID = 0x0013, /*!< Dehumidification Hysteresis attribute */
    ESP_ZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_MAX_COOL_ID   = 0x0014, /*!< Dehumidification Max Cool attribute */
    ESP_ZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_DISPLAY_ID   = 0x0015, /*!< The RelativeHumidityDisplay attribute is an 8-bit value that specifies
                                                                                           whether the RelativeHumidity value is displayed to the user or not. */
} esp_zb_zcl_dehumidification_control_attr_t;


/** @brief Default value for Dehumidification Control cluster revision global attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_CLUSTER_REVISION_DEFAULT 0x0001

/** @brief Min value for RHDehumidification Setpoint attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_RHDEHUMIDIFICATION_SETPOINT_MIN_VALUE 0x1e

/** @brief Max value for RHDehumidification Setpoint attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_RHDEHUMIDIFICATION_SETPOINT_MAX_VALUE 0x64

/** @brief Default value for RHDehumidification Setpoint attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_RHDEHUMIDIFICATION_SETPOINT_DEFAULT_VALUE 0x32

/** @brief Default value for RelativeHumidityMode attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_MODE_DEFAULT_VALUE ((uint8_t)ESP_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_MEASURED_LOCALLY)

/** @brief Default value for DehumidificationLockout attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_LOCKOUT_DEFAULT_VALUE ((uint8_t)ESP_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_LOCKOUT_ALLOWED)

/** @brief Min value for Dehumidification Hysteresis attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_HYSTERESIS_MIN_VALUE 0x02

/** @brief Max value for Dehumidification Hysteresis attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_HYSTERESIS_MAX_VALUE 0x14

/** @brief Default value for Dehumidification Hysteresis attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_HYSTERESIS_DEFAULT_VALUE 0x02

/** @brief Default value for Dehumidification Cool attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_COOL_DEFAULT_VALUE 0x00

/** @brief Min value for Dehumidification Max Cool attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_MAX_COOL_MIN_VALUE 0x14

/** @brief Max value for Dehumidification Max Cool attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_MAX_COOL_MAX_VALUE 0x64

/** @brief Default value for Dehumidification Max Cool attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_MAX_COOL_DEFAULT_VALUE 0x14

/** @brief Default value for RelativeHumidityDisplay attribute */
#define ESP_ZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_DISPLAY_DEFAULT_VALUE ((uint8_t)ESP_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_NOT_DISPLAYED)

/** @brief Enumerate the RelativeHumidityMode Attribute */
typedef enum esp_zb_zcl_dehumidification_control_relative_humidity_mode_e {
    ESP_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_MEASURED_LOCALLY         = 0x00, /*!< RelativeHumidity measured locally */
    ESP_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_UPDATED_OVER_THE_NETWORK,        /*!< RelativeHumidity updated over the network */
} esp_zb_zcl_dehumidification_control_relative_humidity_mode_t;

/** @brief Enumerate the DehumidificationLockout Attribute */
typedef enum esp_zb_zcl_dehumidification_control_dehumidification_lockout_e {
    ESP_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_LOCKOUT_NOT_ALLOWED  = 0x00, /*!< Dehumidification is not allowed */
    ESP_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_LOCKOUT_ALLOWED,             /*!< Dehumidification is allowed */
} esp_zb_zcl_dehumidification_control_dehumidification_lockout_t;

/** @brief Enumerate the RelativeHumidityDisplay Attribute */
typedef enum esp_zb_zcl_dehumidification_control_relative_humidity_display_e {
    ESP_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_NOT_DISPLAYED    = 0x00, /*!< RelativeHumidity is not displayed */
    ESP_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_DISPLAYED,               /*!< RelativeHumidity is displayed */
} esp_zb_zcl_dehumidification_control_relative_humidity_display_t;

#ifdef __cplusplus
}
#endif
