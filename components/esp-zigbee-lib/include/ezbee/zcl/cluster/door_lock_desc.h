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
   DOOR_LOCK Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the door_lock cluster implementation */
#define EZB_ZCL_DOOR_LOCK_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the door_lock server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_DOOR_LOCK_LOCK_STATE_ID                      = 0x0000U, /*!< LockState attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_LOCK_TYPE_ID                       = 0x0001U, /*!< LockType attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_ACTUATOR_ENABLED_ID                = 0x0002U, /*!< ActuatorEnabled attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_DOOR_STATE_ID                      = 0x0003U, /*!< DoorState attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_DOOR_OPEN_EVENTS_ID                = 0x0004U, /*!< DoorOpenEvents attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_DOOR_CLOSED_EVENTS_ID              = 0x0005U, /*!< DoorClosedEvents attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_OPEN_PERIOD_ID                     = 0x0006U, /*!< OpenPeriod attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_NUMBER_OF_LOG_RECORDS_SUPPORTED_ID = 0x0010U, /*!< NumberOfLogRecordsSupported attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_NUMBER_OF_TOTAL_USERS_SUPPORTED_ID = 0x0011U, /*!< NumberOfTotalUsersSupported attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_NUMBER_OF_PIN_USERS_SUPPORTED_ID   = 0x0012U, /*!< NumberOfPINUsersSupported attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_NUMBER_OF_RFID_USERS_SUPPORTED_ID  = 0x0013U, /*!< NumberOfRFIDUsersSupported attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_NUMBER_OF_WEEK_DAY_SCHEDULES_SUPPORTED_PER_USER_ID =
        0x0014U, /*!< NumberOfWeekDaySchedulesSupportedPerUser attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_NUMBER_OF_YEAR_DAY_SCHEDULES_SUPPORTED_PER_USER_ID =
        0x0015U, /*!< NumberOfYearDaySchedulesSupportedPerUser attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_NUMBER_OF_HOLIDAY_SCHEDULES_SUPPORTED_ID =
        0x0016U,                                                          /*!< NumberOfHolidaySchedulesSupported attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_MAX_PIN_CODE_LENGTH_ID              = 0x0017U, /*!< MaxPINCodeLength attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_MIN_PIN_CODE_LENGTH_ID              = 0x0018U, /*!< MinPINCodeLength attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_MAX_RFID_CODE_LENGTH_ID             = 0x0019U, /*!< MaxRFIDCodeLength attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_MIN_RFID_CODE_LENGTH_ID             = 0x001aU, /*!< MinRFIDCodeLength attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_ENABLE_LOGGING_ID                   = 0x0020U, /*!< EnableLogging attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_LANGUAGE_ID                         = 0x0021U, /*!< Language attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_LED_SETTINGS_ID                     = 0x0022U, /*!< LEDSettings attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_AUTO_RELOCK_TIME_ID                 = 0x0023U, /*!< AutoRelockTime attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_SOUND_VOLUME_ID                     = 0x0024U, /*!< SoundVolume attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_OPERATING_MODE_ID                   = 0x0025U, /*!< OperatingMode attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_SUPPORTED_OPERATING_MODES_ID        = 0x0026U, /*!< SupportedOperatingModes attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_DEFAULT_CONFIGURATION_REGISTER_ID   = 0x0027U, /*!< DefaultConfigurationRegister attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_ENABLE_LOCAL_PROGRAMMING_ID         = 0x0028U, /*!< EnableLocalProgramming attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_ENABLE_ONE_TOUCH_LOCKING_ID         = 0x0029U, /*!< EnableOneTouchLocking attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_ENABLE_INSIDE_STATUS_LED_ID         = 0x002aU, /*!< EnableInsideStatusLED attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_ENABLE_PRIVACY_MODE_BUTTON_ID       = 0x002bU, /*!< EnablePrivacyModeButton attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_WRONG_CODE_ENTRY_LIMIT_ID           = 0x0030U, /*!< WrongCodeEntryLimit attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_USER_CODE_TEMPORARY_DISABLE_TIME_ID = 0x0031U, /*!< UserCodeTemporaryDisableTime attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_SEND_PIN_OVER_THE_AIR_ID            = 0x0032U, /*!< SendPINOverTheAir attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_REQUIRE_PI_NFOR_RF_OPERATION_ID     = 0x0033U, /*!< RequirePINforRFOperation attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_SECURITY_LEVEL_ID                   = 0x0034U, /*!< SecurityLevel attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_ALARM_MASK_ID                       = 0x0040U, /*!< AlarmMask attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_KEYPAD_OPERATION_EVENT_MASK_ID      = 0x0041U, /*!< KeypadOperationEventMask attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_RF_OPERATION_EVENT_MASK_ID          = 0x0042U, /*!< RFOperationEventMask attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_ID      = 0x0043U, /*!< ManualOperationEventMask attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_RFID_OPERATION_EVENT_MASK_ID        = 0x0044U, /*!< RFIDOperationEventMask attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_KEYPAD_PROGRAMMING_EVENT_MASK_ID    = 0x0045U, /*!< KeypadProgrammingEventMask attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_RF_PROGRAMMING_EVENT_MASK_ID        = 0x0046U, /*!< RFProgrammingEventMask attribute. */
    EZB_ZCL_ATTR_DOOR_LOCK_RFID_PROGRAMMING_EVENT_MASK_ID      = 0x0047U, /*!< RFIDProgrammingEventMask attribute. */
} ezb_zcl_door_lock_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the DoorLock server cluster.
 */
