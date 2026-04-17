/*
 * SPDX-FileCopyrightText: 2025-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/zcl.h" instead!"

#include <ezbee/aps.h>
#include <ezbee/af.h>
#include <ezbee/zcl/zcl_type.h>
#include <ezbee/zcl/zcl_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/* BreakChange: Not supported now */
#define esp_zb_zcl_put_attribute_value(data_ptr, type, value, value_size) (data_ptr)


/** Non manufacturer specific code for certain attribute */
#define ESP_ZB_ZCL_ATTR_NON_MANUFACTURER_SPECIFIC EZB_ZCL_STD_MANUF_CODE
/** Non manufacturer specific code for certain cluster */
#define EZP_ZB_ZCL_CLUSTER_NON_MANUFACTURER_SPECIFIC EZB_ZCL_STD_MANUF_CODE

/** Defined the ZCL command of address_mode */
typedef ezb_aps_address_mode_t esp_zb_zcl_address_mode_t;

/**
 * @brief Application Framework Profile identifiers.
 *
 */
typedef enum {
    ESP_ZB_AF_HA_PROFILE_ID  = EZB_AF_HA_PROFILE_ID, /** HA profile ID */
    ESP_ZB_AF_SE_PROFILE_ID  = EZB_AF_SE_PROFILE_ID, /** SE profile ID */
    ESP_ZB_AF_ZLL_PROFILE_ID = EZB_AF_TL_PROFILE_ID, /** ZLL profile ID */
    ESP_ZB_AF_GP_PROFILE_ID  = EZB_AF_GP_PROFILE_ID, /** GreenPower profile ID */
} esp_zb_af_profile_id_t;

/** @brief HA Device identifiers.
 */
typedef enum {
    ESP_ZB_HA_ON_OFF_SWITCH_DEVICE_ID              = 0x0000, /*!< General On/Off switch */
    ESP_ZB_HA_LEVEL_CONTROL_SWITCH_DEVICE_ID       = 0x0001, /*!< Level Control Switch  */
    ESP_ZB_HA_ON_OFF_OUTPUT_DEVICE_ID              = 0x0002, /*!< General On/Off output */
    ESP_ZB_HA_LEVEL_CONTROLLABLE_OUTPUT_DEVICE_ID  = 0x0003, /*!< Level Controllable Output */
    ESP_ZB_HA_SCENE_SELECTOR_DEVICE_ID             = 0x0004, /*!< Scene Selector */
    ESP_ZB_HA_CONFIGURATION_TOOL_DEVICE_ID         = 0x0005, /*!< Configuration Tool */
    ESP_ZB_HA_REMOTE_CONTROL_DEVICE_ID             = 0x0006, /*!< Remote Control */
    ESP_ZB_HA_COMBINED_INTERFACE_DEVICE_ID         = 0x0007, /*!< Combined Interface */
    ESP_ZB_HA_RANGE_EXTENDER_DEVICE_ID             = 0x0008, /*!< Range Extender */
    ESP_ZB_HA_MAINS_POWER_OUTLET_DEVICE_ID         = 0x0009, /*!< Mains Power Outlet */
    ESP_ZB_HA_DOOR_LOCK_DEVICE_ID                  = 0x000A, /*!< Door lock client */
    ESP_ZB_HA_DOOR_LOCK_CONTROLLER_DEVICE_ID       = 0x000B, /*!< Door lock controller */
    ESP_ZB_HA_SIMPLE_SENSOR_DEVICE_ID              = 0x000C, /*!< Simple Sensor device */
    ESP_ZB_HA_CONSUMPTION_AWARENESS_DEVICE_ID      = 0x000D, /*!< Consumption Awareness Device */
    ESP_ZB_HA_HOME_GATEWAY_DEVICE_ID               = 0x0050, /*!< Home Gateway */
    ESP_ZB_HA_SMART_PLUG_DEVICE_ID                 = 0x0051, /*!< Smart plug */
    ESP_ZB_HA_WHITE_GOODS_DEVICE_ID                = 0x0052, /*!< White Goods */
    ESP_ZB_HA_METER_INTERFACE_DEVICE_ID            = 0x0053, /*!< Meter Interface */
    ESP_ZB_HA_ON_OFF_LIGHT_DEVICE_ID               = 0x0100, /*!< On/Off Light Device */
    ESP_ZB_HA_DIMMABLE_LIGHT_DEVICE_ID             = 0x0101, /*!< Dimmable Light Device */
    ESP_ZB_HA_COLOR_DIMMABLE_LIGHT_DEVICE_ID       = 0x0102, /*!< Color Dimmable Light Device */
    ESP_ZB_HA_DIMMER_SWITCH_DEVICE_ID              = 0x0104, /*!< Dimmer Switch Device */
    ESP_ZB_HA_COLOR_DIMMER_SWITCH_DEVICE_ID        = 0x0105, /*!< Color Dimmer Switch Device */
    ESP_ZB_HA_LIGHT_SENSOR_DEVICE_ID               = 0x0106, /*!< Light Sensor Device */
    ESP_ZB_HA_SHADE_DEVICE_ID                      = 0x0200, /*!< Shade */
    ESP_ZB_HA_SHADE_CONTROLLER_DEVICE_ID           = 0x0201, /*!< Shade controller */
    ESP_ZB_HA_WINDOW_COVERING_DEVICE_ID            = 0x0202, /*!< Window Covering client*/
    ESP_ZB_HA_WINDOW_COVERING_CONTROLLER_DEVICE_ID = 0x0203, /*!< Window Covering controller */
    ESP_ZB_HA_HEATING_COOLING_UNIT_DEVICE_ID       = 0x0300, /*!< Heating/Cooling Unit device */
    ESP_ZB_HA_THERMOSTAT_DEVICE_ID                 = 0x0301, /*!< Thermostat Device */
    ESP_ZB_HA_TEMPERATURE_SENSOR_DEVICE_ID         = 0x0302, /*!< Temperature Sensor */
    ESP_ZB_HA_IAS_CONTROL_INDICATING_EQUIPMENT_ID  = 0x0400, /*!< IAS Control and Indicating Equipment */
    ESP_ZB_HA_IAS_ANCILLARY_CONTROL_EQUIPMENT_ID   = 0x0401, /*!< IAS Ancillary Control Equipment */
    ESP_ZB_HA_IAS_ZONE_ID                          = 0x0402, /*!< IAS Zone */
    ESP_ZB_HA_IAS_WARNING_DEVICE_ID                = 0x0403, /*!< IAS Warning Device */
    ESP_ZB_HA_TEST_DEVICE_ID                       = 0xfff0, /*!< Custom HA device for test */
    ESP_ZB_HA_CUSTOM_TUNNEL_DEVICE_ID              = 0xfff1, /*!< Custom Tunnel device (should declared in private profile) */
    ESP_ZB_HA_CUSTOM_ATTR_DEVICE_ID                = 0xfff2  /*!< Custom Attributes Device */
} esp_zb_ha_standard_devices_t;

