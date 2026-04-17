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
   ELECTRICAL_MEASUREMENT Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the electrical_measurement cluster implementation */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the electrical_measurement server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_ID             = 0x0000U, /*!< MeasurementType attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_ID                   = 0x0100U, /*!< DCVoltage attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MIN_VALUE_ID         = 0x0101U, /*!< DCVoltageMinValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MAX_VALUE_ID         = 0x0102U, /*!< DCVoltageMaxValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_CURRENT_ID                   = 0x0103U, /*!< DCCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_CURRENT_MIN_VALUE_ID         = 0x0104U, /*!< DCCurrentMinValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_CURRENT_MAX_VALUE_ID         = 0x0105U, /*!< DCCurrentMaxValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_POWER_ID                     = 0x0106U, /*!< DCPower attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_POWER_MIN_VALUE_ID           = 0x0107U, /*!< DCPowerMinValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_POWER_MAX_VALUE_ID           = 0x0108U, /*!< DCPowerMaxValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MULTIPLIER_ID        = 0x0200U, /*!< DCVoltageMultiplier attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_DIVISOR_ID           = 0x0201U, /*!< DCVoltageDivisor attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_CURRENT_MULTIPLIER_ID        = 0x0202U, /*!< DCCurrentMultiplier attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_CURRENT_DIVISOR_ID           = 0x0203U, /*!< DCCurrentDivisor attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_POWER_MULTIPLIER_ID          = 0x0204U, /*!< DCPowerMultiplier attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_POWER_DIVISOR_ID             = 0x0205U, /*!< DCPowerDivisor attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_ID                 = 0x0300U, /*!< ACFrequency attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_MIN_VALUE_ID       = 0x0301U, /*!< ACFrequencyMinValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_MAX_VALUE_ID       = 0x0302U, /*!< ACFrequencyMaxValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_NEUTRAL_CURRENT_ID              = 0x0303U, /*!< NeutralCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_TOTAL_ACTIVE_POWER_ID           = 0x0304U, /*!< TotalActivePower attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_TOTAL_REACTIVE_POWER_ID         = 0x0305U, /*!< TotalReactivePower attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_TOTAL_APPARENT_POWER_ID         = 0x0306U, /*!< TotalApparentPower attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASURED1ST_HARMONIC_CURRENT_ID = 0x0307U, /*!< Measured1stHarmonicCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASURED3RD_HARMONIC_CURRENT_ID = 0x0308U, /*!< Measured3rdHarmonicCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASURED5TH_HARMONIC_CURRENT_ID = 0x0309U, /*!< Measured5thHarmonicCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASURED7TH_HARMONIC_CURRENT_ID = 0x030aU, /*!< Measured7thHarmonicCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASURED9TH_HARMONIC_CURRENT_ID = 0x030bU, /*!< Measured9thHarmonicCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASURED11TH_HARMONIC_CURRENT_ID =
        0x030cU, /*!< Measured11thHarmonicCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASURED_PHASE1ST_HARMONIC_CURRENT_ID =
        0x030dU, /*!< MeasuredPhase1stHarmonicCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASURED_PHASE3RD_HARMONIC_CURRENT_ID =
        0x030eU, /*!< MeasuredPhase3rdHarmonicCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASURED_PHASE5TH_HARMONIC_CURRENT_ID =
        0x030fU, /*!< MeasuredPhase5thHarmonicCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASURED_PHASE7TH_HARMONIC_CURRENT_ID =
        0x0310U, /*!< MeasuredPhase7thHarmonicCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASURED_PHASE9TH_HARMONIC_CURRENT_ID =
        0x0311U, /*!< MeasuredPhase9thHarmonicCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_MEASURED_PHASE11TH_HARMONIC_CURRENT_ID =
        0x0312U, /*!< MeasuredPhase11thHarmonicCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_MULTIPLIER_ID     = 0x0400U, /*!< ACFrequencyMultiplier attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_DIVISOR_ID        = 0x0401U, /*!< ACFrequencyDivisor attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_POWER_MULTIPLIER_ID            = 0x0402U, /*!< PowerMultiplier attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_POWER_DIVISOR_ID               = 0x0403U, /*!< PowerDivisor attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_HARMONIC_CURRENT_MULTIPLIER_ID = 0x0404U, /*!< HarmonicCurrentMultiplier attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_PHASE_HARMONIC_CURRENT_MULTIPLIER_ID =
        0x0405U,                                                             /*!< PhaseHarmonicCurrentMultiplier attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_LINE_CURRENT_ID           = 0x0501U, /*!< LineCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_ACTIVE_CURRENT_ID         = 0x0502U, /*!< ActiveCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_REACTIVE_CURRENT_ID       = 0x0503U, /*!< ReactiveCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_ID            = 0x0505U, /*!< RMSVoltage attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_MIN_VALUE_ID  = 0x0506U, /*!< RMSVoltageMinValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_MAX_VALUE_ID  = 0x0507U, /*!< RMSVoltageMaxValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_CURRENT_ID            = 0x0508U, /*!< RMSCurrent attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_CURRENT_MIN_VALUE_ID  = 0x0509U, /*!< RMSCurrentMinValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_CURRENT_MAX_VALUE_ID  = 0x050aU, /*!< RMSCurrentMaxValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_ID           = 0x050bU, /*!< ActivePower attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_VALUE_ID = 0x050cU, /*!< ActivePowerMinValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_VALUE_ID = 0x050dU, /*!< ActivePowerMaxValue attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_REACTIVE_POWER_ID         = 0x050eU, /*!< ReactivePower attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_APPARENT_POWER_ID         = 0x050fU, /*!< ApparentPower attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_POWER_FACTOR_ID           = 0x0510U, /*!< PowerFactor attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_VOLTAGE_MEASUREMENT_PERIOD_ID =
        0x0511U, /*!< AverageRMSVoltageMeasurementPeriod attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_OVER_VOLTAGE_COUNTER_ID =
        0x0512U, /*!< AverageRMSOverVoltageCounter attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_UNDER_VOLTAGE_COUNTER_ID =
        0x0513U, /*!< AverageRMSUnderVoltageCounter attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_EXTREME_OVER_VOLTAGE_PERIOD_ID =
        0x0514U, /*!< RMSExtremeOverVoltagePeriod attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_EXTREME_UNDER_VOLTAGE_PERIOD_ID =
        0x0515U,                                                                 /*!< RMSExtremeUnderVoltagePeriod attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SAG_PERIOD_ID     = 0x0516U, /*!< RMSVoltageSagPeriod attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SWELL_PERIOD_ID   = 0x0517U, /*!< RMSVoltageSwellPeriod attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_VOLTAGE_MULTIPLIER_ID      = 0x0600U, /*!< ACVoltageMultiplier attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_VOLTAGE_DIVISOR_ID         = 0x0601U, /*!< ACVoltageDivisor attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_CURRENT_MULTIPLIER_ID      = 0x0602U, /*!< ACCurrentMultiplier attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_CURRENT_DIVISOR_ID         = 0x0603U, /*!< ACCurrentDivisor attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_POWER_MULTIPLIER_ID        = 0x0604U, /*!< ACPowerMultiplier attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_POWER_DIVISOR_ID           = 0x0605U, /*!< ACPowerDivisor attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_OVERLOAD_ALARMS_MASK_ID    = 0x0700U, /*!< DCOverloadAlarmsMask attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_OVERLOAD_ID        = 0x0701U, /*!< DCVoltageOverload attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_DC_CURRENT_OVERLOAD_ID        = 0x0702U, /*!< DCCurrentOverload attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_ALARMS_MASK_ID             = 0x0800U, /*!< ACAlarmsMask attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_VOLTAGE_OVERLOAD_ID        = 0x0801U, /*!< ACVoltageOverload attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_CURRENT_OVERLOAD_ID        = 0x0802U, /*!< ACCurrentOverload attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_ACTIVE_POWER_OVERLOAD_ID   = 0x0803U, /*!< ACActivePowerOverload attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AC_REACTIVE_POWER_OVERLOAD_ID = 0x0804U, /*!< ACReactivePowerOverload attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_OVER_VOLTAGE_ID   = 0x0805U, /*!< AverageRMSOverVoltage attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_UNDER_VOLTAGE_ID  = 0x0806U, /*!< AverageRMSUnderVoltage attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_EXTREME_OVER_VOLTAGE_ID   = 0x0807U, /*!< RMSExtremeOverVoltage attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_EXTREME_UNDER_VOLTAGE_ID  = 0x0808U, /*!< RMSExtremeUnderVoltage attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SAG_ID            = 0x0809U, /*!< RMSVoltageSag attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SWELL_ID          = 0x080aU, /*!< RMSVoltageSwell attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_LINE_CURRENT_PH_B_ID          = 0x0901U, /*!< LineCurrentPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_ACTIVE_CURRENT_PH_B_ID        = 0x0902U, /*!< ActiveCurrentPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_REACTIVE_CURRENT_PH_B_ID      = 0x0903U, /*!< ReactiveCurrentPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_PH_B_ID           = 0x0905U, /*!< RMSVoltagePhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_MIN_PH_B_ID       = 0x0906U, /*!< RMSVoltageMinPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_MAX_PH_B_ID       = 0x0907U, /*!< RMSVoltageMaxPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_CURRENT_PH_B_ID           = 0x0908U, /*!< RMSCurrentPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_CURRENT_MIN_PH_B_ID       = 0x0909U, /*!< RMSCurrentMinPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_CURRENT_MAX_PH_B_ID       = 0x090aU, /*!< RMSCurrentMaxPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_PH_B_ID          = 0x090bU, /*!< ActivePowerPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_PH_B_ID      = 0x090cU, /*!< ActivePowerMinPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_PH_B_ID      = 0x090dU, /*!< ActivePowerMaxPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_REACTIVE_POWER_PH_B_ID        = 0x090eU, /*!< ReactivePowerPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_APPARENT_POWER_PH_B_ID        = 0x090fU, /*!< ApparentPowerPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_POWER_FACTOR_PH_B_ID          = 0x0910U, /*!< PowerFactorPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_VOLTAGE_MEASUREMENT_PERIOD_PH_B_ID =
        0x0911U, /*!< AverageRMSVoltageMeasurementPeriodPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_OVER_VOLTAGE_COUNTER_PH_B_ID =
        0x0912U, /*!< AverageRMSOverVoltageCounterPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_UNDER_VOLTAGE_COUNTER_PH_B_ID =
        0x0913U, /*!< AverageRMSUnderVoltageCounterPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_EXTREME_OVER_VOLTAGE_PERIOD_PH_B_ID =
        0x0914U, /*!< RMSExtremeOverVoltagePeriodPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_EXTREME_UNDER_VOLTAGE_PERIOD_PH_B_ID =
        0x0915U, /*!< RMSExtremeUnderVoltagePeriodPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SAG_PERIOD_PH_B_ID   = 0x0916U, /*!< RMSVoltageSagPeriodPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SWELL_PERIOD_PH_B_ID = 0x0917U, /*!< RMSVoltageSwellPeriodPhB attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_LINE_CURRENT_PH_C_ID             = 0x0a01U, /*!< LineCurrentPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_ACTIVE_CURRENT_PH_C_ID           = 0x0a02U, /*!< ActiveCurrentPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_REACTIVE_CURRENT_PH_C_ID         = 0x0a03U, /*!< ReactiveCurrentPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_PH_C_ID              = 0x0a05U, /*!< RMSVoltagePhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_MIN_PH_C_ID          = 0x0a06U, /*!< RMSVoltageMinPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_MAX_PH_C_ID          = 0x0a07U, /*!< RMSVoltageMaxPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_CURRENT_PH_C_ID              = 0x0a08U, /*!< RMSCurrentPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_CURRENT_MIN_PH_C_ID          = 0x0a09U, /*!< RMSCurrentMinPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_CURRENT_MAX_PH_C_ID          = 0x0a0aU, /*!< RMSCurrentMaxPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_PH_C_ID             = 0x0a0bU, /*!< ActivePowerPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_PH_C_ID         = 0x0a0cU, /*!< ActivePowerMinPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_PH_C_ID         = 0x0a0dU, /*!< ActivePowerMaxPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_REACTIVE_POWER_PH_C_ID           = 0x0a0eU, /*!< ReactivePowerPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_APPARENT_POWER_PH_C_ID           = 0x0a0fU, /*!< ApparentPowerPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_POWER_FACTOR_PH_C_ID             = 0x0a10U, /*!< PowerFactorPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_VOLTAGE_MEASUREMENT_PERIOD_PH_C_ID =
        0x0a11U, /*!< AverageRMSVoltageMeasurementPeriodPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_OVER_VOLTAGE_COUNTER_PH_C_ID =
        0x0a12U, /*!< AverageRMSOverVoltageCounterPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_UNDER_VOLTAGE_COUNTER_PH_C_ID =
        0x0a13U, /*!< AverageRMSUnderVoltageCounterPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_EXTREME_OVER_VOLTAGE_PERIOD_PH_C_ID =
        0x0a14U, /*!< RMSExtremeOverVoltagePeriodPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_EXTREME_UNDER_VOLTAGE_PERIOD_PH_C_ID =
        0x0a15U, /*!< RMSExtremeUnderVoltagePeriodPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SAG_PERIOD_PH_C_ID   = 0x0a16U, /*!< RMSVoltageSagPeriodPhC attribute. */
    EZB_ZCL_ATTR_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SWELL_PERIOD_PH_C_ID = 0x0a17U, /*!< RMSVoltageSwellPeriodPhC attribute. */
} ezb_zcl_electrical_measurement_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the ElectricalMeasurement server cluster.
 */
