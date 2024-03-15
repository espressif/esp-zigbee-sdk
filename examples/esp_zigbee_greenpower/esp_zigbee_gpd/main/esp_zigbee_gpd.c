/*
 * SPDX-FileCopyrightText: 2021-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee Green Power device Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */
#include "esp_check.h"
#include "nvs_flash.h"
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "zgp/esp_zigbee_zgpd.h"
#include "esp_zigbee_gpd.h"

#if !CONFIG_ZB_ZGPD
#error define CONFIG_ZB_ZGPD to compile ZGPD exmaple
#endif

static const char *TAG = "ESP_ZGP_DEVICE";

static switch_func_pair_t button_func_pair[] = {
    {GPIO_INPUT_IO_TOGGLE_SWITCH, SWITCH_ONOFF_TOGGLE_CONTROL}
};
static uint8_t g_zb_zgpd_cmd[] = ESP_ZB_ZGPD_APP_INFO_CMD;
static uint8_t g_zb_zgpd_security_key[] = ESP_ZB_ZGPD_SECURITY_KEY;

static void device_init()
{
    esp_zb_zgpd_init(ESP_ZB_ZGP_APP_ID_0000, ESP_ZB_ZGPD_COMMISSIONING_UNIDIR, ESP_ZB_ZGP_ON_OFF_SWITCH_DEV_ID);
    esp_zb_zgpd_set_source_id(ESP_ZB_ZGPD_SRC_ID);
    esp_zb_zgpd_set_security(ESP_ZB_ZGP_SEC_LEVEL_FULL_NO_ENC, ESP_ZB_ZGP_SEC_KEY_TYPE_ZGPD_INDIVIDUAL, g_zb_zgpd_security_key);
    esp_zb_zgpd_set_OOB_key(g_zb_zgpd_security_key);
    esp_zb_zgpd_set_channel(ESP_ZB_ZGPD_CHANNEL);
    esp_zb_zgpd_set_security_frame_counter(ESP_ZB_ZGPD_FRAMER_COUNTER);
    esp_zb_zgpd_set_application_info_present(1);
    esp_zb_zgpd_config_application_info_cmd(1, g_zb_zgpd_cmd);
}

static void zb_buttons_handler(switch_func_pair_t *button_func_pair)
{
    static uint8_t press_start_commission = 1;
    if (button_func_pair->func == SWITCH_ONOFF_TOGGLE_CONTROL) {
        if (press_start_commission) {
            ESP_EARLY_LOGI(TAG, "Start commissioning");
            esp_zb_zgpd_start_commissioning();
            press_start_commission = 0;
        } else {
            ESP_EARLY_LOGI(TAG, "ZGPD send toggle command");
            esp_zb_zgpd_send_command(ESP_ZB_GPDF_CMD_TOGGLE);
        }
    }
}

static esp_err_t deferred_driver_init(void)
{
    ESP_RETURN_ON_FALSE(switch_driver_init(button_func_pair, PAIR_SIZE(button_func_pair), zb_buttons_handler), ESP_FAIL, TAG,
                        "Failed to initialize switch driver");
    return ESP_OK;
}

static void zb_zgpd_signal_handler(esp_zb_zgpd_signal_t signal, esp_err_t error)
{
    switch(signal) {
        case ESP_ZB_ZGPD_SIGNAL_DEVICE_STARTED_UP:
            if (error == ESP_OK) {
                ESP_LOGI(TAG, "Deferred driver initialization %s", deferred_driver_init() ? "failed" : "successful");
                ESP_LOGI(TAG, "ZGPD device started successfully");
                device_init();
                ESP_LOGI(TAG, " Wait to press the button to start commissioning ...");
            } else {
                ESP_LOGI(TAG, "ZGPD Device started failed");
            }
        break;
        case ESP_ZB_ZGPD_SIGNAL_COMMISSIONING:
            if(error == ESP_OK){
                ESP_LOGI(TAG, "Commissioning success");
            } else {
                ESP_LOGI(TAG, "Commissioning failed");
            }
        break;
        default:
            ESP_LOGW(TAG, "Unknown signal: 0x%x", signal);
        break;
    }
}

static void esp_zb_task(void *pvParameters)
{
    /* initialize Zigbee stack */
    esp_zb_zgpd_stack_init(zb_zgpd_signal_handler);

    esp_zb_zgpd_init(ESP_ZB_ZGP_APP_ID_0000, ESP_ZB_ZGPD_COMMISSIONING_UNIDIR, ESP_ZB_ZGP_ON_OFF_SWITCH_DEV_ID);
    esp_zb_zgpd_set_source_id(ESP_ZB_ZGPD_SRC_ID);
    esp_zb_zgpd_set_security(ESP_ZB_ZGP_SEC_LEVEL_FULL_WITH_ENC, ESP_ZB_ZGP_SEC_KEY_TYPE_ZGPD_INDIVIDUAL, g_zb_zgpd_security_key);

    if (esp_zb_zgpd_dev_start()) {
        ESP_LOGI(TAG, "Device started failed");
    } else {
        esp_zb_zgpd_main_loop();
    }
}

void app_main()
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
