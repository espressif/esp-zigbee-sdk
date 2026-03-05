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
   DEVICE_TEMP_CONFIG Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the device_temp_config cluster implementation */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the device_temp_config server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_CURRENT_TEMPERATURE_ID        = 0x0000U, /*!< CurrentTemperature attribute. */
    EZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_MIN_TEMP_EXPERIENCED_ID       = 0x0001U, /*!< MinTempExperienced attribute. */
    EZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_MAX_TEMP_EXPERIENCED_ID       = 0x0002U, /*!< MaxTempExperienced attribute. */
    EZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_OVER_TEMP_TOTAL_DWELL_ID      = 0x0003U, /*!< OverTempTotalDwell attribute. */
    EZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_DEVICE_TEMP_ALARM_MASK_ID     = 0x0010U, /*!< DeviceTempAlarmMask attribute. */
    EZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_LOW_TEMP_THRESHOLD_ID         = 0x0011U, /*!< LowTempThreshold attribute. */
    EZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_HIGH_TEMP_THRESHOLD_ID        = 0x0012U, /*!< HighTempThreshold attribute. */
    EZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_LOW_TEMP_DWELL_TRIP_POINT_ID  = 0x0013U, /*!< LowTempDwellTripPoint attribute. */
    EZB_ZCL_ATTR_DEVICE_TEMP_CONFIG_HIGH_TEMP_DWELL_TRIP_POINT_ID = 0x0014U, /*!< HighTempDwellTripPoint attribute. */
} ezb_zcl_device_temp_config_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the DeviceTempConfig server cluster.
 */
typedef struct ezb_zcl_device_temp_config_cluster_server_config_s {
    int16_t current_temperature; /*!< Configurable mandatory CurrentTemperature attribute */
} ezb_zcl_device_temp_config_cluster_server_config_t;

/**
 * @brief Bitmap for ZCL DeviceTempAlarmMask attribute of DeviceTempConfig.
 */
typedef enum {
    EZB_ZCL_DEVICE_TEMP_CONFIG_DEVICE_TEMP_ALARM_MASK_DEVICE_TEMPERATURE_TOO_LOW  = 0x01U, /*!< DeviceTemperatureTooLow */
    EZB_ZCL_DEVICE_TEMP_CONFIG_DEVICE_TEMP_ALARM_MASK_DEVICE_TEMPERATURE_TOO_HIGH = 0x02U, /*!< DeviceTemperatureTooHigh */
} ezb_zcl_device_temp_config_server_device_temp_alarm_mask_t;

/** @brief Minimum value of CurrentTemperature in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_CURRENT_TEMPERATURE_MIN_VALUE (-200)

/** @brief Maximum value of CurrentTemperature in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_CURRENT_TEMPERATURE_MAX_VALUE (200)

/** @brief Minimum value of MinTempExperienced in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_MIN_TEMP_EXPERIENCED_MIN_VALUE (-200)

/** @brief Maximum value of MinTempExperienced in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_MIN_TEMP_EXPERIENCED_MAX_VALUE (200)

/** @brief Minimum value of MaxTempExperienced in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_MAX_TEMP_EXPERIENCED_MIN_VALUE (-200)

/** @brief Maximum value of MaxTempExperienced in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_MAX_TEMP_EXPERIENCED_MAX_VALUE (200)
/** @brief Default value of OverTempTotalDwell in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_OVER_TEMP_TOTAL_DWELL_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of OverTempTotalDwell in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_OVER_TEMP_TOTAL_DWELL_MIN_VALUE (0x0000)

/** @brief Maximum value of OverTempTotalDwell in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_OVER_TEMP_TOTAL_DWELL_MAX_VALUE (0xffff)
/** @brief Default value of DeviceTempAlarmMask in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_DEVICE_TEMP_ALARM_MASK_DEFAULT_VALUE (0x00)

/** @brief Minimum value of LowTempThreshold in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_LOW_TEMP_THRESHOLD_MIN_VALUE (-200)

/** @brief Maximum value of LowTempThreshold in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_LOW_TEMP_THRESHOLD_MAX_VALUE (200)

/** @brief Minimum value of HighTempThreshold in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_HIGH_TEMP_THRESHOLD_MIN_VALUE (-200)

/** @brief Maximum value of HighTempThreshold in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_HIGH_TEMP_THRESHOLD_MAX_VALUE (200)

/** @brief Minimum value of LowTempDwellTripPoint in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_LOW_TEMP_DWELL_TRIP_POINT_MIN_VALUE (0x000000)

/** @brief Maximum value of LowTempDwellTripPoint in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_LOW_TEMP_DWELL_TRIP_POINT_MAX_VALUE (0xffffff)

/** @brief Minimum value of HighTempDwellTripPoint in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_HIGH_TEMP_DWELL_TRIP_POINT_MIN_VALUE (0x000000)

/** @brief Maximum value of HighTempDwellTripPoint in DeviceTempConfig cluster */
#define EZB_ZCL_DEVICE_TEMP_CONFIG_HIGH_TEMP_DWELL_TRIP_POINT_MAX_VALUE (0xffffff)

typedef ezb_zcl_device_temp_config_cluster_server_config_t ezb_zcl_device_temp_config_cluster_config_t;

/**
 * @brief Add an attribute to an device_temp_config cluster descriptor.
 *
 * @param cluster_desc Pointer to the device_temp_config cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_device_temp_config_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                           uint16_t               attr_id,
                                                           const void            *value);

/**
 * @brief Create an device_temp_config cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the device_temp_config cluster configuration structure, refer to
 * ezb_zcl_device_temp_config_cluster_server_config_t or ezb_zcl_device_temp_config_cluster_client_config_t or NULL (default
 * config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_device_temp_config_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the DeviceTempConfig cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_device_temp_config_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the DeviceTempConfig cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_device_temp_config_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_DEVICE_TEMP_CONFIG_CLIENT_ROLE_INIT ezb_zcl_device_temp_config_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_DEVICE_TEMP_CONFIG_SERVER_ROLE_INIT ezb_zcl_device_temp_config_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
