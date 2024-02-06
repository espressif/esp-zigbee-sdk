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
 * @brief Enum of the mode for connection with the host
 * 
 */
typedef enum {
    NCP_HOST_CONNECTION_MODE_UART = 0x01,       /*!< NCP UART connection with the host */
    NCP_HOST_CONNECTION_MODE_SPI = 0x02,        /*!< NCP SPI connection with the host */
} esp_ncp_host_connection_mode_t;

/**
 * @brief Enum of the status
 * 
 */
typedef enum {
    ESP_NCP_SUCCESS = 0x00,                     /*!< The generic 'no error' */
    ESP_NCP_ERR_FATAL = 0x01,                   /*!< The generic 'fatal error' */
    ESP_NCP_BAD_ARGUMENT = 0x02,                /*!< An invalid value was passed as an argument */
    ESP_NCP_ERR_NO_MEM = 0x03,                  /*!< Out of memory */
} esp_ncp_status_t;

/**
 * @brief Enum of the network state
 * 
 */
typedef enum {
    ESP_NCP_OFFLINES = 0x00,                     /*!< The network is offline */
    ESP_NCP_JOINING = 0x01,                      /*!< Joinging the network */
    ESP_NCP_CONNECTED = 0x02,                    /*!< Conneted with the network */
    ESP_NCP_LEAVING = 0x03,                      /*!< Leaving the network */
    ESP_NCP_CONFIRM = 0x04,                      /*!< Confirm the APS */
    ESP_NCP_INDICATION = 0x05,                   /*!< Indication the APS */
} esp_ncp_states_t;

/**
 * @brief Enum of the network security mode
 * 
 */
typedef enum {
    ESP_NCP_NO_SECURITY = 0x00,                  /*!< The network is no security mode */
    ESP_NCP_PRECONFIGURED_NETWORK_KEY = 0x01,    /*!< Pre-configured the network key */
} esp_ncp_secur_t;

/** 
 * @brief  Initialize with the host for NCP.
 * 
 * @param[in] mode - The mode for connection with the host esp_ncp_host_connection_mode_t
 * 
 * @return 
 *     - ESP_OK on success
 *     - others: refer to esp_err.h
 */
esp_err_t esp_ncp_init(esp_ncp_host_connection_mode_t mode);

/**
 * @brief De-initialize with the host for NCP.
 *
 * @note This currently does not do anything
 *
 * @return 
 *     - ESP_OK on success
 *     - others: refer to esp_err.h
 */
esp_err_t esp_ncp_deinit(void);

/** 
 * @brief  Start communicate with the Host for NCP.
 * 
 * @return
 *    - ESP_OK on success
 *    - others: refer to esp_err.h
 */
esp_err_t esp_ncp_start(void);

/** 
 * @brief  Stop communicate with the Host for NCP.
 * 
 * @note This currently does not do anything
 * 
 * @return
 *    - ESP_OK on success
 *    - others: refer to esp_err.h
 */
esp_err_t esp_ncp_stop(void);

#ifdef __cplusplus
}
#endif
