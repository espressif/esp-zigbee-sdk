| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |

# Light Bulb Example 

This example demonstrates how to configure a Home Automation color dimmable light on a Zigbee router.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee coordinator (see [HA_color_dimmable_switch](../HA_color_dimmable_switch/) example)

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
I (394) main_task: Calling app_main()
I (404) gpio: GPIO[8]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (404) phy_init: phy_version 220,2dbbbe7,Sep 25 2023,20:39:25
I (464) phy: libbtbb version: 90c587c, Sep 25 2023, 20:39:57
I (474) ESP_ZB_COLOR_DIMM_LIGHT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (474) ESP_ZB_COLOR_DIMM_LIGHT: Zigbee stack initialized
I (484) ESP_ZB_COLOR_DIMM_LIGHT: Start network steering
I (484) main_task: Returned from app_main()
I (9604) ESP_ZB_COLOR_DIMM_LIGHT: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
I (9774) ESP_ZB_COLOR_DIMM_LIGHT: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
I (9774) ESP_ZB_COLOR_DIMM_LIGHT: Joined network successfully (Extended PAN ID: 60:55:f9:00:00:f6:07:b4, PAN ID: 0x17ef, Channel:13)
```
- If the board is on a network, it acts as a Zigbee router with the `Home Automation Dimmable Light` function.

- If the board receives a `Level Control` or `Color Control` command from the joined network, the LED on the board will adjust accordingly.
```
 (11234) ESP_ZB_COLOR_DIMM_LIGHT: Received message: endpoint(10), cluster(0x8), attribute(0x0), data size(1)
I (11234) ESP_ZB_COLOR_DIMM_LIGHT: Light level changes to 5
I (12554) ESP_ZB_COLOR_DIMM_LIGHT: Received message: endpoint(10), cluster(0x300), attribute(0x3), data size(2)
I (12554) ESP_ZB_COLOR_DIMM_LIGHT: Light color x changes to 0x4ccc
I (12554) ESP_ZB_COLOR_DIMM_LIGHT: Received message: endpoint(10), cluster(0x300), attribute(0x4), data size(2)
I (12564) ESP_ZB_COLOR_DIMM_LIGHT: Light color y changes to 0x95b1
I (13414) ESP_ZB_COLOR_DIMM_LIGHT: Received message: endpoint(10), cluster(0x8), attribute(0x0), data size(1)
I (13414) ESP_ZB_COLOR_DIMM_LIGHT: Light level changes to 15
I (14524) ESP_ZB_COLOR_DIMM_LIGHT: Received message: endpoint(10), cluster(0x300), attribute(0x3), data size(2)
I (14524) ESP_ZB_COLOR_DIMM_LIGHT: Light color x changes to 0xa3d6
I (14524) ESP_ZB_COLOR_DIMM_LIGHT: Received message: endpoint(10), cluster(0x300), attribute(0x4), data size(2)
I (14534) ESP_ZB_COLOR_DIMM_LIGHT: Light color y changes to 0x547a
I (20974) ESP_ZB_COLOR_DIMM_LIGHT: Received message: endpoint(10), cluster(0x8), attribute(0x0), data size(1)
I (20974) ESP_ZB_COLOR_DIMM_LIGHT: Light level changes to 25
I (21864) ESP_ZB_COLOR_DIMM_LIGHT: Received message: endpoint(10), cluster(0x300), attribute(0x3), data size(2)
I (21864) ESP_ZB_COLOR_DIMM_LIGHT: Light color x changes to 0x2666
I (21864) ESP_ZB_COLOR_DIMM_LIGHT: Received message: endpoint(10), cluster(0x300), attribute(0x4), data size(2)
I (21874) ESP_ZB_COLOR_DIMM_LIGHT: Light color y changes to 0xf5c
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
