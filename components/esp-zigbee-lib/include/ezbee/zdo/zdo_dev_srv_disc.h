/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file zdo_dev_srv_disc.h
 * @brief Zigbee Device Object (ZDO) Device and Service Discovery API
 *
 * This header file provides APIs for device and service discovery operations in a Zigbee network.
 * Device discovery allows devices to find and learn about other devices in the network, including
 * their addresses, capabilities, and services.
 *
 * The device and service discovery includes:
 * - Network address requests (NWK_addr_req) to find 16-bit network address from IEEE address
 * - IEEE address requests (IEEE_addr_req) to find 64-bit IEEE address from network address
 * - Node descriptor requests to get device capabilities
 * - Simple descriptor requests to get endpoint information
 * - Active endpoints requests to list all active endpoints
 * - Power descriptor requests to get power characteristics
 * - Match descriptor requests to find devices supporting specific clusters
 * - Device announcement to announce device presence
 *
 * All requests use a unified structure that includes the destination address,
 * request fields, callback function, and user context.
 */

#pragma once

#include <ezbee/core_types.h>

#include <ezbee/af.h>

#include <ezbee/zdo/zdo_type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration for specifying the request type of address request
 */
enum ezb_zdo_addr_request_type_e {
    ZDO_ADDR_REQUEST_TYPE_SINGLE_DEVICE   = 0x00, /*!< Request for the single device */
    ZDO_ADDR_REQUEST_TYPE_EXTENDED_DEVICE = 0x01, /*!< Request for the extended response */
    ZDO_ADDR_REQUEST_TYPE_RESERVED        = 0x02, /*!< Reserved */
};

/**
 * @brief Represents the request type of zdo address request
 */
typedef uint8_t ezb_zdo_addr_request_type_t;

/**
 * @brief Fields of the ZDP Network Address Request Command
 */
typedef struct ezb_zdp_nwk_addr_req_field_s {
    ezb_extaddr_t ieee_addr_of_interest; /*!< IEEE (64-bit) address of the device to find */
    uint8_t       request_type;          /*!< Request type for this command:
                                              - 0x00 = Single device response (no associated devices list)
                                              - 0x01 = Extended response (includes associated devices list) */
    uint8_t start_index; /*!< Starting index for the associated devices list (only used if request_type is 0x01) */
} ezb_zdp_nwk_addr_req_field_t;

/**
 * @brief Structure for ZDP Address Response
 *
 * This structure is used for both NWK_addr and IEEE_addr responses.
 */
typedef struct ezb_zdp_addr_rsp_field_s {
    uint8_t          status;                  /*!< Status of the address request, see @ref ezb_zdp_status_t */
    ezb_extaddr_t    ieee_addr_remote_dev;    /*!< IEEE (64-bit) address of the remote device */
    ezb_shortaddr_t  nwk_addr_remote_dev;     /*!< Network (16-bit) address of the remote device */
    uint8_t          num_assoc_dev;           /*!< Total number of associated devices (children) of the remote device */
    uint8_t          start_index;             /*!< Starting index of the associated devices list in this response */
    ezb_shortaddr_t *nwk_addr_assoc_dev_list; /*!< Pointer to array of network addresses of associated devices */
} ezb_zdp_address_rsp_field_t;

/**
 * @brief Structure for ZDO Address Request Result
 */
typedef struct ezb_zdo_addr_req_result_s {
    ezb_err_t                    error; /*!< Error code of the address request operation */
    ezb_zdp_address_rsp_field_t *rsp;   /*!< Pointer to the address response field, NULL if error occurred */
} ezb_zdo_addr_req_result_t;

/** @brief Structure for ZDP nwk_addr response */
typedef ezb_zdp_address_rsp_field_t ezb_zdp_nwk_addr_rsp_field_t;

/** @brief Structure for ZDP ieee_addr response */
typedef ezb_zdp_address_rsp_field_t ezb_zdp_ieee_addr_rsp_field_t;

/** @brief Structure for ZDO Network Address Request Result */
typedef ezb_zdo_addr_req_result_t ezb_zdo_nwk_addr_req_result_t;

