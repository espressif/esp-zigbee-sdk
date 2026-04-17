Commissioning
-------------

In the following sections, unless otherwise specified, the general rules are:

  - changes the prefix from ``esp_zb_`` to ``ezb_``
  - changes the error code type from ``esp_err_t`` to ``ezb_err_t`` if used / returned.

BDB Commissioning
^^^^^^^^^^^^^^^^^

The header file of the BDB Commissioning is changed from ``bdb/esp_zigbee_bdb_commissioning.h`` to
:component_file:`ezbee/bdb.h <esp-zigbee-lib/include/ezbee/bdb.h>`.

The following macros, types, and functions have been renamed:

- Rename ``ESP_ZB_BDB_MODE_TOUCHLINK_COMMISSIONING`` to ``EZB_BDB_MODE_TOUCHLINK_INITIATOR``
- Rename ``esp_zb_bdb_commissioning_mode_mask_t`` to ``ezb_bdb_comm_mode_mask_t``
- Rename ``esp_zb_bdb_commissioning_mode_t`` to ``ezb_bdb_comm_mode_t``
- Rename ``esp_zb_bdb_commissioning_status_t`` to ``ezb_bdb_comm_status_t``
- Rename ``esp_zb_set_bdb_commissioning_mode`` to ``ezb_bdb_set_commissioning_mode``
- Rename ``esp_zb_get_bdb_commissioning_mode`` to ``ezb_bdb_get_commissioning_mode``
- Rename ``esp_zb_get_bdb_commissioning_status`` to ``ezb_bdb_get_commissioning_status``

The following macros, types, and functions have been removed:

- ``ESP_ZB_BDB_MIN_COMMISSIONING_TIME``
- ``ESP_ZB_BDB_INITIALIZATION``
- ``ESP_ZB_BDB_TOUCHLINK_COMMISSIONING``
- ``ESP_ZB_BDB_NETWORK_STEERING``
- ``ESP_ZB_BDB_NETWORK_FORMATION``
- ``ESP_ZB_BDB_FINDING_N_BINDING``
- ``ESP_ZB_BDB_TOUCHLINK_TARGET``

The following BDB related APP signals have been removed:

- ``ESP_ZB_BDB_SIGNAL_TC_REJOIN_DONE``
- ``ESP_ZB_BDB_SIGNAL_STEERING_CANCELLED``, please check the parameter of the ``EZB_BDB_SIGNAL_STEERING`` signal
- ``ESP_ZB_BDB_SIGNAL_FORMATION_CANCELLED``, please check the parameter of the ``EZB_BDB_SIGNAL_FORMATION`` signal

The behavioral changes:

- In v2.x, ``EZB_BDB_MODE_INITIALIZATION`` will not run by default unless the user explicitly sets it. That is, when
  the device reboots, the user should call ``ezb_bdb_start_top_level_commissioning(EZB_BDB_MODE_INITIALIZATION)`` to
  start the initialization (rejoin to the previous network).

Touchlink Commissioning
^^^^^^^^^^^^^^^^^^^^^^^

The header file of the Touchlink Commissioning is changed from ``bdb/esp_zigbee_bdb_touchlink.h`` to
:component_file:`ezbee/touchlink.h <esp-zigbee-lib/include/ezbee/touchlink.h>`.

The following macros, types, and functions have been renamed:

- Rename ``ESP_ZB_TOUCHLINK_MASTER_KEY`` to ``EZB_TOUCHLINK_KEY_BITMASK_MASTER``
- Rename ``ESP_ZB_TOUCHLINK_CERTIFICATION_KEY`` to ``EZB_TOUCHLINK_KEY_BITMASK_CERTIFICATION``
- Rename ``esp_zb_touchlink_action_allowed_callback_t`` to ``ezb_touchlink_action_permission_callback_t``
- Rename ``esp_zb_zll_identify_req_callback_t`` to ``ezb_touchlink_identify_callback_t``
- Rename ``esp_zb_zdo_touchlink_target_set_timeout`` to ``ezb_touchlink_set_target_timeout``
- Rename ``esp_zb_zdo_touchlink_set_key_bitmask`` to ``ezb_touchlink_set_key_bitmask``
- Rename ``esp_zb_zdo_touchlink_set_master_key`` to ``ezb_touchlink_set_master_key``
- Rename ``esp_zb_zdo_touchlink_set_rssi_threshold`` to ``ezb_touchlink_set_rssi_threshold``
- Rename ``esp_zb_zdo_touchlink_get_rssi_threshold`` to ``ezb_touchlink_get_rssi_threshold``
- Rename ``esp_zb_zdo_touchlink_set_nwk_channel`` to ``ezb_touchlink_set_channel``
- Rename ``esp_zb_zdo_touchlink_get_nwk_channel`` to ``ezb_touchlink_get_channel``

The following macros, types, and functions have been removed:

- ``esp_zb_touchlink_clear_factory_new``

The following BDB related APP signals have been changed:

- Remove ``ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED``
- Remove ``ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_JOINED_ROUTER``
- Remove ``ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET``
- Remove ``ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK``
- Rename ``ESP_ZB_BDB_SIGNAL_TOUCHLINK`` to ``EZB_BDB_SIGNAL_TOUCHLINK_INITIATOR_FINISHED``
- Rename ``ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET_FINISHED`` to ``EZB_BDB_SIGNAL_TOUCHLINK_TARGET_FINISHED``

The behavioral changes:

- In v2.x, the touchlink commissioning routine will not change the network security type (i.e. centralized or distributed)
  by itself. The user needs to ensure the network security type is correct before starting the touchlink commissioning.

- In v2.x, the channel used for touchlink commissioning is set by the user via :cpp:func:`ezb_touchlink_set_channel`,
  which affects the channel usage for both the touchlink initiator and target. For more details, please refer to the
  documentation of :cpp:func:`ezb_touchlink_set_channel`.
