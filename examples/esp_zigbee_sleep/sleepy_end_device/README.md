| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Sleepy End Device Example 

This test code shows how to configure Zigbee sleepy end device.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee end-device (loaded with sleepy_end_device example)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee coordinator (see [HA_on_off_switch example](../HA_on_off_switch/))

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
I (416) sleep_sys_periph: TEE/APM sleep retention initialization
I (423) sleep_sys_periph: UART sleep retention initialization
I (430) sleep_sys_periph: Timer Group sleep retention initialization
I (437) sleep_sys_periph: IO Matrix sleep retention initialization
I (444) sleep_sys_periph: SPI Mem sleep retention initialization
I (450) sleep_sys_periph: SysTimer sleep retention initialization
I (468) app_start: Starting scheduler on CPU0
I (469) main_task: Started on CPU0
I (469) main_task: Calling app_main()
I (480) pm: Frequency switching config: CPU_MAX: 96, APB_MAX: 96, APB_MIN: 96, Light sleep: ENABLED
I (481) esp_zb_sleep: Enable ieee802154 zigbee light sleep, the wake up source is ESP timer
I (503) phy: phy_version: 200,0, 8a31b65, Jun  6 2023, 20:13:10
I (504) phy: libbtbb version: 98b760f, Jun  6 2023, 20:13:22
I (506) btbb_init: btbb sleep retention initialization
I (512) ieee802154: ieee802154 mac sleep retention initialization
I (526) main_task: Returned from app_main()
I (528) ESP_ZB_SLEEP: ZDO signal: 23, status: -1
I (528) ESP_ZB_SLEEP: Zigbee stack initialized
I (537) ESP_ZB_SLEEP: Zigbee can sleep
I (539) ESP_ZB_SLEEP: Zigbee can sleep
I (543) ESP_ZB_SLEEP: Zigbee can sleep
I (548) ESP_ZB_SLEEP: Zigbee can sleep
I (552) ESP_ZB_SLEEP: Zigbee can sleep
I (556) ESP_ZB_SLEEP: Zigbee can sleep
I (561) ESP_ZB_SLEEP: Zigbee can sleep
I (565) ESP_ZB_SLEEP: Zigbee can sleep
I (570) ESP_ZB_SLEEP: Zigbee can sleep
I (574) ESP_ZB_SLEEP: Zigbee can sleep
I (579) ESP_ZB_SLEEP: Zigbee can sleep
I (583) ESP_ZB_SLEEP: Zigbee can sleep
I (1115) ESP_ZB_SLEEP: Zigbee can sleep
I (1663) ESP_ZB_SLEEP: Start network steering
I (1674) ESP_ZB_SLEEP: Joined network successfully (Extended PAN ID: 60:55:f9:ff:fe:f7:3a:12, PAN ID: 0x5d66, Channel:13)
I (1717) ESP_ZB_SLEEP: Zigbee can sleep
I (1806) ESP_ZB_SLEEP: Zigbee can sleep
I (2171) ESP_ZB_SLEEP: Zigbee can sleep
I (2175) ESP_ZB_SLEEP: Zigbee can sleep
I (2225) ESP_ZB_SLEEP: Zigbee can sleep
...
...
I (71551) ESP_ZB_SLEEP: Received message: endpoint(0xa), cluster(0x6), attribute(0x0), data size(1)
I (71603) ESP_ZB_SLEEP: ON/OFF sets to On
I (71626) ESP_ZB_SLEEP: Zigbee can sleep
I (71756) ESP_ZB_SLEEP: Zigbee can sleep
```

Please note that due to the default sleep threshold of 20 milliseconds, the device may enter sleep mode frequently and print log `Zigbee can sleep`. If you want to reduce the number of sleep occurrences, you can adjust the sleep threshold using the function `esp_zb_sleep_set_threshold(uint32_t threshold_ms)`. For example, you can set the threshold to a higher value like `esp_zb_sleep_set_threshold(2000); // 2000 milliseconds` after initializing Zigbee with `esp_zb_init(&zb_nwk_cfg);`.
## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
