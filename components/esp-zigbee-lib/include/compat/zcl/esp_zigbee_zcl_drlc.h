/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/zcl.h" instead!"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Demand response and load control client attribute enumeration */
typedef enum esp_zb_zcl_drlc_cli_attr_e {
    ESP_ZB_ZCL_ATTR_DRLC_UTILITY_ENROLLMENT_GROUP        = 0x0000,   /*!< UtilityEnrollmentGroup attribute. Provides for
                                                                          utilities to assign devices to groups. */
    ESP_ZB_ZCL_ATTR_DRLC_START_RANDOMIZATION_MINUTES     = 0x0001,   /*!< StartRandomizationMinutes attribute. Represents
                                                                          the maximum number of minutes to be used when
                                                                          randomizing the start of an event. */
    ESP_ZB_ZCL_ATTR_DRLC_DURATION_RANDOMIZATION_MINUTES  = 0x0002,   /*!< DurationRandomizationMinutes attribute. Represents
                                                                          the maximum number of minutes to be used when randomizing
                                                                          the duration of an event. */
    ESP_ZB_ZCL_ATTR_DRLC_DEVICE_CLASS_VALUE              = 0x0003,   /*!< DeviceClassValue attribute. Identifies which bits the
                                                                          device will match in the Device Class fields. */
} esp_zb_zcl_drlc_cli_attr_t;

/** @brief The default value of ESP_ZB_ZCL_ATTR_DRLC_UTILITY_ENROLLMENT_GROUP attribute */
#define ESP_ZB_ZCL_ATTR_DRLC_UTILITY_ENROLLMENT_GROUP_DEFAULT_VALUE 0x00
/** @brief The minimum value of ESP_ZB_ZCL_ATTR_DRLC_UTILITY_ENROLLMENT_GROUP attribute */
#define ESP_ZB_ZCL_ATTR_DRLC_UTILITY_ENROLLMENT_GROUP_MIN_VALUE 0x00
/** @brief The maximum value of ESP_ZB_ZCL_ATTR_DRLC_UTILITY_ENROLLMENT_GROUP attribute */
#define ESP_ZB_ZCL_ATTR_DRLC_UTILITY_ENROLLMENT_GROUP_MAX_VALUE 0xFF

/** @brief The default value of ESP_ZB_ZCL_ATTR_DRLC_START_RANDOMIZATION_MINUTES attribute */
#define ESP_ZB_ZCL_ATTR_DRLC_START_RANDOMIZATION_MINUTES_DEFAULT_VALUE 0x1E
/** @brief The minimum value of ESP_ZB_ZCL_ATTR_DRLC_START_RANDOMIZATION_MINUTES attribute */
#define ESP_ZB_ZCL_ATTR_DRLC_START_RANDOMIZATION_MINUTES_MIN_VALUE 0x00
/** @brief The maximum value of ESP_ZB_ZCL_ATTR_DRLC_START_RANDOMIZATION_MINUTES attribute */
#define ESP_ZB_ZCL_ATTR_DRLC_START_RANDOMIZATION_MINUTES_MAX_VALUE 0x3C

/** @brief The maximum value of ESP_ZB_ZCL_ATTR_DRLC_DURATION_RANDOMIZATION_MINUTES attribute */
#define ESP_ZB_ZCL_ATTR_DRLC_DURATION_RANDOMIZATION_MINUTES_DEFAULT_VALUE 0x00
/** @brief The maximum value of ESP_ZB_ZCL_ATTR_DRLC_DURATION_RANDOMIZATION_MINUTES attribute */
#define ESP_ZB_ZCL_ATTR_DRLC_DURATION_RANDOMIZATION_MINUTES_MIN_VALUE 0x00
/** @brief The maximum value of ESP_ZB_ZCL_ATTR_DRLC_DURATION_RANDOMIZATION_MINUTES attribute */
#define ESP_ZB_ZCL_ATTR_DRLC_DURATION_RANDOMIZATION_MINUTES_MAX_VALUE 0x3C

/** @brief The maximum value of ESP_ZB_ZCL_ATTR_DRLC_DEVICE_CLASS_VALUE attribute */
#define ESP_ZB_ZCL_ATTR_DRLC_DEVICE_CLASS_VALUE_DEFAULT_VALUE 0x0000
/** @brief The maximum value of ESP_ZB_ZCL_ATTR_DRLC_DEVICE_CLASS_VALUE attribute */
#define ESP_ZB_ZCL_ATTR_DRLC_DEVICE_CLASS_VALUE_MIN_VALUE 0x0000
/** @brief The maximum value of ESP_ZB_ZCL_ATTR_DRLC_DEVICE_CLASS_VALUE attribute */
#define ESP_ZB_ZCL_ATTR_DRLC_DEVICE_CLASS_VALUE_MAX_VALUE 0xFFFF

