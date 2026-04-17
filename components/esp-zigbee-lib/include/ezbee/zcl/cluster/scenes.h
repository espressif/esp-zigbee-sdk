/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/scenes_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Global scene group ID
 */
#define EZB_ZCL_SCENE_GLOBAL_SCENE_GROUP_ID 0x0000U

/**
 * @brief Global scene ID
 */
#define EZB_ZCL_SCENE_GLOBAL_SCENE_ID 0x00U

/**
 * @brief The maximum length of the scene name
 * @note The Scene name is 0 to 16 characters
 */
#define EZB_ZCL_SCENE_NAME_MAX_LENGTH 0x10U

/**
 * @brief Structure for the ZCL Scenes extension field set format.
 */
typedef struct ezb_zcl_scenes_extension_field_s {
    struct ezb_zcl_scenes_extension_field_s *next;       /*!< Pointer to next scenes extension field. */
    uint16_t                                 cluster_id; /*!< Cluster ID. */
    uint8_t                                  length;     /*!< Length of scenes extension field. */
    uint8_t                                 *value;      /*!< Extension field attribute value list. */
} ezb_zcl_scenes_extension_field_t;

/**
 * @brief Structure for the ZCL Scenes AddScene command request.
 */
typedef struct ezb_zcl_scenes_add_scene_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint16_t                          group_id;                                      /*!< Group ID of the scene. */
        uint8_t                           scene_id;                                      /*!< Scene ID. */
        uint16_t                          transition_time;                               /*!< Transition time in 1/10s. */
        char                              scene_name[EZB_ZCL_SCENE_NAME_MAX_LENGTH + 1]; /*!< Name of the scene. */
        ezb_zcl_scenes_extension_field_t *extension_field;                               /*!< Scene extension fields. */
    } payload;                                                                           /*!< Payload of the command. */
} ezb_zcl_scenes_add_scene_cmd_t;

/**
 * @brief Structure for the ZCL Scenes ViewScene command request.
 */
typedef struct ezb_zcl_scenes_view_scene_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint16_t group_id; /*!< Group ID of the scene. */
        uint8_t  scene_id; /*!< Scene ID. */
    } payload;             /*!< Payload of the command. */
} ezb_zcl_scenes_view_scene_cmd_t;

/**
 * @brief Structure for the ZCL Scenes RemoveScene command request.
 */
typedef struct ezb_zcl_scenes_remove_scene_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint16_t group_id; /*!< Group ID of the scene. */
        uint8_t  scene_id; /*!< Scene ID. */
    } payload;             /*!< Payload of the command. */
} ezb_zcl_scenes_remove_scene_cmd_t;

/**
 * @brief Structure for the ZCL Scenes RemoveAllScenes command request.
 */
typedef struct ezb_zcl_scenes_remove_all_scenes_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint16_t group_id; /*!< Group ID of the scene. */
    } payload;             /*!< Payload of the command. */
} ezb_zcl_scenes_remove_all_scenes_cmd_t;

/**
 * @brief Structure for the ZCL Scenes StoreScene command request.
 */
typedef struct ezb_zcl_scenes_store_scene_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint16_t group_id; /*!< Group ID of the scene. */
        uint8_t  scene_id; /*!< Scene ID. */
    } payload;             /*!< Payload of the command. */
} ezb_zcl_scenes_store_scene_cmd_t;

/**
 * @brief Structure for the ZCL Scenes RecallScene command request.
 */
typedef struct ezb_zcl_scenes_recall_scene_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint16_t group_id;        /*!< Group ID of the scene. */
        uint8_t  scene_id;        /*!< Scene ID. */
        uint16_t transition_time; /*!< Transition time in 1/10s. */
    } payload;                    /*!< Payload of the command. */
} ezb_zcl_scenes_recall_scene_cmd_t;

/**
 * @brief Structure for the ZCL Scenes GetSceneMembership command request.
 */
typedef struct ezb_zcl_scenes_get_scene_membership_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint16_t group_id; /*!< Group ID of the scene. */
    } payload;             /*!< Payload of the command. */
} ezb_zcl_scenes_get_scene_membership_cmd_t;

/**
 * @brief Structure for the ZCL Scenes CopyScene command request.
 */
typedef struct ezb_zcl_scenes_copy_scene_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
    struct {
        uint8_t  mode;          /*!< Copy mode. */
        uint16_t group_id_from; /*!< Group ID of the source scene. */
        uint8_t  scene_id_from; /*!< Scene ID of the source scene. */
        uint16_t group_id_to;   /*!< Group ID of the destination scene. */
        uint8_t  scene_id_to;   /*!< Scene ID of the destination scene. */
    } payload;                  /*!< Payload of the command. */
} ezb_zcl_scenes_copy_scene_cmd_t;

/**
 * @brief Message for the ZCL Scenes StoreScene request.
 */
typedef struct ezb_zcl_scenes_store_scene_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        uint16_t group_id; /*!< Group ID of the stored scene. */
        uint8_t  scene_id; /*!< Scene ID of the stored scene. */
    } in;                  /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_scenes_store_scene_message_t;

/**
 * @brief Message for the ZCL Scenes RecallScene request.
 */
typedef struct ezb_zcl_scenes_recall_scene_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        uint16_t                          group_id;        /*!< Group ID of the recalled scene. */
        uint8_t                           scene_id;        /*!< ID of the recalled scene. */
        uint16_t                          transition_time; /*!< Transition time for the scene recall. */
        ezb_zcl_scenes_extension_field_t *field_set;       /*!< Extension fields associated with the scene. */
    } in;                                                  /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_scenes_recall_scene_message_t;

