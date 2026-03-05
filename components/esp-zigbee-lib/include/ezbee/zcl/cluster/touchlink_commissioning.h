/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/touchlink_commissioning_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure for the ZCL Touchlink Commissioning GetGroupIdentifiers command request.
 */
typedef struct ezb_zcl_touchlink_get_group_ids_cmd_req_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl;    /*!< Control information for the ZCL command. */
    uint8_t                    start_index; /*!< Starting index for retrieving group identifiers. */
} ezb_zcl_touchlink_get_group_ids_cmd_req_t;

/**
 * @brief Structure for the ZCL Touchlink Commissioning GetEndpointList command request.
 */
typedef struct ezb_zcl_touchlink_get_ep_list_cmd_req_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl;    /*!< Control information for the ZCL command. */
    uint8_t                    start_index; /*!< Starting index for retrieving endpoint list. */
} ezb_zcl_touchlink_get_ep_list_cmd_req_t;

/**
 * @brief Structure for the ZCL Touchlink Commissioning EndpointInformation command request.
 */
typedef struct ezb_zcl_touchlink_ep_info_cmd_req_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl;       /*!< Control information for the ZCL command. */
    ezb_extaddr_t              ieee_addr;      /*!< IEEE address of the device. */
    uint16_t                   nwk_addr;       /*!< Network address of the device. */
    uint8_t                    ep_id;          /*!< Endpoint identifier. */
    uint16_t                   profile_id;     /*!< Application profile identifier. */
    uint16_t                   device_id;      /*!< Device identifier. */
    uint8_t                    device_version; /*!< Device version number. */
} ezb_zcl_touchlink_ep_info_cmd_req_t;

/**
 * @brief Structure containing endpoint information for Touchlink Commissioning.
 */
typedef struct ezb_zcl_touchlink_ep_info_s {
    ezb_extaddr_t ieee_addr;  /*!< Extended IEEE address (64-bit). */
    uint16_t      nwk_addr;   /*!< Network address (16-bit). */
    uint8_t       ep_id;      /*!< Endpoint identifier. */
    uint16_t      profile_id; /*!< Application profile identifier. */
    uint16_t      device_id;  /*!< Device identifier. */
    uint8_t       version;    /*!< Device version number. */
} ezb_zcl_touchlink_ep_info_t;

/**
 * @brief Structure for the ZCL Touchlink Commissioning GetGroupIdentifiers response.
 */
typedef struct ezb_zcl_touchlink_get_group_ids_rsp_s {
    uint8_t   total;       /*!< Total number of group identifiers available. */
    uint8_t   start_index; /*!< Starting index of the returned group identifiers. */
    uint8_t   count;       /*!< Number of group identifiers in this response. */
    uint16_t *group_ids;   /*!< Pointer to array of group identifiers. */
} ezb_zcl_touchlink_get_group_ids_rsp_t;

/**
 * @brief Structure for a single endpoint information record.
 */
typedef struct ezb_zcl_touchlink_ep_info_record_s {
    uint16_t nwk_addr;   /*!< Network address of the device. */
    uint8_t  ep_id;      /*!< Endpoint identifier. */
    uint16_t profile_id; /*!< Application profile identifier. */
    uint16_t device_id;  /*!< Device identifier. */
    uint8_t  version;    /*!< Device version number. */
} ezb_zcl_touchlink_ep_info_record_t;

/**
 * @brief Structure for the ZCL Touchlink Commissioning GetEndpointList response.
 */
typedef struct ezb_zcl_touchlink_get_ep_list_rsp_s {
    uint8_t                             total;       /*!< Total number of endpoints available. */
    uint8_t                             start_index; /*!< Starting index of the returned endpoints. */
    uint8_t                             count;       /*!< Number of endpoint records in this response. */
    ezb_zcl_touchlink_ep_info_record_t *records;     /*!< Pointer to array of endpoint information records. */
} ezb_zcl_touchlink_get_ep_list_rsp_t;

/**
 * @brief Message for the ZCL Touchlink Commissioning EndpointInformation message.
 */
typedef struct ezb_zcl_touchlink_ep_info_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;      /*!< ZCL command header information.
                                                   See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_touchlink_ep_info_t *ep_info; /*!< Pointer to endpoint information. */
    } in;                                     /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_touchlink_ep_info_message_t;

/**
 * @brief Message for the ZCL Touchlink Commissioning GetGroupIdentifiers response message.
 */
typedef struct ezb_zcl_touchlink_get_group_ids_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;            /*!< ZCL command header information.
                                                         See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_touchlink_get_group_ids_rsp_t *rsp; /*!< Pointer to group identifiers response. */
    } in;                                           /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_touchlink_get_group_ids_rsp_message_t;

/**
 * @brief Message for the ZCL Touchlink Commissioning GetEndpointList response message.
 */
typedef struct ezb_zcl_touchlink_get_ep_list_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;          /*!< ZCL command header information.
                                                       See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_touchlink_get_ep_list_rsp_t *rsp; /*!< Pointer to endpoint list response. */
    } in;                                         /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_touchlink_get_ep_list_rsp_message_t;

/**
 * @brief Send ZCL Touchlink Commissioning GetGroupIdentifiers command request.
 *
 * @param cmd_req Pointer to the GetGroupIdentifiers command request structure, @ref
 * ezb_zcl_touchlink_get_group_ids_cmd_req_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_touchlink_get_group_ids_cmd_req(const ezb_zcl_touchlink_get_group_ids_cmd_req_t *cmd_req);

/**
 * @brief Send ZCL Touchlink Commissioning GetEndpointList command request.
 *
 * @param cmd_req Pointer to the GetEndpointList command request structure, @ref ezb_zcl_touchlink_get_ep_list_cmd_req_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_touchlink_get_ep_list_cmd_req(const ezb_zcl_touchlink_get_ep_list_cmd_req_t *cmd_req);

/**
 * @brief Send ZCL Touchlink Commissioning EndpointInformation command request.
 *
 * @param cmd_req Pointer to the EndpointInformation command request structure, @ref ezb_zcl_touchlink_ep_info_cmd_req_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_touchlink_ep_info_cmd_req(const ezb_zcl_touchlink_ep_info_cmd_req_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
