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
   OCCUPANCY_SENSING Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the occupancy_sensing cluster implementation */
#define EZB_ZCL_OCCUPANCY_SENSING_CLUSTER_REVISION (2)

/**
 * @brief Attribute identifiers for the occupancy_sensing server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_OCCUPANCY_SENSING_OCCUPANCY_ID                    = 0x0000U, /*!< Occupancy attribute. */
    EZB_ZCL_ATTR_OCCUPANCY_SENSING_OCCUPANCY_SENSOR_TYPE_ID        = 0x0001U, /*!< OccupancySensorType attribute. */
    EZB_ZCL_ATTR_OCCUPANCY_SENSING_OCCUPANCY_SENSOR_TYPE_BITMAP_ID = 0x0002U, /*!< OccupancySensorTypeBitmap attribute. */
    EZB_ZCL_ATTR_OCCUPANCY_SENSING_PIR_OCCUPIED_TO_UNOCCUPIED_DELAY_ID =
        0x0010U, /*!< PIROccupiedToUnoccupiedDelay attribute. */
    EZB_ZCL_ATTR_OCCUPANCY_SENSING_PIR_UNOCCUPIED_TO_OCCUPIED_DELAY_ID =
        0x0011U, /*!< PIRUnoccupiedToOccupiedDelay attribute. */
    EZB_ZCL_ATTR_OCCUPANCY_SENSING_PIR_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_ID =
        0x0012U, /*!< PIRUnoccupiedToOccupiedThreshold attribute. */
    EZB_ZCL_ATTR_OCCUPANCY_SENSING_ULTRASONIC_OCCUPIED_TO_UNOCCUPIED_DELAY_ID =
        0x0020U, /*!< UltrasonicOccupiedToUnoccupiedDelay attribute. */
    EZB_ZCL_ATTR_OCCUPANCY_SENSING_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_DELAY_ID =
        0x0021U, /*!< UltrasonicUnoccupiedToOccupiedDelay attribute. */
    EZB_ZCL_ATTR_OCCUPANCY_SENSING_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_ID =
        0x0022U, /*!< UltrasonicUnoccupiedToOccupiedThreshold attribute. */
    EZB_ZCL_ATTR_OCCUPANCY_SENSING_PHYSICAL_CONTACT_OCCUPIED_TO_UNOCCUPIED_DELAY_ID =
        0x0030U, /*!< PhysicalContactOccupiedToUnoccupiedDelay attribute. */
    EZB_ZCL_ATTR_OCCUPANCY_SENSING_PHYSICAL_CONTACT_UNOCCUPIED_TO_OCCUPIED_DELAY_ID =
        0x0031U, /*!< PhysicalContactUnoccupiedToOccupiedDelay attribute. */
    EZB_ZCL_ATTR_OCCUPANCY_SENSING_PHYSICAL_CONTACT_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_ID =
        0x0032U, /*!< PhysicalContactUnoccupiedToOccupiedThreshold attribute. */
} ezb_zcl_occupancy_sensing_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the OccupancySensing server cluster.
 */
typedef struct ezb_zcl_occupancy_sensing_cluster_server_config_s {
    uint8_t occupancy;                    /*!< Configurable mandatory Occupancy attribute */
    uint8_t occupancy_sensor_type;        /*!< Configurable mandatory OccupancySensorType attribute */
    uint8_t occupancy_sensor_type_bitmap; /*!< Configurable mandatory OccupancySensorTypeBitmap attribute */
} ezb_zcl_occupancy_sensing_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL OccupancySensorType attribute of OccupancySensing.
 */
