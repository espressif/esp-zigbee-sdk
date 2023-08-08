/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee touchlink switch Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_touchlink_switch.h"
#include "nvs_flash.h"
#include "ha/esp_zigbee_ha_standard.h"

/**
 * @note Make sure set idf.py menuconfig in zigbee component as zigbee end device!
*/
#if !defined ZB_ED_ROLE
#error Define ZB_ED_ROLE in idf.py menuconfig to compile light switch (End Device) source code.
#endif

esp_zb_64bit_addr_t g_zeros_addr = {0, 0, 0, 0, 0, 0, 0, 0};
#define ESP_ZB_IEEE_ADDR_IS_ZERO(addr) (memcmp((addr), (void const*)g_zeros_addr, 8) == 0)

static const char *TAG = "ESP_TL_ON_OFF_SWITCH";

/* Define Button function currently only 1 switch define */
static switch_func_pair_t button_func_pair[] = {
    {GPIO_INPUT_IO_TOGGLE_SWITCH, SWITCH_ONOFF_TOGGLE_CONTROL}
};

/* Define a single remote device struct for managing */
typedef struct light_bulb_info_s
{
  esp_zb_ieee_addr_t ieee_addr;
  uint16_t short_addr;
  uint8_t endpoint;
} light_bulb_info_t;

typedef struct light_control_device_ctx_t
{
    light_bulb_info_t on_off_light;;  /* persistent, remote device struct for recording and managing node info */
    esp_zb_ieee_addr_t pending_dev_addr;  /* addr of device which is pending for discovery */
} light_control_device_ctx_t;

light_control_device_ctx_t g_device_ctx;  /* light control device ifnfomation */

static void esp_zb_buttons_handler(switch_func_pair_t *button_func_pair)
{
    /* By checking the button function pair to call different cmd send */
    switch (button_func_pair->func) {
    case SWITCH_ONOFF_TOGGLE_CONTROL:
        /* Send on-off toggle command to remote device */
        esp_zb_zcl_on_off_cmd_t cmd_req;
        cmd_req.zcl_basic_cmd.dst_addr_u.addr_short = g_device_ctx.on_off_light.short_addr;
        cmd_req.zcl_basic_cmd.dst_endpoint =g_device_ctx.on_off_light.endpoint;
        cmd_req.zcl_basic_cmd.src_endpoint = HA_ONOFF_SWITCH_ENDPOINT;
        cmd_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
        cmd_req.on_off_cmd_id = ESP_ZB_ZCL_CMD_ON_OFF_TOGGLE_ID;
        ESP_EARLY_LOGI(TAG, "send 'on_off toggle' command");
        esp_zb_zcl_on_off_cmd_req(&cmd_req);
        break;
    default:
        break;
    }
}

static void user_find_cb(esp_zb_zdp_status_t zdo_status, uint16_t addr, uint8_t endpoint, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        ESP_LOGI(TAG, "User find cb: response_status:%d, address:0x%x, endpoint:%d", zdo_status, addr, endpoint);
        /* Save into remote device record structure for future use */
        g_device_ctx.on_off_light.short_addr = addr;
        g_device_ctx.on_off_light.endpoint = endpoint;
    }
}

void find_light_bulb(zb_uint16_t short_addr)
{
    esp_zb_zdo_match_desc_req_param_t  find_req;
    find_req.addr_of_interest = short_addr;
    find_req.dst_nwk_addr = short_addr;
    /* Find the match on-off light device */
    esp_zb_zdo_find_on_off_light(&find_req, user_find_cb, NULL);

    memset(g_device_ctx.pending_dev_addr, 0, sizeof(esp_zb_ieee_addr_t));
}