/**
 * @brief ZCL cluster role enum
 * @anchor esp_zb_zcl_cluster_role
 */
typedef enum {
    ESP_ZB_ZCL_CLUSTER_SERVER_ROLE = EZB_ZCL_CLUSTER_SERVER, /*!< Server cluster role */
    ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE = EZB_ZCL_CLUSTER_CLIENT, /*!< Client cluster role */
} esp_zb_zcl_cluster_role_t;

/**
 * @brief ZCL cluster identifiers
 * @anchor esp_zb_zcl_cluster_id
 */
#define ESP_ZB_ZCL_CLUSTER_ID_BASIC                      EZB_ZCL_CLUSTER_ID_BASIC
#define ESP_ZB_ZCL_CLUSTER_ID_POWER_CONFIG               EZB_ZCL_CLUSTER_ID_POWER_CONFIG
#define ESP_ZB_ZCL_CLUSTER_ID_DEVICE_TEMP_CONFIG         EZB_ZCL_CLUSTER_ID_DEVICE_TEMP_CONFIG
#define ESP_ZB_ZCL_CLUSTER_ID_IDENTIFY                   EZB_ZCL_CLUSTER_ID_IDENTIFY
#define ESP_ZB_ZCL_CLUSTER_ID_GROUPS                     EZB_ZCL_CLUSTER_ID_GROUPS
#define ESP_ZB_ZCL_CLUSTER_ID_SCENES                     EZB_ZCL_CLUSTER_ID_SCENES
#define ESP_ZB_ZCL_CLUSTER_ID_ON_OFF                     EZB_ZCL_CLUSTER_ID_ON_OFF
#define ESP_ZB_ZCL_CLUSTER_ID_ON_OFF_SWITCH_CONFIG       EZB_ZCL_CLUSTER_ID_ON_OFF_SWITCH_CONFIG
#define ESP_ZB_ZCL_CLUSTER_ID_LEVEL                      EZB_ZCL_CLUSTER_ID_LEVEL
#define ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL              EZB_ZCL_CLUSTER_ID_LEVEL
#define ESP_ZB_ZCL_CLUSTER_ID_ALARMS                     EZB_ZCL_CLUSTER_ID_ALARMS
#define ESP_ZB_ZCL_CLUSTER_ID_TIME                       EZB_ZCL_CLUSTER_ID_TIME
#define ESP_ZB_ZCL_CLUSTER_ID_RSSI_LOCATION              EZB_ZCL_CLUSTER_ID_RSSI_LOCATION
#define ESP_ZB_ZCL_CLUSTER_ID_ANALOG_INPUT               EZB_ZCL_CLUSTER_ID_ANALOG_INPUT
#define ESP_ZB_ZCL_CLUSTER_ID_ANALOG_OUTPUT              EZB_ZCL_CLUSTER_ID_ANALOG_OUTPUT
#define ESP_ZB_ZCL_CLUSTER_ID_ANALOG_VALUE               EZB_ZCL_CLUSTER_ID_ANALOG_VALUE
#define ESP_ZB_ZCL_CLUSTER_ID_BINARY_INPUT               EZB_ZCL_CLUSTER_ID_BINARY_INPUT
#define ESP_ZB_ZCL_CLUSTER_ID_BINARY_OUTPUT              EZB_ZCL_CLUSTER_ID_BINARY_OUTPUT
#define ESP_ZB_ZCL_CLUSTER_ID_BINARY_VALUE               EZB_ZCL_CLUSTER_ID_BINARY_VALUE
#define ESP_ZB_ZCL_CLUSTER_ID_MULTI_INPUT                EZB_ZCL_CLUSTER_ID_MULTISTATE_INPUT
#define ESP_ZB_ZCL_CLUSTER_ID_MULTI_OUTPUT               EZB_ZCL_CLUSTER_ID_MULTISTATE_OUTPUT
#define ESP_ZB_ZCL_CLUSTER_ID_MULTI_VALUE                EZB_ZCL_CLUSTER_ID_MULTISTATE_VALUE
#define ESP_ZB_ZCL_CLUSTER_ID_COMMISSIONING              EZB_ZCL_CLUSTER_ID_COMMISSIONING
#define ESP_ZB_ZCL_CLUSTER_ID_OTA_UPGRADE                EZB_ZCL_CLUSTER_ID_OTA_UPGRADE
#define ESP_ZB_ZCL_CLUSTER_ID_POLL_CONTROL               EZB_ZCL_CLUSTER_ID_POLL_CONTROL
#define ESP_ZB_ZCL_CLUSTER_ID_GREEN_POWER                EZB_ZCL_CLUSTER_ID_GREEN_POWER
#define ESP_ZB_ZCL_CLUSTER_ID_KEEP_ALIVE                 EZB_ZCL_CLUSTER_ID_KEEP_ALIVE
#define ESP_ZB_ZCL_CLUSTER_ID_SHADE_CONFIG               EZB_ZCL_CLUSTER_ID_SHADE_CONFIG
#define ESP_ZB_ZCL_CLUSTER_ID_DOOR_LOCK                  EZB_ZCL_CLUSTER_ID_DOOR_LOCK
#define ESP_ZB_ZCL_CLUSTER_ID_WINDOW_COVERING            EZB_ZCL_CLUSTER_ID_WINDOW_COVERING
#define ESP_ZB_ZCL_CLUSTER_ID_PUMP_CONFIG_CONTROL        EZB_ZCL_CLUSTER_ID_PUMP_CONFIG_CONTROL
#define ESP_ZB_ZCL_CLUSTER_ID_THERMOSTAT                 EZB_ZCL_CLUSTER_ID_THERMOSTAT
#define ESP_ZB_ZCL_CLUSTER_ID_FAN_CONTROL                EZB_ZCL_CLUSTER_ID_FAN_CONTROL
#define ESP_ZB_ZCL_CLUSTER_ID_DEHUMIDIFICATION_CONTROL   EZB_ZCL_CLUSTER_ID_DEHUMIDIFICATION_CONTROL
#define ESP_ZB_ZCL_CLUSTER_ID_THERMOSTAT_UI_CONFIG       EZB_ZCL_CLUSTER_ID_THERMOSTAT_UI_CONFIG
#define ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL              EZB_ZCL_CLUSTER_ID_COLOR_CONTROL
#define ESP_ZB_ZCL_CLUSTER_ID_BALLAST_CONFIG             EZB_ZCL_CLUSTER_ID_BALLAST_CONFIG
#define ESP_ZB_ZCL_CLUSTER_ID_ILLUMINANCE_MEASUREMENT    EZB_ZCL_CLUSTER_ID_ILLUMINANCE_MEASUREMENT
#define ESP_ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT           EZB_ZCL_CLUSTER_ID_TEMPERATURE_MEASUREMENT
#define ESP_ZB_ZCL_CLUSTER_ID_PRESSURE_MEASUREMENT       EZB_ZCL_CLUSTER_ID_PRESSURE_MEASUREMENT
#define ESP_ZB_ZCL_CLUSTER_ID_FLOW_MEASUREMENT           EZB_ZCL_CLUSTER_ID_FLOW_MEASUREMENT
#define ESP_ZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT   EZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT
#define ESP_ZB_ZCL_CLUSTER_ID_OCCUPANCY_SENSING          EZB_ZCL_CLUSTER_ID_OCCUPANCY_SENSING
#define ESP_ZB_ZCL_CLUSTER_ID_PH_MEASUREMENT             EZB_ZCL_CLUSTER_ID_PH_MEASUREMENT
#define ESP_ZB_ZCL_CLUSTER_ID_EC_MEASUREMENT             EZB_ZCL_CLUSTER_ID_EC_MEASUREMENT
#define ESP_ZB_ZCL_CLUSTER_ID_WIND_SPEED_MEASUREMENT     EZB_ZCL_CLUSTER_ID_WIND_SPEED_MEASUREMENT
#define ESP_ZB_ZCL_CLUSTER_ID_CARBON_DIOXIDE_MEASUREMENT EZB_ZCL_CLUSTER_ID_CARBON_DIOXIDE_MEASUREMENT
#define ESP_ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT          EZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT
#define ESP_ZB_ZCL_CLUSTER_ID_IAS_ZONE                   EZB_ZCL_CLUSTER_ID_IAS_ZONE
#define ESP_ZB_ZCL_CLUSTER_ID_IAS_ACE                    EZB_ZCL_CLUSTER_ID_IAS_ACE
#define ESP_ZB_ZCL_CLUSTER_ID_IAS_WD                     EZB_ZCL_CLUSTER_ID_IAS_WD
#define ESP_ZB_ZCL_CLUSTER_ID_PRICE                      EZB_ZCL_CLUSTER_ID_PRICE
#define ESP_ZB_ZCL_CLUSTER_ID_DRLC                       EZB_ZCL_CLUSTER_ID_DRLC
#define ESP_ZB_ZCL_CLUSTER_ID_METERING                   EZB_ZCL_CLUSTER_ID_METERING
#define ESP_ZB_ZCL_CLUSTER_ID_TUNNEL                     EZB_ZCL_CLUSTER_ID_TUNNEL
#define ESP_ZB_ZCL_CLUSTER_ID_METER_IDENTIFICATION       EZB_ZCL_CLUSTER_ID_METER_IDENTIFICATION
#define ESP_ZB_ZCL_CLUSTER_ID_ELECTRICAL_MEASUREMENT     EZB_ZCL_CLUSTER_ID_ELECTRICAL_MEASUREMENT
#define ESP_ZB_ZCL_CLUSTER_ID_DIAGNOSTICS                EZB_ZCL_CLUSTER_ID_DIAGNOSTICS
typedef ezb_zcl_cluster_id_t esp_zb_zcl_cluster_id_t;

