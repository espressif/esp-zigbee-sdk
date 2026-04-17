| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |

# Touchlink Switch Example 

This example demonstrates how a Touchlink initiator can pair with a Touchlink target.

## Hardware Required
* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running a Zigbee Touchlink target (Zigbee Router)(see [touchlink_target](../touchlink_target) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts,the board, acting as the `Touchlink initiator`, will have the capability to scan nearby `Touchlink targets`.
```
I (416) main_task: Calling app_main()
I (426) TOUCHLINK_INITIATOR: Start ESP Zigbee Stack
I (436) esp zigbee sleep: light sleap disabled
I (446) phy: phy_version: 323,2, a8ef10c, Aug  1 2025, 17:46:10
I (446) phy: libbtbb version: 4515421, Aug  1 2025, 17:46:22
I (466) TOUCHLINK_INITIATOR: Initialize Zigbee stack                                              
I (466) TOUCHLINK_INITIATOR: Deferred driver initialization successful
I (466) TOUCHLINK_INITIATOR: Device started up in factory-reset mode
I (576) main_task: Returned from app_main()
```

- If no `Touchlink target` is found, the board will exit commissioning mode.
```
W (1837) ESP_TL_ON_OFF_SWITCH: No Touchlink target devices found
```

- Pressing the `BOOT` button will re-initiate the Touchlink commissioning process.
```
W (2206) TOUCHLINK_INITIATOR: Press the button to start Touchlink commissioning again

```

- If a `Touchlink target` is found, the board will pair with it and then exit commissioning mode.
```
I (5866) TOUCHLINK_INITIATOR: Commissioning successfully: PAN ID(0x5e9a, EXT: 0x4831b7fffec183f0), Channel(11), Short Address(0xcbf5)
I (5876) TOUCHLINK_INITIATOR: Attempt to find HA light device in the network
I (5886) TOUCHLINK_INITIATOR: Touchlink commissioning successfully
I (5996) TOUCHLINK_INITIATOR: Bound HA light device successfully
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
I (7256) TOUCHLINK_INITIATOR: Sent ZCL On/Off Toggle request                                                                                 
I (7316) TOUCHLINK_INITIATOR: Received ZCL Default Response with status(0x00)                                                                
I (8656) TOUCHLINK_INITIATOR: Sent ZCL On/Off Toggle request                                                                                 
I (8706) TOUCHLINK_INITIATOR: Received ZCL Default Response with status(0x00)                                                                
I (8856) TOUCHLINK_INITIATOR: Sent ZCL On/Off Toggle request                                                                                 
I (8916) TOUCHLINK_INITIATOR: Received ZCL Default Response with status(0x00)                                                                
I (9656) TOUCHLINK_INITIATOR: Sent ZCL On/Off Toggle request                                                                                 
I (9736) TOUCHLINK_INITIATOR: Received ZCL Default Response with status(0x00)  
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
