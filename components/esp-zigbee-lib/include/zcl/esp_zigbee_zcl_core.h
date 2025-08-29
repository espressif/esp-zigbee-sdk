/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"

#include "esp_zigbee_type.h"
#include "esp_zigbee_zcl_common.h"
#include "esp_zigbee_zcl_basic.h"
#include "esp_zigbee_zcl_identify.h"
#include "esp_zigbee_zcl_groups.h"
#include "esp_zigbee_zcl_scenes.h"
#include "esp_zigbee_zcl_on_off.h"
#include "esp_zigbee_zcl_on_off_switch_config.h"
#include "esp_zigbee_zcl_level.h"
#include "esp_zigbee_zcl_color_control.h"
#include "esp_zigbee_zcl_time.h"
#include "esp_zigbee_zcl_binary_input.h"
#include "esp_zigbee_zcl_commissioning.h"
#include "esp_zigbee_zcl_ias_zone.h"
#include "esp_zigbee_zcl_ias_ace.h"
#include "esp_zigbee_zcl_ias_wd.h"
#include "esp_zigbee_zcl_shade_config.h"
#include "esp_zigbee_zcl_door_lock.h"
#include "esp_zigbee_zcl_humidity_meas.h"
#include "esp_zigbee_zcl_temperature_meas.h"
#include "esp_zigbee_zcl_ota.h"
#include "esp_zigbee_zcl_electrical_meas.h"
#include "esp_zigbee_zcl_illuminance_meas.h"
#include "esp_zigbee_zcl_pressure_meas.h"
#include "esp_zigbee_zcl_flow_meas.h"
#include "esp_zigbee_zcl_occupancy_sensing.h"
#include "esp_zigbee_zcl_window_covering.h"
#include "esp_zigbee_zcl_thermostat.h"
#include "esp_zigbee_zcl_fan_control.h"
#include "esp_zigbee_zcl_thermostat_ui_config.h"
#include "esp_zigbee_zcl_analog_input.h"
#include "esp_zigbee_zcl_analog_output.h"
#include "esp_zigbee_zcl_analog_value.h"
#include "esp_zigbee_zcl_carbon_dioxide_measurement.h"
#include "esp_zigbee_zcl_pm2_5_measurement.h"
#include "esp_zigbee_zcl_multistate_value.h"
#include "esp_zigbee_zcl_metering.h"
#include "esp_zigbee_zcl_diagnostics.h"
#include "esp_zigbee_zcl_meter_identification.h"
#include "esp_zigbee_zcl_price.h"
#include "esp_zigbee_zcl_ec_measurement.h"
#include "esp_zigbee_zcl_ph_measurement.h"
#include "esp_zigbee_zcl_wind_speed_measurement.h"
#include "esp_zigbee_zcl_drlc.h"
#include "esp_zigbee_zcl_dehumidification_control.h"
#include "esp_zigbee_zcl_binary_input.h"
#include "esp_zigbee_zcl_binary_output.h"
#include "esp_zigbee_zcl_binary_value.h"
#include "esp_zigbee_zcl_multistate_input.h"
#include "esp_zigbee_zcl_multistate_output.h"
#include "esp_zigbee_zcl_multistate_value.h"
#include "esp_zigbee_zcl_poll_control.h"
#include "esp_zigbee_zcl_device_temp_config.h"
#include "esp_zigbee_zcl_alarms.h"
#include "esp_zigbee_zcl_command.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enum of the Zigbee core action callback id
 *
 * @note
 *    1. If one endpoint possesses the same custom cluster identifier in both client and server roles,
 *       any request or response command for the custom cluster will only trigger the
 *       ``ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_REQ_CB_ID`` callback.
 *    2. The callback ids without ``CMD`` in their names would provide messages of the following structure:
 *       @code{c}
 *       typedef struct xxx_message_s {
 *           esp_zb_device_cb_common_info_t info;
 *           ...
 *       } xxx_message_t;
 *       @endcode
 *       While the callback ids with ``CMD`` in their names would provide messages of the following structure:
 *       @code{c}
 *       typedef struct xxx_message_s {
 *           esp_zb_zcl_cmd_info_t info;
 *           ...
 *       } xxx_message_t;
 *       @endcode
 *
 */
 typedef enum esp_zb_core_action_callback_id_s {
    ESP_ZB_CORE_SET_ATTR_VALUE_CB_ID                    = 0x0000,   /*!< Set attribute value, refer to esp_zb_zcl_set_attr_value_message_t */
    ESP_ZB_CORE_SCENES_STORE_SCENE_CB_ID                = 0x0001,   /*!< Store scene, refer to esp_zb_zcl_store_scene_message_t */
    ESP_ZB_CORE_SCENES_RECALL_SCENE_CB_ID               = 0x0002,   /*!< Recall scene, refer to esp_zb_zcl_recall_scene_message_t */
    ESP_ZB_CORE_IAS_ZONE_ENROLL_RESPONSE_VALUE_CB_ID    = 0x0003,   /*!< IAS Zone enroll response, refer to esp_zb_zcl_ias_zone_enroll_response_message_t */
    ESP_ZB_CORE_OTA_UPGRADE_VALUE_CB_ID                 = 0x0004,   /*!< Upgrade OTA, refer to esp_zb_zcl_ota_upgrade_value_message_t */
    ESP_ZB_CORE_OTA_UPGRADE_SRV_STATUS_CB_ID            = 0x0005,   /*!< OTA Server status, refer to esp_zb_zcl_ota_upgrade_server_status_message_t */
    ESP_ZB_CORE_OTA_UPGRADE_SRV_QUERY_IMAGE_CB_ID       = 0x0006,   /*!< OTA Server query image, refer to esp_zb_zcl_ota_upgrade_server_query_image_message_t */
    ESP_ZB_CORE_THERMOSTAT_VALUE_CB_ID                  = 0x0007,   /*!< Thermostat value, refer to esp_zb_zcl_thermostat_value_message_t */
    ESP_ZB_CORE_METERING_GET_PROFILE_CB_ID              = 0x0008,   /*!< Metering get profile, refer to esp_zb_zcl_metering_get_profile_message_t */
    ESP_ZB_CORE_METERING_GET_PROFILE_RESP_CB_ID         = 0x0009,   /*!< Metering get profile response, refer to esp_zb_zcl_metering_get_profile_resp_message_t */
    ESP_ZB_CORE_METERING_REQ_FAST_POLL_MODE_CB_ID       = 0x000a,   /*!< Metering request fast poll mode, refer to esp_zb_zcl_metering_request_fast_poll_mode_message_t */
    ESP_ZB_CORE_METERING_REQ_FAST_POLL_MODE_RESP_CB_ID  = 0x000b,   /*!< Metering request fast poll mode response, refer to esp_zb_zcl_metering_request_fast_poll_mode_resp_message_t */
    ESP_ZB_CORE_METERING_GET_SNAPSHOT_CB_ID             = 0x000c,   /*!< Metering get snapshot, refer to esp_zb_zcl_metering_get_snapshot_message_t */
    ESP_ZB_CORE_METERING_PUBLISH_SNAPSHOT_CB_ID         = 0x000d,   /*!< Metering publish snapshot, refer to esp_zb_zcl_metering_publish_snapshot_message_t */
    ESP_ZB_CORE_METERING_GET_SAMPLED_DATA_CB_ID         = 0x000e,   /*!< Metering get sampled data, refer to esp_zb_zcl_metering_get_sampled_data_message_t */
    ESP_ZB_CORE_METERING_GET_SAMPLED_DATA_RESP_CB_ID    = 0x000f,   /*!< Metering get sampled data response, refer to esp_zb_zcl_metering_get_sampled_data_resp_message_t */
    ESP_ZB_CORE_DOOR_LOCK_LOCK_DOOR_CB_ID               = 0x0010,   /*!< Lock/unlock door request, refer to esp_zb_zcl_door_lock_lock_door_message_t */
    ESP_ZB_CORE_DOOR_LOCK_LOCK_DOOR_RESP_CB_ID          = 0x0011,   /*!< Lock/unlock door response, refer to esp_zb_zcl_door_lock_lock_door_resp_message_t */
    ESP_ZB_CORE_IDENTIFY_EFFECT_CB_ID                   = 0x0012,   /*!< Identify triggers effect request, refer to esp_zb_zcl_identify_effect_message_t */
    ESP_ZB_CORE_BASIC_RESET_TO_FACTORY_RESET_CB_ID      = 0x0013,   /*!< Reset all clusters of endpoint to factory default, refer to esp_zb_zcl_basic_reset_factory_default_message_t  */
    ESP_ZB_CORE_PRICE_GET_CURRENT_PRICE_CB_ID           = 0x0014,   /*!< Price get current price, refer to esp_zb_zcl_price_get_current_price_message_t */
    ESP_ZB_CORE_PRICE_GET_SCHEDULED_PRICES_CB_ID        = 0x0015,   /*!< Price get scheduled prices, refer to esp_zb_zcl_price_get_scheduled_prices_message_t */
    ESP_ZB_CORE_PRICE_GET_TIER_LABELS_CB_ID             = 0x0016,   /*!< Price get tier labels, refer to esp_zb_zcl_price_get_tier_labels_message_t */
    ESP_ZB_CORE_PRICE_PUBLISH_PRICE_CB_ID               = 0x0017,   /*!< Price publish price, refer to esp_zb_zcl_price_publish_price_message_t */
    ESP_ZB_CORE_PRICE_PUBLISH_TIER_LABELS_CB_ID         = 0x0018,   /*!< Price publish tier labels, refer to esp_zb_zcl_price_publish_tier_labels_message_t */
    ESP_ZB_CORE_PRICE_PRICE_ACK_CB_ID                   = 0x0019,   /*!< Price price acknowledgement, refer to esp_zb_zcl_price_ack_message_t */
    ESP_ZB_CORE_COMM_RESTART_DEVICE_CB_ID               = 0x001a,   /*!< Commissioning restart device, refer to esp_zigbee_zcl_commissioning_restart_device_message_t */
    ESP_ZB_CORE_COMM_OPERATE_STARTUP_PARAMS_CB_ID       = 0x001b,   /*!< Commissioning operate startup parameters, refer to esp_zigbee_zcl_commissioning_operate_startup_parameters_message_t */
    ESP_ZB_CORE_COMM_COMMAND_RESP_CB_ID                 = 0x001c,   /*!< Commissioning command response, refer to esp_zigbee_zcl_commissioning_command_response_message_t */
    ESP_ZB_CORE_IAS_WD_START_WARNING_CB_ID              = 0x001d,   /*!< IAS WD cluster Start Warning command, refer to esp_zb_zcl_ias_wd_start_warning_message_t */
    ESP_ZB_CORE_IAS_WD_SQUAWK_CB_ID                     = 0x001e,   /*!< IAS WD cluster Squawk command, refer to esp_zb_zcl_ias_wd_squawk_message_t */
    ESP_ZB_CORE_IAS_ACE_ARM_CB_ID                       = 0x001f,   /*!< IAS ACE cluster Arm command, refer to esp_zb_zcl_ias_ace_arm_message_t */
    ESP_ZB_CORE_IAS_ACE_BYPASS_CB_ID                    = 0x0020,   /*!< IAS ACE cluster Bypass command, refer to esp_zb_zcl_ias_ace_bypass_message_t */
    ESP_ZB_CORE_IAS_ACE_EMERGENCY_CB_ID                 = 0x0021,   /*!< IAS ACE cluster Emergency command, refer to esp_zb_zcl_ias_ace_emergency_message_t */
    ESP_ZB_CORE_IAS_ACE_FIRE_CB_ID                      = 0x0022,   /*!< IAS ACE cluster Fire command, refer to esp_zb_zcl_ias_ace_fire_message_t */
    ESP_ZB_CORE_IAS_ACE_PANIC_CB_ID                     = 0x0023,   /*!< IAS ACE cluster Panic command, refer to esp_zb_zcl_ias_ace_panic_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_PANEL_STATUS_CB_ID          = 0x0024,   /*!< IAS ACE cluster Get Panel Status command, refer to esp_zb_zcl_ias_ace_get_panel_status_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_BYPASSED_ZONE_LIST_CB_ID    = 0x0025,   /*!< IAS ACE cluster Get Bypass Zone List command, refer to esp_zb_zcl_ias_ace_get_bypassed_zone_list_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_ZONE_STATUS_CB_ID           = 0x0026,   /*!< IAS ACE cluster Get Zone Status command, refer to esp_zb_zcl_ias_ace_get_zone_status_message_t */
    ESP_ZB_CORE_IAS_ACE_ARM_RESP_CB_ID                  = 0x0027,   /*!< IAS ACE cluster Arm command response, refer to esp_zb_zcl_ias_ace_arm_response_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_ZONE_ID_MAP_RESP_CB_ID      = 0x0028,   /*!< IAS ACE cluster Get Zone ID MAP command response, refer to esp_zb_zcl_ias_ace_get_zone_id_map_response_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_ZONE_INFO_RESP_CB_ID        = 0x0029,   /*!< IAS ACE cluster Get Zone Information command response, refer to esp_zb_zcl_ias_ace_get_zone_info_response_message_t */
    ESP_ZB_CORE_IAS_ACE_ZONE_STATUS_CHANGED_CB_ID       = 0x002a,   /*!< IAS ACE cluster Zone Status Changed command, refer to esp_zb_zcl_ias_ace_zone_status_changed_message_t */
    ESP_ZB_CORE_IAS_ACE_PANEL_STATUS_CHANGED_CB_ID      = 0x002b,   /*!< IAS ACE cluster Panel Status Changed command, refer to esp_zb_zcl_ias_ace_panel_status_changed_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_PANEL_STATUS_RESP_CB_ID     = 0x002c,   /*!< IAS ACE cluster Get Panel Status command response, refer to esp_zb_zcl_ias_ace_get_panel_status_response_message_t */
    ESP_ZB_CORE_IAS_ACE_SET_BYPASSED_ZONE_LIST_CB_ID    = 0x002d,   /*!< IAS ACE cluster Set Bypassed Zone List command, refer to esp_zb_zcl_ias_ace_set_bypassed_zone_list_message_t */
    ESP_ZB_CORE_IAS_ACE_BYPASS_RESP_CB_ID               = 0x002e,   /*!< IAS ACE cluster Bypass command response, refer to esp_zb_zcl_ias_ace_bypass_response_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_ZONE_STATUS_RESP_CB_ID      = 0x002f,   /*!< IAS ACE cluster Get Zone Status command response, refer to esp_zb_zcl_ias_ace_get_zone_status_response_message_t */
    ESP_ZB_CORE_WINDOW_COVERING_MOVEMENT_CB_ID          = 0x0030,   /*!< Window covering movement command, refer to esp_zb_zcl_window_covering_movement_message_t */
    ESP_ZB_CORE_OTA_UPGRADE_QUERY_IMAGE_RESP_CB_ID      = 0x0031,   /*!< OTA upgrade query image response message, refer to esp_zb_zcl_ota_upgrade_query_image_resp_message_t */
    ESP_ZB_CORE_THERMOSTAT_WEEKLY_SCHEDULE_SET_CB_ID    = 0x0032,   /*!< Thermostat weekly schedule stable set, refer to esp_zb_zcl_thermostat_weekly_schedule_set_message_t */
    ESP_ZB_CORE_DRLC_LOAD_CONTROL_EVENT_CB_ID           = 0x0040,   /*!< Demand response and load control cluster LoadControlEvent message, refer to esp_zb_zcl_drlc_load_control_event_message_t */
    ESP_ZB_CORE_DRLC_CANCEL_LOAD_CONTROL_EVENT_CB_ID    = 0x0041,   /*!< Demand response and load control cluster CancelLoadControlEvent message, refer to esp_zb_zcl_drlc_cancel_load_control_event_message_t */
    ESP_ZB_CORE_DRLC_CANCEL_ALL_LOAD_CONTROL_EVENTS_CB_ID = 0x0042, /*!< Demand response and load control cluster CancelAllLoadControlEvents message, refer to esp_zb_zcl_drlc_cancel_all_load_control_events_message_t */
    ESP_ZB_CORE_DRLC_REPORT_EVENT_STATUS_CB_ID          = 0x0043,   /*!< Demand response and load control cluster ReportEventStatus message, refer to esp_zb_zcl_drlc_report_event_status_message_t */
    ESP_ZB_CORE_DRLC_GET_SCHEDULED_EVENTS_CB_ID         = 0x0044,   /*!< Demand response and load control cluster GetScheduledEvents message, refer to esp_zb_zcl_drlc_get_scheduled_events_message_t */
    ESP_ZB_CORE_POLL_CONTROL_CHECK_IN_REQ_CB_ID         = 0x0045,   /*!< Poll control cluster CheckInRequest message, refer to esp_zb_zcl_poll_control_check_in_req_message_t */
    ESP_ZB_CORE_ALARMS_RESET_ALARM_CB_ID                = 0x0050,   /*!< Alarms cluster Reset Alarm command, refer to esp_zb_zcl_alarms_reset_alarm_message_t */
    ESP_ZB_CORE_ALARMS_RESET_ALL_ALARMS_CB_ID           = 0x0051,   /*!< Alarms cluster Reset All Alarms command, refer to esp_zb_zcl_alarms_reset_all_alarms_message_t */
    ESP_ZB_CORE_ALARMS_ALARM_CB_ID                      = 0x0052,   /*!<  Alarms cluster Alarm command, refer to esp_zb_zcl_alarms_alarm_message_t */
    ESP_ZB_CORE_ALARMS_GET_ALARM_RESP_CB_ID             = 0x0053,   /*!< Alarms cluster Get Alarm Response command, refer to esp_zb_zcl_alarms_get_alarm_resp_message_t */
    ESP_ZB_CORE_CMD_READ_ATTR_RESP_CB_ID                = 0x1000,   /*!< Read attribute response, refer to esp_zb_zcl_cmd_read_attr_resp_message_t */
    ESP_ZB_CORE_CMD_WRITE_ATTR_RESP_CB_ID               = 0x1001,   /*!< Write attribute response, refer to esp_zb_zcl_cmd_write_attr_resp_message_t */
    ESP_ZB_CORE_CMD_REPORT_CONFIG_RESP_CB_ID            = 0x1002,   /*!< Configure report response, refer to esp_zb_zcl_cmd_config_report_resp_message_t */
    ESP_ZB_CORE_CMD_READ_REPORT_CFG_RESP_CB_ID          = 0x1003,   /*!< Read report configuration response, refer to esp_zb_zcl_cmd_read_report_config_resp_message_t */
    ESP_ZB_CORE_CMD_DISC_ATTR_RESP_CB_ID                = 0x1004,   /*!< Discover attributes response, refer to esp_zb_zcl_cmd_discover_attributes_resp_message_t */
    ESP_ZB_CORE_CMD_DEFAULT_RESP_CB_ID                  = 0x1005,   /*!< Default response, refer to esp_zb_zcl_cmd_default_resp_message_t */
    ESP_ZB_CORE_CMD_OPERATE_GROUP_RESP_CB_ID            = 0x1010,   /*!< Group add group response, refer to esp_zb_zcl_groups_operate_group_resp_message_t */
    ESP_ZB_CORE_CMD_VIEW_GROUP_RESP_CB_ID               = 0x1011,   /*!< Group view response, refer to esp_zb_zcl_groups_view_group_resp_message_t */
    ESP_ZB_CORE_CMD_GET_GROUP_MEMBERSHIP_RESP_CB_ID     = 0x1012,   /*!< Group get membership response, refer to esp_zb_zcl_groups_get_group_membership_resp_message_t */
    ESP_ZB_CORE_CMD_OPERATE_SCENE_RESP_CB_ID            = 0x1020,   /*!< Scenes operate response, refer to esp_zb_zcl_scenes_operate_scene_resp_message_t */
    ESP_ZB_CORE_CMD_VIEW_SCENE_RESP_CB_ID               = 0x1021,   /*!< Scenes view response, refer to esp_zb_zcl_scenes_view_scene_resp_message_t */
    ESP_ZB_CORE_CMD_GET_SCENE_MEMBERSHIP_RESP_CB_ID     = 0x1022,   /*!< Scenes get membership response, refer to esp_zb_zcl_scenes_get_scene_membership_resp_message_t */
    ESP_ZB_CORE_CMD_IAS_ZONE_ZONE_ENROLL_REQUEST_ID     = 0x1030,   /*!< IAS Zone enroll request, refer to esp_zb_zcl_ias_zone_enroll_request_message_t */
    ESP_ZB_CORE_CMD_IAS_ZONE_ZONE_STATUS_CHANGE_NOT_ID  = 0x1031,   /*!< IAS Zone status change notification, refer to esp_zb_zcl_ias_zone_status_change_notification_message_t */
    ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_REQ_CB_ID            = 0x1040,   /*!< Custom Cluster request, refer to esp_zb_zcl_custom_cluster_command_message_t */
    ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_RESP_CB_ID           = 0x1041,   /*!< Custom Cluster response, refer to esp_zb_zcl_custom_cluster_command_message_t */
    ESP_ZB_CORE_CMD_PRIVILEGE_COMMAND_REQ_CB_ID         = 0x1050,   /*!< Custom Cluster request, refer to esp_zb_zcl_privilege_command_message_t */
    ESP_ZB_CORE_CMD_PRIVILEGE_COMMAND_RESP_CB_ID        = 0x1051,   /*!< Custom Cluster response, refer to esp_zb_zcl_privilege_command_message_t */
    ESP_ZB_CORE_CMD_TOUCHLINK_GET_GROUP_ID_RESP_CB_ID   = 0x1060,   /*!< Touchlink commissioning cluster get group id response, refer to esp_zb_touchlink_get_group_identifiers_resp_message_t */
    ESP_ZB_CORE_CMD_TOUCHLINK_GET_ENDPOINT_LIST_RESP_CB_ID = 0x1061,   /*!< Touchlink commissioning cluster get endpoint list response, refer to esp_zb_zcl_touchlink_get_endpoint_list_resp_message_t */
    ESP_ZB_CORE_CMD_THERMOSTAT_GET_WEEKLY_SCHEDULE_RESP_CB_ID = 0x1070, /*!< Thermostat cluster get weekly schedule response, refer to esp_zb_zcl_thermostat_get_weekly_schedule_resp_message_t */
    ESP_ZB_CORE_CMD_GREEN_POWER_RECV_CB_ID                 = 0x1F00,   /*!< Green power cluster command receiving, refer to esp_zb_zcl_cmd_green_power_recv_message_t */
    ESP_ZB_CORE_REPORT_ATTR_CB_ID                          = 0x2000,   /*!< Attribute Report, refer to esp_zb_zcl_report_attr_message_t */
} esp_zb_core_action_callback_id_t;