/**
 * @brief Message for the ZCL Scenes OperateScene response.
 */
typedef struct ezb_zcl_scenes_operate_scene_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header; /*!< ZCL command header information.
                                              See @ref ezb_zcl_cmd_hdr_s. */
        uint8_t                  status;   /*!< Status of response. */
        uint16_t                 group_id; /*!< Group ID from the response. */
        uint8_t                  scene_id; /*!< Scene ID from the response. */
    } in;                                  /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_scenes_operate_scene_rsp_message_t;

/**
 * @brief Message for the ZCL Scenes ViewScene response.
 */
typedef struct ezb_zcl_scenes_view_scene_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t          *header;          /*!< ZCL command header information.
                                                                   See @ref ezb_zcl_cmd_hdr_s. */
        uint8_t                           status;          /*!< Status of response. */
        uint16_t                          group_id;        /*!< Group ID from the response. */
        uint8_t                           scene_id;        /*!< Scene ID from the response. */
        uint16_t                          transition_time; /*!< Transition time from the response. */
        ezb_zcl_scenes_extension_field_t *field_set;       /*!< Extension fields from the response. */
    } in;                                                  /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_scenes_view_scene_rsp_message_t;

/**
 * @brief Message for the ZCL Scenes GetSceneMembership response.
 */
typedef struct ezb_zcl_scenes_get_scene_membership_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;      /*!< ZCL command header information.
                                                  See @ref ezb_zcl_cmd_hdr_s. */
        uint8_t                  status;      /*!< Status of response. */
        uint8_t                  capacity;    /*!< Capacity of the scene table. */
        uint16_t                 group_id;    /*!< Group ID from the response. */
        uint8_t                  scene_count; /*!< Number of scenes in the group. */
        uint8_t                 *scene_list;  /*!< List of scene IDs in the group. */
    } in;                                     /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_scenes_get_scene_membership_rsp_message_t;

/**
 * @brief Send ZCL Scenes AddScene command request.
 *
 * @param cmd_req Pointer to the AddScene command request structure, @ref ezb_zcl_scenes_add_scene_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_scenes_add_scene_cmd_req(const ezb_zcl_scenes_add_scene_cmd_t *cmd_req);

/**
 * @brief Send ZCL Scenes ViewScene command request.
 *
 * @param cmd_req Pointer to the ViewScene command request structure, @ref ezb_zcl_scenes_view_scene_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_scenes_view_scene_cmd_req(const ezb_zcl_scenes_view_scene_cmd_t *cmd_req);

/**
 * @brief Send ZCL Scenes RemoveScene command request.
 *
 * @param cmd_req Pointer to the RemoveScene command request structure, @ref ezb_zcl_scenes_remove_scene_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_scenes_remove_scene_cmd_req(const ezb_zcl_scenes_remove_scene_cmd_t *cmd_req);

/**
 * @brief Send ZCL Scenes RemoveAllScenes command request.
 *
 * @param cmd_req Pointer to the RemoveAllScenes command request structure, @ref ezb_zcl_scenes_remove_all_scenes_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_scenes_remove_all_scenes_cmd_req(const ezb_zcl_scenes_remove_all_scenes_cmd_t *cmd_req);

/**
 * @brief Send ZCL Scenes StoreScene command request.
 *
 * @param cmd_req Pointer to the StoreScene command request structure, @ref ezb_zcl_scenes_store_scene_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_scenes_store_scene_cmd_req(const ezb_zcl_scenes_store_scene_cmd_t *cmd_req);

/**
 * @brief Send ZCL Scenes RecallScene command request.
 *
 * @param cmd_req Pointer to the RecallScene command request structure, @ref ezb_zcl_scenes_recall_scene_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_scenes_recall_scene_cmd_req(const ezb_zcl_scenes_recall_scene_cmd_t *cmd_req);

/**
 * @brief Send ZCL Scenes GetSceneMembership command request.
 *
 * @param cmd_req Pointer to the GetSceneMembership command request structure, @ref ezb_zcl_scenes_get_scene_membership_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_scenes_get_scene_membership_cmd_req(const ezb_zcl_scenes_get_scene_membership_cmd_t *cmd_req);

/**
 * @brief Send ZCL Scenes CopyScene command request.
 *
 * @param cmd_req Pointer to the CopyScene command request structure, @ref ezb_zcl_scenes_copy_scene_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_scenes_copy_scene_cmd_req(const ezb_zcl_scenes_copy_scene_cmd_t *cmd_req);

/**
 * @brief Store the scene to Scenes Table
 *
 * The Scenes Table is persistent storage of the scenes.
 *
 * @param ep_id Endpoint ID that the Scene Table is located.
 * @param group_id Group ID of the scene.
 * @param scene_id Scene ID of the scene.
 * @param transition_time Transition time of the scene.
 * @param field Extension field of the scene to be stored.
 * @return Error code.
 */
ezb_err_t ezb_zcl_scenes_table_store(uint8_t                           ep_id,
                                     uint16_t                          group_id,
                                     uint8_t                           scene_id,
                                     uint16_t                          transition_time,
                                     ezb_zcl_scenes_extension_field_t *field);

#ifdef __cplusplus
} /* extern "C" */
#endif
