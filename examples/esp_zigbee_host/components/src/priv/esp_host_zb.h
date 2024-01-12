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

#include "esp_host_frame.h"

#define ESP_ZNSP_ZB_PACKED_STRUCT __attribute__ ((packed))

typedef enum {
    ESP_ZNSP_TYPE_REQUEST,
    ESP_ZNSP_TYPE_RSPONSE,
    ESP_ZNSP_TYPE_NOTIFY,
} esp_znsp_type_t;

/**
 * @brief Enum of the status
 * 
 */
typedef enum {
    ESP_ZNSP_SUCCESS = 0x00,                            /*!< The generic 'no error' */
    ESP_ZNSP_ERR_FATAL = 0x01,                          /*!< The generic 'fatal error' */
    ESP_ZNSP_BAD_ARGUMENT = 0x02,                       /*!< An invalid value was passed as an argument */
    ESP_ZNSP_ERR_NO_MEM = 0x03,                         /*!< Out of memory */
} esp_znsp_status_t;

/** Definition of the frame ID on the host.
 *
 */
#define ESP_ZNSP_NETWORK_INIT                    0x0000  /*!< Resume network operation after a reboot */
#define ESP_ZNSP_NETWORK_START                   0x0001  /*!< Start the commissioning process */
#define ESP_ZNSP_NETWORK_STATE                   0x0002  /*!< Returns a value indicating whether the node is joining, joined to, or leaving a network */
#define ESP_ZNSP_NETWORK_STACK_STATUS_HANDLER    0x0003  /*!< Notify it when the status of the stack changes */
#define ESP_ZNSP_NETWORK_FORMNETWORK             0x0004  /*!< Forms a new network by becoming the coordinator */
#define ESP_ZNSP_NETWORK_PERMIT_JOINING          0x0005  /*!< Allow other nodes to join the network with this node as their parent */
#define ESP_ZNSP_NETWORK_JOINNETWORK             0x0006  /*!< Associate with the network using the specified network parameters */
#define ESP_ZNSP_NETWORK_LEAVENETWORK            0x0007  /*!< Causes the stack to leave the current network */
#define ESP_ZNSP_NETWORK_START_SCAN              0x0008  /*!< Active scan available network */
#define ESP_ZNSP_NETWORK_SCAN_COMPLETE_HANDLER   0x0009  /*!< Signals that the scan has completed */
#define ESP_ZNSP_NETWORK_STOP_SCAN               0x000A  /*!< Terminates a scan in progress */
#define ESP_ZNSP_NETWORK_PAN_ID_GET              0x000B  /*!< Get the Zigbee network PAN ID */
#define ESP_ZNSP_NETWORK_PAN_ID_SET              0x000C  /*!< Set the Zigbee network PAN ID */
#define ESP_ZNSP_NETWORK_EXTENDED_PAN_ID_GET     0x000D  /*!< Get the Zigbee network extended PAN ID */
#define ESP_ZNSP_NETWORK_EXTENDED_PAN_ID_SET     0x000E  /*!< Set the Zigbee network extended PAN ID */
#define ESP_ZNSP_NETWORK_PRIMARY_CHANNEL_GET     0x000F  /*!< Get the primary channel mask */
#define ESP_ZNSP_NETWORK_PRIMARY_CHANNEL_SET     0x0010  /*!< Set the primary channel mask */
#define ESP_ZNSP_NETWORK_SECONDARY_CHANNEL_GET   0x0011  /*!< Get the secondary channel mask */
#define ESP_ZNSP_NETWORK_SECONDARY_CHANNEL_SET   0x0012  /*!< Set the secondary channel mask */
#define ESP_ZNSP_NETWORK_CHANNEL_GET             0x0013  /*!< Get the 2.4G channel */
#define ESP_ZNSP_NETWORK_CHANNEL_SET             0x0014  /*!< Set the 2.4G channel mask */
#define ESP_ZNSP_NETWORK_TXPOWER_GET             0x0015  /*!< Get the tx power */
#define ESP_ZNSP_NETWORK_TXPOWER_SET             0x0016  /*!< Set the tx power */
#define ESP_ZNSP_NETWORK_PRIMARY_KEY_GET         0x0017  /*!< Get the primary security network key */
#define ESP_ZNSP_NETWORK_PRIMARY_KEY_SET         0x0018  /*!< Set the primary security network key */
#define ESP_ZNSP_NETWORK_FRAME_COUNT_GET         0x0019  /*!< Get the network frame counter */
#define ESP_ZNSP_NETWORK_FRAME_COUNT_SET         0x001A  /*!< Set the network frame counter */
#define ESP_ZNSP_NETWORK_ROLE_GET                0x001B  /*!< Get the network role 0: Coordinator, 1: Router */
#define ESP_ZNSP_NETWORK_ROLE_SET                0x001C  /*!< Set the network role 0: Coordinator, 1: Router */
#define ESP_ZNSP_NETWORK_SHORT_ADDRESS_GET       0x001D  /*!< Get the Zigbee device short address */
#define ESP_ZNSP_NETWORK_SHORT_ADDRESS_SET       0x001E  /*!< Set the Zigbee device short address */
#define ESP_ZNSP_NETWORK_LONG_ADDRESS_GET        0x001F  /*!< Get the Zigbee device long address */
#define ESP_ZNSP_NETWORK_LONG_ADDRESS_SET        0x0020  /*!< Set the Zigbee device long address */
#define ESP_ZNSP_NETWORK_CHANNEL_MASKS_GET       0x0021  /*!< Get the channel masks */
#define ESP_ZNSP_NETWORK_CHANNEL_MASKS_SET       0x0022  /*!< Set the channel masks */
#define ESP_ZNSP_NETWORK_UPDATE_ID_GET           0x0023  /*!< Get the network update ID */
#define ESP_ZNSP_NETWORK_UPDATE_ID_SET           0x0024  /*!< Set the network update ID */
#define ESP_ZNSP_NETWORK_TRUST_CENTER_ADDR_GET   0x0025  /*!< Get the network trust center address */
#define ESP_ZNSP_NETWORK_TRUST_CENTER_ADDR_SET   0x0026  /*!< Set the network trust center address */
#define ESP_ZNSP_NETWORK_LINK_KEY_GET            0x0027  /*!< Get the network link key */
#define ESP_ZNSP_NETWORK_LINK_KEY_SET            0x0028  /*!< Set the network link key */
#define ESP_ZNSP_NETWORK_SECURE_MODE_GET         0x0029  /*!< Get the network security mode */
#define ESP_ZNSP_NETWORK_SECURE_MODE_SET         0x002A  /*!< Set the network security mode */
#define ESP_ZNSP_NETWORK_PREDEFINED_PANID        0x002B  /*!< Enable or disable predefined network panid */
#define ESP_ZNSP_NETWORK_SHORT_TO_IEEE           0x002C  /*!< Get the network IEEE address by the short address */
#define ESP_ZNSP_NETWORK_IEEE_TO_SHORT           0x002D  /*!< Get the network short address by the IEEE address */
#define ESP_ZNSP_ZCL_ENDPOINT_ADD                0x0100  /*!< Configures endpoint information */
#define ESP_ZNSP_ZCL_ENDPOINT_DEL                0x0101  /*!< Remove endpoint information */
#define ESP_ZNSP_ZCL_ATTR_READ                   0x0102  /*!< Read attribute data */
#define ESP_ZNSP_ZCL_ATTR_WRITE                  0x0103  /*!< Write attribute data */
#define ESP_ZNSP_ZCL_ATTR_REPORT                 0x0104  /*!< Report attribute data*/
#define ESP_ZNSP_ZCL_ATTR_DISC                   0x0105  /*!< Discover attribute data */
#define ESP_ZNSP_ZCL_READ                        0x0106  /*!< Read ZCL command */
#define ESP_ZNSP_ZCL_WRITE                       0x0107  /*!< Write ZCL command */
#define ESP_ZNSP_ZCL_REPORT_CONFIG               0x0108  /*!< Report configure */
#define ESP_ZNSP_ZDO_BIND_SET                    0x0200  /*!< Create a binding between two endpoints on two nodes */
#define ESP_ZNSP_ZDO_UNBIND_SET                  0x0201  /*!< Remove a binding between two endpoints on two nodes */
#define ESP_ZNSP_ZDO_FIND_MATCH                  0x0202  /*!< Send match desc request to find matched Zigbee device */

/**
 * @brief A function for process Zigbee stack.
 *
 * @param[in]  input    The pointer to storage the data
 * @param[in]  inlen    The length to storage the data
 *
 * @return 
 *     - ESP_OK on success
 *     - others: refer to esp_err.h
 */
typedef esp_err_t (*host_zb_fn)(const uint8_t *input, uint16_t inlen);

/**
 * @brief Type to represent the protocol frame process function.
 *
 */
typedef struct {
    uint16_t    id;                                     /*!< The frame ID for request */
    host_zb_fn  set_func;                               /*!< A function for process Zigbee stack */
} esp_host_zb_func_t;

/**
 * @brief Type to represent the configures endpoint information on the host.
 *
 */
typedef struct {
    uint8_t     endpoint;                               /*!< The application endpoint to be added */
    uint16_t    profileId;                              /*!< The endpoint's application profile */
    uint16_t    deviceId;                               /*!< The endpoint's device ID within the application profile */
    uint8_t     appFlags;                               /*!< The device version and flags indicating description availability */
    uint8_t     inputClusterCount;                      /*!< The number of cluster IDs in inputClusterList */
    uint16_t    *inputClusterList;                      /*!< Input cluster IDs the endpoint will accept */
    uint8_t     outputClusterCount;                     /*!< The number of cluster IDs in outputClusterList */
    uint16_t    *outputClusterList;                     /*!< Output cluster IDs the endpoint will accept */
} esp_host_zb_endpoint_t;

/**
 * @brief Type to represent the user information for the callbacks.
 *
 */
typedef struct {
    uint32_t user_cb;                                   /*!< A ZDO match desc request callback */
    uint32_t user_ctx;                                  /*!< User information context */
} esp_zb_user_cb_t;

/**
 * @brief   Create the endpoint.
 * 
 * @param[in] endpoint   The endpoint information pointer
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 *
 */
esp_err_t esp_host_zb_ep_create(esp_host_zb_endpoint_t *endpoint);

/**
 * @brief   Process the frame ID payload.
 * 
 * @param[in] host_header The protocol frame header pointer
 * @param[in] buffer      The payload buffer pointer which match the frame ID
 * @param[in] len         The payload buffer length which match the frame ID
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 *
 */
esp_err_t esp_host_zb_input(esp_host_header_t *host_header, const void *buffer, uint16_t len);

/**
 * @brief   Output the frame ID payload.
 * 
 * @param[in] id         The frame ID
 * @param[in] buffer     The output payload pointer which match the frame ID
 * @param[in] len        The output payload length which match the frame ID
 * @param[in] output     The input payload pointer which match the frame ID
 * @param[out] len       The input payload length which match the frame ID
 * 
 * @return
 *    - ESP_OK: succeed
 *    - others: refer to esp_err.h
 *
 */
esp_err_t esp_host_zb_output(uint16_t id, const void *buffer, uint16_t len, void *output, uint16_t *outlen);

#ifdef __cplusplus
}
#endif
