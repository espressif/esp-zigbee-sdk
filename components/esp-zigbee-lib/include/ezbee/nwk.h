/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_NWK_H
#define ESP_ZIGBEE_NWK_H

#include <ezbee/core.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EZB_NWK_ADDR_UNKNOWN 0xFFFFU /*!< Unknown address */

/**
 * @brief Enum of the Zigbee network device type
 * @anchor ezb_nwk_device_type_t
 */
typedef enum {
    EZB_NWK_DEVICE_TYPE_COORDINATOR = 0x0, /*!< Device - Coordinator */
    EZB_NWK_DEVICE_TYPE_ROUTER      = 0x1, /*!< Device - Router */
    EZB_NWK_DEVICE_TYPE_END_DEVICE  = 0x2, /*!< Device - End device */
    EZB_NWK_DEVICE_TYPE_NONE        = 0x3, /*!< Unknown device type */
} ezb_nwk_device_type_t;

/**
 * @brief Enumeration of Zigbee network command status code
 * @anchor ezb_nwk_network_status_t
 */
typedef enum {
    EZB_NWK_NETWORK_STATUS_LEGACY_NO_ROUTE_AVAILABLE   = 0x00U, /*!< No route available */
    EZB_NWK_NETWORK_STATUS_LEGACY_LINK_FAILURE         = 0x01U, /*!< Tree link failure */
    EZB_NWK_NETWORK_STATUS_LINK_FAILURE                = 0x02U, /*!< None-tree link failure */
    EZB_NWK_NETWORK_STATUS_LOW_BATTERY_LEVEL           = 0x03U, /*!< Low battery level */
    EZB_NWK_NETWORK_STATUS_NO_ROUTING_CAPACITY         = 0x04U, /*!< No routing capacity */
    EZB_NWK_NETWORK_STATUS_NO_INDIRECT_CAPACITY        = 0x05U, /*!< No indirect capacity */
    EZB_NWK_NETWORK_STATUS_INDIRECT_TRANSACTION_EXPIRY = 0x06U, /*!< Indirect transaction expiry */
    EZB_NWK_NETWORK_STATUS_TARGET_DEVICE_UNAVAILABLE   = 0x07U, /*!< Target device unavailable */
    EZB_NWK_NETWORK_STATUS_TARGET_ADDRESS_UNALLOCATED  = 0x08U, /*!< Target address unallocated */
    EZB_NWK_NETWORK_STATUS_PARENT_LINK_FAILURE         = 0x09U, /*!< Parent link failure */
    EZB_NWK_NETWORK_STATUS_VALIDATE_ROUTE              = 0x0aU, /*!< Validate route */
    EZB_NWK_NETWORK_STATUS_SOURCE_ROUTE_FAILURE        = 0x0bU, /*!< Source route failure */
    EZB_NWK_NETWORK_STATUS_MANY_TO_ONE_ROUTE_FAILURE   = 0x0cU, /*!< Many-to-one route failure */
    EZB_NWK_NETWORK_STATUS_ADDRESS_CONFLICT            = 0x0dU, /*!< Address conflict */
    EZB_NWK_NETWORK_STATUS_VERIFY_ADDRESS              = 0x0eU, /*!< Verify address */
    EZB_NWK_NETWORK_STATUS_PAN_IDENTIFIER_UPDATE       = 0x0fU, /*!< Pan ID update */
    EZB_NWK_NETWORK_STATUS_NETWORK_ADDRESS_UPDATE      = 0x10U, /*!< Network address update */
    EZB_NWK_NETWORK_STATUS_BAD_FRAME_COUNTER           = 0x11U, /*!< Bad frame counter */
    EZB_NWK_NETWORK_STATUS_BAD_KEY_SEQUENCE_NUMBER     = 0x12U, /*!< Bad key sequence number */
    EZB_NWK_NETWORK_STATUS_UNKNOWN_COMMAND             = 0x13U, /*!< Command received is not known */
    EZB_NWK_NETWORK_STATUS_PANID_CONFLICT              = 0x14U, /*!< PAN ID conflict */
} ezb_nwk_network_status_t;

/**
 * @brief End Device (ED) timeout request
 * @anchor ezb_nwk_ed_timeout_e
 */
