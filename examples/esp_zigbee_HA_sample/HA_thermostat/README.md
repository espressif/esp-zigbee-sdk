| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Thermostat Example

This test code shows how to configure Zigbee Coordinator and use it as an HA thermostat.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee Coordinator (loaded with HA_thermostat)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee end-device (see [HA_temperature_sensor](../HA_temperature_sensor/))

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

As you run the example, you will see the following log:

```
I (497) main_task: Returned from app_main()
I (627) ESP_ZB_THERMOSTAT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (627) ESP_ZB_THERMOSTAT: Initialize Zigbee stack
I (637) ESP_ZB_THERMOSTAT: Device started up in  factory-reset mode
I (637) ESP_ZB_THERMOSTAT: Start network formation
W (797) ESP_ZB_THERMOSTAT: Network(0xbcc7) closed, devices joining not allowed.
I (797) ESP_ZB_THERMOSTAT: Formed network successfully (Extended PAN ID: 74:4d:bd:ff:fe:60:2d:57, PAN ID: 0xbcc7, Channel:13, Short Address: 0x0000)
I (1397) ESP_ZB_THERMOSTAT: Network(0xbcc7) is open for 180 seconds
I (1397) ESP_ZB_THERMOSTAT: Network steering started
I (4637) ESP_ZB_THERMOSTAT: ZDO signal: NWK Device Associated (0x12), status: ESP_OK
I (5157) ESP_ZB_THERMOSTAT: ZDO signal: ZDO Device Update (0x30), status: ESP_OK
I (5187) ESP_ZB_THERMOSTAT: New device commissioned or rejoined (short: 0xe6d0)
I (5257) ESP_ZB_THERMOSTAT: Found temperature sensor
I (5257) ESP_ZB_THERMOSTAT: Request temperature sensor to bind us
I (5267) ESP_ZB_THERMOSTAT: Bind temperature sensor
I (5277) ESP_ZB_THERMOSTAT: Successfully bind the temperature sensor from address(0xe6d0) on endpoint(10)
I (5397) ESP_ZB_THERMOSTAT: ZDO signal: NLME Status Indication (0x32), status: ESP_OK
I (5417) ESP_ZB_THERMOSTAT: The temperature sensor from address(0xe6d0) on endpoint(10) successfully binds us
I (7207) ESP_ZB_THERMOSTAT: Received report from address(0xe6d0) src endpoint(10) to dst endpoint(1) cluster(0x402)
I (7207) ESP_ZB_THERMOSTAT: Measured Value is 24.00 degrees Celsius
I (8367) ESP_ZB_THERMOSTAT: Read attribute response: from address(0xe6d0) src endpoint(10) to dst endpoint(1) cluster(0x0)
I (8367) ESP_ZB_THERMOSTAT: Read attribute response: status(0), cluster(0x0), attribute(0x4), type(0x42), value(11)
I (8387) ESP_ZB_THERMOSTAT: Peer Manufacturer is "ESPRESSIF"
I (8387) ESP_ZB_THERMOSTAT: Read attribute response: status(0), cluster(0x0), attribute(0x5), type(0x42), value(9)
I (8397) ESP_ZB_THERMOSTAT: Peer Model is "esp32h2"
I (10317) ESP_ZB_THERMOSTAT: ZDO signal: ZDO Device Authorized (0x2f), status: ESP_OK
I (10347) ESP_ZB_THERMOSTAT: Network(0xbcc7) is open for 180 seconds
I (11207) ESP_ZB_THERMOSTAT: Received report from address(0xe6d0) src endpoint(10) to dst endpoint(1) cluster(0x402)
I (11207) ESP_ZB_THERMOSTAT: Measured Value is 25.00 degrees Celsius
I (12267) ESP_ZB_THERMOSTAT: Received report from address(0xe6d0) src endpoint(10) to dst endpoint(1) cluster(0x402)
I (12267) ESP_ZB_THERMOSTAT: Measured Value is 24.00 degrees Celsius
I (16207) ESP_ZB_THERMOSTAT: Received report from address(0xe6d0) src endpoint(10) to dst endpoint(1) cluster(0x402)
I (16207) ESP_ZB_THERMOSTAT: Measured Value is 25.00 degrees Celsius
I (19417) ESP_ZB_THERMOSTAT: Received report from address(0xe6d0) src endpoint(10) to dst endpoint(1) cluster(0x402)
I (19417) ESP_ZB_THERMOSTAT: Measured Value is 25.00 degrees Celsius
I (20467) ESP_ZB_THERMOSTAT: Received report from address(0xe6d0) src endpoint(10) to dst endpoint(1) cluster(0x402)
I (20467) ESP_ZB_THERMOSTAT: Measured Value is 25.00 degrees Celsius
I (22947) ESP_ZB_THERMOSTAT: Send 'configure reporting' command
I (22947) ESP_ZB_THERMOSTAT: Send 'read attributes' command
I (22997) ESP_ZB_THERMOSTAT: Configure report response: status(0), cluster(0x402), direction(0xe8), attribute(0xffff)
I (22997) ESP_ZB_THERMOSTAT: Received report from address(0xe6d0) src endpoint(10) to dst endpoint(1) cluster(0x402)
I (23007) ESP_ZB_THERMOSTAT: Measured Value is 25.00 degrees Celsius
I (23027) ESP_ZB_THERMOSTAT: Read attribute response: from address(0xe6d0) src endpoint(10) to dst endpoint(1) cluster(0x402)
I (23027) ESP_ZB_THERMOSTAT: Read attribute response: status(0), cluster(0x402), attribute(0x0), type(0x29), value(196)
I (23037) ESP_ZB_THERMOSTAT: Measured Value is 25.00 degrees Celsius
I (23047) ESP_ZB_THERMOSTAT: Read attribute response: status(0), cluster(0x402), attribute(0x1), type(0x29), value(24)
I (23057) ESP_ZB_THERMOSTAT: Min Measured Value is -10.00 degrees Celsius
I (23067) ESP_ZB_THERMOSTAT: Read attribute response: status(0), cluster(0x402), attribute(0x2), type(0x29), value(64)
I (23077) ESP_ZB_THERMOSTAT: Max Measured Value is 80.00 degrees Celsius
I (23087) ESP_ZB_THERMOSTAT: Read attribute response: status(134), cluster(0x402), attribute(0x3), type(0xc7), value(169)
I (33077) ESP_ZB_THERMOSTAT: Received report from address(0xe6d0) src endpoint(10) to dst endpoint(1) cluster(0x402)
I (33077) ESP_ZB_THERMOSTAT: Measured Value is 25.00 degrees Celsius
```

## Thermostat Functions

Note:
 * This board means the board (e.g. ESP32-H2) loaded with `HA_thermostat` example.
 * The remote board means the board (e.g. ESP32-H2) loaded with `HA_temperature_sensor` example.

Functions:
 * By clicking the switch button (BOOT) on this board, this board will read temperature value, temperature measurement range and temperature tolerance from the remote board. Also, this board will configure the remote board to report the measured temperature value every 10 seconds or every 2 degree changes.


## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
