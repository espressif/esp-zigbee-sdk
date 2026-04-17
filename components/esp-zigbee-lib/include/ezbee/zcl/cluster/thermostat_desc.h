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
   THERMOSTAT Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the thermostat cluster implementation */
#define EZB_ZCL_THERMOSTAT_CLUSTER_REVISION (3)

/**
 * @brief Attribute identifiers for the thermostat server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_THERMOSTAT_LOCAL_TEMPERATURE_ID                  = 0x0000U, /*!< LocalTemperature attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_OUTDOOR_TEMPERATURE_ID                = 0x0001U, /*!< OutdoorTemperature attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_OCCUPANCY_ID                          = 0x0002U, /*!< Occupancy attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_ABS_MIN_HEAT_SETPOINT_LIMIT_ID        = 0x0003U, /*!< AbsMinHeatSetpointLimit attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_ABS_MAX_HEAT_SETPOINT_LIMIT_ID        = 0x0004U, /*!< AbsMaxHeatSetpointLimit attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_ABS_MIN_COOL_SETPOINT_LIMIT_ID        = 0x0005U, /*!< AbsMinCoolSetpointLimit attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_ABS_MAX_COOL_SETPOINT_LIMIT_ID        = 0x0006U, /*!< AbsMaxCoolSetpointLimit attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_PI_COOLING_DEMAND_ID                  = 0x0007U, /*!< PICoolingDemand attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_PI_HEATING_DEMAND_ID                  = 0x0008U, /*!< PIHeatingDemand attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_HVAC_SYSTEM_TYPE_CONFIGURATION_ID     = 0x0009U, /*!< HVACSystemTypeConfiguration attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_LOCAL_TEMPERATURE_CALIBRATION_ID      = 0x0010U, /*!< LocalTemperatureCalibration attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_OCCUPIED_COOLING_SETPOINT_ID          = 0x0011U, /*!< OccupiedCoolingSetpoint attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_OCCUPIED_HEATING_SETPOINT_ID          = 0x0012U, /*!< OccupiedHeatingSetpoint attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_UNOCCUPIED_COOLING_SETPOINT_ID        = 0x0013U, /*!< UnoccupiedCoolingSetpoint attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_UNOCCUPIED_HEATING_SETPOINT_ID        = 0x0014U, /*!< UnoccupiedHeatingSetpoint attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT_ID            = 0x0015U, /*!< MinHeatSetpointLimit attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT_ID            = 0x0016U, /*!< MaxHeatSetpointLimit attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_MIN_COOL_SETPOINT_LIMIT_ID            = 0x0017U, /*!< MinCoolSetpointLimit attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_MAX_COOL_SETPOINT_LIMIT_ID            = 0x0018U, /*!< MaxCoolSetpointLimit attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_MIN_SETPOINT_DEAD_BAND_ID             = 0x0019U, /*!< MinSetpointDeadBand attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_REMOTE_SENSING_ID                     = 0x001aU, /*!< RemoteSensing attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_CONTROL_SEQUENCE_OF_OPERATION_ID      = 0x001bU, /*!< ControlSequenceOfOperation attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_SYSTEM_MODE_ID                        = 0x001cU, /*!< SystemMode attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_ALARM_MASK_ID                         = 0x001dU, /*!< AlarmMask attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_THERMOSTAT_RUNNING_MODE_ID            = 0x001eU, /*!< ThermostatRunningMode attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_START_OF_WEEK_ID                      = 0x0020U, /*!< StartOfWeek attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_NUMBER_OF_WEEKLY_TRANSITIONS_ID       = 0x0021U, /*!< NumberOfWeeklyTransitions attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_NUMBER_OF_DAILY_TRANSITIONS_ID        = 0x0022U, /*!< NumberOfDailyTransitions attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_TEMPERATURE_SETPOINT_HOLD_ID          = 0x0023U, /*!< TemperatureSetpointHold attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_TEMPERATURE_SETPOINT_HOLD_DURATION_ID = 0x0024U, /*!< TemperatureSetpointHoldDuration attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_THERMOSTAT_PROGRAMMING_OPERATION_MODE_ID =
        0x0025U,                                                           /*!< ThermostatProgrammingOperationMode attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_THERMOSTAT_RUNNING_STATE_ID         = 0x0029U, /*!< ThermostatRunningState attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_SETPOINT_CHANGE_SOURCE_ID           = 0x0030U, /*!< SetpointChangeSource attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_SETPOINT_CHANGE_AMOUNT_ID           = 0x0031U, /*!< SetpointChangeAmount attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_SETPOINT_CHANGE_SOURCE_TIMESTAMP_ID = 0x0032U, /*!< SetpointChangeSourceTimestamp attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_OCCUPIED_SETBACK_ID                 = 0x0034U, /*!< OccupiedSetback attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_OCCUPIED_SETBACK_MIN_ID             = 0x0035U, /*!< OccupiedSetbackMin attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_OCCUPIED_SETBACK_MAX_ID             = 0x0036U, /*!< OccupiedSetbackMax attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_UNOCCUPIED_SETBACK_ID               = 0x0037U, /*!< UnoccupiedSetback attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_UNOCCUPIED_SETBACK_MIN_ID           = 0x0038U, /*!< UnoccupiedSetbackMin attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_UNOCCUPIED_SETBACK_MAX_ID           = 0x0039U, /*!< UnoccupiedSetbackMax attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_EMERGENCY_HEAT_DELTA_ID             = 0x003aU, /*!< EmergencyHeatDelta attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_AC_TYPE_ID                          = 0x0040U, /*!< ACType attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_AC_CAPACITY_ID                      = 0x0041U, /*!< ACCapacity attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_AC_REFRIGERANT_TYPE_ID              = 0x0042U, /*!< ACRefrigerantType attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_AC_COMPRESSOR_TYPE_ID               = 0x0043U, /*!< ACCompressorType attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_AC_ERROR_CODE_ID                    = 0x0044U, /*!< ACErrorCode attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_AC_LOUVER_POSITION_ID               = 0x0045U, /*!< ACLouverPosition attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_AC_COIL_TEMPERATURE_ID              = 0x0046U, /*!< ACCoilTemperature attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_AC_CAPACITY_FORMAT_ID               = 0x0047U, /*!< ACCapacityFormat attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_SCHEDULE_CONTEXT_ID                 = 0xeff0U, /*!< ScheduleContext attribute. */
} ezb_zcl_thermostat_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the Thermostat server cluster.
 */
typedef struct ezb_zcl_thermostat_cluster_server_config_s {
    int16_t local_temperature;             /*!< Configurable mandatory LocalTemperature attribute */
    uint8_t control_sequence_of_operation; /*!< Configurable mandatory ControlSequenceOfOperation attribute */
    uint8_t system_mode;                   /*!< Configurable mandatory SystemMode attribute */
} ezb_zcl_thermostat_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL ControlSequenceOfOperation attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_CONTROL_SEQUENCE_OF_OPERATION_COOLING_ONLY               = 0x00U, /*!< CoolingOnly */
    EZB_ZCL_THERMOSTAT_CONTROL_SEQUENCE_OF_OPERATION_COOLING_WITH_REHEAT        = 0x01U, /*!< CoolingWithReheat */
    EZB_ZCL_THERMOSTAT_CONTROL_SEQUENCE_OF_OPERATION_HEATING_ONLY               = 0x02U, /*!< HeatingOnly */
    EZB_ZCL_THERMOSTAT_CONTROL_SEQUENCE_OF_OPERATION_HEATING_WITH_REHEAT        = 0x03U, /*!< HeatingWithReheat */
    EZB_ZCL_THERMOSTAT_CONTROL_SEQUENCE_OF_OPERATION_COOLING_AND_HEATING4_PIPES = 0x04U, /*!< CoolingAndHeating4Pipes */
    EZB_ZCL_THERMOSTAT_CONTROL_SEQUENCE_OF_OPERATION_COOLING_AND_HEATING4_PIPES_WITH_REHEAT =
        0x05U, /*!< CoolingAndHeating4PipesWithReheat */
} ezb_zcl_thermostat_server_control_sequence_of_operation_t;

/**
 * @brief Enumeration for ZCL SystemMode attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_SYSTEM_MODE_OFF               = 0x00U, /*!< Off */
    EZB_ZCL_THERMOSTAT_SYSTEM_MODE_AUTO              = 0x01U, /*!< Auto */
    EZB_ZCL_THERMOSTAT_SYSTEM_MODE_COOL              = 0x03U, /*!< Cool */
    EZB_ZCL_THERMOSTAT_SYSTEM_MODE_HEAT              = 0x04U, /*!< Heat */
    EZB_ZCL_THERMOSTAT_SYSTEM_MODE_EMERGENCY_HEATING = 0x05U, /*!< EmergencyHeating */
    EZB_ZCL_THERMOSTAT_SYSTEM_MODE_PRECOOLING        = 0x06U, /*!< Precooling */
    EZB_ZCL_THERMOSTAT_SYSTEM_MODE_FAN_ONLY          = 0x07U, /*!< FanOnly */
    EZB_ZCL_THERMOSTAT_SYSTEM_MODE_DRY               = 0x08U, /*!< Dry */
    EZB_ZCL_THERMOSTAT_SYSTEM_MODE_SLEEP             = 0x09U, /*!< Sleep */
} ezb_zcl_thermostat_server_system_mode_t;

