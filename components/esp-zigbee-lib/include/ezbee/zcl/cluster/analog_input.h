/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/analog_input_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Analog Input cluster application types
 *      The ApplicationType attribute indicates the specific application usage
 *      for the cluster. ApplicationType is subdivided into Group, Type and
 *      an Index number, as follows:
 *
 *      Group = Bits 24 to 31
 *        An indication of the cluster this attribute is part of. Analog Input
 *        clusters have Group = 0x01.
 *
 *      Type = Bits 16 to 23
 *        The physical quantity that the PresentValue attribute of the cluster
 *        represents.
 *
 *      Index = Bits 0 to 15
 *        The specific application usage of the cluster.
 */

/**
 * @brief Macros for Group ID of ZCL Analog Input
 */
#define EZB_ZCL_AI_GROUP_ID 0x00

/**
 * @brief Macros for ApplicationType attribute of ZCL Analog Input
 */
#define EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(_type, _id) (((_type & 0xff) << 16) | (_id & 0xFFFF))

/** @brief Values for 'Temperature in degrees Celsius' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_TEMPERATURE_2_PIPE_ENTERING =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_TEMPERATURE, 0x0000), /*!< 2 Pipe Entering */
    EZB_ZCL_AI_TEMPERATURE_2_PIPE_LEAVING,                                                          /*!< 2 Pipe Leaving */
    EZB_ZCL_AI_TEMPERATURE_BOILER_ENTERING,                                                         /*!< Boiler Entering */
    EZB_ZCL_AI_TEMPERATURE_BOILER_LEAVING,                                                          /*!< Boiler Leaving */
    EZB_ZCL_AI_TEMPERATURE_CHILLER_CHILLED_WATER_ENTERING,   /*!< Chiller Chilled Water Entering */
    EZB_ZCL_AI_TEMPERATURE_CHILLER_CHILLED_WATER_LEAVING,    /*!< Chiller Chilled Water Leaving */
    EZB_ZCL_AI_TEMPERATURE_CHILLER_CONDENSER_WATER_ENTERING, /*!< Chiller Condenser Water Entering */
    EZB_ZCL_AI_TEMPERATURE_CHILLER_CONDENSER_WATER_LEAVING,  /*!< Chiller Condenser Water Leaving */
    EZB_ZCL_AI_TEMPERATURE_COLD_DECK,                        /*!< Cold Deck */
    EZB_ZCL_AI_TEMPERATURE_COOLING_COIL_DISCHARGE,           /*!< Cooling Coil Discharge */

    EZB_ZCL_AI_TEMPERATURE_COOLING_ENTERING_WATER, /*!< Cooling entering water */
    EZB_ZCL_AI_TEMPERATURE_COOLING_LEAVING_WATER,  /*!< Cooling leaving Water */
    EZB_ZCL_AI_TEMPERATURE_CONDENSER_WATER_RETURN, /*!< Condenser water return */
    EZB_ZCL_AI_TEMPERATURE_CONDENSER_WATER_SUPPLY, /*!< Condenser water supply */
    EZB_ZCL_AI_TEMPERATURE_DECOUPLE_LOOP_0,        /*!< Decouple loop 0. Note: Decouple loop is duplicated in spec */
    EZB_ZCL_AI_TEMPERATURE_BUILDING_LOAD,          /*!< Building load */
    EZB_ZCL_AI_TEMPERATURE_DECOUPLE_LOOP_1,        /*!< Decouple loop 1 */
    EZB_ZCL_AI_TEMPERATURE_DEW_POINT,              /*!< Dew point */
    EZB_ZCL_AI_TEMPERATURE_DISCHARGE_AIR,          /*!< Discharge air */
    EZB_ZCL_AI_TEMPERATURE_DISCHARGE,              /*!< Discharge */

    EZB_ZCL_AI_TEMPERATURE_EXHAUST_AIR_AFTER_HEAT_RECOVERY, /*!< Exhaust air after heat recovery */
    EZB_ZCL_AI_TEMPERATURE_EXHAUST_AIR,                     /*!< Exhaust air */
    EZB_ZCL_AI_TEMPERATURE_GLYCOL,                          /*!< Glycol */
    EZB_ZCL_AI_TEMPERATURE_HEAT_RECOVERY_AIR,               /*!< Heat recovery air */
    EZB_ZCL_AI_TEMPERATURE_HOT_DECK,                        /*!< Hot deck */
    EZB_ZCL_AI_TEMPERATURE_HEAT_EXCHANGER_BYPASS,           /*!< Heat exchanger bypass */
    EZB_ZCL_AI_TEMPERATURE_HEAT_EXCHANGER_ENTERING,         /*!< Heat exchanger entering */
    EZB_ZCL_AI_TEMPERATURE_HEAT_EXCHANGER_LEAVING,          /*!< Heat eXchanger leaving */
    EZB_ZCL_AI_TEMPERATURE_MECHANICAL_ROOM,                 /*!< Mechanical room */
    EZB_ZCL_AI_TEMPERATURE_MIXED_AIR_0,                     /*!< Mixed air 0.  Mixed air is duplicated in spec */

    EZB_ZCL_AI_TEMPERATURE_MIXED_AIR_1,                  /*!< Mixed air 1 */
    EZB_ZCL_AI_TEMPERATURE_OUTDOOR_AIR_DEWPOINT,         /*!< Outdoor air dewpoint */
    EZB_ZCL_AI_TEMPERATURE_OUTDOOR_AIR,                  /*!< Outdoor air */
    EZB_ZCL_AI_TEMPERATURE_PREHEAT_AIR,                  /*!< Preheat air */
    EZB_ZCL_AI_TEMPERATURE_PREHEAT_ENTERING_WATER,       /*!< Preheat entering water */
    EZB_ZCL_AI_TEMPERATURE_PREHEAT_LEAVING_WATER,        /*!< Preheat leaving water */
    EZB_ZCL_AI_TEMPERATURE_PRIMARY_CHILLED_WATER_RETURN, /*!< Primary chilled water return */
    EZB_ZCL_AI_TEMPERATURE_PRIMARY_CHILLED_WATER_SUPPLY, /*!< Primary chilled water supply */
    EZB_ZCL_AI_TEMPERATURE_PRIMARY_HOT_WATER_RETURN,     /*!< Primary hot watter return */
    EZB_ZCL_AI_TEMPERATURE_PRIMARY_HOT_WATER_SUPPLY,     /*!< Primary hot watter supply */

    EZB_ZCL_AI_TEMPERATURE_REHEAT_COIL_DISCHARGE,          /*!< Reheat coil discharge */
    EZB_ZCL_AI_TEMPERATURE_REHEAT_ENTERING_WATER,          /*!< Reheat entering water */
    EZB_ZCL_AI_TEMPERATURE_REHEAT_LEAVING_WATER,           /*!< Reheat leaving water */
    EZB_ZCL_AI_TEMPERATURE_RETURN_AIR,                     /*!< Return air */
    EZB_ZCL_AI_TEMPERATURE_SECONDARY_CHILLED_WATER_RETURN, /*!< Secondary chilled water return */
    EZB_ZCL_AI_TEMPERATURE_SECONDARY_CHILLED_WATER_SUPPLY, /*!< Secondary chilled water supply */
    EZB_ZCL_AI_TEMPERATURE_SECONDARY_HW_RETURN,            /*!< Secondary hw return */
    EZB_ZCL_AI_TEMPERATURE_SECONDARY_HW_SUPPLY,            /*!< Secondary hw supply */
    EZB_ZCL_AI_TEMPERATURE_SIDELOOP_RESET,                 /*!< Sideloop reset */
    EZB_ZCL_AI_TEMPERATURE_SIDELOOP_SETPOINT,              /*!< Sideloop setpoint */

    EZB_ZCL_AI_TEMPERATURE_SIDELOOP,                    /*!< Sideloop */
    EZB_ZCL_AI_TEMPERATURE_SOURCE,                      /*!< Source */
    EZB_ZCL_AI_TEMPERATURE_SUPPLY_AIR,                  /*!< Supply air */
    EZB_ZCL_AI_TEMPERATURE_SUPPLY_LOW_LIMIT,            /*!< Supply low limit */
    EZB_ZCL_AI_TEMPERATURE_TOWER_BASIN,                 /*!< Tower basin */
    EZB_ZCL_AI_TEMPERATURE_TWO_PIPE_LEAVING_WATER,      /*!< Two pipe leaving water */
    EZB_ZCL_AI_TEMPERATURE_RESERVED,                    /*!< Reserved */
    EZB_ZCL_AI_TEMPERATURE_ZONE_DEWPOINT,               /*!< Zone dewpoint */
    EZB_ZCL_AI_TEMPERATURE_ZONE_SENSOR_SETPOINT,        /*!< Zone sensor setpoint */
    EZB_ZCL_AI_TEMPERATURE_ZONE_SENSOR_SETPOINT_OFFSET, /*!< Zone sensor setpoint offset */

    EZB_ZCL_AI_TEMPERATURE_ZONE, /*!< Zone */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_TEMPERATURE_OTHER =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_TEMPERATURE, 0xFFFF), /*!< Other */
} ezb_zcl_ai_temperature_in_degrees_celsius_t;