/********************* Define functions **************************/
static void esp_zb_start_touchlink_commissioning(void)
{
    esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_TOUCHLINK_COMMISSIONING);
    ESP_LOGI(TAG, "Start Touchlink commissioning as initiator");
}

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p     = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;

    switch (sig_type) {
    case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "ZB_ZDO_SIGNAL_SKIP_STARTUP: start join");
        /* If factory new, start Touchlink commissioning, else start only steering */
        if (esp_zb_bdb_is_factory_new()) {
            esp_zb_start_touchlink_commissioning();
        } 
        else {
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_INITIALIZATION);
        }
        break;
    case ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT:
        ESP_LOGI(TAG, "Device restarted");
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED:
        esp_zb_bdb_signal_touchlink_nwk_params_t *sig_params = (esp_zb_bdb_signal_touchlink_nwk_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        memcpy(g_device_ctx.pending_dev_addr, sig_params->device_ieee_addr, sizeof(esp_zb_ieee_addr_t));

        ESP_LOGI(TAG, "Touchlink network started");
        ESP_LOGI(TAG, "Profile: 0x%x, ep: %d", sig_params->profile_id, sig_params->endpoint);
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_JOINED_ROUTER:
        esp_zb_bdb_signal_touchlink_nwk_params_t *joined_router_sig_params = (esp_zb_bdb_signal_touchlink_nwk_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        memcpy(g_device_ctx.pending_dev_addr, joined_router_sig_params->device_ieee_addr, sizeof(esp_zb_ieee_addr_t));
        ESP_LOGI(TAG, "Touchlink network joined router");
        ESP_LOGI(TAG, "Profile: 0x%x, ep: %d", joined_router_sig_params->profile_id, joined_router_sig_params->endpoint);
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK:
        ESP_LOGI(TAG, "Touchlink commissioning as initiator done");
        if (err_status == ESP_OK)
        {
            ESP_LOGI(TAG, "Touchlink Success, device address: 0x%x %x %x %x %x %x %x %x",g_device_ctx.pending_dev_addr[7],g_device_ctx.pending_dev_addr[6],g_device_ctx.pending_dev_addr[5],
            g_device_ctx.pending_dev_addr[4], g_device_ctx.pending_dev_addr[3],g_device_ctx.pending_dev_addr[2],g_device_ctx.pending_dev_addr[1], g_device_ctx.pending_dev_addr[0]);
            
            if (!ESP_ZB_IEEE_ADDR_IS_ZERO(g_device_ctx.pending_dev_addr)) {
                uint16_t short_addr = esp_zb_address_short_by_ieee(g_device_ctx.pending_dev_addr);
                find_light_bulb(short_addr);
            }
        } else {
            /* Repeat touchlink until any bulb will be found */
            esp_zb_start_touchlink_commissioning();
        }
        break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type, esp_err_to_name(err_status));
        break;
    }
}

static void esp_zb_task(void *pvParameters)
{
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZED_CONFIG();
    esp_zb_init(&zb_nwk_cfg);
    esp_zb_set_channel_mask(ESP_ZB_TOUCHLINK_CHANNEL_MASK);
    esp_zb_zdo_touchlink_set_nwk_channel(ESP_ZB_TOUCHLINK_CHANNEL);
    esp_zb_set_rx_on_when_idle(true);

    esp_zb_attribute_list_t *touchlink_cluster = esp_zb_touchlink_commissioning_cluster_create();
    esp_zb_on_off_switch_cfg_t switch_cfg = ESP_ZB_DEFAULT_ON_OFF_SWITCH_CONFIG();
    /* Create a standard HA on-off switch cluster list */
    esp_zb_cluster_list_t *cluster_list = esp_zb_on_off_switch_clusters_create(&switch_cfg);
    /* Add touchlink commissioning cluster */
    esp_zb_cluster_list_add_touchlink_commissioning_cluster(cluster_list, touchlink_cluster, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);

    esp_zb_ep_list_t *esp_zb_ep_list = esp_zb_ep_list_create();
    /* Add created endpoint (cluster_list) to endpoint list */
    esp_zb_ep_list_add_ep(esp_zb_ep_list, cluster_list, HA_ONOFF_SWITCH_ENDPOINT, ESP_ZB_AF_HA_PROFILE_ID, ESP_ZB_HA_ON_OFF_LIGHT_DEVICE_ID);
    esp_zb_device_register(esp_zb_ep_list);

    ESP_ERROR_CHECK(esp_zb_start(false));
    esp_zb_main_loop_iteration();
}

void app_main(void)
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    /* Hardware related and device init */
    switch_driver_init(button_func_pair, PAIR_SIZE(button_func_pair), esp_zb_buttons_handler);

    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
