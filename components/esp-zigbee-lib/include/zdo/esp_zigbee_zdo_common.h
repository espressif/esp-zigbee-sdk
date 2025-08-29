/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_type.h"

#ifdef CONFIG_ZB_GP_ENABLED
#include "zgp/esp_zigbee_zgp.h"
#endif /* CONFIG_ZB_GP_ENABLED */

/**
 * @brief ZDP status values
 * @anchor esp_zb_zdp_status
 * @note the status feedback for the zdo command
 */
typedef enum {
    ESP_ZB_ZDP_STATUS_SUCCESS               = 0x00,   /*!< The requested operation or transmission was completed successfully. */
    ESP_ZB_ZDP_STATUS_INV_REQUESTTYPE       = 0x80,   /*!< The supplied request type was invalid. */
    ESP_ZB_ZDP_STATUS_DEVICE_NOT_FOUND      = 0x81,   /*!< The requested device did not exist on a device following a child descriptor request to a parent.*/
    ESP_ZB_ZDP_STATUS_INVALID_EP            = 0x82,   /*!< The supplied endpoint was equal to 0x00 or between 0xf1 and 0xff. */
    ESP_ZB_ZDP_STATUS_NOT_ACTIVE            = 0x83,   /*!< The requested endpoint is not described by simple descriptor. */
    ESP_ZB_ZDP_STATUS_NOT_SUPPORTED         = 0x84,   /*!< The requested optional feature is not supported on the target device. */
    ESP_ZB_ZDP_STATUS_TIMEOUT               = 0x85,   /*!< A timeout has occurred with the requested operation. */
    ESP_ZB_ZDP_STATUS_NO_MATCH              = 0x86,   /*!< The end device bind request was unsuccessful due to a failure to match any suitable clusters.*/
    ESP_ZB_ZDP_STATUS_NO_ENTRY              = 0x88,   /*!< The unbind request was unsuccessful due to the coordinator or source device not having an entry in its binding table to unbind.*/
    ESP_ZB_ZDP_STATUS_NO_DESCRIPTOR         = 0x89,   /*!< A child descriptor was not available following a discovery request to a parent. */
    ESP_ZB_ZDP_STATUS_INSUFFICIENT_SPACE    = 0x8a,   /*!< The device does not have storage space to support the requested operation. */
    ESP_ZB_ZDP_STATUS_NOT_PERMITTED         = 0x8b,   /*!< The device is not in the proper state to support the requested operation. */
    ESP_ZB_ZDP_STATUS_TABLE_FULL            = 0x8c,   /*!< The device does not have table space to support the operation. */
    ESP_ZB_ZDP_STATUS_NOT_AUTHORIZED        = 0x8d,   /*!< The permissions configuration table on the target indicates that the request is not authorized from this device.*/
    ESP_ZB_ZDP_STATUS_BINDING_TABLE_FULL    = 0x8e,   /*!< The device doesn't have binding table space to support the operation */
    ESP_ZB_ZDP_STATUS_INVALID_INDEX         = 0x8f,   /*!< The index in the received command is out of bounds. */
} esp_zb_zdp_status_t;

/**
 * @brief signal passed to the esp_zb_application_signal_handler
 * @anchor esp_zb_app_signal_type_t
 */
