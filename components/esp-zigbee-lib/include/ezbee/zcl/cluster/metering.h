/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @brief ZCL Metering cluster public header file.
 */

#pragma once

#include "metering_desc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration bitmapping for the Status attribute (Electricity).
 */
typedef enum {
    /*! CheckMeter bit is set to true when a non fatal problem has been detected on the meter */
    EZB_ZCL_METERING_ELECTRICITY_CHECK_METER = 1 << 0,
    /*! LowBattery bit is set to true when the battery needs maintenance */
    EZB_ZCL_METERING_ELECTRICITY_LOW_BATTERY = 1 << 1,
    /*! TamperDetect bit is set to true if a tamper event has been detected */
    EZB_ZCL_METERING_ELECTRICITY_TAMPER_DETECT = 1 << 2,
    /*! PowerFailure bit is set to true during a power outage */
    EZB_ZCL_METERING_ELECTRICITY_POWER_FAILURE = 1 << 3,
    /*! PowerQuality bit is set to true if a power quality event has been  detected such as a low voltage, high voltage */
    EZB_ZCL_METERING_ELECTRICITY_POWER_QUALITY = 1 << 4,
    /*! LeakDetect bit is set to true when a leak has been detected */
    EZB_ZCL_METERING_ELECTRICITY_LEAK_DETECT = 1 << 5,
    /*! ServiceDisconnectOpen bit is Set to true when the service has been disconnected to this premises */
    EZB_ZCL_METERING_ELECTRICITY_SERVICE_DISCONNECT_OPEN = 1 << 6,
    /*! Reserved bit */
    EZB_ZCL_METERING_ELECTRICITY_RESERVED = 1 << 7
} ezb_zcl_metering_status_electricity_t;

/**
 * @brief Enumeration bitmapping for the Status attribute (Gas).
 */
typedef enum {
    /*! CheckMeter bit is Set to true when a non fatal problem has been detected on the meter */
    EZB_ZCL_METERING_GAS_CHECK_METER = 1 << 0,
    /*! LowBattery bit is set to true when the battery needs maintenance */
    EZB_ZCL_METERING_GAS_LOW_BATTERY = 1 << 1,
    /*! TamperDetect bit is set to true if a tamper event has been detected */
    EZB_ZCL_METERING_GAS_TAMPER_DETECT = 1 << 2,
    /*! Reserved bit */
    EZB_ZCL_METERING_GAS_RESERVED = 1 << 3,
    /*! LowPressure bit is set to true when the pressure at the meter is below the meter's low pressure threshold value */
    EZB_ZCL_METERING_GAS_LOW_PRESSURE = 1 << 4,
    /*! LeakDetect bit is set to true when a leak has been detected */
    EZB_ZCL_METERING_GAS_LEAK_DETECT = 1 << 5,
    /*! ServiceDisconnect bit is set to true when the service has been disconnected to this premises */
    EZB_ZCL_METERING_GAS_SERVICE_DISCONNECT = 1 << 6,
    /*! ReverseFlow bit is set to true if flow detected in the opposite direction to  normal (from consumer to supplier) */
    EZB_ZCL_METERING_GAS_REVERSE_FLOW = 1 << 7

} ezb_zcl_metering_status_gas_t;

/**
 * @brief Enumeration bitmapping for the Status attribute (Water).
 */
typedef enum {
    /*! CheckMeter bit is Set to true when a non fatal problem has been detected on the meter */
    EZB_ZCL_METERING_WATER_CHECK_METER = 1 << 0,
    /*! LowBattery bit is set to true when the battery needs maintenance */
    EZB_ZCL_METERING_WATER_LOW_BATTERY = 1 << 1,
    /*! TamperDetect bit set to true if a tamper event has been detected */
    EZB_ZCL_METERING_WATER_TAMPER_DETECT = 1 << 2,
    /*! PipeEmpty bit is set to true when the service pipe at the meter is empty and there is no flow in either direction */
    EZB_ZCL_METERING_WATER_PIPE_EMPTY = 1 << 3,
    /*! LowPressure bit is Set to true when the pressure at the meter is below the meter's low pressure threshold value */
    EZB_ZCL_METERING_WATER_LOW_PRESSURE = 1 << 4,
    /*! LeakDetect bit is set to true when a leak has been detected */
    EZB_ZCL_METERING_WATER_LEAK_DETECT = 1 << 5,
    /*! ServiceDisconnect bit is set to true when the service has been disconnected to this premises */
    EZB_ZCL_METERING_WATER_SERVICE_DISCONNECT = 1 << 6,
    /*! ReverseFlow bit is Set to true if flow detected in the opposite direction to normal (from consumer to supplier) */
    EZB_ZCL_METERING_WATER_REVERSE_FLOW = 1 << 7

} ezb_zcl_metering_status_water_t;

/**
 * @brief Enumeration bitmapping for the Status attribute (Heat and Cooling).
 */
typedef enum {
    /*! CheckMeter bit is Set to true when a non fatal problem has been detected on the meter */
    EZB_ZCL_METERING_HCOOL_CHECK_METER = 1 << 0,
    /*! LowBattery bit is set to true when the battery needs maintenance */
    EZB_ZCL_METERING_HCOOL_LOW_BATTERY = 1 << 1,
    /*! TamperDetect bit is set to true if a tamper event has been detected */
    EZB_ZCL_METERING_HCOOL_TAMPER_DETECT = 1 << 2,
    /*! TemperatureSensor bit is Set to true when an error is detected on a temperature sensor at this premises */
    EZB_ZCL_METERING_HCOOL_TEMPERATURE_SENSOR = 1 << 3,
    /*! BurstDetect bit is set to true when a burst is detected on pipes at this premises */
    EZB_ZCL_METERING_HCOOL_BURST_DETECT = 1 << 4,
    /*! LeakDetect bit is set to true when a leak has been detected */
    EZB_ZCL_METERING_HCOOL_LEAK_DETECT = 1 << 5,
    /*! ServiceDisconnect bit is Set to true when the service has been disconnected to this premises */
    EZB_ZCL_METERING_HCOOL_SERVICE_DISCONNECT = 1 << 6,
    /*! FlowSensor bit is set to true when an error is detected on a flow sensor at this premises */
    EZB_ZCL_METERING_HCOOL_FLOW_SENSOR = 1 << 7
} ezb_zcl_metering_status_heat_cooling_t;

/**
 * @brief Enumeration bitmapping for the ExtendedStatus attribute (General Flags).
 */
typedef enum {
    /*! MeterCoverRemoved bit is set to true when the device detects the meter cover being removed */
    EZB_ZCL_METERING_METER_COVER_REMOVED = 1 << 0,
    /*! StrongMagneticFieldDetected bit is set to true when the device detects presence of a strong magnetic field */
    EZB_ZCL_METERING_STRONG_MAGNETIC_FIELD_DETECTED = 1 << 1,
    /*! BatteryFailure bit is set to true when the device detects that its battery has failed */
    EZB_ZCL_METERING_BATTERY_FAILURE = 1 << 2,
    /*! ProgramMemoryError bit is set to true when the device detects an error within its program (non-volatile) memory */
    EZB_ZCL_METERING_PROGRAM_MEMORY_ERROR = 1 << 3,
    /*! RAMError bit is set to true when the device detects an instance of a Random Access Memory error within the device
    memory */
    EZB_ZCL_METERING_RAM_ERROR = 1 << 4,
    /*! NVMemoryError bit is set to true when the device detects an instance of a Non Volatile memory error within the device
    memory this is a fatal meter error that will require the meter replacement */
    EZB_ZCL_METERING_NV_MEMORY_ERROR = 1 << 5,
    /*! MeasurementSystemError bit is set to true when the device detects an error within its measurement system */
    EZB_ZCL_METERING_MEASUREMENT_SYSTEM_ERROR = 1 << 6,
    /*! WatchdogError bit is set to true when the device has detected an instance of a watchdog reset event (following a
    catastrophic fault within the device) */
    EZB_ZCL_METERING_WATCHDOG_ERROR = 1 << 7,
    /*! SupplyDisconnectFailure bit is set to true when the device has detected that the valve has not closed as expected (for
    gas) or the contactor has not opened as expected (for electricity) */
    EZB_ZCL_METERING_SUPPLY_DISCONNECT_FAILURE = 1 << 8,
    /*! SupplyConnectFailure bit is set to true when the device has detected that the valve has not opened as expected (for gas)
    or the contactor has not closed as expected (for electricity) */
    EZB_ZCL_METERING_SUPPLY_CONNECT_FAILURE = 1 << 9,
    /*! MeasurementSWChanged/Tampered bit is set to true when the device detects that its measurement software has changed */
    EZB_ZCL_METERING_MEASUREMENT_SW_CHANGED = 1 << 10,
    /*! ClockInvalid bit is set to true when the device detects that its internal clock is invalid */
    EZB_ZCL_METERING_CLOCK_INVALID = 1 << 11,
    /*! TemperatureExceeded bit is set to true when the metering device's temperature exceeds a predefined limit.
    There are various reasons for temperature rise in metering devices */
    EZB_ZCL_METERING_TEMPERATURE_EXCEEDED = 1 << 12,
    /*! MoistureDetected bit is set to true when a sensor has detected the presence of moisture e.g. moisture in a gas line
    which can cause a drop in gas pressure, or moisture detected in the sealed component area within a water meter */
    EZB_ZCL_METERING_MOISTURE_DETECTED = 1 << 13,
    /* bits 14-23 reserved */
} ezb_zcl_metering_extstatus_general_t;

