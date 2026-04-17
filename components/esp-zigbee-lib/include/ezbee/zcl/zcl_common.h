/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/core_types.h>

#include <ezbee/af.h>

#include <ezbee/zcl/zcl_type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure for ZCL command confirmation.
 *
 * This structure is triggered when a ZCL command is sent and contains
 * information about the transmission result.
 */
typedef ezb_af_user_cnf_t ezb_zcl_cmd_cnf_t;

/**
 * @brief Context for ZCL command confirmation callback.
 *
 * This structure contains the callback function and user context that will be
 * invoked when a ZCL command transmission completes.
 */
typedef ezb_af_user_cnf_ctx_t ezb_zcl_cmd_cnf_ctx_t;

/**
 * @brief Structure representing a Zigbee attribute.
 *
 * This structure contains all information needed to represent a ZCL attribute,
 * including its identifier, data type, size, and value pointer.
 */
typedef struct ezb_zcl_attribute_s {
    uint16_t id; /*!< Attribute identifier. */
    struct {
        uint8_t  type;  /*!< Attribute data type, see @ref ezb_zcl_attr_type_t. */
        uint16_t size;  /*!< Size of the attribute value in bytes. */
        void    *value; /*!< Pointer to the attribute value buffer. Must be valid for the specified size. */
    } data;             /*!< Attribute data and type information. */
} ezb_zcl_attribute_t;

/**
 * @brief Structure for the command control of ZCL command.
 */
typedef struct ezb_zcl_cmd_ctrl_s {
    ezb_address_t dst_addr;   /*!< Destination address (short or extended). */
    uint8_t       dst_ep;     /*!< Destination endpoint ID. */
    uint8_t       src_ep;     /*!< Source endpoint ID. */
    uint16_t      cluster_id; /*!< Cluster ID. */
    uint16_t      manuf_code; /*!< Manufacturer code (only used if manuf_specific is 1).
                                   Use @ref EZB_ZCL_STD_MANUF_CODE for standard commands. */
    struct {
        uint8_t manuf_specific : 1;  /*!< Set to 1 if command is manufacturer-specific, 0 otherwise. */
        uint8_t direction : 1;       /*!< Command direction: 0=to server, 1=to client. */
        uint8_t dis_default_rsp : 1; /*!< Set to 1 to disable default response, 0 to enable. */
    } fc;                            /*!< Frame control flags. */
    ezb_zcl_cmd_cnf_ctx_t cnf_ctx;   /*!< Confirmation callback context, triggered when command transmission completes. */
} ezb_zcl_cmd_ctrl_t;

/**
 * @brief Structure for the command control of ZCL cluster-specific command.
 *
 * This structure contains control information for sending cluster-specific
 * commands (non-general commands). Cluster ID is determined by the command context.
 */
typedef struct ezb_zcl_cluster_cmd_ctrl_s {
    ezb_address_t         dst_addr;        /*!< Destination address (short or extended). */
    uint8_t               dst_ep;          /*!< Destination endpoint ID. */
    uint8_t               src_ep;          /*!< Source endpoint ID. */
    bool                  dis_default_rsp; /*!< Set to true to disable default response, false to enable. */
    ezb_zcl_cmd_cnf_ctx_t cnf_ctx;         /*!< Confirmation callback context, triggered when command transmission completes. */
} ezb_zcl_cluster_cmd_ctrl_t;

/**
 * @brief Structure for the frame control of ZCL command
 */
typedef struct ezb_zcl_cmd_fc_s {
    uint8_t frame_type : 2; /*!< Frame type: @ref EZB_ZCL_FRAME_TYPE_COMMON or @ref EZB_ZCL_FRAME_TYPE_CLUSTER_SPECIFIC. */
    uint8_t manuf_spec : 1; /*!< Manufacturer specific: 1 if the command is manufacturer-specific, 0 otherwise. */
    uint8_t direction : 1;  /*!< Command direction: 0=to server, 1=to client. */
    uint8_t disable_def_resp : 1; /*!< Disable default response: 1 to disable default response, 0 to enable. */
    uint8_t reserved : 3;         /*!< Reserved bits. */
} ezb_zcl_cmd_fc_t;

#define EZB_ZCL_CMD_FC_GET_FRAME_TYPE(fc) ((fc)&0x03U) /*!< Get the frame type of a ZCL command frame control. */
#define EZB_ZCL_CMD_FC_SET_FRAME_TYPE(fc, type) \
    {                                           \
        (fc) &= ~0x03U;                         \
        (fc) |= (type & 0x03U);                 \
    } /*!< Set the frame type of a ZCL command frame control. */

