/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_type.h"

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
    ESP_ZB_ZDP_STATUS_INVALID_INDEX         = 0x8f,   /*!< The index in the received command is out of bounds. */
} esp_zb_zdp_status_t;

/**
 * @brief signal passed to the esp_zb_application_signal_handler
 * @anchor esp_zb_app_signal_type_t
 * @note It indicates current BDB, NWK or ZDO signal is finished
 */
typedef enum {
    ESP_ZB_ZDO_SIGNAL_DEFAULT_START                 = 0,
    ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP                  = 1,
    ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE                  = 2,
    ESP_ZB_ZDO_SIGNAL_LEAVE                         = 3,
    ESP_ZB_ZDO_SIGNAL_ERROR                         = 4,
    ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START            = 5,
    ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT                 = 6,
    ESP_ZB_BDB_SIGNAL_STEERING                      = 10,
    ESP_ZB_BDB_SIGNAL_FORMATION                     = 11,
    ESP_ZB_NWK_SIGNAL_DEVICE_ASSOCIATED             = 18,
    ESP_ZB_ZDO_SIGNAL_LEAVE_INDICATION              = 19,
    ESP_ZB_COMMON_SIGNAL_CAN_SLEEP                  = 22,
    ESP_ZB_ZDO_SIGNAL_PRODUCTION_CONFIG_READY       = 23,
    ESP_ZB_MACSPLIT_DEVICE_BOOT                     = 43,
    ESP_ZB_MACSPLIT_DEVICE_READY_FOR_UPGRADE        = 44,
    ESP_ZB_MACSPLIT_DEVICE_FW_UPGRADE_EVENT         = 45,
    ESP_ZB_ZDO_SIGNAL_DEVICE_AUTHORIZED             = 47,
    ESP_ZB_ZDO_SIGNAL_DEVICE_UPDATE                 = 48,
    ESP_ZB_NWK_SIGNAL_PANID_CONFLICT_DETECTED       = 49,
    ESP_ZB_NLME_STATUS_INDICATION                   = 50,
    ESP_ZB_NWK_SIGNAL_PERMIT_JOIN_STATUS            = 54,
    ESP_ZB_BDB_SIGNAL_STEERING_CANCELLED            = 55,
    ESP_ZB_BDB_SIGNAL_FORMATION_CANCELLED           = 56,
} esp_zb_app_signal_type_t;

/**
 * @brief The enum of mode of Base Device Behavior (BDB)
 * @anchor esp_zb_bdb_commissioning_mode
 */
typedef enum {
    ESP_ZB_BDB_MODE_INITIALIZATION                  = 0,
    ESP_ZB_BDB_MODE_NETWORK_STEERING                = 2,
    ESP_ZB_BDB_MODE_NETWORK_FORMATION               = 4,
} esp_zb_bdb_commissioning_mode_t;


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
 * @brief Leave parameters
 *
 * @note Stack passes this parameter to application when device leave the network.
 */
typedef struct esp_zb_zdo_signal_leave_params_s {
    esp_zb_nwk_leave_type_t leave_type; /*!< Leave type. @ref nwk_leave_type */
} esp_zb_zdo_signal_leave_params_t;

/**
 * @brief Leave Indication parameters
 *
 * @note Stack passes this parameter to application upon receipt of leave indication primitive.
 */
typedef struct esp_zb_zdo_signal_leave_indication_params_s {
    esp_zb_ieee_addr_t device_addr;       /*!< Long address of device requested to leave or leaving device*/
    uint8_t rejoin;                       /*!< 1 if this was leave with rejoin; 0 - otherwise */
} esp_zb_zdo_signal_leave_indication_params_t;

/**
 * @brief Association parameters
 *
 * @note Stack passes this parameter to application when some device joins/rejoins to network.
 */
typedef struct esp_zb_zdo_signal_device_annce_params_s {
    uint16_t device_short_addr;           /*!< address of device that recently joined to network */
    esp_zb_ieee_addr_t   ieee_addr;       /*!< The 64-bit (IEEE) address assigned to the device. */
    uint8_t       capability;             /*!< The capability of the device. */
} esp_zb_zdo_signal_device_annce_params_t;

/**
 * @brief Macsplit device boot parameters.
 *
 * @note Macsplit passes this parameter to application when device is booted.
 */
typedef struct esp_zb_zdo_signal_macsplit_dev_boot_params_s {
    uint32_t    dev_version;              /*!< macsplit device version */
    esp_zb_ieee_addr_t extended_address;  /*!< The 64-bit (IEEE) address assigned to the device. */
    char      version_str[80];            /*!< macsplit version string */
} esp_zb_zdo_signal_macsplit_dev_boot_params_t;

/**
 * @brief Device Updated signal parameters
 * @note  status of the device update
            0x00 = Standard device secured rejoin
            0x01 = Standard device unsecured join
            0x02 = Device left
            0x03 = Standard device trust center rejoin
            0x04 – 0x07 = Reserved
 */
typedef struct esp_zb_zdo_signal_device_update_params_s {
    esp_zb_ieee_addr_t long_addr;   /*!< Long Address of the updated device */
    uint16_t short_addr;            /*!< Short Address of the updated device */
    uint8_t status;                 /*!< Indicates the updated status of the device */
} esp_zb_zdo_signal_device_update_params_t;

#ifdef __cplusplus
}
#endif