/**
 * @brief A callback for user to obtain device_cb_id buffer id of ZBoss stack
 *
 * @return
 *      -   True: processed
 *      -   False: unprocessed
 */
typedef bool (*esp_zb_zcl_device_cb_id_callback_t)(uint8_t bufid);

 /**
  * @brief A callback for user to obtain raw command bufid of ZBoss stack
  *
  * @note If the @p bufid has been processed in the callback, it should be freed using the zb_zcl_send_default_handler().
  *
  * @return
  *      -   True: processed
  *      -   False: unprocessed
  */
typedef bool (*esp_zb_zcl_raw_command_callback_t)(uint8_t bufid);

/** Identify callback
 *
 * @param[in] identify_on A indication that need start identify or stop
 *
 */
typedef void (*esp_zb_identify_notify_callback_t)(uint8_t identify_on);

/**
 * @brief ZCL reset default attribute callback
 *
 * @param[in] endpoint   The Endpoint identifier
 * @param[in] cluster_id The cluster identifier
 * @param[in] curr_attr  The current attribute information
 *
 * @return The default attribute value will be set to
 */
typedef void *(*esp_zb_zcl_reset_default_attr_callback_t)(uint8_t endpoint, uint16_t cluster_id, esp_zb_zcl_attribute_t curr_attr);

