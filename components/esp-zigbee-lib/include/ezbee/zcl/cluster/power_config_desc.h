/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/zcl_common.h>
#include <ezbee/zcl/zcl_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------------------------------------------*
   POWER_CONFIG Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the power_config cluster implementation */
#define EZB_ZCL_POWER_CONFIG_CLUSTER_REVISION (2)

/**
 * @brief Attribute identifiers for the power_config server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_POWER_CONFIG_MAINS_VOLTAGE_ID                     = 0x0000U, /*!< MainsVoltage attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_MAINS_FREQUENCY_ID                   = 0x0001U, /*!< MainsFrequency attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_MAINS_ALARM_MASK_ID                  = 0x0010U, /*!< MainsAlarmMask attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_MAINS_VOLTAGE_MIN_THRESHOLD_ID       = 0x0011U, /*!< MainsVoltageMinThreshold attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_MAINS_VOLTAGE_MAX_THRESHOLD_ID       = 0x0012U, /*!< MainsVoltageMaxThreshold attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_MAINS_VOLTAGE_DWELL_TRIP_POINT_ID    = 0x0013U, /*!< MainsVoltageDwellTripPoint attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_VOLTAGE_ID                   = 0x0020U, /*!< BatteryVoltage attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_PERCENTAGE_REMAINING_ID      = 0x0021U, /*!< BatteryPercentageRemaining attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_MANUFACTURER_ID              = 0x0030U, /*!< BatteryManufacturer attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_SIZE_ID                      = 0x0031U, /*!< BatterySize attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_A_HR_RATING_ID               = 0x0032U, /*!< BatteryAHrRating attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_QUANTITY_ID                  = 0x0033U, /*!< BatteryQuantity attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_RATED_VOLTAGE_ID             = 0x0034U, /*!< BatteryRatedVoltage attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_ALARM_MASK_ID                = 0x0035U, /*!< BatteryAlarmMask attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_VOLTAGE_MIN_THRESHOLD_ID     = 0x0036U, /*!< BatteryVoltageMinThreshold attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_VOLTAGE_THRESHOLD1_ID        = 0x0037U, /*!< BatteryVoltageThreshold1 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_VOLTAGE_THRESHOLD2_ID        = 0x0038U, /*!< BatteryVoltageThreshold2 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_VOLTAGE_THRESHOLD3_ID        = 0x0039U, /*!< BatteryVoltageThreshold3 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_PERCENTAGE_MIN_THRESHOLD_ID  = 0x003aU, /*!< BatteryPercentageMinThreshold attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_PERCENTAGE_THRESHOLD1_ID     = 0x003bU, /*!< BatteryPercentageThreshold1 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_PERCENTAGE_THRESHOLD2_ID     = 0x003cU, /*!< BatteryPercentageThreshold2 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_PERCENTAGE_THRESHOLD3_ID     = 0x003dU, /*!< BatteryPercentageThreshold3 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY_ALARM_STATE_ID               = 0x003eU, /*!< BatteryAlarmState attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_VOLTAGE_ID                  = 0x0040U, /*!< Battery2Voltage attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_PERCENTAGE_REMAINING_ID     = 0x0041U, /*!< Battery2PercentageRemaining attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_MANUFACTURER_ID             = 0x0050U, /*!< Battery2Manufacturer attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_SIZE_ID                     = 0x0051U, /*!< Battery2Size attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_A_HR_RATING_ID              = 0x0052U, /*!< Battery2AHrRating attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_QUANTITY_ID                 = 0x0053U, /*!< Battery2Quantity attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_RATED_VOLTAGE_ID            = 0x0054U, /*!< Battery2RatedVoltage attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_ALARM_MASK_ID               = 0x0055U, /*!< Battery2AlarmMask attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_VOLTAGE_MIN_THRESHOLD_ID    = 0x0056U, /*!< Battery2VoltageMinThreshold attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_VOLTAGE_THRESHOLD1_ID       = 0x0057U, /*!< Battery2VoltageThreshold1 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_VOLTAGE_THRESHOLD2_ID       = 0x0058U, /*!< Battery2VoltageThreshold2 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_VOLTAGE_THRESHOLD3_ID       = 0x0059U, /*!< Battery2VoltageThreshold3 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_PERCENTAGE_MIN_THRESHOLD_ID = 0x005aU, /*!< Battery2PercentageMinThreshold attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_PERCENTAGE_THRESHOLD1_ID    = 0x005bU, /*!< Battery2PercentageThreshold1 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_PERCENTAGE_THRESHOLD2_ID    = 0x005cU, /*!< Battery2PercentageThreshold2 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_PERCENTAGE_THRESHOLD3_ID    = 0x005dU, /*!< Battery2PercentageThreshold3 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY2_ALARM_STATE_ID              = 0x005eU, /*!< Battery2AlarmState attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_VOLTAGE_ID                  = 0x0060U, /*!< Battery3Voltage attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_PERCENTAGE_REMAINING_ID     = 0x0061U, /*!< Battery3PercentageRemaining attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_MANUFACTURER_ID             = 0x0070U, /*!< Battery3Manufacturer attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_SIZE_ID                     = 0x0071U, /*!< Battery3Size attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_A_HR_RATING_ID              = 0x0072U, /*!< Battery3AHrRating attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_QUANTITY_ID                 = 0x0073U, /*!< Battery3Quantity attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_RATED_VOLTAGE_ID            = 0x0074U, /*!< Battery3RatedVoltage attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_ALARM_MASK_ID               = 0x0075U, /*!< Battery3AlarmMask attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_VOLTAGE_MIN_THRESHOLD_ID    = 0x0076U, /*!< Battery3VoltageMinThreshold attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_VOLTAGE_THRESHOLD1_ID       = 0x0077U, /*!< Battery3VoltageThreshold1 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_VOLTAGE_THRESHOLD2_ID       = 0x0078U, /*!< Battery3VoltageThreshold2 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_VOLTAGE_THRESHOLD3_ID       = 0x0079U, /*!< Battery3VoltageThreshold3 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_PERCENTAGE_MIN_THRESHOLD_ID = 0x007aU, /*!< Battery3PercentageMinThreshold attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_PERCENTAGE_THRESHOLD1_ID    = 0x007bU, /*!< Battery3PercentageThreshold1 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_PERCENTAGE_THRESHOLD2_ID    = 0x007cU, /*!< Battery3PercentageThreshold2 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_PERCENTAGE_THRESHOLD3_ID    = 0x007dU, /*!< Battery3PercentageThreshold3 attribute. */
    EZB_ZCL_ATTR_POWER_CONFIG_BATTERY3_ALARM_STATE_ID              = 0x007eU, /*!< Battery3AlarmState attribute. */
} ezb_zcl_power_config_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the PowerConfig server cluster.
 */