typedef struct ezb_zcl_electrical_measurement_cluster_server_config_s {
    uint32_t measurement_type; /*!< Configurable mandatory MeasurementType attribute */
} ezb_zcl_electrical_measurement_cluster_server_config_t;

/**
 * @brief Bitmap for ZCL MeasurementType attribute of ElectricalMeasurement.
 */
typedef enum {
    EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_ACTIVE_MEASUREMENT_AC     = 0x00000001U, /*!< ActiveMeasurementAC */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_REACTIVE_MEASUREMENT_AC   = 0x00000002U, /*!< ReactiveMeasurementAC */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_APPARENT_MEASUREMENT_AC   = 0x00000004U, /*!< ApparentMeasurementAC */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_PHASE_A_MEASUREMENT       = 0x00000008U, /*!< PhaseAMeasurement */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_PHASE_B_MEASUREMENT       = 0x00000010U, /*!< PhaseBMeasurement */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_PHASE_C_MEASUREMENT       = 0x00000020U, /*!< PhaseCMeasurement */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_DC_MEASUREMENT            = 0x00000040U, /*!< DCMeasurement */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_HARMONICS_MEASUREMENT     = 0x00000080U, /*!< HarmonicsMeasurement */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_POWER_QUALITY_MEASUREMENT = 0x00000100U, /*!< PowerQualityMeasurement */
} ezb_zcl_electrical_measurement_server_measurement_type_t;

