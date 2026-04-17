| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |

# Light Switch Example 

This example demonstrates how to configure a Home Automation On/Off switch on a Zigbee End Device.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee Coordinator (see [on_off_light](../on_off_light/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board, acting as a Zigbee Router with the `Home Automation On/Off Switch` function, will attempt to detect an available Zigbee network.
```
I (417) main_task: Calling app_main()
I (427) ON_OFF_SWITCH: Start ESP Zigbee Stack
I (437) esp zigbee sleep: light sleap disabled
I (447) phy: phy_version: 323,2, a8ef10c, Aug  1 2025, 17:46:10
I (447) phy: libbtbb version: 4515421, Aug  1 2025, 17:46:22
I (467) ON_OFF_SWITCH: Initialize Zigbee stack
I (467) ON_OFF_SWITCH: Deferred driver initialization successful
I (467) ON_OFF_SWITCH: Device started up in factory-reset mode
I (477) main_task: Returned from app_main()
I (1727) ON_OFF_SWITCH: Joined network successfully: PAN ID(0x3051, EXT: 0x4831b7fffec183f0), Channel(13), Short Address(0xe5e0)
```

- The Zigbee Router will attempt to find and bind a `Home Automation Dimmable Light` Device from the network after it joins to the network.
```
I (1727) ON_OFF_SWITCH: Attempt to find HA light device
I (1827) ON_OFF_SWITCH: Attempt to bind HA light device (short address: 0x0000)
I (1847) ON_OFF_SWITCH: Bound HA light device successfully
```

- Pressing the `BOOT` button on the board will send `On/Off toggle` commands to the bound devices.
```
I (24447) ON_OFF_SWITCH: Sent ZCL On/Off Toggle request
I (24517) ON_OFF_SWITCH: Received ZCL Default Response with status(0x00)
I (25077) ON_OFF_SWITCH: Sent ZCL On/Off Toggle request
I (25157) ON_OFF_SWITCH: Received ZCL Default Response with status(0x00)
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
