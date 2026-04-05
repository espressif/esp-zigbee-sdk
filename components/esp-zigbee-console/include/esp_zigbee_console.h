/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "esp_zigbee.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize ESP Zigbee Console.
 *
 * @return ESP_OK on success, error code otherwise.
 */
esp_err_t esp_zb_console_init(void);

/**
 * @brief Start ESP Zigbee Console.
 *
 * @return ESP_OK on success, error code otherwise.
 */
esp_err_t esp_zb_console_start(void);

/**
 * @brief Stop and de-init ESP Zigbee Console.
 *
 * @return ESP_OK on success, error code otherwise.
 */
esp_err_t esp_zb_console_deinit(void);

/**
 * @brief Enable ESP Zigbee Console to manage the endpoint list.
 *
 * The function enables the ESP Zigbee Console to add/show/register
 * ZCL data model with `dm` command.
 *
 * @param device_desc User defined device descriptor, NULL means an empty device.
 * @return ESP_OK on success, error code otherwise.
 */
esp_err_t esp_zb_console_manage_ep_list(ezb_af_device_desc_t device_desc);

#ifdef __cplusplus
}
#endif
