/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/analog_output_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Analog Output cluster application types
 *      The ApplicationType attribute indicates the specific application usage
 *      for the cluster. ApplicationType is subdivided into Group, Type and
 *      an Index number, as follows:
 *
 *      Group = Bits 24 to 31
 *        An indication of the cluster this attribute is part of. Analog Output
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
 * @brief Macros for Group ID of ZCL Analog Output
 */
#define EZB_ZCL_AO_GROUP_ID 0x01

/**
 * @brief Macros for ApplicationType attribute of ZCL Analog Output
 */
#define EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(_type, _id) (((_type & 0xff) << 16) | (_id & 0xFFFF))

/** @brief Values for 'Temperature in degrees Celsius' type of Analog Output cluster */
typedef enum {
    EZB_ZCL_AO_TEMPERATURE_BOILER =
        EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_OUTPUT_APPLICATION_TYPE_TEMPERATURE, 0x0000), /*!< Boiler */
    EZB_ZCL_AO_TEMPERATURE_BOILER_SETPOINT,                                                          /*!< Boiler setpoint */
    EZB_ZCL_AO_TEMPERATURE_COLD_DECK,                                                                /*!< Cold deck */
    EZB_ZCL_AO_TEMPERATURE_CHILLER_SETPOINT_0,        /*!< Chiller setpoint 0. Note: Chiller Setpoint is duplicated in spec */
    EZB_ZCL_AO_TEMPERATURE_CHILLER_SETPOINT_1,        /*!< Chiller setpoint 1 */
    EZB_ZCL_AO_TEMPERATURE_HOT_DECK,                  /*!< Hot deck */
    EZB_ZCL_AO_TEMPERATURE_COOLING_VALVE,             /*!< Cooling valve */
    EZB_ZCL_AO_TEMPERATURE_ZONE_TEMPERATURE_SETPOINT, /*!< Zone temperature setpoint */
    EZB_ZCL_AO_TEMPERATURE_SETPOINT_OFFSET,           /*!< Setpoint offset */
    EZB_ZCL_AO_TEMPERATURE_SETPOINT_SHIFT,            /*!< Setpoint shift */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AO_TEMPERATURE_OTHER =
        EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_OUTPUT_APPLICATION_TYPE_TEMPERATURE, 0xFFFF), /*!< Other */
} ezb_zcl_ao_temperature_in_degrees_celsius_t;

/** @brief Values for 'Relative Humidity in %' type of Analog Output cluster */
typedef enum {
    EZB_ZCL_AO_HUMIDITY_HUMIDIFICATION =
        EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_OUTPUT_APPLICATION_TYPE_HUMIDITY, 0x0000), /*!< Humidification */
    EZB_ZCL_AO_HUMIDITY_ZONE_RELATIVE_HUMIDITY,                                                   /*!< Zone relative humidity */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AO_HUMIDITY_OTHER =
        EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_OUTPUT_APPLICATION_TYPE_HUMIDITY, 0xFFFF), /*!< Other */
} ezb_zcl_ao_relative_humidity_in_percent_t;

