/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/ias_ace_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Length of array of Bitmap of Zone ID Map.
 */
#define EZB_ZCL_IAS_ACE_GET_ZONE_ID_MAP_LENGTH 16
/**
 * @brief Zone ID max value.
 */
#define EZB_ZCL_IAS_ACE_ZONE_ID_MAX_VALUE 0xfe
/**
 * @brief Maximum length of zone label (zcl string).
 */
#define EZB_ZCL_IAS_ACE_ZONE_LABEL_MAX_LENGTH 17
/**
 * @brief Maximum length of arm disarm code (zcl string)
 */
#define EZB_ZCL_IAS_ACE_ARM_DISARM_CODE_MAX_LENGTH 9

/**
 * @brief Pointer to IAS ACE Zone Table.
 */
typedef void *ezb_zcl_ias_ace_zone_table_t;

/**
 * @brief Structure for IAS ACE Zone Table Entry.
 */
typedef struct ezb_zcl_ias_ace_zone_table_ent_s {
    uint8_t       zone_id;                                           /*!< Zone ID. */
    uint16_t      zone_type;                                         /*!< Zone Type, see ezb_zcl_ias_zone_server_zone_type_t. */
    ezb_extaddr_t zone_address;                                      /*!< Zone Address. */
    uint8_t       bypassed : 1;                                      /*!< Zone is bypassed. */
    uint8_t       zone_label[EZB_ZCL_IAS_ACE_ZONE_LABEL_MAX_LENGTH]; /*!< zcl string of Zone Label. */
} ezb_zcl_ias_ace_zone_table_ent_t;

/**
 * @brief Values of the Arm Mode.
 */
typedef enum {
    EZB_ZCL_IAS_ACE_ARM_MODE_DISARM = 0x00, /*!< Disarm. */
    EZB_ZCL_IAS_ACE_ARM_MODE_DAY    = 0x01, /*!< Arm Day/Home Zones Only. */
    EZB_ZCL_IAS_ACE_ARM_MODE_NIGHT  = 0x02, /*!< Arm Night/Sleep Zones Only. */
    EZB_ZCL_IAS_ACE_ARM_MODE_ALL    = 0x03, /*!< Arm All Zones. */
} ezb_zcl_ias_ace_arm_mode_t;

/**
 * @brief Values of the Arm Notification.
 */
typedef enum {
    EZB_ZCL_IAS_ACE_ARM_NOTIF_ALL_ZONES_DISARMED           = 0x00, /*!< All Zones Disarmed. */
    EZB_ZCL_IAS_ACE_ARM_NOTIF_ONLY_DAY_HOME_ZONES_ARMED    = 0x01, /*!< Only Day/Home Zones Armed. */
    EZB_ZCL_IAS_ACE_ARM_NOTIF_ONLY_NIGHT_SLEEP_ZONES_ARMED = 0x02, /*!< Only Night/Sleep Zones Armed. */
    EZB_ZCL_IAS_ACE_ARM_NOTIF_ALL_ZONES_ARMED              = 0x03, /*!< All Zones Armed. */
    EZB_ZCL_IAS_ACE_ARM_NOTIF_INVALID_ARM_DISARM_CODE      = 0x04, /*!< Invalid Arm/Disarm Code. */
    EZB_ZCL_IAS_ACE_ARM_NOTIF_NOT_READY_TO_ARM             = 0x05, /*!< Not ready to arm. */
    EZB_ZCL_IAS_ACE_ARM_NOTIF_ALREADY_DISARMED             = 0x06, /*!< Already disarmed. */
} ezb_zcl_ias_ace_arm_notif_t;

/**
 * @brief IAS ACE Audible Notification Field.
 */
typedef enum {
    EZB_ZCL_IAS_ACE_AUD_NOTIF_MUTE           = 0x00, /*!< Mute (i.e., no audible notification). */
    EZB_ZCL_IAS_ACE_AUD_NOTIF_DEF_SOUND      = 0x01, /*!< Default sound. */
    EZB_ZCL_IAS_ACE_AUD_NOTIF_MANUF_SPECIFIC = 0x80, /*!< Manufacturer specific. */
} ezb_zcl_ias_ace_aud_notif_t;

