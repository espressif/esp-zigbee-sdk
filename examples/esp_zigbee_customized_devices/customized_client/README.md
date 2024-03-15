| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Light Switch Example 

This test code shows how to customized add / update attribute, add cluster and add endpoint to a device. This example also shows how to use varieties ZDO commands and ZCL commands, like binding, finding, read attribute, configure report attribute.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee end device (loaded with customized_client example)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee coordinator (see [customized_server](../customized_server/))

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
I (372) main_task: Calling app_main()
I (382) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2 
I (382) phy_init: phy_version 220,2dbbbe7,Sep 25 2023,20:39:25
I (442) phy: libbtbb version: 90c587c, Sep 25 2023, 20:39:57
I (452) ESP_HA_ON_OFF_SWITCH: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (452) main_task: Returned from app_main()
I (4382) ESP_HA_ON_OFF_SWITCH: Joined network successfully (Extended PAN ID: 60:55:f9:00:00:f6:07:b4, PAN ID: 0x9479, Channel:13)
I (4442) ESP_HA_ON_OFF_SWITCH: Match desc response: status(0), address(0x0), endpoint(10)
I (4552) ESP_HA_ON_OFF_SWITCH: ZDO signal: NLME Status Indication (0x32), status: ESP_OK
I (4602) ESP_HA_ON_OFF_SWITCH: IEEE address: 60:55:f9:00:00:f6:07:b4
I (4662) ESP_HA_ON_OFF_SWITCH: ZDO signal: NLME Status Indication (0x32), status: ESP_OK
I (4702) ESP_HA_ON_OFF_SWITCH: Read attribute response: status(0), cluster(0x6), attribute(0x0), type(0x10), value(0)
I (4732) ESP_HA_ON_OFF_SWITCH: Bind response from address(0x0), endpoint(1) with status(0)
I (4782) ESP_HA_ON_OFF_SWITCH: Configure report response: status(0), cluster(0x6), attribute(0xffff)
I (7512) ESP_HA_ON_OFF_SWITCH: Simple desc resposne: status(0), device_id(256), app_version(0), profile_id(0x104), endpoint_ID(10)
I (7512) ESP_HA_ON_OFF_SWITCH: Cluster ID list: 0x0
I (7512) ESP_HA_ON_OFF_SWITCH: Cluster ID list: 0x3
I (7522) ESP_HA_ON_OFF_SWITCH: Cluster ID list: 0x4
I (7522) ESP_HA_ON_OFF_SWITCH: Cluster ID list: 0x5
I (7532) ESP_HA_ON_OFF_SWITCH: Cluster ID list: 0x6
I (7562) ESP_HA_ON_OFF_SWITCH: Active endpoint response: status(0) and endpoint count(1)
I (7562) ESP_HA_ON_OFF_SWITCH: Endpoint ID List: 10
I (7812) ESP_HA_ON_OFF_SWITCH: Reveived report from address(0x0) src endpoint(10) to dst endpoint(1) cluster(0x6)
I (7812) ESP_HA_ON_OFF_SWITCH: Received report information: attribute(0x0), type(0x10), value(0)

I (15862) ESP_HA_ON_OFF_SWITCH: Send 'on_off toggle' command to address(0x0) endpoint(10)
I (15952) ESP_HA_ON_OFF_SWITCH: Reveived report from address(0x0) src endpoint(10) to dst endpoint(1) cluster(0x6)
I (15952) ESP_HA_ON_OFF_SWITCH: Received report information: attribute(0x0), type(0x10), value(1)

I (24742) ESP_HA_ON_OFF_SWITCH: Send 'on_off toggle' command to address(0x0) endpoint(10)
I (24802) ESP_HA_ON_OFF_SWITCH: Reveived report from address(0x0) src endpoint(10) to dst endpoint(1) cluster(0x6)
I (24802) ESP_HA_ON_OFF_SWITCH: Received report information: attribute(0x0), type(0x10), value(0)

```

## Light Control Functions

 * By toggling the switch button (BOOT) on the ESP32-H2 board loaded with the `customized_client` example, the LED on this board loaded with `customized_server` example will be on and off.


## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
