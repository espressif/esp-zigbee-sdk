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
   WINDOW_COVERING Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the window_covering cluster implementation */
#define EZB_ZCL_WINDOW_COVERING_CLUSTER_REVISION (3)

/**
 * @brief Attribute identifiers for the window_covering server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_WINDOW_COVERING_WINDOW_COVERING_TYPE_ID             = 0x0000U, /*!< WindowCoveringType attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_PHYSICAL_CLOSED_LIMIT_LIFT_ID       = 0x0001U, /*!< PhysicalClosedLimitLift attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_PHYSICAL_CLOSED_LIMIT_TILT_ID       = 0x0002U, /*!< PhysicalClosedLimitTilt attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_CURRENT_POSITION_LIFT_ID            = 0x0003U, /*!< CurrentPositionLift attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_CURRENT_POSITION_TILT_ID            = 0x0004U, /*!< CurrentPositionTilt attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_NUMBER_OF_ACTUATIONS_LIFT_ID        = 0x0005U, /*!< NumberOfActuationsLift attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_NUMBER_OF_ACTUATIONS_TILT_ID        = 0x0006U, /*!< NumberOfActuationsTilt attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_CONFIG_STATUS_ID                    = 0x0007U, /*!< ConfigStatus attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_CURRENT_POSITION_LIFT_PERCENTAGE_ID = 0x0008U, /*!< CurrentPositionLiftPercentage attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_CURRENT_POSITION_TILT_PERCENTAGE_ID = 0x0009U, /*!< CurrentPositionTiltPercentage attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_INSTALLED_OPEN_LIMIT_LIFT_ID        = 0x0010U, /*!< InstalledOpenLimitLift attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_INSTALLED_CLOSED_LIMIT_LIFT_ID      = 0x0011U, /*!< InstalledClosedLimitLift attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_INSTALLED_OPEN_LIMIT_TILT_ID        = 0x0012U, /*!< InstalledOpenLimitTilt attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_INSTALLED_CLOSED_LIMIT_TILT_ID      = 0x0013U, /*!< InstalledClosedLimitTilt attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_VELOCITY_LIFT_ID                    = 0x0014U, /*!< VelocityLift attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_ACCELERATION_TIME_LIFT_ID           = 0x0015U, /*!< AccelerationTimeLift attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_DECELERATION_TIME_LIFT_ID           = 0x0016U, /*!< DecelerationTimeLift attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_MODE_ID                             = 0x0017U, /*!< Mode attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_INTERMEDIATE_SETPOINTS_LIFT_ID      = 0x0018U, /*!< IntermediateSetpointsLift attribute. */
    EZB_ZCL_ATTR_WINDOW_COVERING_INTERMEDIATE_SETPOINTS_TILT_ID      = 0x0019U, /*!< IntermediateSetpointsTilt attribute. */
} ezb_zcl_window_covering_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the WindowCovering server cluster.
 */
typedef struct ezb_zcl_window_covering_cluster_server_config_s {
    uint8_t window_covering_type; /*!< Configurable mandatory WindowCoveringType attribute */
    uint8_t config_status;        /*!< Configurable mandatory ConfigStatus attribute */
    uint8_t mode;                 /*!< Configurable mandatory Mode attribute */
} ezb_zcl_window_covering_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL WindowCoveringType attribute of WindowCovering.
 */
