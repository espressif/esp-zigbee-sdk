| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Green Power device Example 

This example demonstrates how to configure Zigbee Green Power device and use it as on/off switch to send Zigbee Green Power frame to control Zigbee Green Power combo (proxy + sink).

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as Zigbee Green Power Combo (see [green power combo](../esp_zigbee_gpc/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Application

- When the program starts, the board, acting as the `Green Power Device` with the `Green Power Switch` function.
```
I (342) main_task: Calling app_main()
I (352) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2 
I (362) phy: phy_version: 220,2, 37a29de, Dec 29 2023, 16:30:13
I (362) phy: libbtbb version: 944f18e, Dec 29 2023, 16:30:30
I (372) ESP_ZGP_DEVICE: ZGPD device started successfully
```

- Pressing the `BOOT` button on the board will initiate commissioning with the `Green Power Proxy`.
```
I (372) ESP_ZGP_DEVICE:  Wait to press the button to start commissioning ...
```

- If commissioning is successful, pressing the button again will broadcast an On/Off `toggle` command to the network.
```
I (22822) ESP_ZGP_DEVICE: ZGPD send toggle command
I (23572) ESP_ZGP_DEVICE: ZGPD send toggle command
I (24082) ESP_ZGP_DEVICE: ZGPD send toggle command
I (24972) ESP_ZGP_DEVICE: ZGPD send toggle command
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
