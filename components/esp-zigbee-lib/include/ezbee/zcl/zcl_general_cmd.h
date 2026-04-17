/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/zcl_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure for ZCL read attribute command request.
 *
 * This structure is used to construct a ZCL read attribute command.
 * The command can read one or more attributes from a cluster on a remote device.
 *
 * @note The attr_field array must contain at least attr_number elements.
 * @note The response will be delivered via the callback specified in cmd_ctrl.cnf_ctx.
 */
typedef struct ezb_zcl_read_attr_cmd_s {
    ezb_zcl_cmd_ctrl_t cmd_ctrl; /*!< Command control structure. See @ref ezb_zcl_cmd_ctrl_s. */
    struct {
        uint8_t   attr_number; /*!< Number of attributes to read (1-255). Must match the size of attr_field array. */
        uint16_t *attr_field;  /*!< Array of attribute IDs to read. Must be valid for the specified cluster_id. */
    } payload;                 /*!< Command payload containing attribute IDs to read. */
} ezb_zcl_read_attr_cmd_t;

/**
 * @brief Structure for ZCL write attribute command request.
 *
 * This structure is used to construct a ZCL write attribute command.
 * The command can write one or more attributes to a cluster on a remote device.
 *
 * @note The attr_field array must contain at least attr_number elements.
 * @note Each attribute's value must match its specified data type and size.
 * @note The response will be delivered via the callback specified in cmd_ctrl.cnf_ctx.
 */
typedef struct ezb_zcl_write_attr_cmd_s {
    ezb_zcl_cmd_ctrl_t cmd_ctrl; /*!< Command control structure. See @ref ezb_zcl_cmd_ctrl_s. */
    struct {
        uint8_t attr_number;             /*!< Number of attributes to write (1-255). Must match the size of attr_field array. */
        ezb_zcl_attribute_t *attr_field; /*!< Array of attributes to write. Each element contains ID, type, size, and value. */
    } payload;                           /*!< Command payload containing attributes to write. */
} ezb_zcl_write_attr_cmd_t;

/**
 * @brief Structure for ZCL configure reporting record.
 *
 * This structure specifies the reporting configuration for a single attribute.
 * The union field (client or server) is used based on the direction field.
 *
 * @note For direction = EZB_ZCL_REPORTING_SEND (0), use the client structure.
 * @note For direction = EZB_ZCL_REPORTING_RECV (1), use the server structure.
 * @note Setting max_interval to 0xFFFF disables periodic reporting.
 * @note For analog attributes, reportable_change specifies the minimum delta to trigger a report.
 */
typedef struct ezb_zcl_config_report_record_s {
    uint8_t  direction; /*!< Reporting direction: @ref EZB_ZCL_REPORTING_SEND (0) or @ref EZB_ZCL_REPORTING_RECV (1). */
    uint16_t attr_id;   /*!< Attribute ID to configure reporting. */
    union {
        struct {
            uint8_t  attr_type;    /*!< Attribute data type. See @ref ezb_zcl_attr_type_t. */
            uint16_t min_interval; /*!< Minimum reporting interval in seconds (0x0001-0xFFFE). Use 0 for immediate reporting. */
            uint16_t max_interval; /*!< Maximum reporting interval in seconds (0x0001-0xFFFE). Use 0xFFFF to disable periodic
                                      reporting. */
            ezb_zcl_attr_variable_t
                reportable_change; /*!< Minimum change to attribute value that triggers a report.
                                        Required for analog attributes. attributes. Must match attr_type size. */
        } client;                  /*!< Client-side reporting configuration (server reports to client). */
        struct {
            uint16_t timeout; /*!< Timeout period in seconds for server-side reporting (0x0001-0xFFFE). */
        } server;             /*!< Server-side reporting configuration (client receives reports from server). */
    };                        /*!< Union of reporting configuration for client or server. */
} ezb_zcl_config_report_record_t;

