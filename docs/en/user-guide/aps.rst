5.2 Zigbee APS 
--------------


5.2.1. Overview
~~~~~~~~~~~~~~~
The **Zigbee Application Support Sub-layer** (APS) acts as the interface between the network layer and the application layer. It provides a general set of services utilized by both the Zigbee Device Object (ZDO)
and manufacturer-defined  application objects. These services are provided through two main entities:

- **APS Data Entity (APSDE)**: Provides the data transmission service through its associated Service Access Point (SAP), known as the APSDE-SAP.

- **APS Management Entity (APSME)**: Offers the management service through its associated SAP, the APSME-SAP. The APSME also maintains a database of managed objects referred to as the APS Information Base (AIB).


5.2.2. APS Data Services
~~~~~~~~~~~~~~~~~~~~~~~~
The **APSDE** provides a data service that enables both ZDO and application objects to transport application Protocol Data Units (PDU) between two or more devices at the network layer.


5.2.2.1 Functionalities
^^^^^^^^^^^^^^^^^^^^^^^
The **APSDE** provides the following functionalities:

- **Generation of the Application PDU**: The APSDE takes an application PDU and generates an APS PDU by adding the appropriate protocol overhead.
- **Binding**: Once two devices are bound, the APSDE can transfer a message from one bound device to the other.
- **Group Address Filtering**: Provides the ability to filter group-addressed messages based on endpoint group membership.
- **Reliable Transport**: Increases the reliability of transactions beyond what the NWK layer alone offers by employing end-to-end retries.
- **Duplicate Rejection**: Ensures messages offered for transmission are not received more than once.
- **Fragmentation**: Enables segmentation and reassembly of messages longer than the payload of a single NWK layer frame.


5.2.2.2 APIs Introduction
^^^^^^^^^^^^^^^^^^^^^^^^^
The ESP-Zigbee-SDK offers **APSDE-DATA.Request**, **APSDE-DATA.Confirm**, and **APSDE-DATA.Indication** interfaces for user applications.

- APSDE-DATA.Request

This **APSDE-DATA Request** facilitates the transfer of a Next Higher Layer Entity (NHLE) PDU from the local NHLE to one or more peer NHLEs.

.. code-block:: c

 esp_err_t esp_zb_aps_data_request(esp_zb_apsde_data_req_t *req);

This `esp_zb_aps_data_request <https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest/esp32/api-reference/aps/esp_zigbee_aps.html#_CPPv423esp_zb_aps_data_requestP23esp_zb_apsde_data_req_t>`__
provides the capability to send user-customized packets from the local to the remote. The detailed description of its parameter
`esp_zb_apsde_data_req_t <https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest/esp32/api-reference/aps/esp_zigbee_aps.html#_CPPv423esp_zb_apsde_data_req_s>`__ can be found as reference.

- APSDE-DATA.Confirm

The **APSDE-DATA Confirm** reports the results of a request to transfer a data PDU from a local NHLE to one or more peer NHLEs.

.. code-block:: c

    void esp_zb_aps_data_confirm_handler_register(esp_zb_apsde_data_confirm_callback_t cb);

    typedef void (* esp_zb_apsde_data_confirm_callback_t)(esp_zb_apsde_data_confirm_t confirm);

The ``esp_zb_apsde_data_confirm_callback_t`` can be registered by `esp_zb_aps_data_confirm_handler_register <https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest/esp32/api-reference/aps/esp_zigbee_aps.html#_CPPv440esp_zb_aps_data_confirm_handler_register36esp_zb_apsde_data_confirm_callback_t>`__,
When **APSDE-DATA Request** has been confirmed by the remote, the callback will be triggered. The detailed description of parameter
`esp_zb_apsde_data_confirm_t <https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest/esp32/api-reference/aps/esp_zigbee_aps.html#_CPPv427esp_zb_apsde_data_confirm_s>`__ can be found as reference.

- APSDE-DATA.Indication

This **APSDE-DATA Indication** indicates the transfer of a data PDU (ASDU) from the APS sub-layer to the local application entity.

.. code-block:: c

    void esp_zb_aps_data_indication_handler_register(esp_zb_apsde_data_indication_callback_t cb)

    typedef bool (* esp_zb_apsde_data_indication_callback_t)(esp_zb_apsde_data_ind_t ind);


The ``esp_zb_apsde_data_indication_callback_t`` can be registered by `esp_zb_aps_data_indication_handler_register <https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest/esp32/api-reference/aps/esp_zigbee_aps.html#_CPPv443esp_zb_aps_data_indication_handler_register39esp_zb_apsde_data_indication_callback_t>`__,
When the device receives an **APSDE-DATA Indication** packet, the callback will be triggered. The user can then return `TRUE` or `FALSE` to indicate whether the packet still needs to be handled by the stack.
The detailed description of parameter `esp_zb_apsde_data_ind_t <https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest/esp32/api-reference/aps/esp_zigbee_aps.html#_CPPv423esp_zb_apsde_data_ind_s>`__ can be found as reference