typedef enum {
    /**
    * Overview:
    * - The device has started in non-BDB commissioning mode.
    *
    * When generated:
    * - After the device has started and completed non-BDB commissioning.
    * - In case of a commissioning error.
    *
    * Status code:
    * - ESP_OK: Device has started and joined the network.
    * - ESP_FAIL: Device startup failure.
    *
    * Payload:
    * - None.
    */
    ESP_ZB_ZDO_SIGNAL_DEFAULT_START                             = 0x00,

    /**
    * Overview:
    * - Stack framework (scheduler, buffer pool, NVRAM, etc.) startup complete,
    *   ready for initializing bdb commissioning.
    *
    * When generated:
    * - When the stack starts using the esp_zb_start(false) method.
    *
    * Status code:
    * - ESP_OK: Stack framework has been initialized.
    *
    * Payload:
    * - None.
    */
    ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP                              = 0x01,

    /**
    * Overview:
    * - Indicates that a Zigbee device has joined or rejoined the network.
    *
    * When generated:
    * - Upon receiving the device_annce command.
    *
    * Status code:
    * - ESP_OK: device_annce command was received.
    *
    * Payload:
    * - Refer to esp_zb_zdo_signal_device_annce_params_t
    */
    ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE                              = 0x02,

    /**
    * Overview:
    * - Indicates that the device itself has left the network.
    *
    * When generated:
    * - Upon receiving the Leave command.
    *
    * Status code:
    * - ESP_OK: Leave command was received.
    *
    * Payload:
    * - Refer to esp_zb_zdo_signal_leave_params_t
    */
    ESP_ZB_ZDO_SIGNAL_LEAVE                                     = 0x03,

    /**
    * Overview:
    * - Indicates corrupted or incorrect signal information.
    *
    * When generated:
    * - When incorrect signal information is detected.
    *
    * Status code:
    * - None
    *
    * Payload:
    * - None
    */
    ESP_ZB_ZDO_SIGNAL_ERROR                                     = 0x04,

    /**
    * Overview:
    * - Indicate the basic network information of factory new device has been initialized,
    *   ready for Zigbee commissioning
    *
    * When generated:
    * - Upon the basic device behavior has been initialization
    *
    * Status code:
    * - ESP_OK: Factory new device initialization complete
    * - ESP_FAIL: Factory new device commissioning failed
    *
    * Payload:
    * - None
    */
    ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START                        = 0x05,

    /**
    * Overview:
    * - Indicate device joins or rejoins network from the configured network information.
    *
    * When generated:
    * - Upon the device joining or rejoining Zigbee network using configuration network information.
    *
    * Status code:
    * - ESP_OK: Join or rejoin successfully
    * - ESP_FAIL: Join or rejoin failed
    *
    * Payload:
    * - None
    */
    ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT                             = 0x06,

    /**
    * Overview:
    * - Indicates that the Touchlink initiator has successfully started a network with the target and is ready
    *   for rejoining.
    *
    * When generated:
    * - Upon receiving the Network Start response during the Touchlink commissioning procedure.
    *
    * Status code:
    * - ESP_OK: The new network has been started successfully.
    *
    * Payload:
    * - Refer to esp_zb_bdb_signal_touchlink_nwk_started_params_t
    */
    ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED                     = 0x07,

    /**
    * Overview:
    * - Indicate Touchlink target has join the initiator network.
    *
    * When generated:
    * - Upon Touchlink initiator receives the Network Start response during the Touchlink commissioning procedure.
    *
    * Status code:
    * - ESP_OK: Touchlink target join successfully
    *
    * Payload:
    * - Refer to esp_zb_bdb_signal_touchlink_nwk_joined_router_t
    */
    ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_JOINED_ROUTER               = 0x08,

    /**
    * Overview:
    * - Indicates the result of the Touchlink initiator commissioning process.
    *
    * When generated:
    * - When the Touchlink initiator initiates network commission.
    *
    * Status code:
    * - ESP_OK: Commissioning successful.
    * - ESP_FAIL: No valid scan response received.
    *
    * Payload:
    * - None
    */
    ESP_ZB_BDB_SIGNAL_TOUCHLINK                                 = 0x09,

    /**
    * Overview:
    * - Indicates the completion of BDB network steering.
    *
    * When generated:
    * - When the device initiates the network steering commissioning process.
    *
    * Status code:
    * - ESP_OK: Network steering completed successfully.
    * - ESP_FAIL: Network steering failed or was canceled.
    *
    * Payload:
    * - None
    */
    ESP_ZB_BDB_SIGNAL_STEERING                                  = 0x0a,

    /**
    * Overview:
    * - Indicates the completion of BDB network formation.
    *
    * When generated:
    * - When the device initiates the network formation commissioning process.
    *
    * Status code:
    * - ESP_OK: Network formation completed successfully.
    * - ESP_FAIL: Network formation failed or was canceled.
    *
    * Payload:
    * - None
    */
    ESP_ZB_BDB_SIGNAL_FORMATION                                 = 0x0b,

    /**
    * Overview:
    * - Indicates the completion of BDB finding and binding (F&B) for a target endpoint.
    *
    * When generated:
    * - When F&B target timeout.
    *
    * Status code:
    * - ESP_OK: F&B target identifying time is expired.
    * - ESP_FAIL: F&B target identifying is cancelled.
    *
    * Payload:
    * - None
    */
    ESP_ZB_BDB_SIGNAL_FINDING_AND_BINDING_TARGET_FINISHED       = 0x0c,

    /**
    * Overview:
    * - Indicates the BDB F&B with a Target succeeded or F&B initiator timeout expired or cancelled.
    *
    * When generated:
    * - When F&B target timeout.
    *
    * Status code:
    * - ESP_OK: On success.
    * - ESP_FAIL: Expired or cancelled.
    *
    * Payload:
    * - None
    */
    ESP_ZB_BDB_SIGNAL_FINDING_AND_BINDING_INITIATOR_FINISHED    = 0x0d,

    /**
    * Overview:
    * - Indicates that the Touchlink target is preparing to commission with the initiator.
    *
    * When generated:
    * - When the Touchlink procedure starts on the target device.
    *
    * Status code:
    * - ESP_OK: Waiting for the commissioning procedure to proceed.
    * - ESP_FAIL: Touchlink procedure failed or was canceled.
    *
    * Payload:
    * - None
    */
    ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET                          = 0x0e,

    /**
    * Overview:
    * - Indicates that the Touchlink target network has started.
    *
    * When generated:
    * - When the Touchlink target starts the network upon receiving a start_network, join_router, or join_ed request.
    *
    * Status code:
    * - ESP_OK: Network started successfully.
    * - ESP_FAIL: Network start failed or was canceled.
    *
    * Payload:
    * - None
    */
    ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK                             = 0x0f,

    /**
    * Overview:
    * - Indicates that the Touchlink target commissioning procedure has finished.
    *
    * When generated:
    * - When the Touchlink target times out or completes the commissioning procedure.
    *
    * Status code:
    * - ESP_OK: Commissioning procedure completed successfully.
    *
    * Payload:
    * - None
    */
    ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET_FINISHED                 = 0x10,

    /* Reserve: 0x11 */

    /**
    * Overview:
    * - Indicates that a new device has initiated an association procedure.
    *
    * When generated:
    * - When a new device is associated.
    *
    * Status code:
    * - ESP_OK: The new device was successfully associated.
    *
    * Payload:
    * - Refer to esp_zb_nwk_signal_device_associated_params_t
    */
    ESP_ZB_NWK_SIGNAL_DEVICE_ASSOCIATED                         = 0x12,

    /**
    * Overview:
    * - Indicates that a child device has left the network.
    *
    * When generated:
    * - When the leave command is received from the child device.
    *
    * Status code:
    * - ESP_OK: The child device left the network successfully.
    *
    * Payload:
    * - Refer to esp_zb_zdo_signal_leave_indication_params_t
    */
    ESP_ZB_ZDO_SIGNAL_LEAVE_INDICATION                          = 0x13,

    /* Reserve: 0x14 */

    /**
    * Overview:
    * - Indicates the GPCB (Green Power Combo Basic) commissioning signal.
    *
    * When generated:
    * - When a device is commissioned or decommissioned by the GPCB.
    *
    * Status code:
    * - ESP_OK: Commissioning or decommissioning completed successfully.
    *
    * Payload:
    * - Refer to esp_zb_zgp_signal_commissioning_params_t
    */

    ESP_ZB_ZGP_SIGNAL_COMMISSIONING                             = 0x15,

    /**
    * Overview:
    * - Indicates the device can enter sleep mode.
    *
    * When generated:
    * - When the stack determines that the device is eligible to enter sleep mode.
    *
    * Status code:
    * - ESP_OK: The device can enter sleep mode.
    *
    * Payload:
    * - Refer to esp_zb_zdo_signal_can_sleep_params_t
    */
    ESP_ZB_COMMON_SIGNAL_CAN_SLEEP                              = 0x16,

    /**
    * Overview:
    * - Indicates whether a specific part of the production configuration was found.
    *
    * When generated:
    * - After restoring the production configuration.
    *
    * Status code:
    * - ESP_OK: Production configuration successfully loaded from storage.
    * - ESP_FAIL: No production configuration found in storage.
    *
    * Payload:
    * - None
    */
    ESP_ZB_ZDO_SIGNAL_PRODUCTION_CONFIG_READY                   = 0x17,

    /**
    * Overview:
    * - Indicates that the Neighbor Table has expired, and no active route links remain.
    *
    * When generated:
    * - When all routes have expired.
    *
    * Status code:
    * - ESP_OK: All routers have expired.
    *
    * Payload:
    * - None
    */
    ESP_ZB_NWK_SIGNAL_NO_ACTIVE_LINKS_LEFT                      = 0x18,

    /* Reserve: 0x19 - 0x2e */

    /**
    * Overview:
    * - Indicates that a new device has been authorized by the Trust Center in the network.
    *
    * When generated:
    *  - Upon successful authorization.
    *  - Upon authorization failure.
    *  - Upon authorization timeout.
    *
    * Status code:
    * - ESP_OK: New device is authorized.
    *
    * Payload:
    * - Refer to esp_zb_zdo_signal_device_authorized_params_t
    */
    ESP_ZB_ZDO_SIGNAL_DEVICE_AUTHORIZED                         = 0x2f,

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
    * Status code:
    * - ESP_OK: New device information updated.
    *
    * Payload:
    * - Refer to esp_zb_zdo_signal_device_update_params_t
    */
    ESP_ZB_ZDO_SIGNAL_DEVICE_UPDATE                             = 0x30,

    /**
    * Overview:
    * - Detects a PAN ID conflict and inquires for a resolution.
    *
    * When generated:
    *  - Upon detecting a PAN ID conflict.
    *
    * Status code:
    * - ESP_OK: On success.
    *
    * Payload:
    * - None
    */
    ESP_ZB_NWK_SIGNAL_PANID_CONFLICT_DETECTED                   = 0x31,

    /**
    * Overview:
    * - Indicates that a network failure has been detected.
    *
    * When generated:
    * - Triggered when the network encounters a failure and the application can implement
    *   error handling based on the reported status.
    *
    * Status code:
    * - ESP_OK: On success.
    *
    * Payload:
    * - Refer to esp_zb_zdo_signal_nwk_status_indication_params_t
    */
    ESP_ZB_NLME_STATUS_INDICATION                               = 0x32,

    /* Reserve: 0x33 - 0x34 */

    /**
    * Overview:
    * - Indicates that the Trust Center rejoin procedure has been completed.
    *
    * When generated:
    *  - Upon successful completion of the TC rejoin procedure by the device.
    *
    * Status code:
    * - ESP_OK: TC rejoin completed successfully.
    * - ESP_FAIL: Rejoin failed.
    *
    * Payload:
    * - None
    */

    ESP_ZB_BDB_SIGNAL_TC_REJOIN_DONE                            = 0x35,

    /**
    * Overview:
    * - Indicates the status of the network (open or closed).
    *
    * When generated:
    *  - When the network is opened.
    *  - When the network is closed.
    *
    * Status code:
    * - ESP_OK: On successful operation.
    *
    * Payload:
    * - Pointer to uint8_t, indicating the network status (open or closed).
    */
    ESP_ZB_NWK_SIGNAL_PERMIT_JOIN_STATUS                        = 0x36,

    /**
    * Overview:
    * - Indicates the result of cancelling BDB steering.
    *
    * When generated:
    *  - When `esp_zb_bdb_cancel_steering()` is processed.
    *
    * Status code:
    * - ESP_OK: Steering is cancelled successfully.
    * - ESP_ERR_INVALID_STATE: Steering is not in progress.
    * - ESP_FAIL: Failed to cancel steering.
    *
    * Payload:
    * - None
    */
    ESP_ZB_BDB_SIGNAL_STEERING_CANCELLED                        = 0x37,

    /**
    * Overview:
    * - Notifies the result of cancelling BDB formation.
    *
    * When generated:
    *  - When `esp_zb_bdb_cancel_formation()` is processed.
    *
    * Status code:
    * - ESP_OK: Formation is cancelled successfully.
    * - ESP_ERR_INVALID_STATE: Formation is not in progress.
    * - ESP_FAIL: Failed to cancel formation.
    *
    * Payload:
    * - None
    */
    ESP_ZB_BDB_SIGNAL_FORMATION_CANCELLED                       = 0x38,

    /* Reserve: 0x39 - 0x3a */

    /**
    * Overview:
    * - Indicates a ZGP mode change.
    *
    * When generated:
    *  - When a GPCB Sink changes mode between operational mode and commissioning mode.
    *
    * Status code:
    * - ESP_OK: On success.
    *
    * Payload:
    * - None
    */
    ESP_ZB_ZGP_SIGNAL_MODE_CHANGE                               = 0x3b,

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
    * Status code:
    * - ESP_OK: On success.
    *
    * Payload:
    * - Refer to esp_zb_zdo_device_unavailable_params_t
    */
    ESP_ZB_ZDO_DEVICE_UNAVAILABLE                               = 0x3c,

    /**
    * Overview:
    * - ZGP Approve Commissioning.
    *
    * When generated:
    *  - When the ZGP subsystem is ready to create a new pairing, but the APP should check
    *    if the GPD application functionality matches to continue the pairing.
    *
    * Status code:
    * - ESP_OK: On success.
    *
    * Payload:
    * - Refer to esp_zb_zgp_signal_approve_comm_params_t
    */
    ESP_ZB_ZGP_SIGNAL_APPROVE_COMMISSIONING                     = 0x3d,
    ESP_ZB_SIGNAL_END                                           = 0x3e,
} esp_zb_app_signal_type_t;