typedef struct ezb_zcl_power_config_cluster_server_config_s {
    uint16_t mains_voltage;               /*!< Configurable mandatory MainsVoltage attribute */
    uint16_t mains_voltage_min_threshold; /*!< Configurable mandatory MainsVoltageMinThreshold attribute */
    uint16_t mains_voltage_max_threshold; /*!< Configurable mandatory MainsVoltageMaxThreshold attribute */
} ezb_zcl_power_config_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL BatterySize attribute of PowerConfig.
 */
typedef enum {
    EZB_ZCL_POWER_CONFIG_BATTERY_SIZE_NO_BATTERY = 0x00U, /*!< NoBattery */
    EZB_ZCL_POWER_CONFIG_BATTERY_SIZE_BUILD_IN   = 0x01U, /*!< BuildIn */
    EZB_ZCL_POWER_CONFIG_BATTERY_SIZE_OTHER      = 0x02U, /*!< Other */
    EZB_ZCL_POWER_CONFIG_BATTERY_SIZE_AA         = 0x03U, /*!< AA */
    EZB_ZCL_POWER_CONFIG_BATTERY_SIZE_AAA        = 0x04U, /*!< AAA */
    EZB_ZCL_POWER_CONFIG_BATTERY_SIZE_C          = 0x05U, /*!< C */
    EZB_ZCL_POWER_CONFIG_BATTERY_SIZE_D          = 0x06U, /*!< D */
    EZB_ZCL_POWER_CONFIG_BATTERY_SIZE_CR2        = 0x07U, /*!< CR2 */
    EZB_ZCL_POWER_CONFIG_BATTERY_SIZE_CR123_A    = 0x08U, /*!< CR123A */
    EZB_ZCL_POWER_CONFIG_BATTERY_SIZE_UNKNOWN    = 0xFFU, /*!< Unknown */
} ezb_zcl_power_config_server_battery_size_t;

