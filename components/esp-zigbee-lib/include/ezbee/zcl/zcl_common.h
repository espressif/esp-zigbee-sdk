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
 */
typedef ezb_af_user_cnf_t ezb_zcl_cmd_cnf_t;

/**
 * @brief Context for ZCL command confirmation callback.
 */
typedef ezb_af_user_cnf_ctx_t ezb_zcl_cmd_cnf_ctx_t;

/**
 * @brief Structure representing a Zigbee attribute.
 */
typedef struct ezb_zcl_attribute_s {
    uint16_t id; /*!< Identifier of the attribute. */
    struct {
        uint8_t  type;  /*!< Type of the attribute, see @ref ezb_zcl_attr_type_t. */
        uint16_t size;  /*!< Size of the attribute value in bytes. */
        void    *value; /*!< Pointer to the attribute value buffer. Must be valid for the specified size. */
    } data;             /*!< Information of the attribute. */
} ezb_zcl_attribute_t;

/**
 * @brief Structure for the command control of ZCL command.
 */
typedef struct ezb_zcl_cmd_ctrl_s {
    ezb_address_t dst_addr;   /*!< Destination address. */
    uint8_t       dst_ep;     /*!< Identifier of the destination endpoint. */
    uint8_t       src_ep;     /*!< Identifier of the source endpoint. */
    uint16_t      cluster_id; /*!< Identifier of the cluster. */
    uint16_t      manuf_code; /*!< Manufacturer code (only used if manuf_specific is 1).
                                   Use @ref EZB_ZCL_STD_MANUF_CODE for the standard commands. */
    struct {
        uint8_t manuf_specific : 1;  /*!< Manufacturer-specific, 1 if the command is manufacturer-specific, 0 otherwise. */
        uint8_t direction : 1;       /*!< Command direction: 1 to client, 0 to server. */
        uint8_t dis_default_rsp : 1; /*!< Disable default response, 1 to disable the default response, 0 to enable. */
    } fc;                            /*!< Frame control flags. */
    ezb_zcl_cmd_cnf_ctx_t cnf_ctx;   /*!< Context of the confirmation callback, triggered when the command transmission
                                          completes. */
} ezb_zcl_cmd_ctrl_t;

/**
 * @brief Structure for the command control of ZCL cluster-specific command.
 */
typedef struct ezb_zcl_cluster_cmd_ctrl_s {
    ezb_address_t dst_addr;        /*!< Destination address. */
    uint8_t       dst_ep;          /*!< Identifier of the destination endpoint. */
    uint8_t       src_ep;          /*!< Identifier of the source endpoint. */
    bool          dis_default_rsp; /*!< Disable default response: true to disable, false to enable. */
    ezb_zcl_cmd_cnf_ctx_t cnf_ctx; /*!< Context of the confirmation callback, triggered when the command transmission
                                        completes. */
} ezb_zcl_cluster_cmd_ctrl_t;

/**
 * @brief Structure for the frame control of ZCL command
 */
typedef struct ezb_zcl_cmd_fc_s {
    uint8_t frame_type : 2;       /*!< Type of the frame, either @ref EZB_ZCL_FRAME_TYPE_COMMON or @ref
                                       EZB_ZCL_FRAME_TYPE_CLUSTER_SPECIFIC. */
    uint8_t manuf_spec : 1;       /*!< Manufacturer specific, 1 if the command is manufacturer-specific, 0 otherwise. */
    uint8_t direction : 1;        /*!< Command direction: 1 to client, 0 to server. */
    uint8_t disable_def_resp : 1; /*!< Disable default response, 1 to disable the default response, 0 to enable. */
    uint8_t reserved : 3;         /*!< Reserved bits. */
} ezb_zcl_cmd_fc_t;

/**
 * @brief Get the frame type of a ZCL command frame control.
 */
#define EZB_ZCL_CMD_FC_GET_FRAME_TYPE(fc) ((fc)&0x03U)

/**
 * @brief Set the frame type of a ZCL command frame control.
 */
#define EZB_ZCL_CMD_FC_SET_FRAME_TYPE(fc, type) \
    {                                           \
        (fc) &= ~0x03U;                         \
        (fc) |= (type & 0x03U);                 \
    }

/**
 * @brief Check if the ZCL command frame control is manufacturer specific.
 */