enum ezb_nwk_ed_timeout_e {
    EZB_NWK_ED_TIMEOUT_10SEC    = 0U,  /*!< 10 seconds */
    EZB_NWK_ED_TIMEOUT_2MIN     = 1U,  /*!< 2 minutes */
    EZB_NWK_ED_TIMEOUT_4MIN     = 2U,  /*!< 4 minutes */
    EZB_NWK_ED_TIMEOUT_8MIN     = 3U,  /*!< 8 minutes */
    EZB_NWK_ED_TIMEOUT_16MIN    = 4U,  /*!< 16 minutes */
    EZB_NWK_ED_TIMEOUT_32MIN    = 5U,  /*!< 32 minutes */
    EZB_NWK_ED_TIMEOUT_64MIN    = 6U,  /*!< 64 minutes */
    EZB_NWK_ED_TIMEOUT_128MIN   = 7U,  /*!< 128 minutes */
    EZB_NWK_ED_TIMEOUT_256MIN   = 8U,  /*!< 256 minutes */
    EZB_NWK_ED_TIMEOUT_512MIN   = 9U,  /*!< 512 minutes */
    EZB_NWK_ED_TIMEOUT_1024MIN  = 10U, /*!< 1024 minutes */
    EZB_NWK_ED_TIMEOUT_2048MIN  = 11U, /*!< 2048 minutes */
    EZB_NWK_ED_TIMEOUT_4096MIN  = 12U, /*!< 4096 minutes */
    EZB_NWK_ED_TIMEOUT_8192MIN  = 13U, /*!< 8192 minutes */
    EZB_NWK_ED_TIMEOUT_16384MIN = 14U, /*!< 16384 minutes */
};

/**
 * @brief Represent the End Device (ED) timeout value, @ref ezb_nwk_ed_timeout_e
 */
typedef uint8_t ezb_nwk_ed_timeout_t;

#define EZB_NWK_INFO_ITERATOR_INIT NULL    /*!< Initializer for ezb_neighbor_info_iterator_t. */
#define EZB_NWK_INFO_ITERATOR_EOT  NULL    /*!< Indicate the iterator reach the End of Table. */

#define EZB_NWK_MAX_SOURCE_ROUTE (12U)

/**
 * @brief Iterator used to iterate through the tables of network information.
 *
 */
typedef void* ezb_nwk_info_iterator_t;

/**
 * @brief Relationship of network neighbor
 * @anchor ezb_nwk_relationship_t
 */
typedef enum {
    EZB_NWK_RELATIONSHIP_PARENT                = 0U, /*!< The peer device is the parent of current device. */
    EZB_NWK_RELATIONSHIP_CHILD                 = 1U, /*!< The peer device is the child of current device. */
    EZB_NWK_RELATIONSHIP_SIBLING               = 2U, /*!< The peer device is the sibling of current device. */
    EZB_NWK_RELATIONSHIP_NONE_OF_THE_ABOVE     = 3U, /*!< The relationship is none of above. */
} ezb_nwk_relationship_t;

/**
 * @brief Information of network neighbor table entry
 *
 */
typedef struct ezb_nwk_neighbor_info_s {
    ezb_extaddr_t ieee_addr; /*!< Long address (EUI64) of the device. */
    ezb_shortaddr_t short_addr;   /*!< Short address (network address) of the device. */
    uint8_t device_type;          /*!< Neighbor device type, refer to @ref ezb_nwk_device_type_t */
    uint8_t depth;                /*!< The network depth of this device.*/
    uint8_t rx_on_when_idle;      /*!< Indicates if neighbour receiver enabled during idle periods:*/
    uint8_t relationship;         /*!< The relationship between the neighbour and current device, refer to @ref ezb_nwk_relationship_t */
    uint8_t lqi;                  /*!< Link quality. Also used to calculate incoming cost */
    int8_t rssi;                  /*!< Received signal strength indicator */
    uint8_t outgoing_cost;        /*!< The cost of an outgoing link. Got from link status. */
    uint8_t age;                  /*!< Counter value for router aging. The number of nwkLinkStatusPeriod
                                   * intervals since a link status command was received. */
    uint32_t device_timeout;      /*!< Configured end device timeout, in seconds. */
    uint32_t timeout_counter;     /*!< Timeout value ED aging, in milliseconds. */
} ezb_nwk_neighbor_info_t;

/**
 * @brief State of the network route
 * @anchor ezb_nwk_route_state_t
 */
typedef enum {
    EZB_NWK_ROUTE_STATE_ACTIVE               = 0U, /*!< The route is active. */
    EZB_NWK_ROUTE_STATE_DISCOVERY_UNDERWAY   = 1U, /*!< The route is under discovery process. */
    EZB_NWK_ROUTE_STATE_DISCOVERY_FAILED     = 2U, /*!< The discovery process failed of this route. */
    EZB_NWK_ROUTE_STATE_INACTIVE             = 3U, /*!< The route is inactive and under validation. */
} ezb_nwk_route_state_t;

