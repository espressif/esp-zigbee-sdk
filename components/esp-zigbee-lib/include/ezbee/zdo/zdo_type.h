/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/core_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration for ZDP status
 * @anchor ezb_zdp_status_e
 */
enum ezb_zdp_status_e {
    EZB_ZDP_STATUS_SUCCESS          = 0x00U, /*!< The requested operation or transmission was completed successfully. */
    EZB_ZDP_STATUS_INV_REQUESTTYPE  = 0x80U, /*!< The supplied request type was invalid. */
    EZB_ZDP_STATUS_DEVICE_NOT_FOUND = 0x81U, /*!< The requested device did not exist on a device following a child descriptor
                                              *   request to a parent. */
    EZB_ZDP_STATUS_INVALID_EP    = 0x82U,    /*!< The supplied endpoint was equal to 0x00 or between 0xf1 and 0xff. */
    EZB_ZDP_STATUS_NOT_ACTIVE    = 0x83U,    /*!< The requested endpoint is not described by simple descriptor. */
    EZB_ZDP_STATUS_NOT_SUPPORTED = 0x84U,    /*!< The requested optional feature is not supported on the target device. */
    EZB_ZDP_STATUS_TIMEOUT       = 0x85U,    /*!< A timeout has occurred with the requested operation. */
    EZB_ZDP_STATUS_NO_MATCH      = 0x86U,    /*!< The end device bind request was unsuccessful due to a failure to match any
                                              *   suitable clusters. */
    EZB_ZDP_STATUS_NO_ENTRY = 0x88U,      /*!< The unbind request was unsuccessful due to the coordinator or source device not
                                           *   having an entry in its binding table to unbind. */
    EZB_ZDP_STATUS_NO_DESCRIPTOR = 0x89U, /*!< A child descriptor was not available following a discovery request to
                                           *   a parent. */
    EZB_ZDP_STATUS_INSUFFICIENT_SPACE = 0x8aU, /*!< The device does not have space to support the requested operation. */
    EZB_ZDP_STATUS_NOT_PERMITTED      = 0x8bU, /*!< The device is not in the proper state to support the requested operation. */
    EZB_ZDP_STATUS_TABLE_FULL         = 0x8cU, /*!< The device does not have table space to support the operation. */
    EZB_ZDP_STATUS_NOT_AUTHORIZED     = 0x8dU, /*!< The permissions configuration table on the target indicates that the request
                                                *   is not authorized from this device. */
    EZB_ZDP_STATUS_BINDING_TABLE_FULL = 0x8eU, /*!< The device doesn't have binding table space to support the operation */
    EZB_ZDP_STATUS_INVALID_INDEX      = 0x8fU, /*!< The index in the received command is out of bounds. */
};

/**
 * @brief Represents the ZDP status code, see @ref ezb_zdp_status_e
 * @anchor ezb_zdp_status_t
 */
typedef uint8_t ezb_zdp_status_t;

/**
 * @brief ZDO Request Command IDs
 * @anchor ezb_zdo_req_cmd_id_e
 */
enum ezb_zdo_req_cmd_id_e {
    // Device and Service Discovery Client Services Command IDs
    EZB_ZDO_CMD_NWK_ADDR_REQ    = 0x0000U, /*!< Network Address Request */
    EZB_ZDO_CMD_IEEE_ADDR_REQ   = 0x0001U, /*!< IEEE Address Request */
    EZB_ZDO_CMD_NODE_DESC_REQ   = 0x0002U, /*!< Node Descriptor Request */
    EZB_ZDO_CMD_POWER_DESC_REQ  = 0x0003U, /*!< Power Descriptor Request */
    EZB_ZDO_CMD_SIMPLE_DESC_REQ = 0x0004U, /*!< Simple Descriptor Request */
    EZB_ZDO_CMD_ACTIVE_EP_REQ   = 0x0005U, /*!< Active Endpoints Request */
    EZB_ZDO_CMD_MATCH_DESC_REQ  = 0x0006U, /*!< Match Descriptor Request */
    EZB_ZDO_CMD_DEVICE_ANNCE    = 0x0013U, /*!< Device Announce */
    EZB_ZDO_CMD_PARENT_ANNCE    = 0x001fU, /*!< Parent Announce */
    // End Device Bind, Bind, Unbind, and Bind Management Client Service Command IDs
    EZB_ZDO_CMD_BIND_REQ   = 0x0021U, /*!< Bind Request */
    EZB_ZDO_CMD_UNBIND_REQ = 0x0022U, /*!< Unbind Request */
    // @brief Network Management Client Services Command IDs
    EZB_ZDO_CMD_MGMT_LQI_REQ            = 0x0031U, /*!< Mgmt_Lqi_req */
    EZB_ZDO_CMD_MGMT_BIND_REQ           = 0x0033U, /*!< Mgmt_Bind_req */
    EZB_ZDO_CMD_MGMT_LEAVE_REQ          = 0x0034U, /*!< Mgmt_Leave_req */
    EZB_ZDO_CMD_MGMT_PERMIT_JOINING_REQ = 0x0036U, /*!< Mgmt_Permit_Joining_req */
    EZB_ZDO_CMD_MGMT_NWK_UPDATE_REQ     = 0x0038U, /*!< Mgmt_NWK_Update_req */
};

