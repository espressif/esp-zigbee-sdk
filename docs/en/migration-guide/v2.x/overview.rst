Overview
--------

The ESP Zigbee SDK v2.x replaced the ZBOSS core with the Espressif proprietary Zigbee implementation, so headers and APIs have
been restructured and refactored to different namespaces. See :doc:`/api-reference/index` for the details of the differences
between the Core API (prefixed with ``ezb_``) and the SDK API (prefixed with ``esp_zigbee_``).

For most APIs unless otherwise specified, the new API names are the same as the old API names, but with the namespace changed.
A quick check of the API changes can be done by going through the headers of the compatibility layer in
:component:`include/compat <esp-zigbee-lib/include/compat>` directory.

Required Migration Steps
^^^^^^^^^^^^^^^^^^^^^^^^

The following changes are required to migrate a project from v1.x to v2.x:

- Change the inclusion of the all-in-one header from ``esp_zigbee_core.h`` to ``esp_zigbee.h``.
  If you include other headers, see `Header Changes`_ for the details.

- Change the subtype of ``zb_storage`` partition in the ``partitions.csv`` file from ``fat`` to ``nvs``.

- Initialize the ``zb_storage`` partition as NVS storage by calling ``nvs_flash_init_partition("zb_storage")``.

- Replace the function calls / callbacks / error codes with the new API names.

Header Changes
^^^^^^^^^^^^^^

The header changes are not just renaming, but also restructuring and refactoring. The following is a list of header replacements:

- Change ``esp_zigbee_core.h`` to ``esp_zigbee.h``.
- Change ``bdb/esp_zigbee_bdb_commissioning.h`` to ``ezbee/bdb.h``.
- Change ``bdb/esp_zigbee_bdb_touchlink.h`` to ``ezbee/touchlink.h``.
- Change ``zdo/esp_zigbee_zdo_common.h`` to ``ezbee/zdo.h`` or ``ezbee/app_signals.h``.
- Change ``zdo/esp_zigbee_zdo_command.h`` to ``ezbee/zdo.h`` or ``ezbee/app_signals.h``.
- Change ``aps/esp_zigbee_aps.h`` to ``ezbee/aps.h``.
- Change ``nwk/esp_zigbee_nwk.h`` to ``ezbee/nwk.h``.
- Change ``mac/esp_zigbee_mac.h`` to ``ezbee/mac.h``.
- Change ``zcl/esp_zigbee_zcl_{cluster_name}.h`` to ``ezbee/zcl/cluster/{cluster_name}.h``.
- Change ``zcl/esp_zigbee_zcl_common.h`` to ``ezbee/zcl/zcl_common.h``.
- Change ``zcl/esp_zigbee_zcl_core.h`` to ``ezbee/zcl.h``.
- Change ``ha/esp_zigbee_ha_standard.h`` to ``ezbee/zha.h``.
- Change ``esp_zigbee_secur.h`` to ``ezbee/secur.h``.
- Change ``esp_zigbee_ota.h`` to  ``ezbee/zcl/cluster/ota_upgrade.h``
- Change ``platform/esp_zigbee_platform.h`` to ``esp_zigbee.h``.

The following headers are removed:

- The definitions of the types are moved to separate header of each module (af, zdo, zcl, etc.):

    - ``esp_zigbee_types.h``

- ZCL command & message interfaces are moved to separate header of each cluster.

    - ``zcl/esp_zigbee_zcl_command.h``

- ZCL data model creation APIs are moved to separate header of each cluster.

    - ``esp_zigbee_attribute.h``
    - ``esp_zigbee_cluster.h``
    - ``esp_zigbee_endpoint.h``

- Green Power has not been supported in v2.x yet.

    - ``zgp/esp_zigbee_zgp.h``
    - ``zgp/esp_zigbee_zgpd.h``
    - ``zgp/esp_zigbee_zgps.h``

- Trace logging is not supported in v2.x.

    - ``esp_zigbee_trace.h``

NVRAM Data Migration
^^^^^^^^^^^^^^^^^^^^

Previously in ESP Zigbee SDK v1.x, the persistent data is stored as raw blob data in the ``zb_storage`` FAT partition. In
ESP Zigbee SDK v2.x, the persistent data would be stored in the NVS storage partition. It is critical for the old product
to be able to upgrade to the new SDK without losing the persistent data. The migration is done by the following steps:

1. Determine the NVS storage partition used for ESP Zigbee SDK v2.x. If there is no NVS storage partition on the old product,
   a runtime partition can be created and shall be maintained by the application.
2. Read the old NVRAM data, convert and write to the new NVS storage.
3. Erase the old partition.

.. note::

   The entire migration solution is under preparation. If you have an urgent request, please contact us via
   `technical-inquiries <https://www.espressif.com/en/contact-us/technical-inquiries>`_.
