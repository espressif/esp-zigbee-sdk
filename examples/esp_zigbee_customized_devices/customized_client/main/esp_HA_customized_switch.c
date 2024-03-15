/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee customized client Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */
#include "esp_HA_customized_switch.h"
#include "esp_check.h"
#include "esp_err.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "zcl/esp_zigbee_zcl_common.h"

#if !defined ZB_ED_ROLE
#error Define ZB_ED_ROLE in idf.py menuconfig to compile light switch (End Device) source code.
#endif

static const char *TAG = "ESP_HA_ON_OFF_SWITCH";

static switch_func_pair_t button_func_pair[] = {
    {GPIO_INPUT_IO_TOGGLE_SWITCH, SWITCH_ONOFF_TOGGLE_CONTROL}
};

typedef struct light_bulb_device_params_s {
    esp_zb_ieee_addr_t ieee_addr;
    uint8_t  endpoint;
    uint16_t short_addr;
} light_bulb_device_params_t;

typedef struct zdo_info_ctx_s {
    uint8_t endpoint;
    uint16_t short_addr;
} zdo_info_user_ctx_t;

/* remote device struct for recording and managing node info */
light_bulb_device_params_t on_off_light;

static void zb_buttons_handler(switch_func_pair_t *button_func_pair)
{
    switch (button_func_pair->func) {
    case SWITCH_ONOFF_TOGGLE_CONTROL: {
        /* send on-off toggle command to remote device */
        esp_zb_zcl_on_off_cmd_t cmd_req;
        cmd_req.zcl_basic_cmd.dst_addr_u.addr_short = on_off_light.short_addr;
        cmd_req.zcl_basic_cmd.dst_endpoint = on_off_light.endpoint;
        cmd_req.zcl_basic_cmd.src_endpoint = HA_ONOFF_SWITCH_ENDPOINT;
        cmd_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
        cmd_req.on_off_cmd_id = ESP_ZB_ZCL_CMD_ON_OFF_TOGGLE_ID;
        esp_zb_lock_acquire(portMAX_DELAY);
        esp_zb_zcl_on_off_cmd_req(&cmd_req);
        esp_zb_lock_release();
        ESP_EARLY_LOGI(TAG, "Send 'on_off toggle' command to address(0x%x) endpoint(%d)", on_off_light.short_addr, on_off_light.endpoint);
    } break;
    default:
        break;
    }
}

static esp_err_t deferred_driver_init(void)
{
    ESP_RETURN_ON_FALSE(switch_driver_init(button_func_pair, PAIR_SIZE(button_func_pair), zb_buttons_handler), ESP_FAIL, TAG,
                        "Failed to initialize switch driver");
    return ESP_OK;
}

static void bdb_start_top_level_commissioning_cb(uint8_t mode_mask)
{
    ESP_RETURN_ON_FALSE(esp_zb_bdb_start_top_level_commissioning(mode_mask) == ESP_OK, , TAG, "Failed to start Zigbee bdb commissioning");
}

static void bind_cb(esp_zb_zdp_status_t zdo_status, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        ESP_LOGI(TAG, "Bind response from address(0x%x), endpoint(%d) with status(%d)", ((zdo_info_user_ctx_t *)user_ctx)->short_addr,
                 ((zdo_info_user_ctx_t *)user_ctx)->endpoint, zdo_status);
        /* configure report attribute command */
        esp_zb_zcl_config_report_cmd_t report_cmd;
        bool report_change = 0;
        report_cmd.zcl_basic_cmd.dst_addr_u.addr_short = on_off_light.short_addr;
        report_cmd.zcl_basic_cmd.dst_endpoint = on_off_light.endpoint;
        report_cmd.zcl_basic_cmd.src_endpoint = HA_ONOFF_SWITCH_ENDPOINT;
        report_cmd.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
        report_cmd.clusterID = ESP_ZB_ZCL_CLUSTER_ID_ON_OFF;

        esp_zb_zcl_config_report_record_t records[] = {
            {ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV, ESP_ZB_ZCL_ATTR_ON_OFF_ON_OFF_ID, ESP_ZB_ZCL_ATTR_TYPE_BOOL, 0, 30, &report_change}};
        report_cmd.record_number = sizeof(records) / sizeof(esp_zb_zcl_config_report_record_t);
        report_cmd.record_field = records;

        esp_zb_zcl_config_report_cmd_req(&report_cmd);
    }
}