/** @brief Values for 'Percentage %' type of Analog Output cluster */
typedef enum {
    EZB_ZCL_AO_PERCENTAGE_FACE_BYPASS_DAMPER =
        EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_OUTPUT_APPLICATION_TYPE_PERCENTAGE, 0x0000), /*!< Face bypass damper */
    EZB_ZCL_AO_PERCENTAGE_HEAT_RECOVERY_VALVE,                                                      /*!< Heat recovery valve */
    EZB_ZCL_AO_PERCENTAGE_HEAT_RECOVERY_WHEEL,                                                      /*!< Heat recovery wheel */
    EZB_ZCL_AO_PERCENTAGE_HEATING_VALVE,                                                            /*!< Heating valve */
    EZB_ZCL_AO_PERCENTAGE_HOT_DECK_DAMPER,                                                          /*!< Hot deck damper */
    EZB_ZCL_AO_PERCENTAGE_2_PIPE_DAMPER,                                                            /*!< 2 pipe damper */
    EZB_ZCL_AO_PERCENTAGE_2_PIPE_VALVE,                                                             /*!< 2 pipe valve */
    EZB_ZCL_AO_PERCENTAGE_BOILER_MIXING_VALVE,                                                      /*!< Boiler mixing valve */
    EZB_ZCL_AO_PERCENTAGE_BOX_COOLING_VALVE,                                                        /*!< Box cooling valve */
    EZB_ZCL_AO_PERCENTAGE_BOX_HEATING_VALVE,                                                        /*!< Box heating valve */

    EZB_ZCL_AO_PERCENTAGE_CHILLED_WATER_BYPASS_VALVE, /*!< Chilled water bypass valve */
    EZB_ZCL_AO_PERCENTAGE_COLD_DECK_DAMPER,           /*!< Cold deck damper */
    EZB_ZCL_AO_PERCENTAGE_COOLING_DAMPER,             /*!< Cooling damper */
    EZB_ZCL_AO_PERCENTAGE_COOLING_VALVE,              /*!< Cooling valve */
    EZB_ZCL_AO_PERCENTAGE_DAMPER,                     /*!< Damper */
    EZB_ZCL_AO_PERCENTAGE_EXHAUST_AIR_DAMPER,         /*!< Exhaust air damper */
    EZB_ZCL_AO_PERCENTAGE_EXHAUST_DAMPER,             /*!< Exhaust damper */
    EZB_ZCL_AO_PERCENTAGE_HOT_WATER_BYPASS_VALVE,     /*!< Hot water bypass valve */
    EZB_ZCL_AO_PERCENTAGE_HOT_WATER_MIXING_VALVE,     /*!< Hot water mixing valve */
    EZB_ZCL_AO_PERCENTAGE_MINIMUM_OUTSIDE_AIR_DAMPER, /*!< Minimum outside air damper */

    EZB_ZCL_AO_PERCENTAGE_MINIMUM_OUTSIDE_AIR_FAN,    /*!< Minimum outside air fan */
    EZB_ZCL_AO_PERCENTAGE_MIXED_AIR_DAMPER,           /*!< Mixed air damper */
    EZB_ZCL_AO_PERCENTAGE_MIXING_VALVE,               /*!< Mixing valve */
    EZB_ZCL_AO_PERCENTAGE_OUTSIDE_AIR_DAMPER,         /*!< Ourside air damper */
    EZB_ZCL_AO_PERCENTAGE_PRIMARY_CHILLED_WATER_PUMP, /*!< Primary chilled water pump */
    EZB_ZCL_AO_PERCENTAGE_PRIMARY_HOT_WATER_PUMP,     /*!< Primary hot water pump */
    EZB_ZCL_AO_PERCENTAGE_PRIMARY_HEAT_EXCHANGE_PUMP, /*!< Primary heat exchange pump */
    EZB_ZCL_AO_PERCENTAGE_PREHEAT_DAMPER,             /*!< Preheat damper */
    EZB_ZCL_AO_PERCENTAGE_PREHEAT_VALVE,              /*!< Preheat valve */
    EZB_ZCL_AO_PERCENTAGE_REHEAT_VALVE_0,             /*!< Reheat valve 0. Note: Reheat valve is duplicated in spec */

    EZB_ZCL_AO_PERCENTAGE_REHEAT_VALVE_1,               /*!< Reheat valve 1 */
    EZB_ZCL_AO_PERCENTAGE_RETURN_AIR_DAMPER,            /*!< Return air damper */
    EZB_ZCL_AO_PERCENTAGE_SECONDARY_CHILLED_WATER_PUMP, /*!< Secondary chilled water pump */
    EZB_ZCL_AO_PERCENTAGE_SEQUENCED_VALVE,              /*!< Sequenced valve */
    EZB_ZCL_AO_PERCENTAGE_SECONDARY_HOT_WATER_PUMP,     /*!< Secondary hot water pump */
    EZB_ZCL_AO_PERCENTAGE_SECONDARY_HEAT_EXCHANGE_PUMP, /*!< Secondary heat exchange pump */
    EZB_ZCL_AO_PERCENTAGE_SIDELOOP,                     /*!< Sideloop */
    EZB_ZCL_AO_PERCENTAGE_SUPPLY_HEATING_VALVE,         /*!< Supply heating valve */
    EZB_ZCL_AO_PERCENTAGE_SUPPLY_DAMPER,                /*!< Supply damper */
    EZB_ZCL_AO_PERCENTAGE_TOWER_BYPASS_VALVE,           /*!< Tower bypass valve */

    EZB_ZCL_AO_PERCENTAGE_TOWER_FAN,                               /*!< Tower fan */
    EZB_ZCL_AO_PERCENTAGE_VALVE,                                   /*!< Value */
    EZB_ZCL_AO_PERCENTAGE_ZONE_1_DAMPER,                           /*!< Zone 1 damper */
    EZB_ZCL_AO_PERCENTAGE_ZONE_1_HEATING_VALVE,                    /*!< Zone 1 heating valve */
    EZB_ZCL_AO_PERCENTAGE_HEAT_RECOVERY_EXHAUST_BYPASS_DAMPER,     /*!< Heat recovery exhaust bypass damper */
    EZB_ZCL_AO_PERCENTAGE_HEAT_RECOVERY_OUTSIDE_AIR_BYPASS_DAMPER, /*!< Heat recovery outside air bypass damper */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AO_PERCENTAGE_OTHER =
        EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_OUTPUT_APPLICATION_TYPE_PERCENTAGE, 0xFFFF), /*!< Other */
} ezb_zcl_ao_percentage_t;

