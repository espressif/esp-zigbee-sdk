/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_PLATFORM_RADIO_H
#define ESP_ZIGBEE_PLATFORM_RADIO_H

#include <ezbee/core_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Unable to transmit due to channel being busy */
#define EZB_ERR_MAC_CHANNEL_ACCESS_FAILURE EZB_MAKE_ERROR(EZB_ERR_CATEGORY_MAC, 0xe1U)
/** ACK not received after tx with ack_req flag set */
#define EZB_ERR_MAC_NO_ACK EZB_MAKE_ERROR(EZB_ERR_CATEGORY_MAC, 0xe9U)

/**
 * @brief Common radio constants
 */
enum {
    EZB_RADIO_FRAME_MAX_SIZE = 127, /*!< aMaxPhyPacketSize, IEEE 802.15.4-2006 */
    EZB_RADIO_FRAME_MIN_SIZE = 3,   /*!< Minimum size of frame: CONTROL(1) + FCS(2) */

    EZB_RADIO_SYMBOLS_PER_OCTET = 2, /*!< 2.4 GHz IEEE 802.15.4-2006 */
    EZB_RADIO_BIT_RATE = 250000,     /*!< 2.4 GHz IEEE 802.15.4 (bits per second) */
    EZB_RADIO_BITS_PER_OCTET = 8,    /*!< Number of bits per octet */

    /* IEEE 802.15.4-2015, 12.3.3 Symbol rate:
     *   The O-QPSK PHY symbol rate shall be 25 ksymbol/s when operating in the 868 MHz band and
     *   62.5 ksymbol/s when operating in the 780 MHz, 915 MHz, 2380 MHz, or 2450 MHz band.
     */
    EZB_RADIO_SYMBOL_RATE = 62500, /*!< The symbol rate when operating in the 780MHz, 915MHz, 2380MHz, 2450MHz */
    EZB_RADIO_SYMBOL_TIME = 1000000 * 1 / EZB_RADIO_SYMBOL_RATE, /*!< Symbol duration time in microseconds */

    EZB_RADIO_LQI_NONE = 0,        /*!< LQI measurement nezb supported */
    EZB_RADIO_RSSI_INVALID = 127,  /*!< Invalid or unknown RSSI value */
    EZB_RADIO_POWER_INVALID = 127, /*!< Invalid or unknown power value */

    EZB_RADIO_INVALID_SHORT_ADDR = 0xfffe,   /*!< Invalid short address. */
    EZB_RADIO_BROADCAST_SHORT_ADDR = 0xffff, /*!< Broadcast short address. */
};

/**
 * @brief Channel page definition, IEEE 802.15.4-2006
 */
enum {
    EZB_RADIO_CHANNEL_PAGE_0 = 0, /*!< 2.4 GHz channel page */
};

/**
 * @brief Frequency band channel range definition, IEEE 802.15.4-2006
 */
enum {
    EZB_RADIO_2P4GHZ_CHANNEL_MIN = 11, /*!< 2.4 GHz minimum channel number */
    EZB_RADIO_2P4GHZ_CHANNEL_MAX = 26, /*!< 2.4 GHz maximum channel number */
    /** 2.4 GHz all channels mask, totally 16 channels. */
    EZB_RADIO_2P4GHZ_ALL_CHANNEL_MASK = 0xffff << EZB_RADIO_2P4GHZ_CHANNEL_MIN,
};

/**
 * @brief Represents an IEEE 802.15.4 radio frame.
 */
typedef struct ezb_radio_frame_s {
    uint8_t *psdu;      /*!< The PSDU */
    uint8_t length;     /*!< Length of the PSDU. */
    uint8_t channel;    /*!< Channel used to transmit/receive the frame. */

    /**
     * The union of transmit/receive information of radio frame.
     */
    union {
        /**
         * Structure representing radio frame transmit information.
         */
        struct {
            uint64_t timestamp; /*!< The timestamp in microseconds when the frame's SFD field was received. */
            uint8_t max_frame_retries;
            uint8_t max_csma_backoffs;
            uint8_t max_csma_be;
            uint8_t min_csma_be;
        } tx;

        /**
         * Structure representing radio frame receive information.
         */
        struct {
            uint64_t timestamp; /*!< The timestamp in microseconds when the frame's SFD field was received. */
            int8_t rssi;        /*!< Received signal strength indicator in dBm for received frame. */
            uint8_t lqi;        /*!< Link quality indicator for received frame. */

            /* Flags */
            bool acked_with_pending : 1; /*!< The frame was acked with frame pending set. */
        } rx;
    } info;
} ezb_radio_frame_t;

