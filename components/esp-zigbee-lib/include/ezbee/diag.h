/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_DIAG_H
#define ESP_ZIGBEE_DIAG_H

#include <ezbee/core.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Expose the TCLK or APLK (Debug only).
 *
 * Expose the link key of the device to the network by broadcasting a non-standard NWK report (Report ID 6).
 * Some network protocol analyzers (e.g. Wireshark) understands that report and use the key to decode the traffic.
 *
 * @note
 *    - The function is only used for debugging purposes. It must be explicitly called by the application.
 *    - This function is only available in debug build and does nothing in release build.
 *
 * @param[in] device_address The extended address of the device.
 *
 * @return
 *      - EZB_ERR_NONE: Success
 *      - EZB_ERR_INV_ARG: The provided device address is invalid
 *      - EZB_ERR_NOT_FOUND: The device key pair is not found
 */
ezb_err_t ezb_diag_expose_aps_device_key(const ezb_extaddr_t *device_address);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_DIAG_H */
