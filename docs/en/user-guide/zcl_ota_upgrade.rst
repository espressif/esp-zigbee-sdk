Zigbee ZCL OTA Upgrade Cluster
------------------------------


Overview
~~~~~~~~
The OTA (Over-the-Air) upgrade is a process that allows network devices to receive firmware updates wirelessly over the network, without requiring
physical access to the devices. This feature enhances device functionality, introduces new features, and fixes software vulnerabilities without the
need for a service visit or manual intervention.

In Zigbee, the OTA upgrade feature is defined and implemented at the ZCL layer, providing an interoperable means for devices from different manufacturers
to upgrade each other's image. The objective of this chapter is to introduce the OTA upgrade process, provide detailed OTA upgrade API usage implemented
by the esp-zigbee-sdk, and suggest some optional optimizations of OTA upgrade from the ZCL perspective.


Related APIs Preview
~~~~~~~~~~~~~~~~~~~~
The following APIs are related to the main implementation of the ZCL OTA upgrade cluster.

- :cpp:func:`ezb_zcl_ota_upgrade_create_cluster_desc`
- :cpp:func:`ezb_zcl_ota_upgrade_cluster_desc_add_manuf_attr`
- :cpp:func:`ezb_zcl_ota_upgrade_cluster_desc_add_attr`
- :cpp:func:`ezb_zcl_ota_upgrade_image_notify_cmd_req`
- :cpp:func:`ezb_zcl_ota_upgrade_query_next_image_cmd_req`
- :cpp:func:`ezb_zcl_ota_upgrade_add_ota_file`
- :cpp:func:`ezb_zcl_ota_upgrade_remove_ota_file`
- :cpp:func:`ezb_zcl_ota_upgrade_set_download_block_size`
- :cpp:func:`ezb_zcl_ota_upgrade_set_hw_version`


OTA Upgrade Message Diagram
~~~~~~~~~~~~~~~~~~~~~~~~~~~
The OTA upgrade message diagram below shows the **OTA Upgrade Server** as the image provider and the **OTA Upgrade Client** as the device that retrieves image blocks,
downloads them, and applies the new firmware.

.. figure:: ../../_static/zigbee-ota-upgrade-process.png
    :align: center
    :alt: ESP Zigbee OTA PROCESS
    :figclass: align-center


The complete OTA upgrade communication process can be described as follows:

-   Initiating the OTA upgrade notification: The **OTA Upgrade Server** can store multiple OTA upgrade images and send an ``Image Notify Request`` to
    the network via broadcast or to a specific device via unicast, sharing information about the OTA upgrade image. If the **OTA Upgrade Client** is
    interested, it responds with a ``Query Next Image Request`` to prepare the download. The **OTA Upgrade Client** may also send a
    ``Query Next Image Request`` on its own to ask the **OTA Upgrade Server** about available images. If the **OTA Upgrade Server** accepts the query,
    it replies with a ``Query Next Image Response`` indicating availability.

-   Downloading the OTA upgrade image: The downloading process starts with the first ``Image Block Request``, after which the OTA upgrade image is divided
    into multiple blocks and sent in ``Image Block Response`` messages by the **OTA Upgrade Server**.

-   Verify and finish OTA upgrade process: If the **OTA Upgrade Client** verifies the integrity of the entire received image, it should send
    an ``Upgrade End Request`` with the upgrade status. The **OTA Upgrade Server** will then respond with an ``Upgrade End Response`` to indicate the
    final status of the OTA upgrade.

Additionally, the esp-zigbee-sdk provides ``Image Notify Request`` and ``Query Next Image Request`` APIs, allowing devices to freely
initiate OTA upgrades. Developers don't need to manage the image exchange process, as the stack handles the details and provides the
image block or status through callbacks to notify the application.


OTA File
^^^^^^^^
The Zigbee OTA file is composed of a header followed by a number of sub-elements. The format is as follows:

.. highlight:: none

::

    ---------------------------------------------------------------
    | Octets | Variable               | Variable                  |
    ---------------------------------------------------------------
      Data    OTA Header               Sub-elements

