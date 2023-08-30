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
#include "zb_config_platform.h"
#include "esp_zigbee_type.h"
#include "esp_zigbee_attribute.h"
#include "esp_zigbee_cluster.h"
#include "esp_zigbee_endpoint.h"
#include "zcl/esp_zigbee_zcl_command.h"
#include "zdo/esp_zigbee_zdo_command.h"
#include "bdb/esp_zigbee_bdb_touchlink.h"
#include "esp_zigbee_secur.h"
#include "esp_zigbee_ota.h"

/** Enum of the Zigbee network device type
 * @anchor esp_zb_nwk_device_type_t
 */
typedef enum {
    ESP_ZB_DEVICE_TYPE_COORDINATOR = 0x0,       /*!<  Device - Coordinator */
    ESP_ZB_DEVICE_TYPE_ROUTER  = 0x1,           /*!<  Device - Router */
    ESP_ZB_DEVICE_TYPE_ED = 0x2,                /*!<  Device - End device */
    ESP_ZB_DEVICE_TYPE_NONE = 0x3,              /*!<  Unknown Device */
} esp_zb_nwk_device_type_t;

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

#define ESP_ZB_TRANSCEIVER_ALL_CHANNELS_MASK   0x07FFF800U /*!< channel 11-26 for compatibility with 2.4GHZ*/

#ifdef CONFIG_ZB_ZED
#define ESP_ZB_SLEEP_MINIMUM_THRESHOLD_MS 20U /*! Default sleep threshold. Do not sleep when it is less then 1 Beacon Interval to wake up*/
#define ESP_ZB_SLEEP_MAXIMUM_THRESHOLD_MS 86400000U /*! Maximum sleep threshold*/
#endif /** CONFIG_ZB_ZED */

/** ZCL device callback
 *
 * @brief Add the callback to obtain the zboss original buffer id for zcl DEVICE_CB_ID
 *
 * @param[in] bufid The place of DEVICE_CB_ID messages stored in the buffer queue.
 * @return True: the @p bufid has been handled, otherwise, it remains unresolved.
 *
 */
typedef bool (*esp_zb_zcl_device_cb_id_callback_t)(uint8_t bufid);

/** ZCL set attribute callback
 *
 * @param[in] message The operation message for attribute value set by ZCL, @ref esp_zb_zcl_set_attr_value_message_s
 *
 *  @return ESP_OK on success, or others on failure
 */
typedef esp_err_t (*esp_zb_set_attr_callback_t)(const esp_zb_zcl_set_attr_value_message_t message);

/** Report attribute callback
 *
 * @brief A report attribute callback for user to get report info
 *
 * @param[in] addr A struct of address contains short and ieee address @ref esp_zb_zcl_addr_s
 * @param[in] src_endpoint  An endpoint which comes from report device
 * @param[in] dst_endpoint  Destination endpoint number
 * @param[in] cluster_id Cluster id that reported
 * @param[in] attr_id  Attribute id that reported
 * @param[in] attr_type Attribute data type refer to esp_zb_zcl_attr_type_t
 * @param[in] value A pointer to the attribute data value
 *
 */
typedef void (*esp_zb_report_attr_callback_t)(
    esp_zb_zcl_addr_t *addr, uint8_t src_endpoint, uint8_t dst_endpoint, uint16_t cluster_id, uint16_t attr_id, esp_zb_zcl_attr_type_t attr_type, void *value);

/** Read attribute response callback
 *
 * @brief A read attribute response callback for user to get read info.
 *
 * @param[in] status   Status of the read attribute response refer to esp_zb_zcl_status 0 - status success, 134 - unsupported attribute
 * @param[in] cluster_id Cluster id that read
 * @param[in] attr_id  Attribute id that read
 * @param[in] attr_type Attribute data type refer to esp_zb_zcl_attr_type_t
 * @param[in] value A pointer to the attribute data value
 *
 */
typedef void (*esp_zb_read_attr_resp_callback_t)(esp_zb_zcl_status_t status, uint16_t cluster_id, uint16_t attr_id, esp_zb_zcl_attr_type_t attr_type, void *value);

