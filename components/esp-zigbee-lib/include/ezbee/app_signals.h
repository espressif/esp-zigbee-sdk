/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_APP_SIGNAL_H
#define ESP_ZIGBEE_APP_SIGNAL_H

#include <ezbee/core_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The group of the application signal
 */
typedef enum ezb_app_signal_group_e {
    EZB_APP_SIGNAL_GROUP_ZDO,
    EZB_APP_SIGNAL_GROUP_BDB,
    EZB_APP_SIGNAL_GROUP_NWK,
    EZB_APP_SIGNAL_GROUP_MAX_NR,
} ezb_app_signal_group_t;

/**
 * @brief The macro to create an application signal
 *
 * The low 8 bits are the signal number in the group.
 * The high 8bits are the signal group number.
 *
 * @param group The group of the application signal
 * @param signal The signal of the application signal
 *
 * @return The application signal
 */
#define EZB_APP_SIGNAL(group, signal) ((group) << 8 | (signal))

/**
 * @brief signal passed to the ezb_application_signal_handler
 * @anchor ezb_app_signal_type_e
 */
enum ezb_app_signal_type_e {
    /*
     * Start of ZDO signals
     */

    /**
    * Overview:
    * - The device has started in non-BDB commissioning mode.
    *
    * When generated:
    * - After the device has started and completed non-BDB commissioning.
    * - In case of a commissioning error.
    *
    * Payload:
    * - None.
    */
    EZB_ZDO_SIGNAL_DEFAULT_START = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_ZDO, 0x00),

    /**
    * Overview:
    * - Stack framework (scheduler, buffer pool, NVRAM, etc.) startup complete,
    *   ready for initializing bdb commissioning.
    *
    * When generated:
    * - When the stack starts using the ezb_start(false) method.
    *
    * Payload:
    * - None.
    */
    EZB_ZDO_SIGNAL_SKIP_STARTUP = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_ZDO, 0x01),

    /**
    * Overview:
    * - Indicates corrupted or incorrect signal information.
    *
    * When generated:
    * - When incorrect signal information is detected.
    *
    *
    * Payload:
    * - None
    */
    EZB_ZDO_SIGNAL_ERROR = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_ZDO, 0x02),

    /**
    * Overview:
    * - Indicates that the current device has left the network.
    *
    * When generated:
    * - Upon receiving the Leave command.
    *
    * Payload:
    * - Refer to ezb_zdo_signal_leave_params_t
    */
    EZB_ZDO_SIGNAL_LEAVE = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_ZDO, 0x03),

    /**
    * Overview:
    * - Indicates that a device (child or neighbor) has left the network.
    *
    * When generated:
    * - When the leave command is received from the device.
    *
    * Payload:
    * - Refer to ezb_zdo_signal_leave_indication_params_t
    */
    EZB_ZDO_SIGNAL_LEAVE_INDICATION = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_ZDO, 0x04),

    /**
    * Overview:
    * - Indicates that a Zigbee device has joined or rejoined the network.
    *
    * When generated:
    * - Upon receiving the device_annce command.
    *
    * Payload:
    * - Refer to ezb_zdo_signal_device_annce_params_t
    */
    EZB_ZDO_SIGNAL_DEVICE_ANNCE = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_ZDO, 0x05),

    /**
    * Overview:
    * - Notify that the destination device is unavailable.
    *
    * When generated:
    *  - When the stack could not send a packet over NWK or APS, for example:
    *      - No ACK on the MAC layer;
    *      - No response to a network address request;
    *      - No APS-ACK to an APS packet.
    *
    * Payload:
    * - Refer to ezb_zdo_signal_device_unavailable_params_t
    */
    EZB_ZDO_SIGNAL_DEVICE_UNAVAILABLE = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_ZDO, 0x06),

    /**
    * Overview:
    * - Indicates that a device has joined, rejoined, or left the network from the Trust Center or its parents.
    *
    * When generated:
    *  - Standard device secured rejoin.
    *  - Standard device unsecured join.
    *  - Device left.
    *  - Standard device trust center rejoin.
    *
    * Payload:
    * - Refer to ezb_zdo_signal_device_update_params_t
    */
    EZB_ZDO_SIGNAL_DEVICE_UPDATE = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_ZDO, 0x07),

    /**
    * Overview:
    * - Indicates that a new device has been authorized by the Trust Center in the network.
    *
    * When generated:
    *  - Upon successful authorization.
    *  - Upon authorization failure.
    *  - Upon authorization timeout.
    *
    * Payload:
    * - Refer to ezb_zdo_signal_device_authorized_params_t
    */
    EZB_ZDO_SIGNAL_DEVICE_AUTHORIZED = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_ZDO, 0x08),

    /*
     * Start of BDB signals
     */

    /**
    * Overview:
    * - Indicate the basic network information of factory new device has been initialized,
    *   ready for Zigbee commissioning
    *
    * When generated:
    * - Upon the basic device behavior has been initialization
    *
    * Payload:
    * - Refer to ezb_bdb_signal_simple_params_t
    */
    EZB_BDB_SIGNAL_DEVICE_FIRST_START = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_BDB, 0x00),

    /**
    * Overview:
    * - Indicate device joins or rejoins network from the configured network information.
    *
    * When generated:
    * - Upon the device joining or rejoining Zigbee network using configuration network information.
    *
    * Payload:
    * - Refer to ezb_bdb_signal_simple_params_t
    */
    EZB_BDB_SIGNAL_DEVICE_REBOOT = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_BDB, 0x01),

    /**
    * Overview:
    * - Indicates the completion of BDB network steering.
    *
    * When generated:
    * - When the device initiates the network steering commissioning process.
    *
    * Payload:
    * - Refer to ezb_bdb_signal_simple_params_t
    */
    EZB_BDB_SIGNAL_STEERING = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_BDB, 0x02),

    /**
    * Overview:
    * - Indicates the completion of BDB network formation.
    *
    * When generated:
    * - When the device initiates the network formation commissioning process.
    *
    * Payload:
    * - Refer to ezb_bdb_signal_simple_params_t
    */
    EZB_BDB_SIGNAL_FORMATION = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_BDB, 0x03),

    /**
    * Overview:
    * - Indicates the completion of BDB finding and binding (F&B) for a initiator endpoint.
    *
    * When generated:
    * - When F&B initiator timeout.
    *
    * Payload:
    * - Refer to ezb_bdb_signal_simple_params_t
    */
    EZB_BDB_SIGNAL_FINDING_AND_BINDING_INITIATOR_FINISHED = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_BDB, 0x04),

    /**
    * Overview:
    * - Indicates the completion of BDB finding and binding (F&B) for a target endpoint.
    *
    * When generated:
    * - When F&B target timeout.
    *
    * Payload:
    * - Refer to ezb_bdb_signal_simple_params_t
    */
    EZB_BDB_SIGNAL_FINDING_AND_BINDING_TARGET_FINISHED = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_BDB, 0x05),

    /**
    * Overview:
    * - Indicates the completion of Touchlink commissioning for a initiator.
    *
    * When generated:
    * - EZB_BDB_STATUS_SUCCESS: If the touchlink initiator successfully completes the commissioning procedure.
    * - EZB_BDB_STATUS_NO_SCAN_RESPONSE: If no scan response is received while scanning for targets.
    * - EZB_BDB_STATUS_NOT_PERMITTED: If the network type is centralized, or the initiator is in an incorrect commissioning state.
    * - EZB_BDB_STATUS_NO_NETWORK: If the Touchlink initiator fails during the network_start process.
    * - EZB_BDB_STATUS_NOT_AA_CAPABLE: If the initiator is not address assignment capable during touchlink.
    * - EZB_BDB_STATUS_TARGET_FAILURE: If the touchlink initiator fails during the join_router or join_ed process.
    *
    * Payload:
    * - Refer to ezb_bdb_signal_simple_params_t
    */
    EZB_BDB_SIGNAL_TOUCHLINK_INITIATOR_FINISHED = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_BDB, 0x06),

    /**
    * Overview:
    * - Indicates the completion of Touchlink commissioning for a target.
    *
    * When generated:
    * - EZB_BDB_STATUS_SUCCESS: If the touchlink target successfully completes the commissioning procedure.
    * - EZB_BDB_STATUS_TARGET_FAILURE: If the touchlink target times out during commissioning (no target selected)
    *   or during a transaction (target selected but no subsequent step).
    * - EZB_BDB_STATUS_NO_NETWORK: If the touchlink target is selected but fails during the network_start, join_router,
    *   or join_ed process.
    *
    * Payload:
    * - Refer to ezb_bdb_signal_simple_params_t
    */
    EZB_BDB_SIGNAL_TOUCHLINK_TARGET_FINISHED = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_BDB, 0x07),

    /*
     * Start of NWK signals
     */

    /**
    * Overview:
    * - [Obsolete] Indicates that a new device has initiated an association procedure.
    *
    * When generated:
    * - When a new device is associated.
    *
    * Payload:
    * - Refer to ezb_nwk_signal_device_associated_params_t
    */
    EZB_NWK_SIGNAL_DEVICE_ASSOCIATED = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_NWK, 0x00),

    /**
    * Overview:
    * - Indicates that the Neighbor Table has expired, and no active route links remain.
    *
    * When generated:
    * - When all routers in the neighbor table were stale.
    *
    * Payload:
    * - None
    */
    EZB_NWK_SIGNAL_NO_ACTIVE_LINKS_LEFT = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_NWK, 0x01),

    /**
    * Overview:
    * - Detects a PAN ID conflict and inquires for a resolution.
    *
    * When generated:
    *  - Upon detecting a PAN ID conflict.
    *
    * Payload:
    * - None
    */
    EZB_NWK_SIGNAL_PANID_CONFLICT_DETECTED = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_NWK, 0x02),

    /**
    * Overview:
    * - Indicates that a network failure has been detected.
    *
    * When generated:
    * - Triggered when the network encounters a failure and the application can implement
    *   error handling based on the reported status.
    *
    * Payload:
    * - Refer to ezb_nwk_signal_network_status_params_t
    */
    EZB_NWK_SIGNAL_NETWORK_STATUS = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_NWK, 0x03),

    /**
    * Overview:
    * - Indicates the status of the network (open or closed).
    *
    * When generated:
    *  - When the network is opened.
    *  - When the network is closed.
    *
    * Payload:
    * - Refer to ezb_nwk_signal_permit_join_status_params_t
    */
    EZB_NWK_SIGNAL_PERMIT_JOIN_STATUS = EZB_APP_SIGNAL(EZB_APP_SIGNAL_GROUP_NWK, 0x04),

    EZB_APP_SIGNAL_END,
};

