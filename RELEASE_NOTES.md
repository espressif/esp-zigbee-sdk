# Espressif Zigbee SDK Release Notes

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
