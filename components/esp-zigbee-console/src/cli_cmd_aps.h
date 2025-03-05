/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include "cli_cmd.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct esp_zb_cli_aps_argtable_s {
    arg_addr_t *dst_addr;
    arg_u8_t   *dst_ep;
    arg_u8_t   *src_ep;
    arg_u16_t  *profile;
    arg_u16_t  *cluster;
} esp_zb_cli_aps_argtable_t;

void esp_zb_cli_fill_aps_argtable(esp_zb_cli_aps_argtable_t *aps);

esp_err_t esp_zb_cli_parse_aps_dst(esp_zb_cli_aps_argtable_t *parsed_argtable, esp_zb_addr_u *dst_addr_u,
                                   uint8_t *dst_endpoint, esp_zb_zcl_address_mode_t *address_mode,
                                   uint8_t *src_endpoint, uint16_t *cluster_id, uint16_t *profile_id);

#ifdef __cplusplus
}
#endif
