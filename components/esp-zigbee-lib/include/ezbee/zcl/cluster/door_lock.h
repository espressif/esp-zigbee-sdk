/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/door_lock_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Maximum length (in bytes) of a PIN code handled by the stack.
 *
 * @note This is the capacity of the stack buffers. The length actually accepted by the lock is defined
 *       by the MinPINCodeLength / MaxPINCodeLength attributes and has to be validated by the application.
 */
#define EZB_ZCL_DOOR_LOCK_PIN_CODE_MAX_LENGTH 16

/**
 * @brief Values of the User Status field of the DoorLock cluster.
 * @anchor ezb_zcl_door_lock_user_status_t
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_USER_STATUS_AVAILABLE         = 0x00U, /*!< Available (the user ID is not used). */
    EZB_ZCL_DOOR_LOCK_USER_STATUS_OCCUPIED_ENABLED  = 0x01U, /*!< Occupied / enabled. */
    EZB_ZCL_DOOR_LOCK_USER_STATUS_OCCUPIED_DISABLED = 0x03U, /*!< Occupied / disabled. */
    EZB_ZCL_DOOR_LOCK_USER_STATUS_NOT_SUPPORTED     = 0xffU, /*!< Not supported. */
} ezb_zcl_door_lock_user_status_t;

/**
 * @brief Values of the User Type field of the DoorLock cluster.
 * @anchor ezb_zcl_door_lock_user_type_t
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_USER_TYPE_UNRESTRICTED       = 0x00U, /*!< Unrestricted user. */
    EZB_ZCL_DOOR_LOCK_USER_TYPE_YEAR_DAY_SCHEDULE  = 0x01U, /*!< Year day schedule user. */
    EZB_ZCL_DOOR_LOCK_USER_TYPE_WEEK_DAY_SCHEDULE  = 0x02U, /*!< Week day schedule user. */
    EZB_ZCL_DOOR_LOCK_USER_TYPE_MASTER             = 0x03U, /*!< Master user. */
    EZB_ZCL_DOOR_LOCK_USER_TYPE_NON_ACCESS         = 0x04U, /*!< Non access user. */
    EZB_ZCL_DOOR_LOCK_USER_TYPE_NOT_SUPPORTED      = 0xffU, /*!< Not supported. */
} ezb_zcl_door_lock_user_type_t;

/**
 * @brief Values of the Status field of the SetPINCode / ClearPINCode / SetUserStatus responses.
 * @anchor ezb_zcl_door_lock_cmd_status_t
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_CMD_STATUS_SUCCESS        = 0x00U, /*!< Success. */
    EZB_ZCL_DOOR_LOCK_CMD_STATUS_FAIL           = 0x01U, /*!< General failure. */
    EZB_ZCL_DOOR_LOCK_CMD_STATUS_MEMORY_FULL    = 0x02U, /*!< Memory full (SetPINCode only). */
    EZB_ZCL_DOOR_LOCK_CMD_STATUS_DUPLICATE_CODE = 0x03U, /*!< Duplicate code error (SetPINCode only). */
} ezb_zcl_door_lock_cmd_status_t;

/**
 * @brief Values of the Operation Event Source field of the OperationEventNotification command.
 * @anchor ezb_zcl_door_lock_operation_event_source_t
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_SOURCE_KEYPAD        = 0x00U, /*!< Keypad. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_SOURCE_RF            = 0x01U, /*!< Remote access over the Zigbee network. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_SOURCE_MANUAL        = 0x02U, /*!< Manual operation (thumb turn, key, button). */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_SOURCE_RFID          = 0x03U, /*!< RFID reader. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_SOURCE_INDETERMINATE = 0xffU, /*!< Indeterminate. */
} ezb_zcl_door_lock_operation_event_source_t;

