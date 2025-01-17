5.6. Zigbee ZCL Scenes Cluster
------------------------------


5.6.1 Overview
~~~~~~~~~~~~~~~

Scenes are predefined configurations of device attributes, such as brightness, color, and switch status, aimed to create specific environmental settings,
like room lighting. The Zigbee Cluster Library (ZCL) defines a standard Scenes Cluster, enabling devices to work together seamlessly to achieve such
configurations.

ZCL Scenes are typically associated with a specific group ID, representing a set of stored attributes for one or more cluster instances. These instances
can span multiple devices. Standard scene commands facilitate the efficient configuration and management of the Scene Table, simplifying control over
devices and scene settings.

This chapter aims to explain the implementation mechanism of the Scenes Cluster within the esp-zigbee-sdk, introduce the typical usage of scene commands,
and demonstrate practical applications of scenes.


5.6.2 Related APIs Preview
~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following APIs are related to the main implementation of the ZCL Scene cluster.

- :cpp:func:`esp_zb_zcl_attr_list_create`
- :cpp:func:`esp_zb_scenes_cluster_add_attr`
- :cpp:func:`esp_zb_scenes_cluster_create`
- :cpp:func:`esp_zb_cluster_list_add_scenes_cluster`
- :cpp:func:`esp_zb_cluster_list_update_scenes_cluster`
- :cpp:func:`esp_zb_zcl_scenes_add_scene_cmd_req`
- :cpp:func:`esp_zb_zcl_scenes_remove_scene_cmd_req`
- :cpp:func:`esp_zb_zcl_scenes_remove_all_scenes_cmd_req`
- :cpp:func:`esp_zb_zcl_scenes_view_scene_cmd_req`
- :cpp:func:`esp_zb_zcl_scenes_store_scene_cmd_req`
- :cpp:func:`esp_zb_zcl_scenes_recall_scene_cmd_req`
- :cpp:func:`esp_zb_zcl_scenes_get_scene_membership_cmd_req`
- :cpp:func:`esp_zb_zcl_scenes_table_store`
- :cpp:func:`esp_zb_zcl_scenes_table_clear_by_index`
- :cpp:func:`esp_zb_zcl_scenes_table_show`


5.6.3 Scenes Context Relationship
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The Zigbee Scene Cluster is built on the concept of groups in Zigbee applications. It enables coordination across different endpoints and facilitates the
storage of attributes from various clusters. This foundation allows for the creation, application, and management of scenes, providing a cohesive way to
control multiple devices in a synchronized manner.

This section introduces the contextual relationships between scenes, groups, and clusters, offering a detailed understanding of how they work together to
support scene-based applications.


5.6.3.1 Scenes and Groups
^^^^^^^^^^^^^^^^^^^^^^^^^
A group is a collection of endpoints that may span multiple devices, defining the scope for an application scene. Typically, scenes are associated with a
specific group ID to facilitate their organization and management. However, scenes can also exist without being tied to a group. In such cases, the group
ID is replaced by the value 0x0000. Scene-related commands for these scenarios can only be sent as unicast messages and cannot be multicast or broadcast.

In such situations, extra care is required to avoid scene ID collisions. This means that the scene ID must remain unique either within the group or, if no
group is present, within the relevant application scope. Maintaining this uniqueness ensures proper functionality and avoids conflicts when managing scenes.

5.6.3.2 Scenes and Endpoint
^^^^^^^^^^^^^^^^^^^^^^^^^^^
An endpoint represents a device instance that participates in scenes. Endpoints with a Scenes Cluster can be grouped into a specific set using the Group
Cluster, allowing predefined scenes to be established. 

The Scenes Cluster server is responsible for receiving commands to manage scenes, including storing, recalling, or deleting scene configurations. On the
other hand, the Scenes Cluster client sends commands to the server, enabling read or write access to scenes for configuration or control purposes.

5.6.3.3 Scenes and Attribute
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The ZCL specifies which attributes within a cluster should be used as entries for a Scene. For instance, the On/Off`` attribute (0x0001) of the On/Off
Cluster (0x0006) and the CurrentLevel attribute (0x0000) of the Level Control Cluster (0x0008) are standard entries defined by the ZCL.  

In contrast, the esp-zigbee-sdk offers greater flexibility by not restricting which attributes can serve as scene entries. This allows users to design
custom scenes tailored to their specific application requirements.

