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
I (438) phy: libbtbb version: b684fcb, May 17 2023, 20:14:35
I (458) main_task: Returned from app_main()
I (558) ESP_TL_ON_OFF_SWITCH: ZDO signal: 23, status: -1
I (558) ESP_TL_ON_OFF_SWITCH: ZB_ZDO_SIGNAL_SKIP_STARTUP: start join
I (558) ESP_TL_ON_OFF_SWITCH: Start Touchlink commissioning as initiator
I (5798) ESP_TL_ON_OFF_SWITCH: Touchlink commissioning as initiator done
I (5798) ESP_TL_ON_OFF_SWITCH: Start Touchlink commissioning as initiator
I (11018) ESP_TL_ON_OFF_SWITCH: Touchlink commissioning as initiator done
I (11018) ESP_TL_ON_OFF_SWITCH: Start Touchlink commissioning as initiator
I (18938) ESP_TL_ON_OFF_SWITCH: ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED
I (18938) ESP_TL_ON_OFF_SWITCH: profile: 0x104, ep 10
I (19568) ESP_TL_ON_OFF_SWITCH: Touchlink commissioning as initiator done
I (19568) ESP_TL_ON_OFF_SWITCH: Touchlink Success, device address: 0x60 55 f9 0 0 f6 ff ec
I (19638) ESP_TL_ON_OFF_SWITCH: User find cb: response_status:0, address:0x8429, endpoint:10
I (50508) ESP_TL_ON_OFF_SWITCH: send 'on_off toggle' command
I (51048) ESP_TL_ON_OFF_SWITCH: send 'on_off toggle' command
```

## Touchlink Swtich Control Light Functions

 * By toggling the switch button (BOOT) on the ESP32-H2 board loaded with the `touchlink_switch` example, the LED on this board loaded with `touchlink_light` example will be on and off.


## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
