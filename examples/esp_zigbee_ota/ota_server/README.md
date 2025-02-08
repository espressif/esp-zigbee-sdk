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
I (616) main_task: Started on CPU0
I (626) main_task: Calling app_main()
I (646) phy: phy_version: 310,2, 8fa9cb4, Jun  5 2024, 14:19:10
I (646) phy: libbtbb version: a024da6, Jun  5 2024, 14:19:22
I (656) main_task: Returned from app_main()
I (746) ESP_OTA_SERVER: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (746) ESP_OTA_SERVER: Initialize Zigbee stack
I (746) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:4 
I (746) ESP_OTA_SERVER: Deferred driver initialization successful
I (766) ESP_OTA_SERVER: Device started up in factory-reset mode
I (766) ESP_OTA_SERVER: Start network formation
W (926) ESP_OTA_SERVER: Network(0x0841) closed, devices joining not allowed.
I (926) ESP_OTA_SERVER: Formed network successfully (Extended PAN ID: 48:31:b7:ff:fe:c0:2b:6b, PAN ID: 0x0841, Channel:13, Short Address: 0x0000)
I (1536) ESP_OTA_SERVER: Network(0x0841) is open for 180 seconds
I (1536) ESP_OTA_SERVER: Network steering started
I (5136) ESP_OTA_SERVER: ZDO signal: NWK Device Associated (0x12), status: ESP_OK
I (5146) ESP_OTA_SERVER: ZDO signal: ZDO Device Update (0x30), status: ESP_OK
I (5176) ESP_OTA_SERVER: New device commissioned or rejoined (short: 0x43a7)
I (5176) ESP_OTA_SERVER: Notify OTA upgrade
I (5286) ESP_OTA_SERVER: ZDO signal: ZDO Device Authorized (0x2f), status: ESP_OK
I (5316) ESP_OTA_SERVER: Network(0x0841) is open for 180 seconds
I (5846) ESP_OTA_SERVER: OTA upgrade server query image
I (5846) ESP_OTA_SERVER: OTA client address: 0x43a7
I (5846) ESP_OTA_SERVER: OTA version: 0x1010100, image type: 0x1011, manufacturer code: 1001, 
I (5856) ESP_OTA_SERVER: OTA table index: 0x0
I (6436) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [167/618486]
I (6436) ESP_OTA_SERVER: OTA client address: 0x43a7
I (6436) ESP_OTA_SERVER: OTA version: 0x1010101, image type: 0x1011, server status: 0
I (6746) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [390/618486]
I (6996) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [613/618486]
I (7246) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [836/618486]
I (7496) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [1059/618486]
I (7756) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [1282/618486]
I (8006) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [1505/618486]
I (8256) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [1728/618486]
I (8506) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [1951/618486]
I (8756) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [2174/618486]
I (9006) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [2397/618486]
I (9256) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [2620/618486]
I (9506) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [2843/618486]
I (9756) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [3066/618486]
I (10006) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [3289/618486]
I (10256) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [3512/618486]
I (10516) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [3735/618486]
I (10766) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [3958/618486]
I (11016) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [4181/618486]
I (11266) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [4404/618486]
I (11526) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [4627/618486]
...
I (699346) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [614086/618486]
I (699606) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [614309/618486]
I (699856) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [614532/618486]
I (700106) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [614755/618486]
I (700356) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [614978/618486]
I (700616) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [615201/618486]
I (700866) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [615424/618486]
I (701116) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [615647/618486]
I (701366) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [615870/618486]
I (701616) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [616093/618486]
I (701866) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [616316/618486]
I (702116) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [616539/618486]
I (702366) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [616762/618486]
I (702616) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [616985/618486]
I (702866) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [617208/618486]
I (703116) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [617431/618486]
I (703376) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [617654/618486]
I (703626) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [617877/618486]
I (703876) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [618100/618486]
I (704126) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [618323/618486]
I (704386) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0x43a7: progress [618486/618486]
I (704436) ESP_OTA_SERVER: OTA client address: 0x43a7
I (704436) ESP_OTA_SERVER: OTA version: 0x1010101, image type: 0x1011, server status: 2
I (704446) ESP_OTA_SERVER: OTA upgrade time: 0x1234a
```

Note: The example also supports the user pressing the `boot` button to broadcast the `IMAGE_NOTIFY` command to the network.

## OTA Upgrade Functions

 *  After server starts, server send OTA image notify to client. Then client send the query image request to server.
 *  On receipt of the query image request, server initializes by loading the client that holds the three field values (manufacturer code, image type and new file version). If the client values matches with server values, server send response back to client. Otherwise, it shall discard the command and no further processing shall continue.
 *  Following diagram explains the OTA upgrade process in detail:
 ![Zigbee_ota](../../../docs/_static/zigbee-ota-upgrade-process.png)
 * There will be offset time of 5 seconds, calculated by the difference between upgrade time and current time and use it as upgrade delay.
 * ota_file.bin is upgrade bin file for client side to upgrade. Server gets the upgrade bin file (ota_file.bin) and transmit it through OTA process. After OTA finish, the client receive the upgrade bin file and trigger restart. For details see the [esp_ota_client](../ota_client/README.md).

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