/**
 * @brief IAS ACE PanelStatus Parameter.
 */
typedef enum {
    EZB_ZCL_IAS_ACE_PANEL_STATUS_DISARMED     = 0x00, /*!< Panel disarmed (all zones disarmed) and ready to arm. */
    EZB_ZCL_IAS_ACE_PANEL_STATUS_ARMED_STAY   = 0x01, /*!< Armed stay. */
    EZB_ZCL_IAS_ACE_PANEL_STATUS_ARMED_NIGHT  = 0x02, /*!< Armed night. */
    EZB_ZCL_IAS_ACE_PANEL_STATUS_ARMED_AWAY   = 0x03, /*!< Armed away. */
    EZB_ZCL_IAS_ACE_PANEL_STATUS_EXIT_DELAY   = 0x04, /*!< Exit delay. */
    EZB_ZCL_IAS_ACE_PANEL_STATUS_ENTRY_DELAY  = 0x05, /*!< Entry delay. */
    EZB_ZCL_IAS_ACE_PANEL_STATUS_NOT_READY    = 0x06, /*!< Not ready to arm. */
    EZB_ZCL_IAS_ACE_PANEL_STATUS_IN_ALARM     = 0x07, /*!< In alarm. */
    EZB_ZCL_IAS_ACE_PANEL_STATUS_ARMING_STAY  = 0x08, /*!< Arming Stay. */
    EZB_ZCL_IAS_ACE_PANEL_STATUS_ARMING_NIGHT = 0x09, /*!< Arming Night. */
    EZB_ZCL_IAS_ACE_PANEL_STATUS_ARMING_AWAY  = 0x0a, /*!< Arming Away. */
} ezb_zcl_ias_ace_panel_status_t;

/**
 * @brief IAS ACE Alarm Status Field.
 */
typedef enum {
    EZB_ZCL_IAS_ACE_ALARM_STATUS_NO_ALARM        = 0x00, /*!< No alarm. */
    EZB_ZCL_IAS_ACE_ALARM_STATUS_BURGLAR         = 0x01, /*!< Burglar. */
    EZB_ZCL_IAS_ACE_ALARM_STATUS_FIRE            = 0x02, /*!< Fire. */
    EZB_ZCL_IAS_ACE_ALARM_STATUS_EMERGENCY       = 0x03, /*!< Emergency. */
    EZB_ZCL_IAS_ACE_ALARM_STATUS_POLICE_PANIC    = 0x04, /*!< Police Panic. */
    EZB_ZCL_IAS_ACE_ALARM_STATUS_FIRE_PANIC      = 0x05, /*!< Fire Panic. */
    EZB_ZCL_IAS_ACE_ALARM_STATUS_EMERGENCY_PANIC = 0x06, /*!< Emergency Panic. */
} ezb_zcl_ias_ace_alarm_status_t;

/**
 * @brief IAS ACE Bypass Result.
 */
typedef enum {
    EZB_ZCL_IAS_ACE_BYPASS_RESULT_BYPASSED         = 0x00, /*!< Bypass request is successful. Zone is bypassed. */
    EZB_ZCL_IAS_ACE_BYPASS_RESULT_NOT_BYPASSED     = 0x01, /*!< Bypass request is unsuccessful. Zone is not bypassed. */
    EZB_ZCL_IAS_ACE_BYPASS_RESULT_NOT_ALLOWED      = 0x02, /*!< Bypass request is not allowed. Zone is not bypassed. */
    EZB_ZCL_IAS_ACE_BYPASS_RESULT_INVALID_ZONE_ID  = 0x03, /*!< Invalid Zone ID in the request. */
    EZB_ZCL_IAS_ACE_BYPASS_RESULT_UNKNOWN_ZONE_ID  = 0x04, /*!< Valid range of Zone ID, but unknown to server. */
    EZB_ZCL_IAS_ACE_BYPASS_RESULT_INVALID_ARM_CODE = 0x05, /*!< Arm/Disarm Code was entered incorrectly. */
} ezb_zcl_ias_ace_bypass_result_t;