/** Groups cluster add group response callback
 *
 * @brief Add group cluster callback for user to get group id info
 *
 * @param[in] status Status of the add group cluster response, refer to esp_zb_zcl_status_t success status - 0  invalid value status - 135
 * @param[in] group_id Group id that added
 *
 */
typedef void (*esp_zb_add_group_resp_callback_t)(esp_zb_zcl_status_t status, uint16_t group_id);

/** Groups cluster remove group response callback
 *
 * @brief Remove group cluster callback for user to get group id info
 *
 * @param[in] status Status of the remove group cluster response, refer to esp_zb_zcl_status_t success status - 0  invalid value status - 135
 * @param[in] group_id Group id that removed
 *
 */
typedef void (*esp_zb_remove_group_resp_callback_t)(esp_zb_zcl_status_t status, uint16_t group_id);

/** Groups cluster view group response callback
 *
 * @brief View group cluster callback for user to get group id info
 *
 * @param[in] status Status of the view group cluster response, refer to esp_zb_zcl_status_t success status - 0  invalid value status - 135
 * @param[in] group_id Group id that to be viewed
 *
 */
typedef void (*esp_zb_view_group_resp_callback_t)(esp_zb_zcl_status_t status, uint16_t group_id);

/** Groups cluster get group membership response callback
 *
 * @brief Get group cluster membership callback for user to get group info
 *
 * @param[in] status Status of the get membership group cluster response, refer to esp_zb_zcl_status_t success status - 0  fail status - 1
 * @param[in] group_table_capacity Group table capacity that reported
 * @param[in] group_count Group count that reported
 * @param[in] group_id_list Group id list that acquired
 *
 */
typedef void (*esp_zb_get_group_membership_resp_callback_t)(esp_zb_zcl_status_t status, uint8_t group_table_capacity, uint8_t group_count, uint16_t *group_id_list);

/** Scenes cluster view scene response callback
 *
 * @brief View Scenes cluster callback for user to get scene information
 *
 * @param[in] resp The response information for viewing scene @ref esp_zb_zcl_scenes_view_scene_resp_s
 *
 */
typedef void (*esp_zb_zcl_scenes_view_scene_resp_callback_t)(esp_zb_zcl_scenes_view_scene_resp_t resp);

/** Scenes cluster store command callback
 *
 * @brief Store scenes state callback for user to save data entry.
 *
 * @param[in] message The operation message for storing scene from scene cluster client, @ref esp_zb_zcl_store_scene_message_s
 * @return ESP_OK on success, or others on failure
 */
typedef esp_err_t (*esp_zb_scenes_store_cmd_callback_t)(const esp_zb_zcl_store_scene_message_t message);

/** Scenes cluster recall command callback
 *
 * @brief Recall scenes callback for user to recall specific entry.
 *
 * @param[in] message The operation message for recalling scene from scene cluster client, @ref esp_zb_zcl_recall_scene_message_s
 * @return ESP_OK on success, or others on failure
 */
typedef esp_err_t (*esp_zb_scenes_recall_cmd_callback_t)(const esp_zb_zcl_recall_scene_message_t message);

/** OTA upgrade status callback
 *
 * @brief OTA upgrade callback for user to get upgrade status
 *
 * @param[in] message The operation message for ota upgrade, @ref esp_zb_zcl_ota_update_message_s
 * @return ESP_OK on success, or others on failure
 */
typedef esp_err_t (*esp_zb_ota_upgrade_status_callback_t)(const esp_zb_zcl_ota_update_message_t message);

/** Customized cluster command callback
 *
 * @brief A customized cluster command received from remote node and callback for user to get value info
 *
 * @param[in] status Status of the custom command request
 * @param[in] data_type Data type of the added data value refer to esp_zb_zcl_attr_type_t
 * @param[in] value A pointer to the attribute data value based on supported data types @ref esp_zb_zcl_custom_cluster_cmd_req_s
 *
 */
typedef void (*esp_zb_custom_cluster_cmd_callback_t)(uint8_t status, esp_zb_zcl_attr_type_t data_type, void *value);

/** CLI response callback
 *
 * @param[in] bufid index of buffer with ZCL command
 *
 */
