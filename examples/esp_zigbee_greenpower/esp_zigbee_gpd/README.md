| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Green Power device Example 

This example code shows how to configure Zigbee Green Power device and use it as on/off switch to send Zigbee Green Power frame to control Zigbee Green Power combo (proxy + sink).

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee Green Power device (loaded with esp_zigbee_gpd example)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee Green Power Combo (see [green power combo example](../esp_zigbee_gpc/))

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

As you run the example, you will see the following log:

```                                                                 
I (342) main_task: Calling app_main()
I (352) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2 
I (362) phy: phy_version: 220,2, 37a29de, Dec 29 2023, 16:30:13
I (362) phy: libbtbb version: 944f18e, Dec 29 2023, 16:30:30
I (372) ESP_ZGP_DEVICE: ZGPD device started successfully
I (372) ESP_ZGP_DEVICE:  Wait to press the button to start commissioning ...
I (382) main_task: Returned from app_main()
I (19172) ESP_ZGP_DEVICE: Start commissioning
I (19172) ESP_ZGP_DEVICE: Commissioning success
I (22822) ESP_ZGP_DEVICE: ZGPD send toggle command
I (23572) ESP_ZGP_DEVICE: ZGPD send toggle command
I (24082) ESP_ZGP_DEVICE: ZGPD send toggle command
I (24972) ESP_ZGP_DEVICE: ZGPD send toggle command

```

## Switch Control Functions

First time press button is to start commissioning. The rest of time press button is to send toggle command to Zigbee Green Power combo to trigger the light on/off.


## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