5.2.2.3 Typical Usage
^^^^^^^^^^^^^^^^^^^^^

If you expect a string "hello espressif" to be sent by the APS from a device with endpoint identifier (1) to a remote device  with a short address (0x1234) and endpoint identifier (10), residing in a
cluster identifier (0xFFC0), the APS frame will be forwarded up to 2 hops and allowed to fragment if necessary. You can use the following code to implement this function.

.. code-block:: c

    esp_zb_apsde_data_req_t req;
    uint8_t value[] = "hello espressif";
    req.dst_addr_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    req.dst_addr.addr_short = 0x1234;
    req.dst_endpoint = 10;
    req.profile_id = ESP_ZB_AF_HA_PROFILE_ID;
    req.cluster_id = 0xFFC0;
    req.src_endpoint = 1;
    req.asdu_length = sizeof(value);
    req.asdu = value;
    req.radius = 2;
    req.tx_options = (ESP_ZB_APSDE_TX_OPT_ACK_TX | ESP_ZB_APSDE_TX_OPT_FRAG_PERMITTED);
    req.use_alias = false;
    ESP_LOG_BUFFER_CHAR_LEVEL("APSDE REQUEST", req.asdu, req.asdu_length, ESP_LOG_INFO);
    esp_zb_lock_acquire(portMAX_DELAY);
    esp_zb_aps_data_request(&req);
    esp_zb_lock_release();



If you want to confirm whether the **APSDE-DATA.Request** has been sent successfully, you can register a callback using ``esp_zb_aps_data_confirm_handler_register(&zb_apsde_data_confirm_handler)``
and retrieve the confirmation information from the callback.

.. code-block:: c

    void zb_apsde_data_confirm_handler(esp_zb_apsde_data_confirm_t confirm)
    {
        if (confirm.status == 0x00) {
            ESP_LOGI("APSDE CONFIRM",
                    "Sent successfully from endpoint %d, source address 0x%04hx to endpoint %d,"
                    "destination address 0x%04hx",
                    confirm.src_endpoint, esp_zb_get_short_address(), confirm.dst_endpoint, confirm.dst_addr.addr_short);
            ESP_LOG_BUFFER_CHAR_LEVEL("APSDE CONFIRM", confirm.asdu, confirm.asdu_length, ESP_LOG_INFO);
        } else {
            ESP_LOGE("APSDE CONFIRM", "Failed to send APSDE-DATA request, error code: %d", confirm.status);
        }
    }


The **APSDE-DATA.Request** from a device can be intercepted and processed by registering a callback using ``esp_zb_aps_data_indication_handler_register(zb_apsde_data_indication_handler)`` on the
destination device. It's important to note that if the returned value of ``zb_apsde_data_indication_handler()`` is false, the Zigbee stack will continue to handle the APSDE-DATA frame. However,
if it returns true, the Zigbee stack will assume that the user has already processed the frame and will ignore it.

.. code-block:: c

    bool zb_apsde_data_indication_handler(esp_zb_apsde_data_ind_t ind)
    {
        bool processed = false;
        if (ind.status == 0x00) {
            if (ind.dst_endpoint == 10 && ind.profile_id == ESP_ZB_AF_HA_PROFILE_ID && ind.cluster_id == 0xFFC0) {
                ESP_LOGI("APSDE INDICATION",
                        "Received APSDE-DATA %s request with a length of %ld from endpoint %d, source address 0x%04hx to "
                        "endpoint %d, destination address 0x%04hx",
                        ind.dst_addr_mode == 0x01 ? "group" : "unicast", ind.asdu_length, ind.src_endpoint,
                        ind.src_short_addr, ind.dst_endpoint, ind.dst_short_addr);
                ESP_LOG_BUFFER_CHAR_LEVEL("APSDE INDICATION", ind.asdu, ind.asdu_length, ESP_LOG_INFO);
                processed = true;
            }
        } else {
            ESP_LOGE("APSDE INDICATION", "Invalid status of APSDE-DATA indication, error code: %d", ind.status);
            processed = false;
        }
        return processed;
    }


5.2.3. APS Management Services
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The APS management entity SAP (APSME-SAP) provide a management service to allow an application to interact with the stack and the ability to match two devices together based on the services.


5.2.3.1 Functionalities
^^^^^^^^^^^^^^^^^^^^^^^

The APSME provides the following functionalities:

- **Binding Management**: Provides the ability to match two devices together based on their services and their needs.
- **AIB Management**: Provides the ability to get and set attributes in the device’s AIB
- **Security**:  Provides the ability to set up authentic relationships with other devices through the use of secure keys
- **Group Management**: Provides the ability to declare a single address shared by multiple devices, to add devices to the group, and to remove devices from the group.