typedef struct ezb_zcl_door_lock_cluster_server_config_s {
    uint8_t lock_state;       /*!< Configurable mandatory LockState attribute */
    uint8_t lock_type;        /*!< Configurable mandatory LockType attribute */
    bool    actuator_enabled; /*!< Configurable mandatory ActuatorEnabled attribute */
} ezb_zcl_door_lock_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL LockState attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_LOCK_STATE_NOT_FULLY_LOCKED = 0x00U, /*!< NotFullyLocked */
    EZB_ZCL_DOOR_LOCK_LOCK_STATE_LOCKED           = 0x01U, /*!< Locked */
    EZB_ZCL_DOOR_LOCK_LOCK_STATE_UNLOCKED         = 0x02U, /*!< Unlocked */
    EZB_ZCL_DOOR_LOCK_LOCK_STATE_UNDEFINED        = 0xffU, /*!< Undefined */
} ezb_zcl_door_lock_server_lock_state_t;

/**
 * @brief Enumeration for ZCL LockType attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_LOCK_TYPE_DEAD_BOLT           = 0x00U, /*!< DeadBolt */
    EZB_ZCL_DOOR_LOCK_LOCK_TYPE_MAGNETIC            = 0x01U, /*!< Magnetic */
    EZB_ZCL_DOOR_LOCK_LOCK_TYPE_OTHER               = 0x02U, /*!< Other */
    EZB_ZCL_DOOR_LOCK_LOCK_TYPE_MORTISE             = 0x03U, /*!< Mortise */
    EZB_ZCL_DOOR_LOCK_LOCK_TYPE_RIM                 = 0x04U, /*!< Rim */
    EZB_ZCL_DOOR_LOCK_LOCK_TYPE_LATCH_BOLT          = 0x05U, /*!< LatchBolt */
    EZB_ZCL_DOOR_LOCK_LOCK_TYPE_CYLINDRICAL_LOCK    = 0x06U, /*!< CylindricalLock */
    EZB_ZCL_DOOR_LOCK_LOCK_TYPE_TUBULAR_LOCK        = 0x07U, /*!< TubularLock */
    EZB_ZCL_DOOR_LOCK_LOCK_TYPE_INTERCONNECTED_LOCK = 0x08U, /*!< InterconnectedLock */
    EZB_ZCL_DOOR_LOCK_LOCK_TYPE_DEAD_LATCH          = 0x09U, /*!< DeadLatch */
    EZB_ZCL_DOOR_LOCK_LOCK_TYPE_DOOR_FURNITURE      = 0x0aU, /*!< DoorFurniture */
} ezb_zcl_door_lock_server_lock_type_t;

/**
 * @brief Enumeration for ZCL DoorState attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_DOOR_STATE_OPEN              = 0x00U, /*!< Open */
    EZB_ZCL_DOOR_LOCK_DOOR_STATE_CLOSED            = 0x01U, /*!< Closed */
    EZB_ZCL_DOOR_LOCK_DOOR_STATE_ERROR_JAMMED      = 0x02U, /*!< ErrorJammed */
    EZB_ZCL_DOOR_LOCK_DOOR_STATE_ERROR_FORCED_OPEN = 0x03U, /*!< ErrorForcedOpen */
    EZB_ZCL_DOOR_LOCK_DOOR_STATE_ERROR_UNSPECIFIED = 0x04U, /*!< ErrorUnspecified */
    EZB_ZCL_DOOR_LOCK_DOOR_STATE_UNDEFINED         = 0xffU, /*!< Undefined */
} ezb_zcl_door_lock_server_door_state_t;

/**
 * @brief Enumeration for ZCL LEDSettings attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_LED_SETTINGS_NEVER_USE_LED                     = 0x00U, /*!< NeverUseLED */
    EZB_ZCL_DOOR_LOCK_LED_SETTINGS_USE_LED_EXCEPT_FOR_ACCESS_ALLOWED = 0x01U, /*!< UseLEDExceptForAccessAllowed */
    EZB_ZCL_DOOR_LOCK_LED_SETTINGS_USE_LED_FOR_ALL_EVENTS            = 0x02U, /*!< UseLEDForAllEvents */
} ezb_zcl_door_lock_server_led_settings_t;

