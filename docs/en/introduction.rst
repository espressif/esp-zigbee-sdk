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

.. figure:: ../_static/esp_zigbee_stack.png
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

1.2 Supported Features
----------------------

The supported features in current ESP Zigbee SDK are listed below.

1.2.1 ZCL Clusters
~~~~~~~~~~~~~~~~~~

.. table:: **ZCL cluster**
   :align: center

   ========================= ============ 
         Cluster Name         Cluster ID  
   ========================= ============ 
            basic               0x0000    
      power_configuration       0x0001
           identify             0x0003    
            groups              0x0004    
            scenes              0x0005    
            on_off              0x0006    
       on_off_switch_cfg        0x0007    
         level_control          0x0008    
             time               0x000a    
         binary_input           0x000f    
              ota               0x0019    
         shade_config           0x0100    
           door_lock            0x0101
        window_covering         0x0102    
         color_control          0x0300 
    illuminance_measurement     0x0400   
    temperature_measurement     0x0402
      pressure_measurement      0x0403
      humidity_measurement      0x0405
       occupancy_sensing        0x0406
           ias_zone             0x0500
    electrical_measurement      0x0b04
   ========================= ============ 


1.2.1.1 Attributes and Commands
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

See each cluster's supported attribute in `ZCL api-reference <https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest/esp32/api-reference/zcl/index.html>`__


1.2.2 HA Automation Device Types
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. table:: **Zigbee Home Automation**
   :align: center

   =========== ======================= ======================================================================= 
    Device ID       Device Name                                   Default Clusters                             
   =========== ======================= ======================================================================= 
     0x0002         on_off_light                       basic, identify, groups, scenes, on_off                 
     0x0000         on_off_switch                                 basic, identify                              
     0x0102     color_dimmable_light    basic, identify, groups, scenes, on_off, level_control, color_control  
     0x0105     color_dimmable_switch                              basic, identify                             
     0x0009         power_outlet                       basic, identify, groups,scenes, on_off                  
     0x0200             shade               basic, identify, groups, scenes, on_off, level_control, shade      
     0x0201       shade_controller                                 basic, identify                             
     0x000A           door_lock                      basic, identify, groups, scenes, door_lock                
     0x000B     door_lock_controller                               basic, identify                             
     0x0302      temperature_sensor                       basic, identify, temperature_meas                    
     0x0005      configuration_tool     basic, identify, groups, scenes, on_off, level_control, color_control  
   =========== ======================= ======================================================================= 

See default mandatory attributes in each HA device's cluster in `HA api-reference <https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest/esp32/api-reference/ha/index.html>`__

1.2.3 More Supported
~~~~~~~~~~~~~~~~~~~~

For any new cluster or device needs, please open an `issue <https://github.com/espressif/esp-zigbee-sdk/issues>`__ on GitHub. We will get back to you soon.
