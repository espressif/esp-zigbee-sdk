/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbedtls/aes.h"

#if CONFIG_MBEDTLS_HARDWARE_AES

#undef mbedtls_aes_init
#undef mbedtls_aes_free
#undef mbedtls_aes_setkey_enc
#undef mbedtls_aes_setkey_dec
#undef mbedtls_aes_crypt_ecb

void mbedtls_aes_init(mbedtls_aes_context *ctx)
{
    esp_aes_init(ctx);
}

void mbedtls_aes_free(mbedtls_aes_context *ctx)
{
    esp_aes_free(ctx);
}

int mbedtls_aes_setkey_enc(mbedtls_aes_context *ctx, const unsigned char *key, unsigned int keybits)
{
    return esp_aes_setkey(ctx, key, keybits);
}

int mbedtls_aes_setkey_dec(mbedtls_aes_context *ctx, const unsigned char *key, unsigned int keybits)
{
    return esp_aes_setkey(ctx, key, keybits);
}

int mbedtls_aes_crypt_ecb(mbedtls_aes_context *ctx, int mode, const unsigned char input[16], unsigned char output[16])
{
    return esp_aes_crypt_ecb(ctx, mode, input, output);
}

#endif
