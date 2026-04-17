Zigbee ZCL Groups Cluster
-------------------------

Overview
~~~~~~~~
The Zigbee protocol stack defines various device instances based on different profiles and scenarios.
In Zigbee, these are abstracted into logic instance name as endpoints, with each endpoint performing its role
within the network, working together to achieve the user-designed application scenarios.

However, in complex application scenario, a network may contain a large number of endpoints distributed across
different devices. To organize and coordinate the work between these endpoints, the Zigbee ZCL defines the groups
cluster, allowing developers to arrange the endpoints within the network into groups.

The Zigbee group functionality is primarily implemented in the APS layer. The ZCL Groups cluster provides an
application-level method to manage groups within the network. This chapter will focus on explaining the usage
of groups from the ZCL perspective.


Related APIs Preview
~~~~~~~~~~~~~~~~~~~~
The following APIs are related to the main implementation of the ZCL groups cluster.

- :cpp:func:`ezb_zcl_groups_create_cluster_desc`
- :cpp:func:`ezb_zcl_groups_cluster_desc_add_attr`
- :cpp:func:`ezb_zcl_groups_cluster_desc_add_manuf_attr`
- :cpp:func:`ezb_zcl_groups_cluster_client_init`
- :cpp:func:`ezb_zcl_groups_cluster_server_init`
- :cpp:func:`ezb_zcl_groups_add_group_cmd_req`
- :cpp:func:`ezb_zcl_groups_remove_cmd_req`
- :cpp:func:`ezb_zcl_groups_remove_all_groups_cmd_req`
- :cpp:func:`ezb_zcl_groups_view_group_cmd_req`
- :cpp:func:`ezb_zcl_groups_get_group_membership_cmd_req`
- :cpp:func:`ezb_zcl_core_action_handler_register`
- :cpp:func:`ezb_zcl_on_off_toggle_cmd_req`

Typical Usage
~~~~~~~~~~~~~
This section will introduce the typical usage of a groups cluster, including the data model creation process, related commands,
and handlers.

A groupcast application will be introduced, utilizing the groups cluster.

Groups Cluster Creation
^^^^^^^^^^^^^^^^^^^^^^^

A **Home Automation Light Device (HAL Device)** contains a groups server cluster with the mandatory attributes, you can refer to the code below to create it.

.. code-block:: c

    static ezb_err_t ha_on_off_light_setup(uint8_t ep_id)
    {
        ezb_af_device_desc_t dev_desc = ezb_af_create_device_desc();
        ezb_af_ep_desc_t ep_desc = {0};
        ezb_zha_on_off_light_config_t light_cfg = EZB_ZHA_ON_OFF_LIGHT_CONFIG();
        ep_desc = ezb_zha_create_on_off_light(ep_id, &light_cfg);

        ezb_zcl_cluster_desc_t basic_desc = ezb_af_endpoint_get_cluster_desc(ep_desc, EZB_ZCL_CLUSTER_ID_BASIC, EZB_ZCL_CLUSTER_SERVER);
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)"\x09""ESPRESSIF");
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)"\x07"CONFIG_IDF_TARGET);

        ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));
        return ezb_af_device_desc_register(dev_desc);
    }


A groups cluster client is required to add the **Home Automation Switch Device (HAS Device)** to ensure it has capacity to manage groups, the code below can
be used as a reference.

.. code-block:: c

    static ezb_err_t ha_on_off_switch_setup(uint8_t ep_id)
    {
        ezb_af_device_desc_t dev_desc = ezb_af_create_device_desc();
        ezb_af_ep_desc_t ep_desc = {0};
        ezb_zha_on_off_switch_config_t switch_cfg = EZB_ZHA_ON_OFF_SWITCH_CONFIG();
        ep_desc = ezb_zha_create_on_off_switch(ep_id, &switch_cfg);

        ezb_zcl_cluster_desc_t basic_desc = ezb_af_endpoint_get_cluster_desc(ep_desc, EZB_ZCL_CLUSTER_ID_BASIC, EZB_ZCL_CLUSTER_SERVER);
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)"\x09""ESPRESSIF");
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)"\x07"CONFIG_IDF_TARGET);
        ezb_zcl_cluster_desc_t groups_desc = ezb_zcl_groups_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_CLIENT);
        ezb_af_endpoint_add_cluster_desc(ep_desc, groups_desc);

        ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));
        return ezb_af_device_desc_register(dev_desc);
    }


Groups Commands Request and Response
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Add Group Request

If a **HAS Device** have been registered to the stack by calling :cpp:func:`ezb_af_device_desc_register`, the :cpp:func:`ezb_zcl_groups_add_group_cmd_req`
can be sent from the **HAS Device** to the **HAL Device** to add a group, the code below can be used as a reference.

