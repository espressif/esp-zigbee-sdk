/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/zcl_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration for ZCL Core Action Callback Identifier
 * @anchor ezb_zcl_core_action_callback_id_e
 *
 * This enumeration defines the identifiers for various ZCL core action callbacks, when specific ZCL
 * events are triggered or command request/response are received. The callback registered by
 * ezb_zcl_core_action_handler_register() will be triggered with these identifiers and the corresponding message structure type.
 *
 */
enum ezb_zcl_core_action_callback_id_e {
    /** A callback ID triggered when an application-related attribute is changed.
     * see @ref ezb_zcl_set_attr_value_message_s.
     */
    EZB_ZCL_CORE_SET_ATTR_VALUE_CB_ID,

    /** A callback ID triggered when a ZCL general ReadAttribute response is received.
     * see @ref ezb_zcl_cmd_read_attr_rsp_message_s.
     */
    EZB_ZCL_CORE_READ_ATTR_RSP_CB_ID,

    /** A callback ID triggered when a ZCL general WriteAttribute response is received.
     * see @ref ezb_zcl_cmd_write_attr_rsp_message_s.
     */
    EZB_ZCL_CORE_WRITE_ATTR_RSP_CB_ID,

    /** A callback ID triggered when a ZCL general ConfigureReporting response is received.
     * see @ref ezb_zcl_cmd_config_report_rsp_message_s.
     */
    EZB_ZCL_CORE_CONFIG_REPORT_RSP_CB_ID,

    /** A callback ID triggered when a ZCL general ReadReportingConfiguration response is received.
     * see @ref ezb_zcl_cmd_read_report_config_rsp_message_s.
     */
    EZB_ZCL_CORE_READ_REPORT_CONFIG_RSP_CB_ID,

    /** A callback ID triggered when a ZCL General ReportAttribute command is received.
     * see @ref ezb_zcl_cmd_report_attr_message_s.
     */
    EZB_ZCL_CORE_REPORT_ATTR_CB_ID,

    /** A callback ID triggered when a ZCL general DiscoverAttributes response is received.
     * see @ref ezb_zcl_cmd_discover_attributes_rsp_message_s.
     */
    EZB_ZCL_CORE_DISC_ATTR_RSP_CB_ID,

    /** A callback ID triggered when a ZCL general Discover response is received.
     * see @ref ezb_zcl_cmd_discover_commands_rsp_message_s.
     */
    EZB_ZCL_CORE_DISC_CMD_RSP_CB_ID,

    /** A callback ID triggered when a ZCL general DefaultResponse response is received.
     * see @ref ezb_zcl_cmd_default_rsp_message_s.
     */
    EZB_ZCL_CORE_DEFAULT_RSP_CB_ID,

    /** A callback ID triggered when a ZCL command is received with Manufacturer-Specific code.
     * see @ref ezb_zcl_manuf_spec_cmd_message_s.
     */
    EZB_ZCL_CORE_MANUF_SPEC_CMD_CB_ID,

    /** A callback ID triggered when a ZCL Identify IdentifyEffect command is received.
     * see @ref ezb_zcl_identify_effect_message_s.
     */
    EZB_ZCL_CORE_IDENTIFY_EFFECT_CB_ID,

    /** A callback ID triggered when a ZCL Basic ResetToFactoryDefault command is received.
     * see @ref ezb_zcl_basic_reset_factory_default_message_s.
     */
    EZB_ZCL_CORE_BASIC_RESET_TO_FACTORY_DEFAULT_CB_ID,

    /** A callback ID triggered when a ZCL ON_OFF OffWithEffect command is received.
     * see @ref ezb_zcl_on_off_off_with_effect_message_s.
     */
    EZB_ZCL_CORE_ON_OFF_OFF_WITH_EFFECT_CB_ID,

    /** A callback ID triggered when a ZCL Groups AddGroup command is received.
     * see @ref ezb_zcl_groups_add_group_rsp_message_s.
     */
    EZB_ZCL_CORE_GROUPS_ADD_GROUP_RSP_CB_ID,

