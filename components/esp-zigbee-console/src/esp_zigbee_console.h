/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include_next "esp_zigbee_console.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct esp_zb_cli_context_s {
    esp_zb_ep_list_t *ep_list;
} esp_zb_cli_context_t;

esp_zb_cli_context_t *esp_zb_console_get_cli_ctx(void);

#define CLI_CTX() (*esp_zb_console_get_cli_ctx())

esp_err_t esp_zb_console_notify_result(esp_err_t result);

#ifdef __cplusplus
}
#endif