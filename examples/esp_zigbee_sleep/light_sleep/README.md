| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Sleepy End Device Example 

This example demonstrates how to configure a Zigbee end device in [light sleep mode](https://docs.espressif.com/projects/esp-idf/en/latest/esp32h2/api-reference/system/sleep_modes.html#id1).

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
I (418) sleep: Enable automatic switching of GPIO sleep configuration
I (425) sleep_clock: System Power, Clock and Reset sleep retention initialization
I (433) sleep_clock: Modem Power, Clock and Reset sleep retention initialization
I (441) sleep_sys_periph: Interrupt Matrix sleep retention initialization
I (449) sleep_sys_periph: HP System sleep retention initialization
I (456) sleep_sys_periph: TEE/APM sleep retention initialization
I (462) sleep_sys_periph: UART sleep retention initialization
I (469) sleep_sys_periph: Timer Group sleep retention initialization
I (476) sleep_sys_periph: IO Matrix sleep retention initialization
I (483) sleep_sys_periph: SPI Mem sleep retention initialization
I (490) sleep_sys_periph: SysTimer sleep retention initialization
I (496) sleep_sys_periph: PVT sleep retention initialization
I (514) main_task: Started on CPU0
I (514) main_task: Calling app_main()
I (524) pm: Frequency switching config: CPU_MAX: 96, APB_MAX: 96, APB_MIN: 96, Light sleep: ENABLED
I (525) esp_zb_sleep: Enable ieee802154 zigbee light sleep, the wake up source is ESP timer
I (545) phy: phy_version: 210,0, 11c334c, Sep  4 2023, 17:01:13
I (547) phy: libbtbb version: b821802, Sep  4 2023, 17:01:29
I (548) btbb_init: btbb sleep retention initialization
I (554) ieee802154: ieee802154 mac sleep retention initialization
I (563) main_task: Returned from app_main()
I (650) ESP_ZB_SLEEP: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (651) ESP_ZB_SLEEP: Zigbee stack initialized
I (655) ESP_ZB_SLEEP: Start network steering
I (1608) ESP_ZB_SLEEP: Zigbee can sleep
I (2090) ESP_ZB_SLEEP: BDB Device Start failed with status: ESP_FAIL, retrying
I (2718) ESP_ZB_SLEEP: Zigbee can sleep
I (3083) ESP_ZB_SLEEP: Joined network successfully (Extended PAN ID: 60:55:f9:ff:fe:f7:2e:16, PAN ID: 0x6a2a, Channel:13, Short Address: 0x3a41)
I (4137) ESP_ZB_SLEEP: Zigbee can sleep
I (4585) ESP_ZB_SLEEP: Zigbee can sleep
```

- If the board on a network, it acts as a Zigbee end device with the `Home Automation On/Off Light` function.

- The board enters light sleep mode when the Zigbee stack is idle and wakes up either by an RTC timeout (approximately `ED_KEEP_ALIVE` seconds) or a GPIO interrupt.
```
I (9643) ESP_ZB_SLEEP: Zigbee can sleep
I (12585) ESP_ZB_SLEEP: Zigbee can sleep
I (12668) ESP_ZB_SLEEP: Zigbee can sleep
I (16677) ESP_ZB_SLEEP: Zigbee can sleep
I (20701) ESP_ZB_SLEEP: Zigbee can sleep
I (24730) ESP_ZB_SLEEP: Zigbee can sleep
```

- Pressing the `BOOT` button will also wake up the board.
```
I (41897) ESP_ZB_SLEEP: Send 'ieee_addr req' command
I (41906) ESP_ZB_SLEEP: Zigbee can sleep
I (42015) ESP_ZB_SLEEP: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (42066) ESP_ZB_SLEEP: Light sets to On
I (42081) ESP_ZB_SLEEP: Zigbee can sleep
I (42129) ESP_ZB_SLEEP: Zigbee can sleep
I (42293) ESP_ZB_SLEEP: Response IEEE address: 60:55:f9:ff:fe:f7:2e:16
I (42351) ESP_ZB_SLEEP: Zigbee can sleep
```

- With the default sleep threshold set to 20 milliseconds, the device may frequently enter sleep mode, logging `Zigbee can sleep`. To reduce the frequency of
  sleep occurrences, adjust the sleep threshold using `esp_zb_sleep_set_threshold()`.


During the light sleep, a typical power consumption is shown below:
![H2-light-sleep-power-consumption](image/ESP32H2-light-sleep-power-consumption.png)

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