/**
 * @brief Structure for ZCL configure reporting command request.
 *
 * Used to construct a ZCL configure reporting command.
 */
typedef struct ezb_zcl_config_report_cmd_s {
    ezb_zcl_cmd_ctrl_t cmd_ctrl; /*!< Command control, see @ref ezb_zcl_cmd_ctrl_s */
    struct {
        uint16_t                        record_number; /*!< Number of report configuration records in the record_field array. */
        ezb_zcl_config_report_record_t *record_field;  /*!< Array of report configuration records,
                                                            @ref ezb_zcl_config_report_record_s */
    } payload;                                         /*!< Payload containing report configuration records. */
} ezb_zcl_config_report_cmd_t;

/**
 * @brief Structure for a single read report configuration record.
 *
 * Used in ZCL read report configuration command.
 */
typedef struct ezb_zcl_read_report_config_record_s {
    uint8_t report_direction; /*!< Report direction of this attribute, @ref EZB_ZCL_REPORTING_SEND
                                   or @ref EZB_ZCL_REPORTING_RECV */
    uint16_t attr_id;         /*!< Attribute ID to report. */
} ezb_zcl_read_report_config_record_t;

/**
 * @brief Structure for ZCL read report configuration command request.
 *
 * Used to construct a ZCL read report configuration command.
 */
typedef struct ezb_zcl_read_report_config_cmd_s {
    ezb_zcl_cmd_ctrl_t cmd_ctrl; /*!< Command control, see @ref ezb_zcl_cmd_ctrl_s */
    struct {
        uint16_t                             record_number; /*!< Number of attribute records in the record_field array. */
        ezb_zcl_read_report_config_record_t *record_field;  /*!< Array of attribute records,
                                                                 @ref ezb_zcl_read_report_config_record_s */
    } payload;                                              /*!< Payload containing attribute records. */
} ezb_zcl_read_report_config_cmd_t;

/**
 * @brief Structure for ZCL report attribute command request.
 *
 * This structure is used to construct a ZCL report attribute command.
 * This command is typically sent by a server to notify clients of attribute value changes.
 * The command will report all attributes configured for reporting that have changed.
 *
 * @note The actual attributes reported depend on the reporting configuration and which
 *       attributes have changed since the last report.
 */
typedef struct ezb_zcl_report_attr_cmd_s {
    ezb_zcl_cmd_ctrl_t cmd_ctrl; /*!< Command control structure. See @ref ezb_zcl_cmd_ctrl_s. */
    struct {
        uint16_t attr_id; /*!< Attribute ID to report. This triggers reporting for this attribute
                              and any other attributes configured for consolidated reporting. */
    } payload;            /*!< Command payload for attribute reporting. */
} ezb_zcl_report_attr_cmd_t;

/**
 * @brief Structure for ZCL discover attributes command request.
 *
 * This structure is used to construct a ZCL discover attributes command,
 * which queries a remote device for the attributes it supports in a cluster.
 * The response will contain a list of supported attributes starting from start_attr_id.
 */
typedef struct ezb_zcl_disc_attr_cmd_s {
    ezb_zcl_cmd_ctrl_t cmd_ctrl; /*!< Command control structure. See @ref ezb_zcl_cmd_ctrl_s. */
    struct {
        uint16_t start_attr_id;   /*!< The attribute identifier at which to begin discovery. */
        uint8_t  max_attr_number; /*!< Maximum number of attribute identifiers to return (1-255). */
    } payload;                    /*!< Command payload for attribute discovery. */
} ezb_zcl_disc_attr_cmd_t;

/**
 * @brief Structure for ZCL discover commands command request.
 *
 * This structure is used to construct a ZCL discover commands command,
 * which queries a remote device for the commands it supports in a cluster.
 * The response will contain a list of supported commands.
 */