typedef uint8_t (*esp_zb_cli_resp_callback_t)(uint8_t bufid);

/** Identify callback
 *
 * @param[in] identify_on A indication that need start identify or stop
 *
 */
typedef void (*esp_zb_identify_notify_callback_t)(uint8_t identify_on);

/** ZCL command callback
 * @param[in] cmd The zcl command content refers to esp_zb_zcl_cmd_info_t
 * 
 */
typedef void (*esp_zb_privilege_command_callback_t)(esp_zb_zcl_cmd_info_t cmd);

/** IAS zone cluster command callback
 *
 * @brief A IAS zone cluster command received from remote node and callback for user to get the Enroll Request Information
 *
 * @param[in] zone_type The type of IAS zone that refers to esp_zb_zcl_ias_zone_zonetype_t
 * @param[in] manuf The manfacturer code
 *
 */
typedef void (*esp_zb_ias_zone_enroll_request_callback_t)(uint16_t zone_type, uint16_t manuf);

/** IAS zone cluster command callback
 *
 * @brief A IAS zone cluster command received from remote node and callback for user to get the Enroll Eesponse information
 *
 * @param[in] message The response message for enroll ias zone, @ref esp_zb_zcl_ias_zone_enroll_response_message_s
 * @return ESP_OK on success, or others on failure
 *
 */
typedef esp_err_t (*esp_zb_ias_zone_enroll_response_callback_t)(const esp_zb_zcl_ias_zone_enroll_response_message_t message);

/** IAS zone cluster command callback
 *
 * @brief A IAS zone cluster command received from remote node and callback for user to get the Zone Status
 *
 * @note: The Zone Status Change Notification command is generated when a change takes place in one or more bits of the ZoneStatus attribute.
 *
 * @param[in] zone_status The current value of the Zone Status attribute
 * @param[in] extended_status The reserved for additional status information, default is zero
 * @param[in] zone_id A unique reference number allocated by the CIE at zone enrollment time
 * @param[in] delay defined as the amount of time, in quarter-seconds, from the moment when a change takes place in one or more bits of the Zone
 * Status attribute and the successful transmission of the Zone Status Change Notification.
 */
typedef void (*esp_zb_ias_zone_status_notification_cmd_callback_t)(uint16_t zone_status, uint8_t extended_status, uint8_t zone_id, uint16_t delay);

/** Level Control set value
 *
 * @brief A level control command received from remote node and callback for user to set value
 *
 * @param[in] message The level control message for setting value, @ref esp_zb_zcl_level_control_set_value_message_s
 * @return ESP_OK on success, or others on failure
 *
 */
typedef esp_err_t (*esp_zb_level_control_set_value_callback_t)(const esp_zb_zcl_level_control_set_value_message_t message);

/** Active scan network callback
 *
 * @brief A ZDO active scan request callback for user to get scan list status.
 *
 * @note User's callback get response from the device that found in network.
 *
 * @param[in] zdo_status The ZDO response status, refer to `esp_zb_zdp_status`
 * @param[in] count     Number of discovered networks
 * @param[in] nwk_descriptor The pointer to all discvoered networks see refer to esp_zb_network_descriptor_t
 *
 */
typedef void (*esp_zb_zdo_scan_complete_callback_t)(esp_zb_zdp_status_t zdo_status, uint8_t count, esp_zb_network_descriptor_t *nwk_descriptor);

/**
 * @brief The Zigbee Coordinator/ Router device configuration.
 *
 */
typedef struct {
    uint8_t  max_children;          /*!< Max number of the children */
} esp_zb_zczr_cfg_t;

/**
 * @brief The Zigbee End device configuration.
 *
 */
typedef struct {
    uint16_t   ed_timeout;          /*!< Set End Device Timeout */
    uint16_t  keep_alive;           /*!< Set Keep alive Timeout */
} esp_zb_zed_cfg_t;

/**
 * @brief The Zigbee device configuration.
 * @note  For esp_zb_role please refer defined by @ref esp_zb_nwk_device_type_t.
 */
