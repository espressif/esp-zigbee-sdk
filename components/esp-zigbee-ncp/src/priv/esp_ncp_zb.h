/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "esp_err.h"

#define ESP_NCP_ZB_PACKED_STRUCT __attribute__ ((packed))

/**
 * @brief A function for process Zigbee stack.
 *
 * @param[in]  input    The pointer to storage the data from host
 * @param[in]  inlen    The length to storage the data from host
 * @param[out] output   The pointer to storage the data to host
 * @param[out] outlen   The length to storage the data to host
 *
 * @return 
 *     - ESP_OK on success
 *     - others: refer to esp_err.h
 */
typedef esp_err_t (*ncp_zb_fn)(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen);

/**
 * @brief Type to represent the protocol frame process function from the host.
 *
 */
typedef struct {
    uint16_t    id;                                     /*!< The frame ID for request */
    ncp_zb_fn   set_func;                               /*!< A function for process Zigbee stack */
} esp_ncp_zb_func_t;

/**
 * @brief Type to represent the configures endpoint information on the NCP.
 *
 */
typedef struct {
    uint8_t     endpoint;                               /*!< The application endpoint to be added */
    uint16_t    profileId;                              /*!< The endpoint's application profile */
    uint16_t    deviceId;                               /*!< The endpoint's device ID within the application profile */
    uint8_t     appFlags;                               /*!< The device version and flags indicating description availability */
    uint8_t     inputClusterCount;                      /*!< The number of cluster IDs in inputClusterList */
    uint8_t     outputClusterCount;                     /*!< The number of cluster IDs in outputClusterList */
} ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_endpoint_t;

/**
 * @brief Type to represent the application information on the NCP.
 *
 */
typedef struct {
    uint32_t user_cb;                   /*!< A ZDO match desc request callback */
    uint32_t user_ctx;                  /*!< User information context */
} esp_ncp_zb_user_cb_t;

/** Definition of the frame ID on the NCP.
 *
 */
