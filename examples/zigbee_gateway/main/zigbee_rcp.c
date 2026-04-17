/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <string.h>
#include "esp_log.h"
#include "esp_check.h"
#include "sdkconfig.h"
#if CONFIG_ZIGBEE_GW_AUTO_UPDATE_RCP
#include "esp_rcp_update.h"
#include "esp_spiffs.h"
#endif

#if CONFIG_OPENTHREAD_SPINEL_ONLY
#include "esp_radio_spinel.h"
#define ESP_ZIGBEE_RCP_VERSION_MAX_SIZE 80
#endif

#include "esp_zigbee.h"

#include "zigbee_rcp.h"

#define TAG "ZIGBEE_RCP"

#if CONFIG_ZIGBEE_GW_AUTO_UPDATE_RCP

static void rcp_update(void)
{
    /* Deinit uart to transfer UART to the serial loader */
    ESP_LOGI(TAG, "Update RCP");
    esp_zigbee_deinit();
    if (esp_rcp_update() != ESP_OK) {
        esp_rcp_mark_image_verified(false);
    }
    esp_restart();
}

static void rcp_failure_handler(void)
{
#if CONFIG_ZIGBEE_GW_AUTO_UPDATE_RCP
    ESP_LOGI(TAG, "RCP failure, re-flashing RCP");
    rcp_update();
#endif
    esp_restart();
}

esp_err_t esp_zigbee_rcp_update(void)
{
    char rcp_version[ESP_ZIGBEE_RCP_VERSION_MAX_SIZE] = {0};
    ESP_RETURN_ON_ERROR(esp_radio_spinel_rcp_version_get(rcp_version, ESP_RADIO_SPINEL_ZIGBEE), TAG,
                        "Failed to get rcp version from radio spinel");
#if (CONFIG_ZIGBEE_GW_AUTO_UPDATE_RCP)
    char storage_rcp_version[ESP_ZIGBEE_RCP_VERSION_MAX_SIZE] = {0};
    if (esp_rcp_load_version_in_storage(storage_rcp_version, sizeof(storage_rcp_version)) == ESP_OK) {
        if (strcmp(storage_rcp_version, rcp_version)) {
            ESP_LOGI(TAG, "Update the RCP version from %s to %s", storage_rcp_version, rcp_version);
            rcp_update();
        } else {
            ESP_LOGI(TAG, "Running RCP version: %s", rcp_version);
            esp_rcp_mark_image_verified(true);
        }
    } else {
        ESP_LOGI(TAG, "No RCP firmware found in storage, reboot to try next image");
        esp_rcp_mark_image_verified(false);
        esp_restart();
    }
#endif
    return ESP_OK;
}

static esp_err_t spiffs_init(void)
{
    esp_vfs_spiffs_conf_t rcp_fw_conf = {
        .base_path = "/rcp_fw", .partition_label = "rcp_fw", .max_files = 10, .format_if_mount_failed = false};
    return esp_vfs_spiffs_register(&rcp_fw_conf);
}

static void spiffs_deinit(void)
{
    esp_vfs_spiffs_unregister("rcp_fw");
}

esp_err_t esp_zigbee_rcp_init(esp_rcp_update_config_t *config)
{
    ESP_RETURN_ON_FALSE(config != NULL, ESP_ERR_INVALID_ARG, TAG, "config is NULL");
    ESP_ERROR_CHECK(spiffs_init());
    ESP_ERROR_CHECK(esp_rcp_update_init(config));
#if CONFIG_OPENTHREAD_SPINEL_ONLY
    esp_radio_spinel_register_rcp_failure_handler(rcp_failure_handler, ESP_RADIO_SPINEL_ZIGBEE);
#endif
    return ESP_OK;
}

void esp_zigbee_rcp_deinit(void)
{
#if CONFIG_OPENTHREAD_SPINEL_ONLY
    esp_radio_spinel_register_rcp_failure_handler(NULL, ESP_RADIO_SPINEL_ZIGBEE);
#endif
    esp_rcp_update_deinit();
    spiffs_deinit();
}
#endif
