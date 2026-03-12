Common
------

In the following sections, unless otherwise specified, the general rules are:

  - changes the prefix from ``esp_zb_`` to ``ezb_``
  - changes the error code type from ``esp_err_t`` to ``ezb_err_t`` if used / returned.

ESP Zigbee SDK Core
^^^^^^^^^^^^^^^^^^^

The header file of the ESP Zigbee SDK Core is changed from ``esp_zigbee_core.h`` to
:component_file:`esp_zigbee.h <esp-zigbee-lib/include/esp_zigbee.h>`.

The following macros, types, and functions have been renamed:

- Rename ``esp_zb_init`` to ``esp_zigbee_init``

- Rename ``esp_zb_start`` to ``esp_zigbee_start``

- Rename ``esp_zb_is_started`` to ``esp_zigbee_is_started``

- Rename ``esp_zb_lock_acquire`` to ``esp_zigbee_lock_acquire``

- Rename ``esp_zb_lock_release`` to ``esp_zigbee_lock_release``

- Rename ``esp_zb_stack_main_loop`` to ``esp_zigbee_launch_mainloop``

- Rename ``esp_zb_factory_reset`` to ``esp_zigbee_factory_reset``

- Rename ``esp_zb_zczr_cfg_t`` to ``struct esp_zigbee_zczr_config_s``

- Rename ``esp_zb_zed_cfg_t`` to ``struct esp_zigbee_zed_config_s``

- Rename ``esp_zb_cfg_t`` to ``esp_zigbee_device_config_t``, with field name changes:

    - rename ``esp_zb_role`` to ``device_type``
    - rename ``zczr_cfg`` to ``zczr_config``
    - rename ``zed_cfg`` to ``zed_config``
    - remove ``nwk_cfg``

- Rename ``esp_zb_user_callback_t`` to ``esp_zigbee_callback_t``

- Rename ``esp_zb_get_version_string`` to ``esp_zigbee_get_version_string`` and move to
  :component_file:`esp_zigbee_version.h <esp-zigbee-lib/include/esp_zigbee_version.h>`.

- Rename ``esp_zb_set_node_descriptor_manufacturer_code`` to ``ezb_af_node_desc_set_manuf_code`` and move to
  :component_file:`ezbee/af.h <esp-zigbee-lib/include/ezbee/af.h>`.

- Rename ``esp_zb_set_node_power_descriptor`` to ``ezb_af_set_node_power_desc`` and move to
  :component_file:`ezbee/af.h <esp-zigbee-lib/include/ezbee/af.h>`.

The following types and enumerator values are moved to :component_file:`ezbee/nwk.h <esp-zigbee-lib/include/ezbee/nwk.h>`:

    - ``ESP_ZB_ED_AGING_TIMEOUT_*`` and renamed to ``EZB_NWK_ED_TIMEOUT_*``
    - ``esp_zb_aging_timeout_t`` and renamed to ``ezb_nwk_ed_timeout_t``

The following functions are moved to :component_file:`ezbee/bdb.h <esp-zigbee-lib/include/ezbee/bdb.h>` and
renamed to uniform naming convention ``ezb_bdb_*``:

- ``esp_zb_set_primary_network_channel_set()``
- ``esp_zb_get_primary_network_channel_set()``
- ``esp_zb_set_secondary_network_channel_set()``
- ``esp_zb_get_secondary_network_channel_set()``
- ``esp_zb_bdb_is_factory_new()``
- ``esp_zb_bdb_get_scan_duration()``
- ``esp_zb_bdb_set_scan_duration()``
- ``esp_zb_bdb_open_network()``
- ``esp_zb_bdb_close_network()``
- ``esp_zb_bdb_dev_joined()``
- ``esp_zb_bdb_start_top_level_commissioning()``
- ``esp_zb_bdb_reset_via_local_action()``
- ``esp_zb_set_bdb_commissioning_mode()``
- ``esp_zb_get_bdb_commissioning_mode()``
- ``esp_zb_bdb_cancel_steering()``
- ``esp_zb_bdb_cancel_formation()``
- ``esp_zb_get_bdb_commissioning_status()``

The following functions are moved to :component_file:`ezbee/touchlink.h <esp-zigbee-lib/include/ezbee/touchlink.h>`:

- ``esp_zb_zdo_touchlink_set_nwk_channel()`` and renamed to ``ezb_touchlink_set_channel()``
- ``esp_zb_zdo_touchlink_set_nwk_channel()`` and renamed to ``ezb_touchlink_get_channel()``

The following functions are moved to :component_file:`ezbee/core.h <esp-zigbee-lib/include/ezbee/core.h>` and
renamed to uniform naming convention ``ezb_*``:

