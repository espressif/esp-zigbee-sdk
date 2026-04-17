/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/analog_value_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Analog Value cluster application types
 *      The ApplicationType attribute indicates the specific application usage
 *      for the cluster. ApplicationType is subdivided into Group, Type and
 *      an Index number, as follows:
 *
 *      Group = Bits 24 to 31
 *        An indication of the cluster this attribute is part of. Analog Value
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
 * @brief Macros for Group ID of ZCL Analog Value
 */
#define EZB_ZCL_AV_GROUP_ID 0x02

/**
 * @brief Macros for ApplicationType attribute of ZCL Analog Value
 */
#define EZB_ZCL_AV_SET_APP_TYPE_WITH_ID(_type, _id) ((EZB_ZCL_AV_GROUP_ID << 24) | ((_type & 0xff) << 16) | (_id & 0xFFFF))

/** @brief Values for 'Temperature in degrees Celsius' type of Analog Value cluster */
typedef enum {
    EZB_ZCL_AV_TEMPERATURE_SETPOINT_OFFSET_0 =
        EZB_ZCL_AV_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_VALUE_APPLICATION_TYPE_TEMPERATURE, 0x0000), /*!< Setpoint Offset */
    EZB_ZCL_AV_TEMPERATURE_TEMP_DEADBAND,                                                           /*!< Temp deadband */
    EZB_ZCL_AV_TEMPERATURE_OCCUPIED_HEATING_SETPOINT,             /*!< Occupied heating setpoint */
    EZB_ZCL_AV_TEMPERATURE_UNOCCUPIED_HEATING_SETPOINT,           /*!< Unoccupied heating setpoint */
    EZB_ZCL_AV_TEMPERATURE_OCCUPIED_COOLING_SETPOINT,             /*!< Occupied cooling setpoint */
    EZB_ZCL_AV_TEMPERATURE_UNOCCUPIED_COOLING_SETPOINT,           /*!< Unoccupied cooling setpoint */
    EZB_ZCL_AV_TEMPERATURE_STANDBY_HEAT_SETPOINT,                 /*!< Standby heat setpoint */
    EZB_ZCL_AV_TEMPERATURE_STANDBY_COOLING_SETPOINT,              /*!< Standby cooling setpoint */
    EZB_ZCL_AV_TEMPERATURE_EFFECTIVE_OCCUPIED_HEATING_SETPOINT,   /*!< Effective occupied heating setpoint */
    EZB_ZCL_AV_TEMPERATURE_EFFECTIVE_UNOCCUPIED_HEATING_SETPOINT, /*!< Effective unoccupied heating setpoint */
    EZB_ZCL_AV_TEMPERATURE_EFFECTIVE_OCCUPIED_COOLING_SETPOINT,   /*!< Effective occupied cooling setpoint */
    EZB_ZCL_AV_TEMPERATURE_EFFECTIVE_UNOCCUPIED_COOLING_SETPOINT, /*!< Effective unoccupied cooling setpoint */
    EZB_ZCL_AV_TEMPERATURE_EFFECTIVE_STANDBY_HEAT_SETPOINT,       /*!< Effective standby heat setpoint */
    EZB_ZCL_AV_TEMPERATURE_EFFECTIVE_STANDBY_COOLING_SETPOINT,    /*!< Effective standby cooling setpoint */
    EZB_ZCL_AV_TEMPERATURE_SETPOINT_OFFSET_2,                     /*!< Setpoint offset 2 */
    EZB_ZCL_AV_TEMPERATURE_SETPOINT_SHIFT,                        /*!< Setpoint shift */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AV_TEMPERATURE_OTHER =
        EZB_ZCL_AV_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_VALUE_APPLICATION_TYPE_TEMPERATURE, 0xFFFF), /*!< Other*/
} ezb_zcl_av_temperature_in_degrees_celsius_t;

/** @brief Values for 'Area in Square Metres' type of Analog Value cluster */
typedef enum {
    EZB_ZCL_AV_AREA_DUCT_AREA =
        EZB_ZCL_AV_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_VALUE_APPLICATION_TYPE_AREA_IN_SQUARE_METERS, 0x0000), /*!< Duct Area */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AV_AREA_OTHER =
        EZB_ZCL_AV_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_VALUE_APPLICATION_TYPE_AREA_IN_SQUARE_METERS, 0xFFFF), /*!< Other */
} ezb_zcl_av_area_in_squares_meters_t;

/** @brief Values for 'Multiplier - Number' type of Analog Value cluster */
typedef enum {
    EZB_ZCL_AV_MULTIPLIER_DUCT_MULTIPLIER =
        EZB_ZCL_AV_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_VALUE_APPLICATION_TYPE_MULTIPLIER_NUMBER, 0x0000), /*!< Duct Area */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AV_MULTIPLIER_OTHER =
        EZB_ZCL_AV_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_VALUE_APPLICATION_TYPE_MULTIPLIER_NUMBER, 0xFFFF), /*!< Other */
} ezb_zcl_av_multiplier_number_t;

/** @brief Values for 'Flow in Litres per Second' type of Analog Value cluster */
typedef enum {
    EZB_ZCL_AV_FLOW_MINIMUM_AIR_FLOW =
        EZB_ZCL_AV_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_VALUE_APPLICATION_TYPE_FLOW, 0x0000), /*!< Minimum Air Flow */
    EZB_ZCL_AV_FLOW_MAXIMUM_AIR_FLOW,                                                        /*!< Maximum Air Flow */
    EZB_ZCL_AV_FLOW_HEATING_MINIMUM_AIR_FLOW,                                                /*!< Heating Minimum Air Flow */
    EZB_ZCL_AV_FLOW_HEATING_MAXIMUM_AIR_FLOW,                                                /*!< Heating Maximum Air Flow */
    EZB_ZCL_AV_FLOW_STANDBY_MINIMUM_AIR_FLOW,                                                /*!< Standby Minimum Air Flow */
    EZB_ZCL_AV_FLOW_STANDBY_MAXIMUM_AIR_FLOW,                                                /*!< Standby Maximum Air Flow */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_AV_FLOW_OTHER = EZB_ZCL_AV_SET_APP_TYPE_WITH_ID(EZB_ZCL_ANALOG_VALUE_APPLICATION_TYPE_FLOW, 0xFFFF), /*!< Other */
} ezb_zcl_av_flow_in_liters_per_second_t;

#ifdef __cplusplus
} /*  extern "C" */
#endif
