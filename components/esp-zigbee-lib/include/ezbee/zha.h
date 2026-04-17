/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Below definitions are based on Zigbee Home Automation Specification, Revision 29, Version 1.2 */

/**
 * @brief Zigbee Home Automation (ZHA) device identifiers.
 * @anchor ezb_zha_device_id_t
 */
enum {
    /* Standard */
    /* Generic Devices */
    EZB_ZHA_ON_OFF_SWITCH_DEVICE_ID              = 0x0000, /*!< General On/Off switch */
    EZB_ZHA_LEVEL_CONTROL_SWITCH_DEVICE_ID       = 0x0001, /*!< Level Control Switch  */
    EZB_ZHA_ON_OFF_OUTPUT_DEVICE_ID              = 0x0002, /*!< General On/Off output */
    EZB_ZHA_LEVEL_CONTROLLABLE_OUTPUT_DEVICE_ID  = 0x0003, /*!< Level Controllable Output */
    EZB_ZHA_SCENE_SELECTOR_DEVICE_ID             = 0x0004, /*!< Scene Selector */
    EZB_ZHA_CONFIGURATION_TOOL_DEVICE_ID         = 0x0005, /*!< Configuration Tool */
    EZB_ZHA_REMOTE_CONTROL_DEVICE_ID             = 0x0006, /*!< Remote Control */
    EZB_ZHA_COMBINED_INTERFACE_DEVICE_ID         = 0x0007, /*!< Combined Interface */
    EZB_ZHA_RANGE_EXTENDER_DEVICE_ID             = 0x0008, /*!< Range Extender */
    EZB_ZHA_MAINS_POWER_OUTLET_DEVICE_ID         = 0x0009, /*!< Mains Power Outlet */
    EZB_ZHA_DOOR_LOCK_DEVICE_ID                  = 0x000A, /*!< Door lock client */
    EZB_ZHA_DOOR_LOCK_CONTROLLER_DEVICE_ID       = 0x000B, /*!< Door lock controller */
    EZB_ZHA_SIMPLE_SENSOR_DEVICE_ID              = 0x000C, /*!< Simple Sensor device */
    EZB_ZHA_CONSUMPTION_AWARENESS_DEVICE_ID      = 0x000D, /*!< Consumption Awareness Device */
    EZB_ZHA_HOME_GATEWAY_DEVICE_ID               = 0x0050, /*!< Home Gateway */
    EZB_ZHA_SMART_PLUG_DEVICE_ID                 = 0x0051, /*!< Smart plug */
    EZB_ZHA_WHITE_GOODS_DEVICE_ID                = 0x0052, /*!< White Goods */
    EZB_ZHA_METER_INTERFACE_DEVICE_ID            = 0x0053, /*!< Meter Interface */
    /* Lighting Devices */
    EZB_ZHA_ON_OFF_LIGHT_DEVICE_ID               = 0x0100, /*!< On/Off Light Device */
    EZB_ZHA_DIMMABLE_LIGHT_DEVICE_ID             = 0x0101, /*!< Dimmable Light Device */
    EZB_ZHA_COLOR_DIMMABLE_LIGHT_DEVICE_ID       = 0x0102, /*!< Color Dimmable Light Device */
    EZB_ZHA_ON_OFF_LIGHT_SWITCH_DEVICE_ID        = 0x0103, /*!< On/Off Light Switch Device */
    EZB_ZHA_DIMMER_SWITCH_DEVICE_ID              = 0x0104, /*!< Dimmer Switch Device */
    EZB_ZHA_COLOR_DIMMER_SWITCH_DEVICE_ID        = 0x0105, /*!< Color Dimmer Switch Device */
    EZB_ZHA_LIGHT_SENSOR_DEVICE_ID               = 0x0106, /*!< Light Sensor Device */
    EZB_ZHA_OCCUPANCY_SENSOR_DEVICE_ID           = 0x0107, /*!< Occupancy Sensor Device */
    /* Closures Devices */
    EZB_ZHA_SHADE_DEVICE_ID                      = 0x0200, /*!< Shade */
    EZB_ZHA_SHADE_CONTROLLER_DEVICE_ID           = 0x0201, /*!< Shade controller */
    EZB_ZHA_WINDOW_COVERING_DEVICE_ID            = 0x0202, /*!< Window Covering client*/
    EZB_ZHA_WINDOW_COVERING_CONTROLLER_DEVICE_ID = 0x0203, /*!< Window Covering controller */
    /* HVAC Devices */
    EZB_ZHA_HEATING_COOLING_UNIT_DEVICE_ID       = 0x0300, /*!< Heating/Cooling Unit device */
    EZB_ZHA_THERMOSTAT_DEVICE_ID                 = 0x0301, /*!< Thermostat Device */
    EZB_ZHA_TEMPERATURE_SENSOR_DEVICE_ID         = 0x0302, /*!< Temperature Sensor */
    EZB_ZHA_PUMP_DEVICE_ID                       = 0x0303, /*!< Pump Device */
    EZB_ZHA_PUMP_CONTROLLER_DEVICE_ID            = 0x0304, /*!< Pump Controller Device */
    EZB_ZHA_PRESSURE_SENSOR_DEVICE_ID            = 0x0305, /*!< Pressure Sensor Device */
    EZB_ZHA_FLOW_SENSOR_DEVICE_ID                = 0x0306, /*!< Flow Sensor Device */
    EZB_ZHA_MINI_SPLIT_AC_DEVICE_ID              = 0x0307, /*!< Mini Split AC Device */
    /* Intruder Alarm System Devices */
    EZB_ZHA_IAS_CONTROL_INDICATING_EQUIPMENT_ID  = 0x0400, /*!< IAS Control and Indicating Equipment */
    EZB_ZHA_IAS_ANCILLARY_CONTROL_EQUIPMENT_ID   = 0x0401, /*!< IAS Ancillary Control Equipment */
    EZB_ZHA_IAS_ZONE_ID                          = 0x0402, /*!< IAS Zone */
    EZB_ZHA_IAS_WARNING_DEVICE_ID                = 0x0403, /*!< IAS Warning Device */
    /* Custom */
    EZB_ZHA_CUSTOM_GATEWAY_DEVICE_ID = 0xff00, /*!< Custom Gateway Device */
};

/**
 * @brief Zigbee Home Automation (ZHA) device ID type.
 */
typedef uint16_t ezb_zha_device_id_t;

/**
 * @brief Zigbee Home Automation (ZHA) common device configuration.
 *
 */
#define EZB_ZHA_COMMON_DEVICE_CONFIG()                                     \
    {                                                                      \
        .basic_cfg =                                                       \
            {                                                              \
                .zcl_version  = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,   \
                .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,  \
            },                                                             \
        .identify_cfg = {                                                  \
            .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE, \
        },                                                                 \
    }

/**
 * @brief Zigbee Home Automation (ZHA) Custom Gateway device configuration.
 *
 */
#define EZB_ZHA_CUSTOM_GATEWAY_CONFIG() EZB_ZHA_COMMON_DEVICE_CONFIG()

/**
 * @brief Zigbee Home Automation (ZHA) On/Off Light device configuration.
 *
 */
#define EZB_ZHA_ON_OFF_LIGHT_CONFIG()                                              \
    {                                                                              \
        .basic_cfg =                                                               \
            {                                                                      \
                .zcl_version  = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,           \
                .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,          \
            },                                                                     \
        .identify_cfg =                                                            \
            {                                                                      \
                .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,     \
            },                                                                     \
        .groups_cfg =                                                              \
            {                                                                      \
                .name_support = EZB_ZCL_GROUPS_NAME_SUPPORT_DEFAULT_VALUE,         \
            },                                                                     \
        .scenes_cfg =                                                              \
            {                                                                      \
                .scene_count      = EZB_ZCL_SCENES_SCENE_COUNT_DEFAULT_VALUE,      \
                .current_scene    = EZB_ZCL_SCENES_CURRENT_SCENE_DEFAULT_VALUE,    \
                .current_group    = EZB_ZCL_SCENES_CURRENT_GROUP_DEFAULT_VALUE,    \
                .scene_valid      = EZB_ZCL_SCENES_SCENE_VALID_DEFAULT_VALUE,      \
                .name_support     = EZB_ZCL_SCENES_NAME_SUPPORT_DEFAULT_VALUE,     \
                .scene_table_size = EZB_ZCL_SCENES_SCENE_TABLE_SIZE_DEFAULT_VALUE, \
            },                                                                     \
        .on_off_cfg = {                                                            \
            .on_off = EZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE,                         \
        },                                                                         \
    }

/**
 * @brief Zigbee Home Automation (ZHA) On/Off Switch device configuration.
 *
 */
#define EZB_ZHA_ON_OFF_SWITCH_CONFIG() EZB_ZHA_COMMON_DEVICE_CONFIG()

/**
 * @brief Zigbee Home Automation (ZHA) Dimmable Light device configuration.
 *
 */
#define EZB_ZHA_DIMMABLE_LIGHT_CONFIG()                                            \
    {                                                                              \
        .basic_cfg =                                                               \
            {                                                                      \
                .zcl_version  = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,           \
                .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,          \
            },                                                                     \
        .identify_cfg =                                                            \
            {                                                                      \
                .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,     \
            },                                                                     \
        .groups_cfg =                                                              \
            {                                                                      \
                .name_support = EZB_ZCL_GROUPS_NAME_SUPPORT_DEFAULT_VALUE,         \
            },                                                                     \
        .scenes_cfg =                                                              \
            {                                                                      \
                .scene_count      = EZB_ZCL_SCENES_SCENE_COUNT_DEFAULT_VALUE,      \
                .current_scene    = EZB_ZCL_SCENES_CURRENT_SCENE_DEFAULT_VALUE,    \
                .current_group    = EZB_ZCL_SCENES_CURRENT_GROUP_DEFAULT_VALUE,    \
                .scene_valid      = EZB_ZCL_SCENES_SCENE_VALID_DEFAULT_VALUE,      \
                .name_support     = EZB_ZCL_SCENES_NAME_SUPPORT_DEFAULT_VALUE,     \
                .scene_table_size = EZB_ZCL_SCENES_SCENE_TABLE_SIZE_DEFAULT_VALUE, \
            },                                                                     \
        .on_off_cfg =                                                              \
            {                                                                      \
                .on_off = EZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE,                     \
            },                                                                     \
        .level_cfg = {                                                             \
            .current_level = EZB_ZCL_LEVEL_CURRENT_LEVEL_DEFAULT_VALUE,            \
        },                                                                         \
    }

/**
 * @brief Zigbee Home Automation (ZHA) Color Dimmable Light device configuration.
 *
 */
#define EZB_ZHA_COLOR_DIMMABLE_LIGHT_CONFIG()                                               \
    {                                                                                       \
        .basic_cfg =                                                                        \
            {                                                                               \
                .zcl_version  = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,                    \
                .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,                   \
            },                                                                              \
        .identify_cfg =                                                                     \
            {                                                                               \
                .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,              \
            },                                                                              \
        .groups_cfg =                                                                       \
            {                                                                               \
                .name_support = EZB_ZCL_GROUPS_NAME_SUPPORT_DEFAULT_VALUE,                  \
            },                                                                              \
        .scenes_cfg =                                                                       \
            {                                                                               \
                .scene_count      = EZB_ZCL_SCENES_SCENE_COUNT_DEFAULT_VALUE,               \
                .current_scene    = EZB_ZCL_SCENES_CURRENT_SCENE_DEFAULT_VALUE,             \
                .current_group    = EZB_ZCL_SCENES_CURRENT_GROUP_DEFAULT_VALUE,             \
                .scene_valid      = EZB_ZCL_SCENES_SCENE_VALID_DEFAULT_VALUE,               \
                .name_support     = EZB_ZCL_SCENES_NAME_SUPPORT_DEFAULT_VALUE,              \
                .scene_table_size = EZB_ZCL_SCENES_SCENE_TABLE_SIZE_DEFAULT_VALUE,          \
            },                                                                              \
        .on_off_cfg =                                                                       \
            {                                                                               \
                .on_off = EZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE,                              \
            },                                                                              \
        .level_cfg =                                                                        \
            {                                                                               \
                .current_level = EZB_ZCL_LEVEL_CURRENT_LEVEL_DEFAULT_VALUE,                 \
            },                                                                              \
        .color_cfg = {                                                                      \
            .color_mode          = EZB_ZCL_COLOR_CONTROL_COLOR_MODE_DEFAULT_VALUE,          \
            .options             = EZB_ZCL_COLOR_CONTROL_OPTIONS_DEFAULT_VALUE,             \
            .enhanced_color_mode = EZB_ZCL_COLOR_CONTROL_ENHANCED_COLOR_MODE_DEFAULT_VALUE, \
            .color_capabilities  = EZB_ZCL_COLOR_CONTROL_COLOR_CAPABILITIES_DEFAULT_VALUE,  \
            .number_of_primaries = 0,                                                       \
        },                                                                                  \
    }

/**
 * @brief Zigbee Home Automation (ZHA) Dimmer Switch device configuration.
 *
 */
#define EZB_ZHA_DIMMER_SWITCH_CONFIG() EZB_ZHA_COMMON_DEVICE_CONFIG()

/**
 * @brief Zigbee Home Automation (ZHA) Color Dimmer Switch device configuration.
 *
 */
#define EZB_ZHA_COLOR_DIMMER_SWITCH_CONFIG() EZB_ZHA_COMMON_DEVICE_CONFIG()

/**
 * @brief Zigbee Home Automation (ZHA) Mains Power Outlet device configuration.
 *
 */
#define EZB_ZHA_MAINS_POWER_OUTLET_CONFIG() EZB_ZHA_ON_OFF_LIGHT_CONFIG()

/**
 * @brief Zigbee Home Automation (ZHA) Temperature Sensor device configuration.
 *
 */
#define EZB_ZHA_TEMPERATURE_SENSOR_CONFIG()                                                         \
    {                                                                                               \
        .basic_cfg =                                                                                \
            {                                                                                       \
                .zcl_version  = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,                            \
                .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,                           \
            },                                                                                      \
        .identify_cfg =                                                                             \
            {                                                                                       \
                .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,                      \
            },                                                                                      \
        .temp_meas_cfg = {                                                                          \
            .measured_value     = EZB_ZCL_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_DEFAULT_VALUE,     \
            .min_measured_value = EZB_ZCL_TEMPERATURE_MEASUREMENT_MIN_MEASURED_VALUE_DEFAULT_VALUE, \
            .max_measured_value = EZB_ZCL_TEMPERATURE_MEASUREMENT_MAX_MEASURED_VALUE_DEFAULT_VALUE, \
        },                                                                                          \
    }

/**
 * @brief Zigbee Home Automation (ZHA) Light Sensor device configuration.
 *
 */
#define EZB_ZHA_LIGHT_SENSOR_CONFIG()                                                               \
    {                                                                                               \
        .basic_cfg =                                                                                \
            {                                                                                       \
                .zcl_version  = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,                            \
                .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,                           \
            },                                                                                      \
        .identify_cfg =                                                                             \
            {                                                                                       \
                .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,                      \
            },                                                                                      \
        .illuminance_cfg = {                                                                        \
            .measured_value     = EZB_ZCL_ILLUMINANCE_MEASUREMENT_MEASURED_VALUE_DEFAULT_VALUE,     \
            .min_measured_value = EZB_ZCL_ILLUMINANCE_MEASUREMENT_MIN_MEASURED_VALUE_DEFAULT_VALUE, \
            .max_measured_value = EZB_ZCL_ILLUMINANCE_MEASUREMENT_MAX_MEASURED_VALUE_DEFAULT_VALUE, \
        },                                                                                          \
    }

/**
 * @brief Zigbee Home Automation (ZHA) Configuration Tool device configuration.
 *
 */
#define EZB_ZHA_CONFIGURATION_TOOL_CONFIG() EZB_ZHA_ON_OFF_SWITCH_CONFIG()

/**
 * @brief Zigbee Home Automation (ZHA) Thermostat device configuration.
 *
 */
