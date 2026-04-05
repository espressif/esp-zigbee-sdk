| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |

# Light Bulb Example 

This example demonstrates how to configure a Home Automation on/off light on a Zigbee Coordinator.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee Router/End Device (see [on_off_switch](../on_off_switch/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board, acting as a Zigbee Coordinator with the `Home Automation On/Off Light` function, will form an open network within 180 seconds.
```
I (425) main_task: Calling app_main()
I (435) ON_OFF_LIGHT: Start ESP Zigbee Stack
I (445) esp zigbee sleep: light sleap disabled
I (455) phy: phy_version: 323,2, a8ef10c, Aug  1 2025, 17:46:10
I (455) phy: libbtbb version: 4515421, Aug  1 2025, 17:46:22
I (475) ON_OFF_LIGHT: Initialize Zigbee stack
W (475) rmt: channel resolution loss, real=10666666
I (475) ON_OFF_LIGHT: Deferred driver initialization successful
I (485) ON_OFF_LIGHT: Device started up in factory-reset mode
I (475) main_task: Returned from app_main()
I (795) ON_OFF_LIGHT: Formed network successfully: PAN ID(0x3051, EXT: 0x4831b7fffec183f0), Channel(13), Short Address(0x0000)
I (1175) ON_OFF_LIGHT: Network steering completed
I (3705) ON_OFF_LIGHT: New device commissioned or rejoined (short: 0xa515)
```

- If the board receives a `On/Off` command from the joined network, the LED on the board will adjust accordingly.
```
I (26905) ON_OFF_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0006) server with status(0x00)
I (26905) ON_OFF_LIGHT: Set On/Off: 1
I (27535) ON_OFF_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0006) server with status(0x00)
I (27535) ON_OFF_LIGHT: Set On/Off: 0
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
