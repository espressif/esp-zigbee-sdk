/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee CLI Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_zigbee_core.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "ha/esp_zigbee_ha_standard.h"
#include "esp_zigbee_cli_config.h"

#if CONFIG_ZB_ZCZR
#include "cli/zb_esp_cli.h"
#endif
#if !CONFIG_ZB_ZCZR
#error Coordinator/Router role is not compiled!
#endif

static const char *TAG = "ESP_ZB_CLI";

uint8_t esp_zb_cli_agent_handler(uint8_t bufid)
{
    if (esp_zb_cli_agent_ep_handler_general_cmd(bufid) == true) {
        return true;
    }
    if (esp_zb_cli_agent_ep_handler_attr(bufid) == true) {
        return true;
    }

    if (esp_zb_cli_agent_ep_handler_report(bufid) == true) {
        return true;
    }

    if (esp_zb_cli_agent_ep_handler_ping(bufid) == true) {
        return true;
    }

    return false;
}

/**
 * More application signals can be added by the user according to specific requirements
 */
void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p                    = signal_struct->p_app_signal;
    esp_err_t err_status                = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    esp_zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;
    esp_zb_zdo_signal_leave_indication_params_t *leave_ind_params = NULL;
    switch (sig_type) {
    case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Zigbee stack startup");
        break;
    case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Device started up in %s factory-reset mode", esp_zb_bdb_is_factory_new() ? "" : "non");
        } else {
            ESP_LOGE(TAG, "Failed to initialize Zigbee stack");
        }
        break;
    case ESP_ZB_BDB_SIGNAL_FORMATION:
        if (err_status == ESP_OK) {
            esp_zb_ieee_addr_t extended_pan_id;
            esp_zb_get_extended_pan_id(extended_pan_id);
            ESP_LOGI(TAG,
                     "Formed network successfully (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, Channel:%d, Short "
                     "Address: 0x%04hx)",
                     extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4], extended_pan_id[3], extended_pan_id[2],
                     extended_pan_id[1], extended_pan_id[0], esp_zb_get_pan_id(), esp_zb_get_current_channel(), esp_zb_get_short_address());
            ESP_LOGI(TAG, "Join or form %s network", esp_zb_network_is_distributed() ? "distributed" : "centralized");
            esp_zb_bdb_open_network(180);
        } else {
            ESP_LOGW(TAG, "Failed to form network");
        }
        break;
    case ESP_ZB_BDB_SIGNAL_STEERING:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Joined network successfully");
        } else {
            ESP_LOGW(TAG, "Not found network");
        }
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET:
        ESP_LOGI(TAG, "Touchlink target is ready, awaiting commissioning");
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK:
        if (err_status == ESP_OK) {
            esp_zb_ieee_addr_t extended_pan_id;
            esp_zb_get_extended_pan_id(extended_pan_id);
            ESP_LOGI(TAG,
                     "Commissioning successfully, network information (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, "
                     "Channel:%d, Short Address: 0x%04hx)",
                     extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4], extended_pan_id[3], extended_pan_id[2],
                     extended_pan_id[1], extended_pan_id[0], esp_zb_get_pan_id(), esp_zb_get_current_channel(), esp_zb_get_short_address());
        }
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET_FINISHED:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Touchlink target commissioning finished");
        } else {
            ESP_LOGI(TAG, "Touchlink target commissioning failed");
        }
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED:
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_JOINED_ROUTER:
        ESP_LOGI(TAG, "Touchlink initiator receives the response for %s network",
                 sig_type == ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED ? "started" : "router joining");
        esp_zb_bdb_signal_touchlink_nwk_params_t *sig_params = (esp_zb_bdb_signal_touchlink_nwk_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "Response is from profile: 0x%04hx, endpoint: %d, address: 0x%x%x%x%x%x%x%x%X", sig_params->profile_id, sig_params->endpoint,
                 sig_params->device_ieee_addr[7], sig_params->device_ieee_addr[6], sig_params->device_ieee_addr[5], sig_params->device_ieee_addr[4],
                 sig_params->device_ieee_addr[3], sig_params->device_ieee_addr[2], sig_params->device_ieee_addr[1], sig_params->device_ieee_addr[0]);
        break;
    case ESP_ZB_BDB_SIGNAL_TOUCHLINK:
        ESP_LOGI(TAG, "Touchlink commissioning as initiator done");
        esp_zb_ieee_addr_t extended_pan_id;
        esp_zb_get_extended_pan_id(extended_pan_id);
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG,
                     "Commissioning successfully, network information (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, "
                     "Channel:%d, Short Address: 0x%04hx)",
                     extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4], extended_pan_id[3], extended_pan_id[2],
                     extended_pan_id[1], extended_pan_id[0], esp_zb_get_pan_id(), esp_zb_get_current_channel(), esp_zb_get_short_address());
        } else {
            ESP_LOGW(TAG, "Not scan response for Touchlink initiator");
        }
        break;
    case ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE:
        dev_annce_params = (esp_zb_zdo_signal_device_annce_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->device_short_addr);
        break;
    case ESP_ZB_ZDO_SIGNAL_LEAVE_INDICATION:
        leave_ind_params = (esp_zb_zdo_signal_leave_indication_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        if (!leave_ind_params->rejoin) {
            ESP_LOGI(TAG, "Zigbee Node is leaving network: 0x%04hx", leave_ind_params->short_addr);
        }
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
    case ESP_ZB_ZDO_SIGNAL_LEAVE:
        if (err_status == ESP_OK) {
            esp_zb_zcl_reset_all_endpoints_to_factory_default(true, NULL);
            ESP_LOGI(TAG, "leave network, status: %s", esp_err_to_name(err_status));
        } else {
            ESP_LOGE(TAG, "Unable to leave network, status: %s", esp_err_to_name(err_status));
        }
        break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type,
                 esp_err_to_name(err_status));
        break;
    }
}

void zigbee_stack_init(void)
{
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZC_CONFIG();
    esp_zb_init(&zb_nwk_cfg);
    ESP_ERROR_CHECK(esp_zb_set_primary_network_channel_set(1 << ZIGBEE_CHANNEL));
    ESP_ERROR_CHECK(esp_zb_set_secondary_network_channel_set(ESP_ZB_TRANSCEIVER_ALL_CHANNELS_MASK));
    esp_zb_set_rx_on_when_idle(true);

    /* Set ESP Zigbee endpoint to CLI*/
    zb_cli_set_endpoint(ESP_ZIGBEE_CLI_ENDPOINT);
    /* Note that more endpoints can be added to support more application for cli */
    esp_zb_configuration_tool_cfg_t config_tool_cfg = ESP_ZB_DEFAULT_CONFIGURATION_TOOL_CONFIG();
    esp_zb_ep_list_t *esp_zb_configuration_tool_ep = esp_zb_configuration_tool_ep_create(ESP_ZIGBEE_CLI_ENDPOINT, &config_tool_cfg);
    esp_zb_device_register(esp_zb_configuration_tool_ep);
    /* Register cluster response handler for ESP Zigbee CLI endpoint */
    esp_zb_cli_resp_handler_register(esp_zb_cli_agent_handler);
}

void zb_main_loop_task(void *arg)
{
    while (true) {
        if (zb_cli_is_stack_started()) {
            esp_zb_cli_main_loop_iteration();
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));

    zb_cli_console_init();
    zigbee_stack_init();

    xTaskCreate(zb_cli_console_task, "zb_cli_console_task", 4096, NULL, 9, NULL);
    xTaskCreate(zb_main_loop_task, "zb_main_loop_task", 8192, NULL, 10, NULL);
}
