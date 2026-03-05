/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/power_config_desc.h>

/**
 * @brief Enumeration alarm codes for ZCL PowerConfig Mains.
 * @anchor ezb_zcl_power_config_mains_alarm_code_t
 */
typedef enum {
    EZB_ZCL_POWER_CONFIG_MAINS_ALARM_CODE_MAINS_VOLTAGE_TOO_LOW  = 00U, /*!< MainsVoltageTooLow */
    EZB_ZCL_POWER_CONFIG_MAINS_ALARM_CODE_MAINS_VOLTAGE_TOO_HIGH = 01U, /*!< MainsVoltageTooHigh */
} ezb_zcl_power_config_mains_alarm_code_t;

/**
 * @brief Enumeration value for ZCL PowerConfig Battery Source.
 * @anchor ezb_zcl_power_config_battery_source_t
 */
typedef enum {
    EZB_ZCL_POWER_CONFIG_BATTERY_SOURCE1 = 1U, /*!< Battery source1 */
    EZB_ZCL_POWER_CONFIG_BATTERY_SOURCE2 = 2U, /*!< Battery source2 */
    EZB_ZCL_POWER_CONFIG_BATTERY_SOURCE3 = 3U, /*!< Battery source3 */
} ezb_zcl_power_config_battery_source_t;

/**
 * @brief Enumeration alarm mask for ZCL PowerConfig Battery.
 * @anchor ezb_zcl_power_config_battery_alarm_mask_t
 */
typedef enum {
    EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_MASK_TOO_LOW = 1U, /*!< Battery too low */
    EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_MASK_ALARM1  = 2U, /*!< Battery alarm1 */
    EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_MASK_ALARM2  = 4U, /*!< Battery alarm2 */
    EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_MASK_ALARM3  = 8U, /*!< Battery alarm3 */
} ezb_zcl_power_config_battery_alarm_mask_t;

/**
 * @brief Enumeration threshold for ZCL PowerConfig Battery Alarm.
 * @anchor ezb_zcl_power_config_battery_alarm_threshold_t
 */
typedef enum {
    EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_THRESHOLD_MIN = 0U, /*!< Battery alarm min threshold */
    EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_THRESHOLD_T1  = 1U, /*!< Battery alarm t1 threshold */
    EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_THRESHOLD_T2  = 2U, /*!< Battery alarm t2 threshold */
    EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_THRESHOLD_T3  = 3U, /*!< Battery alarm t3 threshold */
} ezb_zcl_power_config_battery_alarm_threshold_t;

/**
 * @brief Calculate the alarm code for ZCL PowerConfig Battery.
 * @param source The source, @ref ezb_zcl_power_config_battery_source_t.
 * @param threshold The threshold, @ref ezb_zcl_power_config_battery_alarm_threshold_t.
 * @return The alarm code.
 */
#define EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_CODE(source, threshold) (((source) << 4) + threshold)

/**
 * @brief Calculate the source shift for the battery alarm.
 * @param source The source, @ref ezb_zcl_power_config_battery_source_t.
 * @return The source shift.
 */
#define EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_SOURCE_SHIFT(source) (((source)-1) * 10)

/**
 * @brief Calculate the alarm state for ZCL PowerConfig Battery Alarm.
 * @param source The source, @ref ezb_zcl_power_config_battery_source_t.
 * @param threshold The threshold, @ref ezb_zcl_power_config_battery_alarm_threshold_t.
 * @return The alarm state.
 */
#define EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_STATE(source, threshold) \
    (((source) << EZB_ZCL_POWER_CONFIG_BATTERY_ALARM_SOURCE_SHIFT(source)) + threshold)
