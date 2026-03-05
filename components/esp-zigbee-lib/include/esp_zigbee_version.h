/*
 * SPDX-FileCopyrightText: 2022-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

/**
 * @def ESP_ZIGBEE_VER_MAJOR
 *
 * The major version of the SDK.
 */
#ifndef ESP_ZIGBEE_VER_MAJOR
#define ESP_ZIGBEE_VER_MAJOR 2
#endif

/**
 * @def ESP_ZIGBEE_VER_MINOR
 *
 * The minor version of the SDK.
 */
#ifndef ESP_ZIGBEE_VER_MINOR
#define ESP_ZIGBEE_VER_MINOR 0
#endif

/**
 * @def ESP_ZIGBEE_VER_PATCH
 *
 * The patch version of the SDK.
 */
#ifndef ESP_ZIGBEE_VER_PATCH
#define ESP_ZIGBEE_VER_PATCH 0
#endif

/**
 * @brief Get the version string of the SDK.
 *
 * @return The version string of the SDK.
 */
const char *esp_zigbee_get_version_string(void);