typedef struct ezb_zcl_disc_cmd_cmd_s {
    ezb_zcl_cmd_ctrl_t cmd_ctrl; /*!< Command control structure. See @ref ezb_zcl_cmd_ctrl_s. */
    struct {
        uint8_t  is_recv;        /*!< Set to 1 to discover received commands, 0 to discover generated commands. */
        uint16_t start_cmd_id;   /*!< The command identifier at which to begin discovery (0x00-0xFF). */
        uint8_t  max_cmd_number; /*!< Maximum number of command identifiers to return (1-255). */
    } payload;                   /*!< Command payload for command discovery. */
} ezb_zcl_disc_cmd_cmd_t;

/**
 * @brief Structure for ZCL default response command request.
 *
 * This structure is used to construct a ZCL default response command.
 */
typedef struct ezb_zcl_default_rsp_cmd_s {
    ezb_zcl_cmd_ctrl_t cmd_ctrl; /*!< Command control structure. See @ref ezb_zcl_cmd_ctrl_s. */
    struct {
        uint8_t tsn;         /*!< Transaction sequence number. */
        uint8_t rsp_to_cmd;  /*!< Command ID to which this is a response. */
        uint8_t status_code; /*!< Status code of the response. See @ref ezb_zcl_status_t. */
    } payload;               /*!< Command payload for default response. */
} ezb_zcl_default_rsp_cmd_t;

/**
 * @brief Structure for a single read attribute response variable.
 *
 * This structure represents one attribute in a read attribute response.
 * Multiple attributes are linked together in a list using the next pointer.
 *
 * @note The attr_value pointer is only valid if status is EZB_ZCL_STATUS_SUCCESS.
 * @note The memory for attr_value is managed by the ZCL stack and will be freed
 *       when the message is processed. Copy the value if you need to retain it.
 */
typedef struct ezb_zcl_read_attr_rsp_variable_s {
    uint16_t attr_id;    /*!< Attribute ID that was read. */
    uint8_t  status;     /*!< Status of the read operation. See @ref ezb_zcl_status_t. */
    uint8_t  attr_type;  /*!< Data type of the attribute. See @ref ezb_zcl_attr_type_t. Only valid if status is SUCCESS. */
    void    *attr_value; /*!< Pointer to the attribute value buffer. Only valid if status is SUCCESS. */
    struct ezb_zcl_read_attr_rsp_variable_s *next; /*!< Pointer to the next variable in the response list, or NULL if last. */
} ezb_zcl_read_attr_rsp_variable_t;

/**
 * @brief Structure for ZCL read attribute response message.
 *
 * This message structure is delivered to the application callback when a read
 * attribute response is received. It contains the results of the read operation
 * for each requested attribute.
 */
typedef struct ezb_zcl_cmd_read_attr_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Common information about the received message.
                                          See @ref ezb_zcl_message_info_s. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;             /*!< ZCL command header information.
                                                          See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_read_attr_rsp_variable_t *variables; /*!< Linked list of attribute response variables.
                                                           Each variable contains one attribute's read result. */
    } in;                                            /*!< Input data from the received response. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. Set this to indicate how the application processed
                                    the response. */
    } out;                       /*!< Output data to be returned to the ZCL stack. */
} ezb_zcl_cmd_read_attr_rsp_message_t;

/**
 * @brief Structure for a single write attribute response variable.
 *
 * This structure represents the result of writing one attribute in a write
 * attribute response. Multiple attributes are linked together in a list.
 *
 * @note If status is EZB_ZCL_STATUS_SUCCESS, the attr_id field is omitted
 *       (set to 0xFFFF) to save space in the response.
 */
typedef struct ezb_zcl_write_attr_rsp_variable_s {
    ezb_zcl_status_t status;  /*!< Status of the write operation. See @ref ezb_zcl_status_t. */
    uint16_t         attr_id; /*!< Attribute ID that was written. Only present if status is not SUCCESS. */
    struct ezb_zcl_write_attr_rsp_variable_s *next; /*!< Pointer to the next variable in the response list, or NULL if last. */
} ezb_zcl_write_attr_rsp_variable_t;