/**
 * @brief Enumeration bitmapping for the ExtendedStatus attribute (Electricity Meter specific Flags).
 */
typedef enum {
    /*! TerminalCoverRemoved bit is set to true when the device detects that its terminal cover has been removed */
    EZB_ZCL_METERING_ELECTRICITY_TERMINAL_COVER_REMOVED = 1L << 24,
    /*! IncorrectPolarity bit is set to true when the electricity meter detects incorrect polarity on the electricity supply */
    EZB_ZCL_METERING_ELECTRICITY_INCORRECT_POLARITY = 1L << 25,
    /*! CurrentWithNoVoltage bit is set to true when the meter has been tampered with, to disconnect the measurement function
    from the supply. Electricity is still flowing but not being  recorded */
    EZB_ZCL_METERING_ELECTRICITY_CURRENT_WITH_NO_VOLTAGE = 1L << 26,
    /*! LimitThresholdExceeded bit is set to true when the electricity meter detects that the load has exceeded the load limit
    threshold */
    EZB_ZCL_METERING_ELECTRICITY_LIMIT_THRESHOLD_EXCEEDED = 1L << 27,
    /*! UnderVoltage bit is set to true when the electricity meter indicates that the voltage measurement over the voltage
    measurement period is lower than the voltage threshold */
    EZB_ZCL_METERING_ELECTRICITY_UNDER_VOLTAGE = 1L << 28,
    /*! OverVoltage bit is set to true when the electricity meter indicates that the voltage measurement over the voltage
    measurement period is higher than the voltage threshold */
    EZB_ZCL_METERING_ELECTRICITY_OVER_VOLTAGE = 1L << 29,
} ezb_zcl_metering_extstatus_electricity_t;

/**
 * @brief Enumeration bitmapping for the ExtendedStatus attribute (Gas Meter specific Flags).
 */
typedef enum {
    /*! BatteryCoverRemoved bit is set to true when the gas meter detects that its battery cover has been removed */
    EZB_ZCL_METERING_GAS_BATTERY_COVER_REMOVED = 1L << 24,
    /*! TiltTamper bit is set to true when the meter detects a change in its physical properties (i.e. that it is being tilted,
    the tilt sensor has been activated or otherwise tampered with) */
    EZB_ZCL_METERING_GAS_TILT_TAMPER = 1L << 25,
    /*!< ExcessFlow bit is set to true when the gas meter detects excess flow (e.g. when local supply restoration is attempted)
     */
    EZB_ZCL_METERING_GAS_EXCESS_FLOW = 1L << 26,
    /* bits 27-63 reserved */
} ezb_zcl_metering_extstatus_gas_t;

/**
 * @brief Values for LowMediumHighStatus attribute.
 */
typedef enum {
    EZB_ZCL_METERING_STATUS_LOW    = 0x00, /*!< Low energy usage */
    EZB_ZCL_METERING_STATUS_MEDIUM = 0x01, /*!< Medium energy usage */
    EZB_ZCL_METERING_STATUS_HIGH   = 0x02, /*!< High energy usage */
} ezb_zcl_metering_low_medium_high_status_t;

/**
 * @brief Values for UnitOfMeasure attribute.
 */
typedef enum {
    EZB_ZCL_METERING_UNIT_KW_KWH_BINARY       = 0x00, /*!< kW, kWh binary value */
    EZB_ZCL_METERING_UNIT_M3_M3H_BINARY       = 0x01, /*!< m3, m3/h binary value */
    EZB_ZCL_METERING_UNIT_FT3_FT3H_BINARY     = 0x02, /*!< ft3, ft3/h binary value */
    EZB_ZCL_METERING_UNIT_CCF_CCFH_BINARY     = 0x03, /*!< ccf, ccf/h binary value */
    EZB_ZCL_METERING_UNIT_USGL_USGLH_BINARY   = 0x04, /*!< US gl, US gl/h binary value */
    EZB_ZCL_METERING_UNIT_IMPGL_IMPGLH_BINARY = 0x05, /*!< IMP gl, IMP gl/h binary value */
    EZB_ZCL_METERING_UNIT_BTU_BTUH_BINARY     = 0x06, /*!< BTU, BTU/h binary value */
    EZB_ZCL_METERING_UNIT_L_LH_BINARY         = 0x07, /*!< l, l/h binary value */
    EZB_ZCL_METERING_UNIT_KPAG_BINARY         = 0x08, /*!< kPA (gauge) binary value */
    EZB_ZCL_METERING_UNIT_KPAA_BINARY         = 0x09, /*!< kPA (absolute) binary value */
    EZB_ZCL_METERING_UNIT_MCF_MCFH_BINARY     = 0x0A, /*!< mcf, mcf/h binary value */
    EZB_ZCL_METERING_UNIT_UNITLESS_BINARY     = 0x0B, /*!< Unitless binary value */
    EZB_ZCL_METERING_UNIT_MJ_MJS_BINARY       = 0x0C, /*!< MJ, MJ/h binary value */
    EZB_ZCL_METERING_UNIT_KVAR_KVARH_BINARY   = 0x0D, /*!< kVar, kVar/h binary value */

    /* 0x0E to 0x7F reserved for future use */

    EZB_ZCL_METERING_UNIT_KW_KWH_BCD       = 0x80, /*!< kW, kWh BCD value */
    EZB_ZCL_METERING_UNIT_M3_M3H_BCD       = 0x81, /*!< m3, m3/h BCD value */
    EZB_ZCL_METERING_UNIT_FT3_FT3H_BCD     = 0x82, /*!< ft3, ft3/h BCD value */
    EZB_ZCL_METERING_UNIT_CCF_CCFH_BCD     = 0x83, /*!< ccf, ccf/h BCD value */
    EZB_ZCL_METERING_UNIT_USGL_USGLH_BCD   = 0x84, /*!< US gl, US gl/h BCD value */
    EZB_ZCL_METERING_UNIT_IMPGL_IMPGLH_BCD = 0x85, /*!< IMP gl, IMP gl/h BCD value */
    EZB_ZCL_METERING_UNIT_BTU_BTUH_BCD     = 0x86, /*!< BTU, BTU/h BCD value */
    EZB_ZCL_METERING_UNIT_L_LH_BCD         = 0x87, /*!< l, l/h BCD value */
    EZB_ZCL_METERING_UNIT_KPAG_BCD         = 0x88, /*!< kPA (gauge) BCD value */
    EZB_ZCL_METERING_UNIT_KPAA_BCD         = 0x89, /*!< kPA (absolute) BCD value */
    EZB_ZCL_METERING_UNIT_MCF_MCFH_BCD     = 0x8A, /*!< mcf, mcf/h BCD value */
    EZB_ZCL_METERING_UNIT_UNITLESS_BCD     = 0x8B, /*!< Unitless BCD value */
    EZB_ZCL_METERING_UNIT_MJ_MJS_BCD       = 0x8C, /*!< MJ, MJ/h BCD value */
    EZB_ZCL_METERING_UNIT_KVAR_KVARH_BCD   = 0x8D, /*!< kVar, kVar/h BCD value */

    EZB_ZCL_METERING_UNIT_BCD_RESERVED = 0x8E
    /*!< 0x8E to 0xFF reserved */
} ezb_zcl_metering_unit_of_measure_t;

/**
 * @brief Values for MeteringDeviceType attribute.
 */