#define ESP_NCP_NETWORK_INIT                    0x0000  /*!< Resume network operation after a reboot */
#define ESP_NCP_NETWORK_START                   0x0001  /*!< Start the commissioning process */
#define ESP_NCP_NETWORK_STATE                   0x0002  /*!< Returns a value indicating whether the node is joining, joined to, or leaving a network */
#define ESP_NCP_NETWORK_STACK_STATUS_HANDLER    0x0003  /*!< Notify it when the status of the stack changes */
#define ESP_NCP_NETWORK_FORMNETWORK             0x0004  /*!< Forms a new network by becoming the coordinator */
#define ESP_NCP_NETWORK_PERMIT_JOINING          0x0005  /*!< Allow other nodes to join the network with this node as their parent */
#define ESP_NCP_NETWORK_JOINNETWORK             0x0006  /*!< Associate with the network using the specified network parameters */
#define ESP_NCP_NETWORK_LEAVENETWORK            0x0007  /*!< Causes the stack to leave the current network */
#define ESP_NCP_NETWORK_START_SCAN              0x0008  /*!< Active scan available network */
#define ESP_NCP_NETWORK_SCAN_COMPLETE_HANDLER   0x0009  /*!< Signals that the scan has completed */
#define ESP_NCP_NETWORK_STOP_SCAN               0x000A  /*!< Terminates a scan in progress */
#define ESP_NCP_NETWORK_PAN_ID_GET              0x000B  /*!< Get the Zigbee network PAN ID */
#define ESP_NCP_NETWORK_PAN_ID_SET              0x000C  /*!< Set the Zigbee network PAN ID */
#define ESP_NCP_NETWORK_EXTENDED_PAN_ID_GET     0x000D  /*!< Get the Zigbee network extended PAN ID */
#define ESP_NCP_NETWORK_EXTENDED_PAN_ID_SET     0x000E  /*!< Set the Zigbee network extended PAN ID */
#define ESP_NCP_NETWORK_PRIMARY_CHANNEL_GET     0x000F  /*!< Get the primary channel mask */
#define ESP_NCP_NETWORK_PRIMARY_CHANNEL_SET     0x0010  /*!< Set the primary channel mask */
#define ESP_NCP_NETWORK_SECONDARY_CHANNEL_GET   0x0011  /*!< Get the secondary channel mask */
#define ESP_NCP_NETWORK_SECONDARY_CHANNEL_SET   0x0012  /*!< Set the secondary channel mask */
#define ESP_NCP_NETWORK_CHANNEL_GET             0x0013  /*!< Get the 2.4G channel */
#define ESP_NCP_NETWORK_CHANNEL_SET             0x0014  /*!< Set the 2.4G channel mask */
#define ESP_NCP_NETWORK_TXPOWER_GET             0x0015  /*!< Get the tx power */
#define ESP_NCP_NETWORK_TXPOWER_SET             0x0016  /*!< Set the tx power */
#define ESP_NCP_NETWORK_PRIMARY_KEY_GET         0x0017  /*!< Get the primary security network key */
#define ESP_NCP_NETWORK_PRIMARY_KEY_SET         0x0018  /*!< Set the primary security network key */
#define ESP_NCP_NETWORK_FRAME_COUNT_GET         0x0019  /*!< Get the network frame counter */
#define ESP_NCP_NETWORK_FRAME_COUNT_SET         0x001A  /*!< Set the network frame counter */
#define ESP_NCP_NETWORK_ROLE_GET                0x001B  /*!< Get the network role 0: Coordinator, 1: Router */
#define ESP_NCP_NETWORK_ROLE_SET                0x001C  /*!< Set the network role 0: Coordinator, 1: Router */
#define ESP_NCP_NETWORK_SHORT_ADDRESS_GET       0x001D  /*!< Get the Zigbee device short address */
#define ESP_NCP_NETWORK_SHORT_ADDRESS_SET       0x001E  /*!< Set the Zigbee device short address */
#define ESP_NCP_NETWORK_LONG_ADDRESS_GET        0x001F  /*!< Get the Zigbee device long address */
#define ESP_NCP_NETWORK_LONG_ADDRESS_SET        0x0020  /*!< Set the Zigbee device long address */
#define ESP_NCP_NETWORK_CHANNEL_MASKS_GET       0x0021  /*!< Get the channel masks */
#define ESP_NCP_NETWORK_CHANNEL_MASKS_SET       0x0022  /*!< Set the channel masks */
#define ESP_NCP_NETWORK_UPDATE_ID_GET           0x0023  /*!< Get the network update ID */
#define ESP_NCP_NETWORK_UPDATE_ID_SET           0x0024  /*!< Set the network update ID */
#define ESP_NCP_NETWORK_TRUST_CENTER_ADDR_GET   0x0025  /*!< Get the network trust center address */
#define ESP_NCP_NETWORK_TRUST_CENTER_ADDR_SET   0x0026  /*!< Set the network trust center address */
#define ESP_NCP_NETWORK_LINK_KEY_GET            0x0027  /*!< Get the network link key */
#define ESP_NCP_NETWORK_LINK_KEY_SET            0x0028  /*!< Set the network link key */
#define ESP_NCP_NETWORK_SECURE_MODE_GET         0x0029  /*!< Get the network security mode */
#define ESP_NCP_NETWORK_SECURE_MODE_SET         0x002A  /*!< Set the network security mode */
#define ESP_NCP_NETWORK_PREDEFINED_PANID        0x002B  /*!< Enable or disable predefined network panid */
#define ESP_NCP_NETWORK_SHORT_TO_IEEE           0x002C  /*!< Get the network IEEE address by the short address */
#define ESP_NCP_NETWORK_IEEE_TO_SHORT           0x002D  /*!< Get the network short address by the IEEE address */
#define ESP_NCP_ZCL_ENDPOINT_ADD                0x0100  /*!< Configures endpoint information on the NCP */
#define ESP_NCP_ZCL_ENDPOINT_DEL                0x0101  /*!< Remove endpoint information on the NCP */
#define ESP_NCP_ZCL_ATTR_READ                   0x0102  /*!< Read attribute data on NCP endpoints */
#define ESP_NCP_ZCL_ATTR_WRITE                  0x0103  /*!< Write attribute data on NCP endpoints */
#define ESP_NCP_ZCL_ATTR_REPORT                 0x0104  /*!< Report attribute data on NCP endpoints */
#define ESP_NCP_ZCL_ATTR_DISC                   0x0105  /*!< Discover attribute data on NCP endpoints */
#define ESP_NCP_ZCL_READ                        0x0106  /*!< Read APS on NCP endpoints */
#define ESP_NCP_ZCL_WRITE                       0x0107  /*!< Write APS on NCP endpoints */
#define ESP_NCP_ZCL_REPORT_CONFIG               0x0108  /*!< Report configure on NCP endpoints */
#define ESP_NCP_ZDO_BIND_SET                    0x0200  /*!< Create a binding between two endpoints on two nodes */
#define ESP_NCP_ZDO_UNBIND_SET                  0x0201  /*!< Remove a binding between two endpoints on two nodes */
#define ESP_NCP_ZDO_FIND_MATCH                  0x0202  /*!< Send match desc request to find matched Zigbee device */
#define ESP_NCP_APS_DATA_REQUEST                0x0300  /*!< Request the aps data */
#define ESP_NCP_APS_DATA_INDICATION             0x0301  /*!< Indication the aps data */
#define ESP_NCP_APS_DATA_CONFIRM                0x0302  /*!< Confirm the aps data */

/**
 * @brief   Process the frame ID on the NCP and response it to the host.
 * 
 * @param[in] ncp_header The protocol frame header pointer
 * @param[in] buffer     The payload buffer pointer which match the frame ID
 * @param[in] len        The payload buffer length which match the frame ID
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 *
 */
esp_err_t esp_ncp_zb_output(esp_ncp_header_t *ncp_header, const void *buffer, uint16_t len);

#ifdef __cplusplus
}
#endif
