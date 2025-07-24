/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_type.h"

/** @brief Binary Input cluster attribute identifiers.
*/
typedef enum {

    ESP_ZB_ZCL_ATTR_BINARY_INPUT_ACTIVE_TEXT_ID               = 0x0004,    /*!< This attribute holds a human readable description of the ACTIVE state of a binary PresentValue. */
    ESP_ZB_ZCL_ATTR_BINARY_INPUT_DESCRIPTION_ID               = 0x001C,    /*!< The description of the usage of the input, output or value, as appropriate to the cluster. */
    ESP_ZB_ZCL_ATTR_BINARY_INPUT_INACTIVE_TEXT_ID             = 0x002E,    /*!< This attribute holds a human readable description of the INACTIVE state of a binary PresentValue. */
    ESP_ZB_ZCL_ATTR_BINARY_INPUT_OUT_OF_SERVICE_ID            = 0x0051,    /*!< OutOfService attribute */
    ESP_ZB_ZCL_ATTR_BINARY_INPUT_POLARITY_ID                  = 0x0054,    /*!< This attribute indicates the relationship between the physical state of the input (or output as appropriate for the cluster) and the logical state represented by a binary PresentValue attribute, when OutOfService is FALSE. */
    ESP_ZB_ZCL_ATTR_BINARY_INPUT_PRESENT_VALUE_ID             = 0x0055,    /*!< PresentValue attribute */
    ESP_ZB_ZCL_ATTR_BINARY_INPUT_RELIABILITY_ID               = 0x0067,    /*!< The attribute indicates whether the PresentValue or the operation of the physical input, output or value in question (as appropriate for the cluster) is reliable. */
    ESP_ZB_ZCL_ATTR_BINARY_INPUT_STATUS_FLAGS_ID              = 0x006F,    /*!< StatusFlag attribute */
    ESP_ZB_ZCL_ATTR_BINARY_INPUT_APPLICATION_TYPE_ID          = 0x0100,    /*!< The attribute indicates the specific application usage for this cluster. */
} esp_zb_zcl_binary_input_attr_t;

/** @brief Values for StatusFlags attribute */
typedef enum {
    ESP_ZB_ZCL_BINARY_INPUT_STATUS_FLAG_NORMAL         = 0x00, /*!< Normal (default) state. */
    ESP_ZB_ZCL_BINARY_INPUT_STATUS_FLAG_IN_ALARM       = 0x01, /*!< In alarm bit. */
    ESP_ZB_ZCL_BINARY_INPUT_STATUS_FLAG_FAULT          = 0x02, /*!< Fault bit. */
    ESP_ZB_ZCL_BINARY_INPUT_STATUS_FLAG_OVERRIDDEN     = 0x04, /*!< Overridden bit. */
    ESP_ZB_ZCL_BINARY_INPUT_STATUS_FLAG_OUT_OF_SERVICE = 0x08, /*!< Out of service bit. */
} esp_zb_zcl_binary_input_status_flags_value_t;

/** @brief Values for Reliability attribute */
typedef enum {
    ESP_ZB_ZCL_BINARY_INPUT_RELIABILITY_NO_FAULT_DETECTED = 0x00, /*!< No fault detected */
    ESP_ZB_ZCL_BINARY_INPUT_RELIABILITY_NO_SENSOR         = 0x01, /*!< No sensor */
    ESP_ZB_ZCL_BINARY_INPUT_RELIABILITY_OVER_RANGE        = 0x02, /*!< Over range */
    ESP_ZB_ZCL_BINARY_INPUT_RELIABILITY_UNDER_RANGE       = 0x03, /*!< Under range */
    ESP_ZB_ZCL_BINARY_INPUT_RELIABILITY_OPEN_LOOP         = 0x04, /*!< Open loop */
    ESP_ZB_ZCL_BINARY_INPUT_RELIABILITY_SHORTED_LOOP      = 0x05, /*!< Shorted loop */
    ESP_ZB_ZCL_BINARY_INPUT_RELIABILITY_NO_OUTPUT         = 0x06, /*!< No output */
    ESP_ZB_ZCL_BINARY_INPUT_RELIABILITY_UNRELIABLE_OTHER  = 0x07, /*!< Unreliable other */
    ESP_ZB_ZCL_BINARY_INPUT_RELIABILITY_PROCESS_ERROR     = 0x08, /*!< Process error */
    /* 0x09 is for multistate clusters only */
    ESP_ZB_ZCL_BINARY_INPUT_RELIABILITY_CONFIGURATION_ERROR = 0x0a, /*!< Configuration error */
} esp_zb_zcl_binary_input_reliability_value_t;

