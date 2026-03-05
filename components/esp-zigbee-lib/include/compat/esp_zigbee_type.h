/*
 * SPDX-FileCopyrightText: 2022-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "sdkconfig.h"
#include "esp_err.h"

#if CONFIG_ZB_SDK_1xx

#include <esp_zigbee.h>
#include <ezbee/core_types.h>
#include <ezbee/af.h>
#include <ezbee/zcl/zcl_type.h>
#include <ezbee/zcl/zcl_reporting.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TO_ESP_ERR(err) esp_zigbee_err_to_esp(err)

#define ESP_ZB_CCM_KEY_SIZE                         EZB_CCM_KEY_SIZE
#define ESP_ZB_ZCL_ATTR_SET_WITH_ATTR_ID(_set, _id) ((_set << 8) | (_id & 0xFF))
#define ESP_ZB_ZCL_MAX_STRING_SIZE                  0xFF
#define ESP_ZB_ZCL_INVALID_TSN                      0xFF

typedef uint8_t             esp_zb_64bit_addr_t[8];
typedef esp_zb_64bit_addr_t esp_zb_ieee_addr_t;
typedef esp_zb_64bit_addr_t esp_zb_ext_pan_id_t;

typedef union {
    uint16_t           addr_short; /*!< Zigbee short address */
    esp_zb_ieee_addr_t addr_long;  /*!< Zigbee long address */
} esp_zb_addr_u;

typedef struct esp_zb_zcl_addr_s {
    uint8_t addr_type; /*!< address type see esp_zb_zcl_address_type_t */
    union {
        uint16_t           short_addr; /*!< Zigbee short address */
        uint32_t           src_id;     /*!< Source ID of ZGPD */
        esp_zb_ieee_addr_t ieee_addr;  /*!< Full IEEE-address of ZGPD */
    } u;                               /*!< Union of the address */
} esp_zb_zcl_addr_t;

typedef struct esp_zb_af_node_desc_s {
    uint16_t node_desc_flags;            /*!< node description */
    uint8_t  mac_capability_flags;       /*!< mac capability */
    uint16_t manufacturer_code;          /*!< Manufacturer code */
    uint8_t  max_buf_size;               /*!< Maximum buffer size */
    uint16_t max_incoming_transfer_size; /*!< Maximum incoming transfer size */
    uint16_t server_mask;                /*!< Server mask */
    uint16_t max_outgoing_transfer_size; /*!< Maximum outgoing transfer size */
    uint8_t  desc_capability_field;      /*!< Descriptor capability field */
} esp_zb_af_node_desc_t;

#define ESP_ZB_ZCL_ADDR_TYPE_SHORT      0U
#define ESP_ZB_ZCL_ADDR_TYPE_IEEE_GPD   1U
#define ESP_ZB_ZCL_ADDR_TYPE_SRC_ID_GPD 2U
#define ESP_ZB_ZCL_ADDR_TYPE_IEEE       3U

#define ESP_ZB_ZCL_VALUE_FF             (-1)
#define ESP_ZB_ZCL_VALUE_FE             (-2)
#define ESP_ZB_ZCL_VALUE_NaN            (.0 / .0)

#define ESP_ZB_ZCL_VALUE_U8_FF          ((uint8_t)ESP_ZB_ZCL_VALUE_FF)
#define ESP_ZB_ZCL_VALUE_U16_FF         ((uint16_t)ESP_ZB_ZCL_VALUE_FF)
#define ESP_ZB_ZCL_VALUE_U32_FF         ((uint32_t)ESP_ZB_ZCL_VALUE_FF)
#define ESP_ZB_ZCL_VALUE_U64_FF         ((uint64_t)ESP_ZB_ZCL_VALUE_FF)

#define ESP_ZB_ZCL_VALUE_S8_NaS         ((int8_t)(1ULL << 7))
#define ESP_ZB_ZCL_VALUE_S16_NaS        ((int16_t)(1ULL << 15))
#define ESP_ZB_ZCL_VALUE_S32_NaS        ((int32_t)(1ULL << 31))
#define ESP_ZB_ZCL_VALUE_S64_NaS        ((int64_t)(1ULL << 63))

#define ESP_ZB_ZCL_VALUE_U8_NONE        ESP_ZB_ZCL_VALUE_U8_FF
#define ESP_ZB_ZCL_VALUE_U16_NONE       ESP_ZB_ZCL_VALUE_U16_FF
#define ESP_ZB_ZCL_VALUE_U32_NONE       ESP_ZB_ZCL_VALUE_U32_FF
#define ESP_ZB_ZCL_VALUE_U64_NONE       ESP_ZB_ZCL_VALUE_U64_FF

#define ESP_ZB_ZCL_VALUE_S8_NONE        ESP_ZB_ZCL_VALUE_S8_NaS
#define ESP_ZB_ZCL_VALUE_S16_NONE       ESP_ZB_ZCL_VALUE_S16_NaS
#define ESP_ZB_ZCL_VALUE_S32_NONE       ESP_ZB_ZCL_VALUE_S32_NaS
#define ESP_ZB_ZCL_VALUE_S64_NONE       ESP_ZB_ZCL_VALUE_S64_NaS

