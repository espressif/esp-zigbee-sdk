/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/zcl/cluster/ias_ace.h" instead!"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Default value for IAS ACE cluster revision global attribute */
#define ESP_ZB_ZCL_IAS_ACE_CLUSTER_REVISION_DEFAULT ((uint16_t)0x0001u)

/** @brief IAS ACE Zone Table maximum length */
#define ESP_ZB_ZCL_IAS_ACE_ZONE_TABLE_LENGTH      255

/** @brief IAS ACE ZoneType attribute maximum value */
#define ESP_ZB_ZCL_IAS_ACE_ZONE_TYPE_MAX_VALUE    0xfffe

/** @brief IAS ACE ZoneID attribute maximum value */
#define ESP_ZB_ZCL_IAS_ACE_ZONE_ID_MAX_VALUE      0xfe

/** @brief IAS ACE ZoneID attribute default value */
#define ESP_ZB_ZCL_IAS_ACE_ZONE_ID_DEFAULT_VALUE  0

/** @brief IAS ACE Set Zone Address default value */
#define ESP_ZB_ZCL_IAS_ACE_SET_ZONE_ADDRESS_DEFAULT_VALUE(ptr)  (ZB_IEEE_ADDR_COPY(ptr, &g_unknown_ieee_addr))

/** @brief IAS Ace cluster command identifiers */
typedef enum {
    ESP_ZB_ZCL_CMD_IAS_ACE_ARM_ID                    = 0x00,   /**< Arm command */
    ESP_ZB_ZCL_CMD_IAS_ACE_BYPASS_ID                 = 0x01,   /**< Bypass command */
    ESP_ZB_ZCL_CMD_IAS_ACE_EMERGENCY_ID              = 0x02,   /**< Emergency command */
    ESP_ZB_ZCL_CMD_IAS_ACE_FIRE_ID                   = 0x03,   /**< Fire command */
    ESP_ZB_ZCL_CMD_IAS_ACE_PANIC_ID                  = 0x04,   /**< Panic command */
    ESP_ZB_ZCL_CMD_IAS_ACE_GET_ZONE_ID_MAP_ID        = 0x05,   /**< Get Zone ID Map command */
    ESP_ZB_ZCL_CMD_IAS_ACE_GET_ZONE_INFO_ID          = 0x06,   /**< Get Zone Information command */
    ESP_ZB_ZCL_CMD_IAS_ACE_GET_PANEL_STATUS_ID       = 0x07,   /**< Get Panel Status command */
    ESP_ZB_ZCL_CMD_IAS_ACE_GET_BYPASSED_ZONE_LIST_ID = 0x08,   /**< Get Bypassed Zone List command */
    ESP_ZB_ZCL_CMD_IAS_ACE_GET_ZONE_STATUS_ID        = 0x09,   /**< Get Zone Status command */
} esp_zb_zcl_ias_ace_cmd_t;

/** @brief IAS Ace cluster response command identifiers */
typedef enum {
    ESP_ZB_ZCL_CMD_IAS_ACE_ARM_RESP_ID                  = 0x00, /**< Arm Response command */
    ESP_ZB_ZCL_CMD_IAS_ACE_GET_ZONE_ID_MAP_RESP_ID      = 0x01, /**< Get Zone ID Map Response command */
    ESP_ZB_ZCL_CMD_IAS_ACE_GET_ZONE_INFO_RESP_ID        = 0x02, /**< Get Zone Information Response command */
    ESP_ZB_ZCL_CMD_IAS_ACE_ZONE_STATUS_CHANGED_ID       = 0x03, /**< Zone status changed */
    ESP_ZB_ZCL_CMD_IAS_ACE_PANEL_STATUS_CHANGED_ID      = 0x04, /**< Panel status changed */
    ESP_ZB_ZCL_CMD_IAS_ACE_GET_PANEL_STATUS_RESPONSE_ID = 0x05, /**< Get Panel Status Response */
    ESP_ZB_ZCL_CMD_IAS_ACE_SET_BYPASSED_ZONE_LIST_ID    = 0x06, /**< Set Bypassed Zone List */
    ESP_ZB_ZCL_CMD_IAS_ACE_BYPASS_RESPONSE_ID           = 0x07, /**< Bypass Response command. */
    ESP_ZB_ZCL_CMD_IAS_ACE_GET_ZONE_STATUS_RESPONSE_ID  = 0x08, /**< Get Zone Status Response Command. */
} esp_zb_zcl_ias_ace_resp_cmd_t;

