| Supported Targets | ESP32-H2 |
| ----------------- | -------- |

# OTA Upgrade Example 

This example code shows how to add OTA server parameter, add OTA server cluster and add endpoint to a device as well as performing an OTA process.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee coordinator device (loaded with ota_server example)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee end device (loaded with ota_client example), (see [ota_client](../ota_client/))

## Configure the project

Before project configuration and build, set the correct chip target using `idf.py --preview set-target esp32h2`.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

As you run the example, you will see the following log:

```
I (377) spi_flash: detected chip: generic
I (381) spi_flash: flash io: dio
I (398) cpu_start: Starting scheduler.
I (509) phy: phy_version: 101,1, 7943bb3, Jul 26 2022, 11:31:12
I (879) ESP_OTA_SERVER: ZDO signal: 23, status: -1
I (879) ESP_OTA_SERVER: Zigbee stack initialized
I (879) ESP_OTA_SERVER: Start network formation
I (1389) ESP_OTA_SERVER: ZDO signal: 54, status: 0
I (1389) ESP_OTA_SERVER: Formed network successfully (Extended PAN ID: ff:fc:74:c0:f0:bd:97:10, PAN ID: 0x31d3)
I (1849) ESP_OTA_SERVER: ZDO signal: 54, status: 0
I (1849) ESP_OTA_SERVER: Network steering started
I (2729) ESP_OTA_SERVER: ZDO signal: 18, status: 0
I (3239) ESP_OTA_SERVER: ZDO signal: 48, status: 0
I (3279) ESP_OTA_SERVER: New device commissioned or rejoined (short: 0x7bbd)
I (3279) ESP_ZIGBEE_OTA: esp zigbee ota server start
I (3389) ESP_OTA_SERVER: ZDO signal: 47, status: 0
I (3429) ESP_OTA_SERVER: ZDO signal: 54, status: 0
I (3026279) ESP_OTA_SERVER: New device commissioned or rejoined (short: 0x7bbd)
```

## OTA Upgrade Functions

 *  After server starts, server send OTA image notify to client. Then client send the query image request to server.
 *  On receipt of the query image request, server initializes by loading the client that holds the three field values (manufacturer code, image type and new file version). If the client values matches with server values, server send response back to client. Otherwise, it shall discard the command and no further processing shall continue.
 *  Following diagram explains the OTA upgrade process in detail:
 ![Zigbee_ota](../zigbee-ota-upgrade-process.png)
 * There will be offset time of 5 seconds, calculated by the difference between upgrade time and current time and use it as upgrade delay.
 * ota_file.bin is upgrade bin file for client side to upgrade. Server gets the upgrade bin file (ota_file.bin) and transmit it through OTA process. After OTA finish, the client receive the upgrade bin file and trigger restart. For details see the [esp_ota_client](../ota_client/README.md).

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
