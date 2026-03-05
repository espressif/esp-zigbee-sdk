/*
 * SPDX-FileCopyrightText: 2022-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/app_signals.h" instead!"

#include <ezbee/app_signals.h>
#include <ezbee/zdo/zdo_type.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ZB_ZDP_STATUS_SUCCESS               EZB_ZDP_STATUS_SUCCESS
#define ESP_ZB_ZDP_STATUS_INV_REQUESTTYPE       EZB_ZDP_STATUS_INV_REQUESTTYPE
#define ESP_ZB_ZDP_STATUS_DEVICE_NOT_FOUND      EZB_ZDP_STATUS_DEVICE_NOT_FOUND
#define ESP_ZB_ZDP_STATUS_INVALID_EP            EZB_ZDP_STATUS_INVALID_EP
#define ESP_ZB_ZDP_STATUS_NOT_ACTIVE            EZB_ZDP_STATUS_NOT_ACTIVE
#define ESP_ZB_ZDP_STATUS_NOT_SUPPORTED         EZB_ZDP_STATUS_NOT_SUPPORTED
#define ESP_ZB_ZDP_STATUS_TIMEOUT               EZB_ZDP_STATUS_TIMEOUT
#define ESP_ZB_ZDP_STATUS_NO_MATCH              EZB_ZDP_STATUS_NO_MATCH
#define ESP_ZB_ZDP_STATUS_NO_ENTRY              EZB_ZDP_STATUS_NO_ENTRY
#define ESP_ZB_ZDP_STATUS_NO_DESCRIPTOR         EZB_ZDP_STATUS_NO_DESCRIPTOR
#define ESP_ZB_ZDP_STATUS_INSUFFICIENT_SPACE    EZB_ZDP_STATUS_INSUFFICIENT_SPACE
#define ESP_ZB_ZDP_STATUS_NOT_PERMITTED         EZB_ZDP_STATUS_NOT_PERMITTED
#define ESP_ZB_ZDP_STATUS_TABLE_FULL            EZB_ZDP_STATUS_TABLE_FULL
#define ESP_ZB_ZDP_STATUS_NOT_AUTHORIZED        EZB_ZDP_STATUS_NOT_AUTHORIZED
#define ESP_ZB_ZDP_STATUS_BINDING_TABLE_FULL    EZB_ZDP_STATUS_BINDING_TABLE_FULL
#define ESP_ZB_ZDP_STATUS_INVALID_INDEX         EZB_ZDP_STATUS_INVALID_INDEX
typedef ezb_zdp_status_t esp_zb_zdp_status_t;

#define ESP_ZB_ZDO_SIGNAL_DEFAULT_START                          EZB_ZDO_SIGNAL_DEFAULT_START
#define ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP                           EZB_ZDO_SIGNAL_SKIP_STARTUP
#define ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE                           EZB_ZDO_SIGNAL_DEVICE_ANNCE
#define ESP_ZB_ZDO_SIGNAL_LEAVE                                  EZB_ZDO_SIGNAL_LEAVE
#define ESP_ZB_ZDO_SIGNAL_ERROR                                  EZB_ZDO_SIGNAL_ERROR
#define ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START                     EZB_BDB_SIGNAL_DEVICE_FIRST_START
#define ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT                          EZB_BDB_SIGNAL_DEVICE_REBOOT
#define ESP_ZB_BDB_SIGNAL_TOUCHLINK                              EZB_BDB_SIGNAL_TOUCHLINK_INITIATOR_FINISHED
#define ESP_ZB_BDB_SIGNAL_STEERING                               EZB_BDB_SIGNAL_STEERING
#define ESP_ZB_BDB_SIGNAL_FORMATION                              EZB_BDB_SIGNAL_FORMATION
#define ESP_ZB_BDB_SIGNAL_FINDING_AND_BINDING_TARGET_FINISHED    EZB_BDB_SIGNAL_FINDING_AND_BINDING_TARGET_FINISHED
#define ESP_ZB_BDB_SIGNAL_FINDING_AND_BINDING_INITIATOR_FINISHED EZB_BDB_SIGNAL_FINDING_AND_BINDING_INITIATOR_FINISHED
#define ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET_FINISHED              EZB_BDB_SIGNAL_TOUCHLINK_TARGET_FINISHED
#define ESP_ZB_NWK_SIGNAL_DEVICE_ASSOCIATED                      EZB_NWK_SIGNAL_DEVICE_ASSOCIATED
#define ESP_ZB_ZDO_SIGNAL_LEAVE_INDICATION                       EZB_ZDO_SIGNAL_LEAVE_INDICATION
#define ESP_ZB_NWK_SIGNAL_NO_ACTIVE_LINKS_LEFT                   EZB_NWK_SIGNAL_NO_ACTIVE_LINKS_LEFT
#define ESP_ZB_ZDO_SIGNAL_DEVICE_AUTHORIZED                      EZB_ZDO_SIGNAL_DEVICE_AUTHORIZED
#define ESP_ZB_ZDO_SIGNAL_DEVICE_UPDATE                          EZB_ZDO_SIGNAL_DEVICE_UPDATE
#define ESP_ZB_NWK_SIGNAL_PANID_CONFLICT_DETECTED                EZB_NWK_SIGNAL_PANID_CONFLICT_DETECTED
#define ESP_ZB_NLME_STATUS_INDICATION                            EZB_NWK_SIGNAL_NETWORK_STATUS
#define ESP_ZB_NWK_SIGNAL_PERMIT_JOIN_STATUS                     EZB_NWK_SIGNAL_PERMIT_JOIN_STATUS
#define ESP_ZB_ZDO_DEVICE_UNAVAILABLE                            EZB_ZDO_SIGNAL_DEVICE_UNAVAILABLE
enum {
    ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED = EZB_APP_SIGNAL_END + 1,
    ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_JOINED_ROUTER,
    ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET,
    ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK,
    ESP_ZB_ZGP_SIGNAL_COMMISSIONING,
    ESP_ZB_COMMON_SIGNAL_CAN_SLEEP,
    ESP_ZB_ZDO_SIGNAL_PRODUCTION_CONFIG_READY,
    ESP_ZB_BDB_SIGNAL_TC_REJOIN_DONE,
    ESP_ZB_BDB_SIGNAL_STEERING_CANCELLED,
    ESP_ZB_BDB_SIGNAL_FORMATION_CANCELLED,
    ESP_ZB_ZGP_SIGNAL_MODE_CHANGE,
    ESP_ZB_ZGP_SIGNAL_APPROVE_COMMISSIONING,
    ESP_ZB_SIGNAL_END,
};
typedef ezb_app_signal_type_t esp_zb_app_signal_type_t;

#define ESP_ZB_NWK_LEAVE_TYPE_RESET  EZB_ZDO_LEAVE_TYPE_RESET
#define ESP_ZB_NWK_LEAVE_TYPE_REJOIN EZB_ZDO_LEAVE_TYPE_REJOIN
typedef ezb_zdo_leave_type_t esp_zb_nwk_leave_type_t;

#define ESP_ZB_ZDO_TC_ACTION_AUTHORIZE EZB_ZDO_TC_ACTION_ACCEPT
#define ESP_ZB_ZDO_TC_ACTION_DENY      EZB_ZDO_TC_ACTION_DENY
#define ESP_ZB_ZDO_TC_ACTION_IGNORE    EZB_ZDO_TC_ACTION_IGNORE
typedef ezb_zdo_tc_action_t esp_zb_zdo_update_dev_tc_action_t;

#define ESP_ZB_ZDO_STANDARD_DEV_SECURED_REJOIN EZB_ZDO_UPDDEV_SECURE_REJOIN
#define ESP_ZB_ZDO_STANDARD_DEV_UNSECURE_JOIN  EZB_ZDO_UPDDEV_UNSECURE_JOIN
#define ESP_ZB_ZDO_STANDARD_DEV_DEVICE_LEFT    EZB_ZDO_UPDDEV_DEVICE_LEFT
#define ESP_ZB_ZDO_STANDARD_DEV_TC_REJOIN      EZB_ZDO_UPDDEV_TC_REJOIN
typedef ezb_zdo_upddev_status_t esp_zb_zdo_update_dev_status_t;

typedef struct esp_zb_zdo_signal_device_annce_params_s {
    uint16_t           device_short_addr;   /*!< address of device that recently joined to network */
    esp_zb_ieee_addr_t ieee_addr;           /*!< The 64-bit (IEEE) address assigned to the device. */
    uint8_t            capability;          /*!< The capability of the device. */
} esp_zb_zdo_signal_device_annce_params_t;

typedef struct esp_zb_zdo_signal_leave_params_s {
    esp_zb_nwk_leave_type_t leave_type;     /*!< Leave type, refer to esp_zb_nwk_leave_type_t */
} esp_zb_zdo_signal_leave_params_t;

typedef struct esp_zb_zdo_signal_leave_indication_params_s {
    uint16_t           short_addr;  /*!< Short address of device requested to leave or leaving device*/
    esp_zb_ieee_addr_t device_addr; /*!< Long address of device requested to leave or leaving device*/
    esp_zb_nwk_leave_type_t rejoin; /*!< 1 if this was leave with rejoin; 0 - otherwise */
} esp_zb_zdo_signal_leave_indication_params_t;

typedef struct esp_zb_bdb_signal_touchlink_nwk_params_s {
    esp_zb_ieee_addr_t device_ieee_addr; /*!< address of device that started the network */
    uint8_t            endpoint;         /*!< endpoint of device that started the network */
    uint16_t           profile_id;       /*!< profile_id of device that started the network */
} esp_zb_bdb_signal_touchlink_nwk_params_t;

typedef esp_zb_bdb_signal_touchlink_nwk_params_t esp_zb_bdb_signal_touchlink_nwk_started_params_t;
typedef esp_zb_bdb_signal_touchlink_nwk_params_t esp_zb_bdb_signal_touchlink_nwk_joined_router_t;
typedef esp_zb_bdb_signal_touchlink_nwk_params_t esp_zb_bdb_signal_touchlink_nwk_joined_ed_t;