/**
 * @brief Operation event codes of the OperationEventNotification command.
 *
 * @note The codes share one value mapping for all the event sources, but each code is only applicable to some of them.
 *       The value is NOT the bit position in the corresponding *OperationEventMask attribute.
 * @anchor ezb_zcl_door_lock_operation_event_code_t
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_UNKNOWN_OR_MS              = 0x00U, /*!< Unknown or manufacturer specific.
                                                                                    Sources: all. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_LOCK                       = 0x01U, /*!< Lock. Sources: all. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_UNLOCK                     = 0x02U, /*!< Unlock. Sources: all. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_LOCK_FAILURE_INVALID_PIN_OR_ID = 0x03U, /*!< Lock failure, invalid PIN, code or ID.
                                                                                    Sources: keypad, RF, RFID. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_LOCK_FAILURE_INVALID_SCHEDULE = 0x04U, /*!< Lock failure, invalid schedule.
                                                                                    Sources: keypad, RF, RFID. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_UNLOCK_FAILURE_INVALID_PIN_OR_ID = 0x05U, /*!< Unlock failure, invalid PIN, code or
                                                                                    ID. Sources: keypad, RF, RFID. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_UNLOCK_FAILURE_INVALID_SCHEDULE = 0x06U, /*!< Unlock failure, invalid schedule.
                                                                                    Sources: keypad, RF, RFID. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_ONE_TOUCH_LOCK             = 0x07U, /*!< One touch lock. Source: manual. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_KEY_LOCK                   = 0x08U, /*!< Key lock. Source: manual. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_KEY_UNLOCK                 = 0x09U, /*!< Key unlock. Source: manual. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_AUTO_LOCK                  = 0x0aU, /*!< Auto lock. Source: manual. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_SCHEDULE_LOCK              = 0x0bU, /*!< Schedule lock. Source: manual. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_SCHEDULE_UNLOCK            = 0x0cU, /*!< Schedule unlock. Source: manual. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_MANUAL_LOCK                = 0x0dU, /*!< Manual lock (key or thumb turn).
                                                                                    Source: manual. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_MANUAL_UNLOCK              = 0x0eU, /*!< Manual unlock (key or thumb turn).
                                                                                    Source: manual. */
    EZB_ZCL_DOOR_LOCK_OPERATION_EVENT_CODE_NON_ACCESS_USER            = 0x0fU, /*!< Non access user operation event.
                                                                                    Source: keypad. */
} ezb_zcl_door_lock_operation_event_code_t;

/**
 * @brief Payload for the ZCL DoorLock SetPINCode command and the GetPINCodeResponse command.
 */
typedef struct ezb_zcl_door_lock_pin_code_payload_s {
    uint16_t user_id;     /*!< User ID (index of the user, starting from 0). */
    uint8_t  user_status; /*!< User status, see @ref ezb_zcl_door_lock_user_status_t. */
    uint8_t  user_type;   /*!< User type, see @ref ezb_zcl_door_lock_user_type_t. */
    uint8_t  pin_code[EZB_ZCL_DOOR_LOCK_PIN_CODE_MAX_LENGTH + 1]; /*!< PIN code as a ZCL octet string,
                                                                      the first byte is the length. */
} ezb_zcl_door_lock_pin_code_payload_t;

/**
 * @brief Payload for the ZCL DoorLock GetPINCode and ClearPINCode commands.
 */
typedef struct ezb_zcl_door_lock_user_id_payload_s {
    uint16_t user_id; /*!< User ID (index of the user, starting from 0). */
} ezb_zcl_door_lock_user_id_payload_t;

/**
 * @brief Payload for the ZCL DoorLock SetUserStatus command and the GetUserStatusResponse command.
 */
typedef struct ezb_zcl_door_lock_user_status_payload_s {
    uint16_t user_id;     /*!< User ID (index of the user, starting from 0). */
    uint8_t  user_status; /*!< User status, see @ref ezb_zcl_door_lock_user_status_t. */
} ezb_zcl_door_lock_user_status_payload_t;

/**
 * @brief Payload for the ZCL DoorLock OperationEventNotification command.
 */
typedef struct ezb_zcl_door_lock_operation_event_notif_payload_s {
    uint8_t  event_source; /*!< Operation event source, see @ref ezb_zcl_door_lock_operation_event_source_t. */
    uint8_t  event_code;   /*!< Operation event code, see @ref ezb_zcl_door_lock_operation_event_code_t. Not every code is
                                applicable to every event source. */
    uint16_t user_id;      /*!< User ID, 0xffff if not applicable. */
    uint8_t  pin_code[EZB_ZCL_DOOR_LOCK_PIN_CODE_MAX_LENGTH + 1]; /*!< PIN code used, as a ZCL octet string. It is only
                                                                      sent if the SendPINOverTheAir attribute is true,
                                                                      otherwise the length is kept and the code is
                                                                      masked by 0xFF. */
    uint32_t local_time;   /*!< Zigbee UTC time of the event, 0xffffffff if unknown. */
} ezb_zcl_door_lock_operation_event_notif_payload_t;

/**
 * @brief Structure for the ZCL DoorLock OperationEventNotification command request.
 */
