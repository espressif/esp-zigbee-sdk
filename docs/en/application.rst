5. Application User Guide
=================================

5.1 ESP NCP Guide
---------------------

The Espressif Zigbee NCP Serial Protocol (ESP ZNSP) defined in this document is the protocol used by a host application processor to interact with the Zigbee stack running on a Network Co-Processor (NCP). 
ESP ZNSP messages are sent between the host and the Zigbee application over either a Serial Peripheral Interface (SPI) or a Universal Asynchronous Receiver/Transmitter (UART) interface.

5.1.1 Introduction
~~~~~~~~~~~~~~~~~~

The ESP ZNSP frames which are used by the Zigbee Gateway application to communicate with the Host are encapsulated in the Serial Line Internet Protocol (SLIP).

5.1.2 SLIP
~~~~~~~~~~~~~~~~~

The application protocol frames which are used by the NCP application to communicate with the microcontroller are encapsulated in the Serial Line Internet Protocol (SLIP). For a
comprehensive documentation and a reference implementation of SLIP, please refer to `RFC 1055 <https://www.rfc-editor.org/rfc/rfc1055.txt>`.

5.1.3 Byte Order
~~~~~~~~~~~~~~~~~

All multiple octet fields are transmitted and received with the least significant octet first, also referred to as `little endian`. This is the same byte order convention specified by 802.15.4 and ZigBee. 

Note that EUI64 fields are treated as a 64-bit number and are therefore trans-mitted and received in little endian order. Each individual octet is transmitted and received by the SPI or UART interface.

5.1.4 16-bit CRC Calculation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As extension each frame contains a 16-bit CRC after the content, calculated over the complete frame payload.

5.1.5 Frame Format
~~~~~~~~~~~~~~~~~~~

The format of the ESP ZNSP frame is as follows:

.. highlight:: none

::

   --------------------------------------
   | Frame Header | Frame Payload | FCS |
   --------------------------------------
     7 bytes        variable byte   2 bytes
   
- Frame Header: Mandatory, fixed size as follows:

   .. highlight:: none

   ::

      -------------------------------------------------
      | Flags | Identifier | Sequence Number | Length |
      -------------------------------------------------
        2 byte  2 byte       1 bytes           2 byte

   - Flags: Defined as follows:

      .. highlight:: none

      ::

         -----------------------------------
         | Version | Frame Type | Reserved |
         -----------------------------------
           0~3 bits  4~7 bits     8~15 bits

      - Version: ESP ZNSP version.
      - Frame Type: 0: Request, 1: Response, 2: Indication.
      - Reserved: Reserved.

   - Identify: Request or Indication ID.
   - Sequence Number: Request transaction sequence number, 0 - 254.
   - Length: Length of the frame without a header.

- Frame Payload: Optional, variable size as follows:

   .. highlight:: none

   ::

      -------------------
      | Data Parameters |
      -------------------
        variable bytes    

5.1.6 Frame ID Lists
~~~~~~~~~~~~~~~~~~~~

+----------+---------------------------------+----------------+------------------------------------------------------------------------------------------+
| Group ID | Frame Name                      | Frame ID       | Function                                                                                 |
+----------+---------------------------------+----------------+------------------------------------------------------------------------------------------+
|  Network | NETWORK_INIT                    | 0x0000         | Resume network operation after a reboot                                                  |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+
|          | NETWORK_START                   | 0x0001         | Start the commissioning process                                                          |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+
|          | NETWORK_STATE                   | 0x0002         | Returns a value indicating whether the node is joining, joined to, or leaving a network  |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+
|          | NETWORK_STACK_STATUS_HANDLER    | 0x0003         | Notify it when the status of the stack changes                                           |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_FORM                    | 0x0004         | Forms a new network by becoming the coordinator                                          |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_PERMIT_JOINING          | 0x0005         | Allow other nodes to join the network with this node as their parent                     |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_JOIN                    | 0x0006         | Associate with the network using the specified network parameters                        |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_LEAVE                   | 0x0007         | Causes the stack to leave the current network                                            |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_START_SCAN              | 0x0008         | Active scan available network                                                            |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_SCAN_COMPLETE_HANDLER   | 0x0009         | Signals that the scan has completed                                                      | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_STOP_SCAN               | 0x000A         | Terminates a scan in progress                                                            |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+  
|          | NETWORK_PAN_ID_GET              | 0x000B         | Get the Zigbee network PAN ID                                                            | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_PAN_ID_SET              | 0x000C         | Set the Zigbee network PAN ID                                                            | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_EXTENDED_PAN_ID_GET     | 0x000D         | Get the Zigbee network extended PAN ID                                                   | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_EXTENDED_PAN_ID_SET     | 0x000E         | Set the Zigbee network extended PAN ID                                                   | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_PRIMARY_CHANNEL_GET     | 0x000F         | Get the primary channel mask                                                             | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_PRIMARY_CHANNEL_SET     | 0x0010         | Set the primary channel mask                                                             | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_SECONDARY_CHANNEL_GET   | 0x0011         | Get the secondary channel mask                                                           | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_SECONDARY_CHANNEL_SET   | 0x0012         | Set the secondary channel mask                                                           | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_CHANNEL_GET             | 0x0013         | Get the 2.4G channel                                                                     | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_CHANNEL_SET             | 0x0014         | Set the 2.4G channel mask                                                                | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_TXPOWER_GET             | 0x0015         | Get the tx power                                                                         | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_TXPOWER_SET             | 0x0016         | Set the tx power                                                                         | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_PRIMARY_KEY_GET         | 0x0017         | Get the primary security network key                                                     | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_PRIMARY_KEY_SET         | 0x0018         | Set the primary security network key                                                     | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_FRAME_COUNT_GET         | 0x0019         | Get the network frame counter                                                            | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_FRAME_COUNT_SET         | 0x001A         | Set the network frame counter                                                            | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_ROLE_GET                | 0x001B         | Get the network role 0: Coordinator, 1: Router                                           | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_ROLE_SET                | 0x001C         | Set the network role 0: Coordinator, 1: Router                                           | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_SHORT_ADDRESS_GET       | 0x001D         | Get the Zigbee device short address                                                      | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_SHORT_ADDRESS_SET       | 0x001E         | Set the Zigbee device short address                                                      | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_LONG_ADDRESS_GET        | 0x001F         | Get the Zigbee device long address                                                       | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_LONG_ADDRESS_SET        | 0x0020         | Set the Zigbee device long address                                                       | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_CHANNEL_MASKS_GET       | 0x0021         | Get the channel masks                                                                    | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_CHANNEL_MASKS_SET       | 0x0022         | Set the channel masks                                                                    | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_UPDATE_ID_GET           | 0x0023         | Get the network update ID                                                                | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_UPDATE_ID_SET           | 0x0024         | Set the network update ID                                                                | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_TRUST_CENTER_ADDR_GET   | 0x0025         | Get the network trust center address                                                     | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_TRUST_CENTER_ADDR_SET   | 0x0026         | Set the network trust center address                                                     | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_LINK_KEY_GET            | 0x0027         | Get the network link key                                                                 | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_LINK_KEY_SET            | 0x0028         | Set the network link key                                                                 | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_SECURE_MODE_GET         | 0x0029         | Get the network security mode                                                            | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_SECURE_MODE_SET         | 0x002A         | Set the network security mode                                                            | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_PREDEFINED_PANID        | 0x002B         | Enable or disable predefined network panid                                               | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_SHORT_TO_IEEE           | 0x002C         | Get the network IEEE address by the short address                                        |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | NETWORK_IEEE_TO_SHORT           | 0x002D         | Get the network short address by the IEEE address                                        |
+----------+---------------------------------+----------------+------------------------------------------------------------------------------------------+
| ZCL      | ZCL_ENDPOINT_ADD                | 0x0100         | Configures endpoint information on the NCP                                               | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | ZCL_ENDPOINT_DEL                | 0x0101         | Remove endpoint information on the NCP                                                   |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+  
|          | ZCL_ATTR_READ                   | 0x0102         | Read attribute data on NCP endpoints                                                     | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | ZCL_ATTR_WRITE                  | 0x0103         | Write attribute data on NCP endpoints                                                    | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | ZCL_ATTR_REPORT                 | 0x0104         | Report attribute data on NCP endpoints                                                   | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | ZCL_ATTR_DISC                   | 0x0105         | Discover attribute data on NCP endpoints                                                 | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | ZCL_READ                        | 0x0106         | Read APS on NCP endpoints                                                                | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | ZCL_WRITE                       | 0x0107         | Write APS on NCP endpoints                                                               | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | ZCL_REPORT_CONFIG               | 0x0108         | Report configure on NCP endpoints                                                        | 
+----------+---------------------------------+----------------+------------------------------------------------------------------------------------------+
|  ZDO     | ZDO_BIND_SET                    | 0x0200         | Create a binding between two endpoints on two nodes                                      | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | ZDO_UNBIND_SET                  | 0x0201         | Remove a binding between two endpoints on two nodes                                      | 
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+ 
|          | ZDO_FIND_MATCH                  | 0x0202         | Send match desc request to find matched Zigbee device                                    | 
+----------+---------------------------------+----------------+------------------------------------------------------------------------------------------+
|  APS     | APS_DATA_REQUEST                | 0x0300         | Request the aps data                                                                     |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+
|          | APS_DATA_INDICATION             | 0x0301         | Indication the aps data                                                                  |
|          +---------------------------------+----------------+------------------------------------------------------------------------------------------+
|          | APS_DATA_CONFIRM                | 0x0302         | Confirm the aps data                                                                     |
+----------+---------------------------------+----------------+------------------------------------------------------------------------------------------+