#define EZB_ZCL_CMD_FC_IS_MANUF_SPEC(fc) (((fc)&0x04U) != 0) /*!< The ZCL command frame control is manufacturer specific. */
#define EZB_ZCL_CMD_FC_SET_MANUF_SPEC(fc)                                              \
    ((fc) |= 0x04U) /*!< Set the manufacturer specific of a ZCL command frame control. \
                     */
#define EZB_ZCL_CMD_FC_CLR_MANUF_SPEC(fc) \
    ((fc) &= ~0x04U) /*!< Clear the manufacturer specific of a ZCL command frame control. */

#define EZB_ZCL_CMD_FC_IS_TO_CLI_DIRECTION(fc) (((fc)&0x08U) != 0)  /*!< The ZCL command frame control is to client. */
#define EZB_ZCL_CMD_FC_SET_DIRECTION(fc) ((fc) |= 0x08U)  /*!< Set the direction of a ZCL command frame control. */
#define EZB_ZCL_CMD_FC_CLR_DIRECTION(fc) ((fc) &= ~0x08U) /*!< Clear the direction of a ZCL command frame control. */

#define EZB_ZCL_CMD_FC_IS_DIS_DEFAULT_RSP(fc) \
    (((fc)&0x10U) != 0) /*!< The ZCL command frame control is disable default response. */
#define EZB_ZCL_CMD_FC_SET_DIS_DEFAULT_RSP(fc) \
    ((fc) |= 0x10U) /*!< Set the disable default response of a ZCL command frame control. */
#define EZB_ZCL_CMD_FC_CLR_DIS_DEFAULT_RSP(fc) \
    ((fc) &= ~0x10U) /*!< Clear the disable default response of a ZCL command frame control. */

/**
 * @brief Structure containing information about a received ZCL command.
 *
 * This structure is populated when a ZCL command is received and contains
 * all addressing and frame control information from the command header.
 */
typedef struct ezb_zcl_cmd_hdr_s {
    ezb_address_t src_addr;   /*!< Source address (short and IEEE address). */
    ezb_address_t dst_addr;   /*!< Destination address of the command. */
    uint8_t       src_ep;     /*!< Source endpoint ID. */
    uint8_t       dst_ep;     /*!< Destination endpoint ID. */
    uint16_t      cluster_id; /*!< Cluster ID for the command. */
    uint16_t      profile_id; /*!< Application profile identifier (e.g., 0x0104 for Home Automation). */
    uint8_t       fc;         /*!< Frame control byte (frame type, direction, etc.). */
    uint16_t      manuf_code; /*!< Manufacturer code (0x0000 if not manufacturer-specific). */
    uint8_t       tsn;        /*!< Transaction sequence number (0x00-0xFF). */
    int8_t        rssi;       /*!< Received signal strength indicator in dBm. */
    uint8_t       cmd_id;     /*!< Command identifier (0x00-0xFF). */
} ezb_zcl_cmd_hdr_t;

/**
 * @brief Structure containing common information for Zigbee device callbacks.
 *
 * This structure is included in all ZCL message structures and provides
 * common information about the received command or response.
 */
typedef struct ezb_zcl_message_info_s {
    ezb_zcl_status_t status;       /*!< Status of the message processing. See @ref ezb_zcl_status_t. */
    uint8_t          dst_ep;       /*!< The destination endpoint ID of the ZCL indication. */
    uint16_t         cluster_id;   /*!< The cluster ID of the ZCL indication. */
    uint8_t          cluster_role; /*!< The role of cluster: @ref EZB_ZCL_CLUSTER_SERVER or @ref EZB_ZCL_CLUSTER_CLIENT. */
} ezb_zcl_message_info_t;

/**
 * @brief Structure for set attribute value message in Zigbee device callback.
 */
typedef struct ezb_zcl_set_attr_value_message_s {
    ezb_zcl_message_info_t info; /*!< Common information for Zigbee device callback. */
    struct {
        ezb_zcl_attribute_t attribute; /*!< Attribute to set. */
    } in;                              /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of the set attribute operation. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_set_attr_value_message_t;

/**
 * @brief Structure for manufacturer-specific command message.
 */
typedef struct ezb_zcl_manuf_spec_cmd_message_s {
    ezb_zcl_message_info_t info; /*!< Common information */
    struct {
        const ezb_zcl_cmd_hdr_t *header;       /*!< ZCL command header information, See @ref ezb_zcl_cmd_hdr_s. */
        uint16_t                 payload_size; /*!< Payload size. */
        uint8_t                 *payload;      /*!< Payload. */
    } in;                                      /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of the set attribute operation. */
    } out;                       /*!< Output: result to send back. */

} ezb_zcl_manuf_spec_cmd_message_t;