/**
 * @brief ZCL status values
 * @anchor esp_zb_zcl_status
 */
#define ESP_ZB_ZCL_STATUS_SUCCESS              EZB_ZCL_STATUS_SUCCESS
#define ESP_ZB_ZCL_STATUS_FAIL                 EZB_ZCL_STATUS_FAIL
#define ESP_ZB_ZCL_STATUS_NOT_AUTHORIZED       EZB_ZCL_STATUS_NOT_AUTHORIZED
#define ESP_ZB_ZCL_STATUS_MALFORMED_CMD        EZB_ZCL_STATUS_MALFORMED_CMD
#define ESP_ZB_ZCL_STATUS_UNSUP_CMD            EZB_ZCL_STATUS_UNSUP_CMD
#define ESP_ZB_ZCL_STATUS_INVALID_FIELD        EZB_ZCL_STATUS_INVALID_FIELD
#define ESP_ZB_ZCL_STATUS_UNSUP_ATTRIB         EZB_ZCL_STATUS_UNSUP_ATTRIB
#define ESP_ZB_ZCL_STATUS_INVALID_VALUE        EZB_ZCL_STATUS_INVALID_VALUE
#define ESP_ZB_ZCL_STATUS_READ_ONLY            EZB_ZCL_STATUS_READ_ONLY
#define ESP_ZB_ZCL_STATUS_INSUFFICIENT_SPACE   EZB_ZCL_STATUS_INSUFFICIENT_SPACE
#define ESP_ZB_ZCL_STATUS_NOT_FOUND            EZB_ZCL_STATUS_NOT_FOUND
#define ESP_ZB_ZCL_STATUS_UNREPORTBLE_ATTRIB   EZB_ZCL_STATUS_UNREPORTBLE_ATTRIB
#define ESP_ZB_ZCL_STATUS_INVALID_TYPE         EZB_ZCL_STATUS_INVALID_TYPE
#define ESP_ZB_ZCL_STATUS_INCONSISTENT         EZB_ZCL_STATUS_INCONSISTENT
#define ESP_ZB_ZCL_STATUS_ACTION_DENIED        EZB_ZCL_STATUS_ACTION_DENIED
#define ESP_ZB_ZCL_STATUS_TIMEOUT              EZB_ZCL_STATUS_TIMEOUT
#define ESP_ZB_ZCL_STATUS_ABORT                EZB_ZCL_STATUS_ABORT
#define ESP_ZB_ZCL_STATUS_INVALID_IMAGE        EZB_ZCL_STATUS_INVALID_IMAGE
#define ESP_ZB_ZCL_STATUS_WAIT_FOR_DATA        EZB_ZCL_STATUS_WAIT_FOR_DATA
#define ESP_ZB_ZCL_STATUS_NO_IMAGE_AVAILABLE   EZB_ZCL_STATUS_NO_IMAGE_AVAILABLE
#define ESP_ZB_ZCL_STATUS_REQUIRE_MORE_IMAGE   EZB_ZCL_STATUS_REQUIRE_MORE_IMAGE
#define ESP_ZB_ZCL_STATUS_NOTIFICATION_PENDING EZB_ZCL_STATUS_NOTIFICATION_PENDING
#define ESP_ZB_ZCL_STATUS_HW_FAIL              0xc0U
#define ESP_ZB_ZCL_STATUS_SW_FAIL              0xc1U
#define ESP_ZB_ZCL_STATUS_CALIB_ERR            EZB_ZCL_STATUS_CALIBRATION_ERROR
#define ESP_ZB_ZCL_STATUS_UNSUP_CLUST          EZB_ZCL_STATUS_UNSUPPORTED_CLUSTER
#define ESP_ZB_ZCL_STATUS_LIMIT_REACHED        0xc4U
typedef ezb_zcl_status_t esp_zb_zcl_status_t;

