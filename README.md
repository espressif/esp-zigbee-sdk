# ESP Zigbee SDK

## Introduction

ESP-Zigbee-SDK is the official Zigbee development framework for Espressif's ESP32 series SoCs. It provides varieties of APIs aimed to simplify the development process of Zigbee products and enable the users to go to production in the shortest possible time.

Refer [ESP Zigbee SDK Guide](https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest) for the latest version of the documentation.

## Software Components

The SDK is built on top of [ESP-IDF](https://github.com/espressif/esp-idf) and a core implementation of Zigbee protocol.

| SDK Version       | Description                                                     | Zigbee Core Stack                  |
|-------------------|-----------------------------------------------------------------|------------------------------------|
| [v1.x][link-v1.x] | LTS version under maintenance (bug fixes only, no new features) | [ZBOSS][link-dsr]                  |
| [v2.x][link-v2.x] | Latest version, recommended for new designs and production      | Espressif proprietary Zigbee stack |

[link-v1.x]: https://github.com/espressif/esp-zigbee-sdk/tree/release/v1.0
[link-v2.x]: https://github.com/espressif/esp-zigbee-sdk/tree/main
[link-dsr]: https://dsr-zoi.com

If you are going to migrate from v1.x to v2.x, please refer to our [Migration Guide](https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest/esp32/migration-guide/v2.x/index.html).

![esp_zigbee_stack](docs/_static/esp_zigbee_sdk.svg)

The Espressif Zigbee SDK is provided as pre-built library inside [esp-zigbee-lib](https://components.espressif.com/components/espressif/esp-zigbee-lib) component.

**Note:** The library component is hosted by [ESP Registry](https://components.espressif.com/), which can be downloaded automatically by specifying the dependency in `idf_component.yml` file. An example: [idf_component.yml](examples/home_automation_devices/on_off_light/main/idf_component.yml). You can also use the command in you project:

```
idf.py add-dependency "espressif/esp-zigbee-lib^2.0.0"
```

## Hardware Components

Some of the reference hardware used in development examples are listed below:

* [ESP32-H2-DevKitM-1](https://docs.espressif.com/projects/espressif-esp-dev-kits/en/latest/esp32h2/esp32-h2-devkitm-1/user_guide.html)

* [ESP32-C6-DevKitM-1](https://docs.espressif.com/projects/espressif-esp-dev-kits/en/latest/esp32c6/esp32-c6-devkitm-1/user_guide.html)

* [ESP32-C5-DevKitM-1](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c5/esp32-c5-devkitc-1/user_guide.html)

* [Espressif Thread Border Router / Zigbee Gateway](https://docs.espressif.com/projects/esp-thread-br/en/latest/hardware_platforms.html)

## Supported ESP-IDF versions

**Note:** The SDK can not be used with ESP-IDF v6.0+ yet.

The SDK is recommended to be used with [ESP-IDF v5.5.4](https://github.com/espressif/esp-idf/tree/v5.5.4). Please check
[Compatibility file on ESP-IDF master](https://github.com/espressif/esp-idf/blob/master/COMPATIBILITY.md) for the support
status of the SoCs.

## Get Started

Please clone this repository using the below command:

```
git clone https://github.com/espressif/esp-zigbee-sdk.git
```

Find our [Zigbee console example](examples/all_device_types_app) under `examples/all_device_types_app` directory and follow the instructions in the
[README of the example](examples/all_device_types_app/README.md) to build and flash the example.

Have fun playing with your Zigbee device.
