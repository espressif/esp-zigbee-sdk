/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "zboss_api.h"
#include "esp_zigbee_type.h"
#include "esp_zigbee_attribute.h"
#include "esp_zigbee_cluster.h"
#include "esp_zigbee_endpoint.h"
#include "esp_zigbee_zcl_command.h"
#include "esp_zigbee_zdo_command.h"
#include "esp_zigbee_secur.h"

/** Enum of the Zigbee network device type
 * @anchor esp_zb_nwk_device_type_t
 */
typedef enum {
    ESP_ZB_DEVICE_TYPE_COORDINATOR = 0x0,       /*!<  Device - Coordinator */
    ESP_ZB_DEVICE_TYPE_ROUTER  = 0x1,           /*!<  Device - Router */
    ESP_ZB_DEVICE_TYPE_ED = 0x2,                /*!<  Device - End device */
    ESP_ZB_DEVICE_TYPE_NONE = 0x3,              /*!<  Unknown Device */
} esp_zb_nwk_device_type_t;

/** ZCL set attribute callback
 *
 * @param[in] status The status for ZCL set attribute 0 - status success
 * @param[in] endpoint The endpoint of this cluster lists
 * @param[in] cluster_id Cluster ID
 * @param[in] attr_id Attribute ID
 * @param[in] value The pointer of the attribute data
 *
 * @note The Zigbee device callback is the default ZCL cluster handler to notify the application about a certain event.
 * It covers attribute changes like on-off, level and color cluster.
 */
typedef void (*esp_zb_set_attr_callback_t)(uint8_t status, uint8_t endpoint, uint16_t cluster_id, uint16_t attr_id, void *value);

/** ZCL basic cluster command reset to factory default callback
 *
 * @param[in] status The status for ZCL reset factory 0 - status success
 * @param[in] endpoint The endpoint of this cluster lists
 *
 * @note The Zigbee device callback is default ZCL cluster handlers to notify the application about a certain event
 * like all clusters / attributes are set to default.
 * @note By using refer to esp_zb_zcl_get_attribute(), user could check the specific cluster / attribute value, certain device action may apply based on user
 * application.
 */
typedef void (*esp_zb_basic_reset_callback_t)(uint8_t status, uint8_t endpoint);

/** Report attribute callback
 *
 * @brief A report attribute callback for user to get report info
 *
 * @param[in] addr A struct of address contains short and ieee address @ref esp_zb_zcl_addr_s
 * @param[in] ep  An endpoint which comes from report device
 * @param[in] cluster_id Cluster id that reported
 * @param[in] attr_id  Attribute id that reported
 * @param[in] attr_type Attribute data type refer to zb_zcl_common.h zcl_attr_type
 * @param[in] value A pointer to the attribute data value
 *
 */
typedef void (*esp_zb_report_attr_callback_t)(
    esp_zb_zcl_addr_t *addr, uint8_t ep, uint16_t cluster_id, uint16_t attr_id, uint8_t attr_type, void *value);

/** Read attribute callback
 *
 * @brief A read attribute callback for user to get read info.
 *
 * @param[in] status   Status of the read attribute response refer to zb_zcl_common.h 0 - status success
 * @param[in] attr_id  Attribute id that reported
 * @param[in] attr_type Attribute data type refer to zb_zcl_common.h zcl_attr_type
 * @param[in] value A pointer to the attribute data value
 *
 */
typedef void (*esp_zb_read_attr_resp_callback_t)(uint8_t status, uint16_t attr_id, uint8_t attr_type, void *value);

/** Identify callback
 *
 * @param[in] identify_on A indication that need start identify or stop
 *
 */
typedef void (*esp_zb_identify_notify_callback_t)(uint8_t identify_on);

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
typedef struct esp_zb_cfg_s{
    esp_zb_nwk_device_type_t esp_zb_role;           /*!< The nwk device type */
    bool   install_code_policy;                     /*!< Allow install code security policy or not */
    union {
        esp_zb_zczr_cfg_t   zczr_cfg;               /*!< The Zigbee zc/zr device configuration */
        esp_zb_zed_cfg_t    zed_cfg;                /*!< The Zigbee zed device configuration */
    } nwk_cfg;                                      /*!< Union of the network configuration */
} esp_zb_cfg_t;

/********************* Declare functions **************************/
/**
 * @brief  Zigbee stack initialization.
 *
 * @note To be called inside the application's main cycle at start.
 * @note Default network channel is set to 13, if esp_zb_set_network_channel() not called or
 * no product config setting refer to tools/mfg_tool.
 * @note Default is no NVRAM erase from start up, user could call factory reset for erase NVRAM and other action please refer esp_zb_factory_reset().
 * @note Make sure to use correct corresponding nwk_cfg with your device type @ref esp_zb_cfg_s.
 * @anchor esp_zb_init
 * @param[in] nwk_cfg   The pointer to the initialization Zigbee configuration
 *
 */
void esp_zb_init(esp_zb_cfg_t *nwk_cfg);

/**
 * @brief   Set the Zigbee device network channel.
 *
 * @note  This function should be run AFTER @ref esp_zb_init is called, if the user wants to set a specific channel
 * without reading channel setting from flash refer to tools/mfg_tool.
 * @note  Default network channel is set to 13, if esp_zb_set_network_channel is not called.
 *
 * @param[in] channel Enabling which channel ranging from 11 - 26, frequency ranging from 2405 MHz to 2480 MHz
 * @return 0 - ESP_OK  invalid channel- ESP_ERR_INVALID_ARG
 */
esp_err_t esp_zb_set_network_channel(uint8_t channel);

/**
 * @brief   Set the Zigbee device long address.
 *
 * @note  Set this function AFTER @ref esp_zb_init called, if user wants to set specific address
 * without reading MAC address from flash refer to tools/mfg_tool or eFUSE.
 *
 * @param[in] addr Pointer of long address
 * @return 0 - ESP_OK
 */
esp_err_t esp_zb_set_long_address(esp_zb_ieee_addr_t addr);

/**
 * @brief   Get the Zigbee device long address.
 *
 * @note Thie function will return a pointer to 64-bit of ieee long address.
 *
 * @param[out] addr pointer of long address
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
 * @brief   Get the Zigbee network extended PAN ID.
 *
 * @note This function will return back a pointer to 64-bit of extended PAN ID.
 *
 * @param[out] ext_pan_id pointer of extended PAN ID
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
 * @brief  Start top level commissioning procedure with specified mode mask.
 *
 * @param[in] mode_mask - commissioning modes refer to ZB_BDB_SIGNAL_STEERING and ZB_BDB_SIGNAL_FORMATION
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
 * complete, zboss_signal_handler callback() is called, so application will know when to do
 * some useful things.
 *
 * @note No-autostart mode: It initializes scheduler and buffers pool, but not MAC and upper layers.
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
 *
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
 * @brief   Set the ZCL identify notify callback for specific endpoint.
 *
 * @note  Set a callback for user to handle identify command.
 *
 * @param[in] endpoint A specific endpoint
 * @param[in] cb A identify notify callback that user used
 *
 */
void esp_zb_add_identify_notify_cb(uint8_t endpoint, esp_zb_identify_notify_callback_t cb);

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

#ifdef __cplusplus
}
#endif
