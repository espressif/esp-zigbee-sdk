/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/binary_value_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Binary Value cluster application types
 *      The ApplicationType attribute indicates the specific application usage
 *      for the cluster. ApplicationType is subdivided into Group, Type and
 *      an Index number, as follows:
 *
 *      Group = Bits 24 to 31
 *        An indication of the cluster this attribute is part of. Binary Input
 *        clusters have Group = 0x00.
 *
 *      Type = Bits 16 to 23
 *        The physical quantity that the PresentValue attribute of the cluster
 *        represents.
 *
 *      Index = Bits 0 to 15
 *        The specific application usage of the cluster.
 */

/**
 * @brief Macros for Group ID of ZCL Binary Value
 */
#define EZB_ZCL_BV_GROUP_ID 0x05

/**
 * @brief Macros for ApplicationType attribute of ZCL Binary Value
 */
#define EZB_ZCL_BV_SET_APP_TYPE_WITH_ID(_type, _id) \
    (((EZB_ZCL_BV_GROUP_ID & 0xFF) << 24) | (((_type) & 0xFF) << 16) | ((_id) & 0xFFFF))

/** @brief Values for Binary Value cluster HVAC application usages */
typedef enum {
    EZB_ZCL_BV_TYPE_FALSE_OFF_NORMAL = EZB_ZCL_BV_SET_APP_TYPE_WITH_ID(0x00, 0x0000), /*!< Present Value = 0 represents False, Off, Normal */
    EZB_ZCL_BV_TYPE_TRUE_ON_ALARM,                                                    /*!< Present Value = 1 represents True, On, Alarm */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_BV_TYPE_OTHER = EZB_ZCL_BV_SET_APP_TYPE_WITH_ID(0x00, 0xFFFF)             /*!< Other */
} ezb_zcl_bv_type_t;

#ifdef __cplusplus
} /*  extern "C" */
#endif