    /** A callback ID triggered when a ZCL Groups ViewGroup command is received.
     * see @ref ezb_zcl_groups_view_group_rsp_message_s.
     */
    EZB_ZCL_CORE_GROUPS_VIEW_GROUP_RSP_CB_ID,

    /** A callback ID triggered when a ZCL Groups GetGroupMembership command is received.
     * see @ref ezb_zcl_groups_get_group_membership_rsp_message_s.
     */
    EZB_ZCL_CORE_GROUPS_GET_GROUP_MEMBERSHIP_RSP_CB_ID,

    /** A callback ID triggered when a ZCL Groups RemoveGroup command is received.
     * see @ref ezb_zcl_groups_remove_group_rsp_message_s.
     */
    EZB_ZCL_CORE_GROUPS_REMOVE_GROUP_RSP_CB_ID,
    /** A callback ID triggered when a ZCL Scenes OperateScene command is received.
     * see @ref ezb_zcl_scenes_operate_scene_rsp_message_s.
     */
    EZB_ZCL_CORE_SCENES_OPERATE_SCENE_RSP_CB_ID,

    /** A callback ID triggered when a ZCL Scenes ViewScene command is received.
     * see @ref ezb_zcl_scenes_view_scene_rsp_message_s.
     */
    EZB_ZCL_CORE_SCENES_VIEW_SCENE_RSP_CB_ID,

    /** A callback ID triggered when a ZCL Scenes GetSceneMembership command is received.
     * see @ref ezb_zcl_scenes_get_scene_membership_rsp_message_s.
     */
    EZB_ZCL_CORE_SCENES_GET_SCENE_MEMBERSHIP_RSP_CB_ID,

    /** A callback ID triggered when a ZCL Scenes StoreScene command is received.
     * see @ref ezb_zcl_scenes_store_scene_message_s.
     */
    EZB_ZCL_CORE_SCENES_STORE_SCENE_CB_ID,

    /** A callback ID triggered when a ZCL Scenes RecallScene command is received.
     * see @ref ezb_zcl_scenes_recall_scene_message_s.
     */
    EZB_ZCL_CORE_SCENES_RECALL_SCENE_CB_ID,

    /** A callback ID triggered when a ZCL DoorLock Lock command is received.
     * see @ref ezb_zcl_door_lock_lock_door_message_s.
     */
    EZB_ZCL_CORE_DOOR_LOCK_LOCK_DOOR_CB_ID,

    /** A callback ID triggered when a ZCL DoorLock Unlock command is received.
     * see @ref ezb_zcl_door_lock_unlock_door_message_t.
     */
    EZB_ZCL_CORE_DOOR_LOCK_UNLOCK_DOOR_CB_ID,

    /** A callback ID triggered when a ZCL DoorLock LockResponse command is received.
     * see @ref ezb_zcl_door_lock_lock_door_rsp_message_s.
     */
    EZB_ZCL_CORE_DOOR_LOCK_LOCK_DOOR_RSP_CB_ID,

    /** A callback ID triggered when a ZCL DoorLock UnlockResponse command is received.
     * see @ref ezb_zcl_door_lock_unlock_door_rsp_message_t.
     */
    EZB_ZCL_CORE_DOOR_LOCK_UNLOCK_DOOR_RSP_CB_ID,

    /** A callback ID triggered when a ZCL WindowCovering Movement command is received.
     * see @ref ezb_zcl_window_covering_movement_message_s.
     */
    EZB_ZCL_CORE_WINDOW_COVERING_MOVEMENT_CB_ID,

