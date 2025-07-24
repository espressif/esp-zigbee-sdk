/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "esp_err.h"
#include "zb_vendor.h"
#include "platform/esp_zigbee_platform.h"
#include "esp_zigbee_version.h"
#include "esp_zigbee_trace.h"
#include "esp_zigbee_attribute.h"
#include "esp_zigbee_cluster.h"
#include "esp_zigbee_endpoint.h"
#include "nwk/esp_zigbee_nwk.h"
#include "zcl/esp_zigbee_zcl_core.h"
#include "zdo/esp_zigbee_zdo_command.h"
#include "bdb/esp_zigbee_bdb_touchlink.h"
#include "bdb/esp_zigbee_bdb_commissioning.h"
#include "esp_zigbee_secur.h"
#include "esp_zigbee_ota.h"

#define ESP_ZB_TRANSCEIVER_ALL_CHANNELS_MASK 0x07FFF800U /*!< channel 11-26 for compatibility with 2.4GHZ*/

#ifdef CONFIG_ZB_ZED
#define ESP_ZB_SLEEP_MAXIMUM_THRESHOLD_MS 86400000U /*! Maximum sleep threshold*/
#endif                                              /** CONFIG_ZB_ZED */

#ifdef CONFIG_ZB_GP_ENABLED
#define ESP_ZGP_GPPB_DEFAULT_FUNCTIONALITY 0x9ac2f /*!< GPP functionality, refer to esp_zgp_gpp_functionality_t */
#define ESP_ZGP_GPS_DEFAULT_FUNCTIONALITY 0x9ac2f /*!< GPS functionality, refer to esp_zgp_gps_functionality_t */
#endif /* CONFIG_ZB_GP_ENABLED */

/**
 * @name End Device (ED) timeout request
 * @anchor nwk_requested_timeout
 */
typedef enum {
    ESP_ZB_ED_AGING_TIMEOUT_10SEC    = 0U, /*!< 10 second timeout */
    ESP_ZB_ED_AGING_TIMEOUT_2MIN     = 1U, /*!< 2 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_4MIN     = 2U, /*!< 4 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_8MIN     = 3U, /*!< 8 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_16MIN    = 4U, /*!< 16 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_32MIN    = 5U, /*!< 32 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_64MIN    = 6U, /*!< 64 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_128MIN   = 7U, /*!< 128 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_256MIN   = 8U, /*!< 256 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_512MIN   = 9U, /*!< 512 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_1024MIN  = 10U, /*!< 1024 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_2048MIN  = 11U, /*!< 2048 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_4096MIN  = 12U, /*!< 4096 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_8192MIN  = 13U, /*!< 8192 minutes */
    ESP_ZB_ED_AGING_TIMEOUT_16384MIN = 14U, /*!< 16384 minutes */
} esp_zb_aging_timeout_t;

/**
 * @brief The Zigbee Coordinator/ Router device configuration.
 *
 */
typedef struct {
    uint8_t max_children; /*!< Max number of the children */
} esp_zb_zczr_cfg_t;

/**
 * @brief The Zigbee End device configuration.
 *
 */
typedef struct {
    uint8_t ed_timeout; /*!< Set End Device Timeout, refer to esp_zb_aging_timeout_t */
    uint32_t keep_alive; /*!< Set Keep alive Timeout, in milliseconds, with a maximum value of 65,000,000,000.*/
} esp_zb_zed_cfg_t;

/**
 * @brief The Zigbee device configuration.
 * @note  For esp_zb_role please refer defined by esp_zb_nwk_device_type_t.
 */
typedef struct esp_zb_cfg_s {
    esp_zb_nwk_device_type_t esp_zb_role; /*!< The nwk device type */
    bool install_code_policy;             /*!< Allow install code security policy or not */
    union {
        esp_zb_zczr_cfg_t zczr_cfg; /*!< The Zigbee zc/zr device configuration */
        esp_zb_zed_cfg_t zed_cfg;   /*!< The Zigbee zed device configuration */
    } nwk_cfg;                      /*!< Union of the network configuration */
} esp_zb_cfg_t;

