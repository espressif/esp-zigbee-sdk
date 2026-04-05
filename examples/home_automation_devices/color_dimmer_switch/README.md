| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |
# Light Switch Example 

This example demonstrates how to configure a Home Automation color dimmer switch on a Zigbee router.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee router (see [color_dimmable_light](../color_dimmable_light/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board, acting as a Zigbee Router with the `Home Automation Dimmer Switch` function, will attempt to detect an available Zigbee network.
```
I (404) main_task: Calling app_main()
I (424) COLOR_DIMMER_SWITCH: Start ESP Zigbee Stack
I (424) ESP-ZIGBEE: SDK Version: v1.6.8-fcae32885b02-94cf5061*; esp32h2; 2026-04-08 12:37:02 UTC
I (424) esp zigbee sleep: light sleap disabled
I (444) phy: phy_version: 323,2, a8ef10c, Aug  1 2025, 17:46:10
I (444) phy: libbtbb version: 4515421, Aug  1 2025, 17:46:22
I (454) COLOR_DIMMER_SWITCH: Initialize Zigbee stack
I (454) COLOR_DIMMER_SWITCH: Deferred driver initialization successful
I (454) COLOR_DIMMER_SWITCH: Device started up in factory-reset mode
I (464) main_task: Returned from app_main()
I (1734) COLOR_DIMMER_SWITCH: Network(0x85ff) is open for 180 seconds
I (1734) COLOR_DIMMER_SWITCH: Joined network successfully: PAN ID(0x85ff, EXT: 0x4831b7fffec183f0), Channel(13), Short Address(0x940a)
```

- The Zigbee Router will attempt to find and bind a `Home Automation Dimmable Light` Device from the network after it joins to the network.
```
I (1734) COLOR_DIMMER_SWITCH: Joined network successfully: PAN ID(0x85ff, EXT: 0x4831b7fffec183f0), Channel(13), Short Address(0x940a)
I (1744) COLOR_DIMMER_SWITCH: Attempt to find HA color dimmable light device
I (1854) COLOR_DIMMER_SWITCH: Attempt to bind HA color dimmable light device (short address: 0x0000)
I (1884) COLOR_DIMMER_SWITCH: Bound HA color dimmable light device successfully
```

- Pressing the `BOOT` button on the board will send level and color control commands to the bound devices.
```
I (101444) COLOR_DIMMER_SWITCH: Move the level of HA dimmable light to 32
I (101544) COLOR_DIMMER_SWITCH: Received ZCL Default Response with status(0x00)
I (116174) COLOR_DIMMER_SWITCH: Move the color of HA dimmable light color_x: 0x0400, color_y: 0x0400
I (116254) COLOR_DIMMER_SWITCH: Received ZCL Default Response with status(0x00)
I (121964) COLOR_DIMMER_SWITCH: Move the level of HA dimmable light to 64
I (122044) COLOR_DIMMER_SWITCH: Received ZCL Default Response with status(0x00)
I (123874) COLOR_DIMMER_SWITCH: Move the color of HA dimmable light color_x: 0x0800, color_y: 0x0800
I (123964) COLOR_DIMMER_SWITCH: Received ZCL Default Response with status(0x00)
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
