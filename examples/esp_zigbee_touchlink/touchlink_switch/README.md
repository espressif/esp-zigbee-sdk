| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Touchlink Switch Example 

This example demonstrates how a Touchlink initiator can pair with a Touchlink target.

## Hardware Required
* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running a Zigbee Touchlink target(Zigbee Router)(see [touchlink_light](../touchlink_light) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts,tThe board, acting as the `Touchlink initiator`, will have the capability to scan nearby `Touchlink targets`.
```
I (357) main_task: Started on CPU0
I (367) main_task: Calling app_main()
I (397) phy: phy_version: 321,2, 632dc08, Feb 13 2025, 16:29:11
I (397) phy: libbtbb version: 509a2a6, Feb 13 2025, 16:29:25
I (397) main_task: Returned from app_main()
I (507) ESP_TL_ON_OFF_SWITCH: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (507) ESP_TL_ON_OFF_SWITCH: Initialize Zigbee stack
I (507) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:4 
I (507) ESP_TL_ON_OFF_SWITCH: Deferred driver initialization successful
I (517) ESP_TL_ON_OFF_SWITCH: Device started up in factory-reset mode
I (527) ESP_TL_ON_OFF_SWITCH: Scanning as a Touchlink initiator...
```

- If no `Touchlink target` is found, the board will exit commissioning mode.
```
I (1837) ESP_TL_ON_OFF_SWITCH: Touchlink commissioning as initiator done
W (1837) ESP_TL_ON_OFF_SWITCH: No Touchlink target devices found
```

- Pressing the `BOOT` button will re-initiate the Touchlink commissioning process.
```
W (1837) ESP_TL_ON_OFF_SWITCH: Press the button to start Touchlink commissioning again
I (13427) ESP_TL_ON_OFF_SWITCH: Scanning as a Touchlink initiator...
```

- If a `Touchlink target` is found, the board will pair with it and then exit commissioning mode.
```
I (17077) ESP_TL_ON_OFF_SWITCH: Touchlink initiator receives the response for started network
I (17077) ESP_TL_ON_OFF_SWITCH: Response is from profile: 0x0104, endpoint: 10, address: 0x744dbdfffe637873
I (17357) ESP_TL_ON_OFF_SWITCH: Touchlink commissioning as initiator done
I (17357) ESP_TL_ON_OFF_SWITCH: Commissioning successfully, network information (Extended PAN ID: 74:4d:bd:ff:fe:63:78:73, PAN ID: 0x231d, Channel:11, Short Address: 0x6bd8)
```

- If the board is on a network, it will act as the `Home Automation On/Off Switch` and search for an `Home Automation  On/Off Light` device on the network.
  If found, it will bind the device to its binding table.
```
I (17397) ESP_TL_ON_OFF_SWITCH: Found light
I (17397) ESP_TL_ON_OFF_SWITCH: Try to bind on/off light
I (17407) ESP_TL_ON_OFF_SWITCH: Bound successfully!
```

- Once paired, pressing the `BOOT` button will trigger an `On/Off toggle` command to control the paired `On/Off Light` device.
```
I (21197) ESP_TL_ON_OFF_SWITCH: send 'on_off toggle' command
I (21837) ESP_TL_ON_OFF_SWITCH: send 'on_off toggle' command
I (22517) ESP_TL_ON_OFF_SWITCH: send 'on_off toggle' command
I (23397) ESP_TL_ON_OFF_SWITCH: send 'on_off toggle' command
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
