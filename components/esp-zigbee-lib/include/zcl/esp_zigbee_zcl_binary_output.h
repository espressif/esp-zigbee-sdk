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

/** @brief Binary Output cluster attribute identifiers. */
typedef enum {
    ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_ACTIVE_TEXT_ID        = 0x0004U, /*!< Human readable description of the ACTIVE state. */
    ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_DESCRIPTION_ID        = 0x001CU, /*!< Description of the usage. */
    ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_INACTIVE_TEXT_ID      = 0x002EU, /*!< Human readable description of the INACTIVE state. */
    ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_MIN_OFF_TIME_ID       = 0x0042U, /*!< Minimum off time. */
    ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_MAX_ON_TIME_ID        = 0x0043U, /*!< Maximum on time. */
    ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_OUT_OF_SERVICE_ID     = 0x0051U, /*!< OutOfService attribute. */
    ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_POLARITY_ID           = 0x0054U, /*!< Relationship between physical and logical state. */
    ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_PRESENT_VALUE_ID      = 0x0055U, /*!< PresentValue attribute. */
    /** TODO: support PriorityArray Attribute */
    // ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_PRIORITY_ARRAY_ID     = 0x0057U, /*!< Priority array attribute. */
    ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_RELIABILITY_ID        = 0x0067U, /*!< Reliability attribute. */
    ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_RELINQUISH_DEFAULT_ID = 0x0068U, /*!< Relinquish default. */
    ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_STATUS_FLAGS_ID       = 0x006FU, /*!< StatusFlag attribute. */
    ESP_ZB_ZCL_ATTR_BINARY_OUTPUT_APPLICATION_TYPE_ID   = 0x0100U, /*!< ApplicationType attribute. */
} esp_zb_zcl_binary_output_attr_t;


/** @brief Default value for ActiveText attribute */
#define ESP_ZB_ZCL_BINARY_OUTPUT_ACTIVE_TEXT_DEFAULT_VALUE          {0}
/** @brief Default value for Description attribute */
#define ESP_ZB_ZCL_BINARY_OUTPUT_DESCRIPTION_DEFAULT_VALUE          {0}
/** @brief Default value for InactiveText attribute */
#define ESP_ZB_ZCL_BINARY_OUTPUT_INACTIVE_TEXT_DEFAULT_VALUE        {0}
/** @brief Default value for MinOffTime attribute */
#define ESP_ZB_ZCL_BINARY_OUTPUT_MIN_OFF_TIME_DEFAULT_VALUE         ESP_ZB_ZCL_VALUE_U32_FF
/** @brief Default value for MaxOnTime attribute */
#define ESP_ZB_ZCL_BINARY_OUTPUT_MAX_ON_TIME_DEFAULT_VALUE          ESP_ZB_ZCL_VALUE_U32_FF
/** @brief OutOfService attribute default value */
#define ESP_ZB_ZCL_BINARY_OUTPUT_OUT_OF_SERVICE_DEFAULT_VALUE       false
/** @brief Default value for Polarity attribute */
#define ESP_ZB_ZCL_BINARY_OUTPUT_POLARITY_DEFAULT_VALUE             ((uint8_t)0)
/** @brief Default value for Reliability attribute */
#define ESP_ZB_ZCL_BINARY_OUTPUT_RELIABILITY_DEFAULT_VALUE          ((uint8_t)0)
/** @brief Default value for RelinquishDefault attribute */
#define ESP_ZB_ZCL_BINARY_OUTPUT_RELINQUISH_DEFAULT_DEFAULT_VALUE   false
/** @brief StatusFlag attribute minimum value */
#define ESP_ZB_ZCL_BINARY_OUTPUT_STATUS_FLAGS_MIN_VALUE              0x00U
/** @brief StatusFlag attribute maximum value */
#define ESP_ZB_ZCL_BINARY_OUTPUT_STATUS_FLAGS_MAX_VALUE              0x0FU
/** @brief StatusFlag attribute default value */
#define ESP_ZB_ZCL_BINARY_OUTPUT_STATUS_FLAGS_DEFAULT_VALUE         ESP_ZB_ZCL_BINARY_OUTPUT_STATUS_FLAGS_MIN_VALUE
/** @brief StatusFlag attribute maximum value */
#define ESP_ZB_ZCL_BINARY_OUTPUT_APPLICATION_TYPE_MIN_VALUE         0
/** @brief StatusFlag attribute maximum value */
#define ESP_ZB_ZCL_BINARY_OUTPUT_APPLICATION_TYPE_MAX_VALUE         ESP_ZB_ZCL_VALUE_U32_FF