/**
 * @brief Bitmap for ZCL DCOverloadAlarmsMask attribute of ElectricalMeasurement.
 */
typedef enum {
    EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_OVERLOAD_ALARMS_MASK_VOLTAGE_OVERLOAD = 0x01U, /*!< VoltageOverload */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_OVERLOAD_ALARMS_MASK_CURRENT_OVERLOAD = 0x02U, /*!< CurrentOverload */
} ezb_zcl_electrical_measurement_server_dc_overload_alarms_mask_t;

/**
 * @brief Bitmap for ZCL ACAlarmsMask attribute of ElectricalMeasurement.
 */
typedef enum {
    EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ALARMS_MASK_VOLTAGE_OVERLOAD          = 0x0001U, /*!< VoltageOverload */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ALARMS_MASK_CURRENT_OVERLOAD          = 0x0002U, /*!< CurrentOverload */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ALARMS_MASK_ACTIVE_POWER_OVERLOAD     = 0x0004U, /*!< ActivePowerOverload */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ALARMS_MASK_REACTIVE_POWER_OVERLOAD   = 0x0008U, /*!< ReactivePowerOverload */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ALARMS_MASK_AVERAGE_RMS_OVER_VOLTAGE  = 0x0010U, /*!< AverageRMSOverVoltage */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ALARMS_MASK_AVERAGE_RMS_UNDER_VOLTAGE = 0x0020U, /*!< AverageRMSUnderVoltage */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ALARMS_MASK_RMS_EXTREME_OVER_VOLTAGE  = 0x0040U, /*!< RMSExtremeOverVoltage */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ALARMS_MASK_RMS_EXTREME_UNDER_VOLTAGE = 0x0080U, /*!< RMSExtremeUnderVoltage */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ALARMS_MASK_RMS_VOLTAGE_SAG           = 0x0100U, /*!< RMSVoltageSag */
    EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ALARMS_MASK_RMS_VOLTAGE_SWELL         = 0x0200U, /*!< RMSVoltageSwell */
} ezb_zcl_electrical_measurement_server_ac_alarms_mask_t;

