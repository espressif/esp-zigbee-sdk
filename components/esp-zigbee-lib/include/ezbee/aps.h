/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_APS_H
#define ESP_ZIGBEE_APS_H

#include <ezbee/core.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration for address mode in APS layer.
 *
 */
enum ezb_aps_address_mode_e {
    /** DstAddress and DstEndpoint not present, only for APSDE-DATA request and confirm  */
    EZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT = EZB_ADDR_MODE_NONE,
    /** 16-bit group address for DstAddress; DstEndpoint not present */
    EZB_APS_ADDR_MODE_16_GROUP_ENDP_NOT_PRESENT = EZB_ADDR_MODE_GROUP,
    /** 16-bit address for DstAddress and DstEndpoint present */
    EZB_APS_ADDR_MODE_16_ENDP_PRESENT           = EZB_ADDR_MODE_SHORT,
    /** 64-bit extended address for DstAddress and DstEndpoint present */
    EZB_APS_ADDR_MODE_64_ENDP_PRESENT           = EZB_ADDR_MODE_EXT,
};

typedef ezb_addr_mode_t ezb_aps_address_mode_t;

/**
 * @brief Enumeration for APSDE-DATA Request TX options
 *
 */
typedef enum ezb_apsde_tx_opt_e {
    EZB_APSDE_TX_OPT_SECURITY_ENABLED         = 0x01U, /*!< Security enabled transmission */
    EZB_APSDE_TX_OPT_USE_NWK_KEY_R21OBSOLETE  = 0x02U, /*!< Use NWK key (obsolete) */
    EZB_APSDE_TX_OPT_ACK_TX                   = 0x04U, /*!< Acknowledged transmission */
    EZB_APSDE_TX_OPT_FRAG_PERMITTED           = 0x08U, /*!< Fragmentation permitted */
    EZB_APSDE_TX_OPT_INC_EXT_NONCE            = 0x10U, /*!< Include extended nonce in APS security frame */
    EZB_APSDE_TX_OPT_USE_ALIAS                = 0x20U, /*!< The next higher layer may use the UseAlias parameter to
                                                            request alias usage by NWK layer for the current frame. */
} ezb_apsde_tx_opt_t;

/**
 * @brief Enumeration the standard key type of the Transport-Key, Verify-Key and Confirm-Key
 *
 */
typedef enum ezb_apsme_key_type_s {
    EZB_APSME_STANDARD_NETWORK_KEY            = 1U, /*!< NWK key */
    EZB_APSME_APP_LINK_KEY                    = 3U, /*!< Application link key */
    EZB_APSME_TC_LINK_KEY                     = 4U, /*!< Trust-center link key */
} ezb_apsme_key_type_t;

/**
 * @brief APSDE-DATA.request Parameters
 *
 */
typedef struct ezb_apsde_data_req_s {
    ezb_address_t dst_address; /*!< The destination address the ASDU is being transferred to. */
    uint8_t src_endpoint;   /*!< The individual endpoint of the entity from which the ASDU is being transferred.*/
    uint8_t dst_endpoint;   /*!< The number of the individual endpoint of the entity to which the ASDU is being transferred or the broadcast endpoint (0xff).*/
    uint16_t cluster_id;    /*!< The identifier of the object for which this frame is intended. */
    uint16_t profile_id;    /*!< The identifier of the profile for which this frame is intended. */

    uint8_t radius;         /*!< The distance, in hops, that a transmitted frame will be allowed to travel through the network.*/

    uint8_t  alias_seq_num; /*!< The sequence number to be used for this NSDU. If the use_alias is true */
    uint16_t alias_src_addr;/*!< The source address to be used for this NSDU. If the use_alias is true */

    uint8_t tx_options;     /*!< The transmission options for the ASDU to be transferred, refer to ezb_apsde_tx_opt_t */

    uint16_t asdu_length;   /*!< The number of octets comprising the ASDU to be transferred */
    uint8_t *asdu;    /*!< The set of octets comprising the ASDU to be transferred. */
} ezb_apsde_data_req_t;

/**
 * @brief APSDE-DATA.confirm Parameters
 *
 */
typedef struct ezb_apsde_data_confirm_s {
    ezb_address_t dst_address; /*!< The destination address the ASDU was being transferred to. */
    uint8_t src_endpoint;     /*!< The individual endpoint of the entity from which the ASDU was being transferred.*/
    uint8_t dst_endpoint;     /*!< The number of the individual endpoint of the entity to which the ASDU was being transferred or the broadcast endpoint (0xff).*/
    uint16_t cluster_id;      /*!< The identifier of the object for which this frame was intended. */
    uint16_t profile_id;      /*!< The identifier of the profile for which this frame was intended. */

    uint8_t status;           /*!< The status of data confirm. 0: success, otherwise failed */

    uint16_t asdu_length;     /*!< The number of octets comprising the ASDU was transferred */
    uint8_t *asdu;      /*!< The set of octets comprising the ASDU was transferred. */
} ezb_apsde_data_confirm_t;

/**
 * @brief APSDE-DATA.indication Parameters
 *
 */
typedef struct ezb_apsde_data_ind_s {
    ezb_address_t dst_address; /*!< The address which the ASDU is send to.*/
    ezb_address_t src_address; /*!< The address which the ASDU is received from.*/
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
} ezb_apsde_data_ind_t;

