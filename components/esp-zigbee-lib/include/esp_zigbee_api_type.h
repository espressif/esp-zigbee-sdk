/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#define ESP_ZB_PACKED_STRUCT __attribute__ ((packed))

typedef uint8_t esp_zb_64bit_addr_t[8];
typedef esp_zb_64bit_addr_t esp_zb_ieee_addr_t;
typedef void (*esp_zb_zcl_cluster_init_t)(void);
typedef void (*esp_zb_callback_t)(uint8_t param);

/**
 * @brief The Zigbee address union consist of 16 bit short address and 64 bit long address.
 *
 */
typedef union {
    uint16_t  addr_short;                           /*!< Zigbee short address */
    esp_zb_ieee_addr_t addr_long;                   /*!< Zigbee long address */
} esp_zb_addr_u;

/** Enum of the Zigbee ZCL address type
 * @brief Possible address types of devices from which ZCL message is received.
 * @anchor esp_zb_zcl_address_type_t
 */
typedef enum {
    ESP_ZB_ZCL_ADDR_TYPE_SHORT = 0U,
    ESP_ZB_ZCL_ADDR_TYPE_IEEE_GPD = 1U,
    ESP_ZB_ZCL_ADDR_TYPE_SRC_ID_GPD = 2U,
    ESP_ZB_ZCL_ADDR_TYPE_IEEE = 3U,
} esp_zb_zcl_address_type_t;

/**
 * @brief Type to represent source address of ZCL message
 * @note Address type refer @ref esp_zb_zcl_address_type_t
 */
