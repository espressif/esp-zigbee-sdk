5.5. Zigbee ZCL OTA Upgrade Cluster
------------------------------------


5.5.1 Overview
~~~~~~~~~~~~~~~
The OTA (Over-the-Air) upgrade is a process that allows network devices to receive firmware updates wirelessly over the network, without requiring
physical access to the devices. This feature enhances device functionality, introduces new features, and fixes software vulnerabilities without the
need for a service visit or manual intervention.

In Zigbee, the OTA upgrade feature is defined and implemented at the ZCL layer, providing an interoperable means for devices from different manufacturers
to upgrade each other's image. The objective of this chapter is to introduce the OTA upgrade process, provide detailed OTA upgrade API usage implemented
by the esp-zigbee-sdk, and suggest some optional optimizations of OTA upgrade from the ZCL perspective.


5.5.2 Related APIs Preview
~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following APIs are related to the main implementation of the ZCL OTA upgrade cluster.

- :cpp:func:`esp_zb_zcl_attr_list_create`
- :cpp:func:`esp_zb_ota_cluster_add_attr`
- :cpp:func:`esp_zb_ota_cluster_create`
- :cpp:func:`esp_zb_cluster_list_add_ota_cluster`
- :cpp:func:`esp_zb_cluster_list_update_ota_cluster`
- :cpp:func:`esp_zb_ota_upgrade_server_notify_req`
- :cpp:func:`esp_zb_ota_upgrade_client_query_image_req`
- :cpp:func:`esp_zb_ota_upgrade_client_query_interval_set`
- :cpp:func:`esp_zb_ota_upgrade_client_query_image_stop`
- :cpp:func:`esp_zb_core_action_handler_register`


5.5.3 OTA Upgrade Message Diagram
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The OTA upgrade message diagram below shows that the **OTA Upgrade Server** functions as an OTA upgrade image provider, allowing the **OTA Upgrade Client**
to access and retrieve the relevant image blocks. The **OTA Upgrade Client** is responsible for downloading and upgrading with the new image.

.. figure:: ../../_static/zigbee-ota-upgrade-process.png
    :align: center
    :alt: ESP Zigbee OTA PROCESS
    :figclass: align-center


The complete OTA upgrade communication process can be described as follows:

-   Initiating the OTA upgrade notification: The **OTA Upgrade Server** can store multiple OTA upgrade images and send an ``Image Notify Request`` to
    the network via broadcast or to a specific device via unicast, sharing information about the OTA upgrade image. If the **OTA Upgrade Client** is
    interested, it responds with a ``Query Next Image Request`` to prepare the download. Additionally, the **OTA Upgrade Client** can also initiate a
    ``Query Next Image Request`` to the **OTA Upgrade Server** to inquire about the OTA upgrade image. If the querying information of image is confirmed
    by the **OTA Upgrade Server**, a ``Query Next Image Response`` with an available status is sent.

-   Downloading the OTA upgrade image: The downloading process starts with the first ``Image Block Request``, after which the OTA upgrade image is divided
    into multiple blocks and sent in ``Image Block Response`` messages by the **OTA Upgrade Server**.

-   Verify and finish OTA upgrade process: If the **OTA Upgrade Client** verifies the integrity of the entire received image, it should send
    an ``Upgrade End Request`` with the upgrade status. The **OTA Upgrade Server** will then respond with an ``Upgrade End Response`` to indicate the
    final status of the OTA upgrade.

Additionally, the esp-zigbee-sdk provides ``Image Notify Request`` and ``Query Next Image Request`` APIs, allowing devices to freely
initiate OTA upgrades. Developers don't need to manage the image exchange process, as the stack handles the details and provides the
image block or status through callbacks to notify the application. 


5.5.4  Typical Usage
~~~~~~~~~~~~~~~~~~~~
This section will introduce the typical usage of a OTA upgrade, including the data model creation process, related commands,
and handlers.

5.5.4.1 OTA Upgrade Cluster Creation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you want to add **OTA Upgrade Server** functionality to an endpoint on a **Home Automation OTA Upgrade Server Device (HAOUS)**, you need
to include a ota upgrade cluster in the endpoint. You can refer to the code below.

