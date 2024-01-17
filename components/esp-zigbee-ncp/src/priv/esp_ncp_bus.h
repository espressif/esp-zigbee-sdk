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
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

/**
 * @brief Enum of the state for bus communicate with the host
 * 
 */
typedef enum {
    BUS_INIT_INIT = 1,                  /*!< Init bus communicate with the host */
    BUS_INIT_START,                     /*!< Start bus communicate with the host */
    BUS_INIT_STOP,                      /*!< Stop bus communicate with the host */
} esp_ncp_bus_state_t;

/** Definition of the NCP bus information
 *
 */
#define NCP_BUS_RINGBUF_SIZE            20480
#define NCP_BUS_RINGBUF_TIMEOUT_MS      50
#define NCP_BUS_TASK_STACK              4096
#define NCP_BUS_TASK_PRIORITY           18
#define NCP_BUS_BUF_SIZE                1024

/**
 * @brief A function for bus initialize.
 *
 * @param[in] transport The mode for bus initialize
 *
 * @return 
 *     - ESP_OK on success
 *     - others: refer to esp_err.h
 */
typedef esp_err_t (*init_fn)(uint8_t transport);

/**
 * @brief A function for bus deinitialize.
 *
 * @return 
 *     - ESP_OK on success
 *     - others: refer to esp_err.h
 *
 */
typedef esp_err_t (*deinit_fn)(void);

/**
 * @brief A function for receive data from bus.
 *
 * @param[in] buffer The pointer to storage the data from bus
 * @param[in] size   The length to storage the data from bus
 *
 * @return 
 *     - ESP_OK on success
 *     - others: refer to esp_err.h
 */
typedef esp_err_t (*read_fn)(void *buffer, uint16_t size);

/** 
 * @brief A function for send data to bus.
 *
 * @param[in] buffer The pointer to storage the data to bus
 * @param[in] size   The length to storage the data to bus
 *
 */
typedef esp_err_t (*write_fn)(void *buffer, uint16_t size);

/**
 * @brief Type to represent NCP bus info structure
 *
 */
typedef struct {
    init_fn    init;                    /*!< A function for bus initialize */
    deinit_fn  deinit;                  /*!< A function for bus deinitialize */
    read_fn    read;                    /*!< A function for receive data from bus */
    write_fn   write;                   /*!< A function for send data to bus */

    esp_ncp_bus_state_t  state;         /*!< The state for bus communicate with the host */
    void *input_buf;                    /*!< The pointer to storage the data from NCP */
    void *output_buf;                   /*!< The pointer to storage the data to NCP */
    SemaphoreHandle_t input_sem;        /*!< A semaphore handle for process the data from NCP */
} esp_ncp_bus_t;

/** 
 * @brief  Input from NCP bus.
 * 
 * @param[in] buffer The input buffer pointer
 * @param[in] len    The input buffer length
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 */
esp_err_t esp_ncp_bus_input(const void *buffer, uint16_t len);

/** 
 * @brief  Output to NCP bus.
 * 
 * @param[in] buffer The output buffer pointer
 * @param[in] len    The output buffer length
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 */
esp_err_t esp_ncp_bus_output(const void *buffer, uint16_t len);

/** 
 * @brief  Initialize NCP bus.
 * 
 * @param[out] bus The pointer to the bus handler @ref esp_ncp_bus_t
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 */
esp_err_t esp_ncp_bus_init(esp_ncp_bus_t **bus);

/** 
 * @brief  De-initialize NCP bus.
 * 
 * @param[in] bus The pointer to the bus handler @ref esp_ncp_bus_t
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 */
esp_err_t esp_ncp_bus_deinit(esp_ncp_bus_t *bus);

/** 
 * @brief  Start NCP bus.
 * 
 * @param[in] bus The pointer to the bus handler @ref esp_ncp_bus_t
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 */
esp_err_t esp_ncp_bus_start(esp_ncp_bus_t *bus);

/** 
 * @brief  Stop NCP bus.
 * 
 * @param[in] bus The pointer to the bus handler @ref esp_ncp_bus_t
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 */
esp_err_t esp_ncp_bus_stop(esp_ncp_bus_t *bus);

#ifdef __cplusplus
}
#endif