/**
 * @brief Structure for ZCL command with no payload.
 */
typedef struct ezb_zcl_ias_ace_cmd_with_no_payload_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
} ezb_zcl_ias_ace_cmd_with_no_payload_t;

/**
 * @brief Structure for IAS ACE Zone Status.
 */
typedef struct ezb_zcl_ias_ace_zone_status_s {
    uint8_t  zone_id;     /*!< Zone ID. */
    uint16_t zone_status; /*!< Zone Status, see ezb_zcl_ias_zone_server_zone_status_t. */
} ezb_zcl_ias_ace_zone_status_t;

/**
 * @brief Payload for the ZCL IAS ACE Arm command.
 */
typedef struct ezb_zcl_ias_ace_arm_payload_s {
    uint8_t arm_mode;                                                    /*!< Arm Mode. */
    uint8_t arm_disarm_code[EZB_ZCL_IAS_ACE_ARM_DISARM_CODE_MAX_LENGTH]; /*!< Arm/Disarm Code. */
    uint8_t zone_id;                                                     /*!< Zone ID. */
} ezb_zcl_ias_ace_arm_payload_t;

/**
 * @brief Payload for the ZCL IAS ACE Bypass Response command.
 */
typedef struct ezb_zcl_ias_ace_bypass_rsp_payload_s {
    uint8_t  num_of_zones;  /*!< Number of Zones. */
    uint8_t *bypass_result; /*!< Bypass Result, see ezb_zcl_ias_ace_bypass_result_t. */
} ezb_zcl_ias_ace_bypass_rsp_payload_t;

/**
 * @brief Payload for the ZCL IAS ACE Bypass command.
 */
typedef struct ezb_zcl_ias_ace_bypass_payload_s {
    uint8_t  num_of_zones;                                                /*!< Number of Zones. */
    uint8_t *zone_id;                                                     /*!< Zone ID list. */
    uint8_t  arm_disarm_code[EZB_ZCL_IAS_ACE_ARM_DISARM_CODE_MAX_LENGTH]; /*!< Arm/Disarm Code. */
} ezb_zcl_ias_ace_bypass_payload_t;

/**
 * @brief Payload for the ZCL IAS ACE Get Panel Status command.
 */
typedef struct ezb_zcl_ias_ace_get_panel_status_rsp_payload_s {
    uint8_t panel_status;      /*!< Panel Status. */
    uint8_t seconds_remaining; /*!< Seconds Remaining Parameter. */
    uint8_t aud_notif;         /*!< Audible Notification. */
    uint8_t alarm_status;      /*!< Alarm Status. */
} ezb_zcl_ias_ace_get_panel_status_rsp_payload_t;

/**
 * @brief Payload for the ZCL IAS ACE Panel Status Changed command.
 */
typedef ezb_zcl_ias_ace_get_panel_status_rsp_payload_t ezb_zcl_ias_ace_panel_status_changed_payload_t;

/**
 * @brief Payload for the ZCL IAS ACE Get Zone Info command.
 */
typedef struct ezb_zcl_ias_ace_get_zone_info_rsp_payload_s {
    uint8_t       zone_id;                                           /*!< Zone ID. */
    uint16_t      zone_type;                                         /*!< Zone Type. */
    ezb_extaddr_t address;                                           /*!< Zone Address. */
    uint8_t       zone_label[EZB_ZCL_IAS_ACE_ZONE_LABEL_MAX_LENGTH]; /*!< Zone Label. */
} ezb_zcl_ias_ace_get_zone_info_rsp_payload_t;

/**
 * @brief Payload for the ZCL IAS ACE Get Zone Status Response command.
 */
typedef struct ezb_zcl_ias_ace_get_zone_status_rsp_payload_s {
    uint8_t                        zone_status_complete; /*!< Zone Status Complete. */
    uint8_t                        num_of_zones;         /*!< Number of Zones. */
    ezb_zcl_ias_ace_zone_status_t *zone_id_status;       /*!< Status of Zone IDs. */
} ezb_zcl_ias_ace_get_zone_status_rsp_payload_t;

