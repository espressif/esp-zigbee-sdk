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
   METER_IDENTIFICATION Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the meter_identification cluster implementation */
#define EZB_ZCL_METER_IDENTIFICATION_CLUSTER_REVISION (2)

/**
 * @brief Attribute identifiers for the meter_identification server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_METER_IDENTIFICATION_COMPANY_NAME_ID      = 0x0000U, /*!< CompanyName attribute. */
    EZB_ZCL_ATTR_METER_IDENTIFICATION_METER_TYPE_ID_ID     = 0x0001U, /*!< MeterTypeID attribute. */
    EZB_ZCL_ATTR_METER_IDENTIFICATION_DATA_QUALITY_ID_ID   = 0x0004U, /*!< DataQualityID attribute. */
    EZB_ZCL_ATTR_METER_IDENTIFICATION_CUSTOMER_NAME_ID     = 0x0005U, /*!< CustomerName attribute. */
    EZB_ZCL_ATTR_METER_IDENTIFICATION_MODEL_ID             = 0x0006U, /*!< Model attribute. */
    EZB_ZCL_ATTR_METER_IDENTIFICATION_PART_NUMBER_ID       = 0x0007U, /*!< PartNumber attribute. */
    EZB_ZCL_ATTR_METER_IDENTIFICATION_PRODUCT_REVISION_ID  = 0x0008U, /*!< ProductRevision attribute. */
    EZB_ZCL_ATTR_METER_IDENTIFICATION_SOFTWARE_REVISION_ID = 0x000aU, /*!< SoftwareRevision attribute. */
    EZB_ZCL_ATTR_METER_IDENTIFICATION_UTILITY_NAME_ID      = 0x000bU, /*!< UtilityName attribute. */
    EZB_ZCL_ATTR_METER_IDENTIFICATION_POD_ID               = 0x000cU, /*!< POD attribute. */
    EZB_ZCL_ATTR_METER_IDENTIFICATION_AVAILABLE_POWER_ID   = 0x000dU, /*!< AvailablePower attribute. */
    EZB_ZCL_ATTR_METER_IDENTIFICATION_POWER_THRESHOLD_ID   = 0x000eU, /*!< PowerThreshold attribute. */
} ezb_zcl_meter_identification_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the MeterIdentification server cluster.
 */
typedef struct ezb_zcl_meter_identification_cluster_server_config_s {
    char    *company_name;    /*!< Configurable mandatory CompanyName attribute */
    uint16_t meter_type_id;   /*!< Configurable mandatory MeterTypeID attribute */
    uint16_t data_quality_id; /*!< Configurable mandatory DataQualityID attribute */
    char    *pod;             /*!< Configurable mandatory POD attribute */
    int32_t  available_power; /*!< Configurable mandatory AvailablePower attribute */
    int32_t  power_threshold; /*!< Configurable mandatory PowerThreshold attribute */
} ezb_zcl_meter_identification_cluster_server_config_t;

typedef ezb_zcl_meter_identification_cluster_server_config_t ezb_zcl_meter_identification_cluster_config_t;

/**
 * @brief Add an attribute to an meter_identification cluster descriptor.
 *
 * @param cluster_desc Pointer to the meter_identification cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_meter_identification_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                             uint16_t               attr_id,
                                                             const void            *value);

/**
 * @brief Create an meter_identification cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the meter_identification cluster configuration structure, refer to
 * ezb_zcl_meter_identification_cluster_server_config_t or ezb_zcl_meter_identification_cluster_client_config_t or NULL (default
 * config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_meter_identification_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the MeterIdentification cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_meter_identification_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the MeterIdentification cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_meter_identification_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_METER_IDENTIFICATION_CLIENT_ROLE_INIT ezb_zcl_meter_identification_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_METER_IDENTIFICATION_SERVER_ROLE_INIT ezb_zcl_meter_identification_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