typedef struct ezb_zcl_door_lock_operation_event_notif_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                        cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_door_lock_operation_event_notif_payload_t payload;  /*!< Payload for the command. */
    bool                       aps_secur_enabled; /*!< APS security enabled transmission. */
} ezb_zcl_door_lock_operation_event_notif_cmd_t;

/**
 * @brief Message for the ZCL DoorLock SetPINCode.
 */
typedef struct ezb_zcl_door_lock_set_pin_code_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t                 *header;  /*!< ZCL command header information.
                                                              See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_door_lock_pin_code_payload_t payload; /*!< Parsed payload of the request. */
    } in;                                                 /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
        uint8_t status;          /*!< Status sent in the SetPINCodeResponse, see @ref ezb_zcl_door_lock_cmd_status_t.
                                      Defaults to general failure, the application has to set it. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_door_lock_set_pin_code_message_t;

/**
 * @brief Message for the ZCL DoorLock GetPINCode.
 */
typedef struct ezb_zcl_door_lock_get_pin_code_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t            *header;  /*!< ZCL command header information.
                                                          See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_door_lock_user_id_payload_t payload; /*!< Parsed payload of the request. */
    } in;                                            /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result;      /*!< Status of processing in application. */
        uint8_t          user_status; /*!< User status sent in the response, see @ref ezb_zcl_door_lock_user_status_t.
                                           Defaults to available (user not found). */
        uint8_t          user_type;   /*!< User type sent in the response, see @ref ezb_zcl_door_lock_user_type_t.
                                           Defaults to not supported (user not found). */
        uint8_t pin_code[EZB_ZCL_DOOR_LOCK_PIN_CODE_MAX_LENGTH + 1]; /*!< PIN code as a ZCL octet string (the first byte
                                                                          is the length), defaults to empty. It is only
                                                                          sent if the SendPINOverTheAir attribute is true,
                                                                          otherwise the length is kept and the code is
                                                                          masked by 0xFF. */
    } out;                           /*!< Output: result to send back. */
} ezb_zcl_door_lock_get_pin_code_message_t;

/**
 * @brief Message for the ZCL DoorLock ClearPINCode.
 */
typedef struct ezb_zcl_door_lock_clear_pin_code_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t            *header;  /*!< ZCL command header information.
                                                          See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_door_lock_user_id_payload_t payload; /*!< Parsed payload of the request. */
    } in;                                            /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
        uint8_t status;          /*!< Status sent in the ClearPINCodeResponse, see @ref ezb_zcl_door_lock_cmd_status_t.
                                      Defaults to general failure, the application has to set it. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_door_lock_clear_pin_code_message_t;

/**
 * @brief Message for the ZCL DoorLock ClearAllPINCodes.
 */
typedef struct ezb_zcl_door_lock_clear_all_pin_codes_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
    } in;                                /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
        uint8_t status;          /*!< Status sent in the ClearAllPINCodesResponse, see @ref ezb_zcl_door_lock_cmd_status_t.
                                      Defaults to general failure, the application has to set it. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_door_lock_clear_all_pin_codes_message_t;

/**
 * @brief Message for the ZCL DoorLock SetUserStatus.
 */
typedef struct ezb_zcl_door_lock_set_user_status_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t                    *header;  /*!< ZCL command header information.
                                                                  See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_door_lock_user_status_payload_t payload; /*!< Parsed payload of the request. */
    } in;                                                    /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
        uint8_t status;          /*!< Status sent in the SetUserStatusResponse, see @ref ezb_zcl_door_lock_cmd_status_t.
                                      Defaults to general failure, the application has to set it. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_door_lock_set_user_status_message_t;

/**
 * @brief Message for the ZCL DoorLock GetUserStatus.
 */
typedef struct ezb_zcl_door_lock_get_user_status_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t            *header;  /*!< ZCL command header information.
                                                          See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_door_lock_user_id_payload_t payload; /*!< Parsed payload of the request. */
    } in;                                            /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result;      /*!< Status of processing in application. */
        uint8_t          user_status; /*!< User status sent in the response, see @ref ezb_zcl_door_lock_user_status_t.
                                           Defaults to available (user not found). */
    } out;                            /*!< Output: result to send back. */
} ezb_zcl_door_lock_get_user_status_message_t;

/**
 * @brief Structure for the ZCL DoorLock SetPINCode command request.
 */
typedef struct ezb_zcl_door_lock_set_pin_code_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t               cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_door_lock_pin_code_payload_t payload;  /*!< Payload for the command. */
    bool                       aps_secur_enabled; /*!< APS security enabled transmission. */
} ezb_zcl_door_lock_set_pin_code_cmd_t;