/**
 * @brief Payload for the ZCL IAS ACE Set Bypassed Zone List command.
 */
typedef struct ezb_zcl_ias_ace_set_bypassed_zone_list_payload_s {
    uint8_t  num_of_zones; /*!< Number of Zones. */
    uint8_t *zone_id;      /*!< Zone ID array. */
} ezb_zcl_ias_ace_set_bypassed_zone_list_payload_t;

/**
 * @brief Payload for the ZCL IAS ACE Zone Status Changed command.
 */
typedef struct ezb_zcl_ias_ace_zone_status_changed_payload_s {
    uint8_t  zone_id;                                           /*!< Zone ID. */
    uint16_t zone_status;                                       /*!< Zone Status. */
    uint8_t  aud_notif;                                         /*!< Audible Notification. */
    uint8_t  zone_label[EZB_ZCL_IAS_ACE_ZONE_LABEL_MAX_LENGTH]; /*!< Zone Label. */
} ezb_zcl_ias_ace_zone_status_changed_payload_t;

/**
 * @brief Payload for the ZCL IAS ACE Get Zone Status command.
 */
typedef struct ezb_zcl_ias_ace_get_zone_status_payload_s {
    uint8_t  starting_zone_id;      /*!< Starting Zone ID. */
    uint8_t  max_num_zone_ids;      /*!< Max Number of Zone IDs Requested. */
    uint8_t  zone_status_mask_flag; /*!< Zone Status Mask Flag. */
    uint16_t zone_status_mask;      /*!< Zone Status Mask. */
} ezb_zcl_ias_ace_get_zone_status_payload_t;

/**
 * @brief Structure for the ZCL IAS ACE Arm command.
 */
typedef struct ezb_zcl_ias_ace_arm_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t    cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_ias_ace_arm_payload_t payload;  /*!< Payload of the ZCL IAS ACE Arm command. */
} ezb_zcl_ias_ace_arm_cmd_t;

/**
 * @brief Structure for the ZCL IAS ACE Bypass command.
 */
typedef struct ezb_zcl_ias_ace_bypass_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t       cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_ias_ace_bypass_payload_t payload;  /*!< Payload of the ZCL IAS ACE Bypass command. */
} ezb_zcl_ias_ace_bypass_cmd_t;

/**
 * @brief Structure for the ZCL IAS ACE Emergency command.
 */
typedef ezb_zcl_ias_ace_cmd_with_no_payload_t ezb_zcl_ias_ace_emergency_cmd_t;

/**
 * @brief Structure for the ZCL IAS ACE Fire command.
 */
typedef ezb_zcl_ias_ace_cmd_with_no_payload_t ezb_zcl_ias_ace_fire_cmd_t;

/**
 * @brief Structure for the ZCL IAS ACE Panic command.
 */
typedef ezb_zcl_ias_ace_cmd_with_no_payload_t ezb_zcl_ias_ace_panic_cmd_t;

/**
 * @brief Structure for the ZCL IAS ACE Get Zone ID Map command.
 */
typedef ezb_zcl_ias_ace_cmd_with_no_payload_t ezb_zcl_ias_ace_get_zone_id_map_cmd_t;

/**
 * @brief Structure for the ZCL IAS ACE Get Zone Information command.
 */
typedef struct ezb_zcl_ias_ace_get_zone_info_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint8_t zone_id; /*!< Zone ID. */
    } payload;           /*!< Payload of the ZCL IAS ACE Get Zone Information command. */
} ezb_zcl_ias_ace_get_zone_info_cmd_t;

/**
 * @brief Structure for the ZCL IAS ACE Get Panel Status command.
 */
typedef ezb_zcl_ias_ace_cmd_with_no_payload_t ezb_zcl_ias_ace_get_panel_status_cmd_t;

/**
 * @brief Structure for the ZCL IAS ACE Get Bypassed Zone List command.
 */
typedef ezb_zcl_ias_ace_cmd_with_no_payload_t ezb_zcl_ias_ace_get_bypassed_zone_list_cmd_t;

/**
 * @brief Structure for the ZCL IAS ACE Get Zone Status command.
 */