typedef enum {
    EZB_ZCL_METERING_ELECTRIC_METERING = 0, /*!< Electric metering device */
    EZB_ZCL_METERING_GAS_METERING      = 1, /*!< Gas metering device */
    EZB_ZCL_METERING_WATER_METERING    = 2, /*!< Water metering device */
    EZB_ZCL_METERING_PRESSURE_METERING = 4, /*!< Pressure metering device */
    EZB_ZCL_METERING_HEAT_METERING     = 5, /*!< Heat metering device */
    EZB_ZCL_METERING_COOLING_METERING  = 6, /*!< Cooling metering device */
    EZB_ZCL_METERING_EUMD              = 7, /*!< End Use Measurement Device (EUMD) for metering electric vehicle charging */
    EZB_ZCL_METERING_PV_GENERATION_METERING              = 8,  /*!< PV Generation Metering device */
    EZB_ZCL_METERING_WIND_TURBINE_GENERATION_METERING    = 9,  /*!< Wind Turbine Generation Metering device */
    EZB_ZCL_METERING_WATER_TURBINE_GENERATION_METERING   = 10, /*!< Water Turbine Generation Metering device */
    EZB_ZCL_METERING_MICRO_GENERATION_METERING           = 11, /*!< Micro Generation Metering device */
    EZB_ZCL_METERING_SOLAR_HOT_WATER_GENERATION_METERING = 12, /*!< Solar Hot Water Generation Metering device */
    EZB_ZCL_METERING_ELECTRIC_METERING_ELEMENT_PHASE1    = 13, /*!< Electric Metering Element/Phase 1 */
    EZB_ZCL_METERING_ELECTRIC_METERING_ELEMENT_PHASE2    = 14, /*!< Electric Metering Element/Phase 2 */
    EZB_ZCL_METERING_ELECTRIC_METERING_ELEMENT_PHASE3    = 15, /*!< Electric Metering Element/Phase 3 */
    /* 16 to 126 reserved */
    EZB_ZCL_METERING_MIRRORED_ELECTRIC_METERING = 127, /*!< Mirrored Electric Metering device */
    EZB_ZCL_METERING_MIRRORED_GAS_METERING      = 128, /*!< Mirrored Gas Metering device */
    EZB_ZCL_METERING_MIRRORED_WATER_METERING    = 129, /*!< Mirrored Water Metering device */
    /* 130 == Mirrored Thermal Metering (deprecated) */
    EZB_ZCL_METERING_MIRRORED_PRESSURE_METERING = 131, /*!< Mirrored Pressure Metering device */
    EZB_ZCL_METERING_MIRRORED_HEAT_METERING     = 132, /*!< Mirrored Heat Metering device */
    EZB_ZCL_METERING_MIRRORED_COOLING_METERING  = 133, /*!< Mirrored Cooling Metering device */
    EZB_ZCL_METERING_MIRRORED_EUMD              = 134, /*!< Mirrored End Use Measurement Device (EUMD) for metering electric
                                                       vehicle charging */
    EZB_ZCL_METERING_MIRRORED_PV_GENERATION_METERING            = 135, /*!< Mirrored PV Generation Metering device */
    EZB_ZCL_METERING_MIRRORED_WIND_TURBINE_GENERATION_METERING  = 136, /*!< Mirrored Wind Turbine Generation Metering device */
    EZB_ZCL_METERING_MIRRORED_WATER_TURBINE_GENERATION_METERING = 137, /*!< Mirrored Water Turbine Generation Metering device */
    EZB_ZCL_METERING_MIRRORED_MICRO_GENERATION_METERING         = 138, /*!< Mirrored Micro Generation Metering device */
    EZB_ZCL_METERING_MIRRORED_SOLAR_HOT_WATER_GENERATION_METERING = 139, /*!< Mirrored Solar Hot Water Generation Metering
                                                                        device */
    EZB_ZCL_METERING_MIRRORED_ELECTRIC_METERING_ELEMENT_PHASE1 = 140,    /*!< Mirrored Electric Metering Element/Phase 1 */
    EZB_ZCL_METERING_MIRRORED_ELECTRIC_METERING_ELEMENT_PHASE2 = 141,    /*!< Mirrored Electric Metering Element/Phase 2 */
    EZB_ZCL_METERING_MIRRORED_ELECTRIC_METERING_ELEMENT_PHASE3 = 142,    /*!< Mirrored Electric Metering Element/Phase 3 */
    /* 143 to 255 reserved */
    EZB_ZCL_METERING_RESERVED = 143
} ezb_zcl_metering_device_type_t;

/**
 * @brief Values for TemperatureUnitOfMeasure attribute.
 */
typedef enum {
    EZB_ZCL_METERING_TEMPERATURE_UNIT_KELVIN_BINARY     = 0x00, /*!< K (Degrees Kelvin) in pure Binary format */
    EZB_ZCL_METERING_TEMPERATURE_UNIT_CELSIUS_BINARY    = 0x01, /*!< C (Degrees Celsius) in pure Binary format */
    EZB_ZCL_METERING_TEMPERATURE_UNIT_FAHRENHEIT_BINARY = 0x02, /*!< F (Degrees Fahrenheit) in pure Binary format */
    /* 0x03 - 0x7F reserved */
    EZB_ZCL_METERING_TEMPERATURE_UNIT_KELVIN_BCD     = 0x80, /*!< K (Degrees Kelvin) in BCD format */
    EZB_ZCL_METERING_TEMPERATURE_UNIT_CELSIUS_BCD    = 0x81, /*!< C (Degrees Celsius) in BCD format */
    EZB_ZCL_METERING_TEMPERATURE_UNIT_FAHRENHEIT_BCD = 0x82, /*!< F (Degrees Fahrenheit) in BCD format */
    /* 0x83 - 0xFF reserved */
} ezb_zcl_metering_temperature_unit_of_measure_t;

/**
 * @brief Generic alarm group: maps MeterStatus attribute to corresponding alarm.
 */
typedef enum {
    EZB_ZCL_METERING_ALARM_CHECK_METER                = 0x00, /*!< Check meter */
    EZB_ZCL_METERING_ALARM_LOW_BATTERY                = 0x01, /*!< Low battery */
    EZB_ZCL_METERING_ALARM_TAMPER_DETECT              = 0x02, /*!< Tamper detect */
    EZB_ZCL_METERING_ALARM_ELECTRICITY_POWER_FAILURE  = 0x03, /*!< Electricity: Power Failure */
    EZB_ZCL_METERING_ALARM_WATER_PIPE_EMPTY           = 0x03, /*!< Water: Pipe Empty */
    EZB_ZCL_METERING_ALARM_HEAT_TEMPERATURE_SENSOR    = 0x03, /*!< Heat: Temperature Sensor */
    EZB_ZCL_METERING_ALARM_COOLING_TEMPERATURE_SENSOR = 0x03, /*!< Cooling Temperature Sensor */
    EZB_ZCL_METERING_ALARM_ELECTRICITY_POWER_QUALITY  = 0x04, /*!< Electricity: Power Quality */
    EZB_ZCL_METERING_ALARM_GAS_LOW_PRESSURE           = 0x04, /*!< Gas: Low Pressure */
    EZB_ZCL_METERING_ALARM_WATER_LOW_PRESSURE         = 0x04, /*!< Water: Low Pressure */
    EZB_ZCL_METERING_ALARM_HEAT_BURST_DETECT          = 0x04, /*!< Heat: Burst Detect */
    EZB_ZCL_METERING_ALARM_COOLING_BURST_DETECT       = 0x04, /*!< Cooling: Burst Detect */
    EZB_ZCL_METERING_ALARM_LEAK_DETECT                = 0x05, /*!< Leak detect */
    EZB_ZCL_METERING_ALARM_SERVICE_DISCONNECT         = 0x06, /*!< Service Disconnect */
    EZB_ZCL_METERING_ALARM_ELECTRICITY_RESERVED       = 0x07, /*!< Electricity: Reserved */
    EZB_ZCL_METERING_ALARM_GAS_REVERSE_FLOW           = 0x07, /*!< Gas: Reverse Flow */
    EZB_ZCL_METERING_ALARM_WATER_REVERSE_FLOW         = 0x07, /*!< Water: Reverse Flow */
    EZB_ZCL_METERING_ALARM_HEAT_FLOW_SENSOR           = 0x07, /*!< Heat: Flow Sensor */
    EZB_ZCL_METERING_ALARM_COOLING_FLOW_SENSOR        = 0x07, /*!< Cooling: Flow Sensor */
    EZB_ZCL_METERING_ALARM_METER_COVER_REMOVED        = 0x08, /*!< Meter Cover Removed */
    EZB_ZCL_METERING_ALARM_METER_COVER_CLOSED         = 0x09, /*!< Meter Cover Closed */
    EZB_ZCL_METERING_ALARM_STRONG_MAGNETIC_FIELD      = 0x0A, /*!< Strong Magnetic Field */
    EZB_ZCL_METERING_ALARM_NO_STRONG_MAGNETIC_FIELD   = 0x0B, /*!< No Strong Magnetic Field */
    EZB_ZCL_METERING_ALARM_BATTERY_FAILURE            = 0x0C, /*!< Battery Failure */
    EZB_ZCL_METERING_ALARM_PROGRAM_MEMORY_ERROR       = 0x0D, /*!< Program Memory Error */
    EZB_ZCL_METERING_ALARM_RAM_ERROR                  = 0x0E, /*!< Ram Error */
    EZB_ZCL_METERING_ALARM_NV_MEMORY_ERROR            = 0x0F  /*!< NV Memory Error */
} ezb_zcl_metering_generic_alarm_group_t;