/**
 * @brief Enumeration for ZCL SoundVolume attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_SOUND_VOLUME_SILENT_MODE = 0x00U, /*!< SilentMode */
    EZB_ZCL_DOOR_LOCK_SOUND_VOLUME_LOW_VOLUME  = 0x01U, /*!< LowVolume */
    EZB_ZCL_DOOR_LOCK_SOUND_VOLUME_HIGH_VOLUME = 0x02U, /*!< HighVolume */
} ezb_zcl_door_lock_server_sound_volume_t;

/**
 * @brief Enumeration for ZCL SecurityLevel attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_SECURITY_LEVEL_NETWORK = 0x00U, /*!< Network */
    EZB_ZCL_DOOR_LOCK_SECURITY_LEVEL_APS     = 0x01U, /*!< APS */
} ezb_zcl_door_lock_server_security_level_t;

/**
 * @brief Bitmap for ZCL SupportedOperatingModes attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_SUPPORTED_OPERATING_MODES_NORMAL_MODE_SUPPORTED   = 0x0001U, /*!< NormalModeSupported */
    EZB_ZCL_DOOR_LOCK_SUPPORTED_OPERATING_MODES_VACATION_MODE_SUPPORTED = 0x0002U, /*!< VacationModeSupported */
    EZB_ZCL_DOOR_LOCK_SUPPORTED_OPERATING_MODES_PRIVACY_MODE_SUPPORTED  = 0x0004U, /*!< PrivacyModeSupported */
    EZB_ZCL_DOOR_LOCK_SUPPORTED_OPERATING_MODES_NO_RF_LOCK_OR_UNLOCK_MODE_SUPPORTED =
        0x0008U,                                                                  /*!< NoRFLockOrUnlockModeSupported */
    EZB_ZCL_DOOR_LOCK_SUPPORTED_OPERATING_MODES_PASSAGE_MODE_SUPPORTED = 0x0010U, /*!< PassageModeSupported */
} ezb_zcl_door_lock_server_supported_operating_modes_t;

/**
 * @brief Bitmap for ZCL DefaultConfigurationRegister attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_DEFAULT_CONFIGURATION_REGISTER_DEFAULT_ENABLE_LOCAL_PROGRAMMING_ATTRIBUTE_IS_ENABLED =
        0x0001U, /*!< DefaultEnableLocalProgrammingAttributeIsEnabled */
    EZB_ZCL_DOOR_LOCK_DEFAULT_CONFIGURATION_REGISTER_DEFAULT_KEYPAD_INTERFACE_IS_ENABLED =
        0x0002U, /*!< DefaultKeypadInterfaceIsEnabled */
    EZB_ZCL_DOOR_LOCK_DEFAULT_CONFIGURATION_REGISTER_DEFAULT_RF_INTERFACE_IS_ENABLED =
        0x0004U, /*!< DefaultRFInterfaceIsEnabled */
    EZB_ZCL_DOOR_LOCK_DEFAULT_CONFIGURATION_REGISTER_DEFAULT_SOUND_VOLUME_IS_ENABLED =
        0x0020U, /*!< DefaultSoundVolumeIsEnabled */
    EZB_ZCL_DOOR_LOCK_DEFAULT_CONFIGURATION_REGISTER_DEFAULT_AUTO_RELOCK_TIME_IS_ENABLED =
        0x0040U, /*!< DefaultAutoRelockTimeIsEnabled */
    EZB_ZCL_DOOR_LOCK_DEFAULT_CONFIGURATION_REGISTER_DEFAULT_LED_SETTINGS_IS_ENABLED =
        0x0080U, /*!< DefaultLEDSettingsIsEnabled */
} ezb_zcl_door_lock_server_default_configuration_register_t;

/**
 * @brief Bitmap for ZCL AlarmMask attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_ALARM_MASK_DEADBOLT_JAMMED                     = 0x0001U, /*!< DeadboltJammed */
    EZB_ZCL_DOOR_LOCK_ALARM_MASK_LOCK_RESET_TO_FACTORY_DEFAULTS      = 0x0002U, /*!< LockResetToFactoryDefaults */
    EZB_ZCL_DOOR_LOCK_ALARM_MASK_RF_POWER_MODULE_CYCLED              = 0x0008U, /*!< RFPowerModuleCycled */
    EZB_ZCL_DOOR_LOCK_ALARM_MASK_TAMPER_ALARM_WRONG_CODE_ENTRY_LIMIT = 0x0010U, /*!< TamperAlarmWrongCodeEntryLimit */
    EZB_ZCL_DOOR_LOCK_ALARM_MASK_TAMPER_ALARM_FRONT_ESCUTCHEON_REMOVED_FROM_MAIN =
        0x0020U, /*!< TamperAlarmFrontEscutcheonRemovedFromMain */
    EZB_ZCL_DOOR_LOCK_ALARM_MASK_FORCED_DOOR_OPEN_UNDER_DOOR_LOCKED_CONDITION =
        0x0040U, /*!< ForcedDoorOpenUnderDoorLockedCondition */
} ezb_zcl_door_lock_server_alarm_mask_t;

