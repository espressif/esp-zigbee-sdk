/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee delta OTA Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_check.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_app_format.h"
#include "esp_delta_ota.h"

#include "esp_delta_ota_ops.h"

static const char *TAG = "ESP_DELTA_OTA_OPS";

static const esp_partition_t *s_cur_partition = NULL;
static esp_delta_ota_handle_t s_delta_ota_handle = NULL;
static esp_delta_ota_ctx_t    *s_delta_ota_ctx = NULL;

static esp_err_t delta_ota_patch_header_verify(void *img_hdr_data)
{
    uint8_t sha_256[DELTA_OTA_UPGRADE_DIGEST_SIZE] = { 0 };
    uint32_t recv_magic = 0;
    uint8_t *digest = NULL;

    if (!img_hdr_data) {
        return ESP_ERR_INVALID_ARG;
    }

    recv_magic = *(uint32_t *)img_hdr_data;
    if (recv_magic != DELTA_OTA_UPGRADE_MAGIC) {
        ESP_LOGE(TAG, "Invalid magic word in patch");
        return ESP_ERR_INVALID_ARG;
    }

    digest = (uint8_t *)(img_hdr_data + sizeof(uint32_t));
    esp_partition_get_sha256(s_cur_partition, sha_256);
    if (memcmp(sha_256, digest, DELTA_OTA_UPGRADE_DIGEST_SIZE) != 0) {
        ESP_LOGE(TAG, "Invalid patch, the SHA256 of the current firmware differs from that in the patch header.");
        return ESP_ERR_INVALID_ARG;
    }

    return ESP_OK;
}

static bool delta_ota_chip_id_verify(void *bin_header_data)
{
    esp_image_header_t *header = (esp_image_header_t *)bin_header_data;
    ESP_RETURN_ON_FALSE(header->chip_id == CONFIG_IDF_FIRMWARE_CHIP_ID, false, TAG,
                        "Mismatch chip id, expected %d, found %d", CONFIG_IDF_FIRMWARE_CHIP_ID, header->chip_id);

    return true;
}

static esp_err_t delta_ota_write_cb(const uint8_t *buf_p, size_t size, void *user_data)
{
    if (size <= 0) {
        return ESP_ERR_INVALID_ARG;
    }

    esp_ota_handle_t ota_handle = (esp_ota_handle_t)user_data;
    int index = 0;

    if (!s_delta_ota_ctx->chip_id_verified) {
        if (s_delta_ota_ctx->header_data_read + size <= DELTA_OTA_UPGRADE_IMAGE_HEADER_SIZE) {
            memcpy(s_delta_ota_ctx->header_data + s_delta_ota_ctx->header_data_read, buf_p, size);
            s_delta_ota_ctx->header_data_read += size;
            return ESP_OK;
        } else {
            index = DELTA_OTA_UPGRADE_IMAGE_HEADER_SIZE - s_delta_ota_ctx->header_data_read;
            memcpy(s_delta_ota_ctx->header_data + s_delta_ota_ctx->header_data_read, buf_p, index);

            if (!delta_ota_chip_id_verify(s_delta_ota_ctx->header_data)) {
                return ESP_ERR_INVALID_VERSION;
            }
            s_delta_ota_ctx->chip_id_verified = true;

            // Write data in header_data buffer.
            esp_err_t err = esp_ota_write(ota_handle, s_delta_ota_ctx->header_data, DELTA_OTA_UPGRADE_IMAGE_HEADER_SIZE);
            if (err != ESP_OK) {
                return err;
            }
        }
    }

    return esp_ota_write(ota_handle, buf_p + index, size - index);
}

static esp_err_t delta_ota_read_cb(uint8_t *buf_p, size_t size, int src_offset)
{
    if (size <= 0) {
        return ESP_ERR_INVALID_ARG;
    }

    return esp_partition_read(s_cur_partition, src_offset, buf_p, size);
}

