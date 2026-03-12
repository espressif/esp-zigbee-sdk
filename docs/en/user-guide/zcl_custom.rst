Zigbee ZCL Custom Cluster
-------------------------

Overview
~~~~~~~~
Zigbee Cluster Library (ZCL) defines a set of standardized functions based on common application scenarios and classic device characteristics, known as clusters.
Each cluster represents a group of related attributes and commands.

However, standard clusters cannot cover everything. In some special scenarios, the standard clusters cannot fully meet the developers' needs.
Therefore, the functionality of custom clusters has emerged.

Such clusters do not have clearly defined attributes and commands in ZCL, requiring developers to create their own specific attributes, commands, and corresponding handling functions.

This chapter will introduce a series of APIs provided by the esp-zigbee-sdk for custom clusters and their usage.


Related APIs Preview
~~~~~~~~~~~~~~~~~~~~
The following APIs are related to the main implementation of the custom cluster.

- :cpp:func:`ezb_zcl_custom_create_cluster_desc`
- :cpp:func:`ezb_zcl_custom_cluster_desc_add_manuf_attr`
- :cpp:func:`ezb_zcl_custom_cluster_cmd_req`
- :cpp:func:`ezb_zcl_custom_cluster_handlers_register`

Typical Usage
~~~~~~~~~~~~~
This section introduces an example that explains how to use the custom cluster APIs to define custom devices and implement custom functionality.

Custom Cluster Creation
^^^^^^^^^^^^^^^^^^^^^^^

A **Home Automation Custom Server Device (HACS Device)** with the custom cluster server, which contains an attribute with REPORT and READ access and
string type, can be created as follows:

.. code-block:: c

    #define CUSTOM_DEVICE_ID                     0xff01
    #define CUSTOM_CLUSTER_ID                    0xff00
    #define CUSTOM_CLUSTER_QUERY_NAME_CMD_ID     0x00
    #define CUSTOM_CLUSTER_QUERY_NAME_RSP_CMD_ID 0x01
    #define CUSTOM_CLUSTER_NAME_ATTR_ID          0x0000

    esp_err_t customized_server_device_setup(uint8_t ep_id)
    {
        ezb_af_device_desc_t   dev_desc      = ezb_af_create_device_desc();
        ezb_af_ep_desc_t       ep_desc       = NULL;
        ezb_zcl_cluster_desc_t basic_desc    = NULL;
        ezb_zcl_cluster_desc_t identify_desc = NULL;
        ezb_zcl_cluster_desc_t custom_desc   = NULL;

        ezb_zcl_basic_cluster_server_config_t basic_cfg = {
            .zcl_version  = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,
            .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,
        };
        basic_desc = ezb_zcl_basic_create_cluster_desc(&basic_cfg, EZB_ZCL_CLUSTER_SERVER);
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID,
                                            (void *)"\x09""ESPRESSIF");
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)"\x07" CONFIG_IDF_TARGET);

        ezb_zcl_identify_cluster_server_config_t identify_cfg = {
            .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,
        };
        identify_desc = ezb_zcl_identify_create_cluster_desc(&identify_cfg, EZB_ZCL_CLUSTER_SERVER);

        ezb_zcl_custom_cluster_config_t custom_cfg = {
            .cluster_id  = CUSTOM_CLUSTER_ID,
            .init_func   = customized_server_device_init,
            .deinit_func = NULL,
        };
        custom_desc = ezb_zcl_custom_create_cluster_desc(&custom_cfg, EZB_ZCL_CLUSTER_SERVER);

        ezb_zcl_custom_cluster_desc_add_attr(custom_desc, CUSTOM_CLUSTER_NAME_ATTR_ID, EZB_ZCL_ATTR_TYPE_STRING,
                                            EZB_ZCL_ATTR_ACCESS_READ | EZB_ZCL_ATTR_ACCESS_REPORTING,
                                            (void *)"\x0b""ESP-Zigbee");
        ezb_af_ep_config_t ep_config = {
            .ep_id              = ep_id,
            .app_profile_id     = EZB_AF_HA_PROFILE_ID,
            .app_device_id      = CUSTOM_DEVICE_ID,
            .app_device_version = 0,
        };
        ep_desc = ezb_af_create_endpoint_desc(&ep_config);

        ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, basic_desc));
        ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, identify_desc));
        ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, custom_desc));

        ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));

        ESP_ERROR_CHECK(ezb_af_device_desc_register(dev_desc));

        return ESP_OK;
    }


A **Home Automation Custom Client Device (HACC Device)** with the custom cluster client, which is used to send the custom command, can be created as follows:

.. code-block:: c

    esp_err_t customized_client_device_setup(uint8_t ep_id)
    {
        ezb_af_device_desc_t   dev_desc      = ezb_af_create_device_desc();
        ezb_af_ep_desc_t       ep_desc       = NULL;
        ezb_zcl_cluster_desc_t basic_desc    = NULL;
        ezb_zcl_cluster_desc_t identify_desc = NULL;
        ezb_zcl_cluster_desc_t custom_desc   = NULL;

        ezb_zcl_basic_cluster_server_config_t basic_cfg = {
            .zcl_version  = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,
            .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,
        };
        basic_desc = ezb_zcl_basic_create_cluster_desc(&basic_cfg, EZB_ZCL_CLUSTER_SERVER);
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID,
                                            (void *)"\x09""ESPRESSIF");
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)"\x07" CONFIG_IDF_TARGET);

        ezb_zcl_identify_cluster_server_config_t identify_cfg = {
            .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,
        };
        identify_desc = ezb_zcl_identify_create_cluster_desc(&identify_cfg, EZB_ZCL_CLUSTER_SERVER);

        ezb_zcl_custom_cluster_config_t custom_cfg = {
            .cluster_id  = CUSTOM_CLUSTER_ID,
            .init_func   = customized_client_device_init,
            .deinit_func = NULL,
        };
        custom_desc = ezb_zcl_custom_create_cluster_desc(&custom_cfg, EZB_ZCL_CLUSTER_CLIENT);

        ezb_af_ep_config_t ep_config = {
            .ep_id              = ep_id,
            .app_profile_id     = EZB_AF_HA_PROFILE_ID,
            .app_device_id      = CUSTOM_DEVICE_ID,
            .app_device_version = 0,
        };
        ep_desc = ezb_af_create_endpoint_desc(&ep_config);

        ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, basic_desc));
        ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, identify_desc));
        ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, custom_desc));

        ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));

        ESP_ERROR_CHECK(ezb_af_device_desc_register(dev_desc));

        return ESP_OK;
    }


.. note::

    Please note that the custom cluster identifier MUST be greater than :c:macro:`EZB_ZCL_CLUSTER_ID_MIN_CUSTOM` in esp-zigbee-sdk.

    The ``ezb_zcl_custom_cluster_config_t`` structure provides the interface for the developer to initialize the custom cluster.

    The above custom cluster client is used to query the name of the device from the custom cluster server.


Custom Command Requests
^^^^^^^^^^^^^^^^^^^^^^^

The :cpp:func:`ezb_zcl_custom_cluster_cmd_req` API can be used to send a custom command request, below code can be used by **HACC Device** to query the name of
the device from the **HACS Device**.

.. code-block:: c

    ezb_err_t customized_client_device_send_query_name_cmd(uint8_t src_ep, uint8_t dst_ep, uint16_t dst_short_addr)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_custom_cluster_cmd_t cmd_req = {
            .cmd_ctrl = {
                .dst_addr = {
                    .addr_mode = EZB_ADDR_MODE_SHORT,
                    .u.short_addr = dst_short_addr,
                },
                .src_ep = src_ep,
                .dst_ep = dst_ep,
                .cluster_id = CUSTOM_CLUSTER_ID,
            },
            .cmd_id = CUSTOM_CLUSTER_QUERY_NAME_CMD_ID,
            .data_length = 0,
            .data = NULL,
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_custom_cluster_cmd_req(&cmd_req);
        esp_zigbee_lock_release();
        return ret;
    }


Custom Cluster Handlers
^^^^^^^^^^^^^^^^^^^^^^^

The :cpp:func:`ezb_zcl_custom_cluster_handlers_register` API can be used to register the custom cluster handlers. It provides below callbacks for the
developer to improve the custom functionality.

The ``ezb_zcl_custom_cluster_process_cmd_t`` callback will be triggered When a ZCL command for the ``CUSTOM_CLUSTER_ID`` is received.
The ``ezb_zcl_custom_cluster_disc_cmd_t`` callback will be triggered When a ZCL general discovery command for the ``CUSTOM_CLUSTER_ID`` is received.
The ``ezb_zcl_custom_cluster_check_value_t`` callback will be triggered before the write attribute of the ``CUSTOM_CLUSTER_ID`` is performed.
The ``ezb_zcl_custom_cluster_write_attr_t`` callback will be triggered after the write attribute of the ``CUSTOM_CLUSTER_ID`` is performed.