/** @brief Values for 'Relative Humidity in %' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_HUMIDITY_DISCHARGE =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_HUMIDITY, 0x0000), /*!< Discharge */
    EZB_ZCL_AI_HUMIDITY_EXHAUST,                                                                 /*!< Exhaust */
    EZB_ZCL_AI_HUMIDITY_HOT_DECK,                                                                /*!< Hot deck */
    EZB_ZCL_AI_HUMIDITY_MIXED_AIR,                                                               /*!< Mixed air */
    EZB_ZCL_AI_HUMIDITY_OUTDOOR_AIR,                                                             /*!< Outdoor air */
    EZB_ZCL_AI_HUMIDITY_RETURN,                                                                  /*!< Return */
    EZB_ZCL_AI_HUMIDITY_SIDELOOP,                                                                /*!< Sideloop */
    EZB_ZCL_AI_HUMIDITY_SPACE,                                                                   /*!< Space */
    EZB_ZCL_AI_HUMIDITY_ZONE,                                                                    /*!< Zone */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_HUMIDITY_OTHER =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_HUMIDITY, 0xFFFF), /*!< Other */
} ezb_zcl_ai_relative_humidity_in_percent_t;

/** @brief Values for 'Pressure in Pascal' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_PRESSURE_BOILER_PUMP_DIFFERENTIAL =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_PRESSURE,
                                        0x0000),             /*!< Boiler pump differential */
    EZB_ZCL_AI_PRESSURE_BUILDING_STATIC,                     /*!< Building static */
    EZB_ZCL_AI_PRESSURE_COLD_DECK_DIFFERENTIAL_SENSOR,       /*!< Cold deck differential sensor */
    EZB_ZCL_AI_PRESSURE_CHILLED_WATER_BUILDING_DIFFERENTIAL, /*!< Chilled water building differential */
    EZB_ZCL_AI_PRESSURE_COLD_DECK_DIFFERENTIAL,              /*!< Cold deck differential */
    EZB_ZCL_AI_PRESSURE_COLD_DECK_STATIC,                    /*!< Cold deck static */
    EZB_ZCL_AI_PRESSURE_CONDENSER_WATER_PUMP_DIFFERENTIAL,   /*!< Condenser water pump differential */
    EZB_ZCL_AI_PRESSURE_DISCHARGE_DIFFERENTIAL,              /*!< Discharge differential */
    EZB_ZCL_AI_PRESSURE_DISCHARGE_STATIC_1,                  /*!< Discharge static 1 */
    EZB_ZCL_AI_PRESSURE_DISCHARGE_STATIC_2,                  /*!< Discharge static 2 */

    EZB_ZCL_AI_PRESSURE_EXHAUST_AIR_DIFFERENTIAL, /*!< Exhaust air differential */
    EZB_ZCL_AI_PRESSURE_EXHAUST_AIR_STATIC,       /*!< Exhaust air static */
    EZB_ZCL_AI_PRESSURE_EXHAUST_DIFFERENTIAL_0, /*!< Exhaust differential 0. Note: Exhaust differential is duplicated in spec */
    EZB_ZCL_AI_PRESSURE_EXHAUST_DIFFERENTIAL_1, /*!< Exhaust differential 1 */
    EZB_ZCL_AI_PRESSURE_HOT_DECK_DIFFERENTIAL_0, /*!< Hot deck differential 0. Note: Hot Deck differential is duplicated in spec
                                                  */
    EZB_ZCL_AI_PRESSURE_HOT_DECK_DIFFERENTIAL_1, /*!< Hot deck differential 1 */
    EZB_ZCL_AI_PRESSURE_HOT_DECK_STATIC,         /*!< Hot deck static */
    EZB_ZCL_AI_PRESSURE_HOT_WATER_BLDG_DIFF,     /*!< Hot water bldg Diff */
    EZB_ZCL_AI_PRESSURE_HEAT_EXCHANGER_STEAM,    /*!< Heat exchanger steam */
    EZB_ZCL_AI_PRESSURE_MIN_OUTDOOR_AIR_DIFFERENTIAL, /*!< Min outdoor air differential */

    EZB_ZCL_AI_PRESSURE_OUTDOOR_AIR_DIFFERENTIAL,                  /*!< Outdoor air differential */
    EZB_ZCL_AI_PRESSURE_PRIMARY_CHILLED_WATER_PUMP_DIFFERENTIAL,   /*!< Primary chilled water pump differential */
    EZB_ZCL_AI_PRESSURE_PRIMATY_HOT_WATER_PUMP_DIFFERENTIAL,       /*!< Primary hot water pump differential */
    EZB_ZCL_AI_PRESSURE_RELIEF_DIFFERENTIAL,                       /*!< Relief differential */
    EZB_ZCL_AI_PRESSURE_RETURN_AIR_STATIC,                         /*!< Return air Static */
    EZB_ZCL_AI_PRESSURE_RETURN_DIFFERENTIAL,                       /*!< Return differential */
    EZB_ZCL_AI_PRESSURE_SECONDARY_CHILLED_WATER_PUMP_DIFFERENTIAL, /*!< Secondary chilled water pump differential */
    EZB_ZCL_AI_PRESSURE_SECONDARY_HOT_WATER_PUMP_DIFFERENTIAL,     /*!< Secondary hot water pump differential */
    EZB_ZCL_AI_PRESSURE_SIDELOOP,                                  /*!< Sideloop */
    EZB_ZCL_AI_PRESSURE_STEAM,                                     /*!< Steam */
    EZB_ZCL_AI_PRESSURE_SUPPLY_DIFFERENTIAL_SENSOR,                /*!< Supply differential sensor */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_PRESSURE_OTHER =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_PRESSURE, 0xFFFF), /*!< Other */
} ezb_zcl_ai_pressure_in_pascal_t;