typedef struct ezb_zcl_ias_ace_get_zone_status_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_ias_ace_get_zone_status_payload_t payload;  /*!< Payload of the ZCL IAS ACE Get Zone Status command. */
} ezb_zcl_ias_ace_get_zone_status_cmd_t;

/**
 * @brief Structure for the ZCL IAS ACE Zone Status Changed command.
 */
typedef struct ezb_zcl_ias_ace_zone_status_changed_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                    cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_ias_ace_zone_status_changed_payload_t payload;  /*!< Payload of the ZCL IAS ACE Zone Status Changed command. */
} ezb_zcl_ias_ace_zone_status_changed_cmd_t;

/**
 * @brief Structure for the ZCL IAS ACE Panel Status Changed command.
 */
typedef struct ezb_zcl_ias_ace_panel_status_changed_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                     cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_ias_ace_panel_status_changed_payload_t payload;  /*!< Payload of the ZCL IAS ACE Panel Status Changed command. */
} ezb_zcl_ias_ace_panel_status_changed_cmd_t;

/**
 * @brief Message for the ZCL IAS ACE Arm command message.
 */
typedef struct ezb_zcl_ias_ace_arm_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;       /*!< ZCL command header information.
                                                    See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_ace_arm_payload_t payload; /*!< Payload of the ZCL IAS ACE Arm command. */
    } in;                                      /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result;    /*!< Status of processing in application. */
        uint8_t          arm_notif; /*!< Arm Notification. */
    } out;                          /*!< Output: result to send back. */
} ezb_zcl_ias_ace_arm_message_t;

/**
 * @brief Message for the ZCL IAS ACE Bypass command message.
 */
typedef struct ezb_zcl_ias_ace_bypass_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;          /*!< ZCL command header information.
                                                       See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_ace_bypass_payload_t payload; /*!< Payload of the ZCL IAS ACE Bypass command. */
    } in;                                         /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t                      result;  /*!< Status of processing in application. */
        ezb_zcl_ias_ace_bypass_rsp_payload_t *payload; /*!< Payload of the ZCL IAS ACE Bypass Response command. */
        ezb_zcl_cmd_cnf_ctx_t cnf_ctx; /*!< Command confirmation context, which will be triggered when response is confirmed. */
    } out;                             /*!< Output: result to send back. */
} ezb_zcl_ias_ace_bypass_message_t;

/**
 * @brief Message for the ZCL IAS ACE Emergency command message.
 */
typedef struct ezb_zcl_ias_ace_emergency_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
    } in;                                /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */

} ezb_zcl_ias_ace_emergency_message_t;

/**
 * @brief Message for the ZCL IAS ACE Fire command message.
 */
typedef struct ezb_zcl_ias_ace_emergency_message_s ezb_zcl_ias_ace_fire_message_t;

/**
 * @brief Message for the ZCL IAS ACE Panic command message.
 */
typedef struct ezb_zcl_ias_ace_emergency_message_s ezb_zcl_ias_ace_panic_message_t;

/**
 * @brief Message for the ZCL IAS ACE Get Panel Status command message.
 */
typedef struct ezb_zcl_ias_ace_get_panel_status_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
    } in;                                /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
        ezb_zcl_ias_ace_get_panel_status_rsp_payload_t
            payload; /*!< Payload of the ZCL IAS ACE Get Panel Status Response command. */
    } out;           /*!< Output: result to send back. */
} ezb_zcl_ias_ace_get_panel_status_message_t;

/**
 * @brief Message for the ZCL IAS ACE Get Bypassed Zone List command message.
 */
typedef struct ezb_zcl_ias_ace_emergency_message_s ezb_zcl_ias_ace_get_bypassed_zone_list_message_t;

/**
 * @brief Message for the ZCL IAS ACE Get Zone Status command message.
 */