    /** A callback ID triggered when a ZCL ColorControl ColorModeChange command is received.
     * see @ref ezb_zcl_color_control_color_mode_change_message_s.
     */
    EZB_ZCL_CORE_COLOR_CONTROL_COLOR_MODE_CHANGE_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE Arm command is received.
     * see @ref ezb_zcl_ias_ace_arm_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_ARM_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE Bypass command is received.
     * see @ref ezb_zcl_ias_ace_bypass_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_BYPASS_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE Emergency command is received.
     * see @ref ezb_zcl_ias_ace_emergency_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_EMERGENCY_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE Fire command is received.
     * see @ref ezb_zcl_ias_ace_emergency_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_FIRE_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE Panic command is received.
     * see @ref ezb_zcl_ias_ace_emergency_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_PANIC_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE GetPanelStatus command is received.
     * see @ref ezb_zcl_ias_ace_get_panel_status_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_GET_PANEL_STATUS_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE GetZoneStatus command is received.
     * see @ref ezb_zcl_ias_ace_get_zone_status_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_GET_ZONE_STATUS_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE ArmResponse command is received.
     * see @ref ezb_zcl_ias_ace_arm_rsp_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_ARM_RSP_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE GetZoneIdMapResponse command is received.
     * see @ref ezb_zcl_ias_ace_get_zone_id_map_rsp_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_GET_ZONE_ID_MAP_RSP_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE GetZoneInfoResponse command is received.
     * see @ref ezb_zcl_ias_ace_get_zone_info_rsp_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_GET_ZONE_INFO_RSP_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE ZoneStatusChanged command is received.
     * see @ref ezb_zcl_ias_ace_zone_status_changed_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_ZONE_STATUS_CHANGED_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE PanelStatusChanged command is received.
     * see @ref ezb_zcl_ias_ace_panel_status_changed_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_PANEL_STATUS_CHANGED_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE GetPanelStatusResponse command is received.
     * see @ref ezb_zcl_ias_ace_get_panel_status_rsp_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_GET_PANEL_STATUS_RSP_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE SetBypassedZoneListResponse command is received.
     * see @ref ezb_zcl_ias_ace_set_bypassed_zone_list_rsp_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_SET_BYPASSED_ZONE_LIST_RSP_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE BypassResponse command is received.
     * see @ref ezb_zcl_ias_ace_bypass_rsp_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_BYPASS_RSP_CB_ID,

    /** A callback ID triggered when a ZCL IAS ACE GetZoneStatusResponse command is received.
     * see @ref ezb_zcl_ias_ace_get_zone_status_rsp_message_s.
     */
    EZB_ZCL_CORE_IAS_ACE_GET_ZONE_STATUS_RSP_CB_ID,

    /** A callback ID triggered when a ZCL IAS WD StartWarning command is received.
     * see @ref ezb_zcl_ias_wd_start_warning_message_s.
     */
    EZB_ZCL_CORE_IAS_WD_START_WARNING_CB_ID,

    /** A callback ID triggered when a ZCL IAS WD Squawk command is received.
     * see @ref ezb_zcl_ias_wd_squawk_message_s.
     */
    EZB_ZCL_CORE_IAS_WD_SQUAWK_CB_ID,

    /** A callback ID triggered when a ZCL IAS Zone InitiateTestMode command is received.
     * see @ref ezb_zcl_ias_zone_initiate_test_mode_message_s.
     */
    EZB_ZCL_CORE_IAS_ZONE_INIT_TEST_MODE_CB_ID,

    /** A callback ID triggered when a ZCL IAS Zone InitiateNormalMode command is received.
     * see @ref ezb_zcl_ias_zone_initiate_normal_mode_message_s.
     */
    EZB_ZCL_CORE_IAS_ZONE_INIT_NORMAL_MODE_CB_ID,

    /** A callback ID triggered when a ZCL IAS Zone EnrollRequest command is received.
     * see @ref ezb_zcl_ias_zone_enroll_req_message_s.
     */
    EZB_ZCL_CORE_IAS_ZONE_ENROLL_CB_ID,

    /** A callback ID triggered when a ZCL IAS Zone EnrollResponse command is received.
     * see @ref ezb_zcl_ias_zone_enroll_rsp_message_s.
     */
    EZB_ZCL_CORE_IAS_ZONE_ENROLL_RSP_CB_ID,

