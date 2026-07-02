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
 * @param[in] cluster_desc The carbon_dioxide_measurement cluster descriptor.
 * @param[in] attr_id      The identifier of the attribute to be added to @p cluster_desc.
 * @param[in] value        The pointer to the initial value of the attribute.
 * @return Error code.
 */
ezb_err_t ezb_zcl_carbon_dioxide_measurement_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                                   uint16_t               attr_id,
                                                                   const void            *value);

/**
 * @brief Create an carbon_dioxide_measurement cluster descriptor.
 *
 * @param[in] cluster_cfg  The pointer to the carbon_dioxide_measurement cluster configuration structure.
                           Use ezb_zcl_carbon_dioxide_measurement_cluster_server_config_t for EZB_ZCL_CLUSTER_SERVER,
                           use ezb_zcl_carbon_dioxide_measurement_cluster_client_config_t for EZB_ZCL_CLUSTER_CLIENT,
                           or use NULL for default configuration of the stack based on the @p role_mask.
 * @param[in] role_mask    The role of the cluster to create.
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_carbon_dioxide_measurement_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the CarbonDioxideMeasurement cluster client role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs initialization.
 */
void ezb_zcl_carbon_dioxide_measurement_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the CarbonDioxideMeasurement cluster server role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs de-initialization.
 */
void ezb_zcl_carbon_dioxide_measurement_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_CARBON_DIOXIDE_MEASUREMENT_CLIENT_ROLE_INIT ezb_zcl_carbon_dioxide_measurement_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_CARBON_DIOXIDE_MEASUREMENT_SERVER_ROLE_INIT ezb_zcl_carbon_dioxide_measurement_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