- OTA Header: The OTA header describes general file metadata such as version and manufacturer. The format is as follows:

    +--------+-----------+-------------------------------------+-----+
    | Octets | Data Types| Field Names                         | M/O |
    +--------+-----------+-------------------------------------+-----+
    | 4      | uint32    | OTA upgrade file identifier         | M   |
    +--------+-----------+-------------------------------------+-----+
    | 2      | uint16    | OTA Header version                  | M   |
    +--------+-----------+-------------------------------------+-----+
    | 2      | uint16    | OTA Header length                   | M   |
    +--------+-----------+-------------------------------------+-----+
    | 2      | uint16    | OTA Header Field control            | M   |
    +--------+-----------+-------------------------------------+-----+
    | 2      | uint32    | Manufacturer code                   | M   |
    +--------+-----------+-------------------------------------+-----+
    | 2      | uint16    | Image type                          | M   |
    +--------+-----------+-------------------------------------+-----+
    | 4      | uint32    | File version                        | M   |
    +--------+-----------+-------------------------------------+-----+
    | 2      | uint16    | ZigBee Stack version                | M   |
    +--------+-----------+-------------------------------------+-----+
    | 32     | ASCII     | OTA Header string                   | M   |
    +--------+-----------+-------------------------------------+-----+
    | 4      | uint32    | Total Image size (including header) | M   |
    +--------+-----------+-------------------------------------+-----+
    | 0/1    | uint8     | Security credential version         | O   |
    +--------+-----------+-------------------------------------+-----+
    | 0/8    | EUI64     | Upgrade file destination            | O   |
    +--------+-----------+-------------------------------------+-----+
    | 0/2    | uint16    | Minimum hardware version            | O   |
    +--------+-----------+-------------------------------------+-----+
    | 0/2    | uint16    | Maximum hardware version            | O   |
    +--------+-----------+-------------------------------------+-----+

- Sub-elements: Sub-elements may contain upgrade data for the embedded device, certificates, or other manufacturer specific pieces. The format is as follows:

.. highlight:: none

::

    ---------------------------------------------------------------------------------
    | Octets | 2-bytes            | 4-bytes                  | Variable             |
    ---------------------------------------------------------------------------------
        Data    Tag ID               Length Field               Data

- Tag ID: The tag identifier denotes the type and format of the data contained within the sub-element. The identifier is one of the values as follows:

    +-----------------+--------------------------------------------+
    | Tag Identifiers | Description                                |
    +-----------------+--------------------------------------------+
    | 0x0000          | Upgrade Image                              |
    +-----------------+--------------------------------------------+
    | 0x0001          | ECDSA Signature (Crypto Suite 1)           |
    +-----------------+--------------------------------------------+
    | 0x0002          | ECDSA Signing Certificate (Crypto Suite 1) |
    +-----------------+--------------------------------------------+
    | 0x0003          | Image Integrity Code                       |
    +-----------------+--------------------------------------------+
    | 0x0004          | Picture Data                               |
    +-----------------+--------------------------------------------+
    | 0x0005          | ECDSA Signature (Crypto Suite 2)           |
    +-----------------+--------------------------------------------+
    | 0x0006          | ECDSA Signing Certificate (Crypto Suite 2) |
    +-----------------+--------------------------------------------+
    | 0xf000 - 0xffff | Manufacturer Specific Use                  |
    +-----------------+--------------------------------------------+

- Length Field: This value dictates the length of the rest of the data within the sub-element in bytes. It does not include the size of the Tag ID or the Length Fields.
- Date: The length of the data in the sub-element must be equal to the value of the Length Field in bytes. The type and format of the data contained in the sub-element
  is specific to the Tag.

The :project_file:`image_builder_tool <tools/image_builder_tool/image_builder_tool.py>` script is Espressif's tool for creating Zigbee OTA image files.
It wraps the application binary in the format defined by the Zigbee specification.