/**
 * @brief The struct of esp zboss app signal message table
 * @anchor esp_zb_app_signal_msg_t
 */
typedef struct {
    esp_zb_app_signal_type_t signal;        /*!< The signal type of Zigbee */
    const char *msg;                        /*!< The string of Zigbee signal */
} esp_zb_app_signal_msg_t;

/**
 * @brief The enum of bind request destination address mode
 * @anchor esp_zb_zdo_bind_dst_addr_mode_t
 */
typedef enum {
    ESP_ZB_ZDO_BIND_DST_ADDR_MODE_16_BIT_GROUP                  = 0x01U,
    ESP_ZB_ZDO_BIND_DST_ADDR_MODE_64_BIT_EXTENDED               = 0x03U,
} esp_zb_zdo_bind_dst_addr_mode_t;

/* zdo param define */
/**
 * @name Leave types
 * @anchor nwk_leave_type
 */
typedef enum {
    ESP_ZB_NWK_LEAVE_TYPE_RESET                 = 0x00, /*!< Leave without rejoin */
    ESP_ZB_NWK_LEAVE_TYPE_REJOIN                = 0x01  /*!< Leave with rejoin */
} esp_zb_nwk_leave_type_t;

/**
 * @brief TC action on incoming update device
 */
typedef enum {
    ESP_ZB_ZDO_TC_ACTION_AUTHORIZE  = 0x00U,    /*!< Authorize device */
    ESP_ZB_ZDO_TC_ACTION_DENY       = 0x01U,    /*!< deny authorization, remove it */
    ESP_ZB_ZDO_TC_ACTION_IGNORE     = 0x02U     /*!< ignore Update Device */
} esp_zb_zdo_update_dev_tc_action_t;