/**
 * @brief Enumeration for ZCL ThermostatRunningMode attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_THERMOSTAT_RUNNING_MODE_OFF  = 0x00U, /*!< Off */
    EZB_ZCL_THERMOSTAT_THERMOSTAT_RUNNING_MODE_COOL = 0x03U, /*!< Cool */
    EZB_ZCL_THERMOSTAT_THERMOSTAT_RUNNING_MODE_HEAT = 0x04U, /*!< Heat */
} ezb_zcl_thermostat_server_thermostat_running_mode_t;

/**
 * @brief Enumeration for ZCL StartOfWeek attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_START_OF_WEEK_SUNDAY    = 0x00U, /*!< Sunday */
    EZB_ZCL_THERMOSTAT_START_OF_WEEK_MONDAY    = 0x01U, /*!< Monday */
    EZB_ZCL_THERMOSTAT_START_OF_WEEK_TUESDAY   = 0x02U, /*!< Tuesday */
    EZB_ZCL_THERMOSTAT_START_OF_WEEK_WEDNESDAY = 0x03U, /*!< Wednesday */
    EZB_ZCL_THERMOSTAT_START_OF_WEEK_THURSDAY  = 0x04U, /*!< Thursday */
    EZB_ZCL_THERMOSTAT_START_OF_WEEK_FRIDAY    = 0x05U, /*!< Friday */
    EZB_ZCL_THERMOSTAT_START_OF_WEEK_SATURDAY  = 0x06U, /*!< Saturday */
} ezb_zcl_thermostat_server_start_of_week_t;

/**
 * @brief Enumeration for ZCL TemperatureSetpointHold attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_TEMPERATURE_SETPOINT_HOLD_SETPOINT_HOLD_OFF = 0x00U, /*!< SetpointHoldOff */
    EZB_ZCL_THERMOSTAT_TEMPERATURE_SETPOINT_HOLD_SETPOINT_HOLD_ON  = 0x01U, /*!< SetpointHoldOn */
} ezb_zcl_thermostat_server_temperature_setpoint_hold_t;

/**
 * @brief Enumeration for ZCL SetpointChangeSource attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_SETPOINT_CHANGE_SOURCE_MANUAL                           = 0x00U, /*!< Manual */
    EZB_ZCL_THERMOSTAT_SETPOINT_CHANGE_SOURCE_SCHEDULE_OR_INTERNAL_PROGRAMMING = 0x01U, /*!< ScheduleOrInternalProgramming */
    EZB_ZCL_THERMOSTAT_SETPOINT_CHANGE_SOURCE_EXTERNAL                         = 0x02U, /*!< External */
} ezb_zcl_thermostat_server_setpoint_change_source_t;

/**
 * @brief Enumeration for ZCL ACType attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_AC_TYPE_COOLING_AND_FIXED_SPEED   = 0x01U, /*!< CoolingAndFixedSpeed */
    EZB_ZCL_THERMOSTAT_AC_TYPE_HEAT_PUMP_AND_FIXED_SPEED = 0x02U, /*!< HeatPumpAndFixedSpeed */
    EZB_ZCL_THERMOSTAT_AC_TYPE_COOLING_AND_INVERTER      = 0x03U, /*!< CoolingAndInverter */
    EZB_ZCL_THERMOSTAT_AC_TYPE_HEAT_PUMP_AND_INVERTER    = 0x04U, /*!< HeatPumpAndInverter */
} ezb_zcl_thermostat_server_ac_type_t;

/**
 * @brief Enumeration for ZCL ACRefrigerantType attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_AC_REFRIGERANT_TYPE_R22   = 0x01U, /*!< R22 */
    EZB_ZCL_THERMOSTAT_AC_REFRIGERANT_TYPE_R410A = 0x02U, /*!< R410a */
    EZB_ZCL_THERMOSTAT_AC_REFRIGERANT_TYPE_R407C = 0x03U, /*!< R407c */
} ezb_zcl_thermostat_server_ac_refrigerant_type_t;

/**
 * @brief Enumeration for ZCL ACCompressorType attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_AC_COMPRESSOR_TYPE_T1 = 0x01U, /*!< T1 */
    EZB_ZCL_THERMOSTAT_AC_COMPRESSOR_TYPE_T2 = 0x02U, /*!< T2 */
    EZB_ZCL_THERMOSTAT_AC_COMPRESSOR_TYPE_T3 = 0x03U, /*!< T3 */
} ezb_zcl_thermostat_server_ac_compressor_type_t;

/**
 * @brief Enumeration for ZCL ACLouverPosition attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_AC_LOUVER_POSITION_FULLY_CLOSED        = 0x01U, /*!< FullyClosed */
    EZB_ZCL_THERMOSTAT_AC_LOUVER_POSITION_FULLY_OPEN          = 0x02U, /*!< FullyOpen */
    EZB_ZCL_THERMOSTAT_AC_LOUVER_POSITION_QUARTER_OPEN        = 0x03U, /*!< QuarterOpen */
    EZB_ZCL_THERMOSTAT_AC_LOUVER_POSITION_HALF_OPEN           = 0x04U, /*!< HalfOpen */
    EZB_ZCL_THERMOSTAT_AC_LOUVER_POSITION_THREE_QUARTERS_OPEN = 0x05U, /*!< ThreeQuartersOpen */
} ezb_zcl_thermostat_server_ac_louver_position_t;

