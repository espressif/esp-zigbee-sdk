| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 | ESP32-H21 | ESP32-H4 | ESP32-S31 |
| ----------------- | -------- | -------- | -------- | --------- | -------- | --------- |

# Zigbee NVRAM Migration Example

This example demonstrates how to migrate the legacy NVRAM data to v2.x NVS based datasets.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.

## Configure the project

Before project configuration and build, make sure to set the correct chip target using
`idf.py set-target TARGET` command. Enable `CONFIG_ZB_EXAMPLE_RUNTIME_NVS_PARTITION`
in `sdkconfig.defaults` to show the solution if no NVS partition was on the old device.

## Erase the NVRAM

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep
the previous examples or other projects stored info using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output
by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

The example is delivered with a legacy NVRAM data - `zb_storage.legacy.bin` which is generated
by v1.x based application. It will be erased to `zb_storage` partition by default and the example
would migrate the data from it to a NVS partition. If `CONFIG_ZB_EXAMPLE_RUNTIME_NVS_PARTITION` is
enabled, the example will find unused space from the flash and register a "runtime" NVS partition
with label `zb_storage_v2` as the migration destination.

After the program starts, it will migrate the legacy NVRAM data automatically.

```
I (406) APP_MAIN: Found unallocated space at 0x000f5400, size 0x0010ac00
I (406) APP_MAIN: Use <zb_storage_v2> partition (0x000f6000)
I (416) APP_MAIN: NVS partition initialized, label: zb_storage_v2, address: 0x000f6000, size: 0x00004000
I (436) APP_MAIN: App marker not found, perform migration
I (436) APP_MAIN: Start migration: <zb_storage> -> <zb_storage_v2>
```

Then starts the Zigbee stack as that stored in the legacy NVRAM data. The network parameters, report
configurations, group table and binding table restored correctly.

```
I (476) APP_MAIN: Start ESP Zigbee Stack
I (536) APP_MAIN: Initialize Zigbee stack
I (546) APP_MAIN: Device started up in non factory-reset mode
I (546) APP_MAIN: Device reboot successfully: PAN ID(0x1234, EXT: 0xaaaaaaaaaaaaaaaa), Channel(13), Short Address(0x0000)
I (1126) APP_MAIN: Network(0x1234) is open for 180 seconds
I (1126) APP_MAIN: Network steering completed
I (4146) APP_MAIN: Zigbee APP Signal: ZDO Device Update(type: 0x07)
I (4146) APP_MAIN: New device commissioned or rejoined (short: 0x90b0)
I (5056) CUSTOM_THERMOSTAT: ZCL Report Attribute message for endpoint(1) cluster(0x0402) client with status(0x00)
I (5056) CUSTOM_THERMOSTAT: Temperature sensor measured value: 29.50 degrees Celsius
I (10556) CUSTOM_THERMOSTAT: ZCL Report Attribute message for endpoint(1) cluster(0x0402) client with status(0x00)
I (10556) CUSTOM_THERMOSTAT: Temperature sensor measured value: -327.68 degrees Celsius
I (21216) CUSTOM_THERMOSTAT: ZCL Report Attribute message for endpoint(1) cluster(0x0402) client with status(0x00)
I (21216) CUSTOM_THERMOSTAT: Temperature sensor measured value: -327.68 degrees Celsius
I (32016) CUSTOM_THERMOSTAT: ZCL Report Attribute message for endpoint(1) cluster(0x0402) client with status(0x00)
I (32016) CUSTOM_THERMOSTAT: Temperature sensor measured value: -327.68 degrees Celsius
I (39746) CUSTOM_THERMOSTAT: ZCL Report Attribute message for endpoint(1) cluster(0x0402) client with status(0x00)
I (39746) CUSTOM_THERMOSTAT: Temperature sensor measured value: 29.50 degrees Celsius
I (42806) CUSTOM_THERMOSTAT: ZCL Report Attribute message for endpoint(1) cluster(0x0402) client with status(0x00)
I (42806) CUSTOM_THERMOSTAT: Temperature sensor measured value: -327.68 degrees Celsius
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