/**
 * @brief ZCL attribute data type values
 * @anchor esp_zb_zcl_attr_type
 */
#define ESP_ZB_ZCL_ATTR_TYPE_NULL              EZB_ZCL_ATTR_TYPE_NO_DATA
#define ESP_ZB_ZCL_ATTR_TYPE_8BIT              EZB_ZCL_ATTR_TYPE_DATA8
#define ESP_ZB_ZCL_ATTR_TYPE_16BIT             EZB_ZCL_ATTR_TYPE_DATA16
#define ESP_ZB_ZCL_ATTR_TYPE_24BIT             EZB_ZCL_ATTR_TYPE_DATA24
#define ESP_ZB_ZCL_ATTR_TYPE_32BIT             EZB_ZCL_ATTR_TYPE_DATA32
#define ESP_ZB_ZCL_ATTR_TYPE_40BIT             EZB_ZCL_ATTR_TYPE_DATA40
#define ESP_ZB_ZCL_ATTR_TYPE_48BIT             EZB_ZCL_ATTR_TYPE_DATA48
#define ESP_ZB_ZCL_ATTR_TYPE_56BIT             EZB_ZCL_ATTR_TYPE_DATA56
#define ESP_ZB_ZCL_ATTR_TYPE_64BIT             EZB_ZCL_ATTR_TYPE_DATA64
#define ESP_ZB_ZCL_ATTR_TYPE_BOOL              EZB_ZCL_ATTR_TYPE_BOOL
#define ESP_ZB_ZCL_ATTR_TYPE_8BITMAP           EZB_ZCL_ATTR_TYPE_MAP8
#define ESP_ZB_ZCL_ATTR_TYPE_16BITMAP          EZB_ZCL_ATTR_TYPE_MAP16
#define ESP_ZB_ZCL_ATTR_TYPE_24BITMAP          EZB_ZCL_ATTR_TYPE_MAP24
#define ESP_ZB_ZCL_ATTR_TYPE_32BITMAP          EZB_ZCL_ATTR_TYPE_MAP32
#define ESP_ZB_ZCL_ATTR_TYPE_40BITMAP          EZB_ZCL_ATTR_TYPE_MAP40
#define ESP_ZB_ZCL_ATTR_TYPE_48BITMAP          EZB_ZCL_ATTR_TYPE_MAP48
#define ESP_ZB_ZCL_ATTR_TYPE_56BITMAP          EZB_ZCL_ATTR_TYPE_MAP56
#define ESP_ZB_ZCL_ATTR_TYPE_64BITMAP          EZB_ZCL_ATTR_TYPE_MAP64
#define ESP_ZB_ZCL_ATTR_TYPE_U8                EZB_ZCL_ATTR_TYPE_UINT8
#define ESP_ZB_ZCL_ATTR_TYPE_U16               EZB_ZCL_ATTR_TYPE_UINT16
#define ESP_ZB_ZCL_ATTR_TYPE_U24               EZB_ZCL_ATTR_TYPE_UINT24
#define ESP_ZB_ZCL_ATTR_TYPE_U32               EZB_ZCL_ATTR_TYPE_UINT32
#define ESP_ZB_ZCL_ATTR_TYPE_U40               EZB_ZCL_ATTR_TYPE_UINT40
#define ESP_ZB_ZCL_ATTR_TYPE_U48               EZB_ZCL_ATTR_TYPE_UINT48
#define ESP_ZB_ZCL_ATTR_TYPE_U56               EZB_ZCL_ATTR_TYPE_UINT56
#define ESP_ZB_ZCL_ATTR_TYPE_U64               EZB_ZCL_ATTR_TYPE_UINT64
#define ESP_ZB_ZCL_ATTR_TYPE_S8                EZB_ZCL_ATTR_TYPE_INT8
#define ESP_ZB_ZCL_ATTR_TYPE_S16               EZB_ZCL_ATTR_TYPE_INT16
#define ESP_ZB_ZCL_ATTR_TYPE_S24               EZB_ZCL_ATTR_TYPE_INT24
#define ESP_ZB_ZCL_ATTR_TYPE_S32               EZB_ZCL_ATTR_TYPE_INT32
#define ESP_ZB_ZCL_ATTR_TYPE_S40               EZB_ZCL_ATTR_TYPE_INT40
#define ESP_ZB_ZCL_ATTR_TYPE_S48               EZB_ZCL_ATTR_TYPE_INT48
#define ESP_ZB_ZCL_ATTR_TYPE_S56               EZB_ZCL_ATTR_TYPE_INT56
#define ESP_ZB_ZCL_ATTR_TYPE_S64               EZB_ZCL_ATTR_TYPE_INT64
#define ESP_ZB_ZCL_ATTR_TYPE_8BIT_ENUM         EZB_ZCL_ATTR_TYPE_ENUM8
#define ESP_ZB_ZCL_ATTR_TYPE_16BIT_ENUM        EZB_ZCL_ATTR_TYPE_ENUM16
#define ESP_ZB_ZCL_ATTR_TYPE_SEMI              EZB_ZCL_ATTR_TYPE_SEMI
#define ESP_ZB_ZCL_ATTR_TYPE_SINGLE            EZB_ZCL_ATTR_TYPE_SINGLE
#define ESP_ZB_ZCL_ATTR_TYPE_DOUBLE            EZB_ZCL_ATTR_TYPE_DOUBLE
#define ESP_ZB_ZCL_ATTR_TYPE_OCTET_STRING      EZB_ZCL_ATTR_TYPE_OCTSTR
#define ESP_ZB_ZCL_ATTR_TYPE_CHAR_STRING       EZB_ZCL_ATTR_TYPE_STRING
#define ESP_ZB_ZCL_ATTR_TYPE_LONG_OCTET_STRING EZB_ZCL_ATTR_TYPE_OCTSTR16
#define ESP_ZB_ZCL_ATTR_TYPE_LONG_CHAR_STRING  EZB_ZCL_ATTR_TYPE_STRING16
#define ESP_ZB_ZCL_ATTR_TYPE_ARRAY             EZB_ZCL_ATTR_TYPE_ARRAY
#define ESP_ZB_ZCL_ATTR_TYPE_16BIT_ARRAY       EZB_ZCL_ATTR_TYPE_ARRAY_DATA16
#define ESP_ZB_ZCL_ATTR_TYPE_32BIT_ARRAY       EZB_ZCL_ATTR_TYPE_ARRAY_DATA32
#define ESP_ZB_ZCL_ATTR_TYPE_STRUCTURE         EZB_ZCL_ATTR_TYPE_STRUCT
#define ESP_ZB_ZCL_ATTR_TYPE_SET               EZB_ZCL_ATTR_TYPE_SET
#define ESP_ZB_ZCL_ATTR_TYPE_BAG               EZB_ZCL_ATTR_TYPE_BAG
#define ESP_ZB_ZCL_ATTR_TYPE_TIME_OF_DAY       EZB_ZCL_ATTR_TYPE_TOD
#define ESP_ZB_ZCL_ATTR_TYPE_DATE              EZB_ZCL_ATTR_TYPE_DATE
#define ESP_ZB_ZCL_ATTR_TYPE_UTC_TIME          EZB_ZCL_ATTR_TYPE_UTC
#define ESP_ZB_ZCL_ATTR_TYPE_CLUSTER_ID        EZB_ZCL_ATTR_TYPE_CLUSTER_ID
#define ESP_ZB_ZCL_ATTR_TYPE_ATTRIBUTE_ID      EZB_ZCL_ATTR_TYPE_ATTRIBUTE_ID
#define ESP_ZB_ZCL_ATTR_TYPE_BACNET_OID        EZB_ZCL_ATTR_TYPE_BAC_OID
#define ESP_ZB_ZCL_ATTR_TYPE_IEEE_ADDR         EZB_ZCL_ATTR_TYPE_IEEE_ADDR
#define ESP_ZB_ZCL_ATTR_TYPE_128_BIT_KEY       EZB_ZCL_ATTR_TYPE_KEY128
#define ESP_ZB_ZCL_ATTR_TYPE_INTERNAL          EZB_ZCL_ATTR_TYPE_INTERNAL
#define ESP_ZB_ZCL_ATTR_TYPE_INVALID           EZB_ZCL_ATTR_TYPE_UNK
typedef ezb_zcl_attr_type_t esp_zb_zcl_attr_type_t;

