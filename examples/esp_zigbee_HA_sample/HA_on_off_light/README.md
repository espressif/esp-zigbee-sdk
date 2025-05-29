| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |

# Light Bulb Example 

This example demonstrates how to configure a Home Automation on/off light on a Zigbee end device.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee coordinator (see [HA_on_off_switch](../HA_on_off_switch/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board will attempt to detect an available Zigbee network every **1 second** until one is found.
```
I (392) main_task: Calling app_main()
I (412) phy: phy_version: 321,2, 632dc08, Feb 13 2025, 16:29:11
I (412) phy: libbtbb version: 509a2a6, Feb 13 2025, 16:29:25
I (422) main_task: Returned from app_main()
I (432) ESP_ZB_ON_OFF_LIGHT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (432) ESP_ZB_ON_OFF_LIGHT: Initialize Zigbee stack
W (442) rmt: channel resolution loss, real=10666666
I (432) ESP_ZB_ON_OFF_LIGHT: Deferred driver initialization successful
I (442) ESP_ZB_ON_OFF_LIGHT: Device started up in factory-reset mode
I (452) ESP_ZB_ON_OFF_LIGHT: Start network steering
I (3382) ESP_ZB_ON_OFF_LIGHT: Joined network successfully (Extended PAN ID: 74:4d:bd:ff:fe:63:c2:e4, PAN ID: 0x1ce4, Channel:13, Short Address: 0x2638)
```

- If the board is on a network, it acts as a Zigbee end device with the `Home Automation On/Off Light` function.

- If the board receives a `On/Off` command from the joined network, the LED on the board will adjust accordingly.
```
I (7162) ESP_ZB_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (7162) ESP_ZB_ON_OFF_LIGHT: Light sets to On
I (7742) ESP_ZB_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (7742) ESP_ZB_ON_OFF_LIGHT: Light sets to Off
I (8462) ESP_ZB_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (8462) ESP_ZB_ON_OFF_LIGHT: Light sets to On
I (8932) ESP_ZB_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (8932) ESP_ZB_ON_OFF_LIGHT: Light sets to Off
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