Below code shows the implementation of the **HACS Device** to handle the query name command and respond the name of the device.

.. code-block:: c

    ezb_zcl_status_t customized_server_device_process_cmd_handler(const ezb_zcl_cmd_hdr_t *header,
                                                                  const uint8_t           *payload,
                                                                  uint16_t                 payload_length)
    {
        ezb_zcl_status_t ret = EZB_ZCL_STATUS_UNSUP_CMD;
        ESP_RETURN_ON_FALSE(header && payload && payload_length, ret = EZB_ZCL_STATUS_INVALID_VALUE, TAG, "Invalid command");
        if (header->cluster_id == CUSTOM_CLUSTER_ID) {
            if (header->cmd_id == CUSTOM_CLUSTER_QUERY_NAME_CMD_ID) {
                ezb_zcl_attr_desc_t attr_desc = ezb_zcl_get_attr_desc(header->dst_ep, header->cluster_id, EZB_ZCL_CLUSTER_SERVER,
                                                                    CUSTOM_CLUSTER_NAME_ATTR_ID, EZB_ZCL_STD_MANUF_CODE);
                assert(attr_desc);
                char                        *name    = (char *)ezb_zcl_attr_desc_get_value(attr_desc);
                ezb_zcl_custom_cluster_cmd_t cmd_req = {
                    .cmd_ctrl =
                        {
                            .dst_addr = header->src_addr,
                            .src_ep   = header->dst_ep,
                            .dst_ep   = header->src_ep,
                        },
                    .cmd_id      = CUSTOM_CLUSTER_QUERY_NAME_RSP_CMD_ID,
                    .data_length = name ? name[0] : 0,
                    .data        = (void *)name,
                };
                ezb_zcl_custom_cluster_cmd_req(&cmd_req);
            }
        }
        return ret;
    }

    static void customized_server_device_init(uint8_t ep_id)
    {
        ezb_zcl_custom_cluster_handlers_t custom_handlers = {
            .cluster_id     = CUSTOM_CLUSTER_ID,
            .cluster_role   = EZB_ZCL_CLUSTER_SERVER,
            .process_cmd_cb = customized_server_device_process_cmd_handler,
            .check_value_cb = NULL,
            .write_attr_cb  = NULL,
            .cmd_disc_cb    = NULL,
        };
        ezb_zcl_custom_cluster_handlers_register(&custom_handlers);
    }

Below code shows the implementation of the **HACC Device** to handle the query name response and respond default response.

.. code-block:: c

    ezb_zcl_status_t customized_client_device_process_cmd_handler(const ezb_zcl_cmd_hdr_t *header,
                                                                  const uint8_t           *payload,
                                                                  uint16_t                 payload_length)
    {
        ezb_zcl_status_t ret = EZB_ZCL_STATUS_UNSUP_CMD;
        ESP_RETURN_ON_FALSE(header && payload && payload_length, ret = EZB_ZCL_STATUS_INVALID_VALUE, TAG, "Invalid command");
        if (header->cluster_id == CUSTOM_CLUSTER_ID) {
            if (header->cmd_id == CUSTOM_CLUSTER_QUERY_NAME_RSP_CMD_ID) {
                ESP_LOGI(TAG, "Receive custom cluster query name response: payload: %*s", payload_length, payload);
                ezb_zcl_default_rsp_cmd_t cmd_req = {
                    .cmd_ctrl =
                        {
                            .dst_addr = header->src_addr,
                            .src_ep   = header->dst_ep,
                            .dst_ep   = header->src_ep,
                        },
                    .payload =
                        {
                            .tsn         = header->tsn,
                            .rsp_to_cmd  = header->cmd_id,
                            .status_code = EZB_ZCL_STATUS_SUCCESS,
                        },
                };
                ret = ezb_zcl_default_rsp_cmd_req(&cmd_req) == EZB_ERR_NONE ? EZB_ZCL_STATUS_SUCCESS : EZB_ZCL_STATUS_FAIL;
            }
        }
        return ret;
    }

    static void customized_client_device_init(uint8_t ep_id)
    {
        ezb_zcl_custom_cluster_handlers_t custom_handlers = {
            .cluster_id     = CUSTOM_CLUSTER_ID,
            .cluster_role   = EZB_ZCL_CLUSTER_CLIENT,
            .process_cmd_cb = customized_client_device_process_cmd_handler,
            .check_value_cb = NULL,
            .write_attr_cb  = NULL,
            .cmd_disc_cb    = NULL,
        };

        ezb_zcl_custom_cluster_handlers_register(&custom_handlers);
    }