/**
 * @brief Structure for ZCL write attribute response message.
 *
 * This message structure is delivered to the application callback when a write
 * attribute response is received. It contains the results of the write operation
 * for each attribute that was written.
 */
typedef struct ezb_zcl_cmd_write_attr_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Common information about the received response. See @ref ezb_zcl_message_info_s. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information. See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_write_attr_rsp_variable_t
            *variables; /*!< Linked list of write response variables. Each variable contains one attribute's write result. */
    } in;               /*!< Input data from the received response. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. Set this to indicate how the application processed
                                    the response. */
    } out;                       /*!< Output data to be returned to the ZCL stack. */
} ezb_zcl_cmd_write_attr_rsp_message_t;

/**
 * @brief Structure for a single configure report response variable.
 *
 * This structure represents the result of configuring reporting for one attribute
 * in a configure reporting response. Multiple attributes are linked together in a list.
 *
 * @note If status is EZB_ZCL_STATUS_SUCCESS, the direction and attr_id fields
 *       are omitted (set to 0xFF and 0xFFFF respectively) to save space.
 */
typedef struct ezb_zcl_config_report_rsp_variable_s {
    uint8_t status;    /*!< Status of the configure report operation. See @ref ezb_zcl_status_t. */
    uint8_t direction; /*!< Reporting direction: @ref EZB_ZCL_REPORTING_SEND or @ref EZB_ZCL_REPORTING_RECV. Only present if
                          status is not SUCCESS. */
    uint16_t attr_id;  /*!< Attribute ID for the report. Only present if status is not SUCCESS. */
    struct ezb_zcl_config_report_rsp_variable_s
        *next; /*!< Pointer to the next variable in the response list, or NULL if last. */
} ezb_zcl_config_report_rsp_variable_t;

/**
 * @brief Structure for ZCL configure reporting response message.
 *
 * This message structure is delivered to the application callback when a configure
 * reporting response is received. It contains the results of configuring reporting
 * for each requested attribute.
 */
typedef struct ezb_zcl_cmd_config_report_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Common information about the received response. See @ref ezb_zcl_message_info_s. */
    struct {
        const ezb_zcl_cmd_hdr_t              *header;    /*!< ZCL command header information. See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_config_report_rsp_variable_t *variables; /*!< Linked list of configure report response variables. Each variable
                                                             contains one attribute's configuration result. */
    } in;                                                /*!< Input data from the received response. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. Set this to indicate how the application processed
                                    the response. */
    } out;                       /*!< Output data to be returned to the ZCL stack. */
} ezb_zcl_cmd_config_report_rsp_message_t;

/**
 * @brief Structure for a single read report configuration response variable.
 *
 * This structure represents the reporting configuration for one attribute in a
 * read report configuration response. Multiple attributes are linked together in a list.
 * The union field (client or server) is used based on the direction field.
 *
 * @note If status is not EZB_ZCL_STATUS_SUCCESS, the union fields are omitted.
 */
typedef struct ezb_zcl_read_report_config_rsp_variable_s {
    ezb_zcl_status_t status;    /*!< Status of the read report configuration operation. See @ref ezb_zcl_status_t. */
    uint8_t          direction; /*!< Reporting direction: @ref EZB_ZCL_REPORTING_SEND or @ref EZB_ZCL_REPORTING_RECV. */
    uint16_t         attr_id;   /*!< Attribute ID for the report. */
    union {
        struct {
            uint8_t attr_type;     /*!< Attribute data type. See @ref ezb_zcl_attr_type_t. Only valid if status is SUCCESS and
                                      direction is SEND. */
            uint16_t min_interval; /*!< Minimum reporting interval in seconds. Only valid if status is SUCCESS and direction is
                                      SEND. */
            uint16_t max_interval; /*!< Maximum reporting interval in seconds. Only valid if status is SUCCESS and direction is
                                      SEND. */
            ezb_zcl_attr_variable_t delta; /*!< Minimum change to attribute value that triggers a report. Only valid for analog
                                        attributes if status is SUCCESS and direction is SEND. */
        } client;                          /*!< Client-side reporting configuration (server reports to client). */
        struct {
            uint16_t timeout; /*!< Timeout period in seconds for server-side reporting. Only valid if status is SUCCESS and
                                 direction is RECV. */
        } server;             /*!< Server-side reporting configuration (client receives reports from server). */
    };                        /*!< Union of reporting configuration for client or server. */
    struct ezb_zcl_read_report_config_rsp_variable_s *next; /*!< Pointer to the next variable in the response list,
                                                                  or NULL if last. */
} ezb_zcl_read_report_config_rsp_variable_t;

