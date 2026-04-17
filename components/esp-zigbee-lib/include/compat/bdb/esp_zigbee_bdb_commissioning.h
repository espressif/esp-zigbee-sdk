/*
 * SPDX-FileCopyrightText: 2022-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/bdb.h" instead!"

#include <ezbee/bdb.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ZB_BDB_MIN_COMMISSIONING_TIME 180U

#define ESP_ZB_BDB_INITIALIZATION          EZB_BDB_MODE_INITIALIZATION
#define ESP_ZB_BDB_TOUCHLINK_COMMISSIONING EZB_BDB_MODE_TOUCHLINK_INITIATOR
#define ESP_ZB_BDB_NETWORK_STEERING        EZB_BDB_MODE_NETWORK_STEERING
#define ESP_ZB_BDB_NETWORK_FORMATION       EZB_BDB_MODE_NETWORK_FORMATION
#define ESP_ZB_BDB_FINDING_N_BINDING       EZB_BDB_MODE_FINDING_N_BINDING
#define ESP_ZB_BDB_TOUCHLINK_TARGET        EZB_BDB_MODE_TOUCHLINK_TARGET
typedef ezb_bdb_comm_mode_mask_t esp_zb_bdb_commissioning_mode_mask_t;

#define ESP_ZB_BDB_MODE_INITIALIZATION          ESP_ZB_BDB_INITIALIZATION
#define ESP_ZB_BDB_MODE_TOUCHLINK_COMMISSIONING ESP_ZB_BDB_TOUCHLINK_COMMISSIONING
#define ESP_ZB_BDB_MODE_NETWORK_STEERING        ESP_ZB_BDB_NETWORK_STEERING
#define ESP_ZB_BDB_MODE_NETWORK_FORMATION       ESP_ZB_BDB_NETWORK_FORMATION
#define ESP_ZB_BDB_MODE_TOUCHLINK_TARGET        ESP_ZB_BDB_TOUCHLINK_TARGET
typedef ezb_bdb_comm_mode_t esp_zb_bdb_commissioning_mode_t;

#define ESP_ZB_BDB_STATUS_SUCCESS                    EZB_BDB_STATUS_SUCCESS
#define ESP_ZB_BDB_STATUS_IN_PROGRESS                EZB_BDB_STATUS_IN_PROGRESS
#define ESP_ZB_BDB_STATUS_NOT_AA_CAPABLE             EZB_BDB_STATUS_NOT_AA_CAPABLE
#define ESP_ZB_BDB_STATUS_NO_NETWORK                 EZB_BDB_STATUS_NO_NETWORK
#define ESP_ZB_BDB_STATUS_TARGET_FAILURE             EZB_BDB_STATUS_TARGET_FAILURE
#define ESP_ZB_BDB_STATUS_FORMATION_FAILURE          EZB_BDB_STATUS_FORMATION_FAILURE
#define ESP_ZB_BDB_STATUS_NO_IDENTIFY_QUERY_RESPONSE EZB_BDB_STATUS_NO_IDENTIFY_QUERY_RESPONSE
#define ESP_ZB_BDB_STATUS_BINDING_TABLE_FULL         EZB_BDB_STATUS_BINDING_TABLE_FULL
#define ESP_ZB_BDB_STATUS_NO_SCAN_RESPONSE           EZB_BDB_STATUS_NO_SCAN_RESPONSE
#define ESP_ZB_BDB_STATUS_NOT_PERMITTED              EZB_BDB_STATUS_NOT_PERMITTED
#define ESP_ZB_BDB_STATUS_TCLK_EX_FAILURE            EZB_BDB_STATUS_TCLK_EX_FAILURE
#define ESP_ZB_BDB_STATUS_NOT_ON_A_NETWORK           EZB_BDB_STATUS_NOT_ON_A_NETWORK
#define ESP_ZB_BDB_STATUS_ON_A_NETWORK               EZB_BDB_STATUS_ON_A_NETWORK
#define ESP_ZB_BDB_STATUS_CANCELLED                  EZB_BDB_STATUS_CANCELLED
#define ESP_ZB_BDB_STATUS_DEV_ANNCE_SEND_FAILURE     EZB_BDB_STATUS_DEV_ANNCE_SEND_FAILURE
typedef ezb_bdb_comm_status_t esp_zb_bdb_commissioning_status_t;

#define esp_zb_set_primary_network_channel_set(channel_mask)   TO_ESP_ERR(ezb_bdb_set_primary_channel_set(channel_mask))
#define esp_zb_get_primary_network_channel_set()               ezb_bdb_get_primary_channel_set()
#define esp_zb_set_secondary_network_channel_set(channel_mask) TO_ESP_ERR(ezb_bdb_set_secondary_channel_set(channel_mask))
#define esp_zb_get_secondary_network_channel_set()             ezb_bdb_get_secondary_channel_set()
#define esp_zb_bdb_get_scan_duration()                         ezb_bdb_get_scan_duration()
#define esp_zb_bdb_set_scan_duration(duration)                 ezb_bdb_set_scan_duration(duration)
#define esp_zb_bdb_dev_joined()                                ezb_bdb_dev_joined()
#define esp_zb_set_bdb_commissioning_mode(mode)                ezb_bdb_set_commissioning_mode(mode)
#define esp_zb_get_bdb_commissioning_mode()                    ezb_bdb_get_commissioning_mode()
#define esp_zb_get_bdb_commissioning_status()                  ezb_bdb_get_commissioning_status()
#define esp_zb_bdb_start_top_level_commissioning(mode_mask)    TO_ESP_ERR(ezb_bdb_start_top_level_commissioning(mode_mask))
#define esp_zb_bdb_cancel_steering()                           TO_ESP_ERR(ezb_bdb_cancel_steering())
#define esp_zb_bdb_cancel_formation()                          TO_ESP_ERR(ezb_bdb_cancel_formation())
#define esp_zb_bdb_cancel_touchlink_target()                   TO_ESP_ERR(ezb_bdb_cancel_touchlink_target())
#define esp_zb_bdb_open_network(permit_duration)               TO_ESP_ERR(ezb_bdb_open_network(permit_duration))
#define esp_zb_bdb_close_network()                             TO_ESP_ERR(ezb_bdb_close_network())
#define esp_zb_bdb_reset_via_local_action()                    ezb_bdb_reset_via_local_action()
#define esp_zb_bdb_is_factory_new()                            ezb_bdb_is_factory_new()

#ifdef __cplusplus
}
#endif

#else
#error "This file is for compatibility, please include "ezbee/bdb.h"!"
#endif