/**
 * @brief Electricity alarm group: alarms specific for electricity meters.
 */
typedef enum {
    EZB_ZCL_METERING_ALARM_LOW_VOLTAGE_L1         = 0x10, /*!< Low Voltage L1 */
    EZB_ZCL_METERING_ALARM_HIGH_VOLTAGE_L1        = 0x11, /*!< High Voltage L1 */
    EZB_ZCL_METERING_ALARM_LOW_VOLTAGE_L2         = 0x12, /*!< Low Voltage L2 */
    EZB_ZCL_METERING_ALARM_HIGH_VOLTAGE_L2        = 0x13, /*!< High Voltage L2 */
    EZB_ZCL_METERING_ALARM_LOW_VOLTAGE_L3         = 0x14, /*!< Low Voltage L3 */
    EZB_ZCL_METERING_ALARM_HIGH_VOLTAGE_L3        = 0x15, /*!< High Voltage L3 */
    EZB_ZCL_METERING_ALARM_OVER_CURRENT_L1        = 0x16, /*!< Over Current L1 */
    EZB_ZCL_METERING_ALARM_OVER_CURRENT_L2        = 0x17, /*!< Over Current L2 */
    EZB_ZCL_METERING_ALARM_OVER_CURRENT_L3        = 0x18, /*!< Over Current L3 */
    EZB_ZCL_METERING_ALARM_FREQUENCY_TOO_LOW_L1   = 0x19, /*!< Frequency too Low L1 */
    EZB_ZCL_METERING_ALARM_FREQUENCY_TOO_HIGH_L1  = 0x1A, /*!< Frequency too High L1 */
    EZB_ZCL_METERING_ALARM_FREQUENCY_TOO_LOW_L2   = 0x1B, /*!< Frequency too Low L2 */
    EZB_ZCL_METERING_ALARM_FREQUENCY_TOO_HIGH_L2  = 0x1C, /*!< Frequency too High L2 */
    EZB_ZCL_METERING_ALARM_FREQUENCY_TOO_LOW_L3   = 0x1D, /*!< Frequency too Low L3 */
    EZB_ZCL_METERING_ALARM_FREQUENCY_TOO_HIGH_L3  = 0x1E, /*!< Frequency too High L3 */
    EZB_ZCL_METERING_ALARM_GROUND_FAULT           = 0x1F, /*!< Ground Fault */
    EZB_ZCL_METERING_ALARM_ELECTRIC_TAMPER_DETECT = 0x20, /*!< Electric Tamper Detect */
    EZB_ZCL_METERING_ALARM_INCORRECT_POLARITY     = 0x21, /*!< Incorrect Polarity */
    EZB_ZCL_METERING_ALARM_CURRENT_NO_VOLTAGE     = 0x22, /*!< Current No Voltage */
    EZB_ZCL_METERING_ALARM_UNDER_VOLTAGE          = 0x23, /*!< Under Voltage */
    EZB_ZCL_METERING_ALARM_OVER_VOLTAGE           = 0x24, /*!< Over Voltage */
    EZB_ZCL_METERING_ALARM_NORMAL_VOLTAGE         = 0x25, /*!< Normal Voltage */
    EZB_ZCL_METERING_ALARM_PF_BELOW_THRESHOLD     = 0x26, /*!< PF Below Threshold */
    EZB_ZCL_METERING_ALARM_PF_ABOVE_THRESHOLD     = 0x27, /*!< PF Above Threshold */
    EZB_ZCL_METERING_ALARM_TERMINAL_COVER_REMOVED = 0x28, /*!< Terminal Cover Removed */
    EZB_ZCL_METERING_ALARM_TERMINAL_COVER_CLOSED  = 0x29, /*!< Terminal Cover Closed */
} ezb_zcl_metering_electricity_alarm_group_t;

/**
 * @brief Generic flow/pressure alarm group: Water, Heat, Cooling, or Gas meters.
 */
typedef enum {
    EZB_ZCL_METERING_ALARM_BURST_DETECT                    = 0x30, /*!< Burst detect */
    EZB_ZCL_METERING_ALARM_PRESSURE_TOO_LOW                = 0x31, /*!< Pressure too low */
    EZB_ZCL_METERING_ALARM_PRESSURE_TOO_HIGH               = 0x32, /*!< Pressure too high */
    EZB_ZCL_METERING_ALARM_FLOW_SENSOR_COMMUNICATION_ERROR = 0x33, /*!< Flow sensor communication error */
    EZB_ZCL_METERING_ALARM_FLOW_SENSOR_MEASUREMENT_FAULT   = 0x34, /*!< Flow sensor measurement fault */
    EZB_ZCL_METERING_ALARM_FLOW_SENSOR_REVERSE_FLOW        = 0x35, /*!< Flow sensor reverse flow */
    EZB_ZCL_METERING_ALARM_FLOW_SENSOR_AIR_DETECT          = 0x36, /*!< Flow sensor air detect */
    EZB_ZCL_METERING_ALARM_PIPE_EMPTY                      = 0x37, /*!< Pipe empty */
} ezb_zcl_metering_generic_flow_pressure_alarm_group_t;

/**
 * @brief Heat and cooling specific alarm group.
 */
typedef enum {
    EZB_ZCL_METERING_ALARM_INLET_TEMPERATURE_SENSOR_FAULT  = 0x50, /*!< Inlet Temperature Sensor Fault */
    EZB_ZCL_METERING_ALARM_OUTLET_TEMPERATURE_SENSOR_FAULT = 0x51, /*!< Outlet Temperature Sensor Fault */
} ezb_zcl_metering_heat_and_cooling_specific_alarm_group_t;

/** @brief The Gas Specific Alarm Group defines alarms specific for Gas meters */
typedef enum {
    EZB_ZCL_METERING_ALARM_TILT_TAMPER           = 0x60, /*!< Tilt Tamper */
    EZB_ZCL_METERING_ALARM_BATTERY_COVER_REMOVED = 0x61, /*!< Battery Cover Removed */
    EZB_ZCL_METERING_ALARM_BATTERY_COVER_CLOSED  = 0x62, /*!< Battery Cover Closed */
    EZB_ZCL_METERING_ALARM_EXCESS_FLOW           = 0x63, /*!< Excess Flow */
    EZB_ZCL_METERING_ALARM_TILT_TAMPER_ENDED     = 0x64, /*!< Tilt Tamper Ended */
} ezb_zcl_metering_gas_specific_alarm_group_t;

/**
 * @brief ZCL Metering extended generic alarm group.
 */
