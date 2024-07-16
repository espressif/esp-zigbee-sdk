/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee HA_on_off_switch Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include "esp_check.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_timer.h"
#include "esp_zigbee_cluster.h"
#include "nvs_flash.h"
#include "esp_ota_client.h"

static const char *TAG = "ESP_OTA_CLIENT";

static const esp_partition_t *s_ota_partition = NULL;
static esp_ota_handle_t s_ota_handle = 0;

#define OTA_UPGRADE_QUERY_INTERVAL (1 * 60) // 1 minutes

static switch_func_pair_t button_func_pair[] = {{GPIO_INPUT_IO_TOGGLE_SWITCH, SWITCH_ON_CONTROL}};

static void zb_zdo_match_desc_handler(esp_zb_zdp_status_t zdo_status, uint16_t addr, uint8_t endpoint, void *user_ctx)
{
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        esp_zb_ota_upgrade_client_query_interval_set(ESP_OTA_CLIENT_ENDPOINT, OTA_UPGRADE_QUERY_INTERVAL);
        esp_zb_ota_upgrade_client_query_image_req(addr, endpoint);
        ESP_LOGI(TAG, "Query OTA upgrade from server endpoint: %d after %d seconds", endpoint, OTA_UPGRADE_QUERY_INTERVAL);
    } else {
        ESP_LOGW(TAG, "No OTA Server found");
    }
}

static void zb_buttons_handler(switch_func_pair_t *button_func_pair)
{
    assert(button_func_pair);
    esp_zb_zdo_match_desc_req_param_t req;
    uint16_t cluster_list[] = {ESP_ZB_ZCL_CLUSTER_ID_OTA_UPGRADE};

    /* Match the OTA server of coordinator */
    req.addr_of_interest = 0x0000;
    req.dst_nwk_addr = 0x0000;
    req.num_in_clusters = 1;
    req.num_out_clusters = 0;
    req.profile_id = ESP_ZB_AF_HA_PROFILE_ID;
    req.cluster_list = cluster_list;
    esp_zb_lock_acquire(portMAX_DELAY);
    if (esp_zb_bdb_dev_joined()) {
        esp_zb_zdo_match_cluster(&req, zb_zdo_match_desc_handler, NULL);
    }
    esp_zb_lock_release();
}

static esp_err_t deferred_driver_init(void)
{
    ESP_RETURN_ON_FALSE(switch_driver_init(button_func_pair, PAIR_SIZE(button_func_pair), zb_buttons_handler), ESP_FAIL, TAG,
                        "Failed to initialize switch driver");
    return ESP_OK;
}

static void bdb_start_top_level_commissioning_cb(uint8_t mode_mask)
{
    ESP_RETURN_ON_FALSE(esp_zb_bdb_start_top_level_commissioning(mode_mask) == ESP_OK, , TAG, "Failed to start Zigbee commissioning");
}

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p       = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    switch (sig_type) {
    case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Initialize Zigbee stack");
        esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_INITIALIZATION);
        break;
    case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Deferred driver initialization %s", deferred_driver_init() ? "failed" : "successful");
            ESP_LOGI(TAG, "Device started up in %s factory-reset mode", esp_zb_bdb_is_factory_new() ? "" : "non");
            if (esp_zb_bdb_is_factory_new()) {
                ESP_LOGI(TAG, "Start network steering");
                esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_STEERING);
            } else {
                ESP_LOGI(TAG, "Device rebooted");
            }
        } else {
            ESP_LOGE(TAG, "Failed to initialize Zigbee stack (status: %s)", esp_err_to_name(err_status));
        }
        break;
    case ESP_ZB_BDB_SIGNAL_STEERING:
        if (err_status == ESP_OK) {
            esp_zb_ieee_addr_t extended_pan_id;
            esp_zb_get_extended_pan_id(extended_pan_id);
            ESP_LOGI(TAG,
                     "Joined network successfully (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, Channel:%d, Short "
                     "Address: 0x%04hx)",
                     extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4], extended_pan_id[3], extended_pan_id[2],
                     extended_pan_id[1], extended_pan_id[0], esp_zb_get_pan_id(), esp_zb_get_current_channel(), esp_zb_get_short_address());
        } else {
            ESP_LOGI(TAG, "Network steering was not successful (status: %s)", esp_err_to_name(err_status));
            esp_zb_scheduler_alarm((esp_zb_callback_t)bdb_start_top_level_commissioning_cb, ESP_ZB_BDB_MODE_NETWORK_STEERING, 5000);
        }
        break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type,
                 esp_err_to_name(err_status));
        break;
    }
}