/** @brief Values for StatusFlags attribute */
typedef enum {
    ESP_ZB_ZCL_BINARY_OUTPUT_STATUS_FLAG_NORMAL         = 0x00, /*!< Normal (default) state. */
    ESP_ZB_ZCL_BINARY_OUTPUT_STATUS_FLAG_IN_ALARM       = 0x01, /*!< In alarm bit. */
    ESP_ZB_ZCL_BINARY_OUTPUT_STATUS_FLAG_FAULT          = 0x02, /*!< Fault bit. */
    ESP_ZB_ZCL_BINARY_OUTPUT_STATUS_FLAG_OVERRIDDEN     = 0x04, /*!< Overridden bit. */
    ESP_ZB_ZCL_BINARY_OUTPUT_STATUS_FLAG_OUT_OF_SERVICE = 0x08, /*!< Out of service bit. */
} esp_zb_zcl_binary_output_status_flags_value_t;

/** @brief Values for Reliability attribute */
typedef enum {
    ESP_ZB_ZCL_BINARY_OUTPUT_RELIABILITY_NO_FAULT_DETECTED = 0x00, /*!< No fault detected */
    ESP_ZB_ZCL_BINARY_OUTPUT_RELIABILITY_NO_SENSOR         = 0x01, /*!< No sensor */
    ESP_ZB_ZCL_BINARY_OUTPUT_RELIABILITY_OVER_RANGE        = 0x02, /*!< Over range */
    ESP_ZB_ZCL_BINARY_OUTPUT_RELIABILITY_UNDER_RANGE       = 0x03, /*!< Under range */
    ESP_ZB_ZCL_BINARY_OUTPUT_RELIABILITY_OPEN_LOOP         = 0x04, /*!< Open loop */
    ESP_ZB_ZCL_BINARY_OUTPUT_RELIABILITY_SHORTED_LOOP      = 0x05, /*!< Shorted loop */
    ESP_ZB_ZCL_BINARY_OUTPUT_RELIABILITY_NO_OUTPUT         = 0x06, /*!< No output */
    ESP_ZB_ZCL_BINARY_OUTPUT_RELIABILITY_UNRELIABLE_OTHER  = 0x07, /*!< Unreliable other */
    ESP_ZB_ZCL_BINARY_OUTPUT_RELIABILITY_PROCESS_ERROR     = 0x08, /*!< Process error */
    /* 0x09 is for multistate clusters only */
    ESP_ZB_ZCL_BINARY_OUTPUT_RELIABILITY_CONFIGURATION_ERROR = 0x0a, /*!< Configuration error */
} esp_zb_zcl_binary_output_reliability_value_t;

/** Binary output cluster application types
 *      The ApplicationType attribute indicates the specific application usage
 *      for the cluster. ApplicationType is subdivided into Group, Type and
 *      an Index number, as follows:
 *
 *      Group = Bits 24 to 31
 *        An indication of the cluster this attribute is part of. Binary output
 *        clusters have Group = 0x00.
 *
 *      Type = Bits 16 to 23
 *        The physical quantity that the PresentValue attribute of the cluster
 *        represents.
 *
 *      Index = Bits 0 to 15
 *        The specific application usage of the cluster.
 */
/** @brief Values for Polarity attribute */
typedef enum {
    ESP_ZB_ZCL_BINARY_OUTPUT_POLARITY_NORMAL  = 0x00, /*!< Normal polarity */
    ESP_ZB_ZCL_BINARY_OUTPUT_POLARITY_REVERSE = 0x01, /*!< Reverse polarity */
} esp_zb_zcl_binary_output_polarity_value_t;

