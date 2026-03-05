/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/binary_input_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Binary Input cluster application types
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
 * @brief Macros for Group ID of ZCL Binary Input
 */
#define EZB_ZCL_BI_GROUP_ID 0x03

/**
 * @brief Macros for ApplicationType attribute of ZCL Binary Input
 */
#define EZB_ZCL_BI_SET_APP_TYPE_WITH_ID(_type, _id) \
    (((EZB_ZCL_BI_GROUP_ID & 0xFF) << 24) | (((_type) & 0xFF) << 16) | ((_id) & 0xFFFF))

typedef enum {
    /*! 2 Pipe Pump Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_2_PIPE_PUMP_STATUS =
        EZB_ZCL_BI_SET_APP_TYPE_WITH_ID(EZB_ZCL_BINARY_INPUT_APPLICATION_TYPE_APP_DOMAIN_HVAC, 0x0000),
    EZB_ZCL_BI_DOMAIN_HVAC_AIR_PROVING_SWITCH,                             /*!< Air Proving Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_ALARM_RESET,                                    /*!< Alarm Reset BI */
    EZB_ZCL_BI_DOMAIN_HVAC_BOILER_STATUS,                                  /*!< Boiler Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_BOILER_FLOW_STATUS,                             /*!< Boiler Flow Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_BOILER_GENERAL_ALARM,                           /*!< Boiler General Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_BOILER_HIGH_TEMPERATURE_ALARM,                  /*!< Boiler High Temperature Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_BOILER_ISOLATION_VALVE_STATUS,                  /*!< Boiler Isolation Valve Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_BOILER_MAINTENANCE_SWITCH,                      /*!< Boiler Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_BOILER_PUMP_OVERLOAD,                           /*!< Boiler Pump Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_BOILER_PUMP_STATUS,                             /*!< Boiler Pump Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_BOILER_STATUS_2,                                /*!< Boiler Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_BOX_HEATING_ALARM,                              /*!< Box Heating Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CHILLER_ALARM,                                  /*!< Chiller Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CHILLER_CHILLED_WATER_FLOW_STATUS,              /*!< Chiller Chilled Water Flow Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CHILLER_CHILLED_WATER_ISOLATION_VALVE_STATUS,   /*!< Chiller Chilled Water Isolation Valve Status BI
                                                                            */
    EZB_ZCL_BI_DOMAIN_HVAC_CHILLER_CONDENSER_WATER_FLOW_STATUS,            /*!< Chiller Condenser Water Flow Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CHILLER_CONDENSER_WATER_ISOLATION_VALVE_STATUS, /*!< Chiller Condenser Water Isolation Valve
                                                                           Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CHILLER_MAINTENANCE_SWITCH,                     /*!< Chiller Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CHILLER_STATUS,                                 /*!< Chiller Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CHILLED_WATER_EXPANSION_TANK_ALARM,             /*!< Chilled Water Expansion Tank Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CHILLED_WATER_EXPANSION_TANK_HIGH_PRESSURE_ALARM,   /*!< Chilled Water Expansion Tank High Pressure
                                                                               Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CHILLED_WATER_EXPANSION_TANK_LOW_PRESSURE_ALARM,    /*!< Chilled Water Expansion Tank Low Pressure
                                                                               Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CHILLED_WATER_EXPANSION_TANK_STATUS,                /*!< Chilled Water Expansion Tank Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_COMBUSTION_DAMPER_STATUS,                           /*!< Combustion Damper Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_COOLING_ALARM,                                      /*!< Cooling Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_COOLING_PUMP_MAINTENANCE_SWITCH,                    /*!< Cooling Pump Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_COOLING_PUMP_OVERLOAD,                              /*!< Cooling Pump Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_COOLING_PUMP_STATUS,                                /*!< Cooling Pump Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_EXPANSION_TANK_ALARM,               /*!< Condenser Water Expansion Tank Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_EXPANSION_TANK_HIGH_PRESSURE_ALARM, /*!< Condenser Water Expansion Tank High
                                                                               Pressure Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_EXPANSION_TANK_LOW_PRESSURE_ALARM,  /*!< Condenser Water Expansion Tank Low
                                                                               Pressure Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_EXPANSION_TANK_STATUS,              /*!< Condenser Water Expansion Tank Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_PUMP_MAINTENANCE_SWITCH,    /*!< Condenser Water Pump Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_PUMP_OVERLOAD,              /*!< Condenser Water Pump Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_PUMP_STATUS,                /*!< Condenser Water Pump Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_DECOUPLE_LOOP_FLOW_DIRECTION,               /*!< Decouple Loop Flow Direction BI */
    EZB_ZCL_BI_DOMAIN_HVAC_DISCHARGE_SMOKE,                            /*!< Discharge Smoke BI */
    EZB_ZCL_BI_DOMAIN_HVAC_DOOR_STATUS,                                /*!< Door Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_ECONOMIZER_COMMAND,                         /*!< Economizer Command BI */
    EZB_ZCL_BI_DOMAIN_HVAC_EMERGENCY_SHUTDOWN,                         /*!< Emergency Shutdown BI */
    EZB_ZCL_BI_DOMAIN_HVAC_EQUIPMENT_TAMPER,                           /*!< Equipment Tamper BI */
    EZB_ZCL_BI_DOMAIN_HVAC_ENERGY_HOLD_OFF,                            /*!< Energy Hold Off BI */
    EZB_ZCL_BI_DOMAIN_HVAC_EXHAUST_FAN_MAINTENANCE_SWITCH,             /*!< Exhaust Fan Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_EXHAUST_FAN_OVERLOAD,                       /*!< Exhaust Fan Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_EXHAUST_FAN_STATUS,                         /*!< Exhaust Fan Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_EXHAUST_FILTER_STATUS,                      /*!< Exhaust Filter Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_EXHAUST_SMOKE,                              /*!< Exhaust Smoke BI */
    EZB_ZCL_BI_DOMAIN_HVAC_EXPANSION_TANK_ALARM,                       /*!< Expansion Tank Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_EXPANSION_TANK_HIGH_PRESSURE_ALARM,         /*!< Expansion Tank High Pressure Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_EXPANSION_TANK_LOW_PRESSURE_ALARM,          /*!< Expansion Tank Low Pressure Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_EXPANSION_TANK_STATUS,                      /*!< Expansion Tank Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_FAN_CONTROL_BY_OTHERS,                      /*!< Fan Control By Others BI */
    EZB_ZCL_BI_DOMAIN_HVAC_FAN_OVERLOAD,                               /*!< Fan Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_FILTER_MONITORING,                          /*!< Filter Monitoring BI */
    EZB_ZCL_BI_DOMAIN_HVAC_FINAL_FILTER_STATUS,                        /*!< Final Filter Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_FREE_COOLING_AVAILABILITY,                  /*!< Free Cooling Availability BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HEAT_RECOVERY_PUMP_STATUS,                  /*!< Heat Recovery Pump Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HEAT_RECOVERY_WHEEL_ALARM,                  /*!< Heat Recovery Wheel Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HEAT_RECOVERY_WHEEL_MAINTENANCE_SWITCH,     /*!< Heat Recovery Wheel Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HEAT_RECOVERY_WHEEL_OVERLOAD,               /*!< Heat Recovery Wheel Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HEAT_RECOVERY_WHEEL_STATUS,                 /*!< Heat Recovery Wheel Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HEATING_ALARM,                              /*!< Heating Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HEATING_COOLING_PUMP_MAINTENANCE_SWITCH,    /*!< Heating/Cooling Pump Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HEATING_COOLING_PUMP_OVERLOAD,              /*!< Heating/Cooling Pump Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HIGH_HUMIDITY_LIMIT,                        /*!< High Humidity Limit BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HIGH_STATIC_PRESSURE_FAULT,                 /*!< High Static Pressure Fault BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HIGH_TEMPERATURE_LIMIT_FAULT,               /*!< High Temperature Limit Fault BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HUMIDIFIER_ALARM,                           /*!< Humidifier Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HUMIDIFIER_MAINTENANCE_SWITCH,              /*!< Humidifier Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HUMIDIFIER_OVERLOAD,                        /*!< Humidifier Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HUMIDIFIER_STATUS,                          /*!< Humidifier Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HEAT_EXCHANGER_ALARM,                       /*!< Heat Exchanger Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HEAT_EXCHANGER_ISOLATION_VALVE_STATUS,      /*!< Heat Exchanger Isolation Valve Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_HEAT_EXCHANGER_MAINTENANCE_SWITCH,          /*!< Heat Exchanger Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_LIGHTING_STATUS,                            /*!< Lighting Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_LOW_STATIC_PRESSURE_FAULT,                  /*!< Low Static Pressure Fault BI */
    EZB_ZCL_BI_DOMAIN_HVAC_LOW_TEMPERATURE_LIMIT_FAULT,                /*!< Low Temperature Limit Fault BI */
    EZB_ZCL_BI_DOMAIN_HVAC_MINIMUM_OUTDOOR_AIR_DAMPER_END_SWITCH,      /*!< Minimum Outdoor Air Damper End Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_MINIMUM_OUTDOOR_AIR_FAN_MAINTENANCE_SWITCH, /*!< Minimum Outdoor Air Fan Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_MINIMUM_OUTDOOR_AIR_FAN_OVERLOAD,           /*!< Minimum Outdoor Air Fan Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_MINIMUM_OUTDOOR_AIR_FAN_STATUS,             /*!< Minimum Outdoor Air Fan Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_MINIMUM_OUTDOOR_AIR_FAN_VARIABLE_FREQUENCY_DRIVE_FAULT, /*!< Minimum Outdoor Air Fan Variable
                                                                                   Frequency Drive Fault BI */
    EZB_ZCL_BI_DOMAIN_HVAC_OCCUPANCY,                                              /*!< Occupancy BI */
    EZB_ZCL_BI_DOMAIN_HVAC_OCCUPANCY_SENSOR,                                       /*!< Occupancy Sensor BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_MAINTENANCE_SWITCH,   /*!< Primary Chilled Water Pump Maintenance Switch
                                                                            BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_OVERLOAD,             /*!< Primary Chilled Water Pump Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_STATUS,               /*!< Primary Chilled Water Pump Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_MAINTENANCE_SWITCH_2, /*!< Primary Chilled Water Pump Maintenance
                                                                            Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_OVERLOAD_2,           /*!< Primary Chilled Water Pump Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_STATUS_2,             /*!< Primary Chilled Water Pump Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PRE_FILTER_STATUS,                               /*!< Pre-Filter Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PREHEAT_ALARM,                                   /*!< Preheat Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PREHEAT_BONNET_SWITCH,                           /*!< Preheat Bonnet Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PREHEAT_PUMP_MAINTENANCE_SWITCH,                 /*!< Preheat Pump Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PREHEAT_PUMP_OVERLOAD,                           /*!< Preheat Pump Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PREHEAT_PUMP_STATUS,                             /*!< Preheat Pump Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_REFRIGERANT_ALARM,                               /*!< Refrigerant Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_REHEAT_ALARM,                                    /*!< Reheat Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_REHEAT_BONNET_SWITCH,                            /*!< Reheat Bonnet Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_REHEAT_PUMP_MAINTENANCE_SWITCH,                  /*!< Reheat Pump Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_REHEAT_PUMP_OVERLOAD,                            /*!< Reheat Pump Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_REHEAT_PUMP_STATUS,                              /*!< Reheat Pump Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_RELIEF_FAN_MAINTENANCE_SWITCH,                   /*!< Relief Fan Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_RELIEF_FAN_OVERLOAD,                             /*!< Relief Fan Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_RELIEF_FAN_STATUS,                               /*!< Relief Fan Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_RELIEF_FAN_VARIABLE_FREQUENCY_DRIVE_FAULT,       /*!< Relief Fan Variable Frequency Drive Fault BI */
    EZB_ZCL_BI_DOMAIN_HVAC_RETURN_AIR_SMOKE,                                /*!< Return Air Smoke BI */
    EZB_ZCL_BI_DOMAIN_HVAC_RETURN_FAN_MAINTENANCE_SWITCH,                   /*!< Return Fan Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_RETURN_FAN_OVERLOAD,                             /*!< Return Fan Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_RETURN_FAN_STATUS,                               /*!< Return Fan Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_RETURN_FAN_VFD_FAULT,                            /*!< Return Fan VFD Fault BI */
    EZB_ZCL_BI_DOMAIN_HVAC_RETURN_SMOKE,                                    /*!< Return Smoke BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP_1_MAINTENANCE_SWITCH, /*!< Secondary Chilled Water Pump 1 Maintenance
                                                                              Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP_1_OVERLOAD,           /*!< Secondary Chilled Water Pump 1 Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP_1_STATUS,             /*!< Secondary Chilled Water Pump 1 Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP_1_MAINTENANCE_SWITCH_2, /*!< Secondary Chilled Water Pump 1
                                                                                Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP_1_OVERLOAD_2,    /*!< Secondary Chilled Water Pump 1 Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP_1_STATUS_2,      /*!< Secondary Chilled Water Pump 1 Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SIDELOOP,                                     /*!< Sideloop BI */
    EZB_ZCL_BI_DOMAIN_HVAC_GENERIC_STATUS,                               /*!< Generic Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SUMMER_WINTER,                                /*!< Summer Winter BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_ALARM,                   /*!< Supplemental Heating Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_PUMP_MAINTENANCE_SWITCH, /*!< Supplemental Heating Pump Maintenance Switch BI
                                                                          */
    EZB_ZCL_BI_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_PUMP_OVERLOAD,           /*!< Supplemental Heating Pump Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_PUMP_STATUS,             /*!< Supplemental Heating Pump Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SUPPLY_FAN_MAINTENANCE_SWITCH,                /*!< Supply Fan Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SUPPLY_FAN_OVERLOAD,                          /*!< Supply Fan Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SUPPLY_FAN_STATUS,                            /*!< Supply Fan Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_SUPPLY_FAN_VARIABLE_FREQUENCY_DRIVE_FAULT,    /*!< Supply Fan Variable Frequency Drive Fault BI */
    EZB_ZCL_BI_DOMAIN_HVAC_TEMPORARY_OCCUPANCY,                          /*!< Temporary Occupancy BI */
    EZB_ZCL_BI_DOMAIN_HVAC_TOWER_LEVEL_ALARM,                            /*!< Tower Level Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_TOWER_LEVEL_STATUS,                           /*!< Tower Level Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_TOWER_TEMP,                                   /*!< Tower Temp BI */
    EZB_ZCL_BI_DOMAIN_HVAC_TOWER_VIBRATION_ALARM_STATUS,                 /*!< Tower Vibration Alarm Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_TOWER_LEVEL_ALARM_2,                          /*!< Tower Level Alarm BI */
    EZB_ZCL_BI_DOMAIN_HVAC_TOWER_LEVEL_SWITCH,                           /*!< Tower Level Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_TOWER_TEMP_SWITCH,                            /*!< Tower Temp Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_TOWER_FAN_ISOLATION_VALVE_STATUS,             /*!< Tower Fan Isolation Valve Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_TOWER_FAN_MAINTENANCE_SWITCH,                 /*!< Tower Fan Maintenance Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_TOWER_FAN_OVERLOAD,                           /*!< Tower Fan Overload BI */
    EZB_ZCL_BI_DOMAIN_HVAC_TOWER_FAN_STATUS,                             /*!< Tower Fan Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_UNIT_ENABLE,                                  /*!< Unit Enable BI */
    EZB_ZCL_BI_DOMAIN_HVAC_UNIT_RESET,                                   /*!< Unit Reset BI */
    EZB_ZCL_BI_DOMAIN_HVAC_WINDOW_STATUS,                                /*!< Window Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_ZONE_SENSOR_TEMPORARY_OCCUPANCY,              /*!< Zone Sensor Temporary Occupancy BI */
    EZB_ZCL_BI_DOMAIN_HVAC_AIR_PROVING_SWITCH_2,                         /*!< Air Proving Switch BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_HEATING_STATUS,                       /*!< Primary Heating Status BI */
    EZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_COOLING_STATUS,                       /*!< Primary Cooling Status BI */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_BI_DOMAIN_HVAC_OTHER =
        EZB_ZCL_BI_SET_APP_TYPE_WITH_ID(EZB_ZCL_BINARY_INPUT_APPLICATION_TYPE_APP_DOMAIN_HVAC, 0xFFFF) /*!< Other */
} ezb_zb_zcl_bi_domain_hvac_t;