static esp_err_t zb_ota_upgrade_status_handler(esp_zb_zcl_ota_upgrade_value_message_t message)
{
    static uint32_t total_size = 0;
    static uint32_t offset = 0;
    static int64_t start_time = 0;
    esp_err_t ret = ESP_OK;

    if (message.info.status == ESP_ZB_ZCL_STATUS_SUCCESS) {
        switch (message.upgrade_status) {
        case ESP_ZB_ZCL_OTA_UPGRADE_STATUS_START:
            ESP_LOGI(TAG, "-- OTA upgrade start");
            start_time = esp_timer_get_time();
            s_ota_partition = esp_ota_get_next_update_partition(NULL);
            assert(s_ota_partition);
            ret = esp_ota_begin(s_ota_partition, 0, &s_ota_handle);
            ESP_RETURN_ON_ERROR(ret, TAG, "Failed to begin OTA partition, status: %s", esp_err_to_name(ret));
            break;
        case ESP_ZB_ZCL_OTA_UPGRADE_STATUS_RECEIVE:
            total_size = message.ota_header.image_size;
            offset += message.payload_size;
            ESP_LOGI(TAG, "-- OTA Client receives data: progress [%ld/%ld]", offset, total_size);
            if (message.payload_size && message.payload) {
                ret = esp_ota_write(s_ota_handle, (const void *)message.payload, message.payload_size);
                ESP_RETURN_ON_ERROR(ret, TAG, "Failed to write OTA data to partition, status: %s", esp_err_to_name(ret));
            }
            break;
        case ESP_ZB_ZCL_OTA_UPGRADE_STATUS_APPLY:
            ESP_LOGI(TAG, "-- OTA upgrade apply");
            break;
        case ESP_ZB_ZCL_OTA_UPGRADE_STATUS_CHECK:
            ret = offset == total_size ? ESP_OK : ESP_FAIL;
            ESP_LOGI(TAG, "-- OTA upgrade check status: %s", esp_err_to_name(ret));
            break;
        case ESP_ZB_ZCL_OTA_UPGRADE_STATUS_FINISH:
            ESP_LOGI(TAG, "-- OTA Finish");
            ESP_LOGI(TAG, "-- OTA Information: version: 0x%lx, manufacturer code: 0x%x, image type: 0x%x, total size: %ld bytes, cost time: %lld ms,",
                     message.ota_header.file_version, message.ota_header.manufacturer_code, message.ota_header.image_type,
                     message.ota_header.image_size, (esp_timer_get_time() - start_time) / 1000);
            ret = esp_ota_end(s_ota_handle);
            ESP_RETURN_ON_ERROR(ret, TAG, "Failed to end OTA partition, status: %s", esp_err_to_name(ret));
            ret = esp_ota_set_boot_partition(s_ota_partition);
            ESP_RETURN_ON_ERROR(ret, TAG, "Failed to set OTA boot partition, status: %s", esp_err_to_name(ret));
            ESP_LOGW(TAG, "Prepare to restart system");
            esp_restart();
            break;
        default:
            ESP_LOGI(TAG, "OTA status: %d", message.upgrade_status);
            break;
        }
    }
    return ret;
}

static esp_err_t zb_ota_upgrade_query_image_resp_handler(esp_zb_zcl_ota_upgrade_query_image_resp_message_t message)
{
    esp_err_t ret = ESP_OK;
    if (message.info.status == ESP_ZB_ZCL_STATUS_SUCCESS) {
        ESP_LOGI(TAG, "Queried OTA image from address: 0x%04hx, endpoint: %d", message.server_addr.u.short_addr, message.server_endpoint);
        ESP_LOGI(TAG, "Image version: 0x%lx, manufacturer code: 0x%x, image size: %ld", message.file_version, message.manufacturer_code,
                 message.image_size);
    }
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Approving OTA image upgrade");
    } else {
        ESP_LOGI(TAG, "Rejecting OTA image upgrade, status: %d", ret);
    }
    return ret;
}

