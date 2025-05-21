/*
 * SPDX-License-Identifier: Apache 2.0 License
 *
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "esp_err.h"
#include "esp_log.h"

#include "esp_delta_ota.h"
#include "detools.h"

static const char *TAG = "esp_delta_ota";

typedef struct esp_delta_ota_ctx {
    void *user_data;
    src_read_cb_t read_cb;
    union {
        merged_stream_write_cb_with_user_ctx_t write_cb_with_user_data;
        merged_stream_write_cb_t write_cb;
    };
    struct detools_apply_patch_t *apply_patch;
    int src_offset;
} esp_delta_ota_ctx;

static int esp_delta_ota_write_cb(void *arg_p, const uint8_t *buf_p, size_t size)
{
    if (size <= 0) {
        return ESP_ERR_INVALID_ARG;
    }
    esp_delta_ota_ctx *handle = (esp_delta_ota_ctx *)arg_p;
    esp_err_t err = ESP_OK;
    if (!handle->user_data) {
        err = handle->write_cb(buf_p, size);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Error in write_cb(): %s", esp_err_to_name(err));
            return ESP_FAIL;
        }
    } else {
        err = handle->write_cb_with_user_data(buf_p, size, handle->user_data);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Error in write_cb_with_user_data(): %s", esp_err_to_name(err));
            return ESP_FAIL;
        }
    }
    return ESP_OK;
}

static int esp_delta_ota_read_cb(void *arg_p, uint8_t *buf_p, size_t size)
{
    if (size <= 0 || !arg_p) {
        return -ESP_ERR_INVALID_ARG;
    }
    esp_delta_ota_ctx *handle = (esp_delta_ota_ctx *)arg_p;
    esp_err_t err = handle->read_cb(buf_p, size, handle->src_offset);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error in read_cb(): %s", esp_err_to_name(err));
        return ESP_FAIL;
    }
    handle->src_offset += size;
    return ESP_OK;
}

static int esp_delta_ota_seek_cb(void *arg_p, int offset)
{
    esp_delta_ota_ctx *handle = (esp_delta_ota_ctx *)arg_p;
    handle->src_offset += offset;
    return ESP_OK;
}

esp_delta_ota_handle_t esp_delta_ota_init(esp_delta_ota_cfg_t *cfg)
{
    esp_delta_ota_ctx *ctx = calloc(1, sizeof(esp_delta_ota_ctx));
    if (!ctx) {
        ESP_LOGE(TAG, "Unable to allocate memory");
        return NULL;
    }
    ctx->user_data = cfg->user_data;
    ctx->read_cb = cfg->read_cb;
    ctx->write_cb_with_user_data = cfg->write_cb_with_user_data;
    ctx->apply_patch = calloc(1, sizeof(struct detools_apply_patch_t));
    if (!ctx->apply_patch) {
        ESP_LOGE(TAG, "Unable to allocate memory");
        free(ctx);
        ctx = NULL;
        return NULL;
    }
    int ret = detools_apply_patch_init(ctx->apply_patch, &esp_delta_ota_read_cb, &esp_delta_ota_seek_cb, 0, &esp_delta_ota_write_cb, ctx);
    if (ret < 0) {
        ESP_LOGE(TAG, "Error while initializing delta_ota: %s", detools_error_as_string(ret));
        free(ctx->apply_patch);
        ctx->apply_patch = NULL;
        free(ctx);
        ctx = NULL;
        return NULL;
    }
    return (esp_delta_ota_handle_t)ctx;
}

esp_err_t esp_delta_ota_feed_patch(esp_delta_ota_handle_t handle, const uint8_t *buf, int size)
{
    if (handle == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    esp_delta_ota_ctx *ctx = (esp_delta_ota_ctx *)handle;

    int err = detools_apply_patch_process(ctx->apply_patch, (const uint8_t *)buf, size);
    if (err != 0) {
        ESP_LOGE(TAG, "Error while applying patch: %s", detools_error_as_string(err));
        return ESP_FAIL;
    }
    return ESP_OK;
}

esp_err_t esp_delta_ota_finalize(esp_delta_ota_handle_t handle)
{
    if (handle == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    esp_delta_ota_ctx *ctx = (esp_delta_ota_ctx *)handle;

    int err = detools_apply_patch_finalize(ctx->apply_patch);
    if (err < 0) {
        ESP_LOGE(TAG, "Error while finishing the patching: %s", detools_error_as_string(err));
        return ESP_FAIL;
    }
    return ESP_OK;
}

esp_err_t esp_delta_ota_deinit(esp_delta_ota_handle_t handle)
{
    if (handle == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    esp_delta_ota_ctx *ctx = (esp_delta_ota_ctx *)handle;

    free(ctx->apply_patch);
    ctx->apply_patch = NULL;
    free(ctx);
    ctx = NULL;
    return ESP_OK;
}