/**
 * @brief Bitmap for ZCL KeypadOperationEventMask attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_KEYPAD_OPERATION_EVENT_MASK_KEYPAD_OP_UNKNOWN_OR_MS = 0x0001U, /*!< KeypadOpUnknownOrMS */
    EZB_ZCL_DOOR_LOCK_KEYPAD_OPERATION_EVENT_MASK_KEYPAD_OP_LOCK          = 0x0002U, /*!< KeypadOpLock */
    EZB_ZCL_DOOR_LOCK_KEYPAD_OPERATION_EVENT_MASK_KEYPAD_OP_UNLOCK        = 0x0004U, /*!< KeypadOpUnlock */
    EZB_ZCL_DOOR_LOCK_KEYPAD_OPERATION_EVENT_MASK_KEYPAD_OP_LOCK_ERROR_INVALID_PIN =
        0x0008U, /*!< KeypadOpLockErrorInvalidPIN */
    EZB_ZCL_DOOR_LOCK_KEYPAD_OPERATION_EVENT_MASK_KEYPAD_OP_LOCK_ERROR_INVALID_SCHEDULE =
        0x0010U, /*!< KeypadOpLockErrorInvalidSchedule */
    EZB_ZCL_DOOR_LOCK_KEYPAD_OPERATION_EVENT_MASK_KEYPAD_OP_UNLOCK_INVALID_PIN = 0x0020U, /*!< KeypadOpUnlockInvalidPIN */
    EZB_ZCL_DOOR_LOCK_KEYPAD_OPERATION_EVENT_MASK_KEYPAD_OP_UNLOCK_INVALID_SCHEDULE =
        0x0040U,                                                                       /*!< KeypadOpUnlockInvalidSchedule */
    EZB_ZCL_DOOR_LOCK_KEYPAD_OPERATION_EVENT_MASK_KEYPAD_OP_NON_ACCESS_USER = 0x0080U, /*!< KeypadOpNonAccessUser */
} ezb_zcl_door_lock_server_keypad_operation_event_mask_t;

/**
 * @brief Bitmap for ZCL RFOperationEventMask attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_RF_OPERATION_EVENT_MASK_RF_OP_UNKNOWN_OR_MS               = 0x0001U, /*!< RFOpUnknownOrMS */
    EZB_ZCL_DOOR_LOCK_RF_OPERATION_EVENT_MASK_RF_OP_LOCK                        = 0x0002U, /*!< RFOpLock */
    EZB_ZCL_DOOR_LOCK_RF_OPERATION_EVENT_MASK_RF_OP_UNLOCK                      = 0x0004U, /*!< RFOpUnlock */
    EZB_ZCL_DOOR_LOCK_RF_OPERATION_EVENT_MASK_RF_OP_LOCK_ERROR_INVALID_CODE     = 0x0008U, /*!< RFOpLockErrorInvalidCode */
    EZB_ZCL_DOOR_LOCK_RF_OPERATION_EVENT_MASK_RF_OP_LOCK_ERROR_INVALID_SCHEDULE = 0x0010U, /*!< RFOpLockErrorInvalidSchedule */
    EZB_ZCL_DOOR_LOCK_RF_OPERATION_EVENT_MASK_RF_OP_UNLOCK_INVALID_CODE         = 0x0020U, /*!< RFOpUnlockInvalidCode */
    EZB_ZCL_DOOR_LOCK_RF_OPERATION_EVENT_MASK_RF_OP_UNLOCK_INVALID_SCHEDULE     = 0x0040U, /*!< RFOpUnlockInvalidSchedule */
} ezb_zcl_door_lock_server_rf_operation_event_mask_t;

/**
 * @brief Bitmap for ZCL ManualOperationEventMask attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_MANUAL_OP_UNKNOWN_OR_MS     = 0x0001U, /*!< ManualOpUnknownOrMS */
    EZB_ZCL_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_MANUAL_OP_THUMB_TURN_LOCK   = 0x0002U, /*!< ManualOpThumbTurnLock */
    EZB_ZCL_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_MANUAL_OP_THUMB_TURN_UNLOCK = 0x0004U, /*!< ManualOpThumbTurnUnlock */
    EZB_ZCL_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_MANUAL_OP_ONE_TOUCH_LOCK    = 0x0008U, /*!< ManualOpOneTouchLock */
    EZB_ZCL_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_MANUAL_OP_KEY_LOCK          = 0x0010U, /*!< ManualOpKeyLock */
    EZB_ZCL_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_MANUAL_OP_KEY_UNLOCK        = 0x0020U, /*!< ManualOpKeyUnlock */
    EZB_ZCL_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_MANUAL_OP_AUTO_LOCK         = 0x0040U, /*!< ManualOpAutoLock */
    EZB_ZCL_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_MANUAL_OP_SCHEDULE_LOCK     = 0x0080U, /*!< ManualOpScheduleLock */
    EZB_ZCL_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_MANUAL_OP_SCHEDULE_UNLOCK   = 0x0100U, /*!< ManualOpScheduleUnlock */
    EZB_ZCL_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_MANUAL_OP_LOCK              = 0x0200U, /*!< ManualOpLock */
    EZB_ZCL_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_MANUAL_OP_UNLOCK            = 0x0400U, /*!< ManualOpUnlock */
} ezb_zcl_door_lock_server_manual_operation_event_mask_t;

