/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"
#include "esp_zigbee_type.h"
#include "esp_zigbee_core.h"
#include "nwk/esp_zigbee_nwk.h"

/* These APIs are mainly for certification and tests.
 * They are not stable and might change in the future.
 */

typedef uint16_t (* esp_zb_addr_assignment_cb_t)(esp_zb_ieee_addr_t ieee_addr);

typedef enum esp_zb_apsme_request_key_type_s {
    ESP_ZB_APSME_REQUEST_APP_LINK_KEY = 2U, /*!< Application link key */
    ESP_ZB_APSME_REQUEST_TC_LINK_KEY  = 4U, /*!< Trust-center link key */
} esp_zb_apsme_request_key_type_t;

typedef enum {
    ESP_ZB_SECUR_PROVISIONAL_KEY = 0U,    /*!< Provisional key - typically a temporary key received but not yet verified */
    ESP_ZB_SECUR_UNVERIFIED_KEY  = 1U,    /*!< Unverified key - received but not validated through the key establishment process */
    ESP_ZB_SECUR_VERIFIED_KEY    = 2U,    /*!< Verified key - successfully established and verified */
    ESP_ZB_SECUR_APPLICATION_KEY = 3U,    /*!< non-standard - for quick check for !TCLK */
    ESP_ZB_SECUR_ANY_KEY_ATTR    = 0xFFU  /*!< Any key attribute - for zb_secur_get_link_key_by_address() */
} esp_zb_secur_key_attribute_t;

typedef enum {
    ESP_ZB_SECUR_UNIQUE_KEY = 0U, /*!< Unique link key - used for a single device pair */
    ESP_ZB_SECUR_GLOBAL_KEY = 1U, /*!< Global link key - shared across multiple devices */
} esp_zb_secur_aps_link_key_type_t;

typedef enum {
    ESP_ZB_SECUR_KEY_SRC_UNKNOWN = 0U, /*!< key source is unknown/doesn't matter */
    ESP_ZB_SECUR_KEY_SRC_CBKE    = 1U, /*!< key was obtained via CBKE (key establishment) */
} esp_zb_secur_key_source_t;

typedef enum {
    ESP_ZB_KEEPALIVE_MODE_NONE = 0U,               /*!< ZC/ZR does not support Keepalive feature */
    ESP_ZB_KEEPALIVE_MODE_MAC_DATA_POLL = 1U,      /*!< ZC/ZR supports Keepalive feature by means of MAC Data Poll */
    ESP_ZB_KEEPALIVE_MODE_ED_TIMEOUT_REQUEST = 2U, /*!< ZC/ZR supports Keepalive feature by means of ED Timeout Request */
    ESP_ZB_KEEPALIVE_MODE_BOTH = 3U,               /*!< ZC/ZR supports both MAC Data Poll and ED Timeout Request as Keepalive methods */
} esp_zb_keepalive_mode_t;

typedef struct esp_zb_apsme_request_key_req_s{
  esp_zb_ieee_addr_t dst_address;     /*!< Destination address*/
  esp_zb_ieee_addr_t partner_address; /*!< Partner address */
  uint8_t key_type;                   /*!< see @ref esp_zb_apsme_request_key_type_s */
} esp_zb_apsme_request_key_req_t;

typedef struct esp_zb_apsme_remove_device_req_s {
    esp_zb_ieee_addr_t parent_address;      /*!< Parent Address*/
    esp_zb_ieee_addr_t child_address;       /*!< Child Address*/
} esp_zb_apsme_remove_device_req_t;

typedef struct esp_zb_secur_update_key_pair_params_s {
    esp_zb_ieee_addr_t address;           /*!< Partner device IEEE address (64-bit extended address) */
    uint8_t key[ESP_ZB_CCM_KEY_SIZE];     /*!< Key value */
    uint8_t key_type;                     /*!< Key type, see @ref esp_zb_secur_key_type_t */
    uint8_t key_attr;                     /*!< Key attributes, see @ref esp_zb_secur_key_attribute_t */
    uint8_t key_source;                   /*!< Source of the key (e.g. how key was obtained) see @ref esp_zb_secur_key_source_t */
} esp_zb_secur_update_key_pair_params_t;


esp_err_t esp_zb_apsme_request_key_request(esp_zb_apsme_request_key_req_t *req);

esp_err_t esp_zb_apsme_remove_device_request(const esp_zb_apsme_remove_device_req_t *req);

esp_err_t esp_zb_aps_group_table_add_group(uint16_t groupid, uint8_t endpoint);

esp_err_t esp_zb_aps_group_table_remove_group(uint16_t groupid, uint8_t endpoint);

esp_err_t esp_zb_secur_update_key_pair(esp_zb_secur_update_key_pair_params_t *params);

esp_err_t esp_zb_secur_set_unsecure_tc_rejoin_enabled(bool enable);

esp_err_t esp_zb_secur_tcpol_set_allow_tc_rejoins(uint8_t allow_tc_rejoins);

bool esp_zb_secur_has_link_key_pair_set(esp_zb_ieee_addr_t address);

esp_err_t esp_zb_nwk_set_short_address(uint16_t short_address);

esp_err_t esp_zb_nwk_set_network_device_role_legacy(esp_zb_nwk_device_type_t role);

esp_err_t esp_zb_nwk_set_keepalive_mode(esp_zb_keepalive_mode_t mode);

esp_err_t esp_zb_nwk_set_neighbor_info(uint16_t short_addr, uint8_t age, uint8_t outgoing_cost, uint8_t lqa);

esp_err_t esp_zb_nwk_set_ed_timeout(esp_zb_aging_timeout_t timeout);

esp_err_t esp_zb_nwk_set_keepalive_timeout(uint64_t timeout);

esp_err_t esp_zb_nwk_set_leave_req_allowed(bool allowed);

esp_err_t esp_zb_nwk_start_concentrator_mode(uint8_t radius, uint32_t disc_time);

esp_err_t esp_zb_nwk_stop_concentrator_mode(void);

esp_err_t esp_zb_address_delete_address_mapping_by_short(uint16_t short_addr);

void esp_zb_mac_add_visible_device(esp_zb_ieee_addr_t ieee_addr);

void esp_zb_mac_add_invisible_short(uint16_t short_addr);

void esp_zb_mac_remove_invisible_short(uint16_t short_addr);

void esp_zb_cert_enable_test_profile(uint16_t profile_id, uint8_t endpoint, uint16_t app_device_id, uint8_t app_device_version);

esp_err_t esp_zb_cert_set_frag_block_size(uint8_t size);

esp_err_t esp_zb_cert_set_route_cost_policy(bool disable_in_out_cost_updating, bool delay_pending_tx_on_rresp, bool use_route_for_neighbor);

void esp_zb_cert_set_address_assignment_cb(esp_zb_addr_assignment_cb_t cb);

void esp_zb_cert_set_update_device_unencrypted(bool unencrypted);

esp_err_t esp_zb_cert_set_binding_table_size(uint8_t src_size, uint8_t dst_size);

esp_err_t esp_zb_cert_disable_addr_conflict_check_on_update_device(bool disable);

esp_err_t esp_zb_cert_use_preconfigured_aps_link_key(uint8_t value);

esp_err_t esp_zb_cert_start_fixed_poll(uint64_t poll_interval, bool permit_turbo_poll);

esp_err_t esp_zb_secur_aps_security_enable(bool enabled);

bool esp_zb_secur_aps_security_is_enabled(void);

#ifdef __cplusplus
}
#endif
