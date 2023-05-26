4. Production Considerations
============================

4.1 Espressif Zigbee manufacturing configuration
------------------------------------------------

Espressif also provides a tool :project_file:`mfg_tool<tools/mfg_tool/README.md>` for user to set the manufacturing related configuration.

Currently, user could config Install code, MAC address, Channel Mask, Manufacture Name, Manufacture Code to a flash binary file in the partition table ``zb_fct``.

- **Install code**

Zigbee installation codes, sometimes also referred to as “install codes,” are provided as a means for a device to join a Zigbee network in a reasonably secure fashion.

The installation code itself is a random value installed on the joining device at manufacturing time and is used to encrypt the initial network key transport from the Zigbee network's centralized Trust Center device (the coordinator) to the joining device.

With the creation of the Zigbee 3.0 standard in late 2016, all Zigbee devices capable of joining networks (as opposed to forming them) must support the use of installation codes during joining, as this is a requirement for Zigbee 3.0 compliance.

ESP Zigbee SDK provide :project:`tools <tools/mfg_tool>` to configuration in the manufacturing time and security related `APIs <https://docs.espressif.com/projects/esp-zigbee-sdk/en/main/esp32/api-reference/esp_zigbee_secur.html>`__ for set/add/remove install code.


- **MAC address**

The MAC address, also called IEEE address, long address, or extended address, is a 64bit number that uniquely identifies this board from all other ZigBee boards in the world.

Each Espressif's SOC already writing ("burning") one-time-programming MAC address in the eFuse memory. Here ESP Zigbee SDK provide a way that user could configure their own MAC address during the manufacturing time.
