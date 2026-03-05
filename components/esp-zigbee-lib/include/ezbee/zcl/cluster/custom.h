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
 * @brief Callback for initializing the custom cluster.
 *
 * @param ep_id Endpoint identifier that the custom cluster is being initialized.
 */
typedef void (*ezb_zcl_custom_cluster_init_t)(uint8_t ep_id);

/**
 * @brief Callback for de-initializing the custom cluster.
 *
 * @param ep_id Endpoint identifier that the custom cluster is being de-initialized.
 */
typedef void (*ezb_zcl_custom_cluster_deinit_t)(uint8_t ep_id);

/**
 * @brief Callback for checking the attribute value of the custom cluster is correct.
 *
 * @param attr_id Attribute identifier that is being checked.
 * @param ep_id   Endpoint identifier that the custom cluster is being checked.
 * @param value   Pointer to the attribute value that is being checked.
 * @return Status code.
 */
typedef ezb_zcl_status_t (*ezb_zcl_custom_cluster_check_value_t)(uint16_t attr_id, uint8_t ep_id, void *value);

/**
 * @brief Callback for post-processing of the attribute of the custom cluster had been written.
 *
 * @param ep_id      Endpoint identifier that the custom cluster is being written to.
 * @param attr_id    Attribute identifier that is being written.
 * @param new_value  Pointer to the new attribute value that is being written.
 * @param manuf_code Manufacturer code.
 */
typedef void (*ezb_zcl_custom_cluster_write_attr_t)(uint8_t ep_id, uint16_t attr_id, void *new_value, uint16_t manuf_code);

/**
 * @brief Callback for discovering the supported commands of the custom cluster.
 *
 * @param[in]  is_recv Indicate that the supported commands are received or sent.
 * @param[out] list    Pointer to the list of supported commands.
 * @return Number of supported commands.
 */
typedef uint8_t (*ezb_zcl_custom_cluster_disc_cmd_t)(bool is_recv, uint8_t **list);

/**
 * @brief Callback for processing the custom cluster command.
 *
 * @param header Pointer to the command header, see @ref ezb_zcl_cmd_hdr_s.
 * @param payload Pointer to the command payload.
 * @param payload_length Length of the command payload.
 * @return Error code.
 */
typedef ezb_zcl_status_t (*ezb_zcl_custom_cluster_process_cmd_t)(const ezb_zcl_cmd_hdr_t *header,
                                                                 const uint8_t           *payload,
                                                                 uint16_t                 payload_length);

/**
 * @brief Structure describing a ZCL cluster handler template.
 */
typedef struct ezb_zcl_custom_cluster_handlers_s {
    uint16_t cluster_id;   /*!< Cluster identifier */
    uint8_t  cluster_role; /*!< Cluster role (server/client) */

    /** Callback for checking the attribute value of the custom cluster is correct. */
    ezb_zcl_custom_cluster_check_value_t check_value_cb;
    /** Callback for post-processing of the attribute of the custom cluster had been written. */
    ezb_zcl_custom_cluster_write_attr_t write_attr_cb;
    /** Callback for discovering the supported commands of the custom cluster. */
    ezb_zcl_custom_cluster_disc_cmd_t cmd_disc_cb;
    /** Callback for processing the custom cluster command. */
    ezb_zcl_custom_cluster_process_cmd_t process_cmd_cb;
} ezb_zcl_custom_cluster_handlers_t;

/**
 * @brief Custom command control type (alias of @ref ezb_zcl_cmd_ctrl_s).
 */
typedef ezb_zcl_cmd_ctrl_t ezb_zcl_custom_cmd_ctrl_t;

/**
 * @brief Structure for the ZCL Custom command request.
 *
 * The cluster_id in cmd_ctrl SHALL be greater than EZB_ZCL_CLUSTER_ID_MIN_CUSTOM.
 */
typedef struct ezb_zcl_custom_cmd_s {
    ezb_zcl_custom_cmd_ctrl_t cmd_ctrl;    /*!< Control information for the ZCL command. */
    uint8_t                   cmd_id;      /*!< Custom command identifier. */
    uint16_t                  data_length; /*!< Length of data for custom command. */
    uint8_t                  *data;        /*!< Data of custom command. */
} ezb_zcl_custom_cmd_t;

/**
 * @brief Structure for the ZCL Custom cluster command request.
 * @anchor ezb_zcl_custom_cluster_cmd_t
 */
typedef ezb_zcl_custom_cmd_t ezb_zcl_custom_cluster_cmd_t;

/**
 * @brief Structure for the ZCL Custom cluster configuration.
 */
typedef struct ezb_zcl_custom_cluster_config_s {
    uint16_t cluster_id; /*!< Custom cluster identifier (SHALL be greater than EZB_ZCL_CLUSTER_ID_MIN_CUSTOM). */
    ezb_zcl_custom_cluster_init_t   init_func;   /*!< Function for initializing the custom cluster. */
    ezb_zcl_custom_cluster_deinit_t deinit_func; /*!< Function for de-initializing the custom cluster. */
} ezb_zcl_custom_cluster_config_t;

/**
 * @brief Add a manufacturer-specific attribute to a custom cluster descriptor.
 *
 * @param cluster_desc Pointer to the custom cluster descriptor, @ref ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param attr_type    Attribute type.
 * @param attr_access  Attribute access.
 * @param manuf_code   Manufacturer code for the attribute.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_custom_cluster_desc_add_manuf_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                                     uint16_t               attr_id,
                                                     uint8_t                attr_type,
                                                     uint8_t                attr_access,
                                                     uint16_t               manuf_code,
                                                     const void            *value);

/**
 * @brief Add an attribute to a custom cluster descriptor.
 *
 * @param cluster_desc Pointer to the custom cluster descriptor, @ref ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param attr_type    Attribute type.
 * @param attr_access  Attribute access.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_custom_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc,
                                               uint16_t               attr_id,
                                               uint8_t                attr_type,
                                               uint8_t                attr_access,
                                               const void            *value);
/**
 * @brief Create a custom cluster descriptor.
 *
 * @param cluster_cfg Pointer to the custom cluster configuration structure, @ref ezb_zcl_custom_cluster_config_s.
 * @param role_mask   Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_custom_create_cluster_desc(const ezb_zcl_custom_cluster_config_t *cluster_cfg, uint8_t role_mask);

/**
 * @brief Send ZCL custom command request.
 *
 * @param cmd_req Pointer to the custom command request structure, @ref ezb_zcl_custom_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_custom_cmd_req(const ezb_zcl_custom_cmd_t *cmd_req);

/**
 * @brief Send ZCL custom cluster command request.
 *
 * @note This function is used to send a custom command request from a client/server to a server/client of a custom cluster.
 *       If the request is sent to a client, the custom cluster server must be present on the source endpoint, and vice versa.
 *
 * @param cmd_req Pointer to the custom command request structure, @ref ezb_zcl_custom_cluster_cmd_t.
 * @return Error code.
 */
ezb_err_t ezb_zcl_custom_cluster_cmd_req(const ezb_zcl_custom_cluster_cmd_t *cmd_req);

/**
 * @brief Register custom cluster handlers.
 *
 * @param handlers Pointer to the custom cluster handlers structure, @ref ezb_zcl_custom_cluster_handlers_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_custom_cluster_handlers_register(const ezb_zcl_custom_cluster_handlers_t *handlers);

#ifdef __cplusplus
} /* extern "C" */
#endif
