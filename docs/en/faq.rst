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

A1.4 Zigbee Light-sleep Mode 
----------------------------

The light-sleep feature for Zigbee is based on ESP-IDF. Refer to the `ESP Light-sleep User Guide <https://docs.espressif.com/projects/esp-idf/en/latest/{IDF_TARGET_PATH_NAME}/api-reference/system/sleep_modes.html>`__
to establish the foundation for implementing Zigbee light-sleep mode.


A1.4.1 How to Configure the Zigbee End Device to Enter Light-sleep Mode
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To enable the Zigbee End Device to enter Light-sleep mode, the following configurations must be applied in ``sdkconfig``:

- ``CONFIG_PM_ENABLE=y``
- ``CONFIG_FREERTOS_USE_TICKLESS_IDLE=y``

With these settings, the ESP-IDF system is able to automatically transition the chip into a low-power state when no tasks need to run for a certain number of ticks.

The `Power Management <https://docs.espressif.com/projects/esp-idf/en/latest/{IDF_TARGET_PATH_NAME}/api-reference/system/power_management.html>`__ provides a more
comprehensive explanation of how the system handles power-saving operations.

The `Zigbee Light-sleep example <https://github.com/espressif/esp-zigbee-sdk/blob/main/examples/esp_zigbee_sleep/light_sleep>`__ is provided for
detailed configuration and usage.

If the Zigbee End Device fails to enter Light-sleep mode, checking the below list may be helpful:

- Verify that both ``CONFIG_PM_ENABLE`` and ``CONFIG_FREERTOS_USE_TICKLESS_IDLE`` are enabled in `menuconfig`.
- Confirm that the :cpp:func:`esp_pm_configure` function is called with the correct configuration parameters.
- Ensure that :cpp:func:`esp_zb_sleep_enable` is set to ``true`` to allow the device to sleep.
- Check whether the device is set to ``rx_off_when_idle`` by calling :cpp:func:`esp_zb_get_rx_on_when_idle()`. If not, please enable it.
- Verify that :cpp:func:`esp_zb_sleep_now` is called when the ``ESP_ZB_COMMON_SIGNAL_CAN_SLEEP`` signal is triggered.
- Ensure that :cpp:func:`esp_zb_sleep_set_threshold` is used to set the minimum sleep threshold, and that the Zigbee task's idle time is greater
  than this threshold.
- Use :cpp:func:`esp_zb_bdb_dev_joined` to confirm whether the device has joined a network. In the official Light-sleep example, the Zigbee task
  remains active if the device is not part of a network.
- Try commenting out any peripheral wake-up sources.


A1.4.2 How to Measure Power Consumption on ESP Development Board
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ESP32-series development boards provide dedicated pins for measuring the chip's current consumption. These test points are located near the top of
the board and are connected by default using a jumper cap.


A1.4.3 Power Consumption in Light-sleep Mode
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The power consumption of the chip in different modes is detailed in the ``Current Consumption Characteristics`` section of the official `datasheet <{IDF_TARGET_DATASHEET_EN_URL}>`__.

If the results in the datasheet differ significantly from your measurements, please contact us via the `Technical Inquiries <https://www.espressif.com/en/contact-us/technical-inquiries>`__.

A1.4.4 How to Set the Sleep Duration for a Zigbee Sleep End Device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A Zigbee Sleep End Device is required to maintain a keep-alive interval with its parent device. This interval determines how long the chip can remain
in sleep mode.

It can be configured using the ``keep_alive`` parameter of the :cpp:func:`esp_zb_init` function.


A1.4.5 Why Does the Current Detector Capture Multiple Peaks When the Zigbee Sleep End Device Starts Up
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This behavior occurs because the Zigbee Light-sleep end device example attempts to scan all channels to find an available network. As a result, the chip sends
a large number of frames during startup.

If the destination network’s channel is known, you can reduce this overhead by calling :cpp:func:`esp_zb_set_primary_network_channel_set` to configure
a single channel for scanning.


A1.4.6 How to Wake Up the Zigbee Light-Sleep End Device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Light-sleep device can be awakened by multiple wake-up source, please see the `light sleep example <https://github.com/espressif/esp-idf/tree/master/examples/system/light_sleep>`__
of ESP-IDF and the official wakeup-source `documentation <https://docs.espressif.com/projects/esp-idf/en/latest/{IDF_TARGET_PATH_NAME}/api-reference/system/sleep_modes.html#wakeup-sources>`__.

The Zigbee Light-sleep end device is configured by default to wake up either when it needs to maintain communication with its parent device (keep-alive)
or when the ``BOOT`` button is pressed, triggering a GPIO event.

If you encounter any issue when adding other wake up sources, please submit a ticket to the `esp-idf issue tracker <https://github.com/espressif/esp-idf/issues>`__.


A1.4.7 Zigbee Light-sleep End Device Fails to Connect with Third-Party Devices
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Generally, a Zigbee Light-sleep End Device behaves the same as a regular Zigbee End Device during the Zigbee commissioning process. Therefore,
Please first try using the typical `Zigbee HA On/Off Light <https://github.com/espressif/esp-zigbee-sdk/tree/main/examples/esp_zigbee_HA_sample/HA_on_off_light>`__
example to connect with the third-party device and help identify the cause of the failure.


A1.4.8 Related Issues
~~~~~~~~~~~~~~~~~~~~~~

- `How a light sleep device wakes up from sleep <https://github.com/espressif/esp-zigbee-sdk/issues/323>`__
- `Watchdog stops working after initializing stack in light sleep <https://github.com/espressif/esp-zigbee-sdk/issues/508>`__
- `GPIO Wake has no effect in light sleep example <https://github.com/espressif/esp-zigbee-sdk/issues/575>`__
- `Low power consumption when using Zigbee features <https://github.com/espressif/esp-zigbee-sdk/issues/606>`__
- `Light sleep example doesn't work <https://github.com/espressif/esp-zigbee-sdk/issues/623>`__

If the above answers can not resolve your question, please submit an issue `here <https://github.com/espressif/esp-zigbee-sdk/issues>`__, and include
the background of your application along with a minimal reproducible example.