/**
 * @brief The application signal struct for esp_zb_app_signal_handler
 *
 */
typedef struct esp_zb_app_signal_s {
    uint32_t *p_app_signal;   /*!< Application pointer signal type, refer to esp_zb_app_signal_type_t */
    esp_err_t esp_err_status; /*!< The error status of the each signal event, refer to esp_err_t */
} esp_zb_app_signal_t;

/**
 * @brief Set the maximum number of devices in a Zigbee network
 *
 * @note The function will only take effect when called before esp_zb_init(), it determines
 *       several table size such as the neighbor table and routing table, 64 by default
 * @param[in] size The overall network size is expected to be set
 * @return
 *       - ESP_OK: on success
 *       - ESP_FAIL: on failure
 */
esp_err_t esp_zb_overall_network_size_set(uint16_t size);

/**
 * @brief Set Zigbee stack I/O buffer size
 *
 * @note The function will only take effect when called before esp_zb_init(), 80 by default.
 * @param[in] size The I/O buffer size is expected to be set
 * @return
 *       - ESP_OK: on success
 *       - ESP_FAIL: on failure
 */
esp_err_t esp_zb_io_buffer_size_set(uint16_t size);

/**
 * @brief Set Zigbee stack scheduler queue size
 *
 * @note The function will only take effect when called before esp_zb_init(), 80 by default.
 * @param[in] size The scheduler queue size is expected to be set
 * @return
 *       - ESP_OK: on success
 *       - ESP_FAIL: on failure
 */
esp_err_t esp_zb_scheduler_queue_size_set(uint16_t size);

/**
 * @brief Set APS source binding table size
 *
 * @note The function will only take effect when called before esp_zb_init(), 16 by default
 * @param[in] size The source binding table size is expected to be set
 * @return
 *       - ESP_OK: on success
 *       - ESP_FAIL: on failure
 */
esp_err_t esp_zb_aps_src_binding_table_size_set(uint16_t size);

/**
 * @brief Set APS destination binding table size
 *
 * @note The function will only take effect when called before esp_zb_init(), 16 by default
 * @param[in] size The destination binding table size is expected to be set
 * @return
 *       - ESP_OK: on success
 *       - ESP_FAIL: on failure
 */
esp_err_t esp_zb_aps_dst_binding_table_size_set(uint16_t size);

/**
 * @brief  Zigbee stack initialization.
 *
 * @note To be called inside the application's main cycle at start.
 * @note Default is no NVRAM erase from start up, user could call factory reset for erase NVRAM and other action please refer esp_zb_factory_reset().
 * @note Make sure to use correct corresponding nwk_cfg with your device type @ref esp_zb_cfg_s.
 * @anchor esp_zb_init
 * @param[in] nwk_cfg   The pointer to the initialization Zigbee configuration
 *
 */
void esp_zb_init(esp_zb_cfg_t *nwk_cfg);

/**
 * @brief Set the BDB primary channel mask.
 *
 * Beacon request will be sent on these channels for the BDB energy scan.
 *
 * @note  This function should be run AFTER @ref esp_zb_init is called and before @ref esp_zb_start. These masks define the allowable channels on which the device may attempt to
 * form or join a network at startup time. If function is not called, by default it will scan all channels or read from `zb_fct` NVRAM zone if available. Please refer to tools/mfg_tool.
 * @param[in] channel_mask  Valid channel mask is from 0x00000800 (only channel 11) to 0x07FFF800 (all channels from 11 to 26)
 * @return  - ESP_OK on success
            - ESP_ERR_INVALID_ARG if the channel mask is out of range
 */
esp_err_t esp_zb_set_primary_network_channel_set(uint32_t channel_mask);

/**
 * @brief Get the BDB primary channel mask
 *
 * @return A 32-bit channel mask
 */
uint32_t esp_zb_get_primary_network_channel_set(void);

