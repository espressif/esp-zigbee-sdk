Zigbee Cluster Library (ZCL)
----------------------------

In ESP Zigbee SDK v2.x, the Zigbee Cluster Library (ZCL) APIs are redesigned for flexibility and easier use.
Besides the namespace changes, the functions, types, enums and fields of structures are renamed to clearer,
more understandable names. The APIs related to specific clusters are moved to the corresponding cluster
header file. Here is a description of the general changes of the ZCL APIs, for details of the new interfaces,
see :doc:`/api-reference/esp_zigbee_core/zcl/index`.

Data Model
^^^^^^^^^^

The data model APIs are redesigned to make the hierarchy of the ZCL data model clearer.

.. list-table:: **ZCL Data Model: Device**
    :header-rows: 1
    :align: center

    * -
      - v1.x
      - v2.x
    * - Type
      - ``esp_zb_ep_list_t``
      - :cpp:type:`ezb_af_device_desc_t`
    * - Create
      - ``esp_zb_ep_list_create()``
      - :cpp:func:`ezb_af_create_device_desc`
    * - Delete
      - N/A
      - :cpp:func:`ezb_af_free_device_desc`
    * - Add Endpoint
      - ``esp_zb_ep_list_add_ep()``
        ``esp_zb_ep_list_add_gateway_ep()``
      - :cpp:func:`ezb_af_device_add_endpoint_desc`
    * - Get Endpoint
      - ``esp_zb_ep_list_get_ep()``
      - :cpp:func:`ezb_af_device_get_endpoint_desc`
    * - Register
      - ``esp_zb_af_device_register()``
      - :cpp:func:`ezb_af_device_desc_register`


.. list-table:: **ZCL Data Model: Endpoint**
    :header-rows: 1
    :align: center

    * -
      - v1.x
      - v2.x
    * - Type
      - ``esp_zb_cluster_list_t``
      - :cpp:type:`ezb_af_ep_desc_t`
    * - Create
      - ``esp_zb_zcl_cluster_list_create()``
      - :cpp:func:`ezb_af_create_endpoint_desc`
        :cpp:func:`ezb_af_create_gateway_endpoint`
    * - Delete
      - N/A
      - :cpp:func:`ezb_af_free_endpoint_desc`
    * - Add Cluster
      - ``esp_zb_cluster_list_add_{cluster}_cluster()``
      - :cpp:func:`ezb_af_endpoint_add_cluster_desc`
    * - Get Cluster
      - ``esp_zb_cluster_list_get_cluster()``
      - :cpp:func:`ezb_af_endpoint_get_cluster_desc`
    * - Update Cluster
      - ``esp_zb_cluster_list_update_cluster()``
      - N/A


.. list-table:: **ZCL Data Model: Cluster**
    :header-rows: 1
    :align: center

    * -
      - v1.x
      - v2.x
    * - Type
      - ``esp_zb_attribute_list_t``
      - :cpp:type:`ezb_zcl_cluster_desc_t`
    * - Create
      - ``esp_zb_zcl_attr_list_create()``
        ``esp_zb_{cluster}_cluster_create()``
      - ``ezb_zcl_{cluster}_create_cluster_desc()``
    * - Delete
      - N/A
      - :cpp:func:`ezb_zcl_free_cluster_desc`
    * - Get
      - ``esp_zb_zcl_get_cluster()``
      - :cpp:func:`ezb_zcl_get_cluster_desc`
    * - Add Attribute
      - ``esp_zb_cluster_add_attr()``
        ``esp_zb_cluster_add_manufacturer_attr()``
        ``esp_zb_custom_cluster_add_custom_attr()``
        ``esp_zb_{cluster}_cluster_add_attr()``
      - :cpp:func:`ezb_zcl_cluster_add_attr_desc`
        ``ezb_zcl_{cluster}_cluster_desc_add_attr()``
        :cpp:func:`ezb_zcl_cluster_desc_add_manuf_attr`
    * - Get Attribute
      - N/A
      - :cpp:func:`ezb_zcl_cluster_get_attr_desc`
    * - Update Attribute
      - ``esp_zb_cluster_update_attr()``
      - N/A