/**
 * @brief Bitmap for ZCL RFIDOperationEventMask attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_RFID_OPERATION_EVENT_MASK_RFID_OP_UNKNOWN_OR_MS           = 0x0001U, /*!< RFIDOpUnknownOrMS */
    EZB_ZCL_DOOR_LOCK_RFID_OPERATION_EVENT_MASK_RFID_OP_LOCK                    = 0x0002U, /*!< RFIDOpLock */
    EZB_ZCL_DOOR_LOCK_RFID_OPERATION_EVENT_MASK_RFID_OP_UNLOCK                  = 0x0004U, /*!< RFIDOpUnlock */
    EZB_ZCL_DOOR_LOCK_RFID_OPERATION_EVENT_MASK_RFID_OP_LOCK_ERROR_INVALID_RFID = 0x0008U, /*!< RFIDOpLockErrorInvalidRFID */
    EZB_ZCL_DOOR_LOCK_RFID_OPERATION_EVENT_MASK_RFID_OP_LOCK_ERROR_INVALID_SCHEDULE =
        0x0010U, /*!< RFIDOpLockErrorInvalidSchedule */
    EZB_ZCL_DOOR_LOCK_RFID_OPERATION_EVENT_MASK_RFID_OP_UNLOCK_ERROR_INVALID_RFID =
        0x0020U, /*!< RFIDOpUnlockErrorInvalidRFID */
    EZB_ZCL_DOOR_LOCK_RFID_OPERATION_EVENT_MASK_RFID_OP_UNLOCK_ERROR_INVALID_SCHEDULE =
        0x0040U, /*!< RFIDOpUnlockErrorInvalidSchedule */
} ezb_zcl_door_lock_server_rfid_operation_event_mask_t;

/**
 * @brief Bitmap for ZCL KeypadProgrammingEventMask attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_KEYPAD_PROGRAMMING_EVENT_MASK_KEYPAD_PROG_UNKNOWN_OR_MS = 0x0001U, /*!< KeypadProgUnknownOrMS */
    EZB_ZCL_DOOR_LOCK_KEYPAD_PROGRAMMING_EVENT_MASK_KEYPAD_PROG_MASTER_CODE_CHANGED =
        0x0002U,                                                                       /*!< KeypadProgMasterCodeChanged */
    EZB_ZCL_DOOR_LOCK_KEYPAD_PROGRAMMING_EVENT_MASK_KEYPAD_PROG_PIN_ADDED   = 0x0004U, /*!< KeypadProgPINAdded */
    EZB_ZCL_DOOR_LOCK_KEYPAD_PROGRAMMING_EVENT_MASK_KEYPAD_PROG_PIN_DELETED = 0x0008U, /*!< KeypadProgPINDeleted */
    EZB_ZCL_DOOR_LOCK_KEYPAD_PROGRAMMING_EVENT_MASK_KEYPAD_PROG_PIN_CHANGED = 0x0010U, /*!< KeypadProgPINChanged */
} ezb_zcl_door_lock_server_keypad_programming_event_mask_t;

/**
 * @brief Bitmap for ZCL RFProgrammingEventMask attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_RF_PROGRAMMING_EVENT_MASK_RF_PROG_UNKNOWN_OR_MS = 0x0001U, /*!< RFProgUnknownOrMS */
    EZB_ZCL_DOOR_LOCK_RF_PROGRAMMING_EVENT_MASK_RF_PROG_PIN_ADDED     = 0x0004U, /*!< RFProgPINAdded */
    EZB_ZCL_DOOR_LOCK_RF_PROGRAMMING_EVENT_MASK_RF_PROG_PIN_DELETED   = 0x0008U, /*!< RFProgPINDeleted */
    EZB_ZCL_DOOR_LOCK_RF_PROGRAMMING_EVENT_MASK_RF_PROG_PIN_CHANGED   = 0x0010U, /*!< RFProgPINChanged */
    EZB_ZCL_DOOR_LOCK_RF_PROGRAMMING_EVENT_MASK_RF_PROG_RFID_ADDED    = 0x0020U, /*!< RFProgRFIDAdded */
    EZB_ZCL_DOOR_LOCK_RF_PROGRAMMING_EVENT_MASK_RF_PROG_RFID_DELETED  = 0x0040U, /*!< RFProgRFIDDeleted */
} ezb_zcl_door_lock_server_rf_programming_event_mask_t;