/**
 * @brief Enumeration for ZCL ACCapacityFormat attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_AC_CAPACITY_FORMAT_BT_UH = 0x00U, /*!< BTUh */
} ezb_zcl_thermostat_server_ac_capacity_format_t;

/**
 * @brief Bitmap for ZCL Occupancy attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_OCCUPANCY_OCCUPIED = 0x01U, /*!< Occupied */
} ezb_zcl_thermostat_server_occupancy_t;

/**
 * @brief Bitmap for ZCL HVACSystemTypeConfiguration attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_HVAC_SYSTEM_TYPE_CONFIGURATION_COOLING_SYSTEM_STAGE = 0x03U, /*!< CoolingSystemStage */
    EZB_ZCL_THERMOSTAT_HVAC_SYSTEM_TYPE_CONFIGURATION_HEATING_SYSTEM_STAGE = 0x0cU, /*!< HeatingSystemStage */
    EZB_ZCL_THERMOSTAT_HVAC_SYSTEM_TYPE_CONFIGURATION_HEATING_SYSTEM_TYPE  = 0x10U, /*!< HeatingSystemType */
    EZB_ZCL_THERMOSTAT_HVAC_SYSTEM_TYPE_CONFIGURATION_HEATING_FUEL_SOURCE  = 0x20U, /*!< HeatingFuelSource */
} ezb_zcl_thermostat_server_hvac_system_type_configuration_t;

/**
 * @brief Bitmap for ZCL RemoteSensing attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_REMOTE_SENSING_LOCAL_TEMPERATURE_REMOTE   = 0x01U, /*!< LocalTemperatureRemote */
    EZB_ZCL_THERMOSTAT_REMOTE_SENSING_OUTDOOR_TEMPERATURE_REMOTE = 0x02U, /*!< OutdoorTemperatureRemote */
    EZB_ZCL_THERMOSTAT_REMOTE_SENSING_OCCUPANCY_REMOTE           = 0x04U, /*!< OccupancyRemote */
} ezb_zcl_thermostat_server_remote_sensing_t;

/**
 * @brief Bitmap for ZCL AlarmMask attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_ALARM_MASK_INITIALIZATION_FAILURE   = 0x01U, /*!< InitializationFailure */
    EZB_ZCL_THERMOSTAT_ALARM_MASK_HARDWARE_FAILURE         = 0x02U, /*!< HardwareFailure */
    EZB_ZCL_THERMOSTAT_ALARM_MASK_SELF_CALIBRATION_FAILURE = 0x04U, /*!< SelfCalibrationFailure */
} ezb_zcl_thermostat_server_alarm_mask_t;

/**
 * @brief Bitmap for ZCL ThermostatProgrammingOperationMode attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_THERMOSTAT_PROGRAMMING_OPERATION_MODE_PROGRAMMING_MODE       = 0x01U, /*!< ProgrammingMode */
    EZB_ZCL_THERMOSTAT_THERMOSTAT_PROGRAMMING_OPERATION_MODE_AUTO_OR_RECOVERY       = 0x02U, /*!< AutoOrRecovery */
    EZB_ZCL_THERMOSTAT_THERMOSTAT_PROGRAMMING_OPERATION_MODE_ECONOMY_OR_ENERGY_STAR = 0x04U, /*!< EconomyOrEnergyStar */
} ezb_zcl_thermostat_server_thermostat_programming_operation_mode_t;

/**
 * @brief Bitmap for ZCL ThermostatRunningState attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_THERMOSTAT_RUNNING_STATE_HEAT_ON              = 0x01U, /*!< HeatOn */
    EZB_ZCL_THERMOSTAT_THERMOSTAT_RUNNING_STATE_COOL_ON              = 0x02U, /*!< CoolOn */
    EZB_ZCL_THERMOSTAT_THERMOSTAT_RUNNING_STATE_FAN_ON               = 0x04U, /*!< FanOn */
    EZB_ZCL_THERMOSTAT_THERMOSTAT_RUNNING_STATE_HEAT_SECOND_STAGE_ON = 0x08U, /*!< HeatSecondStageOn */
    EZB_ZCL_THERMOSTAT_THERMOSTAT_RUNNING_STATE_COOL_SECOND_STAGE_ON = 0x10U, /*!< CoolSecondStageOn */
    EZB_ZCL_THERMOSTAT_THERMOSTAT_RUNNING_STATE_FAN_SECOND_STAGE_ON  = 0x20U, /*!< FanSecondStageOn */
    EZB_ZCL_THERMOSTAT_THERMOSTAT_RUNNING_STATE_FAN_THIRD_STAGE_ON   = 0x40U, /*!< FanThirdStageOn */
} ezb_zcl_thermostat_server_thermostat_running_state_t;