/** @brief Values for 'Parts per Million PPM' type of Analog Output cluster */
typedef enum {
    EZB_ZCL_AO_PPM_SPACE_CARBON_DIOXIDE_LIMIT =
        EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_OUTPUT_APPLICATION_TYPE_PPM, 0x0000), /*!< Space carbon dioxide limit */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AO_PPM_OTHER = EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_OUTPUT_APPLICATION_TYPE_PPM, 0xFFFF), /*!< Other */
} ezb_zcl_ao_ppm_t;

/** @brief Values for 'Rotational Speed in RPM' type of Analog Output cluster */
typedef enum {
    EZB_ZCL_AO_RPM_EXHAUST_FAN_SPEED =
        EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_OUTPUT_APPLICATION_TYPE_RPM, 0x0000), /*!< Exhaust fan speed */
    EZB_ZCL_AO_RPM_FAN_SPEED,                                                                /*!< Fan speed */
    EZB_ZCL_AO_RPM_RELIEF_FAN_SPEED,                                                         /*!< Relief fan speed */
    EZB_ZCL_AO_RPM_RETURN_FAN_SPEED,                                                         /*!< Return fan speed */
    EZB_ZCL_AO_RPM_SUPPLY_FAN_SPEED,                                                         /*!< Supply fan speed */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AO_RPM_OTHER = EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_OUTPUT_APPLICATION_TYPE_RPM, 0xFFFF), /*!< Other */
} ezb_zcl_ao_rpm_t;

/** @brief Values for 'Time in Seconds' type of Analog Output cluster */
typedef enum {
    EZB_ZCL_AO_TIME_RELATIVE =
        EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_OUTPUT_APPLICATION_TYPE_TIME_IN_SECONDS, 0x0000), /*!< Relative */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AO_TIME_OTHER =
        EZB_ZCL_AO_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_OUTPUT_APPLICATION_TYPE_TIME_IN_SECONDS, 0xFFFF), /*!< Other */
} ezb_zcl_ao_time_t;

#ifdef __cplusplus
} /*  extern "C" */
#endif
