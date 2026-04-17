/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/zcl_common.h>
#include <ezbee/zcl/zcl_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------------------------------------------*
   PRESSURE_MEASUREMENT Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the pressure_measurement cluster implementation */
#define EZB_ZCL_PRESSURE_MEASUREMENT_CLUSTER_REVISION (2)

/**
 * @brief Attribute identifiers for the pressure_measurement server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_PRESSURE_MEASUREMENT_MEASURED_VALUE_ID     = 0x0000U, /*!< MeasuredValue attribute. */
    EZB_ZCL_ATTR_PRESSURE_MEASUREMENT_MIN_MEASURED_VALUE_ID = 0x0001U, /*!< MinMeasuredValue attribute. */
    EZB_ZCL_ATTR_PRESSURE_MEASUREMENT_MAX_MEASURED_VALUE_ID = 0x0002U, /*!< MaxMeasuredValue attribute. */
    EZB_ZCL_ATTR_PRESSURE_MEASUREMENT_TOLERANCE_ID          = 0x0003U, /*!< Tolerance attribute. */
    EZB_ZCL_ATTR_PRESSURE_MEASUREMENT_SCALED_VALUE_ID       = 0x0010U, /*!< ScaledValue attribute. */
    EZB_ZCL_ATTR_PRESSURE_MEASUREMENT_MIN_SCALED_VALUE_ID   = 0x0011U, /*!< MinScaledValue attribute. */
    EZB_ZCL_ATTR_PRESSURE_MEASUREMENT_MAX_SCALED_VALUE_ID   = 0x0012U, /*!< MaxScaledValue attribute. */
    EZB_ZCL_ATTR_PRESSURE_MEASUREMENT_SCALED_TOLERANCE_ID   = 0x0013U, /*!< ScaledTolerance attribute. */
    EZB_ZCL_ATTR_PRESSURE_MEASUREMENT_SCALE_ID              = 0x0014U, /*!< Scale attribute. */
} ezb_zcl_pressure_measurement_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the PressureMeasurement server cluster.
 */
typedef struct ezb_zcl_pressure_measurement_cluster_server_config_s {
    int16_t measured_value;     /*!< Configurable mandatory MeasuredValue attribute */
    int16_t min_measured_value; /*!< Configurable mandatory MinMeasuredValue attribute */
    int16_t max_measured_value; /*!< Configurable mandatory MaxMeasuredValue attribute */
} ezb_zcl_pressure_measurement_cluster_server_config_t;

/** @brief Default value of MeasuredValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MEASURED_VALUE_DEFAULT_VALUE ((int16_t)0x8000)

/** @brief Default value of MinMeasuredValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MIN_MEASURED_VALUE_DEFAULT_VALUE ((int16_t)0x8001)

/** @brief Minimum value of MinMeasuredValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MIN_MEASURED_VALUE_MIN_VALUE ((int16_t)0x8001)

/** @brief Maximum value of MinMeasuredValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MIN_MEASURED_VALUE_MAX_VALUE (0x7ffe)
/** @brief Default value of MaxMeasuredValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MAX_MEASURED_VALUE_DEFAULT_VALUE ((int16_t)0x8000)

/** @brief Minimum value of MaxMeasuredValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MAX_MEASURED_VALUE_MIN_VALUE ((int16_t)0x8002)

/** @brief Maximum value of MaxMeasuredValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MAX_MEASURED_VALUE_MAX_VALUE (0x7fff)

/** @brief Minimum value of Tolerance in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_TOLERANCE_MIN_VALUE (0x0000)

/** @brief Maximum value of Tolerance in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_TOLERANCE_MAX_VALUE (0x0800)
/** @brief Default value of ScaledValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_SCALED_VALUE_DEFAULT_VALUE (0x0000)

/** @brief Default value of MinScaledValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MIN_SCALED_VALUE_DEFAULT_VALUE ((int16_t)0x8000)

/** @brief Minimum value of MinScaledValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MIN_SCALED_VALUE_MIN_VALUE ((int16_t)0x8001)

/** @brief Maximum value of MinScaledValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MIN_SCALED_VALUE_MAX_VALUE (0x7ffe)
/** @brief Default value of MaxScaledValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MAX_SCALED_VALUE_DEFAULT_VALUE ((int16_t)0x8000)

/** @brief Minimum value of MaxScaledValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MAX_SCALED_VALUE_MIN_VALUE ((int16_t)0x8002)

/** @brief Maximum value of MaxScaledValue in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_MAX_SCALED_VALUE_MAX_VALUE (0x7fff)

/** @brief Minimum value of ScaledTolerance in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_SCALED_TOLERANCE_MIN_VALUE (0x0000)

/** @brief Maximum value of ScaledTolerance in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_SCALED_TOLERANCE_MAX_VALUE (0x0800)

/** @brief Minimum value of Scale in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_SCALE_MIN_VALUE (0x81)

/** @brief Maximum value of Scale in PressureMeasurement cluster */
#define EZB_ZCL_PRESSURE_MEASUREMENT_SCALE_MAX_VALUE (0x7f)

typedef ezb_zcl_pressure_measurement_cluster_server_config_t ezb_zcl_pressure_measurement_cluster_config_t;

/**
 * @brief Add an attribute to an pressure_measurement cluster descriptor.
 *
 * @param cluster_desc Pointer to the pressure_measurement cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_pressure_measurement_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                             uint16_t               attr_id,
                                                             const void            *value);

/**
 * @brief Create an pressure_measurement cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the pressure_measurement cluster configuration structure, refer to
 * ezb_zcl_pressure_measurement_cluster_server_config_t or ezb_zcl_pressure_measurement_cluster_client_config_t or NULL (default
 * config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_pressure_measurement_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the PressureMeasurement cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_pressure_measurement_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the PressureMeasurement cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_pressure_measurement_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_PRESSURE_MEASUREMENT_CLIENT_ROLE_INIT ezb_zcl_pressure_measurement_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_PRESSURE_MEASUREMENT_SERVER_ROLE_INIT ezb_zcl_pressure_measurement_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
