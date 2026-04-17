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
   MULTISTATE_VALUE Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the multistate_value cluster implementation */
#define EZB_ZCL_MULTISTATE_VALUE_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the multistate_value server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_MULTISTATE_VALUE_STATE_TEXT_ID         = 0x000eU, /*!< StateText attribute. */
    EZB_ZCL_ATTR_MULTISTATE_VALUE_DESCRIPTION_ID        = 0x001cU, /*!< Description attribute. */
    EZB_ZCL_ATTR_MULTISTATE_VALUE_NUMBER_OF_STATES_ID   = 0x004aU, /*!< NumberOfStates attribute. */
    EZB_ZCL_ATTR_MULTISTATE_VALUE_OUT_OF_SERVICE_ID     = 0x0051U, /*!< OutOfService attribute. */
    EZB_ZCL_ATTR_MULTISTATE_VALUE_PRESENT_VALUE_ID      = 0x0055U, /*!< PresentValue attribute. */
    EZB_ZCL_ATTR_MULTISTATE_VALUE_PRIORITY_ARRAY_ID     = 0x0057U, /*!< PriorityArray attribute. */
    EZB_ZCL_ATTR_MULTISTATE_VALUE_RELIABILITY_ID        = 0x0067U, /*!< Reliability attribute. */
    EZB_ZCL_ATTR_MULTISTATE_VALUE_RELINQUISH_DEFAULT_ID = 0x0068U, /*!< RelinquishDefault attribute. */
    EZB_ZCL_ATTR_MULTISTATE_VALUE_STATUS_FLAGS_ID       = 0x006fU, /*!< StatusFlags attribute. */
    EZB_ZCL_ATTR_MULTISTATE_VALUE_APPLICATION_TYPE_ID   = 0x0100U, /*!< ApplicationType attribute. */
} ezb_zcl_multistate_value_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the MultistateValue server cluster.
 */
typedef struct ezb_zcl_multistate_value_cluster_server_config_s {
    uint16_t number_of_states; /*!< Configurable mandatory NumberOfStates attribute */
    bool     out_of_service;   /*!< Configurable mandatory OutOfService attribute */
    uint16_t present_value;    /*!< Configurable mandatory PresentValue attribute */
    uint8_t  status_flags;     /*!< Configurable mandatory StatusFlags attribute */
} ezb_zcl_multistate_value_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL Reliability attribute of MultistateValue.
 */
typedef enum {
    EZB_ZCL_MULTISTATE_VALUE_RELIABILITY_NO_FAULT_DETECTED   = 0x00U, /*!< NoFaultDetected */
    EZB_ZCL_MULTISTATE_VALUE_RELIABILITY_NO_SENSOR           = 0x01U, /*!< NoSensor */
    EZB_ZCL_MULTISTATE_VALUE_RELIABILITY_OVER_RANGE          = 0x02U, /*!< OverRange */
    EZB_ZCL_MULTISTATE_VALUE_RELIABILITY_UNDER_RANGE         = 0x03U, /*!< UnderRange */
    EZB_ZCL_MULTISTATE_VALUE_RELIABILITY_OPEN_LOOP           = 0x04U, /*!< OpenLoop */
    EZB_ZCL_MULTISTATE_VALUE_RELIABILITY_SHORTED_LOOP        = 0x05U, /*!< ShortedLoop */
    EZB_ZCL_MULTISTATE_VALUE_RELIABILITY_NO_OUTPUT           = 0x06U, /*!< NoOutput */
    EZB_ZCL_MULTISTATE_VALUE_RELIABILITY_UNRELIABLE_OTHER    = 0x07U, /*!< UnreliableOther */
    EZB_ZCL_MULTISTATE_VALUE_RELIABILITY_PROCESS_ERROR       = 0x08U, /*!< ProcessError */
    EZB_ZCL_MULTISTATE_VALUE_RELIABILITY_MULTI_STATE_FAULT   = 0x09U, /*!< MultiStateFault */
    EZB_ZCL_MULTISTATE_VALUE_RELIABILITY_CONFIGURATION_ERROR = 0x0AU, /*!< ConfigurationError */
} ezb_zcl_multistate_value_server_reliability_t;

