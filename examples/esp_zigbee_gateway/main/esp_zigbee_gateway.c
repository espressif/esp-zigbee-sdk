/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee Gateway Example
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
#include "esp_vfs_eventfd.h"
#include "esp_spiffs.h"
#include "nvs_flash.h"
#include "esp_rcp_update.h"
#include "esp_zigbee_gateway.h"

#if (!defined ZB_MACSPLIT_HOST && defined ZB_MACSPLIT_DEVICE)
#error Only Zigbee gateway host device should be defined
#endif

static const char *TAG = "ESP_ZB_GATEWAY";

/********************* Define functions **************************/
static void esp_zb_gateway_update_rcp(void)
{
    /* Deinit uart to transfer UART to the serial loader */
    esp_zb_macsplit_uart_deinit();
    if (esp_rcp_update() != ESP_OK) {
        esp_rcp_mark_image_verified(false);
    }
    esp_restart();
}

static void esp_zb_gateway_board_try_update(const char *rcp_version_str)
{
    char version_str[RCP_VERSION_MAX_SIZE];
    if (esp_rcp_load_version_in_storage(version_str, sizeof(version_str)) == ESP_OK) {
        ESP_LOGI(TAG, "RCP Version in Zigbee Gateway storage:%s", version_str);
        if (strcmp(version_str, rcp_version_str)) {
            ESP_LOGI(TAG, "*** NOT MATCH VERSION! ***");
            esp_zb_gateway_update_rcp();
        } else {
            ESP_LOGI(TAG, "*** MATCH VERSION! ***");
            esp_rcp_mark_image_verified(true);
        }
    } else {
        ESP_LOGI(TAG, "RCP firmware not found in storage, will reboot to try next image");
        esp_rcp_mark_image_verified(false);
        esp_restart();
    }
}

static void bdb_start_top_level_commissioning_cb(uint8_t mode_mask)
{
    ESP_ERROR_CHECK(esp_zb_bdb_start_top_level_commissioning(mode_mask));
}

static esp_err_t init_spiffs(void)
{
    esp_vfs_spiffs_conf_t rcp_fw_conf = {
        .base_path = "/rcp_fw", .partition_label = "rcp_fw", .max_files = 10, .format_if_mount_failed = false
    };
    esp_vfs_spiffs_register(&rcp_fw_conf);
    return ESP_OK;
}


void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p       = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    esp_zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;
    esp_zb_zdo_signal_macsplit_dev_boot_params_t *rcp_version = NULL;

    switch (sig_type) {
    case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Zigbee stack initialized");
        esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_INITIALIZATION);
        break;
    case ESP_ZB_MACSPLIT_DEVICE_BOOT:
        ESP_LOGI(TAG, "Zigbee rcp device booted");
        rcp_version = (esp_zb_zdo_signal_macsplit_dev_boot_params_t*)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "Running RCP Version:%s", rcp_version->version_str);
#if(CONFIG_ZIGBEE_GW_AUTO_UPDATE_RCP)
        esp_zb_gateway_board_try_update(rcp_version->version_str);
#endif
        break;
    case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Start network formation");
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_FORMATION);
        } else {
            ESP_LOGE(TAG, "Failed to initialize Zigbee stack (status: %d)", err_status);
        }
        break;
    case ESP_ZB_BDB_SIGNAL_FORMATION:
        if (err_status == ESP_OK) {
            esp_zb_ieee_addr_t ieee_address;
            esp_zb_get_long_address(ieee_address);
            ESP_LOGI(TAG, "Formed network successfully (ieee extended address: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx)",
                     ieee_address[7], ieee_address[6], ieee_address[5], ieee_address[4],
                     ieee_address[3], ieee_address[2], ieee_address[1], ieee_address[0],
                     esp_zb_get_pan_id());
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_STEERING);
        } else {
            ESP_LOGI(TAG, "Restart network formation (status: %d)", err_status);
            esp_zb_scheduler_alarm((esp_zb_callback_t)bdb_start_top_level_commissioning_cb, ESP_ZB_BDB_MODE_NETWORK_FORMATION, 1000);
        }
        break;
    case ESP_ZB_BDB_SIGNAL_STEERING:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Network steering started");
        }
        break;
    case ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE:
        dev_annce_params = (esp_zb_zdo_signal_device_annce_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->device_short_addr);
        break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %d, status: %d", sig_type, err_status);
        break;
    }
}

void rcp_error_handler(uint8_t connect_timeout)
{
    ESP_LOGI(TAG, "RCP connection failed timeout:%d seconds", connect_timeout);
#if(CONFIG_ZIGBEE_GW_AUTO_UPDATE_RCP)
    ESP_LOGI(TAG, "Timeout! Re-flashing RCP");
    esp_zb_gateway_update_rcp();
#endif
}

static void esp_zb_task(void *pvParameters)
{
    /* initialize Zigbee stack with Zigbee coordinator config */
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZC_CONFIG();
    esp_zb_init(&zb_nwk_cfg);
    /* initiate Zigbee Stack start without zb_send_no_autostart_signal auto-start */
    ESP_ERROR_CHECK(esp_zb_start(false));
    esp_zb_add_rcp_failure_cb(rcp_error_handler);
    esp_zb_main_loop_iteration();
    esp_rcp_update_deinit();
    vTaskDelete(NULL);
}

void app_main(void)
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    /* load Zigbee gateway platform config to initialization */
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
#if(CONFIG_ZIGBEE_GW_AUTO_UPDATE_RCP)
    esp_rcp_update_config_t rcp_update_config = ESP_ZB_RCP_UPDATE_CONFIG();
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(init_spiffs());
    ESP_ERROR_CHECK(esp_rcp_update_init(&rcp_update_config));
#endif
    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