/** @brief Default value of MeasurementType in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_DEFAULT_VALUE (0x00000000)

/** @brief Minimum value of MeasurementType in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_MIN_VALUE (0x00000000)

/** @brief Maximum value of MeasurementType in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASUREMENT_TYPE_MAX_VALUE (0xffffffff)
/** @brief Default value of DCVoltage in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of DCVoltage in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MIN_VALUE (0x8001)

/** @brief Maximum value of DCVoltage in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MAX_VALUE (0x7fff)
/** @brief Default value of DCVoltageMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MIN_VALUE_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of DCVoltageMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MIN_VALUE_MIN_VALUE (0x8001)

/** @brief Maximum value of DCVoltageMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MIN_VALUE_MAX_VALUE (0x7fff)
/** @brief Default value of DCVoltageMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MAX_VALUE_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of DCVoltageMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MAX_VALUE_MIN_VALUE (0x8001)

/** @brief Maximum value of DCVoltageMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MAX_VALUE_MAX_VALUE (0x7fff)
/** @brief Default value of DCCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of DCCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_MIN_VALUE (0x8001)

/** @brief Maximum value of DCCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of DCCurrentMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_MIN_VALUE_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of DCCurrentMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_MIN_VALUE_MIN_VALUE (0x8001)

/** @brief Maximum value of DCCurrentMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_MIN_VALUE_MAX_VALUE (0x7fff)
/** @brief Default value of DCCurrentMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_MAX_VALUE_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of DCCurrentMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_MAX_VALUE_MIN_VALUE (0x8001)

/** @brief Maximum value of DCCurrentMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_MAX_VALUE_MAX_VALUE (0x7fff)
/** @brief Default value of DCPower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of DCPower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_MIN_VALUE (0x8001)

/** @brief Maximum value of DCPower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_MAX_VALUE (0x7fff)
/** @brief Default value of DCPowerMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_MIN_VALUE_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of DCPowerMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_MIN_VALUE_MIN_VALUE (0x8001)

/** @brief Maximum value of DCPowerMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_MIN_VALUE_MAX_VALUE (0x7fff)
/** @brief Default value of DCPowerMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_MAX_VALUE_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of DCPowerMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_MAX_VALUE_MIN_VALUE (0x8001)

/** @brief Maximum value of DCPowerMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_MAX_VALUE_MAX_VALUE (0x7fff)
/** @brief Default value of DCVoltageMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MULTIPLIER_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of DCVoltageMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MULTIPLIER_MIN_VALUE (0x0001)

/** @brief Maximum value of DCVoltageMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_MULTIPLIER_MAX_VALUE (0xffff)
/** @brief Default value of DCVoltageDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_DIVISOR_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of DCVoltageDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_DIVISOR_MIN_VALUE (0x0001)

/** @brief Maximum value of DCVoltageDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_DIVISOR_MAX_VALUE (0xffff)
/** @brief Default value of DCCurrentMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_MULTIPLIER_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of DCCurrentMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_MULTIPLIER_MIN_VALUE (0x0001)

/** @brief Maximum value of DCCurrentMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_MULTIPLIER_MAX_VALUE (0xffff)
/** @brief Default value of DCCurrentDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_DIVISOR_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of DCCurrentDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_DIVISOR_MIN_VALUE (0x0001)

/** @brief Maximum value of DCCurrentDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_DIVISOR_MAX_VALUE (0xffff)
/** @brief Default value of DCPowerMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_MULTIPLIER_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of DCPowerMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_MULTIPLIER_MIN_VALUE (0x0001)

/** @brief Maximum value of DCPowerMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_MULTIPLIER_MAX_VALUE (0xffff)
/** @brief Default value of DCPowerDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_DIVISOR_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of DCPowerDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_DIVISOR_MIN_VALUE (0x0001)

/** @brief Maximum value of DCPowerDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_POWER_DIVISOR_MAX_VALUE (0xffff)
/** @brief Default value of ACFrequency in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_DEFAULT_VALUE (0xffff)

/** @brief Default value of ACFrequencyMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_MIN_VALUE_DEFAULT_VALUE (0xffff)

/** @brief Default value of ACFrequencyMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_MAX_VALUE_DEFAULT_VALUE (0xffff)

/** @brief Default value of NeutralCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_NEUTRAL_CURRENT_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of TotalActivePower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_TOTAL_ACTIVE_POWER_MIN_VALUE (0xff800001)

/** @brief Maximum value of TotalActivePower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_TOTAL_ACTIVE_POWER_MAX_VALUE (0x007fffff)

/** @brief Minimum value of TotalReactivePower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_TOTAL_REACTIVE_POWER_MIN_VALUE (0xff800001)

/** @brief Maximum value of TotalReactivePower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_TOTAL_REACTIVE_POWER_MAX_VALUE (0x007fffff)

/** @brief Minimum value of TotalApparentPower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_TOTAL_APPARENT_POWER_MIN_VALUE (0x00000000)

/** @brief Maximum value of TotalApparentPower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_TOTAL_APPARENT_POWER_MAX_VALUE (0xffffffff)
/** @brief Default value of Measured1stHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED1ST_HARMONIC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of Measured1stHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED1ST_HARMONIC_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of Measured1stHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED1ST_HARMONIC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of Measured3rdHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED3RD_HARMONIC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of Measured3rdHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED3RD_HARMONIC_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of Measured3rdHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED3RD_HARMONIC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of Measured5thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED5TH_HARMONIC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of Measured5thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED5TH_HARMONIC_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of Measured5thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED5TH_HARMONIC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of Measured7thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED7TH_HARMONIC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of Measured7thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED7TH_HARMONIC_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of Measured7thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED7TH_HARMONIC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of Measured9thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED9TH_HARMONIC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of Measured9thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED9TH_HARMONIC_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of Measured9thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED9TH_HARMONIC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of Measured11thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED11TH_HARMONIC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of Measured11thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED11TH_HARMONIC_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of Measured11thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED11TH_HARMONIC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of MeasuredPhase1stHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE1ST_HARMONIC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of MeasuredPhase1stHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE1ST_HARMONIC_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of MeasuredPhase1stHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE1ST_HARMONIC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of MeasuredPhase3rdHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE3RD_HARMONIC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of MeasuredPhase3rdHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE3RD_HARMONIC_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of MeasuredPhase3rdHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE3RD_HARMONIC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of MeasuredPhase5thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE5TH_HARMONIC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of MeasuredPhase5thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE5TH_HARMONIC_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of MeasuredPhase5thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE5TH_HARMONIC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of MeasuredPhase7thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE7TH_HARMONIC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of MeasuredPhase7thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE7TH_HARMONIC_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of MeasuredPhase7thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE7TH_HARMONIC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of MeasuredPhase9thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE9TH_HARMONIC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of MeasuredPhase9thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE9TH_HARMONIC_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of MeasuredPhase9thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE9TH_HARMONIC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of MeasuredPhase11thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE11TH_HARMONIC_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of MeasuredPhase11thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE11TH_HARMONIC_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of MeasuredPhase11thHarmonicCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_MEASURED_PHASE11TH_HARMONIC_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of ACFrequencyMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_MULTIPLIER_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of ACFrequencyMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_MULTIPLIER_MIN_VALUE (0x0001)

/** @brief Maximum value of ACFrequencyMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_MULTIPLIER_MAX_VALUE (0xffff)
/** @brief Default value of ACFrequencyDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_DIVISOR_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of ACFrequencyDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_DIVISOR_MIN_VALUE (0x0001)

/** @brief Maximum value of ACFrequencyDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_FREQUENCY_DIVISOR_MAX_VALUE (0xffff)
/** @brief Default value of PowerMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_MULTIPLIER_DEFAULT_VALUE (0x00000001)

/** @brief Minimum value of PowerMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_MULTIPLIER_MIN_VALUE (0x00000000)

/** @brief Maximum value of PowerMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_MULTIPLIER_MAX_VALUE (0xffffffff)
/** @brief Default value of PowerDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_DIVISOR_DEFAULT_VALUE (0x00000001)

/** @brief Minimum value of PowerDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_DIVISOR_MIN_VALUE (0x00000000)

/** @brief Maximum value of PowerDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_DIVISOR_MAX_VALUE (0xffffffff)
/** @brief Default value of HarmonicCurrentMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_HARMONIC_CURRENT_MULTIPLIER_DEFAULT_VALUE (0x00)

/** @brief Minimum value of HarmonicCurrentMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_HARMONIC_CURRENT_MULTIPLIER_MIN_VALUE (0x81)

/** @brief Maximum value of HarmonicCurrentMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_HARMONIC_CURRENT_MULTIPLIER_MAX_VALUE (0x7f)
/** @brief Default value of PhaseHarmonicCurrentMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_PHASE_HARMONIC_CURRENT_MULTIPLIER_DEFAULT_VALUE (0x00)

/** @brief Minimum value of PhaseHarmonicCurrentMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_PHASE_HARMONIC_CURRENT_MULTIPLIER_MIN_VALUE (0x81)

/** @brief Maximum value of PhaseHarmonicCurrentMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_PHASE_HARMONIC_CURRENT_MULTIPLIER_MAX_VALUE (0x7f)
/** @brief Default value of LineCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_LINE_CURRENT_DEFAULT_VALUE (0xffff)

/** @brief Default value of ActiveCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ActiveCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of ActiveCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of ReactiveCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_CURRENT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ReactiveCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_CURRENT_MIN_VALUE (0x8000)

/** @brief Maximum value of ReactiveCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_CURRENT_MAX_VALUE (0x7fff)
/** @brief Default value of RMSVoltage in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_DEFAULT_VALUE (0xffff)

/** @brief Default value of RMSVoltageMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_MIN_VALUE_DEFAULT_VALUE (0xffff)

/** @brief Default value of RMSVoltageMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_MAX_VALUE_DEFAULT_VALUE (0xffff)

/** @brief Default value of RMSCurrent in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_CURRENT_DEFAULT_VALUE (0xffff)

/** @brief Default value of RMSCurrentMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_CURRENT_MIN_VALUE_DEFAULT_VALUE (0xffff)

/** @brief Default value of RMSCurrentMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_CURRENT_MAX_VALUE_DEFAULT_VALUE (0xffff)

/** @brief Default value of ActivePower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ActivePower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_VALUE (0x8000)

/** @brief Maximum value of ActivePower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_VALUE (0x7fff)
/** @brief Default value of ActivePowerMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_VALUE_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ActivePowerMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_VALUE_MIN_VALUE (0x8000)

/** @brief Maximum value of ActivePowerMinValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_VALUE_MAX_VALUE (0x7fff)
/** @brief Default value of ActivePowerMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_VALUE_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ActivePowerMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_VALUE_MIN_VALUE (0x8000)

/** @brief Maximum value of ActivePowerMaxValue in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_VALUE_MAX_VALUE (0x7fff)
/** @brief Default value of ReactivePower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_POWER_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ReactivePower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_POWER_MIN_VALUE (0x8000)

/** @brief Maximum value of ReactivePower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_POWER_MAX_VALUE (0x7fff)
/** @brief Default value of ApparentPower in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_APPARENT_POWER_DEFAULT_VALUE (0xffff)

/** @brief Default value of PowerFactor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_FACTOR_DEFAULT_VALUE (0x00)

/** @brief Minimum value of PowerFactor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_FACTOR_MIN_VALUE (0xc0)

/** @brief Maximum value of PowerFactor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_FACTOR_MAX_VALUE (0x64)
/** @brief Default value of AverageRMSVoltageMeasurementPeriod in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_VOLTAGE_MEASUREMENT_PERIOD_DEFAULT_VALUE (0x0000)

/** @brief Default value of AverageRMSOverVoltageCounter in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_OVER_VOLTAGE_COUNTER_DEFAULT_VALUE (0x0000)

/** @brief Default value of AverageRMSUnderVoltageCounter in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_UNDER_VOLTAGE_COUNTER_DEFAULT_VALUE (0x0000)

/** @brief Default value of RMSExtremeOverVoltagePeriod in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_EXTREME_OVER_VOLTAGE_PERIOD_DEFAULT_VALUE (0x0000)

/** @brief Default value of RMSExtremeUnderVoltagePeriod in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_EXTREME_UNDER_VOLTAGE_PERIOD_DEFAULT_VALUE (0x0000)

/** @brief Default value of RMSVoltageSagPeriod in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SAG_PERIOD_DEFAULT_VALUE (0x0000)

/** @brief Default value of RMSVoltageSwellPeriod in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SWELL_PERIOD_DEFAULT_VALUE (0x0000)

/** @brief Default value of ACVoltageMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_VOLTAGE_MULTIPLIER_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of ACVoltageMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_VOLTAGE_MULTIPLIER_MIN_VALUE (0x0001)

/** @brief Maximum value of ACVoltageMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_VOLTAGE_MULTIPLIER_MAX_VALUE (0xffff)
/** @brief Default value of ACVoltageDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_VOLTAGE_DIVISOR_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of ACVoltageDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_VOLTAGE_DIVISOR_MIN_VALUE (0x0001)

/** @brief Maximum value of ACVoltageDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_VOLTAGE_DIVISOR_MAX_VALUE (0xffff)
/** @brief Default value of ACCurrentMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_CURRENT_MULTIPLIER_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of ACCurrentMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_CURRENT_MULTIPLIER_MIN_VALUE (0x0001)

/** @brief Maximum value of ACCurrentMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_CURRENT_MULTIPLIER_MAX_VALUE (0xffff)
/** @brief Default value of ACCurrentDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_CURRENT_DIVISOR_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of ACCurrentDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_CURRENT_DIVISOR_MIN_VALUE (0x0001)

/** @brief Maximum value of ACCurrentDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_CURRENT_DIVISOR_MAX_VALUE (0xffff)
/** @brief Default value of ACPowerMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_POWER_MULTIPLIER_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of ACPowerMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_POWER_MULTIPLIER_MIN_VALUE (0x0001)

/** @brief Maximum value of ACPowerMultiplier in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_POWER_MULTIPLIER_MAX_VALUE (0xffff)
/** @brief Default value of ACPowerDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_POWER_DIVISOR_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of ACPowerDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_POWER_DIVISOR_MIN_VALUE (0x0001)

/** @brief Maximum value of ACPowerDivisor in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_POWER_DIVISOR_MAX_VALUE (0xffff)
/** @brief Default value of DCOverloadAlarmsMask in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_OVERLOAD_ALARMS_MASK_DEFAULT_VALUE (0x00)

/** @brief Default value of DCVoltageOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_OVERLOAD_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of DCVoltageOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_OVERLOAD_MIN_VALUE (0x8000)

/** @brief Maximum value of DCVoltageOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_VOLTAGE_OVERLOAD_MAX_VALUE (0x7fff)
/** @brief Default value of DCCurrentOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_OVERLOAD_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of DCCurrentOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_OVERLOAD_MIN_VALUE (0x8000)

/** @brief Maximum value of DCCurrentOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_DC_CURRENT_OVERLOAD_MAX_VALUE (0x7fff)
/** @brief Default value of ACAlarmsMask in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ALARMS_MASK_DEFAULT_VALUE (0x0000)

/** @brief Default value of ACVoltageOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_VOLTAGE_OVERLOAD_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of ACVoltageOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_VOLTAGE_OVERLOAD_MIN_VALUE (0x8000)

/** @brief Maximum value of ACVoltageOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_VOLTAGE_OVERLOAD_MAX_VALUE (0x7fff)
/** @brief Default value of ACCurrentOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_CURRENT_OVERLOAD_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of ACCurrentOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_CURRENT_OVERLOAD_MIN_VALUE (0x8000)

/** @brief Maximum value of ACCurrentOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_CURRENT_OVERLOAD_MAX_VALUE (0x7fff)
/** @brief Default value of ACActivePowerOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ACTIVE_POWER_OVERLOAD_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of ACActivePowerOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ACTIVE_POWER_OVERLOAD_MIN_VALUE (0x8000)

/** @brief Maximum value of ACActivePowerOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_ACTIVE_POWER_OVERLOAD_MAX_VALUE (0x7fff)
/** @brief Default value of ACReactivePowerOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_REACTIVE_POWER_OVERLOAD_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of ACReactivePowerOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_REACTIVE_POWER_OVERLOAD_MIN_VALUE (0x8000)

/** @brief Maximum value of ACReactivePowerOverload in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AC_REACTIVE_POWER_OVERLOAD_MAX_VALUE (0x7fff)

/** @brief Minimum value of AverageRMSOverVoltage in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_OVER_VOLTAGE_MIN_VALUE (0x8000)

/** @brief Maximum value of AverageRMSOverVoltage in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_OVER_VOLTAGE_MAX_VALUE (0x7fff)

/** @brief Minimum value of AverageRMSUnderVoltage in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_UNDER_VOLTAGE_MIN_VALUE (0x8000)

/** @brief Maximum value of AverageRMSUnderVoltage in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_UNDER_VOLTAGE_MAX_VALUE (0x7fff)

/** @brief Minimum value of RMSExtremeOverVoltage in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_EXTREME_OVER_VOLTAGE_MIN_VALUE (0x8000)

/** @brief Maximum value of RMSExtremeOverVoltage in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_EXTREME_OVER_VOLTAGE_MAX_VALUE (0x7fff)

/** @brief Minimum value of RMSExtremeUnderVoltage in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_EXTREME_UNDER_VOLTAGE_MIN_VALUE (0x8000)

/** @brief Maximum value of RMSExtremeUnderVoltage in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_EXTREME_UNDER_VOLTAGE_MAX_VALUE (0x7fff)

/** @brief Minimum value of RMSVoltageSag in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SAG_MIN_VALUE (0x8000)

/** @brief Maximum value of RMSVoltageSag in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SAG_MAX_VALUE (0x7fff)

/** @brief Minimum value of RMSVoltageSwell in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SWELL_MIN_VALUE (0x8000)

/** @brief Maximum value of RMSVoltageSwell in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SWELL_MAX_VALUE (0x7fff)
/** @brief Default value of LineCurrentPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_LINE_CURRENT_PH_B_DEFAULT_VALUE (0xffff)

/** @brief Default value of ActiveCurrentPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_CURRENT_PH_B_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ActiveCurrentPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_CURRENT_PH_B_MIN_VALUE (0x8000)

/** @brief Maximum value of ActiveCurrentPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_CURRENT_PH_B_MAX_VALUE (0x7fff)
/** @brief Default value of ReactiveCurrentPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_CURRENT_PH_B_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ReactiveCurrentPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_CURRENT_PH_B_MIN_VALUE (0x8000)

/** @brief Maximum value of ReactiveCurrentPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_CURRENT_PH_B_MAX_VALUE (0x7fff)
/** @brief Default value of RMSVoltagePhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_PH_B_DEFAULT_VALUE (0xffff)

/** @brief Default value of RMSVoltageMinPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_MIN_PH_B_DEFAULT_VALUE (0x8000)

/** @brief Default value of RMSVoltageMaxPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_MAX_PH_B_DEFAULT_VALUE (0x8000)

/** @brief Default value of RMSCurrentPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_CURRENT_PH_B_DEFAULT_VALUE (0xffff)

/** @brief Default value of RMSCurrentMinPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_CURRENT_MIN_PH_B_DEFAULT_VALUE (0xffff)

/** @brief Default value of RMSCurrentMaxPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_CURRENT_MAX_PH_B_DEFAULT_VALUE (0xffff)

/** @brief Default value of ActivePowerPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_PH_B_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ActivePowerPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_PH_B_MIN_VALUE (0x8000)

/** @brief Maximum value of ActivePowerPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_PH_B_MAX_VALUE (0x7fff)
/** @brief Default value of ActivePowerMinPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_PH_B_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ActivePowerMinPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_PH_B_MIN_VALUE (0x8000)

/** @brief Maximum value of ActivePowerMinPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_PH_B_MAX_VALUE (0x7fff)
/** @brief Default value of ActivePowerMaxPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_PH_B_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ActivePowerMaxPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_PH_B_MIN_VALUE (0x8000)

/** @brief Maximum value of ActivePowerMaxPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_PH_B_MAX_VALUE (0x7fff)
/** @brief Default value of ReactivePowerPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_POWER_PH_B_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ReactivePowerPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_POWER_PH_B_MIN_VALUE (0x8000)

/** @brief Maximum value of ReactivePowerPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_POWER_PH_B_MAX_VALUE (0x7fff)
/** @brief Default value of ApparentPowerPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_APPARENT_POWER_PH_B_DEFAULT_VALUE (0xffff)

/** @brief Default value of PowerFactorPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_FACTOR_PH_B_DEFAULT_VALUE (0x00)

/** @brief Minimum value of PowerFactorPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_FACTOR_PH_B_MIN_VALUE (0xc0)

/** @brief Maximum value of PowerFactorPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_FACTOR_PH_B_MAX_VALUE (0x64)
/** @brief Default value of AverageRMSVoltageMeasurementPeriodPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_VOLTAGE_MEASUREMENT_PERIOD_PH_B_DEFAULT_VALUE (0x0000)

/** @brief Default value of AverageRMSOverVoltageCounterPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_OVER_VOLTAGE_COUNTER_PH_B_DEFAULT_VALUE (0x0000)

/** @brief Default value of AverageRMSUnderVoltageCounterPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_UNDER_VOLTAGE_COUNTER_PH_B_DEFAULT_VALUE (0x0000)

/** @brief Default value of RMSExtremeOverVoltagePeriodPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_EXTREME_OVER_VOLTAGE_PERIOD_PH_B_DEFAULT_VALUE (0x0000)

/** @brief Default value of RMSExtremeUnderVoltagePeriodPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_EXTREME_UNDER_VOLTAGE_PERIOD_PH_B_DEFAULT_VALUE (0x0000)

/** @brief Default value of RMSVoltageSagPeriodPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SAG_PERIOD_PH_B_DEFAULT_VALUE (0x0000)

/** @brief Default value of RMSVoltageSwellPeriodPhB in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SWELL_PERIOD_PH_B_DEFAULT_VALUE (0x0000)

/** @brief Default value of LineCurrentPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_LINE_CURRENT_PH_C_DEFAULT_VALUE (0xffff)

/** @brief Default value of ActiveCurrentPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_CURRENT_PH_C_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ActiveCurrentPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_CURRENT_PH_C_MIN_VALUE (0x8000)

/** @brief Maximum value of ActiveCurrentPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_CURRENT_PH_C_MAX_VALUE (0x7fff)
/** @brief Default value of ReactiveCurrentPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_CURRENT_PH_C_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ReactiveCurrentPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_CURRENT_PH_C_MIN_VALUE (0x8000)

/** @brief Maximum value of ReactiveCurrentPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_CURRENT_PH_C_MAX_VALUE (0x7fff)
/** @brief Default value of RMSVoltagePhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_PH_C_DEFAULT_VALUE (0xffff)

/** @brief Default value of RMSVoltageMinPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_MIN_PH_C_DEFAULT_VALUE (0x8000)

/** @brief Default value of RMSVoltageMaxPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_MAX_PH_C_DEFAULT_VALUE (0x8000)

/** @brief Default value of RMSCurrentPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_CURRENT_PH_C_DEFAULT_VALUE (0xffff)

/** @brief Default value of RMSCurrentMinPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_CURRENT_MIN_PH_C_DEFAULT_VALUE (0xffff)

/** @brief Default value of RMSCurrentMaxPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_CURRENT_MAX_PH_C_DEFAULT_VALUE (0xffff)

/** @brief Default value of ActivePowerPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_PH_C_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ActivePowerPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_PH_C_MIN_VALUE (0x8000)

/** @brief Maximum value of ActivePowerPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_PH_C_MAX_VALUE (0x7fff)
/** @brief Default value of ActivePowerMinPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_PH_C_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ActivePowerMinPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_PH_C_MIN_VALUE (0x8000)

/** @brief Maximum value of ActivePowerMinPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MIN_PH_C_MAX_VALUE (0x7fff)
/** @brief Default value of ActivePowerMaxPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_PH_C_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ActivePowerMaxPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_PH_C_MIN_VALUE (0x8000)

/** @brief Maximum value of ActivePowerMaxPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_ACTIVE_POWER_MAX_PH_C_MAX_VALUE (0x7fff)
/** @brief Default value of ReactivePowerPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_POWER_PH_C_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of ReactivePowerPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_POWER_PH_C_MIN_VALUE (0x8000)

/** @brief Maximum value of ReactivePowerPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_REACTIVE_POWER_PH_C_MAX_VALUE (0x7fff)
/** @brief Default value of ApparentPowerPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_APPARENT_POWER_PH_C_DEFAULT_VALUE (0xffff)

/** @brief Default value of PowerFactorPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_FACTOR_PH_C_DEFAULT_VALUE (0x00)

/** @brief Minimum value of PowerFactorPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_FACTOR_PH_C_MIN_VALUE (0xc0)

/** @brief Maximum value of PowerFactorPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_POWER_FACTOR_PH_C_MAX_VALUE (0x64)
/** @brief Default value of AverageRMSVoltageMeasurementPeriodPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_VOLTAGE_MEASUREMENT_PERIOD_PH_C_DEFAULT_VALUE (0x0000)

/** @brief Default value of AverageRMSOverVoltageCounterPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_OVER_VOLTAGE_COUNTER_PH_C_DEFAULT_VALUE (0x0000)

/** @brief Default value of AverageRMSUnderVoltageCounterPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_AVERAGE_RMS_UNDER_VOLTAGE_COUNTER_PH_C_DEFAULT_VALUE (0x0000)

/** @brief Default value of RMSExtremeOverVoltagePeriodPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_EXTREME_OVER_VOLTAGE_PERIOD_PH_C_DEFAULT_VALUE (0x0000)

/** @brief Default value of RMSExtremeUnderVoltagePeriodPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_EXTREME_UNDER_VOLTAGE_PERIOD_PH_C_DEFAULT_VALUE (0x0000)

/** @brief Default value of RMSVoltageSagPeriodPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SAG_PERIOD_PH_C_DEFAULT_VALUE (0x0000)

/** @brief Default value of RMSVoltageSwellPeriodPhC in ElectricalMeasurement cluster */
#define EZB_ZCL_ELECTRICAL_MEASUREMENT_RMS_VOLTAGE_SWELL_PERIOD_PH_C_DEFAULT_VALUE (0x0000)