- ``esp_zb_set_channel_mask()``
- ``esp_zb_get_channel_mask()``
- ``esp_zb_set_tx_power()``
- ``esp_zb_get_tx_power()``

A new API :cpp:func:`ezb_config_memory` is provided to configure the memory resources used by the Zigbee stack, thus the
following functions are no longer used and removed:

- ``esp_zb_overall_network_size_set()``
- ``esp_zb_io_buffer_size_set()``
- ``esp_zb_aps_src_binding_table_size_set()``
- ``esp_zb_aps_dst_binding_table_size_set()``

The light sleep is now controlled by the ESP-IDF configuration: ``CONFIG_FREERTOS_USE_TICKLESS_IDLE`` and ``CONFIG_PM_ENABLE``,
so the following functions are no longer used and removed:

- ``esp_zb_sleep_is_enable()``
- ``esp_zb_sleep_enable()``
- ``esp_zb_sleep_now()``
- ``esp_zb_sleep_set_threshold()``

The ``power source`` and ``transfer size`` fields in the Zigbee node descriptor are now generated according to the device's
settings, so the following functions are removed:

- ``esp_zb_set_node_descriptor_power_source()``
- ``esp_zb_set_node_descriptor_transfer_size()``

The policy for joining to distributed network is now controlled by :cpp:func:`ezb_aps_secur_enable_distributed_security` and
can be checked with :cpp:func:`ezb_aps_secur_is_distributed_security`, so the following functions are no longer used and removed:

- ``esp_zb_tc_policy_set_distributed_security()``
- ``esp_zb_tc_policy_get_distributed_security()``
- ``esp_zb_enable_distributed_network()``
- ``esp_zb_zdo_setup_network_as_distributed()``
- ``esp_zb_network_is_distributed()``
- ``esp_zb_enable_joining_to_distributed()``
- ``esp_zb_joining_to_distributed_network_enabled()``

The following macros, types, and functions have been removed:

- ``ESP_ZB_TRANSCEIVER_ALL_CHANNELS_MASK``
- ``ESP_ZB_SLEEP_MAXIMUM_THRESHOLD_MS``
- ``ESP_ZGP_GPPB_DEFAULT_FUNCTIONALITY``
- ``ESP_ZGP_GPS_DEFAULT_FUNCTIONALITY``
- ``esp_zb_scheduler_queue_size_set()``
- ``esp_zb_main_loop_iteration()``
- ``esp_zb_stack_main_loop_iteration()``
- ``esp_zb_nvram_erase_at_start()``
- ``esp_zb_scheduler_alarm()``
- ``esp_zb_scheduler_alarm_cancel()``
- ``esp_zb_scheduler_user_alarm()``
- ``esp_zb_scheduler_user_alarm_cancel()``
- ``esp_zb_callback_t``

ESP Zigbee SDK Platform
^^^^^^^^^^^^^^^^^^^^^^^

The header file of the ESP Zigbee SDK Platform (``platform/esp_zigbee_platform.h``) is merged into ``esp_zigbee.h``.

The following macros, types, and functions have been renamed:

- Rename ``ZB_RADIO_MODE_NATIVE`` to ``ESP_ZIGBEE_RADIO_MODE_NATIVE``
- Rename ``ZB_RADIO_MODE_UART_RCP`` to ``ESP_ZIGBEE_RADIO_MODE_UART_RCP``
- Rename ``esp_zb_radio_mode_t`` to ``esp_zigbee_radio_mode_t``
- Rename ``esp_zb_uart_config_t`` to ``esp_zigbee_uart_config_t``
- Rename ``esp_zb_radio_config_t`` to ``esp_zigbee_radio_config_t``
- Rename ``esp_zb_platform_config_t`` to ``esp_zigbee_platform_config_t`` with field changes:

    - remove ``host_config``

The following types and functions have been moved to :component_file:`ezbee/mac.h <esp-zigbee-lib/include/ezbee/mac.h>`:

- ``esp_zb_platform_mac_config_t`` and renamed to ``ezb_mac_csma_ca_params_t``
- ``esp_zb_platform_mac_config_set()`` and renamed to ``ezb_mac_set_csma_ca_params()``
- ``esp_zb_platform_mac_config_get()`` and renamed to ``ezb_mac_get_csma_ca_params()``

The following macros, types, and functions have been removed:

- ``esp_zb_host_connection_mode_t`` and its related enumerator values.
- ``esp_zb_serial_mode_t`` and its related enumerator values.
- ``esp_zb_serial_config_t``
- ``esp_zb_host_config_t``
- ``esp_zb_mac_raw_frame_callback_t``
- ``esp_zb_mac_raw_frame_handler_register()``
- ``esp_zb_rcp_deinit`` use ``esp_zigbee_deinit()`` instead.

