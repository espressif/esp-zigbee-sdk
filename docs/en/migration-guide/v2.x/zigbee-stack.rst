Zigbee Stack
------------

In the following sections, unless otherwise specified, the general rules are:

  - changes the prefix from ``esp_zb_`` to ``ezb_``
  - changes the error code type from ``esp_err_t`` to ``ezb_err_t`` if used / returned.

.. contents::
    :local:
    :depth: 1

ZDO (Zigbee Device Object)
^^^^^^^^^^^^^^^^^^^^^^^^^^

In ``zdo/esp_zigbee_zdo_common.h``:

- The following types and enumerator values are moved to :component_file:`ezbee/zdo/zdo_type.h <esp-zigbee-lib/include/ezbee/zdo/zdo_type.h>`:

    - ``esp_zb_zdp_status_t`` and renamed to ``ezb_zdp_status_t``
    - ``ESP_ZB_ZDP_STATUS_*`` and renamed to ``EZB_ZDP_STATUS_*``

- Otherwise, the remainings are expected to related with Zigbee application signals and moved to
  :component_file:`ezbee/app_signals.h <esp-zigbee-lib/include/ezbee/app_signals.h>`.

    - The following types, enumerator values are renamed except for the renaming rule:

        - Rename ``ESP_ZB_NLME_STATUS_INDICATION`` to ``EZB_NWK_SIGNAL_NETWORK_STATUS``
        - Rename ``ESP_ZB_ZDO_TC_ACTION_AUTHORIZE`` to ``EZB_ZDO_TC_ACTION_ACCEPT``
        - Rename ``esp_zb_zdo_update_dev_tc_action_t`` to ``ezb_zdo_tc_action_t``
        - Rename ``ESP_ZB_ZDO_STANDARD_DEV_SECURED_REJOIN`` to ``EZB_ZDO_UPDDEV_SECURE_REJOIN``
        - Rename ``ESP_ZB_ZDO_STANDARD_DEV_UNSECURE_JOIN`` to ``EZB_ZDO_UPDDEV_UNSECURE_JOIN``
        - Rename ``ESP_ZB_ZDO_STANDARD_DEV_DEVICE_LEFT`` to ``EZB_ZDO_UPDDEV_DEVICE_LEFT``
        - Rename ``ESP_ZB_ZDO_STANDARD_DEV_TC_REJOIN`` to ``EZB_ZDO_UPDDEV_TC_REJOIN``
        - Rename ``esp_zb_zdo_update_dev_status_t`` to ``ezb_zdo_upddev_status_t``
        - Rename ``esp_zb_zdo_signal_nwk_status_indication_params_t`` to ``ezb_nwk_signal_network_status_params_t``
        - Rename ``esp_zb_zdo_signal_to_string()`` to ``ezb_app_signal_to_string()``

    - ``esp_zb_app_signal_t`` is renamed to ``ezb_app_signal_t``, and changed to a opaque type. Please use
      :cpp:func:`ezb_app_signal_get_type` and :cpp:func:`ezb_app_signal_get_params` to access the signal type and parameters.

    - The application signal handler now SHALL be registered with :cpp:func:`ezb_app_signal_add_handler` and can be removed with
      :cpp:func:`ezb_app_signal_remove_handler`.

In ``zdo/esp_zigbee_zdo_command.h``:

- The following functions are moved to :component_file:`ezbee/app_signals.h <esp-zigbee-lib/include/ezbee/app_signals.h>`:

    - ``esp_zb_zdo_signal_to_string()`` and renamed to ``ezb_app_signal_to_string()``

- The Active Scan and Energy Detect scan are now provided by :cpp:func:`ezb_nwk_scan`, see :cpp:type:`ezb_nwk_scan_req_t` for details.
  Therefore, the following functions are removed:

    - ``esp_zb_zdo_active_scan_request()``, ``esp_zb_zdo_scan_complete_callback_t``, ``esp_zb_network_descriptor_t``
    - ``esp_zb_zdo_energy_detect_request()``, ``esp_zb_zdo_energy_detect_callback_t``, ``esp_zb_energy_detect_channel_info_t``

- The following macros are removed:

    - ``ESP_ZB_MATCH_DESC_REQ_ROLE``
    - ``ESP_ZB_MATCH_DESC_REQ_TIMEOUT``
    - ``ESP_ZB_IEEE_ADDR_REQ_TIMEOUT``
    - ``ESP_ZB_NWK_ADDR_REQ_TIMEOUT``
    - ``ESP_ZB_NODE_DESC_REQ_TIMEOUT``
    - ``ESP_ZB_BIND_DEVICE_REQ_TIMEOUT``
    - ``ESP_ZB_ACTIVE_EP_REQ_TIMEOUT``
    - ``ESP_ZB_SIMPLE_DESC_REQ_TIMEOUT``
    - ``ESP_ZB_PERMIT_JOIN_REQ_TIMEOUT``
    - ``ESP_ZB_DEVICE_LEAVE_REQ_TIMEOUT``
    - ``ESP_ZB_DEVICE_BIND_TABLE_REQ_TIMEOUT``
    - ``ESP_ZB_DEVICE_MGMT_LQI_REQ_TIMEOUT``
    - ``ESP_ZB_POWER_DESC_REQ_TIMEOUT``
    - ``ESP_ZB_NWK_UPDATE_REQ_TIMEOUT``

