5.7. Zigbee ZCL General Report
------------------------------


5.7.1 Overview
~~~~~~~~~~~~~~~

In the Zigbee Cluster Library (ZCL) specification, many attributes are defined with ``reportable`` access, meaning that their values can be reported to bound devices
either periodically or whenever the values change, without requiring polling from the other side. This provides an energy-efficient and effective communication
mechanism in Zigbee networks, especially useful for sensor-based applications.

This chapter explains how to configure reportable attributes within a cluster to enable automatic value reporting to the network.


5.7.2 Related APIs Preview
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following APIs are related to the main implementation of the ZCL general attribute reporting feature.

- :cpp:func:`esp_zb_zcl_config_report_cmd_req`
- :cpp:func:`esp_zb_zcl_read_report_config_cmd_req`
- :cpp:func:`esp_zb_zcl_report_attr_cmd_req`
- :cpp:func:`esp_zb_zcl_start_attr_reporting`
- :cpp:func:`esp_zb_zcl_stop_attr_reporting`
- :cpp:func:`esp_zb_zcl_find_reporting_info`
- :cpp:func:`esp_zb_zcl_update_reporting_info`
- :cpp:func:`esp_zb_zcl_reset_all_reporting_info`
- :cpp:func:`esp_zb_zdo_device_bind_req`
- :cpp:func:`esp_zb_zdo_binding_table_req`


5.7.3  Typical Usage
~~~~~~~~~~~~~~~~~~~~

This section introduces how to use the APIs of esp-zigbee-sdk to allow the ``LocalTemperature`` attribute of ``Thermostat`` device can be reported to the bound devices


5.7.3.1 Add Reportable Attribute
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Whether an attribute has `reportable` access is defined in the ZCL specification. The ``esp_zb_xxx_cluster_add_attr()`` API provides a way to add attribute access
for a cluster in accordance with the specification. If custom access is required for an attribute, the :cpp:func:`esp_zb_cluster_add_attr` API may be useful.

For example, if a **Home Automation Thermostat Device** requires the ``LocalTemperature`` and ``OutdoorTemperature`` attributes to have `reportable` access, the
following code can be used as a reference.

.. code-block:: c

    #define COORDINATOR_ADDR 0x0000
    #define HA_THERMOSTAT_CLI_EP 1
    #define HA_THERMOSTAT_SRV_EP 1
    #define MANUFACTURER_NAME "\x09""ESPRESSIF"
    #define MODEL_IDENTIFIER "\x07" CONFIG_IDF_TARGET

    static void zb_custom_thermostat_ep_create(void)
    {
        esp_zb_thermostat_cfg_t thermostat_cfg = ESP_ZB_DEFAULT_THERMOSTAT_CONFIG();
        esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
        esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();
        esp_zb_attribute_list_t *basic_cluster = esp_zb_basic_cluster_create(&(thermostat_cfg.basic_cfg));
        esp_zb_attribute_list_t *thermostat_srv = esp_zb_thermostat_cluster_create(&(thermostat_cfg.thermostat_cfg));
        int16_t thermostat_outdoor_temp = 0x954d;
        esp_zb_endpoint_config_t endpoint_config = {
            .endpoint = HA_THERMOSTAT_SRV_EP,
            .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
            .app_device_id = ESP_ZB_HA_THERMOSTAT_DEVICE_ID,
            .app_device_version = 0,
        };

        ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, MANUFACTURER_NAME));
        ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, MODEL_IDENTIFIER));
        ESP_ERROR_CHECK(esp_zb_cluster_list_add_basic_cluster(cluster_list, basic_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE));
        ESP_ERROR_CHECK(esp_zb_cluster_list_add_identify_cluster(cluster_list, esp_zb_identify_cluster_create(&(thermostat_cfg.identify_cfg)), ESP_ZB_ZCL_CLUSTER_SERVER_ROLE));
        ESP_ERROR_CHECK(esp_zb_cluster_list_add_identify_cluster(cluster_list, esp_zb_zcl_attr_list_create(ESP_ZB_ZCL_CLUSTER_ID_IDENTIFY), ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE));
        ESP_ERROR_CHECK(esp_zb_cluster_add_attr(thermostat_srv, ESP_ZB_ZCL_CLUSTER_ID_THERMOSTAT, ESP_ZB_ZCL_ATTR_THERMOSTAT_OUTDOOR_TEMPERATURE_ID,
                                                ESP_ZB_ZCL_ATTR_TYPE_S16, ESP_ZB_ZCL_ATTR_ACCESS_READ_ONLY | ESP_ZB_ZCL_ATTR_ACCESS_REPORTING, &thermostat_outdoor_temp));
        ESP_ERROR_CHECK(esp_zb_cluster_list_add_thermostat_cluster(cluster_list, thermostat_srv, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE));
        ESP_ERROR_CHECK(esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config));
        ESP_ERROR_CHECK(esp_zb_device_register(ep_list));
        return;
    }