/**
 * @brief ZDO update device status
 */
typedef enum {
    ESP_ZB_ZDO_STANDARD_DEV_SECURED_REJOIN  = 0x00U,    /*!< Standard device secured rejoin */
    ESP_ZB_ZDO_STANDARD_DEV_UNSECURED_JOIN  = 0x01U,    /*!< Standard device unsecured join */
    ESP_ZB_ZDO_STANDARD_DEV_LEFT            = 0x02U,    /*!< Standard device left */
    ESP_ZB_ZDO_STANDARD_DEV_TC_REJOIN       = 0x03U,    /*!< Standard device trust center rejoin */
    /* 0x04 – 0x07 = Reserved */
} esp_zb_zdo_update_dev_status_t;

/**
 * @brief The payload of ESP_ZB_ZDO_SIGNAL_LEAVE signal
 *
 */
typedef struct esp_zb_zdo_signal_leave_params_s {
    uint8_t leave_type;             /*!< Leave type, refer to esp_zb_nwk_leave_type_t */
} esp_zb_zdo_signal_leave_params_t;

/**
 * @brief The payload of ESP_ZB_ZDO_SIGNAL_LEAVE_INDICATION signal
 *
 */
typedef struct esp_zb_zdo_signal_leave_indication_params_s {
    uint16_t short_addr;                    /*!< Short address of device requested to leave or leaving device*/
    esp_zb_ieee_addr_t device_addr;         /*!< Long address of device requested to leave or leaving device*/
    uint8_t rejoin;                         /*!< 1 if this was leave with rejoin; 0 - otherwise */
} esp_zb_zdo_signal_leave_indication_params_t;

