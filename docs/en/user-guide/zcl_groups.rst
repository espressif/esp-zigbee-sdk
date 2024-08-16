5.4. Zigbee ZCL Groups Cluster
-------------------------------

5.4.1 Overview
~~~~~~~~~~~~~~~
The Zigbee protocol stack defines various device instances based on different profiles and scenarios.
In Zigbee, these are abstracted into logic instance name as endpoints, with each endpoint performing its role
within the network, working together to achieve the user-designed application scenarios.

However, in complex application scenario, a network may contain a large number of endpoints distributed across
different devices. To organize and coordinate the work between these endpoints, the Zigbee ZCL defines the groups
cluster, allowing developers to arrange the endpoints within the network into groups.

The Zigbee group functionality is primarily implemented in the APS layer. The ZCL Groups cluster provides an
application-level method to manage groups within the network. This chapter will focus on explaining the usage
of groups from the ZCL perspective.


5.4.2 Related APIs Preview
~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following APIs are related to the main implementation of the ZCL groups cluster.

- :cpp:func:`esp_zb_zcl_attr_list_create`
- :cpp:func:`esp_zb_groups_cluster_add_attr`
- :cpp:func:`esp_zb_groups_cluster_create`
- :cpp:func:`esp_zb_cluster_list_add_groups_cluster`
- :cpp:func:`esp_zb_cluster_list_update_groups_cluster`
- :cpp:func:`esp_zb_zcl_groups_add_group_cmd_req`
- :cpp:func:`esp_zb_zcl_groups_remove_group_cmd_req`
- :cpp:func:`esp_zb_zcl_groups_remove_all_groups_cmd_req`
- :cpp:func:`esp_zb_zcl_groups_view_group_cmd_req`
- :cpp:func:`esp_zb_zcl_groups_get_group_membership_cmd_req`
- :cpp:func:`esp_zb_core_action_handler_register`

5.4.3  Typical Usage
~~~~~~~~~~~~~~~~~~~~
This section will introduce the typical usage of a groups cluster, including the data model creation process, related commands,
and handlers.

A groupcast application will be introduced, utilizing the groups cluster.

5.4.3.1 Groups Cluster Creation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you want to **add** group functionality to an endpoint on a **Home Automation Light Device (HAL Device)**, you need to include
a groups cluster in the endpoint. You can refer to the code below.

.. code-block:: c

    #define LIGHT_ENDPOINT 0x10
    esp_zb_on_off_light_cfg_t light_cfg = ESP_ZB_DEFAULT_ON_OFF_LIGHT_CONFIG();
    esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = LIGHT_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_ON_OFF_LIGHT_DEVICE_ID,
        .app_device_version = 0,
    };
    esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();

    /* Below code is equal to esp_zb_on_off_light_ep_create() */
    esp_zb_cluster_list_add_basic_cluster(cluster_list, esp_zb_basic_cluster_create(&(light_cfg.basic_cfg)), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_identify_cluster(cluster_list, esp_zb_identify_cluster_create(&(light_cfg.identify_cfg)), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_groups_cluster(cluster_list, esp_zb_groups_cluster_create(&(light_cfg.groups_cfg)), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_scenes_cluster(cluster_list, esp_zb_scenes_cluster_create(&(light_cfg.scenes_cfg)), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_on_off_cluster(cluster_list, esp_zb_on_off_cluster_create(&(light_cfg.on_off_cfg)), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config);

    esp_zb_device_register(ep_list);


If you intend to **create** a **Home Automation Switch Device (HAS Device)** with a groups client cluster to manage groups in the network,
you can refer to the code below.

.. code-block:: c

    #define SWITCH_ENDPOINT 0x01
    #define LIGHT_ENDPOINT 0x10
    #define GROUP_ID 0x0001
    esp_zb_on_off_switch_cfg_t switch_cfg = ESP_ZB_DEFAULT_ON_OFF_SWITCH_CONFIG();
    esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = SWITCH_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_ON_OFF_SWITCH_DEVICE_ID,
        .app_device_version = 0,
    };
    esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();

    esp_zb_cluster_list_add_basic_cluster(cluster_list, esp_zb_basic_cluster_create(&(switch_cfg.basic_cfg)), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_identify_cluster(cluster_list, esp_zb_identify_cluster_create(&(switch_cfg.identify_cfg)),
                                             ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_groups_cluster(cluster_list, esp_zb_groups_cluster_create(NULL), ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);
    esp_zb_cluster_list_add_on_off_cluster(cluster_list, esp_zb_zcl_attr_list_create(ESP_ZB_ZCL_CLUSTER_ID_ON_OFF), ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);
    esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config);


5.4.3.2 Groups Commands Request and Response
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Add Group Request

If you have already created a **HAS Device** that acts as a coordinator, and you want to send an ``Add Group Request``
command to the **HAS Device** with the short address (suppose it is LIGHT_SHORT_ADDR) to have its ``LIGHT_ENDPOINT (0x0001)`` join
``GROUP_ID (0x0001)``, you can refer to the code below.

.. code-block:: c

    esp_zb_zcl_groups_add_group_cmd_t cmd_req;
    cmd_req.zcl_basic_cmd.dst_addr_u.addr_short = LIGHT_SHORT_ADDR;
    cmd_req.zcl_basic_cmd.src_endpoint = SWITCH_ENDPOINT;
    cmd_req.zcl_basic_cmd.dst_endpoint = LIGHT_ENDPOINT;
    cmd_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    cmd_req.group_id = GROUP_ID;
    ESP_LOGI(TAG, "Add endpoint(%d) to group(%d)", cmd_req.zcl_basic_cmd.dst_endpoint, cmd_req.group_id);
    esp_zb_zcl_groups_add_group_cmd_req(&cmd_req);


- Add Group Response

The callback registered by :cpp:func:`esp_zb_core_action_handler_register` will be triggered with the
``ESP_ZB_CORE_CMD_OPERATE_GROUP_RESP_CB_ID`` signal if the ``Add Group Response`` generated by the
**HAL Device** is received by the **HAS Device**. You can refer to the code below to handle this response.

.. code-block:: c

    static esp_err_t zb_zcl_group_operation_resp(esp_zb_zcl_groups_operate_group_resp_message_t message)
    {
        esp_err_t ret = ESP_OK;
        if (message.info.status == ESP_ZB_ZCL_STATUS_SUCCESS) {
            switch (message.info.command.id) {
            case ESP_ZB_ZCL_CMD_GROUPS_ADD_GROUP:
                ESP_LOGI(TAG, "Succeed in adding endpoint: %d to group: %d", message.info.src_endpoint, message.group_id);
                break;
            case ESP_ZB_ZCL_CMD_GROUPS_REMOVE_GROUP:
                ESP_LOGI(TAG, "Succeed in removing endpoint: %d from group: %d", message.info.src_endpoint, message.group_id);
                break;
            default:
                ESP_LOGW(TAG, "Unknown response command: %d", message.info.command.id);
                break;
            }
        } else {
            ESP_LOGW(TAG, "Failed to operate group with error code: %d", message.info.status);
        }
        return ret;
    }

    static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
    {
        esp_err_t ret = ESP_OK;
        switch (callback_id) {
        case ESP_ZB_CORE_CMD_OPERATE_GROUP_RESP_CB_ID:
            ret = zb_zcl_group_operation_resp(*(esp_zb_zcl_groups_operate_group_resp_message_t *)message);
            break;
        case ESP_ZB_CORE_CMD_VIEW_GROUP_RESP_CB_ID:
            ret = zb_zcl_group_view_resp(*(esp_zb_zcl_groups_view_group_resp_message_t *)message);
            break;
        case ESP_ZB_CORE_CMD_GET_GROUP_MEMBERSHIP_RESP_CB_ID:
            ret = zb_zcl_group_get_membership_resp(*(esp_zb_zcl_groups_get_group_membership_resp_message_t *)message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
        }
        return ret;
    }


Please note that Zigbee device group relationships are non-volatile and stored persistently in NVRAM.


- View Group Request

If you want to view the application name string for a group with ``GROUP_ID`` of the **HAL Device**, you can
call the :cpp:func:`esp_zb_zcl_groups_view_group_cmd_req` in the **HAS Device** to achieve this.You can refer
to the code below. 

.. code-block:: c

    esp_zb_zcl_groups_add_group_cmd_t cmd_req;
    cmd_req.zcl_basic_cmd.dst_addr_u.addr_short = LIGHT_SHORT_ADDR;
    cmd_req.zcl_basic_cmd.src_endpoint = SWITCH_ENDPOINT;
    cmd_req.zcl_basic_cmd.dst_endpoint = LIGHT_ENDPOINT;
    cmd_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    cmd_req.group_id = GROUP_ID;
    ESP_LOGI(TAG, "View group(%d) on address: %04x", cmd_req.group_id, cmd_req.zcl_basic_cmd.dst_addr_u.addr_short);
    esp_zb_zcl_groups_view_group_cmd_req(&cmd_req);


- View Group Response

The callback registered by :cpp:func:`esp_zb_core_action_handler_register` will be triggered with the
``ESP_ZB_CORE_CMD_VIEW_GROUP_RESP_CB_ID`` signal when a ``View Group Response`` command is received.
You can refer to the code below for handling this response.

.. code-block:: c

    static esp_err_t zb_zcl_group_view_resp(esp_zb_zcl_groups_view_group_resp_message_t message)
    {
        esp_err_t ret = ESP_OK;
        if (message.info.status == ESP_ZB_ZCL_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "View response: group id: %d, application name: %s", message.group_id, message.group_name ? message.group_name : 0);
        } else {
            ESP_LOGW(TAG, "Failed to view group with error code: %d", message.info.status);
        }
        return ret;
    }


- Group membership Request

If you want to inquire about the group capacity of the **HAL Device** and the relationship between
``LIGHT_ENDPOINT`` and the group list, you can call :cpp:func:`esp_zb_zcl_groups_get_group_membership_cmd_req`
to do so. Please note that if `cmd_req.group_count` is set to zero, all group identifiers related to
``LIGHT_ENDPOINT`` will be included in the response.

.. code-block:: c

    esp_zb_zcl_groups_get_group_membership_cmd_t cmd_req;
    uint16_t group_list[] = {};
    cmd_req.zcl_basic_cmd.dst_addr_u.addr_short = LIGHT_SHORT_ADDR;
    cmd_req.zcl_basic_cmd.src_endpoint = SWITCH_ENDPOINT;
    cmd_req.zcl_basic_cmd.dst_endpoint = LIGHT_ENDPOINT;
    cmd_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    cmd_req.group_count = 0;
    cmd_req.group_list = group_list;
    esp_zb_zcl_groups_get_group_membership_cmd_req(&cmd_req);
    ESP_LOGI(TAG, "Get the group membership of endpoint %d", cmd_req.zcl_basic_cmd.dst_endpoint);


- Group membership Response

The callback registered by :cpp:func:`esp_zb_core_action_handler_register` will be triggered with the
``ESP_ZB_CORE_CMD_GET_GROUP_MEMBERSHIP_RESP_CB_ID`` signal when the ``Group Membership Response`` is
received by the **HAS Device**. You can refer to the code below to handle this response.

.. code-block:: c

    static esp_err_t zb_zcl_group_get_membership_resp(esp_zb_zcl_groups_get_group_membership_resp_message_t message)
    {
        esp_err_t ret = ESP_OK;
        if (message.info.status == ESP_ZB_ZCL_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "Group membership from address: %04x, Src_endpoint: %d, capacity: %d", message.info.src_address.u.short_addr,
                    message.info.src_endpoint, message.capacity);
            ESP_LOGI(TAG, "Group List:");
            for (int i = 0; i < message.group_count; i++) {
                ESP_LOGI(TAG, "index: %d, Group ID: %d", i, message.group_id[i]);
            }
        }
        return ret;
    }


- Remove Group Request

If you intend to remove a ``LIGHT_ENDPOINT`` endpoint from ``GROUP_ID`` in the **HAL Device**,
you can call the :cpp:func:`esp_zb_zcl_groups_remove_group_cmd_req` to achieve this.

.. code-block:: c

    esp_zb_zcl_groups_add_group_cmd_t cmd_req;
    cmd_req.zcl_basic_cmd.dst_addr_u.addr_short = LIGHT_SHORT_ADDR;
    cmd_req.zcl_basic_cmd.src_endpoint = SWITCH_ENDPOINT;
    cmd_req.zcl_basic_cmd.dst_endpoint = LIGHT_ENDPOINT;
    cmd_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    cmd_req.group_id = GROUP_ID;
    ESP_LOGI(TAG, "Remove endpoint(%d) from group(%d)", cmd_req.zcl_basic_cmd.dst_endpoint, cmd_req.group_id);
    esp_zb_zcl_groups_remove_group_cmd_req(&cmd_req);

- Remove Group Response

The callback registered by :cpp:func:`esp_zb_core_action_handler_register` will be triggered with the
``ESP_ZB_CORE_CMD_OPERATE_GROUP_RESP_CB_ID`` signal when a ``Remove Group Response`` is received by the
**HAS Device**. The implementation for handling this response is the similar as for the ``Add Group Response``.

- Remove All Groups Request 

If you intend to remove all group memberships from the **HAL Device**, you can follow the code below.

.. code-block:: c

    esp_zb_zcl_groups_remove_all_groups_cmd_t cmd_req;
    cmd_req.zcl_basic_cmd.dst_addr_u.addr_short = LIGHT_SHORT_ADDR;
    cmd_req.zcl_basic_cmd.src_endpoint = SWITCH_ENDPOINT;
    cmd_req.zcl_basic_cmd.dst_endpoint = LIGHT_ENDPOINT;
    cmd_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
    esp_zb_zcl_groups_remove_all_groups_cmd_req(&cmd_req);
    ESP_LOGI(TAG, "Remove all group from device address %d", cmd_req.zcl_basic_cmd.dst_addr_u.addr_short);

- Remove All Groups Response

The response is not required for the ``Remove All Groups Request``.


5.4.3.3 Group Cast
^^^^^^^^^^^^^^^^^^
The ZCL Groups cluster provides group management options, enabling developers to implement group casting
functionality, which allows a Zigbee command to be sent from one endpoint to multiple endpoints simultaneously.
For example, if you have three devices (two HAL Devices and one HAS Device) and you want to use group casting
to control the lights of the **HAL Devices** from the **HAS Device**, you can follow these steps:

- Send the :cpp:func:`esp_zb_zcl_groups_add_group_cmd_req` to the HAL Devices to add their ``LIGHT_ENDPOINT`` to the same group.
- Use the following code to groupcast the ``ESP_ZB_ZCL_CMD_ON_OFF_TOGGLE_ID`` command to control all the lights simultaneously:

.. code-block:: c

    esp_zb_zcl_on_off_cmd_t cmd_req;
    cmd_req.zcl_basic_cmd.dst_addr_u.addr_short = GROUP_ID;
    cmd_req.zcl_basic_cmd.src_endpoint = SWITCH_ENDPOINT;
    cmd_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_GROUP_ENDP_NOT_PRESENT;
    cmd_req.on_off_cmd_id = ESP_ZB_ZCL_CMD_ON_OFF_TOGGLE_ID;
    ESP_EARLY_LOGI(TAG, "Send 'on_off toggle' command to group(%d)", cmd_req.zcl_basic_cmd.dst_addr_u.addr_short);
    esp_zb_zcl_on_off_cmd_req(&cmd_req);


Please note that the destination address is replaced with the ``GROUP_ID``, and the address mode is
``ESP_ZB_APS_ADDR_MODE_16_GROUP_ENDP_NOT_PRESENT`` in this command.

Since group casting is performed via a broadcast to all devices for which **macRxOnWhenIdle = TRUE**,
sleeping end devices will not be able to benefit from the features of the Groups and Scenes server cluster.
