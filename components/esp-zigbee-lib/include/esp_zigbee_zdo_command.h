/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "esp_zigbee_type.h"

/* MATCH DESC REQ ZCL configuration */
#define ESP_ZB_MATCH_DESC_REQ_TIMEOUT              (5 * ESP_ZB_TIME_ONE_SECOND)            /* timeout for finding */
#define ESP_ZB_MATCH_DESC_REQ_ROLE                 ESP_ZB_NWK_BROADCAST_RX_ON_WHEN_IDLE    /* find non-sleep Zigbee device, 0xFFFD */

/** Find device callback
 *
 * @brief A ZDO match desc request callback for user to get response info.
 *
 * @note User's callback get response from the remote device that local node wants to find a particular device on endpoint.
 *
 * @param[in] zdo_status A ZDO response feedback status, 0 - response status success refer to zboss_api_zdo.h zdp_status
 * @param[in] addr  A short address of the device response, 0xFFFF - invalid address
 * @param[in] endpoint An endpoint of the device response, 0xFF - invalid endpoint
 *
 */
typedef void (*esp_zb_zdo_match_desc_callback_t)(uint8_t zdo_status, uint16_t addr, uint8_t endpoint);

/** IEEE address request callback
 *
 * @brief A ZDO ieee address request callback for user to get response info.
 *
 * @note User's callback get response from the remote device that local node wants to get ieee address.
 *
 * @param[in] zdo_status A ZDO response feedback status, 0 - response status success refer to zboss_api_zdo.h zdp_status
 * @param[in] ieee_addr  A ieee address of the device response, 0xFFFF FFFF FFFF FFFF - invalid ieee address
 *
 */
typedef void (*esp_zb_zdo_ieee_addr_callback_t)(uint8_t zdo_status, esp_zb_ieee_addr_t ieee_addr);

/** Bind request callback
 *
 * @brief A ZDO bind request callback for user to get response info.
 *
 * @note user's callback get response from the remote device that local node wants to bind.
 *
 * @param[in] zdo_status A ZDO response feedback status, 0 - response status success refer to zboss_api_zdo.h zdp_status
 *
 */
typedef void (*esp_zb_zdo_bind_callback_t)(uint8_t zdo_status);

/** Active endpoint callback
 *
 * @brief A ZDO active endpoint request callback for user to get response info.
 *
 * @note User's callback get response from the remote device that local node wants to get active endpoint.
 *
 * @param[in] zdo_status A ZDO response feedback status, 0 - response status success refer to zboss_api_zdo.h zdp_status
 * @param[in] ep_count  A number of active endpoint
 * @param[in] ep_id_list A pointer of the endpoint id list
 *
 */
typedef void (*esp_zb_zdo_active_ep_callback_t)(uint8_t zdo_status, uint8_t ep_count, uint8_t *ep_id_list);

/** Simple descriptor callback
 *
 * @brief A ZDO simple descriptor request callback for user to get simple desc info.
 *
 * @note User's callback get response from the remote device that local node wants to get simple desc.
 *
 * @param[in] zdo_status A ZDO response feedback status, 0 - response status success refer to zboss_api_zdo.h zdp_status
 * @param[in] simple_desc  A pointer to the simple desc @ref esp_zb_af_simple_desc_1_1_s
 *
 */
typedef void (*esp_zb_zdo_simple_desc_callback_t)(uint8_t zdo_status, esp_zb_af_simple_desc_1_1_t *simple_desc);

/** Permit join request callback
 *
 * @brief A ZDO permit join request callback for user to get permit join response info.
 *
 * @note User's callback get response from the node requested to permit join.
 *
 * @param[in] zdo_status A ZDO response feedback status, 0 - response status success refer to zboss_api_zdo.h zdp_status
 *
 */
typedef void (*esp_zb_zdo_permit_join_callback_t)(uint8_t zdo_status);

/** Leave request callback
 *
 * @brief A ZDO leave request callback for user to get leave status.
 *
 * @note User's callback get response from the device that wants to leave.
 *
 * @param[in] zdo_status A ZDO response feedback status, 0 - response status success refer to zboss_api_zdo.h zdp_status
 *
 */
typedef void (*esp_zb_zdo_leave_callback_t)(uint8_t zdo_status);

