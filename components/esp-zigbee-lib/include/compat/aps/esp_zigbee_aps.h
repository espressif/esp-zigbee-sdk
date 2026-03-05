/*
 * SPDX-FileCopyrightText: 2023-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/aps.h" instead!"

#include <ezbee/aps.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT   EZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT
#define ESP_ZB_APS_ADDR_MODE_16_GROUP_ENDP_NOT_PRESENT   EZB_APS_ADDR_MODE_16_GROUP_ENDP_NOT_PRESENT
#define ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT             EZB_APS_ADDR_MODE_16_ENDP_PRESENT
#define ESP_ZB_APS_ADDR_MODE_64_ENDP_PRESENT             EZB_APS_ADDR_MODE_64_ENDP_PRESENT
#define ESP_ZB_APS_ADDR_MODE_64_PRESENT_ENDP_NOT_PRESENT (0x04U)
typedef ezb_aps_address_mode_t esp_zb_aps_address_mode_t;

#define ESP_ZB_APSDE_TX_OPT_SECURITY_ENABLED        EZB_APSDE_TX_OPT_SECURITY_ENABLED
#define ESP_ZB_APSDE_TX_OPT_USE_NWK_KEY_R21OBSOLETE EZB_APSDE_TX_OPT_USE_NWK_KEY_R21OBSOLETE
#define ESP_ZB_APSDE_TX_OPT_ACK_TX                  EZB_APSDE_TX_OPT_ACK_TX
#define ESP_ZB_APSDE_TX_OPT_FRAG_PERMITTED          EZB_APSDE_TX_OPT_FRAG_PERMITTED
#define ESP_ZB_APSDE_TX_OPT_INC_EXT_NONCE           EZB_APSDE_TX_OPT_INC_EXT_NONCE
typedef ezb_apsde_tx_opt_t esp_zb_apsde_tx_opt_t;

#define ESP_ZB_APSME_STANDARD_NETWORK_KEY EZB_APSME_STANDARD_NETWORK_KEY
#define ESP_ZB_APSME_APP_LINK_KEY         EZB_APSME_APP_LINK_KEY
#define ESP_ZB_APSME_TC_LINK_KEY          EZB_APSME_TC_LINK_KEY
typedef ezb_apsme_key_type_t esp_zb_apsme_key_type_t;

typedef struct esp_zb_apsde_data_req_s {
    uint8_t dst_addr_mode;   /*!< The addressing mode for the destination address used in this primitive and of the APDU to be transferred,
                                  refer to esp_zb_aps_address_mode_t */
    esp_zb_addr_u dst_addr;  /*!< The individual device address or group address of the entity to which the ASDU is being transferred*/
    uint8_t src_endpoint;    /*!< The individual endpoint of the entity from which the ASDU is being transferred.*/
    uint8_t dst_endpoint;    /*!< The number of the individual endpoint of the entity to which the ASDU is being transferred or the broadcast endpoint (0xff).*/
    uint16_t cluster_id;     /*!< The identifier of the object for which this frame is intended. */
    uint16_t profile_id;     /*!< The identifier of the profile for which this frame is intended. */

    uint8_t radius;          /*!< The distance, in hops, that a transmitted frame will be allowed to travel through the network.*/

    uint8_t  alias_seq_num;  /*!< The sequence number to be used for this NSDU. If the use_alias is true */
    uint16_t alias_src_addr; /*!< The source address to be used for this NSDU. If the use_alias is true */

    uint8_t tx_options;      /*!< The transmission options for the ASDU to be transferred, refer to esp_zb_apsde_tx_opt_t */
    bool    use_alias;       /*!< The next higher layer may use the UseAlias parameter to request alias usage by NWK layer for the current frame. */

    uint16_t asdu_length;    /*!< The number of octets comprising the ASDU to be transferred */
    uint8_t *asdu;           /*!< The set of octets comprising the ASDU to be transferred. */
} esp_zb_apsde_data_req_t;

typedef struct esp_zb_apsde_data_confirm_s {
    uint8_t dst_addr_mode;  /*!< The addressing mode for the destination address used in this primitive and of the APDU to be transferred,
                                 refer to esp_zb_aps_address_mode_t */
    esp_zb_addr_u dst_addr; /*!< The individual device address or group address of the entity to which the ASDU is being transferred.*/
    uint8_t src_endpoint;   /*!< The individual endpoint of the entity from which the ASDU was being transferred.*/
    uint8_t dst_endpoint;   /*!< The number of the individual endpoint of the entity to which the ASDU was being transferred or the broadcast endpoint (0xff).*/
    uint16_t cluster_id;    /*!< The identifier of the object for which this frame was intended. */
    uint16_t profile_id;    /*!< The identifier of the profile for which this frame was intended. */

    uint8_t status;         /*!< The status of data confirm. 0: success, otherwise failed */

    uint16_t asdu_length;   /*!< The number of octets comprising the ASDU was transferred */
    uint8_t *asdu;          /*!< The set of octets comprising the ASDU was transferred. */
} esp_zb_apsde_data_confirm_t;

