| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |

# OTA Upgrade Example 

This example demonstrates the whole OTA process from Zigbee OTA upgrade client side.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running a Zigbee coordinator with OTA file (see [ota_server](../ota_server/) example)

## Configure the project

Before project configuration and build, set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board will attempt to detect an available Zigbee network.
```
I (424) main_task: Calling app_main()
I (434) OTA_CLIENT: Start ESP Zigbee Stack
I (444) esp zigbee sleep: light sleap disabled
I (454) phy: phy_version: 323,2, a8ef10c, Aug1 2025, 17:46:10
I (454) phy: libbtbb version: 4515421, Aug1 2025, 17:46:22
I (464) OTA_CLIENT: Initialize Zigbee stack 
I (474) OTA_CLIENT: Device started up in factory-reset mode
I (474) main_task: Returned from app_main()
I (2554) OTA_CLIENT: Joined network successfully: PAN ID(0x1c08, EXT: 0x4831b7fffec18405), Channel(13), Short Address(0xa8d6)
```

- If the board is on a network, it acts as the Zigbee end device with the `OTA Upgrade Client` function.

- If an `Image Notify` request from the network is received by the board, a `Query Next Image` request will be sent to query the OTA image information.
```
I (2884) OTA_CLIENT: -- OTA Upgrade Query Next Image Response
I (2884) OTA_CLIENT: New image available:
I (2884) OTA_CLIENT: Server address: 0x4831b7fffec18405
I (2894) OTA_CLIENT: Endpoint: 1 
I (2894) OTA_CLIENT: Manufacturer code: 0x1234
I (2904) OTA_CLIENT: Image type: 0x5678
I (2914) OTA_CLIENT: File version: 0x00000010
I (2914) OTA_CLIENT: Image size: 158966 bytes 
```

- If the image is available, the OTA upgrade process will be initiated.
```
I (2924) OTA_CLIENT: -- OTA Upgrade Downloading Progress
I (2924) OTA_CLIENT: OTA Start: manuf_code=0x1234, image_type=0x5678, file_version=0x00000010, image_size=158966
I (3434) OTA_CLIENT: -- OTA Upgrade Downloading Progress
I (3434) OTA_CLIENT: OTA Receiving Block: file_offset=0, block_size=56 
W (3434) OTA_CLIENT: In progress: [56 / 158966]
```

- After the OTA image is successfully transmitted, the board will reboot with the upgraded image.

