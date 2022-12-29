| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Light Bulb Example 

This test code shows how to configure Zigbee end device and use it as HA on/off light bulb

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee end-device (loaded with HA_on_off_light example)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee coordinator (see [HA_on_off_switch example](../HA_on_off_switch/))

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
I (307) gpio: GPIO[8]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0
I (317) system_api: Base MAC address is not set
I (317) system_api: read default base MAC address from EFUSE
I (407) phy: libbtbb version: 6c47ec3, Mar 16 2022, 18:54:24
I (407) phy: phy_version: 101, bb2a234, Mar 16 2022, 18:54:11
I (737) ESP_ZB_ON_OFF_LIGHT: status: 255
I (737) ESP_ZB_ON_OFF_LIGHT: Zigbee stack initialized
I (737) ESP_ZB_ON_OFF_LIGHT: Start network steering
I (2397) ESP_ZB_ON_OFF_LIGHT: Joined network successfully (Extended PAN ID: ff:fc:7c:c0:f0:bd:97:10, PAN ID: 0x0000)
I (7707) ESP_ZB_ON_OFF_LIGHT: on/off light set to 1
I (8447) ESP_ZB_ON_OFF_LIGHT: on/off light set to 0
I (8977) ESP_ZB_ON_OFF_LIGHT: on/off light set to 1
I (9427) ESP_ZB_ON_OFF_LIGHT: on/off light set to 0
```

## Light Control Functions

 * By toggling the switch button (BOOT) on the ESP32-H2 board loaded with the `HA_on_off_switch` example, the LED on this board loaded with `HA_on_off_light` example will be on and off.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
