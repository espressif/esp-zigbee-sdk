| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Light Bulb Example 

This test code shows how to configure Zigbee end device and use it as a HA color dimmable light bulb

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee end-device (loaded with HA_color_dimmable_light example)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee coordinator (see [HA_color_dimmable_switch example](../HA_color_dimmable_switch/))

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
I (308) gpio: GPIO[8]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0
I (318) system_api: Base MAC address is not set
I (318) system_api: read default base MAC address from EFUSE
I (408) phy: libbtbb version: 6c47ec3, Mar 16 2022, 18:54:24
I (408) phy: phy_version: 101, bb2a234, Mar 16 2022, 18:54:11
I (738) ESP_ZB_COLOR_DIMM_LIGHT: status: 255
I (738) ESP_ZB_COLOR_DIMM_LIGHT: Zigbee stack initialized
I (738) ESP_ZB_COLOR_DIMM_LIGHT: Start network steering
I (2388) ESP_ZB_COLOR_DIMM_LIGHT: Joined network successfully (Extended PAN ID: ff:fc:7c:c0:f0:bd:97:10, PAN ID: 0x0000)
I (6368) ESP_ZB_COLOR_DIMM_LIGHT: Light level change to:5
I (9678) ESP_ZB_COLOR_DIMM_LIGHT: Light color x change to:19660
I (9678) ESP_ZB_COLOR_DIMM_LIGHT: Light color y change to:38321
I (10108) ESP_ZB_COLOR_DIMM_LIGHT: Light level change to:15
I (10748) ESP_ZB_COLOR_DIMM_LIGHT: Light color x change to:41942
I (10748) ESP_ZB_COLOR_DIMM_LIGHT: Light color y change to:21626
I (11148) ESP_ZB_COLOR_DIMM_LIGHT: Light level change to:25
I (11768) ESP_ZB_COLOR_DIMM_LIGHT: Light color x change to:9830
I (11768) ESP_ZB_COLOR_DIMM_LIGHT: Light color y change to:3932
I (12378) ESP_ZB_COLOR_DIMM_LIGHT: Light level change to:35
I (12988) ESP_ZB_COLOR_DIMM_LIGHT: Light color x change to:19660
I (12988) ESP_ZB_COLOR_DIMM_LIGHT: Light color y change to:38321
I (13558) ESP_ZB_COLOR_DIMM_LIGHT: Light level change to:45
I (14148) ESP_ZB_COLOR_DIMM_LIGHT: Light color x change to:41942
I (14148) ESP_ZB_COLOR_DIMM_LIGHT: Light color y change to:21626
I (15448) ESP_ZB_COLOR_DIMM_LIGHT: Light level change to:55
I (15928) ESP_ZB_COLOR_DIMM_LIGHT: Light color x change to:9830
I (15928) ESP_ZB_COLOR_DIMM_LIGHT: Light color y change to:3932
```
 
## Light Control Functions

 * By toggling the switch button (BOOT) on the ESP32-H2 board loaded with the `HA_color_dimmable_switch` example, the LED on this board loaded with `HA_color_dimmable_light` example will change the color from red, green to blue and also light level will change.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