/**
 * @brief Structure for ZCL read report configuration response message.
 *
 * This message structure is delivered to the application callback when a read
 * report configuration response is received. It contains the current reporting
 * configuration for each requested attribute.
 */
typedef struct ezb_zcl_cmd_read_report_config_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Common information about the received response. See @ref ezb_zcl_message_info_s. */
    struct {
        const ezb_zcl_cmd_hdr_t                   *header; /*!< ZCL command header information. See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_read_report_config_rsp_variable_t *variables; /*!< Linked list of read report configuration variables. Each
                                                                  variable contains one attribute's reporting configuration. */
    } in;                                                     /*!< Input data from the received response. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. Set this to indicate how the application processed
                                    the response. */
    } out;                       /*!< Output data to be returned to the ZCL stack. */
} ezb_zcl_cmd_read_report_config_rsp_message_t;

/**
 * @brief Structure for a single report attribute variable.
 *
 * This structure represents one attribute in an unsolicited report attribute
 * message. Multiple attributes can be reported in a single message for efficiency.
 * The attributes are linked together in a list.
 *
 * @note The memory for attr_value is managed by the ZCL stack and will be freed
 *       when the message is processed. Copy the value if you need to retain it.
 */
typedef struct ezb_zcl_report_attr_variable_s {
    uint16_t attr_id;                            /*!< Attribute ID being reported. */
    uint8_t  attr_type;                          /*!< Data type of the attribute. See @ref ezb_zcl_attr_type_t. */
    void    *attr_value;                         /*!< Pointer to the attribute value buffer. The size depends on attr_type. */
    struct ezb_zcl_report_attr_variable_s *next; /*!< Pointer to the next variable in the report list, or NULL if last. */
} ezb_zcl_report_attr_variable_t;

/**
 * @brief Structure for ZCL report attribute message.
 *
 * This message structure is delivered to the application callback when an
 * unsolicited report attribute command is received. This typically occurs when
 * a remote device reports attribute value changes based on configured reporting.
 */
typedef struct ezb_zcl_cmd_report_attr_message_s {
    ezb_zcl_message_info_t info; /*!< Common information about the received report. See @ref ezb_zcl_message_info_s. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information. See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_report_attr_variable_t
            *variables; /*!< Linked list of report attribute variables. Each variable contains one reported attribute. */
    } in;               /*!< Input data from the received report. */
    struct {
        ezb_zcl_status_t
            result; /*!< Status of processing in application. Set this to indicate how the application processed the report. */
    } out;          /*!< Output data to be returned to the ZCL stack. */
} ezb_zcl_cmd_report_attr_message_t;

/**
 * @brief Structure for a single discover attribute variable.
 *
 * This structure represents one discovered attribute in a discover attributes
 * response. Multiple attributes are linked together in a list.
 */
typedef struct ezb_zcl_disc_attr_variable_s {
    uint16_t                             attr_id;   /*!< Attribute ID discovered. */
    uint8_t                              attr_type; /*!< Data type of the attribute. See @ref ezb_zcl_attr_type_t. */
    struct ezb_zcl_disc_attr_variable_s *next;      /*!< Pointer to the next variable in the discovery list, or NULL if last. */
} ezb_zcl_disc_attr_variable_t;

