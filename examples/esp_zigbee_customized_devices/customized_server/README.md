| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Light Bulb Example 

This test code shows how to customized add / update attribute, how to customized a cluster based on the pre-defined cluster, how to update the cluster.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee coordinator device (loaded with customized_server example)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee coordinator (see [customized_client](../customized_client/))

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
I (320) gpio: GPIO[8]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0
I (330) system_api: Base MAC address is not set
I (330) system_api: read default base MAC address from EFUSE
I (420) phy: libbtbb version: 6c47ec3, Mar 16 2022, 18:54:24
I (420) phy: phy_version: 101, bb2a234, Mar 16 2022, 18:54:11
I (750) ESP_HA_ON_OFF_LIGHT: status: -1
I (750) ESP_HA_ON_OFF_LIGHT: Zigbee stack initialized
I (750) ESP_HA_ON_OFF_LIGHT: Start network formation
I (1260) ESP_HA_ON_OFF_LIGHT: Formed network successfully (Extended PAN ID: ff:fc:7f:c0:f0:bd:97:10, PAN ID: 0x10b9)
I (1720) ESP_HA_ON_OFF_LIGHT: status: 0
I (1720) ESP_HA_ON_OFF_LIGHT: Network steering started
I (5770) ESP_HA_ON_OFF_LIGHT: status: 0
I (6270) ESP_HA_ON_OFF_LIGHT: status: 0
I (6310) ESP_HA_ON_OFF_LIGHT: New device commissioned or rejoined (short: 0xdb25)
I (6850) ESP_HA_ON_OFF_LIGHT: status: 0
I (6890) ESP_HA_ON_OFF_LIGHT: status: 0
I (6900) ESP_HA_ON_OFF_LIGHT: status: 0
I (10950) ESP_HA_ON_OFF_LIGHT: on/off light set to 1
I (12860) ESP_HA_ON_OFF_LIGHT: on/off light set to 0
I (14390) ESP_HA_ON_OFF_LIGHT: on/off light set to 1
I (15950) ESP_HA_ON_OFF_LIGHT: on/off light set to 0
I (22250) ESP_HA_ON_OFF_LIGHT: on/off light set to 1
I (22940) ESP_HA_ON_OFF_LIGHT: on/off light set to 0
I (24760) ESP_HA_ON_OFF_LIGHT: on/off light set to 1
I (25650) ESP_HA_ON_OFF_LIGHT: on/off light set to 0
```

## Light Control Functions

 * By toggling the switch button (BOOT) on the ESP32-H2 board loaded with the `customized_client` example, the LED on this board loaded with `customized_server` example will be on and off.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
