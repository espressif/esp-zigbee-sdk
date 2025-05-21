/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include <stdio.h>
#include <string.h>
#include <freertos/FreeRTOS.h>

#include "unity.h"
#include "esp_delta_ota.h"


extern const uint8_t base_bin_start[] asm("_binary_base_bin_start");
extern const uint8_t base_bin_end[]   asm("_binary_base_bin_end");
extern const uint8_t new_bin_end[]   asm("_binary_new_bin_end");
extern const uint8_t new_bin_start[] asm("_binary_new_bin_start");
extern const uint8_t patch_bin_start[] asm("_binary_patch_bin_start");
extern const uint8_t patch_bin_end[]   asm("_binary_patch_bin_end");
extern const uint8_t bad_patch_bin_start[] asm("_binary_bad_patch_bin_start");
extern const uint8_t bad_patch_bin_end[]   asm("_binary_bad_patch_bin_end");

static uint8_t output_buffer[1300] = {0};
static int output_index = 0;
static esp_err_t write_cb(const uint8_t *buf_p, size_t size)
{
    if (size <= 0) {
        return ESP_OK;
    }
    memcpy(output_buffer + output_index, buf_p, size);
    output_index += size;
    return ESP_OK;
}

static esp_err_t read_cb(uint8_t *buf_p, size_t size, int src_offset)
{

    if (size <= 0) {
        return ESP_ERR_INVALID_ARG;
    }
    memcpy(buf_p, base_bin_start + src_offset, size);
    return ESP_OK;
}

TEST_CASE("Sending full patch at once", "[esp_delta_ota]")
{
    memset(output_buffer, 0, 1000);
    output_index = 0;
    esp_delta_ota_cfg_t cfg = {
        .read_cb = &read_cb,
        .write_cb = &write_cb,
    };

    esp_delta_ota_handle_t handle = esp_delta_ota_init(&cfg);
    TEST_ASSERT_NOT_NULL(handle);

    esp_err_t err = esp_delta_ota_feed_patch(handle, patch_bin_start, patch_bin_end - patch_bin_start);
    TEST_ESP_OK(err);

    err = esp_delta_ota_finalize(handle);
    TEST_ESP_OK(err);

    err = esp_delta_ota_deinit(handle);
    TEST_ESP_OK(err);

    TEST_ASSERT_EQUAL_INT(0, memcmp(new_bin_start, output_buffer, new_bin_end - new_bin_start));
}

TEST_CASE("Applying wrong patch", "[esp_delta_ota]")
{
    memset(output_buffer, 0, 1000);
    output_index = 0;
    esp_delta_ota_cfg_t cfg = {
        .read_cb = &read_cb,
        .write_cb = &write_cb,
    };

    esp_delta_ota_handle_t handle = esp_delta_ota_init(&cfg);
    TEST_ASSERT_NOT_NULL(handle);

    esp_err_t err = esp_delta_ota_feed_patch(handle, bad_patch_bin_start, bad_patch_bin_end - bad_patch_bin_start);
    TEST_ESP_OK(err);

    err = esp_delta_ota_finalize(handle);
    TEST_ESP_OK(err);

    err = esp_delta_ota_deinit(handle);
    TEST_ESP_OK(err);

    TEST_ASSERT_NOT_EQUAL(0, memcmp(new_bin_start, output_buffer, new_bin_end - new_bin_start));
}

TEST_CASE("Sending 1 byte of patch at once", "[esp_delta_ota]")
{
    memset(output_buffer, 0, 1000);
    output_index = 0;
    esp_delta_ota_cfg_t cfg = {
        .read_cb = &read_cb,
        .write_cb = &write_cb,
    };

    esp_delta_ota_handle_t handle = esp_delta_ota_init(&cfg);
    TEST_ASSERT_NOT_NULL(handle);
    esp_err_t err = ESP_OK;

    for (int i = 0; i < patch_bin_end - patch_bin_start; i++) {
        err = esp_delta_ota_feed_patch(handle, patch_bin_start + i, 1);
        TEST_ESP_OK(err);
    }
    err = esp_delta_ota_finalize(handle);
    TEST_ESP_OK(err);

    err = esp_delta_ota_deinit(handle);
    TEST_ESP_OK(err);

    TEST_ASSERT_EQUAL_INT(0, memcmp(new_bin_start, output_buffer, output_index));
}
