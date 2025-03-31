| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Sleepy End Device Example

This example demonstrates how to configure a Zigbee sleepy end device in [deep sleep mode](https://docs.espressif.com/projects/esp-idf/en/latest/esp32h2/api-reference/system/sleep_modes.html#id1).

## Hardware Required
* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running a Zigbee coordinator (see [HA_on_off_switch](../../esp_zigbee_HA_sample/HA_on_off_switch/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board will attempt to detect an available Zigbee network every **1 second** until one is found.
```
I (414) sleep: Configure to isolate all GPIO pins in sleep state
I (420) sleep: Enable automatic switching of GPIO sleep configuration
I (427) main_task: Started on CPU0
I (427) main_task: Calling app_main()
I (437) ESP_ZB_DEEP_SLEEP: Not a deep sleep reset
I (437) ESP_ZB_DEEP_SLEEP: Enabling timer wakeup, 20s

I (447) phy: phy_version: 211,0, 5857fe5, Nov  1 2023, 11:31:09
I (447) phy: libbtbb version: ce629d6, Nov  1 2023, 11:31:19
I (457) main_task: Returned from app_main()
I (587) ESP_ZB_DEEP_SLEEP: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (587) ESP_ZB_DEEP_SLEEP: Zigbee stack initialized
I (587) ESP_ZB_DEEP_SLEEP: Start network steering
I (590) ESP_ZB_DEEP_SLEEP: BDB Device Start failed with status: ESP_FAIL, retrying
I (10557) ESP_ZB_DEEP_SLEEP: Joined network successfully (Extended PAN ID: 60:55:f9:ff:fe:f7:2f:3e, PAN ID: 0xe4c4, Channel:13, Short Address: 0x5e1c)
```

- If the board is on a network, it acts as a Zigbee end device with the `Home Automation On/Off Light` function.

- The board will enter deep sleep mode when Zigbee task is idle. The board can be woken up by a GPIO interrupt or a RTC timer timeout.
```
I (10567) ESP_ZB_DEEP_SLEEP: Start one-shot timer for 5s to enter the deep sleep
I (15567) ESP_ZB_DEEP_SLEEP: Enter deep sleep
```

- When the board wakes up from deep sleep mode, it will trigger a reboot.
```
ESP-ROM:esp32h2-20221101
Build:Nov  1 2022
rst:0x5 (SLEEP_WAKEUP),boot:0xc (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
...
...
...

I (225) sleep: Configure to isolate all GPIO pins in sleep state
I (231) sleep: Enable automatic switching of GPIO sleep configuration
I (239) main_task: Started on CPU0
I (239) main_task: Calling app_main()
I (249) ESP_ZB_DEEP_SLEEP: Wake up from timer. Time spent in deep sleep and boot: 20257ms
I (249) ESP_ZB_DEEP_SLEEP: Enabling timer wakeup, 20s

I (269) phy: phy_version: 211,0, 5857fe5, Nov  1 2023, 11:31:09
I (269) phy: libbtbb version: ce629d6, Nov  1 2023, 11:31:19
I (279) main_task: Returned from app_main()
I (307) ESP_ZB_DEEP_SLEEP: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (307) ESP_ZB_DEEP_SLEEP: Zigbee stack initialized
I (587) ESP_ZB_DEEP_SLEEP: Device started up in non factory-reset mode
I (587) ESP_ZB_DEEP_SLEEP: Device rebooted
I (587) ESP_ZB_DEEP_SLEEP: Start one-shot timer for 5s to enter the deep sleep
I (5597) ESP_ZB_DEEP_SLEEP: Enter deep sleep
```

- Pressing the `BOOT` button will also wake up the board.

- Deep sleep is not used by the SDK. The developer should manage it in their applications. For more wake-up methods, you can refer to the
  [deep sleep example](https://github.com/espressif/esp-idf/tree/master/examples/system/deep_sleep) of ESP-IDF. Additionally, Espressif provides a
  stub for handling wake-ups, which allows for a quick check, and the user can decide whether to wake up or continue deep sleep in this stub, as
  explained in the [deep sleep stub example](https://github.com/espressif/esp-idf/tree/master/examples/system/deep_sleep_wake_stub) of ESP-IDF.

- Implementing a standard Zigbee Sleepy Device is recommended using the [Light Sleep example](../light_sleep). Deep sleep triggers a reboot, and the device needs
  to undergo a re-attach process to rejoin the network. This means additional packet interactions are required after each wake-up from deep sleep. However, the
  Deep sleep mode can be advantageous in reducing power consumption, especially when the device remains in a sleep state for extended periods, such as more than
  30 minutes.

During the deep sleep, a typical power consumption is shown below:

![H2-deep-sleep-power-consumption](image/ESP32H2-deep-sleep-power-consumption.png)

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