/**
 * @brief Received Command identifiers for the ElectricalMeasurement cluster.
 */
typedef enum {
    EZB_ZCL_CMD_ELECTRICAL_MEASUREMENT_GET_PROFILE_INFO_RESPONSE_ID = 0x00U, /*!< GetProfileInfoResponse command. */
    EZB_ZCL_CMD_ELECTRICAL_MEASUREMENT_GET_MEASUREMENT_PROFILE_RESPONSE_ID =
        0x01U, /*!< GetMeasurementProfileResponse command. */
} ezb_zcl_electrical_measurement_server_cmd_id_t;

/**
 * @brief Received Command identifiers for the ElectricalMeasurement cluster.
 */
typedef enum {
    EZB_ZCL_CMD_ELECTRICAL_MEASUREMENT_GET_PROFILE_INFO_ID        = 0x00U, /*!< GetProfileInfo command. */
    EZB_ZCL_CMD_ELECTRICAL_MEASUREMENT_GET_MEASUREMENT_PROFILE_ID = 0x01U, /*!< GetMeasurementProfile command. */
} ezb_zcl_electrical_measurement_client_cmd_id_t;

typedef ezb_zcl_electrical_measurement_cluster_server_config_t ezb_zcl_electrical_measurement_cluster_config_t;

/**
 * @brief Add an attribute to an electrical_measurement cluster descriptor.
 *
 * @param cluster_desc Pointer to the electrical_measurement cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_electrical_measurement_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                               uint16_t               attr_id,
                                                               const void            *value);

/**
 * @brief Create an electrical_measurement cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the electrical_measurement cluster configuration structure, refer to
 * ezb_zcl_electrical_measurement_cluster_server_config_t or ezb_zcl_electrical_measurement_cluster_client_config_t or NULL
 * (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_electrical_measurement_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the ElectricalMeasurement cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_electrical_measurement_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the ElectricalMeasurement cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_electrical_measurement_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_ELECTRICAL_MEASUREMENT_CLIENT_ROLE_INIT ezb_zcl_electrical_measurement_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_ELECTRICAL_MEASUREMENT_SERVER_ROLE_INIT ezb_zcl_electrical_measurement_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
