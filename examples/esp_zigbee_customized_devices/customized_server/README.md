| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Light Bulb Example 

This example demonstrates how to register a customized ZCL On/Off light device with the Zigbee stack.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as Zigbee end device (see [customized_client](../customized_client) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board will register a `Customized` endpoint with the `On/Off Light` function and act as a Zigbee coordinator to form an open network
  within 180 seconds.
```
I (426) main_task: Calling app_main()
I (446) phy: phy_version: 321,2, 632dc08, Feb 13 2025, 16:29:11
I (446) phy: libbtbb version: 509a2a6, Feb 13 2025, 16:29:25
I (456) main_task: Returned from app_main()
I (586) ESP_HA_ON_OFF_LIGHT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (586) ESP_HA_ON_OFF_LIGHT: Initialize Zigbee stack
W (596) rmt: channel resolution loss, real=10666666
I (586) ESP_HA_ON_OFF_LIGHT: Deferred driver initialization successful
I (596) ESP_HA_ON_OFF_LIGHT: Device started up in factory-reset mode
I (606) ESP_HA_ON_OFF_LIGHT: Start network formation
W (766) ESP_HA_ON_OFF_LIGHT: Network(0x46c5) closed, devices joining not allowed.
I (766) ESP_HA_ON_OFF_LIGHT: Formed network successfully (Extended PAN ID: 74:4d:bd:ff:fe:63:de:c5, PAN ID: 0x46c5, Channel:13, Short Address: 0x0000)
I (1366) ESP_HA_ON_OFF_LIGHT: Network(0x46c5) is open for 180 seconds
I (1366) ESP_HA_ON_OFF_LIGHT: Network steering started
```

- If a Zigbee device joins this network and sends an `On/Off` command to the board, the LED on the board will be controlled accordingly.
```
I (16506) ESP_HA_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (16506) ESP_HA_ON_OFF_LIGHT: Light sets to On
W (16556) ESP_HA_ON_OFF_LIGHT: Receive Zigbee action(0x1005) callback
I (17746) ESP_HA_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (17746) ESP_HA_ON_OFF_LIGHT: Light sets to Off
W (17796) ESP_HA_ON_OFF_LIGHT: Receive Zigbee action(0x1005) callback
I (19516) ESP_HA_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (19516) ESP_HA_ON_OFF_LIGHT: Light sets to On
W (19566) ESP_HA_ON_OFF_LIGHT: Receive Zigbee action(0x1005) callback
I (22666) ESP_HA_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (22666) ESP_HA_ON_OFF_LIGHT: Light sets to Off
W (22716) ESP_HA_ON_OFF_LIGHT: Receive Zigbee action(0x1005) callback
```
- If the joined device sends a command to configure the `On/Off` attribute on the customized endpoint, the attribute will be reported based on the configuration.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
