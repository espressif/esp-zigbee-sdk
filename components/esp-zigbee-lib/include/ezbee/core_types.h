/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_CORE_TYPES_H
#define ESP_ZIGBEE_CORE_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include <ezbee/error.h>
#include <ezbee/platform/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Address mode definition.
 * @anchor ezb_addr_mode_e
 */
enum ezb_addr_mode_e {
    /**
     * MAC: PAN ID and address fields are not present.
     * NWK: Reserved.
     * APS: DstAddress and DstEndpoint not present.
     */
    EZB_ADDR_MODE_NONE = 0,
    /**
     * MAC: Reserved.
     * NWK: Reserved.
     * APS: 16-bit group address for DstAddress; DstEndpoint not present.
     */
    EZB_ADDR_MODE_GROUP = 1,
    /**
     * MAC: Address field contains a short address (16 bit).
     * NWK: 16-bit network address of a device or a 16-bit broadcast address.
     * APS: 16-bit address for DstAddress and DstEndpoint present.
     */
    EZB_ADDR_MODE_SHORT = 2,
    /**
     * MAC: Address field contains an extended address (64 bit).
     * NWK: Reserved.
     * APS: 64-bit extended address for DstAddress and DstEndpoint present.
     */
    EZB_ADDR_MODE_EXT = 3,
};

/**
 * @brief Represents the IEEE 802.15.4 Address Mode.
 */
typedef uint8_t ezb_addr_mode_t;

/**
 * @brief Represents the IEEE 802.15.4 PAN ID.
 */
typedef uint16_t ezb_panid_t;

/**
 * @brief Represents the IEEE 802.15.4 Short Address.
 */
typedef uint16_t ezb_shortaddr_t;

/**
 * @brief Represents the IEEE 802 64-bit extended universal identifier (EUI-64)
 */
EZB_PACKED_BEGIN
struct ezb_eui64_s {
    union {
        uint8_t u8[8];  /*!< Extended Address as byte array */
        uint64_t u64;   /*!< Extended Address as 64-bit value */
    } EZB_PACKED_FIELD;
} EZB_PACKED_END;

/**
 * @brief Represents the IEEE 802.15.4 Extended Address.
 */
typedef struct ezb_eui64_s ezb_extaddr_t;

/**
 * @brief Represents the Zigbee Extended PAN ID.
 */
typedef struct ezb_eui64_s ezb_extpanid_t;

/**
 * @brief Represents the Zigbee APS Group Delivery Information.
 */
typedef struct ezb_grpaddr_s {
    ezb_shortaddr_t group;  /*!< 16-bit group address */
    ezb_shortaddr_t bcast;  /*!< 16-bit broadcast address, used for transmission */
} ezb_grpaddr_t;

/**
 * @brief Represents a union of IEEE 802.15.4 Short & Extended Address.
 */
typedef union ezb_addr_u {
    ezb_shortaddr_t short_addr;   /*!< 16-bit network short address */
    ezb_grpaddr_t group_addr;     /*!< Group address information */
    ezb_extaddr_t extended_addr;  /*!< 64-bit extended address */
} ezb_addr_t;

/**
 * @brief Represents a common address with address mode.
 */
typedef struct ezb_address_s {
    ezb_addr_mode_t addr_mode;  /*!< Address mode, refer to @ref ezb_addr_mode_e */
    ezb_addr_t u;               /*!< The data of address, refer to @ref ezb_addr_u */
} ezb_address_t;

/**
 * @brief Compare two EUI-64.
 *
 * @param[in] eui64_1 The first EUI-64.
 * @param[in] eui64_2 The second EUI-64.
 *
 * @return
 *     - True:  The two EUI-64 are equal.
 *     - False: The two EUI-64 are not equal.
 */
static inline bool ezb_eui64_compare(const struct ezb_eui64_s *eui64_1, const struct ezb_eui64_s *eui64_2)
{
    return eui64_1->u64 == eui64_2->u64;
}