/**
 * @brief A callback for user to obtain interesting Zigbee message
 *
 * @note The returned value will be utilized by the stack for post-processing
 * @param[in] callback_id The id of Zigbee core action, refer to esp_zb_core_action_callback_id_t
 * @param[in] message The information of Zigbee core action that bind with the @p callback_id
 *
 * @return ESP_OK The action is handled successfully, others on failure
 */
 typedef esp_err_t (*esp_zb_core_action_callback_t)(esp_zb_core_action_callback_id_t callback_id, const void *message);

 /**
  * @brief Register the Zigbee core action handler
  *
  * @param[in] cb A callback that user can handle the Zigbee action, refer to esp_zb_core_callback_t
  *
  */
 void esp_zb_core_action_handler_register(esp_zb_core_action_callback_t cb);

/**
 * @brief Register the Zigbee device_cb_id handler
 *
 * @param[in] cb A callback that user can handle the Zigbee raw device_cb_id buffer id, refer to esp_zb_core_callback_t
 *
 */
void esp_zb_device_cb_id_handler_register(esp_zb_zcl_device_cb_id_callback_t cb);

/**
 * @brief Register the raw Zigbee command handler
 *
 * @param[in] cb A callback that user can handle the Zigbee raw command buffer id, refer to esp_zb_zcl_raw_command_callback_t
 *
 */
