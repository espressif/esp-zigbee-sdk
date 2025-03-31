# esp-zigbee-sdk

## Introduction  
  
ESP-Zigbee-SDK is the official Zigbee development framework for Espressif's ESP32 series SoCs. It provides varieties of APIs aimed to simplify the development process of Zigbee products and enable the users to go to production in the shortest possible time.

Refer [ESP Zigbee SDK Guide](https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest) for the latest version of the documentation.

## Software Components

The SDK is built on top of [ESP-IDF](https://github.com/espressif/esp-idf) and [ZBOSS](https://dsr-zoi.com/).

![esp_zigbee_stack](docs/_static/esp_zigbee_stack.png)

The ZBOSS and Espressif Zigbee SDK is provided as pre-built library:
- [esp-zboss-lib](https://components.espressif.com/components/espressif/esp-zboss-lib): ZBOSS libraries for ESP32 series SoCs
- [esp-zigbee-lib](https://components.espressif.com/components/espressif/esp-zigbee-lib): Espressif Zigbee SDK and APIs libraries

Note：these two library components are hosted by [ESP Registry](https://components.espressif.com/), which can be downloaded automatically by specifying the dependency in `idf_component.yml` file. An example: [idf_component.yml](examples/esp_zigbee_HA_sample/HA_on_off_light/main/idf_component.yml).

## Hardware Components

Some of the reference hardware used in development examples are listed below:

* [ESP32-H2-DevKitM-1](https://docs.espressif.com/projects/espressif-esp-dev-kits/en/latest/esp32h2/esp32-h2-devkitm-1/user_guide.html)

* [ESP32-C6-DevKitM-1](https://docs.espressif.com/projects/espressif-esp-dev-kits/en/latest/esp32c6/esp32-c6-devkitm-1/user_guide.html)

* [Espressif Thread Border Router / Zigbee Gateway](https://docs.espressif.com/projects/esp-thread-br/en/latest/hardware_platforms.html)

## Get esp-zigbee-sdk

Please clone this repository using the below command:

```
git clone https://github.com/espressif/esp-zigbee-sdk.git
```

## Supported ESP-IDF versions
* This SDK is recommended to be used with [ESP-IDF v5.3.2](https://github.com/espressif/esp-idf/tree/v5.3.2).

## Copyright Notes

- All original content of this repository is Copyright (c) 2022 Espressif Systems (Shanghai) Co. Ltd and licensed under Apache 2.0 license, as described in file LICENSE.
- Example applications supplied in this repository depend on esp-zboss-lib library, which is distributed under a different license, found here [LICENSE](https://github.com/espressif/esp-zboss-lib/blob/master/LICENSE).

Users developing applications based on this SDK have to comply with the terms of both licenses, the license conditions do not prevent development of commercial products.