/**
 * @brief Bitmap for ZCL RFIDProgrammingEventMask attribute of DoorLock.
 */
typedef enum {
    EZB_ZCL_DOOR_LOCK_RFID_PROGRAMMING_EVENT_MASK_RFID_PROG_UNKNOWN_OR_MS = 0x0001U, /*!< RFIDProgUnknownOrMS */
    EZB_ZCL_DOOR_LOCK_RFID_PROGRAMMING_EVENT_MASK_RFID_PROG_RFID_ADDED    = 0x0020U, /*!< RFIDProgRFIDAdded */
    EZB_ZCL_DOOR_LOCK_RFID_PROGRAMMING_EVENT_MASK_RFID_PROG_RFID_DELETED  = 0x0040U, /*!< RFIDProgRFIDDeleted */
} ezb_zcl_door_lock_server_rfid_programming_event_mask_t;

/** @brief Minimum value of ActuatorEnabled in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_ACTUATOR_ENABLED_MIN_VALUE (0x00)

/** @brief Maximum value of ActuatorEnabled in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_ACTUATOR_ENABLED_MAX_VALUE (0x01)

/** @brief Default value of NumberOfLogRecordsSupported in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_NUMBER_OF_LOG_RECORDS_SUPPORTED_DEFAULT_VALUE (0x0000)

/** @brief Default value of NumberOfTotalUsersSupported in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_NUMBER_OF_TOTAL_USERS_SUPPORTED_DEFAULT_VALUE (0x0000)

/** @brief Default value of NumberOfPINUsersSupported in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_NUMBER_OF_PIN_USERS_SUPPORTED_DEFAULT_VALUE (0x0000)

/** @brief Default value of NumberOfRFIDUsersSupported in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_NUMBER_OF_RFID_USERS_SUPPORTED_DEFAULT_VALUE (0x0000)

/** @brief Default value of NumberOfWeekDaySchedulesSupportedPerUser in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_NUMBER_OF_WEEK_DAY_SCHEDULES_SUPPORTED_PER_USER_DEFAULT_VALUE (0x00)

/** @brief Default value of NumberOfYearDaySchedulesSupportedPerUser in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_NUMBER_OF_YEAR_DAY_SCHEDULES_SUPPORTED_PER_USER_DEFAULT_VALUE (0x00)

/** @brief Default value of NumberOfHolidaySchedulesSupported in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_NUMBER_OF_HOLIDAY_SCHEDULES_SUPPORTED_DEFAULT_VALUE (0x00)

/** @brief Default value of MaxPINCodeLength in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_MAX_PIN_CODE_LENGTH_DEFAULT_VALUE (0x08)

/** @brief Default value of MinPINCodeLength in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_MIN_PIN_CODE_LENGTH_DEFAULT_VALUE (0x04)

/** @brief Default value of MaxRFIDCodeLength in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_MAX_RFID_CODE_LENGTH_DEFAULT_VALUE (0x14)

/** @brief Default value of MinRFIDCodeLength in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_MIN_RFID_CODE_LENGTH_DEFAULT_VALUE (0x08)

/** @brief Default value of EnableLogging in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_ENABLE_LOGGING_DEFAULT_VALUE (0x00)

/** @brief Default value of Language in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_LANGUAGE_DEFAULT_VALUE \
    ("\x04"                                      \
     "0x00")

/** @brief Default value of LEDSettings in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_LED_SETTINGS_DEFAULT_VALUE (0x00)

/** @brief Default value of AutoRelockTime in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_AUTO_RELOCK_TIME_DEFAULT_VALUE (0x00000000)

/** @brief Default value of SoundVolume in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_SOUND_VOLUME_DEFAULT_VALUE (0x00)

/** @brief Default value of OperatingMode in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_OPERATING_MODE_DEFAULT_VALUE (0x00)

/** @brief Default value of SupportedOperatingModes in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_SUPPORTED_OPERATING_MODES_DEFAULT_VALUE (0x0001)

/** @brief Default value of DefaultConfigurationRegister in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_DEFAULT_CONFIGURATION_REGISTER_DEFAULT_VALUE (0x0000)

/** @brief Default value of EnableLocalProgramming in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_ENABLE_LOCAL_PROGRAMMING_DEFAULT_VALUE (0x01)

/** @brief Default value of EnableOneTouchLocking in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_ENABLE_ONE_TOUCH_LOCKING_DEFAULT_VALUE (0x0000)

/** @brief Default value of EnableInsideStatusLED in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_ENABLE_INSIDE_STATUS_LED_DEFAULT_VALUE (0x00)

/** @brief Default value of EnablePrivacyModeButton in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_ENABLE_PRIVACY_MODE_BUTTON_DEFAULT_VALUE (0x00)

/** @brief Default value of WrongCodeEntryLimit in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_WRONG_CODE_ENTRY_LIMIT_DEFAULT_VALUE (0x00)

/** @brief Default value of UserCodeTemporaryDisableTime in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_USER_CODE_TEMPORARY_DISABLE_TIME_DEFAULT_VALUE (0x00)

/** @brief Default value of SendPINOverTheAir in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_SEND_PIN_OVER_THE_AIR_DEFAULT_VALUE (0x00)

/** @brief Default value of RequirePINforRFOperation in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_REQUIRE_PI_NFOR_RF_OPERATION_DEFAULT_VALUE (0x00)

/** @brief Default value of SecurityLevel in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_SECURITY_LEVEL_DEFAULT_VALUE (0x00)

/** @brief Default value of AlarmMask in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_ALARM_MASK_DEFAULT_VALUE (0x0000)

/** @brief Default value of KeypadOperationEventMask in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_KEYPAD_OPERATION_EVENT_MASK_DEFAULT_VALUE (0x0000)

/** @brief Default value of RFOperationEventMask in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_RF_OPERATION_EVENT_MASK_DEFAULT_VALUE (0x00)

/** @brief Minimum value of RFOperationEventMask in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_RF_OPERATION_EVENT_MASK_MIN_VALUE (0x00)

/** @brief Maximum value of RFOperationEventMask in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_RF_OPERATION_EVENT_MASK_MAX_VALUE (0x00)
/** @brief Default value of ManualOperationEventMask in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_MANUAL_OPERATION_EVENT_MASK_DEFAULT_VALUE (0x0000)

/** @brief Default value of RFIDOperationEventMask in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_RFID_OPERATION_EVENT_MASK_DEFAULT_VALUE (0x0000)

/** @brief Default value of KeypadProgrammingEventMask in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_KEYPAD_PROGRAMMING_EVENT_MASK_DEFAULT_VALUE (0x0000)

/** @brief Default value of RFProgrammingEventMask in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_RF_PROGRAMMING_EVENT_MASK_DEFAULT_VALUE (0x0000)

/** @brief Default value of RFIDProgrammingEventMask in DoorLock cluster */
#define EZB_ZCL_DOOR_LOCK_RFID_PROGRAMMING_EVENT_MASK_DEFAULT_VALUE (0x0000)

/**
 * @brief Received Command identifiers for the DoorLock cluster.
 */
typedef enum {
    EZB_ZCL_CMD_DOOR_LOCK_LOCK_DOOR_ID               = 0x00U, /*!< LockDoor command. */
    EZB_ZCL_CMD_DOOR_LOCK_UNLOCK_DOOR_ID             = 0x01U, /*!< UnlockDoor command. */
    EZB_ZCL_CMD_DOOR_LOCK_TOGGLE_ID                  = 0x02U, /*!< Toggle command. */
    EZB_ZCL_CMD_DOOR_LOCK_UNLOCK_WITH_TIMEOUT_ID     = 0x03U, /*!< UnlockWithTimeout command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_LOG_RECORD_ID          = 0x04U, /*!< GetLogRecord command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_PIN_CODE_ID            = 0x05U, /*!< SetPINCode command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_PIN_CODE_ID            = 0x06U, /*!< GetPINCode command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_PIN_CODE_ID          = 0x07U, /*!< ClearPINCode command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_ALL_PIN_CODES_ID     = 0x08U, /*!< ClearAllPINCodes command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_USER_STATUS_ID         = 0x09U, /*!< SetUserStatus command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_USER_STATUS_ID         = 0x0AU, /*!< GetUserStatus command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_WEEKDAY_SCHEDULE_ID    = 0x0BU, /*!< SetWeekdaySchedule command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_WEEKDAY_SCHEDULE_ID    = 0x0CU, /*!< GetWeekdaySchedule command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_WEEKDAY_SCHEDULE_ID  = 0x0DU, /*!< ClearWeekdaySchedule command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_YEAR_DAY_SCHEDULE_ID   = 0x0EU, /*!< SetYearDaySchedule command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_YEAR_DAY_SCHEDULE_ID   = 0x0FU, /*!< GetYearDaySchedule command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_YEAR_DAY_SCHEDULE_ID = 0x10U, /*!< ClearYearDaySchedule command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_HOLIDAY_SCHEDULE_ID    = 0x11U, /*!< SetHolidaySchedule command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_HOLIDAY_SCHEDULE_ID    = 0x12U, /*!< GetHolidaySchedule command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_HOLIDAY_SCHEDULE_ID  = 0x13U, /*!< ClearHolidaySchedule command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_USER_TYPE_ID           = 0x14U, /*!< SetUserType command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_USER_TYPE_ID           = 0x15U, /*!< GetUserType command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_RFID_CODE_ID           = 0x16U, /*!< SetRFIDCode command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_RFID_CODE_ID           = 0x17U, /*!< GetRFIDCode command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_RFID_CODE_ID         = 0x18U, /*!< ClearRFIDCode command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_ALL_RFID_CODES_ID    = 0x19U, /*!< ClearAllRFIDCodes command. */
} ezb_zcl_door_lock_server_cmd_id_t;

