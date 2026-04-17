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
   DEHUMIDIFICATION_CONTROL Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the dehumidification_control cluster implementation */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the dehumidification_control server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_ID         = 0x0000U, /*!< RelativeHumidity attribute. */
    EZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_COOLING_ID                   = 0x0001U, /*!< Cooling attribute. */
    EZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_SET_POINT_ID                 = 0x0010U, /*!< SetPoint attribute. */
    EZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_MODE_ID    = 0x0011U, /*!< RelativeHumidityMode attribute. */
    EZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_LOCKOUT_ID  = 0x0012U, /*!< DehumidificationLockout attribute. */
    EZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_HYSTERESIS_ID                = 0x0013U, /*!< Hysteresis attribute. */
    EZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_MAX_COOL_ID                  = 0x0014U, /*!< MaxCool attribute. */
    EZB_ZCL_ATTR_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_DISPLAY_ID = 0x0015U, /*!< RelativeHumidityDisplay attribute. */
} ezb_zcl_dehumidification_control_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the DehumidificationControl server cluster.
 */
typedef struct ezb_zcl_dehumidification_control_cluster_server_config_s {
    uint8_t cooling;    /*!< Configurable mandatory Cooling attribute */
    uint8_t set_point;  /*!< Configurable mandatory SetPoint attribute */
    uint8_t hysteresis; /*!< Configurable mandatory Hysteresis attribute */
    uint8_t max_cool;   /*!< Configurable mandatory MaxCool attribute */
} ezb_zcl_dehumidification_control_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL RelativeHumidityMode attribute of DehumidificationControl.
 */
typedef enum {
    EZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_MODE_MEASURED_LOCALLY         = 0x00U, /*!< MeasuredLocally */
    EZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_MODE_UPDATED_OVER_THE_NETWORK = 0x01U, /*!< UpdatedOverTheNetwork */
} ezb_zcl_dehumidification_control_server_relative_humidity_mode_t;

/**
 * @brief Enumeration for ZCL DehumidificationLockout attribute of DehumidificationControl.
 */
typedef enum {
    EZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_LOCKOUT_DEHUMIDIFICATION_NOT_ALLOWED =
        0x00U, /*!< DehumidificationNotAllowed */
    EZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_LOCKOUT_DEHUMIDIFICATION_ALLOWED = 0x01U, /*!< DehumidificationAllowed */
} ezb_zcl_dehumidification_control_server_dehumidification_lockout_t;

/**
 * @brief Enumeration for ZCL RelativeHumidityDisplay attribute of DehumidificationControl.
 */
typedef enum {
    EZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_DISPLAY_NOT_DISPLAYED = 0x00U, /*!< NotDisplayed */
    EZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_DISPLAY_DISPLAYED     = 0x01U, /*!< Displayed */
} ezb_zcl_dehumidification_control_server_relative_humidity_display_t;

/** @brief Minimum value of RelativeHumidity in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_MIN_VALUE (0x00)

/** @brief Maximum value of RelativeHumidity in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_MAX_VALUE (0x64)

/** @brief Minimum value of Cooling in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_COOLING_MIN_VALUE (0x00)

/** @brief Default value of SetPoint in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_SET_POINT_DEFAULT_VALUE (0x32)

/** @brief Minimum value of SetPoint in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_SET_POINT_MIN_VALUE (0x1e)

/** @brief Maximum value of SetPoint in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_SET_POINT_MAX_VALUE (0x64)
/** @brief Default value of RelativeHumidityMode in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_MODE_DEFAULT_VALUE (0x00)

/** @brief Minimum value of RelativeHumidityMode in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_MODE_MIN_VALUE (0x00)

/** @brief Maximum value of RelativeHumidityMode in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_MODE_MAX_VALUE (0x01)
/** @brief Default value of DehumidificationLockout in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_LOCKOUT_DEFAULT_VALUE (0x01)

/** @brief Minimum value of DehumidificationLockout in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_LOCKOUT_MIN_VALUE (0x00)

/** @brief Maximum value of DehumidificationLockout in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_DEHUMIDIFICATION_LOCKOUT_MAX_VALUE (0x01)
/** @brief Default value of Hysteresis in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_HYSTERESIS_DEFAULT_VALUE (0x02)

/** @brief Minimum value of Hysteresis in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_HYSTERESIS_MIN_VALUE (0x02)

/** @brief Maximum value of Hysteresis in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_HYSTERESIS_MAX_VALUE (0x14)
/** @brief Default value of MaxCool in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_MAX_COOL_DEFAULT_VALUE (0x14)

/** @brief Minimum value of MaxCool in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_MAX_COOL_MIN_VALUE (0x14)

/** @brief Maximum value of MaxCool in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_MAX_COOL_MAX_VALUE (0x64)
/** @brief Default value of RelativeHumidityDisplay in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_DISPLAY_DEFAULT_VALUE (0x00)

/** @brief Minimum value of RelativeHumidityDisplay in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_DISPLAY_MIN_VALUE (0x00)

/** @brief Maximum value of RelativeHumidityDisplay in DehumidificationControl cluster */
#define EZB_ZCL_DEHUMIDIFICATION_CONTROL_RELATIVE_HUMIDITY_DISPLAY_MAX_VALUE (0x01)

typedef ezb_zcl_dehumidification_control_cluster_server_config_t ezb_zcl_dehumidification_control_cluster_config_t;

/**
 * @brief Add an attribute to an dehumidification_control cluster descriptor.
 *
 * @param cluster_desc Pointer to the dehumidification_control cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_dehumidification_control_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                                 uint16_t               attr_id,
                                                                 const void            *value);

/**
 * @brief Create an dehumidification_control cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the dehumidification_control cluster configuration structure, refer to
 * ezb_zcl_dehumidification_control_cluster_server_config_t or ezb_zcl_dehumidification_control_cluster_client_config_t or NULL
 * (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_dehumidification_control_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the DehumidificationControl cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_dehumidification_control_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the DehumidificationControl cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_dehumidification_control_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_DEHUMIDIFICATION_CONTROL_CLIENT_ROLE_INIT ezb_zcl_dehumidification_control_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_DEHUMIDIFICATION_CONTROL_SERVER_ROLE_INIT ezb_zcl_dehumidification_control_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
