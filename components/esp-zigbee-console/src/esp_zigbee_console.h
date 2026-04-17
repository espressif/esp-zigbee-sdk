/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"

#include_next "esp_zigbee_console.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct esp_zb_cli_context_s {
    ezb_af_device_desc_t ep_list;
} esp_zb_cli_context_t;

esp_zb_cli_context_t *esp_zb_console_get_cli_ctx(void);

#define CLI_CTX() (*esp_zb_console_get_cli_ctx())

esp_err_t esp_zb_console_notify_result(ezb_err_t result);

#ifdef __cplusplus
}
#endif