/**
 * @brief   Set the BDB secondary channel mask.
 *
 * Beacon request will be sent on these channels for the BDB energy scan, if no network found after energy scan on the primary channels.
 *
 * @param[in] channel_mask Valid channel mask is from 0x00000800 (only channel 11) to 0x07FFF800 (all channels from 11 to 26)
 * @return  - ESP_OK on success
            - ESP_ERR_INVALID_ARG if the channel mask is out of range
 */
esp_err_t esp_zb_set_secondary_network_channel_set(uint32_t channel_mask);

/**
 * @brief Get the BDB secondary channel mask
 *
 * @return A 32-bit channel mask
 */
uint32_t esp_zb_get_secondary_network_channel_set(void);

/**
 * @brief   Set the 2.4G channel mask.
 *
 * @param[in] channel_mask Valid channel mask is from 0x00000800 (only channel 11) to 0x07FFF800 (all channels from 11 to 26)
 * @return  - ESP_OK on success
            - ESP_ERR_INVALID_ARG if the channel mask is out of range
 */
esp_err_t esp_zb_set_channel_mask(uint32_t channel_mask);

/**
 * @brief Get the 2.4 channel mask
 *
 * @return A 32-bit channel mask
 */
uint32_t esp_zb_get_channel_mask(void);

/**
 * @brief   Check if device is factory new.
 *
 * @return - True factory new.
 *
 */
bool esp_zb_bdb_is_factory_new(void);

/**
 * @brief Get the scan duration time
 *
 * @return Scan duration is in beacon intervals (15.36 ms)
 */
uint8_t esp_zb_bdb_get_scan_duration(void);

/**
 * @brief Set the scan duration time
 *
 * @param[in] duration  The scan duration time is in beacon intervals, defined as ((1 << duration) + 1) * 15.36 ms
 */
void esp_zb_bdb_set_scan_duration(uint8_t duration);

/**
 * @brief Open Zigbee network
 *
 * @param[in] permit_duration Zigbee network open time
 * @return
 *      - ESP_OK: on success
 *      - ESP_ERR_NO_MEM: not memory
 *      - ESP_FAILED: on failed
 */
esp_err_t esp_zb_bdb_open_network(uint8_t permit_duration);

/**
 * @brief Close Zigbee network
 *
 * @return
 *      - ESP_OK: on success
 *      - ESP_FAIL: on failure
 */
esp_err_t esp_zb_bdb_close_network(void);

/**
 * @brief Check if device has joined network or not
 *
 * @return
 *      - true: device is joined
 *      - false: device is not joined
 */
bool esp_zb_bdb_dev_joined(void);

/**
 * @brief Set Touchlink NWK channel
 *
 * @param[in] channel Touchlink NWK channel value
 *
 */
void esp_zb_zdo_touchlink_set_nwk_channel(uint8_t channel);

/**
 * @brief   Set the tx power.
 * @param[in]  power 8-bit of power value in dB, ranging from IEEE802154_TXPOWER_VALUE_MIN to IEEE802154_TXPOWER_VALUE_MAX
 */
void esp_zb_set_tx_power(int8_t power);

/**
 * @brief   Get the tx power.
 * @param[in]  power 8-bit of power pointer value in dB
 */
void esp_zb_get_tx_power(int8_t *power);

/**
 * @brief  Start top level commissioning procedure with specified mode mask.
 *
 * @param[in] mode_mask commissioning modes refer to esp_zb_bdb_commissioning_mode
 *
 * @return - ESP_OK on success
 *
 */
esp_err_t esp_zb_bdb_start_top_level_commissioning(uint8_t mode_mask);

/**
 * @brief Perform `local reset` procedure
 * @note This only takes effect when the device is on a network. The device will leave the current network and
 *       clear all Zigbee persistent data, except the outgoing NWK frame counter. It will be in nearly the same
 *       state as when it left the factory. A `ZB_ZDO_SIGNAL_LEAVE` signal with `ESP_ZB_NWK_LEAVE_TYPE_RESET`
 *       will be triggered to indicate the end of the procedure.
 */
void esp_zb_bdb_reset_via_local_action(void);

/**
 *  @brief Perform "factory reset" procedure
 *  @note The device will completely erase the `zb_storage` partition and then restart
 */
void esp_zb_factory_reset(void);

