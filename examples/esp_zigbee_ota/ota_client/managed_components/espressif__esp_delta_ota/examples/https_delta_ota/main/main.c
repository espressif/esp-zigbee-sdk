/* HTTPS Delta OTA example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_timer.h"
#include "esp_event.h"

#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "esp_ota_ops.h"
#include "esp_app_format.h"
#include "esp_app_desc.h"
#include "esp_partition.h"

#include "esp_http_client.h"
#include "esp_delta_ota.h"

#define BUFFSIZE 1024
#define PATCH_HEADER_SIZE 64
#define DIGEST_SIZE 32
static uint32_t esp_delta_ota_magic = 0xfccdde10;

static const char *TAG = "https_delta_ota_example";

static char ota_write_data[BUFFSIZE + 1] = { 0 };
extern const uint8_t server_cert_pem_start[] asm("_binary_ca_cert_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_ca_cert_pem_end");

const esp_partition_t *current_partition, *destination_partition;
static esp_ota_handle_t ota_handle;

#define IMG_HEADER_LEN sizeof(esp_image_header_t)

static bool verify_chip_id(void *bin_header_data)
{
    esp_image_header_t *header = (esp_image_header_t *)bin_header_data;
    if (header->chip_id != CONFIG_IDF_FIRMWARE_CHIP_ID) {
        ESP_LOGE(TAG, "Mismatch chip id, expected %d, found %d", CONFIG_IDF_FIRMWARE_CHIP_ID, header->chip_id);
        return false;
    }
    return true;
}

#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 2, 0))
static esp_err_t write_cb(const uint8_t *buf_p, size_t size, void *user_data)
#else
static esp_err_t write_cb(const uint8_t *buf_p, size_t size)
#endif
{
    if (size <= 0) {
        return ESP_ERR_INVALID_ARG;
    }

    static char header_data[IMG_HEADER_LEN];
    static bool chip_id_verified = false;
    static int header_data_read = 0;
    int index = 0;

    if (!chip_id_verified) {
        if (header_data_read + size <= IMG_HEADER_LEN) {
            memcpy(header_data + header_data_read, buf_p, size);
            header_data_read += size;
            return ESP_OK;
        } else {
            index = IMG_HEADER_LEN - header_data_read;
            memcpy(header_data + header_data_read, buf_p, index);

            if (!verify_chip_id(header_data)) {
                return ESP_ERR_INVALID_VERSION;
            }
            chip_id_verified = true;

            // Write data in header_data buffer.
            esp_err_t err = esp_ota_write(ota_handle, header_data, IMG_HEADER_LEN);
            if (err != ESP_OK) {
                return err;
            }
        }
    }
    return esp_ota_write(ota_handle, buf_p + index, size - index);
}

static esp_err_t read_cb(uint8_t *buf_p, size_t size, int src_offset)
{
    if (size <= 0) {
        return ESP_ERR_INVALID_ARG;
    }
    return esp_partition_read(current_partition, src_offset, buf_p, size);
}

static void reboot(void)
{
    for (int i = 5; i > 0; i--) {
        ESP_LOGI(TAG, "Rebooting in %d seconds...", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    esp_restart();
}

static void http_cleanup(esp_http_client_handle_t client)
{
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
}

static bool verify_patch_header(void *img_hdr_data)
{
    if (!img_hdr_data) {
        return false;
    }
    uint32_t recv_magic = *(uint32_t *)img_hdr_data;
    uint8_t *digest = (uint8_t *)(img_hdr_data + 4);

    if (recv_magic != esp_delta_ota_magic) {
        ESP_LOGE(TAG, "Invalid magic word in patch");
        return false;
    }
    uint8_t sha_256[DIGEST_SIZE] = { 0 };
    esp_partition_get_sha256(esp_ota_get_running_partition(), sha_256);
    if (memcmp(sha_256, digest, DIGEST_SIZE) != 0) {
        ESP_LOGE(TAG, "SHA256 of current firmware differs from than in patch header. Invalid patch for current firmware");
        return false;
    }
    return true;
}

static void ota_example_task(void *pvParameter)
{
    esp_err_t err;

    esp_http_client_config_t config = {
        .url = CONFIG_EXAMPLE_FIRMWARE_UPG_URL,
        .cert_pem = (char *)server_cert_pem_start,
        .timeout_ms = CONFIG_EXAMPLE_OTA_RECV_TIMEOUT,
        .keep_alive_enable = true,
    };
#ifdef CONFIG_EXAMPLE_SKIP_COMMON_NAME_CHECK
    config.skip_cert_common_name_check = true;
#endif

    esp_http_client_handle_t client = esp_http_client_init(&config);
    if (client == NULL) {
        ESP_LOGE(TAG, "Failed to initialise HTTP connection");
        vTaskDelete(NULL);
    }
    err = esp_http_client_open(client, 0);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
        esp_http_client_cleanup(client);
        vTaskSuspend(NULL);
    }
    esp_http_client_fetch_headers(client);

    current_partition = esp_ota_get_running_partition();
    destination_partition = esp_ota_get_next_update_partition(NULL);

    if (current_partition == NULL || destination_partition == NULL) {
        ESP_LOGE(TAG, "Error getting partition information");
        goto error;
    }

    if (current_partition->subtype >= ESP_PARTITION_SUBTYPE_APP_OTA_MAX ||
            destination_partition->subtype >= ESP_PARTITION_SUBTYPE_APP_OTA_MAX) {
        goto error;
    }

    err = esp_ota_begin(destination_partition, OTA_SIZE_UNKNOWN, &(ota_handle));
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_ota_begin failed: %s", esp_err_to_name(err));
        goto error;
    }
    esp_delta_ota_cfg_t cfg = {
        .read_cb = &read_cb,
    };

#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 2, 0))
    char *user_data = "https_delta_ota";
    cfg.write_cb_with_user_data = &write_cb;
    cfg.user_data = user_data;
#else
    cfg.write_cb = &write_cb;
#endif

    esp_delta_ota_handle_t handle = esp_delta_ota_init(&cfg);
    if (handle == NULL) {
        ESP_LOGE(TAG, "delta_ota_set_cfg failed");
        goto error;
    }

    // Read size equal to patch header to verify the header
    int data_read = esp_http_client_read(client, ota_write_data, PATCH_HEADER_SIZE);
    if (data_read != PATCH_HEADER_SIZE) {
        ESP_LOGE(TAG, "Patch Header not received");
        goto error;
    }
    if (!verify_patch_header(ota_write_data)) {
        ESP_LOGE(TAG, "Patch Header verification failed");
        goto error;
    }

    while (1) {
        int data_read = esp_http_client_read(client, ota_write_data, BUFFSIZE);
        if (data_read < 0) {
            ESP_LOGE(TAG, "Error: SSL data read error");
            goto error;
        } else if (data_read > 0) {
            if (esp_delta_ota_feed_patch(handle, (const uint8_t *)ota_write_data, data_read) < 0) {
                ESP_LOGE(TAG, "Error while applying patch");
                goto error;
            }
        } else if (data_read == 0) {
            if (esp_http_client_is_complete_data_received(client) == true) {
                ESP_LOGI(TAG, "Connection closed");
                break;
            }
            if (errno == ECONNRESET || errno == ENOTCONN) {
                ESP_LOGE(TAG, "Connection closed, errno = %d", errno);
                break;
            }
        }
    }
    err = esp_delta_ota_finalize(handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_delta_ota_finalize() failed : %s", esp_err_to_name(err));
    }
    err = esp_delta_ota_deinit(handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_delta_ota_deinit() failed : %s", esp_err_to_name(err));
    }
    err = esp_ota_end(ota_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_ota_end() failed : %s", esp_err_to_name(err));
    }
    err = esp_ota_set_boot_partition(destination_partition);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_ota_set_boot_partition() failed : %s", esp_err_to_name(err));
    }
    http_cleanup(client);
    reboot();
error:
    http_cleanup(client);
    vTaskDelete(NULL);
}

void app_main(void)
{
    ESP_LOGI(TAG, "Initialising WiFi Connection...");

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());
    xTaskCreate(&ota_example_task, "ota_example_task", 8192, NULL, 5, NULL);
}
