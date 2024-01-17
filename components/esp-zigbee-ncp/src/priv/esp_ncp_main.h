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

/** Definition of the NCP information
 *
 */
#define NCP_TASK_STACK       5120
#define NCP_TASK_PRIORITY    23
#define NCP_TIMEOUT_MS       10
#define NCP_EVENT_QUEUE_LEN  60

/**
 * @brief Enum of the event id for NCP.
 *
 */
typedef enum {
    NCP_EVENT_INPUT,                /*!< Input event from NCP to host */
    NCP_EVENT_OUTPUT,               /*!< Output event from host to NCP */
    NCP_EVENT_RESET,                /*!< Reset event from host to NCP */
    NCP_EVENT_LOOP_STOP,            /*!< Stop loop event from host to NCP */
} esp_ncp_event_t;

/**
 * @brief Type to represent the sync event between the host and NCP.
 *
 */
typedef struct {
    esp_ncp_event_t event;          /*!< The event between the host and NCP */
    uint16_t        size;           /*!< Data size on the event */
} esp_ncp_ctx_t;

/**
 * @brief Type to represent the device infomation for the NCP.
 *
 */
typedef struct esp_ncp_dev_t {
    bool run;                       /*!< The flag of device running or not */
    QueueHandle_t queue;            /*!< The queue handler for sync between the host and NCP */
    esp_ncp_bus_t *bus;             /*!< The bus handler for communicate with the host */
} esp_ncp_dev_t;

/**
 * @brief   NCP send event to queue.
 *
 * @param[in] ncp_event The pointer to the event to be sent @ref esp_ncp_ctx_t
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 */
esp_err_t esp_ncp_send_event(esp_ncp_ctx_t *ncp_event);

#ifdef __cplusplus
}
#endif
