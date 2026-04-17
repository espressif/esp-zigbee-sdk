API Reference
=============

The ESP Zigbee SDK provides a set of APIs and Definitions for Zigbee application development. They are categorized
into two parts: Core API and SDK API.

The Core API is a set of APIs and definitions that implements the core function of Zigbee protocol stack. The Core
APIs and definitions are always prefixed with ``ezb_`` and use :cpp:type:`ezb_err_t` as error code whose value always
prifixed with ``EZB_ERR_``.

The SDK API is a set of APIs and definitions that added by ESP Zigbee SDK, which provides additional functions for
a easier configuration and management of the Zigbee stack. The SDK APIs and definitions are prefixed with ``esp_zigbee_``
and use `esp_err_t <https://docs.espressif.com/projects/esp-idf/en/v5.5.3/{IDF_TARGET_PATH_NAME}/api-reference/error-codes.html>`_
as error code whose value always prifixed with ``ESP_ERR_``.

.. toctree::
   :maxdepth: 1

   esp_zigbee_sdk
   esp_zigbee_core/index