/**
 * @brief The payload of ESP_ZB_COMMON_SIGNAL_CAN_SLEEP signal
 *
 */
typedef struct esp_zb_zdo_signal_can_sleep_params_s {
    uint32_t sleep_duration; /*!< sleep duration in milliseconds */
} esp_zb_zdo_signal_can_sleep_params_t;

/**
 * @brief The payload of ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE signal
 *
 * @note Stack passes this parameter to application when some device joins/rejoins to network.
 */
typedef struct esp_zb_zdo_signal_device_annce_params_s {
    uint16_t device_short_addr;           /*!< address of device that recently joined to network */
    esp_zb_ieee_addr_t   ieee_addr;       /*!< The 64-bit (IEEE) address assigned to the device. */
    uint8_t       capability;             /*!< The capability of the device. */
} esp_zb_zdo_signal_device_annce_params_t;

/**
 * @@brief The payload of ESP_ZB_ZDO_SIGNAL_DEVICE_UPDATE signal
 */
typedef struct esp_zb_zdo_signal_device_update_params_s {
    esp_zb_ieee_addr_t long_addr;   /*!< Long Address of the updated device */
    uint16_t short_addr;            /*!< Short Address of the updated device */
    uint8_t status;                 /*!< Indicates the updated status of the device, refer to esp_zb_zdo_update_dev_status_t */
    uint8_t tc_action;              /*!< Trust center action,  refer to esp_zb_zdo_update_dev_tc_action_t */
    uint16_t parent_short;          /*!< The short address of device's parent */
} esp_zb_zdo_signal_device_update_params_t;