typedef struct esp_zb_cfg_s {
    esp_zb_nwk_device_type_t esp_zb_role;           /*!< The nwk device type */
    bool   install_code_policy;                     /*!< Allow install code security policy or not */
    union {
        esp_zb_zczr_cfg_t   zczr_cfg;               /*!< The Zigbee zc/zr device configuration */
        esp_zb_zed_cfg_t    zed_cfg;                /*!< The Zigbee zed device configuration */
    } nwk_cfg;                                      /*!< Union of the network configuration */
} esp_zb_cfg_t;

/**
 * @brief The application signal struct for esp_zb_app_signal_handler
 *
 */
typedef struct esp_zb_app_signal_s {
    uint32_t        *p_app_signal;      /*!< Application pointer signal type, refer to esp_zb_app_signal_type_t */
    esp_err_t       esp_err_status;     /*!< The error status of the each signal event, refer to esp_err_t */
} esp_zb_app_signal_t;
/********************* Declare functions **************************/
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
 * @brief Set the primary channel mask.
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
 * @brief   Set the secondary channel mask.
 *
 * Beacon request will be sent on these channels for the BDB energy scan, if no network found after energy scan on the primary channels.
 *
 * @param[in] channel_mask Valid channel mask is from 0x00000800 (only channel 11) to 0x07FFF800 (all channels from 11 to 26)
 * @return  - ESP_OK on success
            - ESP_ERR_INVALID_ARG if the channel mask is out of range
 */
esp_err_t esp_zb_set_secondary_network_channel_set(uint32_t channel_mask);

/**
 * @brief   Set the 2.4G channel mask.
 *
 * @param[in] channel_mask Valid channel mask is from 0x00000800 (only channel 11) to 0x07FFF800 (all channels from 11 to 26)
 * @return  - ESP_OK on success
            - ESP_ERR_INVALID_ARG if the channel mask is out of range
 */
esp_err_t esp_zb_set_channel_mask(uint32_t channel_mask);

/**
 * @brief   Set zigbee rx on when idle.
 *
 * @param[in] rx_on enable/disable rx on when idle.
 *
 */
void esp_zb_set_rx_on_when_idle(bool rx_on);

/**
 * @brief   Check if device is factory new.
 *
 * @return - True factory new.
 *
 */
bool esp_zb_bdb_is_factory_new(void);

/**
 * @brief Set Touchlink NWK channel
 *
 * @param[in] channel Touchlink NWK channel value
 *
 */
void esp_zb_zdo_touchlink_set_nwk_channel(uint8_t channel);

/**
 * @brief   Active scan available network.
 *
 * Network discovery service for scanning available network
 *
 * @param[in] channel_mask Valid channel mask is from 0x00000800 (only channel 11) to 0x07FFF800 (all channels from 11 to 26)
 * @param[in] scan_duration Time to spend scanning each channel
 * @param[in] user_cb   A user callback to get the active scan result please refer to esp_zb_zdo_scan_complete_callback_t
 */
void esp_zb_active_scan_request(uint32_t channel_mask, uint8_t scan_duration, esp_zb_zdo_scan_complete_callback_t user_cb);

/**
 * @brief   Set the Zigbee device long address.
 *
 * @note  Set this function AFTER @ref esp_zb_init called, if user wants to set specific address
 * without reading MAC address from flash refer to tools/mfg_tool or eFUSE.
 *
 * @param[in] addr An 64-bit of IEEE long address, which is presented in little-endian.
 * @return - ESP_OK on success
 */
esp_err_t esp_zb_set_long_address(esp_zb_ieee_addr_t addr);

/**
 * @brief   Get the Zigbee device long address.
 *
 * @note This function will return a pointer to 64-bit of ieee long address.
 *
 * @param[out] addr An 64-bit of IEEE long address, which is presented in little-endian.
 *
 */
void esp_zb_get_long_address(esp_zb_ieee_addr_t addr);

/**
 * @brief   Get the Zigbee device short address.
 *
 * @return 16-bit Zigbee short address
 *
 */
uint16_t esp_zb_get_short_address(void);

/**
 * @brief Set the Zigbee network extended PAN ID.
 *
 * @param ext_pan_id An 64-bit of extended PAN ID, which is presented in little-endian.
 */
