/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>

#include "esp_err.h"
#include "esp_zigbee_type.h"

#ifdef __cplusplus
extern "C" {
#endif

const char* esp_zb_get_device_name_by_idx(uint16_t idx);

const char* esp_zb_get_device_name_by_id(uint16_t device_id);

uint16_t esp_zb_get_device_id_by_name(const char *name);

bool esp_zb_is_device_supported(uint16_t device_id);

esp_zb_cluster_list_t *esp_zb_ep_create_ha_default(uint16_t ha_device_id);

#ifdef __cplusplus
}
#endif