| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Light Bulb Example 

This test code shows how to customized add / update attribute, how to customized a cluster based on the pre-defined cluster, how to update the cluster.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee coordinator device (loaded with customized_server example)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee coordinator (see [customized_client](../customized_client/))

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
I (390) main_task: Calling app_main()
I (400) gpio: GPIO[8]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (400) phy_init: phy_version 220,2dbbbe7,Sep 25 2023,20:39:25
I (480) phy: libbtbb version: 90c587c, Sep 25 2023, 20:39:57
I (480) ESP_HA_ON_OFF_LIGHT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (480) ESP_HA_ON_OFF_LIGHT: Zigbee stack initialized
I (490) ESP_HA_ON_OFF_LIGHT: Start network formation
I (490) main_task: Returned from app_main()
I (1000) ESP_HA_ON_OFF_LIGHT: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
I (1000) ESP_HA_ON_OFF_LIGHT: Formed network successfully (Extended PAN ID: 60:55:f9:00:00:f6:07:b4, PAN ID: 0x9479, Channel:13)
I (1480) ESP_HA_ON_OFF_LIGHT: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
I (1480) ESP_HA_ON_OFF_LIGHT: Network steering started
I (9220) ESP_HA_ON_OFF_LIGHT: ZDO signal: NWK Device Associated (0x12), status: ESP_OK
I (9720) ESP_HA_ON_OFF_LIGHT: ZDO signal: ZDO Device Update (0x30), status: ESP_OK
I (9750) ESP_HA_ON_OFF_LIGHT: New device commissioned or rejoined (short: 0x8ceb)
I (9910) ESP_HA_ON_OFF_LIGHT: ZDO signal: ZDO Device Authorized (0x2f), status: ESP_OK
I (9950) ESP_HA_ON_OFF_LIGHT: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
I (10130) ESP_HA_ON_OFF_LIGHT: ZDO signal: NLME Status Indication (0x32), status: ESP_OK
I (10390) ESP_HA_ON_OFF_LIGHT: ZDO signal: NLME Status Indication (0x32), status: ESP_OK
I (21440) ESP_HA_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (21440) ESP_HA_ON_OFF_LIGHT: Light sets to On
I (30320) ESP_HA_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (30320) ESP_HA_ON_OFF_LIGHT: Light sets to Off
```

## Light Control Functions

 * By toggling the switch button (BOOT) on the ESP32-H2 board loaded with the `customized_client` example, the LED on this board loaded with `customized_server` example will be on and off.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