/** @brief Values for Polarity attribute */
typedef enum {
    ESP_ZB_ZCL_BINARY_INPUT_POLARITY_NORMAL  = 0x00, /*!< Normal polarity */
    ESP_ZB_ZCL_BINARY_INPUT_POLARITY_REVERSE = 0x01, /*!< Reverse polarity */
} esp_zb_zcl_binary_input_polarity_value_t;

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
/** @brief Macros for ApplicationType attribute */
#define ESP_ZB_ZCL_BI_GROUP_ID 0x03
#define ESP_ZB_ZCL_BI_SET_APP_TYPE_WITH_ID(_type, _id) (((ESP_ZB_ZCL_BI_GROUP_ID & 0xFF) << 24) | (((_type) & 0xFF) << 16) | ((_id) & 0xFFFF))

/** @brief Values for Binary Input cluster application types (Type field, bits 16-23) */
typedef enum {
    ESP_ZB_ZCL_BI_APP_TYPE_DOMAIN_HVAC     = 0x00, /*!< Application Domain HVAC */
    ESP_ZB_ZCL_BI_APP_TYPE_DOMAIN_SECURITY = 0x01, /*!< Application Domain Security */
    /* 0x02 to 0xFE are reserved */
    ESP_ZB_ZCL_BI_APP_TYPE_OTHER           = 0xFF /*!< Other */
} esp_zb_zcl_bi_application_types_t;