/** @brief Values for 'Flow in Liters per Second' type of Analog Input cluster */
typedef enum {
    /*! Chilled water */
    EZB_ZCL_AI_FLOW_CHILLED_WATER = EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_FLOW, 0x0000),
    EZB_ZCL_AI_FLOW_CHILLER_CHILLED_WATER,        /*!< Chiller chilled water */
    EZB_ZCL_AI_FLOW_CHILLER_CONDENSER_WATER,      /*!< Chiller condenser water */
    EZB_ZCL_AI_FLOW_COLD_DECK,                    /*!< Cold deck */
    EZB_ZCL_AI_FLOW_DECOUPLE_LOOP,                /*!< Decouple loop */
    EZB_ZCL_AI_FLOW_DISCHARGE,                    /*!< Discharge */
    EZB_ZCL_AI_FLOW_EXHAUST_FAN,                  /*!< Exhaust fan */
    EZB_ZCL_AI_FLOW_EXHAUST,                      /*!< Exhaust */
    EZB_ZCL_AI_FLOW_FAN,                          /*!< Fan */
    EZB_ZCL_AI_FLOW_HOT_DECK,                     /*!< Flow hot deck */
    EZB_ZCL_AI_FLOW_HOT_WATER,                    /*!< Hot water */
    EZB_ZCL_AI_FLOW_MIN_OUTDOOR_AIR_FAN,          /*!< Min outdoor air fan */
    EZB_ZCL_AI_FLOW_MIN_OUTDOOR_AIR,              /*!< Min outdoor Air */
    EZB_ZCL_AI_FLOW_OUTDOOR_AIR,                  /*!< Outdoor air */
    EZB_ZCL_AI_FLOW_PRIMARY_CHILLED_WATER,        /*!< Primary chilled water */
    EZB_ZCL_AI_FLOW_RELIEF_FAN,                   /*!< Relief fan */
    EZB_ZCL_AI_FLOW_RELIEF,                       /*!< Relief */
    EZB_ZCL_AI_FLOW_RETURN_FAN,                   /*!< Return fan */
    EZB_ZCL_AI_FLOW_RETURN,                       /*!< Return */
    EZB_ZCL_AI_FLOW_SECONDARY_CHILLED_WATER_FLOW, /*!< Secondary chilled water flow */
    EZB_ZCL_AI_FLOW_SUPPLY_FAN,                   /*!< Supply fan */
    EZB_ZCL_AI_FLOW_TOWER_FAN,                    /*!< Tower fan */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_FLOW_OTHER = EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_FLOW, 0xFFFF), /*!< Other */
} ezb_zcl_ai_flow_in_liters_per_second_t;

