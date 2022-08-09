# esp-zigbee-sdk

## Introduction  
  
ESP-ZIGBEE-SDK is the official Zigbee development framework for Esspresif's ESP32-H2 and ESP32 series SOCs. It provides varieties of APIs aimed to simplify the development process of Zigbee products and enable the users to go to production in the shortest possible time. More details of the sdk see the [esp-zigbee-sdk components](#### esp-zigbee components)  

## Get esp-zigbee-sdk  

Please clone this repository using the below command:

```
git clone --recursive https://github.com/espressif/esp-zigbee-sdk.git
```

> Note the --recursive option. This is required to pull in the various dependencies into esp-matter. In case you have already cloned the repository without this option, execute this to pull in the submodules: `git submodule update --init --recursive`  

## Simple user guide  

#### Pre-requisite Environment  
- Refer [ESP-IDF](https://github.com/espressif/esp-idf) to get the more info about the Espressif IoT Development Framework. Official development framework for Espressif SoCs.  
- Check [IDF Get Started](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html) to know how to install the ESP-IDF environment.

#### Zigbee Examples
- Check the [HA examples](examples/esp_zigbee_HA_sample) if you want to know more about Zigbee Home automation devices  
- Check the [Customized device](examples/esp_zigbee_customized_devices) if you want to know more about customized Zigbee devices  
- Check the [Gateway](examples/esp_zigbee_gateway) if you want to know the Zigbee Gateway  

More new details see examples's [Readme](examples/README.md)

#### esp-zigbee components
- Check the component (esp-zboss-lib) should be downloaded automatically from managment component under each esp-zigbee-sdk example, it includes Zigbee stack static library for supporting Esspresif's ESP32-H2 and ESP32 series SOCs.
- Check the component [esp-zigbee-lib](components/esp-zigbee-lib/) that includes SDK's API to build own projects. More details see the [readme](components/esp-zigbee-lib/README.md) under esp-zigbee-lib component.

## Documentation  

Refer [ESP Zigbee SDK Guide](https://docs.espressif.com/projects/esp-zigbee-sdk/en/main/) for the latest version of the documentation.  
