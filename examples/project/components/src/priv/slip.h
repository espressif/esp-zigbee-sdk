/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

/** Definition SLIP special character codes
 * 
 */
#define SLIP_END                0xC0 /* 0300: start and end of every packet */
#define SLIP_ESC                0xDB /* 0333: escape start (one byte escaped data follows) */
#define SLIP_ESC_END            0xDC /* 0334: following escape: original byte is 0xC0 (END) */
#define SLIP_ESC_ESC            0xDD /* 0335: following escape: original byte is 0xDB (ESC) */

/**
 * @brief   Encode a packet into the buffer located at "inbuf".
 *
 * @param[in]   inbuf  The pointer to store a packet data
 * @param[in]   inlen  The length of a packet data
 * @param[out]  outbuf The pointer to store an encode packet data
 * @param[out]  outlen The length of an encode packet data
 *
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 */
esp_err_t slip_encode(const uint8_t *inbuf, uint16_t inlen, uint8_t **outbuf, uint16_t *outlen);

/**
 * @brief   Decode a packet into the buffer located at "inbuf".
 *
 * @param[in]   inbuf  The pointer to store an encode packet data
 * @param[in]   inlen  The length of an encode packet data
 * @param[out]  outbuf The pointer to store a decode packet data
 * @param[out]  outlen The length of a decode packet data
 *
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 */
esp_err_t slip_decode(const uint8_t *inbuf, uint16_t inlen, uint8_t **outbuf, uint16_t *outlen);

#ifdef __cplusplus
}
#endif