/**
 * @brief Structure for ZCL discover attributes response message.
 *
 * This message structure is delivered to the application callback when a discover
 * attributes response is received. It contains a list of attributes supported
 * by the remote device in the specified cluster.
 */
typedef struct ezb_zcl_cmd_discover_attributes_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Common information about the received response. See @ref ezb_zcl_message_info_s. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information. See @ref ezb_zcl_cmd_hdr_s. */
        uint8_t is_completed; /*!< Set to 1 if all attributes have been discovered, 0 if more attributes exist beyond the
                                 returned list. */
        ezb_zcl_disc_attr_variable_t
            *variables; /*!< Linked list of discovered attribute variables. Each variable contains one discovered attribute. */
    } in;               /*!< Input data from the received response. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. Set this to indicate how the application processed
                                    the response. */
    } out;                       /*!< Output data to be returned to the ZCL stack. */
} ezb_zcl_cmd_discover_attributes_rsp_message_t;

/**
 * @brief Structure for a single discover command variable.
 *
 * This structure represents one discovered command in a discover commands response.
 * Multiple commands are linked together in a list.
 */
typedef struct ezb_zcl_disc_cmd_variable_s {
    uint8_t                             cmd_id; /*!< Command ID discovered (0x00-0xFF). */
    struct ezb_zcl_disc_cmd_variable_s *next;   /*!< Pointer to the next variable in the discovery list, or NULL if last. */
} ezb_zcl_disc_cmd_variable_t;

/**
 * @brief Structure for ZCL discover commands response message.
 *
 * This message structure is delivered to the application callback when a discover
 * commands response is received. It contains a list of commands supported by
 * the remote device in the specified cluster.
 */
typedef struct ezb_zcl_cmd_discover_commands_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Common information about the received response. See @ref ezb_zcl_message_info_s. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;        /*!< ZCL command header information. See @ref ezb_zcl_cmd_hdr_s. */
        uint8_t                  is_recv;       /*!< Set to 1 if discovering received commands, 0 for generated commands. */
        uint8_t                  is_completed;  /*!< Set to 1 if all commands have been discovered, 0 if more commands exist
                                                     beyond the returned list. */
        ezb_zcl_disc_cmd_variable_t *variables; /*!< Linked list of discovered command variables. Each variable contains
                                                     one discovered command ID. */
    } in;                                       /*!< Input data from the received response. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. Set this to indicate how the application processed
                                    the response. */
    } out;                       /*!< Output data to be returned to the ZCL stack. */
} ezb_zcl_cmd_discover_commands_rsp_message_t;

/**
 * @brief Structure for ZCL default response message.
 *
 * This message structure is delivered to the application callback when a default
 * response is received. A default response is sent when a command cannot be processed
 * or when the disable default response bit is not set.
 */
typedef struct ezb_zcl_cmd_default_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Common information about the received response. See @ref ezb_zcl_message_info_s. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;      /*!< ZCL command header information. See @ref ezb_zcl_cmd_hdr_s. */
        uint8_t                  rsp_to_cmd;  /*!< Command ID (0x00-0xFF) to which this is a response. */
        uint8_t                  status_code; /*!< Status code of the response. See @ref ezb_zcl_status_t. */
    } in;                                     /*!< Input data from the received default response. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. Set this to indicate how the application processed
                                    the response. */
    } out;                       /*!< Output data to be returned to the ZCL stack. */
} ezb_zcl_cmd_default_rsp_message_t;

/**
 * @brief Send a ZCL read attribute command request.
 *
 * This function sends a read attribute command to read one or more attributes
 * from a cluster on a remote device. The response will be delivered via the
 * callback specified in cmd_req->cmd_ctrl.cnf_ctx.
 *
 * @param cmd_req Pointer to the read attribute command structure. Must not be NULL.
 *                    The structure must be properly initialized with valid endpoint IDs,
 *                    cluster ID, and attribute IDs.
 * @return Error code.
 */