/**
 * @brief The type of application signal, see @ref ezb_app_signal_type_e
 * @anchor ezb_app_signal_type_t
 */
typedef uint16_t ezb_app_signal_type_t;

/**
 * @brief The type of leave
 */
enum ezb_zdo_leave_type_e {
    EZB_ZDO_LEAVE_TYPE_RESET  = 0, /*!< Leave without rejoin */
    EZB_ZDO_LEAVE_TYPE_REJOIN = 1, /*!< Leave with rejoin */
};

/**
 * @brief Represents the type of leave
 */
typedef uint8_t ezb_zdo_leave_type_t;

/**
 * @brief The action of the trust center
 */
 enum ezb_zdo_tc_action_e {
    EZB_ZDO_TC_ACTION_ACCEPT = 0,   /*!< Accept the device to join the network */
    EZB_ZDO_TC_ACTION_DENY,         /*!< Deny the device to join the network */
    EZB_ZDO_TC_ACTION_IGNORE,       /*!< Ignore the request to join the network */
};

/**
 * @brief Represents the action of the trust center
 */
typedef uint8_t ezb_zdo_tc_action_t;

/**
 * @brief The status of the device update
 */
enum ezb_zdo_upddev_status_e {
    EZB_ZDO_UPDDEV_SECURE_REJOIN = 0x00,  /*!< Secure rejoin */
    EZB_ZDO_UPDDEV_UNSECURE_JOIN = 0x01,  /*!< Unsecure join */
    EZB_ZDO_UPDDEV_DEVICE_LEFT   = 0x02,  /*!< Device left */
    EZB_ZDO_UPDDEV_TC_REJOIN     = 0x03,  /*!< TC rejoin */
};

