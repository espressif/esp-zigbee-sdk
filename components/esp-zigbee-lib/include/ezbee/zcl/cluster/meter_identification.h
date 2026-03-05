/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/meter_identification_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Meter type (MeterTypeID attribute values).
 */
typedef enum {
    EZB_ZCL_METER_TYPE_UTILITY_PRIMARY    = 0x0000,  /*!< Utility primary meter. */
    EZB_ZCL_METER_TYPE_UTILITY_PRODUCTION = 0x0001,  /*!< Utility production meter. */
    EZB_ZCL_METER_TYPE_UTILITY_SECONDARY  = 0x0002,  /*!< Utility secondary meter. */
    EZB_ZCL_METER_TYPE_PRIVATE_PRIMARY    = 0x0100,  /*!< Private primary meter. */
    EZB_ZCL_METER_TYPE_PRIVATE_PRODUCTION = 0x0101,  /*!< Private production meter. */
    EZB_ZCL_METER_TYPE_PRIVATE_SECONDARY  = 0x0102,  /*!< Private secondary meter. */
    EZB_ZCL_METER_TYPE_GENERIC            = 0x0110   /*!< Generic meter. */
} ezb_zcl_meter_identification_meter_type_t;

/**
 * @brief Data quality (DataQualityID attribute values).
 */
typedef enum {
    EZB_ZCL_DATA_QUALITY_ALL_DATA_CERTIFIED                       = 0x0000,  /*!< All data certified. */
    EZB_ZCL_DATA_QUALITY_ONLY_INSTANTANEOUS_POWER_NOT_CERTIFIED   = 0x0001,  /*!< Only instantaneous power not certified. */
    EZB_ZCL_DATA_QUALITY_ONLY_CUMULATED_CONSUMPTION_NOT_CERTIFIED = 0x0002,  /*!< Only cumulated consumption not certified. */
    EZB_ZCL_DATA_QUALITY_NOT_CERTIFIED_DATA                       = 0x0003   /*!< Not certified data. */
} ezb_zcl_meter_identification_data_quality_t;

/**
 * @brief Max length of Company Name attribute.
 */
#define EZB_ZCL_ATTR_METER_IDENTIFICATION_COMPANY_NAME_MAX_LENGTH 16

/**
 * @brief Max length of POD (Point of Delivery) attribute.
 */
#define EZB_ZCL_ATTR_METER_IDENTIFICATION_POD_MAX_LENGTH 16

#ifdef __cplusplus
} /* extern "C" */
#endif
