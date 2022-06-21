# Examples

This directory contains a range of Zigbee examples. These examples are intended to demonstrate different functionalities of usage Zigbee protocol to build Zigbee product, and to provide code that you can copy and adapt into your own projects.  

## Examples Layout
The examples are grouped into subdirectories by category. Each category directory contains one or more example projects:  
- [esp_zigbee_customized_devices](esp_zigbee_customized_devices) Zigbee fully customized attribute/cluster/endpoint for server and client devices
- [esp_zigbee_gateway](esp_zigbee_gateway) Zigbee gateway example to demonstrate Wi-Fi SoCs such as ESP32, ESP32-C3 and ESP32-S3, with an 802.15.4 SoC like ESP32-H2
- [esp_zigbee_rcp](esp_zigbee_rcp) Zigbee rcp (radio co-processor) device
- [esp_zigbee_HA_sample](esp_zigbee_HA_sample) Zigbee HA sample examples

## Using Examples
Please see the information on usage under each Zigbee examples folder.

## Copying Examples
Each example is a standalone project. The examples _do not have to be inside the esp-idf directory_. You can copy an example directory to anywhere on your computer in order to make a copy that you can modify and work with.

The `IDF_PATH` environment variable is the only thing that connects the example to the rest of ESP-IDF.

If you're looking for a more bare-bones project to start from, try [esp-idf-template](https://github.com/espressif/esp-idf-template).

## Contributing Examples

If you have a new example you think we'd like, please consider sending it to us as a Pull Request.

