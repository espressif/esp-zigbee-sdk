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
I (414) main_task: Started on CPU0
I (424) main_task: Calling app_main()
W (424) ESP_OTA_CLIENT: ESP Zigbee OTA example 1.0 is running
I (444) phy: phy_version: 310,2, 8fa9cb4, Jun  5 2024, 14:19:10
I (444) phy: libbtbb version: a024da6, Jun  5 2024, 14:19:22
I (454) main_task: Returned from app_main()
I (524) ESP_OTA_CLIENT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (524) ESP_OTA_CLIENT: Initialize Zigbee stack
I (524) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:4 
I (524) ESP_OTA_CLIENT: Deferred driver initialization successful
I (544) ESP_OTA_CLIENT: Device started up in factory-reset mode
I (544) ESP_OTA_CLIENT: Start network steering
I (25254) ESP_OTA_CLIENT: Joined network successfully (Extended PAN ID: 48:31:b7:ff:fe:c0:2b:6b, PAN ID: 0x0841, Channel:13, Short Address: 0x43a7)
I (25824) ESP_OTA_CLIENT: Queried OTA image from address: 0x0000, endpoint: 5
I (25824) ESP_OTA_CLIENT: Image version: 0x1010101, manufacturer code: 0x1001, image size: 618542
I (25824) ESP_OTA_CLIENT: Approving OTA image upgrade
I (25834) ESP_OTA_CLIENT: -- OTA upgrade start
I (26494) ESP_OTA_CLIENT: -- OTA Client receives data: progress [167/618486]
I (26734) ESP_OTA_CLIENT: -- OTA Client receives data: progress [390/618486]
I (26984) ESP_OTA_CLIENT: -- OTA Client receives data: progress [613/618486]
I (27234) ESP_OTA_CLIENT: -- OTA Client receives data: progress [836/618486]
I (27494) ESP_OTA_CLIENT: -- OTA Client receives data: progress [1059/618486]
I (27744) ESP_OTA_CLIENT: -- OTA Client receives data: progress [1282/618486]
I (27994) ESP_OTA_CLIENT: -- OTA Client receives data: progress [1505/618486]
I (28244) ESP_OTA_CLIENT: -- OTA Client receives data: progress [1728/618486]
I (28494) ESP_OTA_CLIENT: -- OTA Client receives data: progress [1951/618486]
I (28744) ESP_OTA_CLIENT: -- OTA Client receives data: progress [2174/618486]
I (28994) ESP_OTA_CLIENT: -- OTA Client receives data: progress [2397/618486]
I (29244) ESP_OTA_CLIENT: -- OTA Client receives data: progress [2620/618486]
I (29494) ESP_OTA_CLIENT: -- OTA Client receives data: progress [2843/618486]
I (29744) ESP_OTA_CLIENT: -- OTA Client receives data: progress [3066/618486]
I (29994) ESP_OTA_CLIENT: -- OTA Client receives data: progress [3289/618486]
I (30254) ESP_OTA_CLIENT: -- OTA Client receives data: progress [3512/618486]
...
I (720604) ESP_OTA_CLIENT: -- OTA Client receives data: progress [615201/618486]
I (720854) ESP_OTA_CLIENT: -- OTA Client receives data: progress [615424/618486]
I (721104) ESP_OTA_CLIENT: -- OTA Client receives data: progress [615647/618486]
I (721354) ESP_OTA_CLIENT: -- OTA Client receives data: progress [615870/618486]
I (721604) ESP_OTA_CLIENT: -- OTA Client receives data: progress [616093/618486]
I (721854) ESP_OTA_CLIENT: -- OTA Client receives data: progress [616316/618486]
I (722104) ESP_OTA_CLIENT: -- OTA Client receives data: progress [616539/618486]
I (722354) ESP_OTA_CLIENT: -- OTA Client receives data: progress [616762/618486]
I (722604) ESP_OTA_CLIENT: -- OTA Client receives data: progress [616985/618486]
I (722854) ESP_OTA_CLIENT: -- OTA Client receives data: progress [617208/618486]
I (723114) ESP_OTA_CLIENT: -- OTA Client receives data: progress [617431/618486]
I (723364) ESP_OTA_CLIENT: -- OTA Client receives data: progress [617654/618486]
I (723614) ESP_OTA_CLIENT: -- OTA Client receives data: progress [617877/618486]
I (723864) ESP_OTA_CLIENT: -- OTA Client receives data: progress [618100/618486]
I (724124) ESP_OTA_CLIENT: -- OTA Client receives data: progress [618323/618486]
I (724374) ESP_OTA_CLIENT: -- OTA Client receives data: progress [618486/618486]
I (724374) ESP_OTA_CLIENT: -- OTA upgrade check status: ESP_OK
I (724414) ESP_OTA_CLIENT: -- OTA upgrade apply
I (729424) ESP_OTA_CLIENT: -- OTA Finish
I (729424) ESP_OTA_CLIENT: -- OTA Information: version: 0x1010101, manufacturer code: 0x1001, image type: 0x1011, total size: 618486 bytes, cost time: 703581 ms,
I (729424) esp_image: segment 0: paddr=00110020 vaddr=42078020 size=10d18h ( 68888) map
I (729514) esp_image: segment 1: paddr=00120d40 vaddr=40800000 size=072d8h ( 29400) 
I (729544) esp_image: segment 2: paddr=00128020 vaddr=42000020 size=77fe0h (491488) map
I (730094) esp_image: segment 3: paddr=001a0008 vaddr=408072d8 size=06fc0h ( 28608) 
I (730134) esp_image: segment 0: paddr=00110020 vaddr=42078020 size=10d18h ( 68888) map
I (730214) esp_image: segment 1: paddr=00120d40 vaddr=40800000 size=072d8h ( 29400) 
I (730244) esp_image: segment 2: paddr=00128020 vaddr=42000020 size=77fe0h (491488) map
I (730794) esp_image: segment 3: paddr=001a0008 vaddr=408072d8 size=06fc0h ( 28608) 
W (730844) ESP_OTA_CLIENT: Prepare to restart system
ESP-ROM:esp32h2-20221101
Build:Nov  1 2022
rst:0xc (SW_CPU),boot:0xc (SPI_FAST_FLASH_BOOT)
Saved PC:0x400031b6
--- 0x400031b6: software_reset_cpu in ROM

