| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |

# Thermostat Example

This example demonstrates how to configure a Home Automation thermostat on a Zigbee Coordinator.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee end-device (see [temperature_sensor](../temperature_sensor) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board, acting as a Zigbee Coordinator with the `Home Automation Thermostat` function, will form an open network within 180 seconds.
```
I (419) main_task: Calling app_main()
I (439) THERMOSTAT: Start ESP Zigbee Stack
I (439) esp zigbee sleep: light sleap disabled
I (449) phy: phy_version: 323,2, a8ef10c, Aug  1 2025, 17:46:10
I (449) phy: libbtbb version: 4515421, Aug  1 2025, 17:46:22
I (469) main_task: Returned from app_main()
I (479) THERMOSTAT: Initialize Zigbee stack
I (479) THERMOSTAT: Deferred driver initialization successful
I (479) THERMOSTAT: Device started up in factory-reset mode
I (809) THERMOSTAT: Formed network successfully: PAN ID(0x3e40, EXT: 0x4831b7fffec183f0), Channel(13), Short Address(0x0000)
I (1249) THERMOSTAT: Network steering completed

```

- If a Zigbee device with the `Home Automation Temperature Sensor` function joins the network, the board read its manufacturer code and model then add it to
  the binding table.
```
I (11889) THERMOSTAT: Attempt to find HA temperature sensor device on address(0xd9bc)
I (12279) THERMOSTAT: Attempt to read manuf_code and model_id from device (0xd9bc, 0x0a)
I (12369) THERMOSTAT: ZCL Read Attribute Response message for endpoint(1) cluster(0x0000) client with status(0x00)
I (12369) THERMOSTAT: Model identifier: esp32h2
I (12369) THERMOSTAT: Manufacturer name: ESPRESSIF
I (12379) THERMOSTAT: Attempt to bind temperature sensor device (0xd9bc, 0x0a) to local
I (12389) THERMOSTAT: Attempt to subscribe temperature sensor device (0xd9bc, 0x0a) from local
I (12429) THERMOSTAT: Bound HA temperature sensor device (0x0000, 0x0a) to local successfully
```

- By clicking the `BOOT` button on this board, it will read the temperature value, temperature measurement range, and temperature tolerance from the
  remote board. Additionally, it will configure the remote temperature sensor to report the measured temperature value every 10 seconds or whenever
  there is a 2-degree change.
```
I (147449) THERMOSTAT: ZCL Report Attribute message for endpoint(1) cluster(0x0402) client with status(0x00)
I (147449) THERMOSTAT: Temperature sensor measured value: 25.00 degrees Celsius                           
I (157529) THERMOSTAT: ZCL Report Attribute message for endpoint(1) cluster(0x0402) client with status(0x00)
I (157529) THERMOSTAT: Temperature sensor measured value: 25.00 degrees Celsius                           
I (167609) THERMOSTAT: ZCL Report Attribute message for endpoint(1) cluster(0x0402) client with status(0x00)
I (167609) THERMOSTAT: Temperature sensor measured value: 25.00 degrees Celsius  
I (168579) THERMOSTAT: Read Attributes of Temperature Measurement
I (168639) THERMOSTAT: ZCL Read Attribute Response message for endpoint(1) cluster(0x0402) client with status(0x00)
W (168639) THERMOSTAT: Read Temperature Measurement attribute ID: 0x0003 with status: 0x86
I (168649) THERMOSTAT: Max measured value: -10.00 degrees Celsius
I (168659) THERMOSTAT: Min measured value: 80.00 degrees Celsius
I (168669) THERMOSTAT: Measured value: 25.00 degrees Celsius

```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