/**
 * @brief The Zigbee ZDO bind command struct
 *
 * @note Current implementation of the API ONLY supports 64 bit extended address's address mode. Other address mode will support later.
 *
 * @note Be aware of the one req_dst_addr is address that command send to, while dst_address is the destination of the binding entry.
 *
 * @note NOW the dst_addr_mode is default by ZB_BIND_DST_ADDR_MODE_64_BIT_EXTENDED. Later SDK will support other address mode.
 *
 */
typedef struct esp_zb_zdo_bind_req_param_s {
    esp_zb_ieee_addr_t src_address;                     /*!< The IEEE address for the source */
    uint8_t src_endp;                                   /*!< The source endpoint for the binding entry */
    uint16_t cluster_id;                                /*!< The identifier of the cluster on the source device that is bound to the destination */
    esp_zb_addr_u dst_address_u;                        /*!< The destination address for the binding entry */
    uint8_t dst_endp;                                   /*!< This field shall be present only if the
                                                         * DstAddrMode field has a value of
                                                         * refer to ZB_BIND_DST_ADDR_MODE_64_BIT_EXTENDED refer to bind_dst_addr_mode
                                                         * and, if present, shall be the
                                                         * destination endpoint for the binding entry. */
    uint16_t req_dst_addr;                              /*!< Destination address of the request send to */
} esp_zb_zdo_bind_req_param_t;

/**
 * @brief The Zigbee ZDO match descrpitor command struct
 */
typedef struct esp_zb_zdo_match_desc_req_param_s {
    uint16_t   dst_nwk_addr;                            /*!< NWK address that request sent to */
    uint16_t   addr_of_interest;                        /*!< NWK address of interest */
} esp_zb_zdo_match_desc_req_param_t;

/**
 * @brief The Zigbee ZDO ieee request command struct
 *
 */
typedef struct esp_zb_zdo_ieee_addr_req_param_s {
    uint16_t   dst_nwk_addr;                            /*!< NWK address that request sent to */
    uint16_t   addr_of_interest;                        /*!< NWK address of interest */
    uint8_t    request_type;                            /*!< Request type for this command: 0x00  Single device response 0x01 Extended response  */
    uint8_t    start_index;                             /*!< If the Request type for this command is Extended response, the StartIndex provides the
                                                         * starting index for the requested elements of the associated devices list */
} esp_zb_zdo_ieee_addr_req_param_t;

/**
 * @brief The Zigbee ZDO simple descriptor command struct
 *
 */
typedef struct esp_zb_zdo_simple_desc_req_param_s {
    uint16_t   addr_of_interest;                        /*!< NWK address of interest */
    uint8_t    endpoint;                                /*!< Endpoint of interest */
} esp_zb_zdo_simple_desc_req_param_t;

/**
 * @brief The Zigbee ZDO active endpoint command struct
 *
 */
typedef struct esp_zb_zdo_active_ep_req_param_s {
    uint16_t   addr_of_interest;                        /*!< NWK address of interest */
} esp_zb_zdo_active_ep_req_param_t;

/**
 * @brief The Zigbee ZDO permit join command struct
 *
 */
typedef struct esp_zb_zdo_permit_joining_req_param_s {
    uint16_t   dst_nwk_addr;                            /*!< NWK address that request sent to */
    uint8_t permit_duration;                            /*!< The length of time in seconds. 0x00 and 0xff indicate that permission is disabled or enabled */
    uint8_t tc_significance;                            /*!< If this is set to 0x01 and the remote device is the Trust Center, the command affects the Trust Center
                                                         * authentication policy as described in the sub-clauses below; If this is set to 0x00, there is no effect
                                                         * on the Trust Center */
} esp_zb_zdo_permit_joining_req_param_t;

/**
 * @brief The Zigbee ZDO leave command struct
 *
 */
typedef struct esp_zb_zdo_mgmt_leave_req_param_s {
    esp_zb_ieee_addr_t device_address;                  /*!< 64-bit IEEE address on device */
    uint16_t   dst_nwk_addr;                            /*!< NWK address that request sent to */
    unsigned int reserved: 6;                           /*!< Reserved */
    unsigned int remove_children: 1;                    /*!< Bitfield of remove children or not */
    unsigned int rejoin: 1;                             /*!< Bitfield of rejoin or not */
} esp_zb_zdo_mgmt_leave_req_param_t;

