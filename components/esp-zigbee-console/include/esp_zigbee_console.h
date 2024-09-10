/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_core.h"

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
 * @param ep_list   User defined endpoint list, NULL means an empty list.
 * @return ESP_OK on success, error code otherwise.
 */
esp_err_t esp_zb_console_manage_ep_list(esp_zb_ep_list_t *ep_list);

#ifdef __cplusplus
}
#endif