/**
 * @brief Copy an EUI-64.
 *
 * @param[out] dst The destination EUI-64 .
 * @param[in]  src The source EUI-64.
 */
static inline void ezb_eui64_copy(struct ezb_eui64_s *dst, const struct ezb_eui64_s *src)
{
    dst->u64 = src->u64;
}

/**
 * @brief Check if all the bits of an EUI-64 are zeros.
 *
 * @param[in] eui64 The EUI-64 to check.
 *
 * @return
 *     - True:  All the bits of the EUI-64 are zeros.
 *     - False: Not all the bits of the EUI-64 are zeros.
 */
static inline bool ezb_eui64_is_all_zero(const struct ezb_eui64_s *eui64)
{
    return eui64->u64 == 0;
}

/**
 * @brief Set all the bits of an EUI-64 to zeros.
 *
 * @param[in] eui64 The EUI-64 to set.
 */
static inline void ezb_eui64_set_all_zero(struct ezb_eui64_s *eui64)
{
    eui64->u64 = 0;
}

/**
 * @brief Check if all the bits of an EUI-64 are ones.
 *
 * @param[in] eui64 The EUI-64 to check.
 *
 * @return
 *     - True:  All the bits of the EUI-64 are ones.
 *     - False: Not all the bits of the EUI-64 are ones.
 */
static inline bool ezb_eui64_is_all_ones(const struct ezb_eui64_s *eui64)
{
    return eui64->u64 == UINT64_MAX;
}

/**
 * @brief Set all the bits of an EUI-64 to ones.
 *
 * @param[in] eui64 The EUI-64 to set.
 */
static inline void ezb_eui64_set_all_ones(struct ezb_eui64_s *eui64)
{
    eui64->u64 = UINT64_MAX;
}

/**
 * @brief Check if an EUI-64 is invalid.
 *
 * An EUI-64 is invalid if all the bits are zeros or ones.
 *
 * @param[in] eui64 The EUI-64 to check.
 *
 * @return
 *     - True:  The EUI-64 is invalid.
 *     - False: The EUI-64 is valid.
 */
static inline bool ezb_eui64_is_invalid(const struct ezb_eui64_s *eui64)
{
    return ezb_eui64_is_all_zero(eui64) || ezb_eui64_is_all_ones(eui64);
}

/**
 * @def EZB_ADDRESS_SHORT
 *
 * Create a @ref ezb_address_s with EZB_ADDR_MODE_SHORT.
 *
 * @param[in] addr The short address.
 *
 * @return The @ref ezb_address_s with EZB_ADDR_MODE_SHORT.
 */
#define EZB_ADDRESS_SHORT(addr)                                 \
    (ezb_address_t)                                             \
    {                                                           \
        .addr_mode = EZB_ADDR_MODE_SHORT, .u.short_addr = addr, \
    }

/**
 * @def EZB_ADDRESS_EXTENDED
 *
 * Create a @ref ezb_address_s with EZB_ADDR_MODE_EXT.
 *
 * @param[in] addr The extended address.
 *
 * @return The @ref ezb_address_s with EZB_ADDR_MODE_EXT.
 */
#define EZB_ADDRESS_EXTENDED(addr)                               \
    (ezb_address_t)                                              \
    {                                                            \
        .addr_mode = EZB_ADDR_MODE_EXT, .u.extended_addr = addr, \
    }

/**
 * @def EZB_ADDRESS_NONE
 *
 * Create a @ref ezb_address_s with EZB_ADDR_MODE_NONE.
 *
 * @return The @ref ezb_address_s with EZB_ADDR_MODE_NONE.
 */
#define EZB_ADDRESS_NONE()               \
    (ezb_address_t)                      \
    {                                    \
        .addr_mode = EZB_ADDR_MODE_NONE, \
    }

