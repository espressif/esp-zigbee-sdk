/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "esp_check.h"
#include "esp_err.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "switch_driver.h"
#include "alarm_timer.h"

#include "esp_zigbee.h"

#include "data_stream_client.h"
#include "data_consumer.h"

static const char *TAG = "CUSTOMIZED_DATA_CONSUMER";

static void button_event_handler(switch_driver_handle_t handle)
{
    ESP_RETURN_ON_FALSE(handle != SWITCH_INV_HANDLE, , TAG, "Invalid switch handle");
    static bool read_name = true;
    ezb_err_t ret = EZB_ERR_NONE;

    if (read_name) {
        uint16_t attr_field[] = {ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_DEVICE_NAME_ATTR_ID};
        ezb_zcl_read_attr_cmd_t cmd_req = {
            .cmd_ctrl =
                {
                    .dst_addr.addr_mode = EZB_ADDR_MODE_NONE,
                    .src_ep = ESP_ZIGBEE_DATA_CONSUMER_EP_ID,
                    .cluster_id = ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_CLUSTER_ID,
                    .fc.direction = EZB_ZCL_CMD_DIRECTION_TO_SRV,
                },
            .payload.attr_number = sizeof(attr_field) / sizeof(attr_field[0]),
            .payload.attr_field = attr_field,
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = ezb_zcl_read_attr_cmd_req(&cmd_req);
        esp_zigbee_lock_release();
        ESP_EARLY_LOGI(TAG, "Read the name of customized data producer with error(0x%04x)", ret);
        read_name = false;
    } else {
        ezb_zcl_custom_cluster_cmd_t cmd_req = {
            .cmd_ctrl =
                {
                    .dst_addr.addr_mode = EZB_ADDR_MODE_NONE,
                    .src_ep = ESP_ZIGBEE_DATA_CONSUMER_EP_ID,
                    .cluster_id = ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_CLUSTER_ID,
                    .fc.direction = EZB_ZCL_CMD_DIRECTION_TO_SRV,
                },
            .cmd_id = ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_QUERY_DATA_REQ_CMD_ID,
            .data_length = 0,
            .data = NULL,
        };
        esp_zigbee_lock_acquire(portMAX_DELAY);
        ret = esp_zigbee_zcl_customized_data_stream_get_data_cmd_req(&cmd_req);
        esp_zigbee_lock_release();
        ESP_EARLY_LOGI(TAG, "Request data stream from customized data producer with error(0x%04x)", ret);
    }
}

static esp_err_t deferred_driver_init(void)
{
    static bool is_inited = false;

    ESP_RETURN_ON_FALSE(!is_inited, ESP_OK, TAG, "Deferred driver already initialized");

    switch_driver_config_t config = {
        .gpio_num = CONFIG_GPIO_BOOT_ON_DEVKIT,
        .event_cb = button_event_handler,
    };
    switch_driver_handle_t handle = switch_driver_init(&config);

    is_inited = handle == SWITCH_INV_HANDLE ? false : true;

    return is_inited ? ESP_OK : ESP_FAIL;
}

static void zdo_bind_customized_data_producer_device_result(const ezb_zdp_bind_req_result_t *result, void *user_ctx)
{
    assert(result);
    if (result->error == EZB_ERR_NONE) {
        if (result->rsp && result->rsp->status == EZB_ZDP_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "Bound customized data producer successfully");
        } else {
            ESP_LOGE(TAG, "Failed to bind customized data producer with status (0x%02x)", result->rsp->status);
        }
    } else {
        ESP_LOGE(TAG, "Failed to bind customized data producer with error (0x%04x)", result->error);
    }
}