.. code-block:: bash

    usage: image_builder_tool.py [-h] [-d FILE_ID] [-r HEADER_VERSION] -v FILE_VERSION -m MANUF_ID -i IMAGE_TYPE [-s STACK_VERSION] [--header_string HEADER_STRING] [--security-credentials SECURITY_CREDENTIALS]
                                 [--upgrade-dest UPGRADE_DEST] [--min-hw-ver MIN_HW_VER] [--max-hw-ver MAX_HW_VER] --tag TAG_ID:TAG_FILE

    options:
    -h, --help                              show this help message and exit
    -d, --file_id=<4-bytes-hex>             OTA upgrade file identifier, default: 0x0BEEF11E
    -r, --header_version=<4-bytes-hex>      OTA Header version, default: 0x0100
    -m, --manuf-id=<2-bytes-hex>            Manufacturer code
    -i, --image-type=<2-bytes-hex>          Image type
    -v, --file-version=<4-bytes-hex>        File version
    -s, --stack-version=<2-bytes>           Zigbee stack version, default: 0x0002
    --header_string=<text>                  OTA Header string, default: ""
    --security-credentials=<1-byte-hex>     The security credentials required for this upgrade (optional)
    --upgrade-dest=<8-bytes-hex-big-endian> The EUI64 of the device the file is intended for (optional)
    --min-hw-ver=<2-bytes-hex>              Minimum hardware version (optional)
    --max-hw-ver=<2-bytes-hex>              Maximum hardware version (optional)
    --tag=<tag_id:tag_file>                 Tag identifier and binary file

If you would like to use the :example:`On Off Light <home_automation_devices/on_off_light>` application
firmware as the OTA upgrade image for the :example:`OTA Upgrade Server <ota_upgrade/ota_server>`,
please refer to the below steps:

Build the light application binary file and use the :project_file:`image_builder_tool <tools/image_builder_tool/image_builder_tool.py>` to create an OTA image file
with the ``manufacturer_id(0x1001)``, ``image_type(0x1011)``, ``file_version(0x01010110)``, ``tag_id(0x0000)`` and ``tag_file(build/ha_on_off_light_app.bin)``

.. code-block:: bash

   cd ~/esp/esp-zigbee-sdk/examples/esp_zigbee_HA_sample/HA_on_off_light

   idf.py fullclean

   idf.py set-target [CHIP]

   idf.py build

   python ~/esp/esp-zigbee-sdk/tools/image_builder_tool/image_builder_tool.py --manuf-id 0x1234 --image-type 0x5678 --file-version 0x00000010 --tag 0x0000:build/ha_on_off_light_app.bin

Copy the OTA image file into the OTA upgrade server's ``main`` directory.

.. code-block:: bash

    cp -f build/on_off_light_bulb.bin ~/esp/esp-zigbee-sdk/examples/esp_zigbee_ota_server/main/1234-5678-00000010-ha-on-off-light.zigbee

    cd ~/esp/esp-zigbee-sdk/examples/esp_zigbee_ota_server

    idf.py fullclean

    idf.py set-target [CHIP]

    idf.py build


In general, any application binary built with ESP-IDF can serve as the payload of a Zigbee OTA image for ESP devices. ESP-IDF also provides APIs for storing and
managing binaries on chip. See the `Storage API <https://docs.espressif.com/projects/esp-idf/en/latest/esp32h2/api-reference/storage/index.html>`__ documentation.

Typical Usage
~~~~~~~~~~~~~
The following example shows how to use the OTA upgrade APIs to define OTA server and client devices and implement OTA upgrading.

OTA Upgrade Cluster Creation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A **Home Automation OTA Upgrade Server Device (HAOUS)** with an OTA upgrade cluster **server** can be created as follows.

.. code-block:: c

    esp_err_t on_off_switch_with_ota_server_setup(uint8_t ep_id, void *image, uint32_t image_size)
    {
        ezb_af_ep_config_t ep_config = {
            .ep_id              = ep_id,
            .app_profile_id     = EZB_AF_HA_PROFILE_ID,
            .app_device_id      = EZB_ZHA_ON_OFF_SWITCH_DEVICE_ID,
            .app_device_version = 0,
        };

        ezb_af_device_desc_t   dev_desc        = ezb_af_create_device_desc();
        ezb_af_ep_desc_t       ep_desc         = ezb_af_create_endpoint_desc(&ep_config);
        ezb_zcl_cluster_desc_t basic_desc      = EZB_INVALID_ZCL_CLUSTER_DESC;
        ezb_zcl_cluster_desc_t ota_server_desc = EZB_INVALID_ZCL_CLUSTER_DESC;

        ezb_zcl_ota_upgrade_cluster_server_config_t ota_server_cfg = {
            .ota_upgrade_file_table_size = 1,
        };

        basic_desc = ezb_zcl_basic_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_SERVER);
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)"\x09""ESPRESSIF");
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)"\x07"CONFIG_IDF_TARGET);
        ezb_af_endpoint_add_cluster_desc(ep_desc, basic_desc);
        ezb_af_endpoint_add_cluster_desc(ep_desc, ezb_zcl_identify_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_SERVER));
        ota_server_desc = ezb_zcl_ota_upgrade_create_cluster_desc(&ota_server_cfg, EZB_ZCL_CLUSTER_SERVER);
        ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, ota_server_desc));

        ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));
        ESP_ERROR_CHECK(ezb_af_device_desc_register(dev_desc));

        ezb_zcl_core_action_handler_register(ota_upgrade_action_handler);

        ESP_RETURN_ON_FALSE(ezb_zcl_ota_upgrade_add_ota_file(ep_id, image, image_size), ESP_ERR_NOT_SUPPORTED, TAG, "Failed to add OTA file");

        return ESP_OK;
    }

