/*
 * SPDX-FileCopyrightText: 2025-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/zcl.h" instead!"

#include <ezbee/zcl/zcl_core.h>

#include "esp_zigbee_attribute.h"
#include "esp_zigbee_cluster.h"
#include "esp_zigbee_endpoint.h"

#include "zcl/esp_zigbee_zcl_common.h"
#include "zcl/esp_zigbee_zcl_command.h"
#include "zcl/esp_zigbee_zcl_basic.h"
#include "zcl/esp_zigbee_zcl_identify.h"
#include "zcl/esp_zigbee_zcl_level.h"
#include "zcl/esp_zigbee_zcl_on_off.h"
#include "zcl/esp_zigbee_zcl_scenes.h"
#include "zcl/esp_zigbee_zcl_groups.h"
#include "zcl/esp_zigbee_zcl_price.h"
#include "zcl/esp_zigbee_zcl_alarms.h"
#include "zcl/esp_zigbee_zcl_time.h"
#include "zcl/esp_zigbee_zcl_window_covering.h"
#include "zcl/esp_zigbee_zcl_door_lock.h"
#include "zcl/esp_zigbee_zcl_occupancy_sensing.h"
#include "zcl/esp_zigbee_zcl_thermostat.h"
#include "zcl/esp_zigbee_zcl_analog_input.h"
#include "zcl/esp_zigbee_zcl_analog_output.h"
#include "zcl/esp_zigbee_zcl_analog_value.h"
#include "zcl/esp_zigbee_zcl_binary_input.h"
#include "zcl/esp_zigbee_zcl_binary_output.h"
#include "zcl/esp_zigbee_zcl_binary_value.h"
#include "zcl/esp_zigbee_zcl_multistate_input.h"
#include "zcl/esp_zigbee_zcl_multistate_output.h"
#include "zcl/esp_zigbee_zcl_multistate_value.h"
#include "zcl/esp_zigbee_zcl_color_control.h"
#include "zcl/esp_zigbee_zcl_dehumidification_control.h"
#include "zcl/esp_zigbee_zcl_device_temp_config.h"
#include "zcl/esp_zigbee_zcl_carbon_dioxide_measurement.h"
#include "zcl/esp_zigbee_zcl_ph_measurement.h"
#include "zcl/esp_zigbee_zcl_wind_speed_measurement.h"
#include "zcl/esp_zigbee_zcl_flow_meas.h"
#include "zcl/esp_zigbee_zcl_illuminance_meas.h"
#include "zcl/esp_zigbee_zcl_pressure_meas.h"
#include "zcl/esp_zigbee_zcl_humidity_meas.h"
#include "zcl/esp_zigbee_zcl_ec_measurement.h"
#include "zcl/esp_zigbee_zcl_pm2_5_measurement.h"
#include "zcl/esp_zigbee_zcl_meter_identification.h"
#include "zcl/esp_zigbee_zcl_metering.h"
#include "zcl/esp_zigbee_zcl_on_off_switch_config.h"
#include "zcl/esp_zigbee_zcl_power_config.h"
#include "zcl/esp_zigbee_zcl_shade_config.h"
#include "zcl/esp_zigbee_zcl_temperature_meas.h"
#include "zcl/esp_zigbee_zcl_commissioning.h"
#include "zcl/esp_zigbee_zcl_ias_zone.h"
#include "zcl/esp_zigbee_zcl_ias_wd.h"
#include "zcl/esp_zigbee_zcl_ias_ace.h"
#include "zcl/esp_zigbee_zcl_drlc.h"
#include "zcl/esp_zigbee_zcl_electrical_meas.h"
#include "zcl/esp_zigbee_zcl_diagnostics.h"
#include "zcl/esp_zigbee_zcl_ota.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Break Change: Not supported*/
#define esp_zb_zcl_add_privilege_command(endpoint, cluster, command) ESP_ERR_NOT_SUPPORTED
/* Break Change: Not supported*/
#define esp_zb_zcl_delete_privilege_command(endpoint, cluster, command) false
/* Break Change: Not supported, buffer id is not supported in EZB*/
#define esp_zb_device_cb_id_handler_register(cb)
/* Break Change: Not supported, buffer id is not supported in EZB*/
#define esp_zb_raw_command_handler_register(cb)
/* Break Change: Not supported, notify in core action handler*/
#define esp_zb_identify_notify_handler_register(endpoint, cb)

