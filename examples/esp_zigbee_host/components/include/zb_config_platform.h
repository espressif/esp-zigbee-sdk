/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "esp_err.h"

/**
 * @brief Enum of the mode for connection
 * 
 */
typedef enum {
    HOST_CONNECTION_MODE_UART = 0x01,                   /*!< UART connection */
    HOST_CONNECTION_MODE_SPI = 0x02,                    /*!< SPI connection */
} esp_host_connection_mode_t;

typedef enum {
    RADIO_MODE_UART_NCP   = 0x0,                        /*!< UART connection to a 15.4 Network Co-processor */
} esp_zb_radio_mode_t;

typedef struct {
    esp_zb_radio_mode_t             radio_mode;         /*!< The radio mode */
} esp_zb_ncp_config_t;

typedef struct {
    esp_host_connection_mode_t      host_mode;         /*!< The host connection mode */
} esp_zb_host_config_t;

typedef struct {
    esp_zb_ncp_config_t              radio_config;      /*!< The radio configuration */
    esp_zb_host_config_t             host_config;       /*!< The host connection configuration */
} esp_zb_platform_config_t;

/**
 * @brief  Set the soc platform config
 *
 * @param[in] config - pointer to platform configuration @ref esp_zb_platform_config_t
 *
 * @return - ESP_OK on success
 *
 */
esp_err_t esp_zb_platform_config(esp_zb_platform_config_t *config);

#ifdef __cplusplus
}
#endif