esp_err_t esp_delta_ota_begin(const esp_partition_t *partition, size_t image_size, esp_ota_handle_t *out_handle)
{
    esp_err_t ret = ESP_OK;
    esp_ota_handle_t ota_handle = 0;
    esp_delta_ota_cfg_t cfg = {
        .read_cb = &delta_ota_read_cb,
        .write_cb_with_user_data = &delta_ota_write_cb,
    };

    s_cur_partition = esp_ota_get_running_partition();
    assert(s_cur_partition);

    ESP_RETURN_ON_FALSE(s_cur_partition->subtype < ESP_PARTITION_SUBTYPE_APP_OTA_MAX &&
                        partition->subtype < ESP_PARTITION_SUBTYPE_APP_OTA_MAX, ESP_ERR_INVALID_ARG, TAG,
                        "Failed to get partition info of currently or next running app");

    ret = esp_ota_begin(partition, image_size, &ota_handle);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to begin OTA partition, status: %s", esp_err_to_name(ret));

    cfg.user_data = (void *)ota_handle;
    s_delta_ota_handle = esp_delta_ota_init(&cfg);
    assert(s_delta_ota_handle);

    s_delta_ota_ctx = calloc(1, sizeof(esp_delta_ota_ctx_t));
    assert(s_delta_ota_ctx);
    s_delta_ota_ctx->header_data = calloc(1, DELTA_OTA_UPGRADE_IMAGE_HEADER_SIZE);
    assert(s_delta_ota_ctx->header_data);

    *out_handle = ota_handle;

    return ret;
}

esp_err_t esp_delta_ota_write(esp_ota_handle_t handle, uint8_t *data, int size)
{
    esp_err_t ret = ESP_OK;

    static uint8_t *patch_buf = NULL;
    static uint8_t  patch_len = 0;
    const uint8_t *patch_data = (const uint8_t *)data;
    int patch_size = size;
    if (!s_delta_ota_ctx->verify_patch_flag) {
        if (!patch_buf) {
            patch_buf = calloc(1, size);
        } else {
            patch_buf = realloc(patch_buf, patch_len + size);
        }
        ESP_RETURN_ON_FALSE(patch_buf, ESP_ERR_NO_MEM, TAG, "No memory for delta OTA write");
        memcpy(patch_buf + patch_len, data, size);
        patch_len += size;

        if (patch_len <= DELTA_OTA_UPGRADE_PATCH_HEADER_SIZE) {
            return ESP_OK;
        }

        ret = delta_ota_patch_header_verify(patch_buf);
        ESP_GOTO_ON_ERROR(ret, exit, TAG, "Patch Header verification failed, status: %s", esp_err_to_name(ret));
                    
        s_delta_ota_ctx->verify_patch_flag = true;
        patch_data = (const uint8_t *)patch_buf + DELTA_OTA_UPGRADE_PATCH_HEADER_SIZE;
        patch_size = patch_len - DELTA_OTA_UPGRADE_PATCH_HEADER_SIZE;
    }

    if (s_delta_ota_ctx->verify_patch_flag) {
        ret = esp_delta_ota_feed_patch(s_delta_ota_handle, patch_data, patch_size);
        ESP_GOTO_ON_ERROR(ret, exit, TAG, "Failed to apply the patch on the source data, status: %s", esp_err_to_name(ret));
    }

exit:
    if (patch_buf) {
        free(patch_buf);
        patch_buf = NULL;
        patch_len = 0;
    }

    return ret;
}

esp_err_t esp_delta_ota_end(esp_ota_handle_t handle)
{
    esp_err_t ret = ESP_OK;

    if (s_delta_ota_ctx) {
        if (s_delta_ota_ctx->header_data) {
            free(s_delta_ota_ctx->header_data);
            s_delta_ota_ctx->header_data = NULL;
        }
        free(s_delta_ota_ctx);
        s_delta_ota_ctx = NULL;
    }

    ret = esp_delta_ota_finalize(s_delta_ota_handle);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to finish the patch applying operation, status: %s", esp_err_to_name(ret));
    ret = esp_delta_ota_deinit(s_delta_ota_handle);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to clean-up delta ota process, status: %s", esp_err_to_name(ret));
    ret = esp_ota_end(handle);

    return ret;
}