extern esp_err_t esp_zigbee_err_to_esp(ezb_err_t error);

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
    ESP_ZB_CORE_SET_ATTR_VALUE_CB_ID                    = EZB_ZCL_CORE_SET_ATTR_VALUE_CB_ID,   /*!< Set attribute value, refer to esp_zb_zcl_set_attr_value_message_t */
    ESP_ZB_CORE_SCENES_STORE_SCENE_CB_ID                = EZB_ZCL_CORE_SCENES_STORE_SCENE_CB_ID,   /*!< Store scene, refer to esp_zb_zcl_store_scene_message_t */
    ESP_ZB_CORE_SCENES_RECALL_SCENE_CB_ID               = EZB_ZCL_CORE_SCENES_RECALL_SCENE_CB_ID,   /*!< Recall scene, refer to esp_zb_zcl_recall_scene_message_t */
    ESP_ZB_CORE_IAS_ZONE_ENROLL_RESPONSE_VALUE_CB_ID    = EZB_ZCL_CORE_IAS_ZONE_ENROLL_RSP_CB_ID,   /*!< IAS Zone enroll response, refer to esp_zb_zcl_ias_zone_enroll_response_message_t */
    ESP_ZB_CORE_THERMOSTAT_VALUE_CB_ID                  = EZB_ZCL_CORE_THERMOSTAT_SETPOINT_CB_ID,   /*!< Thermostat value, refer to esp_zb_zcl_thermostat_value_message_t */
    ESP_ZB_CORE_METERING_GET_PROFILE_CB_ID              = EZB_ZCL_CORE_METERING_GET_PROFILE_CB_ID,   /*!< Metering get profile, refer to esp_zb_zcl_metering_get_profile_message_t */
    ESP_ZB_CORE_METERING_GET_PROFILE_RESP_CB_ID         = EZB_ZCL_CORE_METERING_GET_PROFILE_RSP_CB_ID,   /*!< Metering get profile response, refer to esp_zb_zcl_metering_get_profile_resp_message_t */
    ESP_ZB_CORE_METERING_REQ_FAST_POLL_MODE_CB_ID       = EZB_ZCL_CORE_METERING_REQUEST_FAST_POLL_MODE_CB_ID,   /*!< Metering request fast poll mode, refer to esp_zb_zcl_metering_request_fast_poll_mode_message_t */
    ESP_ZB_CORE_METERING_REQ_FAST_POLL_MODE_RESP_CB_ID  = EZB_ZCL_CORE_METERING_REQUEST_FAST_POLL_MODE_RSP_CB_ID,   /*!< Metering request fast poll mode response, refer to esp_zb_zcl_metering_request_fast_poll_mode_resp_message_t */
    ESP_ZB_CORE_METERING_GET_SNAPSHOT_CB_ID             = EZB_ZCL_CORE_METERING_GET_SNAPSHOT_CB_ID,   /*!< Metering get snapshot, refer to esp_zb_zcl_metering_get_snapshot_message_t */
    ESP_ZB_CORE_METERING_PUBLISH_SNAPSHOT_CB_ID         = EZB_ZCL_CORE_METERING_PUBLISH_SNAPSHOT_CB_ID,   /*!< Metering publish snapshot, refer to esp_zb_zcl_metering_publish_snapshot_message_t */
    ESP_ZB_CORE_METERING_GET_SAMPLED_DATA_CB_ID         = EZB_ZCL_CORE_METERING_GET_SAMPLED_DATA_CB_ID,   /*!< Metering get sampled data, refer to esp_zb_zcl_metering_get_sampled_data_message_t */
    ESP_ZB_CORE_METERING_GET_SAMPLED_DATA_RESP_CB_ID    = EZB_ZCL_CORE_METERING_GET_SAMPLED_DATA_RSP_CB_ID,   /*!< Metering get sampled data response, refer to esp_zb_zcl_metering_get_sampled_data_resp_message_t */
    ESP_ZB_CORE_DOOR_LOCK_LOCK_DOOR_CB_ID               = EZB_ZCL_CORE_DOOR_LOCK_LOCK_DOOR_CB_ID,   /*!< Lock/unlock door request, refer to esp_zb_zcl_door_lock_lock_door_message_t */
    ESP_ZB_CORE_DOOR_LOCK_LOCK_DOOR_RESP_CB_ID          = EZB_ZCL_CORE_DOOR_LOCK_LOCK_DOOR_RSP_CB_ID,   /*!< Lock/unlock door response, refer to esp_zb_zcl_door_lock_lock_door_resp_message_t */
    ESP_ZB_CORE_IDENTIFY_EFFECT_CB_ID                   = EZB_ZCL_CORE_IDENTIFY_EFFECT_CB_ID,   /*!< Identify triggers effect request, refer to esp_zb_zcl_identify_effect_message_t */
    ESP_ZB_CORE_BASIC_RESET_TO_FACTORY_RESET_CB_ID      = EZB_ZCL_CORE_BASIC_RESET_TO_FACTORY_DEFAULT_CB_ID,   /*!< Reset all clusters of endpoint to factory default, refer to esp_zb_zcl_basic_reset_factory_default_message_t  */
    ESP_ZB_CORE_PRICE_GET_CURRENT_PRICE_CB_ID           = EZB_ZCL_CORE_PRICE_GET_CURRENT_PRICE_CB_ID,   /*!< Price get current price, refer to esp_zb_zcl_price_get_current_price_message_t */
    ESP_ZB_CORE_PRICE_GET_SCHEDULED_PRICES_CB_ID        = EZB_ZCL_CORE_PRICE_GET_SCHEDULED_PRICES_CB_ID,   /*!< Price get scheduled prices, refer to esp_zb_zcl_price_get_scheduled_prices_message_t */
    ESP_ZB_CORE_PRICE_GET_TIER_LABELS_CB_ID             = EZB_ZCL_CORE_PRICE_GET_TIER_LABELS_CB_ID,   /*!< Price get tier labels, refer to esp_zb_zcl_price_get_tier_labels_message_t */
    ESP_ZB_CORE_PRICE_PUBLISH_PRICE_CB_ID               = EZB_ZCL_CORE_PRICE_PUBLISH_PRICE_CB_ID,   /*!< Price publish price, refer to esp_zb_zcl_price_publish_price_message_t */
    ESP_ZB_CORE_PRICE_PUBLISH_TIER_LABELS_CB_ID         = EZB_ZCL_CORE_PRICE_PUBLISH_TIER_LABELS_CB_ID,   /*!< Price publish tier labels, refer to esp_zb_zcl_price_publish_tier_labels_message_t */
    ESP_ZB_CORE_PRICE_PRICE_ACK_CB_ID                   = EZB_ZCL_CORE_PRICE_PRICE_ACK_CB_ID,   /*!< Price price acknowledgement, refer to esp_zb_zcl_price_ack_message_t */
    ESP_ZB_CORE_IAS_WD_START_WARNING_CB_ID              = EZB_ZCL_CORE_IAS_WD_START_WARNING_CB_ID,   /*!< IAS WD cluster Start Warning command, refer to esp_zb_zcl_ias_wd_start_warning_message_t */
    ESP_ZB_CORE_IAS_WD_SQUAWK_CB_ID                     = EZB_ZCL_CORE_IAS_WD_SQUAWK_CB_ID,   /*!< IAS WD cluster Squawk command, refer to esp_zb_zcl_ias_wd_squawk_message_t */
    ESP_ZB_CORE_IAS_ACE_ARM_CB_ID                       = EZB_ZCL_CORE_IAS_ACE_ARM_CB_ID,   /*!< IAS ACE cluster Arm command, refer to esp_zb_zcl_ias_ace_arm_message_t */
    ESP_ZB_CORE_IAS_ACE_BYPASS_CB_ID                    = EZB_ZCL_CORE_IAS_ACE_BYPASS_CB_ID,   /*!< IAS ACE cluster Bypass command, refer to esp_zb_zcl_ias_ace_bypass_message_t */
    ESP_ZB_CORE_IAS_ACE_EMERGENCY_CB_ID                 = EZB_ZCL_CORE_IAS_ACE_EMERGENCY_CB_ID,   /*!< IAS ACE cluster Emergency command, refer to esp_zb_zcl_ias_ace_emergency_message_t */
    ESP_ZB_CORE_IAS_ACE_FIRE_CB_ID                      = EZB_ZCL_CORE_IAS_ACE_FIRE_CB_ID,   /*!< IAS ACE cluster Fire command, refer to esp_zb_zcl_ias_ace_fire_message_t */
    ESP_ZB_CORE_IAS_ACE_PANIC_CB_ID                     = EZB_ZCL_CORE_IAS_ACE_PANIC_CB_ID,   /*!< IAS ACE cluster Panic command, refer to esp_zb_zcl_ias_ace_panic_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_PANEL_STATUS_CB_ID          = EZB_ZCL_CORE_IAS_ACE_GET_PANEL_STATUS_CB_ID,   /*!< IAS ACE cluster Get Panel Status command, refer to esp_zb_zcl_ias_ace_get_panel_status_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_ZONE_STATUS_CB_ID           = EZB_ZCL_CORE_IAS_ACE_GET_ZONE_STATUS_CB_ID,   /*!< IAS ACE cluster Get Zone Status command, refer to esp_zb_zcl_ias_ace_get_zone_status_message_t */
    ESP_ZB_CORE_IAS_ACE_ARM_RESP_CB_ID                  = EZB_ZCL_CORE_IAS_ACE_ARM_RSP_CB_ID,   /*!< IAS ACE cluster Arm command response, refer to esp_zb_zcl_ias_ace_arm_response_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_ZONE_ID_MAP_RESP_CB_ID      = EZB_ZCL_CORE_IAS_ACE_GET_ZONE_ID_MAP_RSP_CB_ID,   /*!< IAS ACE cluster Get Zone ID MAP command response, refer to esp_zb_zcl_ias_ace_get_zone_id_map_response_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_ZONE_INFO_RESP_CB_ID        = EZB_ZCL_CORE_IAS_ACE_GET_ZONE_INFO_RSP_CB_ID,   /*!< IAS ACE cluster Get Zone Information command response, refer to esp_zb_zcl_ias_ace_get_zone_info_response_message_t */
    ESP_ZB_CORE_IAS_ACE_ZONE_STATUS_CHANGED_CB_ID       = EZB_ZCL_CORE_IAS_ACE_ZONE_STATUS_CHANGED_CB_ID,   /*!< IAS ACE cluster Zone Status Changed command, refer to esp_zb_zcl_ias_ace_zone_status_changed_message_t */
    ESP_ZB_CORE_IAS_ACE_PANEL_STATUS_CHANGED_CB_ID      = EZB_ZCL_CORE_IAS_ACE_PANEL_STATUS_CHANGED_CB_ID,   /*!< IAS ACE cluster Panel Status Changed command, refer to esp_zb_zcl_ias_ace_panel_status_changed_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_PANEL_STATUS_RESP_CB_ID     = EZB_ZCL_CORE_IAS_ACE_GET_PANEL_STATUS_RSP_CB_ID,   /*!< IAS ACE cluster Get Panel Status command response, refer to esp_zb_zcl_ias_ace_get_panel_status_response_message_t */
    ESP_ZB_CORE_IAS_ACE_SET_BYPASSED_ZONE_LIST_CB_ID    = EZB_ZCL_CORE_IAS_ACE_SET_BYPASSED_ZONE_LIST_RSP_CB_ID,   /*!< IAS ACE cluster Set Bypassed Zone List command, refer to esp_zb_zcl_ias_ace_set_bypassed_zone_list_message_t */
    ESP_ZB_CORE_IAS_ACE_BYPASS_RESP_CB_ID               = EZB_ZCL_CORE_IAS_ACE_BYPASS_RSP_CB_ID,   /*!< IAS ACE cluster Bypass command response, refer to esp_zb_zcl_ias_ace_bypass_response_message_t */
    ESP_ZB_CORE_IAS_ACE_GET_ZONE_STATUS_RESP_CB_ID      = EZB_ZCL_CORE_IAS_ACE_GET_ZONE_STATUS_RSP_CB_ID,   /*!< IAS ACE cluster Get Zone Status command response, refer to esp_zb_zcl_ias_ace_get_zone_status_response_message_t */
    ESP_ZB_CORE_WINDOW_COVERING_MOVEMENT_CB_ID          = EZB_ZCL_CORE_WINDOW_COVERING_MOVEMENT_CB_ID,   /*!< Window covering movement command, refer to esp_zb_zcl_window_covering_movement_message_t */
    ESP_ZB_CORE_OTA_UPGRADE_QUERY_IMAGE_RESP_CB_ID      = EZB_ZCL_CORE_OTA_UPGRADE_QUERY_NEXT_IMAGE_RSP_CB_ID,   /*!< OTA upgrade query image response message, refer to esp_zb_zcl_ota_upgrade_query_image_resp_message_t */
    ESP_ZB_CORE_THERMOSTAT_WEEKLY_SCHEDULE_SET_CB_ID    = EZB_ZCL_CORE_THERMOSTAT_SET_WEEKLY_SCHEDULE_CB_ID,   /*!< Thermostat weekly schedule stable set, refer to esp_zb_zcl_thermostat_weekly_schedule_set_message_t */
    ESP_ZB_CORE_POLL_CONTROL_CHECK_IN_REQ_CB_ID         = EZB_ZCL_CORE_POLL_CONTROL_CHECK_IN_CB_ID,   /*!< Poll control cluster CheckInRequest message, refer to esp_zb_zcl_poll_control_check_in_req_message_t */
    ESP_ZB_CORE_ALARMS_RESET_ALARM_CB_ID                = EZB_ZCL_CORE_ALARMS_RESET_ALARM_CB_ID,   /*!< Alarms cluster Reset Alarm command, refer to esp_zb_zcl_alarms_reset_alarm_message_t */
    ESP_ZB_CORE_ALARMS_RESET_ALL_ALARMS_CB_ID           = EZB_ZCL_CORE_ALARMS_RESET_ALL_ALARMS_CB_ID,   /*!< Alarms cluster Reset All Alarms command, refer to esp_zb_zcl_alarms_reset_all_alarms_message_t */
    ESP_ZB_CORE_ALARMS_ALARM_CB_ID                      = EZB_ZCL_CORE_ALARMS_ALARM_CB_ID,   /*!<  Alarms cluster Alarm command, refer to esp_zb_zcl_alarms_alarm_message_t */
    ESP_ZB_CORE_ALARMS_GET_ALARM_RESP_CB_ID             = EZB_ZCL_CORE_ALARMS_GET_ALARM_RSP_CB_ID,   /*!< Alarms cluster Get Alarm Response command, refer to esp_zb_zcl_alarms_get_alarm_resp_message_t */
    ESP_ZB_CORE_CMD_READ_ATTR_RESP_CB_ID                = EZB_ZCL_CORE_READ_ATTR_RSP_CB_ID,   /*!< Read attribute response, refer to esp_zb_zcl_cmd_read_attr_resp_message_t */
    ESP_ZB_CORE_CMD_WRITE_ATTR_RESP_CB_ID               = EZB_ZCL_CORE_WRITE_ATTR_RSP_CB_ID,   /*!< Write attribute response, refer to esp_zb_zcl_cmd_write_attr_resp_message_t */
    ESP_ZB_CORE_CMD_REPORT_CONFIG_RESP_CB_ID            = EZB_ZCL_CORE_CONFIG_REPORT_RSP_CB_ID,   /*!< Configure report response, refer to esp_zb_zcl_cmd_config_report_resp_message_t */
    ESP_ZB_CORE_CMD_READ_REPORT_CFG_RESP_CB_ID          = EZB_ZCL_CORE_READ_REPORT_CONFIG_RSP_CB_ID,   /*!< Read report configuration response, refer to esp_zb_zcl_cmd_read_report_config_resp_message_t */
    ESP_ZB_CORE_CMD_DISC_ATTR_RESP_CB_ID                = EZB_ZCL_CORE_DISC_ATTR_RSP_CB_ID,   /*!< Discover attributes response, refer to esp_zb_zcl_cmd_discover_attributes_resp_message_t */
    ESP_ZB_CORE_CMD_DEFAULT_RESP_CB_ID                  = EZB_ZCL_CORE_DEFAULT_RSP_CB_ID,   /*!< Default response, refer to esp_zb_zcl_cmd_default_resp_message_t */
    ESP_ZB_CORE_CMD_OPERATE_GROUP_RESP_CB_ID            = EZB_ZCL_CORE_GROUPS_ADD_GROUP_RSP_CB_ID,   /*!< Group add/remove group response, refer to esp_zb_zcl_groups_operate_group_resp_message_t */
    ESP_ZB_CORE_CMD_VIEW_GROUP_RESP_CB_ID               = EZB_ZCL_CORE_GROUPS_VIEW_GROUP_RSP_CB_ID,   /*!< Group view response, refer to esp_zb_zcl_groups_view_group_resp_message_t */
    ESP_ZB_CORE_CMD_GET_GROUP_MEMBERSHIP_RESP_CB_ID     = EZB_ZCL_CORE_GROUPS_GET_GROUP_MEMBERSHIP_RSP_CB_ID,   /*!< Group get membership response, refer to esp_zb_zcl_groups_get_group_membership_resp_message_t */
    ESP_ZB_CORE_CMD_OPERATE_SCENE_RESP_CB_ID            = EZB_ZCL_CORE_SCENES_OPERATE_SCENE_RSP_CB_ID,   /*!< Scenes operate response, refer to esp_zb_zcl_scenes_operate_scene_resp_message_t */
    ESP_ZB_CORE_CMD_VIEW_SCENE_RESP_CB_ID               = EZB_ZCL_CORE_SCENES_VIEW_SCENE_RSP_CB_ID,   /*!< Scenes view response, refer to esp_zb_zcl_scenes_view_scene_resp_message_t */
    ESP_ZB_CORE_CMD_GET_SCENE_MEMBERSHIP_RESP_CB_ID     = EZB_ZCL_CORE_SCENES_GET_SCENE_MEMBERSHIP_RSP_CB_ID,   /*!< Scenes get membership response, refer to esp_zb_zcl_scenes_get_scene_membership_resp_message_t */
    ESP_ZB_CORE_CMD_IAS_ZONE_ZONE_ENROLL_REQUEST_ID     = EZB_ZCL_CORE_IAS_ZONE_ENROLL_CB_ID,   /*!< IAS Zone enroll request, refer to esp_zb_zcl_ias_zone_enroll_request_message_t */
    ESP_ZB_CORE_CMD_IAS_ZONE_ZONE_STATUS_CHANGE_NOT_ID  = EZB_ZCL_CORE_IAS_ZONE_STATUS_CHANGE_NOTIF_CB_ID,   /*!< IAS Zone status change notification, refer to esp_zb_zcl_ias_zone_status_change_notification_message_t */
    ESP_ZB_CORE_CMD_THERMOSTAT_GET_WEEKLY_SCHEDULE_RESP_CB_ID = EZB_ZCL_CORE_THERMOSTAT_GET_WEEKLY_SCHEDULE_RSP_CB_ID, /*!< Thermostat cluster get weekly schedule response, refer to esp_zb_zcl_thermostat_get_weekly_schedule_resp_message_t */
    ESP_ZB_CORE_REPORT_ATTR_CB_ID                       = EZB_ZCL_CORE_REPORT_ATTR_CB_ID,   /*!< Attribute Report, refer to esp_zb_zcl_report_attr_message_t */

    ESP_ZB_CORE_OTA_UPGRADE_VALUE_CB_ID = EZB_ZCL_CORE_CB_ID_END + 1,
    ESP_ZB_CORE_OTA_UPGRADE_SRV_STATUS_CB_ID,
    ESP_ZB_CORE_OTA_UPGRADE_SRV_QUERY_IMAGE_CB_ID,
    ESP_ZB_CORE_COMM_RESTART_DEVICE_CB_ID,
    ESP_ZB_CORE_COMM_OPERATE_STARTUP_PARAMS_CB_ID,
    ESP_ZB_CORE_COMM_COMMAND_RESP_CB_ID,
    ESP_ZB_CORE_IAS_ACE_GET_BYPASSED_ZONE_LIST_CB_ID,
    ESP_ZB_CORE_DRLC_LOAD_CONTROL_EVENT_CB_ID,
    ESP_ZB_CORE_DRLC_CANCEL_LOAD_CONTROL_EVENT_CB_ID,
    ESP_ZB_CORE_DRLC_CANCEL_ALL_LOAD_CONTROL_EVENTS_CB_ID,
    ESP_ZB_CORE_DRLC_REPORT_EVENT_STATUS_CB_ID,
    ESP_ZB_CORE_DRLC_GET_SCHEDULED_EVENTS_CB_ID,
    ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_REQ_CB_ID,
    ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_RESP_CB_ID,
    ESP_ZB_CORE_CMD_PRIVILEGE_COMMAND_REQ_CB_ID,
    ESP_ZB_CORE_CMD_PRIVILEGE_COMMAND_RESP_CB_ID,
    ESP_ZB_CORE_CMD_TOUCHLINK_GET_GROUP_ID_RESP_CB_ID,
    ESP_ZB_CORE_CMD_TOUCHLINK_GET_ENDPOINT_LIST_RESP_CB_ID,
    ESP_ZB_CORE_CMD_GREEN_POWER_RECV_CB_ID,

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

typedef void (*esp_zb_zcl_command_send_status_callback_t)(esp_zb_zcl_command_send_status_message_t message);

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
 * @brief Register the callback for the ZCL command send status
 *
 * @param[in] cb The ZCL command send status callback, refer to esp_zb_zcl_command_send_status_callback_t
 */
void esp_zb_zcl_command_send_status_handler_register(esp_zb_zcl_command_send_status_callback_t cb);

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

/* UTC Time */
typedef uint32_t (*get_utc_time_callback_t)(void);
void esp_zb_get_utc_time_callback_register(get_utc_time_callback_t cb);

#ifdef __cplusplus
}
#endif

#else
#error "This file is for compatibility, please include "ezbee/zcl.h"!"
#endif
