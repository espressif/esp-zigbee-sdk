/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_PLATFORM_LOG_H
#define ESP_ZIGBEE_PLATFORM_LOG_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Log level representation
 *
 */
typedef int ezb_log_level_t;

#define EZB_LOG_LEVEL_NONE    0 /*!< Log level None. */
#define EZB_LOG_LEVEL_ERROR   1 /*!< Log level Error. */
#define EZB_LOG_LEVEL_WARN    2 /*!< Log level Informational. */
#define EZB_LOG_LEVEL_INFO    3 /*!< Log level Warning. */
#define EZB_LOG_LEVEL_DEBUG   4 /*!< Log level Debug. */
#define EZB_LOG_LEVEL_VERBOSE 5 /*!< Log level Verbose. */

/**
 * @brief Outputs logs.
 *
 * @param[in] log_level The log level.
 * @param[in] format A pointer to the format string.
 * @param[in] ... Arguments for the format specification.
 *
 */
void ezb_plat_log(ezb_log_level_t log_level, const char *format, ...);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_PLATFORM_LOG_H */