The platform configuration is now passed to stack via :cpp:func:`esp_zigbee_init` with :cpp:type:`esp_zigbee_platform_config_t`
as the parameter. The following functions are no longer used and removed:

- ``esp_zb_platform_config()``
- ``esp_zb_platform_config_get()``

ESP Zigbee SDK Types
^^^^^^^^^^^^^^^^^^^^

The header file of the ESP Zigbee Types (``esp_zigbee_type.h``) has been split into header of each module (af, zdo, zcl, etc.).

The thing to note here is that the base type of 64-bit identifiers is changed from ``uint8_t[8]`` to :cpp:type:`ezb_eui64_s`.
This includes the following types:

- ``esp_zb_64bit_addr_t``, use :cpp:type:`ezb_eui64_s` instead.
- ``esp_zb_ieee_addr_t``, use :cpp:type:`ezb_extaddr_t` instead.
- ``esp_zb_ext_pan_id_t``, use :cpp:type:`ezb_extpanid_t` instead.
- ``esp_zb_addr_u``, use :cpp:type:`ezb_addr_t` instead.

The operation on the new 64-bit identifiers can be performed with the following functions:

- :cpp:func:`ezb_eui64_compare`
- :cpp:func:`ezb_eui64_copy`
- :cpp:func:`ezb_eui64_is_all_zero`
- :cpp:func:`ezb_eui64_set_all_zero`
- :cpp:func:`ezb_eui64_is_all_ones`
- :cpp:func:`ezb_eui64_set_all_ones`
- :cpp:func:`ezb_eui64_is_invalid`

The method of initializing the 64-bit identifiers can be changed to:

.. code-block:: c

    ezb_extaddr_t eui64 = { .u64 = 0x0123456789ABCDEF };

Or

.. code-block:: c

    ezb_extaddr_t eui64 = { .u8 = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF } };

Security
^^^^^^^^

The header file of the Zigbee Security is changed from ``esp_zigbee_secur.h`` to
:component_file:`ezbee/secur.h <esp-zigbee-lib/include/ezbee/secur.h>`.

The following macros, types, and functions have been renamed:

- Rename ``ESP_ZB_IC_TYPE_MAX`` to ``EZB_SECUR_IC_TYPE_MAX_NR``
- Rename ``esp_zb_secur_ic_only_enable()`` to ``ezb_secur_set_ic_required()``
- Rename ``esp_zb_secur_link_key_exchange_required_set()`` to ``ezb_secur_set_tclk_exchange_required()``
- Rename ``esp_zb_secur_ic_remove_req()`` to ``ezb_secur_ic_remove()``
- Rename ``esp_zb_secur_ic_remove_all_req()`` to ``ezb_secur_ic_remove_all()``
- Rename ``esp_zb_secur_primary_network_key_get()`` to ``ezb_secur_get_network_key()``
- Rename ``esp_zb_secur_network_key_set()`` to ``ezb_secur_set_network_key()``
- Rename ``esp_zb_secur_network_key_switch()`` to ``ezb_secur_switch_network_key()``
- Rename ``esp_zb_secur_broadcast_network_key_switch()`` to ``ezb_secur_broadcast_switch_network_key()``

The following functions are moved to :component_file:`ezbee/nwk.h <esp-zigbee-lib/include/ezbee/nwk.h>`:

- ``esp_zb_secur_network_min_join_lqi_get()`` and renamed to ``ezb_nwk_get_min_join_lqi()``
- ``esp_zb_secur_network_min_join_lqi_set()`` and renamed to ``ezb_nwk_set_min_join_lqi()``

The network security level is now controlled by :cpp:func:`ezb_secur_set_security_level` and can be checked with
:cpp:func:`ezb_secur_get_security_level`. The following functions are removed:

- ``esp_zb_secur_network_security_enable()``
- ``esp_zb_secur_network_security_is_enabled()``

The multiple global link key is not supported yet, please use :cpp:func:`ezb_secur_set_global_link_key` to
set the global link key. The following functions are removed:

- ``esp_zb_secur_TC_standard_distributed_key_set()``
- ``esp_zb_secur_TC_standard_preconfigure_key_set()``
- ``esp_zb_secur_multi_TC_standard_preconfigure_key_add()``
- ``esp_zb_secur_multi_TC_standard_preconfigure_key_remove()``
- ``esp_zb_secur_multi_standard_distributed_key_add()``
- ``esp_zb_secur_multi_standard_distributed_key_remove()``

The following macros, types, and functions have been removed:

- ``esp_zb_secur_ic_str_add()``
- ``esp_zb_secur_ic_str_set()``