static ezb_err_t zdo_bind_customized_data_producer_device(uint16_t dst_short_addr, uint8_t dst_ep)
{
    ezb_err_t ret = EZB_ERR_NONE;
    ezb_zdo_bind_req_t bind_req = {
        .dst_nwk_addr = ezb_get_short_address(),
        .field =
            {
                .src_ep = ESP_ZIGBEE_DATA_CONSUMER_EP_ID,
                .dst_addr_mode = EZB_ADDR_MODE_EXT,
                .dst_ep = dst_ep,
            },
        .cb = zdo_bind_customized_data_producer_device_result,
        .user_ctx = NULL,
    };
    ezb_get_extended_address(&bind_req.field.src_addr);

    ESP_RETURN_ON_ERROR(ezb_address_extended_by_short(dst_short_addr, &bind_req.field.dst_addr.extended_addr), TAG,
                        "Failed to get extended address for destination device(0x%04hx)", dst_short_addr);
    bind_req.field.cluster_id = ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_CLUSTER_ID;
    ret = ezb_zdo_bind_req(&bind_req);
    if (ret == EZB_ERR_NONE) {
        ESP_LOGI(TAG, "Attempt to bind customized data producer (short address: 0x%04hx)", dst_short_addr);
    } else {
        ESP_LOGE(TAG, "Failed to bind customized data producer (short address: 0x%04hx) with error(0x%04x)", dst_short_addr, ret);
    }
    return ret;
}

static void zdo_find_customized_data_producer_device_result(const ezb_zdo_match_desc_req_result_t *result, void *user_ctx)
{
    assert(result);
    if (result->error == EZB_ERR_NONE) {
        if (result->rsp && result->rsp->status == EZB_ZDP_STATUS_SUCCESS && result->rsp->match_length > 0 &&
            result->rsp->match_list) {
            zdo_bind_customized_data_producer_device(result->rsp->nwk_addr_of_interest, result->rsp->match_list[0]);
        }
    } else {
        ESP_LOGE(TAG, "Failed to find customized data producer in the network with error(0x%04x)", result->error);
    }
}

static ezb_err_t zdo_find_customized_data_producer_device(void)
{
    ezb_err_t ret = EZB_ERR_NONE;
    uint16_t cluster_list[] = {ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_CLUSTER_ID};

    ezb_zdo_match_desc_req_t req = {
        .dst_nwk_addr = 0xFFFD,
        .field =
            {
                .nwk_addr_of_interest = 0xFFFD,
                .profile_id = EZB_AF_HA_PROFILE_ID,
                .num_in_clusters = sizeof(cluster_list) / sizeof(cluster_list[0]),
                .num_out_clusters = 0,
                .cluster_list = cluster_list,
            },
        .cb = zdo_find_customized_data_producer_device_result,
        .user_ctx = NULL,
    };
    ret = ezb_zdo_match_desc_req(&req);
    if (ret == EZB_ERR_NONE) {
        ESP_LOGI(TAG, "Attempt to find customized data producer");
    } else {
        ESP_LOGE(TAG, "Failed to find customized data producer with error(0x%04x)", ret);
    }
    return ret;
}

static void esp_zigbee_alarm_bdb_commissioning(alarm_timer_arg_t arg)
{
    esp_zigbee_lock_acquire(portMAX_DELAY);
    (void)ezb_bdb_start_top_level_commissioning(arg);
    esp_zigbee_lock_release();
}

