/*
 * SPDX-FileCopyrightText: 2021-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "esp_check.h"
#include "esp_err.h"
#include "esp_log.h"
#include "nvs_flash.h"
#if CONFIG_ZB_DELTA_OTA
#include "esp_delta_ota_ops.h"
#else
#include "esp_ota_ops.h"
#endif

#include "alarm_timer.h"

#include "esp_zigbee.h"
#include "ezbee/zha.h"

#include "ota_file_parser.h"
#include "ota_client.h"

static const char *TAG = "OTA_CLIENT";

static const esp_partition_t    *s_ota_partition   = NULL;
static esp_zb_ota_file_parser_t *s_ota_file_parser = NULL;
static esp_ota_handle_t          s_ota_handle      = 0;

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
            ESP_LOGI(TAG, "Device started up in%s factory-reset mode", ezb_bdb_is_factory_new() ? "" : " non");
            if (ezb_bdb_is_factory_new()) {
                ezb_bdb_start_top_level_commissioning(EZB_BDB_MODE_NETWORK_STEERING);
            } else {
                ESP_LOGI(TAG, "Device reboot");
            }
        } else {
            ESP_LOGW(TAG, "%s failed with status(0x%02x), please retry", ezb_app_signal_to_string(signal_type), status);
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
        } else {
            ESP_LOGW(TAG, "Failed to join network with status(0x%02x)", status);
            alarm_timer_schedule(esp_zigbee_alarm_bdb_commissioning, EZB_BDB_MODE_NETWORK_STEERING, 1000);
        }
    } break;
    case EZB_ZDO_SIGNAL_DEVICE_ANNCE: {
        const ezb_zdo_signal_device_annce_params_t *dev_annce_params = ezb_app_signal_get_params(app_signal);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->short_addr);
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

static void zcl_ota_upgrade_client_progress_handler(ezb_zcl_ota_upgrade_client_progress_message_t *message)
{
    esp_err_t ret = ESP_OK;
    ESP_LOGI(TAG, "-- OTA Upgrade Client Progress");

    switch (message->in.progress) {
    case EZB_ZCL_OTA_UPGRADE_PROGRESS_START:
        ESP_LOGI(TAG, "OTA Start: manuf_code=0x%04x, image_type=0x%04x, file_version=0x%08lx, image_size=%ld",
                 message->in.start.manuf_code, message->in.start.image_type, message->in.start.file_version,
                 message->in.start.image_size);

        s_ota_partition = esp_ota_get_next_update_partition(NULL);
        ESP_GOTO_ON_FALSE(s_ota_partition, ESP_ERR_NOT_FOUND, exit, TAG, "No OTA partition found");
        s_ota_file_parser = esp_zb_create_ota_file_parser(message->in.start.image_size);
        ESP_GOTO_ON_FALSE(s_ota_file_parser, ESP_ERR_NOT_FOUND, exit, TAG, "Failed to create OTA file parser");
#if CONFIG_ZB_DELTA_OTA
            ret = esp_delta_ota_begin(s_ota_partition, 0, &s_ota_handle);
#else
            ret = esp_ota_begin(s_ota_partition, 0, &s_ota_handle);
#endif

        ESP_GOTO_ON_FALSE(s_ota_handle, ESP_ERR_NOT_FOUND, exit, TAG, "Failed to start OTA");
        break;
    case EZB_ZCL_OTA_UPGRADE_PROGRESS_RECEIVING:
        ESP_LOGI(TAG, "OTA Receiving Block: file_offset=%ld, block_size=%d", message->in.receiving.file_offset,
                 message->in.receiving.block_size);
        esp_zb_ota_file_parser_setup(s_ota_file_parser, message->in.receiving.block_size, message->in.receiving.block);
        do {
            ret = esp_zb_ota_file_parser_process(s_ota_file_parser);
            ESP_LOGW(TAG, "In progress: [%ld / %ld]", message->in.receiving.file_offset + message->in.receiving.block_size, s_ota_file_parser->total_image_size);
            if (esp_zb_ota_file_parser_is_element_value(s_ota_file_parser)) {
                switch (s_ota_file_parser->element.type) {
                case UPGRADE_IMAGE:
                    ESP_GOTO_ON_FALSE(s_ota_file_parser->element.total <= s_ota_partition->size, ESP_ERR_INVALID_SIZE, exit,
                                      TAG, "OTA image size exceeds partition size");
#if CONFIG_ZB_DELTA_OTA
                    ESP_GOTO_ON_ERROR(esp_delta_ota_write(s_ota_handle, s_ota_file_parser->element.val, s_ota_file_parser->element.length), exit,
                                      TAG, "Failed to write OTA image");
#else
                    ESP_GOTO_ON_ERROR(esp_ota_write(s_ota_handle, s_ota_file_parser->element.val, s_ota_file_parser->element.length), exit,
                                      TAG, "Failed to write OTA image");
#endif
                    break;
                default:
                    ESP_LOG_BUFFER_HEX_LEVEL(TAG, s_ota_file_parser->element.val, s_ota_file_parser->element.length,
                                             ESP_LOG_WARN);
                    break;
                }
            }
        } while (ret == EZB_ERR_NOT_FINISHED);
        ret = ESP_OK;
        break;
    case EZB_ZCL_OTA_UPGRADE_PROGRESS_CHECK:
        ESP_LOGI(TAG, "OTA Check: manuf_code=0x%04x, image_type=0x%04x, file_version=0x%08lx", message->in.check.manuf_code,
                 message->in.check.image_type, message->in.check.file_version);
        ret = esp_zb_ota_file_parser_check(s_ota_file_parser);
        break;
    case EZB_ZCL_OTA_UPGRADE_PROGRESS_APPLY:
        ESP_LOGI(TAG, "OTA Apply: manuf_code=0x%04x, image_type=0x%04x, file_version=0x%08lx", message->in.apply.manuf_code,
                 message->in.apply.image_type, message->in.apply.file_version);
#if CONFIG_ZB_DELTA_OTA
        ret = esp_delta_ota_end(s_ota_handle);
#else
        ret = esp_ota_end(s_ota_handle);
#endif
        ESP_GOTO_ON_ERROR(ret, exit, TAG, "Failed to end OTA: error: %s", esp_err_to_name(ret));
        ret = esp_ota_set_boot_partition(s_ota_partition);
        ESP_GOTO_ON_ERROR(ret, exit, TAG, "Failed to set OTA boot partition, error: %s", esp_err_to_name(ret));
        break;
    case EZB_ZCL_OTA_UPGRADE_PROGRESS_FINISH:
        ESP_LOGI(TAG, "OTA Finish: count_down_delay=%ld seconds", message->in.finish.count_down_delay);
        esp_restart();
        break;
    case EZB_ZCL_OTA_UPGRADE_PROGRESS_ABORT:
        ret = esp_ota_abort(s_ota_handle);
        ESP_LOGW(TAG, "OTA Abort");
        break;
    default:
        ESP_LOGW(TAG, "Unknown OTA progress status: %d", message->in.progress);
        message->out.result = EZB_ZCL_STATUS_SUCCESS;
        break;
    }

exit:
    message->out.result = ret == ESP_OK ? EZB_ZCL_STATUS_SUCCESS : EZB_ZCL_STATUS_ABORT;
}

static void zcl_ota_upgrade_client_query_next_image_rsp_handler(ezb_zcl_ota_upgrade_query_next_image_rsp_message_t *message)
{
    ESP_LOGI(TAG, "-- OTA Upgrade Query Next Image Response");

    if (message->in.image.status == EZB_ZCL_OTA_UPGRADE_STATUS_CODE_SUCCESS) {
        ESP_LOGI(TAG, "New image available:");
        ESP_LOGI(TAG, "  Server address: 0x%016llx", *(uint64_t *)&message->in.image.server_address);
        ESP_LOGI(TAG, "  Endpoint: %d", message->in.image.ep_id);
        ESP_LOGI(TAG, "  Manufacturer code: 0x%04x", message->in.image.manuf_code);
        ESP_LOGI(TAG, "  Image type: 0x%04x", message->in.image.image_type);
        ESP_LOGI(TAG, "  File version: 0x%08lx", message->in.image.file_version);
        ESP_LOGI(TAG, "  Image size: %ld bytes", message->in.image.size);
        message->out.result = EZB_ZCL_STATUS_SUCCESS;
    } else {
        ESP_LOGW(TAG, "No image available, status: 0x%02x", message->in.image.status);
        message->out.result = EZB_ZCL_STATUS_SUCCESS;
    }
}

static void esp_zigbee_zcl_core_action_handler(ezb_zcl_core_action_callback_id_t callback_id, void *message)
{
    switch (callback_id) {
    case EZB_ZCL_CORE_OTA_UPGRADE_CLIENT_PROGRESS_CB_ID:
        zcl_ota_upgrade_client_progress_handler(message);
        break;
    case EZB_ZCL_CORE_OTA_UPGRADE_QUERY_NEXT_IMAGE_RSP_CB_ID:
        zcl_ota_upgrade_client_query_next_image_rsp_handler(message);
        break;
    case EZB_ZCL_CORE_DEFAULT_RSP_CB_ID: {
        ezb_zcl_cmd_default_rsp_message_t *default_rsp = (ezb_zcl_cmd_default_rsp_message_t *)message;
        ESP_LOGI(TAG, "Received ZCL Default Response with status(0x%02x)", default_rsp->in.status_code);
    } break;
    default:
        ESP_LOGW(TAG, "Application Action: 0x%08lx", callback_id);
        break;
    };
}

esp_err_t esp_zigbee_create_zha_on_off_light_with_ota_client_device(void)
{
    ezb_af_ep_config_t ep_config = {
        .ep_id              = ESP_ZIGBEE_OTA_CLIENT_EP_ID,
        .app_profile_id     = EZB_AF_HA_PROFILE_ID,
        .app_device_id      = EZB_ZHA_ON_OFF_LIGHT_DEVICE_ID,
        .app_device_version = 0,
    };

    ezb_af_device_desc_t   dev_desc        = ezb_af_create_device_desc();
    ezb_af_ep_desc_t       ep_desc         = ezb_af_create_endpoint_desc(&ep_config);
    ezb_zcl_cluster_desc_t basic_desc      = EZB_INVALID_ZCL_CLUSTER_DESC;
    ezb_zcl_cluster_desc_t ota_client_desc = EZB_INVALID_ZCL_CLUSTER_DESC;

    ezb_zcl_ota_upgrade_cluster_client_config_t client_default_cfg = {
        .upgrade_server_id    = EZB_ZCL_OTA_UPGRADE_UPGRADE_SERVER_ID_DEFAULT_VALUE,
        .file_offset          = 0,
        .image_upgrade_status = EZB_ZCL_OTA_UPGRADE_IMAGE_UPGRADE_STATUS_DEFAULT_VALUE,
        .manufacturer_id      = ESP_MANUF_CODE,
        .image_type_id        = ESP_IMAGE_TYPE,
    };

    basic_desc = ezb_zcl_basic_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_SERVER);
    ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)ESP_MANUFACTURER_NAME);
    ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)ESP_MODEL_IDENTIFIER);

    ezb_af_endpoint_add_cluster_desc(ep_desc, basic_desc);
    ezb_af_endpoint_add_cluster_desc(ep_desc, ezb_zcl_identify_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_SERVER));

    ota_client_desc = ezb_zcl_ota_upgrade_create_cluster_desc(&client_default_cfg, EZB_ZCL_CLUSTER_CLIENT);
    ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, ota_client_desc));
    ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));
    ESP_ERROR_CHECK(ezb_af_device_desc_register(dev_desc));

    ezb_zcl_ota_upgrade_set_download_block_size(ESP_ZIGBEE_OTA_CLIENT_EP_ID, 223);

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

    ESP_ERROR_CHECK(esp_zigbee_create_zha_on_off_light_with_ota_client_device());

    ESP_ERROR_CHECK(esp_zigbee_start(false));

    esp_zigbee_launch_mainloop();

    esp_zigbee_deinit();

    vTaskDelete(NULL);
}

void app_main(void)
{
    ESP_LOGW(TAG, "ESP Zigbee OTA example (0x%"PRIx32") is running", (uint32_t)ESP_OTA_FILE_VERSION);
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(nvs_flash_init_partition(ESP_ZIGBEE_STORAGE_PARTITION_NAME));
    ESP_LOGI(TAG, "Start ESP Zigbee Stack");
    xTaskCreate(esp_zigbee_stack_main_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