/**
 * @brief ZCL attribute access values
 * @anchor esp_zb_zcl_attr_access
 */
#define ESP_ZB_ZCL_ATTR_ACCESS_READ_ONLY  EZB_ZCL_ATTR_ACCESS_READ_ONLY
#define ESP_ZB_ZCL_ATTR_ACCESS_WRITE_ONLY EZB_ZCL_ATTR_ACCESS_WRITE_ONLY
#define ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE EZB_ZCL_ATTR_ACCESS_READ_WRITE
#define ESP_ZB_ZCL_ATTR_ACCESS_REPORTING  EZB_ZCL_ATTR_ACCESS_REPORTING
#define ESP_ZB_ZCL_ATTR_ACCESS_SINGLETON  0x08U
#define ESP_ZB_ZCL_ATTR_ACCESS_SCENE      EZB_ZCL_ATTR_ACCESS_SCENE
#define ESP_ZB_ZCL_ATTR_MANUF_SPEC        0x20U
#define ESP_ZB_ZCL_ATTR_ACCESS_INTERNAL   0x40U
typedef ezb_zcl_attr_access_t esp_zb_zcl_attr_access_t;
/**
 * @brief ZCL command direction enum
 * @anchor esp_zb_zcl_cmd_direction
 */
enum esp_zb_zcl_cmd_direction_s {
    ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV = EZB_ZCL_CMD_DIRECTION_TO_SRV, /*!< Command for cluster server side */
    ESP_ZB_ZCL_CMD_DIRECTION_TO_CLI = EZB_ZCL_CMD_DIRECTION_TO_CLI, /*!< Command for cluster client side */
};
typedef uint8_t esp_zb_zcl_cmd_direction_t;