/**
 * @brief Bitmap for ZCL ACErrorCode attribute of Thermostat.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_AC_ERROR_CODE_COMPRESSOR_FAILURE_OR_REFRIGERANT_LEAKAGE =
        0x01U, /*!< CompressorFailureOrRefrigerantLeakage */
    EZB_ZCL_THERMOSTAT_AC_ERROR_CODE_ROOM_TEMPERATURE_SENSOR_FAILURE        = 0x02U, /*!< RoomTemperatureSensorFailure */
    EZB_ZCL_THERMOSTAT_AC_ERROR_CODE_OUTDOOR_TEMPERATURE_SENSOR_FAILURE     = 0x04U, /*!< OutdoorTemperatureSensorFailure */
    EZB_ZCL_THERMOSTAT_AC_ERROR_CODE_INDOOR_COIL_TEMPERATURE_SENSOR_FAILURE = 0x08U, /*!< IndoorCoilTemperatureSensorFailure */
    EZB_ZCL_THERMOSTAT_AC_ERROR_CODE_FAN_FAILURE                            = 0x10U, /*!< FanFailure */
} ezb_zcl_thermostat_server_ac_error_code_t;

/** @brief Default value of LocalTemperature in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_LOCAL_TEMPERATURE_DEFAULT_VALUE (-1)

/** @brief Minimum value of LocalTemperature in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_LOCAL_TEMPERATURE_MIN_VALUE (0x954d)

/** @brief Maximum value of LocalTemperature in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_LOCAL_TEMPERATURE_MAX_VALUE (0x7fff)
/** @brief Default value of OutdoorTemperature in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OUTDOOR_TEMPERATURE_DEFAULT_VALUE (-1)

/** @brief Minimum value of OutdoorTemperature in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OUTDOOR_TEMPERATURE_MIN_VALUE (0x954d)

/** @brief Maximum value of OutdoorTemperature in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OUTDOOR_TEMPERATURE_MAX_VALUE (0x7fff)
/** @brief Default value of Occupancy in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPANCY_DEFAULT_VALUE (0x00)

/** @brief Default value of AbsMinHeatSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ABS_MIN_HEAT_SETPOINT_LIMIT_DEFAULT_VALUE (0x02bc)

/** @brief Minimum value of AbsMinHeatSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ABS_MIN_HEAT_SETPOINT_LIMIT_MIN_VALUE (0x954d)

/** @brief Maximum value of AbsMinHeatSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ABS_MIN_HEAT_SETPOINT_LIMIT_MAX_VALUE (0x7fff)
/** @brief Default value of AbsMaxHeatSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ABS_MAX_HEAT_SETPOINT_LIMIT_DEFAULT_VALUE (0x0bb8)

/** @brief Minimum value of AbsMaxHeatSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ABS_MAX_HEAT_SETPOINT_LIMIT_MIN_VALUE (0x954d)

/** @brief Maximum value of AbsMaxHeatSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ABS_MAX_HEAT_SETPOINT_LIMIT_MAX_VALUE (0x7fff)
/** @brief Default value of AbsMinCoolSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ABS_MIN_COOL_SETPOINT_LIMIT_DEFAULT_VALUE (0x0640)

/** @brief Minimum value of AbsMinCoolSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ABS_MIN_COOL_SETPOINT_LIMIT_MIN_VALUE (0x954d)

/** @brief Maximum value of AbsMinCoolSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ABS_MIN_COOL_SETPOINT_LIMIT_MAX_VALUE (0x7fff)
/** @brief Default value of AbsMaxCoolSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ABS_MAX_COOL_SETPOINT_LIMIT_DEFAULT_VALUE (0x0c80)

/** @brief Minimum value of AbsMaxCoolSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ABS_MAX_COOL_SETPOINT_LIMIT_MIN_VALUE (0x954d)

/** @brief Maximum value of AbsMaxCoolSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ABS_MAX_COOL_SETPOINT_LIMIT_MAX_VALUE (0x7fff)

/** @brief Minimum value of PICoolingDemand in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_PI_COOLING_DEMAND_MIN_VALUE (0x00)

/** @brief Maximum value of PICoolingDemand in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_PI_COOLING_DEMAND_MAX_VALUE (0x64)

/** @brief Minimum value of PIHeatingDemand in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_PI_HEATING_DEMAND_MIN_VALUE (0x00)

/** @brief Maximum value of PIHeatingDemand in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_PI_HEATING_DEMAND_MAX_VALUE (0x64)
/** @brief Default value of HVACSystemTypeConfiguration in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_HVAC_SYSTEM_TYPE_CONFIGURATION_DEFAULT_VALUE (0x00)

/** @brief Default value of LocalTemperatureCalibration in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_LOCAL_TEMPERATURE_CALIBRATION_DEFAULT_VALUE (0x00)

/** @brief Minimum value of LocalTemperatureCalibration in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_LOCAL_TEMPERATURE_CALIBRATION_MIN_VALUE (0xe7)

/** @brief Maximum value of LocalTemperatureCalibration in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_LOCAL_TEMPERATURE_CALIBRATION_MAX_VALUE (0x19)
/** @brief Default value of OccupiedCoolingSetpoint in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_COOLING_SETPOINT_DEFAULT_VALUE (0x0a28)

/** @brief Minimum value of OccupiedCoolingSetpoint in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_COOLING_SETPOINT_MIN_VALUE (0x954d)

/** @brief Maximum value of OccupiedCoolingSetpoint in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_COOLING_SETPOINT_MAX_VALUE (0x7fff)
/** @brief Default value of OccupiedHeatingSetpoint in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_HEATING_SETPOINT_DEFAULT_VALUE (0x07d0)

/** @brief Minimum value of OccupiedHeatingSetpoint in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_HEATING_SETPOINT_MIN_VALUE (0x954d)

/** @brief Maximum value of OccupiedHeatingSetpoint in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_HEATING_SETPOINT_MAX_VALUE (0x7fff)
/** @brief Default value of UnoccupiedCoolingSetpoint in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_COOLING_SETPOINT_DEFAULT_VALUE (0x0a28)

/** @brief Minimum value of UnoccupiedCoolingSetpoint in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_COOLING_SETPOINT_MIN_VALUE (0x954d)

/** @brief Maximum value of UnoccupiedCoolingSetpoint in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_COOLING_SETPOINT_MAX_VALUE (0x7fff)
/** @brief Default value of UnoccupiedHeatingSetpoint in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_HEATING_SETPOINT_DEFAULT_VALUE (0x07d0)

/** @brief Minimum value of UnoccupiedHeatingSetpoint in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_HEATING_SETPOINT_MIN_VALUE (0x954d)

/** @brief Maximum value of UnoccupiedHeatingSetpoint in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_HEATING_SETPOINT_MAX_VALUE (0x7fff)
/** @brief Default value of MinHeatSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT_DEFAULT_VALUE (0x02bc)

/** @brief Minimum value of MinHeatSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT_MIN_VALUE (0x954d)

/** @brief Maximum value of MinHeatSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT_MAX_VALUE (0x7fff)
/** @brief Default value of MaxHeatSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT_DEFAULT_VALUE (0x0bb8)

/** @brief Minimum value of MaxHeatSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT_MIN_VALUE (0x954d)

/** @brief Maximum value of MaxHeatSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT_MAX_VALUE (0x7fff)
/** @brief Default value of MinCoolSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MIN_COOL_SETPOINT_LIMIT_DEFAULT_VALUE (0x0640)

/** @brief Minimum value of MinCoolSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MIN_COOL_SETPOINT_LIMIT_MIN_VALUE (0x954d)

/** @brief Maximum value of MinCoolSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MIN_COOL_SETPOINT_LIMIT_MAX_VALUE (0x7fff)
/** @brief Default value of MaxCoolSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MAX_COOL_SETPOINT_LIMIT_DEFAULT_VALUE (0x0c80)

/** @brief Minimum value of MaxCoolSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MAX_COOL_SETPOINT_LIMIT_MIN_VALUE (0x954d)

/** @brief Maximum value of MaxCoolSetpointLimit in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MAX_COOL_SETPOINT_LIMIT_MAX_VALUE (0x7fff)
/** @brief Default value of MinSetpointDeadBand in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MIN_SETPOINT_DEAD_BAND_DEFAULT_VALUE (0x19)

/** @brief Minimum value of MinSetpointDeadBand in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MIN_SETPOINT_DEAD_BAND_MIN_VALUE (0x00)

/** @brief Maximum value of MinSetpointDeadBand in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_MIN_SETPOINT_DEAD_BAND_MAX_VALUE (0x19)
/** @brief Default value of RemoteSensing in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_REMOTE_SENSING_DEFAULT_VALUE (0x00)

/** @brief Minimum value of RemoteSensing in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_REMOTE_SENSING_MIN_VALUE (0x00)

/** @brief Maximum value of RemoteSensing in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_REMOTE_SENSING_MAX_VALUE (0x00)
/** @brief Default value of ControlSequenceOfOperation in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_CONTROL_SEQUENCE_OF_OPERATION_DEFAULT_VALUE (0x04)

/** @brief Default value of SystemMode in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_SYSTEM_MODE_DEFAULT_VALUE (0x01)

/** @brief Default value of AlarmMask in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_ALARM_MASK_DEFAULT_VALUE (0x00)

/** @brief Default value of ThermostatRunningMode in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_THERMOSTAT_RUNNING_MODE_DEFAULT_VALUE (0x00)

/** @brief Default value of NumberOfWeeklyTransitions in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_NUMBER_OF_WEEKLY_TRANSITIONS_DEFAULT_VALUE (0x00)

/** @brief Minimum value of NumberOfWeeklyTransitions in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_NUMBER_OF_WEEKLY_TRANSITIONS_MIN_VALUE (0x00)

/** @brief Maximum value of NumberOfWeeklyTransitions in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_NUMBER_OF_WEEKLY_TRANSITIONS_MAX_VALUE (0xff)
/** @brief Default value of NumberOfDailyTransitions in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_NUMBER_OF_DAILY_TRANSITIONS_DEFAULT_VALUE (0x00)

/** @brief Minimum value of NumberOfDailyTransitions in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_NUMBER_OF_DAILY_TRANSITIONS_MIN_VALUE (0x00)

/** @brief Maximum value of NumberOfDailyTransitions in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_NUMBER_OF_DAILY_TRANSITIONS_MAX_VALUE (0xff)
/** @brief Default value of TemperatureSetpointHold in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_TEMPERATURE_SETPOINT_HOLD_DEFAULT_VALUE (0x00)

/** @brief Default value of TemperatureSetpointHoldDuration in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_TEMPERATURE_SETPOINT_HOLD_DURATION_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of TemperatureSetpointHoldDuration in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_TEMPERATURE_SETPOINT_HOLD_DURATION_MIN_VALUE (0x0000)

/** @brief Maximum value of TemperatureSetpointHoldDuration in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_TEMPERATURE_SETPOINT_HOLD_DURATION_MAX_VALUE (0x05a0)
/** @brief Default value of ThermostatProgrammingOperationMode in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_THERMOSTAT_PROGRAMMING_OPERATION_MODE_DEFAULT_VALUE (0x00)

/** @brief Default value of SetpointChangeSource in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_SETPOINT_CHANGE_SOURCE_DEFAULT_VALUE (0x00)

/** @brief Minimum value of SetpointChangeSource in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_SETPOINT_CHANGE_SOURCE_MIN_VALUE (0x00)

/** @brief Maximum value of SetpointChangeSource in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_SETPOINT_CHANGE_SOURCE_MAX_VALUE (0xff)
/** @brief Default value of SetpointChangeAmount in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_SETPOINT_CHANGE_AMOUNT_DEFAULT_VALUE (0x8000)

/** @brief Minimum value of SetpointChangeAmount in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_SETPOINT_CHANGE_AMOUNT_MIN_VALUE (0x0000)

/** @brief Maximum value of SetpointChangeAmount in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_SETPOINT_CHANGE_AMOUNT_MAX_VALUE (0xffff)
/** @brief Default value of SetpointChangeSourceTimestamp in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_SETPOINT_CHANGE_SOURCE_TIMESTAMP_DEFAULT_VALUE (0x00000000)

/** @brief Minimum value of SetpointChangeSourceTimestamp in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_SETPOINT_CHANGE_SOURCE_TIMESTAMP_MIN_VALUE (0x00000000)

/** @brief Maximum value of SetpointChangeSourceTimestamp in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_SETPOINT_CHANGE_SOURCE_TIMESTAMP_MAX_VALUE (0xfffffffe)
/** @brief Default value of OccupiedSetback in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_SETBACK_DEFAULT_VALUE (0xff)

/** @brief Minimum value of OccupiedSetback in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_SETBACK_MIN_VALUE (0x00)

/** @brief Maximum value of OccupiedSetback in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_SETBACK_MAX_VALUE (0xff)
/** @brief Default value of OccupiedSetbackMin in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_SETBACK_MIN_DEFAULT_VALUE (0xff)

/** @brief Minimum value of OccupiedSetbackMin in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_SETBACK_MIN_MIN_VALUE (0x00)

/** @brief Maximum value of OccupiedSetbackMin in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_SETBACK_MIN_MAX_VALUE (0xff)
/** @brief Default value of OccupiedSetbackMax in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_SETBACK_MAX_DEFAULT_VALUE (0xff)

/** @brief Minimum value of OccupiedSetbackMax in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_SETBACK_MAX_MIN_VALUE (0x00)

/** @brief Maximum value of OccupiedSetbackMax in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_OCCUPIED_SETBACK_MAX_MAX_VALUE (0xff)
/** @brief Default value of UnoccupiedSetback in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_SETBACK_DEFAULT_VALUE (0xff)

/** @brief Minimum value of UnoccupiedSetback in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_SETBACK_MIN_VALUE (0x00)

/** @brief Maximum value of UnoccupiedSetback in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_SETBACK_MAX_VALUE (0xff)
/** @brief Default value of UnoccupiedSetbackMin in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_SETBACK_MIN_DEFAULT_VALUE (0xff)

/** @brief Minimum value of UnoccupiedSetbackMin in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_SETBACK_MIN_MIN_VALUE (0x00)

/** @brief Maximum value of UnoccupiedSetbackMin in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_SETBACK_MIN_MAX_VALUE (0xff)
/** @brief Default value of UnoccupiedSetbackMax in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_SETBACK_MAX_DEFAULT_VALUE (0xff)

/** @brief Minimum value of UnoccupiedSetbackMax in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_SETBACK_MAX_MIN_VALUE (0x00)

/** @brief Maximum value of UnoccupiedSetbackMax in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_UNOCCUPIED_SETBACK_MAX_MAX_VALUE (0xff)
/** @brief Default value of EmergencyHeatDelta in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_EMERGENCY_HEAT_DELTA_DEFAULT_VALUE (0xff)

/** @brief Minimum value of EmergencyHeatDelta in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_EMERGENCY_HEAT_DELTA_MIN_VALUE (0x00)

/** @brief Maximum value of EmergencyHeatDelta in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_EMERGENCY_HEAT_DELTA_MAX_VALUE (0xff)
/** @brief Default value of ACType in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_TYPE_DEFAULT_VALUE (0x00)

/** @brief Default value of ACCapacity in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_CAPACITY_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of ACCapacity in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_CAPACITY_MIN_VALUE (0x0000)

/** @brief Maximum value of ACCapacity in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_CAPACITY_MAX_VALUE (0xffff)
/** @brief Default value of ACRefrigerantType in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_REFRIGERANT_TYPE_DEFAULT_VALUE (0x00)

/** @brief Default value of ACCompressorType in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_COMPRESSOR_TYPE_DEFAULT_VALUE (0x00)

/** @brief Default value of ACErrorCode in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_ERROR_CODE_DEFAULT_VALUE (0x00000000)

/** @brief Minimum value of ACErrorCode in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_ERROR_CODE_MIN_VALUE (0x00000000)

/** @brief Maximum value of ACErrorCode in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_ERROR_CODE_MAX_VALUE (0xffffffff)
/** @brief Default value of ACLouverPosition in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_LOUVER_POSITION_DEFAULT_VALUE (0x00)

/** @brief Default value of ACCoilTemperature in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_COIL_TEMPERATURE_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of ACCoilTemperature in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_COIL_TEMPERATURE_MIN_VALUE (0x954d)

/** @brief Maximum value of ACCoilTemperature in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_COIL_TEMPERATURE_MAX_VALUE (0x7fff)
/** @brief Default value of ACCapacityFormat in Thermostat cluster */
#define EZB_ZCL_THERMOSTAT_AC_CAPACITY_FORMAT_DEFAULT_VALUE (0x00)