typedef struct ezb_zcl_ias_ace_get_zone_status_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                   /*!< ZCL command header information.
                                                                See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_ace_get_zone_status_payload_t payload; /*!< Payload of the ZCL IAS ACE Get Zone Status command. */
    } in;                                                  /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
        ezb_zcl_ias_ace_get_zone_status_rsp_payload_t
                             *payload; /*!< Payload of the ZCL IAS ACE Get Zone Status Response command. */
        ezb_zcl_cmd_cnf_ctx_t cnf_ctx; /*!< Command confirmation context, which will be triggered when response is confirmed. */
    } out;                             /*!< Output: result to send back. */
} ezb_zcl_ias_ace_get_zone_status_message_t;

/**
 * @brief Message for the ZCL IAS ACE Arm Response message.
 */
typedef struct ezb_zcl_ias_ace_arm_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        uint8_t arm_notif; /*!< Arm Notification, see ezb_zcl_ias_ace_arm_notif_t */
    } in;                  /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_ace_arm_rsp_message_t;

/**
 * @brief Message for the ZCL IAS ACE Get Zone ID map Response message.
 */
typedef struct ezb_zcl_ias_ace_get_zone_id_map_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        uint16_t zone_id_map[EZB_ZCL_IAS_ACE_GET_ZONE_ID_MAP_LENGTH]; /*!< Zone ID Map */
    } in;                                                             /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_ace_get_zone_id_map_rsp_message_t;

/**
 * @brief Message for the ZCL IAS ACE Get Zone Information Response message.
 */
typedef struct ezb_zcl_ias_ace_get_zone_info_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_ace_get_zone_info_rsp_payload_t
            payload; /*!< Payload of the ZCL IAS ACE Get Zone Information Response command. */
    } in;            /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_ace_get_zone_info_rsp_message_t;

/**
 * @brief Message for the ZCL IAS ACE Zone Status Changed message.
 */
typedef struct ezb_zcl_ias_ace_zone_status_changed_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_ace_zone_status_changed_payload_t payload; /*!< Payload of the ZCL IAS ACE Zone Status Changed command. */
    } in;                                                      /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_ace_zone_status_changed_message_t;

/**
 * @brief Message for the ZCL IAS ACE Panel Status Changed message.
 */
typedef struct ezb_zcl_ias_ace_panel_status_changed_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_ace_panel_status_changed_payload_t payload; /*!< Payload of the ZCL IAS ACE Panel Status Changed command. */
    } in;                                                       /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_ace_panel_status_changed_message_t;

/**
 * @brief Message for the ZCL IAS ACE Get Panel Status Response message.
 */
typedef struct ezb_zcl_ias_ace_get_panel_status_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_ace_get_panel_status_rsp_payload_t
            payload; /*!< Payload of the ZCL IAS ACE Get Panel Status Response command. */
    } in;            /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_ace_get_panel_status_rsp_message_t;

/**
 * @brief Message for the ZCL IAS ACE Set Bypassed Zone List Response message.
 */
typedef struct ezb_zcl_ias_ace_set_bypassed_zone_list_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_ace_set_bypassed_zone_list_payload_t
            payload; /*!< Payload of the ZCL IAS ACE Set Bypassed Zone List command. */
    } in;            /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_ace_set_bypassed_zone_list_rsp_message_t;

/**
 * @brief Message for the ZCL IAS ACE Bypass Response message.
 */
typedef struct ezb_zcl_ias_ace_bypass_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;             /*!< ZCL command header information.
                                                          See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_ace_bypass_rsp_payload_t payload; /*!< Payload of the ZCL IAS ACE Bypass Response command. */
    } in;                                             /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_ace_bypass_rsp_message_t;

/**
 * @brief Message for the ZCL IAS ACE Get Zone Status Response message.
 */
typedef struct ezb_zcl_ias_ace_get_zone_status_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;             /*!< ZCL command header information.
                                                          See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_ace_get_zone_status_rsp_payload_t
            payload; /*!< Payload of the ZCL IAS ACE Get Zone Status Response command. */
    } in;            /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_ace_get_zone_status_rsp_message_t;

/**
 * @brief Get the zone table of the IAS ACE cluster.
 * @param ep_id A 8-bit endpoint ID which the IAS ACE cluster attach.
 * @return The pointer to the zone table of IAS ACE cluster on the given endpoint.
 *         The pointer is valid until the IAS ACE cluster is unregistered or the device is reset.
 */