/**
 * @brief Bitmap for ZCL MainsAlarmMask attribute of PowerConfig.
 */
typedef enum {
    EZB_ZCL_POWER_CONFIG_MAINS_ALARM_MASK_MAINS_VOLTAGE_TOO_LOW   = 01U, /*!< MainsVoltageTooLow */
    EZB_ZCL_POWER_CONFIG_MAINS_ALARM_MASK_MAINS_VOLTAGE_TOO_HIGH  = 02U, /*!< MainsVoltageTooHigh */
    EZB_ZCL_POWER_CONFIG_MAINS_ALARM_MASK_MAINS_POWER_SUPPLY_LOST = 04U, /*!< MainsPowerSupplyLost */
} ezb_zcl_power_config_server_mains_alarm_mask_t;

/** @brief Default value of MainsVoltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_VOLTAGE_DEFAULT_VALUE (EZB_ZCL_VALUE_UINT16_FF)

/** @brief Minimum value of MainsVoltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_VOLTAGE_MIN_VALUE (0x0000)

/** @brief Maximum value of MainsVoltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_VOLTAGE_MAX_VALUE (0xffff)

/** @brief Minimum value of MainsFrequency in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_FREQUENCY_MIN_VALUE (0x00)

/** @brief Maximum value of MainsFrequency in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_FREQUENCY_MAX_VALUE (0xff)
/** @brief Default value of MainsAlarmMask in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_ALARM_MASK_DEFAULT_VALUE (0x00)

/** @brief Default value of MainsVoltageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_VOLTAGE_MIN_THRESHOLD_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of MainsVoltageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_VOLTAGE_MIN_THRESHOLD_MIN_VALUE (0x0000)

/** @brief Maximum value of MainsVoltageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_VOLTAGE_MIN_THRESHOLD_MAX_VALUE (0xffff)
/** @brief Default value of MainsVoltageMaxThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_VOLTAGE_MAX_THRESHOLD_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of MainsVoltageMaxThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_VOLTAGE_MAX_THRESHOLD_MIN_VALUE (0x0000)

/** @brief Maximum value of MainsVoltageMaxThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_VOLTAGE_MAX_THRESHOLD_MAX_VALUE (0xffff)
/** @brief Default value of MainsVoltageDwellTripPoint in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_VOLTAGE_DWELL_TRIP_POINT_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of MainsVoltageDwellTripPoint in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_VOLTAGE_DWELL_TRIP_POINT_MIN_VALUE (0x0000)

/** @brief Maximum value of MainsVoltageDwellTripPoint in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_MAINS_VOLTAGE_DWELL_TRIP_POINT_MAX_VALUE (0xffff)

/** @brief Minimum value of BatteryVoltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryVoltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_MAX_VALUE (0xff)
/** @brief Default value of BatteryPercentageRemaining in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_REMAINING_DEFAULT_VALUE (0x00)

/** @brief Minimum value of BatteryPercentageRemaining in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_REMAINING_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryPercentageRemaining in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_REMAINING_MAX_VALUE (0xff)

/** @brief Default value of BatterySize in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_SIZE_DEFAULT_VALUE (0xff)

/** @brief Minimum value of BatteryAHrRating in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_A_HR_RATING_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryAHrRating in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_A_HR_RATING_MAX_VALUE (0xffff)

/** @brief Minimum value of BatteryQuantity in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_QUANTITY_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryQuantity in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_QUANTITY_MAX_VALUE (0xff)

/** @brief Minimum value of BatteryRatedVoltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_RATED_VOLTAGE_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryRatedVoltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_RATED_VOLTAGE_MAX_VALUE (0xff)
/** @brief Default value of BatteryAlarmMask in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_MASK_DEFAULT_VALUE (0x00)

/** @brief Default value of BatteryVoltageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_MIN_THRESHOLD_DEFAULT_VALUE (0x00)

/** @brief Minimum value of BatteryVoltageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_MIN_THRESHOLD_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryVoltageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_MIN_THRESHOLD_MAX_VALUE (0xff)
/** @brief Default value of BatteryVoltageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_THRESHOLD1_DEFAULT_VALUE (0x00)

/** @brief Minimum value of BatteryVoltageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_THRESHOLD1_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryVoltageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_THRESHOLD1_MAX_VALUE (0xff)
/** @brief Default value of BatteryVoltageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_THRESHOLD2_DEFAULT_VALUE (0x00)

/** @brief Minimum value of BatteryVoltageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_THRESHOLD2_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryVoltageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_THRESHOLD2_MAX_VALUE (0xff)
/** @brief Default value of BatteryVoltageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_THRESHOLD3_DEFAULT_VALUE (0x00)

/** @brief Minimum value of BatteryVoltageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_THRESHOLD3_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryVoltageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_VOLTAGE_THRESHOLD3_MAX_VALUE (0xff)
/** @brief Default value of BatteryPercentageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_MIN_THRESHOLD_DEFAULT_VALUE (0x00)

/** @brief Minimum value of BatteryPercentageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_MIN_THRESHOLD_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryPercentageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_MIN_THRESHOLD_MAX_VALUE (0xff)
/** @brief Default value of BatteryPercentageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_THRESHOLD1_DEFAULT_VALUE (0x00)

/** @brief Minimum value of BatteryPercentageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_THRESHOLD1_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryPercentageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_THRESHOLD1_MAX_VALUE (0xff)
/** @brief Default value of BatteryPercentageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_THRESHOLD2_DEFAULT_VALUE (0x00)

/** @brief Minimum value of BatteryPercentageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_THRESHOLD2_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryPercentageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_THRESHOLD2_MAX_VALUE (0xff)
/** @brief Default value of BatteryPercentageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_THRESHOLD3_DEFAULT_VALUE (0x00)

/** @brief Minimum value of BatteryPercentageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_THRESHOLD3_MIN_VALUE (0x00)

/** @brief Maximum value of BatteryPercentageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_PERCENTAGE_THRESHOLD3_MAX_VALUE (0xff)
/** @brief Default value of BatteryAlarmState in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_STATE_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery2Voltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2Voltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_MAX_VALUE (0xff)
/** @brief Default value of Battery2PercentageRemaining in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_REMAINING_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery2PercentageRemaining in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_REMAINING_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2PercentageRemaining in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_REMAINING_MAX_VALUE (0xff)

/** @brief Default value of Battery2Size in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_SIZE_DEFAULT_VALUE (0xff)

/** @brief Minimum value of Battery2Size in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_SIZE_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2Size in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_SIZE_MAX_VALUE (0x00)

/** @brief Minimum value of Battery2AHrRating in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_A_HR_RATING_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2AHrRating in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_A_HR_RATING_MAX_VALUE (0xffff)

/** @brief Minimum value of Battery2Quantity in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_QUANTITY_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2Quantity in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_QUANTITY_MAX_VALUE (0xff)

/** @brief Minimum value of Battery2RatedVoltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_RATED_VOLTAGE_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2RatedVoltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_RATED_VOLTAGE_MAX_VALUE (0xff)
/** @brief Default value of Battery2AlarmMask in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_ALARM_MASK_DEFAULT_VALUE (0x00)

/** @brief Default value of Battery2VoltageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_MIN_THRESHOLD_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery2VoltageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_MIN_THRESHOLD_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2VoltageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_MIN_THRESHOLD_MAX_VALUE (0xff)
/** @brief Default value of Battery2VoltageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_THRESHOLD1_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery2VoltageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_THRESHOLD1_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2VoltageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_THRESHOLD1_MAX_VALUE (0xff)
/** @brief Default value of Battery2VoltageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_THRESHOLD2_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery2VoltageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_THRESHOLD2_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2VoltageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_THRESHOLD2_MAX_VALUE (0xff)
/** @brief Default value of Battery2VoltageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_THRESHOLD3_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery2VoltageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_THRESHOLD3_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2VoltageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_VOLTAGE_THRESHOLD3_MAX_VALUE (0xff)
/** @brief Default value of Battery2PercentageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_MIN_THRESHOLD_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery2PercentageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_MIN_THRESHOLD_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2PercentageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_MIN_THRESHOLD_MAX_VALUE (0xff)
/** @brief Default value of Battery2PercentageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_THRESHOLD1_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery2PercentageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_THRESHOLD1_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2PercentageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_THRESHOLD1_MAX_VALUE (0xff)
/** @brief Default value of Battery2PercentageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_THRESHOLD2_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery2PercentageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_THRESHOLD2_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2PercentageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_THRESHOLD2_MAX_VALUE (0xff)
/** @brief Default value of Battery2PercentageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_THRESHOLD3_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery2PercentageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_THRESHOLD3_MIN_VALUE (0x00)

/** @brief Maximum value of Battery2PercentageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_PERCENTAGE_THRESHOLD3_MAX_VALUE (0xff)
/** @brief Default value of Battery2AlarmState in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY2_ALARM_STATE_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery3Voltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3Voltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_MAX_VALUE (0xff)
/** @brief Default value of Battery3PercentageRemaining in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_REMAINING_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery3PercentageRemaining in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_REMAINING_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3PercentageRemaining in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_REMAINING_MAX_VALUE (0xff)

/** @brief Default value of Battery3Size in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_SIZE_DEFAULT_VALUE (0xff)

/** @brief Minimum value of Battery3AHrRating in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_A_HR_RATING_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3AHrRating in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_A_HR_RATING_MAX_VALUE (0xffff)

/** @brief Minimum value of Battery3Quantity in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_QUANTITY_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3Quantity in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_QUANTITY_MAX_VALUE (0xff)

/** @brief Minimum value of Battery3RatedVoltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_RATED_VOLTAGE_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3RatedVoltage in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_RATED_VOLTAGE_MAX_VALUE (0xff)
/** @brief Default value of Battery3AlarmMask in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_ALARM_MASK_DEFAULT_VALUE (0x00)

/** @brief Default value of Battery3VoltageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_MIN_THRESHOLD_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery3VoltageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_MIN_THRESHOLD_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3VoltageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_MIN_THRESHOLD_MAX_VALUE (0xff)
/** @brief Default value of Battery3VoltageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_THRESHOLD1_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery3VoltageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_THRESHOLD1_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3VoltageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_THRESHOLD1_MAX_VALUE (0xff)
/** @brief Default value of Battery3VoltageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_THRESHOLD2_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery3VoltageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_THRESHOLD2_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3VoltageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_THRESHOLD2_MAX_VALUE (0xff)
/** @brief Default value of Battery3VoltageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_THRESHOLD3_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery3VoltageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_THRESHOLD3_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3VoltageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_VOLTAGE_THRESHOLD3_MAX_VALUE (0xff)
/** @brief Default value of Battery3PercentageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_MIN_THRESHOLD_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery3PercentageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_MIN_THRESHOLD_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3PercentageMinThreshold in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_MIN_THRESHOLD_MAX_VALUE (0xff)
/** @brief Default value of Battery3PercentageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_THRESHOLD1_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery3PercentageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_THRESHOLD1_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3PercentageThreshold1 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_THRESHOLD1_MAX_VALUE (0xff)
/** @brief Default value of Battery3PercentageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_THRESHOLD2_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery3PercentageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_THRESHOLD2_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3PercentageThreshold2 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_THRESHOLD2_MAX_VALUE (0xff)
/** @brief Default value of Battery3PercentageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_THRESHOLD3_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Battery3PercentageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_THRESHOLD3_MIN_VALUE (0x00)

/** @brief Maximum value of Battery3PercentageThreshold3 in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_PERCENTAGE_THRESHOLD3_MAX_VALUE (0xff)
/** @brief Default value of Battery3AlarmState in PowerConfig cluster */
#define EZB_ZCL_POWER_CONFIG_BATTERY3_ALARM_STATE_DEFAULT_VALUE (0x00)

typedef ezb_zcl_power_config_cluster_server_config_t ezb_zcl_power_config_cluster_config_t;

/**
 * @brief Add an attribute to an power_config cluster descriptor.
 *
 * @param cluster_desc Pointer to the power_config cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_power_config_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an power_config cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the power_config cluster configuration structure, refer to
 * ezb_zcl_power_config_cluster_server_config_t or ezb_zcl_power_config_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_power_config_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the PowerConfig cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_power_config_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the PowerConfig cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_power_config_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_POWER_CONFIG_CLIENT_ROLE_INIT ezb_zcl_power_config_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_POWER_CONFIG_SERVER_ROLE_INIT ezb_zcl_power_config_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
