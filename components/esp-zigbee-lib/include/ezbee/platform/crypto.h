/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_PLATFORM_CRYPTO_H
#define ESP_ZIGBEE_PLATFORM_CRYPTO_H

#include <stddef.h>
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
 * @brief Initialize the crypto module.
 */
void ezb_plat_crypto_init(void);

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

/**
 * @brief SHA256 hash output size (in bytes).
 */
#define EZB_CRYPTO_SHA256_HASH_SIZE 32

/**
 * @brief Initialize the SHA256 operation context.
 *
 * @param[in] ctx Context for SHA256 operation.
 *
 * @return EZB_ERR_NONE    Successfully initialized SHA256 operation.
 *         EZB_ERR_FAIL    Failed to initialize SHA256 operation.
 *         EZB_ERR_INV_ARG @p ctx was NULL.
 */
ezb_err_t ezb_plat_crypto_sha256_init(ezb_crypto_context_t *ctx);

/**
 * @brief Start the SHA256 operation.
 *
 * @param[in] ctx Context for SHA256 operation.
 *
 * @return EZB_ERR_NONE    Successfully started SHA256 operation.
 *         EZB_ERR_FAIL    Failed to start SHA256 operation.
 *         EZB_ERR_INV_ARG @p ctx was NULL.
 */
ezb_err_t ezb_plat_crypto_sha256_start(ezb_crypto_context_t *ctx);

/**
 * @brief Update the SHA256 operation with new data.
 *
 * @param[in] ctx      Context for SHA256 operation.
 * @param[in] data     Data to feed to SHA256 operation.
 * @param[in] data_len Length of data in bytes.
 *
 * @return EZB_ERR_NONE    Successfully fed data to SHA256 operation.
 *         EZB_ERR_FAIL    Failed to feed data to SHA256 operation.
 *         EZB_ERR_INV_ARG @p ctx or @p data was NULL.
 */
ezb_err_t ezb_plat_crypto_sha256_update(ezb_crypto_context_t *ctx, const uint8_t *data, uint16_t data_len);

/**
 * @brief Finish the SHA256 operation and get the hash.
 *
 * @param[in] ctx      Context for SHA256 operation.
 * @param[out] output  Pointer to the output buffer.
 * @param[in] output_len Length of output buffer in bytes.
 *
 * @return EZB_ERR_NONE    Successfully finished SHA256 operation.
 *         EZB_ERR_FAIL    Failed to finish SHA256 operation.
 *         EZB_ERR_INV_ARG @p ctx or @p output was NULL.
 */
ezb_err_t ezb_plat_crypto_sha256_finish(ezb_crypto_context_t *ctx, uint8_t *output, uint16_t output_len);

/**
 * @brief Free the SHA256 operation context.
 *
 * @param[in] ctx Context for SHA256 operation.
 *
 * @return EZB_ERR_NONE    Successfully freed SHA256 context.
 *         EZB_ERR_FAIL    Failed to free SHA256 context.
 *         EZB_ERR_INV_ARG @p ctx was NULL.
 */
ezb_err_t ezb_plat_crypto_sha256_free(ezb_crypto_context_t *ctx);

/**
 * @brief Elliptic-curve ID.
 */
typedef enum {
    EZB_CRYPTO_ECC_INVALID = 0, /*!< Invalid curve */
    EZB_CRYPTO_ECC_CURVE25519,  /*!< Curve25519, for ECSPEKE */
    EZB_CRYPTO_ECC_SECP256R1,   /*!< SECP256R1,  for ECDHE_PSK */
    EZB_CRYPTO_ECC_SECT163K1,   /*!< SECT163K1 */
    EZB_CRYPTO_ECC_SECT283K1,   /*!< SECT283K1 */
} ezb_crypto_ecc_curve_id_t;

/**
 * @brief Initialize the ECDH operation context.
 *
 * Required curves:
 *   - EZB_CRYPTO_ECC_CURVE25519
 *   - EZB_CRYPTO_ECC_SECP256R1
 *
 * @param[in] ctx Context for ECDH operation.
 * @param[in] curve_id Elliptic-curve ID.
 *
 * @return EZB_ERR_NONE          Successfully initialized ECDH operation.
 *         EZB_ERR_INV_ARG @p ctx was NULL.
 *         EZB_ERR_NOT_SUPPORTED @p curve_id is not supported.
 */