5.6.3.4 Scenes and Scene Table
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The Scene Table stores information about each scene that can be invoked on a device. Each scene is linked to a specific group, and the table entries
typically include the following fields: **Scene Group ID**, **Scene ID**, **Scene Name**, **Scene Transition Time**, **Extension Field Sets**, and
**Transition Time**.

In the esp-zigbee-sdk, the Scene Table is managed internally and shared across the device. Developers can interact with the Scene Table using the provided
APIs, enabling efficient scene configuration and management.


5.6.4  Typical Usage
~~~~~~~~~~~~~~~~~~~~
This section introduces the typical usage of the Scene Cluster, covering the process of creating a data model, related commands, and their handlers.
Additionally, an application example will demonstrate how to switch between two scenes to control the light level.

5.6.4.1 Scenes Cluster Creation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Scene Client Cluster serves as the foundation for configuring scenes on remote devices. If you want to create an endpoint with the Scene Cluster that
can still control a light's status and brightness, you can refer to the code below. Let’s call this implementation the **Scene Switch**.

.. code-block:: c

    #define HA_SCENES_SWITCH 1
    #define HA_SCENES_LIGHT 10
    #define HA_SCENES_LIGHT_ADDR 0x0000 // The short address of Remote scene light
    #define HA_SCENES_LIGHT_GROUP1_ID 0x0001
    #define HA_SCENES_LIGHT_SCENE1_ID 0x01
    #define HA_SCENES_LIGHT_SCENE2_ID 0x02
    #define MANUFACTURER_NAME "\x09""ESPRESSIF"
    #define MODEL_IDENTIFIER "\x07" CONFIG_IDF_TARGET

    static esp_err_t zb_scenes_switch_create(void)
    {
        esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
        esp_zb_endpoint_config_t endpoint_config = {
            .endpoint = HA_SCENES_SWITCH,
            .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
            .app_device_id = ESP_ZB_HA_ON_OFF_SWITCH_DEVICE_ID,
            .app_device_version = 0,
        };
        esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();
        esp_zb_attribute_list_t *basic_cluster = esp_zb_basic_cluster_create(NULL);
        esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, MANUFACTURER_NAME);
        esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, MODEL_IDENTIFIER);
        esp_zb_cluster_list_add_basic_cluster(cluster_list, basic_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
        esp_zb_cluster_list_add_scenes_cluster(cluster_list, esp_zb_scenes_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);
        esp_zb_cluster_list_add_identify_cluster(cluster_list, esp_zb_identify_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
        esp_zb_cluster_list_add_groups_cluster(cluster_list, esp_zb_groups_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);
        esp_zb_cluster_list_add_on_off_cluster(cluster_list, esp_zb_on_off_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);
        esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config);
        return esp_zb_device_register(ep_list);
    }

The Scene Server Cluster serves as the foundation for implementing scene applications. If you want to create an endpoint with the Scene Cluster that acts as
a light, you can refer to the code below. Let’s call this implementation the **Scene Light**.