typedef enum {
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_2_PIPE_PUMP_STATUS =
        ESP_ZB_ZCL_BI_SET_APP_TYPE_WITH_ID(ESP_ZB_ZCL_BI_APP_TYPE_DOMAIN_HVAC, 0x0000), /*!< 2 Pipe Pump Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_AIR_PROVING_SWITCH,                                       /*!< Air Proving Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_ALARM_RESET,                                              /*!< Alarm Reset BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_BOILER_STATUS,                                            /*!< Boiler Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_BOILER_FLOW_STATUS,                                       /*!< Boiler Flow Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_BOILER_GENERAL_ALARM,                                     /*!< Boiler General Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_BOILER_HIGH_TEMPERATURE_ALARM,                            /*!< Boiler High Temperature Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_BOILER_ISOLATION_VALVE_STATUS,                            /*!< Boiler Isolation Valve Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_BOILER_MAINTENANCE_SWITCH,                                /*!< Boiler Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_BOILER_PUMP_OVERLOAD,                                     /*!< Boiler Pump Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_BOILER_PUMP_STATUS,                                       /*!< Boiler Pump Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_BOILER_STATUS_2,                                          /*!< Boiler Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_BOX_HEATING_ALARM,                                        /*!< Box Heating Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CHILLER_ALARM,                                            /*!< Chiller Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CHILLER_CHILLED_WATER_FLOW_STATUS,                        /*!< Chiller Chilled Water Flow Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CHILLER_CHILLED_WATER_ISOLATION_VALVE_STATUS,             /*!< Chiller Chilled Water Isolation Valve Status BI
                                                                                         */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CHILLER_CONDENSER_WATER_FLOW_STATUS,                      /*!< Chiller Condenser Water Flow Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CHILLER_CONDENSER_WATER_ISOLATION_VALVE_STATUS,           /*!< Chiller Condenser Water Isolation Valve
                                                                                           Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CHILLER_MAINTENANCE_SWITCH,                               /*!< Chiller Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CHILLER_STATUS,                                           /*!< Chiller Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CHILLED_WATER_EXPANSION_TANK_ALARM,                       /*!< Chilled Water Expansion Tank Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CHILLED_WATER_EXPANSION_TANK_HIGH_PRESSURE_ALARM,         /*!< Chilled Water Expansion Tank High Pressure
                                                                                           Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CHILLED_WATER_EXPANSION_TANK_LOW_PRESSURE_ALARM,          /*!< Chilled Water Expansion Tank Low Pressure
                                                                                           Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CHILLED_WATER_EXPANSION_TANK_STATUS,                      /*!< Chilled Water Expansion Tank Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_COMBUSTION_DAMPER_STATUS,                                 /*!< Combustion Damper Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_COOLING_ALARM,                                            /*!< Cooling Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_COOLING_PUMP_MAINTENANCE_SWITCH,                          /*!< Cooling Pump Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_COOLING_PUMP_OVERLOAD,                                    /*!< Cooling Pump Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_COOLING_PUMP_STATUS,                                      /*!< Cooling Pump Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_EXPANSION_TANK_ALARM,                     /*!< Condenser Water Expansion Tank Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_EXPANSION_TANK_HIGH_PRESSURE_ALARM,       /*!< Condenser Water Expansion Tank High
                                                                                           Pressure Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_EXPANSION_TANK_LOW_PRESSURE_ALARM,        /*!< Condenser Water Expansion Tank Low
                                                                                           Pressure Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_EXPANSION_TANK_STATUS,                    /*!< Condenser Water Expansion Tank Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_PUMP_MAINTENANCE_SWITCH,                  /*!< Condenser Water Pump Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_PUMP_OVERLOAD,                            /*!< Condenser Water Pump Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_CONDENSER_WATER_PUMP_STATUS,                              /*!< Condenser Water Pump Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_DECOUPLE_LOOP_FLOW_DIRECTION,                             /*!< Decouple Loop Flow Direction BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_DISCHARGE_SMOKE,                                          /*!< Discharge Smoke BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_DOOR_STATUS,                                              /*!< Door Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_ECONOMIZER_COMMAND,                                       /*!< Economizer Command BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_EMERGENCY_SHUTDOWN,                                       /*!< Emergency Shutdown BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_EQUIPMENT_TAMPER,                                         /*!< Equipment Tamper BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_ENERGY_HOLD_OFF,                                          /*!< Energy Hold Off BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_EXHAUST_FAN_MAINTENANCE_SWITCH,                           /*!< Exhaust Fan Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_EXHAUST_FAN_OVERLOAD,                                     /*!< Exhaust Fan Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_EXHAUST_FAN_STATUS,                                       /*!< Exhaust Fan Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_EXHAUST_FILTER_STATUS,                                    /*!< Exhaust Filter Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_EXHAUST_SMOKE,                                            /*!< Exhaust Smoke BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_EXPANSION_TANK_ALARM,                                     /*!< Expansion Tank Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_EXPANSION_TANK_HIGH_PRESSURE_ALARM,                       /*!< Expansion Tank High Pressure Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_EXPANSION_TANK_LOW_PRESSURE_ALARM,                        /*!< Expansion Tank Low Pressure Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_EXPANSION_TANK_STATUS,                                    /*!< Expansion Tank Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_FAN_CONTROL_BY_OTHERS,                                    /*!< Fan Control By Others BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_FAN_OVERLOAD,                                             /*!< Fan Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_FILTER_MONITORING,                                        /*!< Filter Monitoring BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_FINAL_FILTER_STATUS,                                      /*!< Final Filter Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_FREE_COOLING_AVAILABILITY,                                /*!< Free Cooling Availability BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HEAT_RECOVERY_PUMP_STATUS,                                /*!< Heat Recovery Pump Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HEAT_RECOVERY_WHEEL_ALARM,                                /*!< Heat Recovery Wheel Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HEAT_RECOVERY_WHEEL_MAINTENANCE_SWITCH,                   /*!< Heat Recovery Wheel Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HEAT_RECOVERY_WHEEL_OVERLOAD,                             /*!< Heat Recovery Wheel Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HEAT_RECOVERY_WHEEL_STATUS,                               /*!< Heat Recovery Wheel Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HEATING_ALARM,                                            /*!< Heating Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HEATING_COOLING_PUMP_MAINTENANCE_SWITCH,                  /*!< Heating/Cooling Pump Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HEATING_COOLING_PUMP_OVERLOAD,                            /*!< Heating/Cooling Pump Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HIGH_HUMIDITY_LIMIT,                                      /*!< High Humidity Limit BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HIGH_STATIC_PRESSURE_FAULT,                               /*!< High Static Pressure Fault BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HIGH_TEMPERATURE_LIMIT_FAULT,                             /*!< High Temperature Limit Fault BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HUMIDIFIER_ALARM,                                         /*!< Humidifier Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HUMIDIFIER_MAINTENANCE_SWITCH,                            /*!< Humidifier Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HUMIDIFIER_OVERLOAD,                                      /*!< Humidifier Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HUMIDIFIER_STATUS,                                        /*!< Humidifier Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HEAT_EXCHANGER_ALARM,                                     /*!< Heat Exchanger Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HEAT_EXCHANGER_ISOLATION_VALVE_STATUS,                    /*!< Heat Exchanger Isolation Valve Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_HEAT_EXCHANGER_MAINTENANCE_SWITCH,                        /*!< Heat Exchanger Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_LIGHTING_STATUS,                                          /*!< Lighting Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_LOW_STATIC_PRESSURE_FAULT,                                /*!< Low Static Pressure Fault BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_LOW_TEMPERATURE_LIMIT_FAULT,                              /*!< Low Temperature Limit Fault BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_MINIMUM_OUTDOOR_AIR_DAMPER_END_SWITCH,                    /*!< Minimum Outdoor Air Damper End Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_MINIMUM_OUTDOOR_AIR_FAN_MAINTENANCE_SWITCH,               /*!< Minimum Outdoor Air Fan Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_MINIMUM_OUTDOOR_AIR_FAN_OVERLOAD,                         /*!< Minimum Outdoor Air Fan Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_MINIMUM_OUTDOOR_AIR_FAN_STATUS,                           /*!< Minimum Outdoor Air Fan Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_MINIMUM_OUTDOOR_AIR_FAN_VARIABLE_FREQUENCY_DRIVE_FAULT,   /*!< Minimum Outdoor Air Fan Variable
                                                                                           Frequency Drive Fault BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_OCCUPANCY,                                                /*!< Occupancy BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_OCCUPANCY_SENSOR,                                         /*!< Occupancy Sensor BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_MAINTENANCE_SWITCH,            /*!< Primary Chilled Water Pump Maintenance Switch
                                                                                           BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_OVERLOAD,                      /*!< Primary Chilled Water Pump Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_STATUS,                        /*!< Primary Chilled Water Pump Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_MAINTENANCE_SWITCH_2,          /*!< Primary Chilled Water Pump Maintenance
                                                                                           Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_OVERLOAD_2,                    /*!< Primary Chilled Water Pump Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_STATUS_2,                      /*!< Primary Chilled Water Pump Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PRE_FILTER_STATUS,                                        /*!< Pre-Filter Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PREHEAT_ALARM,                                            /*!< Preheat Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PREHEAT_BONNET_SWITCH,                                    /*!< Preheat Bonnet Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PREHEAT_PUMP_MAINTENANCE_SWITCH,                          /*!< Preheat Pump Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PREHEAT_PUMP_OVERLOAD,                                    /*!< Preheat Pump Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PREHEAT_PUMP_STATUS,                                      /*!< Preheat Pump Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_REFRIGERANT_ALARM,                                        /*!< Refrigerant Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_REHEAT_ALARM,                                             /*!< Reheat Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_REHEAT_BONNET_SWITCH,                                     /*!< Reheat Bonnet Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_REHEAT_PUMP_MAINTENANCE_SWITCH,                           /*!< Reheat Pump Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_REHEAT_PUMP_OVERLOAD,                                     /*!< Reheat Pump Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_REHEAT_PUMP_STATUS,                                       /*!< Reheat Pump Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_RELIEF_FAN_MAINTENANCE_SWITCH,                            /*!< Relief Fan Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_RELIEF_FAN_OVERLOAD,                                      /*!< Relief Fan Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_RELIEF_FAN_STATUS,                                        /*!< Relief Fan Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_RELIEF_FAN_VARIABLE_FREQUENCY_DRIVE_FAULT,                /*!< Relief Fan Variable Frequency Drive Fault BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_RETURN_AIR_SMOKE,                                         /*!< Return Air Smoke BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_RETURN_FAN_MAINTENANCE_SWITCH,                            /*!< Return Fan Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_RETURN_FAN_OVERLOAD,                                      /*!< Return Fan Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_RETURN_FAN_STATUS,                                        /*!< Return Fan Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_RETURN_FAN_VFD_FAULT,                                     /*!< Return Fan VFD Fault BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_RETURN_SMOKE,                                             /*!< Return Smoke BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP_1_MAINTENANCE_SWITCH,        /*!< Secondary Chilled Water Pump 1 Maintenance
                                                                                           Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP_1_OVERLOAD,                  /*!< Secondary Chilled Water Pump 1 Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP_1_STATUS,                    /*!< Secondary Chilled Water Pump 1 Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP_1_MAINTENANCE_SWITCH_2,      /*!< Secondary Chilled Water Pump 1
                                                                                           Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP_1_OVERLOAD_2,                /*!< Secondary Chilled Water Pump 1 Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP_1_STATUS_2,                  /*!< Secondary Chilled Water Pump 1 Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SIDELOOP,                                                 /*!< Sideloop BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_GENERIC_STATUS,                                           /*!< Generic Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SUMMER_WINTER,                                            /*!< Summer Winter BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_ALARM,                               /*!< Supplemental Heating Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_PUMP_MAINTENANCE_SWITCH,             /*!< Supplemental Heating Pump Maintenance Switch BI
                                                                                         */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_PUMP_OVERLOAD,                       /*!< Supplemental Heating Pump Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_PUMP_STATUS,                         /*!< Supplemental Heating Pump Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SUPPLY_FAN_MAINTENANCE_SWITCH,                            /*!< Supply Fan Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SUPPLY_FAN_OVERLOAD,                                      /*!< Supply Fan Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SUPPLY_FAN_STATUS,                                        /*!< Supply Fan Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_SUPPLY_FAN_VARIABLE_FREQUENCY_DRIVE_FAULT,                /*!< Supply Fan Variable Frequency Drive Fault BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_TEMPORARY_OCCUPANCY,                                      /*!< Temporary Occupancy BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_TOWER_LEVEL_ALARM,                                        /*!< Tower Level Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_TOWER_LEVEL_STATUS,                                       /*!< Tower Level Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_TOWER_TEMP,                                               /*!< Tower Temp BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_TOWER_VIBRATION_ALARM_STATUS,                             /*!< Tower Vibration Alarm Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_TOWER_LEVEL_ALARM_2,                                      /*!< Tower Level Alarm BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_TOWER_LEVEL_SWITCH,                                       /*!< Tower Level Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_TOWER_TEMP_SWITCH,                                        /*!< Tower Temp Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_TOWER_FAN_ISOLATION_VALVE_STATUS,                         /*!< Tower Fan Isolation Valve Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_TOWER_FAN_MAINTENANCE_SWITCH,                             /*!< Tower Fan Maintenance Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_TOWER_FAN_OVERLOAD,                                       /*!< Tower Fan Overload BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_TOWER_FAN_STATUS,                                         /*!< Tower Fan Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_UNIT_ENABLE,                                              /*!< Unit Enable BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_UNIT_RESET,                                               /*!< Unit Reset BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_WINDOW_STATUS,                                            /*!< Window Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_ZONE_SENSOR_TEMPORARY_OCCUPANCY,                          /*!< Zone Sensor Temporary Occupancy BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_AIR_PROVING_SWITCH_2,                                     /*!< Air Proving Switch BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_HEATING_STATUS,                                   /*!< Primary Heating Status BI */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_PRIMARY_COOLING_STATUS,                                   /*!< Primary Cooling Status BI */
    /* 0x0200 to 0xFFFE are Vendor defined */
    ESP_ZB_ZCL_BI_DOMAIN_HVAC_OTHER = ESP_ZB_ZCL_BI_SET_APP_TYPE_WITH_ID(ESP_ZB_ZCL_BI_APP_TYPE_DOMAIN_HVAC, 0xFFFF) /*!< Other */
} esp_zb_zcl_bi_domain_hvac_t;

