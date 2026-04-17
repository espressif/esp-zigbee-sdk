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
   FAN_CONTROL Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the fan_control cluster implementation */
#define EZB_ZCL_FAN_CONTROL_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the fan_control server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_FAN_CONTROL_FAN_MODE_ID          = 0x0000U, /*!< FanMode attribute. */
    EZB_ZCL_ATTR_FAN_CONTROL_FAN_MODE_SEQUENCE_ID = 0x0001U, /*!< FanModeSequence attribute. */
} ezb_zcl_fan_control_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the FanControl server cluster.
 */
typedef struct ezb_zcl_fan_control_cluster_server_config_s {
    uint8_t fan_mode;          /*!< Configurable mandatory FanMode attribute */
    uint8_t fan_mode_sequence; /*!< Configurable mandatory FanModeSequence attribute */
} ezb_zcl_fan_control_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL FanMode attribute of FanControl.
 */
typedef enum {
    EZB_ZCL_FAN_CONTROL_FAN_MODE_OFF    = 0x00U, /*!< Off */
    EZB_ZCL_FAN_CONTROL_FAN_MODE_LOW    = 0x01U, /*!< Low */
    EZB_ZCL_FAN_CONTROL_FAN_MODE_MEDIUM = 0x02U, /*!< Medium */
    EZB_ZCL_FAN_CONTROL_FAN_MODE_HIGH   = 0x03U, /*!< High */
    EZB_ZCL_FAN_CONTROL_FAN_MODE_ON     = 0x04U, /*!< On */
    EZB_ZCL_FAN_CONTROL_FAN_MODE_AUTO   = 0x05U, /*!< Auto */
    EZB_ZCL_FAN_CONTROL_FAN_MODE_SMART  = 0x06U, /*!< Smart */
} ezb_zcl_fan_control_server_fan_mode_t;

/**
 * @brief Enumeration for ZCL FanModeSequence attribute of FanControl.
 */
typedef enum {
    EZB_ZCL_FAN_CONTROL_FAN_MODE_SEQUENCE_LOW_MED_HIGH      = 0x00U, /*!< LowMedHigh */
    EZB_ZCL_FAN_CONTROL_FAN_MODE_SEQUENCE_LOW_HIGH          = 0x01U, /*!< LowHigh */
    EZB_ZCL_FAN_CONTROL_FAN_MODE_SEQUENCE_LOW_MED_HIGH_AUTO = 0x02U, /*!< LowMedHighAuto */
    EZB_ZCL_FAN_CONTROL_FAN_MODE_SEQUENCE_LOW_HIGH_AUTO     = 0x03U, /*!< LowHighAuto */
    EZB_ZCL_FAN_CONTROL_FAN_MODE_SEQUENCE_ON_AUTO           = 0x04U, /*!< OnAuto */
} ezb_zcl_fan_control_server_fan_mode_sequence_t;

/** @brief Default value of FanMode in FanControl cluster */
#define EZB_ZCL_FAN_CONTROL_FAN_MODE_DEFAULT_VALUE (0x05)

/** @brief Minimum value of FanMode in FanControl cluster */
#define EZB_ZCL_FAN_CONTROL_FAN_MODE_MIN_VALUE (0x00)

/** @brief Maximum value of FanMode in FanControl cluster */
#define EZB_ZCL_FAN_CONTROL_FAN_MODE_MAX_VALUE (0x06)
/** @brief Default value of FanModeSequence in FanControl cluster */
#define EZB_ZCL_FAN_CONTROL_FAN_MODE_SEQUENCE_DEFAULT_VALUE (0x02)

/** @brief Minimum value of FanModeSequence in FanControl cluster */
#define EZB_ZCL_FAN_CONTROL_FAN_MODE_SEQUENCE_MIN_VALUE (0x00)

/** @brief Maximum value of FanModeSequence in FanControl cluster */
#define EZB_ZCL_FAN_CONTROL_FAN_MODE_SEQUENCE_MAX_VALUE (0x04)

typedef ezb_zcl_fan_control_cluster_server_config_t ezb_zcl_fan_control_cluster_config_t;

/**
 * @brief Add an attribute to an fan_control cluster descriptor.
 *
 * @param cluster_desc Pointer to the fan_control cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_fan_control_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an fan_control cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the fan_control cluster configuration structure, refer to
 * ezb_zcl_fan_control_cluster_server_config_t or ezb_zcl_fan_control_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_fan_control_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the FanControl cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_fan_control_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the FanControl cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_fan_control_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_FAN_CONTROL_CLIENT_ROLE_INIT ezb_zcl_fan_control_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_FAN_CONTROL_SERVER_ROLE_INIT ezb_zcl_fan_control_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
