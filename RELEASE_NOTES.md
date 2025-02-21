# Espressif Zigbee SDK Release Notes

## 21-Feb-2025
1.6.4 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.3.2

### Features
- Added support to trigger the ZCL general command response callback of cluster server direction 

### Bug Fixes
- Fixed the APS fragment hang issue when multiple fragment frames are scheduled before the previous fragment transaction is completed

### Changes
- Updated esp-zboss-lib to v1.6.4
- Updated esp-zigbee-lib to v1.6.4
- Moved platform configuration files to esp-zigbee-lib


## 14-Feb-2025
1.6.3 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.3.2

### Features
- Added API support for touchlink to configure the key bitmask
- Added APIs support for APSME to send transport key and switch key
- Added API support for MAC to intercept the IEEE802.15.4 frame
- Added detailed usage information for application signals in `esp_zb_app_signal_type_t`.
- Added the payload definitions of `ESP_ZB_COMMON_SIGNAL_CAN_SLEEP`, `ESP_ZB_ZDO_DEVICE_UNAVAILABLE`, `ESP_ZB_NLME_STATUS_INDICATION`
  and `ESP_ZB_NWK_SIGNAL_DEVICE_ASSOCIATED`signals
- Optimized the route discovery mechanism to prevent the neighbor from expiring immediately upon receiving its forwarded frame

### Bug Fixes
- Fixed the missing mandatory `present_value` attribute in binary input cluster
- Fixed the incorrect default value of `ESP_ZB_ZCL_THERMOSTAT_LOCAL_TEMPERATURE_DEFAULT_VALUE` by changing it to `FF`
- Fixed the potential buffer overflow when the ZCL write, report, or custom request needs to be fragmented for transmission
- Fixed the APSDE-DATA confirm crashing issue when the APSDE-DATA command is sent in binding mode
- Fixed the Touchlink issue where the `scan_request` would be handled when the device was not in Touchlink target commissioning mode
- Fixed the Touchlink issue where the first commissioning would always fail when the Touchlink initiator was in
  `ESP_ZB_BDB_MODE_INITIALIZATION | ESP_ZB_BDB_TOUCHLINK_COMMISSIONING` mode
- Fixed the Touchlink issue where the initiator could not exit commissioning if the response from the target was not received
- Fixed the Touchlink issue where commissioning always failed when the initiator acting as a router failed to find a target


### Changes
- Updated esp-zboss-lib to v1.6.3
- Updated esp-zigbee-lib to v1.6.3
- Removed the unused application signal type from `esp_zb_app_signal_type_t`

## 14-Jan-2025
1.6.2 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.3.2

### Features
- Added support to configure the nwkLinkStatusPeriod
- Added support to configure the MAC CSMA-CA parameters
- Added support for ZCL to control reporting of float data by configuring the delta in reporting_info
- Added support to configure the trace log at runtime
- Adjusted the BDB and ZDO trace log levels to make them more concise and intuitive

### Bug Fixes
- Fixed the buffer leak issue when using `esp_zb_scheduler_user_alarm_cancel()`
- Fixed the trigger condition for `ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_RESP_CB_ID` to ensure it only triggers when the command direction matches the cluster role
- Fixed the issue where `get_scene_membership` and `view_scene` requests with non-zero group IDs did not receive correct responses
- Fixed the issue where `esp_zb_zcl_command_send_status_callback_t` triggers an error message when a ZCL command is sent in a mode other than `ESP_ZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT`
- Fixed the issue where the pre-configured link key set by `esp_zb_secur_TC_standard_preconfigure_key_set()` does not take effect when the device recommissions
- Fixed an issue where the router would no longer allow new devices to join the network after reaching the max_child limit, even if some previously joined devices had left the network
- Fixed unexpected crashes on the coordinator when numerous devices are joining at the same time

### Changes
- Updated esp-zboss-lib to v1.6.2
- Updated esp-zigbee-lib to v1.6.2