.. code-block:: c

    #define HA_SCENES_LIGHT 10
    #define MANUFACTURER_NAME "\x09""ESPRESSIF"
    #define MODEL_IDENTIFIER "\x07"CONFIG_IDF_TARGET

    static esp_err_t zb_scenes_light_create(void)
    {
        esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
        esp_zb_endpoint_config_t endpoint_config = {
            .endpoint = HA_SCENES_LIGHT,
            .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
            .app_device_id = ESP_ZB_HA_ON_OFF_LIGHT_DEVICE_ID,
            .app_device_version = 0,
        };
        esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();
        esp_zb_attribute_list_t *basic_cluster = esp_zb_basic_cluster_create(NULL);
        esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, MANUFACTURER_NAME);
        esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, MODEL_IDENTIFIER);
        esp_zb_cluster_list_add_basic_cluster(cluster_list, basic_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
        esp_zb_cluster_list_add_scenes_cluster(cluster_list, esp_zb_scenes_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
        esp_zb_cluster_list_add_identify_cluster(cluster_list, esp_zb_identify_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
        esp_zb_cluster_list_add_groups_cluster(cluster_list, esp_zb_groups_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
        esp_zb_cluster_list_add_level_cluster(cluster_list, esp_zb_level_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
        esp_zb_cluster_list_add_on_off_cluster(cluster_list, esp_zb_on_off_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
        esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config);
        return esp_zb_device_register(ep_list);
    }

5.6.4.2 Add Scene
^^^^^^^^^^^^^^^^^

The ``Add Scene Command`` is used for applications to add a scene to a specific group on a device. If you want to use a **Scene Switch** to add a scene where
the light is on and its level is set to 255 in ``Group_ID 1`` to a **Scene Light**, ensure that the endpoint containing the scene cluster belongs to
``Group_ID 1``. Then, the scene can be added using the ``Add Scene Command``. The code below provides a reference method.

.. code-block:: c
    
    static esp_err_t zb_switch_send_add_group_to_light(uint16_t short_addr, uint16_t group_id)
    {
        esp_zb_zcl_groups_add_group_cmd_t add_group_cmd = {
            .group_id = group_id,
            .address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
            .zcl_basic_cmd.dst_addr_u.addr_short = short_addr,
            .zcl_basic_cmd.dst_endpoint = HA_SCENES_LIGHT,
            .zcl_basic_cmd.src_endpoint = HA_SCENES_SWITCH,
        };

        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_groups_add_group_cmd_req(&add_group_cmd);
        esp_zb_lock_release();
        ESP_LOGI(TAG, "Add endpoint %d to Group: 0x%04x to short: 0x%04x", add_group_cmd.zcl_basic_cmd.dst_endpoint,
                add_group_cmd.group_id, add_group_cmd.zcl_basic_cmd.dst_addr_u.addr_short);
        return ESP_OK;
    }
    zb_switch_send_add_group_to_light(HA_SCENES_LIGHT_ADDR, HA_SCENES_LIGHT_GROUP1_ID);

    static esp_err_t zb_switch_send_add_scene_to_light(uint16_t short_addr, uint16_t group_id, uint8_t scene_id)
    {
        uint8_t scene_light_state = 1;  // On
        esp_zb_zcl_scenes_extension_field_t on_off_extension_field = {
            .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_ON_OFF,
            .length = sizeof(scene_light_state),
            .extension_field_attribute_value_list = &scene_light_state,
            .next = NULL,
        };
        uint8_t scene_current_level = 255; // Level
        esp_zb_zcl_scenes_extension_field_t level_extension_field = {
            .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL,
            .length = sizeof(scene_current_level),
            .extension_field_attribute_value_list = &scene_current_level,
            .next = &on_off_extension_field,
        };
        esp_zb_zcl_scenes_add_scene_cmd_t add_scene_cmd = {
            .zcl_basic_cmd.dst_addr_u.addr_short = short_addr,
            .zcl_basic_cmd.dst_endpoint = HA_SCENES_LIGHT,
            .zcl_basic_cmd.src_endpoint = HA_SCENES_SWITCH,
            .group_id = group_id,
            .scene_id = scene_id,
            .transition_time = 0x0000,
            .extension_field = &level_extension_field,
        };
        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_scenes_add_scene_cmd_req(&add_scene_cmd);
        esp_zb_lock_release();
        ESP_LOGI(TAG, "Add Scene ID %d of Group ID 0x%04x to short 0x%04x", add_scene_cmd.scene_id, add_scene_cmd.group_id,
                add_scene_cmd.zcl_basic_cmd.dst_addr_u.addr_short);
        return ESP_OK;
    }
    zb_switch_send_add_scene_to_light(HA_SCENES_LIGHT_ADDR, HA_SCENES_LIGHT_GROUP1_ID, HA_SCENES_LIGHT_SCENE1_ID);

An ``Add Scene Response`` callback registered by the :cpp:func:`esp_zb_core_action_handler_register` will be triggered on the **Scene Switch**, indicating
the status of the ``Add Scene Command`` handled on the **Scene Light**. The following code provides a reference:

.. code-block:: c

    static esp_err_t zb_switch_operate_scene_resp_handler(esp_zb_zcl_scenes_operate_scene_resp_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG,
                            "Received message: error status(%d)", message->info.status);

        ESP_LOGI(TAG, "Receive scenes %d command response with Scene ID: %d, Group ID: 0x%04x", message->info.command.id,
                message->scene_id, message->group_id);
        return ESP_OK;
    }

    static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
    {
        esp_err_t ret = ESP_OK;
        switch (callback_id) {
        case ESP_ZB_CORE_CMD_OPERATE_SCENE_RESP_CB_ID:
            ret = zb_switch_operate_scene_resp_handler((esp_zb_zcl_scenes_operate_scene_resp_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
        }
        return ret;
    }

Note that the callback with ``ESP_ZB_CORE_CMD_OPERATE_SCENE_RESP_CB_ID`` will be triggered when the ``Add Scene Response``, ``Store Scene Response``,
``Remove Scene Response``, and ``Remove All Scene Response`` are received.

5.6.4.3 View Scene
^^^^^^^^^^^^^^^^^^

The ``View Scene Command`` offers a way to view the content of a specific scene registered in a specific group. If you intend to view ``Scene_ID 1`` from
``Group_ID 1`` of the **Scene Light**, you can refer to the code below:

.. code-block:: c

    static esp_err_t zb_switch_view_scene_from_light(uint16_t short_addr, uint16_t group_id, uint8_t scene_id)
    {
        esp_zb_zcl_scenes_view_scene_cmd_t view_scene_cmd = {
            .zcl_basic_cmd.dst_addr_u.addr_short = short_addr,
            .zcl_basic_cmd.dst_endpoint = HA_SCENES_LIGHT,
            .zcl_basic_cmd.src_endpoint = HA_SCENES_SWITCH,
            .group_id = group_id,
            .scene_id = scene_id,
        };

        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_scenes_view_scene_cmd_req(&view_scene_cmd);
        esp_zb_lock_release();
        ESP_LOGI(TAG, "View Scene ID: %d in Group ID: 0x%04x of short: 0x%04x", view_scene_cmd.scene_id,
                view_scene_cmd.group_id, view_scene_cmd.zcl_basic_cmd.dst_addr_u.addr_short);
        return ESP_OK;
    }

    zb_switch_view_scene_from_light(HA_SCENES_LIGHT_ADDR, HA_SCENES_LIGHT_GROUP1_ID, HA_SCENES_LIGHT_SCENE1_ID);

A ``View Scene Response`` generated by the **Scene Light** will be received by the **Scene Switch**. You can get the response of the ``View Scene Command``
using this callback:

.. code-block:: c
    
    static esp_err_t zb_switch_view_scene_resp_handler(esp_zb_zcl_scenes_view_scene_resp_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG,
                            "Received message: error status(%d)", message->info.status);

        ESP_LOGI(TAG, "Receive scenes view response with Scene ID: %d, Group ID: 0x%04x", message->scene_id,
                message->group_id);
        return ESP_OK;
    }

    static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
    {
        esp_err_t ret = ESP_OK;
        switch (callback_id) {
        case ESP_ZB_CORE_CMD_VIEW_SCENE_RESP_CB_ID:
            ret = zb_switch_view_scene_resp_handler((esp_zb_zcl_scenes_view_scene_resp_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
        }
        return ret;
    }


5.6.4.4 Store Scene
^^^^^^^^^^^^^^^^^^^

The ``Store Scene Command`` can be used to request the remote device to store the scene in its scene table. If you expect to control the **Scene Light**
to store the current scene via the **Scene Switch**, the below code can be used as a reference:

.. code-block:: c

    static esp_err_t zb_switch_send_store_scene_to_light(uint16_t short_addr, uint16_t group_id, uint8_t scene_id)
    {
        esp_zb_zcl_scenes_store_scene_cmd_t store_scene_cmd = {
            .address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
            .zcl_basic_cmd.dst_addr_u.addr_short = short_addr,
            .zcl_basic_cmd.dst_endpoint = HA_SCENES_LIGHT,
            .zcl_basic_cmd.src_endpoint = HA_SCENES_SWITCH,
            .group_id = group_id,
            .scene_id = scene_id,
        };

        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_scenes_store_scene_cmd_req(&store_scene_cmd);
        esp_zb_lock_release();
        ESP_LOGI(TAG, "Ask the short: 0x%04x to store current scenes to Scene ID: %d of Group ID: 0x%04x",
                store_scene_cmd.zcl_basic_cmd.dst_addr_u.addr_short, store_scene_cmd.scene_id, store_scene_cmd.group_id);
        return ESP_OK;
    }
    zb_switch_send_store_scene_to_light(HA_SCENES_LIGHT_ADDR, HA_SCENES_LIGHT_GROUP1_ID, HA_SCENES_LIGHT_SCENE2_ID);

If the ``Store Scene Command`` is received by the **Scene Light**, the callback ``ESP_ZB_CORE_SCENES_STORE_SCENE_CB_ID`` will be raised. You can call the
``esp_zb_zcl_scenes_table_store`` function to store the relevant clusters to the scene table. Below is the reference code to store the On/Off attribute of
the On/Off Cluster and the current level attribute of the Level Control Cluster as ``Scene_ID 2`` of ``Group_ID 1`` to the scene table:

.. code-block:: c

    static esp_err_t zb_light_scenes_store_handler(esp_zb_zcl_store_scene_message_t *message)
    {
        esp_err_t ret = ESP_OK;
        ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG,
                            "Received message: error status(%d)", message->info.status);
        ESP_LOGI(TAG, "Store scene %d to group %d", message->scene_id, message->group_id);

        uint8_t scene_light_state =
            *(uint8_t *)esp_zb_zcl_get_attribute(message->info.dst_endpoint, ESP_ZB_ZCL_CLUSTER_ID_ON_OFF,
                                                ESP_ZB_ZCL_CLUSTER_SERVER_ROLE, ESP_ZB_ZCL_ATTR_ON_OFF_ON_OFF_ID)
                ->data_p;
        esp_zb_zcl_scenes_extension_field_t on_off_extension_field = {
            .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_ON_OFF,
            .length = sizeof(scene_light_state),
            .extension_field_attribute_value_list = &scene_light_state,
            .next = NULL,
        };
        uint8_t scene_current_level = *(uint8_t *)esp_zb_zcl_get_attribute(
                                        message->info.dst_endpoint, ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL,
                                        ESP_ZB_ZCL_CLUSTER_SERVER_ROLE, ESP_ZB_ZCL_ATTR_LEVEL_CONTROL_CURRENT_LEVEL_ID)
                                        ->data_p;
        esp_zb_zcl_scenes_extension_field_t level_extension_field = {
            .cluster_id = ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL,
            .length = sizeof(scene_current_level),
            .extension_field_attribute_value_list = &scene_current_level,
            .next = &on_off_extension_field,
        };
        ret = esp_zb_zcl_scenes_table_store(message->info.dst_endpoint, message->group_id, message->scene_id, 0x0000,
                                            &level_extension_field);
        esp_zb_zcl_scenes_table_show(message->info.dst_endpoint);
        return ret;
    }

    static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
    {
        esp_err_t ret = ESP_OK;
        switch (callback_id) {
        case ESP_ZB_CORE_SCENES_STORE_SCENE_CB_ID:
            ret = zb_light_scenes_store_handler((esp_zb_zcl_store_scene_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
        }
        return ret;
    }

The :cpp:func:`esp_zb_zcl_scenes_table_show` function provides a visualized method to look up the local scene table. It can be useful to check the stored
scenes and their corresponding attributes.

A ``Store Scene Response`` callback will be raised on the **Scene Switch** to indicate the status of the `Store Scene Command` that was handled on the
**Scene Light**. This callback will provide feedback on whether the scene was successfully stored or if there were any issues during the process.

5.6.4.5 Get Scene Membership
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The ``Get Scene Membership Command`` can be used to find an unused scene number within a group when no commissioning tool is present in the network, or for
a commissioning tool to retrieve the used scenes for a group on a single device or across all devices in the group. If you intend to call it, the following
code can serve as a reference:

.. code-block:: c

    static esp_err_t zb_switch_get_scene_membership_from_light(uint16_t short_addr)
    {
        esp_zb_zcl_scenes_get_scene_membership_cmd_t get_membership_cmd = {
            .address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
            .zcl_basic_cmd.dst_addr_u.addr_short = short_addr,
            .zcl_basic_cmd.dst_endpoint = HA_SCENES_LIGHT,
            .zcl_basic_cmd.src_endpoint = HA_SCENES_SWITCH,
            .group_id = HA_SCENES_LIGHT_GROUP1_ID,
        };

        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_scenes_get_scene_membership_cmd_req(&get_membership_cmd);
        esp_zb_lock_release();
        ESP_LOGI(TAG, "Get scene membership in Group ID: 0x%04x of short: 0x%04x", get_membership_cmd.group_id,
                get_membership_cmd.zcl_basic_cmd.dst_addr_u.addr_short);
        return ESP_OK;
    }
    zb_switch_get_scene_membership_from_light(HA_SCENES_LIGHT_ADDR);

A ``Get Scene Membership Response`` callback will be triggered on the **Scene Switch** to report the scene membership in the **Scene Light**. The following
code serves as a reference:

.. code-block:: c

    static esp_err_t zb_switch_get_scene_membership_handler(esp_zb_zcl_scenes_get_scene_membership_resp_message_t *message)
    {
        ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG,
                            "Received message: error status(%d)", message->info.status);
        ESP_LOGI(TAG, "Receive scenes get scene membership response with Group ID: 0x%04x, capacity: %d", message->group_id,
                message->capacity);
        ESP_LOGI(TAG, "Scene List:");
        for (int i = 0; i < message->scene_count; i++) {
            ESP_LOGI(TAG, "%d", *message->scene_list);
            message->scene_list++;
        }
        return ESP_OK;
    }

    static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
    {
        esp_err_t ret = ESP_OK;
        switch (callback_id) {
        case ESP_ZB_CORE_CMD_GET_SCENE_MEMBERSHIP_RESP_CB_ID:
            ret = zb_switch_get_scene_membership_handler((esp_zb_zcl_scenes_get_scene_membership_resp_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
        }
        return ret;
    }

5.6.4.6 Recall Scene
^^^^^^^^^^^^^^^^^^^^
The ``Recall Scene Command`` is used to recall a scene registered in the scene table. If you intend to recall ``Scene_ID 1`` of ``Group_ID 1`` from the scene
table of the **Scene Light**, you can refer to the following code:

.. code-block:: c

    static esp_err_t zb_switch_send_recall_scene_to_light(uint16_t short_addr, uint16_t group_id, uint8_t scene_id)
    {
        esp_zb_zcl_scenes_recall_scene_cmd_t recall_scene_cmd = {
            .address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
            .zcl_basic_cmd.dst_addr_u.addr_short = short_addr,
            .zcl_basic_cmd.dst_endpoint = HA_SCENES_LIGHT,
            .zcl_basic_cmd.src_endpoint = HA_SCENES_SWITCH,
            .group_id = group_id,
            .scene_id = scene_id,
        };

        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_scenes_recall_scene_cmd_req(&recall_scene_cmd);
        esp_zb_lock_release();
        ESP_LOGI(TAG, "Ask the short: 0x%04x to recall Scene ID: %d of Group ID: 0x%04x",
                recall_scene_cmd.zcl_basic_cmd.dst_addr_u.addr_short, recall_scene_cmd.scene_id,
                recall_scene_cmd.group_id);
        return ESP_OK;
    }
    zb_switch_send_recall_scene_to_light(HA_SCENES_LIGHT_ADDR, HA_SCENES_LIGHT_GROUP1_ID, HA_SCENES_LIGHT_SCENE1_ID);

A callback will be raised to report which scene should be recalled when the ``Recall Scene Command`` is received by the **Scene Light**. The following
code provides a way to recall ``Scene_ID 1`` of ``Group_ID 1`` on the **Scene Light** side.

.. code-block:: c

    static esp_err_t zb_light_scenes_recall_handler(esp_zb_zcl_recall_scene_message_t *message)
    {
        esp_err_t ret = ESP_OK;
        ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
        ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG,
                            "Received message: error status(%d)", message->info.status);
        ESP_LOGI(TAG, "Recall scene %d from group %d", message->scene_id, message->group_id);
        esp_zb_zcl_scenes_extension_field_t *field = message->field_set;
        while (field) {
            if (field->cluster_id == ESP_ZB_ZCL_CLUSTER_ID_ON_OFF) {
                esp_zb_zcl_on_off_cmd_t cmd = {
                    .address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
                    .zcl_basic_cmd.dst_addr_u.addr_short = esp_zb_get_short_address(),
                    .zcl_basic_cmd.src_endpoint = HA_SCENES_LIGHT,
                    .zcl_basic_cmd.dst_endpoint = HA_SCENES_LIGHT,
                    .on_off_cmd_id = *(uint8_t *)field->extension_field_attribute_value_list,
                };
                esp_zb_zcl_on_off_cmd_req(&cmd);
            } else if (field->cluster_id == ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL) {
                esp_zb_zcl_move_to_level_cmd_t cmd = {
                    .address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
                    .zcl_basic_cmd.dst_addr_u.addr_short = esp_zb_get_short_address(),
                    .zcl_basic_cmd.src_endpoint = HA_SCENES_LIGHT,
                    .zcl_basic_cmd.dst_endpoint = HA_SCENES_LIGHT,
                    .level = *(uint8_t *)field->extension_field_attribute_value_list,
                    .transition_time = 0,
                };
                esp_zb_zcl_level_move_to_level_cmd_req(&cmd);
            } else {
                // Other scenes
            }
            field = field->next;
        }
        return ret;
    }

    static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
    {
        esp_err_t ret = ESP_OK;
        switch (callback_id) {
        case ESP_ZB_CORE_SCENES_RECALL_SCENE_CB_ID:
            ret = zb_light_scenes_recall_handler((esp_zb_zcl_recall_scene_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
        }
        return ret;
    }

Note that the application is required to recall the scene based on the ``esp_zb_zcl_recall_scene_message_t`` triggered by the stack. The ``Recall Scene Response``
is not defined in ZCL, so no callback will be triggered.

5.6.4.7 Remove Scene
^^^^^^^^^^^^^^^^^^^^
The ``Remove Scene Command`` is used to remove a specific scene from the scene table. If you intend to remove ``Scene_ID 1`` of ``Group_ID 1`` from the
scene table of the **Scene Light**, you can refer to the code below:

.. code-block:: c

    static esp_err_t zb_switch_send_remove_scene_to_light(uint16_t short_addr, uint16_t group_id, uint8_t scene_id)
    {
        esp_zb_zcl_scenes_remove_scene_cmd_t remove_scene_cmd = {
            .address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
            .zcl_basic_cmd.dst_addr_u.addr_short = short_addr,
            .zcl_basic_cmd.dst_endpoint = HA_SCENES_LIGHT,
            .zcl_basic_cmd.src_endpoint = HA_SCENES_SWITCH,
            .group_id = group_id,
            .scene_id = scene_id,
        };

        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_scenes_remove_scene_cmd_req(&remove_scene_cmd);
        esp_zb_lock_release();
        ESP_LOGI(TAG, "Ask the short: 0x%04x to remove Scene ID: %d of Group ID: 0x%04x",
                remove_scene_cmd.zcl_basic_cmd.dst_addr_u.addr_short, remove_scene_cmd.scene_id,
                remove_scene_cmd.group_id);
        return ESP_OK;
    }
    zb_switch_send_remove_scene_to_light(HA_SCENES_LIGHT_ADDR, HA_SCENES_LIGHT_GROUP1_ID, HA_SCENES_LIGHT_SCENE1_ID);

A ``Remove Scene Response`` callback will be raised on the **Scene Switch Device** to indicate the status of the ``Remove Scene Command`` handled in the **Scene Light**.

5.6.4.8 Remove All Scene
^^^^^^^^^^^^^^^^^^^^^^^^
The ``Remove Scene Command`` provides a way to remove all scenes of a group from the scene table. If you intend to remove all scenes of ``Group_ID 1``
from the scene table of the **Scene Light**, you can refer to the following code:

.. code-block:: c

    static esp_err_t zb_switch_send_remove_all_scene_to_light(uint16_t short_addr, uint16_t group_id)
    {
        esp_zb_zcl_scenes_remove_all_scenes_cmd_t remove_all_scene_cmd = {
            .address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT,
            .zcl_basic_cmd.dst_addr_u.addr_short = short_addr,
            .zcl_basic_cmd.dst_endpoint = HA_SCENES_LIGHT,
            .zcl_basic_cmd.src_endpoint = HA_SCENES_SWITCH,
            .group_id = group_id,
        };

        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_scenes_remove_all_scenes_cmd_req(&remove_all_scene_cmd);
        esp_zb_lock_release();
        ESP_LOGI(TAG, "Ask the short: 0x%04x to remove all scenes in Group ID: 0x%04x",
                remove_all_scene_cmd.zcl_basic_cmd.dst_addr_u.addr_short, remove_all_scene_cmd.group_id);
        return ESP_OK;
    }
    zb_switch_send_remove_all_scene_to_light(HA_SCENES_LIGHT_ADDR, HA_SCENES_LIGHT_GROUP1_ID);

A ``Remove All Scene Response`` callback will be raised on the **Scene Switch** to indicate the status of the ``Remove All Scene Command`` handled by the **Scene Light**.
