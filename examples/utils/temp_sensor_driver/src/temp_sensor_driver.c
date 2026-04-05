/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee temperature sensor driver example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include "temp_sensor_driver.h"

#include "esp_err.h"
#include "esp_check.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**
 * @brief:
 * This example code shows how to configure temperature sensor.
 *
 * @note:
 * The callback will be called with updated temperature sensor value every $interval seconds.
 *
 */

/* temperature sensor handler */
static temperature_sensor_handle_t temp_sensor;
/* callback function pointer */
static esp_temp_sensor_callback_t sensor_cb;
/* update interval in second */
static uint16_t interval = 1;

static const char *TAG = "ESP_TEMP_SENSOR_DRIVER";

static void temp_sensor_driver_update(void *arg)
{
    for (;;) {
        float tsens_value;
        temperature_sensor_get_celsius(temp_sensor, &tsens_value);
        if (sensor_cb) {
            sensor_cb(tsens_value);
        }
        vTaskDelay(pdMS_TO_TICKS(interval * 1000));
    }
}

static esp_err_t temp_sensor_driver_sensor_init(temperature_sensor_config_t *config)
{
    ESP_RETURN_ON_ERROR(temperature_sensor_install(config, &temp_sensor), TAG, "Failed to install on-chip temperature sensor");
    ESP_RETURN_ON_ERROR(temperature_sensor_enable(temp_sensor), TAG, "Failed to enable on-chip temperature sensor");
    return (xTaskCreate(temp_sensor_driver_update, "sensor_update", 2048, NULL, 10, NULL) == pdTRUE) ? ESP_OK : ESP_FAIL;
}

esp_err_t temp_sensor_driver_init(temperature_sensor_config_t *config, uint16_t update_interval, esp_temp_sensor_callback_t cb)
{
    if (ESP_OK != temp_sensor_driver_sensor_init(config)) {
        return ESP_FAIL;
    }
    sensor_cb = cb;
    interval = update_interval;
    return ESP_OK;
}