ezb_err_t ezb_plat_crypto_ecdh_init(ezb_crypto_context_t *ctx, ezb_crypto_ecc_curve_id_t curve_id);

/**
 * @brief Deinitialize the ECDH operation context.
 *
 * @param[in] ctx Context for ECDH operation.
 *
 * @return EZB_ERR_NONE    Successfully deinitialized ECDH operation.
 *         EZB_ERR_INV_ARG @p ctx was NULL.
 */
ezb_err_t ezb_plat_crypto_ecdh_deinit(ezb_crypto_context_t *ctx);

/**
 * @brief Set the generator for ECDH key generation.
 *
 * Required curves:
 *   - EZB_CRYPTO_ECC_CURVE25519
 *
 * @param[in] ctx Context for ECDH operation.
 * @param[in] buf Pointer to the generator buffer.
 * @param[in] blen Length of the generator buffer in bytes.
 *
 * @return EZB_ERR_NONE          Successfully set the generator for ECDH operation.
 *         EZB_ERR_INV_ARG       @p ctx was NULL.
 *         EZB_ERR_NOT_SUPPORTED @p curve_id is not supported.
 */
ezb_err_t ezb_plat_crypto_ecdh_set_generator(ezb_crypto_context_t *ctx, const uint8_t *buf, uint16_t blen);

/**
 * @brief Generate the public key for ECDH operation.
 *
 * Required curves:
 *   - EZB_CRYPTO_ECC_CURVE25519
 *   - EZB_CRYPTO_ECC_SECP256R1
 *
 * @param[in] ctx Context for ECDH operation.
 *
 * @return EZB_ERR_NONE          Successfully generated the public key for ECDH operation.
 *         EZB_ERR_INV_ARG       @p ctx was NULL.
 *         EZB_ERR_NOT_SUPPORTED @p curve_id is not supported.
 */
ezb_err_t ezb_plat_crypto_ecdh_generate_public(ezb_crypto_context_t *ctx);

/**
 * @brief Export the public key for ECDH operation.
 *
 * Required curves:
 *   - EZB_CRYPTO_ECC_CURVE25519: @p pubkey length is 32 bytes.
 *   - EZB_CRYPTO_ECC_SECP256R1:  @p pubkey length is 65 bytes, uncompressed format.
 *
 * @param[in]  ctx        Context for ECDH operation.
 * @param[out] pubkey     Pointer to the public key buffer.
 * @param[in]  pubkey_len Length of the public key buffer in bytes.
 *
 * @return EZB_ERR_NONE          Successfully exported the public key for ECDH operation.
 *         EZB_ERR_INV_ARG       @p ctx or @p pubkey was NULL.
 *         EZB_ERR_NOT_SUPPORTED @p curve_id is not supported.
 */
ezb_err_t ezb_plat_crypto_ecdh_export_public(ezb_crypto_context_t *ctx, uint8_t *pubkey, uint16_t pubkey_len);

/**
 * @brief Compute the shared secret for ECDH operation.
 *
 * Required curves:
 *   - EZB_CRYPTO_ECC_CURVE25519: @p peer_key length is 32 bytes.
 *   - EZB_CRYPTO_ECC_SECP256R1:  @p peer_key length is 65 bytes, uncompressed format.
 *
 * @param[in]  ctx               Context for ECDH operation.
 * @param[in]  peer_key          Pointer to the peer public key.
 * @param[in]  peer_key_len      Length of the peer public key in bytes.
 * @param[out] shared_secret     Pointer to the shared secret.
 * @param[in]  shared_secret_len Length of the shared secret in bytes.
 *
 * @return EZB_ERR_NONE          Successfully computed the shared secret for ECDH operation.
 *         EZB_ERR_INV_ARG       @p ctx or @p peer_key or @p shared_secret was NULL.
 *         EZB_ERR_NOT_SUPPORTED @p curve_id is not supported.
 */
ezb_err_t ezb_plat_crypto_ecdh_compute_shared(ezb_crypto_context_t *ctx,
                                              const uint8_t *peer_key, uint16_t peer_key_len,
                                              uint8_t *shared_secret, uint16_t shared_secret_len);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_PLATFORM_CRYPTO_H */
