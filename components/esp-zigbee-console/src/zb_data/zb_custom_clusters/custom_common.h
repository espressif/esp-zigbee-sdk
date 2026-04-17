/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee.h"

#define EZB_ZHA_CUSTOM_TEST_TOOL_DEVICE_ID 0xfff3

#ifdef __cplusplus
extern "C" {
#endif

ezb_af_ep_desc_t ezb_zha_create_custom_test_tool(uint8_t ep_id, void *cfg);

#ifdef __cplusplus
}
#endif
