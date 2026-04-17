Zigbee APS
----------

Overview
~~~~~~~~
The **Zigbee Application Support Sub-layer** (APS) acts as the interface between the network layer and the application layer. It provides a general set of services utilized by both the Zigbee Device Object (ZDO)
and manufacturer-defined  application objects. These services are provided through two main entities:

- **APS Data Entity (APSDE)**: Provides the data transmission service through its associated Service Access Point (SAP), known as the APSDE-SAP.

- **APS Management Entity (APSME)**: Offers the management service through its associated SAP, the APSME-SAP. The APSME also maintains a database of managed objects referred to as the APS Information Base (AIB).


APS Data Services
~~~~~~~~~~~~~~~~~
The **APSDE** provides a data service that enables both ZDO and application objects to transport application Protocol Data Units (PDU) between two or more devices at the network layer.


Functionalities
^^^^^^^^^^^^^^^
The **APSDE** provides the following functionalities:

- **Generation of the Application PDU**: The APSDE takes an application PDU and generates an APS PDU by adding the appropriate protocol overhead.
- **Binding**: Once two devices are bound, the APSDE can transfer a message from one bound device to the other.
- **Group Address Filtering**: Provides the ability to filter group-addressed messages based on endpoint group membership.
- **Reliable Transport**: Increases the reliability of transactions beyond what the NWK layer alone offers by employing end-to-end retries.
- **Duplicate Rejection**: Ensures messages offered for transmission are not received more than once.
- **Fragmentation**: Enables segmentation and reassembly of messages longer than the payload of a single NWK layer frame.


APIs Introduction
^^^^^^^^^^^^^^^^^
The ESP-Zigbee-SDK offers **APSDE-DATA.Request**, **APSDE-DATA.Confirm**, and **APSDE-DATA.Indication** primitives for user applications.

- **APSDE-DATA.Request**

  **APSDE-DATA.Request** facilitates the transfer of a Next Higher Layer Entity (NHLE) PDU (ASDU) from the local NHLE to one or more peer NHLEs,

  This primitive is implemented as :cpp:func:`ezb_aps_data_request` in the SDK. The function provides the capability to send user-customized
  APS packets to the remote device. The detailed description of its parameter :cpp:type:`ezb_apsde_data_req_t` can be found as reference.

- **APSDE-DATA.Confirm**

  **APSDE-DATA Confirm** reports the results of a request to transfer a data PDU (ASDU) from a local NHLE to one or more peer NHLEs.

  This primitive is implemented as a callback function of type :cpp:type:`ezb_apsde_data_confirm_callback_t` and can be
  registered to the Zigbee stack by :cpp:func:`ezb_apsde_data_confirm_handler_register`. When the **APSDE-DATA Request** has
  been confirmed by the remote device, the callback will be triggered. The detailed description of parameter
  :cpp:type:`ezb_apsde_data_confirm_t` can be found as reference.

- **APSDE-DATA.Indication**

  **APSDE-DATA Indication** indicates the transfer of a data PDU (ASDU) from the APS sub-layer to the local application entity.

  This primitive is implemented as a callback function of type :cpp:type:`ezb_apsde_data_indication_callback_t` and can be
  registered to the Zigbee stack by :cpp:func:`ezb_apsde_data_indication_handler_register`. When the local ASDE receives
  an APS data frame, the callback will be triggered. The user can then return ``true`` or ``false`` to indicate if the packet
  still needs to be handled by the stack. The detailed description of parameter :cpp:type:`ezb_apsde_data_ind_t` can be found
  as reference.

Typical Usage
^^^^^^^^^^^^^

If you are going to send a C-style string "hello espressif" via APS data service from a device with endpoint identifier (1)
to a remote device with short address (0x1234) and endpoint identifier (10), residing in a cluster identifier (0xFFC0),
the APS frame will be forwarded up to 2 hops and allowed to fragment if necessary. You can use the following code to
implement this function.