The :cpp:func:`ezb_zcl_ota_upgrade_add_ota_file` and :cpp:func:`ezb_zcl_ota_upgrade_remove_ota_file` APIs are used to add and remove an OTA upgrade image from the
OTA upgrade table.


If you intend to create a **Home Automation OTA Upgrade Client Device (HAOUC)** with a **OTA Upgrade Client** cluster to download OTA upgrade image
from **HAOUS**, you can refer to the code below.

.. code-block:: c

    esp_err_t on_off_light_with_ota_client_setup(uint8_t ep_id)
    {
        ezb_af_ep_config_t ep_config = {
            .ep_id              = ep_id,
            .app_profile_id     = EZB_AF_HA_PROFILE_ID,
            .app_device_id      = EZB_ZHA_ON_OFF_LIGHT_DEVICE_ID,
            .app_device_version = 0,
        };

        ezb_af_device_desc_t   dev_desc        = ezb_af_create_device_desc();
        ezb_af_ep_desc_t       ep_desc         = ezb_af_create_endpoint_desc(&ep_config);
        ezb_zcl_cluster_desc_t basic_desc      = EZB_INVALID_ZCL_CLUSTER_DESC;
        ezb_zcl_cluster_desc_t ota_client_desc = EZB_INVALID_ZCL_CLUSTER_DESC;
        ezb_zcl_cluster_desc_t custom_desc     = EZB_INVALID_ZCL_CLUSTER_DESC;

        ezb_zcl_ota_upgrade_cluster_client_config_t client_default_cfg = {
            .upgrade_server_id    = EZB_ZCL_OTA_UPGRADE_UPGRADE_SERVER_ID_DEFAULT_VALUE,
            .file_offset          = 0,
            .image_upgrade_status = EZB_ZCL_OTA_UPGRADE_IMAGE_UPGRADE_STATUS_DEFAULT_VALUE,
            .manufacturer_id      = 0x1234,
            .image_type_id        = 0x5678,
        };

        basic_desc = ezb_zcl_basic_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_SERVER);
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)"\x09""ESPRESSIF");
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)"\x07"CONFIG_IDF_TARGET);

        ezb_af_endpoint_add_cluster_desc(ep_desc, basic_desc);
        ezb_af_endpoint_add_cluster_desc(ep_desc, ezb_zcl_identify_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_SERVER));

        ota_client_desc = ezb_zcl_ota_upgrade_create_cluster_desc(&client_default_cfg, EZB_ZCL_CLUSTER_CLIENT);
        ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, ota_client_desc));
        ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));
        ESP_ERROR_CHECK(ezb_af_device_desc_register(dev_desc));

        ezb_zcl_ota_upgrade_set_download_block_size(ep_id, 223);

        ezb_zcl_core_action_handler_register(ota_upgrade_action_handler);

        return ESP_OK;
    }


The :cpp:func:`ezb_zcl_ota_upgrade_set_download_block_size` API is used to set the maximum block size that the OTA client can receive.


OTA Upgrade Commands
^^^^^^^^^^^^^^^^^^^^
The esp-zigbee-sdk provides the following APIs to implement the OTA upgrade process

Notify OTA Upgrade Image
""""""""""""""""""""""""

