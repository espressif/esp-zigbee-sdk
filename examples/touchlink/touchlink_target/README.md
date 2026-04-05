| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |
# Touchlink Light Example 

This example demonstrates how the Touchlink target pairs with the Touchlink initiator.

## Hardware Required
* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* Choose another ESP32-H2 as Touchlink target (Zigbee End Device) (see [touchlink_initiator](../touchlink_initiator) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TOUCHLINK_TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board, acting as the `Touchlink target`, will enter commissioning mode and wait for a `Touchlink initiator` device to initiate a scan.
```
I (425) main_task: Calling app_main()
I (445) TOUCHLINK_TARGET: Start ESP Zigbee Stack
I (445) esp zigbee sleep: light sleap disabled
I (455) phy: phy_version: 323,2, a8ef10c, Aug  1 2025, 17:46:10
I (455) phy: libbtbb version: 4515421, Aug  1 2025, 17:46:22
I (475) main_task: Returned from app_main()
I (485) TOUCHLINK_TARGET: Initialize Zigbee stack
W (485) rmt: channel resolution loss, real=10666666
I (485) TOUCHLINK_TARGET: Deferred driver initialization successful                                                                      
I (495) TOUCHLINK_TARGET: Device started up in factory-reset mode                                                                                                   
```

- If a nearby `Touchlink initiator` device is triggered to scan the Touchlink target, if the received RSSI value exceeds the RSSI threshold (default: -64 dBm) set by `ezb_touchlink_set_rssi_threshold()`, the board will initiate network formation with the `Touchlink initiator` and complete the commissioning process.
```                                                           
I (25325) TOUCHLINK_TARGET: Commissioning successfully: PAN ID(0xe865, EXT: 0x4831b7fffec183f0), Channel(11), Short Address(0x6a08)      
I (25345) TOUCHLINK_TARGET: Touchlink target finished (status: ESP_OK)                                                       
I (27355) TOUCHLINK_TARGET: New device commissioned or rejoined (short: 0x1a12)
```

- If the commissioning is successful, the board will act as an `Home Automation On/Off Light` that can be controlled by the paired `Touchlink initiator` device.
```
I (30025) TOUCHLINK_TARGET: ZCL SetAttributeValue message for endpoint(1) cluster(0x0006) server with status(0x00)
I (30025) TOUCHLINK_TARGET: Set On/Off: 1
I (31415) TOUCHLINK_TARGET: ZCL SetAttributeValue message for endpoint(1) cluster(0x0006) server with status(0x00)
I (31415) TOUCHLINK_TARGET: Set On/Off: 0
I (31625) TOUCHLINK_TARGET: ZCL SetAttributeValue message for endpoint(1) cluster(0x0006) server with status(0x00)
I (31625) TOUCHLINK_TARGET: Set On/Off: 1
I (32425) TOUCHLINK_TARGET: ZCL SetAttributeValue message for endpoint(1) cluster(0x0006) server with status(0x00)
I (32425) TOUCHLINK_TARGET: Set On/Off: 0

```

- The board will remain in the commissioning state for 60 seconds set by `ezb_touchlink_set_target_timeout()` , waiting for the Touchlink initiator to
  initiate commissioning.

- If the log `Touchlink target commissioning finished` appears, it indicates that the target has exited the commissioning state and can no longer pair with
  other Touchlink initiators.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
