Zigbee ZCL General Report
-------------------------


Overview
~~~~~~~~

In the Zigbee Cluster Library (ZCL) specification, many attributes are defined with ``reportable`` access, meaning that their values can be reported to bound devices
either periodically or whenever the values change, without requiring polling from the other side. This provides an energy-efficient and effective communication
mechanism in Zigbee networks, especially useful for sensor-based applications.

This chapter explains how to configure reportable attributes within a cluster to enable automatic value reporting to the network.


Related APIs Preview
~~~~~~~~~~~~~~~~~~~~

The following APIs are related to the main implementation of the ZCL general attribute reporting feature.

- :cpp:func:`ezb_zcl_config_report_cmd_req`
- :cpp:func:`ezb_zcl_read_report_config_cmd_req`
- :cpp:func:`ezb_zcl_report_attr_cmd_req`
- :cpp:func:`ezb_zcl_reporting_start_attr_report`
- :cpp:func:`ezb_zcl_reporting_stop_attr_report`
- :cpp:func:`ezb_zcl_reporting_info_find`
- :cpp:func:`ezb_zcl_reporting_info_update`
- :cpp:func:`ezb_zcl_reporting_info_remove`
- :cpp:func:`ezb_zdo_bind_req`
- :cpp:func:`ezb_zdo_nwk_mgmt_bind_req`


Typical Usage
~~~~~~~~~~~~~

This section introduces how to use the APIs of esp-zigbee-sdk to allow the ``LocalTemperature`` attribute of ``Thermostat`` device can be reported to the bound devices


Add Reportable Attribute
^^^^^^^^^^^^^^^^^^^^^^^^

Whether an attribute has `reportable` access is defined in the ZCL specification. The ``ezb_zcl_{name}_cluster_desc_add_attr()`` API provides a way to add attribute
access for a cluster in accordance with the specification. If custom access is required for an attribute, the ``ezb_zcl_{name}_cluster_desc_add_manuf_attr()`` API
may be useful.

For example, if a **Thermostat Device** requires the ``LocalTemperature`` and ``OutdoorTemperature`` attributes to have `reportable` access, the following code can
be used as a reference.

.. code-block:: c

    esp_err_t esp_zigbee_create_thermostat_device(void)
    {
        ezb_af_device_desc_t dev_desc = ezb_af_create_device_desc();
        ezb_zha_thermostat_config_t thermostat_cfg = EZB_ZHA_THERMOSTAT_CONFIG();
        ezb_af_ep_desc_t ep_desc = ezb_zha_create_thermostat(ESP_ZIGBEE_HA_THERMOSTAT_EP_ID, &thermostat_cfg);
        ezb_zcl_cluster_desc_t basic_desc = {0};
        ezb_zcl_cluster_desc_t thermostat_desc = {0};
        int16_t thermostat_outdoor_temp = EZB_ZCL_THERMOSTAT_OUTDOOR_TEMPERATURE_DEFAULT_VALUE;

        basic_desc = ezb_af_endpoint_get_cluster_desc(ep_desc, EZB_ZCL_CLUSTER_ID_BASIC, EZB_ZCL_CLUSTER_SERVER);
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)"\x09""ESPRESSIF");
        ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)"\x07"CONFIG_IDF_TARGET);
        thermostat_desc = ezb_af_endpoint_get_cluster_desc(ep_desc, EZB_ZCL_CLUSTER_ID_THERMOSTAT, EZB_ZCL_CLUSTER_SERVER);
        ezb_zcl_thermostat_cluster_desc_add_manuf_attr(
            thermostat_desc, EZB_ZCL_ATTR_THERMOSTAT_OUTDOOR_TEMPERATURE_ID, EZB_ZCL_ATTR_TYPE_S16,
            EZB_ZCL_ATTR_ACCESS_READ_ONLY | EZB_ZCL_ATTR_ACCESS_REPORTING, EZB_ZCL_STD_MANUF_CODE, &thermostat_outdoor_temp);
        ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, ezb_zcl_basic_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_CLIENT)));
        ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, ezb_zcl_thermostat_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_CLIENT)));
        ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));
        ESP_ERROR_CHECK(ezb_af_device_desc_register(dev_desc));
        return ESP_OK;
    }

.. note::

    Since ``LocalTemperature`` is a mandatory attribute, it is added by default in the :cpp:func:`ezb_zha_create_thermostat` function, so there
    is no need to add it manually. The ``OutdoorTemperature`` attribute, however, is defined as optional and read-only in the specification. Therefore, the
    :cpp:func:`ezb_zcl_thermostat_cluster_desc_add_manuf_attr` function is used to add this attribute to the ZCL data model.


Add Attribute Reporting Configurations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Zigbee stack will automatically schedule attribute reporting based on the reporting configuration set on the device.

The :cpp:func:`ezb_zcl_config_report_cmd_req` API can be used to configure the attribute reporting settings of either a remote or local device.