#define EZB_ZCL_CMD_FC_IS_MANUF_SPEC(fc) (((fc)&0x04U) != 0)

/**
 * @brief Set the manufacturer specific of a ZCL command frame control.
 */
#define EZB_ZCL_CMD_FC_SET_MANUF_SPEC(fc) ((fc) |= 0x04U)

/**
 * @brief Clear the manufacturer specific of a ZCL command frame control.
 */
#define EZB_ZCL_CMD_FC_CLR_MANUF_SPEC(fc) ((fc) &= ~0x04U)

/**
 * @brief Check if the ZCL command frame control is to client.
 */
#define EZB_ZCL_CMD_FC_IS_TO_CLI_DIRECTION(fc) (((fc)&0x08U) != 0)

/**
 * @brief Set the direction of a ZCL command frame control.
 */
#define EZB_ZCL_CMD_FC_SET_DIRECTION(fc) ((fc) |= 0x08U)

/**
 * @brief Clear the direction of a ZCL command frame control.
 */
#define EZB_ZCL_CMD_FC_CLR_DIRECTION(fc) ((fc) &= ~0x08U)

/**
 * @brief Check if the ZCL command frame control is disable default response.
 */
#define EZB_ZCL_CMD_FC_IS_DIS_DEFAULT_RSP(fc) (((fc)&0x10U) != 0)

/**
 * @brief Set the disable default response of a ZCL command frame control.
 */
#define EZB_ZCL_CMD_FC_SET_DIS_DEFAULT_RSP(fc) ((fc) |= 0x10U)

/**
 * @brief Clear the disable default response of a ZCL command frame control.
 */
#define EZB_ZCL_CMD_FC_CLR_DIS_DEFAULT_RSP(fc) ((fc) &= ~0x10U)

/**
 * @brief Structure containing information about a received ZCL command.
 */
typedef struct ezb_zcl_cmd_hdr_s {
    ezb_address_t src_addr;   /*!< Source address of the received command. */
    ezb_address_t dst_addr;   /*!< Destination address of the received command. */
    uint8_t       src_ep;     /*!< Identifier of the source endpoint. */
    uint8_t       dst_ep;     /*!< Identifier of the destination endpoint. */
    uint16_t      cluster_id; /*!< Identifier of the cluster. */
    uint16_t      profile_id; /*!< Identifier of the application profile. */
    uint8_t       fc;         /*!< Frame control of header of the received command. */
    uint16_t      manuf_code; /*!< Manufacturer code. */
    uint8_t       tsn;        /*!< Transaction sequence number. */
    int8_t        rssi;       /*!< Received signal strength indicator in dBm. */
    uint8_t       cmd_id;     /*!< Identifier of the command. */
} ezb_zcl_cmd_hdr_t;

/**
 * @brief Structure containing common information for Zigbee device callbacks.
 */
typedef struct ezb_zcl_message_info_s {
    ezb_zcl_status_t status;     /*!< Status of the message processing. See @ref ezb_zcl_status_t. */
    uint8_t          dst_ep;     /*!< Identifier of the destination endpoint. */
    uint16_t         cluster_id; /*!< Identifier of the cluster. */
    uint8_t          cluster_role; /*!< Role of the cluster, either @ref EZB_ZCL_CLUSTER_SERVER or @ref EZB_ZCL_CLUSTER_CLIENT. */
} ezb_zcl_message_info_t;

/**
 * @brief Set attribute value callback message structure.
 */
typedef struct ezb_zcl_set_attr_value_message_s {
    ezb_zcl_message_info_t info; /*!< Common Zigbee device callback information. */
    struct {
        ezb_zcl_attribute_t attribute; /*!< Attribute to be updated. */
    } in;                              /*!< Input parameters parsed from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Result of the attribute update operation. */
    } out;                       /*!< Output result returned to the Zigbee stack. */
} ezb_zcl_set_attr_value_message_t;

/**
 * @brief Structure for manufacturer-specific command message.
 */
typedef struct ezb_zcl_manuf_spec_cmd_message_s {
    ezb_zcl_message_info_t info; /*!< Common Zigbee device callback information. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;       /*!< ZCL command header information, see @ref ezb_zcl_cmd_hdr_s. */
        uint16_t                 payload_size; /*!< Size of the payload. */
        uint8_t                 *payload;      /*!< Pointer to the payload. */
    } in;                                      /*!< Input parameters parsed from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Result of the set attribute operation. */
    } out;                       /*!< Output result returned to the Zigbee stack. */

} ezb_zcl_manuf_spec_cmd_message_t;