static void ieee_cb(esp_zb_zdp_status_t zdo_status, esp_zb_ieee_addr_t ieee_addr, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        memcpy(&(on_off_light.ieee_addr), ieee_addr, sizeof(esp_zb_ieee_addr_t));
        ESP_LOGI(TAG, "IEEE address: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
                 ieee_addr[7], ieee_addr[6], ieee_addr[5], ieee_addr[4],
                 ieee_addr[3], ieee_addr[2], ieee_addr[1], ieee_addr[0]);
        /* bind the on-off light to on-off switch */
        esp_zb_zdo_bind_req_param_t bind_req;
        memcpy(&(bind_req.src_address), on_off_light.ieee_addr, sizeof(esp_zb_ieee_addr_t));
        bind_req.src_endp = on_off_light.endpoint;
        bind_req.cluster_id = ESP_ZB_ZCL_CLUSTER_ID_ON_OFF;
        bind_req.dst_addr_mode = ESP_ZB_ZDO_BIND_DST_ADDR_MODE_64_BIT_EXTENDED;
        esp_zb_get_long_address(bind_req.dst_address_u.addr_long);
        bind_req.dst_endp = HA_ONOFF_SWITCH_ENDPOINT;
        bind_req.req_dst_addr = on_off_light.short_addr;
        static zdo_info_user_ctx_t test_info_ctx;
        test_info_ctx.endpoint = HA_ONOFF_SWITCH_ENDPOINT;
        test_info_ctx.short_addr = on_off_light.short_addr;
        esp_zb_zdo_device_bind_req(&bind_req, bind_cb, (void *) & (test_info_ctx));
    }
}

static void ep_cb(esp_zb_zdp_status_t zdo_status, uint8_t ep_count, uint8_t *ep_id_list, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        ESP_LOGI(TAG, "Active endpoint response: status(%d) and endpoint count(%d)", zdo_status, ep_count);
        for (int i = 0; i < ep_count; i++) {
            ESP_LOGI(TAG, "Endpoint ID List: %d", ep_id_list[i]);
        }
    }
}

static void simple_desc_cb(esp_zb_zdp_status_t zdo_status, esp_zb_af_simple_desc_1_1_t *simple_desc, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        ESP_LOGI(TAG, "Simple desc response: status(%d), device_id(%d), app_version(%d), profile_id(0x%x), endpoint_ID(%d)", zdo_status,
                 simple_desc->app_device_id, simple_desc->app_device_version, simple_desc->app_profile_id, simple_desc->endpoint);

        for (int i = 0; i < (simple_desc->app_input_cluster_count + simple_desc->app_output_cluster_count); i++) {
            ESP_LOGI(TAG, "Cluster ID list: 0x%x", *(simple_desc->app_cluster_list + i));
        }
    }
}

