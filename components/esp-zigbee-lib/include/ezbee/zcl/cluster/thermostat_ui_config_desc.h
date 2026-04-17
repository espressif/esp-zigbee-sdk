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
   THERMOSTAT_UI_CONFIG Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the thermostat_ui_config cluster implementation */
#define EZB_ZCL_THERMOSTAT_UI_CONFIG_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the thermostat_ui_config server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_THERMOSTAT_UI_CONFIG_TEMPERATURE_DISPLAY_MODE_ID = 0x0000U, /*!< TemperatureDisplayMode attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_UI_CONFIG_KEYPAD_LOCKOUT_ID           = 0x0001U, /*!< KeypadLockout attribute. */
    EZB_ZCL_ATTR_THERMOSTAT_UI_CONFIG_SCHEDULE_PROGRAMMING_VISIBILITY_ID =
        0x0002U, /*!< ScheduleProgrammingVisibility attribute. */
} ezb_zcl_thermostat_ui_config_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the ThermostatUiConfig server cluster.
 */
typedef struct ezb_zcl_thermostat_ui_config_cluster_server_config_s {
    uint8_t temperature_display_mode; /*!< Configurable mandatory TemperatureDisplayMode attribute */
    uint8_t keypad_lockout;           /*!< Configurable mandatory KeypadLockout attribute */
} ezb_zcl_thermostat_ui_config_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL TemperatureDisplayMode attribute of ThermostatUiConfig.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_UI_CONFIG_TEMPERATURE_DISPLAY_MODE_CELSIUS    = 0x00U, /*!< Celsius */
    EZB_ZCL_THERMOSTAT_UI_CONFIG_TEMPERATURE_DISPLAY_MODE_FAHRENHEIT = 0x01U, /*!< Fahrenheit */
} ezb_zcl_thermostat_ui_config_server_temperature_display_mode_t;

/**
 * @brief Enumeration for ZCL KeypadLockout attribute of ThermostatUiConfig.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_UI_CONFIG_KEYPAD_LOCKOUT_NONE   = 0x00U, /*!< None */
    EZB_ZCL_THERMOSTAT_UI_CONFIG_KEYPAD_LOCKOUT_LEVEL1 = 0x01U, /*!< Level1 */
    EZB_ZCL_THERMOSTAT_UI_CONFIG_KEYPAD_LOCKOUT_LEVEL2 = 0x02U, /*!< Level2 */
    EZB_ZCL_THERMOSTAT_UI_CONFIG_KEYPAD_LOCKOUT_LEVEL3 = 0x03U, /*!< Level3 */
    EZB_ZCL_THERMOSTAT_UI_CONFIG_KEYPAD_LOCKOUT_LEVEL4 = 0x04U, /*!< Level4 */
    EZB_ZCL_THERMOSTAT_UI_CONFIG_KEYPAD_LOCKOUT_LEVEL5 = 0x05U, /*!< Level5 */
} ezb_zcl_thermostat_ui_config_server_keypad_lockout_t;

/**
 * @brief Enumeration for ZCL ScheduleProgrammingVisibility attribute of ThermostatUiConfig.
 */
typedef enum {
    EZB_ZCL_THERMOSTAT_UI_CONFIG_SCHEDULE_PROGRAMMING_VISIBILITY_LOCAL_ENABLED  = 0x00U, /*!< LocalEnabled */
    EZB_ZCL_THERMOSTAT_UI_CONFIG_SCHEDULE_PROGRAMMING_VISIBILITY_LOCAL_DISABLED = 0x01U, /*!< LocalDisabled */
} ezb_zcl_thermostat_ui_config_server_schedule_programming_visibility_t;

/** @brief Default value of TemperatureDisplayMode in ThermostatUiConfig cluster */
#define EZB_ZCL_THERMOSTAT_UI_CONFIG_TEMPERATURE_DISPLAY_MODE_DEFAULT_VALUE (0x00)

/** @brief Minimum value of TemperatureDisplayMode in ThermostatUiConfig cluster */
#define EZB_ZCL_THERMOSTAT_UI_CONFIG_TEMPERATURE_DISPLAY_MODE_MIN_VALUE (0x00)

/** @brief Maximum value of TemperatureDisplayMode in ThermostatUiConfig cluster */
#define EZB_ZCL_THERMOSTAT_UI_CONFIG_TEMPERATURE_DISPLAY_MODE_MAX_VALUE (0x01)
/** @brief Default value of KeypadLockout in ThermostatUiConfig cluster */
#define EZB_ZCL_THERMOSTAT_UI_CONFIG_KEYPAD_LOCKOUT_DEFAULT_VALUE (0x00)

/** @brief Minimum value of KeypadLockout in ThermostatUiConfig cluster */
#define EZB_ZCL_THERMOSTAT_UI_CONFIG_KEYPAD_LOCKOUT_MIN_VALUE (0x00)

/** @brief Maximum value of KeypadLockout in ThermostatUiConfig cluster */
#define EZB_ZCL_THERMOSTAT_UI_CONFIG_KEYPAD_LOCKOUT_MAX_VALUE (0x05)
/** @brief Default value of ScheduleProgrammingVisibility in ThermostatUiConfig cluster */
#define EZB_ZCL_THERMOSTAT_UI_CONFIG_SCHEDULE_PROGRAMMING_VISIBILITY_DEFAULT_VALUE (0x00)

/** @brief Minimum value of ScheduleProgrammingVisibility in ThermostatUiConfig cluster */
#define EZB_ZCL_THERMOSTAT_UI_CONFIG_SCHEDULE_PROGRAMMING_VISIBILITY_MIN_VALUE (0x00)

/** @brief Maximum value of ScheduleProgrammingVisibility in ThermostatUiConfig cluster */
#define EZB_ZCL_THERMOSTAT_UI_CONFIG_SCHEDULE_PROGRAMMING_VISIBILITY_MAX_VALUE (0x01)

typedef ezb_zcl_thermostat_ui_config_cluster_server_config_t ezb_zcl_thermostat_ui_config_cluster_config_t;

/**
 * @brief Add an attribute to an thermostat_ui_config cluster descriptor.
 *
 * @param cluster_desc Pointer to the thermostat_ui_config cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_thermostat_ui_config_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                             uint16_t               attr_id,
                                                             const void            *value);

/**
 * @brief Create an thermostat_ui_config cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the thermostat_ui_config cluster configuration structure, refer to
 * ezb_zcl_thermostat_ui_config_cluster_server_config_t or ezb_zcl_thermostat_ui_config_cluster_client_config_t or NULL (default
 * config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_thermostat_ui_config_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the ThermostatUiConfig cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_thermostat_ui_config_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the ThermostatUiConfig cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_thermostat_ui_config_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_THERMOSTAT_UI_CONFIG_CLIENT_ROLE_INIT ezb_zcl_thermostat_ui_config_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_THERMOSTAT_UI_CONFIG_SERVER_ROLE_INIT ezb_zcl_thermostat_ui_config_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