typedef enum {
    EZB_ZCL_WINDOW_COVERING_WINDOW_COVERING_TYPE_ROLLERSHADE                 = 0x00U, /*!< Rollershade */
    EZB_ZCL_WINDOW_COVERING_WINDOW_COVERING_TYPE_ROLLERSHADE2_MOTOR          = 0x01U, /*!< Rollershade2Motor */
    EZB_ZCL_WINDOW_COVERING_WINDOW_COVERING_TYPE_ROLLERSHADE_EXTERIOR        = 0x02U, /*!< RollershadeExterior */
    EZB_ZCL_WINDOW_COVERING_WINDOW_COVERING_TYPE_ROLLERSHADE_EXTERIOR2_MOTOR = 0x03U, /*!< RollershadeExterior2Motor */
    EZB_ZCL_WINDOW_COVERING_WINDOW_COVERING_TYPE_DRAPERY                     = 0x04U, /*!< Drapery */
    EZB_ZCL_WINDOW_COVERING_WINDOW_COVERING_TYPE_AWNING                      = 0x05U, /*!< Awning */
    EZB_ZCL_WINDOW_COVERING_WINDOW_COVERING_TYPE_SHUTTER                     = 0x06U, /*!< Shutter */
    EZB_ZCL_WINDOW_COVERING_WINDOW_COVERING_TYPE_TILT_BLIND_TILT_ONLY        = 0x07U, /*!< TiltBlindTiltOnly */
    EZB_ZCL_WINDOW_COVERING_WINDOW_COVERING_TYPE_TILT_BLIND_LIFT_AND_TILT    = 0x08U, /*!< TiltBlindLiftAndTilt */
    EZB_ZCL_WINDOW_COVERING_WINDOW_COVERING_TYPE_PROJECTOR_SCREEN            = 0x09U, /*!< ProjectorScreen */
} ezb_zcl_window_covering_server_window_covering_type_t;

/**
 * @brief Bitmap for ZCL ConfigStatus attribute of WindowCovering.
 */
typedef enum {
    EZB_ZCL_WINDOW_COVERING_CONFIG_STATUS_OPERATIONAL                   = 0x01U, /*!< Operational */
    EZB_ZCL_WINDOW_COVERING_CONFIG_STATUS_ONLINE                        = 0x02U, /*!< Online */
    EZB_ZCL_WINDOW_COVERING_CONFIG_STATUS_OPEN_AND_UP_COMMANDS_REVERSED = 0x04U, /*!< OpenAndUpCommandsReversed */
    EZB_ZCL_WINDOW_COVERING_CONFIG_STATUS_LIFT_CLOSED_LOOP              = 0x08U, /*!< LiftClosedLoop */
    EZB_ZCL_WINDOW_COVERING_CONFIG_STATUS_TILT_CLOSED_LOOP              = 0x10U, /*!< TiltClosedLoop */
    EZB_ZCL_WINDOW_COVERING_CONFIG_STATUS_LIFT_ENCODER_CONTROLLED       = 0x20U, /*!< LiftEncoderControlled */
    EZB_ZCL_WINDOW_COVERING_CONFIG_STATUS_TILT_ENCODER_CONTROLLED       = 0x40U, /*!< TiltEncoderControlled */
} ezb_zcl_window_covering_server_config_status_t;

/**
 * @brief Bitmap for ZCL Mode attribute of WindowCovering.
 */
typedef enum {
    EZB_ZCL_WINDOW_COVERING_MODE_MOTOR_DIRECTION_REVERSED = 0x01U, /*!< MotorDirectionReversed */
    EZB_ZCL_WINDOW_COVERING_MODE_CALIBRATION_MODE         = 0x02U, /*!< CalibrationMode */
    EZB_ZCL_WINDOW_COVERING_MODE_MAINTENANCE_MODE         = 0x04U, /*!< MaintenanceMode */
    EZB_ZCL_WINDOW_COVERING_MODE_LED_FEEDBACK             = 0x08U, /*!< LEDFeedback */
} ezb_zcl_window_covering_server_mode_t;

/** @brief Default value of WindowCoveringType in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_WINDOW_COVERING_TYPE_DEFAULT_VALUE (0x00)

/** @brief Default value of PhysicalClosedLimitLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_PHYSICAL_CLOSED_LIMIT_LIFT_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of PhysicalClosedLimitLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_PHYSICAL_CLOSED_LIMIT_LIFT_MIN_VALUE (0x0000)

/** @brief Maximum value of PhysicalClosedLimitLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_PHYSICAL_CLOSED_LIMIT_LIFT_MAX_VALUE (0xffff)
/** @brief Default value of PhysicalClosedLimitTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_PHYSICAL_CLOSED_LIMIT_TILT_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of PhysicalClosedLimitTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_PHYSICAL_CLOSED_LIMIT_TILT_MIN_VALUE (0x0000)

/** @brief Maximum value of PhysicalClosedLimitTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_PHYSICAL_CLOSED_LIMIT_TILT_MAX_VALUE (0xffff)
/** @brief Default value of CurrentPositionLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_CURRENT_POSITION_LIFT_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of CurrentPositionLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_CURRENT_POSITION_LIFT_MIN_VALUE (0x0000)

/** @brief Maximum value of CurrentPositionLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_CURRENT_POSITION_LIFT_MAX_VALUE (0xffff)
/** @brief Default value of CurrentPositionTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_CURRENT_POSITION_TILT_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of CurrentPositionTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_CURRENT_POSITION_TILT_MIN_VALUE (0x0000)

/** @brief Maximum value of CurrentPositionTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_CURRENT_POSITION_TILT_MAX_VALUE (0xffff)
/** @brief Default value of NumberOfActuationsLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_NUMBER_OF_ACTUATIONS_LIFT_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of NumberOfActuationsLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_NUMBER_OF_ACTUATIONS_LIFT_MIN_VALUE (0x0000)

/** @brief Maximum value of NumberOfActuationsLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_NUMBER_OF_ACTUATIONS_LIFT_MAX_VALUE (0xffff)
/** @brief Default value of NumberOfActuationsTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_NUMBER_OF_ACTUATIONS_TILT_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of NumberOfActuationsTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_NUMBER_OF_ACTUATIONS_TILT_MIN_VALUE (0x0000)

/** @brief Maximum value of NumberOfActuationsTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_NUMBER_OF_ACTUATIONS_TILT_MAX_VALUE (0xffff)

/** @brief Maximum value of ConfigStatus in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_CONFIG_STATUS_MAX_VALUE (0x7f)

/** @brief Minimum value of CurrentPositionLiftPercentage in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_CURRENT_POSITION_LIFT_PERCENTAGE_MIN_VALUE (0x00)

/** @brief Maximum value of CurrentPositionLiftPercentage in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_CURRENT_POSITION_LIFT_PERCENTAGE_MAX_VALUE (0x64)

/** @brief Minimum value of CurrentPositionTiltPercentage in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_CURRENT_POSITION_TILT_PERCENTAGE_MIN_VALUE (0x00)

/** @brief Maximum value of CurrentPositionTiltPercentage in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_CURRENT_POSITION_TILT_PERCENTAGE_MAX_VALUE (0x64)
/** @brief Default value of InstalledOpenLimitLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INSTALLED_OPEN_LIMIT_LIFT_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of InstalledOpenLimitLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INSTALLED_OPEN_LIMIT_LIFT_MIN_VALUE (0x0000)

/** @brief Maximum value of InstalledOpenLimitLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INSTALLED_OPEN_LIMIT_LIFT_MAX_VALUE (0xffff)
/** @brief Default value of InstalledClosedLimitLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INSTALLED_CLOSED_LIMIT_LIFT_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of InstalledClosedLimitLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INSTALLED_CLOSED_LIMIT_LIFT_MIN_VALUE (0x0000)

/** @brief Maximum value of InstalledClosedLimitLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INSTALLED_CLOSED_LIMIT_LIFT_MAX_VALUE (0xffff)
/** @brief Default value of InstalledOpenLimitTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INSTALLED_OPEN_LIMIT_TILT_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of InstalledOpenLimitTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INSTALLED_OPEN_LIMIT_TILT_MIN_VALUE (0x0000)

/** @brief Maximum value of InstalledOpenLimitTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INSTALLED_OPEN_LIMIT_TILT_MAX_VALUE (0xffff)
/** @brief Default value of InstalledClosedLimitTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INSTALLED_CLOSED_LIMIT_TILT_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of InstalledClosedLimitTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INSTALLED_CLOSED_LIMIT_TILT_MIN_VALUE (0x0000)

/** @brief Maximum value of InstalledClosedLimitTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INSTALLED_CLOSED_LIMIT_TILT_MAX_VALUE (0xffff)
/** @brief Default value of VelocityLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_VELOCITY_LIFT_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of VelocityLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_VELOCITY_LIFT_MIN_VALUE (0x0000)

/** @brief Maximum value of VelocityLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_VELOCITY_LIFT_MAX_VALUE (0xffff)
/** @brief Default value of AccelerationTimeLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_ACCELERATION_TIME_LIFT_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of AccelerationTimeLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_ACCELERATION_TIME_LIFT_MIN_VALUE (0x0000)

/** @brief Maximum value of AccelerationTimeLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_ACCELERATION_TIME_LIFT_MAX_VALUE (0xffff)
/** @brief Default value of DecelerationTimeLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_DECELERATION_TIME_LIFT_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of DecelerationTimeLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_DECELERATION_TIME_LIFT_MIN_VALUE (0x0000)

/** @brief Maximum value of DecelerationTimeLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_DECELERATION_TIME_LIFT_MAX_VALUE (0xffff)
/** @brief Default value of Mode in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_MODE_DEFAULT_VALUE (0x04)

/** @brief Default value of IntermediateSetpointsLift in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INTERMEDIATE_SETPOINTS_LIFT_DEFAULT_VALUE \
    ("\x08"                                                               \
     "1,0x0000")

/** @brief Default value of IntermediateSetpointsTilt in WindowCovering cluster */
#define EZB_ZCL_WINDOW_COVERING_INTERMEDIATE_SETPOINTS_TILT_DEFAULT_VALUE \
    ("\x08"                                                               \
     "1,0x0000")