typedef enum {
    EZB_ZCM_METERING_ALARM_MEASUREMENT_SYSTEM_ERROR     = 0x70, /*!< Measurement System Error */
    EZB_ZCM_METERING_ALARM_WATCHDOG_ERROR               = 0x71, /*!< Watchdog Error */
    EZB_ZCM_METERING_ALARM_SUPPLY_DISCONNECT_FAILURE    = 0x72, /*!< Supply Disconnect Failure */
    EZB_ZCM_METERING_ALARM_SUPPLY_CONNECT_FAILURE       = 0x73, /*!< Supply Connect Failure */
    EZB_ZCM_METERING_ALARM_MEASUREMENT_SOFTWARE_CHANGED = 0x74, /*!< Measurement Software Changed */
    EZB_ZCM_METERING_ALARM_DST_ENABLED                  = 0x75, /*!< DST enabled */
    EZB_ZCM_METERING_ALARM_DST_DISABLED                 = 0x76, /*!< DST disabled */
    EZB_ZCM_METERING_ALARM_CLOCK_ADJ_BACKWARD =
        0x77, /*!< Clock Adj Backward (the internal clock has applied a negative adjustment) */
    EZB_ZCM_METERING_ALARM_CLOCK_ADJ_FORWARD =
        0x78, /*!< Clock Adj Forward (the internal clock has applied a positive adjustment) */
    EZB_ZCM_METERING_ALARM_CLOCK_INVALID                                = 0x79, /*!< Clock Invalid */
    EZB_ZCM_METERING_ALARM_COMMUNICATION_ERROR_HAN                      = 0x7A, /*!< Communication Error HAN */
    EZB_ZCM_METERING_ALARM_COMMUNICATION_OK_HAN                         = 0x7B, /*!< Communication OK HAN */
    EZB_ZCM_METERING_ALARM_METER_FRAUD_ATTEMPT                          = 0x7C, /*!< Meter Fraud Attempt */
    EZB_ZCM_METERING_ALARM_POWER_LOSS                                   = 0x7D, /*!< Power Loss */
    EZB_ZCM_METERING_ALARM_UNUSUAL_HAN_TRAFFIC                          = 0x7E, /*!< Unusual HAN Traffic */
    EZB_ZCM_METERING_ALARM_UNEXPECTED_CLOCK_CHANGE                      = 0x7F, /*!< Unexpected Clock Change */
    EZB_ZCM_METERING_ALARM_COMMS_USING_UNAUTHENTICATED_COMPONENT        = 0x80, /*!< Comms Using Unauthenticated Component */
    EZB_ZCM_METERING_ALARM_ERROR_REG_CLEAR                              = 0x81, /*!< Error Reg Clear */
    EZB_ZCM_METERING_ALARM_ALARM_REG_CLEAR                              = 0x82, /*!< Alarm Reg Clear */
    EZB_ZCM_METERING_ALARM_UNEXPECTED_HW_RESET                          = 0x83, /*!< Unexpected HW Reset */
    EZB_ZCM_METERING_ALARM_UNEXPECTED_PROGRAM_EXECUTION                 = 0x84, /*!< Unexpected Program Execution */
    EZB_ZCM_METERING_ALARM_EVENTLOG_CLEARED                             = 0x85, /*!< EventLog Cleared */
    EZB_ZCM_METERING_ALARM_LIMIT_THRESHOLD_EXCEEDED                     = 0x86, /*!< Limit Threshold Exceeded */
    EZB_ZCM_METERING_ALARM_LIMIT_THRESHOLD_OK                           = 0x87, /*!< Limit Threshold OK */
    EZB_ZCM_METERING_ALARM_LIMIT_THRESHOLD_CHANGED                      = 0x88, /*!< Limit Threshold Changed */
    EZB_ZCM_METERING_ALARM_MAXIMUM_DEMAND_EXCEEDED                      = 0x89, /*!< Maximum Demand Exceeded */
    EZB_ZCM_METERING_ALARM_PROFILE_CLEARED                              = 0x8A, /*!< Profile Cleared */
    EZB_ZCM_METERING_ALARM_SAMPLING_BUFFER_CLEARED                      = 0x8B, /*!< Sampling Buffer cleared */
    EZB_ZCM_METERING_ALARM_BATTERY_WARNING                              = 0x8C, /*!< Battery Warning */
    EZB_ZCM_METERING_ALARM_WRONG_SIGNATURE                              = 0x8D, /*!< Wrong Signature */
    EZB_ZCM_METERING_ALARM_NO_SIGNATURE                                 = 0x8E, /*!< No Signature */
    EZB_ZCM_METERING_ALARM_UNAUTHORISED_ACTION_FROM_HAN                 = 0x8F, /*!< Unauthorised Action from HAN */
    EZB_ZCM_METERING_ALARM_FAST_POLLING_START                           = 0x90, /*!< Fast Polling Start */
    EZB_ZCM_METERING_ALARM_FAST_POLLING_END                             = 0x91, /*!< Fast Polling End */
    EZB_ZCM_METERING_ALARM_METER_REPORTING_INTERVAL_CHANGED             = 0x92, /*!< Meter Reporting Interval Changed */
    EZB_ZCM_METERING_ALARM_DISCONNECT_DUE_TO_LOAD_LIMIT                 = 0x93, /*!< Disconnect Due to Load Limit */
    EZB_ZCM_METERING_ALARM_METER_SUPPLY_STATUS_REGISTER_CHANGED         = 0x94, /*!< Meter Supply Status Register Changed */
    EZB_ZCM_METERING_ALARM_METER_ALARM_STATUS_REGISTER_CHANGED          = 0x95, /*!< Meter Alarm Status Register Changed */
    EZB_ZCM_METERING_ALARM_EXTENDED_METER_ALARM_STATUS_REGISTER_CHANGED = 0x96, /*!< Extended Meter Alarm Status
                                                                                Register Changed */
} ezb_zcl_metering_extended_generic_alarm_group_t;

/** @brief The Manufacturer Specific Alarm Group defines alarms specific for any meters. These are used
 * for meter specific functionality that is not covered by the current smart energy specification */
typedef enum {
    EZB_ZCL_METERING_ALARM_MANUFACTURER_SPECIFIC_A = 0xB0, /*!< Manufacturer Specific A */
    EZB_ZCL_METERING_ALARM_MANUFACTURER_SPECIFIC_B = 0xB1, /*!< Manufacturer Specific B */
    EZB_ZCL_METERING_ALARM_MANUFACTURER_SPECIFIC_C = 0xB2, /*!< Manufacturer Specific C */
    EZB_ZCL_METERING_ALARM_MANUFACTURER_SPECIFIC_D = 0xB3, /*!< Manufacturer Specific D */
    EZB_ZCL_METERING_ALARM_MANUFACTURER_SPECIFIC_E = 0xB4, /*!< Manufacturer Specific E */
    EZB_ZCL_METERING_ALARM_MANUFACTURER_SPECIFIC_F = 0xB5, /*!< Manufacturer Specific F */
    EZB_ZCL_METERING_ALARM_MANUFACTURER_SPECIFIC_G = 0xB6, /*!< Manufacturer Specific G */
    EZB_ZCL_METERING_ALARM_MANUFACTURER_SPECIFIC_H = 0xB7, /*!< Manufacturer Specific H */
    EZB_ZCL_METERING_ALARM_MANUFACTURER_SPECIFIC_I = 0xB8, /*!< Manufacturer Specific I */
} ezb_zcl_metering_manufacturer_specific_alarm_group_t;

/**
 * @brief ZCL Metering Service disconnect reasons.
 */
typedef enum {
    EZB_ZCL_METERING_REASON_ON                                   = 0x00, /*!< ON (Service NOT disconnected) */
    EZB_ZCL_METERING_REASON_OFF_DUE_TO_OVER_POWER                = 0x01, /*!< OFF due to over power */
    EZB_ZCL_METERING_REASON_OFF_DUE_TO_OVER_VOLTAGE              = 0x02, /*!< OFF due to over voltage */
    EZB_ZCL_METERING_REASON_OFF_DUE_TO_REMOTE_DNO_LOAD_CONTROL   = 0x03, /*!< OFF due to Remote DNO Load Control */
    EZB_ZCL_METERING_REASON_OFF_BY_OTHER_REMOTE_COMMAND          = 0x04, /*!< OFF by other remote command */
    EZB_ZCL_METERING_REASON_OFF_DUE_TO_OVERHEATING_SHORT_CIRCUIT = 0x05, /*!< OFF due to overheating, I > In
                                                                         (Maximum Current) - short circuit */
    EZB_ZCL_METERING_REASON_OFF_DUE_TO_OVERHEATING_OTHER = 0x06,         /*!< OFF due to overheating, I < In (Maximum
                                                                         Current) - other */
} ezb_zcl_metering_service_disconnect_reasons_t;

/** @brief ZCL Metering interval channel values.
 * @anchor ezb_zcl_metering_interval_channel_t
 */
typedef enum {
    EZB_ZCL_METERING_CONSUMPTION_DELIVERED          = 0, /*!< Consumption Delivered */
    EZB_ZCL_METERING_CONSUMPTION_RECEIVED           = 1, /*!< Consumption Received */
    EZB_ZCL_METERING_REACTIVE_CONSUMPTION_DELIVERED = 2, /*!< Reactive Consumption Delivered */
    EZB_ZCL_METERING_REACTIVE_CONSUMPTION_RECEIVED  = 3, /*!< Reactive Consumption Received */
    /*! Value 4 is reserved. Values 5 - 255 is unused */
} ezb_zcl_metering_interval_channel_t;

/**
 * @brief ZCL Metering status field values.
 * @anchor ezb_zcl_metering_status_field_t
 */
typedef enum {
    EZB_ZCL_METERING_SUCCESS                                       = 0x00, /*!< Success */
    EZB_ZCL_METERING_UNDEFINED_INTERVAL_CHANNEL_REQUESTED          = 0x01, /*!< Undefined Interval Channel requested */
    EZB_ZCL_METERING_INTERVAL_CHANNEL_NOT_SUPPORTED                = 0x02, /*!< Interval Channel not supported */
    EZB_ZCL_METERING_INVALID_END_TIME                              = 0x03, /*!< Invalid End Time */
    EZB_ZCL_METERING_MORE_PERIODS_REQUESTED_THAN_CAN_BE_RETURNED   = 0x04, /*!< More periods requested than can be returned */
    EZB_ZCL_METERING_NO_INTERVALS_AVAILABLE_FOR_THE_REQUESTED_TIME = 0x05  /*!< No intervals available for the requested time */
} ezb_zcl_metering_status_field_t;