The :cpp:func:`ezb_zcl_ota_upgrade_image_notify_cmd_req` API notifies the network of an available OTA image identified by manufacturer code, image type, and file version.

.. code-block:: c

    ezb_err_t ota_server_notify_image(uint8_t src_ep, uint16_t manuf_code, uint16_t image_type, uint32_t file_version)
    {
        ezb_zcl_ota_upgrade_image_notify_cmd_t notify_cmd = {
            .cmd_ctrl =
                {
                    .dst_ep                = 0xFF,
                    .src_ep                = src_ep,
                    .dst_addr.addr_mode    = EZB_ADDR_MODE_SHORT,
                    .dst_addr.u.short_addr = 0xFFFD,
                    .cnf_ctx =
                        {
                            .cb       = NULL,
                            .user_ctx = NULL,
                        },
                },
            .payload =
                {
                    .type         = EZB_ZCL_OTA_UPGRADE_IMAGE_NOTIFY_PAYLOAD_TYPE_JITTER_CODE_IMAGE_VERSION,
                    .query_jitter = 100,
                    .manuf_code   = manuf_code,
                    .image_type   = image_type,
                    .file_version = file_version,
                },
        };

        return ezb_zcl_ota_upgrade_image_notify_cmd_req(&notify_cmd);
    }

Note that ``query_jitter`` controls whether a client sends a ``Query Next Image Request``: the client draws a random value and sends the request if that value is
less than ``query_jitter``.