/**
 * @brief Received Command identifiers for the DoorLock cluster.
 */
typedef enum {
    EZB_ZCL_CMD_DOOR_LOCK_LOCK_DOOR_RESPONSE_ID               = 0x00U, /*!< LockDoorResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_UNLOCK_DOOR_RESPONSE_ID             = 0x01U, /*!< UnlockDoorResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_TOGGLE_RESPONSE_ID                  = 0x02U, /*!< ToggleResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_UNLOCK_WITH_TIMEOUT_RESPONSE_ID     = 0x03U, /*!< UnlockWithTimeoutResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_LOG_RECORD_RESPONSE_ID          = 0x04U, /*!< GetLogRecordResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_PIN_CODE_RESPONSE_ID            = 0x05U, /*!< SetPINCodeResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_PIN_CODE_RESPONSE_ID            = 0x06U, /*!< GetPINCodeResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_PIN_CODE_RESPONSE_ID          = 0x07U, /*!< ClearPINCodeResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_ALL_PIN_CODES_RESPONSE_ID     = 0x08U, /*!< ClearAllPINCodesResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_USER_STATUS_RESPONSE_ID         = 0x09U, /*!< SetUserStatusResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_USER_STATUS_RESPONSE_ID         = 0x0AU, /*!< GetUserStatusResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_WEEKDAY_SCHEDULE_RESPONSE_ID    = 0x0BU, /*!< SetWeekdayScheduleResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_WEEKDAY_SCHEDULE_RESPONSE_ID    = 0x0CU, /*!< GetWeekdayScheduleResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_WEEKDAY_SCHEDULE_RESPONSE_ID  = 0x0DU, /*!< ClearWeekdayScheduleResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_YEAR_DAY_SCHEDULE_RESPONSE_ID   = 0x0EU, /*!< SetYearDayScheduleResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_YEAR_DAY_SCHEDULE_RESPONSE_ID   = 0x0FU, /*!< GetYearDayScheduleResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_YEAR_DAY_SCHEDULE_RESPONSE_ID = 0x10U, /*!< ClearYearDayScheduleResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_HOLIDAY_SCHEDULE_RESPONSE_ID    = 0x11U, /*!< SetHolidayScheduleResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_HOLIDAY_SCHEDULE_RESPONSE_ID    = 0x12U, /*!< GetHolidayScheduleResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_HOLIDAY_SCHEDULE_RESPONSE_ID  = 0x13U, /*!< ClearHolidayScheduleResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_USER_TYPE_RESPONSE_ID           = 0x14U, /*!< SetUserTypeResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_USER_TYPE_RESPONSE_ID           = 0x15U, /*!< GetUserTypeResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_SET_RFID_CODE_RESPONSE_ID           = 0x16U, /*!< SetRFIDCodeResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_GET_RFID_CODE_RESPONSE_ID           = 0x17U, /*!< GetRFIDCodeResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_RFID_CODE_RESPONSE_ID         = 0x18U, /*!< ClearRFIDCodeResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_CLEAR_ALL_RFID_CODES_RESPONSE_ID    = 0x19U, /*!< ClearAllRFIDCodesResponse command. */
    EZB_ZCL_CMD_DOOR_LOCK_OPERATING_EVENT_NOTIFICATION_ID     = 0x20U, /*!< OperatingEventNotification command. */
    EZB_ZCL_CMD_DOOR_LOCK_PROGRAMMING_EVENT_NOTIFICATION_ID   = 0x21U, /*!< ProgrammingEventNotification command. */
} ezb_zcl_door_lock_client_cmd_id_t;

typedef ezb_zcl_door_lock_cluster_server_config_t ezb_zcl_door_lock_cluster_config_t;

/**
 * @brief Add an attribute to an door_lock cluster descriptor.
 *
 * @param cluster_desc Pointer to the door_lock cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_door_lock_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an door_lock cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the door_lock cluster configuration structure, refer to
 * ezb_zcl_door_lock_cluster_server_config_t or ezb_zcl_door_lock_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_door_lock_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the DoorLock cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_door_lock_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the DoorLock cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_door_lock_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_DOOR_LOCK_CLIENT_ROLE_INIT ezb_zcl_door_lock_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_DOOR_LOCK_SERVER_ROLE_INIT ezb_zcl_door_lock_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