void esp_zb_set_extended_pan_id(const esp_zb_ieee_addr_t ext_pan_id);

/**
 * @brief   Get the Zigbee network extended PAN ID.
 *
 * @note This function will return back a pointer to 64-bit of extended PAN ID.
 *
 * @param[out] ext_pan_id An 64-bit of extended PAN ID, which is presented in little-endian.
 *
 */
void esp_zb_get_extended_pan_id(esp_zb_ieee_addr_t ext_pan_id);

/**
 * @brief   Get the Zigbee network PAN ID.
 *
 * @return 16-bit Zigbee network PAN ID
 *
 */
uint16_t esp_zb_get_pan_id(void);

/**
 * @brief   Set the Zigbee network PAN ID.
 *
 * @param[in] pan_id 16-bit Zigbee network PAN ID
 *
 */
void esp_zb_set_pan_id(uint16_t pan_id);

/**
 * @brief   Get the currently used channel.
 * @return  8-bit Zigbee network channel number
 */
uint8_t esp_zb_get_current_channel(void);

/**
 * @brief   Set the tx power.
 * @param[in]  power 8-bit of power value in dB
 */
void esp_zb_set_tx_power(int8_t power);

/**
 * @brief   Get the tx power.
 * @param[in]  power 8-bit of power pointer value in dB
 */
void esp_zb_get_tx_power(int8_t *power);

/**
 * @brief  Get the network short address by the IEEE address
 *
 * @param[in] address An 64-bit for the IEEE address, which is presented in little-endian.
 * @return Network short address
 *
 */
uint16_t esp_zb_address_short_by_ieee(esp_zb_ieee_addr_t address);

/**
 * @brief Get the network IEEE address by the short address
 *
 * @param[in] short_addr The 2-byte address which will been used to search the mapped IEEE address
 * @param[out] ieee_addr The 64-bit of address for Zigbee IEEE address, which is presented in little-endian.
 * @return
 *      - ESP_OK: on success
 *      - ESP_ERR_NOT_FOUND: not found the IEEE address
 */
esp_err_t esp_zb_ieee_address_by_short(uint16_t short_addr, uint8_t *ieee_addr);

/**
 * @brief   Get the Zigbee network device type.
 *
 * @return device type @ref esp_zb_nwk_device_type_t
 *
 */
esp_zb_nwk_device_type_t esp_zb_get_network_device_role(void);

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
 *  @brief Perform "Factory reset" procedure.
 *  @note The device will perform leave Zigbee network. The NVRAM store will be erased.
 *
 *  @note The reset can be performed at any time once the device is started (see esp_zb_start()).
 *  After the reset, the application itself will receive the refer to ZB_ZDO_SIGNAL_LEAVE signal.
 *  the remote coordinator will receive the refer to ZB_ZDO_SIGNAL_LEAVE_INDICATION signal. Further action could apply
 *  based on different circumstances.
 *
 *  @note After factory reset, the system reset will be performed.
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
 * must run  esp_zb_main_loop_iteration() after this routine.
 *
 * @note Application should later call Zigbee commissioning initiation - for instance,
 * esp_zb_bdb_start_top_level_commissioning().
 * @anchor esp_zb_start
 * @return - ESP_OK on success
 *
 */
esp_err_t esp_zb_start(bool autostart);

/**
 * @brief  Zigbee main loop iteration.
 *
 * @note Must be called after esp_zb_int() and esp_zb_start()
   inside the application's main cycle.
 *
 */
void esp_zb_main_loop_iteration(void);

/**
 * @brief  Zigbee CLI example main loop iteration.
 *
 * @note It is ONLY for cli specific example loop iteration.
 *
 */
void esp_zb_cli_main_loop_iteration(void);

/**
 * @brief  Enable / Disable erase NVRAM zone before run the refer to esp_zb_start.
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
 * @brief Add ZCL raw device cb id getting callback
 *
 * @param cb A device callback for getting the raw device cb id buffer, refer to esp_zb_zcl_device_cb_id_callback_t
 */