/**
 * @brief   Start Zigbee function.
 *
 * @param[in] autostart - true    autostart mode
 *                      - false   no-autostart mode
 *
 * @note Autostart mode: It initializes, load some parameters from NVRAM and proceed with startup.
 * Startup means either Formation (for ZC), rejoin or discovery/association join.  After startup
 * complete, @ref esp_zb_app_signal_handler is called, so application will know when to do
 * some useful things.
 *
 * @note No-autostart mode: It initializes scheduler and buffers pool, but not MAC and upper layers.
 * Notifies the application that Zigbee framework (scheduler, buffer pool, etc.) has started, but no
 * join/rejoin/formation/BDB initialization has been done yet.
 * Typically esp_zb_start with no_autostart mode is used when application wants to do something before
 * starting joining the network.
 *
 * For example, you can use this function if it is needed to enable leds, timers
 * or any other devices on periphery to work with them before starting working in a network. It's
 * also useful if you want to run something locally during joining.
 *
 * @note Precondition: stack must be initialized by @ref esp_zb_init call. @ref esp_zb_init sets default IB
 * parameters, so caller has a chance to change some of them. Note that NVRAM and product config will be
 * loaded after esp_zb_start() call.
 *
 * @note Zigbee stack is not looped in this routine. Instead, it schedules callback and returns.  Caller
 * must run  esp_zb_stack_main_loop() after this routine.
 *
 * @note Application should later call Zigbee commissioning initiation - for instance,
 * esp_zb_bdb_start_top_level_commissioning().
 * @anchor esp_zb_start
 * @return - ESP_OK on success
 *
 */
esp_err_t esp_zb_start(bool autostart);

/**
 * @brief Get the stack is started or not.
 *
 * @return true if the stack has been started, false otherwise.
 *
 */
bool esp_zb_is_started(void);

/**
 * @brief  Acquire Zigbee lock.
 *
 * @note It's mandatory to acquire the lock before calling any Zigbee SDK APIs, except that the call site is in Zigbee callbacks.
 * @return
 *      - true: on success
 *
 */
bool esp_zb_lock_acquire(TickType_t block_ticks);

/**
 * @brief  Release Zigbee lock.
 *
 */
void esp_zb_lock_release(void);

/**
 * @brief  Zigbee main loop iteration.
 *
 * @deprecated Please use esp_zb_stack_main_loop() instead
 * @note Must be called after esp_zb_init() and esp_zb_start()
   inside the application's main cycle.
 *
 */
ESP_ZB_DEPRECATED
void esp_zb_main_loop_iteration(void);

/**
 * @brief Zigbee stack main loop iteration once.
 *
 * @note Must be called after esp_zb_init() and esp_zb_start().
 */
void esp_zb_stack_main_loop_iteration(void);

/**
 * @brief  Zigbee stack main loop.
 *
 * @note Must be called after esp_zb_init() and esp_zb_start(), it’s an infinite main loop.
 */
void esp_zb_stack_main_loop(void);

/**
 * @brief  Enable/Disable erasing the zb_storage field before the stack runs
 *
 * @note   Enable or disable NVRAM erasing on every application startup. Erasing is disabled by default.
 * @param erase - 1 to enable erasing; 0 - disable.
 *
 */
void esp_zb_nvram_erase_at_start(bool erase);

/**
 * @brief Zigbee stack application signal handler.
 * @anchor esp_zb_app_signal_handler
 *
 * @param[in] signal_s   pointer of Zigbee zdo app signal struct @ref esp_zb_app_signal_s.
 * @note After esp_zb_start, user shall based on the corresponding signal type refer to esp_zdo_app_signal_type from struct pointer signal_s to do certain actions.
 * User could also use refer to esp_zb_bdb_start_top_level_commissioning to change BDB mode.
 * @warning This function has to be defined by user in each example.
 */
void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_s);

/**
 * @brief Obtains pointer to parameters passed with application signal.
 *
 * @param[in] signal_p pointer to the application signal type @ref esp_zb_app_signal_s of p_app_signal
 * @return void pointer to certain signal param content
 */
