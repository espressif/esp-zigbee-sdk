| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Light Switch Example 

This example demonstrates how to configure a Home Automation color dimmable switch on a Zigbee coordinator.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee router (see [HA_color_dimmable_light](../HA_color_dimmable_light/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board, acting as a Zigbee Coordinator with the `Home Automation Dimmable Switch` function, will form an open network within 180 seconds.
```
I (390) main_task: Calling app_main()
I (400) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2 
I (400) phy_init: phy_version 220,2dbbbe7,Sep 25 2023,20:39:25
I (470) phy: libbtbb version: 90c587c, Sep 25 2023, 20:39:57
I (480) ESP_ZB_COLOR_DIMM_SWITCH: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (480) ESP_ZB_COLOR_DIMM_SWITCH: Zigbee stack initialized
I (480) ESP_ZB_COLOR_DIMM_SWITCH: Start network formation
I (490) main_task: Returned from app_main()
I (1000) ESP_ZB_COLOR_DIMM_SWITCH: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
I (1000) ESP_ZB_COLOR_DIMM_SWITCH: Formed network successfully (Extended PAN ID: 60:55:f9:00:00:f6:07:b4, PAN ID: 0x17ef, Channel:13)
I (1480) ESP_ZB_COLOR_DIMM_SWITCH: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
I (1480) ESP_ZB_COLOR_DIMM_SWITCH: Network steering started
```

- If a Zigbee device with the `Home Automation Dimmable Light` function joins the network, the board will add it to the binding table.
```
I (17070) ESP_ZB_COLOR_DIMM_SWITCH: ZDO signal: NWK Device Associated (0x12), status: ESP_OK
I (17570) ESP_ZB_COLOR_DIMM_SWITCH: ZDO signal: ZDO Device Update (0x30), status: ESP_OK
I (17630) ESP_ZB_COLOR_DIMM_SWITCH: New device commissioned or rejoined (short: 0x85da)
I (17660) ESP_ZB_COLOR_DIMM_SWITCH: Found dimmable light
I (17660) ESP_ZB_COLOR_DIMM_SWITCH: Try to bind color control
I (17660) ESP_ZB_COLOR_DIMM_SWITCH: Try to bind level control
I (17670) ESP_ZB_COLOR_DIMM_SWITCH: Bound successfully!
I (17670) ESP_ZB_COLOR_DIMM_SWITCH: Bound successfully!
I (17680) ESP_ZB_COLOR_DIMM_SWITCH: The light originating from address(0x85da) on endpoint(10)
I (18140) ESP_ZB_COLOR_DIMM_SWITCH: ZDO signal: ZDO Device Authorized (0x2f), status: ESP_OK
I (18190) ESP_ZB_COLOR_DIMM_SWITCH: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
```

- Pressing the `BOOT` button on the board will send level and color control commands to the bound devices.
```
I (19660) ESP_ZB_COLOR_DIMM_SWITCH: Send command for moving light to 5 level
I (20840) ESP_ZB_COLOR_DIMM_SWITCH: Send command for moving light color to (0x4ccc, 0x95b1)
I (21840) ESP_ZB_COLOR_DIMM_SWITCH: Send command for moving light to 15 level
I (22810) ESP_ZB_COLOR_DIMM_SWITCH: Send command for moving light color to (0xa3d6, 0x547a)
I (29400) ESP_ZB_COLOR_DIMM_SWITCH: Send command for moving light to 25 level
I (30160) ESP_ZB_COLOR_DIMM_SWITCH: Send command for moving light color to (0x2666, 0xf5c)
I (58620) ESP_ZB_COLOR_DIMM_SWITCH: ZDO signal: ZDO Device Update (0x30), status: ESP_OK

```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