ezb_zcl_ias_ace_zone_table_t ezb_zcl_ias_ace_get_zone_table(uint8_t ep_id);

/**
 * @brief Get the zone entry from the zone table.
 * @param table The pointer to the zone table of IAS ACE cluster.
 * @param zone_id The zone ID of the zone entry to be retrieved.
 * @param entry Pointer to the zone entry to be retrieved.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_zone_table_get_zone(ezb_zcl_ias_ace_zone_table_t      table,
                                              uint8_t                           zone_id,
                                              ezb_zcl_ias_ace_zone_table_ent_t *entry);

/**
 * @brief Add a zone entry to the zone table.
 * @param table The pointer to the zone table of IAS ACE cluster.
 * @param new_entry The pointer to the new zone entry to be added.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_zone_table_add_zone(ezb_zcl_ias_ace_zone_table_t            table,
                                              const ezb_zcl_ias_ace_zone_table_ent_t *new_entry);

/**
 * @brief Remove a zone entry from the zone table by zone ID.
 * @param table The pointer to the zone table of IAS ACE cluster.
 * @param zone_id The zone ID of the zone entry to be removed.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_zone_table_remove_zone(ezb_zcl_ias_ace_zone_table_t table, uint8_t zone_id);

/**
 * @brief Update a zone entry in the zone table by zone entry.
 * @param table The pointer to the zone table of IAS ACE cluster.
 * @param entry The pointer to the zone entry to be updated.
 *              The zone ID in the entry is used to find the existing entry to be updated.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_zone_table_update_zone(ezb_zcl_ias_ace_zone_table_t            table,
                                                 const ezb_zcl_ias_ace_zone_table_ent_t *entry);

/**
 * @brief Send ZCL IAS ACE Arm command request.
 * @param cmd_req Pointer to the Arm command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_arm_cmd_req(const ezb_zcl_ias_ace_arm_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ACE Bypass command request.
 *
 * @param cmd_req Pointer to the Bypass command structure.
 * @note The IAS ACE server shall to update the bypassed attributes in the zone table entry after bypassing a zone.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_bypass_cmd_req(const ezb_zcl_ias_ace_bypass_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ACE Emergency command request.
 *
 * @param cmd_req Pointer to the Emergency command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_emergency_cmd_req(const ezb_zcl_ias_ace_emergency_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ACE Fire command request.
 *
 * @param cmd_req Pointer to the Fire command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_fire_cmd_req(const ezb_zcl_ias_ace_fire_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ACE Panic command request.
 *
 * @param cmd_req Pointer to the Panic command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_panic_cmd_req(const ezb_zcl_ias_ace_panic_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ACE Get Zone ID Map command request.
 *
 * @param cmd_req Pointer to the Get Zone ID Map command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_get_zone_id_map_cmd_req(const ezb_zcl_ias_ace_get_zone_id_map_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ACE Get Zone Information command request.
 *
 * @param cmd_req Pointer to the Get Zone Information command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_get_zone_information_cmd_req(const ezb_zcl_ias_ace_get_zone_info_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ACE Zone Status Changed command request.
 *
 * @param cmd_req Pointer to the Zone Status Changed command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_get_panel_status_cmd_req(const ezb_zcl_ias_ace_get_panel_status_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ACE Get Bypassed Zone List command request.
 *
 * @param cmd_req Pointer to the Get Bypassed Zone List command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_get_bypassed_zone_list_cmd_req(const ezb_zcl_ias_ace_get_bypassed_zone_list_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ACE Get Zone Status command request.
 *
 * @param cmd_req Pointer to the Get Zone Status command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_get_zone_status_cmd_req(const ezb_zcl_ias_ace_get_zone_status_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ACE Zone Status Changed command request.
 *
 * @param cmd_req Pointer to the Zone Status Changed command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_zone_status_changed_cmd_req(const ezb_zcl_ias_ace_zone_status_changed_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ACE Panel Status Changed command request.
 *
 * @param cmd_req Pointer to the Panel Status Changed command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_ace_panel_status_changed_cmd_req(const ezb_zcl_ias_ace_panel_status_changed_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
