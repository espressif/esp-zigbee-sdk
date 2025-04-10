A1 Appendix FAQs
================

A1.1 Compilation errors
-----------------------

Cannot build the application:

-  Make sure you are on the correct esp-idf branch/release. Run ``git submodule
   update —init —recursive`` to make sure the submodules are at the
   correct heads
-  Make sure you are on the correct ESP Zigbee SDK branch.
-  Delete the build/ directory and also sdkconfig and sdkconfig.old and
   then build again.

A1.2 Flashing errors
--------------------

Cannot flash to the target:

- Make sure you have connected your device to the PC.
- Checking the port, run ``ls -la /dev/ttyUSB*`` to check corresponding port is recognized by PC.
- Make sure you choose the correct target.

A1.3 How to check whether a Zigbee device is on the network?
------------------------------------------------------------

A1.3.1 Inquire Remote Device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A Zigbee device powers off, the Zigbee network will not immediately detect its unavailability, as the
device does not emit any events to network when powered down. The network requires some time to diagnose
and confirm the device's status.

If the device is a router, it periodically sends ``Link Status`` network commands to maintain connections with
its neighbors. When the router goes offline, these ``Link Status`` messages stop, and its neighbors will
eventually mark it as unreachable in their neighbor tables. The ``Link Status`` interval is typically
15 seconds. If a neighbor does not receive this command for four consecutive intervals, it considers
the router unreachable.

If the device is an end device, it must periodically send ``Data Request`` MAC commands to keep alive with its
parent. These requests update the aging timer on the parent. When the aging timer expires without receiving
a request, the parent removes the child from its neighbor table.

In summary, the neighbor table retrieved using :cpp:func:`esp_zb_nwk_get_next_neighbor` can be used to check
whether a Zigbee device is currently online. Additionally, the `ESP_ZB_ZDO_DEVICE_UNAVAILABLE` signal is
raised when a request cannot reach the destination device, which also indicates the device is likely offline.

A1.3.2 Inquire Local Device
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The SDK provides the :cpp:func:`esp_zb_bdb_dev_joined` API to indicate whether the local device is currently
on a Zigbee network. Additionally, the :cpp:func:`esp_zb_bdb_is_factory_new` API indicates whether the device is
in a factory-new state, means that it is not currently on the network but has previously joined one will attempt
to rejoin the previous network after rebooting.

A1.3.2 Related Issues
~~~~~~~~~~~~~~~~~~~~~

- `Identify when a device is offline <https://github.com/espressif/esp-zigbee-sdk/issues/417>`__
- `How do I get the current connection state <https://github.com/espressif/esp-zigbee-sdk/issues/544>`__
- `Way to know when an end device has re-joined a coordinator <https://github.com/espressif/esp-zigbee-sdk/issues/343>`__
- `Rejoin after connection is lost? <https://github.com/espressif/esp-zigbee-sdk/issues/18>`__