#define EZB_ZHA_THERMOSTAT_CONFIG()                                                                          \
    {                                                                                                        \
        .basic_cfg =                                                                                         \
            {                                                                                                \
                .zcl_version  = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,                                     \
                .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,                                    \
            },                                                                                               \
        .identify_cfg =                                                                                      \
            {                                                                                                \
                .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,                               \
            },                                                                                               \
        .thermostat_cfg = {                                                                                  \
            .local_temperature             = EZB_ZCL_THERMOSTAT_LOCAL_TEMPERATURE_DEFAULT_VALUE,             \
            .control_sequence_of_operation = EZB_ZCL_THERMOSTAT_CONTROL_SEQUENCE_OF_OPERATION_DEFAULT_VALUE, \
            .system_mode                   = EZB_ZCL_THERMOSTAT_SYSTEM_MODE_DEFAULT_VALUE,                   \
        },                                                                                                   \
    }

/**
 * @brief Zigbee Home Automation (ZHA) Shade device configuration.
 *
 */
#define EZB_ZHA_SHADE_CONFIG()                                                     \
    {                                                                              \
        .basic_cfg =                                                               \
            {                                                                      \
                .zcl_version  = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,           \
                .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,          \
            },                                                                     \
        .identify_cfg =                                                            \
            {                                                                      \
                .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,     \
            },                                                                     \
        .shade_cfg =                                                               \
            {                                                                      \
                .status       = EZB_ZCL_SHADE_CONFIG_STATUS_DEFAULT_VALUE,         \
                .closed_limit = EZB_ZCL_SHADE_CONFIG_CLOSED_LIMIT_DEFAULT_VALUE,   \
                .mode         = EZB_ZCL_SHADE_CONFIG_MODE_DEFAULT_VALUE,           \
            },                                                                     \
        .groups_cfg =                                                              \
            {                                                                      \
                .name_support = EZB_ZCL_GROUPS_NAME_SUPPORT_DEFAULT_VALUE,         \
            },                                                                     \
        .scenes_cfg =                                                              \
            {                                                                      \
                .scene_count      = EZB_ZCL_SCENES_SCENE_COUNT_DEFAULT_VALUE,      \
                .current_scene    = EZB_ZCL_SCENES_CURRENT_SCENE_DEFAULT_VALUE,    \
                .current_group    = EZB_ZCL_SCENES_CURRENT_GROUP_DEFAULT_VALUE,    \
                .scene_valid      = EZB_ZCL_SCENES_SCENE_VALID_DEFAULT_VALUE,      \
                .name_support     = EZB_ZCL_SCENES_NAME_SUPPORT_DEFAULT_VALUE,     \
                .scene_table_size = EZB_ZCL_SCENES_SCENE_TABLE_SIZE_DEFAULT_VALUE, \
            },                                                                     \
        .on_off_cfg =                                                              \
            {                                                                      \
                .on_off = EZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE,                     \
            },                                                                     \
        .level_cfg = {                                                             \
            .current_level = EZB_ZCL_LEVEL_CURRENT_LEVEL_DEFAULT_VALUE,            \
        },                                                                         \
    }

/**
 * @brief Zigbee Home Automation (ZHA) Shade controller device configuration.
 *
 */
#define EZB_ZHA_SHADE_CONTROLLER_CONFIG() EZB_ZHA_COMMON_DEVICE_CONFIG()

/**
 * @brief Zigbee Home Automation (ZHA) Window Covering device configuration.
 *
 */
#define EZB_ZHA_WINDOW_COVERING_CONFIG()                                                            \
    {                                                                                               \
        .basic_cfg =                                                                                \
            {                                                                                       \
                .zcl_version  = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,                            \
                .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,                           \
            },                                                                                      \
        .identify_cfg =                                                                             \
            {                                                                                       \
                .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,                      \
            },                                                                                      \
        .window_covering_cfg =                                                                      \
            {                                                                                       \
                .window_covering_type = EZB_ZCL_WINDOW_COVERING_WINDOW_COVERING_TYPE_DEFAULT_VALUE, \
                .config_status        = EZB_ZCL_WINDOW_COVERING_CONFIG_STATUS_OPERATIONAL,          \
            },                                                                                      \
        .groups_cfg =                                                                               \
            {                                                                                       \
                .name_support = EZB_ZCL_GROUPS_NAME_SUPPORT_DEFAULT_VALUE,                          \
            },                                                                                      \
        .scenes_cfg = {                                                                             \
            .scene_count   = EZB_ZCL_SCENES_SCENE_COUNT_DEFAULT_VALUE,                              \
            .current_scene = EZB_ZCL_SCENES_CURRENT_SCENE_DEFAULT_VALUE,                            \
            .current_group = EZB_ZCL_SCENES_CURRENT_GROUP_DEFAULT_VALUE,                            \
            .scene_valid   = EZB_ZCL_SCENES_SCENE_VALID_DEFAULT_VALUE,                              \
            .name_support  = EZB_ZCL_SCENES_NAME_SUPPORT_DEFAULT_VALUE,                             \
        },                                                                                          \
    }

/**
 * @brief Zigbee Home Automation (ZHA) Window Covering controller device configuration.
 *
 */
#define EZB_ZHA_WINDOW_COVERING_CONTROLLER_CONFIG() EZB_ZHA_COMMON_DEVICE_CONFIG()

/**
 * @brief Zigbee Home Automation (ZHA) Door Lock device configuration.
 *
 */