/**
 * @brief Enumeration for ZCL ApplicationType attribute of MultistateValue.
 */
typedef enum {
    EZB_ZCL_MULTISTATE_VALUE_APPLICATION_TYPE_APP_DOMAIN_HVAC = 0x00U, /*!< AppDomainHVAC */
} ezb_zcl_multistate_value_server_application_type_t;

/**
 * @brief Bitmap for ZCL StatusFlags attribute of MultistateValue.
 */
typedef enum {
    EZB_ZCL_MULTISTATE_VALUE_STATUS_FLAGS_IN_ALARM       = 0x01U, /*!< InAlarm */
    EZB_ZCL_MULTISTATE_VALUE_STATUS_FLAGS_FAULT          = 0x02U, /*!< Fault */
    EZB_ZCL_MULTISTATE_VALUE_STATUS_FLAGS_OVERRIDDEN     = 0x04U, /*!< Overridden */
    EZB_ZCL_MULTISTATE_VALUE_STATUS_FLAGS_OUT_OF_SERVICE = 0x08U, /*!< OutOfService */
} ezb_zcl_multistate_value_server_status_flags_t;

/** @brief Default value of NumberOfStates in MultistateValue cluster */
#define EZB_ZCL_MULTISTATE_VALUE_NUMBER_OF_STATES_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of NumberOfStates in MultistateValue cluster */
#define EZB_ZCL_MULTISTATE_VALUE_NUMBER_OF_STATES_MIN_VALUE (0x0001)

/** @brief Maximum value of NumberOfStates in MultistateValue cluster */
#define EZB_ZCL_MULTISTATE_VALUE_NUMBER_OF_STATES_MAX_VALUE (0xffff)
/** @brief Default value of OutOfService in MultistateValue cluster */
#define EZB_ZCL_MULTISTATE_VALUE_OUT_OF_SERVICE_DEFAULT_VALUE (0x00)

/** @brief Default value of Reliability in MultistateValue cluster */
#define EZB_ZCL_MULTISTATE_VALUE_RELIABILITY_DEFAULT_VALUE (0x00)

/** @brief Default value of StatusFlags in MultistateValue cluster */
#define EZB_ZCL_MULTISTATE_VALUE_STATUS_FLAGS_DEFAULT_VALUE (0x00)

/** @brief Minimum value of StatusFlags in MultistateValue cluster */
#define EZB_ZCL_MULTISTATE_VALUE_STATUS_FLAGS_MIN_VALUE (0x00)

/** @brief Maximum value of StatusFlags in MultistateValue cluster */
#define EZB_ZCL_MULTISTATE_VALUE_STATUS_FLAGS_MAX_VALUE (0x0f)

/** @brief Minimum value of ApplicationType in MultistateValue cluster */
#define EZB_ZCL_MULTISTATE_VALUE_APPLICATION_TYPE_MIN_VALUE (0x00000000)

/** @brief Maximum value of ApplicationType in MultistateValue cluster */
#define EZB_ZCL_MULTISTATE_VALUE_APPLICATION_TYPE_MAX_VALUE (0xffffffff)

typedef ezb_zcl_multistate_value_cluster_server_config_t ezb_zcl_multistate_value_cluster_config_t;

/**
 * @brief Add an attribute to an multistate_value cluster descriptor.
 *
 * @param cluster_desc Pointer to the multistate_value cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_multistate_value_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                         uint16_t               attr_id,
                                                         const void            *value);

/**
 * @brief Create an multistate_value cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the multistate_value cluster configuration structure, refer to
 * ezb_zcl_multistate_value_cluster_server_config_t or ezb_zcl_multistate_value_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_multistate_value_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the MultistateValue cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_multistate_value_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the MultistateValue cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_multistate_value_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_MULTISTATE_VALUE_CLIENT_ROLE_INIT ezb_zcl_multistate_value_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_MULTISTATE_VALUE_SERVER_ROLE_INIT ezb_zcl_multistate_value_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