typedef enum {
    EZB_ZCL_OCCUPANCY_SENSING_OCCUPANCY_SENSOR_TYPE_PIR                = 0x00U, /*!< PIR */
    EZB_ZCL_OCCUPANCY_SENSING_OCCUPANCY_SENSOR_TYPE_ULTRASONIC         = 0x01U, /*!< Ultrasonic */
    EZB_ZCL_OCCUPANCY_SENSING_OCCUPANCY_SENSOR_TYPE_PIR_AND_ULTRASONIC = 0x02U, /*!< PIRAndUltrasonic */
    EZB_ZCL_OCCUPANCY_SENSING_OCCUPANCY_SENSOR_TYPE_PHYSICAL_CONTACT   = 0x03U, /*!< PhysicalContact */
} ezb_zcl_occupancy_sensing_server_occupancy_sensor_type_t;

/**
 * @brief Bitmap for ZCL Occupancy attribute of OccupancySensing.
 */
typedef enum {
    EZB_ZCL_OCCUPANCY_SENSING_OCCUPANCY_UNOCCUPIED = 0x00U, /*!< unoccupied */
    EZB_ZCL_OCCUPANCY_SENSING_OCCUPANCY_OCCUPIED   = 0x01U, /*!< occupied */
} ezb_zcl_occupancy_sensing_server_occupancy_t;

/**
 * @brief Bitmap for ZCL OccupancySensorTypeBitmap attribute of OccupancySensing.
 */
typedef enum {
    EZB_ZCL_OCCUPANCY_SENSING_OCCUPANCY_SENSOR_TYPE_BITMAP_PIR              = 0x01U, /*!< PIR */
    EZB_ZCL_OCCUPANCY_SENSING_OCCUPANCY_SENSOR_TYPE_BITMAP_ULTRASONIC       = 0x02U, /*!< Ultrasonic */
    EZB_ZCL_OCCUPANCY_SENSING_OCCUPANCY_SENSOR_TYPE_BITMAP_PHYSICAL_CONTACT = 0x04U, /*!< PhysicalContact */
} ezb_zcl_occupancy_sensing_server_occupancy_sensor_type_bitmap_t;

