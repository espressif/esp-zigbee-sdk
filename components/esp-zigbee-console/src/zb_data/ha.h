/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "ezbee/zha.h"

#ifdef __cplusplus
extern "C" {
#endif

const char *ezb_get_device_name_by_idx(uint16_t idx);

const char *ezb_get_device_name_by_id(uint16_t device_id);

uint16_t ezb_get_device_id_by_name(const char *name);

bool ezb_is_device_supported(uint16_t device_id);

ezb_af_ep_desc_t ezb_ep_create_ha_default(uint8_t ep_id, uint16_t ha_device_id);

/* Remove it, when argtable_ext.c is supported */
uint16_t esp_zb_get_device_id_by_name(const char *name);

#ifdef __cplusplus
}
#endif