/**
 * @brief Represents the status of the device update
 */
typedef uint8_t ezb_zdo_upddev_status_t;

/**
 * @brief The type of authorization
 */
 enum ezb_zdo_auth_type_e {
    EZB_ZDO_AUTH_TYPE_LEGACY = 0,       /*!< Legacy authorization type, pre-R21 */
    EZB_ZDO_AUTH_TYPE_TCLK,             /*!< Authorized by Static Trust Center Link Key Exchange */
};

/**
 * @brief Represents the type of authorization
 */
typedef uint8_t ezb_zdo_auth_type_t;

/**
 * @brief The status of authorization
 */
enum ezb_zdo_auth_status_e {
    EZB_ZDO_AUTH_STATUS_SUCCESS = 0,        /*!< Authorization successfully completed */
    EZB_ZDO_AUTH_STATUS_TIMEOUT,            /*!< Authorization timed out */
    EZB_ZDO_AUTH_STATUS_FAILED,             /*!< Authorization failed */
};

/**
 * @brief Represents the status of authorization
 */
typedef uint8_t ezb_zdo_auth_status_t;

/**
 * @brief The payload of EZB_ZDO_SIGNAL_LEAVE signal
 */
typedef struct ezb_zdo_signal_leave_params_s {
    ezb_zdo_leave_type_t leave_type;    /*!< Leave type, refer to ezb_zdo_leave_type_t */
} ezb_zdo_signal_leave_params_t;

