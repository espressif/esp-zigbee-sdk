| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |
# Customized data producer and customer Example 

This example demonstrates how to use the custom cluster to customize a Zigbee device.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee coordinator (see [data_producer](../data_producer/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board, acting as a Zigbee Router with the `Customized Data Customer` (query data stream) function, will attempt to detect an available Zigbee network.
```
I (402) main_task: Calling app_main()
I (422) CUSTOMIZED_DATA_CONSUMER: Start ESP Zigbee Stack
I (422) ESP-ZIGBEE: SDK Version: v1.6.8-fcae32885b02-c1ffcb29*; esp32h2; 2026-04-08 12:07:37 UTC
I (422) esp zigbee sleep: light sleap disabled
I (442) phy: phy_version: 323,2, a8ef10c, Aug  1 2025, 17:46:10
I (442) phy: libbtbb version: 4515421, Aug  1 2025, 17:46:22
I (462) CUSTOMIZED_DATA_CONSUMER: Initialize Zigbee stack
I (462) CUSTOMIZED_DATA_CONSUMER: Deferred driver initialization successful
I (462) CUSTOMIZED_DATA_CONSUMER: Device started up in factory-reset mode
I (472) main_task: Returned from app_main()
I (1582) CUSTOMIZED_DATA_CONSUMER: Network(0x891a) is open for 180 seconds
I (1582) CUSTOMIZED_DATA_CONSUMER: Joined network successfully: PAN ID(0x891a, EXT: 0x4831b7fffec183f0), Channel(13), Short Address(0xe547)
```

- The Zigbee Router will attempt to find and bind a `Customized Data Producer` device from the network after it joins to the network.
```
I (1592) CUSTOMIZED_DATA_CONSUMER: Attempt to find customized data producer
I (1692) CUSTOMIZED_DATA_CONSUMER: Attempt to bind customized data producer (short address: 0x0000)
I (1702) CUSTOMIZED_DATA_CONSUMER: Bound customized data producer successfully
```

- Pressing the `BOOT` button first time on the board will read the name of `Customized Data Producer`.
```
I (127392) CUSTOMIZED_DATA_CONSUMER: Read the name of customized data producer with error(0x0000)
I (127472) CUSTOMIZED_DATA_CONSUMER: Received ZCL Read Attribute Response with status(0x00)
I (127472) CUSTOMIZED_DATA_CONSUMER: Attribute(0x0000), type(0x42)
I (127472) CUSTOMIZED_DATA_CONSUMER: Data producer name: DATA_PRODUCER
```
- Press the `Boot` again, the board will send the query data command to the bound `Customized Data Producer`
```
I (196362) CUSTOMIZED_DATA_CONSUMER: Request data stream from customized data producer with error(0x0000)
I (196512) CUSTOMIZED_DATA_CONSUMER: Received data from customized data producer with length(0x0100)
I (196512) CUSTOMIZED_DATA_CONSUMER: 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f
I (196522) CUSTOMIZED_DATA_CONSUMER: 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f
I (196522) CUSTOMIZED_DATA_CONSUMER: 20 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f
I (196532) CUSTOMIZED_DATA_CONSUMER: 30 31 32 33 34 35 36 37 38 39 3a 3b 3c 3d 3e 3f
I (196542) CUSTOMIZED_DATA_CONSUMER: 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f
I (196552) CUSTOMIZED_DATA_CONSUMER: 50 51 52 53 54 55 56 57 58 59 5a 5b 5c 5d 5e 5f
I (196552) CUSTOMIZED_DATA_CONSUMER: 60 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f
I (196562) CUSTOMIZED_DATA_CONSUMER: 70 71 72 73 74 75 76 77 78 79 7a 7b 7c 7d 7e 7f
I (196572) CUSTOMIZED_DATA_CONSUMER: 80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f
I (196582) CUSTOMIZED_DATA_CONSUMER: 90 91 92 93 94 95 96 97 98 99 9a 9b 9c 9d 9e 9f
I (196592) CUSTOMIZED_DATA_CONSUMER: a0 a1 a2 a3 a4 a5 a6 a7 a8 a9 aa ab ac ad ae af
I (196592) CUSTOMIZED_DATA_CONSUMER: b0 b1 b2 b3 b4 b5 b6 b7 b8 b9 ba bb bc bd be bf
I (196602) CUSTOMIZED_DATA_CONSUMER: c0 c1 c2 c3 c4 c5 c6 c7 c8 c9 ca cb cc cd ce cf
I (196612) CUSTOMIZED_DATA_CONSUMER: d0 d1 d2 d3 d4 d5 d6 d7 d8 d9 da db dc dd de df
I (196622) CUSTOMIZED_DATA_CONSUMER: e0 e1 e2 e3 e4 e5 e6 e7 e8 e9 ea eb ec ed ee ef
I (196622) CUSTOMIZED_DATA_CONSUMER: f0 f1 f2 f3 f4 f5 f6 f7 f8 f9 fa fb fc fd fe ff
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
