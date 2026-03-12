Zigbee ZCL Scenes Cluster
-------------------------


Overview
~~~~~~~~

Scenes are predefined configurations of device attributes, such as brightness, color, and switch status, aimed at creating specific environmental settings,
like room lighting. The Zigbee Cluster Library (ZCL) defines a standard Scenes Cluster, enabling devices to work together seamlessly to achieve such
configurations.

ZCL Scenes are typically associated with a specific group ID, representing a set of stored attributes for one or more cluster instances. These instances
can span multiple devices. Standard scene commands facilitate the efficient configuration and management of the Scene Table, simplifying control over
devices and scene settings.

This chapter aims to explain the implementation mechanism of the Scenes Cluster within the esp-zigbee-sdk, introduce the typical usage of scene commands,
and demonstrate practical applications of scenes.


Related APIs Preview
~~~~~~~~~~~~~~~~~~~~
The following APIs are central to the ZCL Scenes cluster in esp-zigbee-sdk.

- :cpp:func:`ezb_zcl_create_attr_desc`
- :cpp:func:`ezb_zcl_scenes_cluster_desc_add_attr`
- :cpp:func:`ezb_zcl_scenes_create_cluster_desc`
- :cpp:func:`ezb_af_endpoint_add_cluster_desc`
- :cpp:func:`ezb_zcl_scenes_add_scene_cmd_req`
- :cpp:func:`ezb_zcl_scenes_remove_scene_cmd_req`
- :cpp:func:`ezb_zcl_scenes_remove_all_scenes_cmd_req`
- :cpp:func:`ezb_zcl_scenes_view_scene_cmd_req`
- :cpp:func:`ezb_zcl_scenes_store_scene_cmd_req`
- :cpp:func:`ezb_zcl_scenes_recall_scene_cmd_req`
- :cpp:func:`ezb_zcl_scenes_get_scene_membership_cmd_req`
- :cpp:func:`ezb_zcl_scenes_table_store`
- :cpp:func:`ezb_zcl_core_action_handler_register`


Scenes Context Relationship
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section introduces the contextual relationships between scenes, groups, and clusters, offering a detailed understanding of how they work together to
support scene-based applications.


Scenes and Groups
^^^^^^^^^^^^^^^^^
A group is a collection of endpoints that may span multiple devices, defining the scope for an application scene. Typically, scenes are associated with a
specific group ID to facilitate their organization and management. However, scenes can also exist without being tied to a group. In such cases, the group
ID is replaced by the value 0x0000. Scene-related commands for these scenarios can only be sent as unicast messages and cannot be multicast or broadcast.

In such situations, extra care is required to avoid scene ID collisions. This means that the scene ID must remain unique either within the group or, if no
group is present, within the relevant application scope. Maintaining this uniqueness ensures proper functionality and avoids conflicts when managing scenes.

Scenes and Endpoint
^^^^^^^^^^^^^^^^^^^
An endpoint represents a device instance that participates in scenes. Endpoints with a Scenes Cluster can be grouped into a specific set using the Group
Cluster, allowing predefined scenes to be established.

The Scenes Cluster server is responsible for receiving commands to manage scenes, including storing, recalling, or deleting scene configurations. On the
other hand, the Scenes Cluster client sends commands to the server, enabling read or write access to scenes for configuration or control purposes.

Scenes and Attribute
^^^^^^^^^^^^^^^^^^^^
The ZCL specifies which attributes within a cluster should be used as entries for a Scene. For instance, the ``On/Off`` attribute (0x0001) of the On/Off
Cluster (0x0006) and the CurrentLevel attribute (0x0000) of the Level Control Cluster (0x0008) are standard entries defined by the ZCL.

In contrast, the esp-zigbee-sdk offers greater flexibility by not restricting which attributes can serve as scene entries. This allows users to design
custom scenes tailored to their specific application requirements.

Scenes and Scene Table
^^^^^^^^^^^^^^^^^^^^^^
In the esp-zigbee-sdk, the Scene Table is managed internally and shared across the device. Developers can interact with the Scene Table using the provided
APIs, enabling efficient scene configuration and management.


Typical Usage
~~~~~~~~~~~~~
This section introduces the typical usage of the Scene Cluster, covering the process of creating a data model, related commands, and their handlers.
Additionally, an application example will demonstrate how to switch between two scenes to control the light level.

