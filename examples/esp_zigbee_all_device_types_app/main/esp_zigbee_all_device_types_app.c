/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "esp_zigbee_all_device_types_app.h"

static const char *TAG = "ESP_ZB_CONSOLE_APP";

static void log_nwk_info(const char *status_string)
{
    esp_zb_ieee_addr_t extended_pan_id;
    esp_zb_get_extended_pan_id(extended_pan_id);
    ESP_LOGI(TAG, "%s (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, "
                  "Channel:%d, Short Address: 0x%04hx)", status_string,
                  extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4],
                  extended_pan_id[3], extended_pan_id[2], extended_pan_id[1], extended_pan_id[0],
                  esp_zb_get_pan_id(), esp_zb_get_current_channel(), esp_zb_get_short_address());
}

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p     = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    esp_zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;
    esp_zb_zdo_signal_leave_indication_params_t *leave_ind_params = NULL;
    const char *err_name = esp_err_to_name(err_status);
    switch (sig_type) {
    case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Initialize Zigbee stack");
        break;
    case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Device started up in%s factory-reset mode", esp_zb_bdb_is_factory_new() ? "" : " non");
        } else {
            ESP_LOGE(TAG, "%s failed with status: %s, please retry", esp_zb_zdo_signal_to_string(sig_type),
                     esp_err_to_name(err_status));
        }
        break;
    case ESP_ZB_BDB_SIGNAL_FORMATION:
        if (err_status == ESP_OK) {
            log_nwk_info("Formed network successfully");
        } else {
            ESP_LOGI(TAG, "Failed to form network (status: %s)", err_name);
        }
        break;
    case ESP_ZB_BDB_SIGNAL_STEERING:
        if (err_status == ESP_OK) {
            log_nwk_info("Joined network successfully");
        } else {
            ESP_LOGI(TAG, "Failed to join network (status: %s)", err_name);
        }
        break;
    case ESP_ZB_ZDO_SIGNAL_LEAVE:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Left network successfully");
        } else {
            ESP_LOGE(TAG, "Failed to leave network (status: %s)", err_name);
        }
        break;
    case ESP_ZB_ZDO_SIGNAL_LEAVE_INDICATION:
        leave_ind_params = (esp_zb_zdo_signal_leave_indication_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "Zigbee Node (0x%04hx) is leaving network", leave_ind_params->short_addr);
        break;
    case ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE:
        dev_annce_params = (esp_zb_zdo_signal_device_annce_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->device_short_addr);
        break;
    case ESP_ZB_NWK_SIGNAL_PERMIT_JOIN_STATUS:
        if (err_status == ESP_OK) {
            if (*(uint8_t *)esp_zb_app_signal_get_params(p_sg_p)) {
                ESP_LOGI(TAG, "Network(0x%04hx) is open for %d seconds", esp_zb_get_pan_id(), *(uint8_t *)esp_zb_app_signal_get_params(p_sg_p));
            } else {
                ESP_LOGW(TAG, "Network(0x%04hx) closed, devices joining not allowed.", esp_zb_get_pan_id());
            }
        }
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET:
        ESP_LOGI(TAG, "Touchlink target is ready, waiting for commissioning");
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK:
        if (err_status == ESP_OK) {
            log_nwk_info("Touchlink commissioning successfully");
        } else {
            ESP_LOGW(TAG, "Touchlink commissioning failed (status: %s)", err_name);
        }
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET_FINISHED:
        ESP_LOGI(TAG, "Touchlink target finished (status: %s)", err_name);
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED:
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_JOINED_ROUTER:
        ESP_LOGI(TAG, "Touchlink initiator receives the response for %s network",
                 sig_type == ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED ? "started" : "router joining");
        esp_zb_bdb_signal_touchlink_nwk_params_t *sig_params = (esp_zb_bdb_signal_touchlink_nwk_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "Response is from profile: 0x%04hx, endpoint: %d, address: 0x%16" PRIx64,
                      sig_params->profile_id, sig_params->endpoint, *(uint64_t*)sig_params->device_ieee_addr);
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK:
        if (err_status == ESP_OK) {
            log_nwk_info("Touchlink commissioning successfully");
        } else {
            ESP_LOGW(TAG, "No Touchlink target devices found");
        }
        break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type,
                 err_name);
        break;
    }
}

void zb_stack_init(void)
{
    /* Initialize Zigbee stack with default configuration */
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZR_CONFIG();
    esp_zb_init(&zb_nwk_cfg);

    /* Set default allowed network channels */
    esp_zb_set_channel_mask(ESP_ZB_TRANSCEIVER_ALL_CHANNELS_MASK);

    /* Set default scan channels */
    esp_zb_set_primary_network_channel_set(ESP_ZB_TRANSCEIVER_ALL_CHANNELS_MASK);
    esp_zb_set_secondary_network_channel_set(ESP_ZB_TRANSCEIVER_ALL_CHANNELS_MASK);

    /* Enable CLI managed ep_list */
    esp_zb_console_manage_ep_list(NULL);
}

static void zb_stack_main_task(void *pvParameters)
{
    zb_stack_init();

    /* Do not call `esp_zb_start()`.
     *
     * We want the timing of starting the stack to be managed by CLI,
     * so that we have a chance to do configurations on the stack.
     *
     */

    esp_zb_stack_main_loop();

    esp_zb_console_deinit();
    vTaskDelete(NULL);
}

void app_main(void)
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_zb_console_init());
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    xTaskCreate(zb_stack_main_task, "Zigbee_main", 4096, NULL, 5, NULL);
    ESP_LOGI(TAG, "Start ESP Zigbee Console");
    ESP_ERROR_CHECK(esp_zb_console_start());
}
