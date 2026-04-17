/*
 * SPDX-FileCopyrightText: 2022-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/secur.h" instead!"

#include <ezbee/secur.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ZB_IC_TYPE_48  EZB_SECUR_IC_TYPE_48
#define ESP_ZB_IC_TYPE_64  EZB_SECUR_IC_TYPE_64
#define ESP_ZB_IC_TYPE_96  EZB_SECUR_IC_TYPE_96
#define ESP_ZB_IC_TYPE_128 EZB_SECUR_IC_TYPE_128
#define ESP_ZB_IC_TYPE_MAX EZB_SECUR_IC_TYPE_MAX_NR
typedef ezb_secur_ic_type_t esp_zb_secur_ic_type_t;

#define esp_zb_secur_ic_only_enable(enabled)                TO_ESP_ERR(ezb_secur_set_ic_required(enabled))
#define esp_zb_secur_link_key_exchange_required_set(enable) ((void)ezb_secur_set_tclk_exchange_required(enable))

#define esp_zb_secur_ic_str_add(address, ic_str) (ESP_ERR_NOT_SUPPORTED)
#define esp_zb_secur_ic_str_set(ic_str)          (ESP_ERR_NOT_SUPPORTED)

#define esp_zb_secur_ic_add(address, ic_type, ic) TO_ESP_ERR(ezb_secur_ic_add((const ezb_extaddr_t *)address, ic_type, ic))
#define esp_zb_secur_ic_remove_req(address)       TO_ESP_ERR(ezb_secur_ic_remove((const ezb_extaddr_t *)address))
#define esp_zb_secur_ic_remove_all_req()          TO_ESP_ERR(ezb_secur_ic_remove_all())
#define esp_zb_secur_ic_set(ic_type, ic)          TO_ESP_ERR(ezb_secur_ic_set(ic_type, ic))
uint8_t *esp_zb_secur_ic_get(uint8_t *ic_type);

#define esp_zb_secur_TC_standard_distributed_key_set(key)  ezb_secur_set_global_link_key(key)
#define esp_zb_secur_TC_standard_preconfigure_key_set(key) ezb_secur_set_global_link_key(key)

#define esp_zb_secur_network_security_enable(enabled) TO_ESP_ERR(ezb_secur_set_security_level((enabled ? EZB_SECUR_SECLEVEL_ENC_MIC32 : EZB_SECUR_SECLEVEL_NONE)))
#define esp_zb_secur_network_security_is_enabled()    (ezb_secur_get_security_level() > EZB_SECUR_SECLEVEL_NONE)

#define esp_zb_secur_primary_network_key_get(key)         TO_ESP_ERR(ezb_secur_get_network_key(key))
#define esp_zb_secur_network_key_set(key)                 TO_ESP_ERR(ezb_secur_set_network_key(key))
#define esp_zb_secur_network_key_switch(key, key_seq_num) TO_ESP_ERR(ezb_secur_switch_network_key(key, key_seq_num))

#define esp_zb_secur_broadcast_network_key(key, key_seq_num)   TO_ESP_ERR(ezb_secur_broadcast_network_key(key, key_seq_num))
#define esp_zb_secur_broadcast_network_key_switch(key_seq_num) TO_ESP_ERR(ezb_secur_broadcast_switch_network_key(key_seq_num))

#define esp_zb_secur_network_min_join_lqi_get()    ezb_nwk_get_min_join_lqi()
#define esp_zb_secur_network_min_join_lqi_set(lqi) ezb_nwk_set_min_join_lqi(lqi)

#define esp_zb_secur_multi_TC_standard_preconfigure_key_add(key)    (ESP_ERR_NOT_SUPPORTED)
#define esp_zb_secur_multi_TC_standard_preconfigure_key_remove(key) (ESP_ERR_NOT_SUPPORTED)
#define esp_zb_secur_multi_standard_distributed_key_add(key)        (ESP_ERR_NOT_SUPPORTED)
#define esp_zb_secur_multi_standard_distributed_key_remove(key)     (ESP_ERR_NOT_SUPPORTED)

#ifdef __cplusplus
} /*  extern "C" */
#endif

#else
#error "This file is for compatibility, please include "ezbee/secur.h"!"
#endif
