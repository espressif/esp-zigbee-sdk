/*
 * SPDX-FileCopyrightText: 2022-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "esp_zigbee.h" instead!"

#include <esp_zigbee.h>

#include "platform/esp_zigbee_platform.h"
#include "mac/esp_zigbee_mac.h"
#include "nwk/esp_zigbee_nwk.h"
#include "aps/esp_zigbee_aps.h"
#include "zdo/esp_zigbee_zdo_common.h"
#include "zdo/esp_zigbee_zdo_command.h"
#include "bdb/esp_zigbee_bdb_commissioning.h"
#include "bdb/esp_zigbee_bdb_touchlink.h"
#include "zcl/esp_zigbee_zcl_core.h"
#include "esp_zigbee_secur.h"

#ifdef __cplusplus
extern "C" {
#endif

/* esp_zigbee_core.h */
#define ESP_ZB_TRANSCEIVER_ALL_CHANNELS_MASK 0x07FFF800U /*!< channel 11-26 for compatibility with 2.4GHZ */
#define esp_zb_start(autostart)             esp_zigbee_start(autostart)
#define esp_zb_is_started()                 esp_zigbee_is_started()
#define esp_zb_lock_acquire(block_ticks)    esp_zigbee_lock_acquire(block_ticks)
#define esp_zb_lock_release()               esp_zigbee_lock_release()
#define esp_zb_stack_main_loop()            esp_zigbee_launch_mainloop()
#define esp_zb_stack_main_loop_iteration()  /* Deprecated */

typedef struct esp_zigbee_zczr_config_s esp_zb_zczr_cfg_t;
typedef struct esp_zigbee_zed_config_s esp_zb_zed_cfg_t;
typedef struct esp_zb_cfg_s {
    esp_zb_nwk_device_type_t esp_zb_role;
    bool install_code_policy;
    union {
        esp_zb_zczr_cfg_t zczr_cfg;
        esp_zb_zed_cfg_t zed_cfg;
    } nwk_cfg;
} esp_zb_cfg_t;

void esp_zb_init(esp_zb_cfg_t *nwk_cfg);

typedef void (*esp_zb_callback_t)(uint8_t param);
typedef esp_zigbee_callback_t esp_zb_user_callback_t;
typedef void* esp_zb_user_cb_handle_t;
#define ESP_ZB_USER_CB_HANDLE_INVALID NULL

void esp_zb_scheduler_alarm(esp_zb_callback_t cb, uint8_t param, uint32_t time);
void esp_zb_scheduler_alarm_cancel(esp_zb_callback_t cb, uint8_t param);
esp_zb_user_cb_handle_t esp_zb_scheduler_user_alarm(esp_zb_user_callback_t cb, void *param, uint32_t time);
esp_err_t esp_zb_scheduler_user_alarm_cancel(esp_zb_user_cb_handle_t handle);

#define esp_zb_zdo_touchlink_set_nwk_channel(v) TO_ESP_ERR(ezb_touchlink_set_channel(v))
#define esp_zb_zdo_touchlink_get_nwk_channel()  ezb_touchlink_get_channel()
#define esp_zb_set_channel_mask(channel_mask)   TO_ESP_ERR(ezb_set_channel_mask(channel_mask))
#define esp_zb_get_channel_mask()               ezb_get_channel_mask()

#define esp_zb_set_tx_power(power) ezb_set_tx_power(power)
#define esp_zb_get_tx_power(power) ezb_get_tx_power(power)

/* Misc*/
#define esp_zb_factory_reset()              esp_zigbee_factory_reset()
#define esp_zb_nvram_erase_at_start(erase)  /* Don't support erase NVRAM at start */

/* Memory */
#define esp_zb_scheduler_queue_size_set(size)        /* No scheduler queue */
esp_err_t esp_zb_overall_network_size_set(uint16_t size);
#define esp_zb_io_buffer_size_set(size)              TO_ESP_ERR(ezb_config_memory(&(ezb_mem_config_t){.buffer_pool_size = size}))
#define esp_zb_aps_src_binding_table_size_set(size)  TO_ESP_ERR(ezb_config_memory(&(ezb_mem_config_t){.aps_bind_src_table_size = size}))
#define esp_zb_aps_dst_binding_table_size_set(size)  TO_ESP_ERR(ezb_config_memory(&(ezb_mem_config_t){.aps_bind_dst_table_size = size}))

/* Security */
#define esp_zb_enable_joining_to_distributed(enable)      ezb_aps_secur_enable_distributed_security(enable)
#define esp_zb_joining_to_distributed_network_enabled()   ezb_aps_secur_is_distributed_security()
#define esp_zb_enable_distributed_network(enable)         ezb_aps_secur_enable_distributed_security(enable)
#define esp_zb_network_is_distributed()                   ezb_aps_secur_is_distributed_security()
#define esp_zb_zdo_setup_network_as_distributed()         ezb_aps_secur_enable_distributed_security(true)
#define esp_zb_tc_policy_set_distributed_security(enable) ezb_aps_secur_enable_distributed_security(enable)
#define esp_zb_tc_policy_get_distributed_security()       ezb_aps_secur_is_distributed_security()

/* Sleep */
#define ESP_ZB_SLEEP_MAXIMUM_THRESHOLD_MS 86400000U /*!< Maximum sleep threshold*/
#define esp_zb_sleep_is_enable()          (true)
#define esp_zb_sleep_enable(enable)
#define esp_zb_sleep_now()
#define esp_zb_sleep_set_threshold(threshold_ms)

/* AF */
#define esp_zb_set_node_descriptor_power_source(is_main_power)    /* Don't need to set the power source separately */
#define esp_zb_set_node_descriptor_transfer_size(max_in, max_out) /* Don't need to set the transfer size separately */
#define esp_zb_set_node_descriptor_manufacturer_code(manuf_code)  ezb_af_node_desc_set_manuf_code(manuf_code)
#define esp_zb_set_node_power_descriptor(node_power)              TO_ESP_ERR(ezb_af_set_node_power_desc(&node_power))

/* Versioning */
#define esp_zb_get_version_string() esp_zigbee_get_version_string()

#ifdef __cplusplus
}
#endif

#else
#error "This file is for compatibility, please include "esp_zigbee.h"!"
#endif
