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
#include "esp_check.h"
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

static void zb_buttons_handler(switch_func_pair_t *button_func_pair)
{
    /* By checking the button function pair to call different cmd send */
    switch (button_func_pair->func) {
    case SWITCH_ONOFF_TOGGLE_CONTROL:
        /* Send on-off toggle command to remote device */
        esp_zb_zcl_on_off_cmd_t cmd_req;
        cmd_req.zcl_basic_cmd.src_endpoint = HA_ONOFF_SWITCH_ENDPOINT;
        cmd_req.address_mode = ESP_ZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT;
        cmd_req.on_off_cmd_id = ESP_ZB_ZCL_CMD_ON_OFF_TOGGLE_ID;
        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_on_off_cmd_req(&cmd_req);
        esp_zb_lock_release();
        ESP_EARLY_LOGI(TAG, "send 'on_off toggle' command");
        break;
    default:
        break;
    }
}

static esp_err_t deferred_driver_init(void)
{
    ESP_RETURN_ON_FALSE(switch_driver_init(button_func_pair, PAIR_SIZE(button_func_pair), zb_buttons_handler), ESP_FAIL, TAG,
                        "Failed to initialize switch driver");
    return ESP_OK;
}

static void bind_cb(esp_zb_zdp_status_t zdo_status, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        ESP_LOGI(TAG, "Bound successfully!");
        if (user_ctx) {
            ESP_LOGI(TAG, "The light originating from address(0x%x) on endpoint(%d)", g_device_ctx.on_off_light.short_addr,
                     g_device_ctx.on_off_light.endpoint);
        }
    }
}

static void user_find_cb(esp_zb_zdp_status_t zdo_status, uint16_t addr, uint8_t endpoint, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        ESP_LOGI(TAG, "Found light");
        esp_zb_zdo_bind_req_param_t bind_req;
        g_device_ctx.on_off_light.short_addr = addr;
        g_device_ctx.on_off_light.endpoint = endpoint;
        esp_zb_ieee_address_by_short(g_device_ctx.on_off_light.short_addr, g_device_ctx.on_off_light.ieee_addr);
        esp_zb_get_long_address(bind_req.src_address);
        bind_req.src_endp = HA_ONOFF_SWITCH_ENDPOINT;
        bind_req.cluster_id = ESP_ZB_ZCL_CLUSTER_ID_ON_OFF;
        bind_req.dst_addr_mode = ESP_ZB_ZDO_BIND_DST_ADDR_MODE_64_BIT_EXTENDED;
        memcpy(bind_req.dst_address_u.addr_long, g_device_ctx.on_off_light.ieee_addr, sizeof(esp_zb_ieee_addr_t));
        bind_req.dst_endp = endpoint;
        bind_req.req_dst_addr = esp_zb_get_short_address();
        ESP_LOGI(TAG, "Try to bind on/off light");
        esp_zb_zdo_device_bind_req(&bind_req, bind_cb, NULL);
    }
}

void find_light_bulb(uint16_t short_addr)
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
    ESP_LOGI(TAG, "Scanning as a Touchlink initiator...");
}

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p     = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;

    switch (sig_type) {
    case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Initialize Zigbee stack");
        esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_INITIALIZATION);
        break;
    case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Deferred driver initialization %s", deferred_driver_init() ? "failed" : "successful");
            ESP_LOGI(TAG, "Device started up in %s factory-reset mode", esp_zb_bdb_is_factory_new() ? "" : "non");
            if (esp_zb_bdb_is_factory_new()) {
                esp_zb_start_touchlink_commissioning();
            } else {
                ESP_LOGI(TAG, "Device rebooted");
            }
        } else {
            ESP_LOGW(TAG, "Failed to initialize Zigbee stack (status: %s)", esp_err_to_name(err_status));
        }
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED:
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_JOINED_ROUTER:
        esp_zb_bdb_signal_touchlink_nwk_params_t *sig_params = (esp_zb_bdb_signal_touchlink_nwk_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        memcpy(g_device_ctx.pending_dev_addr, sig_params->device_ieee_addr, sizeof(esp_zb_ieee_addr_t));
        ESP_LOGI(TAG, "Touchlink initiator receives the response for %s network",
                 sig_type == ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED ? "started" : "router joining");
        ESP_LOGI(TAG, "Response is from profile: 0x%04hx, endpoint: %d, address: 0x%x%x%x%x%x%x%x%X", sig_params->profile_id, sig_params->endpoint,
                 sig_params->device_ieee_addr[7], sig_params->device_ieee_addr[6], sig_params->device_ieee_addr[5], sig_params->device_ieee_addr[4],
                 sig_params->device_ieee_addr[3], sig_params->device_ieee_addr[2], sig_params->device_ieee_addr[1], sig_params->device_ieee_addr[0]);
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK:
        ESP_LOGI(TAG, "Touchlink commissioning as initiator done");
        esp_zb_ieee_addr_t extended_pan_id;
        esp_zb_get_extended_pan_id(extended_pan_id);
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG,
                     "Commissioning successfully, network information (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, "
                     "Channel:%d, Short Address: 0x%04hx)",
                     extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4], extended_pan_id[3], extended_pan_id[2],
                     extended_pan_id[1], extended_pan_id[0], esp_zb_get_pan_id(), esp_zb_get_current_channel(), esp_zb_get_short_address());
            if (!ESP_ZB_IEEE_ADDR_IS_ZERO(g_device_ctx.pending_dev_addr)) {
                find_light_bulb(esp_zb_address_short_by_ieee(g_device_ctx.pending_dev_addr));
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
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = HA_ONOFF_SWITCH_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_ON_OFF_SWITCH_DEVICE_ID,
        .app_device_version = 0
    };
    esp_zb_ep_list_add_ep(esp_zb_ep_list, cluster_list, endpoint_config);
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

    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