## 05-Dec-2024
1.6.1 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.3.2

### Features
- Added support for APS to send data requests in parallel to multiple devices
- Added support for ZCL dehumidification control cluster
- Added support for ZCL OTA upgrade cluster to process commands with wildcard parameters
- Added support for APP to configure Zigbee non-volatile memory by setting the size of zb_storage partition
- Added support for ESP32C6 and ESP32C5 to communicate via radio spinel
- Added API to enable/disable install code only mode at runtime

### Bug Fixes
- Fixed the crash on coordinator when numerous devices attempt to associate with the network simultaneously
- Fixed the crash caused by insufficient delayed buffers for MAC transactions
- Fixed the infinite loop issue when the tx queue is no sufficient on ZB_RADIO_SPINEL_UART enabled device
- Fixed the issue where APS fragments could not be sent again after a previous fragment is not acked
- Fixed the rejoin issue for Touchlink initiator when attempting to start the network with the second target
- Fixed the issue where ZDO mgmt LQI req will not trigger user_cb when the response neighbor table is empty

### Changes
- Updated esp-zboss-lib to v1.6.1
- Updated esp-zigbee-lib to v1.6.1
- Rename `ESP_ZB_ZCL_CLUSTER_ID_DEHUMID_CONTROL` to `ESP_ZB_ZCL_CLUSTER_ID_DEHUMIDIFICATION_CONTROL`


## 01-NOV-2024
1.6.0 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.3.1

### Features
- Added support for the extended responses to ZDO nwk_addr_req and ieee_addr_req commands
- Added support for ZCL to add attribute with manufacturer code
- Added support for ZCL to send general request with manufacturer code, direction and disable default response options.
- Added support for ZCL to report error status for each record in the read reporting configuration response

### Bug Fixes
- Fixed the error datatype for the `time` and `time_status` member of `esp_zb_time_cluster_cfg_t`
- Fixed the issue where the Touchlink initiator couldn't rejoin the network on the commissioning channel
- Fixed the crash occurring when the touchlink initiator recommissioned after a rejoin failure
- Fixed the issue that certain NWK requests were still encrypted when nwkSecurityLevel was 0

### Changes
- Updated esp-zboss-lib to v1.6.0
- Updated esp-zigbee-lib to v1.6.0
- Added the `manuf_specific`, `direction`, `dis_default_resp` and `manuf_code` options to ZCL general commands. 

### Breaking Changes
- Removed the `esp_zigbee_cli` support
- Redefined the callback type for `esp_zb_zdo_ieee_addr_req()` and `esp_zb_zdo_nwk_addr_req()`
- Redefined the `esp_zb_zcl_cmd_read_report_config_resp_message_t` struct


## 12-Oct-2024
1.5.1 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.1.4

### Features
- Added support for ZDO mgmt LQI request and response API
- Added support for ZDO network address request and response API
- Added support for Touchlink to set the extended PAN ID during commissioning
- Added support for ZCL demand response and load control cluster
- Added support for ZCL thermostat weekly schedule
- Added support to send APS request by long address
- Added API to enable/disable network security
- Added API to retrieve the detailed version of the SDK at runtime
- Added the esp32c5 support based on the esp-idf master

### Bug Fixes
- Fixed the compilation warning originating from `ESP_ZB_PACKED_STRUCT union` in `esp_zigbee_type.h`
- Fixed the bug where an invalid attribute was added to the attribute list even when an error occurred
- Fixed the issue where excess link status records were delayed and sent in the next period when the device had more than 26 neighbors
- Fixed the crashing issue that occurred when the target device rebooted after touchlink commissioning had completed but no devices had joined

### Changes
- Updated esp-zboss-lib to v1.5.1
- Updated esp-zigbee-lib to v1.5.1
- Change the member of `esp_zb_apsde_data_req_t` from `uint16_t dst_short_addr;` to `esp_zb_addr_u dst_addr;`