.. list-table:: **ZCL Data Model: Attribute**
    :header-rows: 1
    :align: center

    * -
      - v1.x
      - v2.x
    * - Type
      - ``esp_zb_zcl_attr_t``
      - :cpp:type:`ezb_zcl_attr_desc_t`
    * - Create
      - N/A
      - :cpp:func:`ezb_zcl_create_attr_desc`
    * - Delete
      - N/A
      - :cpp:func:`ezb_zcl_free_attr_desc`
    * - Get
      - ``esp_zb_zcl_get_attribute()``
        ``esp_zb_zcl_get_manufacturer_attribute()``
      - :cpp:func:`ezb_zcl_get_attr_desc`
    * - Set Value
      - ``esp_zb_zcl_set_attribute_val()``
        ``esp_zb_zcl_set_manufacturer_attribute_val()``
      - :cpp:func:`ezb_zcl_set_attr_value`


ZCL Commands
^^^^^^^^^^^^

The ZCL command APIs are renamed to follow the convention: ``ezb_zcl_{cluster}_{command}_cmd_req()``.
The command request structures now share the same structure: :cpp:type:`ezb_zcl_cluster_cmd_ctrl_t`, in which you can
specify the confirm information to get the transmission result of the command, and the ``ezb_err_t`` is used as the return
value rather than the transaction sequence number.  The ``profile_id`` field is removed from this structure, the profile id
is determined by the profile id of the source endpoint specified by ``src_ep``.

An important behavior change is that the command APIs now require the data model to exist on the device. This includes
the correct role of the correct cluster in the source endpoint. For example, to send the ``OnOff On`` command, you need
to ensure the **``OnOff``** **client** cluster is added to the **source endpoint** before calling the command API.

If you want to send an arbitrary command without the cluster data model (typically for gateway usage), you can add
a special gateway endpoint to the device. The check of the cluster data model would be skipped if the transmission
request is from/to a gateway endpoint.

ZCL Messages
^^^^^^^^^^^^

The ZCL messages are reported via core action callback, as in v1.x. The definition of the message structure
of each core action is defined in separate header files of each cluster. Generally, the message contains a common
``info`` field which contains the rx information of the message, ``in`` field which contains the input data of the message,
and ``out`` field which contains the output data of the message (always response payload of the request).

ZCL Clusters
^^^^^^^^^^^^

The v2.x implementation aims to conform to the ZCL specification as much as possible, so several behavior changes have
been introduced. The list below highlights the changes for commonly used clusters. For more details, see the API references
of corresponding cluster header files.

- An important change for all clusters is that clusters on different endpoints are implemented as separate instances and
  would not affect each other.

On/Off
~~~~~~

- The ``esp_zb_zcl_on_off_cmd_req`` API has been split into three APIs:

    - :cpp:func:`ezb_zcl_on_off_off_cmd_req`
    - :cpp:func:`ezb_zcl_on_off_on_cmd_req`
    - :cpp:func:`ezb_zcl_on_off_toggle_cmd_req`

Scenes
~~~~~~

- The scenes table is maintained separately for each Scenes cluster instance, and the size is configured by
  :cpp:member:`ezb_zcl_scenes_cluster_server_config_s::scene_table_size` when the Scenes cluster is created
  using the :cpp:func:`ezb_zcl_scenes_create_cluster_desc` API.

Time
~~~~

- The Time cluster server now requires a time interface to get/set the current UTC time, which can be registered by
  :cpp:func:`ezb_zcl_time_server_interface_register`. The interface is used to synchronize the time attribute of the
  cluster with system RTC timer.

- The :cpp:func:`ezb_zcl_time_server_synchronize_time` API is provided to discover and synchronize with other Time servers
  on the network. The server preference is determined based on the ranking of the ``time status`` attribute as defined in
  the ZCL specification.

Color Control
~~~~~~~~~~~~~

- ``EZB_ZCL_CORE_COLOR_CONTROL_COLOR_MODE_CHANGE_CB_ID`` core action is introduced to notify the user of the color mode change.
  It allows the user to provide the customized color value conversion logic during the color mode change.

Thermostat
~~~~~~~~~~