5.1.7 Network Frame ID Details
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

5.1.7.1 NETWORK_INIT
^^^^^^^^^^^^^^^^^^^^^

Resume network operation after a reboot

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.2 NETWORK_PAN_ID_SET
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the Zigbee network PAN ID

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint16_t panid                        : 16-bit Zigbee network PAN ID                             |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.3 NETWORK_PAN_ID_GET
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the Zigbee network PAN ID

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint16_t panid                        : 16-bit Zigbee network PAN ID                             |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.4 NETWORK_EXTENDED_PAN_ID_SET
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the Zigbee network extended PAN ID

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[8] extpanid                   : An 64-bit of extended PAN ID                             |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.5 NETWORK_EXTENDED_PAN_ID_GET
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the Zigbee network extended PAN ID

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t[8] extpanid                   : An 64-bit of extended PAN ID                             |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.6 NETWORK_PRIMARY_CHANNEL_SET     
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the primary channel mask

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint32_t channelmask                  : Valid channel mask                                       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.7 NETWORK_SECONDARY_CHANNEL_SET   
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the secondary channel mask

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint32_t channelmask                  : Valid channel mask                                       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.8 NETWORK_CHANNEL_SET        
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the 2.4G channel mask

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint32_t channelmask                  : Valid channel mask                                       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.9 NETWORK_TXPOWER_SET        
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the tx power

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t  power                        : 8-bit of power value in dB                               |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.10 NETWORK_FORM
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Forms a new network by becoming the coordinator

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t  role                         : The role of device in zigbee network                     |
|                        | uint8_t  max_children or ed_timeout   : Max number of the children when coordinator or router,   |
|                        |                                         timeout when end device                                  |
|                        | bool     install_code_policy          : Allow install code security policy or not                |
|                        | uint32_t keep_alive                   : Keep alive timeout in milliseconds when end device       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t[8] extended_panid             : The IEEE address for the source                          |
|                        | uint8_t    panid                      : PAN id                                                   |
|                        | uint8_t    channel                    : Current channel work on|                                 |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.11 NETWORK_START_SCAN 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Active scan available network

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint32_t channel_mask                 : Bits set as 1 indicate that the channel should be scanned|
|                        | uint8_t  scan_duration                : Time to spend scanning each channel                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.12 NETWORK_SCAN_COMPLETE_HANDLER   
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Signals that the scan has completed

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t status                        : The ZDO response status                                  |
|                        | uint8_t count                         : Number of discovered networks                            |
|                        | uint16_t short_pan_id                 : PAN id                                                   |
|                        | bool     permit_joining               : Indicates that at least one router/coordinator on the    |
|                        |                                         network currently permits joining                        |
|                        | uint8_t[8] extended_panid             : The IEEE address for the source                          |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.13 NETWORK_STOP_SCAN  
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Terminates a scan in progress

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.14 NETWORK_START     
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Start the commissioning process

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | bool autostart                        : Autostart or no-autostart                                |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.15 NETWORK_STATE      
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Returns a value indicating whether the node is joining, joined to, or leaving a network

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t network_state                 : A value indicating whether the node is joining, joined to|
|                        |                                         , or leaving a network                                   |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.16 NETWORK_STACK_STATUS_HANDLER    
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Notify it when the status of the stack changes

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t stack_status                  : The status of the stack changes                          |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t stack_status                  : The status of the stack changes                          |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.17 NETWORK_JOIN
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Associate with the network using the specified network parameters

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t  role                         : The role of device in zigbee network                     |
|                        | bool     install_code_policy          : Allow install code security policy or not                |
|                        | uint8_t  max_children or ed_timeout   : Max number of the children when coordinator or router,   |
|                        |                                         timeout when end device                                  |
|                        | uint32_t keep_alive                   : Keep alive timeout in milliseconds when end device       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint16_t      short_addr              : Short address of device requested to join device         |
|                        | uint8_t[8]    ieee_addr               : Long address of device requested to join  device         |
|                        | uint16_t      capability              : Capability of device requested to join device            |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.18 NETWORK_PERMIT_JOINING 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Allow other nodes to join the network with this node as their parent

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t      duration                 : A value of 0x00 disables joining                         |
|                        |                                       : A value of 0xFF enables joining                          |
|                        |                                       : Other value enables joining for that number of seconds   |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t      duration                 : A value of 0x00 disables joining                         |
|                        |                                       : A value of 0xFF enables joining                          |
|                        |                                       : Other value enables joining for that number of seconds   |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.19 NETWORK_LEAVE   
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Causes the stack to leave the current network

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint16_t     short_addr               : Short address of device requested to leave device        |
|                        | uint8_t[8]   device_addr              : Long address of device requested to leave device         |
|                        | uint16_t     rejoin                   : 1 if this was leave with rejoin; 0 - otherwise           |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.20 NETWORK_SHORT_ADDRESS_GET  
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the Zigbee device short address

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint16_t short_addr                   : The Zigbee device short address                          |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.21 NETWORK_LONG_ADDRESS_GET   
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the Zigbee device long address

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t[8] long_addr                  : The Zigbee device long address                           |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.22 NETWORK_CHANNEL_GET        
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the 2.4G channel

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t channel                     : The Zigbee device current channel                          |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.23 NETWORK_PRIMARY_CHANNEL_GET     
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the primary channel mask

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint32_t channel_mask                     : The primary channel mask                             |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.24 NETWORK_PRIMARY_KEY_GET
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the primary security network key

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t[16] network_key                     : The primary security network key                   |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.25 NETWORK_PRIMARY_KEY_SET
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the primary security network key

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[16] network_key                     : The primary security network key                   |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.26 NETWORK_FRAME_COUNT_GET
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the network frame counter

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint32_t frame_counter                      : The network frame counter                          |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.27 NETWORK_FRAME_COUNT_SET
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the network frame counter

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint32_t frame_counter                      : The network frame counter                          |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.28 NETWORK_ROLE_GET   
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the network role 0: Coordinator, 1: Router

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t role                      : The network role                                             |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.29 NETWORK_ROLE_SET   
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the network role 0: Coordinator, 1: Router

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t role                      : The network role                                             |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.30 NETWORK_SHORT_ADDRESS_SET       
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the Zigbee device short address

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint16_t short_addr                      : The Zigbee device short address                       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.31 NETWORK_LONG_ADDRESS_SET        
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the Zigbee device long address

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[8] long_addr                      : The Zigbee device long address                       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.32 NETWORK_CHANNEL_MASKS_GET   
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the network role 0: Coordinator, 1: Router

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint32_t role                      : The Zigbee device the 2.4G channel mask                     |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.33 NETWORK_CHANNEL_MASKS_SET       
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the channel masks

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint32_t channel_mask                      : The Zigbee device the 2.4G channel mask             |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.34 NETWORK_UPDATE_ID_GET  
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the network update ID

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t nwk_update_id                      : The network update ID                               |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.35 NETWORK_UPDATE_ID_SET  
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the network update ID

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t nwk_update_id                      : The network update ID                               |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.36 NETWORK_TRUST_CENTER_ADDR_GET   
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the network trust center address

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t[8] nwk_update_id                      : The network trust center address                 |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.37 NETWORK_TRUST_CENTER_ADDR_SET   
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the network trust center address

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t nwk_update_id                      : The network trust center address                    |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.38 NETWORK_LINK_KEY_GET   
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the network link key

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t[16] link_key                      : The network link key                                 |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.39 NETWORK_LINK_KEY_SET        
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the network link key

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[16] link_key                      : The network link key                                 |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.40 NETWORK_SECURE_MODE_GET
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the network security mode

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_secur_t secur_mode                      : The network security mode                      |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.41 NETWORK_SECURE_MODE_SET
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set the network security mode

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | esp_ncp_secur_t secur_mode                      : The network security mode                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.42 NETWORK_PREDEFINED_PANID
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Enable or disable predefined network panid

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | esp_ncp_secur_t secur_mode                      : Enable od disable the network panid            |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.43 NETWORK_SHORT_TO_IEEE
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the network IEEE address by the short address

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint16_t short_addr                      : The Zigbee device short address                       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t[8] ieee_addr                      : The Zigbee device long address                       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.7.44 NETWORK_IEEE_TO_SHORT
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Get the network short address by the IEEE address

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[8] ieee_addr                      : The Zigbee device long address                       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint16_t short_addr                      : The Zigbee device short address                       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.8 ZCL Frame ID Details
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

