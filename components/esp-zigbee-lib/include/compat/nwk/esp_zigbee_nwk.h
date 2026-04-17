/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/nwk.h" instead!"

#include <ezbee/nwk.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ZB_DEVICE_TYPE_COORDINATOR EZB_NWK_DEVICE_TYPE_COORDINATOR
#define ESP_ZB_DEVICE_TYPE_ROUTER      EZB_NWK_DEVICE_TYPE_ROUTER
#define ESP_ZB_DEVICE_TYPE_ED          EZB_NWK_DEVICE_TYPE_END_DEVICE
#define ESP_ZB_DEVICE_TYPE_NONE        EZB_NWK_DEVICE_TYPE_NONE
typedef ezb_nwk_device_type_t esp_zb_nwk_device_type_t;

#define ESP_ZB_NWK_COMMAND_STATUS_NO_ROUTE_AVAILABLE          EZB_NWK_NETWORK_STATUS_LEGACY_NO_ROUTE_AVAILABLE
#define ESP_ZB_NWK_COMMAND_STATUS_TREE_LINK_FAILURE           EZB_NWK_NETWORK_STATUS_LEGACY_LINK_FAILURE
#define ESP_ZB_NWK_COMMAND_STATUS_NONE_TREE_LINK_FAILURE      EZB_NWK_NETWORK_STATUS_LINK_FAILURE
#define ESP_ZB_NWK_COMMAND_STATUS_LOW_BATTERY_LEVEL           EZB_NWK_NETWORK_STATUS_LOW_BATTERY_LEVEL
#define ESP_ZB_NWK_COMMAND_STATUS_NO_ROUTING_CAPACITY         EZB_NWK_NETWORK_STATUS_NO_ROUTING_CAPACITY
#define ESP_ZB_NWK_COMMAND_STATUS_NO_INDIRECT_CAPACITY        EZB_NWK_NETWORK_STATUS_NO_INDIRECT_CAPACITY
#define ESP_ZB_NWK_COMMAND_STATUS_INDIRECT_TRANSACTION_EXPIRY EZB_NWK_NETWORK_STATUS_INDIRECT_TRANSACTION_EXPIRY
#define ESP_ZB_NWK_COMMAND_STATUS_TARGET_DEVICE_UNAVAILABLE   EZB_NWK_NETWORK_STATUS_TARGET_DEVICE_UNAVAILABLE
#define ESP_ZB_NWK_COMMAND_STATUS_TARGET_ADDRESS_UNALLOCATED  EZB_NWK_NETWORK_STATUS_TARGET_ADDRESS_UNALLOCATED
#define ESP_ZB_NWK_COMMAND_STATUS_PARENT_LINK_FAILURE         EZB_NWK_NETWORK_STATUS_PARENT_LINK_FAILURE
#define ESP_ZB_NWK_COMMAND_STATUS_VALIDATE_ROUTE              EZB_NWK_NETWORK_STATUS_VALIDATE_ROUTE
#define ESP_ZB_NWK_COMMAND_STATUS_SOURCE_ROUTE_FAILURE        EZB_NWK_NETWORK_STATUS_SOURCE_ROUTE_FAILURE
#define ESP_ZB_NWK_COMMAND_STATUS_MANY_TO_ONE_ROUTE_FAILURE   EZB_NWK_NETWORK_STATUS_MANY_TO_ONE_ROUTE_FAILURE
#define ESP_ZB_NWK_COMMAND_STATUS_ADDRESS_CONFLICT            EZB_NWK_NETWORK_STATUS_ADDRESS_CONFLICT
#define ESP_ZB_NWK_COMMAND_STATUS_VERIFY_ADDRESS              EZB_NWK_NETWORK_STATUS_VERIFY_ADDRESS
#define ESP_ZB_NWK_COMMAND_STATUS_PAN_IDENTIFIER_UPDATE       EZB_NWK_NETWORK_STATUS_PAN_IDENTIFIER_UPDATE
#define ESP_ZB_NWK_COMMAND_STATUS_NETWORK_ADDRESS_UPDATE      EZB_NWK_NETWORK_STATUS_NETWORK_ADDRESS_UPDATE
#define ESP_ZB_NWK_COMMAND_STATUS_BAD_FRAME_COUNTER           EZB_NWK_NETWORK_STATUS_BAD_FRAME_COUNTER
#define ESP_ZB_NWK_COMMAND_STATUS_BAD_KEY_SEQUENCE_NUMBER     EZB_NWK_NETWORK_STATUS_BAD_KEY_SEQUENCE_NUMBER
#define ESP_ZB_NWK_COMMAND_STATUS_UNKNOWN_COMMAND             EZB_NWK_NETWORK_STATUS_UNKNOWN_COMMAND
typedef ezb_nwk_network_status_t esp_zb_nwk_command_status_t;

