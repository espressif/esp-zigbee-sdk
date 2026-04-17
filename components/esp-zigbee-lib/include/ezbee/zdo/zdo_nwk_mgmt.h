/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file zdo_nwk_mgmt.h
 * @brief Zigbee Device Object (ZDO) Network Management API
 *
 * This header file provides APIs for network management operations in a Zigbee network.
 * Network management includes operations for monitoring and controlling the network topology
 * and device behavior.
 *
 * The network management includes:
 * - Link Quality Indicator (LQI) requests to query neighbor table information
 * - Leave requests to remove devices from the network
 * - Permit joining requests to control device joining
 * - Network update requests to scan and update network parameters
 * - Binding table management requests to query binding information
 *
 * All requests use a unified structure that includes the destination address,
 * request fields, callback function, and user context.
 */

#pragma once

#include <ezbee/zdo/zdo_type.h>

#include <ezbee/af.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Fields of the ZDP Network Management Link Quality Indicator (LQI) Request Command
 */
typedef struct ezb_zdp_nwk_mgmt_lqi_req_field_s {
    uint8_t start_index; /*!< Starting index in the neighbor table for the requested entries */
} ezb_zdp_nwk_mgmt_lqi_req_field_t;

/**
 * @brief Structure for ZDP Network Management Link Quality Indicator (LQI) Neighbor Table Entry
 *
 * This structure represents a single entry in the neighbor table, containing information about a neighboring device.
 */
typedef struct ezb_zdp_nwk_mgmt_lqi_neighbor_table_entry_s {
    ezb_extpanid_t  extended_pan_id;     /*!< Extended PAN ID */
    ezb_extaddr_t   extended_addr;       /*!< Extended address */
    ezb_shortaddr_t nwk_addr;            /*!< NWK address */
    uint8_t         device_type : 2;     /*!< Device type: 0 = Coordinator, 1 = Router, 2 = End Device, 3 = Reserved */
    uint8_t         rx_on_when_idle : 2; /*!< RX on when idle: 0 = Disabled, 1 = Enabled, 2-3 = Reserved */
    uint8_t         affinity : 3;        /*!< Relationship: 0 = Parent, 1 = Child, 2 = Sibling, 3 = None, 4-7 = Reserved */
    uint8_t         reserved1 : 1;       /*!< Reserved field */
    uint8_t         permit_joining : 2;  /*!< Permit joining: 0 = Not accepting, 1 = Accepting, 2-3 = Reserved */
    uint8_t         reserved2 : 6;       /*!< Reserved field */
    uint8_t         device_depth;        /*!< Depth of the device in the network tree (0 = coordinator) */
    uint8_t         lqa;                 /*!< Link Quality Assessment value (0-255, higher is better) */
} ezb_zdp_nwk_mgmt_lqi_neighbor_table_entry_t;

/**
 * @brief Structure for ZDP Network Management Link Quality Indicator (LQI) Response
 */
typedef struct ezb_zdp_nwk_mgmt_lqi_rsp_field_s {
    uint8_t status;                    /*!< Status of the LQI request, see @ref ezb_zdp_status_t */
    uint8_t neighbor_table_entries;    /*!< Total number of entries in the neighbor table */
    uint8_t start_index;               /*!< Starting index of the entries returned in this response */
    uint8_t neighbor_table_list_count; /*!< Number of neighbor table entries in this response */
    ezb_zdp_nwk_mgmt_lqi_neighbor_table_entry_t *neighbor_table_list; /*!< Pointer to array of neighbor table entries */
} ezb_zdp_nwk_mgmt_lqi_rsp_field_t;

/**
 * @brief Structure for ZDO Network Management LQI Request Result
 */
typedef struct ezb_zdo_nwk_mgmt_lqi_req_result_s {
    ezb_err_t                         error; /*!< Error code of the request operation */
    ezb_zdp_nwk_mgmt_lqi_rsp_field_t *rsp;   /*!< Pointer to the LQI response field, NULL if error occurred */
} ezb_zdo_nwk_mgmt_lqi_req_result_t;

/**
 * @brief A callback to handle the result of ZDO Network Management LQI Request
 */