/*
 * Platform abstraction for radio configuration.
 */

/**
 * @brief Set the PAN ID on the platform.
 *
 * @param[in] panid The IEEE 802.15.4 PAN ID.
 *
 */
void ezb_plat_radio_set_panid(ezb_panid_t panid);

/**
 * @brief Set the Short Address on the platform.
 *
 * @param[in] addr The IEEE 802.15.4 16-bit Short Address.
 *
 */
void ezb_plat_radio_set_shortaddr(ezb_shortaddr_t addr);

/**
 * @brief Set the Extended Address on the platform.
 *
 * @param[in] extaddr A pointer to the IEEE 802.15.4 64-bit Extended Address stored in little-endian byte order.
 *
 */
void ezb_plat_radio_set_extaddr(const ezb_extaddr_t *extaddr);

/**
 * @brief Get the IEEE EUI-64 MAC Address factory-assigned on the platform.
 *
 * @param[out] macaddr A pointer to the MAC Address.
 *
 */
void ezb_plat_radio_get_macaddr(uint8_t *macaddr);

/**
 * @brief Set the status of promiscuous mode.
 *
 * @param[in] enable True/False to enable/disable promiscuous mode.
 *
 */
void ezb_plat_radio_set_promiscuous(bool enable);

/**
 * @brief Get the status of promiscuous mode.
 *
 * @return
 *      - True  The promiscuous mode is enabled.
 *      - False The promiscuous mode is disabled.
 *
 */
bool ezb_plat_radio_get_promiscuous(void);

/**
 * @brief Set the radio's transmit power in dBm for all channels.
 *
 * @param[in] power The transmit power in dBm.
 *
 */
void ezb_plat_radio_set_tx_power(int8_t power);

/**
 * @brief Get the radio's transmit power in dBm.
 *
 * @param[out] power A pointer to the transmit power in dBm.
 *
 */
void ezb_plat_radio_get_tx_power(int8_t *power);

/**
 * @brief Set rx-on-when-idle state to the radio platform.
 *
 * @param[in] enable True to keep radio in Receive state, False to put to Sleep state during idle periods.
 *
 * @return EZB_ERR_NONE on success, EZB_ERR_FAIL otherwise.
 *
 */
ezb_err_t ezb_plat_radio_set_rx_when_idle(bool enable);

/*
 * Platform abstraction for radio operation
 */

/**
 * @brief Enable the radio.
 *
 * @return EZB_ERR_NONE on success, EZB_ERR_FAIL otherwise.
 *
 */
ezb_err_t ezb_plat_radio_enable(void);

/**
 * @brief Disable the radio.
 *
 * @return EZB_ERR_NONE on success, EZB_ERR_FAIL otherwise.
 *
 */
ezb_err_t ezb_plat_radio_disable(void);

/**
 * @brief Check if the radio is enabled or not.
 *
 * @return True if the radio is enabled, False otherwise.
 *
 */
bool ezb_plat_radio_is_enabled(void);

/**
 * @brief Set state of the radio to Sleep (from Receive).
 *
 * @return EZB_ERR_NONE on success, EZB_ERR_FAIL otherwise.
 *
 */
ezb_err_t ezb_plat_radio_sleep(void);

/**
 * @brief Set state of the radio to Receive (from Sleep).
 *
 * @param[in] channel The radio channel on which to receive.
 *
 * @return EZB_ERR_NONE on success, EZB_ERR_FAIL otherwise.
 *
 */
ezb_err_t ezb_plat_radio_receive(uint8_t channel);

/**
 * @brief Signal that the radio platform has done the receiving of a frame.
 *
 * @param[in] frame A pointer to the received frame or NULL if the receive operation failed.
 * @param[in] error EZB_ERR_NONE if a frame successfully received,
 *                  EZB_ERR_NO_MEM if a frame reception failed due to lack of rx buffer.
 *
 */
