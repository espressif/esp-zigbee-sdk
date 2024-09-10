/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#define EXIT_ON_FALSE(a, err_code, ...) do {                                    \
        if (unlikely(!(a))) {                                                   \
            ret = err_code;                                                     \
            __VA_ARGS__;                                                        \
            goto exit;                                                          \
        }                                                                       \
    } while(0);

#define EXIT_ON_ERROR(x, ...) do {                                              \
        esp_err_t err_rc_ = (x);                                                \
        if (unlikely(err_rc_ != ESP_OK)) {                                      \
            ret = err_rc_;                                                      \
            __VA_ARGS__;                                                        \
            goto exit;                                                          \
        }                                                                       \
    } while(0);

#define EXIT_NOW(...) do {                                                      \
        __VA_ARGS__;                                                            \
        goto exit;                                                              \
    } while(0);

typedef int (*cli_output_element_func_t)(const void *, char *, size_t, void *);

void cli_output(const char *format, ...) __attribute__ ((format (printf, 1, 2)));
void cli_output_line(const char *line);
void cli_output_array(const char *arr_name, void *array, size_t arr_cnt, size_t element_size,
                      cli_output_element_func_t write_element, void *user_ctx);
void cli_output_array_u8(const char *arr_name, uint8_t *array, size_t arr_cnt, const char *format);
void cli_output_array_u16(const char *arr_name, uint16_t *array, size_t arr_cnt, const char *format);
void cli_output_table_header(uint8_t column_num, const char *const *titles, const uint8_t *widths);
void cli_output_buffer(const void *buffer, uint16_t buff_len);

#ifdef __cplusplus
}
#endif