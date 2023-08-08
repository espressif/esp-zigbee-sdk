/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee touchlink light Example
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
#include "esp_touchlink_light.h"
#include "nvs_flash.h"
#include "ha/esp_zigbee_ha_standard.h"

#if ! defined ZB_ROUTER_ROLE
#error define ZB_ROUTER_ROLE to compile
#endif /* defined ZB_ROUTER_ROLE */

static const char *TAG = "ESP_TL_ON_OFF_LIGHT";

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p     = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    esp_zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;
    switch (sig_type) {
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET:
        ESP_LOGI(TAG, "Touchlink target started");
        break;
    case ESP_ZB_NWK_SIGNAL_PERMIT_JOIN_STATUS:
        ESP_LOGI(TAG, "Device is on permit join status");
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK:
        ESP_LOGI(TAG, "Touchlink target : network started");
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET_FINISHED:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Touchlink target finished: success");
        } else {
            ESP_LOGI(TAG, "Touchlink target finished: failed");
        }
        break;
    case ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE:
        dev_annce_params = (esp_zb_zdo_signal_device_annce_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->device_short_addr);
        break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type, esp_err_to_name(err_status));
        break;
    }
}

void attr_cb(uint8_t status, uint8_t endpoint, uint16_t cluster_id, uint16_t attr_id, void *new_value)
{
    if (cluster_id == ESP_ZB_ZCL_CLUSTER_ID_ON_OFF) {
        uint8_t value = *(uint8_t *)new_value;
        if (attr_id == ESP_ZB_ZCL_ATTR_ON_OFF_ON_OFF_ID) {
            /* implemented light on/off control */
            ESP_LOGI(TAG, "on/off light set to %hd", value);
            light_driver_set_power((bool)value);
        }
    } else {
        /* Implement some actions if needed when other cluster changed */
        ESP_LOGI(TAG, "cluster:0x%x, attribute:0x%x changed ", cluster_id, attr_id);
    }
}

static void esp_zb_task(void *pvParameters)
{
    /* Initialize Zigbee stack with Zigbee coordinator config */
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZR_CONFIG();
    esp_zb_init(&zb_nwk_cfg);
    esp_zb_set_channel_mask(ESP_ZB_TOUCHLINK_CHANNEL_MASK);
    esp_zb_set_rx_on_when_idle(true);
 
    esp_zb_set_bdb_commissioning_mode(ESP_ZB_BDB_TOUCHLINK_TARGET);
    
    esp_zb_attribute_list_t *touchlink_cluster = esp_zb_touchlink_commissioning_cluster_create();

    esp_zb_on_off_light_cfg_t light_cfg = ESP_ZB_DEFAULT_ON_OFF_LIGHT_CONFIG();
    /* Create a standard HA on-off light cluster list */
    esp_zb_cluster_list_t *cluster_list = esp_zb_on_off_light_clusters_create(&light_cfg);

    /* Add touchlink commissioning cluster */
    esp_zb_cluster_list_add_touchlink_commissioning_cluster(cluster_list, touchlink_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);

    esp_zb_ep_list_t *esp_zb_ep_list = esp_zb_ep_list_create();
    /* Add created endpoint (cluster_list) to endpoint list */
    esp_zb_ep_list_add_ep(esp_zb_ep_list, cluster_list, HA_ESP_LIGHT_ENDPOINT, ESP_ZB_AF_HA_PROFILE_ID, ESP_ZB_HA_ON_OFF_LIGHT_DEVICE_ID);
    
    esp_zb_device_register(esp_zb_ep_list);
    esp_zb_device_add_set_attr_value_cb(attr_cb);

    ESP_ERROR_CHECK(esp_zb_start(true));
    esp_zb_main_loop_iteration();
}

void app_main(void)
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    /* Load Zigbee platform config to initialization */
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    /* Hardware related and device init */
    light_driver_init(LIGHT_DEFAULT_OFF);

    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
