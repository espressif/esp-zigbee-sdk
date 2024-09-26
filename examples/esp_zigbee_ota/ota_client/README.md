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
I (453) app_start: Starting scheduler on CPU0
I (458) main_task: Started on CPU0                                    
I (462) main_task: Calling app_main()
W (466) ESP_OTA_CLIENT: ESP Zigbee OTA example 2.0 is running
I (492) phy: phy_version: 230,2, 9aae6ea, Jan 15 2024, 11:17:12
I (494) phy: libbtbb version: 944f18e, Jan 15 2024, 11:17:25
I (498) main_task: Returned from app_main()
I (552) ESP_OTA_CLIENT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL                                                                
I (553) ESP_OTA_CLIENT: Initialize Zigbee stack
I (558) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:4                                                 
I (558) ESP_OTA_CLIENT: Deferred driver initialization successful
I (571) ESP_OTA_CLIENT: Device started up in  factory-reset mode
I (577) ESP_OTA_CLIENT: Start network steering
I (3472) ESP_OTA_CLIENT: Joined network successfully (Extended PAN ID: 74:4d:bd:ff:fe:63:78:8a, PAN ID: 0xa1ea, Channel:13, Short Address: 0xfc9a)
I (3878) ESP_OTA_CLIENT: Queried OTA image from address: 0x0000, endpoint: 5                                                                 
I (3879) ESP_OTA_CLIENT: Image version: 0x1010110, manufacturer code: 0x1001, image size: 618536                                             
I (3885) ESP_OTA_CLIENT: Approving OTA image upgrade
I (3891) ESP_OTA_CLIENT: -- OTA upgrade start
I (4447) ESP_OTA_CLIENT: -- OTA Client receives data: progress [167/618480]                                                                  
I (4692) ESP_OTA_CLIENT: -- OTA Client receives data: progress [390/618480]                                                                  
I (4937) ESP_OTA_CLIENT: -- OTA Client receives data: progress [613/618480]                                                                  
I (5182) ESP_OTA_CLIENT: -- OTA Client receives data: progress [836/618480]                                                                  
I (5431) ESP_OTA_CLIENT: -- OTA Client receives data: progress [1059/618480]                                                                 
I (5676) ESP_OTA_CLIENT: -- OTA Client receives data: progress [1282/618480]                                                                 
I (5921) ESP_OTA_CLIENT: -- OTA Client receives data: progress [1505/618480]                                                                 
I (6166) ESP_OTA_CLIENT: -- OTA Client receives data: progress [1728/618480]                                                                 
I (6411) ESP_OTA_CLIENT: -- OTA Client receives data: progress [1951/618480]                                                                 
I (6657) ESP_OTA_CLIENT: -- OTA Client receives data: progress [2174/618480]                                                                 
I (6902) ESP_OTA_CLIENT: -- OTA Client receives data: progress [2397/618480]                                                                 
I (7147) ESP_OTA_CLIENT: -- OTA Client receives data: progress [2620/618480]                                                                 
I (7392) ESP_OTA_CLIENT: -- OTA Client receives data: progress [2843/618480]                                                                 
I (7640) ESP_OTA_CLIENT: -- OTA Client receives data: progress [3066/618480]                                                                 
I (7886) ESP_OTA_CLIENT: -- OTA Client receives data: progress [3289/618480]
I (8131) ESP_OTA_CLIENT: -- OTA Client receives data: progress [3512/618480]
...
I (684235) ESP_OTA_CLIENT: -- OTA Client receives data: progress [615201/618480]
I (684484) ESP_OTA_CLIENT: -- OTA Client receives data: progress [615424/618480]
I (684729) ESP_OTA_CLIENT: -- OTA Client receives data: progress [615647/618480]
I (684974) ESP_OTA_CLIENT: -- OTA Client receives data: progress [615870/618480]
I (685220) ESP_OTA_CLIENT: -- OTA Client receives data: progress [616093/618480]
I (685465) ESP_OTA_CLIENT: -- OTA Client receives data: progress [616316/618480]
I (685715) ESP_OTA_CLIENT: -- OTA Client receives data: progress [616539/618480]
I (685966) ESP_OTA_CLIENT: -- OTA Client receives data: progress [616762/618480]
I (686217) ESP_OTA_CLIENT: -- OTA Client receives data: progress [616985/618480]
I (686462) ESP_OTA_CLIENT: -- OTA Client receives data: progress [617208/618480]
I (686707) ESP_OTA_CLIENT: -- OTA Client receives data: progress [617431/618480]
I (686952) ESP_OTA_CLIENT: -- OTA Client receives data: progress [617654/618480]
I (687198) ESP_OTA_CLIENT: -- OTA Client receives data: progress [617877/618480]
I (687445) ESP_OTA_CLIENT: -- OTA Client receives data: progress [618100/618480]
I (687690) ESP_OTA_CLIENT: -- OTA Client receives data: progress [618323/618480]
I (687932) ESP_OTA_CLIENT: -- OTA Client receives data: progress [618480/618480]
I (687933) ESP_OTA_CLIENT: -- OTA upgrade check status: ESP_OK
I (687973) ESP_OTA_CLIENT: -- OTA upgrade apply
I (692974) ESP_OTA_CLIENT: -- OTA Finish
I (692974) ESP_OTA_CLIENT: -- OTA Information: version: 0x1010110, manufacturer code: 0x1001, image type: 0x1011, total size: 618480 bytes, cost time: 689078 ms,
I (692983) esp_image: segment 0: paddr=00110020 vaddr=42078020 size=10d18h ( 68888) map
I (693070) esp_image: segment 1: paddr=00120d40 vaddr=40800000 size=072d8h ( 29400) 
I (693104) esp_image: segment 2: paddr=00128020 vaddr=42000020 size=77fe0h (491488) map
I (693658) esp_image: segment 3: paddr=001a0008 vaddr=408072d8 size=06fc0h ( 28608) 
I (693692) esp_image: segment 0: paddr=00110020 vaddr=42078020 size=10d18h ( 68888) map
I (693771) esp_image: segment 1: paddr=00120d40 vaddr=40800000 size=072d8h ( 29400) 
I (693806) esp_image: segment 2: paddr=00128020 vaddr=42000020 size=77fe0h (491488) map
I (694360) esp_image: segment 3: paddr=001a0008 vaddr=408072d8 size=06fc0h ( 28608) 
W (694417) ESP_OTA_CLIENT: Prepare to restart system
ESP-ROM:esp32h2-20221101                                              
Build:Nov  1 2022                                                     
rst:0xc (SW_CPU),boot:0xc (SPI_FAST_FLASH_BOOT)
Saved PC:0x400031b6                                                   
0x400031b6: software_reset_cpu in ROM

...
I (552) main_task: Started on CPU0                                    
I (556) main_task: Calling app_main()
W (560) ESP_OTA_CLIENT: ESP Zigbee OTA example 2.0 is running
I (585) phy: phy_version: 230,2, 9aae6ea, Jan 15 2024, 11:17:12
I (587) phy: libbtbb version: 944f18e, Jan 15 2024, 11:17:25
I (598) main_task: Returned from app_main()
I (600) ESP_OTA_CLIENT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (601) ESP_OTA_CLIENT: Initialize Zigbee stack
I (2969) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:4 
I (2969) ESP_OTA_CLIENT: Deferred driver initialization successful
I (2975) ESP_OTA_CLIENT: Device started up in non factory-reset mode
I (2982) ESP_OTA_CLIENT: Device rebooted
I (3090) ESP_OTA_CLIENT: Queried OTA image from address: 0x0000, endpoint: 5
I (3091) ESP_OTA_CLIENT: Image version: 0x1010110, manufacturer code: 0x1001, image size: 618536
I (3097) ESP_OTA_CLIENT: Rejecting OTA image upgrade, status: ESP_ERR_INVALID_VERSION
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
