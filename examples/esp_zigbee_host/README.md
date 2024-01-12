| Supported Targets | ESP32 | ESP32-C3 | ESP32-C6 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- |

# Host Example 

This example demonstrates how to build a host device. It runs on any Espressif Wi-Fi SoCs such as ESP32, ESP32-C3 and ESP32-S3, with an 802.15.4 SoC like ESP32-H2 running [esp_zigbee_ncp](../esp_zigbee_ncp) to provide Zigbee functionality.

## Hardware Required

* One development board with ESP32 or ESP32-S3 SoC acting as Zigbee host (loaded with esp_zigbee_host example)
* A USB cable for power supply, output log and programming
* Three jumper wires for UART (TX, RX, and GND)
* Choose ESP32 or ESP32-S3 as host and **Flash** Zigbee ncp on the ESP32-H2 DevKitC
* Connect the two SoCs via UART, below is an example setup with ESP32-DevKitC and ESP32-H2-DevKitC:

ESP32 pin     | ESP32-H2 pin
------------- |-------------
   GND        |    GND
   TX         |    GPIO4 (RX)
   RX         |    GPIO5 (TX)

* TX, RX pin can be also configured by `idf.py menuconfig` -> `Component config` -> `Zigbee NCP Host`

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board by running `idf.py -p <PORT> build flash`

## Host Functions

 * After ncp starts up, it will start working together with host via UART communication
 * More Host functionalities supporting Wi-Fi interaction will come later

## Example Output

As you run the example, you will see the following log:

```
I (169) cpu_start: Pro cpu start user code
I (169) cpu_start: cpu freq: 160000000 Hz
I (169) cpu_start: Application information:
I (174) cpu_start: Project name:     esp_zigbee_host
I (179) cpu_start: App version:      200bb14-dirty
I (185) cpu_start: Compile time:     Jan 29 2024 20:21:28
I (191) cpu_start: ELF file SHA256:  5e169858d9058980...
I (197) cpu_start: ESP-IDF:          v5.1.2
I (202) cpu_start: Min chip rev:     v0.0
I (206) cpu_start: Max chip rev:     v3.99 
I (211) cpu_start: Chip rev:         v0.0
I (216) heap_init: Initializing. RAM available for dynamic allocation:
I (223) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (229) heap_init: At 3FFB2AB8 len 0002D548 (181 KiB): DRAM
I (236) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (242) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (248) heap_init: At 4008E0A0 len 00011F60 (71 KiB): IRAM
I (256) spi_flash: detected chip: gd
I (259) spi_flash: flash io: dio
W (263) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (277) app_start: Starting scheduler on CPU0
I (281) app_start: Starting scheduler on CPU1
I (281) main_task: Started on CPU0
I (291) main_task: Calling app_main()
I (301) uart: queue free spaces: 20
I (311) gpio: GPIO[0]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2 
I (311) main_task: Returned from app_main()
```

When receive `ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP`, `ESP_ZB_NWK_SIGNAL_PERMIT_JOIN_STATUS` and `ESP_ZB_BDB_SIGNAL_FORMATION`, you will see the following log:

```
I (311) ESP_ZNSP_FRAME: 10 00 00 00 d0 01 00 00 23 06 
I (321) ESP_ZB_ON_OFF_SWITCH: Zigbee stack initialized
I (351) ESP_ZNSP_FRAME: 10 00 04 00 71 01 00 00 09 a8 
I (371) ESP_ZNSP_FRAME: 10 00 00 01 c0 01 00 00 c6 ce 
I (381) ESP_ZNSP_FRAME: 10 00 10 00 7a 01 00 00 00 3a 
I (401) ESP_ZNSP_FRAME: 10 00 01 00 39 01 00 00 e1 4f 
I (411) ESP_ZNSP_FRAME: 20 00 05 00 73 01 00 00 dc 78 
I (421) ESP_ZNSP_FRAME: 10 00 0b 00 ab 02 00 04 25 78 f3 
W (411) ESP_ZB_ON_OFF_SWITCH: Network(0x2504) closed, devices joining not allowed.
I (431) ESP_ZNSP_FRAME: 20 00 04 00 78 0b 00 21 2e c0 fe ff b7 31 48 04 
I (431) ESP_ZNSP_FRAME: 25 0d ed 9c 
I (441) ESP_ZNSP_FRAME: 10 00 0d 00 3b 08 00 21 2e c0 fe ff b7 31 48 b6 
I (441) ESP_ZNSP_FRAME: 52 
I (451) ESP_ZNSP_FRAME: 10 00 0b 00 3c 02 00 04 25 b1 fd 
I (461) ESP_ZNSP_FRAME: 10 00 13 00 be 01 00 0d ad a4 
I (471) ESP_ZNSP_FRAME: 10 00 1d 00 7d 02 00 00 00 1c cb 
I (451) ESP_ZB_ON_OFF_SWITCH: Formed network successfully (Extended PAN ID: 48:31:b7:ff:fe:c0:2e:21, PAN ID: 0x2504, Channel:13, Short Address: 0x0000)
I (1001) ESP_ZNSP_FRAME: 20 00 05 00 be 01 00 b4 25 3b 
I (1011) ESP_ZNSP_FRAME: 10 00 0b 00 ac 02 00 04 25 a4 c3 
I (1001) ESP_ZB_ON_OFF_SWITCH: Network(0x2504) is open for 180 seconds

```