## 27-Aug-2024
1.5.0 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.1.4

### Features
- Added support for ZCL OTA upgrade optional header setting
- Added support for ZCL OTA upgrade frame fragmentation
- Added support for ZCL light sensor device
- Added support for ZCL pH measurement cluster
- Added support for ZCL electrical conductivity measurement cluster
- Added support for ZCL gateway endpoint without a client cluster to handle report attribute commands
- Added support for NWK maximum children setting

### Bug Fixes
- Fixed the issue with syncing ZCL diagnostic cluster attributes with the stack
- Fixed the crashing issue caused by the RX queue being busy when enabling ZB_RADIO_SPINEL_UART
- Fixed the unexpected delay in setpoint execution when using the thermostat cluster weekly schedule
- Fixed the incorrect check for the minimum dead band of the thermostat cluster
- Fixed the invalid endpoint ID in some core action messages

### Changes
- Updated esp-zboss-lib to v1.5.0
- Updated esp-zigbee-lib to v1.5.0
- Optimized ZCL OTA upgrade rate
- Deprecated `esp_zb_main_loop_iteration()`; use `esp_zb_stack_main_loop()` instead
- Unified the MACRO format for the default attributes of carbon dioxide, PM2.5, temperature, flow, and humidity measurement clusters

### Breaking Changes
- Renamed `esp_zb_window_covering_controller_cluster_create()` to `esp_zb_window_covering_controller_clusters_create()`
- Renamed `esp_zb_on_off_switch_cfg_cluster_create()` to `esp_zb_on_off_switch_config_cluster_create()`
- Changed the parameter of `esp_zb_ias_ace_cluster_create()` from `uint8_t` to `esp_zb_ias_ace_cluster_cfg_t *`
- Changed the parameter of `esp_zb_touchlink_commissioning_cluster_create()` from `void` to `esp_zb_touchlink_commissioning_cfg_t *`
- Changed the parameter of `esp_zb_diagnostics_cluster_create()` from `void` to `esp_zb_diagnostics_cluster_cfg_t *`
- Changed the parameter of `esp_zb_price_cluster_create()` from `void` to `esp_zb_price_cluster_cfg_t *`


## 19-Jul-2024
1.4.1 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.1.4

### Features
- Updated esp-zboss-lib to v1.4.1
- Updated esp-zigbee-lib to v1.4.1
- Supported NWK route record getting APIs
- Supported ZCL OTA image query request and response APIs
- Optimized APS maximum valid payload size for non-fragmented frames

### Bug Fixes
- Fixed touchlink assert when the touchlink initiator scans mismatched targets and is required to leave


## 04-Jul-2024
1.4.0 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.1.3

### Features
- Updated esp-zboss-lib to v1.4.0
- Updated esp-zigbee-lib to v1.4.0
- Supported more flexible ZCL data model APIs
- Supported sending ZCL commands without client cluster
- Supported receiving ZCL commands without server cluster for gateway endpoint
- Supported ZDO energy detection
- Supported ZDO scanning of closed networks
- Supported ZCL IAS WD cluster
- Optimized ZCL window covering and controller device type support
- Added ZCL window covering cluster message callback

### Bug Fixes
- Fixed issues with attribute reporting and reading when fragmentation is required

### Note
- Reusing the ZCL Zigbee data model entries is no longer allowed, all attributes/clusters/endpoints have to be created separately
- Deprecated `esp_zb_cluster_list_update_xxx_cluster()` APIs


## 24-May-2024
1.3.2 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.1.3

### Features
- Updated esp-zboss-lib to v1.3.2
- Updated esp-zigbee-lib to v1.3.2
- Supported APS data confirmation
- Supported ZCL IAS ACE cluster
- Supported ZCL read report config command
- Added NWK parameters setting APIs
- Added NWK neighbor table getting APIs
- Added NWK routing table getting APIs
- Added Zigbee scheduler queue size setting API
- Optimized Zigbee device reset mechanism