/** @brief Values for 'Percentage %' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_PERCENTAGE_CHILLER_FULL_LOAD_AMPERAGE =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_PERCENTAGE,
                                        0x0000), /*!< Chiller full load amperage */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_PERCENTAGE_OTHER =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_PERCENTAGE, 0xFFFF), /*!< Other */
} ezb_zcl_ai_percentage_t;

/** @brief Values for 'Parts per Million PPM' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_PPM_RETURN_CARBON_DIOXIDE =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_PPM, 0x0000), /*!< Return carbon dioxide */
    EZB_ZCL_AI_PPM_ZONE_CARBON_DIOXIDE,                                                     /*!< Zone carbon dioxide */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_PPM_OTHER = EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_PPM, 0xFFFF), /*!< Other */
} ezb_zcl_ai_ppm_t;

/** @brief Values for 'Rotational Speed in RPM' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_RPM_EXHAUS_FAN_REMOTE =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_RPM, 0x0000), /*!< Exhaust fan remote */
    EZB_ZCL_AI_RPM_HEAT_RECOVERY_WHEEL_REMOTE,                                              /*!< Heat recovery wheel remote */
    EZB_ZCL_AI_RPM_MIN_OUTDOOR_AIR_FAN_REMOTE,                                              /*!< Min outdoor air fan remote */
    EZB_ZCL_AI_RPM_RELIEF_FAN_REMOTE,                                                       /*!< Relief fan remote */
    EZB_ZCL_AI_RPM_RETURN_FAN_REMOTE,                                                       /*!< Return fan remote */
    EZB_ZCL_AI_RPM_SUPPLY_FAN_REMOTE,                                                       /*!< Supply fan remote */
    EZB_ZCL_AI_RPM_VARIABLE_SPEED_DRIVE_MOTOR,                                              /*!< Variable speed drive motor */
    EZB_ZCL_AI_RPM_VARIABLE_SPEED_DRIVE_SETPOINT, /*!< Variable speed drive setpoint */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_RPM_OTHER = EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_RPM, 0xFFFF), /*!< Other */
} ezb_zcl_ai_rpm_t;

