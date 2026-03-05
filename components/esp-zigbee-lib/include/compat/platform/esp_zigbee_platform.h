/*
 * SPDX-FileCopyrightText: 2025-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "esp_zigbee.h" instead!"

#include "hal/gpio_types.h"
#include "hal/uart_types.h"
#include "driver/uart.h"
#include "esp_ieee802154_types.h"
#include "esp_zigbee.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration of Zigbee radio mode
 */
#define ZB_RADIO_MODE_NATIVE    ESP_ZIGBEE_RADIO_MODE_NATIVE
#define ZB_RADIO_MODE_UART_RCP  ESP_ZIGBEE_RADIO_MODE_UART_RCP
typedef esp_zigbee_radio_mode_t esp_zb_radio_mode_t;

/**
 * @brief Enumeration of Zigbee host connection mode
 */
typedef enum {
    ZB_HOST_CONNECTION_MODE_NONE = 0x0, /*!< Disable host connection */
} esp_zb_host_connection_mode_t;

/**
 * @brief Uart configuration
 */
typedef esp_zigbee_uart_config_t esp_zb_uart_config_t;

/**
 * @brief Zigbee radio configuration
 */
typedef esp_zigbee_radio_config_t esp_zb_radio_config_t;

/**
 * @brief Zigbee host configuration
 */
typedef struct {
    esp_zb_host_connection_mode_t host_connection_mode;   /*!< The host connection mode */
    esp_zb_uart_config_t          host_uart_config;       /*!< The uart configuration to host */
} esp_zb_host_config_t;

/**
 * @brief Zigbee platform configuration
 */
typedef struct {
    esp_zb_radio_config_t radio_config; /*!< The radio configuration */
    esp_zb_host_config_t  host_config;  /*!< The host connection configuration */
}  esp_zb_platform_config_t;


/**
 * @brief  Set the espressif soc platform config
 *
 * @param[in] config - pointer to platform configuration @ref esp_zb_platform_config_t
 *
 * @return - ESP_OK on success
 *
 */
esp_err_t esp_zb_platform_config(esp_zb_platform_config_t *config);

/**
 * @brief  Get the espressif soc platform config
 *
 * @return - pointer to platform configuration @ref esp_zb_platform_config_t
 *
 */
esp_zb_platform_config_t* esp_zb_platform_config_get(void);

/**
 * @brief  Deinitialize the RCP
 *
 * @return - ESP_OK on success
 *
 */
#define esp_zb_rcp_deinit() esp_zigbee_deinit()

#ifdef __cplusplus
} /*  extern "C" */
#endif

#else
#error "This file is for compatibility, please include "esp_zigbee.h"!"
#endif
