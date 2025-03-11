| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Light Switch Example 

This example demonstrates how to configure a Home Automation On/Off switch on a Zigbee Coordinator.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee end-device (see [HA_on_off_light](../HA_on_off_light/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board, acting as a Zigbee Coordinator with the `Home Automation On/Off Switch` function, will form an open network within 180 seconds.
```
I (453) main_task: Returned from app_main()
I (583) ESP_ZB_ON_OFF_SWITCH: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (583) ESP_ZB_ON_OFF_SWITCH: Initialize Zigbee stack
I (583) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:4 
I (583) ESP_ZB_ON_OFF_SWITCH: Deferred driver initialization successful
I (603) ESP_ZB_ON_OFF_SWITCH: Device started up in factory-reset mode
I (613) ESP_ZB_ON_OFF_SWITCH: Start network formation
W (763) ESP_ZB_ON_OFF_SWITCH: Network(0x1ce4) closed, devices joining not allowed.
I (763) ESP_ZB_ON_OFF_SWITCH: Formed network successfully (Extended PAN ID: 74:4d:bd:ff:fe:63:c2:e4, PAN ID: 0x1ce4, Channel:13, Short Address: 0x0000)
I (1373) ESP_ZB_ON_OFF_SWITCH: Network(0x1ce4) is open for 180 seconds
I (1373) ESP_ZB_ON_OFF_SWITCH: Network steering started
```

- If a Zigbee device with the `Home Automation On/Off Light` function joins the network, the board will add it to the binding table.
```
I (7803) ESP_ZB_ON_OFF_SWITCH: ZDO signal: NWK Device Associated (0x12), status: ESP_OK
I (7813) ESP_ZB_ON_OFF_SWITCH: ZDO signal: ZDO Device Update (0x30), status: ESP_OK
I (7843) ESP_ZB_ON_OFF_SWITCH: New device commissioned or rejoined (short: 0x2638)
I (7873) ESP_ZB_ON_OFF_SWITCH: Found light
I (7873) ESP_ZB_ON_OFF_SWITCH: Try to bind On/Off
I (7883) ESP_ZB_ON_OFF_SWITCH: Bound successfully!
I (7883) ESP_ZB_ON_OFF_SWITCH: The light originating from address(0x2638) on endpoint(10)
```

- Pressing the `BOOT` button on the board will send `On/Off toggle` commands to the bound devices.
```
I (11743) ESP_ZB_ON_OFF_SWITCH: Send 'on_off toggle' command
I (12323) ESP_ZB_ON_OFF_SWITCH: Send 'on_off toggle' command
I (13043) ESP_ZB_ON_OFF_SWITCH: Send 'on_off toggle' command
I (13513) ESP_ZB_ON_OFF_SWITCH: Send 'on_off toggle' command
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
