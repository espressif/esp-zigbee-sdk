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
   SHADE_CONFIG Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the shade_config cluster implementation */
#define EZB_ZCL_SHADE_CONFIG_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the shade_config server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_SHADE_CONFIG_PHYSICAL_CLOSED_LIMIT_ID = 0x0000U, /*!< PhysicalClosedLimit attribute. */
    EZB_ZCL_ATTR_SHADE_CONFIG_MOTOR_STEP_SIZE_ID       = 0x0001U, /*!< MotorStepSize attribute. */
    EZB_ZCL_ATTR_SHADE_CONFIG_STATUS_ID                = 0x0002U, /*!< Status attribute. */
    EZB_ZCL_ATTR_SHADE_CONFIG_CLOSED_LIMIT_ID          = 0x0010U, /*!< ClosedLimit attribute. */
    EZB_ZCL_ATTR_SHADE_CONFIG_MODE_ID                  = 0x0011U, /*!< Mode attribute. */
} ezb_zcl_shade_config_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the ShadeConfig server cluster.
 */
typedef struct ezb_zcl_shade_config_cluster_server_config_s {
    uint8_t  status;       /*!< Configurable mandatory Status attribute */
    uint16_t closed_limit; /*!< Configurable mandatory ClosedLimit attribute */
    uint8_t  mode;         /*!< Configurable mandatory Mode attribute */
} ezb_zcl_shade_config_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL Mode attribute of ShadeConfig.
 */
typedef enum {
    EZB_ZCL_SHADE_CONFIG_MODE_NORMAL    = 0x00U, /*!< Normal */
    EZB_ZCL_SHADE_CONFIG_MODE_CONFIGURE = 0x01U, /*!< Configure */
} ezb_zcl_shade_config_server_mode_t;

/**
 * @brief Bitmap for ZCL Status attribute of ShadeConfig.
 */
typedef enum {
    EZB_ZCL_SHADE_CONFIG_STATUS_SHADE_OPERATIONAL          = 0x01U, /*!< ShadeOperational */
    EZB_ZCL_SHADE_CONFIG_STATUS_SHADE_ADJUSTING            = 0x02U, /*!< ShadeAdjusting */
    EZB_ZCL_SHADE_CONFIG_STATUS_SHADE_DIRECTION            = 0x04U, /*!< ShadeDirection */
    EZB_ZCL_SHADE_CONFIG_STATUS_FORWARD_DIRECTION_OF_MOTOR = 0x08U, /*!< ForwardDirectionOfMotor */
} ezb_zcl_shade_config_server_status_t;

/** @brief Minimum value of PhysicalClosedLimit in ShadeConfig cluster */
#define EZB_ZCL_SHADE_CONFIG_PHYSICAL_CLOSED_LIMIT_MIN_VALUE (0x0001)

/** @brief Maximum value of PhysicalClosedLimit in ShadeConfig cluster */
#define EZB_ZCL_SHADE_CONFIG_PHYSICAL_CLOSED_LIMIT_MAX_VALUE (0xfffe)

/** @brief Minimum value of MotorStepSize in ShadeConfig cluster */
#define EZB_ZCL_SHADE_CONFIG_MOTOR_STEP_SIZE_MIN_VALUE (0x00)

/** @brief Maximum value of MotorStepSize in ShadeConfig cluster */
#define EZB_ZCL_SHADE_CONFIG_MOTOR_STEP_SIZE_MAX_VALUE (0xfe)
/** @brief Default value of Status in ShadeConfig cluster */
#define EZB_ZCL_SHADE_CONFIG_STATUS_DEFAULT_VALUE (0x00)

/** @brief Default value of ClosedLimit in ShadeConfig cluster */
#define EZB_ZCL_SHADE_CONFIG_CLOSED_LIMIT_DEFAULT_VALUE (0x0001)

/** @brief Minimum value of ClosedLimit in ShadeConfig cluster */
#define EZB_ZCL_SHADE_CONFIG_CLOSED_LIMIT_MIN_VALUE (0x0001)

/** @brief Maximum value of ClosedLimit in ShadeConfig cluster */
#define EZB_ZCL_SHADE_CONFIG_CLOSED_LIMIT_MAX_VALUE (0xfffe)
/** @brief Default value of Mode in ShadeConfig cluster */
#define EZB_ZCL_SHADE_CONFIG_MODE_DEFAULT_VALUE (0x00)

/** @brief Minimum value of Mode in ShadeConfig cluster */
#define EZB_ZCL_SHADE_CONFIG_MODE_MIN_VALUE (0x00)

/** @brief Maximum value of Mode in ShadeConfig cluster */
#define EZB_ZCL_SHADE_CONFIG_MODE_MAX_VALUE (0xfe)

typedef ezb_zcl_shade_config_cluster_server_config_t ezb_zcl_shade_config_cluster_config_t;

/**
 * @brief Add an attribute to an shade_config cluster descriptor.
 *
 * @param[in] cluster_desc The shade_config cluster descriptor.
 * @param[in] attr_id      The identifier of the attribute to be added to @p cluster_desc.
 * @param[in] value        The pointer to the initial value of the attribute.
 * @return Error code.
 */
ezb_err_t ezb_zcl_shade_config_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an shade_config cluster descriptor.
 *
 * @param[in] cluster_cfg  The pointer to the shade_config cluster configuration structure.
                           Use ezb_zcl_shade_config_cluster_server_config_t for EZB_ZCL_CLUSTER_SERVER,
                           use ezb_zcl_shade_config_cluster_client_config_t for EZB_ZCL_CLUSTER_CLIENT,
                           or use NULL for default configuration of the stack based on the @p role_mask.
 * @param[in] role_mask    The role of the cluster to create.
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_shade_config_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the ShadeConfig cluster client role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs initialization.
 */
void ezb_zcl_shade_config_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the ShadeConfig cluster server role for a given endpoint.
 *
 * @param[in] ep_id The identifier of the endpoint hosting the cluster that needs de-initialization.
 */
void ezb_zcl_shade_config_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_SHADE_CONFIG_CLIENT_ROLE_INIT ezb_zcl_shade_config_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_SHADE_CONFIG_SERVER_ROLE_INIT ezb_zcl_shade_config_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