/********************* Declare functions **************************/
/* ZDO command list, more ZDO command will be supported later like node_desc, power_desc */

/**
 * @brief   Send bind device request command
 *
 * @param[in] cmd_req  Pointer to the bind request command @ref esp_zb_zdo_bind_req_param_s
 * @param[in] user_cb  A user callback that will be called if received bind response refer to esp_zb_zdo_bind_callback_t
 *
 * @note Current implementation of API only support bind address mode ZB_APS_ADDR_MODE_64_ENDP_PRESENT for addressing.
 *
 */
void esp_zb_zdo_device_bind_req(esp_zb_zdo_bind_req_param_t *cmd_req, esp_zb_zdo_bind_callback_t user_cb);

/**
 * @brief   Send find on-off device request command
 *
 * @param[in] cmd_req  Pointer to the find request command @ref esp_zb_zdo_match_desc_req_param_s
 * @param[in] user_cb  A user callback that will be called if received find response refer to esp_zb_zdo_match_desc_callback_t
 *
 */
void esp_zb_zdo_find_on_off_light(esp_zb_zdo_match_desc_req_param_t *cmd_req, esp_zb_zdo_match_desc_callback_t user_cb);

/**
 * @brief   Send find color_dimmable device request command
 *
 * @param[in] cmd_req  Pointer to the find request command @ref esp_zb_zdo_match_desc_req_param_s
 * @param[in] user_cb  A user callback that will be called if received find response refer to esp_zb_zdo_match_desc_callback_t
 *
 */
void esp_zb_zdo_find_color_dimmable_light(esp_zb_zdo_match_desc_req_param_t *cmd_req, esp_zb_zdo_match_desc_callback_t user_cb);

/**
 * @brief   Send ieee request command
 *
 * @param[in] cmd_req  Pointer to the ieee address request command @ref esp_zb_zdo_ieee_addr_req_param_s
 * @param[in] user_cb  A user callback that will be called if received ieee address response refer to esp_zb_zdo_ieee_addr_callback_t
 *
 */
void esp_zb_zdo_ieee_addr_req(esp_zb_zdo_ieee_addr_req_param_t *cmd_req, esp_zb_zdo_ieee_addr_callback_t user_cb);

/**
 * @brief   Send simple descriptor request command
 *
 * @param[in] cmd_req  Pointer to the simple descriptor request command @ref esp_zb_zdo_simple_desc_req_param_s
 * @param[in] user_cb  A user callback that will be called if received simple desc response refer to esp_zb_zdo_simple_desc_callback_t
 *
 */
void esp_zb_zdo_simple_desc_req(esp_zb_zdo_simple_desc_req_param_t *cmd_req, esp_zb_zdo_simple_desc_callback_t user_cb);

/**
 * @brief   Send active endpoint request command
 *
 * @param[in] cmd_req  Pointer to the active endpoint request command @ref esp_zb_zdo_active_ep_req_param_s
 * @param[in] user_cb  A user callback that will be called if received active ep response refer to esp_zb_zdo_active_ep_callback_t
 *
 */
void esp_zb_zdo_active_ep_req(esp_zb_zdo_active_ep_req_param_t *cmd_req, esp_zb_zdo_active_ep_callback_t user_cb);

/**
 * @brief   Send leave request command
 *
 * @param[in] cmd_req  Pointer to the leave request command @ref esp_zb_zdo_mgmt_leave_req_param_s
 * @param[in] user_cb  A user callback that will be called if received leave response refer to esp_zb_zdo_leave_callback_t
 *
 */
void esp_zb_zdo_device_leave_req(esp_zb_zdo_mgmt_leave_req_param_t *cmd_req, esp_zb_zdo_leave_callback_t user_cb);

/**
 * @brief   Send permit join request command
 *
 * @param[in] cmd_req  Pointer to the permit join request command @ref esp_zb_zdo_permit_joining_req_param_s
 * @param[in] user_cb  A user callback that will be called if received permit join response refer to esp_zb_zdo_permit_join_callback_t
 *
 */
void esp_zb_zdo_permit_joining_req(esp_zb_zdo_permit_joining_req_param_t *cmd_req, esp_zb_zdo_permit_join_callback_t user_cb);

#ifdef __cplusplus
}
#endif
