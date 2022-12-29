| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Light Switch Example 

This test code shows how to configure Zigbee Coordinator and use it as an HA color dimmable switch

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee Coordinator (loaded with HA_color_dimmable_switch)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee end-device (see [HA_color_dimmable_light](../HA_color_dimmable_light/))

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py --preview set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

As you run the example, you will see the following log:

```
I (318) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2
I (328) system_api: Base MAC address is not set
I (328) system_api: read default base MAC address from EFUSE
I (418) phy: libbtbb version: 6c47ec3, Mar 16 2022, 18:54:24
I (418) phy: phy_version: 101, bb2a234, Mar 16 2022, 18:54:11
I (748) ESP_ZB_COLOR_DIMM_SWITCH: status: 255
I (748) ESP_ZB_COLOR_DIMM_SWITCH: Zigbee stack initialized
I (748) ESP_ZB_COLOR_DIMM_SWITCH: Start network formation
I (1258) ESP_ZB_COLOR_DIMM_SWITCH: Formed network successfully (Extended PAN ID: ff:fc:7f:c0:f0:bd:97:10, PAN ID: 0xfa0d)
I (1718) ESP_ZB_COLOR_DIMM_SWITCH: status: 0
I (13798) ESP_ZB_COLOR_DIMM_SWITCH: status: 0
I (14308) ESP_ZB_COLOR_DIMM_SWITCH: status: 0
I (14348) ESP_ZB_COLOR_DIMM_SWITCH: New device commissioned or rejoined (short: 0xcda0)
I (14388) ESP_ZB_COLOR_DIMM_SWITCH: User find cb: address:0xcda0, endpoint:10
I (14888) ESP_ZB_COLOR_DIMM_SWITCH: status: 0
I (14918) ESP_ZB_COLOR_DIMM_SWITCH: status: 0
I (17478) ESP_ZB_COLOR_DIMM_SWITCH: send move to level command:5
I (20988) ESP_ZB_COLOR_DIMM_SWITCH: send color move to color command color_x:19660,color_y:38321
I (22418) ESP_ZB_COLOR_DIMM_SWITCH: send move to level command:15
I (23038) ESP_ZB_COLOR_DIMM_SWITCH: send color move to color command color_x:41942,color_y:21626
I (23438) ESP_ZB_COLOR_DIMM_SWITCH: send move to level command:25
I (23918) ESP_ZB_COLOR_DIMM_SWITCH: send color move to color command color_x:9830,color_y:3932
I (24268) ESP_ZB_COLOR_DIMM_SWITCH: send move to level command:35
I (24698) ESP_ZB_COLOR_DIMM_SWITCH: send color move to color command color_x:19660,color_y:38321
I (25178) ESP_ZB_COLOR_DIMM_SWITCH: send move to level command:45
I (25538) ESP_ZB_COLOR_DIMM_SWITCH: send color move to color command color_x:41942,color_y:21626
I (26058) ESP_ZB_COLOR_DIMM_SWITCH: send move to level command:55
I (26478) ESP_ZB_COLOR_DIMM_SWITCH: send color move to color command color_x:9830,color_y:3932
```

## Light Control Functions

  * By toggling the switch button (BOOT) on this board, the LED on the board loaded with the `HA_color_dimmable_light` example will be change color and light level.


## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
