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
#include "esp_host_bus.h"
#include "zb_config_platform.h"

/** Definition of the HOST information
 *
 */
#define HOST_TASK_STACK       5120
#define HOST_TASK_PRIORITY    23
#define HOST_TIMEOUT_MS       10
#define HOST_EVENT_QUEUE_LEN  60

/**
 * @brief Enum of the event id for HOST.
 *
 */
typedef enum {
    HOST_EVENT_INPUT,                /*!< Input event */
    HOST_EVENT_OUTPUT,               /*!< Output event */
    HOST_EVENT_RESET,                /*!< Reset event */
    HOST_EVENT_APS,                  /*!< Application event */
    HOST_EVENT_LOOP_STOP,            /*!< Stop loop event */
} esp_host_event_t;

/**
 * @brief Type to represent the sync event between the host and BUS.
 *
 */
typedef struct {
    esp_host_event_t event;          /*!< The event between the host and BUS */
    uint16_t        size;            /*!< Data size on the event */
} esp_host_ctx_t;

/**
 * @brief Type to represent the device infomation for the HOST.
 *
 */
typedef struct esp_host_dev_t {
    bool run;                       /*!< The flag of device running or not */
    QueueHandle_t queue;            /*!< The queue handler for sync between the host and HOST */
    esp_host_bus_t *bus;            /*!< The bus handler for communicate with the host */
} esp_host_dev_t;

/**
 * @brief   HOST send event to queue.
 *
 * @param[in] host_event The pointer to the event to be sent @ref esp_host_ctx_t
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 */
esp_err_t esp_host_send_event(esp_host_ctx_t *host_event);

/** 
 * @brief  Initialize the host.
 * 
 * @param[in] mode - The mode for connection
 * 
 * @return 
 *     - ESP_OK on success
 *     - others: refer to esp_err.h
 */
esp_err_t esp_host_init(esp_host_connection_mode_t mode);

/**
 * @brief De-initialize the host.
 *
 * @note This currently does not do anything
 *
 * @return 
 *     - ESP_OK on success
 *     - others: refer to esp_err.h
 */
esp_err_t esp_host_deinit(void);

/** 
 * @brief  Start host communicate.
 * 
 * @return
 *    - ESP_OK on success
 *    - others: refer to esp_err.h
 */
esp_err_t esp_host_start(void);

/** 
 * @brief  Stop host communicate.
 * 
 * @note This currently does not do anything
 * 
 * @return
 *    - ESP_OK on success
 *    - others: refer to esp_err.h
 */
esp_err_t esp_host_stop(void);

#ifdef __cplusplus
}
#endif
