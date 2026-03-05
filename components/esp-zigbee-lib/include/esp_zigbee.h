/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdbool.h>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "hal/gpio_types.h"
#include "hal/uart_types.h"
#include "driver/uart.h"

#include "esp_zigbee_version.h"
#include "ezbee/core.h"
#include "ezbee/nwk.h"
#include "ezbee/aps.h"
#include "ezbee/af.h"
#include "ezbee/zdo.h"
#include "ezbee/zcl.h"
#include "ezbee/bdb.h"
#include "ezbee/secur.h"
#include "ezbee/app_signals.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration of Zigbee radio mode
 */
typedef enum {
    ESP_ZIGBEE_RADIO_MODE_NATIVE   = 0x0,   /*!< Use the native 15.4 radio */
    ESP_ZIGBEE_RADIO_MODE_UART_RCP = 0x1,   /*!< UART connection to a 15.4 capable radio co-processor (RCP) */
    ESP_ZIGBEE_RADIO_MODE_MAX_NR,           /*!< Using for parameter check */
} esp_zigbee_radio_mode_t;

/**
 * @brief The uart port config for Zigbee.
 */
 typedef struct esp_zigbee_uart_config_s {
    uart_port_t   port;        /*!< UART port number */
    uart_config_t uart_config; /*!< UART configuration, see uart_config_t docs */
    gpio_num_t    rx_pin;      /*!< UART RX pin */
    gpio_num_t    tx_pin;      /*!< UART TX pin */
} esp_zigbee_uart_config_t;

/**
 * @brief Zigbee radio configuration
 */
typedef struct esp_zigbee_radio_config_s {
    esp_zigbee_radio_mode_t  radio_mode;            /*!< The radio mode */
    union {
        esp_zigbee_uart_config_t radio_uart_config; /*!< The uart configuration to RCP */
    };
} esp_zigbee_radio_config_t;

/**
 * @brief Zigbee platform configuration
 */
typedef struct esp_zigbee_platform_config_s {
    const char *storage_partition_name;     /*!< The name of the storage partition */
    esp_zigbee_radio_config_t radio_config; /*!< The radio configuration */
} esp_zigbee_platform_config_t;

/**
 * @brief The Zigbee Coordinator/ Router device configuration.
 *
 */
struct esp_zigbee_zczr_config_s {
    uint8_t max_children; /*!< Max number of the children */
};

/**
 * @brief The Zigbee End device configuration.
 *
 */
struct esp_zigbee_zed_config_s {
    uint8_t ed_timeout;  /*!< Set End Device Timeout, refer to @ref ezb_nwk_ed_timeout_e */
    uint32_t keep_alive; /*!< Set Keep alive Timeout, in milliseconds. */
};

/**
 * @brief The Zigbee device configuration.
 */
typedef struct esp_zigbee_device_config_s {
    ezb_nwk_device_type_t device_type;          /*!< The nwk device type, @ref ezb_nwk_device_type_t */
    bool install_code_policy;                   /*!< Allow install code security policy or not */
    union {
        struct esp_zigbee_zczr_config_s zczr_config; /*!< The Zigbee zc/zr device configuration */
        struct esp_zigbee_zed_config_s  zed_config;  /*!< The Zigbee zed device configuration */
    };
} esp_zigbee_device_config_t;

/**
 * @brief The Zigbee configuration.
 */
typedef struct esp_zigbee_config_s {
    esp_zigbee_device_config_t device_config;       /*!< The Zigbee device configuration */
    esp_zigbee_platform_config_t platform_config;   /*!< The Zigbee platform configuration */
} esp_zigbee_config_t;

/**
 * @brief Initialize ESP-Zigbee stack.
 * @anchor esp_zigbee_init
 *
 * @param[in] config The Zigbee configuration, @ref esp_zigbee_config_s.
 *
 * @return ESP_OK on success, error code otherwise.
 *
 */
esp_err_t esp_zigbee_init(const esp_zigbee_config_t *config);

/**
 * @brief Deinitialize ESP-Zigbee stack.
 * @anchor esp_zigbee_deinit
 *
 * @return ESP_OK on success, error code otherwise.
 *
 */
esp_err_t esp_zigbee_deinit(void);

/**
 * @brief Start Zigbee function.
 * @anchor esp_zigbee_start
 *
 * @param[in] autostart
 *                - True:    autostart mode
 *                - False:   no-autostart mode.
 *
 * @note
 *     - **Prerequisite**: The stack SHALL be initialized by @ref esp_zigbee_init.
 *     - **Postprocess**: The stack is not looped in this routine. Instead, it schedules callback and returns.
 *       The application SHALL call @ref esp_zigbee_launch_mainloop after this routine.
 *
 * @note
 *     - The stack will initialize the framework, load persistent data from datasets and continue the startup procedure.
 *       The startup procedure always means commissioning the device to a network (formation, rejoin or join the network;
 *       typically by BDB process).
 *     - **Autostart**: Do everything, including the startup procedure.
 *     - **No-autostart**: Do everything, but skip the startup procedure. Typically esp_zigbee_start()
 *       with no-autostart mode is used when application wants to do something before starting joining
 *       the network and control the startup process by itself.
 *
 * @return
 *     - ESP_OK: Stack started successfully.
 *     - ESP_FAIL: Stack failed to start.
 */
esp_err_t esp_zigbee_start(bool autostart);

/**
 * @brief Get the stack is started or not.
 * @anchor esp_zigbee_is_started
 *
 * @return true if the stack has been started, false otherwise.
 *
 */
bool esp_zigbee_is_started(void);

/**
 * @brief Launch the mainloop of ESP-Zigbee.
 * @anchor esp_zigbee_launch_mainloop
 *
 * @return ESP_OK on success, error code otherwise.
 *
 */
esp_err_t esp_zigbee_launch_mainloop(void);

/**
 * @brief Acquire Zigbee lock.
 *
 * @note It's mandatory to acquire the lock before calling any Zigbee SDK APIs, except that the call site is in Zigbee callbacks.
 *
 * @param[in] block_ticks The maximum number of RTOS ticks to wait for the lock.
 *
 * @return
 *      - True on lock acquired
 *      - False on failing to acquire the lock with the timeout.
 *
 */
bool esp_zigbee_lock_acquire(TickType_t block_ticks);

/**
 * @brief  Release Zigbee lock.
 *
 */
void esp_zigbee_lock_release(void);

/**
 * @brief The ESP-Zigbee callback type
 *
 * @param[in] ctx The context to be passed to the callback.
 */
typedef void (*esp_zigbee_callback_t)(void* ctx);

/**
 * @brief This function posts a task to the ESP-Zigbee task queue.
 *
 * @param[in] cb  The callback function to execute.
 * @param[in] ctx The context to be passed to the callback.
 *
 * @return
 *   - ESP_OK
 *   - ESP_FAIL
 */
esp_err_t esp_zigbee_task_queue_post(esp_zigbee_callback_t cb, void *ctx);

/**
 * @brief Convert core stack error to esp_err_t.
 *
 * @param[in] error The error code from the core stack.
 *
 * @return The esp_err_t error code.
 */
esp_err_t esp_zigbee_err_to_esp(ezb_err_t error);

/**
 * @brief Perform "factory reset" procedure.
 *
 * @note This function will clear all the datasets and restart the device.
 *
 */
__attribute__((__noreturn__))
void esp_zigbee_factory_reset(void);

#ifdef __cplusplus
} /*  extern "C" */
#endif