static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
{
    esp_err_t ret = ESP_OK;
    switch (callback_id) {
    case ESP_ZB_CORE_OTA_UPGRADE_VALUE_CB_ID:
        ret = zb_ota_upgrade_status_handler(*(esp_zb_zcl_ota_upgrade_value_message_t *)message);
        break;
    case ESP_ZB_CORE_OTA_UPGRADE_QUERY_IMAGE_RESP_CB_ID:
        ret = zb_ota_upgrade_query_image_resp_handler(*(esp_zb_zcl_ota_upgrade_query_image_resp_message_t *)message);
        break;
    default:
        ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
        break;
    }
    return ret;
}

static esp_err_t zb_register_ota_upgrade_client_device(void)
{
    esp_zb_attribute_list_t *basic_cluster = esp_zb_basic_cluster_create(NULL);
    /** Create ota client cluster with attributes.
     *  Manufacturer code, image type and file version should match with configured values for server.
     *  If the client values do not match with configured values then it shall discard the command and
     *  no further processing shall continue.
     */
    esp_zb_ota_cluster_cfg_t ota_cluster_cfg = {
        .ota_upgrade_file_version = OTA_UPGRADE_RUNNING_FILE_VERSION,
        .ota_upgrade_downloaded_file_ver = OTA_UPGRADE_DOWNLOADED_FILE_VERSION,
        .ota_upgrade_manufacturer = OTA_UPGRADE_MANUFACTURER,
        .ota_upgrade_image_type = OTA_UPGRADE_IMAGE_TYPE,
    };
    esp_zb_attribute_list_t *ota_cluster = esp_zb_ota_cluster_create(&ota_cluster_cfg);
    esp_zb_zcl_ota_upgrade_client_variable_t variable_config = {
        .timer_query = ESP_ZB_ZCL_OTA_UPGRADE_QUERY_TIMER_COUNT_DEF,
        .hw_version = OTA_UPGRADE_HW_VERSION,
        .max_data_size = OTA_UPGRADE_MAX_DATA_SIZE,
    };
    uint16_t ota_upgrade_server_addr = 0xffff;
    uint8_t ota_upgrade_server_ep = 0xff;
    esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();
    esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = ESP_OTA_CLIENT_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_TEST_DEVICE_ID,
        .app_device_version = 0,
    };
    /* Added attributes */
    ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, ESP_MANUFACTURER_NAME));
    ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, ESP_MODEL_IDENTIFIER));
    ESP_ERROR_CHECK(esp_zb_ota_cluster_add_attr(ota_cluster, ESP_ZB_ZCL_ATTR_OTA_UPGRADE_CLIENT_DATA_ID, (void *)&variable_config));
    ESP_ERROR_CHECK(esp_zb_ota_cluster_add_attr(ota_cluster, ESP_ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ADDR_ID, (void *)&ota_upgrade_server_addr));
    ESP_ERROR_CHECK(esp_zb_ota_cluster_add_attr(ota_cluster, ESP_ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_ENDPOINT_ID, (void *)&ota_upgrade_server_ep));
    /* Added clusters */
    ESP_ERROR_CHECK(esp_zb_cluster_list_add_basic_cluster(cluster_list, basic_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE));
    ESP_ERROR_CHECK(esp_zb_cluster_list_add_ota_cluster(cluster_list, ota_cluster, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE));
    /* Added endpoints */
    ESP_ERROR_CHECK(esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config));
    /* Register device */
    return esp_zb_device_register(ep_list);
}

static void esp_zb_task(void *pvParameters)
{
    /* Initialize Zigbee stack with Zigbee end-device config */
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZED_CONFIG();
    esp_zb_init(&zb_nwk_cfg);
    esp_zb_core_action_handler_register(zb_action_handler);
    esp_zb_set_primary_network_channel_set(ESP_ZB_PRIMARY_CHANNEL_MASK);
    ESP_ERROR_CHECK(zb_register_ota_upgrade_client_device());
    ESP_ERROR_CHECK(esp_zb_start(false));
    esp_zb_main_loop_iteration();
}

void app_main(void)
{
    ESP_LOGW(TAG, "ESP Zigbee OTA example 1.0 is running");
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
