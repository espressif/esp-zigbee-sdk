/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#pragma once

#include "esp_err.h"
#include "esp_rcp_update.h"

esp_err_t esp_zigbee_rcp_init(esp_rcp_update_config_t *config);

void esp_zigbee_rcp_deinit(void);

esp_err_t esp_zigbee_rcp_update(void);