/**
 * @brief Received Command identifiers for the WindowCovering cluster.
 */
typedef enum {
    EZB_ZCL_CMD_WINDOW_COVERING_UP_OPEN_ID               = 0x00U, /*!< UpOpen command. */
    EZB_ZCL_CMD_WINDOW_COVERING_DOWN_CLOSE_ID            = 0x01U, /*!< DownClose command. */
    EZB_ZCL_CMD_WINDOW_COVERING_STOP_ID                  = 0x02U, /*!< Stop command. */
    EZB_ZCL_CMD_WINDOW_COVERING_GO_TO_LIFT_VALUE_ID      = 0x04U, /*!< GoToLiftValue command. */
    EZB_ZCL_CMD_WINDOW_COVERING_GO_TO_LIFT_PERCENTAGE_ID = 0x05U, /*!< GoToLiftPercentage command. */
    EZB_ZCL_CMD_WINDOW_COVERING_GO_TO_TILT_VALUE_ID      = 0x07U, /*!< GoToTiltValue command. */
    EZB_ZCL_CMD_WINDOW_COVERING_GO_TO_TILT_PERCENTAGE_ID = 0x08U, /*!< GoToTiltPercentage command. */
} ezb_zcl_window_covering_server_cmd_id_t;

typedef ezb_zcl_window_covering_cluster_server_config_t ezb_zcl_window_covering_cluster_config_t;

/**
 * @brief Add an attribute to an window_covering cluster descriptor.
 *
 * @param cluster_desc Pointer to the window_covering cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_window_covering_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                        uint16_t               attr_id,
                                                        const void            *value);

/**
 * @brief Create an window_covering cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the window_covering cluster configuration structure, refer to
 * ezb_zcl_window_covering_cluster_server_config_t or ezb_zcl_window_covering_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_window_covering_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the WindowCovering cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_window_covering_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the WindowCovering cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_window_covering_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_WINDOW_COVERING_CLIENT_ROLE_INIT ezb_zcl_window_covering_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_WINDOW_COVERING_SERVER_ROLE_INIT ezb_zcl_window_covering_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
