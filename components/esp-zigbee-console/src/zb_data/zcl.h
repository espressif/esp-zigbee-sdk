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

const char* esp_zb_get_cluster_name_by_idx(uint16_t idx);

const char* esp_zb_get_cluster_name_by_id(uint16_t cluster_id);

uint16_t esp_zb_get_cluster_id_by_name(const char *name);

esp_zb_attribute_list_t *esp_zb_cluster_create_default(uint16_t cluster_id);

esp_err_t esp_zb_cluster_add_std_attr(esp_zb_attribute_list_t *attr_list, uint16_t attr_id, void *value_p);

esp_err_t esp_zb_cluster_register(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);

#ifdef __cplusplus
}
#endif