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
   TIME Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the time cluster implementation */
#define EZB_ZCL_TIME_CLUSTER_REVISION (1)

/**
 * @brief Attribute identifiers for the time server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_TIME_TIME_ID             = 0x0000U, /*!< Time attribute. */
    EZB_ZCL_ATTR_TIME_TIME_STATUS_ID      = 0x0001U, /*!< TimeStatus attribute. */
    EZB_ZCL_ATTR_TIME_TIME_ZONE_ID        = 0x0002U, /*!< TimeZone attribute. */
    EZB_ZCL_ATTR_TIME_DST_START_ID        = 0x0003U, /*!< DstStart attribute. */
    EZB_ZCL_ATTR_TIME_DST_END_ID          = 0x0004U, /*!< DstEnd attribute. */
    EZB_ZCL_ATTR_TIME_DST_SHIFT_ID        = 0x0005U, /*!< DstShift attribute. */
    EZB_ZCL_ATTR_TIME_STANDARD_TIME_ID    = 0x0006U, /*!< StandardTime attribute. */
    EZB_ZCL_ATTR_TIME_LOCAL_TIME_ID       = 0x0007U, /*!< LocalTime attribute. */
    EZB_ZCL_ATTR_TIME_LAST_SET_TIME_ID    = 0x0008U, /*!< LastSetTime attribute. */
    EZB_ZCL_ATTR_TIME_VALID_UNTIL_TIME_ID = 0x0009U, /*!< ValidUntilTime attribute. */
    EZB_ZCL_ATTR_TIME_TIME_CTX_ID         = 0xeffeU, /*!< TimeCtx attribute. */
} ezb_zcl_time_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the Time server cluster.
 */
typedef struct ezb_zcl_time_cluster_server_config_s {
    uint32_t time;        /*!< Configurable mandatory Time attribute */
    uint8_t  time_status; /*!< Configurable mandatory TimeStatus attribute */
} ezb_zcl_time_cluster_server_config_t;

/**
 * @brief Bitmap for ZCL TimeStatus attribute of Time.
 */
typedef enum {
    EZB_ZCL_TIME_TIME_STATUS_MASTER          = 0x01U, /*!< Master */
    EZB_ZCL_TIME_TIME_STATUS_SYNCHRONIZED    = 0x02U, /*!< Synchronized */
    EZB_ZCL_TIME_TIME_STATUS_MASTER_ZONE_DST = 0x04U, /*!< MasterZoneDst */
    EZB_ZCL_TIME_TIME_STATUS_SUPERSEDING     = 0x08U, /*!< Superseding */
} ezb_zcl_time_server_time_status_t;

/** @brief Default value of Time in Time cluster */
#define EZB_ZCL_TIME_TIME_DEFAULT_VALUE (0xffffffff)

/** @brief Minimum value of Time in Time cluster */
#define EZB_ZCL_TIME_TIME_MIN_VALUE (0x00000000)

/** @brief Maximum value of Time in Time cluster */
#define EZB_ZCL_TIME_TIME_MAX_VALUE (0xfffffffe)
/** @brief Default value of TimeStatus in Time cluster */
#define EZB_ZCL_TIME_TIME_STATUS_DEFAULT_VALUE (0x00)

/** @brief Default value of TimeZone in Time cluster */
#define EZB_ZCL_TIME_TIME_ZONE_DEFAULT_VALUE (0x00000000)

/** @brief Minimum value of TimeZone in Time cluster */
#define EZB_ZCL_TIME_TIME_ZONE_MIN_VALUE (-86400)

/** @brief Maximum value of TimeZone in Time cluster */
#define EZB_ZCL_TIME_TIME_ZONE_MAX_VALUE (86400)
/** @brief Default value of DstStart in Time cluster */
#define EZB_ZCL_TIME_DST_START_DEFAULT_VALUE (0xffffffff)

/** @brief Minimum value of DstStart in Time cluster */
#define EZB_ZCL_TIME_DST_START_MIN_VALUE (0x00000000)

/** @brief Maximum value of DstStart in Time cluster */
#define EZB_ZCL_TIME_DST_START_MAX_VALUE (0xfffffffe)
/** @brief Default value of DstEnd in Time cluster */
#define EZB_ZCL_TIME_DST_END_DEFAULT_VALUE (0xffffffff)

/** @brief Minimum value of DstEnd in Time cluster */
#define EZB_ZCL_TIME_DST_END_MIN_VALUE (0x00000000)

/** @brief Maximum value of DstEnd in Time cluster */
#define EZB_ZCL_TIME_DST_END_MAX_VALUE (0xfffffffe)
/** @brief Default value of DstShift in Time cluster */
#define EZB_ZCL_TIME_DST_SHIFT_DEFAULT_VALUE (0x00000000)

/** @brief Minimum value of DstShift in Time cluster */
#define EZB_ZCL_TIME_DST_SHIFT_MIN_VALUE (-86400)

/** @brief Maximum value of DstShift in Time cluster */
#define EZB_ZCL_TIME_DST_SHIFT_MAX_VALUE (86400)
/** @brief Default value of StandardTime in Time cluster */
#define EZB_ZCL_TIME_STANDARD_TIME_DEFAULT_VALUE (0xffffffff)

/** @brief Minimum value of StandardTime in Time cluster */
#define EZB_ZCL_TIME_STANDARD_TIME_MIN_VALUE (0x00000000)

/** @brief Maximum value of StandardTime in Time cluster */
#define EZB_ZCL_TIME_STANDARD_TIME_MAX_VALUE (0xfffffffe)
/** @brief Default value of LocalTime in Time cluster */
#define EZB_ZCL_TIME_LOCAL_TIME_DEFAULT_VALUE (0xffffffff)

/** @brief Minimum value of LocalTime in Time cluster */
#define EZB_ZCL_TIME_LOCAL_TIME_MIN_VALUE (0x00000000)

/** @brief Maximum value of LocalTime in Time cluster */
#define EZB_ZCL_TIME_LOCAL_TIME_MAX_VALUE (0xfffffffe)
/** @brief Default value of LastSetTime in Time cluster */
#define EZB_ZCL_TIME_LAST_SET_TIME_DEFAULT_VALUE (0xffffffff)

/** @brief Minimum value of LastSetTime in Time cluster */
#define EZB_ZCL_TIME_LAST_SET_TIME_MIN_VALUE (0x00000000)

/** @brief Maximum value of LastSetTime in Time cluster */
#define EZB_ZCL_TIME_LAST_SET_TIME_MAX_VALUE (0xffffffff)
/** @brief Default value of ValidUntilTime in Time cluster */
#define EZB_ZCL_TIME_VALID_UNTIL_TIME_DEFAULT_VALUE (0xffffffff)

/** @brief Minimum value of ValidUntilTime in Time cluster */
#define EZB_ZCL_TIME_VALID_UNTIL_TIME_MIN_VALUE (0x00000000)

/** @brief Maximum value of ValidUntilTime in Time cluster */
#define EZB_ZCL_TIME_VALID_UNTIL_TIME_MAX_VALUE (0xffffffff)

typedef ezb_zcl_time_cluster_server_config_t ezb_zcl_time_cluster_config_t;

/**
 * @brief Add an attribute to an time cluster descriptor.
 *
 * @param cluster_desc Pointer to the time cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_time_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an time cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the time cluster configuration structure, refer to ezb_zcl_time_cluster_server_config_t or
 * ezb_zcl_time_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_time_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the Time cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_time_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the Time cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_time_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_TIME_CLIENT_ROLE_INIT ezb_zcl_time_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_TIME_SERVER_ROLE_INIT ezb_zcl_time_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
