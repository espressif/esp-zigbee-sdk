| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# OTA Upgrade Example 

This example demonstrates how to perform an OTA process from Zigbee OTA upgrade server side.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee end device (see [ota_client](../ota_client/) example)

## Configure the project

Before project configuration and build, set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Function

- When the program starts, the board, acting as the Zigbee Coordinator with the `OTA Upgrade Server` function and forms an open Zigbee network within 180 seconds.
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
```

- If a device joins the network created by the board, an `Image Notify` request will be broadcasted to the network.
```
I (5136) ESP_OTA_SERVER: ZDO signal: NWK Device Associated (0x12), status: ESP_OK
I (5146) ESP_OTA_SERVER: ZDO signal: ZDO Device Update (0x30), status: ESP_OK
I (5176) ESP_OTA_SERVER: New device commissioned or rejoined (short: 0x43a7)
I (5176) ESP_OTA_SERVER: Notify OTA upgrade
I (5286) ESP_OTA_SERVER: ZDO signal: ZDO Device Authorized (0x2f), status: ESP_OK
```

- If a `Query Next Image` request is received by the board, the OTA upgrade process will begin, provided that the OTA version matches.
```
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
```

- After the OTA upgrade is completed, the board will finalize the OTA process.
```
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

- This board can initiate an `Image Notify` request again when the `BOOT` button on the board is pressed.

- The [OTA file](main/ota_file.bin) in this example is built using the [image_builder_tool](../../../tools/image_builder_tool/image_builder_tool.py), which generates a standard OTA image format.


## OTA Upgrade Message Diagram 

 ![Zigbee_ota](../../../docs/_static/zigbee-ota-upgrade-process.png)

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