/** @brief ZCL Metering profile interval period values. */
typedef enum {
    EZB_ZCL_METERING_INTERVAL_PERIOD_DAILY       = 0, /*!< Daily */
    EZB_ZCL_METERING_INTERVAL_PERIOD_60_MINUTES  = 1, /*!< 60 minutes */
    EZB_ZCL_METERING_INTERVAL_PERIOD_30_MINUTES  = 2, /*!< 30 minutes */
    EZB_ZCL_METERING_INTERVAL_PERIOD_15_MINUTES  = 3, /*!< 15 minutes */
    EZB_ZCL_METERING_INTERVAL_PERIOD_10_MINUTES  = 4, /*!< 10 minutes */
    EZB_ZCL_METERING_INTERVAL_PERIOD_7_5_MINUTES = 5, /*!< 7.5 minutes */
    EZB_ZCL_METERING_INTERVAL_PERIOD_5_MINUTES   = 6, /*!< 5 minutes */
    EZB_ZCL_METERING_INTERVAL_PERIOD_2_5_MINUTES = 7, /*!< 2.5 minutes */
    EZB_ZCL_METERING_INTERVAL_PERIOD_1_MINUTE    = 8  /*!< 1 minute */
} ezb_zcl_metering_profile_interval_period_t;

/**
 * @brief ZCL Metering sample type enumerations.
 * @anchor ezb_zcl_metering_sample_type_e
 */
enum ezb_zcl_metering_sample_type_e {
    EZB_ZCL_METERING_SAMPLE_TYPE_CONSUMPTION_DELIVERED          = 0, /*!< Consumption Delivered */
    EZB_ZCL_METERING_SAMPLE_TYPE_CONSUMPTION_RECEIVED           = 1, /*!< Consumption Received */
    EZB_ZCL_METERING_SAMPLE_TYPE_REACTIVE_CONSUMPTION_DELIVERED = 2, /*!< Reactive Consumption Delivered */
    EZB_ZCL_METERING_SAMPLE_TYPE_REACTIVE_CONSUMPTION_RECEIVED  = 3, /*!< Reactive Consumption Received */
    EZB_ZCL_METERING_SAMPLE_TYPE_INSTANTANEOUS_DEMAND           = 4  /*!< InstantaneousDemand*/
};
/**
 * @brief ZCL Metering sample type.
 * @anchor ezb_zcl_metering_sample_type_t
 */
typedef uint8_t ezb_zcl_metering_sample_type_t;

/** @brief ZCL Metering snapshot cause bitmap.
 * @anchor ezb_zcl_metering_snapshot_cause_t
 */
typedef enum {
    EZB_ZCL_METERING_CAUSE_GENERAL                        = 1 << 0,  /*!< General */
    EZB_ZCL_METERING_CAUSE_END_OF_BILLING_PERIOD          = 1 << 1,  /*!< End of Billing Period */
    EZB_ZCL_METERING_CAUSE_END_OF_BLOCK_PERIOD            = 1 << 2,  /*!< End of Block Period */
    EZB_ZCL_METERING_CAUSE_CHANGE_OF_TARIFF_INFORMATION   = 1 << 3,  /*!< Change of Tariff Information */
    EZB_ZCL_METERING_CAUSE_CHANGE_OF_PRICE_MATRIX         = 1 << 4,  /*!< Change of Price Matrix */
    EZB_ZCL_METERING_CAUSE_CHANGE_OF_BLOCK_THRESHOLDS     = 1 << 5,  /*!< Change of Block Thresholds */
    EZB_ZCL_METERING_CAUSE_CHANGE_OF_CV                   = 1 << 6,  /*!< Change of CV */
    EZB_ZCL_METERING_CAUSE_CHANGE_OF_CF                   = 1 << 7,  /*!< Change of CF */
    EZB_ZCL_METERING_CAUSE_CHANGE_OF_CALENDAR             = 1 << 8,  /*!< Change of Calendar */
    EZB_ZCL_METERING_CAUSE_CRITICAL_PEAK_PRICING          = 1 << 9,  /*!< Critical Peak Pricing */
    EZB_ZCL_METERING_CAUSE_MANUALLY_TRIGGERED_FROM_CLIENT = 1 << 10, /*!< Manually Triggered from Client */
    EZB_ZCL_METERING_CAUSE_END_OF_RESOLVE_PERIOD          = 1 << 11, /*!< End of Resolve Period */
    EZB_ZCL_METERING_CAUSE_CHANGE_OF_TENANCY              = 1 << 12, /*!< Change of Tenancy */
    EZB_ZCL_METERING_CAUSE_CHANGE_OF_SUPPLIER             = 1 << 13, /*!< Change of Supplier */
    EZB_ZCL_METERING_CAUSE_CHANGE_OF_METER_MODE           = 1 << 14, /*!< Change of (Meter) Mode */
    EZB_ZCL_METERING_CAUSE_DEBT_PAYMENT                   = 1 << 15, /*!< Debt Payment */
    EZB_ZCL_METERING_CAUSE_SCHEDULED_SNAPSHOT             = 1 << 16, /*!< Scheduled Snapshot */
    EZB_ZCL_METERING_CAUSE_OTA_FIRMWARE_DOWNLOAD          = 1 << 17, /*!< OTA Firmware Download */
} ezb_zcl_metering_snapshot_cause_t;
#define EZB_ZCL_METERING_CAUSE_SELECT_ALL_SNAPSHOTS 0xFFFFFFFF /*!< Select All Snapshots */

/**
 * @brief ZCL Metering snapshot payload type.
 * @anchor ezb_zcl_metering_snapshot_payload_type_t
 */
typedef enum {
    EZB_ZCL_METERING_TOU_DELIVERED_REGISTERS         = 0,   /*!< TOU Information Set DeliveredRegisters */
    EZB_ZCL_METERING_TOU_RECEIVED_REGISTERS          = 1,   /*!< TOU Information Set Received Registers */
    EZB_ZCL_METERING_BLOCK_TIER_DELIVERED            = 2,   /*!< Block Tier Information Set Delivered */
    EZB_ZCL_METERING_BLOCK_TIER_RECEIVED             = 3,   /*!< Block Tier Information Set Received */
    EZB_ZCL_METERING_TOU_DELIVERED_NO_BILLING        = 4,   /*!< TOU Information Set Delivered (No Billing) */
    EZB_ZCL_METERING_TOU_RECEIVED_NO_BILLING         = 5,   /*!< TOU Information Set Received (No Billing) */
    EZB_ZCL_METERING_BLOCK_TIER_DELIVERED_NO_BILLING = 6,   /*!< Block Tier Information Set Delivered (No Billing) */
    EZB_ZCL_METERING_BLOCK_TIER_RECEIVED_NO_BILLING  = 7,   /*!< Block Tier Information Set Received (No Billing) */
    EZB_ZCL_METERING_DATA_UNAVAILABLE                = 128, /*!< Data Unavailable */
} ezb_zcl_metering_snapshot_payload_type_t;

/**
 * @brief Payload for the ZCL Metering Get Profile command.
 */
typedef struct ezb_zcl_metering_get_profile_payload_s {
    uint8_t  interval_channel; /*!< Interval channel; see @ref ezb_zcl_metering_interval_channel_t. */
    uint32_t end_time;         /*!< End time. */
    uint8_t  num_of_periods;   /*!< Number of periods. */
} ezb_zcl_metering_get_profile_payload_t;

/**
 * @brief Payload for the ZCL Metering Request Fast Poll Mode command.
 */
EZB_PACKED_BEGIN
struct ezb_zcl_metering_request_fast_poll_mode_payload_s {
    uint8_t period;   /*!< Fast poll update period in seconds. */
    uint8_t duration; /*!< Duration in minutes. */
} EZB_PACKED_END;
typedef struct ezb_zcl_metering_request_fast_poll_mode_payload_s ezb_zcl_metering_request_fast_poll_mode_payload_t;

/**
 * @brief Payload for the ZCL Metering Get Snapshot command.
 */
typedef struct ezb_zcl_metering_get_snapshot_payload_s {
    uint32_t earliest_start_time; /*!< Earliest start time. */
    uint32_t latest_end_time;     /*!< Latest end time. */
    uint8_t  snapshot_offset;     /*!< Snapshot offset. */
    uint32_t snapshot_cause;      /*!< Snapshot cause bitmap. */
} ezb_zcl_metering_get_snapshot_payload_t;

/**
 * @brief Payload for the ZCL Metering Get Sampled Data command.
 */
typedef struct ezb_zcl_metering_get_sampled_payload_s {
    uint16_t                       sample_id;           /*!< Sample ID. */
    uint32_t                       earliest_start_time; /*!< Earliest start time. */
    ezb_zcl_metering_sample_type_t sample_type;         /*!< Sample type; see @ref ezb_zcl_metering_sample_type_e. */
    uint16_t                       num_of_samples;      /*!< Number of samples. */
} ezb_zcl_metering_get_sampled_payload_t;

/**
 * @brief Payload for the ZCL Metering Get Profile Response command.
 */