.. note::

    Since ``LocalTemperature`` is a mandatory attribute, it is added by default in the :cpp:func:`esp_zb_cluster_list_add_thermostat_cluster` function, so there
    is no need to add it manually. The ``OutdoorTemperature`` attribute, however, is defined as optional and read-only in the specification. Therefore, the
    :cpp:func:`esp_zb_cluster_add_attr` function is used to add this attribute to the ZCL data model.


5.7.3.2 Add Attribute Reporting Configurations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Zigbee stack will automatically schedule attribute reporting based on the reporting configuration set on the device.

The :cpp:func:`esp_zb_zcl_config_report_cmd_req` function can be used to configure the attribute reporting settings of either a remote or local device.

For example, if you want to configure the ``LocalTemperature`` attribute to report immediately when its value changes by more than 100, and ensure it is reported at
least every 10 seconds regardless of changes on the local device; and additionally, configure the ``OutdoorTemperature`` attribute to report with a minimum interval
of 5 seconds when its value changes by more than 50, and ensure it is reported at least every 10 seconds regardless of changes, you can refer to the following example:

.. code-block:: c

    static void zb_thermostat_local_config_report_req(void)
    {
        esp_zb_zcl_config_report_cmd_t report_cmd = {0};
        int16_t local_temp_change = 100;
        int16_t outdoor_temp_change = 50;
        report_cmd.zcl_basic_cmd.dst_addr_u.addr_short = esp_zb_get_short_address();
        report_cmd.zcl_basic_cmd.dst_endpoint = HA_THERMOSTAT_SRV_EP;
        report_cmd.zcl_basic_cmd.src_endpoint = HA_THERMOSTAT_SRV_EP;
        report_cmd.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
        report_cmd.clusterID = ESP_ZB_ZCL_CLUSTER_ID_THERMOSTAT;

        esp_zb_zcl_config_report_record_t records[] = {
            {
                .direction = ESP_ZB_ZCL_REPORT_DIRECTION_SEND,
                .attributeID = ESP_ZB_ZCL_ATTR_THERMOSTAT_LOCAL_TEMPERATURE_ID,
                .attrType = ESP_ZB_ZCL_ATTR_TYPE_S16,
                .min_interval = 0,
                .max_interval = 10,
                .reportable_change = &local_temp_change,
            },
            {
                .direction = ESP_ZB_ZCL_REPORT_DIRECTION_SEND,
                .attributeID = ESP_ZB_ZCL_ATTR_THERMOSTAT_OUTDOOR_TEMPERATURE_ID,
                .attrType = ESP_ZB_ZCL_ATTR_TYPE_S16,
                .min_interval = 5,
                .max_interval = 10,
                .reportable_change = &outdoor_temp_change,
            },
        };
        report_cmd.record_number = sizeof(records) / sizeof(esp_zb_zcl_config_report_record_t);
        report_cmd.record_field = records;
        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_config_report_cmd_req(&report_cmd);
        esp_zb_lock_release();
    }

.. note::

    If the minimum reporting interval is set to 0x0000, then there is no minimum reporting limit.

    If the maximum reporting interval is set to ``0xFFFF``, the device will not issue reports for the specified attribute, and the configuration information for that
    attribute does not need to be maintained.
    
    If the maximum reporting interval is set to ``0x0000`` and the minimum reporting interval is not equal to ``0xFFFF``, there will be no periodic reporting, but
    change-based reporting still be operational.
    
    If the maximum reporting interval is set to ``0x0000`` and the minimum reporting interval is set to ``0xFFFF``, the device will revert to its default reporting
    configuration. The reportable change field, if present, will be set to zero.
    
    The reportable change field specifies the minimum change to the attribute value that will trigger a report.
    
    The attributes with data types of array, structure, set or bag cannot be reported.
    
    The response of this request will be delivered in the :cpp:func:`esp_zb_core_action_handler_register` callback with the ``ESP_ZB_CORE_CMD_REPORT_CONFIG_RESP_CB_ID`` event.


The following code can be used as a reference to read the reporting configuration of the destination device. This helps verify whether the reporting setup is correct.

.. code-block:: c

    static void zb_thermostat_local_read_reporting_config_req(void)
    {
        esp_zb_zcl_read_report_config_cmd_t read_report_config_cmd = {0};
        esp_zb_zcl_attribute_record_t record[] = {{
            .report_direction = ESP_ZB_ZCL_REPORT_DIRECTION_SEND,
            .attributeID = ESP_ZB_ZCL_ATTR_THERMOSTAT_LOCAL_TEMPERATURE_ID,
        }};
        read_report_config_cmd.zcl_basic_cmd.dst_addr_u.addr_short = esp_zb_get_short_address();
        read_report_config_cmd.zcl_basic_cmd.src_endpoint = HA_THERMOSTAT_SRV_EP;
        read_report_config_cmd.zcl_basic_cmd.dst_endpoint = HA_THERMOSTAT_SRV_EP;
        read_report_config_cmd.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
        read_report_config_cmd.direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV;
        read_report_config_cmd.clusterID = ESP_ZB_ZCL_CLUSTER_ID_THERMOSTAT;
        read_report_config_cmd.record_number = sizeof(record) / sizeof(record[0]);
        read_report_config_cmd.record_field = record;
        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_read_report_config_cmd_req(&read_report_config_cmd);
        esp_zb_lock_release();
    }