Query OTA Upgrade Image
"""""""""""""""""""""""

The :cpp:func:`ezb_zcl_ota_upgrade_query_next_image_req_cmd_req` API is used to for ota upgrade client to query an OTA upgrade image with manufacturer code, image
type and file version from the server.

.. code-block:: c

    ezb_err_t ota_client_query_next_image( uint16_t dst_short_addr, uint8_t src_ep, uint16_t manuf_code, uint16_t image_type, uint32_t file_version)
    {
        ezb_zcl_ota_upgrade_query_next_image_req_cmd_t query_next_image_req = {
            .cmd_ctrl = {
                .dst_ep = 0xFF,
                .src_ep = src_ep,
                .dst_addr.addr_mode = EZB_ADDR_MODE_SHORT,
                .dst_addr.u.short_addr = dst_short_addr,
            },
            .payload = {
                .manuf_code = manuf_code,
                .image_type = image_type,
                .file_version = file_version,
            },
        };
        return ezb_zcl_ota_upgrade_query_next_image_cmd_req(&query_next_image_req);
    }

The ``EZB_ZCL_CORE_CMD_OTA_UPGRADE_QUERY_NEXT_IMAGE_RESP_CB_ID`` callback runs when the OTA upgrade client receives a ``Query Next Image Response``. Set
``message->out.result`` to ``EZB_ZCL_STATUS_SUCCESS`` to proceed, or use another ``ezb_zcl_status_t`` value to reject or abort as appropriate.


.. code-block:: c

    void ota_client_handle_query_next_image_resp(ezb_zcl_ota_upgrade_query_next_image_resp_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, , TAG, "Invalid message");
        if (message->in.image.status == EZB_ZCL_OTA_UPGRADE_STATUS_CODE_SUCCESS) {
            ESP_LOGI(TAG, "Query Next Image: new image (status 0x%02x)", message->in.image.status);
            ESP_LOGI(TAG, "  ep_id=%u, manuf=0x%04x, type=0x%04x, ver=0x%08lx, size=%lu B", message->in.image.ep_id,
                     message->in.image.manuf_code, message->in.image.image_type, (unsigned long)message->in.image.file_version,
                     (unsigned long)message->in.image.size);
            message->out.result = EZB_ZCL_STATUS_SUCCESS;
        } else {
            ESP_LOGW(TAG, "Query Next Image: no upgrade, status 0x%02x", message->in.image.status);
            message->out.result = EZB_ZCL_STATUS_SUCCESS;
        }
    }

Process OTA Upgrade Image Blocks
""""""""""""""""""""""""""""""""

When the **HAOUC** accepts an image offered by the **HAOUS**, it sends a ``Query Next Image Request`` to the **HAOUS** to start the download.

The ``EZB_ZCL_CORE_CMD_OTA_UPGRADE_UPLOADING_PROGRESS_CB_ID`` callback reports server-side OTA progress (uploading blocks to the client). Returning an error status
aborts the upgrade.

Three progress values cover the server-side flow; the application steers behavior by setting ``message->out`` appropriately.

- ``EZB_ZCL_OTA_UPGRADE_PROGRESS_START``: A ``Query Next Image Request`` was received from the OTA upgrade client.
- ``EZB_ZCL_OTA_UPGRADE_PROGRESS_SENDING``: An ``Image Block Request`` was received from the OTA upgrade client.
- ``EZB_ZCL_OTA_UPGRADE_PROGRESS_FINISH``: An ``Upgrade End`` command was received from the OTA upgrade client.


.. code-block:: c

    void ota_upgrade_server_handle_ota_progress(ezb_zcl_ota_upgrade_server_progress_message_t *message)
    {
        ESP_LOGI(TAG, "-- OTA Upgrade Server Progress");

        switch (message->in.progress) {
        case EZB_ZCL_OTA_UPGRADE_PROGRESS_START:
            ESP_LOGI(TAG, "OTA Query Start:");
            ESP_LOGI(TAG, "  Client: short_addr=0x%04x, ep_id=%d", message->in.start.query.short_address,
                    message->in.start.query.ep_id);
            ESP_LOGI(TAG, "  Query: manuf_code=0x%04x, image_type=0x%04x, file_version=0x%08lx, hw_version=0x%04x",
                    message->in.start.query.manuf_code, message->in.start.query.image_type, message->in.start.query.file_version,
                    message->in.start.query.hw_version);
            ESP_LOGI(TAG, "  Policy: file_version=0x%08lx", message->in.start.policy.file_version);
            // Accept the query and return the file version from policy
            message->out.result = EZB_ZCL_STATUS_SUCCESS;
            break;
        case EZB_ZCL_OTA_UPGRADE_PROGRESS_SENDING:
            ESP_LOGI(TAG, "OTA Sending Block:");
            ESP_LOGI(TAG, "  manuf_code=0x%04x, image_type=0x%04x, file_version=0x%08lx", message->in.sending.manuf_code,
                    message->in.sending.image_type, message->in.sending.file_version);
            ESP_LOGW(TAG, "Offset: %ld, Block Size: %d", message->in.sending.file_offset, message->in.sending.block_size);
            message->out.result = EZB_ZCL_STATUS_SUCCESS;
            break;
        case EZB_ZCL_OTA_UPGRADE_PROGRESS_FINISH:
            ESP_LOGI(TAG, "OTA Upgrade End:");
            ESP_LOGI(TAG, "  status=0x%02x, manuf_code=0x%04x, image_type=0x%04x, file_version=0x%08lx", message->in.finish.status,
                    message->in.finish.manuf_code, message->in.finish.image_type, message->in.finish.file_version);
            message->out.finish.current_time = 0; // Application should set actual current time
            message->out.finish.upgrade_time = 0; // Application should set actual upgrade time (0 = immediate)
            message->out.result              = EZB_ZCL_STATUS_SUCCESS;
            break;
        case EZB_ZCL_OTA_UPGRADE_PROGRESS_ABORT:
            ESP_LOGW(TAG, "OTA Abort");
            message->out.result = EZB_ZCL_STATUS_SUCCESS;
            break;
        default:
            ESP_LOGW(TAG, "Unknown OTA progress status: %d", message->in.progress);
            message->out.result = EZB_ZCL_STATUS_SUCCESS;
            break;
        }
    }

After the OTA image is validated and approved in the ``EZB_ZCL_CORE_CMD_OTA_UPGRADE_QUERY_NEXT_IMAGE_RESP_CB_ID`` handler, the **HAOUC** continues the upgrade with
the **HAOUS**.

The ``EZB_ZCL_CORE_CMD_OTA_UPGRADE_DOWNLOADING_PROGRESS_CB_ID`` callback reports client-side progress while the image is downloaded and applied.

Five progress values cover the client-side flow; set ``message->out`` as appropriate. Any error status aborts the upgrade.

- ``EZB_ZCL_OTA_UPGRADE_PROGRESS_START``: A ``Query Next Image Response`` was received from the OTA upgrade server.
- ``EZB_ZCL_OTA_UPGRADE_PROGRESS_RECEIVING``: An ``Image Block Response`` was received from the OTA upgrade server.
- ``EZB_ZCL_OTA_UPGRADE_PROGRESS_CHECK``: All image blocks were received and verified.
- ``EZB_ZCL_OTA_UPGRADE_PROGRESS_APPLY``: An ``Upgrade End Response`` was received from the OTA upgrade server.
- ``EZB_ZCL_OTA_UPGRADE_PROGRESS_FINISH``: No further OTA file is required; the client upgrade sequence is complete.

.. code-block:: c

    void ota_upgrade_client_handle_ota_progress(ezb_zcl_ota_upgrade_client_progress_message_t *message)
    {
        ESP_LOGI(TAG, "-- OTA Upgrade Client Progress");

        switch (message->in.progress) {
        case EZB_ZCL_OTA_UPGRADE_PROGRESS_START:
            ESP_LOGI(TAG, "OTA Start: manuf_code=0x%04x, image_type=0x%04x, file_version=0x%08lx, image_size=%ld",
                    message->in.start.manuf_code, message->in.start.image_type, message->in.start.file_version,
                    message->in.start.image_size);

            break;
        case EZB_ZCL_OTA_UPGRADE_PROGRESS_RECEIVING:
            ESP_LOGI(TAG, "OTA Receiving Block: file_offset=%ld, block_size=%d", message->in.receiving.file_offset,
                    message->in.receiving.block_size);
            break;
        case EZB_ZCL_OTA_UPGRADE_PROGRESS_CHECK:
            ESP_LOGI(TAG, "OTA Check: manuf_code=0x%04x, image_type=0x%04x, file_version=0x%08lx", message->in.check.manuf_code,
                    message->in.check.image_type, message->in.check.file_version);
            break;
        case EZB_ZCL_OTA_UPGRADE_PROGRESS_APPLY:
            ESP_LOGI(TAG, "OTA Apply: manuf_code=0x%04x, image_type=0x%04x, file_version=0x%08lx", message->in.apply.manuf_code,
                    message->in.apply.image_type, message->in.apply.file_version);
            break;
        case EZB_ZCL_OTA_UPGRADE_PROGRESS_FINISH:
            ESP_LOGI(TAG, "OTA Finish: count_down_delay=%ld seconds", message->in.finish.count_down_delay);
            esp_restart();
            break;
        case EZB_ZCL_OTA_UPGRADE_PROGRESS_ABORT:
            ESP_LOGW(TAG, "OTA Abort");
            break;
        default:
            ESP_LOGW(TAG, "Unknown OTA progress status: %d", message->in.progress);
            break;
        }

        message->out.result = EZB_ZCL_STATUS_SUCCESS;
    }

For more information on applying a firmware image on ESP platforms, see the `ESP-IDF OTA API <https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/ota.html>`__ documentation.

More details please see examples:

:example_file:`ota_client <ota_upgrade/ota_client/main/ota_client.c>`

:example_file:`ota_server <ota_upgrade/ota_server/main/ota_server.c>`


OTA Upgrade Rate Optimization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Several techniques can improve OTA upgrade throughput and reliability.

General Optimization
^^^^^^^^^^^^^^^^^^^^

- Adjust the ``OTA_UPGRADE_MAX_DATA_SIZE`` to improve frame exchange; a value of 223 is recommended.
- Increase the ``FREERTOS_HZ`` in menuconfig to enhance the system's response rate. The default value is 100.
- Enable the ``IEEE802154_TIMING_OPTIMIZATION`` in menuconfig to optimize IEEE802154 timing.
- Reduce unrelated logs during the OTA upgrade process.

In testing, the optimizations above raised OTA throughput to about 8.1 KB/s.

Delta OTA
^^^^^^^^^
Delta OTA transmits only the differences between an old and a new firmware image instead of the full image. That reduces airtime and is especially
helpful for low-bandwidth, low-power IoT links.

If you need to upgrade the firmware running on the chip with less changes, enabling Delta OTA feature will be effective.

Refer to `Delta OTA Upgrade Functions <https://github.com/espressif/esp-zigbee-sdk/tree/main/examples/esp_zigbee_ota/ota_client#delta-ota-upgrade-functions>`__
for instructions on enabling delta OTA.
