/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include "esp_zigbee_core.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t cli_zcl_core_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message);

#ifdef __cplusplus
}
#endif