    /** A callback ID triggered when a ZCL IAS Zone StatusChangeNotification command is received.
     * see @ref ezb_zcl_ias_zone_status_change_notif_message_s.
     */
    EZB_ZCL_CORE_IAS_ZONE_STATUS_CHANGE_NOTIF_CB_ID,

    /** A callback ID triggered when a ZCL Alarms Alarm command is received.
     * see @ref ezb_zcl_alarms_alarm_cmd_message_s.
     */
    EZB_ZCL_CORE_ALARMS_ALARM_CB_ID,

    /** A callback ID triggered when a ZCL Alarms GetAlarmResponse command is received.
     * see @ref ezb_zcl_alarms_get_alarm_rsp_message_s.
     */
    EZB_ZCL_CORE_ALARMS_GET_ALARM_RSP_CB_ID,

    /** A callback ID triggered when a ZCL Alarms ResetAlarm command is received.
     * see @ref ezb_zcl_alarms_reset_alarm_message_s.
     */
    EZB_ZCL_CORE_ALARMS_RESET_ALARM_CB_ID,

    /** A callback ID triggered when a ZCL Alarms ResetAllAlarms command is received.
     * see @ref ezb_zcl_alarms_reset_all_alarms_message_s.
     */
    EZB_ZCL_CORE_ALARMS_RESET_ALL_ALARMS_CB_ID,

    /** A callback ID triggered when a ZCL Thermostat Setpoint command is received.
     * see @ref ezb_zcl_thermostat_setpoint_message_s.
     */
    EZB_ZCL_CORE_THERMOSTAT_SETPOINT_CB_ID,

    /** A callback ID triggered when a ZCL Thermostat SetWeeklySchedule command is received.
     * see @ref ezb_zcl_thermostat_set_weekly_schedule_message_s.
     */
    EZB_ZCL_CORE_THERMOSTAT_SET_WEEKLY_SCHEDULE_CB_ID,

    /** A callback ID triggered when a ZCL Thermostat GetWeeklyScheduleResponse command is received.
     * see @ref ezb_zcl_thermostat_get_weekly_schedule_rsp_message_s.
     */
    EZB_ZCL_CORE_THERMOSTAT_GET_WEEKLY_SCHEDULE_RSP_CB_ID,

    /** A callback ID triggered when a ZCL OTA Upgrade Client Progress command is received.
     * see @ref ezb_zcl_ota_upgrade_client_progress_message_s.
     */
    EZB_ZCL_CORE_OTA_UPGRADE_CLIENT_PROGRESS_CB_ID,

    /** A callback ID triggered when a ZCL OTA Upgrade QueryNextImageResponse command is received.
     * see @ref ezb_zcl_ota_upgrade_query_next_image_rsp_message_s.
     */
    EZB_ZCL_CORE_OTA_UPGRADE_QUERY_NEXT_IMAGE_RSP_CB_ID,

    /** A callback ID triggered when a ZCL OTA Upgrade Server Progress command is received.
     * see @ref ezb_zcl_ota_upgrade_server_progress_message_s.
     */
    EZB_ZCL_CORE_OTA_UPGRADE_SERVER_PROGRESS_CB_ID,

    /** A callback ID triggered when a ZCL PollControl CheckIn command is received.
     * see @ref ezb_zcl_poll_control_check_in_message_s.
     */
    EZB_ZCL_CORE_POLL_CONTROL_CHECK_IN_CB_ID,

    /** A callback ID triggered when a ZCL ElectricalMeasurement GetProfileInfo command is received.
     * see @ref ezb_zcl_electrical_measurement_get_prof_info_message_s.
     */
    EZB_ZCL_CORE_ELECTRICAL_MEASUREMENT_GET_PROF_INFO_CB_ID,

    /** A callback ID triggered when a ZCL ElectricalMeasurement GetMeasurementProfile command is received.
     * see @ref ezb_zcl_electrical_measurement_get_meas_prof_message_s.
     */
    EZB_ZCL_CORE_ELECTRICAL_MEASUREMENT_GET_MEAS_PROF_CB_ID,