void esp_zb_raw_command_handler_register(esp_zb_zcl_raw_command_callback_t cb);

/**
 * @brief Register the callback for the ZCL command send status
 *
 * @param[in] cb The ZCL command send status callback, refer to esp_zb_zcl_command_send_status_callback_t
 */
void esp_zb_zcl_command_send_status_handler_register(esp_zb_zcl_command_send_status_callback_t cb);

/**
 * @brief   Set the ZCL identify notify callback for specific endpoint.
 *
 * @note  Set a callback for user to handle identify command.
 *
 * @param[in] endpoint A specific endpoint
 * @param[in] cb A identify notify callback that user used
 *
 */
void esp_zb_identify_notify_handler_register(uint8_t endpoint, esp_zb_identify_notify_callback_t cb);

/**
 * @brief Add a callback and the privilege command the Zigbee cluster in endpoint.
 *
 * @note The privilege command will skip the Zigbee stack and be exposed to users by the callback indirectly.
 *       Allowing different commands to use the same callback.
 *
 * @param[in] endpoint The specific endpoint for @p cluster
 * @param[in] cluster The specific cluster for @p command
 * @param[in] command The specific command ID is required to handle for users.
 * @return
 *      - ESP_OK: on success
 *      - ESP_FAIL: on failure
 */
