/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file zdo_bind_mgmt.h
 * @brief Zigbee Device Object (ZDO) Binding Management API
 *
 * This header file provides APIs for managing bindings in a Zigbee network.
 * Bindings establish relationships between source and destination devices,
 * allowing automatic message routing based on cluster IDs and endpoints.
 *
 * The binding management includes:
 * - Creating bindings between devices (Bind_req)
 * - Removing bindings between devices (Unbind_req)
 *
 * All requests use a unified structure that includes the destination address,
 * request fields, callback function, and user context.
 */

#pragma once

#include <ezbee/core_types.h>

#include <ezbee/zdo/zdo_type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Fields of the ZDP Bind_req Command
 */
typedef struct ezb_zdp_bind_req_field_s {
    ezb_extaddr_t src_addr;      /*!< The IEEE address for the source*/
    uint8_t       src_ep;        /*!< The source endpoint for the binding entry */
    uint16_t      cluster_id;    /*!< The identifier of the cluster on the source device that is bound to the destination. */
    uint8_t       dst_addr_mode; /*!< The addressing mode for the destination address used in this command.
                                      Valid values:
                                      - 0x00 = reserved
                                      - 0x01 = 16-bit group address (DstAddress and DstEndp not present)
                                      - 0x02 = reserved
                                      - 0x03 = 64-bit extended address (DstAddress and DstEndp present)
                                      - 0x04 - 0xff = reserved */
    ezb_addr_t dst_addr; /*!< The address of the destination device. The format of this field is determined by the value of
                            DstAddrMode. */
    uint8_t dst_ep;      /*!< The endpoint of the destination device. This field is present only if DstAddrMode is 0x03. */
} ezb_zdp_bind_req_field_t;

/**
 * @brief Structure for ZDP Bind Response
 */
typedef struct ezb_zdp_bind_rsp_field_s {
    uint8_t status; /*!< Status of the bind operation, see @ref ezb_zdp_status_t */
} ezb_zdp_bind_rsp_field_t;

/**
 * @brief Structure for ZDP Bind Request Result
 */
typedef struct ezb_zdp_bind_req_result_s {
    ezb_err_t                 error; /*!< Error code of the bind request operation */
    ezb_zdp_bind_rsp_field_t *rsp;   /*!< Pointer to the bind response field, NULL if error occurred */
} ezb_zdp_bind_req_result_t;

/**
 * @brief A callback to handle the result of ZDO Bind Request
 */
typedef void (*ezb_zdo_bind_req_callback_t)(const ezb_zdp_bind_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO Bind Request
 *
 * This structure contains all parameters needed to send a bind request to a remote device.
 */
typedef struct ezb_zdo_bind_req_s {
    ezb_shortaddr_t             dst_nwk_addr; /*!< Network address of the destination device to receive the bind request */
    ezb_zdp_bind_req_field_t    field;        /*!< Fields of the bind request command */
    ezb_zdo_bind_req_callback_t cb;           /*!< User callback for result of ZDO Bind Request */
    void                       *user_ctx;     /*!< User argument of request will be passed to user callback */
} ezb_zdo_bind_req_t;

/**
 * @brief Structure for ZDO Unbind Request
 *
 * The unbind request uses the same structure as the bind request since they share the same parameters.
 */
typedef ezb_zdo_bind_req_t ezb_zdo_unbind_req_t;

/**
 * @brief Fields of the ZDP Unbind Request Command
 *
 * The unbind request uses the same fields as the bind request.
 */
typedef ezb_zdp_bind_req_field_t ezb_zdp_unbind_req_field_t;

/**
 * @brief Structure for ZDP Unbind Response
 *
 * The unbind response uses the same structure as the bind response.
 */
typedef ezb_zdp_bind_rsp_field_t ezb_zdp_unbind_rsp_field_t;

/**
 * @brief Structure for ZDP Unbind Request Result
 *
 * The unbind request result uses the same structure as the bind request result.
 */
typedef ezb_zdp_bind_req_result_t ezb_zdp_unbind_req_result_t;

/**
 * @brief Send a ZDO Bind Request Command
 *
 * The Bind_req command is generated from a local device wishing to create a binding entry
 * in the binding table of a remote device. A binding establishes a relationship between
 * a source device/endpoint/cluster and a destination device/endpoint.
 *
 * @param[in] req Pointer to the bind request structure containing destination address,
 *                request fields, callback function, and user context, see @ref ezb_zdo_bind_req_t
 *
 * @return
 *      - EZB_ERR_NONE: Request sent successfully
 *      - Other error codes: see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_bind_req(const ezb_zdo_bind_req_t *req);

/**
 * @brief Send a ZDO Unbind Request Command
 *
 * The Unbind_req command is generated from a local device wishing to remove a binding entry
 * from the binding table of a remote device.
 *
 * @param[in] req Pointer to the unbind request structure containing destination address,
 *                request fields, callback function, and user context, see @ref ezb_zdo_unbind_req_t
 *
 * @return
 *      - EZB_ERR_NONE: Request sent successfully
 *      - Other error codes: see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_unbind_req(const ezb_zdo_unbind_req_t *req);

#ifdef __cplusplus
} /*  extern "C" */
#endif