### Bug Fixes
- Fixed the crash caused by a full rx radio queue during radio frame handling
- Fixed the buffer ID not being freed during rapid on/off level control
- Fixed the issue with the rough transition in color control


## 30-Apr-2024
1.3.1 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.1.3

### Features
- Updated esp-zboss-lib to v1.3.1
- Updated esp-zigbee-lib to v1.3.1

### Bug Fixes
- Fixed the movement transition for color control
- Fixed the jitter of broadcast endpoint handler
- Fixed the failure in Zigbee flash read or write operations


## 26-Apr-2024
1.3.0 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.1.3

### Features
- Updated esp-zboss-lib to v1.3.0
- Updated esp-zigbee-lib to v1.3.0
- Supported ZCL commissioning cluster
- Supported devive sleep before join network
- Supported the parameter of pointer type for scheduler_alarm
- Supported event fd setting in application

### Bug Fixes
- Fixed the transition id checking for touchlink identify command
- Fixed the zdo binding user callback
- Disabled response default command for broadcasted frame
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/276
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/310
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/314
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/318
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/325

### Break Changes
- Renamed `esp_zb_radio_mode_t`, `esp_zb_host_connection_mode_t`, `zb_esp_uart_init_mode` and `esp_zb_serial_mode_t`

## 12-Apr-2024
1.2.3 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.1.3

### Features
- Updated esp-zboss-lib to v1.2.3
- Updated esp-zigbee-lib to v1.2.3
- Added flow measurement cluster support
- Added ZCL manufacturer attribute settings
- Optimized the accuracy for stack timer
- Optimized device handler and endpoint handler for code size
- Optimized ZCL hue and saturation movement method

### Bug Fixes
- Fixed the empty zdo binding table issue
- Fixed the user callback for writing ZCL attributes
- Fixed the enumerated member of pressure measurement cluster
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/305
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/307
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/315

## 29-Mar-2024
1.2.2 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.1.3

### Features
- Updated esp-zboss-lib to v1.2.2
- Updated esp-zigbee-lib to v1.2.2
- Added diagnostics cluster support
- Added meter_identification cluster support
- Added price cluster support
- Added Zigbee network size setting API
- Added Zigbee I/O buffer size setting API
- Added Zigbee binding table size setting API
- Added ZB_DEBUG_MODE option for optimizing the code size of release version library
- Removed ESP_ZB_TRACE_ENABLE option

### Bug Fixes
- Fixed profile id for zcl commands
- Fixed moving value for color control handler
- Fixed reuse issue with endpoint, cluster, and attribute lists
- Fixed issue with Zigbee sleep not waking up via GPIO
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/99
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/269
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/282
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/284
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/285

### Note
- The default network size is set to 64, please use the `esp_zb_overall_network_size_set()` to configure it.
- The default I/O buffer size is set to 80, please use the `esp_zb_io_buffer_size_set()` to configure it.
- The default binging table size is changed to 16, please use the API `esp_zb_aps_src_binding_table_size_set()` and `esp_zb_aps_dst_binding_table_size_set()` to configure it.


## 15-Mar-2024
1.2.1 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.1.3

### Features
- Updated esp-zboss-lib to v1.2.1
- Updated esp-zigbee-lib to v1.2.1
- Added manufacturer code setting API
- Supported the large data transmission for zcl commands

### Bug Fixes
- Fixed mfg tool
- Fixed multiple link key initialization
- Fixed touchlink nwk update request handler
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/202
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/244
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/254


## 8-Mar-2024
1.2.0 version release of ESP-ZIGBEE-SDK is based on esp-idf v5.1.3

### Features
- Updated esp-zboss-lib to v1.2.0
- Updated esp-zigbee-lib to v1.2.0
- Supported to report the level value at each step upon receiving the level change command
- Supported cli to configure green power functionality
- Supported to print assert location
- Supported 64-bit timer for stack
- Supported to configure the multiple pre-configured link key for centralized and distributed network
- Added more optional attributes support for color control

