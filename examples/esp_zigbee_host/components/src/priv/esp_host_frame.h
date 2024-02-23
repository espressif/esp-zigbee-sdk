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
 * @brief Type to represent the protocol frame used between the host and the NCP.
 *
 */
typedef struct {
    struct {
        uint16_t version:4;                     /*!< The EGSP protocol version */
        uint16_t type:4;                        /*!< The frame type */
        uint16_t reserved:8;                    /*!< The reserved bits of flags */
    } flags;
    uint16_t id;                                /*!< The frame ID for request, response and notify, refer to the frame ID list */
    uint8_t  sn;                                /*!< The transaction sequence number for request, response and notify */
    uint16_t len;                               /*!< The payload length for request, response and notify */
} __attribute__((packed)) esp_host_header_t;

/** 
 * @brief  Output to host.
 * 
 * @param[in] buffer The output buffer pointer
 * @param[in] len    The output buffer length
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 * 
 */
esp_err_t esp_host_frame_input(const void *buffer, uint16_t len);

/**
 * @brief   Process the frame ID on the HOST and response it to the host.
 * 
 * @param[in] host_header The protocol frame header pointer
 * @param[in] buffer     The payload buffer pointer which match the frame ID
 * @param[in] len        The payload buffer length which match the frame ID
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 *
 */
esp_err_t esp_host_frame_output(esp_host_header_t *host_header, const void *buffer, uint16_t len);

#ifdef __cplusplus
}
#endif
