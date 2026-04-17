/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/groups_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure for the ZCL Groups AddGroup command request.
 */
typedef struct ezb_zcl_groups_add_group_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint16_t group_id;   /*!< Group identifier to which the destination endpoint will be added. */
        char    *group_name; /*!< Optional group name. */
    } payload;               /*!< Command payload. */
} ezb_zcl_groups_add_group_cmd_t;

/**
 * @brief Structure for the ZCL Groups ViewGroup command request.
 */
typedef struct ezb_zcl_groups_view_group_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint16_t group_id; /*!< Group identifier to query. */
    } payload;             /*!< Command payload. */
} ezb_zcl_groups_view_group_cmd_t;

/**
 * @brief Structure for the ZCL Groups GetGroupMembership command request.
 */
typedef struct ezb_zcl_groups_get_group_membership_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint8_t   group_count; /*!< Number of group IDs in group_list (0 = return all groups). */
        uint16_t *group_list;  /*!< List of group IDs to check for membership. */
    } payload;                 /*!< Command payload. */
} ezb_zcl_groups_get_group_membership_cmd_t;

/**
 * @brief Structure for the ZCL Groups RemoveGroup command request.
 */
typedef struct ezb_zcl_groups_remove_group_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint16_t group_id; /*!< Group identifier from which the destination endpoint will be removed. */
    } payload;             /*!< Command payload. */
} ezb_zcl_groups_remove_group_cmd_t;

/**
 * @brief Structure for the ZCL Groups RemoveAllGroups command request.
 */
typedef struct ezb_zcl_groups_remove_all_groups_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
} ezb_zcl_groups_remove_all_groups_cmd_t;

/**
 * @brief Structure for the ZCL Groups AddGroupIfIdentifying command request.
 */
typedef ezb_zcl_groups_add_group_cmd_t ezb_zcl_groups_add_group_if_identifying_cmd_t;

/**
 * @brief Message for the ZCL Groups AddGroupResponse.
 */
typedef struct ezb_zcl_groups_add_group_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;   /*!< Header of the received ZCL command. */
        uint8_t                  status;   /*!< Status of the AddGroup command (e.g. success, duplicate). */
        uint16_t                 group_id; /*!< Group ID from the AddGroup command. */
    } in;                                  /*!< Input: parsed fields from the response. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_groups_add_group_rsp_message_t;

/**
 * @brief Message for the ZCL Groups ViewGroupResponse.
 */
typedef struct ezb_zcl_groups_view_group_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;     /*!< Header of the received ZCL command. */
        uint8_t                  status;     /*!< Status of the ViewGroup command. */
        uint16_t                 group_id;   /*!< Group ID from the ViewGroup command. */
        char                    *group_name; /*!< Group name (optional; not supported by the stack). */
    } in;                                    /*!< Input: parsed fields from the response. */
    struct {
        ezb_zcl_status_t result; /*!< Application processing result to return to the stack. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_groups_view_group_rsp_message_t;

/**
 * @brief Message for the ZCL Groups GetGroupMemberShipResponse.
 */
typedef struct ezb_zcl_groups_get_group_membership_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;      /*!< Header of the received ZCL command. */
        uint8_t                  capacity;    /*!< Remaining capacity of the device group table. */
        uint8_t                  group_count; /*!< Number of groups in group_list. */
        uint16_t                *group_list;  /*!< Identifiers of all groups in the group table (or the requested subset). */
    } in;                                     /*!< Input: parsed fields from the response. */
    struct {
        ezb_zcl_status_t result; /*!< Application processing result to return to the stack. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_groups_get_group_membership_rsp_message_t;

/**
 * @brief Message for the ZCL Groups RemoveGroupResponse.
 *
 */
typedef struct ezb_zcl_groups_remove_group_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;   /*!< Header of the received ZCL command. */
        uint8_t                  status;   /*!< Status of the RemoveGroup command. */
        uint16_t                 group_id; /*!< Group ID from the RemoveGroup command. */
    } in;                                  /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Application processing result to return to the stack. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_groups_remove_group_rsp_message_t;

/**
 * @brief Send ZCL Groups AddGroup command request.
 *
 * The AddGroup command allows the sending device to add group membership in a particular group for one or more endpoints on
 * the receiving device.
 *
 * @param cmd_req A pointer to the AddGroup command request structure, @ref ezb_zcl_groups_add_group_cmd_s.
 * @return Error code
 */
ezb_err_t ezb_zcl_groups_add_group_cmd_req(const ezb_zcl_groups_add_group_cmd_t *cmd_req);

/**
 * @brief Send ZCL Groups ViewGroup command request.
 *
 * The ViewGroup command allows the sending device to request that the receiving entity or entities respond with a view group
 * response command containing the application name string for a particular group.
 *
 * @param cmd_req A pointer to the ViewGroup command request structure, @ref ezb_zcl_groups_view_group_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_groups_view_group_cmd_req(const ezb_zcl_groups_view_group_cmd_t *cmd_req);

/**
 * @brief Send ZCL Groups GetGroupMembership command request.
 *
 * Inquires about the group membership of the receiving device/endpoint; response includes
 * capacity and list of group IDs.
 *
 * @param cmd_req A pointer to the GetGroupMembership command request structure, @ref ezb_zcl_groups_view_group_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_groups_get_group_membership_cmd_req(const ezb_zcl_groups_get_group_membership_cmd_t *cmd_req);

/**
 * @brief Send ZCL Groups RemoveGroup command request.
 *
 * The remove group command allows the sender to request that the receiving entity or entities remove their membership, if any,
 * in a particular group.
 *
 * @param cmd_req A pointer to the RemoveGroup command request structure, @ref ezb_zcl_groups_remove_group_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_groups_remove_cmd_req(const ezb_zcl_groups_remove_group_cmd_t *cmd_req);

/**
 * @brief Send ZCL Groups RemoveAllGroups command request.
 *
 * The remove all groups command allows the sending device to direct the receiving entity or entities to remove all group
 * associations.
 *
 * @param cmd_req A pointer to the RemoveAllGroups command request structure, @ref ezb_zcl_groups_remove_all_groups_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_groups_remove_all_groups_cmd_req(const ezb_zcl_groups_remove_all_groups_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