/**
 * @brief ZCL report direction enum of attribute
 * @anchor esp_zb_zcl_report_direction_t
 */
enum esp_zb_zcl_report_direction_s {
    ESP_ZB_ZCL_REPORT_DIRECTION_SEND = EZB_ZCL_REPORTING_SEND, /**< Report should be sent by a cluster. */
    ESP_ZB_ZCL_REPORT_DIRECTION_RECV = EZB_ZCL_REPORTING_RECV, /**< Report should be received by a cluster. */
};
typedef uint8_t esp_zb_zcl_report_direction_t;

/**
 * @brief The Zigbee zcl cluster attribute value struct
 *
 */
typedef struct esp_zb_zcl_attribute_data_s {
    uint8_t  type;  /*!< The type of attribute, which can refer to esp_zb_zcl_attr_type_t */
    uint16_t size;  /*!< The value size of attribute  */
    void    *value; /*!< The value of attribute, Note that if the type is string/array, the first byte of value indicates the
                       string length */
} esp_zb_zcl_attribute_data_t;

/**
 * @brief The Zigbee zcl cluster attribute struct
 *
 */
typedef ezb_zcl_attribute_t esp_zb_zcl_attribute_t;

/**
 * @brief The Zigbee zcl cluster command properties struct
 *
 */
