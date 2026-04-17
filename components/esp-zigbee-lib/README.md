# esp-zigbee-lib

## Introduction
This component contains binary libraries for the Espressif proprietary Zigbee stack and the integration of ESP-IDF.
It provides the functionalities and APIs that users could use in the Zigbee product development:
    + A set of ZCL data model APIs which allows full customization
    + Standard ZCL clusters implementation for out-of-box usages
    + Standard Home Automation off-the-shelf devices
    + Varieties of ZDO commands for Zigbee node management
    + Zigbee BDB commissioning
    + Zigbee toucklink commissioning
    + Zigbee coordinator, router and (sleepy) end device roles
    + Zigbee security management: install code, tclk exchange
    + More to come ... ...

For the list of current supported ZCL clusters, attributes, commands, Zigbee Home Automation devices, see details [docs](https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest/esp32/introduction.html#supported-features).

For any new feature requests, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon.

## User guide
For a demonstration of the library use, see the examples folder [examples](https://github.com/espressif/esp-zigbee-sdk/tree/main/examples).
For information on how to program Espressif SoCs, see [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf).
For esp-zigbee-lib related user guide and documents, see [docs](https://docs.espressif.com/projects/esp-zigbee-sdk/).