#define ESP_ZB_ZCL_VALUE_SINGLE_NONE    ESP_ZB_ZCL_VALUE_NaN
#define ESP_ZB_ZCL_VALUE_DOUBLE_NONE    ESP_ZB_ZCL_VALUE_NaN

#define ESP_ZB_AF_NODE_POWER_MODE_SYNC_ON_WHEN_IDLE      EZB_AF_NODE_POWER_MODE_SYNC_ON_WHEN_IDLE
#define ESP_ZB_AF_NODE_POWER_MODE_COME_ON_PERIODICALLY   EZB_AF_NODE_POWER_MODE_COME_ON_PERIODICALLY
#define ESP_ZB_AF_NODE_POWER_MODE_COME_ON_WHEN_SIMULATED EZB_AF_NODE_POWER_MODE_COME_ON_WHEN_SIMULATED
typedef ezb_af_node_power_mode_t esp_zb_af_node_power_mode_t;

#define ESP_ZB_AF_NODE_POWER_SOURCE_CONSTANT_POWER       EZB_AF_NODE_POWER_SOURCE_CONSTANT_POWER
#define ESP_ZB_AF_NODE_POWER_SOURCE_RECHARGEABLE_BATTERY EZB_AF_NODE_POWER_SOURCE_RECHARGEABLE_BATTERY
#define ESP_ZB_AF_NODE_POWER_SOURCE_DISPOSABLE_BATTERY   EZB_AF_NODE_POWER_SOURCE_DISPOSABLE_BATTERY
typedef ezb_af_node_power_source_t esp_zb_af_node_power_source_t;

#define ESP_ZB_AF_NODE_POWER_SOURCE_LEVEL_CRITICAL    EZB_AF_NODE_POWER_SOURCE_LEVEL_CRITICAL
#define ESP_ZB_AF_NODE_POWER_SOURCE_LEVEL_33_PERCENT  EZB_AF_NODE_POWER_SOURCE_LEVEL_33_PERCENT
#define ESP_ZB_AF_NODE_POWER_SOURCE_LEVEL_66_PERCENT  EZB_AF_NODE_POWER_SOURCE_LEVEL_66_PERCENT
#define ESP_ZB_AF_NODE_POWER_SOURCE_LEVEL_100_PERCENT EZB_AF_NODE_POWER_SOURCE_LEVEL_100_PERCENT
typedef ezb_af_node_power_source_level_t esp_zb_af_node_power_source_level_t;

typedef ezb_af_node_power_desc_t esp_zb_af_node_power_desc_t;

typedef struct esp_zb_af_simple_desc_1_1_s {
    uint8_t   endpoint;                 /*!< Endpoint */
    uint16_t  app_profile_id;           /*!< Application profile identifier */
    uint16_t  app_device_id;            /*!< Application device identifier */
    uint32_t  app_device_version : 4;   /*!< Application device version */
    uint32_t  reserved : 4;             /*!< Reserved */
    uint8_t   app_input_cluster_count;  /*!< Application input cluster count */
    uint8_t   app_output_cluster_count; /*!< Application output cluster count */
    uint16_t *app_cluster_list;         /*!< Pointer to an array of uint16_t cluster IDs whose total length is
                                             (app_input_cluster_count + app_output_cluster_count).
                                             Input cluster IDs start from index 0.
                                             Output cluster IDs start from index app_input_cluster_count. */
} esp_zb_af_simple_desc_1_1_t;

/******************* attribute data model *******************/

/**
 * @brief Type to represent ZCL attribute definition structure
 * @note Access define refer to zcl_attr_access
 */
typedef struct esp_zb_zcl_attr_s {
    uint16_t id;         /*!< Attribute id */
    uint8_t  type;       /*!< Attribute type see zcl_attr_type */
    uint8_t  access;     /*!< Attribute access options according to zcl_attr_access */
    uint16_t manuf_code; /*!< Manufacture specific id, refer to ESP_ZB_ZCL_NON_MANUFACTURER_SPECIFIC */
    void    *data_p;     /*!< Pointer to attribute data */
} esp_zb_zcl_attr_t;

/**
 * @brief The esp-zigbee data model of list of attribute.
 *
 * @note An attribute list groups up a single cluster.
 */
typedef struct {
    void *attr_list;
} esp_zb_attribute_list_t;

/******************* cluster data model *******************/

/**
 * @brief Type to represent ZCL cluster definition structure
 * @note Cluster id refer to zcl_cluster_id and attribute define see @ref esp_zb_zcl_attr_s
 */
typedef struct {
    void *cluster;
} esp_zb_zcl_cluster_t;

/**
 * @brief The esp-zigbee data model of list of cluster.
 *
 */
typedef struct {
    void *cluster_list;
} esp_zb_cluster_list_t;

