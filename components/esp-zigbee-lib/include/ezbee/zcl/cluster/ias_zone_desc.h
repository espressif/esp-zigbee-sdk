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
   IAS_ZONE Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the ias_zone cluster implementation */
#define EZB_ZCL_IAS_ZONE_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the ias_zone server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_IAS_ZONE_ZONE_STATE_ID      = 0x0000U, /*!< ZoneState attribute. */
    EZB_ZCL_ATTR_IAS_ZONE_ZONE_TYPE_ID       = 0x0001U, /*!< ZoneType attribute. */
    EZB_ZCL_ATTR_IAS_ZONE_ZONE_STATUS_ID     = 0x0002U, /*!< ZoneStatus attribute. */
    EZB_ZCL_ATTR_IAS_ZONE_IAS_CIE_ADDRESS_ID = 0x0010U, /*!< IasCieAddress attribute. */
    EZB_ZCL_ATTR_IAS_ZONE_ZONE_ID_ID         = 0x0011U, /*!< ZoneId attribute. */
    EZB_ZCL_ATTR_IAS_ZONE_NUMBER_OF_ZONE_SENSITIVITY_LEVELS_SUPPORTED_ID =
        0x0012U,                                                       /*!< NumberOfZoneSensitivityLevelsSupported attribute. */
    EZB_ZCL_ATTR_IAS_ZONE_CURRENT_ZONE_SENSITIVITY_LEVEL_ID = 0x0013U, /*!< CurrentZoneSensitivityLevel attribute. */
    EZB_ZCL_ATTR_IAS_ZONE_ZONE_CTX_ID                       = 0xeff0U, /*!< ZoneCtx attribute. */
} ezb_zcl_ias_zone_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the IasZone server cluster.
 */
typedef struct ezb_zcl_ias_zone_cluster_server_config_s {
    uint8_t  zone_state;      /*!< Configurable mandatory ZoneState attribute */
    uint16_t zone_type;       /*!< Configurable mandatory ZoneType attribute */
    uint16_t zone_status;     /*!< Configurable mandatory ZoneStatus attribute */
    uint64_t ias_cie_address; /*!< Configurable mandatory IasCieAddress attribute */
    uint8_t  zone_id;         /*!< Configurable mandatory ZoneId attribute */
} ezb_zcl_ias_zone_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL ZoneState attribute of IasZone.
 */
typedef enum {
    EZB_ZCL_IAS_ZONE_ZONE_STATE_NOT_ENROLLED = 0x00U, /*!< NotEnrolled */
    EZB_ZCL_IAS_ZONE_ZONE_STATE_ENROLLED     = 0x01U, /*!< Enrolled */
} ezb_zcl_ias_zone_server_zone_state_t;

/**
 * @brief Enumeration for ZCL ZoneType attribute of IasZone.
 */
typedef enum {
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_STANDARD_CIE              = 0x0000U, /*!< StandardCie */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_MOTION_SENSOR             = 0x000dU, /*!< MotionSensor */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_CONTACT_SWITCH            = 0x0015U, /*!< ContactSwitch */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_DOOR_WINDOW_HANDLE        = 0x0016U, /*!< DoorWindowHandle */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_FIRE_SENSOR               = 0x0028U, /*!< FireSensor */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_WATER_SENSOR              = 0x002aU, /*!< WaterSensor */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_CARBON_MONOXIDE_SENSOR    = 0x002bU, /*!< CarbonMonoxideSensor */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_PERSONAL_EMERGENCY_DEVICE = 0x002cU, /*!< PersonalEmergencyDevice */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_VIBRATION_MOVEMENT_SENSOR = 0x002dU, /*!< VibrationMovementSensor */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_REMOTE_CONTROL            = 0x010fU, /*!< RemoteControl */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_KEY_FOB                   = 0x0115U, /*!< KeyFob */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_KEYPAD                    = 0x021dU, /*!< Keypad */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_STANDARD_WARNING_DEVICE   = 0x0225U, /*!< StandardWarningDevice */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_GLASS_BREAK_SENSOR        = 0x0226U, /*!< GlassBreakSensor */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_SECURITY_REPEATER         = 0x0229U, /*!< SecurityRepeater */
    EZB_ZCL_IAS_ZONE_ZONE_TYPE_INVALID_ZONE_TYPE         = 0xffffU, /*!< InvalidZoneType */
} ezb_zcl_ias_zone_server_zone_type_t;

/**
 * @brief Bitmap for ZCL ZoneStatus attribute of IasZone.
 */
typedef enum {
    EZB_ZCL_IAS_ZONE_ZONE_STATUS_ALARM1             = 0x0001U, /*!< Alarm1 */
    EZB_ZCL_IAS_ZONE_ZONE_STATUS_ALARM2             = 0x0002U, /*!< Alarm2 */
    EZB_ZCL_IAS_ZONE_ZONE_STATUS_TAMPER             = 0x0004U, /*!< Tamper */
    EZB_ZCL_IAS_ZONE_ZONE_STATUS_BATTERY            = 0x0008U, /*!< Battery */
    EZB_ZCL_IAS_ZONE_ZONE_STATUS_SUPERVISION_NOTIFY = 0x0010U, /*!< SupervisionNotify */
    EZB_ZCL_IAS_ZONE_ZONE_STATUS_RESTORE_NOTIFY     = 0x0020U, /*!< RestoreNotify */
    EZB_ZCL_IAS_ZONE_ZONE_STATUS_TROUBLE            = 0x0040U, /*!< Trouble */
    EZB_ZCL_IAS_ZONE_ZONE_STATUS_AC                 = 0x0080U, /*!< AC */
    EZB_ZCL_IAS_ZONE_ZONE_STATUS_TEST               = 0x0100U, /*!< Test */
    EZB_ZCL_IAS_ZONE_ZONE_STATUS_BATTERY_DEFECT     = 0x0200U, /*!< BatteryDefect */
} ezb_zcl_ias_zone_server_zone_status_t;

/** @brief Default value of ZoneState in IasZone cluster */
#define EZB_ZCL_IAS_ZONE_ZONE_STATE_DEFAULT_VALUE (0x00)

/** @brief Default value of ZoneStatus in IasZone cluster */
#define EZB_ZCL_IAS_ZONE_ZONE_STATUS_DEFAULT_VALUE (0x0000)

/** @brief Default value of ZoneId in IasZone cluster */
#define EZB_ZCL_IAS_ZONE_ZONE_ID_DEFAULT_VALUE (0xff)

/** @brief Minimum value of ZoneId in IasZone cluster */
#define EZB_ZCL_IAS_ZONE_ZONE_ID_MIN_VALUE (0x00)

/** @brief Maximum value of ZoneId in IasZone cluster */
#define EZB_ZCL_IAS_ZONE_ZONE_ID_MAX_VALUE (0xff)
/** @brief Default value of NumberOfZoneSensitivityLevelsSupported in IasZone cluster */
#define EZB_ZCL_IAS_ZONE_NUMBER_OF_ZONE_SENSITIVITY_LEVELS_SUPPORTED_DEFAULT_VALUE (0x02)

/** @brief Minimum value of NumberOfZoneSensitivityLevelsSupported in IasZone cluster */
#define EZB_ZCL_IAS_ZONE_NUMBER_OF_ZONE_SENSITIVITY_LEVELS_SUPPORTED_MIN_VALUE (0x02)

/** @brief Maximum value of NumberOfZoneSensitivityLevelsSupported in IasZone cluster */
#define EZB_ZCL_IAS_ZONE_NUMBER_OF_ZONE_SENSITIVITY_LEVELS_SUPPORTED_MAX_VALUE (0xff)
/** @brief Default value of CurrentZoneSensitivityLevel in IasZone cluster */
#define EZB_ZCL_IAS_ZONE_CURRENT_ZONE_SENSITIVITY_LEVEL_DEFAULT_VALUE (0x00)

/** @brief Minimum value of CurrentZoneSensitivityLevel in IasZone cluster */
#define EZB_ZCL_IAS_ZONE_CURRENT_ZONE_SENSITIVITY_LEVEL_MIN_VALUE (0x00)

/** @brief Maximum value of CurrentZoneSensitivityLevel in IasZone cluster */
#define EZB_ZCL_IAS_ZONE_CURRENT_ZONE_SENSITIVITY_LEVEL_MAX_VALUE (0xff)

/**
 * @brief Received Command identifiers for the IasZone cluster.
 */
typedef enum {
    EZB_ZCL_CMD_IAS_ZONE_ZONE_ENROLL_RESPONSE_ID           = 0x00U, /*!< ZoneEnrollResponse command. */
    EZB_ZCL_CMD_IAS_ZONE_INITIATE_NORMAL_OPERATION_MODE_ID = 0x01U, /*!< InitiateNormalOperationMode command. */
    EZB_ZCL_CMD_IAS_ZONE_INITIATE_TEST_MODE_ID             = 0x02U, /*!< InitiateTestMode command. */
} ezb_zcl_ias_zone_server_cmd_id_t;

/**
 * @brief Received Command identifiers for the IasZone cluster.
 */
typedef enum {
    EZB_ZCL_CMD_IAS_ZONE_ZONE_STATUS_CHANGE_NOTIFICATION_ID = 0x00U, /*!< ZoneStatusChangeNotification command. */
    EZB_ZCL_CMD_IAS_ZONE_ZONE_ENROLL_REQUEST_ID             = 0x01U, /*!< ZoneEnrollRequest command. */
} ezb_zcl_ias_zone_client_cmd_id_t;

typedef ezb_zcl_ias_zone_cluster_server_config_t ezb_zcl_ias_zone_cluster_config_t;

/**
 * @brief Add an attribute to an ias_zone cluster descriptor.
 *
 * @param cluster_desc Pointer to the ias_zone cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_zone_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an ias_zone cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the ias_zone cluster configuration structure, refer to
 * ezb_zcl_ias_zone_cluster_server_config_t or ezb_zcl_ias_zone_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_ias_zone_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the IasZone cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_ias_zone_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the IasZone cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_ias_zone_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_IAS_ZONE_CLIENT_ROLE_INIT ezb_zcl_ias_zone_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_IAS_ZONE_SERVER_ROLE_INIT ezb_zcl_ias_zone_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