...
I (558) main_task: Started on CPU0
I (562) main_task: Calling app_main()
W (566) ESP_OTA_CLIENT: ESP Zigbee OTA example 2.0 is running
I (591) phy: phy_version: 230,2, 9aae6ea, Jan 15 2024, 11:17:12
I (593) phy: libbtbb version: 944f18e, Jan 15 2024, 11:17:25
I (604) main_task: Returned from app_main()
I (606) ESP_OTA_CLIENT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (607) ESP_OTA_CLIENT: Initialize Zigbee stack
I (2975) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:4 
I (2975) ESP_OTA_CLIENT: Deferred driver initialization successful
I (2981) ESP_OTA_CLIENT: Device started up in non factory-reset mode
I (2988) ESP_OTA_CLIENT: Device rebooted
I (100250) ESP_OTA_CLIENT: Queried OTA image from address: 0x0000, endpoint: 5
I (100251) ESP_OTA_CLIENT: Image version: 0x1010101, manufacturer code: 0x1001, image size: 618542
I (100257) ESP_OTA_CLIENT: Rejecting OTA image upgrade, status: ESP_ERR_INVALID_VERSION
```

Note: The example also supports the user pressing the `boot` button to send the `QUERY_NEXT_IMAGE` command to query the image from the coordinator.

## OTA Upgrade Functions

 * After receiving OTA image notify from server, client send the query image request and image block requests to server upon receiving the response from server.
 * Following diagram explains the OTA upgrade process in detail:
 ![Zigbee_ota](../../../docs/_static/zigbee-ota-upgrade-process.png)
 * Server gets the upgrade bin file (ota_file.bin) and transmit it through OTA process. After upgrade finish, the client will restart. Upgrade bin file will be loaded from client side and a log "OTA example 2.0 is running" can be seen on the log indicates OTA file upgraded successfully.

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