static bool esp_zigbee_app_signal_handler(const ezb_app_signal_t *app_signal)
{
    ezb_app_signal_type_t signal_type = ezb_app_signal_get_type(app_signal);

    switch (signal_type) {
    case EZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Initialize Zigbee stack");
        ezb_bdb_start_top_level_commissioning(EZB_BDB_MODE_INITIALIZATION);
        break;
    case EZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case EZB_BDB_SIGNAL_DEVICE_REBOOT: {
        ezb_bdb_comm_status_t status = *((ezb_bdb_comm_status_t *)ezb_app_signal_get_params(app_signal));
        if (status == EZB_BDB_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "Deferred driver initialization %s", deferred_driver_init() ? "failed" : "successful");
            ESP_LOGI(TAG, "Device started up in%s factory-reset mode", ezb_bdb_is_factory_new() ? "" : " non");
            if (ezb_bdb_is_factory_new()) {
                ezb_bdb_start_top_level_commissioning(EZB_BDB_MODE_NETWORK_STEERING);
            } else {
                ESP_LOGI(TAG, "Device reboot");
            }
        } else {
            ESP_LOGW(TAG, "%s failed with status(0x%02x), retry again", ezb_app_signal_to_string(signal_type), status);
            alarm_timer_schedule(esp_zigbee_alarm_bdb_commissioning, EZB_BDB_MODE_INITIALIZATION, 1000);
        }
    } break;
    case EZB_BDB_SIGNAL_STEERING: {
        ezb_bdb_comm_status_t status = *((ezb_bdb_comm_status_t *)ezb_app_signal_get_params(app_signal));
        if (status == EZB_BDB_STATUS_SUCCESS) {
            ezb_extpanid_t extended_pan_id;
            ezb_nwk_get_extended_panid(&extended_pan_id);
            ESP_LOGI(TAG, "Joined network successfully: PAN ID(0x%04hx, EXT: 0x%llx), Channel(%d), Short Address(0x%04hx)",
                     ezb_nwk_get_panid(), extended_pan_id.u64, ezb_nwk_get_current_channel(), ezb_nwk_get_short_address());
            zdo_find_customized_data_producer_device();
        } else {
            ESP_LOGW(TAG, "Failed to join network with status(0x%02x)", status);
            alarm_timer_schedule(esp_zigbee_alarm_bdb_commissioning, EZB_BDB_MODE_NETWORK_STEERING, 1000);
        }
    } break;
    case EZB_ZDO_SIGNAL_LEAVE: {
        const ezb_zdo_signal_leave_params_t *leave_params = ezb_app_signal_get_params(app_signal);
        ESP_LOGI(TAG, "Left network successfully with type(0x%02x)", leave_params->leave_type);
    } break;
    case EZB_NWK_SIGNAL_PERMIT_JOIN_STATUS: {
        uint8_t duration = *(uint8_t *)ezb_app_signal_get_params(app_signal);
        if (duration) {
            ESP_LOGI(TAG, "Network(0x%04hx) is open for %d seconds", ezb_nwk_get_panid(), duration);
        } else {
            ESP_LOGW(TAG, "Network(0x%04hx) closed, devices joining not allowed.", ezb_nwk_get_panid());
        }
    } break;
    default:
        ESP_LOGI(TAG, "Zigbee APP Signal: %s(type: 0x%02x)", ezb_app_signal_to_string(signal_type), signal_type);
        break;
    }
    return true;
}

static void zcl_core_cmd_read_attr_rsp_handler(ezb_zcl_cmd_read_attr_rsp_message_t *message)
{
    ESP_RETURN_ON_FALSE(message, , TAG, "message is empty");
    ESP_RETURN_ON_FALSE(message->info.dst_ep == ESP_ZIGBEE_DATA_CONSUMER_EP_ID, , TAG, "Unsupported destination endpoint");
    ESP_RETURN_ON_FALSE(message->info.cluster_id == ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_CLUSTER_ID, , TAG,
                        "Unsupported cluster ID");
    ESP_LOGI(TAG, "Received ZCL Read Attribute Response with status(0x%02x)", message->info.status);
    for (ezb_zcl_read_attr_rsp_variable_t *var = message->in.variables; var != NULL; var = var->next) {
        if (var->status == EZB_ZCL_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "Attribute(0x%04x), type(0x%x)", var->attr_id, var->attr_type);
            if (var->attr_id == ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_DEVICE_NAME_ATTR_ID) {
                ESP_LOGI(TAG, "Data producer name: %.*s", *(uint8_t *)var->attr_value, (char *)(var->attr_value + 1));
            }
        }
    }
}

static void esp_zigbee_zcl_core_action_handler(ezb_zcl_core_action_callback_id_t callback_id, void *message)
{
    switch (callback_id) {
    case EZB_ZCL_CORE_READ_ATTR_RSP_CB_ID:
        zcl_core_cmd_read_attr_rsp_handler(message);
        break;
    case EZB_ZCL_CORE_DEFAULT_RSP_CB_ID: {
        ezb_zcl_cmd_default_rsp_message_t *default_rsp = (ezb_zcl_cmd_default_rsp_message_t *)message;
        ESP_LOGI(TAG, "Received ZCL Default Response with status(0x%02x)", default_rsp->in.status_code);
    } break;
    default:
        ESP_LOGW(TAG, "ZCL Core Action: ID(0x%04lx)", callback_id);
        break;
    }
}

