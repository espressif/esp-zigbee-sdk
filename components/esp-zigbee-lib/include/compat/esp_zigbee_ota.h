/*
 * SPDX-FileCopyrightText: 2022-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/zcl/cluster/ota_upgrade.h" instead!"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct esp_zb_ota_zcl_information_s {
    esp_zb_zcl_addr_t src_addr;
    uint16_t          dst_short_addr;
    uint8_t           src_endpoint;
    uint8_t           dst_endpoint;
    uint16_t          cluster_id;
    uint16_t          profile_id;
    uint8_t           command_id;
    uint16_t          manufacturer_specific;
} esp_zb_ota_zcl_information_t;

typedef struct esp_zb_ota_file_optional_s {
    uint8_t            security_credential_version;
    esp_zb_ieee_addr_t upgrade_file_destination;
    uint16_t           minimum_hardware_version;
    uint16_t           maximum_hardware_version;
} esp_zb_ota_file_optional_t;

typedef struct esp_zb_ota_file_header_s {
    uint16_t                 manufacturer_code;
    uint16_t                 image_type;
    uint32_t                 file_version;
    uint32_t                 image_size;
    uint16_t                 field_control;
    esp_zb_ota_file_optional_t optional;
} esp_zb_ota_file_header_t;

typedef esp_err_t (*esp_zb_ota_next_data_callback_t)(esp_zb_ota_zcl_information_t message,
                                                     uint16_t                       index,
                                                     uint8_t                        size,
                                                     uint8_t                      **data);

typedef struct esp_zb_zcl_ota_upgrade_client_variable_s {
    uint16_t timer_query;
    uint16_t hw_version;
    uint8_t  max_data_size;
} esp_zb_zcl_ota_upgrade_client_variable_t;

typedef struct esp_zb_zcl_ota_upgrade_server_variable_s {
    uint8_t  query_jitter;
    uint32_t current_time;
    uint8_t  file_count;
} esp_zb_zcl_ota_upgrade_server_variable_t;

typedef struct esp_zb_ota_upgrade_server_notify_req_s {
    uint8_t                      endpoint;
    uint8_t                      index;
    uint8_t                      notify_on;
    uint32_t                     ota_upgrade_time;
    esp_zb_ota_file_header_t     ota_file_header;
    esp_zb_ota_next_data_callback_t next_data_cb;
} esp_zb_ota_upgrade_server_notify_req_t;

#define esp_zb_ota_upgrade_server_notify_req(req) ((void)(req), ESP_ERR_NOT_SUPPORTED)

#define esp_zb_ota_upgrade_client_query_image_req(server_ep, server_addr) \
    ((void)(server_ep), (void)(server_addr), ESP_ERR_NOT_SUPPORTED)

#define esp_zb_ota_upgrade_client_query_interval_set(endpoint, interval) \
    ((void)(endpoint), (void)(interval), ESP_ERR_NOT_SUPPORTED)

#define esp_zb_ota_upgrade_client_query_image_stop() (ESP_ERR_NOT_SUPPORTED)

#ifdef __cplusplus
}
#endif

#else
#error "This file is for compatibility, please include "ezbee/zcl/cluster/ota_upgrade.h"!"
#endif