/**
 * @brief The payload of ESP_ZB_ZDO_SIGNAL_DEVICE_AUTHORIZED signal
 * @note The authorization_type as following:
 *          0x00 = Authorization type for legacy devices ( < r21)
 *              Status:
 *                  0x00: Authorization success
 *                  0x01: Authorization failed
 *          0x01 = Authorization type for r21 device through TCLK
 *              Status:
 *                  0x00: Authorization success
 *                  0x01: Authorization timeout
 *                  0x02: Authorization failed
 *          0x02 = Authorization type for SE through CBKE
 *              Status:
 *                  0x00: Authorization success
 */
typedef struct esp_zb_zdo_signal_device_authorized_params_s {
    esp_zb_ieee_addr_t long_addr; /*!< Long Address of the updated device */
    uint16_t short_addr;          /*!< Short Address of the updated device */
    uint8_t authorization_type;   /*!< Type of the authorization procedure */
    uint8_t authorization_status; /*!< Status of the authorization procedure which depends on authorization_type */
} esp_zb_zdo_signal_device_authorized_params_t;

/**
 * @brief The payload of ESP_ZB_ZDO_DEVICE_UNAVAILABLE signal
 *
 */
typedef struct esp_zb_zdo_device_unavailable_params_s {
    esp_zb_ieee_addr_t long_addr; /*!< Long address of the unavailable device */
    uint16_t short_addr;          /*!< Short address of unavailable device */
} esp_zb_zdo_device_unavailable_params_t;

#ifdef CONFIG_ZB_GP_ENABLED
/**
 * @brief ZGP approve commissioning parameters
 *
 */
typedef struct esp_zgp_approve_comm_params_s {
    esp_zb_zgpd_id_t              zgpd_id;                                /*!< ZGPD ID */
    uint8_t                       device_id;                              /*!< ZGPD device ID */
    uint16_t                      manuf_id;                               /*!< Manufacturer ID (meaningful if device_id = 0xFE or 0xFF) */
    uint16_t                      manuf_model_id;                         /*!< Manufacturer model ID (meaningful if device_id = 0xFE or 0xFF) */
    esp_zb_ieee_addr_t            ieee_addr;                              /*!< ZGPD long IEEE address if available, otherwise filled with zeroes */
    uint8_t                       pairing_endpoint;                       /*!< Device endpoint, on which commissioning is currently active */
    esp_zb_zgp_gpd_cmds_list_t    gpd_cmds_list;                          /*!< ZGPD Command list */
    esp_zb_zgp_cluster_list_t     cluster_list;                           /*!< ZGPD Cluster list */
    uint8_t                       num_of_reports;                         /*!< total number of different report descriptors that GPD sent during the commissioning process */
    esp_zb_zgp_raw_report_desc_t  reports[ZB_ZGP_APP_DESCR_REPORTS_NUM];  /*!< array of reports*/
    bool                          pairing_configuration;                  /*!< It is ZB_TRUE in case this approve signal was triggered by GP Pairing Configuration command */
    uint8_t                       actions;                                /*!< Pairing configuration actions */
    uint8_t                       num_of_endpoints;                       /*!< Pairing configuration number of paired endpoints field
                                                                            - 0x00 and 0xfd: there are no paired endpoints
                                                                            - 0xff: all matching endpoints are to be paired
                                                                            - 0xfe: paired endpoints are to be derived by the sink itself
                                                                            - other values: paired_endpoints field is present and contains the list of local endpoints paired to this GPD
                                                                            **/
    uint8_t              paired_endpoints[ZB_ZGP_MAX_PAIRED_ENDPOINTS];   /*!< Paired endpoint numbers */
} esp_zgp_approve_comm_params_t;