.. code-block:: c

    uint8_t asdu[] = "hello espressif";
    ezb_apsde_data_req_t req = {
        .dst_address = EZB_ADDRESS_SHORT(0x1234),
        .dst_endpoint = 10,

        .src_endpoint = 1,

        .profile_id = EZB_AF_HA_PROFILE_ID,
        .cluster_id = 0xFFC0,

        .tx_options = (EZB_APSDE_TX_OPT_ACK_TX | EZB_APSDE_TX_OPT_FRAG_PERMITTED),

        .radius = 2,

        .asdu_length = sizeof(asdu),
        .asdu = asdu,
    };

    esp_zigbee_lock_acquire(portMAX_DELAY);
    ezb_apsde_data_request(&req);
    esp_zigbee_lock_release();

If you want to confirm whether the request has been sent successfully, you can register a callback using
:cpp:func:`ezb_apsde_data_confirm_handler_register` and retrieve the confirmation information from the callback.

.. code-block:: c

    void zb_apsde_data_confirm_handler(const ezb_apsde_data_confirm_t *confirm)
    {
        if (confirm->status == 0x00) {
            ESP_LOGI("APSDE-DATA.Confirm",
                    "Sent successfully from endpoint %d, source address 0x%04hx to endpoint %d,"
                    "destination address 0x%04hx",
                    confirm->src_endpoint, ezb_nwk_get_short_address(),
                    confirm->dst_endpoint, confirm->dst_address.u.addr_short);
            ESP_LOG_BUFFER_CHAR_LEVEL("APSDE-DATA.Confirm", confirm->asdu, confirm->asdu_length, ESP_LOG_INFO);
        } else {
            ESP_LOGE("APSDE-DATA.Confirm", "Failed to send APS data frame, error code: %d", confirm->status);
        }
    }

The APS data frame send by **APSDE-DATA.Request** from a device can be intercepted and processed by registering a callback
using :cpp:func:`ezb_apsde_data_indication_handler_register` on the destination device. It's important to note that if the
returned value of ``zb_apsde_data_indication_handler()`` is ``false``, the Zigbee stack will continue to handle the APS data
frame. However, if it returns ``true``, the Zigbee stack will assume that the user has already processed the frame and will
skip the further processing.

.. code-block:: c

    bool zb_apsde_data_indication_handler(const ezb_apsde_data_ind_t *ind)
    {
        bool processed = false;
        if (ind->status == 0x00) {
            if (ind->dst_endpoint == 10 && ind->profile_id == EZB_AF_HA_PROFILE_ID && ind->cluster_id == 0xFFC0) {
                ESP_LOGI("APSDE-DATA.Indication",
                         "Received APS %s data frame from endpoint %d, source address 0x%04hx to "
                         "endpoint %d, destination address 0x%04hx",
                         ind->dst_address.addr_mode == EZB_APS_ADDR_MODE_16_GROUP_ENDP_NOT_PRESENT ? "group" : "unicast",
                         ind->src_endpoint, ind->src_address.u.addr_short, ind->dst_endpoint, ind->dst_address.u.addr_short);
                ESP_LOG_BUFFER_CHAR_LEVEL("APSDE-DATA.Indication", ind.asdu, ind.asdu_length, ESP_LOG_INFO);
                processed = true;
            }
        } else {
            ESP_LOGE("APSDE-DATA.Indication", "Invalid status of APSDE-DATA.Indication, error code: %d", ind.status);
            processed = false;
        }
        return processed;
    }


APS Management Services
~~~~~~~~~~~~~~~~~~~~~~~
The APS management entity SAP (APSME-SAP) provide a management service to allow an application to interact with the stack and the ability to match two devices together based on the services.


Functionalities
^^^^^^^^^^^^^^^

The APSME provides the following functionalities:

- **Binding Management**: Provides the ability to match two devices together based on their services and their needs.
- **AIB Management**: Provides the ability to get and set attributes in the device's AIB.
- **Security**:  Provides the ability to set up authentic relationships with other devices through the use of secure keys
- **Group Management**: Provides the ability to declare a single address shared by multiple devices, to add devices to the group, and to remove devices from the group.
