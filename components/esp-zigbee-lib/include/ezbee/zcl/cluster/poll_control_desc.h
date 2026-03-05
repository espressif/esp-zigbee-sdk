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
   POLL_CONTROL Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the poll_control cluster implementation */
#define EZB_ZCL_POLL_CONTROL_CLUSTER_REVISION (3)

/**
 * @brief Attribute identifiers for the poll_control server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_POLL_CONTROL_CHECK_IN_INTERVAL_ID      = 0x0000U, /*!< CheckInInterval attribute. */
    EZB_ZCL_ATTR_POLL_CONTROL_LONG_POLL_INTERVAL_ID     = 0x0001U, /*!< LongPollInterval attribute. */
    EZB_ZCL_ATTR_POLL_CONTROL_SHORT_POLL_INTERVAL_ID    = 0x0002U, /*!< ShortPollInterval attribute. */
    EZB_ZCL_ATTR_POLL_CONTROL_FAST_POLL_TIMEOUT_ID      = 0x0003U, /*!< FastPollTimeout attribute. */
    EZB_ZCL_ATTR_POLL_CONTROL_CHECK_IN_INTERVAL_MIN_ID  = 0x0004U, /*!< CheckInIntervalMin attribute. */
    EZB_ZCL_ATTR_POLL_CONTROL_LONG_POLL_INTERVAL_MIN_ID = 0x0005U, /*!< LongPollIntervalMin attribute. */
    EZB_ZCL_ATTR_POLL_CONTROL_FAST_POLL_TIMEOUT_MAX_ID  = 0x0006U, /*!< FastPollTimeoutMax attribute. */
    EZB_ZCL_ATTR_POLL_CONTROL_CHECK_IN_CONTEXT_ID       = 0xeff0U, /*!< CheckInContext attribute. */
} ezb_zcl_poll_control_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the PollControl server cluster.
 */
typedef struct ezb_zcl_poll_control_cluster_server_config_s {
    uint32_t check_in_interval;   /*!< Configurable mandatory CheckInInterval attribute */
    uint32_t long_poll_interval;  /*!< Configurable mandatory LongPollInterval attribute */
    uint16_t short_poll_interval; /*!< Configurable mandatory ShortPollInterval attribute */
    uint16_t fast_poll_timeout;   /*!< Configurable mandatory FastPollTimeout attribute */
} ezb_zcl_poll_control_cluster_server_config_t;

/** @brief Default value of CheckInInterval in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_CHECK_IN_INTERVAL_DEFAULT_VALUE (0x00003840)

/** @brief Minimum value of CheckInInterval in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_CHECK_IN_INTERVAL_MIN_VALUE (0x00000000)

/** @brief Maximum value of CheckInInterval in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_CHECK_IN_INTERVAL_MAX_VALUE (0x006e0000)
/** @brief Default value of LongPollInterval in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_LONG_POLL_INTERVAL_DEFAULT_VALUE (0x00000014)

/** @brief Minimum value of LongPollInterval in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_LONG_POLL_INTERVAL_MIN_VALUE (0x00000004)

/** @brief Maximum value of LongPollInterval in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_LONG_POLL_INTERVAL_MAX_VALUE (0x006e0000)
/** @brief Default value of ShortPollInterval in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_SHORT_POLL_INTERVAL_DEFAULT_VALUE (0x0002)

/** @brief Minimum value of ShortPollInterval in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_SHORT_POLL_INTERVAL_MIN_VALUE (0x0001)

/** @brief Maximum value of ShortPollInterval in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_SHORT_POLL_INTERVAL_MAX_VALUE (0xffff)
/** @brief Default value of FastPollTimeout in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_FAST_POLL_TIMEOUT_DEFAULT_VALUE (0x0028)

/** @brief Minimum value of FastPollTimeout in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_FAST_POLL_TIMEOUT_MIN_VALUE (0x0001)

/** @brief Maximum value of FastPollTimeout in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_FAST_POLL_TIMEOUT_MAX_VALUE (0xffff)
/** @brief Default value of CheckInIntervalMin in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_CHECK_IN_INTERVAL_MIN_DEFAULT_VALUE (0x00000000)

/** @brief Default value of LongPollIntervalMin in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_LONG_POLL_INTERVAL_MIN_DEFAULT_VALUE (0x00000000)

/** @brief Default value of FastPollTimeoutMax in PollControl cluster */
#define EZB_ZCL_POLL_CONTROL_FAST_POLL_TIMEOUT_MAX_DEFAULT_VALUE (0x0000)

/**
 * @brief Received Command identifiers for the PollControl cluster.
 */
typedef enum {
    EZB_ZCL_CMD_POLL_CONTROL_CHECK_IN_ID = 0x00U, /*!< CheckIn command. */
} ezb_zcl_poll_control_server_cmd_id_t;

/**
 * @brief Received Command identifiers for the PollControl cluster.
 */
typedef enum {
    EZB_ZCL_CMD_POLL_CONTROL_CHECK_IN_RESPONSE_ID       = 0x00U, /*!< CheckInResponse command. */
    EZB_ZCL_CMD_POLL_CONTROL_FAST_POLL_STOP_ID          = 0x01U, /*!< FastPollStop command. */
    EZB_ZCL_CMD_POLL_CONTROL_SET_LONG_POLL_INTERVAL_ID  = 0x02U, /*!< SetLongPollInterval command. */
    EZB_ZCL_CMD_POLL_CONTROL_SET_SHORT_POLL_INTERVAL_ID = 0x03U, /*!< SetShortPollInterval command. */
} ezb_zcl_poll_control_client_cmd_id_t;

typedef ezb_zcl_poll_control_cluster_server_config_t ezb_zcl_poll_control_cluster_config_t;

/**
 * @brief Add an attribute to an poll_control cluster descriptor.
 *
 * @param cluster_desc Pointer to the poll_control cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_poll_control_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an poll_control cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the poll_control cluster configuration structure, refer to
 * ezb_zcl_poll_control_cluster_server_config_t or ezb_zcl_poll_control_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_poll_control_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the PollControl cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_poll_control_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the PollControl cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_poll_control_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_POLL_CONTROL_CLIENT_ROLE_INIT ezb_zcl_poll_control_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_POLL_CONTROL_SERVER_ROLE_INIT ezb_zcl_poll_control_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
