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
   LEVEL Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the level cluster implementation */
#define EZB_ZCL_LEVEL_CLUSTER_REVISION (3)

/**
 * @brief Attribute identifiers for the level server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_LEVEL_CURRENT_LEVEL_ID          = 0x0000U, /*!< CurrentLevel attribute. */
    EZB_ZCL_ATTR_LEVEL_REMAINING_TIME_ID         = 0x0001U, /*!< RemainingTime attribute. */
    EZB_ZCL_ATTR_LEVEL_MIN_LEVEL_ID              = 0x0002U, /*!< MinLevel attribute. */
    EZB_ZCL_ATTR_LEVEL_MAX_LEVEL_ID              = 0x0003U, /*!< MaxLevel attribute. */
    EZB_ZCL_ATTR_LEVEL_CURRENT_FREQUENCY_ID      = 0x0004U, /*!< CurrentFrequency attribute. */
    EZB_ZCL_ATTR_LEVEL_MIN_FREQUENCY_ID          = 0x0005U, /*!< MinFrequency attribute. */
    EZB_ZCL_ATTR_LEVEL_MAX_FREQUENCY_ID          = 0x0006U, /*!< MaxFrequency attribute. */
    EZB_ZCL_ATTR_LEVEL_ON_OFF_TRANSITION_TIME_ID = 0x0010U, /*!< OnOffTransitionTime attribute. */
    EZB_ZCL_ATTR_LEVEL_ON_LEVEL_ID               = 0x0011U, /*!< OnLevel attribute. */
    EZB_ZCL_ATTR_LEVEL_ON_TRANSITION_TIME_ID     = 0x0012U, /*!< OnTransitionTime attribute. */
    EZB_ZCL_ATTR_LEVEL_OFF_TRANSITION_TIME_ID    = 0x0013U, /*!< OffTransitionTime attribute. */
    EZB_ZCL_ATTR_LEVEL_DEFAULT_MOVE_RATE_ID      = 0x0014U, /*!< DefaultMoveRate attribute. */
    EZB_ZCL_ATTR_LEVEL_OPTIONS_ID                = 0x000fU, /*!< Options attribute. */
    EZB_ZCL_ATTR_LEVEL_START_UP_CURRENT_LEVEL_ID = 0x4000U, /*!< StartUpCurrentLevel attribute. */
    EZB_ZCL_ATTR_LEVEL_CVC_CONTEXT_ID            = 0xeff0U, /*!< CVCContext attribute. */
} ezb_zcl_level_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the Level server cluster.
 */
typedef struct ezb_zcl_level_cluster_server_config_s {
    uint8_t current_level; /*!< Configurable mandatory CurrentLevel attribute */
} ezb_zcl_level_cluster_server_config_t;

/** @brief Default value of CurrentLevel in Level cluster */
#define EZB_ZCL_LEVEL_CURRENT_LEVEL_DEFAULT_VALUE (0xff)

/** @brief Default value of RemainingTime in Level cluster */
#define EZB_ZCL_LEVEL_REMAINING_TIME_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of RemainingTime in Level cluster */
#define EZB_ZCL_LEVEL_REMAINING_TIME_MIN_VALUE (0x0000)

/** @brief Maximum value of RemainingTime in Level cluster */
#define EZB_ZCL_LEVEL_REMAINING_TIME_MAX_VALUE (0xffff)
/** @brief Default value of MinLevel in Level cluster */
#define EZB_ZCL_LEVEL_MIN_LEVEL_DEFAULT_VALUE (0x00)

/** @brief Default value of MaxLevel in Level cluster */
#define EZB_ZCL_LEVEL_MAX_LEVEL_DEFAULT_VALUE (0xff)

/** @brief Minimum value of MaxLevel in Level cluster */
#define EZB_ZCL_LEVEL_MAX_LEVEL_MIN_VALUE (0x00)

/** @brief Maximum value of MaxLevel in Level cluster */
#define EZB_ZCL_LEVEL_MAX_LEVEL_MAX_VALUE (0xff)
/** @brief Default value of CurrentFrequency in Level cluster */
#define EZB_ZCL_LEVEL_CURRENT_FREQUENCY_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of CurrentFrequency in Level cluster */
#define EZB_ZCL_LEVEL_CURRENT_FREQUENCY_MIN_VALUE (0)

/** @brief Maximum value of CurrentFrequency in Level cluster */
#define EZB_ZCL_LEVEL_CURRENT_FREQUENCY_MAX_VALUE (0xffff)
/** @brief Default value of MinFrequency in Level cluster */
#define EZB_ZCL_LEVEL_MIN_FREQUENCY_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of MinFrequency in Level cluster */
#define EZB_ZCL_LEVEL_MIN_FREQUENCY_MIN_VALUE (0x0000)

/** @brief Maximum value of MinFrequency in Level cluster */
#define EZB_ZCL_LEVEL_MIN_FREQUENCY_MAX_VALUE (0xffff)
/** @brief Default value of MaxFrequency in Level cluster */
#define EZB_ZCL_LEVEL_MAX_FREQUENCY_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of MaxFrequency in Level cluster */
#define EZB_ZCL_LEVEL_MAX_FREQUENCY_MIN_VALUE (0)