```
I (330453) OTA_CLIENT: OTA Receiving Block: file_offset=499966, block_size=223
W (330453) OTA_CLIENT: In progress: [500189 / 501134]
I (330583) OTA_CLIENT: -- OTA Upgrade Client Progress
I (330583) OTA_CLIENT: OTA Receiving Block: file_offset=500189, block_size=223
W (330583) OTA_CLIENT: In progress: [500412 / 501134]
I (330723) OTA_CLIENT: -- OTA Upgrade Client Progress
I (330723) OTA_CLIENT: OTA Receiving Block: file_offset=500412, block_size=223
W (330723) OTA_CLIENT: In progress: [500635 / 501134]
I (330883) OTA_CLIENT: -- OTA Upgrade Client Progress
I (330883) OTA_CLIENT: OTA Receiving Block: file_offset=500635, block_size=223
W (330883) OTA_CLIENT: In progress: [500858 / 501134]
I (331023) OTA_CLIENT: -- OTA Upgrade Client Progress
I (331023) OTA_CLIENT: OTA Receiving Block: file_offset=500858, block_size=223
W (331023) OTA_CLIENT: In progress: [501081 / 501134]
I (331133) OTA_CLIENT: -- OTA Upgrade Client Progress
I (331133) OTA_CLIENT: OTA Receiving Block: file_offset=501081, block_size=53
W (331133) OTA_CLIENT: In progress: [501134 / 501134]
I (331133) OTA_CLIENT: -- OTA Upgrade Client Progress
I (331143) OTA_CLIENT: OTA Check: manuf_code=0x131b, image_type=0x0001, file_version=0x10022000
I (331213) OTA_CLIENT: -- OTA Upgrade Client Progress
I (331213) OTA_CLIENT: OTA Apply: manuf_code=0x131b, image_type=0x0001, file_version=0x10022000
I (331223) esp_image: segment 0: paddr=000c0020 vaddr=42060020 size=107a4h ( 67492) map
I (331243) esp_image: segment 1: paddr=000d07cc vaddr=40800000 size=0784ch ( 30796)
I (331253) esp_image: segment 2: paddr=000d8020 vaddr=42000020 size=59658h (366168) map
I (331323) esp_image: segment 3: paddr=00131680 vaddr=4080784c size=06e10h ( 28176)
I (331333) esp_image: segment 4: paddr=00138498 vaddr=4080e660 size=02090h (  8336)
I (331343) esp_image: segment 0: paddr=000c0020 vaddr=42060020 size=107a4h ( 67492) map
I (331353) esp_image: segment 1: paddr=000d07cc vaddr=40800000 size=0784ch ( 30796)
I (331363) esp_image: segment 2: paddr=000d8020 vaddr=42000020 size=59658h (366168) map
I (331443) esp_image: segment 3: paddr=00131680 vaddr=4080784c size=06e10h ( 28176)
I (331443) esp_image: segment 4: paddr=00138498 vaddr=4080e660 size=02090h (  8336)
I (331493) OTA_CLIENT: -- OTA Upgrade Client Progress
I (331493) OTA_CLIENT: OTA Finish: count_down_delay=0 seconds
ESP-ROM:esp32h2-20221101
Build:Nov  1 2022
rst:0xc (SW_CPU),boot:0xc (SPI_FAST_FLASH_BOOT)
Saved PC:0x400031b6
--- 0x400031b6: software_reset_cpu in ROM

...
 (346) cpu_start: Unicore app
I (355) cpu_start: Pro cpu start user code
I (355) cpu_start: cpu freq: 96000000 Hz
I (356) app_init: Application information:
I (356) app_init: Project name:     OTA_CLIENT
I (360) app_init: App version:      ae11952e-dirty
I (364) app_init: Compile time:     Apr 10 2026 15:53:07
I (369) app_init: ELF file SHA256:  3c1f8ecb8...
--- Warning: Checksum mismatch between flashed and built applications. Checksum of built application is 47351e1b7d8ad1bea9a9ae061d66387e48f2c73420efa8fc5bc9cbbf9b09c9bc
I (374) app_init: ESP-IDF: v5.5.1-dirty
I (378) efuse_init: Min chip rev:     v0.0
I (382) efuse_init: Max chip rev:     v1.99
I (386) efuse_init: Chip rev:v0.1
I (390) heap_init: Initializing. RAM available for dynamic allocation:
I (396) heap_init: At 40812B70 len 0003A810 (234 KiB): RAM
I (401) heap_init: At 4084D380 len 00002B60 (10 KiB): RAM
I (406) heap_init: At 50000000 len 00000FE8 (3 KiB): RTCRAM
I (413) spi_flash: detected chip: gd
I (415) spi_flash: flash io: dio
W (418) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (430) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (436) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (443) main_task: Started on CPU0
I (453) main_task: Calling app_main()
W (453) OTA_CLIENT: ESP Zigbee OTA example (0x10022000) is running
I (473) OTA_CLIENT: Start ESP Zigbee Stack
I (483) phy: phy_version: 323,2, a8ef10c, Aug  1 2025, 17:46:10
I (483) phy: libbtbb version: 4515421, Aug  1 2025, 17:46:22
I (503) OTA_CLIENT: Initialize Zigbee stack
I (503) OTA_CLIENT: Device started up in non factory-reset mode
I (503) OTA_CLIENT: Device reboot
I (503) main_task: Returned from app_main()
```

- The application with version 0x10022000 will run on the board after the device has started up from the upgraded firmware.

- This board can initiate the `Query Next Image` request againwhen the `BOOT` button on the board is pressed.

## OTA Upgrade Message Diagram

 ![Zigbee_ota](../../../docs/_static/zigbee-ota-upgrade-process.png)

## Delta OTA Upgrade Functions

Compressed Delta OTA Updates aims at enabling Over-the-Air firmware update with compressed delta binaries. Instead of the complete binary to be hosted on the OTA update server, a patch file is hosted which is the difference between the base firmware and the new firmware in compressed form.

### Advantages

* Patch file have smaller size than the complete firmware file. This reduces the time and network usage to download the file from server.
* No additional storage partition is required for the "patch".
* Only firmware level changes are required. No bootloader related changes required.

### How to use the function

This example uses `esp_delta_ota` component which available though the [IDF component manager](https://components.espressif.com/component/espressif/esp_delta_ota). Please refer to its documentation for more details.

* Enable `ZB_DELTA_OTA` in menuconfig.
* Install required packages:

```
pip install -r managed_components/espressif__esp_delta_ota/examples/https_delta_ota/tools/requirements.txt
```

* Generate the upgrade file:
    * An old firmware as the base firmware which will flash into the device.
    * A new firmware to which we want to upgrade to.
    * Use the [python tool](./managed_components/espressif__esp_delta_ota/examples/https_delta_ota/tools/esp_delta_ota_patch_gen.py) create the patch file.

        ```
        python esp_delta_ota_patch_gen.py --chip <target> --base_binary <base_binary> --new_binary <new_binary> --patch_file_name <patch_file_name>
        ```

> **_NOTE:_** Make sure that the firmware present in the device is used as `base_binary` while creating the patch file. For this purpose, user should keep backup of the firmware running in the device as it is required for creating the patch file.

## OTA Upgrade Rate Optimization

Here are some ways to optimize the OTA upgrade rate:
- Adjust the `OTA_UPGRADE_MAX_DATA_SIZE` to improve frame exchange; a value of 223 is recommended.
- Increase `FREERTOS_HZ` in menuconfig to enhance the system's response rate. The default value is 100.
- Enable `IEEE802154_TIMING_OPTIMIZATION` in menuconfig to optimize IEEE802154 timing.
- Reduce unrelated logs during the OTA upgrade process.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
