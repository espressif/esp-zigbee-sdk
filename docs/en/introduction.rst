1. Introduction
===============

1.1 Espressif Zigbee Solutions
------------------------------

Espressif's Zigbee Solutions consist of:

   - A full spectrum of Zigbee device platforms
   - Production ready SDK
   - Zigbee and ESP RainMaker integration

1.1.1 Espressif Zigbee Platforms
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Espressif platform solutions are as shown below:

.. figure:: ../_static/esp_zigbee_platform.png
    :align: center
    :alt: ESP platform
    :figclass: align-center

- ESP32-H SoCs and modules with 802.15.4 can be used to build **Zigbee devices**.
- By efficiently combining ESP32-H and our Wi-Fi SoCs, a **Zigbee gateway** can be built to connect the Zigbee network with the Wi-Fi network. We provide hardware devkits, reference designs and production-ready SDK, which supports the latest Zigbee 3.0.
- We also provide Matter-Zigbee solutions that enable non-Matter devices based on Zigbee and other protocols to connect to the Matter ecosystem. A **Matter-Zigbee Bridge** uses ESP32-H and another Wi-Fi SoC. See `ESP Matter <https://docs.espressif.com/projects/esp-matter/en/main/esp32/>`__ here.

1.1.2 ESP Zigbee SDK
~~~~~~~~~~~~~~~~~~~~

Espressif's Zigbee SDK is built on top of the `Zboss stack <https://dsr-zboss.com/>`__. It will be compiled as library called (esp-zboss-lib) and provided to user.

-  It provides ZCL data model APIs, varieties of ZDO, ZCL commands to support application layer of the Zigbee stack.
-  It provides simplified APIs for Zigbee nwk layer configuration, BDB commissioning and security related functions. 
-  It provides Standard Home Automation off-the-shelf devices that ready to use.
-  It includes rich production references.

Espressif is aimed to simplify the development process of Zigbee products and enable the users to go to production in the shortest possible time.

.. figure:: ../_static/SDk_structure.png
    :align: center
    :alt: ESP Zigbee Software Components
    :figclass: align-center

|  

1.1.3 Zigbee and ESP RainMaker Integration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Espressif's AIoT cloud platform `ESP RainMaker <https://rainmaker.espressif.com/>`__ can provide remote control and enable cloud-based device management for Zigbee devices.

By combining the above-mentioned Zigbee hardware and software solutions with ESP RainMaker, this one-stop Zigbee ecosystem solution provides a full-fledged cloud deployment through your own private account with advanced device management features.

.. todo::
    Add introduction here and add example in the rainmaker repository for Zigbee solution
