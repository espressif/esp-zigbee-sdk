/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"

/**
 * @brief Set the maximum MAC transaction persistence time.
 *
 * @param us Maximum persistence time in microseconds, its value SHALL be within the range [0, 0x3BFFC400].
 * @return
 *      - ESP_OK: Operation successful
 *      - ESP_ERR_NO_MEM: Memory allocation failed
 *      - ESP_ERR_INVALID_ARG: Invalid argument
 *      - Others: Operation failed
 */
esp_err_t esp_zb_mac_set_transaction_persistence_time(uint32_t us);

/**
 * @brief Get the maximum MAC transaction persistence time.
 *
 * @return The maximum persistence time in microseconds. If the value is UINT32_MAX, the operation failed.
 */
uint32_t esp_zb_mac_get_transaction_persistence_time(void);

#ifdef __cplusplus
}
#endif