/** @brief Maximum value of MaxFrequency in Level cluster */
#define EZB_ZCL_LEVEL_MAX_FREQUENCY_MAX_VALUE (0xffff)
/** @brief Default value of OnOffTransitionTime in Level cluster */
#define EZB_ZCL_LEVEL_ON_OFF_TRANSITION_TIME_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of OnOffTransitionTime in Level cluster */
#define EZB_ZCL_LEVEL_ON_OFF_TRANSITION_TIME_MIN_VALUE (0x0000)

/** @brief Maximum value of OnOffTransitionTime in Level cluster */
#define EZB_ZCL_LEVEL_ON_OFF_TRANSITION_TIME_MAX_VALUE (0xffff)
/** @brief Default value of OnLevel in Level cluster */
#define EZB_ZCL_LEVEL_ON_LEVEL_DEFAULT_VALUE (0xff)

/** @brief Minimum value of OnLevel in Level cluster */
#define EZB_ZCL_LEVEL_ON_LEVEL_MIN_VALUE (0)

/** @brief Maximum value of OnLevel in Level cluster */
#define EZB_ZCL_LEVEL_ON_LEVEL_MAX_VALUE (0xff)
/** @brief Default value of OnTransitionTime in Level cluster */
#define EZB_ZCL_LEVEL_ON_TRANSITION_TIME_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of OnTransitionTime in Level cluster */
#define EZB_ZCL_LEVEL_ON_TRANSITION_TIME_MIN_VALUE (0x0000)

/** @brief Maximum value of OnTransitionTime in Level cluster */
#define EZB_ZCL_LEVEL_ON_TRANSITION_TIME_MAX_VALUE (0xfffe)
/** @brief Default value of OffTransitionTime in Level cluster */
#define EZB_ZCL_LEVEL_OFF_TRANSITION_TIME_DEFAULT_VALUE (0xffff)

/** @brief Minimum value of OffTransitionTime in Level cluster */
#define EZB_ZCL_LEVEL_OFF_TRANSITION_TIME_MIN_VALUE (0x0000)

/** @brief Maximum value of OffTransitionTime in Level cluster */
#define EZB_ZCL_LEVEL_OFF_TRANSITION_TIME_MAX_VALUE (0xfffe)

/** @brief Minimum value of DefaultMoveRate in Level cluster */
#define EZB_ZCL_LEVEL_DEFAULT_MOVE_RATE_MIN_VALUE (0x00)

/** @brief Maximum value of DefaultMoveRate in Level cluster */
#define EZB_ZCL_LEVEL_DEFAULT_MOVE_RATE_MAX_VALUE (0xfe)
/** @brief Default value of Options in Level cluster */
#define EZB_ZCL_LEVEL_OPTIONS_DEFAULT_VALUE (0x00)

/** @brief Minimum value of StartUpCurrentLevel in Level cluster */
#define EZB_ZCL_LEVEL_START_UP_CURRENT_LEVEL_MIN_VALUE (0x00)

/** @brief Maximum value of StartUpCurrentLevel in Level cluster */
#define EZB_ZCL_LEVEL_START_UP_CURRENT_LEVEL_MAX_VALUE (0xff)

/**
 * @brief Received Command identifiers for the Level cluster.
 */
typedef enum {
    EZB_ZCL_CMD_LEVEL_MOVE_TO_LEVEL_ID             = 0x00U, /*!< MoveToLevel command. */
    EZB_ZCL_CMD_LEVEL_MOVE_ID                      = 0x01U, /*!< Move command. */
    EZB_ZCL_CMD_LEVEL_STEP_ID                      = 0x02U, /*!< Step command. */
    EZB_ZCL_CMD_LEVEL_STOP_ID                      = 0x03U, /*!< Stop command. */
    EZB_ZCL_CMD_LEVEL_MOVE_TO_LEVEL_WITH_ON_OFF_ID = 0x04U, /*!< MoveToLevelWithOnOff command. */
    EZB_ZCL_CMD_LEVEL_MOVE_WITH_ON_OFF_ID          = 0x05U, /*!< MoveWithOnOff command. */
    EZB_ZCL_CMD_LEVEL_STEP_WITH_ON_OFF_ID          = 0x06U, /*!< StepWithOnOff command. */
    EZB_ZCL_CMD_LEVEL_STOP_WITH_ON_OFF_ID          = 0x07U, /*!< StopWithOnOff command. */
    EZB_ZCL_CMD_LEVEL_MOVE_TO_CLOSEST_FREQUENCY_ID = 0x08U, /*!< MoveToClosestFrequency command. */
} ezb_zcl_level_server_cmd_id_t;

typedef ezb_zcl_level_cluster_server_config_t ezb_zcl_level_cluster_config_t;

/**
 * @brief Add an attribute to an level cluster descriptor.
 *
 * @param cluster_desc Pointer to the level cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_level_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an level cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the level cluster configuration structure, refer to ezb_zcl_level_cluster_server_config_t or
 * ezb_zcl_level_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_level_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the Level cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_level_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the Level cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_level_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_LEVEL_CLIENT_ROLE_INIT ezb_zcl_level_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_LEVEL_SERVER_ROLE_INIT ezb_zcl_level_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
