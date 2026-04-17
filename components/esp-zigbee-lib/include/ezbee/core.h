/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_CORE_H
#define ESP_ZIGBEE_CORE_H

#include <ezbee/core_types.h>
#include <ezbee/app_signals.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EZB_ZIGBEE_VERSION_2004 0x01U
#define EZB_ZIGBEE_VERSION_2006 0x02U

#define EZB_ZIGBEE_STACK_STD    0x01U
#define EZB_ZIGBEE_STACK_PRO    0x02U

#define EZB_ZIGBEE_STACK_SPEC_LEGACY 0U
#define EZB_ZIGBEE_STACK_SPEC_R21    21U
#define EZB_ZIGBEE_STACK_SPEC_R22    22U
#define EZB_ZIGBEE_STACK_SPEC_R23    23U

#define EZB_ZIGBEE_FREQ_BAND_868MHZ     (1U << 0) /*!< 868-868.6 MHz */
#define EZB_ZIGBEE_FREQ_BAND_SUB_GHZ_NA (1U << 2) /*!< 902-928 MHz */
#define EZB_ZIGBEE_FREQ_BAND_2P4GHZ     (1U << 3) /*!< 2400-2483.5 MHz */
#define EZB_ZIGBEE_FREQ_BAND_SUB_GHZ_EU (1U << 4) /*!< 863-876MHz, 915-921MHz */

/**
 * @brief Initialize the ESP-Zigbee core
 * @anchor ezb_core_init
 *
 * @return EZB_ERR_NONE on success, error code otherwise.
 *
 */
ezb_err_t ezb_core_init(void);

/**
 * @brief Deinitialize the ESP-Zigbee core
 * @anchor ezb_core_deinit
 *
 */
void ezb_core_deinit(void);

/**
 * @brief The memory configuration structure.
 */
typedef struct ezb_mem_config_s {
    /** The capacity of the buffer pool */
    uint16_t buffer_pool_size;
    /** The capacity of the address table */
    uint16_t address_table_size;
    /** The capacity of the neighbor table */
    uint16_t neighbor_table_size;
    /** The capacity of the route table */
    uint16_t route_table_size;
    /** The capacity of the route discovery table */
    uint16_t route_discovery_table_size;
    /** The capacity of the route record table */
    uint16_t route_record_table_size;
    /** The capacity of the APS device key pair set */
    uint16_t aps_key_pair_set_size;
    /** The capacity of source entries in the APS binding table */
    uint16_t aps_bind_table_src_size;
    /** The capacity of destination entries in the APS binding table */
    uint16_t aps_bind_table_dst_size;
} ezb_mem_config_t;

/**
 * @brief Configure the memory after the stack is initialized.
 *
 * @note This function must be called after @ref ezb_core_init is called.
 *
 * @param[in] mem_cfg The memory configuration, see @ref ezb_mem_config_s.
 *                    The size of 0 in the configuration will use the default size.
 *
 * @return EZB_ERR_NONE on success, error code otherwise.
 */
ezb_err_t ezb_config_memory(const ezb_mem_config_t *mem_cfg);

/**
 * @brief Start the Zigbee device.
 * @anchor ezb_dev_start
 *
 * @param[in] autostart - True: autostart mode,
 *                      - False: no-autostart mode.
 *
 * @return EZB_ERR_NONE on success, error code otherwise.
 */
ezb_err_t ezb_dev_start(bool autostart);

/**
 * @brief Check if the Zigbee device is started.
 *
 * @return
 *      - True: if the Zigbee device is started
 *      - False: if the Zigbee device is not started
 */
bool ezb_dev_is_started(void);

/**
 * @brief Set the extended address of the Zigbee device.
 *
 * @note This is identical to @ref ezb_nwk_set_extended_address.
 *
 * @param[in] extaddr The pointer to the 64-bit of extended address, in little-endian.
 */
void ezb_set_extended_address(const ezb_extaddr_t *extaddr);

/**
 * @brief Get the extended address of the Zigbee device.
 *
 * @note This is identical to @ref ezb_nwk_get_extended_address.
 *
 * @param[out] extaddr The pointer to the 64-bit of extended address, in little-endian.
 */
void ezb_get_extended_address(ezb_extaddr_t *extaddr);

