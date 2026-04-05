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

#pragma once

#include "driver/temperature_sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Temperature sensor callback
 *
 * @param[in] temperature Temperature value in degrees Celsius from sensor
 *
 */
typedef void (*esp_temp_sensor_callback_t)(float temperature);

/**
 * @brief Initialize temperature sensor and set callback function
 *
 * @param config          Pointer of temperature sensor configuration.
 * @param update_interval Sensor value update interval.
 * @param cb              Callback function pointer.
 *
 * @return ESP_OK if the driver initialization succeed, otherwise ESP_FAIL.
 */
esp_err_t temp_sensor_driver_init(temperature_sensor_config_t *config, uint16_t update_interval, esp_temp_sensor_callback_t cb);

#ifdef __cplusplus
} // extern "C"
#endif
