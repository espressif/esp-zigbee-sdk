2. Developing with ESP Zigbee SDK
=================================

Please refer the :project_file:`Release Notes <RELEASE_NOTES.txt>` to know more about ESP Zigbee SDK releases. Check :project_file:`README <README.md>` to know more details.

2.1 Development Setup
---------------------

This section talks about setting up your development environment, fetching the Git repositories, and instructions to build and flash.


2.1.1 Setting up the Repositories
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Clone the `esp-idf <https://github.com/espressif/esp-idf>`_ and the `esp-zigbee-sdk <https://github.com/espressif/esp-zigbee-sdk>`_ repository.

.. code-block:: bash

   git clone https://github.com/espressif/esp-idf.git


.. code-block:: bash

   git clone --recursive https://github.com/espressif/esp-zigbee-sdk.git


Follow the `ESP-IDF getting started guide <https://idf.espressif.com/>`_ to set up the IDF development environment.


2.1.2 Building Applications on esp-idf (Option)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Build following examples in the esp-idf environment

- `Zigbee_example <https://github.com/espressif/esp-idf/blob/master/examples/zigbee>`__

2.1.3 Building Applications on esp-zigbee-sdk (Recommended)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Build following examples in the esp-zigbee-sdk environment which implemented with provided SDK's API

-  :project:`esp_zigbee_HA_sample <examples/esp_zigbee_HA_sample>`
-  :project:`esp_zigbee_customized_client_devices <examples/esp_zigbee_customized_devices/customized_client>`
-  :project:`esp_zigbee_customized_client_server <examples/esp_zigbee_customized_devices/customized_server>`
-  :project:`esp_zigbee_gateway <examples/esp_zigbee_gateway>`
-  :project:`esp_zigbee_rcp <examples/esp_zigbee_rcp>`

2.1.4 Flashing the Firmware
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Choose IDF target.

.. only:: esp32

   ::

      idf.py set-target {IDF_TARGET_PATH_NAME}

.. only:: esp32c3

   ::

      idf.py set-target {IDF_TARGET_PATH_NAME}
      
.. only:: esp32s3

   ::

      idf.py set-target {IDF_TARGET_PATH_NAME}

.. only:: esp32h4

   ::

      idf.py --preview set-target {IDF_TARGET_PATH_NAME}

-  If IDF target has not been set explicitly, then ``esp32`` is
   considered as default.


(When flashing the SDK for the first time, it is recommended to do
``idf.py -p PORT erase-flash`` to wipe out entire flash and start out fresh.)

::

   idf.py -p PORT flash monitor


2.2 Running example
--------------------

See the examples readme for more details: :project_file:`README <examples/README.md>`

2.3 Developing your Product
---------------------------

2.3.1 Data Model
~~~~~~~~~~~~~~~~

Understanding the structure before actually modifying and customizing
the device is helpful.

.. figure:: ../_static/datamodel.png
    :align: center
    :alt: ESP Zigbee Data Model
    :figclass: align-center
    
Node
^^^^
A node is a single ESP32-H4 based product. It represents a network node in the Zigbee network. A single node can expose multiple endpoints.

Endpoints
^^^^^^^^^

Within each node are endpoints. Endpoints, identified by a number between 1 and 240, define each application running in a ZigBee node (yes, a single ZigBee node can run multiple applications).
Endpoints serve three purposes in ZigBee:

- Endpoints allow for different application profiles to exist within each node.
- Endpoints allow for separate control points to exist within each node.
- Endpoints allow for separate devices to exist within each node.

Clusters
^^^^^^^^

Clusters, defined by a 16-bit identifier, are application objects. Whereas the NwkAddr and endpoint are addressing concepts, the cluster defines application meaning.

- An endpoint can have multiple clusters.
- Clusters, in addition to the identifier, have direction. In the SimpleDescriptor which describes an endpoint, a cluster is listed as either input or output.
- Clusters contain both code (commands) and data (attributes). Commands cause action. Attributes keep track of the current state of that cluster.

Attributes
^^^^^^^^^^

Attributes are identified by a 16-bit number, store the current “state” of a given cluster. A data entity which represents a physical quantity or state.

- A cluster can have multiple attributes.
- There are generic ZCL commands to read and write attributes on any given cluster.
- Attributes can even be set up to report automatically at regular intervals, if they change, or both.


2.3.2 A HA_on_off_light example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section demonstrates how a Home Automation (HA) on_off_light example creates as reference.

See example: :project_file:`HA_on_off_light <examples/esp_zigbee_HA_sample/HA_on_off_light/main/esp_zb_light.c>`

2.3.2.1 Data Model
^^^^^^^^^^^^^^^^^^
In the standard HA_on_off_light example, we use :cpp:func:`esp_zb_on_off_light_ep_create` to create a HA on off single endpoint.

Data model looks like:

.. figure:: ../_static/HA_on_off_light.png
    :align: center
    :alt: ESP Zigbee Data Model
    :figclass: align-center