/**
 * @brief Structure for the ZCL DoorLock GetPINCode command request.
 */
typedef struct ezb_zcl_door_lock_get_pin_code_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t          cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_door_lock_user_id_payload_t payload;  /*!< Payload for the command. */
    bool                       aps_secur_enabled; /*!< APS security enabled transmission. */
} ezb_zcl_door_lock_get_pin_code_cmd_t;

/**
 * @brief Structure for the ZCL DoorLock ClearPINCode command request.
 * @anchor ezb_zcl_door_lock_clear_pin_code_cmd_t
 */
typedef ezb_zcl_door_lock_get_pin_code_cmd_t ezb_zcl_door_lock_clear_pin_code_cmd_t;

/**
 * @brief Structure for the ZCL DoorLock GetUserStatus command request.
 * @anchor ezb_zcl_door_lock_get_user_status_cmd_t
 */
typedef ezb_zcl_door_lock_get_pin_code_cmd_t ezb_zcl_door_lock_get_user_status_cmd_t;

/**
 * @brief Structure for the ZCL DoorLock SetUserStatus command request.
 */
typedef struct ezb_zcl_door_lock_set_user_status_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                  cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_door_lock_user_status_payload_t payload;  /*!< Payload for the command. */
    bool                       aps_secur_enabled; /*!< APS security enabled transmission. */
} ezb_zcl_door_lock_set_user_status_cmd_t;

/**
 * @brief Structure for the ZCL DoorLock ClearAllPINCodes command request.
 */
typedef struct ezb_zcl_door_lock_clear_all_pin_codes_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl;          /*!< Control information for the ZCL command. */
    bool                       aps_secur_enabled; /*!< APS security enabled transmission. */
} ezb_zcl_door_lock_clear_all_pin_codes_cmd_t;

/**
 * @brief Message for the ZCL DoorLock SetPINCodeResponse, ClearPINCodeResponse, ClearAllPINCodesResponse and
 *        SetUserStatusResponse.
 */
typedef struct ezb_zcl_door_lock_cmd_status_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        uint8_t status;                  /*!< Status of the command, see @ref ezb_zcl_door_lock_cmd_status_t. */
    } in;                                /*!< Input: parsed fields from the response. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_door_lock_cmd_status_rsp_message_t;

/**
 * @brief Message for the ZCL DoorLock GetPINCodeResponse.
 */
typedef struct ezb_zcl_door_lock_get_pin_code_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t                 *header;  /*!< ZCL command header information.
                                                              See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_door_lock_pin_code_payload_t payload; /*!< Parsed payload of the response. The PIN code is masked by
                                                               0xFF if it is not sent over the air. */
    } in;                                                 /*!< Input: parsed fields from the response. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_door_lock_get_pin_code_rsp_message_t;

/**
 * @brief Message for the ZCL DoorLock GetUserStatusResponse.
 */
typedef struct ezb_zcl_door_lock_get_user_status_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t                    *header;  /*!< ZCL command header information.
                                                                  See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_door_lock_user_status_payload_t payload; /*!< Parsed payload of the response. */
    } in;                                                /*!< Input: parsed fields from the response. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_door_lock_get_user_status_rsp_message_t;

/**
 * @brief Message for the ZCL DoorLock OperationEventNotification.
 */
typedef struct ezb_zcl_door_lock_operation_event_notif_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t                          *header;  /*!< ZCL command header information.
                                                                        See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_door_lock_operation_event_notif_payload_t payload; /*!< Parsed payload of the notification. */
    } in;                                                          /*!< Input: parsed fields from the notification. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_door_lock_operation_event_notif_message_t;

/**
 * @brief Structure for the ZCL DoorLock LockDoor command request.
 */
typedef struct ezb_zcl_door_lock_lock_door_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl;          /*!< Control information for the ZCL command. */
    bool                       aps_secur_enabled; /*!< APS security enabled transmission. */
} ezb_zcl_door_lock_lock_door_cmd_t;

/**
 * @brief Structure for the ZCL DoorLock UnlockDoor command request.
 * @anchor ezb_zcl_door_lock_unlock_door_cmd_t
 */
typedef ezb_zcl_door_lock_lock_door_cmd_t ezb_zcl_door_lock_unlock_door_cmd_t;

/**
 * @brief Message for the ZCL DoorLock LockDoor.
 */
