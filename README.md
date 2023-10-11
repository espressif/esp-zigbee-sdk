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

## Get esp-zigbee-sdk

Please clone this repository using the below command:

```
git clone https://github.com/espressif/esp-zigbee-sdk.git
```

## Supported ESP-IDF versions
* This SDK currently works with ESP-IDF release/v5.1 branch.

## Copyright Notes

- All original content of this repository is Copyright (c) 2022 Espressif Systems (Shanghai) Co. Ltd and licensed under Apache 2.0 license, as described in file LICENSE.
- Example applications supplied in this repository depend on esp-zboss-lib library, which is distributed under a different license, found here [LICENSE](https://github.com/espressif/esp-zboss-lib/blob/master/LICENSE).

Users developing applications based on this SDK have to comply with the terms of both licenses, the license conditions do not prevent development of commercial products.