Above is the endpoint list we created, then we use :cpp:func:`esp_zb_device_register` to register a Zigbee device.


2.3.2.2 Attribute Callback
^^^^^^^^^^^^^^^^^^^^^^^^^^

An attribute change callback is registered in :cpp:func:`esp_zb_device_add_set_attr_value_cb` to allow user get notification that certain attributes has changed.

It depends on user how to process those attribute changes based on different circumstances, see the example to handle on_off LED light.

.. code-block:: c

   void attr_cb(uint8_t status, uint8_t endpoint, uint16_t cluster_id, uint16_t attr_id, void *new_value)
   {
    if (cluster_id == ZB_ZCL_CLUSTER_ID_ON_OFF) {
        uint8_t value = *(uint8_t*)new_value;
        if (attr_id == ZB_ZCL_ATTR_ON_OFF_ON_OFF_ID) {
            /* implemented light on/off control */
            ESP_LOGI(TAG, "on/off light set to %hd", value);
            light_driver_set_power((bool)value);
        }
    } else {
        /* Implement some actions if needed when other cluster changed */
        ESP_LOGI(TAG, "cluster:0x%x, attribute:0x%x changed ", cluster_id, attr_id);
    }
   }


2.3.2.3 Zigbee stack Configuring and starting
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
In this example, a Zigbee end-device is configured to HA_on_off_light. :c:macro:`ESP_ZB_ZED_CONFIG()` , see :cpp:type:`esp_zb_cfg_t` definition in the API reference chapter below.

Initialize Zigbee stack by using :cpp:func:`esp_zb_init`, start Zigbee stack by using :cpp:func:`esp_zb_start` and main loop of the Zigbee stack by using :cpp:func:`esp_zb_main_loop_iteration`.

After Zigbee stack is running, by checking different signals that stack provided, user could start BDB commissioning by using :cpp:func:`esp_zb_bdb_start_top_level_commissioning`.

2.3.3 A HA_on_off_switch example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section demonstrates how a Home Automation (HA) on_off_switch example creates as reference.

See example: :project_file:`HA_on_off_switch <examples/esp_zigbee_HA_sample/HA_on_off_switch/main/esp_zb_switch.c>`


2.3.2.1 Data Model
^^^^^^^^^^^^^^^^^^
In the standard HA_on_off_light example, we use :cpp:func:`esp_zb_on_off_switch_ep_create` to create a HA on off single endpoint.

Data model looks like:

.. figure:: ../_static/HA_on_off_switch.png
    :align: center
    :alt: ESP Zigbee Data Model
    :figclass: align-center

Above is the endpoint list we created, then we use :cpp:func:`esp_zb_device_register` to register a Zigbee device.

2.3.2.2 ZCL commands
^^^^^^^^^^^^^^^^^^^^
Varieties of ZCL commands is provided in the :project_file:`esp_zigbee_zcl_command <components/esp-zigbee-lib/include/esp_zigbee_zcl_command.h>`.

In this example we demonstrate a ZCL on_off_toggle command.

After button on the board is pressed, the :cpp:func:`esp_zb_buttons_handler` creates a on_off toggle command :cpp:func:`esp_zb_zcl_on_off_cmd_req`. The user has to provide a remote node endpoint, local node endpoint, destination short address, and command type to pack the command request. See :cpp:type:`esp_zb_zcl_on_off_cmd_t`.

.. code-block:: c

   static void esp_zb_buttons_handler(switch_func_pair_t *button_func_pair)
   {
       if (button_func_pair->func == SWITCH_ONOFF_TOGGLE_CONTROL) {
           /* implemented light switch toggle functionality */
           esp_zb_zcl_on_off_cmd_t cmd_req;
           cmd_req.zcl_basic_cmd.dst_addr_u.addr_short = on_off_light.short_addr;
           cmd_req.zcl_basic_cmd.dst_endpoint = on_off_light.endpoint;
           cmd_req.zcl_basic_cmd.src_endpoint = HA_ONOFF_SWITCH_ENDPOINT;
           cmd_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
           cmd_req.on_off_cmd_id = ZB_ZCL_CMD_ON_OFF_TOGGLE_ID;
           ESP_EARLY_LOGI(TAG, "send 'on_off toggle' command");
           esp_zb_zcl_on_off_cmd_req(&cmd_req);
       }
   }

2.3.2.3 Zigbee stack Configuring and starting
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
In this example, a Zigbee coordinator is configured to HA_on_off_switch. :c:macro:`ESP_ZB_ZC_CONFIG()`, see :cpp:type:`esp_zb_cfg_t` definition in the API reference chapter below.

Initialize Zigbee stack by using :cpp:func:`esp_zb_init`, start Zigbee stack by using :cpp:func:`esp_zb_start` and main loop of the Zigbee stack by using :cpp:func:`esp_zb_main_loop_iteration`.

After Zigbee stack is running, by checking different signals that stack provided, user could start BDB commissioning by using :cpp:func:`esp_zb_bdb_start_top_level_commissioning`.

.. todo::
   2.3.4 Adding customized devices