/**
 * @brief Information of network routing table entry
 *
 */
typedef struct ezb_nwk_route_info_s {
    ezb_shortaddr_t dest_addr;     /*!< 16-bit network address of the destination. */
    ezb_shortaddr_t next_hop_addr; /*!< 16-bit network address of the next hop on the way to the destination. */
    uint8_t expiry;                /*!< Expiration time. */
    struct {
        uint8_t status                : 3;  /*!< The status of the route, bit 0 - 2, refer to ezb_nwk_route_state_t */
        uint8_t no_route_cache        : 1;  /*!< Dest does not store source routes, bit 3 */
        uint8_t many_to_one           : 1;  /*!< Dest is the concentrator and many-to-one request was used, bit 4 */
        uint8_t route_record_required : 1;  /*!< Route record command frame should be sent
                                             *   to the dest prior to the next data packet, bit 5 */
        EZB_DEPRECATED
        uint8_t group_id              : 1;  /*!< @deprecated */
        uint8_t /* reserved */        : 1;  /*!< Reserved, bit 7 */
    } flags;                                /*!< Flags in the routing table entry */
} ezb_nwk_route_info_t;

/**
 * @brief Information of network route record table entry
 *
 */
typedef struct ezb_nwk_route_record_info_s {
    ezb_shortaddr_t dest_address;            /*!< Destination network address of this route record. */
    uint8_t expiry;                             /*!< Expiration time. */
    uint8_t relay_count;                        /*!< The count of relay nodes from concentrator to the destination. */
    ezb_shortaddr_t path[EZB_NWK_MAX_SOURCE_ROUTE]; /*!< The set of network addresses that represent the route
                                                     *   in order from the concentrator to the destination.*/
} ezb_nwk_route_record_info_t;

/**
 * @brief Set the network update id
 *
 * @param[in] id The network update id is expected to be set
 * @return
 *      - EZB_ERR_NONE: On success
 *      - EZB_ERR_INV_STATE: Device is already on a network
 */
ezb_err_t ezb_nwk_set_update_id(uint8_t id);

/**
 * @brief Get the network update id
 *
 * @return The network update id
 */
uint8_t ezb_nwk_get_update_id(void);

/**
 * @brief Set the network outgoing frame counter
 *
 * @param[in] frame_counter The network frame counter value is expect to be set
 * @return
 *      - EZB_ERR_NONE: On success
 *      - EZB_ERR_INV_STATE: Device is already on a network
 */
ezb_err_t ezb_nwk_set_frame_counter(uint32_t frame_counter);

/**
 * @brief Get the current network outgoing frame counter
 *
 * @return The network outgoing frame counter
 */
uint32_t ezb_nwk_get_frame_counter(void);

/**
 * @brief Enable/Disable Rx when device is in IDLE state.
 * @anchor ezb_nwk_set_rx_on_when_idle
 *
 * @param[in] rx_on True - Rx remains on during idle periods, False - Rx is put to sleep during idle periods.
 */
void ezb_nwk_set_rx_on_when_idle(bool rx_on);

/**
 * @brief Get the current state of RxOnWhenIdle.
 * @anchor ezb_nwk_get_rx_on_when_idle
 *
 * @return The state of RxOnWhenIdle.
 */
bool ezb_nwk_get_rx_on_when_idle(void);

/**
 * @brief Set the maximum number of children allowed.
 *
 * The function only takes effect on ZC/ZR.
 *
 * @param[in] max_children Maximum number of children.
 *
 * @return
 *      - EZB_ERR_NONE: On success
 *      - EZB_ERR_NOT_SUPPORTED: for ZED.
 *
 */
ezb_err_t ezb_nwk_set_max_children(uint8_t max_children);

/**
 * @brief Get the maximum number of children allowed.
 *
 * @return
 *      - Maximum number of children, for ZC/ZR
 *      - 0, for ZED
 *
 */
uint8_t ezb_nwk_get_max_children(void);

/**
 * @brief Set the IEEE (extended) address of the device.
 * @anchor ezb_nwk_set_extended_address
 *
 * @note Set this function AFTER @ref ezb_core_init called, if user wants to set specific address
 *       which is different from the MAC address.
 *
 * @param[in] extaddr The pointer to the 64-bit of IEEE address, in little-endian.
 */