#define EZB_ZHA_DOOR_LOCK_CONFIG()                                                 \
    {                                                                              \
        .basic_cfg =                                                               \
            {                                                                      \
                .zcl_version  = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,           \
                .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,          \
            },                                                                     \
        .identify_cfg =                                                            \
            {                                                                      \
                .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,     \
            },                                                                     \
        .door_lock_cfg =                                                           \
            {                                                                      \
                .lock_state       = EZB_ZCL_DOOR_LOCK_LOCK_STATE_NOT_FULLY_LOCKED, \
                .lock_type        = EZB_ZCL_DOOR_LOCK_LOCK_TYPE_DEAD_BOLT,         \
                .actuator_enabled = false,                                         \
            },                                                                     \
        .groups_cfg =                                                              \
            {                                                                      \
                .name_support = EZB_ZCL_GROUPS_NAME_SUPPORT_DEFAULT_VALUE,         \
            },                                                                     \
        .scenes_cfg = {                                                            \
            .scene_count   = EZB_ZCL_SCENES_SCENE_COUNT_DEFAULT_VALUE,             \
            .current_scene = EZB_ZCL_SCENES_CURRENT_SCENE_DEFAULT_VALUE,           \
            .current_group = EZB_ZCL_SCENES_CURRENT_GROUP_DEFAULT_VALUE,           \
            .scene_valid   = EZB_ZCL_SCENES_SCENE_VALID_DEFAULT_VALUE,             \
            .name_support  = EZB_ZCL_SCENES_NAME_SUPPORT_DEFAULT_VALUE,            \
        },                                                                         \
    }

/**
 * @brief Zigbee Home Automation (ZHA) Door Lock controller device configuration.
 *
 */
#define EZB_ZHA_DOOR_LOCK_CONTROLLER_CONFIG() EZB_ZHA_COMMON_DEVICE_CONFIG()

/**
 * @brief Zigbee Home Automation (ZHA) common device configuration.
 *
 */
typedef struct ezb_zha_common_device_config_s {
    ezb_zcl_basic_cluster_server_config_t basic_cfg;       /*!< Basic cluster configuration,
                                                         * see @ref ezb_zcl_basic_cluster_server_config_s */
    ezb_zcl_identify_cluster_server_config_t identify_cfg; /*!< Identify cluster configuration,
                                                         * see @ref ezb_zcl_identify_cluster_server_config_s */
} ezb_zha_common_device_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Custom Gateway device configuration.
 * @anchor ezb_zha_custom_gateway_config_t
 */
typedef ezb_zha_common_device_config_t ezb_zha_custom_gateway_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) On/Off Light device configuration.
 */
typedef struct ezb_zha_on_off_light_config_s {
    ezb_zcl_basic_cluster_server_config_t basic_cfg;       /*!< Basic cluster configuration,
                                                         * see @ref ezb_zcl_basic_cluster_server_config_s */
    ezb_zcl_identify_cluster_server_config_t identify_cfg; /*!< Identify cluster configuration,
                                                         * see @ref ezb_zcl_identify_cluster_server_config_s */
    ezb_zcl_groups_cluster_server_config_t groups_cfg;     /*!< Groups cluster configuration,
                                                         * see @ref ezb_zcl_groups_cluster_server_config_s */
    ezb_zcl_scenes_cluster_server_config_t scenes_cfg;     /*!< Scenes cluster configuration,
                                                         * see @ref ezb_zcl_scenes_cluster_server_config_s */
    ezb_zcl_on_off_cluster_server_config_t on_off_cfg;     /*!< On off cluster configuration,
                                                         * see @ref ezb_zcl_on_off_cluster_server_config_s */
} ezb_zha_on_off_light_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) On/Off Switch device configuration.
 * @anchor ezb_zha_on_off_switch_config_t
 */
typedef ezb_zha_common_device_config_t ezb_zha_on_off_switch_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Dimmable Light device configuration.
 */
typedef struct ezb_zha_dimmable_light_config_s {
    ezb_zcl_basic_cluster_server_config_t basic_cfg;       /*!< Basic cluster configuration,
                                                         * see @ref ezb_zcl_basic_cluster_server_config_s */
    ezb_zcl_identify_cluster_server_config_t identify_cfg; /*!< Identify cluster configuration,
                                                         * see @ref ezb_zcl_identify_cluster_server_config_s */
    ezb_zcl_groups_cluster_server_config_t groups_cfg;     /*!< Groups cluster configuration,
                                                         * see @ref ezb_zcl_groups_cluster_server_config_s */
    ezb_zcl_scenes_cluster_server_config_t scenes_cfg;     /*!< Scenes cluster configuration,
                                                         * see @ref ezb_zcl_scenes_cluster_server_config_s */
    ezb_zcl_on_off_cluster_server_config_t on_off_cfg;     /*!< On off cluster configuration,
                                                         * see @ref ezb_zcl_on_off_cluster_server_config_s */
    ezb_zcl_level_cluster_server_config_t level_cfg;       /*!< Level cluster configuration,
                                                         * see @ref ezb_zcl_level_cluster_server_config_s */
} ezb_zha_dimmable_light_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Color Dimmable Light device configuration.
 */
