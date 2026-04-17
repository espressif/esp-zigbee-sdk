/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_ERROR_H
#define ESP_ZIGBEE_ERROR_H

#include <stdint.h>

#include <ezbee/platform/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Error code representation.
 * @anchor ezb_err_t
 */
typedef int ezb_err_t;

/**
 * @brief Error code category
 *
 * @anchor ezb_err_category_t
 *
 */
typedef enum {
    EZB_ERR_CATEGORY_GENERIC, /*!< Generic error */
    EZB_ERR_CATEGORY_MAC,     /*!< Mac layer error */
    EZB_ERR_CATEGORY_NWK,     /*!< NWK layer error */
    EZB_ERR_CATEGORY_APS,     /*!< APS layer error */
    EZB_ERR_CATEGORY_ZDP,     /*!< ZDP error */
    EZB_ERR_CATEGORY_ZCL,     /*!< ZCL layer error */

    EZB_ERR_CATEGORY_MAX_NR,  /*!< Total category number */
} ezb_err_category_t;

/**
 * @def EZB_MAKE_ERROR
 *
 * Construct an error code with category and code value.
 *
 * @param[in] category The category of the error, refer to @ref ezb_err_category_t.
 * @param[in] code The code value indicating the error within the category.
 *
 */
#define EZB_MAKE_ERROR(category, code) ((ezb_err_t)((code) == 0 ? 0 : ((((category) & 0xff) << 8) | ((code) & 0xff))))

/**
 * @brief Get the the error category of a given error code.
 *
 * @param err Error code.
 *
 * @return The category of the given error code, refer to @ref ezb_err_category_t
 *
 */
static inline ezb_err_category_t ezb_get_err_category(ezb_err_t err)
{
    return (ezb_err_category_t)((err >> 8) & 0xff);
}

/**
 * @brief Get the original status enumerations of the error code.
 *
 * @param err Error code.
 *
 * @return An 8-bit value
 *
 */
static inline uint8_t ezb_get_err_value(ezb_err_t err)
{
    return (uint8_t)(err & 0xff);
}

#define EZB_ERR_NONE 0  /*!< Success without error */
#define EZB_ERR_FAIL -1 /*!< Generic failure */

#define EZB_ERR_NO_MEM        EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x01) /*!< No sufficient memory */
#define EZB_ERR_INV_ARG       EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x02) /*!< Invalid argument */
#define EZB_ERR_INV_STATE     EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x03) /*!< Invalid state */
#define EZB_ERR_INV_SIZE      EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x04) /*!< Invalid size */
#define EZB_ERR_NOT_FOUND     EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x05) /*!< Requested resource not found */
#define EZB_ERR_NOT_SUPPORTED EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x06) /*!< Operation is not supported */
#define EZB_ERR_TIMEOUT       EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x07) /*!< Operation timed out */
#define EZB_ERR_ABORT         EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x08) /*!< Operation is aborted */
#define EZB_ERR_BUSY          EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x09) /*!< Busy state */
#define EZB_ERR_NOT_FINISHED  EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x0C) /*!< Operation is not fully finished */
#define EZB_ERR_NOT_ALLOWED   EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x0D) /*!< Operation is not allowed */

#define EZB_ERR_PARSE         EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x10) /*!< Fail to parse frame/packet */
#define EZB_ERR_EMPTY_DATA    EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x11) /*!< Received Empty data */
#define EZB_ERR_DROP          EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x12) /*!< Frame is dropped */
#define EZB_ERR_SECURITY      EZB_MAKE_ERROR(EZB_ERR_CATEGORY_GENERIC, 0x13) /*!< Fail to process security */

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_ERROR_H */