.. code-block:: c

    static ezb_err_t switch_send_add_group_cmd(uint8_t src_ep, uint8_t dst_ep, uint16_t dst_short_addr, uint16_t group_id)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_groups_add_group_cmd_t add_group_cmd = {
            .cmd_ctrl = {
                .dst_addr = {.addr_mode = EZB_ADDR_MODE_SHORT, .u.short_addr = dst_short_addr},
                .src_ep = src_ep,
                .dst_ep = dst_ep,
            },
            .payload = {.group_id = group_id},
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_groups_add_group_cmd_req(&add_group_cmd);
        esp_zigbee_lock_release();
        return ret;
    }


- Add Group Response

The ``EZB_ZCL_CORE_GROUPS_ADD_GROUP_RSP_CB_ID`` will be triggered by the handler registered with :cpp:func:`ezb_zcl_core_action_handler_register` when an
``Add Group Response`` arrives on the **HAS Device**. You can check and handle the response in the callback function. Below code can be used as a reference:

.. code-block:: c

    static void switch_handle_add_group_resp(ezb_zcl_groups_add_group_rsp_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, , TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == EZB_ZCL_STATUS_SUCCESS, , TAG,
                            "Add Group response error status(%d)", message->info.status);
        ESP_LOGI(TAG, "Add Group response: group_id 0x%04x, status 0x%02x", message->in.group_id, message->in.status);
    }

    static void zcl_action_handler(ezb_zcl_core_action_callback_id_t callback_id, void *message)
    {
        switch (callback_id) {
        case EZB_ZCL_CORE_GROUPS_ADD_GROUP_RSP_CB_ID:
            switch_handle_add_group_resp((ezb_zcl_groups_add_group_rsp_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "ZCL core action 0x%x", callback_id);
            break;
        }
    }

Please note that Zigbee device group relationships are non-volatile and stored persistently in NVRAM.


- View Group Request

The :cpp:func:`ezb_zcl_groups_view_group_cmd_req` can be used to view the application name string for the specific group on the **HAL Device**. Below code can be
used as a reference:

.. code-block:: c

    static ezb_err_t switch_send_view_group_cmd(uint8_t src_ep, uint8_t dst_ep, uint16_t dst_short_addr, uint16_t group_id)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_groups_view_group_cmd_t cmd = {
            .cmd_ctrl =
                {
                    .dst_addr = {.addr_mode = EZB_ADDR_MODE_SHORT, .u.short_addr = dst_short_addr},
                    .src_ep   = src_ep,
                    .dst_ep   = dst_ep,
                },
            .payload = {.group_id = group_id},
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_groups_view_group_cmd_req(&cmd);
        esp_zigbee_lock_release();
        return ret;
    }


- View Group Response

The ``EZB_ZCL_CORE_GROUPS_VIEW_GROUP_RSP_CB_ID`` will be triggered by the handler registered with :cpp:func:`ezb_zcl_core_action_handler_register` when a
``View Group Response`` arrives on the **HAS Device**. You can check and handle the response in the callback function. Below code can be used as a reference:

.. code-block:: c

    static void switch_handle_view_group_resp(ezb_zcl_groups_view_group_rsp_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, , TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == EZB_ZCL_STATUS_SUCCESS, , TAG,
                            "View group response error status(%d)", message->info.status);
        ESP_LOGI(TAG, "View group: id 0x%04x");
        if (message->in.group_name) {
            ESP_LOG_BUFFER_CHAR("Group name", message->in.group_name, strlen(message->in.group_name));
        } else {
            ESP_LOGI(TAG, "Group name: (none)");
        }
    }

    static void zcl_action_handler(ezb_zcl_core_action_callback_id_t callback_id, void *message)
    {
        switch (callback_id) {
        case EZB_ZCL_CORE_GROUPS_VIEW_GROUP_RSP_CB_ID:
            switch_handle_view_group_resp((ezb_zcl_groups_view_group_rsp_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "ZCL core action 0x%x", callback_id);
            break;
        }
    }

- Group membership Request

The :cpp:func:`ezb_zcl_groups_get_group_membership_cmd_req` can be used to inquire about the group capacity of the **HAL Device** and the relationship between
the specific endpoint and the group list. If ``payload.group_count`` is zero, the response lists all groups for that endpoint. Below code can be used as a reference:

.. code-block:: c

    static ezb_err_t switch_send_get_group_membership_cmd(uint8_t src_ep, uint8_t dst_ep, uint16_t dst_short_addr)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_groups_get_group_membership_cmd_t cmd = {
            .cmd_ctrl =
                {
                    .dst_addr = {.addr_mode = EZB_ADDR_MODE_SHORT, .u.short_addr = dst_short_addr},
                    .src_ep   = src_ep,
                    .dst_ep   = dst_ep,
                },
            .payload =
                {
                    .group_count = 0,
                    .group_list  = NULL,
                },
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_groups_get_group_membership_cmd_req(&cmd);
        esp_zigbee_lock_release();
        return ret;
    }


- Group membership Response

The ``EZB_ZCL_CORE_GROUPS_GET_GROUP_MEMBERSHIP_RSP_CB_ID`` will be triggered by the handler registered with :cpp:func:`ezb_zcl_core_action_handler_register` when
a ``Group Membership Response`` arrives on the **HAS Device**. You can check and handle the response in the callback function. Below code can be used as a reference:

.. code-block:: c

    static void switch_handle_get_group_membership_rsp(ezb_zcl_groups_get_group_membership_rsp_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, , TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == EZB_ZCL_STATUS_SUCCESS, , TAG,
                            "Get group membership response error status(%d)", message->info.status);
        ESP_LOGI(TAG, "Group membership capacity %u, count %u", message->in.capacity, message->in.group_count);
        if (message->in.header) {
            ESP_LOGI(TAG, "From src ep %u", message->in.header->src_ep);
        }
        for (uint8_t i = 0; i < message->in.group_count && message->in.group_list; i++) {
            ESP_LOGI(TAG, "  [%u] group 0x%04x", i, message->in.group_list[i]);
        }
    }

    static void zcl_action_handler(ezb_zcl_core_action_callback_id_t callback_id, void *message)
    {
        switch (callback_id) {
        case EZB_ZCL_CORE_GROUPS_GET_GROUP_MEMBERSHIP_RSP_CB_ID:
            switch_handle_get_group_membership_rsp((ezb_zcl_groups_get_group_membership_rsp_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "ZCL core action 0x%x", callback_id);
            break;
        }
    }


- Remove Group Request

The :cpp:func:`ezb_zcl_groups_remove_cmd_req` can be used to remove the specific endpoint from the specific group on the **HAL Device**. Below code can be used as
a reference:

.. code-block:: c

    static ezb_err_t switch_send_remove_group_cmd(uint8_t src_ep, uint8_t dst_ep, uint16_t dst_short_addr, uint16_t group_id)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_groups_remove_group_cmd_t cmd = {
            .cmd_ctrl =
                {
                    .dst_addr = {.addr_mode = EZB_ADDR_MODE_SHORT, .u.short_addr = dst_short_addr},
                    .src_ep   = src_ep,
                    .dst_ep   = dst_ep,
                },
            .payload = {.group_id = group_id},
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_groups_remove_cmd_req(&cmd);
        esp_zigbee_lock_release();
        return ret;
    }

- Remove Group Response

The ``EZB_ZCL_CORE_GROUPS_REMOVE_GROUP_RSP_CB_ID`` will be triggered by the handler registered with :cpp:func:`ezb_zcl_core_action_handler_register` when
a ``Remove Group Response`` arrives on the **HAS Device**. You can check and handle the response in the callback function. Below code can be used as a reference:


- Remove All Groups Request

The :cpp:func:`ezb_zcl_groups_remove_all_groups_cmd_req` can be used to remove all group memberships from the **HAL Device**. Below code can be used as a reference:

.. code-block:: c

    static ezb_err_t switch_send_remove_all_groups_cmd(uint8_t src_ep, uint8_t dst_ep, uint16_t dst_short_addr)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_groups_remove_all_groups_cmd_t cmd = {
            .cmd_ctrl =
                {
                    .dst_addr = {.addr_mode = EZB_ADDR_MODE_SHORT, .u.short_addr = dst_short_addr},
                    .src_ep   = src_ep,
                    .dst_ep   = dst_ep,
                },
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_groups_remove_all_groups_cmd_req(&cmd);
        esp_zigbee_lock_release();
        return ret;
    }

- Remove All Groups Response

The response is not required for the ``Remove All Groups Request``.


Group Cast
^^^^^^^^^^
The ZCL Groups cluster provides group management functionality, enabling developers to implement group casting functionality, which allows a Zigbee command to be
sent from one endpoint to multiple endpoints simultaneously. For example, if you have three devices (two HAL Devices and one HAS Device) and you want to use group
casting to control the lights of the **HAL Devices** from the **HAS Device**, you can follow these steps:

- **HAL Devices** send :cpp:func:`ezb_zcl_groups_add_group_cmd_req` to **HAS Device** to add the specific endpoint to the group.
- If the **HAS Device** receives the **Add Group Request** successfully, it will send a **Add Group Response** to the **HAL Device**.
- **HAS Device** send :cpp:func:`ezb_zcl_on_off_toggle_cmd_req` with ``EZB_ADDR_MODE_GROUP`` mode to **HAL Devices** to toggle the lights.

.. code-block:: c

    static ezb_err_t switch_groupcast_on_off_toggle(uint8_t src_ep, uint16_t group_id)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_on_off_cmd_t cmd_req = {
            .cmd_ctrl =
                {
                    .dst_addr =
                        {
                            .addr_mode = EZB_ADDR_MODE_GROUP,
                            .u.group_addr =
                                {
                                    .group = group_id,
                                    .bcast = 0xfffd,
                                },
                        },
                    .src_ep             = src_ep,
                },
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_on_off_toggle_cmd_req(&cmd_req);
        esp_zigbee_lock_release();
        return ret;
    }


The destination is a ``group address`` (EZB_ADDR_MODE_GROUP), not a device short address; there is no per-device destination endpoint in the APS frame.

Since group casting is performed via a broadcast to all devices for which **macRxOnWhenIdle = TRUE**, sleeping end devices will not be able to benefit from the
features of the Groups and Scenes server cluster.