typedef struct esp_zb_zcl_command_s {
    uint8_t id;        /*!< The command id */
    uint8_t direction; /*!< The command direction */
    uint8_t is_common; /*!< The command is common type */
} esp_zb_zcl_command_t;

/**
 * @brief The Zigbee ZCL basic command info
 *
 */
typedef struct esp_zb_zcl_basic_cmd_s {
    esp_zb_addr_u dst_addr_u;   /*!< Single short address or group address */
    uint8_t       dst_endpoint; /*!< Destination endpoint */
    uint8_t       src_endpoint; /*!< Source endpoint */
} esp_zb_zcl_basic_cmd_t;

/**
 * @brief The Zigbee ZCL command common struct, no command specific payload
 *
 */
typedef struct esp_zb_zcl_common_cmd_s {
    esp_zb_zcl_basic_cmd_t    zcl_basic_cmd; /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;  /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
} esp_zb_zcl_common_cmd_t;

/**
 * @brief The Zigbee zcl cluster device callback common information
 *
 */
typedef struct esp_zb_device_cb_common_info_s {
    esp_zb_zcl_status_t status;       /*!< The operation status of ZCL, refer to esp_zb_zcl_status_t */
    uint8_t             dst_endpoint; /*!< The destination endpoint id of the ZCL indication */
    uint16_t            cluster;      /*!< The cluster id of the ZCL indication */
} esp_zb_device_cb_common_info_t;

