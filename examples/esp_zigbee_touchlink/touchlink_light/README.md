| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Touchlink Light Example 

This example demonstrates how the Touchlink target pairs with the Touchlink initiator.

## Hardware Required
* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* Choose another ESP32-H2 as Touchlink target(Zigbee Router) (see [touchlink_light](../touchlink_light) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board, acting as the `Touchlink target`, will enter commissioning mode and wait for a `Touchlink initiator` device to initiate a scan.
```
I (413) main_task: Started on CPU0
I (423) main_task: Calling app_main()
I (443) phy: phy_version: 321,2, 632dc08, Feb 13 2025, 16:29:11
I (443) phy: libbtbb version: 509a2a6, Feb 13 2025, 16:29:25
I (453) main_task: Returned from app_main()
I (463) ESP_TL_ON_OFF_LIGHT: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (463) ESP_TL_ON_OFF_LIGHT: Initialize Zigbee stack
W (473) rmt: channel resolution loss, real=10666666
I (473) ESP_TL_ON_OFF_LIGHT: Deferred driver initialization successful
I (483) ESP_TL_ON_OFF_LIGHT: Device started up in factory-reset mode
I (493) ESP_TL_ON_OFF_LIGHT: Touchlink target is ready, awaiting commissioning
```

- If a nearby `Touchlink initiator` device is triggered to scan the Touchlink target, the board will print the initiator's IEEE address and RSSI.
```
Received Touchlink scan request from 74:4d:bd:ff:fe:63:c2:e4, RSSI: -2 dBm
Received Touchlink scan request from 74:4d:bd:ff:fe:63:c2:e4, RSSI: -2 dBm
Received Touchlink scan request from 74:4d:bd:ff:fe:63:c2:e4, RSSI: -2 dBm
Received Touchlink scan request from 74:4d:bd:ff:fe:63:c2:e4, RSSI: -2 dBm
Received Touchlink scan request from 74:4d:bd:ff:fe:63:c2:e4, RSSI: -2 dBm
```

- If the received RSSI value exceeds the RSSI threshold (default: -64 dBm) set by `esp_zb_zdo_touchlink_set_rssi_threshold()`, the board will initiate network
  formation with the `Touchlink initiator` and complete the commissioning process.
```
W (5663) ESP_TL_ON_OFF_LIGHT: Network(0x5182) closed, devices joining not allowed.
I (5663) ESP_TL_ON_OFF_LIGHT: Commissioning successfully, network information (Extended PAN ID: 74:4d:bd:ff:fe:63:78:73, PAN ID: 0x5182, Channel:11, Short Address: 0xbef5)
I (5673) ESP_TL_ON_OFF_LIGHT: Touchlink target commissioning finished
I (7323) ESP_TL_ON_OFF_LIGHT: ZDO signal: ZDO Device Update (0x30), status: ESP_OK
I (7333) ESP_TL_ON_OFF_LIGHT: New device commissioned or rejoined (short: 0x396a)
```

- If the commissioning is successful, the board will act as an `Home Automation On/Off Light` that can be controlled by the paired `Touchlink initiator` device.
```
I (342253) ESP_TL_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (342253) ESP_TL_ON_OFF_LIGHT: Light sets to On
I (342973) ESP_TL_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (342983) ESP_TL_ON_OFF_LIGHT: Light sets to Off
I (345183) ESP_TL_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (345183) ESP_TL_ON_OFF_LIGHT: Light sets to On
I (345573) ESP_TL_ON_OFF_LIGHT: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (345573) ESP_TL_ON_OFF_LIGHT: Light sets to Off
```

- The board will remain in the commissioning state for 60 seconds set by `esp_zb_zdo_touchlink_target_set_timeout()` , waiting for the Touchlink initiator to
  initiate commissioning.

- If the log `Touchlink target commissioning finished` appears, it indicates that the target has exited the commissioning state and can no longer pair with
  other Touchlink initiators.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
