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
   ANALOG_INPUT Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the analog_input cluster implementation */
#define EZB_ZCL_ANALOG_INPUT_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the analog_input server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_ANALOG_INPUT_DESCRIPTION_ID       = 0x001cU, /*!< Description attribute. */
    EZB_ZCL_ATTR_ANALOG_INPUT_MAX_PRESENT_VALUE_ID = 0x0041U, /*!< MaxPresentValue attribute. */
    EZB_ZCL_ATTR_ANALOG_INPUT_MIN_PRESENT_VALUE_ID = 0x0045U, /*!< MinPresentValue attribute. */
    EZB_ZCL_ATTR_ANALOG_INPUT_OUT_OF_SERVICE_ID    = 0x0051U, /*!< OutOfService attribute. */
    EZB_ZCL_ATTR_ANALOG_INPUT_PRESENT_VALUE_ID     = 0x0055U, /*!< PresentValue attribute. */
    EZB_ZCL_ATTR_ANALOG_INPUT_RELIABILITY_ID       = 0x0067U, /*!< Reliability attribute. */
    EZB_ZCL_ATTR_ANALOG_INPUT_RESOLUTION_ID        = 0x006aU, /*!< Resolution attribute. */
    EZB_ZCL_ATTR_ANALOG_INPUT_STATUS_FLAGS_ID      = 0x006fU, /*!< StatusFlags attribute. */
    EZB_ZCL_ATTR_ANALOG_INPUT_ENGINEERING_UNITS_ID = 0x0075U, /*!< EngineeringUnits attribute. */
    EZB_ZCL_ATTR_ANALOG_INPUT_APPLICATION_TYPE_ID  = 0x0100U, /*!< ApplicationType attribute. */
} ezb_zcl_analog_input_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the AnalogInput server cluster.
 */
typedef struct ezb_zcl_analog_input_cluster_server_config_s {
    bool    out_of_service; /*!< Configurable mandatory OutOfService attribute */
    float   present_value;  /*!< Configurable mandatory PresentValue attribute */
    uint8_t status_flags;   /*!< Configurable mandatory StatusFlags attribute */
} ezb_zcl_analog_input_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL Reliability attribute of AnalogInput.
 */
typedef enum {
    EZB_ZCL_ANALOG_INPUT_RELIABILITY_NO_FAULT_DETECTED   = 0x00U, /*!< NoFaultDetected */
    EZB_ZCL_ANALOG_INPUT_RELIABILITY_NO_SENSOR           = 0x01U, /*!< NoSensor */
    EZB_ZCL_ANALOG_INPUT_RELIABILITY_OVER_RANGE          = 0x02U, /*!< OverRange */
    EZB_ZCL_ANALOG_INPUT_RELIABILITY_UNDER_RANGE         = 0x03U, /*!< UnderRange */
    EZB_ZCL_ANALOG_INPUT_RELIABILITY_OPEN_LOOP           = 0x04U, /*!< OpenLoop */
    EZB_ZCL_ANALOG_INPUT_RELIABILITY_SHORTED_LOOP        = 0x05U, /*!< ShortedLoop */
    EZB_ZCL_ANALOG_INPUT_RELIABILITY_NO_OUTPUT           = 0x06U, /*!< NoOutput */
    EZB_ZCL_ANALOG_INPUT_RELIABILITY_UNRELIABLE_OTHER    = 0x07U, /*!< UnreliableOther */
    EZB_ZCL_ANALOG_INPUT_RELIABILITY_PROCESS_ERROR       = 0x08U, /*!< ProcessError */
    EZB_ZCL_ANALOG_INPUT_RELIABILITY_MULTI_STATE_FAULT   = 0x09U, /*!< MultiStateFault */
    EZB_ZCL_ANALOG_INPUT_RELIABILITY_CONFIGURATION_ERROR = 0x0AU, /*!< ConfigurationError */
} ezb_zcl_analog_input_server_reliability_t;

/**
 * @brief Enumeration for ZCL ApplicationType attribute of AnalogInput.
 */