void ezb_nwk_set_extended_address(const ezb_extaddr_t *extaddr);

/**
 * @brief Get the IEEE (extended) address of the device.
 * @anchor ezb_nwk_get_extended_address
 *
 * @param[out] extaddr The pointer to the 64-bit of IEEE address, in little-endian.
 */
void ezb_nwk_get_extended_address(ezb_extaddr_t *extaddr);

/**
 * @brief Set the network (short) address of the device.
 * @anchor ezb_nwk_set_short_address
 *
 * @param[in] short_addr The 16-bit network (short) address.
 */
void ezb_nwk_set_short_address(ezb_shortaddr_t short_addr);

/**
 * @brief Get the network (short) address of the device.
 * @anchor ezb_nwk_get_short_address
 *
 * @return 16-bit Zigbee short address, in little-endian.
 */
ezb_shortaddr_t ezb_nwk_get_short_address(void);

/**
 * @brief Set the extended PAN ID of the network.
 * @anchor ezb_nwk_set_extended_panid
 *
 * @note Please do not use this function to set the extended PAN ID, use @ref ezb_set_use_extended_panid instead.
 *
 * @param[in] extpanid The pointer to the 64-bit of extended PAN ID, in little-endian.
 */
void ezb_nwk_set_extended_panid(const ezb_extpanid_t *extpanid);

/**
 * @brief Get the extended PAN ID of the network.
 * @anchor ezb_nwk_get_extended_panid
 *
 * @param[out] extpanid The pointer to the 64-bit of extended PAN ID, in little-endian.
 */
void ezb_nwk_get_extended_panid(ezb_extpanid_t *extpanid);

/**
 * @brief Set the PAN ID of the network.
 * @anchor ezb_nwk_set_panid
 *
 * @note The PAN ID will be set from the network PIB to the IEEE802154 PIB
 *
 * @param[in] panid The 16-bit of PAN ID, in little-endian.
 */
void ezb_nwk_set_panid(ezb_panid_t panid);

/**
 * @brief Get the PAN ID of the network.
 * @anchor ezb_nwk_get_panid
 *
 * @return 16-bit PAN ID, in little-endian.
 */
ezb_panid_t ezb_nwk_get_panid(void);

/**
 * @brief Get the currently used channel.
 * @anchor ezb_nwk_get_current_channel
 *
 * @return 8-bit Zigbee network channel number
 */
uint8_t ezb_nwk_get_current_channel(void);

/**
 * @brief Set the tx power.
 * @anchor ezb_nwk_set_tx_power
 *
 * @param[in] power The tx power in dBm.
 */
void ezb_nwk_set_tx_power(int8_t power);

/**
 * @brief Get the tx power.
 * @anchor ezb_nwk_get_tx_power
 *
 * @param[out] power The tx power in dBm.
 */
void ezb_nwk_get_tx_power(int8_t *power);

/**
 * @brief  Get the short address by IEEE (extended) address
 *
 * @param[in]  extaddr   The 64-bit IEEE (extended) address of a known device.
 * @param[out] shortaddr The 16-bit short address of the device.
 *
 * @return
 *      - EZB_ERR_NONE: on success
 *      - EZB_ERR_NOT_FOUND: The mapped short address is not found
 */
ezb_err_t ezb_address_short_by_extended(const ezb_extaddr_t *extaddr, ezb_shortaddr_t *shortaddr);

/**
 * @brief Get the IEEE (extended) address by the short address
 *
 * @param[in]  shortaddr The 16-bit short address of a known device.
 * @param[out] extaddr   The 64-bit IEEE (extended) address of the device.
 *
 * @return
 *      - EZB_ERR_NONE: on success
 *      - EZB_ERR_NOT_FOUND: The mapped IEEE (extended) address is not found
 */
ezb_err_t ezb_address_extended_by_short(ezb_shortaddr_t shortaddr, ezb_extaddr_t *extaddr);

/**
 * @brief Set the Zigbee network device role
 *
 * @param[in] role The network device role is expected to be set
 * @return
 *      - EZB_ERR_NONE: On success
 *      - EZB_ERR_INV_STATE: Device is already on a network
 *      - EZB_ERR_INV_ARG: Invalid device role
 */
ezb_err_t ezb_nwk_set_device_type(ezb_nwk_device_type_t role);

/**
 * @brief   Get the Zigbee network device type.
 *
 * @return device type @ref ezb_nwk_device_type_t
 *
 */
ezb_nwk_device_type_t ezb_nwk_get_device_type(void);