esp_err_t esp_zb_zcl_add_privilege_command(uint8_t endpoint, uint16_t cluster, uint16_t command);

/**
 * @brief Delete the privilege command from the @p cluster of @p endpoint
 *
 * @param[in] endpoint The specific endpoint for @p cluster
 * @param[in] cluster The specific cluster for @p command
 * @param[in] command The specific command ID will be deleted so that the stack will handle the command rather than user.
 * @return
 *      -   True: On success
 *      -   False: Nothing to delete
 */
bool esp_zb_zcl_delete_privilege_command(uint8_t endpoint, uint16_t cluster, uint16_t command);

/**
 * @brief Reset all endpoints to factory default
 *
 * @note If @p cb is not set or @p cb return NULL, the default attribute value will be set to zero
 * @param[in] reset_report Whether reset report of clusters or not
 * @param[in] cb The user can utilize the callback to set default attribute value
 *
 * @return
 *      - ESP_OK: on success
 *      - ESP_FAIL: on failed
 */
esp_err_t esp_zb_zcl_reset_all_endpoints_to_factory_default(bool reset_report, esp_zb_zcl_reset_default_attr_callback_t cb);

/**
 * @brief Reset endpoint to factory default
 *
 * @note If @p cb is not set or @p cb return NULL, the default attribute value will be set to zero
 * @param[in] endpoint      The endpoint identifier which will be reset
 * @param[in] reset_report  Whether reset report of clusters or not
 * @param[in] cb The user can utilize the callback to set default attribute value
 *
 * @return
 *      - ESP_OK: on success
 *      - ESP_FAIL: on failed
 */
esp_err_t esp_zb_zcl_reset_endpoint_to_factory_default(uint8_t endpoint, bool reset_report, esp_zb_zcl_reset_default_attr_callback_t cb);

/**
 * @brief Reset the NVRAM and ZCL data to factory default
 *
 */
void esp_zb_zcl_reset_nvram_to_factory_default(void);

/**
 * @brief Register a Zigbee device.
 *
 * @note
 *      1. After successful registration, the SDK will retain a copy of the whole data model,
 *         the \p ep_list will be freed.
 *      2. For any lists (e.g. ``esp_zb_cluster_list_t`` and ``esp_zb_attribute_list_t``) added to the data
 *         modal should only be created and modified by the API.
 *      3. Please DO NOT reuse ANY of lists in the data mode. If you have two identical stuff (e.g. two endpoints
 *         with identical clusters), please create/add them twice.
 *
 * @param[in] ep_list  An endpoint list which wants to register, see @ref esp_zb_ep_list_s
 *
 * @return
 *      - ESP_OK on success
 *
 */
esp_err_t esp_zb_device_register(esp_zb_ep_list_t *ep_list);

#ifdef __cplusplus
}
#endif