/** @brief Structure for ZDO IEEE Address Request Result */
typedef ezb_zdo_addr_req_result_t ezb_zdo_ieee_addr_req_result_t;

/**
 * @brief A callback to handle the result of ZDO Network Address Request
 */
typedef void (*ezb_zdo_nwk_addr_req_callback_t)(const ezb_zdo_nwk_addr_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO Network Address Request
 *
 * This structure contains all parameters needed to send a network address request to find
 * the 16-bit network address corresponding to a known IEEE address.
 */
typedef struct ezb_zdo_nwk_addr_req_s {
    ezb_shortaddr_t                 dst_nwk_addr; /*!< Network address of the destination device to receive the request */
    ezb_zdp_nwk_addr_req_field_t    field;        /*!< Fields of the network address request command */
    ezb_zdo_nwk_addr_req_callback_t cb;           /*!< User callback for result of ZDO Network Address Request */
    void                           *user_ctx;     /*!< User argument of request will be passed to user callback */
} ezb_zdo_nwk_addr_req_t;

/**
 * @brief Fields of the ZDP IEEE Address Request Command
 */
typedef struct ezb_zdp_ieee_addr_req_field_s {
    ezb_shortaddr_t nwk_addr_of_interest; /*!< Network (16-bit) address of the device to find */
    uint8_t         request_type;         /*!< Request type for this command:
                                           *   - 0x00 = Single device response (no associated devices list)
                                           *   - 0x01 = Extended response (includes associated devices list) */
    uint8_t start_index; /*!< Starting index for the associated devices list (only used if request_type is 0x01) */
} ezb_zdp_ieee_addr_req_field_t;

/**
 * @brief A callback to handle the result of ZDO IEEE Address Request
 */
typedef void (*ezb_zdo_ieee_addr_req_callback_t)(const ezb_zdo_ieee_addr_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO IEEE Address Request
 *
 * This structure contains all parameters needed to send an IEEE address request to find
 * the 64-bit IEEE address corresponding to a known network address.
 */
typedef struct ezb_zdo_ieee_addr_req_s {
    ezb_shortaddr_t                  dst_nwk_addr; /*!< Network address of the destination device to receive the request */
    ezb_zdp_ieee_addr_req_field_t    field;        /*!< Fields of the IEEE address request command */
    ezb_zdo_ieee_addr_req_callback_t cb;           /*!< User callback for result of ZDO IEEE Address Request */
    void                            *user_ctx;     /*!< User argument of request will be passed to user callback */
} ezb_zdo_ieee_addr_req_t;

/**
 * @brief Structure for ZDP Simple Descriptor Response
 */
typedef struct ezb_zdp_simple_desc_rsp_field_s {
    uint8_t              status;               /*!< Status of the simple descriptor request, see @ref ezb_zdp_status_t */
    ezb_shortaddr_t      nwk_addr_of_interest; /*!< Network address of the device that was queried */
    uint8_t              length;               /*!< Length of the simple descriptor in bytes */
    ezb_af_simple_desc_t desc;                 /*!< Simple descriptor containing endpoint information */
} ezb_zdp_simple_desc_rsp_field_t;

/**
 * @brief Structure for ZDO Simple Descriptor Request Result
 */
typedef struct ezb_zdo_simple_desc_req_result_s {
    ezb_err_t                        error; /*!< Error code of the simple descriptor request operation */
    ezb_zdp_simple_desc_rsp_field_t *rsp;   /*!< Pointer to the simple descriptor response field, NULL if error occurred */
} ezb_zdo_simple_desc_req_result_t;

/**
 * @brief Fields of the ZDP Simple Descriptor Request Command
 */
typedef struct ezb_zdp_simple_desc_req_field_s {
    ezb_shortaddr_t nwk_addr_of_interest; /*!< Network address of the device to query */
    uint8_t         endpoint;             /*!< Endpoint number on the destination device (1-240) */
} ezb_zdp_simple_desc_req_field_t;

/**
 * @brief A callback to handle the result of ZDO Simple Descriptor Request
 */
typedef void (*ezb_zdo_simple_desc_req_callback_t)(const ezb_zdo_simple_desc_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO Simple Descriptor Request
 *
 * This structure contains all parameters needed to send a simple descriptor request to get
 * information about a specific endpoint on a remote device.
 */
typedef struct ezb_zdo_simple_desc_req_s {
    ezb_shortaddr_t                    dst_nwk_addr; /*!< Network address of the destination device to receive the request */
    ezb_zdp_simple_desc_req_field_t    field;        /*!< Fields of the simple descriptor request command */
    ezb_zdo_simple_desc_req_callback_t cb;           /*!< User callback for result of ZDO Simple Descriptor Request */
    void                              *user_ctx;     /*!< User argument of request will be passed to user callback */
} ezb_zdo_simple_desc_req_t;

/**
 * @brief Fields of the ZDP Match Descriptor Request Command
 */
typedef struct ezb_zdp_match_desc_req_field_s {
    ezb_shortaddr_t nwk_addr_of_interest; /*!< Network address of the device to query */
    uint16_t        profile_id;           /*!< Profile ID to match at the destination, see @ref ezb_af_profile_id_t */
    uint8_t         num_in_clusters;      /*!< Number of input clusters (server clusters) in the cluster_list */
    uint8_t         num_out_clusters;     /*!< Number of output clusters (client clusters) in the cluster_list */
    uint16_t       *cluster_list; /*!< Pointer to array of cluster IDs. First num_in_clusters entries are input clusters,
                                   *   followed by num_out_clusters entries for output clusters. Total size must be
                                   *   (num_in_clusters + num_out_clusters) * sizeof(uint16_t) */
} ezb_zdp_match_desc_req_field_t;

/**
 * @brief Structure for ZDP Match Descriptor Response
 */
typedef struct ezb_zdp_match_desc_rsp_field_s {
    ezb_zdp_status_t status;               /*!< Status of the match descriptor request, see @ref ezb_zdp_status_t */
    ezb_shortaddr_t  nwk_addr_of_interest; /*!< Network address of the device that was queried */
    uint8_t          match_length;         /*!< Number of endpoints on the remote device that match the request criteria */
    uint8_t         *match_list;           /*!< Pointer to array of endpoint numbers (uint8_t) that match the criteria */
} ezb_zdp_match_desc_rsp_field_t;

/**
 * @brief Structure for ZDO Match Descriptor Request Result
 */
typedef struct ezb_zdo_match_desc_req_result_s {
    ezb_err_t                       error; /*!< Error code of the match descriptor request operation */
    ezb_zdp_match_desc_rsp_field_t *rsp;   /*!< Pointer to the match descriptor response field, NULL if error occurred */
} ezb_zdo_match_desc_req_result_t;

/**
 * @brief A callback to handle the result of ZDO Match Descriptor Request
 */
typedef void (*ezb_zdo_match_desc_req_callback_t)(const ezb_zdo_match_desc_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO Match Descriptor Request
 *
 * This structure contains all parameters needed to send a match descriptor request to find
 * endpoints on a remote device that support specific clusters.
 */
typedef struct ezb_zdo_match_desc_req_s {
    ezb_shortaddr_t                   dst_nwk_addr; /*!< Network address of the destination device to receive the request */
    ezb_zdp_match_desc_req_field_t    field;        /*!< Fields of the match descriptor request command */
    ezb_zdo_match_desc_req_callback_t cb;           /*!< User callback for result of ZDO Match Descriptor Request,
                                                         If the request is broadcast, the callback may be invoked multiple
                                                         times to report different responses, with the NULL response indicating
                                                         completion. */
    void                             *user_ctx;     /*!< User argument of request will be passed to user callback */
} ezb_zdo_match_desc_req_t;

/**
 * @brief Fields of the ZDP Simple Request Command
 *
 * This is a base structure used for simple requests that only need a network address.
 */
typedef struct ezb_zdp_simple_req_field_s {
    ezb_shortaddr_t nwk_addr_of_interest; /*!< Network address of the device to query */
} ezb_zdp_simple_req_field_t;

/**
 * @brief Fields of the ZDP Active Endpoints Request Command
 *
 * The active endpoints request uses the same fields as the simple request.
 */
typedef ezb_zdp_simple_req_field_t ezb_zdp_active_ep_req_field_t;

/**
 * @brief Structure for ZDP Active Endpoints Response
 */
typedef struct ezb_zdp_active_ep_rsp_field_s {
    ezb_zdp_status_t status;               /*!< Status of the active endpoints request, see @ref ezb_zdp_status_t */
    ezb_shortaddr_t  nwk_addr_of_interest; /*!< Network address of the device that was queried */
    uint8_t          active_ep_count;      /*!< Number of active endpoints on the remote device */
    uint8_t         *active_ep_list;       /*!< Pointer to array of active endpoint numbers (uint8_t) */
} ezb_zdp_active_ep_rsp_field_t;

/**
 * @brief Structure for ZDO Active Endpoints Request Result
 */
typedef struct ezb_zdo_active_ep_req_result_s {
    ezb_err_t                      error; /*!< Error code of the active endpoints request operation */
    ezb_zdp_active_ep_rsp_field_t *rsp;   /*!< Pointer to the active endpoints response field, NULL if error occurred */
} ezb_zdo_active_ep_req_result_t;

/**
 * @brief A callback to handle the result of ZDO Active Endpoints Request
 */
typedef void (*ezb_zdo_active_ep_req_callback_t)(const ezb_zdo_active_ep_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO Active Endpoints Request
 *
 * This structure contains all parameters needed to send an active endpoints request to get
 * a list of all active endpoints on a remote device.
 */
typedef struct ezb_zdo_active_ep_req_s {
    ezb_shortaddr_t                  dst_nwk_addr; /*!< Network address of the destination device to receive the request */
    ezb_zdp_active_ep_req_field_t    field;        /*!< Fields of the active endpoints request command */
    ezb_zdo_active_ep_req_callback_t cb;           /*!< User callback for result of ZDO Active Endpoints Request */
    void                            *user_ctx;     /*!< User argument of request will be passed to user callback */
} ezb_zdo_active_ep_req_t;

/**
 * @brief Fields of the ZDP Power Descriptor Request Command
 *
 * The power descriptor request uses the same fields as the simple request.
 */
typedef ezb_zdp_simple_req_field_t ezb_zdp_power_desc_req_field_t;

/**
 * @brief Structure for ZDP Power Descriptor Response
 */
typedef struct ezb_zdp_power_desc_rsp_field_s {
    ezb_zdp_status_t         status;               /*!< Status of the power descriptor request, see @ref ezb_zdp_status_t */
    ezb_shortaddr_t          nwk_addr_of_interest; /*!< Network address of the device that was queried */
    ezb_af_node_power_desc_t power_desc; /*!< Power descriptor containing power characteristics of the remote device */
} ezb_zdp_power_desc_rsp_field_t;

/**
 * @brief Structure for ZDO Power Descriptor Request Result
 */
typedef struct ezb_zdo_power_desc_req_result_s {
    ezb_err_t                       error; /*!< Error code of the power descriptor request operation */
    ezb_zdp_power_desc_rsp_field_t *rsp;   /*!< Pointer to the power descriptor response field, NULL if error occurred */
} ezb_zdo_power_desc_req_result_t;

/**
 * @brief A callback to handle the result of ZDO Power Descriptor Request
 */
typedef void (*ezb_zdo_power_desc_req_callback_t)(const ezb_zdo_power_desc_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO Power Descriptor Request
 *
 * This structure contains all parameters needed to send a power descriptor request to get
 * power characteristics of a remote device.
 */
typedef struct ezb_zdo_power_desc_req_s {
    ezb_shortaddr_t                   dst_nwk_addr; /*!< Network address of the destination device to receive the request */
    ezb_zdp_power_desc_req_field_t    field;        /*!< Fields of the power descriptor request command */
    ezb_zdo_power_desc_req_callback_t cb;           /*!< User callback for result of ZDO Power Descriptor Request */
    void                             *user_ctx;     /*!< User argument of request will be passed to user callback */
} ezb_zdo_power_desc_req_t;

/**
 * @brief Structure for ZDO Device Announcement Request Result
 */
typedef struct ezb_zdo_device_annce_req_result_s {
    ezb_err_t error; /*!< Error code of the device announcement request operation */
} ezb_zdo_device_annce_req_result_t;

/**
 * @brief A callback to handle the result of ZDO Device Announcement Request
 */
typedef void (*ezb_zdo_device_annce_req_callback_t)(const ezb_zdo_device_annce_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO Device Announcement Request
 */
typedef struct ezb_zdo_device_annce_req_s {
    ezb_zdo_device_annce_req_callback_t cb;       /*!< User callback for result of ZDO Device Announcement Request */
    void                               *user_ctx; /*!< User argument of request will be passed to user callback */
} ezb_zdo_device_annce_req_t;

/**
 * @brief Field for ZDP Parent Announcement Response
 */
typedef struct ezb_zdp_device_annce_rsp_field_s {
    uint8_t        status;          /*!< The status of the Parent_annce command. */
    uint8_t        num_of_children; /*!< The number of ChildInfo structures contained in the message. */
    ezb_extaddr_t *child_info;      /*!< Extended address for child */
} ezb_zdp_device_annce_rsp_field_t;

/**
 * @brief Structure for ZDP Parent Announcement Request Result
 */
typedef struct ezb_zdo_parent_annce_req_result_s {
    ezb_err_t                         error; /*!< Error code of the power descriptor request operation */
    ezb_zdp_device_annce_rsp_field_t *rsp;   /*!< Pointer to the power descriptor response field, NULL if error occurred */
} ezb_zdo_parent_annce_req_result_t;

/**
 * @brief A callback to handle the result of ZDO Parent Announcement Request
 */
typedef void (*ezb_zdo_parent_annce_req_callback_t)(const ezb_zdo_parent_annce_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO Parent Announcement Request
 */
typedef struct ezb_zdo_parent_annce_req_s {
    ezb_shortaddr_t                     dst_nwk_addr; /*!< NWK address that request sent to */
    ezb_zdo_parent_annce_req_callback_t cb;           /*!< User callback for result of ZDO Parent Announcement Request，
                                                           If the request is broadcast, the callback may be invoked multiple
                                                           times to report different responses, with the NULL response indicating
                                                           completion. */
    void                               *user_ctx;     /*!< User argument of request will be passed to user callback */
} ezb_zdo_parent_annce_req_t;

/**
 * @brief Fields of the ZDP Node Descriptor Request Command
 *
 * The node descriptor request uses the same fields as the simple request.
 */
typedef ezb_zdp_simple_req_field_t ezb_zdp_node_desc_req_field_t;

/**
 * @brief Structure for ZDP Node Descriptor Response
 */
typedef struct ezb_zdp_node_desc_rsp_field_s {
    ezb_zdp_status_t   status;               /*!< Status of the node descriptor request, see @ref ezb_zdp_status_t */
    ezb_shortaddr_t    nwk_addr_of_interest; /*!< Network address of the device that was queried */
    ezb_af_node_desc_t node_desc;            /*!< Node descriptor containing device capabilities and characteristics */
    /** TODO: add TLVs */
} ezb_zdp_node_desc_rsp_field_t;

/**
 * @brief Structure for ZDO Node Descriptor Request Result
 */
typedef struct ezb_zdo_node_desc_req_result_s {
    ezb_err_t                      error; /*!< Error code of the node descriptor request operation */
    ezb_zdp_node_desc_rsp_field_t *rsp;   /*!< Pointer to the node descriptor response field, NULL if error occurred */
} ezb_zdo_node_desc_req_result_t;

/**
 * @brief A callback to handle the result of ZDO Node Descriptor Request
 */
typedef void (*ezb_zdo_node_desc_req_callback_t)(const ezb_zdo_node_desc_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO Node Descriptor Request
 *
 * This structure contains all parameters needed to send a node descriptor request to get
 * device capabilities and characteristics of a remote device.
 */
typedef struct ezb_zdo_node_desc_req_s {
    ezb_shortaddr_t                  dst_nwk_addr; /*!< Network address of the destination device to receive the request */
    ezb_zdp_node_desc_req_field_t    field;        /*!< Fields of the node descriptor request command */
    ezb_zdo_node_desc_req_callback_t cb;           /*!< User callback for result of ZDO Node Descriptor Request */
    void                            *user_ctx;     /*!< User argument of request will be passed to user callback */
} ezb_zdo_node_desc_req_t;

/**
 * @brief Send a ZDO NWK_addr_req command.
 *
 * The NWK_addr_req is generated from a Local Device wishing to inquire as to the 16-bit address of the Remote Device based on
 * its known IEEE address.
 * @param[in] req A structure used to configure the fields of the NWK_addr_req command, see @ref ezb_zdo_nwk_addr_req_t
 *
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_nwk_addr_req(const ezb_zdo_nwk_addr_req_t *req);

/**
 * @brief Send a ZDO IEEE_addr_req command.
 *
 * The IEEE_addr_req is generated from a Local Device wishing to inquire as to the 64-bit IEEE address of the Remote
 * Device based on their known 16-bit address.
 * @param[in] req A structure used to configure the fields of the IEEE_addr_req command, see @ref ezb_zdo_ieee_addr_req_t
 *
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_ieee_addr_req(const ezb_zdo_ieee_addr_req_t *req);

/**
 * @brief Send a ZDO Simple_Desc_req command.
 *
 * The Simple_Desc_req command is generated from a local device wishing to inquire as to the simple descriptor of a remote
 * device on a specified endpoint.
 * @param[in] req A structure used to configure the fields of the Simple_Desc_req command, see @ref ezb_zdo_simple_desc_req_t
 *
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_simple_desc_req(const ezb_zdo_simple_desc_req_t *req);

/**
 * @brief Send a ZDO Match_Desc_req command.
 *
 * The Match_Desc_req command is generated from a local device wishing to find remote devices supporting a specific simple
 * descriptor match criterion.
 * @param[in] req A structure used to configure the fields of the Match_Desc_req command, see @ref ezb_zdo_match_desc_req_t
 *
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_match_desc_req(const ezb_zdo_match_desc_req_t *req);

/**
 * @brief Send a ZDO Active_EP_req command.
 *
 * The Active_EP_req command is generated from a local device wishing to acquire the list of endpoints on a remote device with
 * simple descriptors.
 * @param[in] req A structure used to configure the fields of the Active_EP_req command, see @ref ezb_zdo_active_ep_req_t
 *
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_active_ep_req(const ezb_zdo_active_ep_req_t *req);

/**
 * @brief Send a ZDO Power_Desc_req command.
 *
 * The Power_Desc_req command is generated from a local device wishing to inquire as to the power descriptor of a remote device.
 * @param[in] req A structure used to configure the fields of the Power_Desc_req command, see @ref ezb_zdo_power_desc_req_t
 *
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_power_desc_req(const ezb_zdo_power_desc_req_t *req);

/**
 * @brief Send a ZDO Node_Desc_req command.
 *
 * The Node_Desc_req command is generated from a local device wishing to inquire as to the node descriptor of a remote device.
 * @param[in] req A structure used to configure the fields of the Node_Desc_req command, see @ref ezb_zdo_node_desc_req_t
 *
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_node_desc_req(const ezb_zdo_node_desc_req_t *req);

/**
 * @brief Announce the existence of the Zigbee network to the network.
 *
 * The Device_Annce_req command is generated from a local device wishing to announce itself to the network.
 * @param[in] req A structure used to configure the fields of the Device_Annce_req command, see @ref ezb_zdo_device_annce_req_t

 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_device_annce_req(const ezb_zdo_device_annce_req_t *req);

/**
 * @brief Announce the existence of the Zigbee network to the parent device.
 *
 * The Parent_Annce_req command is generated from a local device wishing to announce itself to the parent device.
 * @param[in] req A structure used to configure the fields of the Parent_Annce_req command, see @ref ezb_zdo_parent_annce_req_t
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_parent_annce_req(const ezb_zdo_parent_annce_req_t *req);

#ifdef __cplusplus
} /*  extern "C" */
#endif