/**
 * @brief Set the value of a ZCL attribute.
 *
 * This function updates an attribute in the ZCL data model. If @p check_access is enabled, the function verifies that the
 * attribute is writable before performing the update.
 *
 * @param[in] ep_id         The identifier of the endpoint.
 * @param[in] cluster_id    The identifier of the cluster.
 * @param[in] cluster_role  The role of the cluster, either @ref EZB_ZCL_CLUSTER_SERVER or @ref EZB_ZCL_CLUSTER_CLIENT.
 * @param[in] attr_id       The identifier of the attribute.
 * @param[in] manuf_code    The manufacturer code. Use @ref EZB_ZCL_STD_MANUF_CODE for standard attributes.
 * @param[in] value         The pointer to the attribute value to be written, the data type must match the attribute definition.
 * @param[in] check_access  If true, verifies that the attribute is writable before updating it.
 *
 * @return ZCL status code on success, or error code otherwise.
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
 * This function calculates the size in bytes of an attribute value based on its data type. For variable-length types (strings,
 * arrays), the @p attr_value pointer SHALL NOT be NULL.
 *
 * @param[in] attr_type  The type of the attribute. See @ref ezb_zcl_attr_type_t.
 * @param[in] attr_value The pointer to the attribute value.
 * @return The size of the attribute value in bytes.
 */
uint16_t ezb_zcl_get_attr_value_size(ezb_zcl_attr_type_t attr_type, const void *attr_value);

/**
 * @brief Write attribute value into a buffer.
 *
 * @param[out] buffer     The pointer to the buffer where the attribute value is written.
 * @param[in]  value      The pointer to the attribute value to be written.
 * @param[in]  value_type The type of the attribute value. See @ref ezb_zcl_attr_type_t.
 * @return true if the value is written successfully, false otherwise.
 */
bool ezb_zcl_write_attr_value(uint8_t *buffer, const void *value, ezb_zcl_attr_type_t value_type);

/**
 * @brief Read the attribute value from the buffer.
 *
 * @param[out] value The pointer to the attribute value.
 * @param[in] buffer The pointer to the buffer to read the attribute value.
 * @param[in] value_type  The type of the attribute value. See @ref ezb_zcl_attr_type_t.
 * @return true if the value is read successfully, false otherwise.
 */
bool ezb_zcl_read_attr_value(void *value, const uint8_t *buffer, ezb_zcl_attr_type_t value_type);

/**
 * @brief Check if an attribute type is analog (numeric, continuous).
 *
 * Analog attributes can have reporting thresholds (delta values) configured.
 *
 * @param[in] attr_type The type of the attribute. See @ref ezb_zcl_attr_type_t.
 * @return true if the attribute is analog, false otherwise.
 */
bool ezb_zcl_attr_type_is_analog(ezb_zcl_attr_type_t attr_type);

/**
 * @brief Check if an attribute type is composite (variable-length).
 *
 * Composite attributes have variable length and include strings, arrays, structures, sets, and bags.
 *
 * @param[in] attr_type The type of the attribute. See @ref ezb_zcl_attr_type_t.
 * @return true if the attribute is composite, false otherwise.
 */
bool ezb_zcl_attr_type_is_composite(ezb_zcl_attr_type_t attr_type);

/**
 * @brief Check if an attribute type is discrete (fixed-length).
 *
 * Discrete attributes have a fixed length and include integers, booleans, and enumerations.
 *
 * @param[in] attr_type The type of the attribute. See @ref ezb_zcl_attr_type_t.
 * @return true if the attribute is discrete, false otherwise.
 */
bool ezb_zcl_attr_type_is_discrete(ezb_zcl_attr_type_t attr_type);

/**
 * @brief Check if an attribute supports reporting.
 *
 * This function checks if the attribute has the reporting access flag set, indicating it can be configured for automatic
 * attribute reporting.
 *
 * @param[in] attr_desc The description of the attribute.
 * @return true if the attribute supports reporting, false otherwise.
 */
bool ezb_zcl_attr_is_reportable(ezb_zcl_attr_desc_t attr_desc);

#ifdef __cplusplus
} /*  extern "C" */
#endif