/** @brief Values of the Arm Mode */
typedef enum {
    ESP_ZB_ZCL_IAS_ACE_ARM_MODE_DISARM  = 0x00, /**< Disarm */
    ESP_ZB_ZCL_IAS_ACE_ARM_MODE_DAY     = 0x01, /**< Arm Day/Home Zones Only */
    ESP_ZB_ZCL_IAS_ACE_ARM_MODE_NIGHT   = 0x02, /**< Arm Night/Sleep Zones Only */
    ESP_ZB_ZCL_IAS_ACE_ARM_MODE_ALL     = 0x03, /**< Arm All Zones */
} esp_zb_zcl_ias_ace_arm_mode_t;

/** @brief Values of the Arm Notification */
typedef enum {
    ESP_ZB_ZCL_IAS_ACE_ARM_NOTIF_ALL_ZONES_DISARMED           = 0x00,   /**< All Zones Disarmed */
    ESP_ZB_ZCL_IAS_ACE_ARM_NOTIF_ONLY_DAY_HOME_ZONES_ARMED    = 0x01,   /**< Only Day/Home Zones Armed */
    ESP_ZB_ZCL_IAS_ACE_ARM_NOTIF_ONLY_NIGHT_SLEEP_ZONES_ARMED = 0x02,   /**< Only Night/Sleep Zones Armed */
    ESP_ZB_ZCL_IAS_ACE_ARM_NOTIF_ALL_ZONES_ARMED              = 0x03,   /**< All Zones Armed */
    ESP_ZB_ZCL_IAS_ACE_ARM_NOTIF_INVALID_ARM_DISARM_CODE      = 0x04,   /**< Invalid Arm/Disarm Code */
    ESP_ZB_ZCL_IAS_ACE_ARM_NOTIF_NOT_READY_TO_ARM             = 0x05,   /**< Not ready to arm */
    ESP_ZB_ZCL_IAS_ACE_ARM_NOTIF_ALREADY_DISARMED             = 0x06,   /**< Already disarmed */
} esp_zb_zcl_ias_ace_arm_notif_t;

/** @brief Length of array of Bitmap of Zone ID Map, ZCL spec 8.3.2.5.2.1 */
#define ESP_ZB_ZCL_IAS_ACE_GET_ZONE_ID_MAP_LENGTH 16

/** @brief Zone Type is empty */
#define ESP_ZB_ZCL_IAS_ACE_GET_ZONE_INFO_TYPE_NONE   0xffff

/** @brief IAS ACE Audible Notification Field @see ZCL spec 8.3.2.4.4.4 */
typedef enum {
    ESP_ZB_ZCL_IAS_ACE_AUD_NOTIFICATION_MUTE           = 0x00, /**< Mute (i.e., no audible notification) */
    ESP_ZB_ZCL_IAS_ACE_AUD_NOTIFICATION_DEF_SOUND      = 0x01, /**< Default sound */
    ESP_ZB_ZCL_IAS_ACE_AUD_NOTIFICATION_MANUF_SPECIFIC = 0x80, /**< Manufacturer specific */
} esp_zb_zcl_ias_ace_aud_notification_t;

