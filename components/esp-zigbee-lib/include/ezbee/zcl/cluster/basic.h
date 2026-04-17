/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/basic_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure for the ZCL Basic FactoryReset command request.
 */
typedef struct ezb_zcl_basic_factory_reset_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t cmd_ctrl; /*!< Control information for the ZCL command. */
} ezb_zcl_basic_factory_reset_cmd_t;

/**
 * @brief Message for the ZCL Basic ResetToFactoryDefaults message.
 */
typedef struct ezb_zcl_basic_reset_factory_default_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;             /*!< ZCL command header information.
                                                          See @ref ezb_zcl_cmd_hdr_s. */
    } in;                                             /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of the reset to factory default operation. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_basic_reset_factory_default_message_t;

/**
 * @brief Send ZCL Basic FactoryReset command request.
 *
 * @param cmd_req Pointer to the FactoryReset command structure, @ref ezb_zcl_basic_factory_reset_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_basic_factory_reset_cmd_req(const ezb_zcl_basic_factory_reset_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