### Bug Fixes
- Fixed the group membership response
- Fixed optional hue attribute for color control
- Fixed the parameters for esp_zb_ep_list_add_ep()
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/83
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/251
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/256

### Break Changes
- The `esp_zb_ep_list_add_ep()` function now utilizes an endpoint configuration structure，instead of multi parameters.


## 22-Feb-2024
1.1.2 version release of ESP-ZIGBEE-SDK

### Features
- Updated esp-zboss-lib to v1.1.2
- Updated esp-zigbee-lib to v1.1.2
- Added on/off off_with_effect, on_with_recall_global_scene and on_with_timed_off command
- Added zcl custom cluster handler update API
- Added device joining network minimum lqi setting API
- Added beacon scan duration setting API
- Changed the minimum custom cluster value to 0x8000

### Bug Fixes
- Fixed green power attribute setting
- Fixed green power device type
- Fixed assert of zcl malformed packet
- Fixed distributed router formation capability, when it reboots
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/212
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/209
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/193


## 6-Feb-2024
1.1.1 version release of ESP-ZIGBEE-SDK

### Features
- Updated esp-zboss-lib to v1.1.1
- Updated esp-zigbee-lib to v1.1.1
- Support touchlink commissioning cluster get group id command and response
- Support touchlink commissioning cluster get endpoint list command and response
- Support touchlink commissioning cluster endpoint information command

### Bug Fixes
- Fixed the color control step loop handler, when step value less than time transition.

## 2-Feb-2024
1.1.0 version release of ESP-ZIGBEE-SDK

### Features
- Updated esp-zboss-lib to v1.1.0
- Updated esp-zigbee-lib to v1.1.0
- Added more commands support for cli example
- Added zigbee stack lock support
- Added reset factory to default APIs
- Added zll identify callback
- Added zigbee device announcement APIs
- Replaced the macsplit of the gateway with Radio Spinel
- Replaced zigbee rcp example with ot-rcp example

### Bug Fixes
- Fixed the error trigger the zcl identify timer upon write_req
- Fixed Zigbee color control downward movement failure
- Fixed Zigbee color control step color failure
- Fixed the scan_response for touchlink scan req handler
- Fixed touchlink transaction id
- Corrected the check for clearing touchlink factory new
- Rectified the logic of touchlink set network key
- Fixed touchlink target does not not send join router response with failure status
- Fixed the erase-NVRAM operation of device leave network for touchlink
- Fixed esp_zigbee_gateway build error on Win11
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/231

## 19-Jan-2024
1.0.9 version release of ESP-ZIGBEE-SDK

### Features
- Updated esp-zboss-lib to v1.0.9
- Updated esp-zigbee-lib to v1.0.9
- Added bdb open network API
- Added apsde user APIs
- Added color control remaining_time(0x0002) attribute support
- Added set and bag data type for custom cluster

### Bug Fixes
- Fixed the effect of fragment for broadcast frame
- Fixed crashing for touchlink initiator device with multi-endpoint
- Fixed data type of esp_zb_zcl_color_move_color_cmd_t
- Fixed data type of esp_zb_ias_zone_cluster_cfg_t
- Fixed rcp failure
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/216
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/221
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/223


## 12-Jan-2024
1.0.8 version release of ESP-ZIGBEE-SDK

### Features
- Updated esp-zboss-lib to v1.0.8
- Updated esp-zigbee-lib to v1.0.8
- Supported Zigbee APS frame fragment
- Supported Zigbee Green Power feature and examples
- Supported nvram 16 bytes alignment
- Added bdb commissioning cancelled APIs
- Refined the mfg tool
- Enabled the 802.15.4 receive done handler feature
- Removed esp32h4 target support

### Bug Fixes
- Maintained the zcl scene table for every endpoint
- Fixed zcl command send status callback
- Fixed the user callback of zcl color control
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/191
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/190
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/82