5.1.8.1 ZCL Command ID Lists     
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Cluster    | ZCL Command Name                                                   | ZCL Command ID | ZCL Command Payload                                                                               | ZCL Command Function                       |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Basic      | basic_fact_reset                                                   | 0x0000         | None                                                                                              | ZCL basic reset to factory default         |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| On/Off     | Turn off                                                           | 0x0000         | None                                                                                              | ZCL on-off                                 |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | Turn on                                                            | 0x0001         | None                                                                                              | ZCL on-off                                 |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | Toggle state                                                       | 0x0002         | None                                                                                              | ZCL on-off                                 |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Identify   | identify                                                           | 0x0000         | uint16_t identify_time                 : identify itself for specific time                        | ZCL identify                               |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | identify_query                                                     | 0x0001         | None                                                                                              | ZCL identify query                         |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | identify_trigger_effect                                            | 0x0040         | uint8_t effect_id                      : The field specifies the identify effect to use           | ZCL identify trigger effect                |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t effect_variant                 : The field is used to indicate which variant of the effect|                                            |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Level      | level_move_to_level                                                | 0x0000         | uint8_t level                          : level wants to move to                                   | ZCL move to level                          |
| control    |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | level_move                                                         | 0x0001         | uint8_t move_mode                      : move mode either up or down                              | ZCL move level                             |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t rate                           : move rate wants to movement in units per second          |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | level_step                                                         | 0x0002         | uint8_t step_mode                      : step mode either up or down                              | ZCL step level                             |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t step_size                      : step size wants to change                                |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | level_stop                                                         | 0x0003         | None                                                                                              | ZCL stop level                             |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | level_move_to_level_with_onoff                                     | 0x0004         | uint8_t level                          : level wants to move to                                   | ZCL move to level with on/off              |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | level_move_with_onoff                                              | 0x0005         | uint8_t move_mode                      : move mode either up or down                              | ZCL move level with on/off effect          |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t rate                           : move rate wants to movement in units per second          |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | level_step_with_onoff                                              | 0x0006         | uint8_t step_mode                      : step mode either up or down                              | ZCL step level with on/off effect          |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t step_size                      : step size wants to change                                |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Color      | color_move_to_hue                                                  | 0x0000         | uint8_t hue                            : current value of hue                                     | ZCL color move to hue                      |
| control    |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t direction                      : direction                                                |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_move_hue                                                     | 0x0001         | uint8_t move_mode                      : move mode                                                | ZCL color move hue                         |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t rate                           : rate                                                     |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_step_hue                                                     | 0x0002         | uint8_t step_mode                      : step mode                                                | ZCL color step hue                         |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t step_size                      : step size                                                |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_move_to_saturation                                           | 0x0003         | uint8_t saturation                     : current value of saturation                              | ZCL color move to saturation               |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | int16_t transition_time                : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_move_saturation                                              | 0x0004         | uint8_t move_mode                      : move mode                                                | ZCL color move saturation                  |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t rate                           : rate                                                     |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_step_saturation                                              | 0x0005         | uint8_t step_mode                      : step mode                                                | ZCL color step saturation                  |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t step_size                      : step size                                                |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_move_to_hue_and_saturation                                   | 0x0006         | uint8_t hue                            : current value of hue                                     | ZCL color move to hue/saturation           |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t saturation                     : current value of saturation                              |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_move_to_color                                                | 0x0007         | uint16_t color_x                       : current value of chromaticity value x                    | ZCL color move to color                    |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t color_y                       : current value of chromaticity value y                    |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_move_color                                                   | 0x0008         |  uint16_t rate_x                       : specifies rate of movement in steps per second of color x| ZCL color move color                       |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                |  uint16_t rate_y                       : specifies rate of movement in steps per second of color y|                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_step_color                                                   | 0x0009         | int16_t step_x                         : specifies the change to be added to color x              | ZCL color step color                       |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | int16_t step_y                         : specifies the change to be added to color y              |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_move_to_color_temperature                                    | 0x000A         | uint16_t color_temperature             : The field indicates the color-temperature value          | ZCL color move to color temperature        |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_enhanced_move_to_hue                                         | 0x0040         | uint16_t enhanced_hue                  : The field specifies the target enhanced hue for the lamp | ZCL color enhanced move to hue             |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t direction                      : The direction                                            |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_enhanced_move_hue                                            | 0x0041         | uint8_t move_mode                      : The Move Mode                                            | ZCL color enhanced move hue                |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t rate                          : The rate of movement in steps per second                 |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_enhanced_step_hue                                            | 0x0042         | uint8_t step_mode                      : The Step Mode                                            | ZCL color enhanced step hue                |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t step_size                     : The Step Size                                            |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_enhanced_move_to_hue_saturation                              | 0x0043         | uint16_t enhanced_hue                  : The Enhanced Hue specifies the target extended hue       | ZCL color enhanced move to hue saturation  |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t saturation                     : The value of Saturation                                  |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_color_loop_set                                               | 0x0044         | uint8_t update_flags                   : The Update Flags                                         | ZCL color color loop set                   |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                |  uint8_t action                        : The Action to take for the color loop                    |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint8_t direction                      : The Direction field of the color loop set command        |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t time                          : The Time over which to perform a full color loop         |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t start_hue                     : The starting hue to use for the color loop               |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_stop_move_step                                               | 0x0047         | None                                                                                              | ZCL color stop                             |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_move_color_temperature                                       | 0x004B         | uint8_t move_mode                      : The Move Mode field of the Move Hue command              | ZCL color move color temperature           |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t rate                          : The Rate of movement in steps per second                 |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t color_temperature_minimum     : The lower bound on the Color-Temperature attribute       |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t color_temperature_maximum     : The upper bound on the Color-Temperature attribute       |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | color_step_color_temperature                                       | 0x004C         | uint8_t move_mode                      : The Move Mode field of the Step Hue command              | ZCL color step color temperature           |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t step_size                     : The Step Size field specifies the change to be added to  |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t color_temperature_minimum     : The lower bound on the Color-Temperature attribute       |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t color_temperature_maximum     : The upper bound on the Color-Temperature attribute       |                                            |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Door Lock  | lock_door                                                          | 0x0000         | None                                                                                              | ZCL lock door                              |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | unlock_door                                                        | 0x0001         | None                                                                                              | ZCL unlock door                            |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Groups     | groups_add_group                                                   | 0x0000         | uint16_t group_id                      : Group id                                                 | ZCL groups add group                       |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | groups_view_group                                                  | 0x0001         | uint16_t group_id                      : Group id                                                 | ZCL view group                             |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | groups_get_group_membership                                        | 0x0002         | uint8_t group_count                    : Total group count                                        | ZCL groups get group membership            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t[] group_list                  : Group ID list                                            |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | groups_remove_group                                                | 0x0003         | uint16_t group_id                      : Group id                                                 | ZCL groups remove group                    |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | groups_remove_all_groups                                           | 0x0004         | None                                                                                              | ZCL groups remove all groups               |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Scene      | scenes_add_scene                                                   | 0x0000         | uint16_t group_id                      : Group id                                                 | ZCL scenes add scene                       |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t scene_id                       : Scene id                                                 |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t transition_time               : time wants to transition tenths of a second              |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t extension_count               : Total ZCL scenes extension field count                   |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t cluster_id                    : Cluster id                                               |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t length                        : Length of scenes_extension_field                         |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint8_t[] extension_value              : Extension field attribute value                          |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                |                                                                                                   |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t cluster_id                    : Cluster id                                               |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint16_t length                        : Length of scenes_extension_field                         |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |    
|            |                                                                    |                | uint8_t[] extension_value              : Extension field attribute value                          |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | scenes_view_scene                                                  | 0x0001         | uint16_t group_id                      : Group id                                                 | ZCL scenes view scene                      |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t scene_id                       : Scene id                                                 |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | scenes_remove_scene                                                | 0x0002         | uint16_t group_id                      : Group id                                                 | ZCL scenes remove scene                    |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t scene_id                       : Scene id                                                 |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | scenes_remove_all_scenes                                           | 0x0003         | uint16_t group_id                      : Group id                                                 | ZCL scenes remove all scenes               |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | scenes_store_scene                                                 | 0x0004         | uint16_t group_id                      : Group id                                                 | ZCL scenes store scene                     |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t scene_id                       : Scene id                                                 |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | scenes_recall_scene                                                | 0x0005         | uint16_t group_id                      : Group id                                                 | ZCL scenes recall scene                    |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t scene_id                       : Scene id                                                 |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | scenes_get_scene_membership                                        | 0x0006         | uint16_t group_id                      : Group id                                                 | ZCL scenes get scene membership            |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| IAS Zone   | ias_zone_enroll_cmd_resp                                           | 0x0000         | uint8_t enroll_rsp_code                : The enroll response code                                 | ZCL IAS zone enroll response               |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t zone_id                        : Zone ID is the index of table                            |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | ias_zone_status_change_notif                                       | 0x0000         | uint16_t zone_status                   : Zone status                                              | ZCL IAS zone Change Notification           |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t  extend_status                 : Extended status for additional info                      |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t  zone_id                       : Zone ID is the index of table                            |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t delay                         : Delay in quarter-seconds                                 |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | ias_zone_enroll                                                    | 0x0001         | uint16_t zone_type                     : Zone type                                                | ZCL IAS zone enroll request                |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t manuf_code                    : Manufacturer code                                        |                                            |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Window     | window_covering_cluster_send                                       | 0x0000         | uint16_t length                        : Length of the value                                      | ZCL window covering send                   |
| Covering   |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t[] value                        : The value                                                |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t cluster_id                    : Cluster id                                               |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t cmd_id                         : Command id                                               |                                            |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Electrical | electrical_measurement_cluster_get_profile_info_resp               | 0x0000         | uint8_t count                          : The counter for response command                         | ZCL electrical profile information command |
| Measurement|                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t interval_period                : The Profile interval period                              |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t max_number_of_intervals       : The Profile max number of intervals                       |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uuint16_t attributes_size              : The Profile attributes size                              |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t[] attributes_list             : The Profile attributes ID list                           |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t cluster_id                    : Cluster id                                               |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | electrical_measurement_cluster_get_measurement_profile_resp        | 0x0001         | uint32_t start_time                    : The start time for profile response command              | ZCL electrical profile responset           |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint32_t status                        : The status                                               |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint32_t interval_period               : The interval period                                      |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t interval_delivered_number      : The interval delivered numbe                             |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t attributes_id                  : The interval attributes id                               |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t[] intervals                    : The array of atttibute values intervals id               |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t cluster_id                    : Cluster id                                               |                                            |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Thermostat | thermostat_setpoint_raise_lower                                    | 0x0000         | uint8_t mode                           : Mode field                                               | ZCL thermostat setpoint raise lower        |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | int8_t amount                          : Amount field                                             |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | thermostat_set_weekly_schedule                                     | 0x0001         | uint8_t num_of_transitions             : Number of transitions for sequence field                 | ZCL thermostat set weekly schedule         |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t day_of_week                    : Day of week for sequence field                           |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t mode_for_seq                   : Mode for sequence field                                  |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t transition_time               : Transition time field                                    |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t heat_set_point                : Heat set point field                                     |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t cool_set_point                : Cool set point field                                     |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | thermostat_get_weekly_schedule                                     | 0x0002         | uint8_t days_to_return                 : Days to return field                                     | ZCL thermostat get weekly schedule         |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t mode_to_return                 : Mode to return field                                     |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | thermostat_clear_weekly_schedule                                   | 0x0003         | None                                                                                              | ZCL thermostat clear weekly schedule       |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | thermostat_get_relay_status_log                                    | 0x0004         | None                                                                                              | ZCL thermostat get relay status log        |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Metering   | metering_get_profile                                               | 0x0000         | uint8_t interval_channel               : Interval channel                                         | ZCL metering get profile request           |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint32_t end_time                      : End time is a 32-bit value (in UTC)                      |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t number_of_periods              : Number of periods represents                             |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | metering_request_fast_poll_mode                                    | 0x0003         | uint8_t fast_poll_update_period        : Desired fast poll period (seconds)                       | ZCL metering request fast poll mode        |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t duration                       : Desired duration (minutes)                               |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | metering_get_snapshot                                              | 0x0006         | uint32_t earliest_start_time           : A UTC Timestamp indicating the earliest time             | ZCL metering get snapshot                  |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint32_t latest_end_time               : A UTC Timestamp indicating the latest time               |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t snapshot_offset                : This field identifies the individual snapshot            |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint32_t snapshot_cause                : This field is used to select snapshots that were taken   |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | metering_get_sampled_data                                          | 0x0008         | uint16_t sample_id                     : Unique identifier allocated to this Sampling session     | ZCL metering get sampled data              |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint32_t earliest_sample_time          : A UTC Timestamp indicating the earliest time             |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t sample_type                    : Sample_type identifies the required type of sampled data |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t number_of_samples             : The number of samples being requested                    |                                            |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
| Custom     | zb_zcl_custom_cluster_cmd_req                                      | 0xFFFD         | uint16_t type                          : The type of custom data                                  | Custom cluster command request             |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t length                        : The length of custom datat                               |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t[] value                        : The value of custom datat                                |                                            |
|            +--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+
|            | zb_zcl_custom_cluster_cmd_resp                                     | 0xFFFE         | uint16_t type                          : The type of custom data                                  | Custom cluster command response            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint16_t length                        : The length of custom datat                               |                                            |
|            |                                                                    |                +---------------------------------------------------------------------------------------------------+                                            |
|            |                                                                    |                | uint8_t[] value                        : The value of custom datat                                |                                            |
+------------+--------------------------------------------------------------------+----------------+---------------------------------------------------------------------------------------------------+--------------------------------------------+

.. note::

   The ZCL command payloads in ESP ZNSP are similar to the data structure defined in `ZCL Command APIs <https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest/esp32/api-reference/zcl/esp_zigbee_zcl_command.html>`_

5.1.8.2 ZCL_ENDPOINT_ADD       
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Configures endpoint information on the NCP

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t     endpoint                  :  The application endpoint to be added                    |
|                        | uint16_t    profileId                 :  The endpoint's application profile                      |
|                        | uint16_t    deviceId                  :  The endpoint's device ID within the application profile |
|                        | uint8_t     appFlags                  :  The version and flags indicate description availability |
|                        | uint8_t     inputClusterCount         :  The number of cluster IDs in inputClusterList           |
|                        | uint8_t     outputClusterCount        :  The number of cluster IDs in outputClusterList          |
|                        | uint16_t[]  inputClusterList          :  Input cluster IDs the endpoint will accept              |
|                        | uint16_t[]  outputClusterList         :  Output cluster IDs the endpoint may send                |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.8.3 ZCL_ENDPOINT_DEL       
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Remove endpoint information on the NCP

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t     endpoint                  :  The application endpoint to be added                    |
|                        | uint16_t    profileId                 :  The endpoint's application profile                      |
|                        | uint16_t    deviceId                  :  The endpoint's device ID within the application profile |
|                        | uint8_t     appFlags                  :  The version and flags indicate description availability |
|                        | uint8_t     inputClusterCount         :  The number of cluster IDs in inputClusterList           |
|                        | uint8_t     outputClusterCount        :  The number of cluster IDs in outputClusterList          |
|                        | uint16_t[]  inputClusterList          :  Input cluster IDs the endpoint will accept              |
|                        | uint16_t[]  outputClusterList         :  Output cluster IDs the endpoint may send                |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.8.4 ZCL_ATTR_READ 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Read attribute data on NCP endpoints

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[8]  dst_addr                  : The single short address or group address                |
|                        | uint8_t   dst_endpoint                : Destination Endpoint ID                                  |
|                        | uint8_t   src_endpoint                : Source Endpoint ID                                       |
|                        | uint8_t   address_mode                : ZCL address mode                                         |
|                        | uint16_t  cluster                     : Cluster ID                                               |
|                        | uint8_t   attr_number                 : Attribute number                                         |
|                        | uint16_t[]  attributeId               : Attribute ID                                             |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t     status                : Status                                                       |
|                        | uint8_t     fc                    : A 8-bit Frame control                                        |
|                        | uint16_t    manuf_code            : Manufacturer code                                            |
|                        | uint8_t     tsn                   : Transaction sequence number                                  |
|                        | uint8_t     rssi                  : Signal strength                                              |
|                        | uint8_t     addr_type             : address type see esp_zb_zcl_address_type_t                   |
|                        | uint8_t[8]  device_addr           : Long address of device requested to leave device             |
|                        | uint16_t dst_address              : The destination short address of command                     |
|                        | uint8_t src_endpoint              : The source endpoint of command                               |
|                        | uint8_t dst_endpoint              : The destination endpoint of command                          |
|                        | uint16_t cluster                  : The cluster id for command                                   |
|                        | uint16_t profile                  : The application profile identifier                           |
|                        | uint8_t id                        : The command id                                               |
|                        | uint8_t direction                 : The command direction                                        |
|                        | uint8_t is_common                 : The command is common type                                   |
|                        | uint8_t   attr_number             : Attribute number                                             |
|                        | uint8_t attr_status               : The status of the read operation on this attribute           |
|                        | uint16_t  attributeId             : Attribute ID                                                 |
|                        | uint8_t   dataType                : Attribute data type                                          |
|                        | uint8_t   dataLength              : Attribute data length                                        |
|                        | uint8_t[] data                    : Attribute data                                               |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.8.5 ZCL_ATTR_WRITE
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Write attribute data on NCP endpoints

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[8]  dst_addr                  : The single short address or group address                |
|                        | uint8_t   dst_endpoint                : Destination Endpoint ID                                  |
|                        | uint8_t   src_endpoint                : Source Endpoint ID                                       |
|                        | uint8_t   address_mode                : ZCL address mode                                         |
|                        | uint16_t  cluster                     : Cluster ID                                               |
|                        | uint8_t   attr_number                 : Attribute number                                         |
|                        | uint16_t  attributeId                 : Attribute ID                                             |
|                        | uint8_t   dataType                    : Attribute data type                                      |
|                        | uint8_t   dataLength                  : Attribute data length                                    |
|                        | uint8_t[] data                        : Attribute data                                           |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t     status                : Status                                                       |
|                        | uint8_t     fc                    : A 8-bit Frame control                                        |
|                        | uint16_t    manuf_code            : Manufacturer code                                            |
|                        | uint8_t     tsn                   : Transaction sequence number                                  |
|                        | uint8_t     rssi                  : Signal strength                                              |
|                        | uint8_t     addr_type             : address type see esp_zb_zcl_address_type_t                   |
|                        | uint8_t[8]  device_addr           : Long address of device requested to leave device             |
|                        | uint16_t dst_address              : The destination short address of command                     |
|                        | uint8_t src_endpoint              : The source endpoint of command                               |
|                        | uint8_t dst_endpoint              : The destination endpoint of command                          |
|                        | uint16_t cluster                  : The cluster id for command                                   |
|                        | uint16_t profile                  : The application profile identifier                           |
|                        | uint8_t id                        : The command id                                               |
|                        | uint8_t direction                 : The command direction                                        |
|                        | uint8_t is_common                 : The command is common type                                   |
|                        | uint8_t   attr_number             : Attribute number                                             |
|                        | uint8_t attr_status               : The status of the read operation on this attribute           |
|                        | uint16_t  attributeId             : Attribute ID                                                 |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.8.6 ZCL_ATTR_REPORT        
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Report attribute data on NCP endpoints

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[8]  dst_addr                  : The single short address or group address                |
|                        | uint8_t   dst_endpoint                : Destination Endpoint ID                                  |
|                        | uint8_t   src_endpoint                : Source Endpoint ID                                       |
|                        | uint8_t   address_mode                : ZCL address mode                                         |
|                        | uint16_t  clusterID                   : Cluster ID to report                                     |
|                        | uint8_t   cluster_role                : Cluster role                                             |
|                        | uint16_t  attributeID                 : Attribute ID to report                                   |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t     status                : Status                                                       |
|                        | uint8_t     addr_type             : address type see esp_zb_zcl_address_type_t                   |
|                        | uint8_t[8]  device_addr           : Long address of device requested to leave device             |
|                        | uint8_t     src_endpoint          : The endpoint id which comes from report device               |
|                        | uint8_t     dst_endpoint          : The destination endpoint id                                  |
|                        | uint16_t    cluster               : The cluster id that reported                                 |
|                        | uint8_t     attr_number           : Attribute number                                             |
|                        | uint16_t    id                    : The identify of attribute                                    |
|                        | uint8_t     type                  : The type of attribute,                                       |
|                        | uint8_t     size                  : The value size of attribute                                  |
|                        | uint8_t[]   data                  : Attribute data                                               |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.8.7 ZCL_ATTR_DISC 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Discover attribute data on NCP endpoints

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[8]  dst_addr                  : The single short address or group address                |
|                        | uint8_t   dst_endpoint                : Destination Endpoint ID                                  |
|                        | uint8_t   src_endpoint                : Source Endpoint ID                                       |
|                        | uint8_t   address_mode                : ZCL address mode                                         |
|                        | uint16_t  cluster_id                  : The cluster identifier                                   |
|                        | uint16_t  start_attr_id               : The attribute identifier to begin the discover           |
|                        | uint8_t   max_attr_number             : The maximum number of attribute identifiers              |
|                        | uint8_t   direction                   : The command direction                                    |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t     status                : Status                                                       |
|                        | uint8_t     fc                    : A 8-bit Frame control                                        |
|                        | uint16_t    manuf_code            : Manufacturer code                                            |
|                        | uint8_t     tsn                   : Transaction sequence number                                  |
|                        | uint8_t     rssi                  : Signal strength                                              |
|                        | uint8_t     addr_type             : address type see esp_zb_zcl_address_type_t                   |
|                        | uint8_t[8]  device_addr           : Long address of device requested to leave device             |
|                        | uint16_t dst_address              : The destination short address of command                     |
|                        | uint8_t src_endpoint              : The source endpoint of command                               |
|                        | uint8_t dst_endpoint              : The destination endpoint of command                          |
|                        | uint16_t cluster                  : The cluster id for command                                   |
|                        | uint16_t profile                  : The application profile identifier                           |
|                        | uint8_t id                        : The command id                                               |
|                        | uint8_t direction                 : The command direction                                        |
|                        | uint8_t is_common                 : The command is common type                                   |
|                        | uint8_t     attr_number           : Attribute number                                             |
|                        | uint16_t    id                    : The identify of attribute                                    |
|                        | uint8_t     type                  : The type of attribute,                                       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.8.8 ZCL_READ  
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Read APS on NCP endpoints

