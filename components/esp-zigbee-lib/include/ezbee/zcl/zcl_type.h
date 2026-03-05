/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup zcl_constants ZCL Constants
 * @{
 */

/** @brief Invalid Zigbee endpoint ID in ZCL. */
#define EZB_ZCL_INVALID_EP_ID 0x00U

/** @brief Cluster role: server (responds to commands). */
#define EZB_ZCL_CLUSTER_SERVER 0x01U

/** @brief Cluster role: client (sends commands). */
#define EZB_ZCL_CLUSTER_CLIENT 0x02U

/** @brief ZCL frame type: common (general commands like Read/Write Attributes). */
#define EZB_ZCL_FRAME_TYPE_COMMON 0x00U

/** @brief ZCL frame type: cluster-specific (commands defined by individual clusters). */
#define EZB_ZCL_FRAME_TYPE_CLUSTER_SPECIFIC 0x01U

/** @brief Not manufacturer-specific command or attribute. */
#define EZB_ZCL_NOT_MANUFACTURER_SPECIFIC 0x00U

/** @brief Manufacturer-specific command or attribute. */
#define EZB_ZCL_MANUFACTURER_SPECIFIC 0x01U

/** @brief Invalid manufacturer code. */
#define EZB_ZCL_INV_MANUF_CODE 0xFFFFU

/** @brief Standard manufacturer code. */
#define EZB_ZCL_STD_MANUF_CODE 0x0000U

/** @brief Attribute: Espressif manufacturer code. */
#define EZB_ZCL_ESP_MANUF_CODE 0x131BU

/** @brief Enable default response in ZCL frame (default behavior). */
#define EZB_ZCL_FRAME_ENABLE_DEFAULT_RESPONSE  0x00U

/** @brief Disable default response in ZCL frame. */
#define EZB_ZCL_FRAME_DISABLE_DEFAULT_RESPONSE 0x01U

/** @brief Command direction: to server (client sends to server). */
#define EZB_ZCL_CMD_DIRECTION_TO_SRV 0x00U

/** @brief Command direction: to client (server sends to client). */
#define EZB_ZCL_CMD_DIRECTION_TO_CLI 0x01U

/** @brief Reporting direction: send (server reports to client). */
#define EZB_ZCL_REPORTING_SEND 0x00U

/** @brief Reporting direction: receive (client receives reports from server). */
#define EZB_ZCL_REPORTING_RECV 0x01U

/** @} */

/** @brief Attribute ID for the global ClusterRevision attribute. */
#define EZB_ZCL_ATTR_GLOBAL_CLUSTER_REVISION_ID 0xFFFDU

/**
 * @brief Enumeration for AttributeReportingStatus
 */
typedef enum ezb_zcl_attribute_reporting_status_e
{
    EZB_ZCL_AR_STATUS_PENDING  = 0x00U,  /**< Pending. */
    EZB_ZCL_AR_STATUS_COMPLETE = 0x01U  /**< Attribute Reporting Complete. */
} ezb_zcl_attribute_reporting_status_t;

/** @brief Attribute ID for the global AttributeReportingStatus attribute. */
#define EZB_ZCL_ATTR_GLOBAL_ATTRIBUTE_REPORTING_STATUS_ID 0xFFFEU

/**
 * @brief Union for ZCL attribute variable.
 */
typedef union {
    uint8_t u8;       /*!< 8-bit unsigned integer. */
    int8_t  s8;       /*!< 8-bit signed integer. */
    uint16_t u16;     /*!< 16-bit unsigned integer. */
    int16_t  s16;     /*!< 16-bit signed integer. */
    uint32_t u24;     /*!< 24-bit unsigned integer. */
    int32_t  s24;     /*!< 24-bit signed integer. */
    uint32_t u32;     /*!< 32-bit unsigned integer. */
    int32_t  s32;     /*!< 32-bit signed integer. */
    uint64_t u40;     /*!< 40-bit unsigned integer. */
    int64_t  s40;     /*!< 40-bit signed integer. */
    uint64_t u48;     /*!< 48-bit unsigned integer. */
    int64_t  s48;     /*!< 48-bit signed integer. */
    uint64_t u56;     /*!< 56-bit unsigned integer. */
    int64_t  s56;     /*!< 56-bit signed integer. */
    uint64_t u64;     /*!< 64-bit unsigned integer. */
    int64_t  s64;     /*!< 64-bit signed integer. */
    float    f32;     /*!< 32-bit floating point number. */
    uint32_t crc32;   /*!< 32-bit CRC value. */
    uint8_t  data[8]; /*!< 8-byte array. */
} ezb_zcl_attr_variable_t;

/** @defgroup zcl_special_values ZCL Special Values
 * @{
 */

/** @brief All bits are set in the data value (invalid/unknown value for unsigned types). */
#define EZB_ZCL_VALUE_FF (-1)

/** @brief All bits are set except the lowest bit (invalid/unknown value variant). */
#define EZB_ZCL_VALUE_FE (-2)

/** @brief Not a Number defined for semi-precision floating point values. */
#define EZB_ZCL_VALUE_NaN (0.0 / 0.0)

/** @} */

typedef uint32_t ezb_zcl_uint24_t;     /*!< 24-bit unsigned integer. */
#define EZB_ZCL_UINT24_MAX  (0xFFFFFF) /*!< 24-bit unsigned integer maximum value. */
#define EZB_ZCL_UINT24_MIN  (0)        /*!< 24-bit unsigned integer minimum value. */
#define EZB_ZCL_UINT24_SIZE 3U         /*!< 24-bit unsigned integer size. */

typedef int32_t ezb_zcl_int24_t;                /*!< 24-bit signed integer. */
#define EZB_ZCL_INT24_MAX  (0x7FFFFF)           /*!< 24-bit signed integer maximum value. */
#define EZB_ZCL_INT24_MIN  (-EZB_ZCL_INT24_MAX) /*!< 24-bit signed integer minimum value. */
#define EZB_ZCL_INT24_SIZE 3U                   /*!< 24-bit signed integer size. */

typedef uint64_t ezb_zcl_uint40_t;         /*!< 40-bit unsigned integer. */
#define EZB_ZCL_UINT40_MAX  (0xFFFFFFFFFF) /*!< 40-bit unsigned integer maximum value. */
#define EZB_ZCL_UINT40_MIN  (0)            /*!< 40-bit unsigned integer minimum value. */
#define EZB_ZCL_UINT40_SIZE 5U             /*!< 40-bit unsigned integer size. */

typedef int64_t ezb_zcl_int40_t;                /*!< 40-bit signed integer. */
#define EZB_ZCL_INT40_MAX  (0x7FFFFFFFFF)       /*!< 40-bit signed integer maximum value. */
#define EZB_ZCL_INT40_MIN  (-EZB_ZCL_INT40_MAX) /*!< 40-bit signed integer minimum value. */
#define EZB_ZCL_INT40_SIZE 5U                   /*!< 40-bit signed integer size. */

typedef uint64_t ezb_zcl_uint48_t;           /*!< 48-bit unsigned integer. */
#define EZB_ZCL_UINT48_MAX  (0xFFFFFFFFFFFF) /*!< 48-bit unsigned integer maximum value. */
#define EZB_ZCL_UINT48_MIN  (0)              /*!< 48-bit unsigned integer minimum value. */
#define EZB_ZCL_UINT48_SIZE 6U               /*!< 48-bit unsigned integer size. */

typedef int64_t ezb_zcl_int48_t;                /*!< 48-bit signed integer. */
#define EZB_ZCL_INT48_MAX  (0x7FFFFFFFFFFF)     /*!< 48-bit signed integer maximum value. */
#define EZB_ZCL_INT48_MIN  (-EZB_ZCL_INT48_MAX) /*!< 48-bit signed integer minimum value. */
#define EZB_ZCL_INT48_SIZE 6U                   /*!< 48-bit signed integer size. */

typedef uint64_t ezb_zcl_uint56_t;             /*!< 56-bit unsigned integer. */
#define EZB_ZCL_UINT56_MAX  (0xFFFFFFFFFFFFFF) /*!< 56-bit unsigned integer maximum value. */
#define EZB_ZCL_UINT56_MIN  (0)                /*!< 56-bit unsigned integer minimum value. */
#define EZB_ZCL_UINT56_SIZE 7U                 /*!< 56-bit unsigned integer size. */

typedef int64_t ezb_zcl_int56_t;                /*!< 56-bit signed integer. */
#define EZB_ZCL_INT56_MAX  (0x7FFFFFFFFFFFFF)   /*!< 56-bit signed integer maximum value. */
#define EZB_ZCL_INT56_MIN  (-EZB_ZCL_INT56_MAX) /*!< 56-bit signed integer minimum value. */
#define EZB_ZCL_INT56_SIZE 7U                   /*!< 56-bit signed integer size. */

#define EZB_ZCL_KEY128_SIZE 16U /*!< 128-bit key size. */

#define EZB_ZCL_VALUE_UINT8_FF  ((uint8_t)EZB_ZCL_VALUE_FF)    /*!< ZCL_VALUE_FF for uint8_t. */
#define EZB_ZCL_VALUE_UINT16_FF ((uint16_t)EZB_ZCL_VALUE_FF)   /*!< ZCL_VALUE_FF for uint16_t. */
#define EZB_ZCL_VALUE_UINT24_FF ((uint32_t)EZB_ZCL_UINT24_MAX) /*!< ZCL_VALUE_FF for uint24_t. */
#define EZB_ZCL_VALUE_UINT32_FF ((uint32_t)EZB_ZCL_VALUE_FF)   /*!< ZCL_VALUE_FF for uint32_t. */
#define EZB_ZCL_VALUE_UINT40_FF ((uint64_t)EZB_ZCL_UINT40_MAX) /*!< ZCL_VALUE_FF for uint40_t. */
#define EZB_ZCL_VALUE_UINT48_FF ((uint64_t)EZB_ZCL_UINT48_MAX) /*!< ZCL_VALUE_FF for uint48_t. */
#define EZB_ZCL_VALUE_UINT56_FF ((uint64_t)EZB_ZCL_UINT56_MAX) /*!< ZCL_VALUE_FF for uint56_t. */
#define EZB_ZCL_VALUE_UINT64_FF ((uint64_t)EZB_ZCL_VALUE_FF)   /*!< ZCL_VALUE_FF for uint64_t. */

#define EZB_ZCL_VALUE_INT8_NaS  ((int8_t)INT8_MIN)               /*!< ZCL_VALUE_NaS for int8_t. */
#define EZB_ZCL_VALUE_INT16_NaS ((int16_t)INT16_MIN)             /*!< ZCL_VALUE_NaS for int16_t. */
#define EZB_ZCL_VALUE_INT24_NaS ((int32_t)EZB_ZCL_INT24_MIN - 1) /*!< ZCL_VALUE_NaS for int24_t. */
#define EZB_ZCL_VALUE_INT32_NaS ((int32_t)INT32_MIN)             /*!< ZCL_VALUE_NaS for int32_t. */
#define EZB_ZCL_VALUE_INT40_NaS ((int64_t)EZB_ZCL_INT40_MIN - 1) /*!< ZCL_VALUE_NaS for int40_t. */
#define EZB_ZCL_VALUE_INT48_NaS ((int64_t)EZB_ZCL_INT48_MIN - 1) /*!< ZCL_VALUE_NaS for int48_t. */
#define EZB_ZCL_VALUE_INT56_NaS ((int64_t)EZB_ZCL_INT56_MIN - 1) /*!< ZCL_VALUE_NaS for int56_t. */
#define EZB_ZCL_VALUE_INT64_NaS ((int64_t)INT64_MIN)             /*!< ZCL_VALUE_NaS for int64_t. */

#define EZB_ZCL_VALUE_UINT8_NONE  EZB_ZCL_VALUE_UINT8_FF  /*!< ZCL_VALUE_NONE for uint8_t. */
#define EZB_ZCL_VALUE_UINT16_NONE EZB_ZCL_VALUE_UINT16_FF /*!< ZCL_VALUE_NONE for uint16_t. */
#define EZB_ZCL_VALUE_UINT24_NONE EZB_ZCL_VALUE_UINT24_FF /*!< ZCL_VALUE_NONE for uint24_t. */
#define EZB_ZCL_VALUE_UINT32_NONE EZB_ZCL_VALUE_UINT32_FF /*!< ZCL_VALUE_NONE for uint32_t. */
#define EZB_ZCL_VALUE_UINT40_NONE EZB_ZCL_VALUE_UINT40_FF /*!< ZCL_VALUE_NONE for uint40_t. */
#define EZB_ZCL_VALUE_UINT48_NONE EZB_ZCL_VALUE_UINT48_FF /*!< ZCL_VALUE_NONE for uint48_t. */
#define EZB_ZCL_VALUE_UINT56_NONE EZB_ZCL_VALUE_UINT56_FF /*!< ZCL_VALUE_NONE for uint56_t. */
#define EZB_ZCL_VALUE_UINT64_NONE EZB_ZCL_VALUE_UINT64_FF /*!< ZCL_VALUE_NONE for uint64_t. */

#define EZB_ZCL_VALUE_INT8_NONE  EZB_ZCL_VALUE_INT8_NaS  /*!< ZCL_VALUE_INT8_NONE for int8_t. */
#define EZB_ZCL_VALUE_INT16_NONE EZB_ZCL_VALUE_INT16_NaS /*!< ZCL_VALUE_INT16_NONE for int16_t. */
#define EZB_ZCL_VALUE_INT24_NONE EZB_ZCL_VALUE_INT24_NaS /*!< ZCL_VALUE_INT24_NONE for int24_t. */
#define EZB_ZCL_VALUE_INT32_NONE EZB_ZCL_VALUE_INT32_NaS /*!< ZCL_VALUE_INT32_NONE for int32_t. */
#define EZB_ZCL_VALUE_INT40_NONE EZB_ZCL_VALUE_INT40_NaS /*!< ZCL_VALUE_INT40_NONE for int40_t. */
#define EZB_ZCL_VALUE_INT48_NONE EZB_ZCL_VALUE_INT48_NaS /*!< ZCL_VALUE_INT48_NONE for int48_t. */
#define EZB_ZCL_VALUE_INT56_NONE EZB_ZCL_VALUE_INT56_NaS /*!< ZCL_VALUE_INT56_NONE for int56_t. */
#define EZB_ZCL_VALUE_INT64_NONE EZB_ZCL_VALUE_INT64_NaS /*!< ZCL_VALUE_INT64_NONE for int64_t. */

#define EZB_ZCL_VALUE_SINGLE_NONE EZB_ZCL_VALUE_NaN /*!< ZCL_VALUE_SINGLE_NONE for float. */
#define EZB_ZCL_VALUE_DOUBLE_NONE EZB_ZCL_VALUE_NaN /*!< ZCL_VALUE_DOUBLE_NONE for double. */

/**
 * @brief ZCL status codes.
 * @anchor ezb_zcl_status_e
 *
 * These status codes are returned by ZCL operations to indicate success or
 * various error conditions. They follow the Zigbee Cluster Library specification.
 */
enum ezb_zcl_status_e {
    EZB_ZCL_STATUS_SUCCESS            = 0x00U,   /*!< ZCL Success */
    EZB_ZCL_STATUS_FAIL               = 0x01U,   /*!< ZCL Fail */
    EZB_ZCL_STATUS_NOT_AUTHORIZED     = 0x7EU,   /*!< Server is not authorized to upgrade the client */
    EZB_ZCL_STATUS_MALFORMED_CMD      = 0x80U,   /*!< Malformed command */
    EZB_ZCL_STATUS_UNSUP_CMD          = 0x81U,   /*!< Unsupported cluster command */
    EZB_ZCL_STATUS_INVALID_FIELD      = 0x85U,   /*!< Invalid field */
    EZB_ZCL_STATUS_UNSUP_ATTRIB       = 0x86U,   /*!< Unsupported attribute */
    EZB_ZCL_STATUS_INVALID_VALUE      = 0x87U,   /*!< Invalid value */
    EZB_ZCL_STATUS_READ_ONLY          = 0x88U,   /*!< Read only */
    EZB_ZCL_STATUS_INSUFFICIENT_SPACE = 0x89U,   /*!< Insufficient space */
    EZB_ZCL_STATUS_NOT_FOUND          = 0x8bU,   /*!< Not found */
    EZB_ZCL_STATUS_UNREPORTBLE_ATTRIB = 0x8cU,   /*!< Unreporttable attribute */
    EZB_ZCL_STATUS_INVALID_TYPE       = 0x8dU,   /*!< Invalid type */
    EZB_ZCL_STATUS_INCONSISTENT       = 0x92U,   /*!< Supplied values are inconsistent */
    EZB_ZCL_STATUS_ACTION_DENIED      = 0x93U,   /*!< The credentials presented by the device sending the command are not
                                                      sufficient to perform this action. */
    EZB_ZCL_STATUS_TIMEOUT            = 0x94U,   /*!< Timeout */
    EZB_ZCL_STATUS_ABORT              = 0x95U,   /*!< Abort */
    EZB_ZCL_STATUS_INVALID_IMAGE      = 0x96U,   /*!< Invalid OTA upgrade image */
    EZB_ZCL_STATUS_WAIT_FOR_DATA      = 0x97U,   /*!< Server does not have data block available yet */
    EZB_ZCL_STATUS_NO_IMAGE_AVAILABLE = 0x98U,   /*!< No OTA upgrade image available for the client */
    EZB_ZCL_STATUS_REQUIRE_MORE_IMAGE = 0x99U,   /*!< The client still requires more OTA upgrade image files to
                                                     successfully upgrade.  */
    EZB_ZCL_STATUS_NOTIFICATION_PENDING = 0x9AU, /*!< The command has been received and is being processed. */
    EZB_ZCL_STATUS_CALIBRATION_ERROR    = 0xc2U, /*!< Calibration error */
    EZB_ZCL_STATUS_UNSUPPORTED_CLUSTER  = 0xc3U, /*!< Cluster is not found on the target endpoint */
};

/**
 * @brief Represents the status of ZCL command, see values of @ref ezb_zcl_status_e
 * @anchor ezb_zcl_status_t
 */
typedef uint8_t ezb_zcl_status_t;

/**
 * @brief Enumeration of ZCL general command identifiers.
 *
 * These are the standard ZCL general commands that are available in all clusters.
 * General commands are frame type 0x00 and include attribute operations and discovery.
 */
enum ezb_zcl_general_cmd_e {
    EZB_ZCL_CMD_READ_ATTRIBUTES                       = 0x00U, /*!< Command to read one or more attributes from a cluster. */
    EZB_ZCL_CMD_READ_ATTRIBUTES_RESPONSE              = 0x01U, /*!< Response to a read attributes command. */
    EZB_ZCL_CMD_WRITE_ATTRIBUTES                      = 0x02U, /*!< Command to write one or more attributes to a cluster. */
    EZB_ZCL_CMD_WRITE_ATTRIBUTES_UNDIVIDED            = 0x03U, /*!< Command to write multiple attributes atomically. */
    EZB_ZCL_CMD_WRITE_ATTRIBUTES_RESPONSE             = 0x04U, /*!< Response to a write attributes command. */
    EZB_ZCL_CMD_WRITE_ATTRIBUTES_NO_RESPONSE          = 0x05U, /*!< Command to write attributes without requiring a response. */
    EZB_ZCL_CMD_CONFIGURE_REPORTING                   = 0x06U, /*!< Command to configure attribute reporting. */
    EZB_ZCL_CMD_CONFIGURE_REPORTING_RESPONSE          = 0x07U, /*!< Response to a configure reporting command. */
    EZB_ZCL_CMD_READ_REPORTING_CONFIGURATION          = 0x08U, /*!< Command to read reporting configuration for attributes. */
    EZB_ZCL_CMD_READ_REPORTING_CONFIGURATION_RESPONSE = 0x09U, /*!< Response to a read reporting configuration command. */
    EZB_ZCL_CMD_REPORT_ATTRIBUTES                     = 0x0aU, /*!< Command to report attribute values (unsolicited). */
    EZB_ZCL_CMD_DEFAULT_RESPONSE                      = 0x0bU, /*!< Default response to any ZCL command. */
    EZB_ZCL_CMD_DISCOVER_ATTRIBUTES                   = 0x0cU, /*!< Command to discover supported attributes in a cluster. */
    EZB_ZCL_CMD_DISCOVER_ATTRIBUTES_RESPONSE          = 0x0dU, /*!< Response to a discover attributes command. */
    EZB_ZCL_CMD_READ_ATTRIBUTES_STRUCTURED            = 0x0eU, /*!< Command to read structured attributes (advanced). */
    EZB_ZCL_CMD_WRITE_ATTRIBUTES_STRUCTURED           = 0x0fU, /*!< Command to write structured attributes (advanced). */
    EZB_ZCL_CMD_WRITE_ATTRIBUTES_STRUCTURED_RESPONSE  = 0x10U, /*!< Response to a write structured attributes command. */
    EZB_ZCL_CMD_DISCOVER_COMMANDS_RECEIVED            = 0x11U, /*!< Command to discover commands that can be received. */
    EZB_ZCL_CMD_DISCOVER_COMMANDS_RECEIVED_RESPONSE   = 0x12U, /*!< Response to a discover commands received command. */
    EZB_ZCL_CMD_DISCOVER_COMMANDS_GENERATED           = 0x13U, /*!< Command to discover commands that can be generated. */
    EZB_ZCL_CMD_DISCOVER_COMMANDS_GENERATED_RESPONSE  = 0x14U, /*!< Response to a discover commands generated command. */
    EZB_ZCL_CMD_DISCOVER_ATTRIBUTES_EXTENDED          = 0x15U, /*!< Command to discover extended attribute information. */
    EZB_ZCL_CMD_DISCOVER_ATTRIBUTES_EXTENDED_RESPONSE = 0x16U, /*!< Response to a discover attributes extended command. */
};
typedef uint8_t ezb_zcl_cmd_id_t;

/** @brief Attribute identifier. */
typedef uint16_t ezb_zcl_attr_id_t;

/**
 * @brief Enumeration of ZCL attribute data types.
 * @anchor ezb_zcl_attr_type_e
 *
 * These types define the data format for ZCL attributes. The types follow the
 * Zigbee Cluster Library specification and include primitive types, strings,
 * arrays, and complex types.
 */
enum ezb_zcl_attr_type_e {
    EZB_ZCL_ATTR_TYPE_NO_DATA      = 0x00U, /*!< Null data type. */
    EZB_ZCL_ATTR_TYPE_DATA8        = 0x08U, /*!< 8-bit data. */
    EZB_ZCL_ATTR_TYPE_DATA16       = 0x09U, /*!< 16-bit data. */
    EZB_ZCL_ATTR_TYPE_DATA24       = 0x0aU, /*!< 24-bit data. */
    EZB_ZCL_ATTR_TYPE_DATA32       = 0x0bU, /*!< 32-bit data. */
    EZB_ZCL_ATTR_TYPE_DATA40       = 0x0cU, /*!< 40-bit data. */
    EZB_ZCL_ATTR_TYPE_DATA48       = 0x0dU, /*!< 48-bit data. */
    EZB_ZCL_ATTR_TYPE_DATA56       = 0x0eU, /*!< 56-bit data. */
    EZB_ZCL_ATTR_TYPE_DATA64       = 0x0fU, /*!< 64-bit data. */
    EZB_ZCL_ATTR_TYPE_BOOL         = 0x10U, /*!< Boolean type. */
    EZB_ZCL_ATTR_TYPE_MAP8         = 0x18U, /*!< 8-bit bitmap. */
    EZB_ZCL_ATTR_TYPE_MAP16        = 0x19U, /*!< 16-bit bitmap. */
    EZB_ZCL_ATTR_TYPE_MAP24        = 0x1aU, /*!< 24-bit bitmap. */
    EZB_ZCL_ATTR_TYPE_MAP32        = 0x1bU, /*!< 32-bit bitmap. */
    EZB_ZCL_ATTR_TYPE_MAP40        = 0x1cU, /*!< 40-bit bitmap. */
    EZB_ZCL_ATTR_TYPE_MAP48        = 0x1dU, /*!< 48-bit bitmap. */
    EZB_ZCL_ATTR_TYPE_MAP56        = 0x1eU, /*!< 56-bit bitmap. */
    EZB_ZCL_ATTR_TYPE_MAP64        = 0x1fU, /*!< 64-bit bitmap. */
    EZB_ZCL_ATTR_TYPE_UINT8        = 0x20U, /*!< Unsigned 8-bit integer. */
    EZB_ZCL_ATTR_TYPE_UINT16       = 0x21U, /*!< Unsigned 16-bit integer. */
    EZB_ZCL_ATTR_TYPE_UINT24       = 0x22U, /*!< Unsigned 24-bit integer. */
    EZB_ZCL_ATTR_TYPE_UINT32       = 0x23U, /*!< Unsigned 32-bit integer. */
    EZB_ZCL_ATTR_TYPE_UINT40       = 0x24U, /*!< Unsigned 40-bit integer. */
    EZB_ZCL_ATTR_TYPE_UINT48       = 0x25U, /*!< Unsigned 48-bit integer. */
    EZB_ZCL_ATTR_TYPE_UINT56       = 0x26U, /*!< Unsigned 56-bit integer. */
    EZB_ZCL_ATTR_TYPE_UINT64       = 0x27U, /*!< Unsigned 64-bit integer. */
    EZB_ZCL_ATTR_TYPE_INT8         = 0x28U, /*!< Signed 8-bit integer. */
    EZB_ZCL_ATTR_TYPE_INT16        = 0x29U, /*!< Signed 16-bit integer. */
    EZB_ZCL_ATTR_TYPE_INT24        = 0x2aU, /*!< Signed 24-bit integer. */
    EZB_ZCL_ATTR_TYPE_INT32        = 0x2bU, /*!< Signed 32-bit integer. */
    EZB_ZCL_ATTR_TYPE_INT40        = 0x2cU, /*!< Signed 40-bit integer. */
    EZB_ZCL_ATTR_TYPE_INT48        = 0x2dU, /*!< Signed 48-bit integer. */
    EZB_ZCL_ATTR_TYPE_INT56        = 0x2eU, /*!< Signed 56-bit integer. */
    EZB_ZCL_ATTR_TYPE_INT64        = 0x2fU, /*!< Signed 64-bit integer. */
    EZB_ZCL_ATTR_TYPE_ENUM8        = 0x30U, /*!< 8-bit enumeration. */
    EZB_ZCL_ATTR_TYPE_ENUM16       = 0x31U, /*!< 16-bit enumeration. */
    EZB_ZCL_ATTR_TYPE_SEMI         = 0x38U, /*!< Semi-precision floating point. */
    EZB_ZCL_ATTR_TYPE_SINGLE       = 0x39U, /*!< Single-precision floating point. */
    EZB_ZCL_ATTR_TYPE_DOUBLE       = 0x3aU, /*!< Double-precision floating point. */
    EZB_ZCL_ATTR_TYPE_OCTSTR       = 0x41U, /*!< Octet string. */
    EZB_ZCL_ATTR_TYPE_STRING       = 0x42U, /*!< Character string. */
    EZB_ZCL_ATTR_TYPE_OCTSTR16     = 0x43U, /*!< Long octet string. */
    EZB_ZCL_ATTR_TYPE_STRING16     = 0x44U, /*!< Long character string. */
    EZB_ZCL_ATTR_TYPE_ARRAY        = 0x48U, /*!< Array. */
    EZB_ZCL_ATTR_TYPE_ARRAY_DATA16 = 0x49U, /*!< 16-bit array. */
    EZB_ZCL_ATTR_TYPE_ARRAY_DATA32 = 0x4aU, /*!< 32-bit array. */
    EZB_ZCL_ATTR_TYPE_STRUCT       = 0x4cU, /*!< Structure. */
    EZB_ZCL_ATTR_TYPE_SET          = 0x50U, /*!< Set. */
    EZB_ZCL_ATTR_TYPE_BAG          = 0x51U, /*!< Bag. */
    EZB_ZCL_ATTR_TYPE_TOD          = 0xe0U, /*!< Time of day. */
    EZB_ZCL_ATTR_TYPE_DATE         = 0xe1U, /*!< Date. */
    EZB_ZCL_ATTR_TYPE_UTC          = 0xe2U, /*!< UTC time. */
    EZB_ZCL_ATTR_TYPE_CLUSTER_ID   = 0xe8U, /*!< Cluster ID. */
    EZB_ZCL_ATTR_TYPE_ATTRIBUTE_ID = 0xe9U, /*!< Attribute ID. */
    EZB_ZCL_ATTR_TYPE_BAC_OID      = 0xeaU, /*!< BACnet object identifier. */
    EZB_ZCL_ATTR_TYPE_EUI64        = 0xf0U, /*!< IEEE address. */
    EZB_ZCL_ATTR_TYPE_KEY128       = 0xf1U, /*!< 128-bit security key. */
    EZB_ZCL_ATTR_TYPE_INTERNAL     = 0xfeU, /*!< Internal attribute type */
    EZB_ZCL_ATTR_TYPE_UNK          = 0xffU  /*!< Invalid attribute type. */
};

/**
 * @brief Represents the data type of ZCL attribute, see values of @ref ezb_zcl_attr_type_e
 * @anchor ezb_zcl_attr_type_t
 */
typedef uint8_t ezb_zcl_attr_type_t;

/**
 * @brief Enumeration the bitmask of ZCL attribute access control.
 * @anchor ezb_zcl_attr_access_e
 */
enum ezb_zcl_attr_access_e {
    EZB_ZCL_ATTR_ACCESS_READ      = 0x01U, /*!< Attribute is readable. */
    EZB_ZCL_ATTR_ACCESS_WRITE     = 0x02U, /*!< Attribute is writeable. */
    EZB_ZCL_ATTR_ACCESS_REPORTING = 0x04U, /*!< Attribute supports reporting. */
    EZB_ZCL_ATTR_ACCESS_SCENE     = 0x10U, /*!< Attribute is used in scene management. */
};

/**
 * @brief Represents the access control flags of ZCL attribute, see values of @ref ezb_zcl_attr_access_e
 * @anchor ezb_zcl_attr_access_t
 */
typedef uint8_t ezb_zcl_attr_access_t;

/** @brief Attribute is read only */
#define EZB_ZCL_ATTR_ACCESS_READ_ONLY (EZB_ZCL_ATTR_ACCESS_READ)

/** @brief Attribute is write only */
#define EZB_ZCL_ATTR_ACCESS_WRITE_ONLY (EZB_ZCL_ATTR_ACCESS_WRITE)

/** @brief Attribute is readable and writeable */
#define EZB_ZCL_ATTR_ACCESS_READ_WRITE (EZB_ZCL_ATTR_ACCESS_READ | EZB_ZCL_ATTR_ACCESS_WRITE)

/**
 * @brief Enumeration of ZCL cluster identifiers.
 *
 * These identifiers define the standard Zigbee clusters as specified in the
 * Zigbee Cluster Library. Clusters 0x8000-0xFFFF are reserved for custom clusters.
 */
enum ezb_zcl_cluster_id_e {
    EZB_ZCL_CLUSTER_ID_BASIC                      = 0x0000U, /*!< Basic cluster identifier. */
    EZB_ZCL_CLUSTER_ID_POWER_CONFIG               = 0x0001U, /*!< Power configuration cluster identifier. */
    EZB_ZCL_CLUSTER_ID_DEVICE_TEMP_CONFIG         = 0x0002U, /*!< Device temperature configuration cluster identifier. */
    EZB_ZCL_CLUSTER_ID_IDENTIFY                   = 0x0003U, /*!< Identify cluster identifier. */
    EZB_ZCL_CLUSTER_ID_GROUPS                     = 0x0004U, /*!< Groups cluster identifier. */
    EZB_ZCL_CLUSTER_ID_SCENES                     = 0x0005U, /*!< Scenes cluster identifier. */
    EZB_ZCL_CLUSTER_ID_ON_OFF                     = 0x0006U, /*!< On/Off cluster identifier. */
    EZB_ZCL_CLUSTER_ID_ON_OFF_SWITCH_CONFIG       = 0x0007U, /*!< On/Off switch configuration cluster identifier. */
    EZB_ZCL_CLUSTER_ID_LEVEL                      = 0x0008U, /*!< Level control cluster identifier. */
    EZB_ZCL_CLUSTER_ID_ALARMS                     = 0x0009U, /*!< Alarms cluster identifier. */
    EZB_ZCL_CLUSTER_ID_TIME                       = 0x000aU, /*!< Time cluster identifier. */
    EZB_ZCL_CLUSTER_ID_RSSI_LOCATION              = 0x000bU, /*!< RSSI location cluster identifier. */
    EZB_ZCL_CLUSTER_ID_ANALOG_INPUT               = 0x000cU, /*!< Analog input (basic) cluster identifier. */
    EZB_ZCL_CLUSTER_ID_ANALOG_OUTPUT              = 0x000dU, /*!< Analog output (basic) cluster identifier. */
    EZB_ZCL_CLUSTER_ID_ANALOG_VALUE               = 0x000eU, /*!< Analog value (basic) cluster identifier. */
    EZB_ZCL_CLUSTER_ID_BINARY_INPUT               = 0x000fU, /*!< Binary input (basic) cluster identifier. */
    EZB_ZCL_CLUSTER_ID_BINARY_OUTPUT              = 0x0010U, /*!< Binary output (basic) cluster identifier. */
    EZB_ZCL_CLUSTER_ID_BINARY_VALUE               = 0x0011U, /*!< Binary value (basic) cluster identifier. */
    EZB_ZCL_CLUSTER_ID_MULTISTATE_INPUT           = 0x0012U, /*!< Multistate input (basic) cluster identifier. */
    EZB_ZCL_CLUSTER_ID_MULTISTATE_OUTPUT          = 0x0013U, /*!< Multistate output (basic) cluster identifier. */
    EZB_ZCL_CLUSTER_ID_MULTISTATE_VALUE           = 0x0014U, /*!< Multistate value (basic) cluster identifier. */
    EZB_ZCL_CLUSTER_ID_COMMISSIONING              = 0x0015U, /*!< Commissioning cluster identifier. */
    EZB_ZCL_CLUSTER_ID_OTA_UPGRADE                = 0x0019U, /*!< Over The Air cluster identifier. */
    EZB_ZCL_CLUSTER_ID_POLL_CONTROL               = 0x0020U, /*!< Poll control cluster identifier. */
    EZB_ZCL_CLUSTER_ID_GREEN_POWER                = 0x0021U, /*!< Green Power cluster identifier. */
    EZB_ZCL_CLUSTER_ID_KEEP_ALIVE                 = 0x0025U, /*!< Keep Alive cluster identifier. */
    EZB_ZCL_CLUSTER_ID_SHADE_CONFIG               = 0x0100U, /*!< Shade configuration cluster identifier. */
    EZB_ZCL_CLUSTER_ID_DOOR_LOCK                  = 0x0101U, /*!< Door lock cluster identifier. */
    EZB_ZCL_CLUSTER_ID_WINDOW_COVERING            = 0x0102U, /*!< Window covering cluster identifier. */
    EZB_ZCL_CLUSTER_ID_PUMP_CONFIG_CONTROL        = 0x0200U, /*!< Pump configuration and control cluster identifier. */
    EZB_ZCL_CLUSTER_ID_THERMOSTAT                 = 0x0201U, /*!< Thermostat cluster identifier. */
    EZB_ZCL_CLUSTER_ID_FAN_CONTROL                = 0x0202U, /*!< Fan control cluster identifier. */
    EZB_ZCL_CLUSTER_ID_DEHUMIDIFICATION_CONTROL   = 0x0203U, /*!< Dehumidification control cluster identifier. */
    EZB_ZCL_CLUSTER_ID_THERMOSTAT_UI_CONFIG       = 0x0204U, /*!< Thermostat user interface configuration cluster identifier. */
    EZB_ZCL_CLUSTER_ID_COLOR_CONTROL              = 0x0300U, /*!< Color control cluster identifier. */
    EZB_ZCL_CLUSTER_ID_BALLAST_CONFIG             = 0x0301U, /*!< Ballast configuration cluster identifier. */
    EZB_ZCL_CLUSTER_ID_ILLUMINANCE_MEASUREMENT    = 0x0400U, /*!< Illuminance measurement */
    EZB_ZCL_CLUSTER_ID_TEMPERATURE_MEASUREMENT    = 0x0402U, /*!< Temperature measurement */
    EZB_ZCL_CLUSTER_ID_PRESSURE_MEASUREMENT       = 0x0403U, /*!< Pressure measurement */
    EZB_ZCL_CLUSTER_ID_FLOW_MEASUREMENT           = 0x0404U, /*!< Flow measurement */
    EZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT   = 0x0405U, /*!< Relative humidity measurement */
    EZB_ZCL_CLUSTER_ID_OCCUPANCY_SENSING          = 0x0406U, /*!< Occupancy sensing */
    EZB_ZCL_CLUSTER_ID_PH_MEASUREMENT             = 0x0409U, /*!< pH measurement */
    EZB_ZCL_CLUSTER_ID_EC_MEASUREMENT             = 0x040aU, /*!< Electrical conductivity measurement */
    EZB_ZCL_CLUSTER_ID_WIND_SPEED_MEASUREMENT     = 0x040bU, /*!< Wind speed measurement */
    EZB_ZCL_CLUSTER_ID_CARBON_DIOXIDE_MEASUREMENT = 0x040dU, /*!< Carbon dioxide measurement */
    EZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT          = 0x042aU, /*!< PM2.5 measurement */
    EZB_ZCL_CLUSTER_ID_IAS_ZONE                   = 0x0500U, /*!< IAS zone */
    EZB_ZCL_CLUSTER_ID_IAS_ACE                    = 0x0501U, /*!< IAS ACE */
    EZB_ZCL_CLUSTER_ID_IAS_WD                     = 0x0502U, /*!< IAS WD */
    EZB_ZCL_CLUSTER_ID_PRICE                      = 0x0700U, /*!< Price cluster identifier. */
    EZB_ZCL_CLUSTER_ID_DRLC                       = 0x0701U, /*!< Demand Response and Load Control cluster identifier */
    EZB_ZCL_CLUSTER_ID_METERING                   = 0x0702U, /*!< Metering */
    EZB_ZCL_CLUSTER_ID_TUNNEL                     = 0x0704U, /*!< Tunnel */
    EZB_ZCL_CLUSTER_ID_METER_IDENTIFICATION       = 0x0b01U, /*!< Meter Identification cluster identifier */
    EZB_ZCL_CLUSTER_ID_ELECTRICAL_MEASUREMENT     = 0x0b04U, /*!< Electrical measurement */
    EZB_ZCL_CLUSTER_ID_DIAGNOSTICS                = 0x0b05U, /*!< Home Automation Diagnostics */
    EZB_ZCL_CLUSTER_ID_TOUCHLINK_COMMISSIONING    = 0x1000U, /*!< Touchlink commissioning */
};
typedef uint16_t ezb_zcl_cluster_id_t;

#define EZB_ZCL_CUSTOM_CLUSTER_ID_MIN_VAL 0x8000U /*!< Minimum value for custom cluster IDs. */

#define EZB_ZCL_CLUSTER_ID_MIN_CUSTOM EZB_ZCL_CUSTOM_CLUSTER_ID_MIN_VAL /*!< Minimum value for custom cluster IDs. */

#define EZB_ZCL_INVALID_UTC_TIME UINT32_MAX /*!< Invalid UTC time. */

#ifdef __cplusplus
} /*  extern "C" */
#endif