.. code-block:: c

    #define ESP_OTA_SERVER_ENDPOINT       1
    #define OTA_UPGRADE_QUERY_JITTER      0x64
    #define OTA_UPGRADE_CURRENT_TIME      0x0000
    #define OTA_UPGRADE_IMAGE_COUNT       1 
    esp_zb_attribute_list_t *basic_cluster = esp_zb_basic_cluster_create(NULL);
    esp_zb_attribute_list_t *ota_cluster = esp_zb_zcl_attr_list_create(ESP_ZB_ZCL_CLUSTER_ID_OTA_UPGRADE);
    esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();
    esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
    esp_zb_zcl_ota_upgrade_server_variable_t variable = {
        .query_jitter = OTA_UPGRADE_QUERY_JITTER,
        .current_time = OTA_UPGRADE_CURRENT_TIME,
        .file_count = OTA_UPGRADE_IMAGE_COUNT,
    };
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = ESP_OTA_SERVER_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_TEST_DEVICE_ID,
        .app_device_version = 0,
    };

    ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, ESP_MANUFACTURER_NAME));
    ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, ESP_MODEL_IDENTIFIER));
    ESP_ERROR_CHECK(esp_zb_ota_cluster_add_attr(ota_cluster, ESP_ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_DATA_ID, (void *)&variable));
    ESP_ERROR_CHECK(esp_zb_cluster_list_add_basic_cluster(cluster_list, basic_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE));
    ESP_ERROR_CHECK(esp_zb_cluster_list_add_ota_cluster(cluster_list, ota_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE));
    ESP_ERROR_CHECK(esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config));
    esp_zb_device_register(ep_list);

The ``OTA_UPGRADE_IMAGE_COUNT`` specifies the number of OTA upgrade images that the OTA upgrade server can store. If multiple distinct OTA
images need to be supported, set this to the appropriate value. The ``OTA_UPGRADE_QUERY_JITTER`` parameter, which ranges from 0x01 to 0x64,
is used by the client to decide whether to respond to the ``Image Notify Command``. The client generates a random value, and if it’s less
than ``OTA_UPGRADE_QUERY_JITTER``, the client will send a ``Query Next Image Request``; otherwise, the command will be ignored. We set this
to the maximum in this example. The ``OTA_UPGRADE_CURRENT_TIME`` helps the client device determine when to upgrade its running firmware with
the newly downloaded image(s).


If you intend to create a **Home Automation OTA Upgrade Client Device (HAOUC)** with a **OTA Upgrade Client** cluster to download OTA upgrade image
from **HAOUS**, you can refer to the code below.

.. code-block:: c

    #define OTA_UPGRADE_RUNNING_FILE_VERSION    0x01010101
    #define OTA_UPGRADE_DOWNLOADED_FILE_VERSION ESP_ZB_ZCL_OTA_UPGRADE_DOWNLOADED_FILE_VERSION_DEF_VALUE
    #define OTA_UPGRADE_MANUFACTURER            0x1001
    #define OTA_UPGRADE_IMAGE_TYPE              0x1011
    #define OTA_UPGRADE_HW_VERSION              0x0101
    #define OTA_UPGRADE_MAX_DATA_SIZE           223 
    esp_zb_attribute_list_t *basic_cluster = esp_zb_basic_cluster_create(NULL);
    esp_zb_ota_cluster_cfg_t ota_cluster_cfg = {
        .ota_upgrade_file_version = OTA_UPGRADE_RUNNING_FILE_VERSION,
        .ota_upgrade_downloaded_file_ver = OTA_UPGRADE_DOWNLOADED_FILE_VERSION,
        .ota_upgrade_manufacturer = OTA_UPGRADE_MANUFACTURER,
        .ota_upgrade_image_type = OTA_UPGRADE_IMAGE_TYPE,
    };
    esp_zb_attribute_list_t *ota_cluster = esp_zb_ota_cluster_create(&ota_cluster_cfg);
    esp_zb_zcl_ota_upgrade_client_variable_t variable_config = {
        .timer_query = ESP_ZB_ZCL_OTA_UPGRADE_QUERY_TIMER_COUNT_DEF,
        .hw_version = OTA_UPGRADE_HW_VERSION,
        .max_data_size = OTA_UPGRADE_MAX_DATA_SIZE,
    };
    uint16_t ota_upgrade_server_addr = 0xffff;
    uint8_t ota_upgrade_server_ep = 0xff;
    esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();
    esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = ESP_OTA_CLIENT_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_TEST_DEVICE_ID,
        .app_device_version = 0,
    };
    ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, ESP_MANUFACTURER_NAME));
    ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, ESP_MODEL_IDENTIFIER));
    ESP_ERROR_CHECK(esp_zb_ota_cluster_add_attr(ota_cluster, ESP_ZB_ZCL_ATTR_OTA_UPGRADE_CLIENT_DATA_ID, (void *)&variable_config));
    ESP_ERROR_CHECK(esp_zb_ota_cluster_add_attr(ota_cluster, ESP_ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ADDR_ID, (void *)&ota_upgrade_server_addr));
    ESP_ERROR_CHECK(esp_zb_ota_cluster_add_attr(ota_cluster, ESP_ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ENDPOINT_ID, (void *)&ota_upgrade_server_ep));
    ESP_ERROR_CHECK(esp_zb_cluster_list_add_basic_cluster(cluster_list, basic_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE));
    ESP_ERROR_CHECK(esp_zb_cluster_list_add_ota_cluster(cluster_list, ota_cluster, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE));
    ESP_ERROR_CHECK(esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config));
    esp_zb_device_register(ep_list);