typedef enum {
    /*! Glass Breakage Detection */
    EZB_ZCL_BI_DOMAIN_SECURITY_GLASS_BREAKAGE_DETECTION_0 =
        EZB_ZCL_BI_SET_APP_TYPE_WITH_ID(EZB_ZCL_BINARY_INPUT_APPLICATION_TYPE_APP_DOMAIN_SECURITY, 0x0000),
    EZB_ZCL_BI_DOMAIN_SECURITY_INTRUSION_DETECTION,        /*!< Intrusion Detection */
    EZB_ZCL_BI_DOMAIN_SECURITY_MOTION_DETECTION,           /*!< Motion Detection */
    EZB_ZCL_BI_DOMAIN_SECURITY_GLASS_BREAKAGE_DETECTION_1, /*!< Glass Breakage Detection */
    EZB_ZCL_BI_DOMAIN_SECURITY_ZONE_ARMED,                 /*!< Zone Armed */
    EZB_ZCL_BI_DOMAIN_SECURITY_GLASS_BREAKAGE_DETECTION_2, /*!< Glass Breakage Detection */
    EZB_ZCL_BI_DOMAIN_SECURITY_SMOKE_DETECTION,            /*!< Smoke Detection */
    EZB_ZCL_BI_DOMAIN_SECURITY_CARBON_DIOXIDE_DETECTION,   /*!< Carbon Dioxide Detection */
    EZB_ZCL_BI_DOMAIN_SECURITY_HEAT_DETECTION,             /*!< Heat Detection */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_BI_DOMAIN_SECURITY_OTHER =
        EZB_ZCL_BI_SET_APP_TYPE_WITH_ID(EZB_ZCL_BINARY_INPUT_APPLICATION_TYPE_APP_DOMAIN_SECURITY, 0xFFFF) /*!< Other */
} ezb_zcl_bi_domain_security_t;

#ifdef __cplusplus
} /*  extern "C" */
#endif