/** @brief Macros for ApplicationType attribute */
#define ESP_ZB_ZCL_BO_GROUP_ID 0x04
#define ESP_ZB_ZCL_BO_SET_APP_TYPE_WITH_ID(_type, _id) (((ESP_ZB_ZCL_BO_GROUP_ID & 0xFF) << 24) | (((_type) & 0xFF) << 16) | ((_id) & 0xFFFF))

/** @brief Values for Binary Output cluster application types (Type field, bits 16-23) */
typedef enum {
    ESP_ZB_ZCL_BO_APP_TYPE_DOMAIN_HVAC     = 0x00, /*!< Application Domain HVAC */
    ESP_ZB_ZCL_BO_APP_TYPE_DOMAIN_SECURITY = 0x01, /*!< Application Domain Security */
    /* 0x02 to 0xFE are reserved */
    ESP_ZB_ZCL_BO_APP_TYPE_OTHER    = 0xFF  /*!< Other */
} esp_zb_zcl_bo_application_types_t;

/** @brief Values for Binary Output cluster HVAC application usages */
typedef enum {
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_2_PIPE_CIRCULATION_PUMP_STATUS =
        ESP_ZB_ZCL_BO_SET_APP_TYPE_WITH_ID(ESP_ZB_ZCL_BO_APP_TYPE_DOMAIN_HVAC, 0x0000), /*!< 2 Pipe Circulation Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_2_PIPE_VALVE,                                             /*!< 2 Pipe Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_2_PIPE_VALVE_COMMAND,                                     /*!< 2 Pipe Valve Command BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_BOILER,                                                   /*!< Boiler BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_BOILER_ISOLATION_VALVE,                                   /*!< Boiler Isolation Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_BOILER_PUMP,                                              /*!< Boiler Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_BOX_COOLING_2_POSITION,                                   /*!< Box Cooling 2 Position BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_BOX_HEATING_2_POSITION,                                   /*!< Box Heating 2 Position BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_BOX_HEATING_ENABLE,                                       /*!< Box Heating Enable BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_BOX_HEATING_STAGE_1,                                      /*!< Box Heating Stage 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_BOX_HEATING_STAGE_2,                                      /*!< Box Heating Stage 2 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_BOX_HEATING_STAGE_3,                                      /*!< Box Heating Stage 3 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_CHILLER_1_ISOLATION_VALVE,                                /*!< Chiller 1 Isolation Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_CHILLER,                                                  /*!< Chiller BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_CHILLER_CHILLED_WATER_ISOLATION_VALVE,          /*!< Chiller Chilled Water Isolation Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_CHILLER_CONDENSER_WATER_ISOLATION_VALVE,        /*!< Chiller Condenser Water Isolation Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COMBUSTION_DAMPER,                              /*!< Combustion Damper BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COMPRESSOR_STAGE_1,                             /*!< Compressor Stage 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COMPRESSOR_STAGE_2,                             /*!< Compressor Stage 2 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COOLING_CIRCULATION_PUMP,                       /*!< Cooling Circulation Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_1,                                /*!< Cooling Stage 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_2,                                /*!< Cooling Stage 2 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_3,                                /*!< Cooling Stage 3 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_4,                                /*!< Cooling Stage 4 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_5,                                /*!< Cooling Stage 5 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_6,                                /*!< Cooling Stage 6 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_7,                                /*!< Cooling Stage 7 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COOLING_STAGE_8,                                /*!< Cooling Stage 8 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COOLING_VALVE,                                  /*!< Cooling Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_COOLING_VALVE_COMMAND,                          /*!< Cooling Valve Command BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_CHILLED_WATER_PUMP,                             /*!< Chilled Water Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_ECONOMIZER_ENABLE,                              /*!< Economizer Enable BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_EXHAUST_AIR_DAMPER,                             /*!< Exhaust Air Damper BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_EXHAUST_FAN,                                    /*!< Exhaust Fan BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_FAN,                                            /*!< Fan BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_FAN_SPEED_1,                                    /*!< Fan Speed 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_FAN_SPEED_2,                                    /*!< Fan Speed 2 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_FAN_SPEED_3,                                    /*!< Fan Speed 3 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HEAT_RECOVERY_PUMP,                             /*!< Heat Recovery Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HEAT_RECOVERY_VALVE,                            /*!< Heat Recovery Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HEAT_RECOVERY_WHEEL,                            /*!< Heat Recovery Wheel BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HEATING_STAGE_1,                                /*!< Heating Stage 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HEATING_STAGE_2,                                /*!< Heating Stage 2 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HEATING_STAGE_3,                                /*!< Heating Stage 3 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HEATING_VALVE,                                  /*!< Heating Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HEATING_VALVE_COMMAND,                          /*!< Heating Valve Command BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HOT_GAS_BYPASS_VALVE,                           /*!< Hot Gas Bypass Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HUMIDIFICATION_STAGE_1,                         /*!< Humidification Stage 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HUMIDIFICATION_STAGE_2,                         /*!< Humidification Stage 2 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HUMIDIFICATION_STAGE_3,                         /*!< Humidification Stage 3 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HUMIDIFICATION_STAGE_4,                         /*!< Humidification Stage 4 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HUMIDIFIER_ENABLE,                              /*!< Humidifier Enable BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_HEAT_EXCHANGER_ISOLATION_VALVE,                 /*!< Heat Exchanger Isolation Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_LIGHTING,                                       /*!< Lighting BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_MINIMUM_OUTSIDE_AIR_DAMPER,                     /*!< Minimum Outside Air Damper BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_MINIMUM_OUTSIDE_AIR_FAN,                        /*!< Minimum Outside Air Fan BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_OUTSIDE_AIR_DAMPER,                             /*!< Outside Air Damper BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PRIMARY_CHILLED_WATER_PUMP_1,                   /*!< Primary Chilled Water Pump 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PLATE_AND_FRAME_HEAT_EXCHANGER_ISOLATION_VALVE, /*!< Plate-and-Frame Heat Exchanger Isolation
                                                                                 Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PRIMARY_HOT_WATER_PUMP,                         /*!< Primary Hot Water Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PRIMARY_HEAT_EXCHANGE_PUMP,                     /*!< Primary Heat Exchange Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_CIRCULATION_PUMP,                       /*!< Preheat Circulation Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_ENABLE,                                 /*!< Preheat Enable BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_1,                                /*!< Preheat Stage 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_2,                                /*!< Preheat Stage 2 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_3,                                /*!< Preheat Stage 3 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_4,                                /*!< Preheat Stage 4 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_5,                                /*!< Preheat Stage 5 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_6,                                /*!< Preheat Stage 6 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_7,                                /*!< Preheat Stage 7 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_STAGE_8,                                /*!< Preheat Stage 8 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_PREHEAT_VALVE,                                  /*!< Preheat Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_REHEAT_CIRCULATION_PUMP,                        /*!< Reheat Circulation Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_REHEAT_ENABLE,                                  /*!< Reheat Enable BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_1,                                 /*!< Reheat Stage 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_2,                                 /*!< Reheat Stage 2 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_3,                                 /*!< Reheat Stage 3 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_4,                                 /*!< Reheat Stage 4 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_5,                                 /*!< Reheat Stage 5 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_6,                                 /*!< Reheat Stage 6 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_7,                                 /*!< Reheat Stage 7 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_REHEAT_STAGE_8,                                 /*!< Reheat Stage 8 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_RELIEF_FAN,                                     /*!< Relief Fan BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_RETURN_FAN,                                     /*!< Return Fan BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_REVERSING_VALVE_1,                              /*!< Reversing Valve 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_REVERSING_VALVE_2,                              /*!< Reversing Valve 2 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SECONDARY_CHILLED_WATER_PUMP,                   /*!< Secondary Chilled Water Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SECONDARY_HOT_WATER_PUMP,                       /*!< Secondary Hot Water Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SECONDARY_HEAT_EXCHANGE_PUMP,                   /*!< Secondary Heat Exchange Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP,                                       /*!< Sideloop BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_1,                               /*!< Sideloop Stage 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_2,                               /*!< Sideloop Stage 2 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_3,                               /*!< Sideloop Stage 3 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_4,                               /*!< Sideloop Stage 4 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_5,                               /*!< Sideloop Stage 5 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_6,                               /*!< Sideloop Stage 6 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_7,                               /*!< Sideloop Stage 7 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SIDELOOP_STAGE_8,                               /*!< Sideloop Stage 8 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_STEAM_ISOLATION_VALVE,                          /*!< Steam Isolation Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_2_POSITION,                /*!< Supplemental Heating 2 Position BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_STAGE_1,                   /*!< Supplemental Heating Stage 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_VALVE,                     /*!< Supplemental Heating Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_ENABLE,                    /*!< Supplemental Heating Enable BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SUPPLEMENTAL_HEATING_PUMP,                      /*!< Supplemental Heating Pump BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_SUPPLY_FAN,                                     /*!< Supply Fan BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_TOWER_BASIN_HEATER_1,                           /*!< Tower Basin Heater BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_TOWER_BASIN_MAKEUP_1,                           /*!< Tower Basin Makeup BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_TOWER_BASIN_HEATER_2,                           /*!< Tower Basin Heater BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_TOWER_BASIN_MAKEUP_2,                           /*!< Tower Basin Makeup BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_TOWER_ISOLATION_VALVE,                          /*!< Tower Isolation Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_TOWER_FAN,                                      /*!< Tower Fan BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_TOWER_FAN_SPEED_1,                              /*!< Tower Fan Speed 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_TOWER_FAN_SPEED_2,                              /*!< Tower Fan Speed 2 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_TOWER_FAN_SPEED_3,                              /*!< Tower Fan Speed 3 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_ZONE_HEATING_STAGE_1,                           /*!< Zone Heating Stage 1 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_ZONE_HEATING_STAGE_2,                           /*!< Zone Heating Stage 2 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_ZONE_HEATING_STAGE_3,                           /*!< Zone Heating Stage 3 BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_ZONE_HEATING_VALVE,                             /*!< Zone Heating Valve BO */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_2_PIPE_CIRCULATION_PUMP_2,                      /*!< 2 Pipe Circulation Pump BO */
    /* 0x0200 to 0xFFFE are Vendor defined */
    ESP_ZB_ZCL_BO_DOMAIN_HVAC_OTHER =
        ESP_ZB_ZCL_BO_SET_APP_TYPE_WITH_ID(ESP_ZB_ZCL_BO_APP_TYPE_DOMAIN_HVAC, 0xFFFF) /*!< Other */
} esp_zb_zcl_bo_domain_hvac_t;

