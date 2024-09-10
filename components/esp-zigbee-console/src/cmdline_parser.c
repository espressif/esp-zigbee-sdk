/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "esp_check.h"
#include "esp_zigbee_core.h"

#include "cmdline_parser.h"

#define TAG ""

static esp_err_t parse_digit(char digit_char, uint8_t *value)
{
    ESP_RETURN_ON_FALSE(('0' <= digit_char) && (digit_char <= '9'), ESP_ERR_INVALID_ARG, TAG, "Invalid digit char");
    *value = (uint8_t)(digit_char - '0');

    return ESP_OK;
}

static esp_err_t parse_hex_digit(char hex_char, uint8_t *value)
{
    esp_err_t error = ESP_OK;

    if (('A' <= hex_char) && (hex_char <= 'F')) {
        *value = (uint8_t)(hex_char - 'A' + 10);
    } else if (('a' <= hex_char) && (hex_char <= 'f')) {
        *value = (uint8_t)(hex_char - 'a' + 10);
    } else {
        error = parse_digit(hex_char, value);
    }

    return error;
}

esp_err_t parse_u64(const char *string, uint64_t *value_u64)
{
    uint64_t value = 0;
    const char *cur = string;
    bool is_hex = false;

    enum {
        Max_Hex_Before_Overflow = (0xffffffffffffffffULL / 16),
        Max_Dec_Before_Overflow = (0xffffffffffffffffULL / 10),
    };

    ESP_RETURN_ON_FALSE(string != NULL, ESP_ERR_INVALID_ARG, TAG, "Invalid string");

    if (cur[0] == '0' && (cur[1] == 'x' || cur[1] == 'X')) {
        cur += 2;
        is_hex = true;
    }

    do {
        uint8_t  digit;

        ESP_RETURN_ON_ERROR(is_hex ? parse_hex_digit(*cur, &digit) : parse_digit(*cur, &digit),
                            TAG, "Fail to parse single char, wrong format");
        ESP_RETURN_ON_FALSE(value <= (is_hex ? Max_Hex_Before_Overflow : Max_Dec_Before_Overflow), ESP_ERR_INVALID_SIZE,
                            TAG, "Overflow uint64");
        value = (is_hex ? (value << 4) : (value * 10)) + digit;
        cur++;
    } while (*cur != '\0');

    *value_u64 = value;

    return ESP_OK;
}

esp_err_t parse_u32(const char *string, uint32_t *value_u32)
{
    uint64_t value;
    ESP_RETURN_ON_ERROR(parse_u64(string, &value), TAG, "Fail to parse");
    ESP_RETURN_ON_FALSE(value <= UINT32_MAX, ESP_ERR_INVALID_SIZE, TAG, "Overflow uint32");
    *value_u32 = value;
    return ESP_OK;
}

esp_err_t parse_u16(const char *string, uint16_t *value_u16)
{
    uint64_t value;
    ESP_RETURN_ON_ERROR(parse_u64(string, &value), TAG, "Fail to parse");
    ESP_RETURN_ON_FALSE(value <= UINT16_MAX, ESP_ERR_INVALID_SIZE, TAG, "Overflow uint16");
    *value_u16 = value;
    return ESP_OK;
}

esp_err_t parse_u8(const char *string, uint8_t *value_u8)
{
    uint64_t value;
    ESP_RETURN_ON_ERROR(parse_u64(string, &value), TAG, "Fail to parse");
    ESP_RETURN_ON_FALSE(value <= UINT8_MAX, ESP_ERR_INVALID_SIZE, TAG, "Overflow uint8");
    *value_u8 = value;
    return ESP_OK;
}