typedef struct ezb_zha_color_dimmable_light_config_s {
    ezb_zcl_basic_cluster_server_config_t basic_cfg;         /*!< Basic cluster configuration,
                                                           * see @ref ezb_zcl_basic_cluster_server_config_s */
    ezb_zcl_identify_cluster_server_config_t identify_cfg;   /*!< Identify cluster configuration,
                                                           * see @ref ezb_zcl_identify_cluster_server_config_s */
    ezb_zcl_groups_cluster_server_config_t groups_cfg;       /*!< Groups cluster configuration,
                                                           * see @ref ezb_zcl_groups_cluster_server_config_s */
    ezb_zcl_scenes_cluster_server_config_t scenes_cfg;       /*!< Scenes cluster configuration,
                                                           * see @ref ezb_zcl_scenes_cluster_server_config_s */
    ezb_zcl_on_off_cluster_server_config_t on_off_cfg;       /*!< On off cluster configuration,
                                                           * see @ref ezb_zcl_on_off_cluster_server_config_s */
    ezb_zcl_level_cluster_server_config_t level_cfg;         /*!< Level cluster configuration,
                                                           * see @ref ezb_zcl_level_cluster_server_config_s */
    ezb_zcl_color_control_cluster_server_config_t color_cfg; /*!< Color control cluster configuration,
                                                           * see @ref ezb_zcl_color_control_cluster_server_config_s */
} ezb_zha_color_dimmable_light_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Dimmer Switch device configuration.
 * @anchor ezb_zha_dimmer_switch_config_t
 */
typedef ezb_zha_common_device_config_t ezb_zha_dimmer_switch_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Color Dimmer Switch device configuration.
 * @anchor ezb_zha_color_dimmer_switch_config_t
 */
typedef ezb_zha_common_device_config_t ezb_zha_color_dimmer_switch_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Mains Power Outlet device configuration.
 */
typedef struct ezb_zha_mains_power_outlet_config_s {
    ezb_zcl_basic_cluster_server_config_t basic_cfg;       /*!< Basic cluster configuration,
                                                         * see @ref ezb_zcl_basic_cluster_server_config_s */
    ezb_zcl_identify_cluster_server_config_t identify_cfg; /*!< Identify cluster configuration,
                                                         * see @ref ezb_zcl_identify_cluster_server_config_s */
    ezb_zcl_groups_cluster_server_config_t groups_cfg;     /*!< Groups cluster configuration,
                                                         * see @ref ezb_zcl_groups_cluster_server_config_s */
    ezb_zcl_scenes_cluster_server_config_t scenes_cfg;     /*!< Scenes cluster configuration,
                                                         * see @ref ezb_zcl_scenes_cluster_server_config_s */
    ezb_zcl_on_off_cluster_server_config_t on_off_cfg;     /*!< On off cluster configuration,
                                                         * see @ref ezb_zcl_on_off_cluster_server_config_s */
} ezb_zha_mains_power_outlet_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Temperature Sensor device configuration.
 */
typedef struct ezb_zha_temperature_sensor_config_s {
    ezb_zcl_basic_cluster_server_config_t basic_cfg;       /*!< Basic cluster configuration,
                                                         * see @ref ezb_zcl_basic_cluster_server_config_s */
    ezb_zcl_identify_cluster_server_config_t identify_cfg; /*!< Identify cluster configuration,
                                                         * see @ref ezb_zcl_identify_cluster_server_config_s */
    /** Temperature measurement cluster configuration, see @ref ezb_zcl_temperature_measurement_cluster_server_config_s */
    ezb_zcl_temperature_measurement_cluster_server_config_t temp_meas_cfg;
} ezb_zha_temperature_sensor_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Light Sensor device configuration.
 */
typedef struct ezb_zha_light_sensor_config_s {
    ezb_zcl_basic_cluster_server_config_t basic_cfg;       /*!< Basic cluster configuration,
                                                         * see @ref ezb_zcl_basic_cluster_server_config_s */
    ezb_zcl_identify_cluster_server_config_t identify_cfg; /*!< Identify cluster configuration,
                                                         * see @ref ezb_zcl_identify_cluster_server_config_s */
    /** Illuminance measurement cluster configuration, see @ref ezb_zcl_illuminance_measurement_cluster_server_config_s */
    ezb_zcl_illuminance_measurement_cluster_server_config_t illuminance_cfg;

} ezb_zha_light_sensor_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Configuration Tool device configuration.
 * @anchor ezb_zha_configuration_tool_config_t
 */
typedef ezb_zha_common_device_config_t ezb_zha_configuration_tool_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Thermostat device configuration.
 */
typedef struct ezb_zha_thermostat_config_s {
    ezb_zcl_basic_cluster_server_config_t basic_cfg;           /*!< Basic cluster configuration,
                                                             * see @ref ezb_zcl_basic_cluster_server_config_s */
    ezb_zcl_identify_cluster_server_config_t identify_cfg;     /*!< Identify cluster configuration,
                                                             * see @ref ezb_zcl_identify_cluster_server_config_s */
    ezb_zcl_thermostat_cluster_server_config_t thermostat_cfg; /*!< Thermostat cluster configuration,
                                                             * see @ref ezb_zcl_thermostat_cluster_server_config_s */
} ezb_zha_thermostat_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Shade device configuration.
 */
typedef struct ezb_zha_shade_config_s {
    ezb_zcl_basic_cluster_server_config_t basic_cfg;        /*!< Basic cluster configuration,
                                                          * see @ref ezb_zcl_basic_cluster_server_config_s */
    ezb_zcl_identify_cluster_server_config_t identify_cfg;  /*!< Identify cluster configuration,
                                                          * see @ref ezb_zcl_identify_cluster_server_config_s */
    ezb_zcl_shade_config_cluster_server_config_t shade_cfg; /*!< Shade config cluster configuration,
                                                          * see @ref ezb_zcl_shade_config_cluster_server_config_s */
    ezb_zcl_groups_cluster_server_config_t groups_cfg;      /*!< Groups cluster configuration,
                                                          * see @ref ezb_zcl_groups_cluster_server_config_s */
    ezb_zcl_scenes_cluster_server_config_t scenes_cfg;      /*!< Scenes cluster configuration,
                                                          * see @ref ezb_zcl_scenes_cluster_server_config_s */
    ezb_zcl_on_off_cluster_server_config_t on_off_cfg;      /*!< On off cluster configuration,
                                                          * see @ref ezb_zcl_on_off_cluster_server_config_s */
    ezb_zcl_level_cluster_server_config_t level_cfg;        /*!< Level cluster configuration,
                                                          * see @ref ezb_zcl_level_cluster_server_config_s */
} ezb_zha_shade_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Shade controller device configuration.
 * @anchor ezb_zha_shade_controller_config_t
 */
