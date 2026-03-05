/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/ias_zone_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Values of the Enroll Response Code definition.
 */
typedef enum {
    EZB_ZCL_IAS_ZONE_ENROLL_RESPONSE_CODE_SUCCESS        = 0x00, /*!< Success. */
    EZB_ZCL_IAS_ZONE_ENROLL_RESPONSE_CODE_NOT_SUPPORTED  = 0x01, /*!< Not supported. */
    EZB_ZCL_IAS_ZONE_ENROLL_RESPONSE_CODE_NOT_PERMITTED  = 0x02, /*!< No enroll permit. */
    EZB_ZCL_IAS_ZONE_ENROLL_RESPONSE_CODE_TOO_MANY_ZONES = 0x03, /*!< Too many zones. */
} ezb_zcl_ias_zone_enroll_rsp_code_t;

/**
 * @brief Payload for IAS ZONE Enroll request command.
 */
typedef struct ezb_zcl_ias_zone_enroll_req_s {
    uint16_t zone_type;  /*!< Zone type. */
    uint16_t manuf_code; /*!< Manufacturer code. */
} ezb_zcl_ias_zone_enroll_req_payload_t;

/**
 * @brief Payload for IAS ZONE Enroll response command.
 */
typedef struct ezb_zcl_ias_zone_enroll_rsp_payload_s {
    uint8_t enroll_rsp_code; /*!< The enroll response code. */
    uint8_t zone_id;         /*!< The zone ID is the index of the table. */
} ezb_zcl_ias_zone_enroll_rsp_payload_t;

/**
 * @brief Payload for IAS ZONE Zone Status Change Notification command.
 * @note The Zone Status Change Notification command can be triggered by changing the value of the zone status attribute.
 */
typedef struct ezb_zcl_ias_zone_status_change_notif_payload_s {
    uint16_t zone_status;   /*!< The zone status shall be the current value of the zone status attribute. */
    uint8_t  extend_status; /*!< Extended status for additional info. */
    uint8_t  zone_id;       /*!< The zone ID is the index of the table. */
    uint16_t delay;         /*!< Delay in quarter-seconds. */
} ezb_zcl_ias_zone_status_change_notif_payload_t;

/**
 * @brief Payload for IAS ZONE Initiate Test Mode command.
 */
typedef struct ezb_zcl_ias_zone_initiate_test_mode_payload_s {
    uint8_t duration;                       /*!< Duration of the test mode in seconds. */
    uint8_t current_zone_sensitivity_level; /*!< Level of sensitivity for the current zone. */
} ezb_zcl_ias_zone_initiate_test_mode_payload_t;

/**
 * @brief Structure for IAS ZONE Enroll request command.
 */
typedef struct ezb_zcl_ias_zone_enroll_req_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t            cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_ias_zone_enroll_req_payload_t payload;  /*!< Payload for the Enroll request command. */
} ezb_zcl_ias_zone_enroll_req_cmd_t;

/**
 * @brief Structure for IAS ZONE Initiate Normal Operation Mode command.
 */
typedef struct ezb_zcl_ias_zone_initiate_normal_operation_mode_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
} ezb_zcl_ias_zone_initiate_normal_operation_mode_cmd_t;

/**
 * @brief Structure for IAS ZONE Initiate Test Mode command.
 */
typedef struct ezb_zcl_ias_zone_initiate_test_mode_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                    cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_ias_zone_initiate_test_mode_payload_t payload;  /*!< Payload for the Initiate Test Mode command. */
} ezb_zcl_ias_zone_initiate_test_mode_cmd_t;

/**
 * @brief Structure for IAS ZONE Enroll Response command.
 */
typedef struct ezb_zcl_ias_zone_enroll_rsp_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t            cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_ias_zone_enroll_rsp_payload_t payload;  /*!< Payload for the Enroll Response command. */
} ezb_zcl_ias_zone_enroll_rsp_cmd_t;

/**
 * @brief Message for IAS ZONE Enroll Request command message.
 */
typedef struct ezb_zcl_ias_zone_enroll_req_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t              *header;  /*!< Header of command */
        ezb_zcl_ias_zone_enroll_req_payload_t payload; /*!< Payload for the Enroll Request command. */
    } in;                                              /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_zone_enroll_req_message_t;

/**
 * @brief Message for IAS ZONE Enroll Response command message.
 */
typedef struct ezb_zcl_ias_zone_enroll_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                /*!< ZCL command header information.
                                                             See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_zone_enroll_rsp_payload_t payload; /*!< Payload for the Enroll Response command. */
    } in;                                              /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_zone_enroll_rsp_message_t;

/**
 * @brief Message for IAS ZONE Zone Status Change Notification command message.
 */
typedef struct ezb_zcl_ias_zone_status_change_notif_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                      /*!< ZCL command header information.
                                                                 See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_zone_status_change_notif_payload_t payload; /*!< Payload for the Zone Status Change Notification command. */
    } in;                                                       /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_zone_status_change_notif_message_t;

/**
 * @brief Message for IAS ZONE Initiate Test Mode command message.
 */
typedef struct ezb_zcl_ias_zone_initiate_test_mode_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        ezb_zcl_ias_zone_initiate_test_mode_payload_t payload; /*!< Payload for the Initiate Test Mode command. */
    } in;                                                      /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_zone_initiate_test_mode_message_t;

/**
 * @brief Message for IAS ZONE Initiate Normal Mode command message.
 */
typedef struct ezb_zcl_ias_zone_initiate_normal_mode_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_zone_initiate_normal_mode_message_t;

/**
 * @brief Send ZCL IAS ZONE Enroll Request command.
 *
 * @param cmd_req Pointer to the Enroll Request command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_zone_enroll_cmd_req(const ezb_zcl_ias_zone_enroll_req_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ZONE Enroll Response command.
 *
 * @param cmd_resp Pointer to the Enroll Response command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_zone_enroll_cmd_resp(const ezb_zcl_ias_zone_enroll_rsp_cmd_t *cmd_resp);

/**
 * @brief Send ZCL IAS ZONE Initiate Test Mode command.
 *
 * @param cmd_req Pointer to the Initiate Test Mode command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_zone_initiate_test_mode_cmd_req(const ezb_zcl_ias_zone_initiate_test_mode_cmd_t *cmd_req);

/**
 * @brief Send ZCL IAS ZONE Initiate Normal Operation Mode command.
 *
 * @param cmd_req Pointer to the Initiate Normal Operation Mode command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_zone_initiate_normal_operation_mode_cmd_req(
    const ezb_zcl_ias_zone_initiate_normal_operation_mode_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