/** @brief IAS ACE PanelStatus Parameter */
typedef enum {
    ESP_ZB_ZCL_IAS_ACE_PANEL_STATUS_DISARMED      = 0x00, /**< Panel disarmed (all zones disarmed) and ready to arm */
    ESP_ZB_ZCL_IAS_ACE_PANEL_STATUS_ARMED_STAY    = 0x01, /**< Armed stay */
    ESP_ZB_ZCL_IAS_ACE_PANEL_STATUS_ARMED_NIGHT   = 0x02, /**< Armed night */
    ESP_ZB_ZCL_IAS_ACE_PANEL_STATUS_ARMED_AWAY    = 0x03, /**< Armed away */
    ESP_ZB_ZCL_IAS_ACE_PANEL_STATUS_EXIT_DELAY    = 0x04, /**< Exit delay */
    ESP_ZB_ZCL_IAS_ACE_PANEL_STATUS_ENTRY_DELAY   = 0x05, /**< Entry delay */
    ESP_ZB_ZCL_IAS_ACE_PANEL_STATUS_NOT_READY     = 0x06, /**< Not ready to arm */
    ESP_ZB_ZCL_IAS_ACE_PANEL_STATUS_IN_ALARM      = 0x07, /**< In alarm */
    ESP_ZB_ZCL_IAS_ACE_PANEL_STATUS_ARMING_STAY   = 0x08, /**< Arming Stay */
    ESP_ZB_ZCL_IAS_ACE_PANEL_STATUS_ARMING_NIGHT  = 0x09, /**< Arming Night */
    ESP_ZB_ZCL_IAS_ACE_PANEL_STATUS_ARMING_AWAY   = 0x0a, /**< Arming Away */
} esp_zb_zcl_ias_ace_panel_status_t;

/** @brief IAS ACE Alarm Status Field */
typedef enum {
    ESP_ZB_ZCL_IAS_ACE_ALARM_STATUS_NO_ALARM        = 0x00, /**< No alarm */
    ESP_ZB_ZCL_IAS_ACE_ALARM_STATUS_BURGLAR         = 0x01, /**< Burglar */
    ESP_ZB_ZCL_IAS_ACE_ALARM_STATUS_FIRE            = 0x02, /**< Fire */
    ESP_ZB_ZCL_IAS_ACE_ALARM_STATUS_EMERGENCY       = 0x03, /**< Emergency */
    ESP_ZB_ZCL_IAS_ACE_ALARM_STATUS_POLICE_PANIC    = 0x04, /**< Police Panic */
    ESP_ZB_ZCL_IAS_ACE_ALARM_STATUS_FIRE_PANIC      = 0x05, /**< Fire Panic */
    ESP_ZB_ZCL_IAS_ACE_ALARM_STATUS_EMERGENCY_PANIC = 0x06, /**< Emergency Panic */
} esp_zb_zcl_ias_ace_alarm_status_t;

/** @brief IAS ACE Bypass Result */
typedef enum {
    ESP_ZB_ZCL_IAS_ACE_BYPASS_RESULT_BYPASSED         = 0x00,   /**< Bypass request is successful. Zone is bypassed. */
    ESP_ZB_ZCL_IAS_ACE_BYPASS_RESULT_NOT_BYPASSED     = 0x01,   /**< Bypass request is unsuccessful. Zone is not bypassed. */
    ESP_ZB_ZCL_IAS_ACE_BYPASS_RESULT_NOT_ALLOWED      = 0x02,   /**< Bypass request is not allowed. Zone is not bypassed. */
    ESP_ZB_ZCL_IAS_ACE_BYPASS_RESULT_INVALID_ZONE_ID  = 0x03,   /**< Invalid Zone ID in the request. */
    ESP_ZB_ZCL_IAS_ACE_BYPASS_RESULT_UNKNOWN_ZONE_ID  = 0x04,   /**< Valid range of Zone ID, but unknown to server. */
    ESP_ZB_ZCL_IAS_ACE_BYPASS_RESULT_INVALID_ARM_CODE = 0x05,   /**< Arm/Disarm Code was entered incorrectly. */
} esp_zb_zcl_ias_ace_bypass_result_t;

#ifdef __cplusplus
}
#endif

#endif