void esp_zb_zcl_device_cb_id_cb(esp_zb_zcl_device_cb_id_callback_t cb);

/* callback register */
/**
 * @brief   Add set ZCL attribute change device callback.
 * @note    User is able to enabling some device action based on the callback arguments.
 *
 * @param[in] cb A device callback that user used refer to esp_zb_set_attr_callback_t
 *
 */
void esp_zb_device_add_set_attr_value_cb(esp_zb_set_attr_callback_t cb);

/**
 * @brief   Set the ZCL report attribute device callback.
 *
 * @note  Set a callback being called on receive attribute report. The callback will
 *  be provided with all data necessary for correct attribute handling.
 *
 * @param[in] cb A report attribute callback that user used refer to esp_zb_report_attr_callback_t
 *
 */
void esp_zb_device_add_report_attr_cb(esp_zb_report_attr_callback_t cb);

/**
 * @brief   Set the ZCL read attribute response callback for specific endpoint.
 *
 * @note  Set a callback being called on receive read attribute response. The callback will
 *  be provided with all data necessary for correct attribute handling.
 * @param[in] endpoint A specific endpoint
 * @param[in] cb A read attribute callback that user used refer to esp_zb_read_attr_resp_callback_t
 *
 */
void esp_zb_add_read_attr_resp_cb(uint8_t endpoint, esp_zb_read_attr_resp_callback_t cb);

/**
 * @brief   Set the ZCL groups cluster add group response callback for specific endpoint for client.
 *
 * @note  Set a callback being called on receive add group cluster response. The callback will
 *  be provided with all data necessary for correct attribute handling.
 * @param[in] endpoint A specific endpoint
 * @param[in] cb Add group cluster callback that user used refer to esp_zb_add_group_resp_callback_t
 *
 */
void esp_zb_groups_add_group_resp_cb(uint8_t endpoint, esp_zb_add_group_resp_callback_t cb);

/**
 * @brief   Set the ZCL groups cluster remove group response callback for specific endpoint for client.
 *
 * @note  Set a callback being called on receive remove group cluster response. The callback will
 *  be provided with all data necessary for correct attribute handling.
 * @param[in] endpoint A specific endpoint
 * @param[in] cb Remove group cluster callback that user used refer to esp_zb_remove_group_resp_callback_t
 *
 */
void esp_zb_groups_remove_group_resp_cb(uint8_t endpoint, esp_zb_remove_group_resp_callback_t cb);

/**
 * @brief   Set the ZCL groups cluster view group response callback for specific endpoint for client.
 *
 * @note  Set a callback being called on receive view group cluster response. The callback will
 *  be provided with all data necessary for correct attribute handling.
 * @param[in] endpoint A specific endpoint
 * @param[in] cb View group cluster callback that user used refer to esp_zb_view_group_resp_callback_t
 *
 */
void esp_zb_groups_view_group_resp_cb(uint8_t endpoint, esp_zb_view_group_resp_callback_t cb);

/**
 * @brief   Set the ZCL groups cluster get group membership response callback for specific endpoint for client.
 *
 * @note  Set a callback being called on receive get group cluster membership response. The callback will
 *  be provided with all data necessary for correct attribute handling.
 * @param[in] endpoint A specific endpoint
 * @param[in] cb Get group cluster membership callback that user used refer to esp_zb_get_group_membership_resp_callback_t
 *
 */
void esp_zb_groups_get_group_membership_resp_cb(uint8_t endpoint, esp_zb_get_group_membership_resp_callback_t cb);

/**
 * @brief   Set the ZCL scenes cluster get scene information response callback for specific endpoint for client.
 *
 * @param[in] endpoint A specific endpoint
 * @param[in] cb Get scenes cluster view scene callback that user used can refer to esp_zb_zcl_scenes_view_scene_resp_callback_t
 *
 */
void esp_zb_scenes_view_scene_resp_cb(uint8_t endpoint, esp_zb_zcl_scenes_view_scene_resp_callback_t cb);

