/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "esp_zigbee_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Parse string to uint64_t
 *
 * @param[in] string A string contains the content to be parsed.
 * @param[out] value_u64 Parsed value
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Wrong format
 *      - ESP_ERR_INVALID_SIZE: Value overflows
 */
esp_err_t parse_u64(const char *string, uint64_t *value_u64);

/**
 * @brief Parse string to uint32_t
 *
 * @param[in] string A string contains the content to be parsed.
 * @param[out] value_u32 Parsed value
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Wrong format
 *      - ESP_ERR_INVALID_SIZE: Value overflows
 */
esp_err_t parse_u32(const char *string, uint32_t *value_u32);

/**
 * @brief Parse string to uint16_t
 *
 * @param[in] string A string contains the content to be parsed.
 * @param[out] value_u16 Parsed value
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Wrong format
 *      - ESP_ERR_INVALID_SIZE: Value overflows
 */
esp_err_t parse_u16(const char *string, uint16_t *value_u16);

/**
 * @brief Parse string to uint8_t
 *
 * @param[in] string A string contains the content to be parsed.
 * @param[out] value_u8 Parsed value
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Wrong format
 *      - ESP_ERR_INVALID_SIZE: Value overflows
 */
esp_err_t parse_u8(const char *string, uint8_t *value_u8);

/**
 * @brief Parse HEX string to data in the buffer
 *
 * @param[in] string A string contains the data in HEX.
 * @param[out] buffer Buffer to put the parsed data.
 * @param[in] buffer_size Buffer size of the provided buffer.
 * @param[out] out_size Length of data.
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Invalid arguments
 *      - ESP_ERR_INVALID_SIZE: Insufficient buffer provided
 */
esp_err_t parse_hex_str(const char *string, uint8_t *buffer, size_t buffer_size, size_t* out_size);

/**
 * @brief Parse HEX string to IEEE address
 *
 * @param[in] string A string contains the data in HEX.
 * @param[out] ieee_addr Parsed IEEE address.
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Invalid arguments
 *      - ESP_ERR_INVALID_SIZE: Wrong string length
 */
esp_err_t parse_ieee_addr(const char *string, esp_zb_ieee_addr_t ieee_addr);

/**
 * @brief Parse HEX string to @ref esp_zb_zcl_addr_t
 *
 * @param[in] string A string contains the data in HEX.
 * @param[out] addr Parsed esp_zb_zcl_addr_t structure.
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Invalid arguments
 */
esp_err_t parse_zcl_addr(const char *string, esp_zb_zcl_addr_t *addr);

/**
 * @brief Parse setting string to attribute access value
 *
 * @param[in] string A string contains the attribute access settings.
 * @param[out] access Parsed attribute access value
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Wrong setting
 */
esp_err_t parse_attr_access(const char *string, uint8_t *access);

#ifdef __cplusplus
}
#endif