typedef ezb_zha_common_device_config_t ezb_zha_shade_controller_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Window Covering device configuration.
 */
typedef struct ezb_zha_window_covering_config_s {
    ezb_zcl_basic_cluster_server_config_t basic_cfg;       /*!< Basic cluster configuration,
                                                         * see @ref ezb_zcl_basic_cluster_server_config_s */
    ezb_zcl_identify_cluster_server_config_t identify_cfg; /*!< Identify cluster configuration,
                                                         * see @ref ezb_zcl_identify_cluster_server_config_s */
    ezb_zcl_window_covering_cluster_server_config_t
        window_covering_cfg;                        /*!< Window covering cluster configuration,
                                                     * see @ref ezb_zcl_window_covering_cluster_server_config_s */
    ezb_zcl_groups_cluster_server_config_t groups_cfg; /*!< Groups cluster configuration,
                                                     * see @ref ezb_zcl_groups_cluster_server_config_s */
    ezb_zcl_scenes_cluster_server_config_t scenes_cfg; /*!< Scenes cluster configuration,
                                                     * see @ref ezb_zcl_scenes_cluster_server_config_s */
} ezb_zha_window_covering_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Window Covering controller device configuration.
 * @anchor ezb_zha_window_covering_controller_config_t
 */
typedef ezb_zha_common_device_config_t ezb_zha_window_covering_controller_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Door Lock device configuration.
 */
typedef struct ezb_zha_door_lock_config_s {
    ezb_zcl_basic_cluster_server_config_t basic_cfg;         /*!< Basic cluster configuration,
                                                           * see @ref ezb_zcl_basic_cluster_server_config_s */
    ezb_zcl_identify_cluster_server_config_t identify_cfg;   /*!< Identify cluster configuration,
                                                           * see @ref ezb_zcl_identify_cluster_server_config_s */
    ezb_zcl_door_lock_cluster_server_config_t door_lock_cfg; /*!< Door lock cluster configuration,
                                                           * see @ref ezb_zcl_door_lock_cluster_server_config_s */
    ezb_zcl_groups_cluster_server_config_t groups_cfg;       /*!< Groups cluster configuration,
                                                           * see @ref ezb_zcl_groups_cluster_server_config_s */
    ezb_zcl_scenes_cluster_server_config_t scenes_cfg;       /*!< Scenes cluster configuration,
                                                           * see @ref ezb_zcl_scenes_cluster_server_config_s */
} ezb_zha_door_lock_config_t;

/**
 * @brief Zigbee Home Automation (ZHA) Door Lock controller device configuration.
 * @anchor ezb_zha_door_lock_controller_config_t
 */
typedef ezb_zha_common_device_config_t ezb_zha_door_lock_controller_config_t;

/**
 * @brief Create Zigbee Home Automation (ZHA) Custom Gateway device.
 *
 * @param ep_id The endpoint ID that the custom gateway device is assigned to.
 * @param cfg The pointer to custom gateway device configuration, @ref ezb_zha_custom_gateway_config_t.
 * @return The created Zigbee ZHA Custom Gateway.
 */
ezb_af_ep_desc_t ezb_zha_create_custom_gateway(uint8_t ep_id, const ezb_zha_custom_gateway_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) On/Off Light device.
 *
 * @param ep_id The endpoint ID that the on-off light device is assigned to.
 * @param cfg The pointer to on-off light device configuration, @ref ezb_zha_on_off_light_config_s.
 * @return The created Zigbee ZHA On/Off Light.
 */
ezb_af_ep_desc_t ezb_zha_create_on_off_light(uint8_t ep_id, const ezb_zha_on_off_light_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) On/Off Switch device.
 *
 * @param ep_id The endpoint ID that the on-off switch device is assigned to.
 * @param cfg The pointer to on-off switch device configuration, @ref ezb_zha_on_off_switch_config_t.
 * @return The created Zigbee ZHA On/Off Switch.
 */