typedef struct ezb_zcl_metering_get_profile_rsp_s {
    uint32_t                                   end_time; /*!< End time. */
    ezb_zcl_metering_status_field_t            status;   /*!< Status; see @ref ezb_zcl_metering_status_field_t. */
    ezb_zcl_metering_profile_interval_period_t profile_interval_period;  /*!< Profile interval period. */
    uint8_t                                    num_of_periods_delivered; /*!< Number of periods delivered. */
    uint32_t                                  *intervals;                /*!< Series of interval data. */
} ezb_zcl_metering_get_profile_rsp_t;

/**
 * @brief Payload for the ZCL Metering Request Fast Poll Mode Response command.
 */
typedef struct ezb_zcl_metering_request_fast_poll_mode_rsp_s {
    uint8_t  period;   /*!< Applied update period in seconds. */
    uint32_t end_time; /*!< Fast poll mode end time. */
} ezb_zcl_metering_request_fast_poll_mode_rsp_t;

/**
 * @brief ZCL Metering snapshot TOU information set sub-payload.
 */
typedef struct ezb_zcl_metering_tou_info_set_s {
    uint64_t current_summation;       /*!< An unsigned 48-bit integer that returns the value of the
                                      CurrentSummationDelivered attribute at the stated snapshot timestamp */
    uint32_t bill_to_date;            /*!< An unsigned 32-bit integer that provides a value for the costs in the current billing
                                      period */
    uint32_t bill_to_date_time_stamp; /*!< A UTC timestamp that indicates when the value of the associated
                                      BillToDateDelivered parameter was last updated */
    uint32_t projected_bill;          /*!< An unsigned 32-bit integer that provides a value indicating what the estimated state
                                      of the account will be at the end of the billing period based on past consumption */
    uint32_t projected_bill_time_stamp;    /*!< A UTC timestamp that indicates when the associated ProjectedBillDelivered
                                           parameter was last updated */
    uint8_t bill_delivered_trailing_digit; /*!< An 8-bit BitMap used to determine where the decimal point is located in the
                                           BillToDateDelivered and ProjectedBillDelivered fields */
    uint8_t num_of_tiers_in_use; /*!< An 8-bit integer representing the number of tiers in use at the time the snapshot was
                                 taken */
    uint64_t *tier_summation;    /*!< The Publish Snapshot command contains N elements of CurrentTierNSummationDelivered
                                 attributes from the TOU Information Set. The Metering server shall send only the number
                                 of tiers in use, as stated in this command */
} ezb_zcl_metering_tou_info_set_t;

/**
 * @brief ZCL Metering TOU delivered payload.
 * @anchor ezb_zcl_metering_tou_delivered_payload_t
 */
typedef ezb_zcl_metering_tou_info_set_t ezb_zcl_metering_tou_delivered_payload_t;

/**
 * @brief ZCL Metering TOU received payload.
 * @anchor ezb_zcl_metering_tou_received_payload_t
 */
typedef ezb_zcl_metering_tou_info_set_t ezb_zcl_metering_tou_received_payload_t;

/** @brief Structure for ZCL Metering snapshot block information set sub-payload. */
typedef struct ezb_zcl_metering_block_info_set_s {
    uint64_t current_summation;       /*!< An unsigned 48-bit integer that returns the value of the
                                      CurrentSummationDelivered attribute at the stated snapshot timestamp */
    uint32_t bill_to_date;            /*!< An unsigned 32-bit integer that provides a value for the costs in the current billing
                                      period */
    uint32_t bill_to_date_time_stamp; /*!< A UTC timestamp that indicates when the value of the associated
                                      BillToDateDelivered parameter was last updated */
    uint32_t projected_bill;          /*!< An unsigned 32-bit integer that provides a value indicating what the estimated state
                                      of the account will be at the end of the billing period based on past consumption */
    uint32_t projected_bill_time_stamp;    /*!< A UTC timestamp that indicates when the associated ProjectedBillDelivered
                                           parameter was last updated */
    uint8_t bill_delivered_trailing_digit; /*!< An 8-bit BitMap used to determine where the decimal point is located in the
                                           BillToDateDelivered and ProjectedBillDelivered fields */
    uint8_t num_of_tiers_in_use; /*!< An 8-bit integer representing the number of tiers in use at the time the snapshot was
                                 taken */
    uint64_t *tier_summation; /*!< The Publish Snapshot command contains N elements of CurrentTierNSummationDelivered attributes
                              from the TOU Information Set */
    uint8_t num_of_tiers_and_block_thresholds_in_use; /*!< An 8-bit BitMap representing the number of tiers and block
                                                      thresholds in use at the time the snapshot was taken */
    uint64_t *tier_block_summation; /*!< The Publish Snapshot command contains N elements of the Block Information Attribute Set
                                    (Delivered). The metering server shall send only the number of Tiers and Blocks in use as
                                    stated in this command */
} ezb_zcl_metering_block_info_set_t;

/**
 * @brief ZCL Metering block tier delivered payload.
 * @anchor ezb_zcl_metering_block_tier_delivered_payload_t
 */
typedef ezb_zcl_metering_block_info_set_t ezb_zcl_metering_block_tier_delivered_payload_t;

/**
 * @brief ZCL Metering block tier received payload.
 * @anchor ezb_zcl_metering_block_tier_received_payload_t
 */
typedef ezb_zcl_metering_block_info_set_t ezb_zcl_metering_block_tier_received_payload_t;

/**
 * @brief ZCL Metering TOU information no billing set sub-payload.
 */
typedef struct ezb_zcl_metering_tou_info_no_billing_set_s {
    uint64_t current_summation;  /*!< An unsigned 48-bit integer that returns the value of the
                                 CurrentSummationDelivered attribute at the stated snapshot timestamp */
    uint8_t num_of_tiers_in_use; /*!< An 8-bit integer representing the number of tiers in use at the time the snapshot was
                                 taken */
    uint64_t *tier_summation; /*!< The Publish Snapshot command contains N elements of CurrentTierNSummationDelivered attributes
                              from the TOU Information Set. The metering server shall send only the number of Tiers in use as
                              stated in this command */
} ezb_zcl_metering_tou_info_no_billing_set_t;

/**
 * @brief ZCL Metering TOU delivered no billing payload.
 * @anchor ezb_zcl_metering_tou_delivered_no_billing_payload_t
 */
typedef ezb_zcl_metering_tou_info_no_billing_set_t ezb_zcl_metering_tou_delivered_no_billing_payload_t;

/**
 * @brief ZCL Metering TOU received no billing payload.
 * @anchor ezb_zcl_metering_tou_received_no_billing_payload_t
 */
typedef ezb_zcl_metering_tou_info_no_billing_set_t ezb_zcl_metering_tou_received_no_billing_payload_t;

/**
 * @brief ZCL Metering block information no billing set sub-payload.
 */
typedef struct ezb_zcl_metering_block_info_no_billing_set_s {
    uint64_t current_summation;  /*!< An unsigned 48-bit integer that returns the value of the
                                 CurrentSummationDelivered attribute at the stated snapshot timestamp */
    uint8_t num_of_tiers_in_use; /*!< An 8-bit integer representing the number of tiers in use at the time the snapshot was
                                 taken */
    uint64_t *tier_summation; /*!< The Publish Snapshot command contains N elements of CurrentTierNSummationDelivered attributes
                              from the TOU Information Set */
    uint8_t num_of_tiers_and_block_thresholds_in_use; /*!< An 8-bit BitMap representing the number of tiers and block
                                                      thresholds in use at the time the snapshot was taken */
    uint64_t *tier_block_summation; /*!< The Publish Snapshot command contains N elements of the Block Information Attribute Set
                                    (Delivered). The metering server shall send only the number of Tiers and Blocks in use as
                                    stated in this command */
} ezb_zcl_metering_block_info_no_billing_set_t;

/**
 * @brief ZCL Metering block tier delivered no billing payload.
 * @anchor ezb_zcl_metering_block_tier_delivered_no_billing_payload_t
 */
typedef ezb_zcl_metering_block_info_no_billing_set_t ezb_zcl_metering_block_tier_delivered_no_billing_payload_t;

/**
 * @brief ZCL Metering block tier received no billing payload.
 * @anchor ezb_zcl_metering_block_tier_received_no_billing_payload_t
 */
typedef ezb_zcl_metering_block_info_no_billing_set_t ezb_zcl_metering_block_tier_received_no_billing_payload_t;

/**
 * @brief ZCL Metering snapshot sub-payload union.
 */