## 21-Dec-2023
1.0.7 version release of ESP-ZIGBEE-SDK

### Features
- Updated esp-zboss-lib to v1.0.7
- Updated esp-zigbee-lib to v1.0.7
- Supported zcl color mode callback
- Supported set starting value before on command
- Supported zcl send_command_status callback
- Supported zcl default response callback
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/135
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/141
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/142

### Bug Fixes
- Fixed zcl level transition time callback 
- Fixed zigbee touchlink device information request
- Fixed zigbee broadcast table size


## 08-Dec-2023
1.0.6 version release of ESP-ZIGBEE-SDK

### Features
- Updated esp-zboss-lib to v1.0.6
- Updated esp-zigbee-lib to v1.0.6
- Supported the touchink and steering mode
- Supported more APIs for touchlink feature
- Supported the dual-communication for custom cluster
- Supported the 16-bit and 32-bit array for custom attribute

### Bug Fixes
- Fixed zigbee gets group membership crash
- Fixed zigbee gets scene membership crash
- Fixed zigbee touchlink initiator scanning
- Fixed the response of time cluster
- Fixed the valid range for move_to_level command
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/156
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/158


## 23-Nov-2023
1.0.5 version release of ESP-ZIGBEE-SDK

### Features
- Updated esp-zboss-lib to v1.0.5
- Updated esp-zigbee-lib to v1.0.5
- Increased the maximum number of records in the group table to 32
- Increased the maximum number of records in the binding table to 64
- Increased the maximum number of endpoints per device to 64

### Bug Fixes
- Fixed the invalid endpoint ID in the door lock response
- Fixed the effect of the OFF command for the level control cluster
- Fixed the zdo binding table response callback
- Fixed the touchlink primary channel reset
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/150
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/65


## 21-Nov-2023
1.0.4 version release of ESP-ZIGBEE-SDK

### Features
- Update esp-zboss-lib to v1.0.3
- Support Zigbee touchlink and steering switch
- Support the command with on/off of level control cluster
- Add the identify_effect device id callback for user
- Add the identify_effect command
- Add block mechanism for zb osif iteration
- Update example partition table

### Bug Fixes
- Fix the payload of custom cluster
- Fix the data type of zb keep alive

## 10-Nov-2023
1.0.3 version release of ESP-ZIGBEE-SDK

### Features
- Add ZCL door lock cluster callback support
- Add ZCL local report configuration support
- Add the close Zigbee network API
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/137
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/128

### Bug Fixes
- Fix zb nvram bug
- Fix off_with_effect of on/off cluster


## 03-Nov-2023
1.0.2 version release of ESP-ZIGBEE-SDK

### Features
- Update esp-zboss-lib to v1.0.2
- Support the ZCL metering cluster
- Support ZCL custom profile
- Support the ON/OFF command affects the level control cluster
- Update the SDK document for ZCL metering cluster
- Update the esp-idf CI tool

### Bug Fixes
- Fix esp mac issue
- Fix the data type for analog value/input
- Fix zcl custom cluster data type
- Fix zcl general response multiple time
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/36
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/106
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/126


## 20-Oct-2023
1.0.1 version release of ESP-ZIGBEE-SDK

### Features
- Update esp-zboss-lib to v1.0.1
- Support the effect of level control and on/off cluster
- Support to scan all touchlink channels 
- Optimize the Zigbee OTA examples
- Update the Zigbee OTA README.md
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/100
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/72

### Bug Fixes
- Fix the panid setting
- Fix the reading attribute of zcl timer cluster
- Increase the endpoint number in the ZCL group table from 4 to 32


## 10-Oct-2023
1.0.0 version release of ESP-ZIGBEE-SDK