typedef struct esp_zb_zcl_addr_s {
    esp_zb_zcl_address_type_t addr_type;            /*!< address type see esp_zb_zcl_address_type_t */
    union {
        uint16_t short_addr;            /*!< Zigbee short address */
        uint32_t src_id;                /*!< Source ID of ZGPD */
        esp_zb_ieee_addr_t ieee_addr;   /*!< Full IEEE-address of ZGPD */
    } u;                                /*!< Union of the address */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_addr_t;

/**
 * @brief Type to represent ZCL attribute definition structure
 * @note Access define refer to zcl_attr_access
 */
typedef struct esp_zb_zcl_attr_s {
    uint16_t id;                        /*!< Attribute id */
    uint8_t type;                       /*!< Attribute type see zcl_attr_type */
    uint8_t access;                     /*!< Attribute access options according to zcl_attr_access */
    void *data_p;                       /*!< Pointer to attribute data */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_attr_t;

/**
 * @brief Type to represent ZCL cluster definition structure
 * @note Cluster id refer to zcl_cluster_id and attribute define see @ref esp_zb_zcl_attr_s
 */
typedef struct esp_zb_zcl_cluster_s {
    uint16_t cluster_id;                        /*!< ZCL 16-bit cluster id. Refer zcl_cluster_id */
    uint16_t attr_count;                        /*!< Attributes number supported by the cluster */
    esp_zb_zcl_attr_t *attr_desc_list;          /*!< List of cluster attributes esp_zb_zcl_attr_t */
    uint8_t role_mask;                          /*!< Cluster role, refer to zcl_cluster_role */
    uint16_t manuf_code;                        /*!< Manufacturer code for cluster and its attributes */
    esp_zb_zcl_cluster_init_t cluster_init;     /*!< cluster init callback function */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_cluster_t;

/**
 * @brief Type to represent type signed int_24
 * @note Internal use
 */
typedef struct esp_zb_int24_s {
    uint16_t low;               /*!< Low 16-bit of the value */
    int8_t   high;              /*!< High 8-bit of the value with signed */
} ESP_ZB_PACKED_STRUCT
esp_zb_int24_t;

/**
 * @brief Type to represent type unsigned int_24
 * @note Internal use
 */
typedef struct esp_zb_uint24_s {
    uint16_t low;               /*!< Low 16-bit of the value */
    uint8_t high;               /*!< High 8-bit of the value */
} ESP_ZB_PACKED_STRUCT
esp_zb_uint24_t;

/**
 * @brief Type to represent type unsigned int_48
 * @note Internal use
 */
typedef struct esp_zb_uint48_s {
    uint32_t low;               /*!< Low 32-bit of the value */
    uint16_t high;              /*!< High 16-bit of the value */
} ESP_ZB_PACKED_STRUCT
esp_zb_uint48_t;

/**
 * @brief Type to represent type signed int_48
 * @note Internal use
 */
typedef struct esp_zb_int48_s {
    uint32_t low;               /*!< Low 32-bit of the value */
    int16_t high;               /*!< High 16-bit of the value with signed */
} ESP_ZB_PACKED_STRUCT
esp_zb_int48_t;

/**
 * @brief Union of the ZCL attribute value
 * @note Internal use
 */
union esp_zb_zcl_attr_var_u {
    uint8_t u8;         /*!< Unsigned 8-bit int of integer */
    int8_t s8;          /*!< Signed 8-bit int of integer */
    uint16_t u16;       /*!< Unsigned 16-bit of integer */
    int16_t s16;        /*!< Signed 16-bit of integer */
    esp_zb_uint24_t u24;/*!< Unsigned 24-bit of the integer */
    esp_zb_int24_t s24; /*!< Signed 24-bit of the integer */
    uint32_t u32;       /*!< Unsigned 32-bit of the integer */
    int32_t s32;        /*!< Signed 32-bit of the integer */
    esp_zb_uint48_t u48;/*!< Unsigned 48-bit of the integer */
    uint8_t data_buf[4];/*!< Data array */
};

/**
 * @brief Type to represent ZCL attribute reporting info structure
 * @note Internal use
 */
typedef struct esp_zb_zcl_reporting_info_s {
    uint8_t direction;              /*!< Direction: report is send or received */
    uint8_t ep;                     /*!< Endpoint number */
    uint16_t cluster_id;            /*!< Cluster ID for reporting */
    uint8_t cluster_role;           /*!< Cluster rolo server/client */
    uint16_t attr_id;               /*!< Attribute ID for reporting */
    uint8_t flags;                  /*!< Flags to inform status of reporting */
    uint32_t run_time;              /*!< Time to run next reporting activity */
    union {
        struct {
            uint16_t min_interval; /*!< Actual minimum reporting interval */
            uint16_t max_interval; /*!< Actual maximum reporting interval */
            union esp_zb_zcl_attr_var_u delta; /*!< Actual reportable change */
            union esp_zb_zcl_attr_var_u reported_value; /*!< The last reported value */
            uint16_t def_min_interval; /*!< Default minimum reporting interval */
            uint16_t def_max_interval; /*!< Default maximum reporting interval */
        }
        send_info;  /*!< send_info is stored on cluster server side (as usual) and describes how
                  attribute should be reported */
        struct {
            uint16_t timeout; /*!< Timeout period */
        }
        recv_info; /*!< recv_info is stored on cluster client side (as usual) and describes how
                 attribute report is received */
    }
    u;            /*!< Union of the report info*/

    struct {
        uint16_t short_addr; /*!< Destination short address */
        uint8_t  endpoint;   /*!< Destination endpoint */
        uint16_t profile_id; /*!< Profile id */
    }
    dst;        /*!< Union of the ZCL destination */
}
esp_zb_zcl_reporting_info_t;

/**
 * @brief Structure of Alarm variables
 * @note Internal use
 */
typedef struct esp_zb_zcl_cvc_alarm_variables_s {
    uint8_t endpoint_id;                /*!< Endpoint id */
    uint16_t cluster_id;                /*!< Cluster id */
    uint16_t attribute_id;              /*!< Attribute id */
    uint8_t alarm_buf_id;               /*!< Alarm buffer id */
    bool is_used;                       /*!< Is Used flag */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_cvc_alarm_variables_t;

/**
 * @brief Structure of simple descriptor request of ZCL command
 */
typedef struct esp_zb_af_simple_desc_1_1_s {
    uint8_t    endpoint;                        /*!< Endpoint */
    uint16_t   app_profile_id;                  /*!< Application profile identifier */
    uint16_t   app_device_id;                   /*!< Application device identifier */
    uint32_t    app_device_version: 4;          /*!< Application device version */
    uint32_t    reserved: 4;                    /*!< Reserved */
    uint8_t    app_input_cluster_count;         /*!< Application input cluster count */
    uint8_t    app_output_cluster_count;        /*!< Application output cluster count */
    uint16_t   app_cluster_list[2];             /*!< Application input and output cluster list */
} ZB_PACKED_STRUCT
esp_zb_af_simple_desc_1_1_t;

/**
 * @brief Type to represent ZCL endpoint definition structure
 * @note  The esp_zb_zcl_reporting_info_t defines see @ref esp_zb_zcl_reporting_info_s
* @note  The esp_zb_af_simple_desc_1_1_t defines see @ref esp_zb_af_simple_desc_1_1_s
 */
typedef struct esp_zb_endpoint_s {
    uint8_t ep_id;                              /*!< Endpoint ID */
    uint16_t profile_id;                        /*!< Application profile, which implemented on endpoint */
    esp_zb_callback_t device_handler;           /*!< endpoint specific callback, handles all commands for this endpoint. If set, it will be called to handle callback,like esp_zb_add_read_attr_resp_cb */
    esp_zb_callback_t identify_handler;         /*!< Identify notification callback. If set, it will be called on identification start and stop indicating start event with a non-zero argument*/
    uint8_t reserved_size;                      /*!< Unused parameter (reserved for future use) */
    void *reserved_ptr;                         /*!< Unused parameter (reserved for future use) */
    uint8_t cluster_count;                      /*!< Number of supported clusters */
    esp_zb_zcl_cluster_t *cluster_desc_list;    /*!< Supported clusters list */
    esp_zb_af_simple_desc_1_1_t *simple_desc;   /*!< Simple descriptor */
    uint8_t rep_info_count;                     /*!< Number of reporting info slots */
    esp_zb_zcl_reporting_info_t *reporting_info; /*!< Attributes reporting information */
    uint8_t cvc_alarm_count;          /*!< Number of continuous value change alarm slots */
    esp_zb_zcl_cvc_alarm_variables_t *cvc_alarm_info;   /*!< pointer to the cvc alarm structure */
} ESP_ZB_PACKED_STRUCT
esp_zb_endpoint_t;

#ifdef __cplusplus
}
#endif
