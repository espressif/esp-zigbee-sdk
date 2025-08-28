/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Device Temperature Configuration cluster attribute identifiers */
typedef enum esp_zb_zcl_device_temp_config_attr_e {
    ESP_ZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_CURRENT_TEMP_ID               = 0x0000, /*!< CurrentTemperature */
    ESP_ZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_MIN_TEMP_EXPERIENCED_ID       = 0x0001, /*!< MinTempExperienced */
    ESP_ZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_MAX_TEMP_EXPERIENCED_ID       = 0x0002, /*!< MaxTempExperienced */
    ESP_ZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_OVER_TEMP_TOTAL_DWELL_ID      = 0x0003, /*!< OverTempTotalDwell */
    ESP_ZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_DEVICE_TEMP_ALARM_MASK_ID     = 0x0010, /*!< DeviceTempAlarmMask */
    ESP_ZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_LOW_TEMP_THRESHOLD_ID         = 0x0011, /*!< LowTempThreshold */
    ESP_ZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_HIGH_TEMP_THRESHOLD_ID        = 0x0012, /*!< HighTempThreshold */
    ESP_ZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_LOW_TEMP_DWELL_TRIP_POINT_ID  = 0x0013, /*!< LowTempDwellTripPoint */
    ESP_ZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_HIGH_TEMP_DWELL_TRIP_POINT_ID = 0x0014, /*!< HighTempDwellTripPoint */
} esp_zb_zcl_device_temp_config_attr_t;

/** @brief Minimum value for CurrentTemp attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_CURRENT_TEMP_MIN_VALUE  (-200)
/** @brief Maximum value for CurrentTemp attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_CURRENT_TEMP_MAX_VALUE  (+200)

/** @brief Minimum value for MinTempExperienced attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_MIN_TEMP_EXPERIENCED_MIN_VALUE  (-200)
/** @brief Maximum value for MinTempExperienced attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_MIN_TEMP_EXPERIENCED_MAX_VALUE  (+200)

/** @brief Minimum value for MaxTempExperienced attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_MAX_TEMP_EXPERIENCED_MIN_VALUE  (-200)
/** @brief Maximum value for MaxTempExperienced attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_MAX_TEMP_EXPERIENCED_MAX_VALUE  (+200)

/** @brief Minimum value for OverTotalDwell attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_OVER_TEMP_TOTAL_DWELL_MIN_VALUE (0x0000)
/** @brief Maximum value for OverTotalDwell attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_OVER_TEMP_TOTAL_DWELL_MAX_VALUE (0xffff)

/** @brief Minimum value for DeviceTempAlarmMask attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_DEVICE_TEMP_ALARM_MASK_MIN_VALUE (0b00000000)
/** @brief Maximum value for DeviceTempAlarmMask attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_DEVICE_TEMP_ALARM_MASK_MAX_VALUE (0b00000011)

/** @brief Minimum value for LowTempThreshold attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_LOW_TEMP_THRESHOLD_MIN_VALUE  (-200)
/** @brief Maximum value for LowTempThreshold attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_LOW_TEMP_THRESHOLD_MAX_VALUE  (+200)

/** @brief Minimum value for HighTempThreshold attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_HIGH_TEMP_THRESHOLD_MIN_VALUE  (-200)
/** @brief Maximum value for HighTempThreshold attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_HIGH_TEMP_THRESHOLD_MAX_VALUE  (+200)

/** @brief Minimum value for LowTempTripPoint attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_LOW_TEMP_DWELL_TRIP_POINT_MIN_VALUE (0x000000)
/** @brief Maximum value for LowTempTripPoint attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_LOW_TEMP_DWELL_TRIP_POINT_MAX_VALUE (0xffffff)

/** @brief Minimum value for HighTempTripPoint attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_HIGH_TEMP_DWELL_TRIP_POINT_MIN_VALUE (0x000000)
/** @brief Maximum value for HighTempTripPoint attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_HIGH_TEMP_DWELL_TRIP_POINT_MAX_VALUE (0xffffff)

/** @brief Default value for CurrentTemp attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_CURRENT_TEMP_DEFAULT_VALUE                ESP_ZB_ZCL_VALUE_S16_NONE

/** @brief Default value for MinTempExperienced attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_MIN_TEMP_EXPERIENCED_DEFAULT_VALUE        ESP_ZB_ZCL_VALUE_S16_NONE

/** @brief Default value for MaxTempExperienced attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_MAX_TEMP_EXPERIENCED_DEFAULT_VALUE        ESP_ZB_ZCL_VALUE_S16_NONE

/** @brief Default value for OverTempTotalDwell attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_OVER_TEMP_TOTAL_DWELL_DEFAULT_VALUE       0

/** @brief Default value for DeviceTempAlarmMask attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_DEVICE_TEMP_ALARM_MASK_DEFAULT_VALUE      0

/** @brief Default value for LowTempThreshold attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_LOW_TEMP_THRESHOLD_DEFAULT_VALUE          ESP_ZB_ZCL_VALUE_S16_NONE

/** @brief Default value for HighTempThreshold attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_HIGH_TEMP_THRESHOLD_DEFAULT_VALUE         ESP_ZB_ZCL_VALUE_S16_NONE

/** @brief Default value for LowTempDwellTripPoint attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_LOW_TEMP_DWELL_TRIP_POINT_DEFAULT_VALUE   (0xffffff)

/** @brief Default value for HighTempDwellTripPoint attribute */
#define ESP_ZB_ZCL_DEVICE_TEMP_CONFIG_HIGH_TEMP_DWELL_TRIP_POINT_DEFAULT_VALUE  (0xffffff)

#ifdef __cplusplus
}
#endif