The ``OTA_UPGRADE_RUNNING_FILE_VERSION`` represents the device’s current running image version, which is used to determine if an upgrade from the
OTA upgrade server is needed. ``OTA_UPGRADE_DOWNLOADED_FILE_VERSION`` is used to initialize the ``DownloadedFileVersion`` attribute, this attribute will be
updated to the matched file version with OTA upgrade server after the OTA upgrade process completes. ``OTA_UPGRADE_MAX_DATA_SIZE`` represents the maximum
data block size the OTA upgrade client can receive.

5.5.4.2 Generate and Apply OTA Upgrade Image
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The OTA upgrade implementation in the esp-zigbee-sdk provides a standard method for exchanging OTA images across different platforms and ensures
efficient transmission based on developer configurations. However, it does not manage image generation or application; developers are responsible
for creating and applying the OTA image.

Generate an OTA Upgrade Image for the ESP Platform
""""""""""""""""""""""""""""""""""""""""""""""""""

In general, any application binary file compiled by ESP-IDF can be used as an OTA upgrade image for ESP devices. The ESP-IDF file system also provides various
methods for storing binary files on the chip. For more details, please refer to the `Storage API <https://docs.espressif.com/projects/esp-idf/en/latest/esp32h2/api-reference/storage/index.html>`__.
If you would like to use the `On Off Light <https://github.com/espressif/esp-zigbee-sdk/tree/main/examples/esp_zigbee_HA_sample/HA_on_off_light/>`_  application
firmware as the OTA upgrade image for the `OTA Upgrade Server <https://github.com/espressif/esp-zigbee-sdk/tree/main/examples/esp_zigbee_ota/ota_server/>`_,
please refer to the below steps:


Build the light application binary file

.. code-block:: bash

   cd ~/esp/esp-zigbee-sdk/examples/esp_zigbee_HA_sample/HA_on_off_light

   idf.py fullclean

   idf.py set-target [CHIP]

   idf.py build

Copy the binary file to the ``main`` folder of OTA upgrade server

.. code-block:: bash

    cp -f build/on_off_light_bulb.bin ~/esp/esp-zigbee-sdk/examples/esp_zigbee_ota/ota_server/main/ota_file.bin

    cd ~/esp/esp-zigbee-sdk/examples/esp_zigbee_ota/ota_server/main/ota_file.bin

    idf.py fullclean

    idf.py set-target [CHIP]

    idf.py build

Apply an OTA Upgrade Image on the ESP Platform
""""""""""""""""""""""""""""""""""""""""""""""

For more detailed information on applying the image on the ESP platform, please refer to `OTA API <https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/ota.html>`__ documentation.


5.5.4.3 OTA Upgrade Commands
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Add OTA Upgrade Image
"""""""""""""""""""""