typedef struct esp_zb_apsde_data_ind_s {
    uint8_t dst_addr_mode;      /*!< The addressing mode for the destination address used in this primitive and of the APDU that has been received,
                                     refer to esp_zb_aps_address_mode_t */
    union {
        uint16_t dst_short_addr;    /*!< The individual device address or group address to which the ASDU is directed.*/
        ezb_addr_t dst_addr;
    };
    uint8_t src_addr_mode;      /*!< Reserved, The addressing mode for the source address used in this primitive and of the APDU that has been received.*/
    union {
        uint16_t src_short_addr;    /*!< The individual device address of the entity from which the ASDU has been received.*/
        ezb_addr_t src_addr;
    };
    uint8_t dst_endpoint;       /*!< The target endpoint on the local entity to which the ASDU is directed.*/
    uint8_t src_endpoint;       /*!< The number of the individual endpoint of the entity from which the ASDU has been received.*/
    uint16_t cluster_id;        /*!< The identifier of the received object.*/
    uint16_t profile_id;        /*!< The identifier of the profile from which this frame originated.*/

    uint8_t status;             /*!< The status of the incoming frame processing, 0: on success */
    uint8_t security_status;    /*!< UNSECURED if the ASDU was received without any security. SECURED_NWK_KEY if the received ASDU was secured with the NWK key. */
    uint8_t key_index;          /*!< This value is only valid when SecurityStatus is set to SECURED_LINK_KEY.*/
    uint8_t lqi;                /*!< The link quality indication delivered by the NLDE.*/

    uint16_t asdu_length;       /*!< The number of octets comprising the ASDU being indicated by the APSDE.*/
    uint8_t *asdu;              /*!< The set of octets comprising the ASDU being indicated by the APSDE. */
} esp_zb_apsde_data_ind_t;

typedef bool (*esp_zb_apsde_data_indication_callback_t)(esp_zb_apsde_data_ind_t ind);
typedef void (*esp_zb_apsde_data_confirm_callback_t)(esp_zb_apsde_data_confirm_t confirm);

void esp_zb_aps_data_indication_handler_register(esp_zb_apsde_data_indication_callback_t cb);
void esp_zb_aps_data_confirm_handler_register(esp_zb_apsde_data_confirm_callback_t cb);

static inline esp_err_t esp_zb_aps_data_request(const esp_zb_apsde_data_req_t *req)
{
    ezb_apsde_data_req_t *data_req = (ezb_apsde_data_req_t *)req;
    if (data_req->dst_address.addr_mode == EZB_ADDR_MODE_GROUP) {
        data_req->dst_address.u.group_addr.bcast = 0xfffd; /* Group to RxOnWhenIdle devices  */
    }
    if (req->use_alias) {
        data_req->tx_options |= EZB_APSDE_TX_OPT_USE_ALIAS;
    } else {
        data_req->tx_options &= ~EZB_APSDE_TX_OPT_USE_ALIAS;
    }
    return TO_ESP_ERR(ezb_apsde_data_request(data_req));
}

static inline esp_err_t esp_zb_aps_set_trust_center_address(const esp_zb_ieee_addr_t address)
{
    return TO_ESP_ERR(ezb_aps_set_trust_center_address((const ezb_extaddr_t *)address));
}

static inline void esp_zb_aps_get_trust_center_address(esp_zb_ieee_addr_t address)
{
    ezb_aps_get_trust_center_address((ezb_extaddr_t *)address);
}

typedef struct esp_zb_apsme_transport_key_req_s {
    esp_zb_ieee_addr_t dst_address;
    uint8_t key_type;
    union {
        struct {
            uint8_t key[ESP_ZB_CCM_KEY_SIZE];
            esp_zb_ieee_addr_t parent_address;
            uint8_t key_seq_number;
            bool use_parent;
        } nwk;
        struct {
            uint8_t key[ESP_ZB_CCM_KEY_SIZE];
            esp_zb_ieee_addr_t partner_address;
            uint8_t initiator;
        } app;
        struct {
            uint8_t key[ESP_ZB_CCM_KEY_SIZE];
        } tc;
    } key_data;
} esp_zb_apsme_transport_key_req_t;

esp_err_t esp_zb_apsme_transport_key_request(const esp_zb_apsme_transport_key_req_t *req);

typedef struct esp_zb_apsme_switch_key_req_s {
    esp_zb_ieee_addr_t dst_address;
    uint8_t key_seq_number;
} esp_zb_apsme_switch_key_req_t;

esp_err_t esp_zb_apsme_switch_key_request(const esp_zb_apsme_switch_key_req_t *req);

#define esp_zb_aps_set_fragment_max_window_size(max_ws) TO_ESP_ERR(ezb_aps_set_fragment_max_window_size(max_ws))
#define esp_zb_aps_get_fragment_max_window_size()       ezb_aps_get_fragment_max_window_size()
#define esp_zb_aps_set_fragment_interframe_delay(d_ms)  TO_ESP_ERR(ezb_aps_set_fragment_interframe_delay(d_ms))
#define esp_zb_aps_get_fragment_interframe_delay()      ezb_aps_get_fragment_interframe_delay()

#ifdef __cplusplus
} /*  extern "C" */
#endif

#else
#error "This file is for compatibility, please include "ezbee/aps.h"!"
#endif