void *esp_zb_app_signal_get_params(uint32_t *signal_p);

/**
 * @brief Schedule alarm - callback to be executed after timeout.
 *
 * @note Function will be called via scheduler after timeout expired in millisecond. Timer resolution depends on implementation. Same callback can be scheduled for execution more then once.
 *
 * @param[in] cb - function to call via scheduler
 * @param[in] param - parameter to pass to the function
 * @param[in] time - timeout, in millisecond
 */
void esp_zb_scheduler_alarm(esp_zb_callback_t cb, uint8_t param, uint32_t time);

/**
 * @brief Cancel scheduled alarm.
 *
 * @note This function cancel previously scheduled alarm.
 *
 * @param[in] cb - function to cancel
 * @param[in] param - parameter to pass to the function to cancel
 */
void esp_zb_scheduler_alarm_cancel(esp_zb_callback_t cb, uint8_t param);

/**
 * @brief Schedule user alarm - callback to be executed after timeout.
 *
 * @note Function will be called via scheduler after timeout expired in millisecond. Timer resolution depends on implementation. Same callback can be scheduled for execution more then once.
 *
 * @param[in] cb - function to call via scheduler
 * @param[in] param - parameter to pass to the function
 * @param[in] time - timeout, in millisecond
 *
 * @return
 *      - the handle used to cancel the user alarm
 */
esp_zb_user_cb_handle_t esp_zb_scheduler_user_alarm(esp_zb_user_callback_t cb, void *param, uint32_t time);

/**
 * @brief Cancel scheduled user alarm.
 *
 * @note This function cancel previously scheduled user alarm.
 *
 * @param[in] handle - the handle returned by esp_zb_scheduler_user_alarm
 *
 * @return
 *      - ESP_OK: on success
 *      - ESP_ERR_NOT_FOUND: not found the user alarm
 */
esp_err_t esp_zb_scheduler_user_alarm_cancel(esp_zb_user_cb_handle_t handle);

/**
 * @brief  Set BDB commissioning mode.
 *
 * @param[in] commissioning_mode commissioning mode that refer to esp_zb_bdb_commissioning_mode_mask_t.
 *
 */
void esp_zb_set_bdb_commissioning_mode(esp_zb_bdb_commissioning_mode_mask_t commissioning_mode);

/**
 * @brief Set BDB commissioning mode
 *
 * @return commissioning mode, refer to esp_zb_bdb_commissioning_mode_mask_t
 */
esp_zb_bdb_commissioning_mode_mask_t esp_zb_get_bdb_commissioning_mode(void);

/**
 * @brief Schedule to cancel Steering procedure for a node not on a network
 *
 * @note The signal ESP_ZB_BDB_SIGNAL_STEERING_CANCELLED with the status of this operation will be raised.
 * @return
 *      - ESP_OK: on success
 *      - ESP_FAIL: on failed
 */
esp_err_t esp_zb_bdb_cancel_steering(void);

/**
 * @brief Schedule to cancel Formation procedure
 *
 * @note The signal ESP_ZB_BDB_SIGNAL_FORMATION_CANCELLED with the status of the operation will be raised.
 * @return
 *      - ESP_OK: on success
 *      - ESP_FAIL: on failed
 */
esp_err_t esp_zb_bdb_cancel_formation(void);

#ifdef ZB_DISTRIBUTED_SECURITY_ON

/**
 * @brief Set trust center policy state to distributed or not
 *
 * @param[in] enabled The trust center policy state
 */
void esp_zb_tc_policy_set_distributed_security(bool enabled);

/**
 * @brief Check the trust center policy is distributed
 *
 * @return
 *      - true: trust center policy is set as distributed
 *      - false: trust center policy is not set as distributed
 */
bool esp_zb_tc_policy_get_distributed_security();

/**
 * @brief Enable or disable the Zigbee distributed network.
 *
 * @param[in] enabled The status of Zigbee distribute network
 */
void esp_zb_enable_distributed_network(bool enabled);

/**
 * @brief Allow to setup network as distributed when started
 *
 */
