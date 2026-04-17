/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_PLATFORM_TOOLCHAIN_H
#define ESP_ZIGBEE_PLATFORM_TOOLCHAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def EZB_HAS_BUILTIN
 *
 * Check whether the compiler supports a given builtin.
 *
 * @param[in] builtin The builtin name to check.
 *
 */
#ifdef __has_builtin
#define EZB_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
#define EZB_HAS_BUILTIN(builtin) 0
#endif

/**
 * @def EZB_HAS_GNU_ATTRIBUTE
 *
 * Check whether the compiler supports a given GNU attribute.
 *
 * @param[in] attribute The attribute name to check.
 *
 */
#ifdef __has_attribute
#define EZB_HAS_GNU_ATTRIBUTE(attribute) __has_attribute(attribute)
#else
#define EZB_HAS_GNU_ATTRIBUTE(attribute) 0
#endif

/**
 * @def EZB_CRITICAL_RESULT
 *
 * Compiler-specific indication that the function result must be used.
 *
 */
#if EZB_HAS_GNU_ATTRIBUTE(warn_unused_result)
#define EZB_CRITICAL_RESULT __attribute__((warn_unused_result))
#else
#define EZB_CRITICAL_RESULT
#endif

/**
 * @def EZB_PACKED_BEGIN
 *
 * Compiler-specific indication that a class or struct must be byte packed.
 *
 */

/**
 * @def EZB_PACKED_FIELD
 *
 * Indicate to the compiler a nested struct or union to be packed within byte packed class or struct.
 *
 */

/**
 * @def EZB_PACKED_END
 *
 * Compiler-specific indication at the end of a byte packed class or struct.
 *
 */
#if EZB_HAS_GNU_ATTRIBUTE(packed)
#define EZB_PACKED_BEGIN
#define EZB_PACKED_FIELD __attribute__((packed))
#define EZB_PACKED_END   __attribute__((packed))
#else
#define EZB_PACKED_BEGIN
#define EZB_PACKED_FIELD
#define EZB_PACKED_END
#error "packed" attribute is not supported by the toolchain!
#endif

/**
 * @def EZB_WEAK
 *
 * Compiler-specific weak symbol modifier.
 *
 */
#if EZB_HAS_GNU_ATTRIBUTE(weak)
#define EZB_WEAK __attribute__((weak))
#else
#define EZB_WEAK
#endif

/**
 * @def EZB_EXPERIMENTAL
 *
 * Compiler-specific experimental symbol modifier.
 *
 */
#if EZB_HAS_GNU_ATTRIBUTE(warning)
#define EZB_EXPERIMENTAL __attribute__((warning ("Experimental API!")))
#else
#define EZB_EXPERIMENTAL
#endif

/**
 * @def EZB_DEPRECATED
 *
 * Compiler-specific deprecated symbol modifier.
 *
 */
#if EZB_HAS_GNU_ATTRIBUTE(deprecated)
#define EZB_DEPRECATED __attribute__((deprecated))
#define EZB_DEPRECATED_MSG(msg) __attribute__((deprecated (msg)))
#else
#define EZB_DEPRECATED
#define EZB_DEPRECATED_MSG(msg)
#endif

/**
 * @def EZB_UNAVAILABLE
 *
 * Compiler-specific deprecated symbol modifier.
 *
 */
#if EZB_HAS_GNU_ATTRIBUTE(unavailable)
#define EZB_UNAVAILABLE __attribute__((unavailable))
#define EZB_UNAVAILABLE_MSG(msg) __attribute__((unavailable (msg)))
#else
#define EZB_UNAVAILABLE
#define EZB_UNAVAILABLE_MSG(msg)
#endif

/**
 * @def EZB_PRINTF
 *
 * Compiler-specific indication that `printf` style arguments check must be done.
 *
 * Specifies that a function or method takes `printf` style arguments and should be type-checked against
 * a format string.
 *
 * @param[in] fmt_index The argument index of the format string, start from 1.
 * @param[in] va_index The argument index of the first variadic argument, start from 1.
 *
 */
#if EZB_HAS_GNU_ATTRIBUTE(format)
#define EZB_PRINTF(fmt_index, va_index) __attribute__((format(printf, fmt_index, va_index)))
#else
#define EZB_PRINTF(fmt_index, va_index)
#endif

/**
 * @def EZB_CONSTRUCTOR
 *
 * Compiler-specific indication that function is a constructor.
 *
 */
#if EZB_HAS_GNU_ATTRIBUTE(constructor)
#define EZB_CONSTRUCTOR __attribute__((constructor))
#else
#define EZB_CONSTRUCTOR
#error "constructor" attribute is not supported by the toolchain!
#endif

#if EZB_HAS_GNU_ATTRIBUTE(fallthrough)
#define EZB_FALLTHROUGH __attribute__((fallthrough))
#else
#define EZB_FALLTHROUGH
#endif

#if EZB_HAS_GNU_ATTRIBUTE(unused)
#define EZB_MAYBE_UNUSED __attribute__((unused))
#else
#define EZB_MAYBE_UNUSED
#endif

#if EZB_HAS_GNU_ATTRIBUTE(alias)
#define EZB_ALIAS(alias_name) __attribute__((alias(#alias_name)))
#else
#error "alias" attribute is not supported by the toolchain!
#endif

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_PLATFORM_TOOLCHAIN_H */