typedef struct esp_zb_zdo_signal_nwk_status_indication_params_s {
    uint8_t status;               /*!< Error code associated with the failure, refer to esp_zb_nwk_command_status_t */
    uint16_t network_addr;        /*!< Network device address associated with the status information */
    uint8_t unknown_command_id;   /*!< Unknown command ID */
} esp_zb_zdo_signal_nwk_status_indication_params_t;

typedef struct esp_zb_zdo_signal_device_update_params_s {
    esp_zb_ieee_addr_t long_addr;   /*!< Long Address of the updated device */
    uint16_t short_addr;            /*!< Short Address of the updated device */
    uint8_t status;                 /*!< Indicates the updated status of the device, refer to esp_zb_zdo_update_dev_status_t */
    uint8_t tc_action;              /*!< Trust center action,  refer to esp_zb_zdo_update_dev_tc_action_t */
    uint16_t parent_short;          /*!< The short address of device's parent */
} esp_zb_zdo_signal_device_update_params_t;

typedef struct esp_zb_zdo_signal_device_authorized_params_s {
    esp_zb_ieee_addr_t long_addr; /*!< Long Address of the updated device */
    uint16_t short_addr;          /*!< Short Address of the updated device */
    uint8_t authorization_type;   /*!< Type of the authorization procedure */
    uint8_t authorization_status; /*!< Status of the authorization procedure which depends on authorization_type */
} esp_zb_zdo_signal_device_authorized_params_t;

typedef struct esp_zb_zdo_device_unavailable_params_s {
    esp_zb_ieee_addr_t long_addr; /*!< Long address of the unavailable device */
    uint16_t short_addr;          /*!< Short address of unavailable device */
} esp_zb_zdo_device_unavailable_params_t;

typedef struct esp_zb_zdo_signal_can_sleep_params_s {
    uint32_t sleep_duration;      /*!< sleep duration in milliseconds */
} esp_zb_zdo_signal_can_sleep_params_t;

typedef struct esp_zb_nwk_signal_device_associated_params_s {
    esp_zb_ieee_addr_t device_addr; /*!< address of associated device */
} esp_zb_nwk_signal_device_associated_params_t;

typedef struct esp_zb_app_signal_s {
    uint32_t *p_app_signal;
    esp_err_t esp_err_status;
} esp_zb_app_signal_t;

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_s);
void *esp_zb_app_signal_get_params(uint32_t *signal_p);
const char *esp_zb_zdo_signal_to_string(esp_zb_app_signal_type_t signal);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#else
#error "This file is for compatibility, please include "ezbee/app_signals.h"!"
#endif
