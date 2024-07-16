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
W (420) ESP_OTA_CLIENT: ESP Zigbee OTA example 1.0 is running
I (450) phy: phy_version: 210,0, 11c334c, Sep  4 2023, 17:01:13
I (450) phy: libbtbb version: b821802, Sep  4 2023, 17:01:29
I (460) main_task: Returned from app_main()
I (530) ESP_OTA_CLIENT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (17500) ESP_OTA_CLIENT: -- OTA upgrade start
I (17600) ESP_OTA_CLIENT: Joined network successfully (Extended PAN ID: 60:55:f9:ff:fe:f7:2e:16, PAN ID: 0x397c, Channel:13)
I (17740) ESP_OTA_CLIENT: -- OTA Client receives data: progress [8/552328]
I (17980) ESP_OTA_CLIENT: -- OTA Client receives data: progress [72/552328]
I (18200) ESP_OTA_CLIENT: -- OTA Client receives data: progress [136/552328]
I (18440) ESP_OTA_CLIENT: -- OTA Client receives data: progress [200/552328]
I (18660) ESP_OTA_CLIENT: -- OTA Client receives data: progress [264/552328]
I (18890) ESP_OTA_CLIENT: -- OTA Client receives data: progress [328/552328]
I (19120) ESP_OTA_CLIENT: -- OTA Client receives data: progress [392/552328]
I (19350) ESP_OTA_CLIENT: -- OTA Client receives data: progress [456/552328]
I (19580) ESP_OTA_CLIENT: -- OTA Client receives data: progress [520/552328]
I (19810) ESP_OTA_CLIENT: -- OTA Client receives data: progress [584/552328]
I (20040) ESP_OTA_CLIENT: -- OTA Client receives data: progress [648/552328]
I (20270) ESP_OTA_CLIENT: -- OTA Client receives data: progress [712/552328]
I (20500) ESP_OTA_CLIENT: -- OTA Client receives data: progress [776/552328]
...
I (2006958) ESP_OTA_CLIENT: -- OTA Client receives data: progress [552584/552928]                                                            
I (2007188) ESP_OTA_CLIENT: -- OTA Client receives data: progress [552648/552928]                                                            
I (2007418) ESP_OTA_CLIENT: -- OTA Client receives data: progress [552712/552928]                                                            
I (2007648) ESP_OTA_CLIENT: -- OTA Client receives data: progress [552776/552928]                                                            
I (2007878) ESP_OTA_CLIENT: -- OTA Client receives data: progress [552840/552928]                                                            
I (2008108) ESP_OTA_CLIENT: -- OTA Client receives data: progress [552904/552928]                                                            
I (2008338) ESP_OTA_CLIENT: -- OTA Client receives data: progress [552928/552928]                                                            
I (2008338) ESP_OTA_CLIENT: -- OTA upgrade check status: ESP_OK
I (2008388) ESP_OTA_CLIENT: -- OTA upgrade apply               
I (2013398) ESP_OTA_CLIENT: -- OTA Finish                   
I (2013398) ESP_OTA_CLIENT: -- OTA Information: version: 0x1010110, manufacturer code: 0x1001, image type: 0x1011, total size: 552928 bytes, cost time: 2002578 ms,
I (2013398) esp_image: segment 0: paddr=00110020 vaddr=42070020 size=10fb8h ( 69560) map                                                     
I (2013488) esp_image: segment 1: paddr=00120fe0 vaddr=40800000 size=07038h ( 28728)                                                         
I (2013518) esp_image: segment 2: paddr=00128020 vaddr=42000020 size=6866ch (427628) map                                                     
I (2013998) esp_image: segment 3: paddr=00190694 vaddr=40807038 size=06928h ( 26920)                                                         
I (2014028) esp_image: segment 0: paddr=00110020 vaddr=42070020 size=10fb8h ( 69560) map                                                     
I (2014108) esp_image: segment 1: paddr=00120fe0 vaddr=40800000 size=07038h ( 28728)                                                         
I (2014138) esp_image: segment 2: paddr=00128020 vaddr=42000020 size=6866ch (427628) map                                                     
I (2014618) esp_image: segment 3: paddr=00190694 vaddr=40807038 size=06928h ( 26920)   
W (2014688) ESP_OTA_CLIENT: Prepare to restart system
ESP-ROM:esp32h2-20221101                                              
Build:Nov  1 2022                                                                                                                            
rst:0xc (SW_CPU),boot:0xc (SPI_FAST_FLASH_BOOT)
Saved PC:0x400031b6
0x400031b6: software_reset_cpu in ROM