/**
 * @brief The payload of EZB_ZDO_SIGNAL_LEAVE_INDICATION signal
 *
 */
typedef struct ezb_zdo_signal_leave_indication_params_s {
    ezb_shortaddr_t short_addr;         /*!< Short address of device requested to leave or leaving device*/
    ezb_extaddr_t  device_addr;         /*!< Long address of device requested to leave or leaving device*/
    ezb_zdo_leave_type_t leave_type;    /*!< Leave type, refer to ezb_zdo_leave_type_t*/
} ezb_zdo_signal_leave_indication_params_t;

/**
 * @brief The payload of EZB_ZDO_SIGNAL_DEVICE_ANNCE signal
 */
typedef struct ezb_zdo_signal_device_annce_params_s {
    ezb_shortaddr_t short_addr; /*!< address of device that recently joined to network */
    ezb_extaddr_t device_addr;  /*!< The 64-bit (IEEE) address assigned to the device. */
    uint8_t       capability;   /*!< The capability of the device. */
} ezb_zdo_signal_device_annce_params_t;

/**
 * @brief The payload of EZB_ZDO_SIGNAL_DEVICE_UPDATE signal
 */
typedef struct ezb_zdo_signal_device_update_params_s {
    ezb_extaddr_t device_addr;      /*!< Long Address of the updated device */
    ezb_shortaddr_t short_addr;     /*!< Short Address of the updated device */
    ezb_zdo_upddev_status_t status; /*!< Indicates the updated status of the device, refer to ezb_zdo_upddev_status_t */
    ezb_zdo_tc_action_t tc_action;  /*!< Trust center action,  refer to ezb_zdo_tc_action_t */
    ezb_shortaddr_t parent_short;   /*!< The short address of device's parent */
} ezb_zdo_signal_device_update_params_t;

/**
 * @brief The payload of EZB_ZDO_SIGNAL_DEVICE_AUTHORIZED signal
 */