/**
 * @brief Represents the ZDO request command ID, see @ref ezb_zdo_req_cmd_id_e
 * @anchor ezb_zdo_req_cmd_id_t
 */
typedef uint16_t ezb_zdo_req_cmd_id_t;

/**
 * @brief Device and Service Discovery Server Service Response Command IDs
 * @anchor ezb_zdo_rsp_cmd_id_e
 */
enum ezb_zdo_rsp_cmd_id_e {
    // Device and Service Discovery Server Service Response Command IDs
    EZB_ZDO_CMD_NWK_ADDR_RSP     = 0x8000U, /*!< Network Address Response */
    EZB_ZDO_CMD_IEEE_ADDR_RSP    = 0x8001U, /*!< IEEE Address Response */
    EZB_ZDO_CMD_NODE_DESC_RSP    = 0x8002U, /*!< Node Descriptor Response */
    EZB_ZDO_CMD_POWER_DESC_RSP   = 0x8003U, /*!< Power Descriptor Response */
    EZB_ZDO_CMD_SIMPLE_DESC_RSP  = 0x8004U, /*!< Simple Descriptor Response */
    EZB_ZDO_CMD_ACTIVE_EP_RSP    = 0x8005U, /*!< Active Endpoints Response */
    EZB_ZDO_CMD_MATCH_DESC_RSP   = 0x8006U, /*!< Match Descriptor Response */
    EZB_ZDO_CMD_PARENT_ANNCE_RSP = 0x801fU, /*!< Parent Announce Response */
    // End Device Bind, Unbind, and Bind Management Server Service Response Command IDs
    EZB_ZDO_CMD_BIND_RSP   = 0x8021U, /*!< Bind Response */
    EZB_ZDO_CMD_UNBIND_RSP = 0x8022U, /*!< Unbind Response */
    // Network Management Server Service Response Command IDs
    EZB_ZDO_CMD_MGMT_NWK_DISC_RSP                      = 0x8030U, /*!< Mgmt_NWK_Disc_rsp (Deprecated) */
    EZB_ZDO_CMD_MGMT_LQI_RSP                           = 0x8031U, /*!< Mgmt_Lqi_rsp */
    EZB_ZDO_CMD_MGMT_RTG_RSP                           = 0x8032U, /*!< Mgmt_Rtg_rsp */
    EZB_ZDO_CMD_MGMT_BIND_RSP                          = 0x8033U, /*!< Mgmt_Bind_rsp */
    EZB_ZDO_CMD_MGMT_LEAVE_RSP                         = 0x8034U, /*!< Mgmt_Leave_rsp */
    EZB_ZDO_CMD_MGMT_DIRECT_JOIN_RSP                   = 0x8035U, /*!< Mgmt_Direct_Join_rsp */
    EZB_ZDO_CMD_MGMT_PERMIT_JOINING_RSP                = 0x8036U, /*!< Mgmt_Permit_Joining_rsp */
    EZB_ZDO_CMD_MGMT_CACHE_RSP                         = 0x8037U, /*!< Mgmt_Cache_rsp */
    EZB_ZDO_CMD_MGMT_NWK_UPDATE_NOTIFY                 = 0x8038U, /*!< Mgmt_NWK_Update_notify */
    EZB_ZDO_CMD_MGMT_NWK_ENHANCED_UPDATE_NOTIFY        = 0x8039U, /*!< Mgmt_NWK_Enhanced_Update_notify */
    EZB_ZDO_CMD_MGMT_NWK_IEEE_JOINING_LIST_RSP         = 0x803AU, /*!< Mgmt_NWK_IEEE_Joining_List_rsp */
    EZB_ZDO_CMD_MGMT_NWK_UNSOLICITED_ENH_UPDATE_NOTIFY = 0x803BU  /*!< Mgmt_NWK_Unsolicited_Enhanced_Update_notify */
};

/**
 * @brief Represents the ZDO response command ID, see @ref ezb_zdo_rsp_cmd_id_e
 * @anchor ezb_zdo_rsp_cmd_id_t
 */
typedef uint16_t ezb_zdo_rsp_cmd_id_t;

#ifdef __cplusplus
} /*  extern "C" */
#endif
