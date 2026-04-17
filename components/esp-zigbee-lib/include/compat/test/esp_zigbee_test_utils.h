/*
 * SPDX-FileCopyrightText: 2025-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/test_utils.h" instead!"

#include <ezbee/test_utils.h>

#define esp_zb_cert_set_route_cost_policy(disable_in_out_cost_updating, delay_pending_tx_on_rresp, use_route_for_neighbor) \
    TO_ESP_ERR(ezb_cert_set_route_cost_policy(disable_in_out_cost_updating, delay_pending_tx_on_rresp, use_route_for_neighbor))

#define esp_zb_nwk_set_neighbor_info(short_addr, age, c_o, c_i) TO_ESP_ERR(ezb_nwk_set_neighbor_info(short_addr, age, c_o, c_i))
#define esp_zb_nwk_route_delete(dst_addr)                       ezb_nwk_route_delete(dst_addr)
#define esp_zb_nwk_route_delete_by_link(nbr_addr)               ezb_nwk_route_delete_by_link(nbr_addr)
#define esp_zb_nwk_start_concentrator_mode(radius, disc_time)   TO_ESP_ERR(ezb_nwk_concentrator_start(radius, 0, disc_time))
#define esp_zb_nwk_stop_concentrator_mode()                     TO_ESP_ERR(ezb_nwk_concentrator_stop())

#else
#error "This file is for compatibility, please include "ezbee/test_utils.h"!"
#endif
