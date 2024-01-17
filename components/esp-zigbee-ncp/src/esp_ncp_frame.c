/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <stdint.h>

#include <esp_err.h>
#include "esp_log.h"
#include "esp_crc.h"
#include "esp_random.h"

#include "slip.h"
#include "esp_ncp_frame.h"
#include "esp_ncp_zb.h"
#include "esp_ncp_bus.h"
#include "esp_ncp_main.h"

static const char* TAG = "ESP_NCP_FRAME";

esp_err_t esp_ncp_frame_output(const void *buffer, uint16_t len)
{
    esp_err_t ret = ESP_ERR_INVALID_ARG;
    uint8_t *output = NULL;
    uint16_t outlen = 0;

    do {
        if (!buffer) {
            ESP_LOGE(TAG, "Invalid packet");
            break;
        }

        /* SLIP */
        slip_decode(buffer, len, &output, &outlen);
        if (!output) {
            ESP_LOGE(TAG, "SLIP characters must include");
            ESP_LOG_BUFFER_HEX_LEVEL(TAG, buffer, len, ESP_LOG_ERROR);
            break;
        }

        /* Packet Length */
        uint16_t data_head_len = sizeof(esp_ncp_header_t);
        if (outlen < data_head_len) {
            ESP_LOGE(TAG, "Invalid packet format");
            ESP_LOG_BUFFER_HEX_LEVEL(TAG, output, outlen, ESP_LOG_ERROR);
            ret = ESP_ERR_INVALID_SIZE;
            break;
        }

        /* Packet Header */
        esp_ncp_header_t *ncp_header = (esp_ncp_header_t *)output;
        uint8_t *payload = NULL;

        if (ncp_header->len + data_head_len > outlen) {
            ESP_LOGE(TAG, "Invalid packet len %d, expect %d", outlen, ncp_header->len + data_head_len);
            ESP_LOG_BUFFER_HEX_LEVEL(TAG, output, outlen, ESP_LOG_ERROR);
            ret = ESP_ERR_INVALID_SIZE;
            break;
        }

        /* CheckSum */
        uint16_t *checksum = (uint16_t *)(output + data_head_len + ncp_header->len);
        uint16_t crc_val = esp_crc16_le(UINT16_MAX, output, (outlen - sizeof(uint16_t)));
        if (crc_val != (*checksum)) {
            ESP_LOGE(TAG, "Invalid checksum %02x, expect %02x", *checksum, crc_val);
            ESP_LOG_BUFFER_HEX_LEVEL(TAG, output, outlen, ESP_LOG_ERROR);
            ret = ESP_ERR_INVALID_CRC;
            break;
        }

        if (ncp_header->len != 0) {
            payload = (uint8_t *)output + data_head_len;
        }

        ESP_LOG_BUFFER_HEX_LEVEL(TAG, output, outlen, ESP_LOG_INFO);

        /* Packet Payload */
        ret = esp_ncp_zb_output(ncp_header, payload, ncp_header->len);
    } while(0);

    if (output) {
        free(output);
        output = NULL;
    }

    return (ret != ESP_OK) ? esp_ncp_resp_input(NULL, &ret, 1) : ESP_OK;
}

static esp_err_t esp_ncp_frame_input(esp_ncp_header_t *data_header, const void *buffer, uint16_t len)
{
    uint8_t *output = NULL;
    uint16_t outlen = 0;

    uint16_t data_head_len = sizeof(esp_ncp_header_t);
    uint16_t size = data_head_len + len + sizeof(uint16_t);
    esp_err_t ret = ESP_OK;

    /* Alloc Data Buffer */
    uint8_t *data = calloc(1, size);
    if (data == NULL) {
        ESP_LOGE(TAG, "Malloc data fail!");
        return ESP_FAIL;
    }

    /* Packet Header */
    memcpy(data, data_header, data_head_len);

    /* Packet Payload */
    if (buffer && len) {
        memcpy(data + data_head_len, buffer, len);
    }

    /* CheckSum */
    uint16_t crc_val = esp_crc16_le(UINT16_MAX, data, data_head_len + len);
    memcpy(data + data_head_len + len, &crc_val, sizeof(uint16_t));

    /* SLIP */
    slip_encode(data, size, &output, &outlen);
    free(data);

    /* Response */
    ret = esp_ncp_bus_input(output, outlen);
    if (output) {
        free(output);
        output = NULL;
    }

    return ret;
}

esp_err_t esp_ncp_resp_input(esp_ncp_header_t *src, const void *buffer, uint16_t len)
{
    esp_ncp_header_t data_header = {
        .id = src ? src->id : 0xFFFF,
        .sn = src ? src->sn : esp_random() % 0xFF,
        .len = len,
        .flags = {
            .version = src ? src->flags.version : 0,
        }
    };
    data_header.flags.type = 1;

    return esp_ncp_frame_input(&data_header, buffer, len);
}

esp_err_t esp_ncp_noti_input(esp_ncp_header_t *src, const void *buffer, uint16_t len)
{
    esp_ncp_header_t data_header = {
        .id = src->id,
        .sn = src->sn,
        .len = len,
        .flags = {
            .version = src->flags.version,
        }
    };
    data_header.flags.type = 2;

    return esp_ncp_frame_input(&data_header, buffer, len);
}
