| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Touchlink Switch Example 

This test code shows touchlink initiator how to find and join network.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Touchlink initiator(Zigbee end deivce) (see [touchlink_switch](./))
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Touchlink target(Zigbee Router)(see [touchlink_light](../touchlink_light))

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
I (373) main_task: Calling app_main()
I (383) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2 
I (383) phy_init: phy_version 220,2dbbbe7,Sep 25 2023,20:39:25
I (453) phy: libbtbb version: 90c587c, Sep 25 2023, 20:39:57
I (463) ESP_TL_ON_OFF_SWITCH: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (463) ESP_TL_ON_OFF_SWITCH: ZB_ZDO_SIGNAL_SKIP_STARTUP: start join
I (463) ESP_TL_ON_OFF_SWITCH: Start Touchlink commissioning as initiator
I (473) main_task: Returned from app_main()
I (1783) ESP_TL_ON_OFF_SWITCH: Touchlink commissioning as initiator done
I (1783) ESP_TL_ON_OFF_SWITCH: Start Touchlink commissioning as initiator
I (3093) ESP_TL_ON_OFF_SWITCH: Touchlink commissioning as initiator done
I (3093) ESP_TL_ON_OFF_SWITCH: Start Touchlink commissioning as initiator
I (4393) ESP_TL_ON_OFF_SWITCH: Touchlink commissioning as initiator done
I (4393) ESP_TL_ON_OFF_SWITCH: Start Touchlink commissioning as initiator
I (5703) ESP_TL_ON_OFF_SWITCH: Touchlink commissioning as initiator done
I (5703) ESP_TL_ON_OFF_SWITCH: Start Touchlink commissioning as initiator
I (7003) ESP_TL_ON_OFF_SWITCH: Touchlink commissioning as initiator done
I (7003) ESP_TL_ON_OFF_SWITCH: Start Touchlink commissioning as initiator
I (8313) ESP_TL_ON_OFF_SWITCH: Touchlink commissioning as initiator done
I (8313) ESP_TL_ON_OFF_SWITCH: Start Touchlink commissioning as initiator
I (12333) ESP_TL_ON_OFF_SWITCH: Touchlink network started
I (12333) ESP_TL_ON_OFF_SWITCH: Profile: 0x104, ep: 10
I (12953) ESP_TL_ON_OFF_SWITCH: Touchlink commissioning as initiator done
I (12953) ESP_TL_ON_OFF_SWITCH: Touchlink Success, device address: 0x60 55 f9 0 0 f6 6 18
I (12993) ESP_TL_ON_OFF_SWITCH: User find cb: response_status:0, address:0x7d0, endpoint:10
I (21193) ESP_TL_ON_OFF_SWITCH: send 'on_off toggle' command
I (22173) ESP_TL_ON_OFF_SWITCH: send 'on_off toggle' command
I (22773) ESP_TL_ON_OFF_SWITCH: send 'on_off toggle' command
I (24003) ESP_TL_ON_OFF_SWITCH: send 'on_off toggle' command
```

## Touchlink Swtich Control Light Functions

 * By toggling the switch button (BOOT) on the ESP32-H2 board loaded with the `touchlink_switch` example, the LED on this board loaded with `touchlink_light` example will be on and off.


## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