...
I (388) boot: Loaded app from partition at offset 0x110000
I (389) boot: Disabling RNG early entropy source...
I (400) cpu_start: Unicore app                                        
I (401) cpu_start: Pro cpu up.                                        
W (410) clk: esp_perip_clk_init() has not been implemented yet
I (417) cpu_start: Pro cpu start user code
I (417) cpu_start: cpu freq: 96000000 Hz
I (417) cpu_start: Application information:
I (420) cpu_start: Project name:     esp_ota_client
I (425) cpu_start: App version:      6e967b2-dirty
I (431) cpu_start: Compile time:     Jul 11 2024 14:22:26
I (437) cpu_start: ELF file SHA256:  54626c3368d1c5e7...
Warning: checksum mismatch between flashed and built applications. Checksum of built application is bc0b636f48447b6879fea08e501d6bc2e97430c1bd8cfdd60eea62a52de6d9de
I (443) cpu_start: ESP-IDF:          v5.1.3
I (447) cpu_start: Min chip rev:     v0.0
I (452) cpu_start: Max chip rev:     v0.99 
I (457) cpu_start: Chip rev:         v0.1
I (462) heap_init: Initializing. RAM available for dynamic allocation:
I (469) heap_init: At 408120E0 len 0003B2A0 (236 KiB): D/IRAM
I (475) heap_init: At 4084D380 len 00002B60 (10 KiB): STACK/DIRAM
I (483) spi_flash: detected chip: generic
I (487) spi_flash: flash io: dio                                      
W (491) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.   
I (504) sleep: Configure to isolate all GPIO pins in sleep state
I (511) sleep: Enable automatic switching of GPIO sleep configuration
I (518) app_start: Starting scheduler on CPU0
I (523) main_task: Started on CPU0                                    
I (523) main_task: Calling app_main()
W (523) ESP_OTA_CLIENT: ESP Zigbee OTA example 2.0 is running
I (553) phy: phy_version: 230,2, 9aae6ea, Jan 15 2024, 11:17:12
I (553) phy: libbtbb version: 944f18e, Jan 15 2024, 11:17:25
I (563) main_task: Returned from app_main()
I (573) ESP_OTA_CLIENT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL                                                                
I (573) ESP_OTA_CLIENT: Initialize Zigbee stack
I (2953) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:4                                                
I (2953) ESP_OTA_CLIENT: Deferred driver initialization successful
I (2963) ESP_OTA_CLIENT: Device started up in non factory-reset mode
I (2963) ESP_OTA_CLIENT: Device rebooted
```

Note: The example also supports the user pressing the `boot` button to send the `QUERY_NEXT_IMAGE` command to query the image from the coordinator.

## OTA Upgrade Functions

 * After receiving OTA image notify from server, client send the query image request and image block requests to server upon receiving the response from server.
 * Following diagram explains the OTA upgrade process in detail:
 ![Zigbee_ota](../../../docs/_static/zigbee-ota-upgrade-process.png)
 * Server gets the upgrade bin file (ota_file.bin) and transmit it through OTA process. After upgrade finish, the client will restart. Upgrade bin file will be loaded from client side and a log "OTA example 2.0 is running" can be seen on the log indicates OTA file upgraded successfully.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
