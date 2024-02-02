| Supported Targets | ESP32 | ESP32-C3 | ESP32-C6 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- |

# Gateway Example

This example demonstrates how to build a Zigbee Gateway device. It runs on a Wi-Fi SoC such as ESP32, ESP32-C3 and ESP32-S3, with an 802.15.4 SoC like ESP32-H2 running [ot_rcp](https://github.com/espressif/esp-idf/tree/master/examples/openthread/ot_rcp) to provide 802.15.4 radio.

## Hardware Required

* One development board with ESP32 or ESP32-S3 SoC acting as Zigbee gateway (loaded with esp_zigbee_gateway example)
* A USB cable for power supply and programming
* Five jumper wires for UART (TX, RX, RST, BOOT and GND)
* Gateway doesn't function alone. Choose ESP32-H2 as rcp (see [ot_rcp example](https://github.com/espressif/esp-idf/tree/master/examples/openthread/ot_rcp))
* **Flash** Zigbee rcp on the ESP32-H2 DevKitC first **before** connecting to Zigbee gateway, if auto rcp update feature is disable.
* Connect the two SoCs via UART, below is an example setup with ESP32-DevKitC and ESP32-H2-DevKitC:
![Zigbee_gateway](zigbee-gateway-esp32-esp32h2.jpg)

### Standalone Modules

The SDK supports manually connecting an ESP32-H2 RCP to an ESP32 series Wi-Fi SoC. Extra two jumper wires needed for RESET (RST) and BOOT based on the picture above. As one way of connection is following:

ESP32 pin     | ESP32-H2 pin
------------- |-------------
   GND        |    G
   GPIO4 (RX) |    TX
   GPIO5 (TX) |    RX
   GPI017     |    RST
   GPIO18     |    GPIO9(BOOT)

TX, RX, RST and BOOT pin from ESP32 side can be configured by user in `idf.py menuconfig` under menu "ESP Zigbee gateway rcp update".

TX, RX pins from ESP32-H2 should be configured in [ot_rcp example](https://github.com/espressif/esp-idf/tree/master/examples/openthread/ot_rcp) via "OpenThread RCP Example > Configure RCP UART pin manually" options.

Other pin number is also available for user to configure if needed.

### ESP Thread Border Router Board

The ESP Thread border router board provides an integrated module of an ESP32-S3 SoC and an ESP32-H2 RCP.

![br_dev_kit](../../docs/_static/esp-thread-border-router-board.png)

The two SoCs are connected with following interfaces:
* UART and SPI for serial communication
* RESET and BOOT pins for RCP Update
* 3-Wires PTA for RF coexistence

No jumper wires needed. No `idf.py menuconfig` under menu "ESP Zigbee gateway rcp update" configure to change.

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Create the RCP firmware image

The esp_zigbee_gateway supports updating the RCP image. Generate rcp image before building the esp_zigbee_gateway example.

Build the [ot_rcp](https://github.com/espressif/esp-idf/tree/master/examples/openthread/ot_rcp) example. Later in the esp_zigbee_gateway building process, the built RCP image will be automatically packed into the esp_zigbee_gateway firmware. See detail in [CMakeLists.txt](main/CMakeLists.txt).

Notes:
- `OPENTHREAD_NCP_VENDOR_HOOK` of `ot_rcp` should be selected via menuconfig.

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

As you run the example, you will see the following log:

```
I (4438) esp_netif_handlers: example_netif_sta ip: 192.168.201.120, mask: 255.255.252.0, gw: 192.168.200.1
I (4438) example_connect: Got IPv4 event: Interface "example_netif_sta" address: 192.168.201.120
I (4498) example_connect: Got IPv6 event: Interface "example_netif_sta" address: fe80:0000:0000:0000:3685:18ff:fe7e:74b4, type: ESP_IP6_ADDR_IS_LINK_LOCAL
I (4498) example_common: Connected to example_netif_sta
I (4508) example_common: - IPv4 address: 192.168.201.120,
I (4508) example_common: - IPv6 address: fe80:0000:0000:0000:3685:18ff:fe7e:74b4, type: ESP_IP6_ADDR_IS_LINK_LOCAL
I (4518) wifi:Set ps type: 0, coexist: 0

I (4588) RCP_UPDATE: RCP: using update sequence 0
I (4588) main_task: Returned from app_main()
I (4618) ESP_ZB_GATEWAY: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (4638) ESP_ZB_GATEWAY: Zigbee stack initialized
I (4668) ESP_ZB_GATEWAY: Zigbee rcp device booted
I (4668) ESP_ZB_GATEWAY: Running RCP Version: zigbee-54f0517724-f371cda-1.0.0-2023-10-10 06:17:54 UTC
I (4668) ESP_ZB_GATEWAY: Storage RCP Version: zigbee-54f0517724-f371cda-1.0.0-2023-10-10 06:17:54 UTC
I (4678) ESP_ZB_GATEWAY: *** MATCH VERSION! ***
I (5608) wifi:<ba-add>idx:0 (ifx:0, 9c:3a:9a:04:18:92), tid:0, ssn:0, winSize:64
I (5628) ESP_ZB_GATEWAY: Start network formation
I (7958) ESP_ZB_GATEWAY: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
I (8418) ESP_ZB_GATEWAY: Formed network successfully (ieee_address: 60:55:f9:ff:fe:f7:69:04, PAN ID: 0x3fe3, Channel:13)
I (9248) ESP_ZB_GATEWAY: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
I (9768) ESP_ZB_GATEWAY: Network steering started
```

## Gateway Functions

 * The built esp_zigbee_gateway image will contain an updatable RCP image and can automatically update the RCP on version mismatch or RCP failure.
 * After Zigbee gateway starts up, it will read MAC ieee address and Zigbee stack version string from the Zigbee rcp and start working together with Zigbee rcp via UART communication to form a Zigbee network
 * More Gateway functionalities supporting Wi-Fi interaction will come later

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon
