/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_MAC_H
#define ESP_ZIGBEE_MAC_H

#include <ezbee/core.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the maximum MAC transaction persistence time.
 *
 * @param us Maximum persistence time in microseconds, its value SHALL be within the range [0, 0x3BFFC400].
 *
 * @return
 *      - EZB_ERR_NONE: Operation successful
 *      - error code: Operation failed
 */
EZB_EXPERIMENTAL
ezb_err_t ezb_mac_set_transaction_persistence_time(uint32_t us);

/**
 * @brief Get the maximum MAC transaction persistence time.
 *
 * @return The maximum persistence time in microseconds.
 */
EZB_EXPERIMENTAL
uint32_t ezb_mac_get_transaction_persistence_time(void);

/**
 * @brief CSMA-CA parameters.
 */
typedef struct ezb_mac_csma_ca_params_s {
    uint8_t min_be;        /*!< The minimum value of the backoff exponent, BE, in the CSMA-CA algorithm. */
    uint8_t max_be;        /*!< The maximum value of the backoff exponent, BE, in the CSMA-CA algorithm. */
    uint8_t max_backoffs;  /*!< The maximum number of backoffs the CSMA-CA algorithm will attempt before
                                declaring a channel access failure. */
} ezb_mac_csma_ca_params_t;

/**
 * @brief Set the CSMA-CA parameters for the MAC layer.
 *
 * @param[in] params The CSMA-CA parameters.
 *
 * @return
 *      - EZB_ERR_NONE: Success.
 *      - EZB_ERR_INV_ARG: The @p params are invalid or with invalid values.
 */
EZB_EXPERIMENTAL
ezb_err_t ezb_mac_set_csma_ca_params(const ezb_mac_csma_ca_params_t *params);

/**
 * @brief Get the CSMA-CA parameters for the MAC layer.
 *
 * @param[out] params The CSMA-CA parameters will be stored in this pointer.
 *
 * @return
 *      - EZB_ERR_NONE: Success.
 */
EZB_EXPERIMENTAL
ezb_err_t ezb_mac_get_csma_ca_params(ezb_mac_csma_ca_params_t *params);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_MAC_H */