.. note::

   The response of this request will be delivered via the :cpp:func:`esp_zb_core_action_handler_register` callback with the ``ESP_ZB_CORE_CMD_READ_REPORT_CFG_RESP_CB_ID`` event.


5.7.3.3 Add Destination for Attribute Reporting
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

An APS binding is required for the stack to determine where the report should be sent when the attribute reporting condition is met, which can be managed via ZDO.
If the ``LocalTemperature`` attribute of the **Home Automation Thermostat Device** is intended to report to the coordinator, you can refer to the following code:

.. code-block:: c

    static void bind_cb(esp_zb_zdp_status_t zdo_status, void *user_ctx)
    {
        esp_zb_zdo_bind_req_param_t *bind_req = (esp_zb_zdo_bind_req_param_t *)user_ctx;

        if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "Successfully bind local temperature from address(0x%x) on endpoint(%d)", bind_req->req_dst_addr, bind_req->dst_endp);
        }
        free(bind_req);
    }

    static void zb_thermostat_local_temperature_bind_req()
    {
        esp_zb_zdo_bind_req_param_t *bind_req = (esp_zb_zdo_bind_req_param_t *)calloc(1, sizeof(esp_zb_zdo_bind_req_param_t));
        bind_req->req_dst_addr = esp_zb_get_short_address();
        bind_req->src_endp = HA_THERMOSTAT_SRV_EP;
        bind_req->dst_endp = HA_THERMOSTAT_CLI_EP;
        bind_req->cluster_id = ESP_ZB_ZCL_CLUSTER_ID_THERMOSTAT;
        bind_req->dst_addr_mode = ESP_ZB_ZDO_BIND_DST_ADDR_MODE_64_BIT_EXTENDED;
        esp_zb_ieee_address_by_short(COORDINATOR_ADDR, bind_req->dst_address_u.addr_long);
        esp_zb_get_long_address(bind_req->src_address);
        esp_zb_zdo_device_bind_req(bind_req, bind_cb, bind_req);
    }


5.7.3.4 Report Attribute Commands
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The esp-zigbee-sdk provides :cpp:func:`esp_zb_zcl_report_attr_cmd_req` to support applications in actively reporting attributes. If you want to report the
``LocalTemperature`` attribute to the coordinator, you can refer to the code below.

.. code-block:: c

    static void zb_thermostat_report_attr_req(void)
    {
        esp_zb_zcl_report_attr_cmd_t report_attr_cmd = {0};
        report_attr_cmd.zcl_basic_cmd.dst_addr_u.addr_short = COORDINATOR_ADDR;
        report_attr_cmd.zcl_basic_cmd.src_endpoint = HA_THERMOSTAT_SRV_EP;
        report_attr_cmd.zcl_basic_cmd.dst_endpoint = HA_THERMOSTAT_CLI_EP;
        report_attr_cmd.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
        report_attr_cmd.direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_CLI;
        report_attr_cmd.clusterID = ESP_ZB_ZCL_CLUSTER_ID_THERMOSTAT;
        report_attr_cmd.attributeID = ESP_ZB_ZCL_ATTR_THERMOSTAT_LOCAL_TEMPERATURE_ID;
        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_report_attr_cmd_req(&report_attr_cmd);
        esp_zb_lock_release();
    }


5.7.3.5 Local Attribute Reporting Configurations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- The :cpp:func:`esp_zb_zcl_start_attr_reporting` and :cpp:func:`esp_zb_zcl_stop_attr_reporting` functions allow the application to notify the stack to start or stop reporting for a specified attribute.

- The :cpp:func:`esp_zb_zcl_find_reporting_info` function enables the application to find the local reporting information.

- The :cpp:func:`esp_zb_zcl_update_reporting_info` function allows the application to update the reporting configuration for an attribute.

- The :cpp:func:`esp_zb_zcl_reset_all_reporting_info` function provides a way to reset all reporting information configured on the device.


5.7.4  Failure Analysis
~~~~~~~~~~~~~~~~~~~~~~~

If the attribute reporting feature does not work on your device, please follow the steps below to debug:

- Call :cpp:func:`esp_zb_bdb_dev_joined` to confirm the device has successfully joined the network.

- Double-check that the destination device is on the same Zigbee network as the current device.

- Use :cpp:func:`esp_zb_zcl_get_attribute` to verify that ``ESP_ZB_ZCL_ATTR_ACCESS_REPORTING`` is set in the returned attribute access flags.

- Ensure the change of attribute value is greater than the ``reportable_change`` of reporting information and the type of attribute value is reportable.

- Use :cpp:func:`esp_zb_zdo_binding_table_req` to check whether this attribute is bound to the correct destination address.

- Use :cpp:func:`esp_zb_zcl_find_reporting_info` to inspect the reporting information and ensure that this attribute is configured properly.