typedef struct ezb_zdo_signal_device_authorized_params_s {
    ezb_extaddr_t device_addr;      /*!< Extended Address of the authorized device */
    ezb_shortaddr_t short_addr;     /*!< Short Address of the authorized device */
    ezb_zdo_auth_type_t type;       /*!< Authorization type, refer to ezb_zdo_auth_type_t */
    ezb_zdo_auth_status_t status;   /*!< Authorization status, refer to ezb_zdo_auth_status_t */
} ezb_zdo_signal_device_authorized_params_t;

/**
 * @brief The payload of EZB_ZDO_SIGNAL_DEVICE_UNAVAILABLE signal
 */
typedef struct ezb_zdo_signal_device_unavailable_params_s {
    ezb_extaddr_t device_addr;      /*!< Extended address of the unavailable device */
    ezb_shortaddr_t short_addr;     /*!< Short address of unavailable device */
} ezb_zdo_signal_device_unavailable_params_t;

/**
 * @brief The payload of BDB signals
 */
typedef struct ezb_bdb_signal_simple_params_s {
    uint8_t status;             /*!< Indicates the status of the simple signal, refer to ezb_bdb_status_t */
} ezb_bdb_signal_simple_params_t;

/**
 * @brief The payload of EZB_NWK_SIGNAL_PERMIT_JOIN_STATUS signal
 */
typedef struct ezb_nwk_signal_permit_join_status_params_s {
    uint8_t duration;             /*!< Duration of the permit joining state, in seconds */
} ezb_nwk_signal_permit_join_status_params_t;

/**
 * @brief The payload of EZB_NWK_SIGNAL_NETWORK_STATUS signal
 */
 typedef struct ezb_nwk_signal_network_status_params_s {
    uint8_t status;                 /*!< Error code associated with the failure, refer to ezb_nwk_network_status_t */
    ezb_shortaddr_t network_addr;   /*!< Network device address associated with the status information */
    uint8_t unknown_command_id;     /*!< Unknown command ID */
} ezb_nwk_signal_network_status_params_t;

/**
 * @brief The application signal struct for ezb_app_signal_handler
 * @anchor ezb_app_signal_t
 */
typedef void *ezb_app_signal_t;

/**
 * @brief The pointer to the application signal handler function
 * @anchor ezb_app_signal_handler_t
 *
 * @param[in] app_signal The pointer to the application signal, @ref ezb_app_signal_t
 *
 * @return true if the application signal is handled, false otherwise
 */
typedef bool (*ezb_app_signal_handler_t)(const ezb_app_signal_t *app_signal);

/**
 * @brief Obtains pointer to parameters passed with application signal.
 *
 * @param[in] signal The pointer to the application signal, @ref ezb_app_signal_t.
 *
 * @return The pointer to the parameter of the application signal
 */
const void *ezb_app_signal_get_params(const ezb_app_signal_t *signal);

/**
 * @brief Obtains the type of the application signal
 *
 * @param[in] signal The pointer to the application signal, @ref ezb_app_signal_t.
 *
 * @return The type of the application signal, @ref ezb_app_signal_type_t
 */
ezb_app_signal_type_t ezb_app_signal_get_type(const ezb_app_signal_t *signal);

/**
 * @brief Stringify the Zigbee Device Object signal
 *
 * @param[in] signal A @ref ezb_app_signal_type_t object that expect to stringified
 * @return A string pointer of ezb_app_signal_type_t
 */
const char *ezb_app_signal_to_string(ezb_app_signal_type_t signal);

/**
 * @brief Add an application signal handler.
 *
 * @param[in] handler The application signal handler, @ref ezb_app_signal_handler_t
 *
 * @return EZB_ERR_NONE on success, error code otherwise.
 */
ezb_err_t ezb_app_signal_add_handler(ezb_app_signal_handler_t handler);

/**
 * @brief Remove an application signal handler.
 *
 * @param[in] handler The application signal handler, @ref ezb_app_signal_handler_t
 */
void ezb_app_signal_remove_handler(ezb_app_signal_handler_t handler);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_APP_SIGNAL_H */