- Otherwise, the remainings are expected to related with Zigbee Device Object commands and moved to
  :component_file:`ezbee/zdo/zdo_dev_srv_disc.h <esp-zigbee-lib/include/ezbee/zdo/zdo_dev_srv_disc.h>`,
  :component_file:`ezbee/zdo/zdo_bind_mgmt.h <esp-zigbee-lib/include/ezbee/zdo/zdo_bind_mgmt.h>`, and
  :component_file:`ezbee/zdo/zdo_nwk_mgmt.h <esp-zigbee-lib/include/ezbee/zdo/zdo_nwk_mgmt.h>` respectively.
  Please refer to the :doc:`API reference </api-reference/esp_zigbee_core/zdo>` for details.

APS (Application Support Sub-layer)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The header file of the APS layer is changed from ``aps/esp_zigbee_aps.h`` to
:component_file:`ezbee/aps.h <esp-zigbee-lib/include/ezbee/aps.h>`.

The following macros, types, and functions have been renamed:

- Rename ``esp_zb_apsde_data_req_t`` to ``ezb_apsde_data_req_t`` with field changes:

    - remove ``use_alias``, add ``EZB_APSDE_TX_OPT_USE_ALIAS`` to ``tx_options`` instead.
    - remove ``dst_addr_mode`` and ``dst_addr``, use ``dst_address`` instead. See :cpp:type:`ezb_address_t`.

- Rename ``esp_zb_aps_data_confirm`` to ``ezb_apsde_data_confirm`` with field changes:

    - remove ``dst_addr_mode`` and ``dst_short_addr``, use ``dst_address`` instead. See :cpp:type:`ezb_address_t`.
    - change the type of ``asdu_length`` from ``uint32_t`` to ``uint16_t``
    - remove ``tx_time``

- Rename ``esp_zb_aps_data_indication`` to ``ezb_apsde_data_indication`` with field changes:

    - remove ``dst_addr_mode`` and ``dst_short_addr``, use ``dst_address`` instead. See :cpp:type:`ezb_address_t`.
    - remove ``src_addr_mode`` and ``src_short_addr``, use ``src_address`` instead. See :cpp:type:`ezb_address_t`.
    - change the type of ``asdu_length`` from ``uint32_t`` to ``uint16_t``
    - remove ``rx_time`` / ``security_status``

- Rename ``esp_zb_aps_data_request`` to ``ezb_apsde_data_request``
- Rename ``esp_zb_aps_data_indication_handler_register`` to ``ezb_apsde_data_indication_handler_register``
- Rename ``esp_zb_aps_data_confirm_handler_register`` to ``ezb_apsde_data_confirm_handler_register``

The following macros, types, and functions have been removed:

- ``ESP_ZB_APS_ADDR_MODE_64_PRESENT_ENDP_NOT_PRESENT``
- ``ESP_ZB_APSDE_TX_OPT_NO_LONG_ADDR``
- ``esp_zb_apsme_transport_key_req_t`` and ``esp_zb_apsme_transport_key_request()``
- ``esp_zb_apsme_switch_key_req_t`` and ``esp_zb_apsme_switch_key_request()``
- ``esp_zb_aps_set_authenticated()`` and ``esp_zb_aps_is_authenticated()``

NWK (Network Layer)
^^^^^^^^^^^^^^^^^^^

The header file of the NWK layer is changed from ``nwk/esp_zigbee_nwk.h`` to
:component_file:`ezbee/nwk.h <esp-zigbee-lib/include/ezbee/nwk.h>`.

The following macros, types, and functions have been renamed:

- Rename ``ESP_ZB_NWK_COMMAND_STATUS_*`` to ``EZB_NWK_NETWORK_STATUS_*``

    - rename ``ESP_ZB_NWK_COMMAND_STATUS_NO_ROUTE_AVAILABLE`` to ``EZB_NWK_NETWORK_STATUS_LEGACY_NO_ROUTE_AVAILABLE``
    - rename ``ESP_ZB_NWK_COMMAND_STATUS_TREE_LINK_FAILURE`` to ``EZB_NWK_NETWORK_STATUS_LEGACY_LINK_FAILURE``
    - rename ``ESP_ZB_NWK_COMMAND_STATUS_NONE_TREE_LINK_FAILURE`` to ``EZB_NWK_NETWORK_STATUS_LINK_FAILURE``

- Rename ``esp_zb_nwk_command_status_t`` to ``ezb_nwk_network_status_t``
- Rename ``esp_zb_set_pan_id()`` to ``ezb_nwk_set_panid()``
- Rename ``esp_zb_get_pan_id()`` to ``ezb_nwk_get_panid()``
- Rename ``esp_zb_set_network_device_role()`` to ``ezb_nwk_set_device_type()``
- Rename ``esp_zb_get_network_device_role()`` to ``ezb_nwk_get_device_type()``
- Rename ``esp_zb_set_long_address()`` to ``ezb_nwk_set_extended_address()``
- Rename ``esp_zb_get_long_address()`` to ``ezb_nwk_get_extended_address()``
- Rename ``esp_zb_set_extended_pan_id()`` to ``ezb_set_use_extended_panid()``
- Rename ``esp_zb_get_extended_pan_id()`` to ``ezb_nwk_get_extended_panid()``
- Rename ``esp_zb_address_short_by_ieee()`` to ``ezb_address_short_by_extended()``
- Rename ``esp_zb_ieee_address_by_short()`` to ``ezb_address_extended_by_short()``

The following macros, types, and functions have been removed:

- Rename ``ESP_ZB_NWK_RELATIONSHIP_PREVIOUS_CHILD``
- Rename ``ESP_ZB_NWK_RELATIONSHIP_UNAUTHENTICATED_CHILD``