/** @brief Values for 'Current in Amps' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_CURRENT_CHILLER_AMPS =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_CURRENT_IN_AMPS, 0x0000), /*!< Chiller amps */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_CURRENT_OTHER =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_CURRENT_IN_AMPS, 0xFFFF), /*!< Other */
} ezb_zcl_ai_current_t;

/** @brief Values for 'Frequency in Hz' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_FREQUENCY_VARIABLE_SPEED_DRIVE_OUTPUT =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_FREQUENCY_IN_HZ, 0x0000), /*!< Variable speed
                                                                                                        drive output */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_FREQUENCY_OTHER =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_FREQUENCY_IN_HZ, 0xFFFF), /*!< Other */
} ezb_zcl_ai_frequency_t;

/** @brief Values for 'Power in Watts' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_POWER_IN_WATTS_CONSUMPTION =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_POWER_IN_WATTS, 0x0000), /*!< Consumption */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_POWER_IN_WATTS_OTHER =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_POWER_IN_WATTS, 0xFFFF), /*!< Other */
} ezb_zcl_ai_power_in_watts_t;

/** @brief Values for 'Power in kW' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_POWER_IN_KILOWATTS_ABSOLUTE =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_POWER_IN_KW, 0x0000), /*!< Absolute */
    EZB_ZCL_AI_POWER_IN_KILOWATTS_CONSUMPTION,                                                      /*!< Consumption */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_POWER_IN_KILOWATTS_OTHER =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_POWER_IN_KW, 0xFFFF), /*!< Other */
} ezb_zcl_ai_power_in_kilowatts_t;