/**
 * @brief The frame header of Zigbee zcl command struct
 *
 * @note frame control field:
 * |----1 bit---|---------1 bit---------|---1 bit---|----------1 bit-----------|---4 bit---|
 * | Frame type | Manufacturer specific | Direction | Disable Default Response | Reserved  |
 *
 */
typedef struct esp_zb_zcl_frame_header_s {
    uint8_t  fc;         /*!< A 8-bit Frame control */
    uint16_t manuf_code; /*!< Manufacturer code */
    uint8_t  tsn;        /*!< Transaction sequence number */
    int8_t   rssi;       /*!< Signal strength */
} esp_zb_zcl_frame_header_t;

/**
 * @brief The Zigbee zcl command basic application information struct
 *
 */
typedef struct esp_zb_zcl_cmd_info_s {
    esp_zb_zcl_status_t status;       /*!< The status of command, which can refer to  esp_zb_zcl_status_t */
    esp_zb_zcl_frame_header_t header; /*!< The command frame properties, which can refer to esp_zb_zcl_frame_field_t */
    esp_zb_zcl_addr_t src_address;    /*!< The struct of address contains short and ieee address, which can refer to esp_zb_zcl_addr_s */
    uint16_t dst_address;             /*!< The destination short address of command */
    uint8_t src_endpoint;             /*!< The source endpoint of command */
    uint8_t dst_endpoint;             /*!< The destination endpoint of command */
    uint16_t cluster;                 /*!< The cluster id for command */
    uint16_t profile;                 /*!< The application profile identifier*/
    esp_zb_zcl_command_t command;     /*!< The properties of command */
} esp_zb_zcl_cmd_info_t;

/**
 * @brief The ZCL attribute location information struct
 *
 */
typedef struct esp_zb_zcl_attr_location_info_s {
    uint8_t  endpoint_id;  /*!< The endpoint identifier on which the cluster id is resident. */
    uint16_t cluster_id;   /*!< The cluster identifier on which the attribute is resident, refer to esp_zb_zcl_cluster_id_t */
    uint8_t  cluster_role; /*!< The role of cluster, refer to esp_zb_zcl_cluster_role_t */
    uint16_t manuf_code;   /*!< The manufacturer code of attribute */
    uint16_t attr_id;      /*!< The attribute identifier */
} esp_zb_zcl_attr_location_info_t;

/**
 * @brief ZCL Cluster Check Attribute Value Handler, which should be called before attribute change and checks if new value is
 * in correct range and can be applied.
 *
 * @param[in] attr_id  ZCL Attribute ID
 * @param[in] endpoint Device endpoint
 * @param[in] value    Pointer to the new Attribute Value
 *
 * @return The result of check value whose value refer to esp_err_t
 */
typedef ezb_zcl_custom_cluster_check_value_t esp_zb_zcl_cluster_check_value_callback_t;

/**
 * @brief ZCL Cluster Write Attribute Handler, which should be called before attribute change (if any cluster-specific action
 * needs to be bound to attribute change, it can be placed in this handler).
 *
 * @param[in] endpoint   Device endpoint
 * @param[in] attr_id    ZCL Attribute ID
 * @param[in] new_value  Pointer to the new Attribute Value
 * @param[in] manuf_code Manufacturer specific code
 */
typedef ezb_zcl_custom_cluster_write_attr_t esp_zb_zcl_cluster_write_attr_callback_t;

#define esp_zb_zcl_get_attribute_size(attr_type, attr_value) ezb_zcl_get_attr_value_size(attr_type, attr_value)

#ifdef __cplusplus
}
#endif

#else
#error "This file is for compatibility, please include "ezbee/zcl.h"!"
#endif