If you expect to add an OTA Upgrade image with the ``OTA_UPGRADE_MANUFACTURER(0x1001)``, ``OTA_UPGRADE_IMAGE_TYPE(0x1011)``, ``OTA_UPGRADE_FILE_VERSION(0x01010110)``
and ``OTA_UPGRADE_IMAGE_SIZE(618480)`` to first entry in the OTA upgrade table of the **HAOUS** device. You can call the :cpp:func:`esp_zb_ota_upgrade_server_notify_req`
API to register this image in the OTA upgrade table at the specified index.

.. code-block:: c

    #define OTA_IMAGE_SIZE 618480
    esp_zb_ota_upgrade_server_notify_req_t req = {
        .endpoint = ESP_OTA_SERVER_ENDPOINT,
        .index = 0,                                       // The index of OTA Server OTA image table
        .notify_on = false,                               // Simply register the OTA image without sending a notification.
        .ota_upgrade_time = OTA_UPGRADE_CURRENT_TIME + 1, // When to upgrade its running firmware image
        .ota_file_header =
            {
                .manufacturer_code = OTA_UPGRADE_MANUFACTURER,
                .image_type = OTA_UPGRADE_IMAGE_TYPE,
                .file_version = OTA_UPGRADE_FILE_VERSION,
                .image_size = OTA_IMAGE_SIZE,
            },
        .next_data_cb = zb_ota_next_data_handler,
    };
    esp_zb_ota_upgrade_server_notify_req(&req);


The size of the OTA upgrade table is determined by the ``OTA_UPGRADE_IMAGE_COUNT`` of the **HAOUS** device. The ``zb_ota_next_data_handler`` is a callback
that is triggered by the stack once the OTA upgrade process has started. At this point, the stack expects to retrieve the image block data from the
application.

Notify OTA Upgrade Image
""""""""""""""""""""""""

If you expect to notify the OTA upgrade image to specific device whose network address is ``0x1234`` on **HAOUS** side, you can set the optional ``field_control``
to achieve this, you can refer to below code.

.. code-block:: c

    esp_zb_ota_upgrade_server_notify_req_t req = {
        .endpoint = ESP_OTA_SERVER_ENDPOINT,
        .index = 0,                                       // The index of OTA Server OTA image table
        .notify_on = true,                                // Notify current image
        .ota_upgrade_time = OTA_UPGRADE_CURRENT_TIME + 1, // When to upgrade its running firmware image
        .ota_file_header = {
                .manufacturer_code = OTA_UPGRADE_MANUFACTURER,
                .image_type = OTA_UPGRADE_IMAGE_TYPE,
                .file_version = OTA_UPGRADE_FILE_VERSION,
                .image_size = OTA_IMAGE_SIZE,
            },
        .next_data_cb = zb_ota_next_data_handler,
    };

    req.ota_file_header.field_control = ESP_ZB_ZCL_OTA_UPGRADE_FILE_HEADER_FC_DEVICE_SPECIFIC;
    esp_zb_ieee_address_by_short(0x1234, req.ota_file_header.optional.upgrade_file_destination);
    esp_zb_ota_upgrade_server_notify_req(&req);


Please note that if the ``ESP_ZB_ZCL_OTA_UPGRADE_FILE_HEADER_FC_DEVICE_SPECIFIC`` bit of ``field control`` has not been set and the ``notify_on``
is set to ``true``, the :cpp:func:`esp_zb_ota_upgrade_server_notify_req` will broadcast the ``Image Notify Request`` to the network.

