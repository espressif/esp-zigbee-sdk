/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee customized server Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include "esp_log.h"
#include "esp_ota_server.h"
#include "nvs_flash.h"
#include "esp_check.h"

static const char *TAG = "ESP_OTA_SERVER";

static uint32_t s_ota_image_offset = 0;

static switch_func_pair_t button_func_pair[] = {{GPIO_INPUT_IO_TOGGLE_SWITCH, SWITCH_ON_CONTROL}};

static esp_err_t zb_ota_next_data_handler(esp_zb_ota_zcl_information_t message, uint16_t index, uint8_t size, uint8_t **data);

static void bdb_start_top_level_commissioning_cb(uint8_t mode_mask)
{
    ESP_RETURN_ON_FALSE(esp_zb_bdb_start_top_level_commissioning(mode_mask) == ESP_OK, , TAG, "Failed to start Zigbee commissioning");
}

/**
 * @brief Send OTA image notify request
 * @param[in] notify_on
 *      - true: Adds the OTA image file to the OTA image table and broadcasts it to the network
 *      - false: Only adds the OTA image file to the OTA image table
 */
static esp_err_t zb_ota_upgrade_srv_send_notify_image(bool notify_on)
{
    esp_zb_ota_upgrade_server_notify_req_t req = {
        .endpoint = ESP_OTA_SERVER_ENDPOINT,
        .index = OTA_UPGRADE_INDEX,
        .notify_on = notify_on,
        .ota_upgrade_time = OTA_UPGRADE_TIME,
        .ota_file_header =
            {
                .manufacturer_code = OTA_UPGRADE_MANUFACTURER,
                .image_type = OTA_UPGRADE_IMAGE_TYPE,
                .file_version = OTA_UPGRADE_FILE_VERSION,
                .image_size = ota_file_end - ota_file_start,
            },
        .next_data_cb = zb_ota_next_data_handler,
    };
    return esp_zb_ota_upgrade_server_notify_req(&req);
}

static void zb_buttons_handler(switch_func_pair_t *button_func_pair)
{
    esp_zb_lock_acquire(portMAX_DELAY);
    if (esp_zb_bdb_dev_joined()) {
        zb_ota_upgrade_srv_send_notify_image(true);
        ESP_LOGI(TAG, "Send OTA Server notify image request");
    }
    esp_zb_lock_release();
}

static esp_err_t deferred_driver_init(void)
{
    ESP_RETURN_ON_FALSE(switch_driver_init(button_func_pair, PAIR_SIZE(button_func_pair), zb_buttons_handler), ESP_FAIL, TAG,
                        "Failed to initialize switch driver");
    return ESP_OK;
}

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
   uint32_t *p_sg_p       = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    esp_zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;
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
                ESP_LOGI(TAG, "Start network formation");
                esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_FORMATION);
            } else {
                esp_zb_bdb_open_network(180);
                ESP_LOGI(TAG, "Device rebooted");
            }
        } else {
            ESP_LOGE(TAG, "Failed to initialize Zigbee stack (status: %s)", esp_err_to_name(err_status));
        }
        break;
    case ESP_ZB_BDB_SIGNAL_FORMATION:
        if (err_status == ESP_OK) {
            esp_zb_ieee_addr_t extended_pan_id;
            esp_zb_get_extended_pan_id(extended_pan_id);
            ESP_LOGI(TAG, "Formed network successfully (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, Channel:%d, Short Address: 0x%04hx)",
                     extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4],
                     extended_pan_id[3], extended_pan_id[2], extended_pan_id[1], extended_pan_id[0],
                     esp_zb_get_pan_id(), esp_zb_get_current_channel(), esp_zb_get_short_address());
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_STEERING);
        } else {
            ESP_LOGI(TAG, "Restart network formation (status: %s)", esp_err_to_name(err_status));
            esp_zb_scheduler_alarm((esp_zb_callback_t)bdb_start_top_level_commissioning_cb, ESP_ZB_BDB_MODE_NETWORK_FORMATION, 1000);
        }
        break;

    case ESP_ZB_BDB_SIGNAL_STEERING:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Network steering started");
        }
        break;

    case ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE: {
        dev_annce_params = (esp_zb_zdo_signal_device_annce_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->device_short_addr);
        /* Broadcast Image Notify Request when the OTA server is not in OTA process */
        if (s_ota_image_offset == 0) {
            zb_ota_upgrade_srv_send_notify_image(true);
            ESP_LOGI(TAG, "Notify OTA upgrade");
        }
        break;
    }
    case ESP_ZB_NWK_SIGNAL_PERMIT_JOIN_STATUS:
        if (err_status == ESP_OK) {
            if (*(uint8_t *)esp_zb_app_signal_get_params(p_sg_p)) {
                ESP_LOGI(TAG, "Network(0x%04hx) is open for %d seconds", esp_zb_get_pan_id(), *(uint8_t *)esp_zb_app_signal_get_params(p_sg_p));
            } else {
                ESP_LOGW(TAG, "Network(0x%04hx) closed, devices joining not allowed.", esp_zb_get_pan_id());
            }
        }
        break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type,
                 esp_err_to_name(err_status));
        break;
    }
}

static esp_err_t zb_ota_next_data_handler(esp_zb_ota_zcl_information_t message, uint16_t index, uint8_t size, uint8_t **data)
{
    switch (index) {
    case OTA_UPGRADE_INDEX:
        *data = (uint8_t *)ota_file_start + s_ota_image_offset;
        s_ota_image_offset += size;
        break;
    default:
        ESP_LOGW(TAG, "Failed to locate the OTA image using the index (%d)", index);
        return ESP_FAIL;
        break;
    }
    if (s_ota_image_offset >= (ota_file_end - ota_file_start)) {
        s_ota_image_offset = 0;
    }
    ESP_LOGI(TAG, "-- OTA Server transmits data from 0x%x to 0x%x: progress [%ld/%d]", message.dst_short_addr, message.src_addr.u.short_addr,
             s_ota_image_offset, (ota_file_end - ota_file_start));
    return (*data) ? ESP_OK : ESP_FAIL;
}