Scenes Cluster Creation
^^^^^^^^^^^^^^^^^^^^^^^

The Scene Client Cluster serves as the foundation for configuring scenes on remote devices. The below code shows how to create an endpoint with the Scene
Cluster that can still control a light's status and brightness, let’s call this implementation the **Scene Switch**.

.. code-block:: c

    static esp_err_t ha_on_off_switch_create(uint8_t ep_id)
    {
        ezb_af_device_desc_t dev_desc = ezb_af_create_device_desc();
        ezb_af_ep_desc_t ep_desc = {0};
        ezb_zha_on_off_switch_config_t switch_cfg = EZB_ZHA_ON_OFF_SWITCH_CONFIG();

        ep_desc = ezb_zha_create_on_off_switch(ep_id, &switch_cfg);

        ezb_zcl_cluster_desc_t basic_desc = ezb_af_endpoint_get_cluster_desc(ep_desc, EZB_ZCL_CLUSTER_ID_BASIC, EZB_ZCL_CLUSTER_SERVER);
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)"\x09""ESPRESSIF");
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)"\x07"CONFIG_IDF_TARGET);
        ezb_zcl_cluster_desc_t scenes_desc = ezb_zcl_scenes_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_CLIENT);
        ezb_af_endpoint_add_cluster_desc(ep_desc, scenes_desc);

        ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));
        return ezb_af_device_desc_register(dev_desc);
    }

The Scene Server Cluster serves as the foundation for implementing scene applications. The standard Home automation light device contains a scene server
cluster with the mandatory attributes. You can refer to the code below to create it; let's call this implementation the **Scene Light**.

.. code-block:: c

    static esp_err_t ha_on_off_light_create(uint8_t ep_id)
    {
        ezb_af_device_desc_t dev_desc = ezb_af_create_device_desc();
        ezb_af_ep_desc_t ep_desc = {0};
        ezb_zha_on_off_light_config_t light_cfg = EZB_ZHA_ON_OFF_LIGHT_CONFIG();
        light_cfg.scenes_cfg.scene_table_size = 32;
        ep_desc = ezb_zha_create_on_off_light(ep_id, &light_cfg);

        ezb_zcl_cluster_desc_t basic_desc = ezb_af_endpoint_get_cluster_desc(ep_desc, EZB_ZCL_CLUSTER_ID_BASIC, EZB_ZCL_CLUSTER_SERVER);
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)"\x09""ESPRESSIF");
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)"\x07"CONFIG_IDF_TARGET);

        ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));
        return ezb_af_device_desc_register(dev_desc);
    }

The capacity of the scene table in the Scenes Server cluster is set to 16 by default. You can configure it by setting
:cpp:member:`ezb_zha_on_off_light_config_t::scenes_cfg::scene_table_size` field.

Add Scene
^^^^^^^^^

The :cpp:func:`ezb_zcl_scenes_add_scene_cmd_req` API is used by applications to add a scene to a specific group on a device. Before doing so, the group must be
added to the device. The :cpp:func:`ezb_zcl_groups_add_group_cmd_req` API is used for this purpose. The code below provides a reference implementation.

