| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |

# Light Bulb Example 

This example demonstrates how to use the custom cluster to customize a Zigbee device.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee Router or End Device (see [data_customer](../data_customer/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board, acting as a Zigbee Coordinator with the `Customized Data Producer` (generate data stream) function, will form an open network within 180 seconds.
```
I (399) main_task: Calling app_main()
I (419) CUSTOMIZED_DATA_PRODUCER: Start ESP Zigbee Stack
I (419) ESP-ZIGBEE: SDK Version: v1.6.8-fcae32885b02-c1ffcb29; esp32h2; 2026-04-08 11:34:58 UTC
I (419) esp zigbee sleep: light sleap disabled
I (439) phy: phy_version: 323,2, a8ef10c, Aug  1 2025, 17:46:10
I (439) phy: libbtbb version: 4515421, Aug  1 2025, 17:46:22
I (459) CUSTOMIZED_DATA_PRODUCER: Initialize Zigbee stack
I (459) CUSTOMIZED_DATA_PRODUCER: Device started up in factory-reset mode
I (459) main_task: Returned from app_main()
I (789) CUSTOMIZED_DATA_PRODUCER: Formed network successfully: PAN ID(0x891a, EXT: 0x4831b7fffec183f0), Channel(13), Short Address(0x0000)
I (1039) CUSTOMIZED_DATA_PRODUCER: Network(0x891a) is open for 180 seconds
```

- If the board receives a ZCL `CustomizedQueryData` command from the `Customized Data Consumer`, it will respond with a data stream containing the requested information.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
