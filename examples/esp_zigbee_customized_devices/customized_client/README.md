| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Light Switch Example 

This example demonstrates how to register a customized ZCL On/Off switch device with the Zigbee stack and implement the ZCL attribute reporting mechanism.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as Zigbee coordinator (see [customized_server](../customized_server/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board will attempt to detect an available Zigbee network every **1 second** until one is found.
```
I (416) main_task: Returned from app_main()
I (426) ESP_HA_ON_OFF_SWITCH: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (1406) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:4 
I (1406) ESP_HA_ON_OFF_SWITCH: Deferred driver initialization successful
I (1406) ESP_HA_ON_OFF_SWITCH: Joined network successfully (Extended PAN ID: 74:4d:bd:ff:fe:63:de:c5, PAN ID: 0x46c5, Channel:13, Short Address: 0x5cf2)
```

- If the board successfully joins a Zigbee network, it acts as a Zigbee end device, registers a `Customized` endpoint with the `On/Off Switch` function,
  and then attempts to match an `On/Off Light` device on the network.
```
I (1446) ESP_HA_ON_OFF_SWITCH: Match desc response: status(0), address(0x0), endpoint(10)
```

- If the matching is successful, the board will send ZDO `Active Ep`, `Simple Desc`, `IEEE Addr`, and `Read Attr` requests to collect basic information
  about the matched remote device.
```
I (1446) ESP_HA_ON_OFF_SWITCH: Match desc response: status(0), address(0x0), endpoint(10)
I (1486) ESP_HA_ON_OFF_SWITCH: Active endpoint response: status(0) and endpoint count(2)
I (1486) ESP_HA_ON_OFF_SWITCH: Endpoint ID List: 10
I (1486) ESP_HA_ON_OFF_SWITCH: Endpoint ID List: 242
I (1506) ESP_HA_ON_OFF_SWITCH: Simple desc response: status(0), device_id(256), app_version(0), profile_id(0x104), endpoint_ID(10)
I (1506) ESP_HA_ON_OFF_SWITCH: Cluster ID list: 0x0
I (1516) ESP_HA_ON_OFF_SWITCH: Cluster ID list: 0x3
I (1516) ESP_HA_ON_OFF_SWITCH: Cluster ID list: 0x4
I (1526) ESP_HA_ON_OFF_SWITCH: Cluster ID list: 0x5
I (1526) ESP_HA_ON_OFF_SWITCH: Cluster ID list: 0x6
I (1546) ESP_HA_ON_OFF_SWITCH: IEEE address: 74:4d:bd:ff:fe:63:de:c5
I (1556) ESP_HA_ON_OFF_SWITCH: Read attribute response: status(0), cluster(0x6), attribute(0x0), type(0x10), value(0)
```

- After this, the board will send `Bind` and `Config Report` requests to the matched `On/Off Light` device, enabling the light to report its `On/Off`
  attribute whenever it changes or when the maximum reporting interval is reached.
```
I (1596) ESP_HA_ON_OFF_SWITCH: Bind response from address(0x0), endpoint(1) with status(0)
I (1626) ESP_HA_ON_OFF_SWITCH: Configure report response: status(0), cluster(0x6), attribute(0xffff)
I (1636) ESP_HA_ON_OFF_SWITCH: Received report from address(0x0) src endpoint(10) to dst endpoint(1) cluster(0x6)
I (1636) ESP_HA_ON_OFF_SWITCH: Received report information: attribute(0x0), type(0x10), value(0)
```

- Pressing the `BOOT` button on the board will send an `On/Off toggle` command to control the remote `On/Off Light` device.
```
I (14686) ESP_HA_ON_OFF_SWITCH: Send 'on_off toggle' command to address(0x0) endpoint(10)
W (14716) ESP_HA_ON_OFF_SWITCH: Receive Zigbee action(0x1005) callback
I (14716) ESP_HA_ON_OFF_SWITCH: Received report from address(0x0) src endpoint(10) to dst endpoint(1) cluster(0x6)
I (14716) ESP_HA_ON_OFF_SWITCH: Received report information: attribute(0x0), type(0x10), value(1)

I (15926) ESP_HA_ON_OFF_SWITCH: Send 'on_off toggle' command to address(0x0) endpoint(10)
W (15956) ESP_HA_ON_OFF_SWITCH: Receive Zigbee action(0x1005) callback
I (15956) ESP_HA_ON_OFF_SWITCH: Received report from address(0x0) src endpoint(10) to dst endpoint(1) cluster(0x6)
I (15956) ESP_HA_ON_OFF_SWITCH: Received report information: attribute(0x0), type(0x10), value(0)

I (17696) ESP_HA_ON_OFF_SWITCH: Send 'on_off toggle' command to address(0x0) endpoint(10)
W (17726) ESP_HA_ON_OFF_SWITCH: Receive Zigbee action(0x1005) callback
I (17726) ESP_HA_ON_OFF_SWITCH: Received report from address(0x0) src endpoint(10) to dst endpoint(1) cluster(0x6)
I (17726) ESP_HA_ON_OFF_SWITCH: Received report information: attribute(0x0), type(0x10), value(1)

I (20846) ESP_HA_ON_OFF_SWITCH: Send 'on_off toggle' command to address(0x0) endpoint(10)
W (20876) ESP_HA_ON_OFF_SWITCH: Receive Zigbee action(0x1005) callback
I (20876) ESP_HA_ON_OFF_SWITCH: Received report from address(0x0) src endpoint(10) to dst endpoint(1) cluster(0x6)
I (20876) ESP_HA_ON_OFF_SWITCH: Received report information: attribute(0x0), type(0x10), value(0)
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