/**
 * @brief   Set the ZCL scenes cluster store command callback for server.
 *
 * @note  Set a callback (optional) being called on receive scenes store command. The callback provides the
 *  content of exactly extension field stored to the scenes table.
 * @param[in] cb A scenes cluster store callback that user used refer to esp_zb_scenes_store_cmd_callback_t
 *
 */
void esp_zb_device_add_scenes_store_cmd_cb(esp_zb_scenes_store_cmd_callback_t cb);

/**
 * @brief Set the ZCL scenes cluster scene table for users.
 *
 * @param[in] group_id          The group id of scene, which will be used to find scenes table record
 * @param[in] scene_id          The scene id of scene, which will be used to find scenes table record
 * @param[in] transition_time   The transition time of scene, whose unit is 100 milliseconds
 * @param[in] field             The pointer to zcl senes extension field list
 * @return
 *      - ESP_OK: on success
 *      - ESP_FAIL: the group id or scene id is invalid
 */
esp_err_t esp_zb_zcl_scenes_table_store(uint16_t group_id, uint8_t scene_id, uint16_t transition_time, esp_zb_zcl_scenes_extension_field_t *field);

/**
 * @brief   Set the ZCL scenes cluster recall command callback for server.
 *
 * @note  Set a callback (optional) being called on receive scenes recall command. The callback provides the
 *  content of exactly extension field is recalled from the scenes table.
 * @param[in] cb A scenes cluster recall callback that user used refer to esp_zb_scenes_recall_cmd_callback_t
 *
 */
void esp_zb_device_add_scenes_recall_cmd_cb(esp_zb_scenes_recall_cmd_callback_t cb);

/**
 * @brief View the zcl scene table
 *
 */
void esp_zb_zcl_scenes_table_show(void);

/**
 * @brief Set the ZCL IAS Zone to handle the received enroll response command for server.
 *
 * @param cb A ias zone cluster enroll response callback that user used refer to esp_zb_ias_zone_enroll_response_callback_t
 *
 */
void esp_zb_device_add_ias_zone_enroll_response_cb(esp_zb_ias_zone_enroll_response_callback_t cb);


/**
 * @brief Set callback for getting the Level Control current level.
 *
 * @param cb A level control set value callback that user used refer to esp_zb_level_control_set_value_callback_t
 *
 */
void esp_zb_device_add_level_control_set_value_cb(esp_zb_level_control_set_value_callback_t cb);

/**
 * @brief   Set the ZCL OTA upgrade status callback for client.
 *
 * @note  Set a callback being called on receive OTA upgrade response. The callback will
 *  be provided with all data necessary for correct attribute handling.
 * @param[in] cb A device callback that user used refer to esp_zb_ota_upgrade_status_callback_t
 *
 */
void esp_zb_device_add_ota_upgrade_status_cb(esp_zb_ota_upgrade_status_callback_t cb);

/**
 * @brief   Set the ZCL customized cluster command request callback for specific endpoint.
 *
 * @note  Set a callback being called on receive customized cluster command request. The callback will
 *  be provided with all data necessary for correct attribute handling.
 * @param[in] endpoint A specific endpoint
 * @param[in] cluster_id A customized cluster id
 * @param[in] cb A customized cluster callback that user used refer to esp_zb_custom_cluster_cmd_callback_t
 *
 */
void esp_zb_add_custom_cluster_command_cb(uint8_t endpoint, uint16_t cluster_id, esp_zb_custom_cluster_cmd_callback_t cb);

/**
 * @brief   Set the Command line interface (CLI) handler callback for specific endpoint.
 *
 * @note  Set a command handler callback for handle response from other device to CLI device.
 * @param[in] endpoint A specific endpoint
 * @param[in] cb A CLI command handler callback that user used refer to esp_zb_cli_resp_callback_t
 *
 */
void esp_zb_add_cli_resp_handler_cb(uint8_t endpoint, esp_zb_cli_resp_callback_t cb);

/**
 * @brief   Set the ZCL identify notify callback for specific endpoint.
 *
 * @note  Set a callback for user to handle identify command.
 *
 * @param[in] endpoint A specific endpoint
 * @param[in] cb A identify notify callback that user used
 *
 */
void esp_zb_add_identify_notify_cb(uint8_t endpoint, esp_zb_identify_notify_callback_t cb);