/**
 * @brief Received Command identifiers for the Thermostat cluster.
 */
typedef enum {
    EZB_ZCL_CMD_THERMOSTAT_SETPOINT_RAISE_OR_LOWER_ID = 0x00U, /*!< SetpointRaiseOrLower command. */
    EZB_ZCL_CMD_THERMOSTAT_SET_WEEKLY_SCHEDULE_ID     = 0x01U, /*!< SetWeeklySchedule command. */
    EZB_ZCL_CMD_THERMOSTAT_GET_WEEKLY_SCHEDULE_ID     = 0x02U, /*!< GetWeeklySchedule command. */
    EZB_ZCL_CMD_THERMOSTAT_CLEAR_WEEKLY_SCHEDULE_ID   = 0x03U, /*!< ClearWeeklySchedule command. */
    EZB_ZCL_CMD_THERMOSTAT_GET_RELAY_STATUS_LOG_ID    = 0x04U, /*!< GetRelayStatusLog command. */
} ezb_zcl_thermostat_server_cmd_id_t;

/**
 * @brief Received Command identifiers for the Thermostat cluster.
 */
typedef enum {
    EZB_ZCL_CMD_THERMOSTAT_GET_WEEKLY_SCHEDULE_RESPONSE_ID  = 0x00U, /*!< GetWeeklyScheduleResponse command. */
    EZB_ZCL_CMD_THERMOSTAT_GET_RELAY_STATUS_LOG_RESPONSE_ID = 0x01U, /*!< GetRelayStatusLogResponse command. */
} ezb_zcl_thermostat_client_cmd_id_t;

typedef ezb_zcl_thermostat_cluster_server_config_t ezb_zcl_thermostat_cluster_config_t;

/**
 * @brief Add an attribute to an thermostat cluster descriptor.
 *
 * @param cluster_desc Pointer to the thermostat cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_thermostat_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an thermostat cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the thermostat cluster configuration structure, refer to
 * ezb_zcl_thermostat_cluster_server_config_t or ezb_zcl_thermostat_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_thermostat_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the Thermostat cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_thermostat_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the Thermostat cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_thermostat_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_THERMOSTAT_CLIENT_ROLE_INIT ezb_zcl_thermostat_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_THERMOSTAT_SERVER_ROLE_INIT ezb_zcl_thermostat_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
