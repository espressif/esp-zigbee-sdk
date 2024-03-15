| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# Green Power proxy combo Example 

This example code shows how to configure Zigbee Green Power combo (proxy + sink) and use it as on/off light to receive Zigbee Green Power frame from Zigbee Green device.

## Hardware Required

* One development board with ESP32-H2 SoC acting as Zigbee Green Power combo (loaded with esp_zigbee_gpc example)
* A USB cable for power supply and programming
* Choose another ESP32-H2 as Zigbee Green Power device (see [green power device example](../esp_zigbee_gpd/))

## Configure the project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target TARGET` command.

## Erase the NVRAM 

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info 
using `idf.py -p PORT erase-flash`

## Build and Flash

Build the project, flash it to the board, and start the monitor tool to view the serial output by running `idf.py -p PORT flash monitor`.

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

When the combo device disables `ZGP_COMBO_PROXY_ENABLED`, it will proxy through the ZGP proxy (see [green power proxy example](../esp_zigbee_gpp/)).

As you run the example, you will see the following log:

```
I (460) main_task: Calling app_main()
W (470) rmt: channel resolution loss, real=10666666
I (470) gpio: GPIO[8]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (480) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2 
I (500) phy: phy_version: 220,2, 37a29de, Dec 29 2023, 16:30:13
I (500) phy: libbtbb version: 944f18e, Dec 29 2023, 16:30:30
I (500) main_task: Returned from app_main()
I (510) ESP_ZGP_COMBO: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (510) ESP_ZGP_COMBO: Zigbee stack initialized
I (520) ESP_ZGP_COMBO: Start network formation
W (680) ESP_ZGP_COMBO: Network(0x685a) closed, devices joining not allowed.
I (680) ESP_ZGP_COMBO: Formed network successfully (Extended PAN ID: 60:55:f9:ff:fe:f7:2e:16, PAN ID: 0x685a, Channel:24, Short Address: 0x0000)
I (1280) ESP_ZGP_COMBO: Network(0x685a) is open for 180 seconds
I (1280) ESP_ZGP_COMBO: Network steering started
I (5500) ESP_ZGP_COMBO: ZDO signal: NWK Device Associated (0x12), status: ESP_OK
I (6020) ESP_ZGP_COMBO: ZDO signal: ZDO Device Update (0x30), status: ESP_OK
I (6080) ESP_ZGP_COMBO: New device commissioned or rejoined (short: 0x6917)
I (6710) ESP_ZGP_COMBO: ZDO signal: ZDO Device Authorized (0x2f), status: ESP_OK
I (6770) ESP_ZGP_COMBO: Network(0x685a) is open for 180 seconds
I (18650) ESP_ZGP_COMBO: Enter commissioning mode
I (18650) ESP_ZGP_COMBO: Send commissioning mode to ZGP proxy
I (18650) ESP_ZGP_COMBO: ZGP new mode 1 cause: 2
I (21620) ESP_ZGP_COMBO: Received ZGP sink message: endpoint(242), cluster(0x21), command(0x4)
I (21630) ESP_ZGP_COMBO: handle accept commissioning information
I (21780) ESP_ZGP_COMBO: Commissioning done with status: 0
I (21780) ESP_ZGP_COMBO: Commissioning information: app_id 0 endpoint 0 and src_id is 0x12345678
I (21790) ESP_ZGP_COMBO: ZGP new mode 0 cause: 3
I (25310) ESP_ZGP_COMBO: Received ZGP sink message: endpoint(242), cluster(0x21), command(0x0)
I (25310) ESP_ZGP_COMBO: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (25320) ESP_ZGP_COMBO: Light sets to On
I (26060) ESP_ZGP_COMBO: Received ZGP sink message: endpoint(242), cluster(0x21), command(0x0)
I (26060) ESP_ZGP_COMBO: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (26070) ESP_ZGP_COMBO: Light sets to Off
I (26550) ESP_ZGP_COMBO: Received ZGP sink message: endpoint(242), cluster(0x21), command(0x0)
I (26560) ESP_ZGP_COMBO: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (26560) ESP_ZGP_COMBO: Light sets to On
I (27470) ESP_ZGP_COMBO: Received ZGP sink message: endpoint(242), cluster(0x21), command(0x0)
I (27480) ESP_ZGP_COMBO: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (27480) ESP_ZGP_COMBO: Light sets to Off

```

When the combo device enables `ZGP_COMBO_PROXY_ENABLED`, it will act as a proxy itself.

As you run the example, you will see the following log:

```
I (459) main_task: Calling app_main()
W (469) rmt: channel resolution loss, real=10666666
I (469) gpio: GPIO[8]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (479) gpio: GPIO[9]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2 
I (499) phy: phy_version: 220,2, 37a29de, Dec 29 2023, 16:30:13
I (499) phy: libbtbb version: 944f18e, Dec 29 2023, 16:30:30
I (499) main_task: Returned from app_main()
I (579) ESP_ZGP_COMBO: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (579) ESP_ZGP_COMBO: Zigbee stack initialized
I (589) ESP_ZGP_COMBO: Start network formation
W (749) ESP_ZGP_COMBO: Network(0x6bd2) closed, devices joining not allowed.
I (749) ESP_ZGP_COMBO: Formed network successfully (Extended PAN ID: 60:55:f9:ff:fe:f7:2e:16, PAN ID: 0x6bd2, Channel:24, Short Address: 0x0000)
I (1359) ESP_ZGP_COMBO: Network(0x6bd2) is open for 180 seconds
I (1359) ESP_ZGP_COMBO: Network steering started
I (5479) ESP_ZGP_COMBO: Enter commissioning mode
I (5479) ESP_ZGP_COMBO: ZGP new mode 1 cause: 2
I (9619) ESP_ZGP_COMBO: handle accept commissioning information
I (10219) ESP_ZGP_COMBO: Commissioning done with status: 0
I (10219) ESP_ZGP_COMBO: Commissioning information: app_id 0 endpoint 0 and src_id is 0x12345678
I (10229) ESP_ZGP_COMBO: ZGP new mode 0 cause: 3
I (11929) ESP_ZGP_COMBO: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (11929) ESP_ZGP_COMBO: Light sets to On
I (12779) ESP_ZGP_COMBO: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (12779) ESP_ZGP_COMBO: Light sets to Off
I (13489) ESP_ZGP_COMBO: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (13489) ESP_ZGP_COMBO: Light sets to On
I (13999) ESP_ZGP_COMBO: Received message: endpoint(10), cluster(0x6), attribute(0x0), data size(1)
I (13999) ESP_ZGP_COMBO: Light sets to Off
```

## Light Control Functions

LED light will on/off when ZGPD (Zigbee Green Power device) press the button to send toggle command.


## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.