    /** A callback ID triggered when a ZCL ElectricalMeasurement GetProfileInfoResponse command is received.
     * see @ref ezb_zcl_electrical_measurement_get_prof_info_rsp_message_s.
     */
    EZB_ZCL_CORE_ELECTRICAL_MEASUREMENT_GET_PROF_INFO_RSP_CB_ID,

    /** A callback ID triggered when a ZCL ElectricalMeasurement GetMeasurementProfileResponse command is received.
     * GetMeasurementProfileResponse command is received.
     * see @ref ezb_zcl_electrical_measurement_get_meas_prof_rsp_message_s.
     */
    EZB_ZCL_CORE_ELECTRICAL_MEASUREMENT_GET_MEAS_PROF_RSP_CB_ID,

    /** A callback ID triggered when a ZCL Metering GetProfile command is received.
     * see @ref ezb_zcl_metering_get_profile_req_message_s.
     */
    EZB_ZCL_CORE_METERING_GET_PROFILE_CB_ID,

    /** A callback ID triggered when a ZCL Metering GetProfileResponse command is received.
     * see @ref ezb_zcl_metering_get_profile_rsp_message_s.
     */
    EZB_ZCL_CORE_METERING_GET_PROFILE_RSP_CB_ID,

    /** A callback ID triggered when a ZCL Metering RequestFastPollMode command is received.
     * see @ref ezb_zcl_metering_request_fast_poll_mode_req_message_s.
     */
    EZB_ZCL_CORE_METERING_REQUEST_FAST_POLL_MODE_CB_ID,

    /** A callback ID triggered when a ZCL Metering RequestFastPollModeResponse command is received.
     * see @ref ezb_zcl_metering_request_fast_poll_mode_rsp_message_s.
     */
    EZB_ZCL_CORE_METERING_REQUEST_FAST_POLL_MODE_RSP_CB_ID,

    /** A callback ID triggered when a ZCL Metering GetSnapshot command is received.
     * see @ref ezb_zcl_metering_get_snapshot_req_message_s.
     */
    EZB_ZCL_CORE_METERING_GET_SNAPSHOT_CB_ID,

    /** A callback ID triggered when a ZCL Metering PublishSnapshot command is received.
     * see @ref ezb_zcl_metering_publish_snapshot_command_message_s.
     */
    EZB_ZCL_CORE_METERING_PUBLISH_SNAPSHOT_CB_ID,

    /** A callback ID triggered when a ZCL Metering GetSampledData command is received.
     * see @ref ezb_zcl_metering_get_sampled_data_req_message_s.
     */
    EZB_ZCL_CORE_METERING_GET_SAMPLED_DATA_CB_ID,

    /** A callback ID triggered when a ZCL Metering GetSampledDataResponse command is received.
     * see @ref ezb_zcl_metering_get_sampled_data_rsp_message_s.
     */
    EZB_ZCL_CORE_METERING_GET_SAMPLED_DATA_RSP_CB_ID,

    /** A callback ID triggered when a ZCL Price GetCurrentPrice command is received.
     * see @ref ezb_zcl_price_get_current_price_message_s.
     */
    EZB_ZCL_CORE_PRICE_GET_CURRENT_PRICE_CB_ID,

    /** A callback ID triggered when a ZCL Price GetScheduledPrices command is received.
     * see @ref ezb_zcl_price_get_scheduled_prices_message_s.
     */
    EZB_ZCL_CORE_PRICE_GET_SCHEDULED_PRICES_CB_ID,

    /** A callback ID triggered when a ZCL Price GetTierLabels command is received.
     * see @ref ezb_zcl_price_get_tier_labels_message_s.
     */
    EZB_ZCL_CORE_PRICE_GET_TIER_LABELS_CB_ID,

    /** A callback ID triggered when a ZCL Price PriceAck command is received.
     * see @ref ezb_zcl_price_price_ack_message_s.
     */
    EZB_ZCL_CORE_PRICE_PRICE_ACK_CB_ID,

    /** A callback ID triggered when a ZCL Price PublishPrice command is received.
     * see @ref ezb_zcl_price_publish_price_message_s.
     */
    EZB_ZCL_CORE_PRICE_PUBLISH_PRICE_CB_ID,