.. code-block:: c

    static ezb_err_t switch_send_add_group_cmd(uint8_t src_ep, uint16_t dst_short_addr, uint8_t dst_ep, uint16_t group_id)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_groups_add_group_cmd_t add_group_cmd = {
            .cmd_ctrl = {
                .dst_addr = {
                    .addr_mode = EZB_ADDR_MODE_SHORT,
                    .u.short_addr = dst_short_addr,
                },
                .src_ep = src_ep,
                .dst_ep = dst_ep,
            },
            .payload = {
                .group_id = group_id,
                .group_name = NULL,
            },
        };

        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_groups_add_group_cmd_req(&add_group_cmd);
        esp_zigbee_lock_release();
        return ret;
    }

    static ezb_err_t switch_send_add_scene_cmd(uint8_t src_ep, uint16_t dst_short_addr, uint8_t dst_ep, uint16_t group_id, uint8_t scene_id)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        uint8_t scene_light_state = 1;  // On
        ezb_zcl_scenes_extension_field_t on_off_extension_field = {
            .cluster_id = EZB_ZCL_CLUSTER_ID_ON_OFF,
            .length = sizeof(scene_light_state),
            .value = &scene_light_state,
            .next = NULL,
        };
        uint8_t scene_current_level = 255; // Level
        ezb_zcl_scenes_extension_field_t level_extension_field = {
            .cluster_id = EZB_ZCL_CLUSTER_ID_LEVEL,
            .length = sizeof(scene_current_level),
            .value = &scene_current_level,
            .next = &on_off_extension_field,
        };
        ezb_zcl_scenes_add_scene_cmd_t add_scene_cmd = {
            .cmd_ctrl = {
                .dst_addr = {
                    .addr_mode = EZB_ADDR_MODE_SHORT,
                    .u.short_addr = dst_short_addr,
                },
                .src_ep = src_ep,
                .dst_ep = dst_ep,
            },
            .payload = {
                .group_id = group_id,
                .scene_id = scene_id,
                .transition_time = 0x000a,
                .scene_name = NULL,
                .extension_field = &level_extension_field,
            }
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_scenes_add_scene_cmd_req(&add_scene_cmd);
        esp_zigbee_lock_release();
        return ret;
    }

A core action callback with ``EZB_ZCL_CORE_CMD_OPERATE_SCENE_RESP_CB_ID`` will be triggered on the **Scene Switch**, indicating the status of the ``Add Scene Response`` that
was handled on the **Scene Light**. The following code provides a reference:

.. code-block:: c

    static void switch_handle_operate_scene_rsp(ezb_zcl_scenes_operate_scene_rsp_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, , TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == EZB_ZCL_STATUS_SUCCESS, , TAG,
                            "Received message: error status(%d)", message->info.status);

        ESP_LOGI(TAG, "Receive scenes %d command response with Scene ID: %d, Group ID: 0x%04x", message->in.header->cmd_id,
                message->in.scene_id, message->in.group_id);
    }

    static void zcl_action_handler(ezb_zcl_core_action_callback_id_t callback_id, const void *message)
    {
        switch (callback_id) {
        case EZB_ZCL_CORE_SCENES_OPERATE_SCENE_RSP_CB_ID:
            switch_handle_operate_scene_rsp((ezb_zcl_scenes_operate_scene_rsp_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
        }
    }

Note that the callback with ``EZB_ZCL_CORE_CMD_OPERATE_SCENE_RESP_CB_ID`` will be triggered when the ``Add Scene Response``, ``Store Scene Response``,
``Remove Scene Response``, and ``Remove All Scene Response`` are received.

View Scene
^^^^^^^^^^

The :cpp:func:`ezb_zcl_scenes_view_scene_cmd_req` API is used by applications to view the content of a specific scene registered in a specific group. The code below provides a reference implementation:

.. code-block:: c

    static ezb_err_t switch_send_view_scene_cmd(uint8_t src_ep, uint16_t dst_short_addr, uint8_t dst_ep, uint16_t group_id, uint8_t scene_id)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_scenes_view_scene_cmd_t view_scene_cmd = {
            .cmd_ctrl = {
                .dst_addr = {
                    .addr_mode = EZB_ADDR_MODE_SHORT,
                    .u.short_addr = dst_short_addr,
                },
                .src_ep = src_ep,
                .dst_ep = dst_ep,
            },
            .payload = {
                .group_id = group_id,
                .scene_id = scene_id,
            },
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_scenes_view_scene_cmd_req(&view_scene_cmd);
        esp_zigbee_lock_release();
        return ret;
    }

A core action callback with ``EZB_ZCL_CORE_CMD_VIEW_SCENE_RESP_CB_ID`` will be triggered on the **Scene Switch**, indicating the status of the ``View Scene Response`` that
was handled from the **Scene Light**. The following code provides a reference implementation:

.. code-block:: c

    static void switch_view_scene_rsp_handler(ezb_zcl_scenes_view_scene_rsp_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, , TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == EZB_ZCL_STATUS_SUCCESS, , TAG,
                            "Received message: error status(%d)", message->info.status);

        ESP_LOGI(TAG, "Receive scenes view response with Scene ID: %d, Group ID: 0x%04x", message->in.scene_id,
                message->in.group_id);
    }


    }


Store Scene
^^^^^^^^^^^

