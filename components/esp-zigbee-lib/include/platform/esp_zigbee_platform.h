/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "hal/gpio_types.h"
#include "hal/uart_types.h"
#include "driver/uart.h"
#include "esp_ieee802154_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration of Zigbee radio mode
 */
typedef enum {
    ZB_RADIO_MODE_NATIVE   = 0x0,      /*!< Use the native 15.4 radio */
    ZB_RADIO_MODE_UART_RCP = 0x1,      /*!< UART connection to a 15.4 capable radio co - processor (RCP) */
} esp_zb_radio_mode_t;

/**
 * @brief Enumeration of Zigbee host connection mode
 */
typedef enum {
    ZB_HOST_CONNECTION_MODE_NONE       = 0x0, /*!< Disable host connection */
    ZB_HOST_CONNECTION_MODE_CLI_UART   = 0x1, /*!< CLI UART connection to the host */
    ZB_HOST_CONNECTION_MODE_RCP_UART   = 0x2, /*!< RCP UART connection to the host */
} esp_zb_host_connection_mode_t;

/**
 * @brief Enumeration of Zigbee serial connection mode
 */
typedef enum {
    ZB_SERIAL_MODE_DISABLE   = 0x0,      /*!< Disable osif serial mode  */
    ZB_SERIAL_MODE_UART      = 0x1,      /*!< osif serial mode through uart */
} esp_zb_serial_mode_t;

/**
 * @brief Uart configuration
 */
typedef struct {
    uart_port_t port;               /*!< UART port number */
    gpio_num_t rx_pin;              /*!< UART RX pin */
    gpio_num_t tx_pin;              /*!< UART TX pin */
    uart_config_t uart_config;      /*!< UART configuration, see uart_config_t docs */
} esp_zb_uart_config_t;

/**
 * @brief Zigbee host connection mode
 */
typedef struct {
    esp_zb_serial_mode_t             serial_mode;                   /*!< The osif serial connection mode */
    esp_zb_uart_config_t             osif_serial_uart_config;       /*!< The uart configuration to osif serial */
} esp_zb_serial_config_t;

/**
 * @brief Zigbee radio configuration
 */
typedef struct {
    esp_zb_radio_mode_t     radio_mode;         /*!< The radio mode */
    esp_zb_uart_config_t    radio_uart_config;  /*!< The uart configuration to RCP */
} esp_zb_radio_config_t;

/**
 * @briefZigbee host configuration
 */
typedef struct {
    esp_zb_host_connection_mode_t   host_connection_mode;   /*!< The host connection mode */
    esp_zb_uart_config_t            host_uart_config;       /*!< The uart configuration to host */
} esp_zb_host_config_t;

/**
 * @brief Zigbee platform configuration
 */
typedef struct {
    esp_zb_radio_config_t               radio_config;   /*!< The radio configuration */
    esp_zb_host_config_t                host_config;    /*!< The host connection configuration */
}  esp_zb_platform_config_t;

/**
 * @brief Zigbee platform MAC configuration
 */
typedef struct {
    uint8_t csma_min_be;        /*!< The minimum value of the backoff exponent, BE, in the CSMA-CA algorithm. */
    uint8_t csma_max_be;        /*!< The maximum value of the backoff exponent, BE, in the CSMA-CA algorithm. */
    uint8_t csma_max_backoffs;  /*!< The maximum number of backoffs the CSMA-CA algorithm will attempt before
                                     declaring a channel access failure. */
} esp_zb_platform_mac_config_t;

/**
 * @brief A callback for user to obtain the MAC raw frame
 *
 * @param[in] frame The MAC raw frame
 * @param[in] info The basic information of MAC raw frame
 * @return
 *      - true: Indicates the stack should drop this frame
 *      - false: Indicates the stack should continue to handle the frame
 */
typedef bool (*esp_zb_mac_raw_frame_callback_t)(const uint8_t *frame, const esp_ieee802154_frame_info_t *info);

/**
 * @brief Register a callback to intercept the MAC raw frame.
 *
 * @param[in] cb A callback will be raised when receiving the MAC raw frame
 * @return
 *      - ESP_OK: On success, otherwise, failed
 */
esp_err_t esp_zb_mac_raw_frame_handler_register(esp_zb_mac_raw_frame_callback_t cb);

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
 * @brief  Set the espressif platform mac config
 *
 * @param[in] config - pointer to platform mac configuration @ref esp_zb_platform_mac_config_t
 *
 * @return - ESP_OK on success
 *         - ESP_ERR_INVALID_ARG if @p config is invalid or with invalid values.
 *         - ESP_ERR_NOT_SUPPORTED if ZB_RADIO_NATIVE is not enabled.
 *
 */
esp_err_t esp_zb_platform_mac_config_set(const esp_zb_platform_mac_config_t *config);

/**
 * @brief  Get the espressif platform mac config
 *
 * @param[out] config - pointer to platform mac configuration @ref esp_zb_platform_mac_config_t
 *
 * @return - ESP_OK on success
 *         - ESP_ERR_NOT_SUPPORTED if ZB_RADIO_NATIVE is not enabled.
 *
 */
esp_err_t esp_zb_platform_mac_config_get(esp_zb_platform_mac_config_t *config);

/**
 * @brief  Deinitialize the RCP
 *
 * @return - ESP_OK on success
 *
 */
esp_err_t esp_zb_rcp_deinit(void);

/**
 * @brief  Set zigbee default long poll interval
 *
 * @note  Used internally by the Zigbee SDK, no user intervention is required.
 *
 * @param[in] milliseconds - default long_poll_interval
 */
void esp_zb_set_default_long_poll_interval(uint32_t milliseconds);

/**
 * @brief  Get the zigbee default long poll interval
 *
 * @note  Used internally by the Zigbee SDK, no user intervention is required.
 *
 * @return zigbee default long poll interval
 *
 */
uint32_t esp_zb_get_default_long_poll_interval(void);

#ifdef __cplusplus
}
#endif
