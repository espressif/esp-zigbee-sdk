5.3 Zigbee ZCL Custom Cluster
-----------------------------

5.3.1 Overview
~~~~~~~~~~~~~~~
Zigbee Cluster Library (ZCL) defines a set of standardized functions based on common application scenarios and classic device characteristic, known as clusters.
Each cluster represents a group of related attributes and commands.

However, standard clusters cannot cover everything. In some special scenarios, the standard clusters cannot fully meet the developers' needs.
Therefore, the functionality of custom clusters has emerged.

Such clusters do not have clearly defined attributes and commands in ZCL, requiring developers to create their own specific attributes, commands, and corresponding handling functions. 

This chapter will introduce a series of APIs provided by the esp-zigbee-sdk for custom clusters and their usage.


5.3.2 Related APIs Preview
~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following APIs are related to the main implementation of the custom cluster.

- :cpp:func:`esp_zb_zcl_attr_list_create`
- :cpp:func:`esp_zb_custom_cluster_add_custom_attr`
- :cpp:func:`esp_zb_cluster_list_add_custom_cluster`
- :cpp:func:`esp_zb_zcl_custom_cluster_handlers_update`
- :cpp:func:`esp_zb_zcl_custom_cluster_cmd_req`
- :cpp:func:`esp_zb_zcl_custom_cluster_cmd_resp`
- :cpp:func:`esp_zb_core_action_handler_register`

5.3.3  Typical Usage
~~~~~~~~~~~~~~~~~~~~
This section will introduce the typical usage of a custom cluster, including the data model creation process, related commands, and handlers.

5.3.3.1 Custom Cluster Creation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you intend to **create** a custom server cluster identifier (0xff00) with a REPORT and WRITE access string attribute (0x0000) and a READ_WRITE access 16-bit attribute (0x0001)
on an endpoint device (0x01) for a **Home Automation Custom Server Device (HACS Device)**, you can follow the code below:

.. code-block:: c

    #define CUSTOM_SERVER_ENDPOINT 0x01
    #define CUSTOM_CLIENT_ENDPOINT 0x01
    #define CUSTOM_CLUSTER_ID 0xff00
    #define CUSTOM_COMMAND_RESP 0x0001
    esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = CUSTOM_SERVER_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_CUSTOM_ATTR_DEVICE_ID,
        .app_device_version = 0,
    };
    esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();
    esp_zb_attribute_list_t *custom_cluster = esp_zb_zcl_attr_list_create(CUSTOM_CLUSTER_ID);
    uint16_t custom_attr1_id = 0x0000;
    uint8_t custom_attr1_value[] = "\x0b""hello world";
    uint16_t custom_attr2_id = 0x0001;
    uint16_t custom_attr2_value = 0x1234;
    esp_zb_custom_cluster_add_custom_attr(custom_cluster, custom_attr1_id, ESP_ZB_ZCL_ATTR_TYPE_CHAR_STRING,
                                          ESP_ZB_ZCL_ATTR_ACCESS_WRITE_ONLY | ESP_ZB_ZCL_ATTR_ACCESS_REPORTING, custom_attr1_value);
    esp_zb_custom_cluster_add_custom_attr(custom_cluster, custom_attr2_id, ESP_ZB_ZCL_ATTR_TYPE_U16, ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE,
                                          &custom_attr2_value);

    /* Mandatory clusters */
    esp_zb_cluster_list_add_basic_cluster(cluster_list, esp_zb_basic_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_identify_cluster(cluster_list, esp_zb_identify_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    /* Custom cluster */
    esp_zb_cluster_list_add_custom_cluster(cluster_list, custom_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);

    esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config);
    esp_zb_device_register(ep_list);


If you intend to **create** a custom client cluster (0xff00) without any attributes on endpoint device (0x01) for a **Home Automation Custom Client Device (HACC Device)**,
you can refer to the code below:

.. code-block:: c

    #define CUSTOM_SERVER_ENDPOINT 0x01
    #define CUSTOM_CLIENT_ENDPOINT 0x01
    #define CUSTOM_CLUSTER_ID 0xff00
    #define CUSTOM_COMMAND_REQ 0x0000
    esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = CUSTOM_CLIENT_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_CUSTOM_ATTR_DEVICE_ID,
        .app_device_version = 0,
    };
    esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();
    esp_zb_attribute_list_t *custom_cluster = esp_zb_zcl_attr_list_create(CUSTOM_CLUSTER_ID);

    /* Mandatory clusters */
    esp_zb_cluster_list_add_basic_cluster(cluster_list, esp_zb_basic_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_identify_cluster(cluster_list, esp_zb_identify_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    /* Custom cluster */
    esp_zb_cluster_list_add_custom_cluster(cluster_list, custom_cluster, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);
    esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config);
    esp_zb_device_register(ep_list);

Please note that the custom cluster identifier MUST be greater than :c:macro:`ESP_ZB_CUSTOM_CLUSTER_ID_MIN_VAL` in esp-zigbee-sdk.


5.3.3.2 Custom Attribute Checking Hooks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you need to **check** and **limit** the write operations for your custom cluster from a remote device and **verify** whether the written value is within a specified range,
you can call :cpp:func:`esp_zb_zcl_custom_cluster_handlers_update` to add the cluster handler to implement this functionality. Refer to the code below:

.. code-block:: c

    static int zb_zcl_custom_cluster_check_value_handler(uint16_t attr_id, uint8_t endpoint, uint8_t *value)
    {
        esp_err_t ret = ESP_OK;
        ESP_LOGI(TAG, "Hook for checking custom cluster attribute validity");
        return ret;
    }

    static void zb_zcl_custom_cluster_write_attr_handler(uint8_t endpoint, uint16_t attr_id, uint8_t *new_value, uint16_t manuf_code)
    {
        ESP_LOGI(TAG, "Hook for indicating which attribute will be written");
    }

    esp_zb_zcl_custom_cluster_handlers_t custom_handler = {
        .cluster_id = CUSTOM_CLUSTER_ID,
        .cluster_role = ESP_ZB_ZCL_CLUSTER_SERVER_ROLE,
        .check_value_cb = zb_zcl_custom_cluster_check_value_handler,
        .write_attr_cb = zb_zcl_custom_cluster_write_attr_handler,
    };
    esp_zb_zcl_custom_cluster_handlers_update(custom_handler);

Please note that if the return value of ``zb_zcl_custom_cluster_check_value_handler()`` is not ``ESP_OK``, the write operation will be halted.


5.3.3.3 Custom Command Requests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you have already created a custom client cluster on the **HACC Device** and you want to **send** a custom command to the **HACS Device**,
you can follow the code below:

.. code-block:: c

    esp_zb_zcl_custom_cluster_cmd_req_t req;
    uint8_t custom_value[] = "\x0e""Hi, espressif";
    req.zcl_basic_cmd.dst_addr_u.addr_short = 0x1234; // Set it according to the actual destination short address.
    req.zcl_basic_cmd.dst_endpoint = CUSTOM_SERVER_ENDPOINT;
    req.zcl_basic_cmd.src_endpoint = CUSTOM_CLIENT_ENDPOINT;
    req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    req.cluster_id = CUSTOM_CLUSTER_ID;
    req.profile_id = ESP_ZB_AF_HA_PROFILE_ID;
    req.direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV;
    req.custom_cmd_id = CUSTOM_COMMAND_REQ;
    req.data.type = ESP_ZB_ZCL_ATTR_TYPE_CHAR_STRING;
    req.data.size = sizeof(custom_value);
    req.data.value = custom_value;
    esp_zb_lock_acquire(portMAX_DELAY);
    esp_zb_zcl_custom_cluster_cmd_req(&req);
    esp_zb_lock_release();
    ESP_EARLY_LOGI(TAG, "Send %s to custom device", custom_value);


5.3.3.4 Custom Command Handlers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you have already created the **HACS Device** and a ZCL command with a custom cluster is **received** on this device with the direction set to ``ESP_ZB_ZCL_CLUSTER_SERVER_ROLE``,
the ``ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_REQ_CB_ID`` signal will be triggered in :cpp:func:`esp_zb_core_action_handler_register`. If you want to **extract** the payload of
this command, **set** it to the attribute with identifier (0x0000) to trigger a **report** for the new attribute, and then **respond** with "Done" to the sender, you can refer to
the code below.

.. code-block:: c

    static void bind_cb(esp_zb_zdp_status_t zdo_status, void *user_ctx)
    {
        if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
            /* Set payload to custom attribute */
            if (user_ctx) {
                esp_zb_zcl_set_attribute_val(CUSTOM_SERVER_ENDPOINT, CUSTOM_CLUSTER_ID, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE, 0x0000, user_ctx, false);
                free(user_ctx);
            }
            /* Response custom command */
            esp_zb_zcl_custom_cluster_cmd_resp_t resp;
            uint8_t custom_value[] = "\x05""Done";
            resp.zcl_basic_cmd.src_endpoint = CUSTOM_SERVER_ENDPOINT;
            resp.address_mode = ESP_ZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT;
            resp.profile_id = ESP_ZB_AF_HA_PROFILE_ID;
            resp.cluster_id = CUSTOM_CLUSTER_ID;
            resp.direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV;
            resp.custom_cmd_id = CUSTOM_COMMAND_RESP;
            resp.data.type = ESP_ZB_ZCL_ATTR_TYPE_CHAR_STRING;
            resp.data.size = sizeof(custom_value);
            resp.data.value = custom_value;
            esp_zb_zcl_custom_cluster_cmd_resp(&resp);
            ESP_EARLY_LOGI(TAG, "Send %s to address: 0x%04x", custom_value, resp.zcl_basic_cmd.dst_addr_u.addr_short);
        }
    }

    static esp_err_t zb_custom_request_handler(const esp_zb_zcl_custom_cluster_command_message_t *message)
    {
        esp_err_t ret = ESP_OK;

        ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                            message->info.status);
        ESP_LOGI(TAG, "Receive custom command: %d from address 0x%04hx", message->info.command.id, message->info.src_address.u.short_addr);
        ESP_LOGI(TAG, "Payload size: %d", message->data.size);
        ESP_LOG_BUFFER_CHAR(TAG, ((uint8_t *)message->data.value) + 1, message->data.size - 1);

        /* Add bind information for attribute report */
        esp_zb_zdo_bind_req_param_t bind_req;
        esp_zb_get_long_address(bind_req.src_address);
        bind_req.src_endp = message->info.dst_endpoint;
        bind_req.cluster_id = CUSTOM_CLUSTER_ID;
        bind_req.dst_addr_mode = ESP_ZB_ZDO_BIND_DST_ADDR_MODE_64_BIT_EXTENDED;
        esp_zb_ieee_address_by_short(message->info.src_address.u.short_addr, bind_req.dst_address_u.addr_long);
        bind_req.dst_endp = message->info.src_endpoint;
        bind_req.req_dst_addr = esp_zb_get_short_address();
        uint8_t *user_ctx = malloc(message->data.size);
        memcpy(user_ctx, message->data.value, message->data.size);
        esp_zb_zdo_device_bind_req(&bind_req, bind_cb, user_ctx);
        return ret;
    }

    static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
    {
        esp_err_t ret = ESP_OK;
        switch (callback_id) {
        case ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_REQ_CB_ID:
            ret = zb_custom_request_handler((esp_zb_zcl_custom_cluster_command_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
        }
        return ret;
    }

If you expect to **parse** and **handle** the report attribute information and custom response command from the **HACS Device** on **HACC Device**, you need to **register**
:cpp:func:`esp_zb_core_action_handler_register` you can refer to below code:

.. code-block:: c

    static esp_err_t zb_attribute_reporting_handler(const esp_zb_zcl_report_attr_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                            message->status);
        ESP_LOGI(TAG, "Received report from address(0x%x) src endpoint(%d) to dst endpoint(%d) cluster(0x%x)", message->src_address.u.short_addr,
                message->src_endpoint, message->dst_endpoint, message->cluster);
        ESP_LOGI(TAG, "Received report information: attribute(0x%x), type(0x%x)", message->attribute.id, message->attribute.data.type);
        ESP_LOG_BUFFER_CHAR(TAG, ((uint8_t *)message->attribute.data.value) + 1, message->attribute.data.size - 1);

        return ESP_OK;
    }

    static esp_err_t zb_custom_response_handler(const esp_zb_zcl_custom_cluster_command_message_t *message)
    {
        esp_err_t ret = ESP_OK;

        ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                            message->info.status);
        ESP_LOGI(TAG, "Receive custom command: %d from address 0x%04hx", message->info.command.id, message->info.src_address.u.short_addr);
        ESP_LOGI(TAG, "Payload size: %d", message->data.size);
        ESP_LOG_BUFFER_CHAR(TAG, ((uint8_t *)message->data.value) + 1, message->data.size - 1);
        return ret;
    }

    static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
    {
        esp_err_t ret = ESP_OK;
        switch (callback_id) {
        case ESP_ZB_CORE_REPORT_ATTR_CB_ID:
            ret = zb_attribute_reporting_handler((esp_zb_zcl_report_attr_message_t *)message);
            break;
        case ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_RESP_CB_ID:
            ret = zb_custom_response_handler((esp_zb_zcl_custom_cluster_command_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
        }
        return ret;
    }

Please note that if the direction of the custom command is ``ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV`` / ``ESP_ZB_ZCL_CMD_DIRECTION_TO_CLI`` and its destination
cluster is ``ESP_ZB_ZCL_CLUSTER_SERVER_ROLE`` / ``ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE``, the ``ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_REQ_CB_ID`` signal will be triggered.
Otherwise, ``ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_RESP_CB_ID`` will be triggered.
