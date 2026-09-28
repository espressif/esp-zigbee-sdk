/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "custom_themostat.h"

#include "esp_check.h"

#include "esp_zigbee.h"
#include "ezbee/zha.h"

#define TAG "CUSTOM_THERMOSTAT"

static inline float zb_s16_to_temperature(int16_t value) { return 1.0 * value / 100; }

static void zcl_core_cmd_report_attr_handler(ezb_zcl_cmd_report_attr_message_t *message)
{
    ESP_RETURN_ON_FALSE(message, , TAG, "message is empty");
    ESP_LOGI(TAG, "ZCL Report Attribute message for endpoint(%d) cluster(0x%04x) %s with status(0x%02x)", message->info.dst_ep,
             message->info.cluster_id, message->info.cluster_role == EZB_ZCL_CLUSTER_SERVER ? "server" : "client",
             message->info.status);

    switch (message->info.cluster_id) {
    case EZB_ZCL_CLUSTER_ID_TEMPERATURE_MEASUREMENT: {
        ezb_zcl_report_attr_variable_t *var = message->in.variables;
        while (var) {
            switch (var->attr_id) {
            case EZB_ZCL_ATTR_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_ID:
                ESP_LOGI(TAG, "Temperature sensor measured value: %.2f degrees Celsius",
                         zb_s16_to_temperature(*(int16_t *)var->attr_value));
                break;
            default:
                ESP_LOGI(TAG, "Temperature Measurement attribute ID: 0x%04x with type: 0x%02x", var->attr_id, var->attr_type);
                break;
            }
            var = var->next;
        }
        break;
    }
    default:
        ESP_LOGW(TAG, "Unknown cluster ID: 0x%04x", message->info.cluster_id);
        break;
    }
}

static void esp_zigbee_zcl_core_action_handler(ezb_zcl_core_action_callback_id_t callback_id, void *message)
{
    switch (callback_id) {
    case EZB_ZCL_CORE_REPORT_ATTR_CB_ID:
        zcl_core_cmd_report_attr_handler(message);
        break;
    case EZB_ZCL_CORE_DEFAULT_RSP_CB_ID: {
        ezb_zcl_cmd_default_rsp_message_t *default_rsp = (ezb_zcl_cmd_default_rsp_message_t *)message;
        ESP_LOGI(TAG, "Received ZCL Default Response: 0x%02x", default_rsp->in.status_code);
    } break;
    default:
        ESP_LOGW(TAG, "ZCL Core Action: ID(0x%04lx)", callback_id);
        break;
    }
}

static void esp_zigbee_add_manufacturer_and_model_attributes(ezb_af_ep_desc_t ep_desc)
{
    ezb_zcl_cluster_desc_t basic_cluster = ezb_af_endpoint_get_cluster_desc(ep_desc, EZB_ZCL_CLUSTER_ID_BASIC, EZB_ZCL_CLUSTER_SERVER);

    ezb_zcl_basic_cluster_desc_add_attr(basic_cluster, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)ESP_MANUFACTURER_NAME);
    ezb_zcl_basic_cluster_desc_add_attr(basic_cluster, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)ESP_MODEL_IDENTIFIER);

    ezb_af_endpoint_add_cluster_desc(ep_desc, ezb_zcl_basic_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_CLIENT));
}

static ezb_af_ep_desc_t esp_zigbee_create_thermostat_device(uint8_t ep_id, const ezb_zha_thermostat_config_t *cfg)
{
    ezb_af_ep_desc_t ep_desc = ezb_zha_create_thermostat(ep_id, cfg);

    esp_zigbee_add_manufacturer_and_model_attributes(ep_desc);

    ezb_zcl_cluster_desc_t cluster = ezb_zcl_temperature_measurement_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_CLIENT);
    ezb_af_endpoint_add_cluster_desc(ep_desc, cluster);

    return ep_desc;
}

static ezb_af_ep_desc_t esp_zigbee_create_temperature_sensor_device(uint8_t ep_id, const ezb_zha_temperature_sensor_config_t *cfg)
{
    ezb_af_ep_desc_t ep_desc = ezb_zha_create_temperature_sensor(ep_id, cfg);

    esp_zigbee_add_manufacturer_and_model_attributes(ep_desc);

    return ep_desc;
}

esp_err_t esp_zigbee_setup_zcl_model(void)
{
    ezb_af_device_desc_t        dev_desc       = ezb_af_create_device_desc();
    ezb_af_ep_desc_t            ep_desc        = NULL;

    ezb_zha_thermostat_config_t         thermostat_cfg         = EZB_ZHA_THERMOSTAT_CONFIG();
    ezb_zha_temperature_sensor_config_t temperature_sensor_cfg = EZB_ZHA_TEMPERATURE_SENSOR_CONFIG();

    ep_desc = esp_zigbee_create_thermostat_device(ESP_ZIGBEE_HA_THERMOSTAT_EP_ID, &thermostat_cfg);
    ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));

    ep_desc = esp_zigbee_create_temperature_sensor_device(ESP_ZIGBEE_HA_TEMPERATURE_SENSOR_EP_ID, &temperature_sensor_cfg);
    ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));

    ESP_ERROR_CHECK(ezb_af_device_desc_register(dev_desc));

    ezb_zcl_core_action_handler_register(esp_zigbee_zcl_core_action_handler);

    return ESP_OK;
}