/**
 * @brief Add a callback and the privilege command the Zigbee cluster in endpoint.
 *
 * @note The privilege command will skip the Zigbee stack and be exposed to users by the callback indirectly.
 *       Allowing different commands to use the same callback.
 *
 * @param[in] endpoint The specific endpoint for @p cluster
 * @param[in] cluster The specific cluster for @p command
 * @param[in] command The specific command ID is required to handle for users.
 * @param[in] cb The callback refers to esp_zb_privilege_command_callback_t callback will be called, when application layer receives the @p command
 *
 */
void esp_zb_add_cluster_privilege_command_cb(uint8_t endpoint, uint16_t cluster, uint16_t command, esp_zb_privilege_command_callback_t cb);

/**
 * @brief Delete the privilege command from the @p cluster of @p endpoint
 *
 * @param[in] endpoint The specific endpoint for @p cluster
 * @param[in] cluster The specific cluster for @p command
 * @param[in] command The specific command ID will be deleted so that the stack will handle the command rather than user.
 * @return
 *      -   True: On success
 *      -   False: Nothing to delete
 */
bool esp_zb_delete_cluster_privilege_command(uint8_t endpoint, uint16_t cluster, uint16_t command);

/**
 * @brief Set a callback to handle the received ias zone enroll request command for client.
 *
 * @param endpoint A specific endpoint
 * @param cb A ias zone cluster enroll request callback that user used refer to esp_zb_ias_zone_enroll_request_callback_t
 *
 */
void esp_zb_add_ias_zone_enroll_request_cb(uint8_t endpoint, esp_zb_ias_zone_enroll_request_callback_t cb);

/**
 * @brief Set a callback to handle the received ias zone status change notification for client.
 *
 * @param endpoint A specific endpoint
 * @param cb A ias zone cluster zone status change notification callback that user used refer to esp_zb_ias_zone_status_notification_cmd_callback_t
 *
 */
void esp_zb_add_ias_zone_status_notification_cb(uint8_t endpoint, esp_zb_ias_zone_status_notification_cmd_callback_t cb);

/**
 * @brief  Set BDB commissioning mode.
 *
 * @param[in] commissioning_mode commissioning mode that refer to esp_zb_bdb_commissioning_mode_mask_t.
 *
 */
void esp_zb_set_bdb_commissioning_mode(esp_zb_bdb_commissioning_mode_mask_t commissioning_mode);

/* ZCL attribute, cluster, endpoint, device related */

/**
 * @brief Register a Zigbee device.
 *
 * @param[in] ep_list  An endpoint list which wants to register @ref esp_zb_ep_list_s
 *
 * @return
 *      - ESP_OK on success
 *
 */
esp_err_t esp_zb_device_register(esp_zb_ep_list_t *ep_list);

/**
 * @brief  Zigbee stack minior initialization for RCP.
 *
 * @warning It is ONLY for RCP initialization for limited Zigbee stack init
 */
void esp_zb_rcp_init(void);

/**
 * @brief  Zigbee main loop iteration for RCP
 *
 * @warning It is ONLY for RCP main loop iteration.
 *
 */
void esp_zb_rcp_main_loop_iteration(void);

#ifdef ZB_DISTRIBUTED_SECURITY_ON
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
#endif

/**
 * @brief Set the sleep threshold on the device. When the scheduler detects that the device can enter sleep mode, it will notify the application with the signal ESP_ZB_COMMON_SIGNAL_CAN_SLEEP.
 * The device cannot enter sleep mode when the sleep interval is less than this threshold.
 * Default sleep threshold is 20 milliseconds, beacuse do not sleep when it is less then 1 Beacon Interval to wake up.
 *
 * @param[in] threshold_ms Sleep threshold in milliseconds
 *
 * @return ESP_OK if new threshold is valid and applied.
 * @return ESP_FAIL if the user attempts to set a threshold greater than ESP_ZB_SLEEP_MAXIMUM_THRESHOLD_MS or less than ESP_ZB_SLEEP_MINIMUM_THRESHOLD_MS.
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

#ifdef __cplusplus
}
#endif
