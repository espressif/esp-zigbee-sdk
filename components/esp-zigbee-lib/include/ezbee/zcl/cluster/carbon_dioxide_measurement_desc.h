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
   CARBON_DIOXIDE_MEASUREMENT Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the carbon_dioxide_measurement cluster implementation */
#define EZB_ZCL_CARBON_DIOXIDE_MEASUREMENT_CLUSTER_REVISION (2)

/**
 * @brief Attribute identifiers for the carbon_dioxide_measurement server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_CARBON_DIOXIDE_MEASUREMENT_MEASURED_VALUE_ID     = 0x0000U, /*!< MeasuredValue attribute. */
    EZB_ZCL_ATTR_CARBON_DIOXIDE_MEASUREMENT_MIN_MEASURED_VALUE_ID = 0x0001U, /*!< MinMeasuredValue attribute. */
    EZB_ZCL_ATTR_CARBON_DIOXIDE_MEASUREMENT_MAX_MEASURED_VALUE_ID = 0x0002U, /*!< MaxMeasuredValue attribute. */
    EZB_ZCL_ATTR_CARBON_DIOXIDE_MEASUREMENT_TOLERANCE_ID          = 0x0003U, /*!< Tolerance attribute. */
} ezb_zcl_carbon_dioxide_measurement_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the CarbonDioxideMeasurement server cluster.
 */
typedef struct ezb_zcl_carbon_dioxide_measurement_cluster_server_config_s {
    float measured_value;     /*!< Configurable mandatory MeasuredValue attribute */
    float min_measured_value; /*!< Configurable mandatory MinMeasuredValue attribute */
    float max_measured_value; /*!< Configurable mandatory MaxMeasuredValue attribute */
} ezb_zcl_carbon_dioxide_measurement_cluster_server_config_t;

/** @brief Default value of MeasuredValue in CarbonDioxideMeasurement cluster */
#define EZB_ZCL_CARBON_DIOXIDE_MEASUREMENT_MEASURED_VALUE_DEFAULT_VALUE (.0 / .0)

/** @brief Default value of MinMeasuredValue in CarbonDioxideMeasurement cluster */
#define EZB_ZCL_CARBON_DIOXIDE_MEASUREMENT_MIN_MEASURED_VALUE_DEFAULT_VALUE (.0 / .0)

/** @brief Minimum value of MinMeasuredValue in CarbonDioxideMeasurement cluster */
#define EZB_ZCL_CARBON_DIOXIDE_MEASUREMENT_MIN_MEASURED_VALUE_MIN_VALUE (0.0)

/** @brief Default value of MaxMeasuredValue in CarbonDioxideMeasurement cluster */
#define EZB_ZCL_CARBON_DIOXIDE_MEASUREMENT_MAX_MEASURED_VALUE_DEFAULT_VALUE (.0 / .0)

/** @brief Maximum value of MaxMeasuredValue in CarbonDioxideMeasurement cluster */
#define EZB_ZCL_CARBON_DIOXIDE_MEASUREMENT_MAX_MEASURED_VALUE_MAX_VALUE (1.0)

typedef ezb_zcl_carbon_dioxide_measurement_cluster_server_config_t ezb_zcl_carbon_dioxide_measurement_cluster_config_t;

/**
 * @brief Add an attribute to an carbon_dioxide_measurement cluster descriptor.
 *
 * @param cluster_desc Pointer to the carbon_dioxide_measurement cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_carbon_dioxide_measurement_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                                   uint16_t               attr_id,
                                                                   const void            *value);

/**
 * @brief Create an carbon_dioxide_measurement cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the carbon_dioxide_measurement cluster configuration structure, refer to
 * ezb_zcl_carbon_dioxide_measurement_cluster_server_config_t or ezb_zcl_carbon_dioxide_measurement_cluster_client_config_t or
 * NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_carbon_dioxide_measurement_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the CarbonDioxideMeasurement cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_carbon_dioxide_measurement_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the CarbonDioxideMeasurement cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_carbon_dioxide_measurement_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_CARBON_DIOXIDE_MEASUREMENT_CLIENT_ROLE_INIT ezb_zcl_carbon_dioxide_measurement_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_CARBON_DIOXIDE_MEASUREMENT_SERVER_ROLE_INIT ezb_zcl_carbon_dioxide_measurement_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
