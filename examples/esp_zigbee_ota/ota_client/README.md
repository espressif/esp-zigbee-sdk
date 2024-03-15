| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# OTA Upgrade Example 

This example code shows how to add OTA client attribute and parameter, add OTA cluster and add endpoint to a device. It demonstrates the whole OTA process from client side.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee end device (loaded with ota_client example)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee coordinator (loaded with ota_server example), see [ota_server](../ota_server/))

## Configure the project

Before project configuration and build, set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

As you run the example, you will see the following log:

```
I (420) main_task: Calling app_main()
I (420) ESP_OTA_CLIENT: OTA example 1.0 is running
I (450) phy: phy_version: 210,0, 11c334c, Sep  4 2023, 17:01:13
I (450) phy: libbtbb version: b821802, Sep  4 2023, 17:01:29
I (460) main_task: Returned from app_main()
I (530) ESP_OTA_CLIENT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (17500) ESP_OTA_CLIENT: -- OTA upgrade start
I (17600) ESP_OTA_CLIENT: Joined network successfully (Extended PAN ID: 60:55:f9:ff:fe:f7:2e:16, PAN ID: 0x397c, Channel:13)
I (17740) ESP_OTA_CLIENT: -- OTA Client receives data: progress [8/159616]
I (17980) ESP_OTA_CLIENT: -- OTA Client receives data: progress [72/159616]
I (18200) ESP_OTA_CLIENT: -- OTA Client receives data: progress [136/159616]
I (18440) ESP_OTA_CLIENT: -- OTA Client receives data: progress [200/159616]
I (18660) ESP_OTA_CLIENT: -- OTA Client receives data: progress [264/159616]
I (18890) ESP_OTA_CLIENT: -- OTA Client receives data: progress [328/159616]
I (19120) ESP_OTA_CLIENT: -- OTA Client receives data: progress [392/159616]
I (19350) ESP_OTA_CLIENT: -- OTA Client receives data: progress [456/159616]
I (19580) ESP_OTA_CLIENT: -- OTA Client receives data: progress [520/159616]
I (19810) ESP_OTA_CLIENT: -- OTA Client receives data: progress [584/159616]
I (20040) ESP_OTA_CLIENT: -- OTA Client receives data: progress [648/159616]
I (20270) ESP_OTA_CLIENT: -- OTA Client receives data: progress [712/159616]
I (20500) ESP_OTA_CLIENT: -- OTA Client receives data: progress [776/159616]
...
I (597100) ESP_OTA_CLIENT: -- OTA Client receives data: progress [158728/159616]
I (597330) ESP_OTA_CLIENT: -- OTA Client receives data: progress [158792/159616]
I (597560) ESP_OTA_CLIENT: -- OTA Client receives data: progress [158856/159616]
I (597790) ESP_OTA_CLIENT: -- OTA Client receives data: progress [158920/159616]
I (598030) ESP_OTA_CLIENT: -- OTA Client receives data: progress [158984/159616]
I (598260) ESP_OTA_CLIENT: -- OTA Client receives data: progress [159048/159616]
I (598490) ESP_OTA_CLIENT: -- OTA Client receives data: progress [159112/159616]
I (598720) ESP_OTA_CLIENT: -- OTA Client receives data: progress [159176/159616]
I (598950) ESP_OTA_CLIENT: -- OTA Client receives data: progress [159240/159616]
I (599180) ESP_OTA_CLIENT: -- OTA Client receives data: progress [159304/159616]
I (599450) ESP_OTA_CLIENT: -- OTA Client receives data: progress [159368/159616]
I (599690) ESP_OTA_CLIENT: -- OTA Client receives data: progress [159432/159616]
I (599920) ESP_OTA_CLIENT: -- OTA Client receives data: progress [159496/159616]
I (600140) ESP_OTA_CLIENT: -- OTA Client receives data: progress [159560/159616]
I (600420) ESP_OTA_CLIENT: -- OTA Client receives data: progress [159616/159616]
I (600420) ESP_OTA_CLIENT: -- OTA upgrade check status: ESP_OK
I (600490) ESP_OTA_CLIENT: -- OTA upgrade apply
I (605560) ESP_OTA_CLIENT: -- OTA Finish
I (605560) ESP_OTA_CLIENT: -- OTA Information: version: 0x1010110, manufactor code: 0x1001, image type: 0x1011, total size: 159616 bytes, cost time: 588056 ms,
I (605560) esp_image: segment 0: paddr=000d0020 vaddr=42018020 size=08750h ( 34640) map
I (605610) esp_image: segment 1: paddr=000d8778 vaddr=40800000 size=078a0h ( 30880)
I (605650) esp_image: segment 2: paddr=000e0020 vaddr=42000020 size=141f8h ( 82424) map
I (605740) esp_image: segment 3: paddr=000f4220 vaddr=408078a0 size=01da4h (  7588)
I (605750) esp_image: segment 4: paddr=000f5fcc vaddr=40809650 size=00f88h (  3976)
I (605760) esp_image: segment 0: paddr=000d0020 vaddr=42018020 size=08750h ( 34640) map
I (605800) esp_image: segment 1: paddr=000d8778 vaddr=40800000 size=078a0h ( 30880)
I (605830) esp_image: segment 2: paddr=000e0020 vaddr=42000020 size=141f8h ( 82424) map
I (605930) esp_image: segment 3: paddr=000f4220 vaddr=408078a0 size=01da4h (  7588)
I (605940) esp_image: segment 4: paddr=000f5fcc vaddr=40809650 size=00f88h (  3976)
W (605950) ESP_OTA_CLIENT: Prepare to restart system
ESP-ROM:esp32h2-20221101
Build:Nov  1 2022
rst:0xc (SW_CPU),boot:0xc (SPI_FAST_FLASH_BOOT)
Saved PC:0x400031b6
0x400031b6: software_reset_cpu in ROM
...
I (245) cpu_start: Pro cpu start user code
I (245) cpu_start: cpu freq: 96000000 Hz
I (246) cpu_start: Application information:
I (248) cpu_start: Project name:     hello_world
I (253) cpu_start: App version:      c6_h2_rng_final_tests-2545-g54f
I (260) cpu_start: Compile time:     Oct 12 2023 20:27:10
I (266) cpu_start: ELF file SHA256:  b5785ec0d...
Warning: checksum mismatch between flashed and built applications. Checksum of built application is 38ff6cede25780e96382904d67d767d2d901bf9cf04baad40b5990e4f28cb6b8
I (272) cpu_start: ESP-IDF:          v5.2-dev-3300-g54f0517724
I (278) cpu_start: Min chip rev:     v0.0
I (283) cpu_start: Max chip rev:     v0.99
I (288) cpu_start: Chip rev:         v0.1
I (292) heap_init: Initializing. RAM available for dynamic allocation:
I (300) heap_init: At 4080B460 len 00041F20 (263 KiB): D/IRAM
I (306) heap_init: At 4084D380 len 00002B60 (10 KiB): STACK/DIRAM
I (314) spi_flash: detected chip: generic
I (317) spi_flash: flash io: dio
I (322) sleep: Configure to isolate all GPIO pins in sleep state
I (328) sleep: Enable automatic switching of GPIO sleep configuration
I (336) main_task: Started on CPU0
I (336) main_task: Calling app_main()
Hello world!
This is esp32h2 chip with 1 CPU core(s), BLE, 802.15.4 (Zigbee/Thread), silicon revision v0.1, 2MB external flash
Minimum free heap size: 264784 bytes
Restarting in 10 seconds...
Restarting in 9 seconds...
Restarting in 8 seconds...
Restarting in 7 seconds...
Restarting in 6 seconds...
Restarting in 5 seconds...
```

## OTA Upgrade Functions

 * After receiving OTA image notify from server, client send the query image request and image block requests to server upon receiving the response from server.
 * Following diagram explains the OTA upgrade process in detail:
 ![Zigbee_ota](../../../docs/_static/zigbee-ota-upgrade-process.png)
 * Server gets the upgrade bin file (ota_file.bin) and transmit it through OTA process. After upgrade finish, the client will restart. Upgrade bin file will be loaded from client side and a log "OTA example 2.0 is running" can be seen on the log indicates OTA file upgraded successfully.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