/**
 * @brief Set the End Device (ED) timeout
 *
 * @note For ZC/ZR, the value indicates the duration of missing keepalive messages before aging out the end device.
 *       For ZED, the value indicates the duration of failed keepalive process before it is considered as lost links
 *       to its parent.
 *
 * @param[in] timeout The End Device (ED) timeout value, @ref ezb_nwk_ed_timeout_e
 */
void ezb_nwk_set_ed_timeout(ezb_nwk_ed_timeout_t timeout);

/**
 * @brief Get the End Device timeout value.
 *
 * @return The End Device timeout value, @ref ezb_nwk_ed_timeout_e
 */
ezb_nwk_ed_timeout_t ezb_nwk_get_ed_timeout(void);

/**
 * @brief Set the interval of keepalive process on End Device.
 *
 * @note This function is only available for End Device. By default, this is set to 1/4 of the ED timeout.
 *
 * @param[in] interval The keepalive interval, in milliseconds.
 */
void ezb_nwk_set_keepalive_interval(uint32_t interval);

/**
 * @brief Get the keepalive interval for the End Device.
 *
 * @note This function is only available for End Device.
 *
 * @return The keepalive interval, in milliseconds.
 */
uint32_t ezb_nwk_get_keepalive_interval(void);

/**
 * @brief Set the interval of fast poll process on Sleepy End Device (SED).
 *
 * @note This function is only available for End Device. By default, this is set to 200 milliseconds.
 *
 * @param[in] interval The fast poll interval, in milliseconds.
 */
void ezb_nwk_set_fast_poll_interval(uint32_t interval);

/**
 * @brief Get the fast poll interval for the Sleepy End Device (SED).
 *
 * @note This function is only available for Sleepy End Device (SED).
 *
 * @return The fast poll interval, in milliseconds.
 */
uint32_t ezb_nwk_get_fast_poll_interval(void);

/**
 * @brief  Iterate through the neighbor table and get information about active neighbor
 *
 * @param[in] iterator iterator used to iterate through neighbor table, refer to ezb_nwk_info_iterator_t
 * @param[out] nbr_info next neighbor information, @ref ezb_nwk_neighbor_info_s
 *
 * @return - EZB_ERR_NONE on success
 *         - EZB_ERR_NOT_FOUND on finish iteration
 *         - EZB_ERR_INV_ARG if arguments are invalid
 *
 */
ezb_err_t ezb_nwk_get_next_neighbor(ezb_nwk_info_iterator_t *iterator, ezb_nwk_neighbor_info_t *nbr_info);

/**
 * @brief  Iterate through the routing table and get the information in the entry
 *
 * @param[in] iterator iterator used to iterate through routing table, refer to ezb_nwk_info_iterator_t
 * @param[out] route_info next route entry information, @ref ezb_nwk_route_info_s
 *
 * @return - EZB_ERR_NONE on success
 *         - EZB_ERR_NOT_FOUND on finish iteration
 *         - EZB_ERR_INV_ARG if arguments are invalid
 *
 */
ezb_err_t ezb_nwk_get_next_route(ezb_nwk_info_iterator_t *iterator, ezb_nwk_route_info_t *route_info);

/**
 * @brief  Iterate through the route record table (a.k.a source route table) and get the information in the entry
 *
 * @param[in] iterator iterator used to iterate through routing table, refer to ezb_nwk_info_iterator_t
 * @param[out] route_record_info next route record entry information, @ref ezb_nwk_route_record_info_s
 *
 * @return - EZB_ERR_NONE on success
 *         - EZB_ERR_NOT_FOUND on finish iteration
 *         - EZB_ERR_INV_ARG if arguments are invalid
 *
 */
ezb_err_t ezb_nwk_get_next_route_record(ezb_nwk_info_iterator_t *iterator, ezb_nwk_route_record_info_t *route_record_info);

/**
 * @brief  Get the nwkLinkStatusPeriod attribute in NIB
 *
 * @return The time in seconds between link status command frames.
 *
 */
uint8_t ezb_nwk_get_link_status_period(void);

/**
 * @brief  Set the nwkLinkStatusPeriod attribute in NIB
 *
 * @param[in] period The time in seconds between link status command frames.
 *
 * @return - EZB_ERR_NONE on success, error code otherwise.
 *
 */
ezb_err_t ezb_nwk_set_link_status_period(uint8_t period);

/**
 * @brief  Get the minimum LQI value for device joining the network
 *
 * @return The minimum LQI value
 */
uint8_t ezb_nwk_get_min_join_lqi(void);

