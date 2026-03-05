/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_PLATFORM_CRYPTO_H
#define ESP_ZIGBEE_PLATFORM_CRYPTO_H

#include <stdint.h>

#include <ezbee/error.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Key Material required for Crypto operations.
 */
typedef struct ezb_crypto_key_s {
    const uint8_t *key; /*!< Pointer to the buffer containing key. */
    uint16_t key_len;   /*!< The key length in bytes (applicable when `mKey` is not NULL). */
} ezb_crypto_key_t;

/**
 * @brief Context object for platform APIs.
 */
typedef struct ezb_crypto_context_s {
    void *ctx;         /*!< Pointer to the context. */
    uint16_t ctx_size; /*!< The length of the context in bytes. */
} ezb_crypto_context_t;

/**
 * @brief Initialize the AES operation.
 *
 * @param[in] context Context for AES operation.
 *
 * @return EZB_ERR_NONE    Successfully Initialised AES operation.
 *         EZB_ERR_FAIL    Failed to Initialise AES operation.
 *         EZB_ERR_INV_ARG @p context was NULL.
 *         EZB_ERR_NO_MEM  Cannot allocate the context.
 */
ezb_err_t ezb_plat_crypto_aes_init(ezb_crypto_context_t *context);

/**
 * @brief Set the key for AES encryption.
 *
 * @param[in] context Context for AES operation.
 * @param[in] key     Key to use for AES operation.
 *
 * @return EZB_ERR_NONE    Successfully set the key for AES operation.
 *         EZB_ERR_FAIL    Failed to set the key for AES operation.
 *         EZB_ERR_INV_ARG @p context or @p key was NULL
 */
ezb_err_t ezb_plat_crypto_aes_setkey_enc(ezb_crypto_context_t *context, const ezb_crypto_key_t *key);

/**
 * @brief Set the key for AES decryption.
 *
 * @param[in] context Context for AES operation.
 * @param[in] key     Key to use for AES operation.
 *
 * @return EZB_ERR_NONE    Successfully set the key for AES operation.
 *         EZB_ERR_FAIL    Failed to set the key for AES operation.
 *         EZB_ERR_INV_ARG @p context or @p key was NULL
 */
ezb_err_t ezb_plat_crypto_aes_setkey_dec(ezb_crypto_context_t *context, const ezb_crypto_key_t *key);

/**
 * @brief Encrypt the data by AES(-ECB).
 *
 * @param[in]  context Context for AES operation.
 * @param[in]  input   Pointer to the input buffer.
 * @param[out] output  Pointer to the output buffer.
 *
 * @return EZB_ERR_NONE    Successfully encrypted @p input.
 *         EZB_ERR_FAIL    Failed to encrypt @p input.
 *         EZB_ERR_INV_ARG @p context or @p key or @p output were NULL.
 */
ezb_err_t ezb_plat_crypto_aes_encrypt(ezb_crypto_context_t *context, const uint8_t *input, uint8_t *output);

/**
 * @brief Decrypt the data by AES(-ECB).
 *
 * @param[in]  context Context for AES operation.
 * @param[in]  input   Pointer to the input buffer.
 * @param[out] output  Pointer to the output buffer.
 *
 * @return EZB_ERR_NONE    Successfully decrypted @p input.
 *         EZB_ERR_FAIL    Failed to decrypted @p input.
 *         EZB_ERR_INV_ARG @p context or @p key or @p output were NULL.
 */
ezb_err_t ezb_plat_crypto_aes_decrypt(ezb_crypto_context_t *context, const uint8_t *input, uint8_t *output);

/**
 * @brief Free the AES context.
 *
 * @param[in] context Context for AES operation.
 *
 * @return EZB_ERR_NONE    Successfully freed AES context.
 *         EZB_ERR_FAIL    Failed to free AES context.
 *         EZB_ERR_INV_ARG @p context was NULL.
 */
ezb_err_t ezb_plat_crypto_aes_free(ezb_crypto_context_t *context);

/**
 * @brief Initialize cryptographically-secure pseudorandom number generator (CSPRNG).
 */
void ezb_plat_crypto_random_init(void);

/**
 * @brief Deinitialize cryptographically-secure pseudorandom number generator (CSPRNG).
 */
void ezb_plat_crypto_random_deinit(void);

/**
 * @brief Fill buffer with cryptographically secure random bytes.
 *
 * @param[out] output        A pointer to where the true random values are placed. Must not be NULL.
 * @param[in]  output_length Length in bytes of @p output.
 *
 * @return EZB_ERR_NONE    Successfully filled @p output with true random values.
 *         EZB_ERR_FAIL    Failed to fill @p output with true random values.
 *         EZB_ERR_INV_ARG @p output was NULL.
 */
ezb_err_t ezb_plat_crypto_random_get(uint8_t *output, uint16_t output_length);

/**
 * @brief Fill buffer with entropy.
 *
 * MUST be implemented using a true random number generator (TRNG).
 *
 * @param[out] output        A pointer to where the true random values are placed. Must not be NULL.
 * @param[in]  output_length Length in bytes of @p output.
 *
 * @return EZB_ERR_NONE    Successfully filled @p output with true random values.
 *         EZB_ERR_FAIL    Failed to fill @p output with true random values.
 *         EZB_ERR_INV_ARG @p output was NULL.
 */
ezb_err_t ezb_plat_crypto_entropy_get(uint8_t *output, uint16_t output_length);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_PLATFORM_CRYPTO_H */