/** @brief Values for 'Energy in kWH' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_ENERGY_KWH_VARIABLE_SPEED_DRIVE =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_ENERGY_IN_KWH, 0x0000), /*!< Variable
                                                                                                      speed drive */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_ENERGY_KWH_OTHER =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_ENERGY_IN_KWH, 0xFFFF), /*!< Other */
} ezb_zcl_ai_energy_kwh_t;

/** @brief Values for 'Count - Unitless' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_COUNT_UNITLESS_COUNT =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_COUNT_UNITLESS, 0x0000), /*!< Count */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_COUNT_UNITLESS_OTHER =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_COUNT_UNITLESS, 0xFFFF), /*!< Other */
} ezb_zcl_ai_count_unitless_t;

/** @brief Values for 'Enthalpy in KJoules per Kg' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_ENTHALPY_OUTDOOR_AIR =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_ENTHALPY_IN_KJOULES_PER_KG, 0x0000), /*!< Out door
                                                                                                                   air */
    EZB_ZCL_AI_ENTHALPY_RETURN_AIR, /*!< Return air */
    EZB_ZCL_AI_ENTHALPY_SPACE,      /*!< Space */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_ENTHALPY_OTHER =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_ENTHALPY_IN_KJOULES_PER_KG, 0xFFFF), /*!< Other */
} ezb_zcl_ai_enthalpy_t;

/** @brief Values for 'Time in Seconds' type of Analog Input cluster */
typedef enum {
    EZB_ZCL_AI_TIME_RELATIVE =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_TIME_IN_SECONDS, 0x0000), /*!< Relative */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AI_TIME_OTHER =
        EZB_ZCL_AI_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_TIME_IN_SECONDS, 0xFFFF), /*!< Other */
} ezb_zcl_ai_time_t;

#ifdef __cplusplus
} /*  extern "C" */
#endif
