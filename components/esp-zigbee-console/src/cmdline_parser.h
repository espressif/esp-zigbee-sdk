/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CLI_ADDR_TYPE_16BIT = 0,
    CLI_ADDR_TYPE_32BIT,
    CLI_ADDR_TYPE_64BIT,
} cli_addr_type_t;

typedef struct {
    cli_addr_type_t addr_type;
    union {
        uint16_t addr16; /* Parsed 16-bit address value */
        uint32_t addr32; /* Parsed 32-bit address value */
        uint64_t addr64; /* Parsed 64-bit address value */
        uint8_t  u8[8];  /* Raw address bytes */
    } u;
} cli_addr_t;

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
 * @brief Parse HEX string to @ref cli_addr_t
 *
 * @param[in] string A string contains the data in HEX.
 * @param[out] addr Parsed cli_addr_t structure.
 * @return
 *      - ESP_OK: Success
 *      - ESP_ERR_INVALID_ARG: Invalid arguments
 */
esp_err_t parse_addr(const char *string, cli_addr_t *addr);

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