Based on the code below, the ``LocalTemperature`` attribute is configured to report immediately when its value changes by more than 100, and to be reported
at least every 10 seconds regardless of changes on the local device. Additionally, the ``OutdoorTemperature`` attribute is configured to report with a
minimum interval of 5 seconds when its value changes by more than 50, and to be reported at least every 10 seconds regardless of changes.

.. code-block:: c

    static ezb_err_t thermostat_local_config_report_req(uint8_t ep_id)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        int16_t local_temp_change = 100;
        int16_t outdoor_temp_change = 50;
        ezb_zcl_config_report_record_t records[] = {
            {
                .direction = EZB_ZCL_REPORTING_SEND,
                .attr_id = EZB_ZCL_ATTR_THERMOSTAT_LOCAL_TEMPERATURE_ID,
                .client.attr_type = EZB_ZCL_ATTR_TYPE_INT16,
                .client.min_interval = 0,
                .client.max_interval = 10,
                .client.reportable_change = {.s16 = local_temp_change},
            },
            {
                .direction = EZB_ZCL_REPORTING_SEND,
                .attr_id = EZB_ZCL_ATTR_THERMOSTAT_OUTDOOR_TEMPERATURE_ID,
                .client.attr_type = EZB_ZCL_ATTR_TYPE_INT16,
                .client.min_interval = 5,
                .client.max_interval = 10,
                .client.reportable_change = {.s16 = outdoor_temp_change},
            },
        };

        ezb_zcl_config_report_cmd_t report_cmd = {
            .cmd_ctrl =
                {
                    .dst_addr =
                        {
                            .addr_mode = EZB_ADDR_MODE_SHORT,
                            .u.short_addr = ezb_nwk_get_short_address(),
                        },
                    .src_ep = ep_id,
                    .dst_ep = ep_id,
                    .cluster_id = EZB_ZCL_CLUSTER_ID_THERMOSTAT,
                },
        };

        report_cmd.payload.record_number = sizeof(records) / sizeof(ezb_zcl_config_report_record_t);
        report_cmd.payload.record_field = records;
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_config_report_cmd_req(&report_cmd);
        esp_zigbee_lock_release();
        return ret;
    }

.. note::

    If the minimum reporting interval is set to 0x0000, then there is no minimum reporting limit.

    If the maximum reporting interval is set to ``0xFFFF``, the device will not issue reports for the specified attribute, and the configuration information for
    that attribute does not need to be maintained.

    If the maximum reporting interval is set to ``0x0000`` and the minimum reporting interval is not equal to ``0xFFFF``, there will be no periodic reporting, but
    change-based reporting still be operational.

    If the maximum reporting interval is set to ``0x0000`` and the minimum reporting interval is set to ``0xFFFF``, the device will revert to its default reporting
    configuration. The reportable change field, if present, will be set to zero.

    The reportable change field specifies the minimum change to the attribute value that will trigger a report.

    The attributes with data types of array, structure, set or bag cannot be reported.

    The response of this request will be delivered in the :cpp:func:`ezb_zcl_core_action_handler_register` callback with the ``EZB_ZCL_CORE_CMD_REPORT_CONFIG_RESP_CB_ID`` event.


The following code can be used as a reference to read the reporting configuration of the destination device. This helps verify whether the reporting setup is correct.

.. code-block:: c

    static ezb_err_t thermostat_local_read_reporting_config_req(uint8_t ep_id)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_read_report_config_record_t record[] = {{
            .report_direction = EZB_ZCL_REPORTING_SEND,
            .attr_id = EZB_ZCL_ATTR_THERMOSTAT_LOCAL_TEMPERATURE_ID,
        }};
        ezb_zcl_read_report_config_cmd_t read_report_config_cmd = {
            .cmd_ctrl =
                {
                    .dst_addr =
                        {
                            .addr_mode = EZB_ADDR_MODE_SHORT,
                            .u.short_addr = ezb_nwk_get_short_address(),
                        },
                    .src_ep = ep_id,
                    .dst_ep = ep_id,
                    .cluster_id = EZB_ZCL_CLUSTER_ID_THERMOSTAT,
                },
        };
        read_report_config_cmd.payload.record_number = sizeof(record) / sizeof(record[0]);
        read_report_config_cmd.payload.record_field = record;
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_read_report_config_cmd_req(&read_report_config_cmd);
        esp_zigbee_lock_release();
        return ret;
    }

.. note::

   The response of this request will be delivered via the :cpp:func:`esp_zb_core_action_handler_register` callback with the ``ESP_ZB_CORE_CMD_READ_REPORT_CFG_RESP_CB_ID`` event.


Add Destination for Attribute Reporting
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

An APS binding is required for the stack to determine where the report should be sent when the attribute reporting condition is met, which can be managed via ZDO.
If the ``LocalTemperature`` attribute of the **Thermostat Device** is intended to report to the destination device, the following code can be used as a references:

.. code-block:: c

    static void bind_result(const ezb_zdp_bind_req_result_t *result, void *user_ctx)
    {
        ezb_zdo_bind_req_t *bind_req = (ezb_zdo_bind_req_t *)user_ctx;

        assert(result);
        if (result->error == EZB_ERR_NONE) {
            if (result->rsp && result->rsp->status == EZB_ZDP_STATUS_SUCCESS) {
                if (bind_req->dst_nwk_addr == ezb_nwk_get_short_address()) {
                    ESP_LOGI(TAG, "Bound local thermostat successfully");
                }
            } else {
                ESP_LOGE(TAG, "Bound failure with status (0x%02x)", result->rsp->status);
            }
        } else {
            ESP_LOGE(TAG, "Bound failure with error (0x%04x) result", result->error);
        }
        if (user_ctx) {
            free(user_ctx);
        }
    }

    static ezb_err_t thermostat_local_bind(uint16_t dst_short_addr, uint8_t dst_ep, uint8_t src_ep)
    {
        ezb_err_t ret = EZB_ERR_FAIL;
        ezb_zdo_bind_req_t *bind_sensor = malloc(sizeof(ezb_zdo_bind_req_t));
        bind_sensor->dst_nwk_addr = ezb_nwk_get_short_address();
        bind_sensor->field.src_ep = src_ep;
        bind_sensor->field.cluster_id = EZB_ZCL_CLUSTER_ID_THERMOSTAT;
        bind_sensor->field.dst_addr_mode = EZB_ADDR_MODE_EXT;
        bind_sensor->field.dst_ep = dst_ep;
        bind_sensor->cb = bind_result;
        bind_sensor->user_ctx = bind_sensor;

        ezb_nwk_get_extended_address(&bind_sensor->field.src_addr);

        ESP_RETURN_ON_ERROR(ezb_address_extended_by_short(dst_short_addr, &bind_sensor->field.dst_addr.extended_addr), TAG,
                            "Failed to get extended address for destination device(0x%04hx)", dst_short_addr);
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zdo_bind_req(bind_sensor);
        esp_zigbee_lock_release();

        return ret;
    }


Report Attribute Commands
^^^^^^^^^^^^^^^^^^^^^^^^^

The esp-zigbee-sdk provides :cpp:func:`ezb_zcl_report_attr_cmd_req` API to support applications in actively reporting attributes. If you want to report the
``LocalTemperature`` attribute to the bound destination, you can refer to the code below.

.. code-block:: c

    static ezb_err_t thermostat_report_attr_req(uint8_t src_ep)
    {
        ezb_err_t ret = EZB_ERR_NONE;
        ezb_zcl_report_attr_cmd_t report_attr_cmd = {
            .cmd_ctrl =
                {
                    .fc.direction       = EZB_ZCL_CMD_DIRECTION_TO_CLI,
                    .dst_addr.addr_mode = EZB_ADDR_MODE_NONE,
                    .src_ep             = src_ep,
                    .cluster_id         = EZB_ZCL_CLUSTER_ID_THERMOSTAT,
                },
            .payload =
                {
                    .attr_id = EZB_ZCL_ATTR_THERMOSTAT_LOCAL_TEMPERATURE_ID,
                },
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_report_attr_cmd_req(&report_attr_cmd);
        esp_zigbee_lock_release();
        return ret;
    }


Local Attribute Reporting Configurations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- The :cpp:func:`ezb_zcl_reporting_start_attr_report` and :cpp:func:`ezb_zcl_reporting_stop_attr_report` functions allow the application to notify the stack to
  start or stop reporting for a specified attribute.

- The :cpp:func:`ezb_zcl_reporting_info_find` function enables the application to find the local reporting information.

- The :cpp:func:`ezb_zcl_reporting_info_update` function allows the application to update the reporting configuration for an attribute.

- The :cpp:func:`ezb_zcl_reporting_info_remove` function provides a way to remove the reporting information for an attribute.


Failure Analysis
~~~~~~~~~~~~~~~~

If the attribute reporting feature does not work on your device, please follow the steps below to debug:

- Call :cpp:func:`ezb_bdb_dev_joined` to confirm the device has successfully joined the network.

- Double-check that the destination device is on the same Zigbee network as the current device.

- Use :cpp:func:`ezb_zcl_get_attr_desc` to verify that ``EZB_ZCL_ATTR_ACCESS_REPORTING`` is set in the returned attribute access flags.

- Ensure the change of attribute value is greater than the ``reportable_change`` of reporting information and the type of attribute value is reportable.

- Use :cpp:func:`ezb_zdo_nwk_mgmt_bind_req` to check whether this attribute is bound to the correct destination address.

- Use :cpp:func:`ezb_zcl_reporting_info_find` to inspect the reporting information and ensure that this attribute is configured properly.
