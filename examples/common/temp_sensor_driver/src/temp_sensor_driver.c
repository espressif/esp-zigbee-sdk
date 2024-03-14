/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
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

/* temperatuer sensor instance handle */
static temperature_sensor_handle_t temp_sensor;
/* call back function pointer */
static esp_temp_sensor_callback_t func_ptr;
/* update interval in seconds */
static uint16_t interval = 1;

static const char *TAG = "ESP_TEMP_SENSOR_DRIVER";

/**
 * @brief Tasks for updating the sensor value
 *
 * @param arg      Unused value.
 */
static void temp_sensor_driver_value_update(void *arg)
{
    for (;;) {
        float tsens_value;
        temperature_sensor_get_celsius(temp_sensor, &tsens_value);
        if (func_ptr) {
            func_ptr(tsens_value);
        }
        vTaskDelay(pdMS_TO_TICKS(interval * 1000));
    }
}

/**
 * @brief init temperature sensor
 *
 * @param config      pointer of temperature sensor config.
 */
static esp_err_t temp_sensor_driver_sensor_init(temperature_sensor_config_t *config)
{
    ESP_RETURN_ON_ERROR(temperature_sensor_install(config, &temp_sensor),
                        TAG, "Fail to install on-chip temperature sensor");
    ESP_RETURN_ON_ERROR(temperature_sensor_enable(temp_sensor),
                        TAG, "Fail to enable on-chip temperature sensor");
    return (xTaskCreate(temp_sensor_driver_value_update, "sensor_update", 2048, NULL, 10, NULL) == pdTRUE) ? ESP_OK : ESP_FAIL;
}

esp_err_t temp_sensor_driver_init(temperature_sensor_config_t *config, uint16_t update_interval,
                             esp_temp_sensor_callback_t cb)
{
    if (ESP_OK != temp_sensor_driver_sensor_init(config)) {
        return ESP_FAIL;
    }
    func_ptr = cb;
    interval = update_interval;
    return ESP_OK;
}
