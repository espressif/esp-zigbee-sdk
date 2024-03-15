| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# OTA Upgrade Example 

This example code shows how to add OTA server parameter, add OTA server cluster and add endpoint to a device as well as performing an OTA process.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee coordinator device (loaded with ota_server example)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee end device (loaded with ota_client example), (see [ota_client](../ota_client/))

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
I (470) main_task: Calling app_main()
I (500) phy: phy_version: 210,0, 11c334c, Sep  4 2023, 17:01:13
I (500) phy: libbtbb version: b821802, Sep  4 2023, 17:01:29
I (500) main_task: Returned from app_main()
I (570) ESP_OTA_SERVER: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (570) ESP_OTA_SERVER: Zigbee stack initialized
I (570) ESP_OTA_SERVER: Start network formation
I (1090) ESP_OTA_SERVER: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
I (1090) ESP_OTA_SERVER: Formed network successfully (Extended PAN ID: 60:55:f9:ff:fe:f7:2e:16, PAN ID: 0x397c, Channel:13)
I (1570) ESP_OTA_SERVER: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
I (1570) ESP_OTA_SERVER: Network steering started
I (15950) ESP_OTA_SERVER: ZDO signal: NWK Device Associated (0x12), status: ESP_OK
I (16450) ESP_OTA_SERVER: ZDO signal: ZDO Device Update (0x30), status: ESP_OK
I (16490) ESP_OTA_SERVER: New device commissioned or rejoined (short: 0x7042)
I (16490) ESP_OTA_SERVER: OTA Server notify
I (16590) ESP_OTA_SERVER: OTA upgrade server query image
I (16590) ESP_OTA_SERVER: OTA client address: 0x7042
I (16590) ESP_OTA_SERVER: OTA version: 0x1010101, image type: 0x1011, manfacturer code: 1001,
I (16600) ESP_OTA_SERVER: OTA table index: 0x0
I (16690) ESP_OTA_SERVER: ZDO signal: ZDO Device Authorized (0x2f), status: ESP_OK
I (16750) ESP_OTA_SERVER: ZDO signal: NWK Permit Join (0x36), status: ESP_OK
I (16850) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [8/159616]
I (16850) ESP_OTA_SERVER: OTA client address: 0x7042
I (16850) ESP_OTA_SERVER: OTA version: 0x1010110, image type: 0x1011, server status: 0
I (17100) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [72/159616]
I (17320) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [136/159616]
I (17560) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [200/159616]
I (17780) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [264/159616]
I (18010) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [328/159616]
I (18240) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [392/159616]
I (18470) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [456/159616]
I (18700) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [520/159616]
I (18930) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [584/159616]
I (19160) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [648/159616]
I (19390) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [712/159616]
I (19620) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [776/159616]
I (19850) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [840/159616]
I (20100) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [904/159616]
I (20330) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [968/159616]
I (20560) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [1032/159616]
I (20790) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [1096/159616]
I (21020) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [1160/159616]
I (21250) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [1224/159616]
...
I (595990) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [158664/159616]
I (596220) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [158728/159616]
I (596450) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [158792/159616]
I (596680) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [158856/159616]
I (596910) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [158920/159616]
I (597150) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [158984/159616]
I (597380) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [159048/159616]
I (597610) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [159112/159616]
I (597840) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [159176/159616]
I (598070) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [159240/159616]
I (598300) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [159304/159616]
I (598530) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [159368/159616]
I (598810) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [159432/159616]
I (599030) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [159496/159616]
I (599260) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [159560/159616]
I (599540) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x7042: progress [159616/159616]
I (599610) ESP_OTA_SERVER: OTA client address: 0x7042
I (599610) ESP_OTA_SERVER: OTA version: 0x1010110, image type: 0x1011, server status: 2
I (599610) ESP_OTA_SERVER: OTA upgrade time: 0x1234a
```

## OTA Upgrade Functions

 *  After server starts, server send OTA image notify to client. Then client send the query image request to server.
 *  On receipt of the query image request, server initializes by loading the client that holds the three field values (manufacturer code, image type and new file version). If the client values matches with server values, server send response back to client. Otherwise, it shall discard the command and no further processing shall continue.
 *  Following diagram explains the OTA upgrade process in detail:
 ![Zigbee_ota](../../../docs/_static/zigbee-ota-upgrade-process.png)
 * There will be offset time of 5 seconds, calculated by the difference between upgrade time and current time and use it as upgrade delay.
 * ota_file.bin is upgrade bin file for client side to upgrade. Server gets the upgrade bin file (ota_file.bin) and transmit it through OTA process. After OTA finish, the client receive the upgrade bin file and trigger restart. For details see the [esp_ota_client](../ota_client/README.md).

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