#define ESP_ZB_ED_AGING_TIMEOUT_10SEC    EZB_NWK_ED_TIMEOUT_10SEC
#define ESP_ZB_ED_AGING_TIMEOUT_2MIN     EZB_NWK_ED_TIMEOUT_2MIN
#define ESP_ZB_ED_AGING_TIMEOUT_4MIN     EZB_NWK_ED_TIMEOUT_4MIN
#define ESP_ZB_ED_AGING_TIMEOUT_8MIN     EZB_NWK_ED_TIMEOUT_8MIN
#define ESP_ZB_ED_AGING_TIMEOUT_16MIN    EZB_NWK_ED_TIMEOUT_16MIN
#define ESP_ZB_ED_AGING_TIMEOUT_32MIN    EZB_NWK_ED_TIMEOUT_32MIN
#define ESP_ZB_ED_AGING_TIMEOUT_64MIN    EZB_NWK_ED_TIMEOUT_64MIN
#define ESP_ZB_ED_AGING_TIMEOUT_128MIN   EZB_NWK_ED_TIMEOUT_128MIN
#define ESP_ZB_ED_AGING_TIMEOUT_256MIN   EZB_NWK_ED_TIMEOUT_256MIN
#define ESP_ZB_ED_AGING_TIMEOUT_512MIN   EZB_NWK_ED_TIMEOUT_512MIN
#define ESP_ZB_ED_AGING_TIMEOUT_1024MIN  EZB_NWK_ED_TIMEOUT_1024MIN
#define ESP_ZB_ED_AGING_TIMEOUT_2048MIN  EZB_NWK_ED_TIMEOUT_2048MIN
#define ESP_ZB_ED_AGING_TIMEOUT_4096MIN  EZB_NWK_ED_TIMEOUT_4096MIN
#define ESP_ZB_ED_AGING_TIMEOUT_8192MIN  EZB_NWK_ED_TIMEOUT_8192MIN
#define ESP_ZB_ED_AGING_TIMEOUT_16384MIN EZB_NWK_ED_TIMEOUT_16384MIN
typedef ezb_nwk_ed_timeout_t esp_zb_aging_timeout_t;

#define ESP_ZB_NWK_INFO_ITERATOR_INIT EZB_NWK_INFO_ITERATOR_INIT
#define ESP_ZB_NWK_INFO_ITERATOR_EOT  EZB_NWK_INFO_ITERATOR_EOT

#define ESP_ZB_NWK_MAX_SOURCE_ROUTE   EZB_NWK_MAX_SOURCE_ROUTE


typedef ezb_nwk_info_iterator_t esp_zb_nwk_info_iterator_t;

#define ESP_ZB_NWK_RELATIONSHIP_PARENT                EZB_NWK_RELATIONSHIP_PARENT
#define ESP_ZB_NWK_RELATIONSHIP_CHILD                 EZB_NWK_RELATIONSHIP_CHILD
#define ESP_ZB_NWK_RELATIONSHIP_SIBLING               EZB_NWK_RELATIONSHIP_SIBLING
#define ESP_ZB_NWK_RELATIONSHIP_NONE_OF_THE_ABOVE     EZB_NWK_RELATIONSHIP_NONE_OF_THE_ABOVE
#define ESP_ZB_NWK_RELATIONSHIP_PREVIOUS_CHILD        (4U)
#define ESP_ZB_NWK_RELATIONSHIP_UNAUTHENTICATED_CHILD (5U)
typedef ezb_nwk_relationship_t esp_zb_nwk_relationship_t;

#define ESP_ZB_NWK_ROUTE_STATE_ACTIVE             EZB_NWK_ROUTE_STATE_ACTIVE
#define ESP_ZB_NWK_ROUTE_STATE_DISCOVERY_UNDERWAY EZB_NWK_ROUTE_STATE_DISCOVERY_UNDERWAY
#define ESP_ZB_NWK_ROUTE_STATE_DISCOVERY_FAILED   EZB_NWK_ROUTE_STATE_DISCOVERY_FAILED
#define ESP_ZB_NWK_ROUTE_STATE_INACTIVE           EZB_NWK_ROUTE_STATE_INACTIVE
typedef ezb_nwk_route_state_t esp_zb_nwk_route_state_t;