5.1.8.9 ZCL_WRITE 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Write ZCL command on NCP endpoints

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[8]  dst_addr                  : The single short address or group address                |
|                        | uint8_t   dst_endpoint                : Destination Endpoint ID                                  |
|                        | uint8_t   src_endpoint                : Source Endpoint ID                                       |
|                        | uint8_t   address_mode                : ZCL address mode                                         |
|                        | uint16_t profile_id                   : Profile id                                               |
|                        | uint16_t cluster_id                   : Cluster id                                               |
|                        | uint16_t cmd_id                       : ZCL and custom command id                                |
|                        | uint8_t  direction                    : Direction of command                                     |
|                        | uint8_t   dataType                    : Command data type                                        |
|                        | uint8_t   dataLength                  : Command data length                                      |
|                        | uint8_t[] data                        : Command data                                             |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.8.10 ZCL_REPORT_CONFIG      
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Report configure on NCP endpoints

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[8]  dst_addr                  : The single short address or group address                |
|                        | uint8_t   dst_endpoint                : Destination Endpoint ID                                  |
|                        | uint8_t   src_endpoint                : Source Endpoint ID                                       |
|                        | uint8_t   address_mode                : ZCL address mode                                         |
|                        | uint16_t  cluster_id                  : The cluster identifier                                   |
|                        | uint16_t  record_number               : The Number of report configuration record                |
|                        | uint8_t direction                     : The direction of the attribute are reported operation    |
|                        | uint16_t attributeID                  : Attribute ID to report                                   |
|                        | uint8_t attrType                      : Attribute type to Report                                 |
|                        | uint16_t min_interval                 : Minimum reporting interval                               |
|                        | uint16_t max_interval                 : Maximum reporting interval                               |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t     status                : Status                                                       |
|                        | uint8_t     fc                    : A 8-bit Frame control                                        |
|                        | uint16_t    manuf_code            : Manufacturer code                                            |
|                        | uint8_t     tsn                   : Transaction sequence number                                  |
|                        | uint8_t     rssi                  : Signal strength                                              |
|                        | uint8_t     addr_type             : address type see esp_zb_zcl_address_type_t                   |
|                        | uint8_t[8]  device_addr           : Long address of device requested to leave device             |
|                        | uint16_t dst_address              : The destination short address of command                     |
|                        | uint8_t src_endpoint              : The source endpoint of command                               |
|                        | uint8_t dst_endpoint              : The destination endpoint of command                          |
|                        | uint16_t cluster                  : The cluster id for command                                   |
|                        | uint16_t profile                  : The application profile identifier                           |
|                        | uint8_t id                        : The command id                                               |
|                        | uint8_t direction                 : The command direction                                        |
|                        | uint8_t is_common                 : The command is common type                                   |
|                        | uint8_t     attr_number           : Attribute number                                             |
|                        | uint8_t attr_status               : The status of the reported operation on this attribute       |
|                        | uint8_t direction                 : The direction of the attribute are reported operation        |
|                        | uint16_t  attributeId             : Attribute ID                                                 |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.9 ZDO Frame ID Details
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

