/*
 * SPDX-FileCopyrightText: 2021-2026 Espressif Systems (Shanghai) CO LTD
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
#include "ezbee/zha.h"

#include "ota_server.h"

static const char *TAG = "OTA_SERVER";

extern const uint8_t ota_file_start[] asm("_binary_131B_0001_10022000_ota_file_zigbee_start");
extern const uint8_t ota_file_end[] asm("_binary_131B_0001_10022000_ota_file_zigbee_end");

static void ota_server_notify_image(uint16_t short_addr)
{
    ezb_zcl_ota_upgrade_image_notify_cmd_t notify_cmd = {
        .cmd_ctrl =
            {
                .dst_ep                = 0xFF,
                .src_ep                = ESP_ZIGBEE_OTA_SERVER_EP_ID,
                .dst_addr.addr_mode    = EZB_ADDR_MODE_SHORT,
                .dst_addr.u.short_addr = short_addr,
                .cnf_ctx =
                    {
                        .cb       = NULL,
                        .user_ctx = NULL,
                    },
            },
        .payload =
            {
                .type         = EZB_ZCL_OTA_UPGRADE_IMAGE_NOTIFY_PAYLOAD_TYPE_JITTER_CODE_IMAGE_VERSION,
                .query_jitter = 100,
                .manuf_code   = ESP_MANUF_CODE,
                .image_type   = ESP_IMAGE_TYPE,
                .file_version = ESP_OTA_FILE_VERSION,
            },
    };

    ezb_zcl_ota_upgrade_image_notify_cmd_req(&notify_cmd);
    ESP_LOGI(TAG, "Broadcast OTA Image Notify Command");
}

static void button_event_handler(switch_driver_handle_t handle)
{
    ESP_RETURN_ON_FALSE(handle != SWITCH_INV_HANDLE, , TAG, "Invalid switch handle");

    esp_zigbee_lock_acquire(portMAX_DELAY);
    ota_server_notify_image(0xFFFD);
    esp_zigbee_lock_release();
    ESP_EARLY_LOGI(TAG, "Broadcast OTA Image Notify Command");
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
                ezb_bdb_start_top_level_commissioning(EZB_BDB_MODE_NETWORK_FORMATION);
            } else {
                ezb_bdb_open_network(180);
                ESP_LOGI(TAG, "Device reboot");
            }
        } else {
            ESP_LOGW(TAG, "The %s failed with status(0x%02x), please retry", ezb_app_signal_to_string(signal_type), status);
            alarm_timer_schedule(esp_zigbee_alarm_bdb_commissioning, EZB_BDB_MODE_INITIALIZATION, 1000);
        }
    } break;
    case EZB_BDB_SIGNAL_FORMATION: {
        ezb_bdb_comm_status_t status = *((ezb_bdb_comm_status_t *)ezb_app_signal_get_params(app_signal));
        if (status == EZB_BDB_STATUS_SUCCESS) {
            ezb_extpanid_t extended_pan_id;
            ezb_nwk_get_extended_panid(&extended_pan_id);
            ESP_LOGI(TAG, "Formed network successfully: PAN ID(0x%04hx, EXT: 0x%llx), Channel(%d), Short Address(0x%04hx)",
                     ezb_nwk_get_panid(), extended_pan_id.u64, ezb_nwk_get_current_channel(), ezb_nwk_get_short_address());
            ezb_bdb_start_top_level_commissioning(EZB_BDB_MODE_NETWORK_STEERING);
        } else {
            ESP_LOGW(TAG, "Failed to form network with status(0x%02x)", status);
            alarm_timer_schedule(esp_zigbee_alarm_bdb_commissioning, EZB_BDB_MODE_NETWORK_FORMATION, 1000);
        }
    } break;
    case EZB_BDB_SIGNAL_STEERING: {
        ezb_bdb_comm_status_t status = *((ezb_bdb_comm_status_t *)ezb_app_signal_get_params(app_signal));
        if (status == EZB_BDB_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "Network steering completed");
        } else {
            ESP_LOGW(TAG, "Failed to steering network with status(0x%02x)", status);
            alarm_timer_schedule(esp_zigbee_alarm_bdb_commissioning, EZB_BDB_MODE_NETWORK_STEERING, 1000);
        }
    } break;
    case EZB_ZDO_SIGNAL_DEVICE_ANNCE: {
        const ezb_zdo_signal_device_annce_params_t *dev_annce_params = ezb_app_signal_get_params(app_signal);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->short_addr);
        ota_server_notify_image(dev_annce_params->short_addr);
    } break;
    case EZB_ZDO_SIGNAL_LEAVE_INDICATION: {
        const ezb_zdo_signal_leave_indication_params_t *leave_ind_params = ezb_app_signal_get_params(app_signal);
        ESP_LOGI(TAG, "Zigbee Node(0x%04hx) is leaving network", leave_ind_params->short_addr);
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

static void zcl_ota_upgrade_server_progress_handler(ezb_zcl_ota_upgrade_server_progress_message_t *message)
{
    ESP_LOGI(TAG, "-- OTA Upgrade Server Progress");

    switch (message->in.progress) {
    case EZB_ZCL_OTA_UPGRADE_PROGRESS_START:
        ESP_LOGI(TAG, "OTA Query Start:");
        ESP_LOGI(TAG, "  Client: short_addr=0x%04x, ep_id=%d", message->in.start.query.short_address,
                 message->in.start.query.ep_id);
        ESP_LOGI(TAG, "  Query: manuf_code=0x%04x, image_type=0x%04x, file_version=0x%08lx, hw_version=0x%04x",
                 message->in.start.query.manuf_code, message->in.start.query.image_type, message->in.start.query.file_version,
                 message->in.start.query.hw_version);
        ESP_LOGI(TAG, "  Policy: file_version=0x%08lx", message->in.start.policy.file_version);
        // Accept the query and return the file version from policy
        message->out.result = EZB_ZCL_STATUS_SUCCESS;
        break;
    case EZB_ZCL_OTA_UPGRADE_PROGRESS_SENDING:
        ESP_LOGI(TAG, "OTA Sending Block:");
        ESP_LOGI(TAG, "  manuf_code=0x%04x, image_type=0x%04x, file_version=0x%08lx", message->in.sending.manuf_code,
                 message->in.sending.image_type, message->in.sending.file_version);
        ESP_LOGW(TAG, "In progress: [%ld / %ld]", message->in.sending.file_offset, (uint32_t)(ota_file_end - ota_file_start));
        message->out.result = EZB_ZCL_STATUS_SUCCESS;
        break;
    case EZB_ZCL_OTA_UPGRADE_PROGRESS_FINISH:
        ESP_LOGI(TAG, "OTA Upgrade End:");
        ESP_LOGI(TAG, "  status=0x%02x, manuf_code=0x%04x, image_type=0x%04x, file_version=0x%08lx", message->in.finish.status,
                 message->in.finish.manuf_code, message->in.finish.image_type, message->in.finish.file_version);
        message->out.finish.current_time = 0; // Application should set actual current time
        message->out.finish.upgrade_time = 0; // Application should set actual upgrade time (0 = immediate)
        message->out.result              = EZB_ZCL_STATUS_SUCCESS;
        break;
    case EZB_ZCL_OTA_UPGRADE_PROGRESS_ABORT:
        ESP_LOGW(TAG, "OTA Abort");
        message->out.result = EZB_ZCL_STATUS_SUCCESS;
        break;
    default:
        ESP_LOGW(TAG, "Unknown OTA progress status: %d", message->in.progress);
        message->out.result = EZB_ZCL_STATUS_SUCCESS;
        break;
    }
}

static void esp_zigbee_zcl_core_action_handler(ezb_zcl_core_action_callback_id_t callback_id, void *message)
{
    switch (callback_id) {
    case EZB_ZCL_CORE_OTA_UPGRADE_SERVER_PROGRESS_CB_ID:
        zcl_ota_upgrade_server_progress_handler(message);
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

esp_err_t esp_zigbee_create_zha_on_off_switch_with_ota_server_device(void)
{
    ezb_af_ep_config_t ep_config = {
        .ep_id              = ESP_ZIGBEE_OTA_SERVER_EP_ID,
        .app_profile_id     = EZB_AF_HA_PROFILE_ID,
        .app_device_id      = EZB_ZHA_ON_OFF_LIGHT_DEVICE_ID,
        .app_device_version = 0,
    };

    ezb_af_device_desc_t   dev_desc        = ezb_af_create_device_desc();
    ezb_af_ep_desc_t       ep_desc         = ezb_af_create_endpoint_desc(&ep_config);
    ezb_zcl_cluster_desc_t basic_desc      = EZB_INVALID_ZCL_CLUSTER_DESC;
    ezb_zcl_cluster_desc_t ota_server_desc = EZB_INVALID_ZCL_CLUSTER_DESC;

    ezb_zcl_ota_upgrade_cluster_server_config_t ota_server_cfg = {
        .ota_upgrade_file_table_size = 1,
    };
    
    basic_desc = ezb_zcl_basic_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_SERVER);
    ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)ESP_MANUFACTURER_NAME);
    ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)ESP_MODEL_IDENTIFIER);
    ezb_af_endpoint_add_cluster_desc(ep_desc, basic_desc);
    ezb_af_endpoint_add_cluster_desc(ep_desc, ezb_zcl_identify_create_cluster_desc(NULL, EZB_ZCL_CLUSTER_SERVER));
    ota_server_desc = ezb_zcl_ota_upgrade_create_cluster_desc(&ota_server_cfg, EZB_ZCL_CLUSTER_SERVER);
    ESP_ERROR_CHECK(ezb_af_endpoint_add_cluster_desc(ep_desc, ota_server_desc));

    ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));
    ESP_ERROR_CHECK(ezb_af_device_desc_register(dev_desc));

    ezb_zcl_core_action_handler_register(esp_zigbee_zcl_core_action_handler);

    ESP_RETURN_ON_FALSE(
        ezb_zcl_ota_upgrade_add_ota_file(ESP_ZIGBEE_OTA_SERVER_EP_ID, (uint8_t *)ota_file_start, ota_file_end - ota_file_start),
        ESP_ERR_NOT_SUPPORTED, TAG, "Failed to add OTA file");

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

    ESP_ERROR_CHECK(esp_zigbee_create_zha_on_off_switch_with_ota_server_device());

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