typedef enum {
    ESP_ZB_ZCL_BI_DOMAIN_SECURITY_GLASS_BREAKAGE_DETECTION_0 =
        ESP_ZB_ZCL_BI_SET_APP_TYPE_WITH_ID(ESP_ZB_ZCL_BI_APP_TYPE_DOMAIN_SECURITY, 0x0000), /*!< Glass Breakage Detection */
    ESP_ZB_ZCL_BI_DOMAIN_SECURITY_INTRUSION_DETECTION,                                      /*!< Intrusion Detection */
    ESP_ZB_ZCL_BI_DOMAIN_SECURITY_MOTION_DETECTION,                                         /*!< Motion Detection */
    ESP_ZB_ZCL_BI_DOMAIN_SECURITY_GLASS_BREAKAGE_DETECTION_1,                               /*!< Glass Breakage Detection */
    ESP_ZB_ZCL_BI_DOMAIN_SECURITY_ZONE_ARMED,                                               /*!< Zone Armed */
    ESP_ZB_ZCL_BI_DOMAIN_SECURITY_GLASS_BREAKAGE_DETECTION_2,                               /*!< Glass Breakage Detection */
    ESP_ZB_ZCL_BI_DOMAIN_SECURITY_SMOKE_DETECTION,                                          /*!< Smoke Detection */
    ESP_ZB_ZCL_BI_DOMAIN_SECURITY_CARBON_DIOXIDE_DETECTION,                                 /*!< Carbon Dioxide Detection */
    ESP_ZB_ZCL_BI_DOMAIN_SECURITY_HEAT_DETECTION,                                           /*!< Heat Detection */
    /* 0x0200 to 0xFFFE are Vendor defined */
    ESP_ZB_ZCL_BI_DOMAIN_SECURITY_OTHER = ESP_ZB_ZCL_BI_SET_APP_TYPE_WITH_ID(ESP_ZB_ZCL_BI_APP_TYPE_DOMAIN_SECURITY, 0xFFFF) /*!< Other */
} esp_zb_zcl_bi_domain_security_t;