/**
 * @brief Set the minimum LQI value for device joining the network
 *
 * @param[in] lqi The minimum LQI value
 *
 */
void ezb_nwk_set_min_join_lqi(uint8_t lqi);

/**
 * @brief Convert the network status to string.
 *
 * @param[in] status The network status to convert, @ref ezb_nwk_network_status_t
 *
 * @return The string representation of the network status
 */
const char *ezb_nwk_network_status_to_string(ezb_nwk_network_status_t status);

/**
 * @brief Enumeration of network scan types
 * @anchor ezb_nwk_scan_type_t
 */
enum ezb_nwk_scan_type_e {
    EZB_NWK_SCAN_TYPE_ED = 0,     /*!< Energy detection */
    EZB_NWK_SCAN_TYPE_ACTIVE,     /*!< Active scan */
    EZB_NWK_SCAN_TYPE_MAX_NR,     /*!< Maximum number of scan types */
};

/**
 * @brief Represent the network scan type
 */
typedef uint8_t ezb_nwk_scan_type_t;

/**
 * @brief Information of active scan result (beacon)
 */
typedef struct ezb_nwk_active_scan_result_s {
    ezb_shortaddr_t shortaddr;         /*!< Short address of the router */
    ezb_panid_t panid;                 /*!< PAN ID of the network */
    ezb_extpanid_t extpanid;           /*!< Extended PAN ID of the network */
    uint8_t channel_page;              /*!< Channel page of the network */
    uint8_t channel_number;            /*!< Channel number of the network */
    uint8_t nwk_update_id;             /*!< Network update ID */
    uint8_t stack_profile    : 4;      /*!< Stack profile */
    uint8_t protocol_version : 4;      /*!< Protocol version */
    bool permit_join : 1;              /*!< Indicate if it permits joining */
    bool router_capacity : 1;          /*!< Indicate if it is capable to accept router's joining request */
    bool enddev_capacity : 1;          /*!< Indicate if it is capable to accept end device's joining request */
} ezb_nwk_active_scan_result_t;

/**
 * @brief Information of energy detection scan result
 */
typedef struct ezb_nwk_ed_scan_result_s {
    uint8_t channel_page;              /*!< Channel page of the scanned channel */
    uint8_t channel_number;            /*!< Channel number of the scanned channel */
    int8_t max_rssi;                   /*!< Maximum RSSI value, the detected energy */
} ezb_nwk_ed_scan_result_t;

/**
 * @brief Callback function for active scan.
 *
 * @note It will be called when a active scan result is available (beacon is received) or the scan is finished.
 *
 * @param[in] result   The active scan result, @ref ezb_nwk_active_scan_result_s, or NULL if the scan is finished.
 * @param[in] user_ctx The user context
 */
typedef void (*ezb_nwk_active_scan_callback_t)(ezb_nwk_active_scan_result_t *result, void *user_ctx);

/**
 * @brief Callback function for energy detection scan.
 *
 * @note It will be called when a energy detection scan result is available (ED finished on channel) or the scan is finished.
 *
 * @param[in] result   The energy detection scan result, @ref ezb_nwk_ed_scan_result_s, or NULL if the scan is finished.
 * @param[in] user_ctx The user context
 */
typedef void (*ezb_nwk_ed_scan_callback_t)(ezb_nwk_ed_scan_result_t *result, void *user_ctx);

/**
 * @brief Request for network scan
 */
typedef struct ezb_nwk_scan_req_s {
    ezb_nwk_scan_type_t scan_type;  /*!< Scan type, @ref ezb_nwk_scan_type_t */
    uint8_t scan_duration;          /*!< Scan duration, time spent scanning each channel,
                                     *   (2^n + 1) * BeaconInterval(15.36 ms). */
    uint32_t scan_channels;         /*!< Scan channels, bitmask of the channels to scan */
    union {
        ezb_nwk_active_scan_callback_t active_scan_cb; /*!< Callback function for active scan. */
        ezb_nwk_ed_scan_callback_t ed_scan_cb;         /*!< Callback function for energy detection scan. */
    };
    void *user_ctx;                                    /*!< The user context for the callback functions. */
} ezb_nwk_scan_req_t;

/**
 * @brief Request for network scan
 *
 * @param[in] req The network scan request, @ref ezb_nwk_scan_req_s
 *
 * @return - EZB_ERR_NONE on success, error code otherwise.
 */
ezb_err_t ezb_nwk_scan(const ezb_nwk_scan_req_t *req);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_NWK_H */