void esp_zb_zdo_setup_network_as_distributed(void);

/**
 * @brief Check if the current network is a distributed security network
 *
 * @return - True: The current network is distributed, otherwise it is not.
 */
bool esp_zb_network_is_distributed(void);

/**
 * @brief Enable or disable the Zigbee device to join a distributed TC network
 *
 * @note It is disabled by default
 *
 * @param[in] enabled Enable or disable
 */
void esp_zb_enable_joining_to_distributed(bool enabled);

/**
 * @brief Determine whether the Zigbee device can join the distributed TC network or not
 *
 * @return - True: The Zigbee device can join the distributed TC network; otherwise, it cannot
 */
bool esp_zb_joining_to_distributed_network_enabled(void);
#endif

/**
 * @brief Set the sleep threshold on the device. When the scheduler detects that the device can enter sleep mode,
 *        it will notify the application with the signal ESP_ZB_COMMON_SIGNAL_CAN_SLEEP.
 *        The default sleep threshold is 20 milliseconds.
 *
 * @param[in] threshold_ms Sleep threshold in milliseconds
 *
 * @return ESP_OK if new threshold is valid and applied.
 * @return ESP_FAIL if the user attempts to set a threshold greater than ESP_ZB_SLEEP_MAXIMUM_THRESHOLD_MS.
 *
 */
esp_err_t esp_zb_sleep_set_threshold(uint32_t threshold_ms);

/**
* @brief Blocking function responsible for putting device into sleep mode.
*/
void esp_zb_sleep_now(void);

/**
 * @brief Enable the Zigbee sleep.
 *
 * @param[in] enable Enable Zigbee Sleep
 *
 */
void esp_zb_sleep_enable(bool enable);

/**
 * @brief Get Zigbee sleep is enable or not.
 *
 * @return TRUE Zigbee sleep is enable.
 * @return FALSE Zigbee sleep is disable.
 *
 */
bool esp_zb_sleep_is_enable(void);

/**
 * @brief Get bdb_commissioning_status
 *
 * @return commissioning_status refer to esp_zb_bdb_commissioning_status_t
 *
 */
#ifndef ZB_MACSPLIT_DEVICE
esp_zb_bdb_commissioning_status_t esp_zb_get_bdb_commissioning_status(void);
#endif

/**
 * @brief Set the Zigbee node descriptor manufacturer code.
 *
 * @note The function should be called after esp_zb_start()
 *
 * @param[in] manufacturer_code The manufacturer code of Zigbee device
 */
void esp_zb_set_node_descriptor_manufacturer_code(uint16_t manufacturer_code);

/**
 * @brief Set the power source for the Zigbee node descriptor.
 *
 * @note The function should be called after esp_zb_start()
 *
 * @param[in] is_main_power  Indicates whether the current power source is mains power (true) or not (false).
 */
void esp_zb_set_node_descriptor_power_source(bool is_main_power);

/**
 * @brief Set the maximum incoming transfer size and maximum outgoing transfer size for the Zigbee node descriptor
 *
 * @param[in] max_incoming_size The APS Service Data Unit (ASDU) that can be transferred to this node in one
 * single message transfer
 * @param[in] max_outgoing_size The APS Service Data Unit (ASDU) that can be transferred from this node in one
 * single message transfer
 * @return
 *      - ESP_OK: on success
 *      - ESP_ERR_INVALID_ARG @p max_incoming_size or @p max_outgoing_size is out of valid range
 */
esp_err_t esp_zb_set_node_descriptor_transfer_size(uint16_t max_incoming_size, uint16_t max_outgoing_size);

/**
 * @brief Set the node power descriptor
 *
 * @note The function should be called after esp_zb_start();
 *
 * @param[in] node_power The fields of the node power descriptor, @see esp_zb_af_node_power_desc_t
 */
void esp_zb_set_node_power_descriptor(esp_zb_af_node_power_desc_t node_power);

/**
 * @brief Get the version string of the SDK.
 *
 * @return The version string of the SDK.
 */
const char *esp_zb_get_version_string(void);

#ifdef __cplusplus
}
#endif
