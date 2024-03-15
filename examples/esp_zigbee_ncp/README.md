| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Ncp Example 

This example code shows how to configure Zigbee ncp (Network Co-Processor) device.

## Hardware Required

* The example is a single SoC solution, it doesn't need a Wi-Fi SoC to run the example. We will provide a esp_zigbee_host example later as a reference.
* A USB cable for power supply, output log and programming.
* Choose ESP32 or ESP32-S3 as host and **Flash** Zigbee ncp on the ESP32-H2 DevKitC .
* Connect the two SoCs via UART, below is an example setup with ESP32-DevKitC and ESP32-H2-DevKitC:

ESP32 pin     | ESP32-H2 pin
------------- |-------------
   GND        |    GND
   TX         |    GPIO4 (RX)
   RX         |    GPIO5 (TX)

* TX, RX pin can be also configured by `idf.py menuconfig` -> `Component config` -> `Zigbee Network Co-processor`

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board by running `idf.py -p <PORT> build flash`

## Ncp Functions

 * After ncp starts up, it will start working together with host via UART communication

## Example Output

As you run the example, you will see the following log:

```
I (215) cpu_start: Unicore app
I (215) cpu_start: Pro cpu up.
W (224) clk: esp_perip_clk_init() has not been implemented yet
I (231) cpu_start: Pro cpu start user code
I (231) cpu_start: cpu freq: 96000000 Hz
I (232) cpu_start: Application information:
I (234) cpu_start: Project name:     esp_zigbee_ncp
I (239) cpu_start: App version:      bf601f7-dirty
I (245) cpu_start: Compile time:     Jan  8 2024 14:19:02
I (251) cpu_start: ELF file SHA256:  3289485a32051de4...
I (257) cpu_start: ESP-IDF:          v5.1.2
I (262) cpu_start: Min chip rev:     v0.0
I (266) cpu_start: Max chip rev:     v0.99 
I (271) cpu_start: Chip rev:         v0.2
I (276) heap_init: Initializing. RAM available for dynamic allocation:
I (283) heap_init: At 40815790 len 00037BF0 (222 KiB): D/IRAM
I (290) heap_init: At 4084D380 len 00002B60 (10 KiB): STACK/DIRAM
I (297) spi_flash: detected chip: generic
I (301) spi_flash: flash io: dio
W (305) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (318) sleep: Configure to isolate all GPIO pins in sleep state
I (325) sleep: Enable automatic switching of GPIO sleep configuration
I (332) app_start: Starting scheduler on CPU0
I (337) main_task: Started on CPU0
I (337) main_task: Calling app_main()
I (347) uart: queue free spaces: 20
I (347) main_task: Returned from app_main()
```

When receive `NCP_FRAME_ID_NETWORK_INIT`, `NCP_FRAME_ID_NETWORK_PRIMARY_CHANNEL_SET`, `NCP_FRAME_ID_NETWORK_FORMNETWORK` and `NCP_FRAME_ID_START`, you will see the following log:

```
I (187677) ESP_NCP_FRAME: 00 00 00 00 00 00 00 ff ff 
I (189617) ESP_NCP_FRAME: 00 00 05 00 05 04 00 00 20 00 00 d3 6e 
I (191197) ESP_NCP_FRAME: 00 00 09 00 09 07 00 00 00 14 00 00 00 00 fa 45 
I (191207) phy: phy_version: 211,0, 5857fe5, Nov  1 2023, 11:31:09
I (191207) phy: libbtbb version: ce629d6, Nov  1 2023, 11:31:19
I (193627) ESP_NCP_FRAME: 00 00 1c 00 1c 15 00 25 20 00 00 00 00 00 00 0a 
I (193627) ESP_NCP_FRAME: 01 00 00 00 06 00 03 00 00 10 01 00 d0 46 
I (193627) ESP_NCP_ZB: addr 2025, dst_endpoint a, src_endpoint 1, address_mode 0, profile_id 00, cluster_id 06, cmd_id 03, direction 00
I (195487) ESP_NCP_FRAME: 00 00 0d 00 0d 01 00 00 73 1b 
I (195497) ESP_NCP_ZB: Zigbee stack initialized
W (195507) ESP_NCP_ZB: Network(0x92b6) closed, devices joining not allowed.
I (195507) ESP_NCP_ZB: Start network formation
I (195507) ESP_NCP_ZB: Formed network successfully (Extended PAN ID: 60:55:f9:ff:fe:f7:39:f7, PAN ID: 0x92b6, Channel:25)
I (196097) ESP_NCP_ZB: Network(0x92b6) is open for 180 seconds
I (196097) ESP_NCP_ZB: Network steering started
```

It means that the device work on a coordinator and wait for a end device joining. When a new device joined successfully, you will see the following log:

```
I (198237) ESP_NCP_ZB: New device commissioned or rejoined (short: 0x60c9)
I (198417) ESP_NCP_ZB: Network(0x92b6) is open for 180 seconds

```

Then the device can process the ZCL command and attribute, eg: `NCP_FRAME_ID_ZCL_WRITE`, `NCP_FRAME_ID_ATTR_READ` and so on.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon
