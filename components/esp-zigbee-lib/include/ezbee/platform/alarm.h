/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_PLATFORM_ALARM_H
#define ESP_ZIGBEE_PLATFORM_ALARM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Start the microsecond alarm and set it to fire at @p t0 after @p dt.
 *
 * @note The platform MUST support:
 *         - all values in [0, 2^32-1], for @p t0, and
 *         - all values in [0, 2^31-1], for @p dt.
 *
 * @param[in] t0 The reference time in microseconds.
 * @param[in] dt The delay in microseconds from @p t0.
 *
 */
void ezb_plat_micro_alarm_start_at(uint32_t t0, uint32_t dt);

/**
 * @brief Stop the microsecond alarm.
 *
 */
void ezb_plat_micro_alarm_stop(void);

/**
 * @brief Get the current time.
 *
 * @note The current time MUST represent a 32-bit free-running timer.
 *       The time value MUST utilize the entire range [0, 2^32-1] and MUST NOT wrap before 2^32.
 *
 * @returns The current time in microseconds.
 *
 */
uint32_t ezb_plat_micro_alarm_get_now(void);

/**
 * @brief Signal that the microsecond alarm has fired.
 *
 */
extern void ezb_plat_signal_micro_alarm_fired(void);

/**
 * @brief Start the millisecond alarm and set it to fire at @p t0 after @p dt.
 *
 * @note The platform MUST support:
 *         - all values in [0, 2^32-1], for @p t0, and
 *         - all values in [0, 2^31-1], for @p dt.
 *
 * @param[in] t0 The reference time in milliseconds.
 * @param[in] dt The delay in milliseconds from @p t0.
 *
 */
void ezb_plat_milli_alarm_start_at(uint32_t t0, uint32_t dt);

/**
 * @brief Stop the millisecond alarm.
 *
 */
void ezb_plat_milli_alarm_stop(void);

/**
 * @brief Get the current time.
 *
 * @note The current time MUST represent a 32-bit free-running timer.
 *       The time value MUST utilize the entire range [0, 2^32-1] and MUST NOT wrap before 2^32.
 *
 * @returns The current time in milliseconds.
 *
 */
uint32_t ezb_plat_milli_alarm_get_now(void);

/**
 * @brief Signal that the millisecond alarm has fired.
 *
 */
extern void ezb_plat_signal_milli_alarm_fired(void);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_PLATFORM_ALARM_H */