esp_err_t parse_hex_str(const char *string, uint8_t *buffer, size_t buffer_size, size_t* out_size)
{
    esp_err_t ret = ESP_OK;
    int idx = 0;
    const char *cur = string;

    ESP_GOTO_ON_FALSE(string, ESP_ERR_INVALID_ARG, exit, TAG, "Invalid string");
    /* We require HEX string to have prefix '0x' or '0X' */
    ESP_GOTO_ON_FALSE(cur[0] == '0' && (cur[1] == 'x' || cur[1] == 'x'), ESP_ERR_INVALID_ARG, exit, TAG, "Invalid HEX string prefix");
    ESP_GOTO_ON_FALSE(buffer, ESP_ERR_INVALID_ARG, exit, TAG, "Invalid buffer");
    ESP_GOTO_ON_FALSE(buffer_size, ESP_ERR_INVALID_ARG, exit, TAG, "Invalid buffer size");

    cur += 2;
    memset(buffer, 0, buffer_size);

    do {
        uint8_t nibble_l = 0;
        uint8_t nibble_h = 0;

        ESP_GOTO_ON_ERROR(parse_hex_digit(*cur++, &nibble_h), exit, TAG, "Invalid HEX format");
        ESP_GOTO_ON_ERROR(parse_hex_digit(*cur++, &nibble_l), exit, TAG, "Invalid HEX format");
        if (idx < buffer_size) {
            buffer[idx] = (nibble_h << 4) + nibble_l;
        }
        idx++;
    } while (*cur != '\0');

    if (idx > buffer_size ) {
        ret = ESP_ERR_INVALID_SIZE;
    }

exit:
    if (out_size != NULL) {
        *out_size = idx;
    }
    return ret;
}

esp_err_t parse_ieee_addr(const char *string, esp_zb_ieee_addr_t ieee_addr)
{
#define DATA_SIZE sizeof(esp_zb_ieee_addr_t)
    uint8_t temp[DATA_SIZE] = {0};
    size_t parsed = 0;
    ESP_RETURN_ON_ERROR(parse_hex_str(string, temp, DATA_SIZE, &parsed), TAG, "Fail to parse HEX data");
    if (parsed != DATA_SIZE) {
        return ESP_ERR_INVALID_SIZE;
    }
    /* Reverse the result */
    for (int i = 0; i < DATA_SIZE; i++) {
        ((uint8_t*)ieee_addr)[i] = temp[DATA_SIZE - 1 - i];
    }
    return ESP_OK;
}

esp_err_t parse_zcl_addr(const char *string, esp_zb_zcl_addr_t *addr)
{
    esp_err_t ret = parse_ieee_addr(string, addr->u.ieee_addr);
    if (ret == ESP_OK) {
        addr->addr_type = ESP_ZB_ZCL_ADDR_TYPE_IEEE;
    } else {
        uint16_t short_addr = 0;
        ret = parse_u16(string, &short_addr);
        if (ret == ESP_OK) {
            addr->u.short_addr = short_addr;
            addr->addr_type = ESP_ZB_ZCL_ADDR_TYPE_SHORT;
        }
    }

    return ret;
}

esp_err_t parse_attr_access(const char *string, uint8_t *access)
{
    uint8_t tmp_access = 0;
    const char *cur = string;

    ESP_RETURN_ON_FALSE(string != NULL, ESP_ERR_INVALID_ARG, TAG, "Invalid string");

    do {
        switch (*cur) {
            case 'R':
            case 'r':
                tmp_access |= ESP_ZB_ZCL_ATTR_ACCESS_READ_ONLY;
                break;
            case 'W':
            case 'w':
                tmp_access |= ESP_ZB_ZCL_ATTR_ACCESS_WRITE_ONLY;
                break;
            case 'P':
            case 'p':
                tmp_access |= ESP_ZB_ZCL_ATTR_ACCESS_REPORTING;
                break;
            case 'S':
            case 's':
                tmp_access |= ESP_ZB_ZCL_ATTR_ACCESS_SCENE;
                break;
            default:
                ESP_RETURN_ON_ERROR(ESP_ERR_INVALID_ARG, TAG, "Invalid attr access: '%c'", *cur);
                break;
        }
        cur++;
    } while (*cur != '\0');

    *access = tmp_access;

    return ESP_OK;
}
