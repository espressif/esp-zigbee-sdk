/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ezbee/platform/crypto.h"

#define MBEDTLS_ALLOW_PRIVATE_ACCESS
#include <mbedtls/ecp.h>
#undef MBEDTLS_ALLOW_PRIVATE_ACCESS

ezb_err_t ezb_plat_crypto_ecdh_init(ezb_crypto_context_t *ctx, ezb_crypto_ecc_curve_id_t curve_id)
{
    ezb_err_t error = EZB_ERR_NONE;
    mbedtls_ecp_keypair *keypair;

    if (ctx == NULL || ctx->ctx == NULL) {
        return EZB_ERR_INV_ARG;
    }

    if (ctx->ctx_size < sizeof(*keypair)) {
        return EZB_ERR_FAIL;
    } else {
        keypair = (mbedtls_ecp_keypair *)ctx->ctx;
    }

    mbedtls_ecp_group_id grp_id = MBEDTLS_ECP_DP_NONE;
    mbedtls_ecp_group *grp = &keypair->grp;

    switch (curve_id) {
    case EZB_CRYPTO_ECC_CURVE25519:
        grp_id = MBEDTLS_ECP_DP_CURVE25519;
        break;
    case EZB_CRYPTO_ECC_SECP256R1:
        grp_id = MBEDTLS_ECP_DP_SECP256R1;
        break;
    default:
        return EZB_ERR_NOT_SUPPORTED;
    }

    mbedtls_ecp_keypair_init(keypair);
    if (mbedtls_ecp_group_load(grp, grp_id) != 0) {
        error = EZB_ERR_FAIL;
    }

    return error;
}