/**
 * @def EZB_ADDRESS_GROUP
 *
 * Create a @ref ezb_address_s with EZB_ADDR_MODE_GROUP.
 *
 * @param[in] g The group address.
 * @param[in] b The broadcast address.
 *
 * @return The @ref ezb_address_s with EZB_ADDR_MODE_GROUP.
 */
#define EZB_ADDRESS_GROUP(g, b)           \
    (ezb_address_t)                       \
    {                                     \
        .addr_mode = EZB_ADDR_MODE_GROUP, \
        .u.group_addr.group = (g),        \
        .u.group_addr.bcast = (b),        \
    }

/**
 * @brief Set the address mode to EZB_ADDR_MODE_SHORT.
 *
 * @param[in] address The address to set.
 * @param[in] short_addr The short address to set.
 */
static inline void ezb_address_set_short(ezb_address_t *address, ezb_shortaddr_t short_addr)
{
    address->addr_mode = EZB_ADDR_MODE_SHORT;
    address->u.short_addr = short_addr;
}

/**
 * @brief Set the address to EZB_ADDR_MODE_EXT.
 *
 * @param[in] address The address to set.
 * @param[in] extended_addr The extended address to set.
 */
static inline void ezb_address_set_extended(ezb_address_t *address, ezb_extaddr_t extended_addr)
{
    address->addr_mode = EZB_ADDR_MODE_EXT;
    ezb_eui64_copy(&address->u.extended_addr, &extended_addr);
}

/**
 * @brief Set the address to EZB_ADDR_MODE_NONE.
 *
 * @param[in] address The address to set.
 */
static inline void ezb_address_set_none(ezb_address_t *address)
{
    address->addr_mode = EZB_ADDR_MODE_NONE;
    ezb_eui64_set_all_zero(&address->u.extended_addr);
}

/**
 * @brief Check if the address is equal to a short address.
 *
 * @param[in] addr The address to check.
 * @param[in] short_addr The short address.
 *
 * @return
 *     - True:  The mode is EZB_ADDR_MODE_SHORT and the address is equal to the short address.
 *     - False: The mode is not EZB_ADDR_MODE_SHORT or the address is not equal to the short address.
 */
static inline bool ezb_address_is_short(const ezb_address_t *addr, ezb_shortaddr_t short_addr)
{
    return addr->addr_mode == EZB_ADDR_MODE_SHORT && addr->u.short_addr == short_addr;
}

/**
 * @brief Check if the address is equal to an extended address.
 *
 * @param[in] addr The address to check.
 * @param[in] extended_addr The extended address.
 *
 * @return
 *     - True:  The mode is EZB_ADDR_MODE_EXT and the address is equal to the extended address.
 *     - False: The mode is not EZB_ADDR_MODE_EXT or the address is not equal to the extended address.
 */
static inline bool ezb_address_is_extended(const ezb_address_t *addr, ezb_extaddr_t extended_addr)
{
    return addr->addr_mode == EZB_ADDR_MODE_EXT && ezb_eui64_compare(&addr->u.extended_addr, &extended_addr);
}

/**
 * @brief Compare two addresses.
 *
 * @param[in] addr1 The first address.
 * @param[in] addr2 The second address.
 *
 * @return
 *     - True:  The two addresses are equal.
 *     - False: The two addresses are not equal.
 */
static inline bool ezb_address_compare(const ezb_address_t *addr1, const ezb_address_t *addr2)
{
    return (addr1->addr_mode == addr2->addr_mode) &&
        (addr1->addr_mode == EZB_ADDR_MODE_SHORT ? addr1->u.short_addr == addr2->u.short_addr
                                                 : addr1->u.extended_addr.u64 == addr2->u.extended_addr.u64);
}

#define EZB_AES_KEY_SIZE 16
#define EZB_CCM_KEY_SIZE EZB_AES_KEY_SIZE

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_CORE_TYPES_H */
