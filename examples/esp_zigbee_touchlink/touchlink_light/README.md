| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Touchlink Light Example 

This test code shows touchlink target how to quick pairing of devices.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Touchlink initiator(Zigbee end deivce) (see [touchlink_switch](../touchlink_switch))
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Touchlink target(Zigbee Router)(see [touchlink_light](./))

## Important operating steps
* 1) Power on touchlink_light (Zigbee Router) and flash touchlink_light application code.
* 2) Then wait for `5-10 seconds` and Power on touchlink_switch (Zigbee end deivce) and flash touchlink_switch application code.

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
I (460) phy: libbtbb version: 90c587c, Sep 25 2023, 20:39:57
I (470) ESP_TL_ON_OFF_LIGHT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (470) ESP_TL_ON_OFF_LIGHT: Touchlink target started
I (470) main_task: Returned from app_main()
I (16190) ESP_TL_ON_OFF_LIGHT: Device is on permit join status
I (16190) ESP_TL_ON_OFF_LIGHT: Touchlink target : network started
I (16190) ESP_TL_ON_OFF_LIGHT: Touchlink target finished: success
I (18810) ESP_TL_ON_OFF_LIGHT: ZDO signal: ZDO Device Update (0x30), status: ESP_OK
I (18830) ESP_TL_ON_OFF_LIGHT: New device commissioned or rejoined (short: 0xbf2f)
I (27070) ESP_TL_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (27070) ESP_TL_ON_OFF_LIGHT: Light sets to On
I (28050) ESP_TL_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (28050) ESP_TL_ON_OFF_LIGHT: Light sets to Off
I (28650) ESP_TL_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (28650) ESP_TL_ON_OFF_LIGHT: Light sets to On
I (29860) ESP_TL_ON_OFF_LIGHT: ZDO signal: NLME Status Indication (0x32), status: ESP_OK
I (29880) ESP_TL_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (29880) ESP_TL_ON_OFF_LIGHT: Light sets to Off
I (50140) ESP_TL_ON_OFF_LIGHT: ZDO signal: NLME Status Indication (0x32), status: ESP_OK
```

## Light Control Functions

 * By toggling the switch button (BOOT) on the ESP32-H2 board loaded with the `touchlink_switch` example, the LED on this board loaded with `touchlink_light` example will be on and off.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