    /** A callback ID triggered when a ZCL Price PublishTierLabels command is received.
     * see @ref ezb_zcl_price_publish_tier_labels_message_s.
     */
    EZB_ZCL_CORE_PRICE_PUBLISH_TIER_LABELS_CB_ID,

    /** A callback ID triggered when a ZCL Touchlink EpInfo command is received.
     * see @ref ezb_zcl_touchlink_ep_info_message_s.
     */
    EZB_ZCL_CORE_TOUCHLINK_EP_INFO_CB_ID,

    /** A callback ID triggered when a ZCL Touchlink GetGroupIdsResponse command is received.
     * see @ref ezb_zcl_touchlink_get_group_ids_rsp_message_s.
     */
    EZB_ZCL_CORE_TOUCHLINK_GET_GROUP_IDS_RSP_CB_ID,

    /** A callback ID triggered when a ZCL Touchlink GetEndpointListResponse command is received.
     * see @ref ezb_zcl_touchlink_get_ep_list_rsp_message_s.
     */
    EZB_ZCL_CORE_TOUCHLINK_GET_ENDPOINT_LIST_RSP_CB_ID,

    /** The end of the ZCL core action callback IDs. */
    EZB_ZCL_CORE_CB_ID_END,
};

/**
 * @brief The type of the ZCL core action callback identifier.
 */
typedef uint32_t ezb_zcl_core_action_callback_id_t;

/**
 * @brief A raw ZCL frame, triggered when a raw ZCL frame is received.
 */
typedef struct ezb_zcl_raw_frame_s {
    ezb_zcl_cmd_hdr_t *header;         /*!< The header of the raw ZCL frame. */
    uint16_t           payload_length; /*!< The payload length of the raw ZCL frame. */
    uint8_t           *payload;        /*!< The payload of the raw ZCL frame. */
} ezb_zcl_raw_frame_t;

/**
 * @brief A callback for ZCL core action, triggered when ZCL command needs to be notified to the application.
 *
 * This callback is invoked by the ZCL stack when a command is received or a response
 * is received for a previously sent command. The message structure type depends on
 * the callback_id parameter.
 *
 * @param callback_id  The action callback identifier. See @ref ezb_zcl_core_action_callback_id_e.
 * @param message      Pointer to the message data. The structure type depends on callback_id.
 */
typedef void (*ezb_zcl_core_action_callback_t)(ezb_zcl_core_action_callback_id_t callback_id, void *message);

/**
 * @brief Register a ZCL core action callback handler.
 *
 * This function registers a callback handler that will be invoked when ZCL commands
 * are received or responses are received. Only one callback handler can be registered
 * at a time. Register NULL to unregister the current handler.
 *
 * @param cb Function pointer to the action callback handler, or NULL to unregister.
 */
void ezb_zcl_core_action_handler_register(ezb_zcl_core_action_callback_t cb);

/**
 * @brief A callback for ZCL raw frame, triggered when a raw ZCL frame is received.
 *
 * This callback is invoked by the ZCL stack when a raw ZCL frame is received. The callback
 * is used to notify the application about the raw ZCL frame.
 *
 * @param raw_frame Pointer to the raw ZCL frame.
 * @return True if the raw ZCL frame is processed successfully and the stack should drop this frame, false otherwise.
 */
typedef bool (*ezb_zcl_raw_frame_callback_t)(const ezb_zcl_raw_frame_t *raw_frame);

/**
 * @brief Register a ZCL raw frame callback handler.
 *
 * This function registers a callback handler that will be invoked when a raw ZCL frame is received.
 * Only one callback handler can be registered at a time. Register NULL to unregister the current handler.
 *
 * @param cb Function pointer to the raw frame callback handler, or NULL to unregister.
 */
void ezb_zcl_raw_command_handler_register(ezb_zcl_raw_frame_callback_t cb);

#ifdef __cplusplus
} /*  extern "C" */
#endif