Query OTA Upgrade Image
"""""""""""""""""""""""

If you expect to query an OTA Upgrade image from the endpoint ``ESP_OTA_SERVER_ENDPOINT`` of **HAOUS** whose short address is ``0x0000`` on **HAOUC** side,
you can call :cpp:func:`esp_zb_ota_upgrade_client_query_image_req`, please refer to below code.

.. code-block:: c

    esp_zb_ota_upgrade_client_query_image_req(0x0000, ESP_OTA_SERVER_ENDPOINT);


The request will be sent after 1 minutes, you can call :cpp:func:`esp_zb_ota_upgrade_client_query_interval_set` to the interval of querying image
request. If you expect to stop query image request, you can call :cpp:func:`esp_zb_ota_upgrade_client_query_image_stop` to achieve it.

Approve and Reject OTA Upgrade request
""""""""""""""""""""""""""""""""""""""

The application can decide whether to approve an OTA upgrade request from a remote device.

The ``ESP_ZB_CORE_OTA_UPGRADE_SRV_QUERY_IMAGE_CB_ID`` signal indicates the OTA upgrade request details on the **HAOUS** side. Returning ``ESP_OK``
approves the request; otherwise, the OTA upgrade request is aborted. You can follow the code below for implementation.

.. code-block:: c

    static esp_err_t zb_ota_upgrade_server_query_image_handler(esp_zb_zcl_ota_upgrade_server_query_image_message_t message)
    {
        esp_err_t ret = ESP_OK;
        ESP_RETURN_ON_FALSE(message.info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_FAIL, TAG, "Failed to parse OTA upgrade server query image message");
        ESP_LOGI(TAG, "OTA upgrade server query image");
        ESP_LOGI(TAG, "OTA client address: 0x%x", message.zcl_addr.u.short_addr);
        ESP_LOGI(TAG, "OTA version: 0x%lx, image type: 0x%x, manufacturer code: %x, ", message.version, message.image_type, message.manufacturer_code);
        if (message.table_idx) {
            ESP_LOGI(TAG, "OTA table index: 0x%x", *message.table_idx);
        }
        ESP_RETURN_ON_FALSE(
            (message.image_type == OTA_UPGRADE_IMAGE_TYPE && message.manufacturer_code == OTA_UPGRADE_MANUFACTURER),
            ESP_ERR_NOT_FOUND, TAG, "OTA query image mismatch");
        return ret;
    }

The ``ESP_ZB_CORE_OTA_UPGRADE_QUERY_IMAGE_RESP_CB_ID`` signal is triggered when **HAOUC** receives the ``Next Image Response``. Returning ``ESP_OK``
to the stack indicates that the OTA upgrade image for the remote device is approved by the application; otherwise, the OTA upgrade process will be aborted. See the
code example below for reference.

.. code-block:: c

    static esp_err_t zb_ota_upgrade_query_image_resp_handler(esp_zb_zcl_ota_upgrade_query_image_resp_message_t message)
    {
        esp_err_t ret = ESP_OK;
        if (message.info.status == ESP_ZB_ZCL_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "Queried OTA image from address: 0x%04hx, endpoint: %d", message.server_addr.u.short_addr, message.server_endpoint);
            ESP_LOGI(TAG, "Image version: 0x%lx, manufacturer code: 0x%x, image size: %ld", message.file_version, message.manufacturer_code,
                    message.image_size);
        }
        if (ret == ESP_OK) {
            ESP_LOGI(TAG, "Approving OTA image upgrade");
        } else {
            ESP_LOGI(TAG, "Rejecting OTA image upgrade, status: %s", esp_err_to_name(ret));
        }
        return ret;
    }


Image Block Request and Response
""""""""""""""""""""""""""""""""

When the OTA upgrade image is approved by both **HAOUS** and **HAOUC**, the image transmission process begins. To simplify application operations, the SDK
abstracts the OTA upgrade image block communication process, reporting status and data to the application.

The status of the OTA upgrade image block communication is triggered by a callback registered through :cpp:func:`esp_zb_core_action_handler_register` with
the ``ESP_ZB_CORE_OTA_UPGRADE_SRV_STATUS_CB_ID`` signal on the **HAOUS** side. On the **HAOUC** side, the status and data of the OTA upgrade image block
communication are triggered by the callback registered through :cpp:func:`esp_zb_core_action_handler_register()` with the ``ESP_ZB_CORE_OTA_UPGRADE_VALUE_CB_ID``
signal.

The ``ESP_ZB_CORE_OTA_UPGRADE_SRV_STATUS_CB_ID`` signal handler would look like this:

.. code-block:: c

    static esp_err_t zb_ota_upgrade_server_status_handler(esp_zb_zcl_ota_upgrade_server_status_message_t message)
    {
        esp_err_t ret = ESP_OK;
        ESP_RETURN_ON_FALSE(message.info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_FAIL, TAG, "Failed to parse OTA upgrade server status message");
        ESP_LOGI(TAG, "OTA client address: 0x%x", message.zcl_addr.u.short_addr);
        ESP_LOGI(TAG, "OTA version: 0x%lx, image type: 0x%x, server status: %d", message.version, message.image_type, message.server_status);
        if (message.upgrade_time) {
            ESP_LOGI(TAG, "OTA upgrade time: 0x%lx", *message.upgrade_time);
        }
        return ret;
    }

The ``ESP_ZB_CORE_OTA_UPGRADE_VALUE_CB_ID`` signal handler would look like this:

.. code-block:: c

    static esp_err_t zb_ota_upgrade_status_handler(esp_zb_zcl_ota_upgrade_value_message_t message)
    {
        static uint32_t total_size = 0;
        static uint32_t offset = 0;
        static int64_t start_time = 0;
        esp_err_t ret = ESP_OK;

        if (message.info.status == ESP_ZB_ZCL_STATUS_SUCCESS) {
            switch (message.upgrade_status) {
            case ESP_ZB_ZCL_OTA_UPGRADE_STATUS_START:
                ESP_LOGI(TAG, "-- OTA upgrade start");
                start_time = esp_timer_get_time();
                ESP_RETURN_ON_ERROR(ret, TAG, "Failed to begin OTA partition, status: %s", esp_err_to_name(ret));
                break;
            case ESP_ZB_ZCL_OTA_UPGRADE_STATUS_RECEIVE:
                total_size = message.ota_header.image_size;
                offset += message.payload_size;
                ESP_LOGI(TAG, "-- OTA Client receives data: progress [%ld/%ld]", offset, total_size);
                break;
            case ESP_ZB_ZCL_OTA_UPGRADE_STATUS_APPLY:
                ESP_LOGI(TAG, "-- OTA upgrade apply");
                break;
            case ESP_ZB_ZCL_OTA_UPGRADE_STATUS_CHECK:
                ret = offset == total_size ? ESP_OK : ESP_FAIL;
                ESP_LOGI(TAG, "-- OTA upgrade check status: %s", esp_err_to_name(ret));
                break;
            case ESP_ZB_ZCL_OTA_UPGRADE_STATUS_FINISH:
                ESP_LOGI(TAG, "-- OTA Finish");
                ESP_LOGI(TAG, "-- OTA Information: version: 0x%lx, manufacturer code: 0x%x, image type: 0x%x, total size: %ld bytes, cost time: %lld ms,",
                        message.ota_header.file_version, message.ota_header.manufacturer_code, message.ota_header.image_type,
                        message.ota_header.image_size, (esp_timer_get_time() - start_time) / 1000);
                break;
            default:
                ESP_LOGI(TAG, "OTA status: %d", message.upgrade_status);
                break;
            }
        }
        return ret;
    }


You can retrieve the image block from this handler. It’s essential for you to apply the image block to effectively upgrade the firmware.

More details please see examples:

:project_file:`ota_client <examples/esp_zigbee_ota/ota_client/main/esp_ota_client.c>`

:project_file:`ota_server <examples/esp_zigbee_ota/ota_server/main/esp_ota_server.c>`


5.5.5  OTA Upgrade Rate Optimization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
There are several methods available to improve the OTA upgrade process.

5.5.5.1 General Optimization
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Adjust the ``OTA_UPGRADE_MAX_DATA_SIZE`` to improve frame exchange; a value of 223 is recommended.
- Increase the ``FREERTOS_HZ`` in menuconfig to enhance the system's response rate. The default value is 100.
- Enable the ``IEEE802154_TIMING_OPTIMIZATION`` in menuconfig to optimize IEEE802154 timing.
- Reduce unrelated logs during the OTA upgrade process.

Based on actual test results, the optimizations above can increase the OTA upgrade rate to 8.1 KB/s.

5.5.5.2 Delta OTA
^^^^^^^^^^^^^^^^^
Delta OTA is a firmware update technique designed to transmit and apply updates by only sending the "delta" or differences between the old and new
firmware versions, rather than the complete new firmware image. This approach can significantly reduce the data transfer size, which is especially
beneficial for IoT devices operating on low-bandwidth, low-power protocols.

If you need to upgrade the firmware running on the chip with less changes, enabling Delta OTA feature will be effective.

Refer to `Delta OTA Upgrade Functions <https://github.com/espressif/esp-zigbee-sdk/tree/main/examples/esp_zigbee_ota/ota_client#delta-ota-upgrade-functions>`__
for instructions on enabling delta OTA.