### Features
- Update esp-zboss-lib to v1.0.0
- Update examples README.md
- Add trace log user API
- Add NWK_AGGRESSIVE_ROUTE_ADD_TIME to vendor configuration
- Add ZCL thermostat cluster
- Add ZCL fan control cluster
- Add ZCL thermostat ui config cluster
- Add ZCL analog input cluster
- Add ZCL analog output cluster
- Add ZCL analog value cluster
- Add ZCL carbon dioxide measurement cluster
- Add ZCL pm2.5 measurement cluster
- Add ZCL multistate value cluster
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/36
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/59
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/96

### Bug Fixes
- Fix Zigbee light sleep
- Fix Zigbee ZCL general(read/write/report_config) command
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/102
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/106


## 12-Sep-2023
0.9.5 version release of ESP-ZIGBEE-SDK

### Features
- Add zigbee trace support
- Add zigbee assert support


## 8-Sep-2023
0.9.4 version release of ESP-ZIGBEE-SDK

### Features
- Update esp-zboss-lib to v0.7.0
- Add zigbee discover attribtues support

### Bug Fixes
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/91
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/55


## 30-Aug-2023
0.9.3 version release of ESP-ZIGBEE-SDK

### Features
- Add zigbee action event mechanism.
- Add more support for Zigbee zcl common command.
- Add zigbee zcl scene response support.
- Optimize the Zigbee endpoint handler implementation.
- Optimize the custom cluster implementation.
- Move the active_scan_complete_req to zdo layer

### Bug Fixes
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/48
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/70


## 29-Aug-2023
0.9.2 version release of ESP-ZIGBEE-SDK

### Features
- Add zigbee sleep feature support
- Add zigbee sleepy end device example


## 25-Aug-2023
0.9.1 version release of ESP-ZIGBEE-SDK

### Features
- Add the Zigbee device sends command to itself support in non-network state.
- Add the short address maps ieee address API.

### Bug Fixes
- Fix the custom cluster request command without size field.
- Fix the wrong printing of IEEE address for CLI
- Fix the byte order for long address


## 11-Aug-2023
0.9.0 version release of ESP-ZIGBEE-SDK

### Features
- Fix Zigbee zdo simple desc list
- Add more Zigbee parameters configuration option
- Add distribute network support
- Optimize the zcl device cb id implementation
- Add non-volatile scene table

### Bug Fixes
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/40
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/57
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/67
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/68
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/69


## 2-Aug-2023
0.8.0 version release of ESP-ZIGBEE-SDK

### Features
- Add touchlink feature support
- Add touchlink example


## 28-July-2023
0.7.2 version release of ESP-ZIGBEE-SDK

### Features
- Add security network key getting API
- Add zdo bind table request command
- Add more zcl color control command support
- Enlarge mac rx queue size
- Support more endpoints on Zigbee device
- Support more types of custom cluster
- Add scene cluster view command response
- Add scene cluster for prompts
- Optimize the scene cluster implementation

### Bug Fixes
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/51
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/53


## 14-July-2023
0.7.1 version release of ESP-ZIGBEE-SDK

### Features
- Fix the process of privilege command handler
- Add ias zone cluster request, response and notification handler
- Add method to match common cluster
- Fix compile warnings

### Bug Fixes
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/42


## 30-June-2023
0.7.0 version release of ESP-ZIGBEE-SDK

### Features
- add zb privilege command support
- add ESP-Thread-Border/Zigbee-Gateway Board V1.2 support
- use ESP_ZB_TRANSCEIVER_ALL_CHANNELS_MASK as zb end device primary channel mask
- Examples support the ESP-Thread-Border/Zigbee-Gateway Board V1.2

### Bug Fixes
- fix zb zcl ias zone cmd crash
- fix node des callback issue
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/34
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/38


## 16-June-2023
0.6.2 version release of ESP-ZIGBEE-SDK

### Features
- support active scan available PAN
- add illuminance measurement cluster
- add pressure measurement cluster
- add electrical measurement cluster
- add window covering cluster
- add occupancy sensing cluster

### Bug Fixes
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/20


## 9-June-2023
0.6.1 version release of ESP-ZIGBEE-SDK

### Features
- stringify zigbee app signal
- register attribute from local variable to static

### Bug Fixes
- fix callback for custom cluster
- fix end device distributed key setting
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/25
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/27


## 26-May-2023
0.6.0 version release of ESP-ZIGBEE-SDK

### Features
- add TC standard distributed and pre-configured key settings
- add TC link key exchange setting
- add zb tx power setting
- add destination endpoint to report callback
- enable write callback for custom cluster

### New Changes
- Examples under esp-zigbee-sdk would use management component registry to download both esp-zigbee-lib and esp-zboss-lib.

### Bug Fixes
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/21
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/22
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/23
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/24
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/25


## 6-April-2023
0.5.4 version release of ESP-ZIGBEE-SDK

### Features
- provide set PANID api
- provide humidity, power config cluster, with docs update
- support group bind
- support zigbee gateway (wifi, zigbee coexist) on single chip C6 solution

### Bug Fixes
- fix the ZCL report command source address alignment issue
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/7
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/10
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/8
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/11


## 17-Mar-2023
0.5.3 version release of ESP-ZIGBEE-SDK

### Features
- Add More cluster (ias zone, on_off_switch_configuration binary_input) support
- support ESP32-H2 MP chip

### Bug Fixes
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/6


## 28-Feb-2023
0.5.2 version release of ESP-ZIGBEE-SDK

### Features
- add the API for hue/saturation command and attribute callback support
- add the API for report attribute

### Bug Fixes
- fix the issue https://github.com/espressif/esp-zigbee-sdk/issues/4
- fix the issue https://github.com/espressif/esp-zigbee-sdk/issues/5


## 10-Feb-2023
0.5.1 version release of ESP-ZIGBEE-SDK

### Features
- Add new API for ZDO and ZCL
- Delete the API esp_zb_set_network_channel
- Add the API for esp_zb_set_primary_network_channel_set/ esp_zb_set_secondary_network_channel_set
- Add the API for get current channel
- Add the API for set ZCL attribute
- Add more clusters for cli example to support dimmable light example for pytest

### Bug Fixes
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/1
- Closes: https://github.com/espressif/esp-zigbee-sdk/issues/3
- Closes: https://github.com/espressif/esp-idf/issues/10662


## 1-Feb-2023
0.5.0 version release of ESP-ZIGBEE-SDK

### Features
- Add timeout handler mechanism for user
- Minor type name updates
- Partition table adjustment for examples
- ZDO related API requests and callbacks update with new argument


## 23-Dec-2022
0.4.1 version release of ESP-ZIGBEE-SDK

### Features
- esp-zigbee-lib version updated to 0.4.1
- Add support for esp32c6
- Update examples to support esp32c6
- Add esp32c6 target in CI test

### Bug Fixes
- Bug fixed for rcp_incompatible_switch_port


## 14-Dec-2022
0.4.0 version release of ESP-ZIGBEE-SDK

### Features
- esp-zigbee-lib version updated to 0.4.0
- Add example for ota upgrade process
- Add README.md for ota upgrade process
- Add docs for ota api-reference
- Add ota example in CI test
- Add scene cluster commands
- Update the template file for MR process
- Add APIs for ota upgrade cluster to ensure the ota upgrade process

### Bug Fixes
- Bug fixed for buffer length issue on customized cluster command


## 28-July-2022
Initial version release of ESP-ZIGBEE-SDK

### Features
- HA standard:
	Standard Home Automation devices setting and build up
- ZCL:
	Provide the ZCL common and cluster specific command
- ZDO:
	Varieties of the ZDO command
- Security:
	Zigbee security support to install code related function
- NWK:
	Zigbee stack related function to support ZC, ZR and ZED
- CORE:
	Zigbee device hardware platform configuration setting related function, customized attribute, cluster and endpoint API
