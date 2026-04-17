# Zigbee Home Automation Devices Example

Those are the ha (Home Automation) Zigbee devices example. More examples will be coming soon.

## Overview

The folder contains examples demonstrating Zigbee ha standard device

* [on_off_light](on_off_light) is a standard ha on-off light bulb example demonstrating Zigbee Coordinator. It provides a simple on/off condition for a Zigbee light. It runs on an 802.15.4 SoC like ESP32-H2. For more details see [README](on_off_light/README.md).

* [on_off_switch](on_off_switch) is a standard ha on-off switch example demonstrating Zigbee End-device. It provides an on/off toggle to control a Zigbee ha on off light. It runs on an 802.15.4 SoC like ESP32-H2. For more details to see [README](on_off_switch/README.md).

* [color_dimmable_light](color_dimmable_light) is a standard ha color dimmable light bulb example demonstrating Zigbee Coordinator. It provides a color dimmable condition for a Zigbee light. It runs on an 802.15.4 SoC like ESP32-H2. For more details see [README](color_dimmable_light/README.md).

* [color_dimmable_switch](color_dimmable_switch) is a standard ha color dimmable switch example demonstrating Zigbee Router. It provides a toggle to control a Zigbee ha color dimmable light to change color and dim light. It runs on an 802.15.4 SoC like ESP32-H2. For more details to see [README](color_dimmable_switch/README.md).

* [temperature_sensor](temperature_sensor) is a standard ha temperature sensor example demonstrating Zigbee End-device. It provides temperature measurement using the on-chip temperature sensor. It runs on an 802.15.4 SoC like ESP32-H2. For more details see [README](temperature_sensor/README.md).

* [thermostat](ha_thermostat) is a standard ha thermostat example demonstrating Zigbee Coordinator. It provides temperature acquisition from temperature sensor device with both read and report mechanisms. It runs on an 802.15.4 SoC like ESP32-H2. For more details to see [README](thermostat/README.md).