/**
 * @brief APSDE data indication application callback
 *
 * @param[in] ind APSDE-DATA.indication
 * @return
 *      - true: The indication has already been handled
 *      - false: The indication has not been handled; it will be processed by the stack.
 *
 */
typedef bool (*ezb_apsde_data_indication_callback_t)(const ezb_apsde_data_ind_t *ind);

/**
 * @brief APSDE data confirm application callback
 *
 * @param[in] confirm APSDE-DATA.confirm
 */
typedef void (*ezb_apsde_data_confirm_callback_t)(const ezb_apsde_data_confirm_t *confirm);

/**
 * @brief Register the callback for retrieving the aps data indication
 *
 * @param[in] cb A function pointer for ezb_apsde_data_indication_callback_t
 */
void ezb_apsde_data_indication_handler_register(ezb_apsde_data_indication_callback_t cb);

/**
 * @brief Register the callback for retrieving the aps data confirm
 *
 * @note If the callback is registered by the application, the application is responsible for handling APSDE confirm.
 * @param[in] cb A function pointer for ezb_apsde_data_confirm_callback_t
 */
void ezb_apsde_data_confirm_handler_register(ezb_apsde_data_confirm_callback_t cb);

/**
 * @brief APS data request
 *
 * @param[in] req A pointer for apsde data request, @ref ezb_apsde_data_req_s
 * @return
 *      - EZB_ERR_NONE: on success
 *      - EZB_ERR_INV_ARG: invalid arguments
 *      - EZB_ERR_NO_MEM: not memory
 *      - EZB_ERR_FAIL: on failed
 */
ezb_err_t ezb_apsde_data_request(const ezb_apsde_data_req_t *req);

/**
 * @brief Enable or disable distributed security
 *
 * @param[in] enable True to enable distributed security, false to disable
 *
 */
void ezb_aps_secur_enable_distributed_security(bool enable);

/**
 * @brief Check if the distributed security is enabled
 *
 * @return True if the distributed security is enabled, false otherwise
 */
bool ezb_aps_secur_is_distributed_security(void);

/**
 * @brief Set the APS trust center address
 *
 * @param[in] tc_addr The IEEE (extended) address of the trust center
 *
 * @return
 *      - EZB_ERR_NONE: On success
 *      - EZB_ERR_INV_STATE: Device is already on a network
 */
ezb_err_t ezb_aps_set_trust_center_address(const ezb_extaddr_t *tc_addr);

/**
 * @brief Get the APS trust center address
 *
 * @param[out] tc_addr The IEEE (extended) address of the trust center
 */
void ezb_aps_get_trust_center_address(ezb_extaddr_t *tc_addr);

/**
 * @brief Set the maximum window size for APS fragmentation.
 *
 * @note The window size must be configured with the same value on both the source and destination nodes.
 *
 * @param[in] max_window_size The maximum number of fragments in a window, ranging from 1 to 8 (default: 8),
 *                            that can be sent before requiring an acknowledgment.
 *
 * @return
 *      - EZB_ERR_NONE: Operation successful
 *      - EZB_ERR_INV_ARG: @p max_window_size is out of the valid range
 */
ezb_err_t ezb_aps_set_fragment_max_window_size(uint8_t max_window_size);

/**
 * @brief Get the current maximum window size used for APS fragmentation.
 *
 * @return The configured APS fragment window size.
 */
uint8_t ezb_aps_get_fragment_max_window_size(void);

/**
 * @brief Set the delay, in milliseconds, between sending two blocks of a fragmented transmission
 *
 * @param[in] delay_ms Delay in milliseconds between sending consecutive APS fragment blocks, default is 0.
 *
 * @return
 *      - EZB_ERR_NONE: Operation successful
 *      - Others: Operation failed
 */
ezb_err_t ezb_aps_set_fragment_interframe_delay(uint8_t delay_ms);

/**
 * @brief Get the current interframe delay for APS fragmentation.
 *
 * @return The interframe delay in milliseconds.
 */
uint8_t ezb_aps_get_fragment_interframe_delay(void);

/**
 * @brief Set allowable 2.4GHz channels for this device to use for network operations.
 * @anchor ezb_aps_set_channel_mask
 *
 * @param[in] channel_mask The 2.4GHz channel mask. Valid channel mask is from 0x00000800 (only channel 11)
 *                         to 0x07FFF800 (all channels from 11 to 26).
 *
 * @return
 *      - EZB_ERR_NONE: on success
 *      - EZB_ERR_INV_ARG: if the channel mask is out of range
 */
ezb_err_t ezb_aps_set_channel_mask(uint32_t channel_mask);

/**
 * @brief Get allowable 2.4GHz channels for this device to use for network operations.
 * @anchor ezb_aps_get_channel_mask
 *
 * @return The valid 32-bit 2.4GHz channel mask.
 */
uint32_t ezb_aps_get_channel_mask(void);

/**
 * @brief Set the extended PAN ID that used for commissioning.
 * @anchor ezb_aps_set_use_extended_panid
 *
 * @param[in] extpanid The pointer to the 64-bit of extended PAN ID, in little-endian.
 */
void ezb_aps_set_use_extended_panid(const ezb_extpanid_t *extpanid);

/**
 * @brief Get the extended PAN ID that used for commissioning.
 * @anchor ezb_aps_get_use_extended_panid
 *
 * @param[out] extpanid The pointer to the 64-bit of extended PAN ID, in little-endian.
 */
void ezb_aps_get_use_extended_panid(ezb_extpanid_t *extpanid);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_APS_H */