/** @brief Values for Binary Output cluster Security application usages */
typedef enum {
    ESP_ZB_ZCL_BO_DOMAIN_SECURITY_ARM_DISARM_COMMAND = ESP_ZB_ZCL_BO_SET_APP_TYPE_WITH_ID(0x02, 0x0000), /*!< Arm Disarm Command BO */
    ESP_ZB_ZCL_BO_DOMAIN_SECURITY_OCCUPANCY_CONTROL,                                                     /*!< Occupancy Control BO */
    ESP_ZB_ZCL_BO_DOMAIN_SECURITY_ENABLE_CONTROL,                                                        /*!< Enable Control BO */
    ESP_ZB_ZCL_BO_DOMAIN_SECURITY_ACCESS_CONTROL,                                                        /*!< Access Control BO */
    /* 0x0200 to 0xFFFE are Vendor defined */
    ESP_ZB_ZCL_BO_DOMAIN_SECURITY_OTHER = ESP_ZB_ZCL_BO_SET_APP_TYPE_WITH_ID(0x02, 0xFFFF) /*!< Other */
} esp_zb_zcl_bo_domain_security_t;

void esp_zb_zcl_binary_output_init_server(void);
void esp_zb_zcl_binary_output_init_client(void);

#define ESP_ZB_ZCL_CLUSTER_ID_BINARY_OUTPUT_SERVER_ROLE_INIT esp_zb_zcl_binary_output_init_server
#define ESP_ZB_ZCL_CLUSTER_ID_BINARY_OUTPUT_CLIENT_ROLE_INIT esp_zb_zcl_binary_output_init_client

#ifdef __cplusplus
}
#endif