typedef struct ezb_zcl_door_lock_lock_door_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
    } in;                                /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_door_lock_lock_door_message_t;

/**
 * @brief Message for the ZCL DoorLock UnlockDoor.
 * @anchor ezb_zcl_door_lock_unlock_door_message_t
 */
typedef ezb_zcl_door_lock_lock_door_message_t ezb_zcl_door_lock_unlock_door_message_t;

/**
 * @brief Message for the ZCL DoorLock LockDoor response.
 */
typedef struct ezb_zcl_door_lock_lock_door_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_status_t req_status; /*!< Status of the request command (indicates if the message was received successfully). */
    } in;                            /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_door_lock_lock_door_rsp_message_t;

/**
 * @brief Message for the ZCL DoorLock UnlockDoor response.
 * @anchor ezb_zcl_door_lock_unlock_door_rsp_message_t
 */
typedef ezb_zcl_door_lock_lock_door_rsp_message_t ezb_zcl_door_lock_unlock_door_rsp_message_t;

/**
 * @brief Send ZCL DoorLock LockDoor command request.
 *
 * @param cmd_req Pointer to the LockDoor command request structure, @ref ezb_zcl_door_lock_lock_door_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_door_lock_lock_door_cmd_req(const ezb_zcl_door_lock_lock_door_cmd_t *cmd_req);

/**
 * @brief Send ZCL DoorLock UnlockDoor command request.
 *
 * @param cmd_req Pointer to the UnlockDoor command request structure, @ref ezb_zcl_door_lock_unlock_door_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_door_lock_unlock_door_cmd_req(const ezb_zcl_door_lock_unlock_door_cmd_t *cmd_req);

/**
 * @brief Send ZCL DoorLock SetPINCode command request.
 *
 * @note The PIN code is always sent, the SendPINOverTheAir attribute only controls what the DoorLock server transmits.
 *
 * @param cmd_req Pointer to the SetPINCode command request structure, @ref ezb_zcl_door_lock_set_pin_code_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_door_lock_set_pin_code_cmd_req(const ezb_zcl_door_lock_set_pin_code_cmd_t *cmd_req);

/**
 * @brief Send ZCL DoorLock GetPINCode command request.
 *
 * @param cmd_req Pointer to the GetPINCode command request structure, @ref ezb_zcl_door_lock_get_pin_code_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_door_lock_get_pin_code_cmd_req(const ezb_zcl_door_lock_get_pin_code_cmd_t *cmd_req);

/**
 * @brief Send ZCL DoorLock ClearPINCode command request.
 *
 * @param cmd_req Pointer to the ClearPINCode command request structure, @ref ezb_zcl_door_lock_clear_pin_code_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_door_lock_clear_pin_code_cmd_req(const ezb_zcl_door_lock_clear_pin_code_cmd_t *cmd_req);

/**
 * @brief Send ZCL DoorLock ClearAllPINCodes command request.
 *
 * @param cmd_req Pointer to the ClearAllPINCodes command request structure, @ref ezb_zcl_door_lock_clear_all_pin_codes_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_door_lock_clear_all_pin_codes_cmd_req(const ezb_zcl_door_lock_clear_all_pin_codes_cmd_t *cmd_req);

/**
 * @brief Send ZCL DoorLock SetUserStatus command request.
 *
 * @param cmd_req Pointer to the SetUserStatus command request structure, @ref ezb_zcl_door_lock_set_user_status_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_door_lock_set_user_status_cmd_req(const ezb_zcl_door_lock_set_user_status_cmd_t *cmd_req);

/**
 * @brief Send ZCL DoorLock GetUserStatus command request.
 *
 * @param cmd_req Pointer to the GetUserStatus command request structure, @ref ezb_zcl_door_lock_get_user_status_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_door_lock_get_user_status_cmd_req(const ezb_zcl_door_lock_get_user_status_cmd_t *cmd_req);

/**
 * @brief Send ZCL DoorLock OperationEventNotification command (from the DoorLock server to the client).
 *
 * @note The application is responsible for checking the corresponding *OperationEventMask attribute before sending.
 *       The PIN code is only included if the SendPINOverTheAir attribute of the source endpoint is true, otherwise
 *       the length of the PIN code is kept and the code is masked by 0xFF.
 *
 * @param cmd_req Pointer to the OperationEventNotification command structure, @ref ezb_zcl_door_lock_operation_event_notif_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_door_lock_operation_event_notif_cmd_req(const ezb_zcl_door_lock_operation_event_notif_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
