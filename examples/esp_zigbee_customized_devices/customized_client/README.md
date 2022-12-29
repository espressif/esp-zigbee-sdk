| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Light Switch Example 

This test code shows how to customized add / update attribute, add cluster and add endpoint to a device. This example also shows how to use varieties ZDO commands and ZCL commands, like binding, finding, read attribute, configure report attribute.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee end device (loaded with customized_client example)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee coordinator (see [customized_server](../customized_server/))

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
I (308) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2
I (318) system_api: Base MAC address is not set
I (318) system_api: read default base MAC address from EFUSE
I (408) phy: libbtbb version: 6c47ec3, Mar 16 2022, 18:54:24
I (408) phy: phy_version: 101, bb2a234, Mar 16 2022, 18:54:11
I (788) ESP_HA_ON_OFF_SWITCH: status: -1
I (3438) ESP_HA_ON_OFF_SWITCH: Start network steering
I (25068) ESP_HA_ON_OFF_SWITCH: Joined network successfully (Extended PAN ID: ff:fc:c2:c4:f0:bd:97:10, PAN ID: 0x9a0f)
I (25098) ESP_HA_ON_OFF_SWITCH: User_find_cb: address:0, endpoint:10
I (25198) ESP_HA_ON_OFF_SWITCH: Active_ep_cb status:0 and count:1
I (25198) ESP_HA_ON_OFF_SWITCH: endpoint ID list:10
I (25218) ESP_HA_ON_OFF_SWITCH: Simple_desc_cb device_id:2,app_version:0,profile_id:0x104,endpoint ID:10
I (25218) ESP_HA_ON_OFF_SWITCH: cluster ID list:0x0
I (25218) ESP_HA_ON_OFF_SWITCH: cluster ID list:0x3
I (25228) ESP_HA_ON_OFF_SWITCH: cluster ID list:0x4
I (25238) ESP_HA_ON_OFF_SWITCH: cluster ID list:0x5
I (25238) ESP_HA_ON_OFF_SWITCH: cluster ID list:0x6
I (25258) ESP_HA_ON_OFF_SWITCH: ieee_cb address is:ff:fc:c2:c4:f0:bd:97:10
I (25318) ESP_HA_ON_OFF_SWITCH: Bind_cb status:0
I (28248) ESP_HA_ON_OFF_SWITCH: Switch got read attribute response with status:0,value:0,attr_type:0x10,attr_id:0x0
I (174518) ESP_HA_ON_OFF_SWITCH: send 'on_off toggle' command
I (174588) ESP_HA_ON_OFF_SWITCH: Switch got report attribute from address:0x0,value:1,attr_type:0x10,attr_id:0x0
I (175268) ESP_HA_ON_OFF_SWITCH: send 'on_off toggle' command
I (179688) ESP_HA_ON_OFF_SWITCH: Switch got report attribute from address:0x0,value:0,attr_type:0x10,attr_id:0x0
I (180118) ESP_HA_ON_OFF_SWITCH: send 'on_off toggle' command
I (184788) ESP_HA_ON_OFF_SWITCH: Switch got report attribute from address:0x0,value:1,attr_type:0x10,attr_id:0x0
```

## Light Control Functions

 * By toggling the switch button (BOOT) on the ESP32-H2 board loaded with the `customized_client` example, the LED on this board loaded with `customized_server` example will be on and off.


## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
