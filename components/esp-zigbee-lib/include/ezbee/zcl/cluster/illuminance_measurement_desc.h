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
   ILLUMINANCE_MEASUREMENT Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the illuminance_measurement cluster implementation */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_CLUSTER_REVISION (2)

/**
 * @brief Attribute identifiers for the illuminance_measurement server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_ILLUMINANCE_MEASUREMENT_MEASURED_VALUE_ID     = 0x0000U, /*!< MeasuredValue attribute. */
    EZB_ZCL_ATTR_ILLUMINANCE_MEASUREMENT_MIN_MEASURED_VALUE_ID = 0x0001U, /*!< MinMeasuredValue attribute. */
    EZB_ZCL_ATTR_ILLUMINANCE_MEASUREMENT_MAX_MEASURED_VALUE_ID = 0x0002U, /*!< MaxMeasuredValue attribute. */
    EZB_ZCL_ATTR_ILLUMINANCE_MEASUREMENT_TOLERANCE_ID          = 0x0003U, /*!< Tolerance attribute. */
    EZB_ZCL_ATTR_ILLUMINANCE_MEASUREMENT_LIGHT_SENSOR_TYPE_ID  = 0x0004U, /*!< LightSensorType attribute. */
} ezb_zcl_illuminance_measurement_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the IlluminanceMeasurement server cluster.
 */
typedef struct ezb_zcl_illuminance_measurement_cluster_server_config_s {
    uint16_t measured_value;     /*!< Configurable mandatory MeasuredValue attribute */
    uint16_t min_measured_value; /*!< Configurable mandatory MinMeasuredValue attribute */
    uint16_t max_measured_value; /*!< Configurable mandatory MaxMeasuredValue attribute */
} ezb_zcl_illuminance_measurement_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL LightSensorType attribute of IlluminanceMeasurement.
 */
typedef enum {
    EZB_ZCL_ILLUMINANCE_MEASUREMENT_LIGHT_SENSOR_TYPE_PHOTODIODE = 0x00U, /*!< Photodiode */
    EZB_ZCL_ILLUMINANCE_MEASUREMENT_LIGHT_SENSOR_TYPE_CMOS       = 0x01U, /*!< CMOS */
    EZB_ZCL_ILLUMINANCE_MEASUREMENT_LIGHT_SENSOR_TYPE_UNKNOWN    = 0xffU, /*!< Unknown */
} ezb_zcl_illuminance_measurement_server_light_sensor_type_t;

/** @brief Default value of MeasuredValue in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_MEASURED_VALUE_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of MeasuredValue in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_MEASURED_VALUE_MIN_VALUE (0x0000)

/** @brief Maximum value of MeasuredValue in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_MEASURED_VALUE_MAX_VALUE (0xffff)
/** @brief Default value of MinMeasuredValue in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_MIN_MEASURED_VALUE_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of MinMeasuredValue in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_MIN_MEASURED_VALUE_MIN_VALUE (0x0001)

/** @brief Maximum value of MinMeasuredValue in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_MIN_MEASURED_VALUE_MAX_VALUE (0xfffd)
/** @brief Default value of MaxMeasuredValue in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_MAX_MEASURED_VALUE_DEFAULT_VALUE (0xfffe)

/** @brief Minimum value of MaxMeasuredValue in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_MAX_MEASURED_VALUE_MIN_VALUE (0x0002)

/** @brief Maximum value of MaxMeasuredValue in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_MAX_MEASURED_VALUE_MAX_VALUE (0xfffe)

/** @brief Minimum value of Tolerance in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_TOLERANCE_MIN_VALUE (0x0000)

/** @brief Maximum value of Tolerance in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_TOLERANCE_MAX_VALUE (0x0800)
/** @brief Default value of LightSensorType in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_LIGHT_SENSOR_TYPE_DEFAULT_VALUE (0xff)

/** @brief Minimum value of LightSensorType in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_LIGHT_SENSOR_TYPE_MIN_VALUE (0x00)

/** @brief Maximum value of LightSensorType in IlluminanceMeasurement cluster */
#define EZB_ZCL_ILLUMINANCE_MEASUREMENT_LIGHT_SENSOR_TYPE_MAX_VALUE (0xff)

typedef ezb_zcl_illuminance_measurement_cluster_server_config_t ezb_zcl_illuminance_measurement_cluster_config_t;

/**
 * @brief Add an attribute to an illuminance_measurement cluster descriptor.
 *
 * @param[in] cluster_desc The illuminance_measurement cluster descriptor.
 * @param[in] attr_id      The identifier of the attribute to be added to @p cluster_desc.
 * @param[in] value        The pointer to the initial value of the attribute.
 * @return Error code.
 */
ezb_err_t ezb_zcl_illuminance_measurement_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                                uint16_t               attr_id,
                                                                const void            *value);

/**
 * @brief Create an illuminance_measurement cluster descriptor.
 *
 * @param[in] cluster_cfg  The pointer to the illuminance_measurement cluster configuration structure.
                           Use ezb_zcl_illuminance_measurement_cluster_server_config_t for EZB_ZCL_CLUSTER_SERVER,
                           use ezb_zcl_illuminance_measurement_cluster_client_config_t for EZB_ZCL_CLUSTER_CLIENT,
                           or use NULL for default configuration of the stack based on the @p role_mask.
 * @param[in] role_mask    The role of the cluster to create.
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_illuminance_measurement_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the IlluminanceMeasurement cluster client role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs initialization.
 */
void ezb_zcl_illuminance_measurement_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the IlluminanceMeasurement cluster server role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs de-initialization.
 */
void ezb_zcl_illuminance_measurement_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_ILLUMINANCE_MEASUREMENT_CLIENT_ROLE_INIT ezb_zcl_illuminance_measurement_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_ILLUMINANCE_MEASUREMENT_SERVER_ROLE_INIT ezb_zcl_illuminance_measurement_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