static esp_err_t zb_ota_upgrade_server_status_handler(esp_zb_zcl_ota_upgrade_server_status_message_t message)
{
    esp_err_t ret = ESP_OK;
    ESP_RETURN_ON_FALSE(message.info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_FAIL, TAG, "Failed to parse OTA upgrade server status message");
    ESP_LOGI(TAG, "OTA client address: 0x%x", message.zcl_addr.u.short_addr);
    ESP_LOGI(TAG, "OTA version: 0x%lx, image type: 0x%x, server status: %d", message.version, message.image_type, message.server_status);
    if (message.upgrade_time) {
        ESP_LOGI(TAG, "OTA upgrade time: 0x%lx", *message.upgrade_time);
    }
    if(message.server_status == ESP_ZB_ZCL_OTA_UPGRADE_SERVER_ABORTED || message.server_status == ESP_ZB_ZCL_OTA_UPGRADE_SERVER_END) {
        s_ota_image_offset = 0;
    }
    return ret;
}

static esp_err_t zb_ota_upgrade_server_query_image_handler(esp_zb_zcl_ota_upgrade_server_query_image_message_t message)
{
    esp_err_t ret = ESP_OK;
    ESP_RETURN_ON_FALSE(message.info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_FAIL, TAG, "Failed to parse OTA upgrade server query image message");
    ESP_LOGI(TAG, "OTA upgrade server query image");
    ESP_LOGI(TAG, "OTA client address: 0x%x", message.zcl_addr.u.short_addr);
    ESP_LOGI(TAG, "OTA version: 0x%lx, image type: 0x%x, manufacturer code: %x, ", message.version, message.image_type, message.manufacturer_code);
    if (message.table_idx) {
        ESP_LOGI(TAG, "OTA table index: 0x%x", *message.table_idx);
    }
    ESP_RETURN_ON_FALSE((message.image_type == OTA_UPGRADE_IMAGE_TYPE && message.manufacturer_code == OTA_UPGRADE_MANUFACTURER), ESP_ERR_NOT_FOUND,
                        TAG, "OTA query image mismatch");
    s_ota_image_offset = 0;
    return ret;
}

static esp_err_t zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
{
    esp_err_t ret = ESP_OK;
    switch (callback_id) {
    case ESP_ZB_CORE_OTA_UPGRADE_SRV_STATUS_CB_ID:
        ret = zb_ota_upgrade_server_status_handler(*(esp_zb_zcl_ota_upgrade_server_status_message_t *)message);
        break;
    case ESP_ZB_CORE_OTA_UPGRADE_SRV_QUERY_IMAGE_CB_ID:
        ret = zb_ota_upgrade_server_query_image_handler(*(esp_zb_zcl_ota_upgrade_server_query_image_message_t *)message);
        break;
    default:
        ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
        break;
    }
    return ret;
}

static esp_err_t zb_register_ota_upgrade_server_device(void)
{
    esp_zb_attribute_list_t *basic_cluster = esp_zb_basic_cluster_create(NULL);
    esp_zb_attribute_list_t *ota_cluster = esp_zb_zcl_attr_list_create(ESP_ZB_ZCL_CLUSTER_ID_OTA_UPGRADE);
    esp_zb_cluster_list_t *cluster_list = esp_zb_zcl_cluster_list_create();
    esp_zb_ep_list_t *ep_list = esp_zb_ep_list_create();
    esp_zb_zcl_ota_upgrade_server_variable_t variable = {
        .query_jitter = OTA_UPGRADE_QUERY_JITTER,
        .current_time = OTA_UPGRADE_CURRENT_TIME,
        .file_count = OTA_UPGRADE_IMAGE_COUNT,
    };
    esp_zb_endpoint_config_t endpoint_config = {
        .endpoint = ESP_OTA_SERVER_ENDPOINT,
        .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .app_device_id = ESP_ZB_HA_TEST_DEVICE_ID,
        .app_device_version = 0,
    };

    /* Added attributes */
    ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, ESP_MANUFACTURER_NAME));
    ESP_ERROR_CHECK(esp_zb_basic_cluster_add_attr(basic_cluster, ESP_ZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, ESP_MODEL_IDENTIFIER));
    ESP_ERROR_CHECK(esp_zb_ota_cluster_add_attr(ota_cluster, ESP_ZB_ZCL_ATTR_OTA_UPGRADE_SERVER_DATA_ID, (void *)&variable));
    /* Added clusters */
    ESP_ERROR_CHECK(esp_zb_cluster_list_add_basic_cluster(cluster_list, basic_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE));
    ESP_ERROR_CHECK(esp_zb_cluster_list_add_ota_cluster(cluster_list, ota_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE));
    /* Added endpoints */
    ESP_ERROR_CHECK(esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config));
    /* Register device */
    return esp_zb_device_register(ep_list);
}

static void esp_zb_task(void *pvParameters)
{
    /* initialize Zigbee stack */
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZC_CONFIG();
    esp_zb_init(&zb_nwk_cfg);

    esp_zb_set_primary_network_channel_set(ESP_ZB_PRIMARY_CHANNEL_MASK);
    esp_zb_core_action_handler_register(zb_action_handler);
    ESP_ERROR_CHECK(zb_register_ota_upgrade_server_device());
    ESP_ERROR_CHECK(esp_zb_start(false));
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