/** @brief DRLC device classes enumeration */
typedef enum esp_zb_zcl_drlc_device_class_e {
    ESP_ZB_ZCL_DRLC_DEVICE_CLASS_HVAC               = 1 << 0,  /*!< HVAC Compressor or Furnace */
    ESP_ZB_ZCL_DRLC_DEVICE_CLASS_STRIP_HEATER       = 1 << 1,  /*!< Strip Heaters/Baseboard Heaters */
    ESP_ZB_ZCL_DRLC_DEVICE_CLASS_WATER_HEATER       = 1 << 2,  /*!< Water Heater */
    ESP_ZB_ZCL_DRLC_DEVICE_CLASS_POOL_PUMP          = 1 << 3,  /*!< Pool Pump/Spa/Jacuzzi */
    ESP_ZB_ZCL_DRLC_DEVICE_CLASS_SMART_APPLIANCE    = 1 << 4,  /*!< Smart Appliances */
    ESP_ZB_ZCL_DRLC_DEVICE_CLASS_IRRIGATION_PUMP    = 1 << 5,  /*!< Irrigation Pump */
    ESP_ZB_ZCL_DRLC_DEVICE_CLASS_MCI_LOADS          = 1 << 6,  /*!< Managed Commercial & Industrial (C&I) loads */
    ESP_ZB_ZCL_DRLC_DEVICE_CLASS_SIMPLE_LOADS       = 1 << 7,  /*!< Simple misc. (Residential On/Off) loads */
    ESP_ZB_ZCL_DRLC_DEVICE_CLASS_EXTERIOR_LIGHTNING = 1 << 8,  /*!< Exterior Lighting */
    ESP_ZB_ZCL_DRLC_DEVICE_CLASS_INTERIOR_LIGHTNING = 1 << 9,  /*!< Interior Lighting */
    ESP_ZB_ZCL_DRLC_DEVICE_CLASS_ELECTRIC_VEHICLE   = 1 << 10, /*!< Electric Vehicle */
    ESP_ZB_ZCL_DRLC_DEVICE_CLASS_GENERATION_SYSTEMS = 1 << 11  /*!< Generation Systems */
} esp_zb_zcl_drlc_device_class_t;

/** @brief DRLC Criticality Level value applied by the device */
typedef enum esp_zb_zcl_drlc_criticality_levels_e {
    ESP_ZB_ZCL_DRLC_CRITICALITY_LEVEL_0 = 0x00,     /*!< Reserved */
    ESP_ZB_ZCL_DRLC_CRITICALITY_GREEN,              /*!< Green */
    ESP_ZB_ZCL_DRLC_CRITICALITY_LEVEL_1,            /*!< Level 1 */
    ESP_ZB_ZCL_DRLC_CRITICALITY_LEVEL_2,            /*!< Level 2 */
    ESP_ZB_ZCL_DRLC_CRITICALITY_LEVEL_3,            /*!< Level 3 */
    ESP_ZB_ZCL_DRLC_CRITICALITY_LEVEL_4,            /*!< Level 4 */
    ESP_ZB_ZCL_DRLC_CRITICALITY_LEVEL_5,            /*!< Level 5 */
    ESP_ZB_ZCL_DRLC_CRITICALITY_EMERGENCY,          /*!< Emergency */
    ESP_ZB_ZCL_DRLC_CRITICALITY_PLANNED_OUTAGE,     /*!< Planned Outage */
    ESP_ZB_ZCL_DRLC_CRITICALITY_SERVICE_DISCONNECT  /*!< Service Disconnect */
} esp_zb_zcl_drlc_criticality_levels_t;

/** @brief Commands are generated by DRLC Server */
typedef enum esp_zb_zcl_drlc_srv_cmd_e {
    ESP_ZB_ZCL_DRLC_SRV_CMD_LOAD_CONTROL_EVENT              = 0x00, /*!< LoadControlEvent */
    ESP_ZB_ZCL_DRLC_SRV_CMD_CANCEL_LOAD_CONTROL_EVENT       = 0x01, /*!< CancelLoadControlEvent */
    ESP_ZB_ZCL_DRLC_SRV_CMD_CANCEL_ALL_LOAD_CONTROL_EVENTS  = 0x02, /*!< Cancel AllLoadControlEvents */
} esp_zb_zcl_drlc_srv_cmd_t;

/** @brief Commands are generated by DRLC Client */
typedef enum esp_zb_zcl_drlc_cli_cmd_e {
    ESP_ZB_ZCL_DRLC_CLI_CMD_REPORT_EVENT_STATUS  = 0x00,    /*!< ReportEventStatus */
    ESP_ZB_ZCL_DRLC_CLI_CMD_GET_SCHEDULED_EVENTS = 0x01,    /*!< GetScheduledEvents */
} esp_zb_zcl_drlc_cli_cmd_t;

#ifdef __cplusplus
}
#endif

#endif