typedef void (*ezb_zdo_nwk_mgmt_lqi_req_callback_t)(const ezb_zdo_nwk_mgmt_lqi_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO Network Management Link Quality Indicator (LQI) Request
 */
typedef struct ezb_zdo_nwk_mgmt_lqi_req_s {
    ezb_shortaddr_t                     dst_nwk_addr; /*!< NWK address that request sent to */
    ezb_zdp_nwk_mgmt_lqi_req_field_t    field;        /*!< The fields of the LQI request */
    ezb_zdo_nwk_mgmt_lqi_req_callback_t cb;           /*!< User callback for result of ZDO Network Management LQI Request */
    void                               *user_ctx;     /*!< User argument of request will be passed to user callback */
} ezb_zdo_nwk_mgmt_lqi_req_t;

/**
 * @brief Structure for ZDP Network Management Leave Response
 */
typedef struct ezb_zdp_nwk_mgmt_leave_rsp_field_s {
    uint8_t status; /*!< Status of the leave operation, see @ref ezb_zdp_status_t */
} ezb_zdp_nwk_mgmt_leave_rsp_field_t;

/**
 * @brief Structure for ZDO Network Management Leave Request Result
 */
typedef struct ezb_zdo_nwk_mgmt_leave_req_result_s {
    ezb_err_t                           error; /*!< Error code of the request operation */
    ezb_zdp_nwk_mgmt_leave_rsp_field_t *rsp;   /*!< Pointer to the leave response field, NULL if error occurred */
} ezb_zdo_nwk_mgmt_leave_req_result_t;

/**
 * @brief Fields of the ZDP Network Management Leave Request Command
 */
typedef struct ezb_zdp_nwk_mgmt_leave_req_field_s {
    ezb_extaddr_t device_addr;     /*!< IEEE address of the device to be removed from the network */
    bool          remove_children; /*!< If true, remove all children of the device; if false, reassign children */
    bool          rejoin;          /*!< If true, the device is allowed to rejoin the network */
} ezb_zdp_nwk_mgmt_leave_req_field_t;

/**
 * @brief A callback to handle the result of ZDO Network Management Leave Request
 */
typedef void (*ezb_zdo_nwk_mgmt_leave_req_callback_t)(const ezb_zdo_nwk_mgmt_leave_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO Network Management Leave Request
 */
typedef struct ezb_zdo_nwk_mgmt_leave_req_s {
    ezb_shortaddr_t                       dst_nwk_addr; /*!< NWK address that request sent to */
    ezb_zdp_nwk_mgmt_leave_req_field_t    field;        /*!< The fields of the leave request */
    ezb_zdo_nwk_mgmt_leave_req_callback_t cb;           /*!< User callback for result of ZDO Network Management Leave Request */
    void                                 *user_ctx;     /*!< User argument of request will be passed to user callback */
} ezb_zdo_nwk_mgmt_leave_req_t;

/**
 * @brief Fields of the ZDP Network Management Permit Joining Request Command
 */
typedef struct ezb_zdp_nwk_mgmt_permit_joining_req_field_s {
    uint8_t permit_duration; /*!< Duration in seconds for which joining is permitted. 0x00 = disable joining, 0xFF = enable
                                joining indefinitely */
    uint8_t tc_significance; /*!< Trust Center significance. 0x00 = not significant, 0x01 = significant (only TC can permit
                                joining) */
    /* TODO: support TLV */
    /* bool disable_tlv; */
} ezb_zdp_nwk_mgmt_permit_joining_req_field_t;

/**
 * @brief Structure for ZDP Network Management Permit Joining Response
 */
typedef struct ezb_zdp_nwk_mgmt_permit_joining_rsp_field_s {
    uint8_t status; /*!< Status of the permit joining operation, see @ref ezb_zdp_status_t */
} ezb_zdp_nwk_mgmt_permit_joining_rsp_field_t;

/**
 * @brief Structure for ZDO Network Management Permit Joining Request Result
 */
typedef struct ezb_zdo_nwk_mgmt_permit_joining_req_result_s {
    ezb_err_t error;                                  /*!< Error code of the request operation */
    ezb_zdp_nwk_mgmt_permit_joining_rsp_field_t *rsp; /*!< Pointer to the permit joining response field,
                                                           NULL if error occurred */
} ezb_zdo_nwk_mgmt_permit_joining_req_result_t;

/**
 * @brief A callback to handle the result of ZDO Network Management Permit Joining Request
 */
typedef void (*ezb_zdo_nwk_mgmt_permit_joining_req_callback_t)(const ezb_zdo_nwk_mgmt_permit_joining_req_result_t *result,
                                                               void                                               *user_ctx);

/**
 * @brief Structure for ZDO Network Management Permit Joining Request
 */
typedef struct ezb_zdo_nwk_mgmt_permit_joining_req_s {
    uint16_t                                    dst_nwk_addr; /*!< NWK address that request sent to */
    ezb_zdp_nwk_mgmt_permit_joining_req_field_t field;        /*!< The fields of the permit joining request */
    ezb_zdo_nwk_mgmt_permit_joining_req_callback_t cb;        /*!< User callback for result of ZDO Network Management
                                                                   Permit Joining Request */
    void *user_ctx; /*!< User argument of request will be passed to user callback */
} ezb_zdo_nwk_mgmt_permit_joining_req_t;

/**
 * @brief Fields of the ZDP Network Management Network Update Request Command
 */
typedef struct ezb_zdp_nwk_mgmt_nwk_update_req_field_s {
    uint32_t scan_channels; /*!< Bitmask of channels to scan (bits 0-26 represent channels 11-26) */
    uint8_t  scan_duration; /*!< Duration of each channel scan in seconds */
    uint8_t  scan_count;    /*!< Number of scans to perform on each channel */
    uint8_t  nwk_update_id; /*!< Network update identifier, should be incremented for each update */
    uint8_t  nwk_mgmt_addr; /*!< Network manager address (0x00 = use default) */
} ezb_zdp_nwk_mgmt_nwk_update_req_field_t;

/**
 * @brief Structure for ZDP Network Management Network Update Notify
 *
 * This structure is returned as a notification when a network update operation completes.
 */
typedef struct ezb_zdp_nwk_mgmt_nwk_update_notify_field_s {
    uint8_t  status;                      /*!< Status of the network update operation, see @ref ezb_zdp_status_t */
    uint32_t scanned_channels;            /*!< Bitmask of channels that were scanned */
    uint16_t total_transmissions;         /*!< Total number of transmissions performed during scanning */
    uint16_t transmissions_failure;       /*!< Number of failed transmissions during scanning */
    uint8_t  scanned_channels_list_count; /*!< Number of channels in the scanned channels list */
    int8_t  energy_values[27];            /*!< Array of energy values for each scanned channel (one byte per channel) */
} ezb_zdp_nwk_mgmt_nwk_update_notify_field_t;

/**
 * @brief Structure for ZDO Network Management Network Update Request Result
 */
typedef struct ezb_zdo_nwk_mgmt_nwk_update_req_result_s {
    ezb_err_t                                   error; /*!< Error code of the request operation */
    ezb_zdp_nwk_mgmt_nwk_update_notify_field_t *rsp;   /*!< Pointer to the network update notify field,
                                                            NULL if error occurred */
} ezb_zdo_nwk_mgmt_nwk_update_req_result_t;

/**
 * @brief A callback to handle the result of ZDO Network Management Network Update Request
 */
typedef void (*ezb_zdo_nwk_mgmt_nwk_update_req_callback_t)(const ezb_zdo_nwk_mgmt_nwk_update_req_result_t *result,
                                                           void                                           *user_ctx);

/**
 * @brief Structure for ZDO Network Management Network Update Request
 */
typedef struct ezb_zdo_nwk_mgmt_nwk_update_req_s {
    uint16_t                                dst_nwk_addr; /*!< NWK address that request sent to */
    ezb_zdp_nwk_mgmt_nwk_update_req_field_t field;        /*!< The fields of the network update request */
    ezb_zdo_nwk_mgmt_nwk_update_req_callback_t cb;        /*!< User callback for result of ZDO Network Management
                                                               Network Update Request, If the request is broadcast,
                                                               the callback may be invoked multiple times to report
                                                               different responses, with the NULL response indicating
                                                               completion. */
    void *user_ctx; /*!< User argument of request will be passed to user callback */
} ezb_zdo_nwk_mgmt_nwk_update_req_t;

/**
 * @brief Fields of the ZDP Network Management Binding Table Request Command
 */
typedef struct ezb_zdp_nwk_mgmt_bind_req_field_s {
    uint8_t start_index; /*!< Starting index in the binding table for the requested entries */
} ezb_zdp_nwk_mgmt_bind_req_field_t;

/**
 * @brief Structure for ZDP Network Management Binding Table Entry
 */
typedef struct ezb_zdp_nwk_mgmt_bind_table_entry_s {
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
    uint8_t dst_ep;      /*!< The endpoint of the destination device. */
} ezb_zdp_nwk_mgmt_bind_table_entry_t;

/**
 * @brief Structure for ZDP Network Management Binding Table Response
 */
typedef struct ezb_zdp_nwk_mgmt_bind_rsp_field_s {
    uint8_t                              status; /*!< Status of the binding table request, see @ref ezb_zdp_status_t */
    uint8_t                              binding_table_entries; /*!< Total number of entries in the binding table */
    uint8_t                              start_index;           /*!< Starting index of the entries returned in this response */
    uint8_t                              binding_table_list_count; /*!< Number of binding table entries in this response */
    ezb_zdp_nwk_mgmt_bind_table_entry_t *binding_table_list;       /*!< Pointer to array of binding table entries */
} ezb_zdp_nwk_mgmt_bind_rsp_field_t;

/**
 * @brief Structure for ZDO Network Management Binding Table Request Result
 */
typedef struct ezb_zdo_nwk_mgmt_bind_req_result_s {
    ezb_err_t                          error; /*!< Error code of the request operation */
    ezb_zdp_nwk_mgmt_bind_rsp_field_t *rsp;   /*!< Pointer to the binding table response field, NULL if error occurred */
} ezb_zdo_nwk_mgmt_bind_req_result_t;

/**
 * @brief A callback to handle the result of ZDO Network Management Binding Table Request
 */
typedef void (*ezb_zdo_nwk_mgmt_bind_req_callback_t)(const ezb_zdo_nwk_mgmt_bind_req_result_t *result, void *user_ctx);

/**
 * @brief Structure for ZDO Network Management Binding Table Request
 */
typedef struct ezb_zdo_nwk_mgmt_bind_req_s {
    uint16_t                             dst_nwk_addr; /*!< NWK address that request sent to */
    ezb_zdp_nwk_mgmt_bind_req_field_t    field;        /*!< The fields of the binding request */
    ezb_zdo_nwk_mgmt_bind_req_callback_t cb;           /*!< User callback for result of ZDO Network Management Binding
                                                            Table Request */
    void                                *user_ctx; /*!< User argument of request will be passed to user callback */
} ezb_zdo_nwk_mgmt_bind_req_t;

/**
 * @brief Send a ZDO Network Management Link Quality Indicator (LQI) Request
 *
 * The LQI_req command is generated from a local device wishing to inquire as to the Link Quality Indicator (LQI) of a remote
 * device.
 * @param[in] req A structure used to configure the fields of the LQI_req command, see @ref ezb_zdo_nwk_mgmt_lqi_req_t
 *
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_nwk_mgmt_lqi_req(const ezb_zdo_nwk_mgmt_lqi_req_t *req);

/**
 * @brief Send a ZDO Network Management Leave Request
 *
 * The Leave_req command is generated from a local device wishing to leave a network.
 * @param[in] req A structure used to configure the fields of the Leave_req command, see @ref ezb_zdo_nwk_mgmt_leave_req_t
 *
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_nwk_mgmt_leave_req(const ezb_zdo_nwk_mgmt_leave_req_t *req);

/**
 * @brief Send a ZDO Network Management Permit Joining Request
 *
 * The Permit_Joining_req command is generated from a local device wishing to permit joining a network.
 * @param[in] req A structure used to configure the fields of the Permit_Joining_req command, see @ref
 * ezb_zdo_nwk_mgmt_permit_joining_req_t
 *
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_nwk_mgmt_permit_joining_req(const ezb_zdo_nwk_mgmt_permit_joining_req_t *req);

/**
 * @brief Send a ZDO Network Management Network Update Request
 *
 * The Network_Update_req command is generated from a local device wishing to update a network.
 * @param[in] req A structure used to configure the fields of the Network_Update_req command, see @ref
 * ezb_zdo_nwk_mgmt_nwk_update_req_t
 *
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_nwk_mgmt_nwk_update_req(const ezb_zdo_nwk_mgmt_nwk_update_req_t *req);

/**
 * @brief Send a ZDO Network Management Binding Table Request
 *
 * The Mgmt_Bind_req command is generated from a local device wishing to retrieve a binding table from a remote device.
 * @param[in] req A structure used to configure the fields of the Mgmt_Bind_req command, see @ref ezb_zdo_nwk_mgmt_bind_req_t
 *
 * @return Error code, see @ref ezb_err_t
 */
ezb_err_t ezb_zdo_nwk_mgmt_bind_req(const ezb_zdo_nwk_mgmt_bind_req_t *req);

#ifdef __cplusplus
} /*  extern "C" */
#endif