/** @brief Default value for ActiveText attribute */
#define ESP_ZB_ZCL_BINARY_INPUT_ACTIVE_TEXT_DEFAULT_VALUE {0}

/** @brief Default value for Description attribute */
#define ESP_ZB_ZCL_BINARY_INPUT_DESCRIPTION_DEFAULT_VALUE {0}

/** @brief Default value for InactiveText attribute */
#define ESP_ZB_ZCL_BINARY_INPUT_INACTIVE_TEXT_DEFAULT_VALUE {0}

/** @brief OutOfService attribute default value */
#define ESP_ZB_ZCL_BINARY_INPUT_OUT_OF_SERVICE_DEFAULT_VALUE false

/** @brief Default value for Polarity attribute */
#define ESP_ZB_ZCL_BINARY_INPUT_POLARITY_DEFAULT_VALUE ((uint8_t)0)

/** @brief Default value for Reliability attribute */
#define ESP_ZB_ZCL_BINARY_INPUT_RELIABILITY_DEFAULT_VALUE ((uint8_t)0)

/** @brief StatusFlag attribute default value */
#define ESP_ZB_ZCL_BINARY_INPUT_STATUS_FLAGS_DEFAULT_VALUE ESP_ZB_ZCL_BINARY_INPUT_STATUS_FLAGS_MIN_VALUE

/** @brief StatusFlag attribute minimum value */
#define ESP_ZB_ZCL_BINARY_INPUT_STATUS_FLAGS_MIN_VALUE 0

/** @brief StatusFlag attribute maximum value */
#define ESP_ZB_ZCL_BINARY_INPUT_STATUS_FLAGS_MAX_VALUE 0x0F

void esp_zb_zcl_binary_input_init_server(void);
void esp_zb_zcl_binary_input_init_client(void);

#define ESP_ZB_ZCL_CLUSTER_ID_BINARY_INPUT_SERVER_ROLE_INIT esp_zb_zcl_binary_input_init_server
#define ESP_ZB_ZCL_CLUSTER_ID_BINARY_INPUT_CLIENT_ROLE_INIT esp_zb_zcl_binary_input_init_client

#ifdef __cplusplus
}
#endif