typedef union ezb_zcl_metering_snapshot_sub_payload_s {
    ezb_zcl_metering_tou_delivered_payload_t        tou_delivered;        /*!< TOU information set delivered payload */
    ezb_zcl_metering_tou_received_payload_t         tou_received;         /*!< TOU information set received payload */
    ezb_zcl_metering_block_tier_delivered_payload_t block_tier_delivered; /*!< Block tier information set delivered payload */
    ezb_zcl_metering_block_tier_received_payload_t  block_tier_received;  /*!< Block tier information set received payload */
    /*! TOU information set delivered (no billing) payload */
    ezb_zcl_metering_tou_delivered_no_billing_payload_t tou_delivered_no_billing;
    /*! TOU information set received (no billing) payload */
    ezb_zcl_metering_tou_received_no_billing_payload_t tou_received_no_billing;
    /*! Block tier information set delivered (no billing) payload */
    ezb_zcl_metering_block_tier_delivered_no_billing_payload_t block_tier_delivered_no_billing;
    /*! Block tier information set received (no billing) payload */
    ezb_zcl_metering_block_tier_received_no_billing_payload_t block_tier_received_no_billing;
} ezb_zcl_metering_snapshot_sub_payload_t;

/**
 * @brief ZCL Metering publish snapshot payload.
 */
typedef struct ezb_zcl_metering_publish_snapshot_payload_s {
    uint32_t snapshot_id;           /*!< Snapshot ID */
    uint32_t snapshot_time;         /*!< Snapshot Time */
    uint8_t  total_snapshots_found; /*!< Total Snapshots */
    uint8_t  command_index;         /*!< Command Index */
    uint8_t  total_num_of_commands; /*!< Total Number of Commands */
    uint32_t snapshot_cause;        /*!< Snapshot Cause BitMap see @ref ezb_zcl_metering_snapshot_cause_t */
    uint8_t  payload_type;          /*!< Payload Type see @ref ezb_zcl_metering_snapshot_payload_type_t*/
    ezb_zcl_metering_snapshot_sub_payload_t sub_payload; /*!< Snapshot Sub-Payload */
} ezb_zcl_metering_publish_snapshot_payload_t;

/**
 * @brief Payload for the ZCL Metering Get Sampled Data Response command.
 */
typedef struct ezb_zcl_metering_get_sampled_data_rsp_s {
    uint16_t                       sample_id;      /*!< Sample ID */
    uint32_t                       start_time;     /*!< Start Time */
    ezb_zcl_metering_sample_type_t sample_type;    /*!< Sample Type see @ref ezb_zcl_metering_sample_type_t */
    uint16_t                       req_interval;   /*!< Requested Interval */
    uint16_t                       num_of_samples; /*!< Number of Samples */
    uint32_t *samples; /*!< An unsigned 24-bit integer, series of sample data captured using the Sample Type specified */
} ezb_zcl_metering_get_sampled_data_rsp_t;

/* Command structures */
/**
 * @brief Structure for the ZCL Metering GetProfile command request.
 */
typedef struct ezb_zcl_metering_get_profile_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t             cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_metering_get_profile_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_metering_get_profile_cmd_t;

/**
 * @brief Structure for the ZCL Metering Request Fast Poll Mode command request.
 */
typedef struct ezb_zcl_metering_request_fast_poll_mode_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                        cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_metering_request_fast_poll_mode_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_metering_request_fast_poll_mode_cmd_t;

/**
 * @brief Structure for the ZCL Metering Get Snapshot command request.
 */
typedef struct ezb_zcl_metering_get_snapshot_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t              cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_metering_get_snapshot_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_metering_get_snapshot_cmd_t;

/**
 * @brief Structure for the ZCL Metering Get Sampled Data command request.
 */
typedef struct ezb_zcl_metering_get_sampled_data_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t             cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_metering_get_sampled_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_metering_get_sampled_data_cmd_t;

/* Callback message structures */
/**
 * @brief Message for the ZCL Metering Get Profile request message.
 */
typedef struct ezb_zcl_metering_get_profile_req_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                /*!< ZCL command header information.
                                                             See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_metering_get_profile_payload_t payload; /*!< Get Profile command payload. */
    } in;                                               /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t                    result;  /*!< Status of processing in application. */
        ezb_zcl_metering_get_profile_rsp_t *payload; /*!< Get Profile Response payload. */
        ezb_zcl_cmd_cnf_ctx_t               cnf_ctx; /*!< Command confirmation context. */
    } out;                                           /*!< Output: result to send back. */
} ezb_zcl_metering_get_profile_req_message_t;

/**
 * @brief Message for the ZCL Metering Get Profile Response message.
 */
typedef struct ezb_zcl_metering_get_profile_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;            /*!< ZCL command header information.
                                                         See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_metering_get_profile_rsp_t payload; /*!< Get Profile Response payload. */
    } in;                                           /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_metering_get_profile_rsp_message_t;

/**
 * @brief Message for the ZCL Metering Request Fast Poll Mode request message.
 */
typedef struct ezb_zcl_metering_request_fast_poll_mode_req_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                           /*!< ZCL command header information.
                                                                        See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_metering_request_fast_poll_mode_payload_t payload; /*!< Request Fast Poll Mode payload. */
    } in;                                                          /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t                              result;  /*!< Status of processing in application. */
        ezb_zcl_metering_request_fast_poll_mode_rsp_t payload; /*!< Request Fast Poll Mode Response payload. */
    } out;                                                     /*!< Output: result to send back. */
} ezb_zcl_metering_request_fast_poll_mode_req_message_t;

/**
 * @brief Message for the ZCL Metering Request Fast Poll Mode Response message.
 */
typedef struct ezb_zcl_metering_request_fast_poll_mode_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                       /*!< ZCL command header information.
                                                                    See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_metering_request_fast_poll_mode_rsp_t payload; /*!< Request Fast Poll Mode Response payload. */
    } in;                                                      /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_metering_request_fast_poll_mode_rsp_message_t;

/**
 * @brief Message for the ZCL Metering Get Snapshot request message.
 */
typedef struct ezb_zcl_metering_get_snapshot_req_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                 /*!< ZCL command header information.
                                                              See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_metering_get_snapshot_payload_t payload; /*!< Get Snapshot payload. */
    } in;                                                /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t                             result;  /*!< Status of processing in application. */
        ezb_zcl_metering_publish_snapshot_payload_t *payload; /*!< Publish Snapshot payload. */
        ezb_zcl_cmd_cnf_ctx_t                        cnf_ctx; /*!< Command confirmation context. */
    } out;                                                    /*!< Output: result to send back. */
} ezb_zcl_metering_get_snapshot_req_message_t;

/**
 * @brief Message for the ZCL Metering Publish Snapshot message.
 */
typedef struct ezb_zcl_metering_publish_snapshot_command_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                     /*!< ZCL command header information.
                                                                See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_metering_publish_snapshot_payload_t payload; /*!< Publish Snapshot payload. */
    } in;                                                    /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_metering_publish_snapshot_command_message_t;

/**
 * @brief Message for the ZCL Metering Get Sampled Data request message.
 */
typedef struct ezb_zcl_metering_get_sampled_data_req_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                /*!< ZCL command header information.
                                                             See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_metering_get_sampled_payload_t payload; /*!< Get Sampled Data payload. */
    } in;                                               /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t                         result;  /*!< Status of processing in application. */
        ezb_zcl_metering_get_sampled_data_rsp_t *payload; /*!< Get Sampled Data Response payload. */
        ezb_zcl_cmd_cnf_ctx_t                    cnf_ctx; /*!< Command confirmation context. */
    } out;                                                /*!< Output: result to send back. */
} ezb_zcl_metering_get_sampled_data_req_message_t;

/**
 * @brief Message for the ZCL Metering Get Sampled Data Response message.
 */
typedef struct ezb_zcl_metering_get_sampled_data_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                /*!< ZCL command header information.
                                                             See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_metering_get_sampled_data_rsp_t payload; /*!< Get Sampled Data Response payload. */
    } in;                                                /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_metering_get_sampled_data_rsp_message_t;

/**
 * @brief Send ZCL Metering GetProfile command request.
 *
 * @param cmd_req Pointer to the GetProfile command request structure, @ref ezb_zcl_metering_get_profile_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_metering_get_profile_cmd_req(const ezb_zcl_metering_get_profile_cmd_t *cmd_req);

/**
 * @brief Send ZCL Metering Request Fast Poll Mode command request.
 *
 * @param cmd_req Pointer to the Request Fast Poll Mode command request structure, @ref
 * ezb_zcl_metering_request_fast_poll_mode_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_metering_request_fast_poll_mode_cmd_req(const ezb_zcl_metering_request_fast_poll_mode_cmd_t *cmd_req);

/**
 * @brief Send ZCL Metering Get Snapshot command request.
 *
 * @param cmd_req Pointer to the Get Snapshot command request structure, @ref ezb_zcl_metering_get_snapshot_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_metering_get_snapshot_cmd_req(const ezb_zcl_metering_get_snapshot_cmd_t *cmd_req);

/**
 * @brief Send ZCL Metering Get Sampled Data command request.
 *
 * @param cmd_req Pointer to the Get Sampled Data command request structure, @ref ezb_zcl_metering_get_sampled_data_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_metering_get_sampled_data_cmd_req(const ezb_zcl_metering_get_sampled_data_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