The :cpp:func:`ezb_zcl_scenes_store_scene_cmd_req` API is used by applications to require the remote device to store the current scenes to the scene table. The code
below provides a reference implementation:

.. code-block:: c

    static ezb_err_t switch_send_store_scene_cmd(uint8_t src_ep, uint16_t dst_short_addr, uint8_t dst_ep, uint16_t group_id, uint8_t scene_id)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_scenes_store_scene_cmd_t store_scene_cmd = {
            .cmd_ctrl = {
                .dst_addr = {
                    .addr_mode = EZB_ADDR_MODE_SHORT,
                    .u.short_addr = dst_short_addr,
                },
                .src_ep = src_ep,
                .dst_ep = dst_ep,
            },
            .payload = {
                .group_id = group_id,
                .scene_id = scene_id,
            },
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_scenes_store_scene_cmd_req(&store_scene_cmd);
        esp_zigbee_lock_release();
        return ret;
    }

A core action callback with ``EZB_ZCL_CORE_SCENES_STORE_SCENE_CB_ID`` will be triggered on the **Scene Light**, indicating the status of the ``Store Scene`` that
was received, then the application can write the extension fields  of the specific scene into the scene table. The following code provides a reference implementation:

.. code-block:: c

    static void light_handle_store_scenes_message(ezb_zcl_scenes_store_scene_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, , TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == EZB_ZCL_STATUS_SUCCESS,, TAG,
                            "Received message: error status(%d)", message->info.status);
        ESP_LOGI(TAG, "Store scene %d to group %d", message->in.scene_id, message->in.group_id);

        ezb_zcl_attr_desc_t on_off_attr_desc =
            ezb_zcl_get_attr_desc(message->info.dst_ep, EZB_ZCL_CLUSTER_ID_ON_OFF, EZB_ZCL_CLUSTER_SERVER,
                                EZB_ZCL_ATTR_ON_OFF_ON_OFF_ID, EZB_ZCL_STD_MANUF_CODE);

        bool on_off_state = *(bool *)ezb_zcl_attr_desc_get_value(on_off_attr_desc);

        ezb_zcl_scenes_extension_field_t on_off_extension_field = {
            .cluster_id = EZB_ZCL_CLUSTER_ID_ON_OFF,
            .length     = sizeof(on_off_state),
            .value      = (uint8_t *)&on_off_state,
            .next       = NULL,
        };
        ezb_zcl_attr_desc_t level_attr_desc =
            ezb_zcl_get_attr_desc(message->info.dst_ep, EZB_ZCL_CLUSTER_ID_LEVEL, EZB_ZCL_CLUSTER_SERVER,
                                EZB_ZCL_ATTR_LEVEL_CURRENT_LEVEL_ID, EZB_ZCL_STD_MANUF_CODE);

        uint8_t                          scene_current_level   = *(uint8_t *)ezb_zcl_attr_desc_get_value(level_attr_desc);
        ezb_zcl_scenes_extension_field_t level_extension_field = {
            .cluster_id = EZB_ZCL_CLUSTER_ID_LEVEL,
            .length     = sizeof(scene_current_level),
            .value      = (uint8_t *)&scene_current_level,
            .next       = &on_off_extension_field,
        };
        ezb_zcl_scenes_table_store(message->info.dst_ep, message->in.group_id, message->in.scene_id, 0x0000,
                                        &level_extension_field);
    }

    static void zcl_action_handler(ezb_zcl_core_action_callback_id_t callback_id, const void *message)
    {
        switch (callback_id) {
        case EZB_ZCL_CORE_SCENES_STORE_SCENE_CB_ID:
            light_handle_store_scenes_message((ezb_zcl_scenes_store_scene_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
        }
    }


A core action callback with ``EZB_ZCL_CORE_SCENES_STORE_SCENE_RSP_CB_ID`` will be triggered on the **Scene Switch** to indicate the status of the ``Store Scene Response`` that
was handled on the **Scene Light**.

Get Scene Membership
^^^^^^^^^^^^^^^^^^^^
The :cpp:func:`ezb_zcl_scenes_get_scene_membership_cmd_req` API is used by applications to get the scene membership of a specific group. The code below provides a reference implementation:

.. code-block:: c

    static ezb_err_t switch_send_get_scene_membership_cmd(uint8_t src_ep, uint8_t dst_ep, uint16_t short_addr, uint16_t group_id)
    {
        ezb_err_t                                 ret                = EZB_ERR_NONE;
        ezb_zcl_scenes_get_scene_membership_cmd_t get_membership_cmd = {
            .cmd_ctrl =
                {
                    .dst_addr =
                        {
                            .addr_mode    = EZB_ADDR_MODE_SHORT,
                            .u.short_addr = short_addr,
                        },
                    .src_ep = src_ep,
                    .dst_ep = dst_ep,
                },
            .payload =
                {
                    .group_id = group_id,
                },
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_scenes_get_scene_membership_cmd_req(&get_membership_cmd);
        esp_zigbee_lock_release();
        return ret;
    }

A core action callback with ``EZB_ZCL_CORE_SCENES_GET_SCENE_MEMBERSHIP_RSP_CB_ID`` will be triggered on the **Scene Switch** to report the scene membership in the **Scene Light**. The following
code provides a reference implementation:

.. code-block:: c

    static void switch_handle_get_scene_membership_rsp(ezb_zcl_scenes_get_scene_membership_rsp_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, , TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == EZB_ZCL_STATUS_SUCCESS, , TAG,
                            "Received message: error status(%d)", message->info.status);
        ESP_LOGI(TAG, "Receive scenes get scene membership response with Group ID: 0x%04x, capacity: %d", message->in.group_id,
                message->in.capacity);
        ESP_LOGI(TAG, "Scene List:");
        for (int i = 0; i < message->in.scene_count; i++) {
            ESP_LOGI(TAG, "%d", *message->in.scene_list);
            message->in.scene_list++;
        }
    }

    static void zcl_action_handler(ezb_zcl_core_action_callback_id_t callback_id, const void *message)
    {
        switch (callback_id) {
        case EZB_ZCL_CORE_SCENES_GET_SCENE_MEMBERSHIP_RSP_CB_ID:
            switch_handle_get_scene_membership_rsp((ezb_zcl_scenes_get_scene_membership_rsp_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
        }
    }

Recall Scene
^^^^^^^^^^^^
The :cpp:func:`ezb_zcl_scenes_recall_scene_cmd_req` API is used by applications to recall a scene registered in the scene table of the **Scene Light**. The code
below provides a reference implementation.

.. code-block:: c

    static ezb_err_t switch_send_recall_scene_cmd(uint8_t  src_ep,
                                              uint8_t  dst_ep,
                                              uint16_t short_addr,
                                              uint16_t group_id,
                                              uint8_t  scene_id)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_scenes_recall_scene_cmd_t recall_scene_cmd = {
            .cmd_ctrl =
                {
                    .dst_addr =
                        {
                            .addr_mode    = EZB_ADDR_MODE_SHORT,
                            .u.short_addr = short_addr,
                        },
                    .src_ep = src_ep,
                    .dst_ep = dst_ep,
                },
            .payload = {.group_id = group_id, .scene_id = scene_id, .transition_time = 0x0000},
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_scenes_recall_scene_cmd_req(&recall_scene_cmd);
        esp_zigbee_lock_release();
        return ret;
    }

A core action callback with ``EZB_ZCL_CORE_SCENES_RECALL_SCENE_CB_ID`` will be triggered on the **Scene Light**, indicating the status of the ``Recall Scene`` that
was received. The application can recall the specific scene by the extension fields of the scene. The following code provides a reference implementation:

.. code-block:: c

    static void light_handle_recall_scenes(ezb_zcl_scenes_recall_scene_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, , TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == EZB_ZCL_STATUS_SUCCESS, , TAG, "Received message: error status(%d)",
                            message->info.status);
        ESP_LOGI(TAG, "Recall scene %d from group %d", message->in.scene_id, message->in.group_id);
        ezb_zcl_scenes_extension_field_t *field = message->in.field_set;
        while (field) {
            if (field->cluster_id == EZB_ZCL_CLUSTER_ID_ON_OFF) {
                ezb_zcl_on_off_cmd_t cmd = {
                    .cmd_ctrl =
                        {
                            .dst_addr =
                                {
                                    .addr_mode    = EZB_ADDR_MODE_SHORT,
                                    .u.short_addr = esp_zb_get_short_address(),
                                },
                            .src_ep = message->info.dst_ep,
                            .dst_ep = message->info.dst_ep,
                        },
                };
                if (*(bool *)field->value == true) {
                    ezb_zcl_on_off_on_cmd_req(&cmd);
                } else {
                    ezb_zcl_on_off_off_cmd_req(&cmd);
                }
            } else if (field->cluster_id == EZB_ZCL_CLUSTER_ID_LEVEL) {
                ezb_zcl_level_move_to_level_cmd_t cmd = {
                    .cmd_ctrl =
                        {
                            .dst_addr =
                                {
                                    .addr_mode    = EZB_ADDR_MODE_SHORT,
                                    .u.short_addr = esp_zb_get_short_address(),
                                },
                            .src_ep = message->info.dst_ep,
                            .dst_ep = message->info.dst_ep,
                        },
                    .payload =
                        {
                            .level           = *(uint8_t *)field->value,
                            .transition_time = message->in.transition_time,
                        },
                };
                ezb_zcl_level_move_to_level_cmd_req(&cmd);
            } else {
                // Other scenes
            }
            field = field->next;
        }
    }

    static void zcl_action_handler(ezb_zcl_core_action_callback_id_t callback_id, const void *message)
    {
        switch (callback_id) {
        case EZB_ZCL_CORE_SCENES_RECALL_SCENE_CB_ID:
            light_handle_recall_scenes((ezb_zcl_scenes_recall_scene_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
        }
    }

Note that the application is required to recall the scene based on the ``ezb_zcl_scenes_recall_scene_message_t`` triggered by the stack. The ``Recall Scene Response``
is not defined in ZCL, so no callback will be triggered.

Remove Scene
^^^^^^^^^^^^
The :cpp:func:`ezb_zcl_scenes_remove_scene_cmd_req` API is used by applications to remove a specific scene from the scene table of the **Scene Light**. The code
below provides a reference implementation:

.. code-block:: c

    static ezb_err_t switch_remove_scene_cmd(uint8_t  src_ep,
                                             uint8_t  dst_ep,
                                             uint16_t dst_short_addr,
                                             uint16_t group_id,
                                             uint8_t  scene_id)
    {
        ezb_err_t                         ret              = EZB_ERR_NONE;
        ezb_zcl_scenes_remove_scene_cmd_t remove_scene_cmd = {
            .cmd_ctrl =
                {
                    .dst_addr =
                        {
                            .addr_mode    = EZB_ADDR_MODE_SHORT,
                            .u.short_addr = dst_short_addr,
                        },
                    .src_ep = src_ep,
                    .dst_ep = dst_ep,
                },
            .payload =
                {
                    .group_id = group_id,
                    .scene_id = scene_id,
                },
        };

        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_scenes_remove_scene_cmd_req(&remove_scene_cmd);
        esp_zigbee_lock_release();
        return ret;
    }


A core action callback with ``EZB_ZCL_CORE_SCENES_REMOVE_SCENE_RSP_CB_ID`` will be triggered on the **Scene Switch**, indicating the status of the ``Remove Scene Response`` that
was handled on the **Scene Light**.

Remove All Scene
^^^^^^^^^^^^^^^^
The :cpp:func:`ezb_zcl_scenes_remove_all_scenes_cmd_req` API is used by applications to remove all scenes of a specific group from the scene table of the **Scene Light**. The code
below provides a reference implementation:

.. code-block:: c

    static ezb_err_t switch_remove_all_scene_cmd(uint8_t src_ep, uint8_t dst_ep, uint16_t dst_short_addr, uint16_t group_id)
    {
        ezb_err_t                              ret                  = EZB_ERR_NONE;
        ezb_zcl_scenes_remove_all_scenes_cmd_t remove_all_scene_cmd = {
            .cmd_ctrl =
                {
                    .dst_addr =
                        {
                            .addr_mode    = EZB_ADDR_MODE_SHORT,
                            .u.short_addr = dst_short_addr,
                        },
                    .src_ep = src_ep,
                    .dst_ep = dst_ep,
                },
            .payload = {.group_id = group_id},
        };

        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_scenes_remove_all_scenes_cmd_req(&remove_all_scene_cmd);
        esp_zigbee_lock_release();
        return ret;
    }

THe ``Remove All Scene Response`` without any response.
