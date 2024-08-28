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
I (623) app_start: Starting scheduler on CPU0
I (628) main_task: Started on CPU0                                    
I (632) main_task: Calling app_main()
I (655) phy: phy_version: 230,2, 9aae6ea, Jan 15 2024, 11:17:12
I (656) phy: libbtbb version: 944f18e, Jan 15 2024, 11:17:25
I (660) main_task: Returned from app_main()
I (730) ESP_OTA_SERVER: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL                                                                
I (731) ESP_OTA_SERVER: Initialize Zigbee stack
I (737) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:4                                                 
I (736) ESP_OTA_SERVER: Deferred driver initialization successful
I (749) ESP_OTA_SERVER: Device started up in  factory-reset mode
I (755) ESP_OTA_SERVER: Start network formation
W (909) ESP_OTA_SERVER: Network(0xa1ea) closed, devices joining not allowed.                                                                 
I (912) ESP_OTA_SERVER: Formed network successfully (Extended PAN ID: 74:4d:bd:ff:fe:63:78:8a, PAN ID: 0xa1ea, Channel:13, Short Address: 0x0000)
I (1389) ESP_OTA_SERVER: Network(0xa1ea) is open for 180 seconds
I (1392) ESP_OTA_SERVER: Network steering started
I (5769) ESP_OTA_SERVER: ZDO signal: NWK Device Associated (0x12), status: ESP_OK                                                            
I (5773) ESP_OTA_SERVER: ZDO signal: ZDO Device Update (0x30), status: ESP_OK                                                                
I (5805) ESP_OTA_SERVER: New device commissioned or rejoined (short: 0xfc9a)                                                                 
I (5806) ESP_OTA_SERVER: Notify OTA upgrade
I (5898) ESP_OTA_SERVER: ZDO signal: ZDO Device Authorized (0x2f), status: ESP_OK                                                            
I (5928) ESP_OTA_SERVER: Network(0xa1ea) is open for 180 seconds
I (6301) ESP_OTA_SERVER: OTA upgrade server query image
I (6301) ESP_OTA_SERVER: OTA client address: 0xfc9a
I (6302) ESP_OTA_SERVER: OTA version: 0x1010101, image type: 0x1011, manufacturer code: 1001,                                                
I (6311) ESP_OTA_SERVER: OTA table index: 0x0
I (6816) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [167/618480]                                              
I (6817) ESP_OTA_SERVER: OTA client address: 0xfc9a
I (6821) ESP_OTA_SERVER: OTA version: 0x1010110, image type: 0x1011, server status: 0                                                        
I (7102) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [390/618480]                                              
I (7347) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [613/618480]                                              
I (7592) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [836/618480]                                              
I (7837) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [1059/618480]                                             
I (8086) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [1282/618480]                                             
I (8331) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [1505/618480]                                             
I (8576) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [1728/618480]                                             
I (8821) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [1951/618480]                                             
I (9066) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [2174/618480]                                             
I (9312) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [2397/618480]                                             
I (9557) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [2620/618480]                                             
I (9802) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [2843/618480]                                             
I (10047) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [3066/618480]                                            
I (10295) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [3289/618480]                                            
I (10541) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [3512/618480]                                            
I (10786) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [3735/618480]                                            
I (11031) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [3958/618480]                                            
I (11280) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [4181/618480]                                            
I (11525) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [4404/618480]                                            
I (11770) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [4627/618480]
...
I (685405) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [614086/618480]
I (685650) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [614309/618480]
I (685905) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [614532/618480]
I (686151) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [614755/618480]
I (686400) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [614978/618480]
I (686648) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [615201/618480]
I (686893) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [615424/618480]
I (687143) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [615647/618480]
I (687388) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [615870/618480]
I (687633) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [616093/618480]
I (687879) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [616316/618480]
I (688124) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [616539/618480]
I (688374) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [616762/618480]
I (688625) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [616985/618480]
I (688876) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [617208/618480]
I (689121) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [617431/618480]
I (689366) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [617654/618480]
I (689611) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [617877/618480]
I (689856) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [618100/618480]
I (690104) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [618323/618480]
I (690349) ESP_OTA_SERVER: -- OTA Server transmits data from 0x0 to 0xfc9a: progress [618480/618480]
I (690404) ESP_OTA_SERVER: OTA client address: 0xfc9a
I (690405) ESP_OTA_SERVER: OTA version: 0x1010110, image type: 0x1011, server status: 2
I (690408) ESP_OTA_SERVER: OTA upgrade time: 0x1234a

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