static void customized_data_consumer_handler(const uint8_t *data, uint16_t data_length)
{
    ESP_LOGI(TAG, "Received data from customized data producer with length(0x%04x)", data_length);
    ESP_LOG_BUFFER_HEX(TAG, data, data_length);
}

esp_err_t esp_zigbee_create_customized_data_consumer_device(void)
{
    ezb_af_device_desc_t dev_desc = ezb_af_create_device_desc();
    ezb_af_ep_desc_t ep_desc = NULL;
    ezb_zcl_cluster_desc_t basic_desc = NULL;
    ezb_zcl_cluster_desc_t identify_desc = NULL;
    ezb_zcl_cluster_desc_t custom_desc = NULL;

    ezb_zcl_basic_cluster_server_config_t basic_cfg = {
        .zcl_version = EZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE,
        .power_source = EZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE,
    };
    basic_desc = ezb_zcl_basic_create_cluster_desc(&basic_cfg, EZB_ZCL_CLUSTER_SERVER);
    ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)ESP_MANUFACTURER_NAME);
    ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)ESP_MODEL_IDENTIFIER);

    ezb_zcl_identify_cluster_server_config_t identify_cfg = {
        .identify_time = EZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE,
    };
    identify_desc = ezb_zcl_identify_create_cluster_desc(&identify_cfg, EZB_ZCL_CLUSTER_SERVER);

    ezb_zcl_custom_cluster_config_t custom_cfg = {
        .cluster_id = ESP_ZIGBEE_CUSTOMIZED_DATA_STREAM_CLUSTER_ID,
        .init_func = esp_zigbee_zcl_customized_data_stream_client_init,
        .deinit_func = esp_zigbee_zcl_customized_data_stream_client_deinit,
    };
    custom_desc = ezb_zcl_custom_create_cluster_desc(&custom_cfg, EZB_ZCL_CLUSTER_CLIENT);

    ezb_af_ep_config_t ep_config = {
        .ep_id = ESP_ZIGBEE_DATA_CONSUMER_EP_ID,
        .app_profile_id = EZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZIGBEE_CUSTOMIZED_DATA_CONSUMER_DEVICE_ID,
        .app_device_version = 0,
    };
    ep_desc = ezb_af_create_endpoint_desc(&ep_config);

    ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, basic_desc));
    ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, identify_desc));
    ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, custom_desc));

    ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));

    ESP_ERROR_CHECK(ezb_af_device_desc_register(dev_desc));

    esp_zigbee_zcl_customized_data_stream_client_set_data_customer(customized_data_consumer_handler);

    ezb_zcl_core_action_handler_register(esp_zigbee_zcl_core_action_handler);

    return ESP_OK;
}

esp_err_t esp_zigbee_setup_commissioning(void)
{
    ezb_aps_secur_enable_distributed_security(false);
    ESP_ERROR_CHECK(ezb_bdb_set_primary_channel_set(ESP_ZIGBEE_PRIMARY_CHANNEL_MASK));
    ESP_ERROR_CHECK(ezb_bdb_set_secondary_channel_set(ESP_ZIGBEE_SECONDARY_CHANNEL_MASK));
    ESP_ERROR_CHECK(ezb_app_signal_add_handler(esp_zigbee_app_signal_handler));

    return ESP_OK;
}

static void esp_zigbee_stack_main_task(void *pvParameters)
{
    esp_zigbee_config_t config = ESP_ZIGBEE_DEFAULT_CONFIG();

    ESP_ERROR_CHECK(esp_zigbee_init(&config));

    ESP_ERROR_CHECK(esp_zigbee_setup_commissioning());

    ESP_ERROR_CHECK(esp_zigbee_create_customized_data_consumer_device());

    ESP_ERROR_CHECK(esp_zigbee_start(false));

    esp_zigbee_launch_mainloop();

    esp_zigbee_deinit();

    vTaskDelete(NULL);
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(nvs_flash_init_partition(ESP_ZIGBEE_STORAGE_PARTITION_NAME));
    ESP_LOGI(TAG, "Start ESP Zigbee Stack");
    xTaskCreate(esp_zigbee_stack_main_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