ezb_af_ep_desc_t ezb_zha_create_on_off_switch(uint8_t ep_id, const ezb_zha_on_off_switch_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Dimmable Light device.
 *
 * @param ep_id The endpoint ID that the dimmable light device is assigned to.
 * @param cfg The pointer to dimmable light device configuration, @ref ezb_zha_dimmable_light_config_s.
 * @return The created Zigbee ZHA Dimmable Light.
 */
ezb_af_ep_desc_t ezb_zha_create_dimmable_light(uint8_t ep_id, const ezb_zha_dimmable_light_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Color Dimmable Light device.
 *
 * @param ep_id The endpoint ID that the color dimmable light device is assigned to.
 * @param cfg The pointer to color dimmable light device configuration, @ref ezb_zha_color_dimmable_light_config_s.
 * @return The created Zigbee ZHA Color Dimmable Light.
 */
ezb_af_ep_desc_t ezb_zha_create_color_dimmable_light(uint8_t ep_id, const ezb_zha_color_dimmable_light_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Dimmer Switch device.
 *
 * @param ep_id The endpoint ID that the dimmer switch device is assigned to.
 * @param cfg The pointer to dimmer switch device configuration, @ref ezb_zha_dimmer_switch_config_t.
 * @return The created Zigbee ZHA Dimmer Switch.
 */
ezb_af_ep_desc_t ezb_zha_create_dimmer_switch(uint8_t ep_id, const ezb_zha_dimmer_switch_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Color Dimmer Switch device.
 *
 * @param ep_id The endpoint ID that the color dimmer switch device is assigned to.
 * @param cfg The pointer to color dimmer switch device configuration, @ref ezb_zha_color_dimmer_switch_config_t.
 * @return The created Zigbee ZHA Color Dimmer Switch.
 */
ezb_af_ep_desc_t ezb_zha_create_color_dimmer_switch(uint8_t ep_id, const ezb_zha_color_dimmer_switch_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Mains Power Outlet device.
 *
 * @param ep_id The endpoint ID that the mains power outlet device is assigned to.
 * @param cfg The pointer to mains power outlet device configuration, @ref ezb_zha_mains_power_outlet_config_s.
 * @return The created Zigbee ZHA Mains Power Outlet.
 */
ezb_af_ep_desc_t ezb_zha_create_mains_power_outlet(uint8_t ep_id, const ezb_zha_mains_power_outlet_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Temperature Sensor device.
 *
 * @param ep_id The endpoint ID that the temperature sensor device is assigned to.
 * @param cfg The pointer to temperature sensor device configuration, @ref ezb_zha_temperature_sensor_config_s.
 * @return The created Zigbee ZHA Temperature Sensor.
 */
ezb_af_ep_desc_t ezb_zha_create_temperature_sensor(uint8_t ep_id, const ezb_zha_temperature_sensor_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Light Sensor device.
 *
 * @param ep_id The endpoint ID that the light sensor device is assigned to.
 * @param cfg The pointer to light sensor device configuration, @ref ezb_zha_light_sensor_config_s.
 * @return The created Zigbee ZHA Light Sensor.
 */
ezb_af_ep_desc_t ezb_zha_create_light_sensor(uint8_t ep_id, const ezb_zha_light_sensor_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Configuration Tool device.
 *
 * @param ep_id The endpoint ID that the configuration tool device is assigned to.
 * @param cfg The pointer to configuration tool device configuration, @ref ezb_zha_configuration_tool_config_t.
 * @return The created Zigbee ZHA Configuration Tool.
 */
ezb_af_ep_desc_t ezb_zha_create_configuration_tool(uint8_t ep_id, const ezb_zha_configuration_tool_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Thermostat device.
 *
 * @param ep_id The endpoint ID that the thermostat device is assigned to.
 * @param cfg The pointer to thermostat device configuration, @ref ezb_zha_thermostat_config_s.
 * @return The created Zigbee ZHA Thermostat.
 */
ezb_af_ep_desc_t ezb_zha_create_thermostat(uint8_t ep_id, const ezb_zha_thermostat_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Shade device.
 *
 * @param ep_id The endpoint ID that the shade device is assigned to.
 * @param cfg The pointer to shade device configuration, @ref ezb_zha_shade_config_s.
 * @return The created Zigbee ZHA Shade.
 */
ezb_af_ep_desc_t ezb_zha_create_shade(uint8_t ep_id, const ezb_zha_shade_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Shade controller device.
 *
 * @param ep_id The endpoint ID that the shade controller device is assigned to.
 * @param cfg The pointer to shade controller device configuration, @ref ezb_zha_shade_controller_config_t.
 * @return The created Zigbee ZHA Shade controller.
 */
ezb_af_ep_desc_t ezb_zha_create_shade_controller(uint8_t ep_id, const ezb_zha_shade_controller_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Window Covering device.
 *
 * @param ep_id The endpoint ID that the window covering device is assigned to.
 * @param cfg The pointer to window covering device configuration, @ref ezb_zha_window_covering_config_s.
 * @return The created Zigbee ZHA Window Covering.
 */
ezb_af_ep_desc_t ezb_zha_create_window_covering(uint8_t ep_id, const ezb_zha_window_covering_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Window Covering controller device.
 *
 * @param ep_id The endpoint ID that the window covering controller device is assigned to.
 * @param cfg The pointer to window covering controller device configuration, @ref
 * ezb_zha_window_covering_controller_config_t.
 * @return The created Zigbee ZHA Window Covering controller.
 */
ezb_af_ep_desc_t ezb_zha_create_window_covering_controller(uint8_t                                            ep_id,
                                                           const ezb_zha_window_covering_controller_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Door Lock device.
 *
 * @param ep_id The endpoint ID that the door lock device is assigned to.
 * @param cfg The pointer to door lock device configuration, @ref ezb_zha_door_lock_config_s.
 * @return The created Zigbee ZHA Door Lock.
 */
ezb_af_ep_desc_t ezb_zha_create_door_lock(uint8_t ep_id, const ezb_zha_door_lock_config_t *cfg);

/**
 * @brief Create Zigbee Home Automation (ZHA) Door Lock controller device.
 *
 * @param ep_id The endpoint ID that the door lock controller device is assigned to.
 * @param cfg The pointer to door lock controller device configuration, @ref
 * ezb_zha_door_lock_controller_config_t.
 * @return The created Zigbee ZHA Door Lock controller.
 */
ezb_af_ep_desc_t ezb_zha_create_door_lock_controller(uint8_t ep_id, const ezb_zha_door_lock_controller_config_t *cfg);

#ifdef __cplusplus
} /*  extern "C" */
#endif