5.1.9.1 ZDO_BIND_SET  
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Create a binding between two endpoints on two nodes

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[8] src_address                : The IEEE address for the source                          |
|                        | uint8_t src_endp                      : The source endpoint for the binding entry                |
|                        | uint16_t cluster_id                   : The identifier of the cluster on the source device that  |
|                        |                                         is bound to the destination                              |
|                        | uint8_t dst_addr_mode                 : The destination address mode                             |
|                        | uint8_t[8] addr_short_long            : The destination address for the binding entry            |
|                        | uint8_t dst_endp                      : The destination endpoint for the binding entry           |
|                        | uint16_t req_dst_addr                 : Destination address of the request send to               |
|                        | uint32_t user_cb                      : A ZDO match desc request callback                        |
|                        | uint32_t user_ctx                     : User information context                                 |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t zdo_status                    : Status value indicating success or the reason for failure|
|                        | uint32_t user_cb                      : A ZDO match desc request callback                        |
|                        | uint32_t user_ctx                     : User information context                                 |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.9.2 ZDO_UNBIND_SET
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Remove a binding between two endpoints on two nodes

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[8] src_address                : The IEEE address for the source                          |
|                        | uint8_t src_endp                      : The source endpoint for the binding entry                |
|                        | uint16_t cluster_id                   : The identifier of the cluster on the source device that  |
|                        |                                         is bound to the destination                              |
|                        | uint8_t dst_addr_mode                 : The destination address mode                             |
|                        | uint8_t[8] addr_short_long            : The destination address for the binding entry            |
|                        | uint8_t dst_endp                      : The destination endpoint for the binding entry           |
|                        | uint16_t req_dst_addr                 : Destination address of the request send to               |
|                        | uint32_t user_cb                      : A ZDO match desc request callback                        |
|                        | uint32_t user_ctx                     : User information context                                 |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t zdo_status                    : Status value indicating success or the reason for failure|
|                        | uint32_t user_cb                      : A ZDO match desc request callback                        |
|                        | uint32_t user_ctx                     : User information context                                 |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.9.2 ZDO_FIND_MATCH
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Send match desc request to find matched Zigbee device

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint32_t user_cb                    : A ZDO match desc request callback                          |
|                        | uint32_t user_ctx                   : User information context                                   |
|                        | uint16_t dst_nwk_addr               : NWK address that request sent to                           |
|                        | uint16_t addr_of_interest           : NWK address of interest                                    |
|                        | uint16_t profile_id                 : Profile ID to be match at the destination                  |
|                        | uint8_t num_in_clusters             : The number of input clusters for matching cluster server   |
|                        | uint8_t num_out_clusters            : The number of output clusters for matching cluster client  |
|                        | uint16_t[] cluster_list             : The cluster ID with size num_in_clusters + num_out_clusters|
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t  zdo_status                 : The ZDO response status                                    |
|                        | uint16_t addr                       : A short address of the device response                     |
|                        | uint8_t  endpoint                   : An endpoint of the device response                         |
|                        | uint32_t user_cb                    : A ZDO match desc request callback                          |
|                        | uint32_t user_ctx                   : User information context                                   |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.10 APS Frame ID Details
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

