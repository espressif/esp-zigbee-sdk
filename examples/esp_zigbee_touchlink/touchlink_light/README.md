| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Touchlink Light Example 

This test code shows touchlink target how to quick pairing of devices.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Touchlink initiator(Zigbee end deivce) (see [touchlink_switch](../touchlink_switch))
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Touchlink target(Zigbee Router)(see [touchlink_light](./))

## Important operating steps
* 1) Power on touchlink_light (Zigbee Router) and flash touchlink_light application code.
* 2) Then wait for `5-10 seconds` and Power on touchlink_switch (Zigbee end deivce) and flash touchlink_switch application code.

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py --preview set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

As you run the example, you will see the following log:

```
I (461) phy: libbtbb version: b684fcb, May 17 2023, 20:14:35                                                   
I (481) main_task: Returned from app_main()                                                                    
I (581) ESP_TL_ON_OFF_LIGHT: ZDO signal: 23, status: -1                                                        
I (581) ESP_TL_ON_OFF_LIGHT: Touchlink target started                                                          
I (21061) ESP_TL_ON_OFF_LIGHT: device is on permit join status                                                 
I (21061) ESP_TL_ON_OFF_LIGHT: Touchlink target : network started                                              
I (21061) ESP_TL_ON_OFF_LIGHT: Touchlink target finished: success                                              
I (21071) ESP_TL_ON_OFF_LIGHT: Touchlink target finished:Touchlink Target timeout 60s  
I (23671) ESP_TL_ON_OFF_LIGHT: ZDO signal: 48, status: 0                                                       
I (23691) ESP_TL_ON_OFF_LIGHT: New device commissioned or rejoined (short: 0xc214)              
I (33921) ESP_TL_ON_OFF_LIGHT: ZDO signal: 50, status: 0                                                       
I (54191) ESP_TL_ON_OFF_LIGHT: ZDO signal: 50, status: 0                                                       
I (54641) ESP_TL_ON_OFF_LIGHT: on/off light set to 1                                                           
I (55181) ESP_TL_ON_OFF_LIGHT: on/off light set to 0  
```

## Light Control Functions

 * By toggling the switch button (BOOT) on the ESP32-H2 board loaded with the `touchlink_switch` example, the LED on this board loaded with `touchlink_light` example will be on and off.

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