typedef struct esp_zb_nwk_neighbor_info_s {
    esp_zb_ieee_addr_t ieee_addr; /*!< Long address (EUI64) of the device. */
    ezb_shortaddr_t short_addr;   /*!< Short address (network address) of the device. */
    uint8_t device_type;          /*!< Neighbor device type, refer to @ref esp_zb_nwk_device_type_t */
    uint8_t depth;                /*!< The network depth of this device.*/
    uint8_t rx_on_when_idle;      /*!< Indicates if neighbour receiver enabled during idle periods:*/
    uint8_t relationship;         /*!< The relationship between the neighbour and current device, refer to @ref esp_zb_nwk_relationship_t */
    uint8_t lqi;                  /*!< Link quality. Also used to calculate incoming cost */
    int8_t rssi;                  /*!< Received signal strength indicator */
    uint8_t outgoing_cost;        /*!< The cost of an outgoing link. Got from link status. */
    uint8_t age;                  /*!< Counter value for router aging. The number of nwkLinkStatusPeriod
                                   *   intervals since a link status command was received. */
    uint32_t device_timeout;      /*!< Configured end device timeout, in seconds. */
    uint32_t timeout_counter;     /*!< Timeout value ED aging, in milliseconds. */
} esp_zb_nwk_neighbor_info_t;
typedef ezb_nwk_route_info_t esp_zb_nwk_route_info_t;
typedef ezb_nwk_route_record_info_t esp_zb_nwk_route_record_info_t;

#define esp_zb_set_rx_on_when_idle(rx_on)            ezb_nwk_set_rx_on_when_idle(rx_on)
#define esp_zb_get_rx_on_when_idle()                 ezb_nwk_get_rx_on_when_idle()
#define esp_zb_set_short_address(short_addr)         ezb_nwk_set_short_address(short_addr)
#define esp_zb_get_short_address()                   ezb_nwk_get_short_address()
#define esp_zb_set_pan_id(pan_id)                    ezb_nwk_set_panid(pan_id)
#define esp_zb_get_pan_id()                          ezb_nwk_get_panid()
#define esp_zb_get_current_channel()                 ezb_nwk_get_current_channel()
#define esp_zb_nwk_set_update_id(id)                 TO_ESP_ERR(ezb_nwk_set_update_id(id))
#define esp_zb_nwk_get_update_id()                   ezb_nwk_get_update_id()
#define esp_zb_nwk_set_frame_counter(frame_counter)  TO_ESP_ERR(ezb_nwk_set_frame_counter(frame_counter))
#define esp_zb_nwk_get_frame_counter()               ezb_nwk_get_frame_counter()
#define esp_zb_nwk_set_max_children(max_children)    TO_ESP_ERR(ezb_nwk_set_max_children(max_children))
#define esp_zb_nwk_get_max_children()                ezb_nwk_get_max_children()
#define esp_zb_set_network_device_role(role)         TO_ESP_ERR(ezb_nwk_set_device_type(role))
#define esp_zb_get_network_device_role()             ezb_nwk_get_device_type()
#define esp_zb_nwk_get_link_status_period()          ezb_nwk_get_link_status_period()
#define esp_zb_nwk_set_link_status_period(period)    TO_ESP_ERR(ezb_nwk_set_link_status_period(period))
#define esp_zb_nwk_get_next_neighbor(itor, info)     TO_ESP_ERR(ezb_nwk_get_next_neighbor(itor, (ezb_nwk_neighbor_info_t *)info))
#define esp_zb_nwk_get_next_route(itor, info)        TO_ESP_ERR(ezb_nwk_get_next_route(itor, info))
#define esp_zb_nwk_get_next_route_record(itor, info) TO_ESP_ERR(ezb_nwk_get_next_route_record(itor, info))

#define esp_zb_set_default_long_poll_interval(milliseconds) ezb_nwk_set_keepalive_interval(milliseconds)
#define esp_zb_get_default_long_poll_interval()             ezb_nwk_get_keepalive_interval()

static inline esp_err_t esp_zb_set_long_address(const esp_zb_ieee_addr_t addr)
{
    ezb_nwk_set_extended_address((const ezb_extaddr_t *)addr);
    return ESP_OK;
}

static inline void esp_zb_get_long_address(esp_zb_ieee_addr_t addr)
{
    ezb_nwk_get_extended_address((ezb_extaddr_t *)addr);
}

static inline void esp_zb_set_extended_pan_id(const esp_zb_ext_pan_id_t ext_pan_id)
{
    ezb_set_use_extended_panid((const ezb_extpanid_t *)ext_pan_id);
}

static inline void esp_zb_get_extended_pan_id(esp_zb_ext_pan_id_t ext_pan_id)
{
    ezb_nwk_get_extended_panid((ezb_extpanid_t *)ext_pan_id);
}

static inline ezb_shortaddr_t esp_zb_address_short_by_ieee(const esp_zb_ieee_addr_t ieee_addr)
{
    ezb_shortaddr_t short_addr = EZB_NWK_ADDR_UNKNOWN;

    ezb_address_short_by_extended((const ezb_extaddr_t *)ieee_addr, &short_addr);

    return short_addr;
}

static inline esp_err_t esp_zb_ieee_address_by_short(ezb_shortaddr_t short_addr, esp_zb_ieee_addr_t ieee_addr)
{
    return TO_ESP_ERR(ezb_address_extended_by_short(short_addr, (ezb_extaddr_t *)ieee_addr));
}

#ifdef __cplusplus
} /*  extern "C" */
#endif

#else
#error "This file is for compatibility, please include "ezbee/nwk.h"!"
#endif