static void user_find_cb(esp_zb_zdp_status_t zdo_status, uint16_t addr, uint8_t endpoint, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        ESP_LOGI(TAG, "Match desc response: status(%d), address(0x%x), endpoint(%d)", zdo_status, addr, endpoint);
        /* save into remote device record structure for future use */
        on_off_light.endpoint = endpoint;
        on_off_light.short_addr = addr;
        /* find the active endpoint */
        esp_zb_zdo_active_ep_req_param_t active_ep_req;
        active_ep_req.addr_of_interest = on_off_light.short_addr;
        esp_zb_zdo_active_ep_req(&active_ep_req, ep_cb, NULL);
        /* get the node simple descriptor */
        esp_zb_zdo_simple_desc_req_param_t simple_desc_req;
        simple_desc_req.addr_of_interest = addr;
        simple_desc_req.endpoint = endpoint;
        esp_zb_zdo_simple_desc_req(&simple_desc_req, simple_desc_cb, NULL);
        /* get the light ieee address */
        esp_zb_zdo_ieee_addr_req_param_t ieee_req;
        ieee_req.addr_of_interest = on_off_light.short_addr;
        ieee_req.dst_nwk_addr = on_off_light.short_addr;
        ieee_req.request_type = 0;
        ieee_req.start_index = 0;
        esp_zb_zdo_ieee_addr_req(&ieee_req, ieee_cb, NULL);
        esp_zb_zcl_read_attr_cmd_t read_req;
        uint16_t attributes[] = {ESP_ZB_ZCL_ATTR_ON_OFF_ON_OFF_ID};
        read_req.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
        read_req.attr_number = sizeof(attributes) / sizeof(uint16_t);
        read_req.attr_field = attributes;
        read_req.clusterID = ESP_ZB_ZCL_CLUSTER_ID_ON_OFF;
        read_req.zcl_basic_cmd.dst_endpoint = on_off_light.endpoint;
        read_req.zcl_basic_cmd.src_endpoint = HA_ONOFF_SWITCH_ENDPOINT;
        read_req.zcl_basic_cmd.dst_addr_u.addr_short = on_off_light.short_addr;
        esp_zb_zcl_read_attr_cmd_req(&read_req);
    }
}

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p       = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    esp_zb_zdo_signal_leave_params_t *leave_params = NULL;
    switch (sig_type) {
    case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT:
    case ESP_ZB_BDB_SIGNAL_STEERING:
        if (err_status != ESP_OK) {
            ESP_LOGW(TAG, "Stack %s failure with %s status, steering",esp_zb_zdo_signal_to_string(sig_type), esp_err_to_name(err_status));
            esp_zb_scheduler_alarm((esp_zb_callback_t)bdb_start_top_level_commissioning_cb, ESP_ZB_BDB_MODE_NETWORK_STEERING, 1000);
        } else {
            /* device auto start successfully and on a formed network */
            ESP_LOGI(TAG, "Deferred driver initialization %s", deferred_driver_init() ? "failed" : "successful");
            esp_zb_ieee_addr_t extended_pan_id;
            esp_zb_get_extended_pan_id(extended_pan_id);
            ESP_LOGI(TAG, "Joined network successfully (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, Channel:%d, Short Address: 0x%04hx)",
                     extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4],
                     extended_pan_id[3], extended_pan_id[2], extended_pan_id[1], extended_pan_id[0],
                     esp_zb_get_pan_id(), esp_zb_get_current_channel(), esp_zb_get_short_address());
            esp_zb_zdo_match_desc_req_param_t  find_req;
            find_req.addr_of_interest = 0x0000;
            find_req.dst_nwk_addr = 0x0000;
            /* find the match on-off light device */
            esp_zb_zdo_find_on_off_light(&find_req, user_find_cb, NULL);
        }
        break;
    case ESP_ZB_ZDO_SIGNAL_LEAVE:
        leave_params = (esp_zb_zdo_signal_leave_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        if (leave_params->leave_type == ESP_ZB_NWK_LEAVE_TYPE_RESET) {
            ESP_LOGI(TAG, "Reset device");
        }
        break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type,
                 esp_err_to_name(err_status));
        break;
    }
}


static esp_err_t zb_attribute_reporting_handler(const esp_zb_zcl_report_attr_message_t *message)
{
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->status);
    ESP_LOGI(TAG, "Received report from address(0x%x) src endpoint(%d) to dst endpoint(%d) cluster(0x%x)", message->src_address.u.short_addr,
             message->src_endpoint, message->dst_endpoint, message->cluster);
    ESP_LOGI(TAG, "Received report information: attribute(0x%x), type(0x%x), value(%d)\n", message->attribute.id, message->attribute.data.type,
             message->attribute.data.value ? *(uint8_t *)message->attribute.data.value : 0);
    return ESP_OK;
}

static esp_err_t zb_read_attr_resp_handler(const esp_zb_zcl_cmd_read_attr_resp_message_t *message)
{
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);

    esp_zb_zcl_read_attr_resp_variable_t *variable = message->variables;
    while (variable) {
        ESP_LOGI(TAG, "Read attribute response: status(%d), cluster(0x%x), attribute(0x%x), type(0x%x), value(%d)", variable->status,
                 message->info.cluster, variable->attribute.id, variable->attribute.data.type,
                 variable->attribute.data.value ? *(uint8_t *)variable->attribute.data.value : 0);
        variable = variable->next;
    }

    return ESP_OK;
}