It means that the device work on a coordinator and wait for a end device joining. When a new device joined successfully, you will see the following log:

```
I (8001) ESP_ZNSP_FRAME: 20 00 06 00 eb 0c 00 50 03 f7 39 f7 fe ff f9 55 
I (8001) ESP_ZNSP_FRAME: 60 8c 00 64 b2 
I (8011) ESP_ZB_ON_OFF_SWITCH: New device commissioned or rejoined (short: 0x0350)
I (8031) ESP_ZNSP_FRAME: 10 00 02 02 79 01 00 00 a3 43 
I (8101) ESP_ZNSP_FRAME: 20 00 02 02 bc 0f 00 00 00 00 00 50 03 0a b0 5d 
I (8101) ESP_ZNSP_FRAME: 0d 40 00 00 00 00 10 2c 
I (8101) ESP_ZB_ON_OFF_SWITCH: Found light
I (8121) ESP_ZNSP_FRAME: 10 00 2c 00 1e 08 00 f7 39 f7 fe ff f9 55 60 ed 
I (8121) ESP_ZNSP_FRAME: f3 
I (8131) ESP_ZNSP_FRAME: 10 00 1f 00 3f 08 00 21 2e c0 fe ff b7 31 48 69 
I (8131) ESP_ZNSP_FRAME: 5d 
I (8141) ESP_ZNSP_FRAME: 10 00 1d 00 57 02 00 00 00 25 e7 
I (8141) ESP_ZB_ON_OFF_SWITCH: Try to bind On/Off
I (8161) ESP_ZNSP_FRAME: 10 00 00 02 15 01 00 00 25 45 
I (8171) ESP_ZNSP_FRAME: 20 00 00 02 f8 0c 00 00 00 00 00 2c 5e 0d 40 60 
I (8171) ESP_ZNSP_FRAME: fc fa 3f 70 60 
I (8171) ESP_ZB_ON_OFF_SWITCH: Bound successfully!
I (8181) ESP_ZB_ON_OFF_SWITCH: The light originating from address(0x350) on endpoint(10)

```

Then the device can process the ZCL command and attribute, eg: `NCP_FRAME_ID_ZCL_WRITE`, `NCP_FRAME_ID_ATTR_READ` and so on. you will see the following log:

```
I (11811) ESP_ZB_ON_OFF_SWITCH: Send 'on_off toggle' command
I (11831) ESP_ZNSP_FRAME: 10 00 07 01 cc 01 00 00 23 45 
I (12881) ESP_ZB_ON_OFF_SWITCH: Send 'on_off toggle' command
I (12901) ESP_ZNSP_FRAME: 10 00 07 01 98 01 00 00 d9 e2 
I (13711) ESP_ZB_ON_OFF_SWITCH: Send 'on_off toggle' command
I (13731) ESP_ZNSP_FRAME: 10 00 07 01 3d 01 00 00 b3 2e 
I (14641) ESP_ZB_ON_OFF_SWITCH: Send 'on_off toggle' command
I (14661) ESP_ZNSP_FRAME: 10 00 07 01 51 01 00 00 63 20 
I (15501) ESP_ZB_ON_OFF_SWITCH: Send 'on_off toggle' command
I (15521) ESP_ZNSP_FRAME: 10 00 07 01 e6 01 00 00 de 16 
I (16231) ESP_ZB_ON_OFF_SWITCH: Send 'on_off toggle' command
I (16251) ESP_ZNSP_FRAME: 10 00 07 01 db 01 00 00 a3 d1 
```

Then the end device will toggle on/off.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon
