| Supported Targets | ESP32-H2 | ESP32-C6 | ESP32-C5 |
| ----------------- | -------- | -------- | -------- |

# Light Bulb Example 

This example demonstrates how to configure a Home Automation color dimmable light on a Zigbee Coordinator.

## Hardware Required

* One 802.15.4 enabled development board (e.g., ESP32-H2 or ESP32-C6) running this example.
* A second board running as a Zigbee Router or End Device (see [color_dimmable_switch](../color_dimmable_switch/) example)

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Application Functions

- When the program starts, the board, acting as a Zigbee Coordinator with the `Home Automation Dimmable Light` function, will form an open network within 180 seconds.
```
I (412) main_task: Calling app_main()                                                                                                        
I (432) COLOR_DIMMABLE_LIGHT: Start ESP Zigbee Stack                                                                                  
I (432) ESP-ZIGBEE: SDK Version: v1.6.8-fcae32885b02-94cf5061*; esp32h2; 2026-04-08 12:28:23 UTC                                             
I (432) esp zigbee sleep: light sleap disabled                                                                                               
I (452) phy: phy_version: 323,2, a8ef10c, Aug  1 2025, 17:46:10  
I (452) phy: libbtbb version: 4515421, Aug  1 2025, 17:46:22
I (472) main_task: Returned from app_main()
I (522) COLOR_DIMMABLE_LIGHT: Initialize Zigbee stack
W (522) rmt: channel resolution loss, real=10666666
I (522) COLOR_DIMMABLE_LIGHT: Deferred driver initialization successful                                                               
I (532) COLOR_DIMMABLE_LIGHT: Device started up in factory-reset mode                                                                 
I (842) COLOR_DIMMABLE_LIGHT: Formed network successfully: PAN ID(0x85ff, EXT: 0x4831b7fffec183f0), Channel(13), Short Address(0x0000) 
I (1032) COLOR_DIMMABLE_LIGHT: Network(0x85ff) is open for 180 seconds                                                                
I (1032) COLOR_DIMMABLE_LIGHT: Network steering completed
I (39612) COLOR_DIMMABLE_LIGHT: Zigbee APP Signal: ZDO Device Update(type: 0x7)                                                       
I (39702) COLOR_DIMMABLE_LIGHT: New device commissioned or rejoined(short: 0x940a)                                                    
I (39912) COLOR_DIMMABLE_LIGHT: Zigbee APP Signal: ZDO Device Authorized(type: 0x8)                                                   
I (39952) COLOR_DIMMABLE_LIGHT: Network(0x85ff) is open for 180 seconds  
```

- If the board receives a ZCL `MoveToLevelWithOnOff` of LevelControl command from the network, below log will be printed and the LED on the board will adjust accordingly.
```
I (139842) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0008) server with status(0x00)              
I (139842) COLOR_DIMMABLE_LIGHT: Set Level: 255
I (139842) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0006) server with status(0x00)              
I (139852) COLOR_DIMMABLE_LIGHT: Set On/Off: 1
I (139952) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0008) server with status(0x00)              
I (139952) COLOR_DIMMABLE_LIGHT: Set Level: 233
I (140062) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0008) server with status(0x00)              
I (140062) COLOR_DIMMABLE_LIGHT: Set Level: 211
I (140172) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0008) server with status(0x00)              
I (140172) COLOR_DIMMABLE_LIGHT: Set Level: 189
I (140282) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0008) server with status(0x00)              
I (140282) COLOR_DIMMABLE_LIGHT: Set Level: 166
I (140382) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0008) server with status(0x00)              
I (140382) COLOR_DIMMABLE_LIGHT: Set Level: 144
I (140492) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0008) server with status(0x00)              
I (140492) COLOR_DIMMABLE_LIGHT: Set Level: 122
I (140602) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0008) server with status(0x00)              
I (140602) COLOR_DIMMABLE_LIGHT: Set Level: 99
I (140712) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0008) server with status(0x00)              
I (140712) COLOR_DIMMABLE_LIGHT: Set Level: 77
I (140822) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0008) server with status(0x00)              
I (140822) COLOR_DIMMABLE_LIGHT: Set Level: 55
I (140932) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0008) server with status(0x00)              
I (140932) COLOR_DIMMABLE_LIGHT: Set Level: 32
```

- If the board receives a ZCL `ZCL MoveToColor` ColorControl command from the network, below log will be printed and the LED on the board will adjust accordingly.
```          
I (154682) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (154682) COLOR_DIMMABLE_LIGHT: Set Color: 0x0066, 0x0000
I (154682) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (154692) COLOR_DIMMABLE_LIGHT: Set Color: 0x0066, 0x0066
I (154792) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (154792) COLOR_DIMMABLE_LIGHT: Set Color: 0x00cc, 0x0066
I (154792) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (154802) COLOR_DIMMABLE_LIGHT: Set Color: 0x00cc, 0x00cc
I (154902) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (154902) COLOR_DIMMABLE_LIGHT: Set Color: 0x0133, 0x00cc
I (154902) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (154912) COLOR_DIMMABLE_LIGHT: Set Color: 0x0133, 0x0133
I (155012) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155012) COLOR_DIMMABLE_LIGHT: Set Color: 0x0199, 0x0133
I (155012) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155022) COLOR_DIMMABLE_LIGHT: Set Color: 0x0199, 0x0199
I (155122) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155122) COLOR_DIMMABLE_LIGHT: Set Color: 0x0200, 0x0199
I (155122) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155132) COLOR_DIMMABLE_LIGHT: Set Color: 0x0200, 0x0200
I (155232) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155232) COLOR_DIMMABLE_LIGHT: Set Color: 0x0266, 0x0200
I (155232) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155242) COLOR_DIMMABLE_LIGHT: Set Color: 0x0266, 0x0266
I (155342) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155342) COLOR_DIMMABLE_LIGHT: Set Color: 0x02cc, 0x0266
I (155342) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155352) COLOR_DIMMABLE_LIGHT: Set Color: 0x02cc, 0x02cc
I (155452) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155452) COLOR_DIMMABLE_LIGHT: Set Color: 0x0333, 0x02cc
I (155452) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155462) COLOR_DIMMABLE_LIGHT: Set Color: 0x0333, 0x0333
I (155562) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155562) COLOR_DIMMABLE_LIGHT: Set Color: 0x0399, 0x0333
I (155562) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155572) COLOR_DIMMABLE_LIGHT: Set Color: 0x0399, 0x0399
I (155672) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155672) COLOR_DIMMABLE_LIGHT: Set Color: 0x0400, 0x0399
I (155672) COLOR_DIMMABLE_LIGHT: ZCL SetAttributeValue message for endpoint(10) cluster(0x0300) server with status(0x00)              
I (155682) COLOR_DIMMABLE_LIGHT: Set Color: 0x0400, 0x0400
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
