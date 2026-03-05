/*
 * SPDX-FileCopyrightText: 2025-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* NOTE: The APIs in this file are mainly for certification and tests.
 *       They are not stable and might change in the future.
 */

#pragma once

#include <ezbee/core.h>

#ifndef ESP_ZIGBEE_TEST_UTILS_H
#define ESP_ZIGBEE_TEST_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ezb_nwk_leave_req_s {
    ezb_extaddr_t device_address;
    bool rejoin : 1;
    bool remove_children : 1;
} ezb_nwk_leave_req_t;

ezb_err_t ezb_nwk_leave_request(const ezb_nwk_leave_req_t *req);

ezb_err_t ezb_cert_set_route_cost_policy(bool disable_in_out_cost_updating, bool delay_pending_tx_on_rrep, bool use_route_for_neighbor);

ezb_err_t ezb_nwk_set_neighbor_info(uint16_t short_addr, uint8_t age, uint8_t outgoing_cost, uint8_t incoming_cost);

ezb_err_t ezb_nwk_concentrator_start(uint8_t radius, uint8_t disc_sp_time, uint8_t disc_time);

ezb_err_t ezb_nwk_concentrator_stop(void);

ezb_err_t ezb_nwk_concentrator_discovery(void);

void ezb_nwk_route_delete(ezb_shortaddr_t dst_addr);

void ezb_nwk_route_delete_by_link(ezb_shortaddr_t nbr_addr);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_TEST_UTILS_H */