/**
 * @brief Set the value of a ZCL attribute.
 *
 * This function updates an attribute value in the ZCL data model. If check_access
 * is true, it will verify that the attribute is writable before updating.
 *
 * @param ep_id        Endpoint ID.
 * @param cluster_id   Cluster ID.
 * @param cluster_role Cluster role: @ref EZB_ZCL_CLUSTER_SERVER or @ref EZB_ZCL_CLUSTER_CLIENT.
 * @param attr_id      Attribute ID.
 * @param manuf_code   Manufacturer code. Use @ref EZB_ZCL_STD_MANUF_CODE for standard attributes.
 * @param value        Pointer to the new attribute value. Must match the attribute's data type.
 * @param check_access If true, verify attribute is writable before updating.
 * @return ZCL status code. EZB_ZCL_STATUS_SUCCESS on success, error code otherwise.
 */
ezb_zcl_status_t ezb_zcl_set_attr_value(uint8_t  ep_id,
                                        uint16_t cluster_id,
                                        uint8_t  cluster_role,
                                        uint16_t attr_id,
                                        uint16_t manuf_code,
                                        void    *value,
                                        bool     check_access);

/**
 * @brief Get the size of a ZCL attribute value.
 *
 * This function calculates the size in bytes of an attribute value based on its
 * data type. For variable-length types (strings, arrays), the attr_value pointer
 * must be provided to read the length field.
 *
 * @param attr_type  Attribute data type. See @ref ezb_zcl_attr_type_t.
 * @param attr_value  Pointer to the attribute value. Required for variable-length types (strings, arrays),
 *                        can be NULL for fixed-size types.
 * @return Size of the attribute value in bytes.
 */
uint16_t ezb_zcl_get_attr_value_size(ezb_zcl_attr_type_t attr_type, const void *attr_value);

/**
 * @brief Write the attribute value to the buffer.
 *
 * @param buffer Pointer to the buffer to write the attribute value.
 * @param value  Pointer to the operational attribute value.
 * @param value_type  Attribute data type. See @ref ezb_zcl_attr_type_t.
 * @return true if the value is written successfully, false otherwise.
 */
bool ezb_zcl_write_attr_value(uint8_t *buffer, const void *value, ezb_zcl_attr_type_t value_type);

/**
 * @brief Read the attribute value from the buffer.
 *
 * @param value  Pointer to the operational attribute value.
 * @param buffer Pointer to the buffer to read the attribute value.
 * @param value_type  Attribute data type. See @ref ezb_zcl_attr_type_t.
 * @return true if the value is read successfully, false otherwise.
 */
bool ezb_zcl_read_attr_value(void *value, const uint8_t *buffer, ezb_zcl_attr_type_t value_type);

/**
 * @brief Check if an attribute type is analog (numeric, continuous).
 *
 * Analog attributes can have reporting thresholds (delta values) configured.
 * Examples include integers, floats, and time values.
 *
 * @param attr_type Attribute type. See @ref ezb_zcl_attr_type_t.
 * @return true if the attribute type is analog, false otherwise.
 */
bool ezb_zcl_attr_type_is_analog(ezb_zcl_attr_type_t attr_type);

/**
 * @brief Check if an attribute type is composite (variable-length).
 *
 * Composite attributes have variable length and include strings, arrays,
 * structures, sets, and bags.
 *
 * @param attr_type Attribute type. See @ref ezb_zcl_attr_type_t.
 * @return true if the attribute is composite, false otherwise.
 */
bool ezb_zcl_attr_type_is_composite(ezb_zcl_attr_type_t attr_type);

/**
 * @brief Check if an attribute type is discrete (fixed-length).
 *
 * Discrete attributes have a fixed length and include integers, booleans,
 * and enumerations.
 *
 * @param attr_type Attribute type. See @ref ezb_zcl_attr_type_t.
 * @return true if the attribute is discrete, false otherwise.
 */
bool ezb_zcl_attr_type_is_discrete(ezb_zcl_attr_type_t attr_type);

/**
 * @brief Check if an attribute supports reporting.
 *
 * This function checks if the attribute has the reporting access flag set,
 * indicating it can be configured for automatic attribute reporting.
 *
 * @param attr_desc Pointer to the attribute descriptor.
 * @return true if the attribute supports reporting, false otherwise.
 */
bool ezb_zcl_attr_is_reportable(ezb_zcl_attr_desc_t attr_desc);

#ifdef __cplusplus
} /*  extern "C" */
#endif