typedef enum {
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_TEMPERATURE                = 0x00U, /*!< Temperature */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_HUMIDITY                   = 0x01U, /*!< Humidity */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_PRESSURE                   = 0x02U, /*!< Pressure */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_FLOW                       = 0x03U, /*!< Flow */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_PERCENTAGE                 = 0x04U, /*!< Percentage */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_PPM                        = 0x05U, /*!< PPM */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_RPM                        = 0x06U, /*!< RPM */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_CURRENT_IN_AMPS            = 0x07U, /*!< CurrentInAmps */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_FREQUENCY_IN_HZ            = 0x08U, /*!< FrequencyInHz */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_POWER_IN_WATTS             = 0x09U, /*!< PowerInWatts */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_POWER_IN_KW                = 0x0AU, /*!< PowerInKw */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_ENERGY_IN_KWH              = 0x0BU, /*!< EnergyInKwh */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_COUNT_UNITLESS             = 0x0CU, /*!< CountUnitless */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_ENTHALPY_IN_KJOULES_PER_KG = 0x0DU, /*!< EnthalpyInKjoulesPerKg */
    EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_TIME_IN_SECONDS            = 0x0EU, /*!< TimeInSeconds */
} ezb_zcl_analog_input_server_application_type_t;

/**
 * @brief Bitmap for ZCL StatusFlags attribute of AnalogInput.
 */
typedef enum {
    EZB_ZCL_ANALOG_INPUT_STATUS_FLAGS_IN_ALARM       = 0x01U, /*!< InAlarm */
    EZB_ZCL_ANALOG_INPUT_STATUS_FLAGS_FAULT          = 0x02U, /*!< Fault */
    EZB_ZCL_ANALOG_INPUT_STATUS_FLAGS_OVERRIDDEN     = 0x04U, /*!< Overridden */
    EZB_ZCL_ANALOG_INPUT_STATUS_FLAGS_OUT_OF_SERVICE = 0x08U, /*!< OutOfService */
} ezb_zcl_analog_input_server_status_flags_t;

/** @brief Default value of OutOfService in AnalogInput cluster */
#define EZB_ZCL_ANALOG_INPUT_OUT_OF_SERVICE_DEFAULT_VALUE (0x00)

/** @brief Default value of Reliability in AnalogInput cluster */
#define EZB_ZCL_ANALOG_INPUT_RELIABILITY_DEFAULT_VALUE (0x00)

/** @brief Default value of StatusFlags in AnalogInput cluster */
#define EZB_ZCL_ANALOG_INPUT_STATUS_FLAGS_DEFAULT_VALUE (0x00)

/** @brief Minimum value of StatusFlags in AnalogInput cluster */
#define EZB_ZCL_ANALOG_INPUT_STATUS_FLAGS_MIN_VALUE (0x00)

/** @brief Maximum value of StatusFlags in AnalogInput cluster */
#define EZB_ZCL_ANALOG_INPUT_STATUS_FLAGS_MAX_VALUE (0x0f)

/** @brief Minimum value of EngineeringUnits in AnalogInput cluster */
#define EZB_ZCL_ANALOG_INPUT_ENGINEERING_UNITS_MIN_VALUE (0x0100)

/** @brief Maximum value of EngineeringUnits in AnalogInput cluster */
#define EZB_ZCL_ANALOG_INPUT_ENGINEERING_UNITS_MAX_VALUE (0xffff)

/** @brief Minimum value of ApplicationType in AnalogInput cluster */
#define EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_MIN_VALUE (0x00000000)

/** @brief Maximum value of ApplicationType in AnalogInput cluster */
#define EZB_ZCL_ANALOG_INPUT_APPLICATION_TYPE_MAX_VALUE (0xffffffff)

typedef ezb_zcl_analog_input_cluster_server_config_t ezb_zcl_analog_input_cluster_config_t;

/**
 * @brief Add an attribute to an analog_input cluster descriptor.
 *
 * @param cluster_desc Pointer to the analog_input cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_analog_input_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an analog_input cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the analog_input cluster configuration structure, refer to
 * ezb_zcl_analog_input_cluster_server_config_t or ezb_zcl_analog_input_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_analog_input_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the AnalogInput cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_analog_input_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the AnalogInput cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_analog_input_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_ANALOG_INPUT_CLIENT_ROLE_INIT ezb_zcl_analog_input_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_ANALOG_INPUT_SERVER_ROLE_INIT ezb_zcl_analog_input_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