5.1.10.1 APS_DATA_REQUEST
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Request the aps data

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        | uint8_t[8] dst_address                : The IEEE address for the source                          |
|                        | uint8_t dst_endpoint                  : The number of the individual endpoint                    |
|                        | uint8_t src_endpoint                  : The individual endpoint of the entity                    |
|                        | uint8_t dst_addr_mode                 : The destination address mode                             |
|                        | uint16_t profile_id                   : The profile id                                           |
|                        | uint16_t cluster_id                   : The cluster id                                           |
|                        | uint8_t tx_options                    : The transmission options for the ASDU to be transferred  |
|                        | bool use_alias                        : Use the UseAlias parameter to request                    |
|                        | uint8_t[8] alias_src_addr             : The source address to be used, If the use_alias is true  |
|                        | uint8_t alias_seq_num                 : The transmission options for the ASDU to be transferred  |
|                        | uint8_t radius                        : The distance that a transmitted frame to travel          |
|                        | uint32_t asdu_length                  : The number of octets comprising the ASDU being request   |
|                        | uint8_t asdu[]                        : The set of octets comprising the ASDU to be transferred  |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | esp_ncp_status_t status:         Status value indicating success or the reason for failure       |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.10.2 APS_DATA_INDICATION
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Indication the aps data

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t states;                     : The states of the device                                   |
|                        | uint8_t dst_addr_mode               : The dest addr mode used in this primitive and of the APDU  |
|                        | uint8_t[8] dst_addr                 : The individual device address or group address to directed |
|                        | uint8_t dst_endpoint                : The target endpoint on the local entity to directed        |
|                        | uint8_t src_addr_mode               : The source addr mode used in this primitive and of the APDU|
|                        | uint8_t[8] src_addr                 : The individual device address which the ASDU was received  |
|                        | uint8_t src_endpoint                : The individual endpoint number which the ASDU was received |
|                        | uint16_t profile_id                 : The identifier of the profile which this frame originated  |
|                        | uint16_t cluster_id                 : The identifier of the received cluster                     |
|                        | uint8_t indication_status           : The status of the incoming frame processing                |
|                        | uint8_t security_status             : The ASDU without any security or secured with NWK key      |
|                        | uint8_t lqi                         : The link quality indication delivered by the NLDE          |
|                        | uint32_t rx_time                    : The time indication for the received packet                |
|                        | uint32_t asdu_length                : The number of octets comprising the ASDU being indicated   |
|                        | uint8_t asdu[]                      : The set of octets comprising the ASDU to be indicated      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t states;                     : The states of the device                                   |
|                        | uint8_t dst_addr_mode               : The dest addr mode used in this primitive and of the APDU  |
|                        | uint8_t[8] dst_addr                 : The individual device address or group address to directed |
|                        | uint8_t dst_endpoint                : The target endpoint on the local entity to directed        |
|                        | uint8_t src_addr_mode               : The source addr mode used in this primitive and of the APDU|
|                        | uint8_t[8] src_addr                 : The individual device address which the ASDU was received  |
|                        | uint8_t src_endpoint                : The individual endpoint number which the ASDU was received |
|                        | uint16_t profile_id                 : The identifier of the profile which this frame originated  |
|                        | uint16_t cluster_id                 : The identifier of the received cluster                     |
|                        | uint8_t indication_status           : The status of the incoming frame processing                |
|                        | uint8_t security_status             : The ASDU without any security or secured with NWK key      |
|                        | uint8_t lqi                         : The link quality indication delivered by the NLDE          |
|                        | uint32_t rx_time                    : The time indication for the received packet                |
|                        | uint32_t asdu_length                : The number of octets comprising the ASDU being indicated   |
|                        | uint8_t asdu[]                      : The set of octets comprising the ASDU to be indicated      |
+------------------------+--------------------------------------------------------------------------------------------------+