static esp_err_t zb_configure_report_resp_handler(const esp_zb_zcl_cmd_config_report_resp_message_t *message)
{
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);

    esp_zb_zcl_config_report_resp_variable_t *variable = message->variables;
    while (variable) {
        ESP_LOGI(TAG, "Configure report response: status(%d), cluster(0x%x), attribute(0x%x)", message->info.status, message->info.cluster,
                 variable->attribute_id);
        variable = variable->next;
    }

    return ESP_OK;
}

static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
{
    esp_err_t ret = ESP_OK;
    switch (callback_id) {
    case ESP_ZB_CORE_REPORT_ATTR_CB_ID:
        ret = zb_attribute_reporting_handler((esp_zb_zcl_report_attr_message_t *)message);
        break;
    case ESP_ZB_CORE_CMD_READ_ATTR_RESP_CB_ID:
        ret = zb_read_attr_resp_handler((esp_zb_zcl_cmd_read_attr_resp_message_t *)message);
        break;
    case ESP_ZB_CORE_CMD_REPORT_CONFIG_RESP_CB_ID:
        ret = zb_configure_report_resp_handler((esp_zb_zcl_cmd_config_report_resp_message_t *)message);
        break;
    default:
        ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
        break;
    }
    return ret;
}

static void esp_zb_task(void *pvParameters)
{
    /* initialize Zigbee stack */
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZED_CONFIG();
    esp_zb_init(&zb_nwk_cfg);
    uint8_t test_attr;
    test_attr = 0;
    /* basic cluster create with fully customized */
    esp_zb_attribute_list_t *esp_zb_basic_cluster = esp_zb_zcl_attr_list_create(ESP_ZB_ZCL_CLUSTER_ID_BASIC);
    esp_zb_basic_cluster_add_attr(esp_zb_basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_ZCL_VERSION_ID, &test_attr);
    esp_zb_basic_cluster_add_attr(esp_zb_basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_POWER_SOURCE_ID, &test_attr);
    esp_zb_cluster_update_attr(esp_zb_basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_ZCL_VERSION_ID, &test_attr);
    /* identify cluster create with fully customized */
    esp_zb_attribute_list_t *esp_zb_identify_cluster = esp_zb_zcl_attr_list_create(ESP_ZB_ZCL_CLUSTER_ID_IDENTIFY);
    esp_zb_identify_cluster_add_attr(esp_zb_identify_cluster, ESP_ZB_ZCL_ATTR_IDENTIFY_IDENTIFY_TIME_ID, &test_attr);
    /* create client role of the cluster */
    esp_zb_attribute_list_t *esp_zb_on_off_client_cluster = esp_zb_zcl_attr_list_create(ESP_ZB_ZCL_CLUSTER_ID_ON_OFF);
    esp_zb_attribute_list_t *esp_zb_identify_client_cluster = esp_zb_zcl_attr_list_create(ESP_ZB_ZCL_CLUSTER_ID_IDENTIFY);
    /* create cluster lists for this endpoint */
    esp_zb_cluster_list_t *esp_zb_cluster_list = esp_zb_zcl_cluster_list_create();
    esp_zb_cluster_list_add_basic_cluster(esp_zb_cluster_list, esp_zb_basic_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_identify_cluster(esp_zb_cluster_list, esp_zb_identify_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_on_off_cluster(esp_zb_cluster_list, esp_zb_on_off_client_cluster, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);
    esp_zb_cluster_list_add_identify_cluster(esp_zb_cluster_list, esp_zb_identify_client_cluster, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);

    esp_zb_ep_list_t *esp_zb_ep_list = esp_zb_ep_list_create();
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = HA_ONOFF_SWITCH_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_ON_OFF_SWITCH_DEVICE_ID,
        .app_device_version = 0
    };
    esp_zb_ep_list_add_ep(esp_zb_ep_list, esp_zb_cluster_list, endpoint_config);
    esp_zb_device_register(esp_zb_ep_list);
    esp_zb_core_action_handler_register(zb_action_handler);
    esp_zb_set_primary_network_channel_set(ESP_ZB_PRIMARY_CHANNEL_MASK);
    esp_zb_set_secondary_network_channel_set(ESP_ZB_SECONDARY_CHANNEL_MASK);
    ESP_ERROR_CHECK(esp_zb_start(true));
    esp_zb_main_loop_iteration();
}

void app_main(void)
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