/** @brief Default value of PIROccupiedToUnoccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PIR_OCCUPIED_TO_UNOCCUPIED_DELAY_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of PIROccupiedToUnoccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PIR_OCCUPIED_TO_UNOCCUPIED_DELAY_MIN_VALUE (0x0000)

/** @brief Maximum value of PIROccupiedToUnoccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PIR_OCCUPIED_TO_UNOCCUPIED_DELAY_MAX_VALUE (0xfffe)
/** @brief Default value of PIRUnoccupiedToOccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PIR_UNOCCUPIED_TO_OCCUPIED_DELAY_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of PIRUnoccupiedToOccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PIR_UNOCCUPIED_TO_OCCUPIED_DELAY_MIN_VALUE (0x0000)

/** @brief Maximum value of PIRUnoccupiedToOccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PIR_UNOCCUPIED_TO_OCCUPIED_DELAY_MAX_VALUE (0xfffe)
/** @brief Default value of PIRUnoccupiedToOccupiedThreshold in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PIR_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_DEFAULT_VALUE (0x01)

/** @brief Minimum value of PIRUnoccupiedToOccupiedThreshold in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PIR_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_MIN_VALUE (0x01)

/** @brief Maximum value of PIRUnoccupiedToOccupiedThreshold in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PIR_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_MAX_VALUE (0xfe)
/** @brief Default value of UltrasonicOccupiedToUnoccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_ULTRASONIC_OCCUPIED_TO_UNOCCUPIED_DELAY_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of UltrasonicOccupiedToUnoccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_ULTRASONIC_OCCUPIED_TO_UNOCCUPIED_DELAY_MIN_VALUE (0x0000)

/** @brief Maximum value of UltrasonicOccupiedToUnoccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_ULTRASONIC_OCCUPIED_TO_UNOCCUPIED_DELAY_MAX_VALUE (0xfffe)
/** @brief Default value of UltrasonicUnoccupiedToOccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_DELAY_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of UltrasonicUnoccupiedToOccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_DELAY_MIN_VALUE (0x0000)

/** @brief Maximum value of UltrasonicUnoccupiedToOccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_DELAY_MAX_VALUE (0xfffe)
/** @brief Default value of UltrasonicUnoccupiedToOccupiedThreshold in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_DEFAULT_VALUE (0x01)

/** @brief Minimum value of UltrasonicUnoccupiedToOccupiedThreshold in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_MIN_VALUE (0x01)

/** @brief Maximum value of UltrasonicUnoccupiedToOccupiedThreshold in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_ULTRASONIC_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_MAX_VALUE (0xfe)
/** @brief Default value of PhysicalContactOccupiedToUnoccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PHYSICAL_CONTACT_OCCUPIED_TO_UNOCCUPIED_DELAY_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of PhysicalContactOccupiedToUnoccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PHYSICAL_CONTACT_OCCUPIED_TO_UNOCCUPIED_DELAY_MIN_VALUE (0x0000)

/** @brief Maximum value of PhysicalContactOccupiedToUnoccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PHYSICAL_CONTACT_OCCUPIED_TO_UNOCCUPIED_DELAY_MAX_VALUE (0xfffe)
/** @brief Default value of PhysicalContactUnoccupiedToOccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PHYSICAL_CONTACT_UNOCCUPIED_TO_OCCUPIED_DELAY_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of PhysicalContactUnoccupiedToOccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PHYSICAL_CONTACT_UNOCCUPIED_TO_OCCUPIED_DELAY_MIN_VALUE (0x0000)

/** @brief Maximum value of PhysicalContactUnoccupiedToOccupiedDelay in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PHYSICAL_CONTACT_UNOCCUPIED_TO_OCCUPIED_DELAY_MAX_VALUE (0xfffe)
/** @brief Default value of PhysicalContactUnoccupiedToOccupiedThreshold in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PHYSICAL_CONTACT_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_DEFAULT_VALUE (0x01)

/** @brief Minimum value of PhysicalContactUnoccupiedToOccupiedThreshold in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PHYSICAL_CONTACT_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_MIN_VALUE (0x01)

/** @brief Maximum value of PhysicalContactUnoccupiedToOccupiedThreshold in OccupancySensing cluster */
#define EZB_ZCL_OCCUPANCY_SENSING_PHYSICAL_CONTACT_UNOCCUPIED_TO_OCCUPIED_THRESHOLD_MAX_VALUE (0xfe)

typedef ezb_zcl_occupancy_sensing_cluster_server_config_t ezb_zcl_occupancy_sensing_cluster_config_t;

/**
 * @brief Add an attribute to an occupancy_sensing cluster descriptor.
 *
 * @param[in] cluster_desc The occupancy_sensing cluster descriptor.
 * @param[in] attr_id      The identifier of the attribute to be added to @p cluster_desc.
 * @param[in] value        The pointer to the initial value of the attribute.
 * @return Error code.
 */
ezb_err_t ezb_zcl_occupancy_sensing_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                          uint16_t               attr_id,
                                                          const void            *value);

/**
 * @brief Create an occupancy_sensing cluster descriptor.
 *
 * @param[in] cluster_cfg  The pointer to the occupancy_sensing cluster configuration structure.
                           Use ezb_zcl_occupancy_sensing_cluster_server_config_t for EZB_ZCL_CLUSTER_SERVER,
                           use ezb_zcl_occupancy_sensing_cluster_client_config_t for EZB_ZCL_CLUSTER_CLIENT,
                           or use NULL for default configuration of the stack based on the @p role_mask.
 * @param[in] role_mask    The role of the cluster to create.
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_occupancy_sensing_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the OccupancySensing cluster client role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs initialization.
 */
void ezb_zcl_occupancy_sensing_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the OccupancySensing cluster server role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs de-initialization.
 */
void ezb_zcl_occupancy_sensing_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_OCCUPANCY_SENSING_CLIENT_ROLE_INIT ezb_zcl_occupancy_sensing_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_OCCUPANCY_SENSING_SERVER_ROLE_INIT ezb_zcl_occupancy_sensing_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
