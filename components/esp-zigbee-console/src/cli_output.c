/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdarg.h>
#include <string.h>

#include "esp_log.h"

#include "cli_util.h"

void cli_output(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void cli_output_newline()
{
    cli_output("\n");
}

void cli_output_line(const char *line)
{
    cli_output("%s\n", line);
}

void cli_output_array(const char *arr_name, void *array, size_t arr_cnt, size_t element_size,
                      cli_output_element_func_t write_element, void *user_ctx)
{
#define LINE_WIDTH          128
#define LINE_REMAIN(s, c)   (LINE_WIDTH - (c - s))

    char line[LINE_WIDTH];
    char *cur = line;

    uint8_t *element = array;

    cur += snprintf(line, LINE_REMAIN(line, cur), "%s: [", arr_name);

    for (int idx = 0; idx < arr_cnt; idx++) {
        cur += write_element(element, cur, LINE_REMAIN(line, cur), user_ctx);
        if (LINE_REMAIN(line, cur) < 2) {
            cur -= 5; /* spaces for "...]\0" */
            cur += snprintf(line, LINE_REMAIN(line, cur), "...");
            break;
        }
        element += element_size;
        *cur++ = ',';
        *cur++ = ' ';
    }

    if (arr_cnt > 0) {
        cur -= 2;
    }

    *cur++ = ']';
    *cur++ = '\0';

    cli_output_line(line);
}

static int write_u8(const uint8_t *pval, char *buf, size_t buf_size, const char *format)
{
    return snprintf(buf, buf_size, format, *pval);
}

static int write_u16(const uint16_t *pval, char *buf, size_t buf_size, const char *format)
{
    return snprintf(buf, buf_size, format, *pval);
}

void cli_output_array_u8(const char *arr_name, uint8_t *array, size_t arr_cnt, const char *format)
{
    cli_output_array(arr_name, array, arr_cnt, sizeof(*array), (cli_output_element_func_t)&write_u8, (void*)format);
}

void cli_output_array_u16(const char *arr_name, uint16_t *array, size_t arr_cnt, const char *format)
{
    cli_output_array(arr_name, array, arr_cnt, sizeof(*array), (cli_output_element_func_t)&write_u16, (void*)format);
}

void cli_output_table_separator(uint8_t column_num, const uint8_t *widths)
{
    for (uint8_t index = 0; index < column_num; index++) {
        cli_output("+");
        for (uint8_t width = widths[index]; width != 0; width--) {
            cli_output("-");
        }
    }
    cli_output_line("+");
}

void cli_output_table_header(uint8_t column_num, const char *const *titles, const uint8_t *widths)
{
    for (uint8_t index = 0; index < column_num; index++) {
        const char *title = titles[index];
        uint8_t width = widths[index];
        size_t title_length = strlen(title);

        if (title_length + 2 <= width) {
            /* Use left aligned style with spaces when there are enough spaces
             * for `title` ("| Title    |"). */
            cli_output("| %*s", -(int)(width - 1), title);
        } else {
            /* Use narrow style and write as many chars from `title` as it can
             * fit in the given column width ("|Title|"). */
            cli_output("|%*.*s", -(int)(width), width, title);
        }
    }

    cli_output_line("|");
    cli_output_table_separator(column_num, widths);
}

void cli_output_buffer(const void *buffer, uint16_t buff_len)
{
    ESP_LOG_BUFFER_HEXDUMP("", buffer, buff_len, ESP_LOG_INFO);
}
