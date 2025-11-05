/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <stdarg.h>

#include "esp_log.h"
#include "esp_idf_version.h"

#define LOG_LEVEL_LEN   3U
#define LOG_LEVEL_MASK  ((1U << LOG_LEVEL_LEN) - 1U)
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 5, 0)
/* Declare the `esp_log()` symbol to ensure compatibility with the new `esp_log()` feature introduced in
ESP-IDF v5.5.0 for lower versions. */
void esp_log(uint32_t config, const char *tag, const char *format, ...)
{

    va_list args;
    va_start(args, format);
    esp_log_writev((config & LOG_LEVEL_MASK), tag, format, args);
    va_end(args);
}
#else
static_assert(LOG_LEVEL_LEN == ESP_LOG_LEVEL_LEN, "ESP_LOG_LEVEL_LEN has been changed!");
#endif