- The :cpp:func:`ezb_zcl_thermostat_set_weekly_schedule_cmd_req` API allows adding multiple schedule entries (up to 10)
  in a single command.

- The :cpp:func:`ezb_zcl_thermostat_get_weekly_schedule_cmd_req` API does not support multiple days mode.

OTA_Upgrade
~~~~~~~~~~~

OTA Upgrade cluster has been redesigned to simplify the handling and management of OTA files for the OTA Upgrade cluster server.
The new implementation only performs the OTA file delivery (on the server side) and download (on the client side). The application
shall parse, verify and apply the OTA file itself. See our :example:`OTA examples <ota_upgrade/>` for more details.

- The user can add/remove OTA files to an OTA Upgrade server using :cpp:func:`ezb_zcl_ota_upgrade_add_ota_file` and
  :cpp:func:`ezb_zcl_ota_upgrade_remove_ota_file`. The server will respond to the client's query request and start the
  transmission of the OTA file. The user only needs to monitor the server-side OTA progress via the core action
  ``EZB_ZCL_CORE_OTA_UPGRADE_SERVER_PROGRESS_CB_ID``.

- The entire OTA file is passed to the user through the core action ``EZB_ZCL_CORE_OTA_UPGRADE_CLIENT_PROGRESS_CB_ID`` during the
  OTA upgrade process. The user can parse, verify and apply the OTA file itself according to the OTA file format defined in the ZCL
  specification.

- ``esp_zb_zcl_ota_upgrade_server_variable_t`` and ``esp_zb_zcl_ota_upgrade_client_variable_t`` are removed; please use APIs to
  configure the OTA server and client variables respectively (e.g. :cpp:func:`ezb_zcl_ota_upgrade_set_download_block_size`
  and :cpp:func:`ezb_zcl_ota_upgrade_set_hw_version`).

- The following core actions are removed:

    - ``ESP_ZB_CORE_OTA_UPGRADE_SRV_QUERY_IMAGE_CB_ID``, please handle the ``EZB_ZCL_OTA_UPGRADE_PROGRESS_START`` event of
      ``EZB_ZCL_CORE_OTA_UPGRADE_SERVER_PROGRESS_CB_ID`` core action.
    - ``ESP_ZB_CORE_OTA_UPGRADE_SRV_STATUS_CB_ID``, please handle the ``EZB_ZCL_OTA_UPGRADE_PROGRESS_FINISH`` event of
      ``EZB_ZCL_CORE_OTA_UPGRADE_SERVER_PROGRESS_CB_ID`` core action.
    - ``ESP_ZB_CORE_OTA_UPGRADE_VALUE_CB_ID``, please handle the ``EZB_ZCL_OTA_UPGRADE_PROGRESS_RECEIVING`` event of
      ``EZB_ZCL_CORE_OTA_UPGRADE_CLIENT_PROGRESS_CB_ID`` core action.

Poll Control
~~~~~~~~~~~~

- The configuration attributes of Poll Control are no longer stored persistently by the stack. Instead, these attributes
  will report their value change via ``EZB_ZCL_CORE_SET_ATTR_VALUE_CB_ID``, in which the user can save the values and
  restore them across device reboots.

Custom Cluster
~~~~~~~~~~~~~~

- The implementation of custom cluster has been redesigned in a more flexible manner, which allows the user to fully customize its
  behavior by registering handlers by :cpp:func:`ezb_zcl_custom_cluster_handlers_register`. As a result, ``CUSTOM_CLUSTER_REQ_CB_ID``
  and ``CUSTOM_CLUSTER_RESP_CB_ID`` core actions have been removed.

Home Automation (HA)
^^^^^^^^^^^^^^^^^^^^

The Home Automation (HA) APIs are updated to Zigbee Home Automation Specification, Revision 29, Version 1.2.
The default clusters included in the HA device endpoint are aligned to only mandatory clusters defined in the specification.
For more details, see :doc:`/introduction`.

The APIs (``esp_zb_{device_type}_ep_create()``) that create the device(endpoint list) with single HA device endpoint
are removed. The APIs (``esp_zb_{device_type}_clusters_create()``) that create the HA device endpoint are replaced by
``ezb_zha_create_{device_type}`` APIs under the new data model framework.
