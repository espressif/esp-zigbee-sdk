| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |

# Temperature Sensor Example

This example demonstrates how to configure a Home Automation temperature sensor on a Zigbee End Device.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee Coordinator (see [thermostat](../thermostat/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board, acting as a Zigbee End Device with the `Home Automation Temperature Sensor` function, will attempt to detect an available Zigbee network.

```
I (416) main_task: Calling app_main()                                                                                                        
I (426) TEMPERATURE_SENSOR: Start ESP Zigbee Stack                                                                             
I (436) esp zigbee sleep: light sleap disabled                                                                                               
I (446) phy: phy_version: 323,2, a8ef10c, Aug  1 2025, 17:46:10                                                                              
I (446) phy: libbtbb version: 4515421, Aug  1 2025, 17:46:22                                                                                 
I (466) TEMPERATURE_SENSOR: Initialize Zigbee stack                                                                            
I (466) temperature_sensor: Range [-10°C ~ 80°C], error < 1°C                                                                                
I (476) TEMPERATURE_SENSOR: Deferred driver initialization successful                                                          
I (476) TEMPERATURE_SENSOR: Device started up in factory-reset mode                                                            
I (486) main_task: Returned from app_main()                                                                                                  
I (1986) TEMPERATURE_SENSOR: Received ZCL Default Response: status(0x00)                                                       
I (2086) TEMPERATURE_SENSOR: Joined network successfully: PAN ID(0x3e40, EXT: 0x4831b7fffec183f0), Channel(13), Short Address(0xd9bc)
```

- The board updates the temperature attribute of the `Temperature Measurement` cluster based on the actual temperature sensor value of the chip.

- By clicking the `BOOT` button on this board, the board will actively report the current measured temperature to the bound device.
```
I (734026) TEMPERATURE_SENSOR: Report the temperature of sensor
I (734176) TEMPERATURE_SENSOR: Received ZCL Default Response: status(0x00)
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