ezb_err_t ezb_zcl_read_attr_cmd_req(const ezb_zcl_read_attr_cmd_t *cmd_req);

/**
 * @brief Send a ZCL write attribute command request.
 *
 * This function sends a write attribute command to write one or more attributes
 * to a cluster on a remote device. The response will be delivered via the
 * callback specified in cmd_req->cmd_ctrl.cnf_ctx.
 *
 * @param cmd_req Pointer to the write attribute command structure. Must not be NULL.
 *                    Each attribute's value must match its specified data type and size.
 * @return Error code.
 */
ezb_err_t ezb_zcl_write_attr_cmd_req(const ezb_zcl_write_attr_cmd_t *cmd_req);

/**
 * @brief Send a ZCL configure reporting command request.
 *
 * This function sends a configure reporting command to configure automatic
 * attribute reporting for one or more attributes. The response will be
 * delivered via the callback specified in cmd_req->cmd_ctrl.cnf_ctx.
 *
 * @param cmd_req Pointer to the configure report command structure. Must not be NULL.
 *                    Each record must have valid direction, attr_id, and appropriate union fields.
 * @return Error code.
 */
ezb_err_t ezb_zcl_config_report_cmd_req(const ezb_zcl_config_report_cmd_t *cmd_req);

/**
 * @brief Send a ZCL read reporting configuration command request.
 *
 * This function sends a read reporting configuration command to query the current
 * reporting configuration for one or more attributes. The response will be
 * delivered via the callback specified in cmd_req->cmd_ctrl.cnf_ctx.
 *
 * @param cmd_req Pointer to the read report configuration command structure. Must not be NULL.
 *                    Each record must specify direction and attr_id.
 * @return Error code.
 */
ezb_err_t ezb_zcl_read_report_config_cmd_req(const ezb_zcl_read_report_config_cmd_t *cmd_req);

/**
 * @brief Send a ZCL report attribute command request.
 *
 * This function sends an unsolicited report attribute command to report the current
 * value of one or more attributes. This is typically used by servers to notify
 * clients of attribute value changes.
 *
 * @param cmd_req Pointer to the report attribute command structure. Must not be NULL.
 *                    The attribute ID must be valid and the attribute must support reporting.
 * @return Error code.
 */
ezb_err_t ezb_zcl_report_attr_cmd_req(const ezb_zcl_report_attr_cmd_t *cmd_req);

/**
 * @brief Send a ZCL discover attributes command request.
 *
 * This function sends a discover attributes command to query a remote device for
 * the attributes it supports in a cluster. The response will be delivered via
 * the callback specified in cmd_req->cmd_ctrl.cnf_ctx.
 *
 * @param cmd_req Pointer to the discover attributes command structure. Must not be NULL.
 *                    The start_attr_id and max_attr_number must be set appropriately.
 * @return Error code.
 */
ezb_err_t ezb_zcl_disc_attr_cmd_req(const ezb_zcl_disc_attr_cmd_t *cmd_req);

/**
 * @brief Send a ZCL discover commands command request.
 *
 * This function sends a discover commands command to query a remote device for
 * the commands it supports (received or generated) in a cluster. The response
 * will be delivered via the callback specified in cmd_req->cmd_ctrl.cnf_ctx.
 *
 * @param cmd_req Pointer to the discover commands command structure. Must not be NULL.
 *                    The is_recv, start_cmd_id, and max_cmd_number must be set appropriately.
 * @return Error code.
 */
ezb_err_t ezb_zcl_disc_cmd_cmd_req(const ezb_zcl_disc_cmd_cmd_t *cmd_req);

/**
 * @brief Send a ZCL default response command request.
 *
 * This function sends a ZCL default response command to respond a command.
 *
 * @param cmd_req Pointer to the default response command structure, @ref ezb_zcl_default_rsp_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_default_rsp_cmd_req(const ezb_zcl_default_rsp_cmd_t *cmd_req);

#ifdef __cplusplus
} /*  extern "C" */
#endif