/**
 * @brief The esp-zigbee data model of list of endpoint.
 *
 */
typedef struct {
    void *ep_list;
} esp_zb_ep_list_t;

/**
 * @brief Structure of device descriptor on a endpoint
 */
typedef struct esp_zb_endpoint_config_s {
    uint8_t  endpoint;               /*!< Endpoint */
    uint16_t app_profile_id;         /*!< Application profile identifier */
    uint16_t app_device_id;          /*!< Application device identifier */
    uint32_t app_device_version : 4; /*!< Application device version */
    uint32_t reserved : 4;           /*!< Reserved */
} esp_zb_endpoint_config_t;

EZB_PACKED_BEGIN
struct esp_zb_int24_s {
    uint16_t low;  /*!< Low 16-bit of the value */
    int8_t   high; /*!< High 8-bit of the value with signed */
} EZB_PACKED_END;
typedef struct esp_zb_int24_s esp_zb_int24_t;

EZB_PACKED_BEGIN
struct esp_zb_uint24_s {
    uint16_t low;  /*!< Low 16-bit of the value */
    uint8_t  high; /*!< High 8-bit of the value */
} EZB_PACKED_END;
typedef struct esp_zb_uint24_s esp_zb_uint24_t;

EZB_PACKED_BEGIN
struct esp_zb_uint48_s {
    uint32_t low;  /*!< Low 32-bit of the value */
    uint16_t high; /*!< High 16-bit of the value */
} EZB_PACKED_END;
typedef struct esp_zb_uint48_s esp_zb_uint48_t;

EZB_PACKED_BEGIN
struct esp_zb_int48_s {
    uint32_t low;  /*!< Low 32-bit of the value */
    int16_t  high; /*!< High 16-bit of the value with signed */
} EZB_PACKED_END;
typedef struct esp_zb_int48_s esp_zb_int48_t;

#define ESP_ZB_ZCL_ATTR_VAR_U_SIZE sizeof(esp_zb_int48_t)
union esp_zb_zcl_attr_var_u {
    uint8_t         u8;          /*!< Unsigned 8-bit int of integer */
    int8_t          s8;          /*!< Signed 8-bit int of integer */
    uint16_t        u16;         /*!< Unsigned 16-bit of integer */
    int16_t         s16;         /*!< Signed 16-bit of integer */
    esp_zb_uint24_t u24;         /*!< Unsigned 24-bit of the integer */
    esp_zb_int24_t  s24;         /*!< Signed 24-bit of the integer */
    uint32_t        u32;         /*!< Unsigned 32-bit of the integer */
    int32_t         s32;         /*!< Signed 32-bit of the integer */
    esp_zb_uint48_t u48;         /*!< Unsigned 48-bit of the integer */
    uint8_t         data_buf[4]; /*!< Data array */
    float           f32;         /*!< Single precision, ESP_ZB_ZCL_ATTR_TYPE_SINGLE data type */
    uint64_t        reserved;    /*!< Reserved for future use */
};

#define ESP_ZB_ZCL_REPORTING_INFO_SIZE sizeof(esp_zb_zcl_attr_var_u)

typedef struct esp_zb_zcl_reporting_info_s {
    uint8_t  direction;    /*!< Direction: report is send or received */
    uint8_t  ep;           /*!< Endpoint number */
    uint16_t cluster_id;   /*!< Cluster ID for reporting */
    uint8_t  cluster_role; /*!< Cluster role server/client */
    uint16_t attr_id;      /*!< Attribute ID for reporting */
    uint8_t  flags;        /*!< Flags to inform status of reporting */
    uint64_t run_time;     /*!< Time to run next reporting activity */
    union {
        struct {
            uint16_t                    min_interval;     /*!< Actual minimum reporting interval */
            uint16_t                    max_interval;     /*!< Actual maximum reporting interval */
            union esp_zb_zcl_attr_var_u delta;            /*!< Actual reportable change */
            union esp_zb_zcl_attr_var_u reported_value;   /*!< The last reported value */
            uint16_t                    def_min_interval; /*!< Default minimum reporting interval */
            uint16_t                    def_max_interval; /*!< Default maximum reporting interval */
        } send_info; /*!< send_info is stored on cluster server side (as usual) and describes how
                   attribute should be reported */
        struct {
            uint16_t timeout; /*!< Timeout period */
        } recv_info;          /*!< recv_info is stored on cluster client side (as usual) and describes how
                            attribute report is received */
    } u;                      /*!< Union of the report info*/

    struct {
        uint16_t short_addr;             /*!< Destination short address */
        uint8_t  endpoint;               /*!< Destination endpoint */
        uint16_t profile_id;             /*!< Profile id */
    } dst;                               /*!< Union of the ZCL destination */
    uint16_t                 manuf_code; /*!< Manufacturer specific code */
    ezb_zcl_reporting_info_t info;       /*!< info of ezb_zcl_reporting_info_t */
} esp_zb_zcl_reporting_info_t;

#ifdef __cplusplus
}
#endif

#endif