/**
 * @brief The payload of ESP_ZB_ZGP_SIGNAL_APPROVE_COMMISSIONING signal
 *
 */
typedef struct esp_zb_zgp_signal_approve_comm_params_s {
    esp_zgp_approve_comm_params_t *param;  /*!< Parameter for approving commissioning */
} esp_zb_zgp_signal_approve_comm_params_t;

/**
 *  @brief The payload of ESP_ZB_ZGP_SIGNAL_MODE_CHANGE signal
 *
 *  Stack passes this parameter to application to notify about GP mode change.
 */
typedef struct esp_zb_zgp_signal_mode_change_params_s {
    esp_zb_zgp_mode_change_reason_t reason; /*!< Reason for mode change, refer to esp_zb_zgp_mode_change_reason_t */
    esp_zb_zgp_mode_t new_mode;             /*!< New mode */
} esp_zb_zgp_signal_mode_change_params_t;

/**
 * @brief The payload of ESP_ZB_ZGP_SIGNAL_COMMISSIONING signal
 *
 */
typedef struct esp_zb_zgp_signal_commissioning_params_s {
    esp_zb_zgpd_id_t zgpd_id;         /*!< Pointer to GPD ID */
    esp_zb_zgp_comm_status_t result;  /*!< commissioning result, refer to esp_zb_zgp_comm_status_t */
} esp_zb_zgp_signal_commissioning_params_t;
#endif /* CONFIG_ZB_GP_ENABLED */

/**
 * @brief The payload of ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED signal
 *
 */
typedef struct esp_zb_bdb_signal_touchlink_nwk_started_params_s {
    esp_zb_ieee_addr_t device_ieee_addr;    /*!< The ieee address of touchlink target */
    uint8_t endpoint;                       /*!< The endpoint id on the touchlink target */
    uint16_t profile_id;                    /*!< The profile id of touchlink profile */
} esp_zb_bdb_signal_touchlink_nwk_started_params_t;

/**
 * @brief The payload of ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_JOINED_ROUTER signal
 *
 */
typedef esp_zb_bdb_signal_touchlink_nwk_started_params_t esp_zb_bdb_signal_touchlink_nwk_joined_router_t;

/**
 * @brief The payload of ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_JOINED_ED signal
 *
 */
typedef esp_zb_bdb_signal_touchlink_nwk_started_params_t esp_zb_bdb_signal_touchlink_nwk_joined_ed_t;

/**
 * @brief The payload of ESP_ZB_NLME_STATUS_INDICATION signal
 *
 */
typedef struct esp_zb_zdo_signal_nwk_status_indication_params_s {
    uint8_t status;               /*!< Error code associated with the failure, refer to esp_zb_nwk_command_status_t */
    uint16_t network_addr;        /*!< Network device address associated with the status information */
    uint8_t unknown_command_id;   /*!< Unknown command ID */
} ESP_ZB_PACKED_STRUCT esp_zb_zdo_signal_nwk_status_indication_params_t;

/**
 * @brief The payload of ESP_ZB_NWK_SIGNAL_DEVICE_ASSOCIATED signal
 *
 */
typedef struct esp_zb_nwk_signal_device_associated_params_s {
    esp_zb_ieee_addr_t device_addr; /*!< address of associated device */
} esp_zb_nwk_signal_device_associated_params_t;

#ifdef __cplusplus
}
#endif