extern void ezb_plat_radio_receive_done(ezb_radio_frame_t *frame, ezb_err_t error);

/**
 * @brief Get a radio frame buffer for transmit.
 *
 * @return A pointer to the radio frame buffer
 *
 */
ezb_radio_frame_t *ezb_plat_radio_get_transmit_buffer(void);

/**
 * @brief Start the transmit sequence on the radio.
 *
 * @param[in] frame A pointer to the frame to be transmitted.
 *
 * @return EZB_ERR_NONE Successfully transitioned to Transmit state.
 *         EZB_ERR_INV_STATE The radio was not in Receive state.
 *
 */
ezb_err_t ezb_plat_radio_transmit(ezb_radio_frame_t *frame);

/**
 * @brief Signal that the radio platform has started the transmission.
 *
 * @param[in] frame A pointer to the frame that is being transmitted.
 *
 */
extern void ezb_plat_radio_transmit_started(ezb_radio_frame_t *frame);

/**
 * @brief Signal that the radio platform has done the transmission.
 *
 * @param[in] frame A pointer to the frame that was transmitted.
 * @param[in] ack   A pointer to the ACK frame, NULL if no ACK was received.
 * @param[in] error EZB_ERR_NONE if the frame was transmitted.
 *                  EZB_ERR_MAC_NO_ACK if the frame was transmitted but no ACK was received.
 *                  EZB_ERR_MAC_CHANNEL_ACCESS_FAILURE tx could not be done due to activity on the channel.
 *                  EZB_ERR_ABORT if transmission was aborted for other reasons.
 *
 */
extern void ezb_plat_radio_transmit_done(ezb_radio_frame_t *frame, ezb_radio_frame_t *ack, ezb_err_t error);

/**
 * @brief Get the most recent RSSI measurement.
 *
 * @returns The RSSI in dBm when it is valid.  127 when RSSI is invalid.
 *
 */
int8_t ezb_plat_radio_get_rssi(void);

/**
 * @brief Start the energy detection sequence on the radio.
 *
 * @param[in] channel   The channel to perform the energy detection on.
 * @param[in] duration  The duration in milliseconds, for the channel to be scanned.
 *
 * @returns EZB_ERR_NONE   Successfully started scanning the channel.
 *          EZB_ERR_BUSY   The radio is performing energy scanning.
 *
 */
ezb_err_t ezb_plat_radio_energy_detect(uint8_t channel, uint32_t duration);

/**
 * @brief Signal that the radio platform has done the energy detection.
 *
 * @param[in] max_rssi  The maximum RSSI encountered on the scanned channel.
 *
 */
extern void ezb_plat_radio_energy_detect_done(int8_t max_rssi);

/**
 * @brief Set the state of source address match feature.
 *
 * @param[in] enable True/False to enable/disable source address match feature.
 *
 */
void ezb_plat_radio_set_src_match(bool enable);

/**
 * @brief Add a address to the source address match table.
 *
 * @param[in] addr      The address to be added.
 * @param[in] is_short  True/False flag indicating is the address is short/extended address.
 *
 * @returns EZB_ERR_NONE    Successfully added address to the source match table.
 *          EZB_ERR_NO_MEM  No available entry in the source match table.
 *
 */
ezb_err_t ezb_plat_radio_add_src_match_entry(uint8_t *addr, bool is_short);

/**
 * @brief Remove a address from the source address match table.
 *
 * @param[in] addr      The address to be removed.
 * @param[in] is_short  True/False flag indicating is the address is short/extended address.
 *
 * @returns EZB_ERR_NONE        Successfully removed address to the source match table.
 *          EZB_ERR_NOT_FOUND   The address is not in source address match table.
 *
 */
ezb_err_t ezb_plat_radio_clear_src_match_entry(uint8_t *addr, bool is_short);

/**
 * @brief Clear the the short/extended source address match table.
 *
 * @param[in] is_short  True/False flag indicating short/extended address match table to be cleared.
 *
 */
void ezb_plat_radio_clear_src_match_entries(bool is_short);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_PLATFORM_RADIO_H */