5.1.10.3 APS_DATA_CONFIRM
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Confirm the aps data

+------------------------+--------------------------------------------------------------------------------------------------+
| Command Parameters:                                                                                                       |
|                        |        None                                                                                      |
+------------------------+--------------------------------------------------------------------------------------------------+
| Response Parameters:                                                                                                      |
|                        | uint8_t states;                     : The states of the device                                   |
|                        | uint8_t dst_addr_mode               : The dest addr mode used in this primitive and of the APDU  |
|                        | uint8_t[8] dst_address              : The IEEE address for the dest                              |
|                        | uint8_t dst_endpoint                : The individual endpoint of the dest                        |
|                        | uint8_t src_endpoint                : The individual endpoint of the source                      |
|                        | uint32_t tx_time                    : The time confirm for the transferred packet                |
|                        | uint8_t  confirm_status             : The status of data confirm                                 |
|                        | uint32_t asdu_length                : The number of octets comprising the ASDU being confirmed   |
|                        | uint8_t asdu[]                      : The set of octets comprising the ASDU to be confirm        |
+------------------------+--------------------------------------------------------------------------------------------------+
| Notify Parameters:                                                                                                        |
|                        | uint8_t states;                     : The states of the device                                   |
|                        | uint8_t dst_addr_mode               : The dest addr mode used in this primitive and of the APDU  |
|                        | uint8_t[8] dst_address              : The IEEE address for the dest                              |
|                        | uint8_t dst_endpoint                : The individual endpoint of the dest                        |
|                        | uint8_t src_endpoint                : The individual endpoint of the source                      |
|                        | uint32_t tx_time                    : The time confirm for the transferred packet                |
|                        | uint8_t  confirm_status             : The status of data confirm                                 |
|                        | uint32_t asdu_length                : The number of octets comprising the ASDU being confirmed   |
|                        | uint8_t asdu[]                      : The set of octets comprising the ASDU to be confirm        |
+------------------------+--------------------------------------------------------------------------------------------------+

.. note::
    * Command:  c0 00 00 09 00 09 07 00 00 00 14 00 00 00 00 FA 45 c0
    * Response: c0 10 00 09 00 09 01 00 00 99 00 c0
    * Notify:   c0 20 00 09 00 1a 0b 00 f7 39 f7 fe ff f9 55 60 4b fc 0d 20 00 c0