/**
 * @brief Set the short address of the Zigbee device.
 *
 * @note This is identical to @ref ezb_nwk_set_short_address.
 *
 * @param[in] short_addr The short address of the Zigbee device.
 */
void ezb_set_short_address(ezb_shortaddr_t short_addr);

/**
 * @brief Get the short address of the Zigbee device.
 *
 * @note This is identical to @ref ezb_nwk_get_short_address.
 *
 * @return The short address of the Zigbee device.
 */
ezb_shortaddr_t ezb_get_short_address(void);

/**
 * @brief Set the extended PAN ID to be used for commissioning.
 * @anchor ezb_set_use_extended_panid
 *
 * @note This is identical to @ref ezb_aps_set_use_extended_panid.
 *
 * @param[in] extpanid The pointer to the 64-bit of extended PAN ID, in little-endian.
 */
void ezb_set_use_extended_panid(const ezb_extpanid_t *extpanid);

/**
 * @brief Get the extended PAN ID to be used for commissioning.
 * @anchor ezb_get_use_extended_panid
 *
 * @note This is identical to @ref ezb_aps_get_use_extended_panid.
 *
 * @param[out] extpanid The pointer to the 64-bit of extended PAN ID, in little-endian.
 */
void ezb_get_use_extended_panid(ezb_extpanid_t *extpanid);

/**
 * @brief Get the extended PAN ID of the network.
 *
 * @note This is identical to @ref ezb_nwk_get_extended_panid.
 *
 * @param[out] extpanid The pointer to the 64-bit of extended PAN ID, in little-endian.
 */
void ezb_get_extended_panid(ezb_extpanid_t *extpanid);

/**
 * @brief Set the PAN ID of the network.
 *
 * @note This is identical to @ref ezb_nwk_set_panid.
 *
 * @param[in] pan_id The 16-bit of PAN ID, in little-endian.
 */
void ezb_set_panid(ezb_panid_t pan_id);

/**
 * @brief Get the PAN ID of the network.
 *
 * @note This is identical to @ref ezb_nwk_get_panid.
 *
 * @return The 16-bit of PAN ID, in little-endian.
 */
ezb_panid_t ezb_get_panid(void);

/**
 * @brief Get the currently used channel.
 *
 * @note This is identical to @ref ezb_nwk_get_current_channel.
 *
 * @return The currently used channel.
 */
uint8_t ezb_get_current_channel(void);

/**
 * @brief Set the tx power.
 *
 * @note This is identical to @ref ezb_nwk_set_tx_power.
 *
 * @param[in] power The tx power in dBm.
 */
void ezb_set_tx_power(int8_t power);

/**
 * @brief Get the tx power.
 *
 * @note This is identical to @ref ezb_nwk_get_tx_power.
 *
 * @param[out] power The tx power in dBm.
 */
void ezb_get_tx_power(int8_t *power);

/**
 * @brief Set the 2.4GHz channel mask.
 *
 * @note This is identical to @ref ezb_aps_set_channel_mask.
 *
 * @param[in] channel_mask The 2.4GHz channel mask.
 *
 * @return
 *      - EZB_ERR_NONE: on success
 *      - EZB_ERR_INV_ARG: if the channel mask is out of range
 */
ezb_err_t ezb_set_channel_mask(uint32_t channel_mask);

/**
 * @brief Get the 2.4GHz channel mask
 *
 * @note This is identical to @ref ezb_aps_get_channel_mask.
 *
 * @return A 32-bit channel mask
 */
uint32_t ezb_get_channel_mask(void);

/**
 * @brief Enable/Disable Rx when device is in IDLE state.
 *
 * @note This is identical to @ref ezb_nwk_set_rx_on_when_idle.
 *
 * @param[in] rx_on True - Rx remains on during idle periods, False - Rx is put to sleep during idle periods.
 */
void ezb_set_rx_on_when_idle(bool rx_on);

/**
 * @brief Get the current state of RxOnWhenIdle.
 *
 * @note This is identical to @ref ezb_nwk_get_rx_on_when_idle.
 *
 * @return The state of RxOnWhenIdle.
 */
bool ezb_get_rx_on_when_idle(void);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_CORE_H */
