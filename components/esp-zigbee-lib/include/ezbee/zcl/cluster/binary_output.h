/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/binary_output_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Binary Output cluster application types
 *      The ApplicationType attribute indicates the specific application usage
 *      for the cluster. ApplicationType is subdivided into Group, Type and
 *      an Index number, as follows:
 *
 *      Group = Bits 24 to 31
 *        An indication of the cluster this attribute is part of. Binary Input
 *        clusters have Group = 0x00.
 *
 *      Type = Bits 16 to 23
 *        The physical quantity that the PresentValue attribute of the cluster
 *        represents.
 *
 *      Index = Bits 0 to 15
 *        The specific application usage of the cluster.
 */

/**
 * @brief Macros for Group ID of ZCL Binary Output
 */
#define EZB_ZCL_BO_GROUP_ID 0x04

/**
 * @brief Macros for ApplicationType attribute of ZCL Binary Output
 */
#define EZB_ZCL_BO_SET_APP_TYPE_WITH_ID(_type, _id) \
    (((EZB_ZCL_BO_GROUP_ID & 0xFF) << 24) | (((_type) & 0xFF) << 16) | ((_id) & 0xFFFF))

/** @brief Values for Binary Output cluster HVAC application usages */
typedef enum {
    /*! 2 Pipe Circulation Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_2_PIPE_CIRCULATION_PUMP_STATUS =
        EZB_ZCL_BO_SET_APP_TYPE_WITH_ID(EZB_ZCL_BINARY_OUTPUT_APPLICATION_TYPE_APP_DOMAIN_HVAC, 0x0000),
    EZB_ZCL_BO_DOMAIN_HVAC_2_PIPE_VALVE,                                   /*!< 2 Pipe Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_2_PIPE_VALVE_COMMAND,                           /*!< 2 Pipe Valve Command BO */
    EZB_ZCL_BO_DOMAIN_HVAC_BOILER,                                         /*!< Boiler BO */
    EZB_ZCL_BO_DOMAIN_HVAC_BOILER_ISOLATION_VALVE,                         /*!< Boiler Isolation Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_BOILER_PUMP,                                    /*!< Boiler Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_BOX_COOLING_2_POSITION,                         /*!< Box Cooling 2 Position BO */
    EZB_ZCL_BO_DOMAIN_HVAC_BOX_HEATING_2_POSITION,                         /*!< Box Heating 2 Position BO */
    EZB_ZCL_BO_DOMAIN_HVAC_BOX_HEATING_ENABLE,                             /*!< Box Heating Enable BO */
    EZB_ZCL_BO_DOMAIN_HVAC_BOX_HEATING_STAGE_1,                            /*!< Box Heating Stage 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_BOX_HEATING_STAGE_2,                            /*!< Box Heating Stage 2 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_BOX_HEATING_STAGE_3,                            /*!< Box Heating Stage 3 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_CHILLER_1_ISOLATION_VALVE,                      /*!< Chiller 1 Isolation Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_CHILLER,                                        /*!< Chiller BO */
    EZB_ZCL_BO_DOMAIN_HVAC_CHILLER_CHILLED_WATER_ISOLATION_VALVE,          /*!< Chiller Chilled Water Isolation Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_CHILLER_CONDENSER_WATER_ISOLATION_VALVE,        /*!< Chiller Condenser Water Isolation Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COMBUSTION_DAMPER,                              /*!< Combustion Damper BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COMPRESSOR_STAGE_1,                             /*!< Compressor Stage 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COMPRESSOR_STAGE_2,                             /*!< Compressor Stage 2 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COOLING_CIRCULATION_PUMP,                       /*!< Cooling Circulation Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_1,                                /*!< Cooling Stage 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_2,                                /*!< Cooling Stage 2 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_3,                                /*!< Cooling Stage 3 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_4,                                /*!< Cooling Stage 4 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_5,                                /*!< Cooling Stage 5 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_6,                                /*!< Cooling Stage 6 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_7,                                /*!< Cooling Stage 7 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_8,                                /*!< Cooling Stage 8 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COOLING_VALVE,                                  /*!< Cooling Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_COOLING_VALVE_COMMAND,                          /*!< Cooling Valve Command BO */
    EZB_ZCL_BO_DOMAIN_HVAC_CHILLED_WATER_PUMP,                             /*!< Chilled Water Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_ECONOMIZER_ENABLE,                              /*!< Economizer Enable BO */
    EZB_ZCL_BO_DOMAIN_HVAC_EXHAUST_AIR_DAMPER,                             /*!< Exhaust Air Damper BO */
    EZB_ZCL_BO_DOMAIN_HVAC_EXHAUST_FAN,                                    /*!< Exhaust Fan BO */
    EZB_ZCL_BO_DOMAIN_HVAC_FAN,                                            /*!< Fan BO */
    EZB_ZCL_BO_DOMAIN_HVAC_FAN_SPEED_1,                                    /*!< Fan Speed 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_FAN_SPEED_2,                                    /*!< Fan Speed 2 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_FAN_SPEED_3,                                    /*!< Fan Speed 3 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HEAT_RECOVERY_PUMP,                             /*!< Heat Recovery Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HEAT_RECOVERY_VALVE,                            /*!< Heat Recovery Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HEAT_RECOVERY_WHEEL,                            /*!< Heat Recovery Wheel BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HEATING_STAGE_1,                                /*!< Heating Stage 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HEATING_STAGE_2,                                /*!< Heating Stage 2 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HEATING_STAGE_3,                                /*!< Heating Stage 3 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HEATING_VALVE,                                  /*!< Heating Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HEATING_VALVE_COMMAND,                          /*!< Heating Valve Command BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HOT_GAS_BYPASS_VALVE,                           /*!< Hot Gas Bypass Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HUMIDIFICATION_STAGE_1,                         /*!< Humidification Stage 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HUMIDIFICATION_STAGE_2,                         /*!< Humidification Stage 2 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HUMIDIFICATION_STAGE_3,                         /*!< Humidification Stage 3 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HUMIDIFICATION_STAGE_4,                         /*!< Humidification Stage 4 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HUMIDIFIER_ENABLE,                              /*!< Humidifier Enable BO */
    EZB_ZCL_BO_DOMAIN_HVAC_HEAT_EXCHANGER_ISOLATION_VALVE,                 /*!< Heat Exchanger Isolation Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_LIGHTING,                                       /*!< Lighting BO */
    EZB_ZCL_BO_DOMAIN_HVAC_MINIMUM_OUTSIDE_AIR_DAMPER,                     /*!< Minimum Outside Air Damper BO */
    EZB_ZCL_BO_DOMAIN_HVAC_MINIMUM_OUTSIDE_AIR_FAN,                        /*!< Minimum Outside Air Fan BO */
    EZB_ZCL_BO_DOMAIN_HVAC_OUTSIDE_AIR_DAMPER,                             /*!< Outside Air Damper BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_1,                   /*!< Primary Chilled Water Pump 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PLATE_AND_FRAME_HEAT_EXCHANGER_ISOLATION_VALVE, /*!< Plate-and-Frame Heat Exchanger Isolation
                                                                           Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PRIMARY_HOT_WATER_PUMP,                         /*!< Primary Hot Water Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PRIMARY_HEAT_EXCHANGE_PUMP,                     /*!< Primary Heat Exchange Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_CIRCULATION_PUMP,                       /*!< Preheat Circulation Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_ENABLE,                                 /*!< Preheat Enable BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_1,                                /*!< Preheat Stage 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_2,                                /*!< Preheat Stage 2 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_3,                                /*!< Preheat Stage 3 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_4,                                /*!< Preheat Stage 4 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_5,                                /*!< Preheat Stage 5 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_6,                                /*!< Preheat Stage 6 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_7,                                /*!< Preheat Stage 7 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_8,                                /*!< Preheat Stage 8 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_VALVE,                                  /*!< Preheat Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_REHEAT_CIRCULATION_PUMP,                        /*!< Reheat Circulation Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_REHEAT_ENABLE,                                  /*!< Reheat Enable BO */
    EZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_1,                                 /*!< Reheat Stage 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_2,                                 /*!< Reheat Stage 2 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_3,                                 /*!< Reheat Stage 3 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_4,                                 /*!< Reheat Stage 4 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_5,                                 /*!< Reheat Stage 5 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_6,                                 /*!< Reheat Stage 6 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_7,                                 /*!< Reheat Stage 7 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_8,                                 /*!< Reheat Stage 8 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_RELIEF_FAN,                                     /*!< Relief Fan BO */
    EZB_ZCL_BO_DOMAIN_HVAC_RETURN_FAN,                                     /*!< Return Fan BO */
    EZB_ZCL_BO_DOMAIN_HVAC_REVERSING_VALVE_1,                              /*!< Reversing Valve 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_REVERSING_VALVE_2,                              /*!< Reversing Valve 2 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP,                   /*!< Secondary Chilled Water Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SECONDARY_HOT_WATER_PUMP,                       /*!< Secondary Hot Water Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SECONDARY_HEAT_EXCHANGE_PUMP,                   /*!< Secondary Heat Exchange Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP,                                       /*!< Sideloop BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_1,                               /*!< Sideloop Stage 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_2,                               /*!< Sideloop Stage 2 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_3,                               /*!< Sideloop Stage 3 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_4,                               /*!< Sideloop Stage 4 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_5,                               /*!< Sideloop Stage 5 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_6,                               /*!< Sideloop Stage 6 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_7,                               /*!< Sideloop Stage 7 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_8,                               /*!< Sideloop Stage 8 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_STEAM_ISOLATION_VALVE,                          /*!< Steam Isolation Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_2_POSITION,                /*!< Supplemental Heating 2 Position BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_STAGE_1,                   /*!< Supplemental Heating Stage 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_VALVE,                     /*!< Supplemental Heating Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_ENABLE,                    /*!< Supplemental Heating Enable BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_PUMP,                      /*!< Supplemental Heating Pump BO */
    EZB_ZCL_BO_DOMAIN_HVAC_SUPPLY_FAN,                                     /*!< Supply Fan BO */
    EZB_ZCL_BO_DOMAIN_HVAC_TOWER_BASIN_HEATER_1,                           /*!< Tower Basin Heater BO */
    EZB_ZCL_BO_DOMAIN_HVAC_TOWER_BASIN_MAKEUP_1,                           /*!< Tower Basin Makeup BO */
    EZB_ZCL_BO_DOMAIN_HVAC_TOWER_BASIN_HEATER_2,                           /*!< Tower Basin Heater BO */
    EZB_ZCL_BO_DOMAIN_HVAC_TOWER_BASIN_MAKEUP_2,                           /*!< Tower Basin Makeup BO */
    EZB_ZCL_BO_DOMAIN_HVAC_TOWER_ISOLATION_VALVE,                          /*!< Tower Isolation Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_TOWER_FAN,                                      /*!< Tower Fan BO */
    EZB_ZCL_BO_DOMAIN_HVAC_TOWER_FAN_SPEED_1,                              /*!< Tower Fan Speed 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_TOWER_FAN_SPEED_2,                              /*!< Tower Fan Speed 2 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_TOWER_FAN_SPEED_3,                              /*!< Tower Fan Speed 3 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_ZONE_HEATING_STAGE_1,                           /*!< Zone Heating Stage 1 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_ZONE_HEATING_STAGE_2,                           /*!< Zone Heating Stage 2 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_ZONE_HEATING_STAGE_3,                           /*!< Zone Heating Stage 3 BO */
    EZB_ZCL_BO_DOMAIN_HVAC_ZONE_HEATING_VALVE,                             /*!< Zone Heating Valve BO */
    EZB_ZCL_BO_DOMAIN_HVAC_2_PIPE_CIRCULATION_PUMP_2,                      /*!< 2 Pipe Circulation Pump BO */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_BO_DOMAIN_HVAC_OTHER =
        EZB_ZCL_BO_SET_APP_TYPE_WITH_ID(EZB_ZCL_BINARY_OUTPUT_APPLICATION_TYPE_APP_DOMAIN_HVAC, 0xFFFF) /*!< Other */
} ezb_zb_zcl_bo_domain_hvac_t;

/** @brief Values for Binary Output cluster Security application usages */
typedef enum {
    /*! Arm Disarm Command BO */
    EZB_ZCL_BO_DOMAIN_SECURITY_ARM_DISARM_COMMAND =
        EZB_ZCL_BO_SET_APP_TYPE_WITH_ID(EZB_ZCL_BINARY_OUTPUT_APPLICATION_TYPE_APP_DOMAIN_SECURITY, 0x0000),
    EZB_ZCL_BO_DOMAIN_SECURITY_OCCUPANCY_CONTROL, /*!< Occupancy Control BO */
    EZB_ZCL_BO_DOMAIN_SECURITY_ENABLE_CONTROL,    /*!< Enable Control BO */
    EZB_ZCL_BO_DOMAIN_SECURITY_ACCESS_CONTROL,    /*!< Access Control BO */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_BO_DOMAIN_SECURITY_OTHER =
        EZB_ZCL_BO_SET_APP_TYPE_WITH_ID(EZB_ZCL_BINARY_OUTPUT_APPLICATION_TYPE_APP_DOMAIN_SECURITY, 0xFFFF) /*!< Other */
} ezb_zcl_bo_domain_security_t;

#ifdef __cplusplus
} /*  extern "C" */
#endif
