/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <string.h>

#include "ota_file_parser.h"

#define TAG "OTA_FILE_PARSER"

esp_zb_ota_file_parser_t *esp_zb_create_ota_file_parser(uint32_t total_image_size)
{
    esp_zb_ota_file_parser_t *parser = (esp_zb_ota_file_parser_t *)calloc(1, sizeof(esp_zb_ota_file_parser_t));
    if (!parser) {
        return NULL;
    }
    parser->total_image_size = total_image_size;
    return parser;
}

void esp_zb_free_ota_file_parser(esp_zb_ota_file_parser_t *parser)
{
    if (parser) {
        free(parser);
    }
}

void esp_zb_ota_file_parser_setup(esp_zb_ota_file_parser_t *parser, uint32_t block_size, uint8_t *block)
{
    parser->in        = block;
    parser->in_length = block_size;
}

bool esp_zb_ota_file_parser_is_element_value(esp_zb_ota_file_parser_t *parser)
{
    return parser && parser->element.length && parser->element.val ? true : false;
}

static uint16_t ota_file_stream_format(uint8_t *dst, uint16_t dst_offset, uint16_t dst_total, uint8_t *src, uint16_t src_total)
{
    uint16_t size = 0;
    if (dst_offset < dst_total) {
        size = MIN(dst_total - dst_offset, src_total);
        memcpy(dst + dst_offset, src, size);
        dst_offset += size;
    }
    return size;
}

static void ota_file_parser_refresh(esp_zb_ota_file_parser_t *parser, uint16_t written)
{
    parser->offset += written;
    parser->total_offset += written;
    parser->in        = parser->in + written;
    parser->in_length = parser->in_length - written;
}

static ezb_zcl_ota_file_header_optional_t ota_file_parser_get_optional(uint8_t fc, uint8_t *buffer)
{
    ezb_zcl_ota_file_header_optional_t optional = {0};
    uint16_t                              offset   = 0;
    if (fc & EZB_ZCL_OTA_FILE_HEADER_FC_SECURITY_CREDENTIAL_VERSION_PRESENT) {
        memcpy(&optional.security_credential_version, buffer + offset, sizeof(uint8_t));
        offset += sizeof(uint8_t);
    }
    if (fc & EZB_ZCL_OTA_FILE_HEADER_FC_DEVICE_SPECIFIC) {
        memcpy(&optional.upgrade_file_destination, buffer + offset, sizeof(ezb_extaddr_t));
        offset += sizeof(ezb_extaddr_t);
    }
    if (fc & EZB_ZCL_OTA_FILE_HEADER_FC_HW_VERSION_PRESENT) {
        memcpy(&optional.minimum_hardware_version, buffer + offset, sizeof(uint16_t));
        offset += sizeof(uint16_t);
        memcpy(&optional.maximum_hardware_version, buffer + offset, sizeof(uint16_t));
        offset += sizeof(uint16_t);
    }
    return optional;
}

esp_err_t esp_zb_ota_file_parser_check(esp_zb_ota_file_parser_t *parser)
{
    return parser && parser->total_image_size > 0 && parser->total_offset == parser->total_image_size ? ESP_OK : ESP_FAIL;
}

esp_err_t esp_zb_ota_file_parser_process(esp_zb_ota_file_parser_t *parser)
{
    /* Check input validity，No more data to continue parsing */
    if (parser && (parser->in_length == 0 || parser->in == NULL)) {
        parser->element.length = 0;
        parser->element.val    = NULL;
        return ESP_ERR_INVALID_ARG;
    }

    /* Parse header */
    uint16_t written = 0;
    if (sizeof(parser->header.mandatory) > parser->total_offset) {
        written = ota_file_stream_format((uint8_t *)&parser->header.mandatory, parser->offset, sizeof(parser->header.mandatory),
                                         parser->in, parser->in_length);
        ota_file_parser_refresh(parser, written);
        parser->offset = parser->total_offset >= sizeof(parser->header.mandatory) ? 0 : parser->offset;
        goto exit;
    }

    /* Parse optional */
    if (parser->header.mandatory.hdr_length > parser->total_offset) {
        written = ota_file_stream_format((uint8_t *)&parser->header.optional, parser->offset,
                                         parser->header.mandatory.hdr_length - sizeof(parser->header.mandatory), parser->in,
                                         parser->in_length);
        ota_file_parser_refresh(parser, written);
        if (parser->total_offset >= parser->header.mandatory.hdr_length) {
            parser->offset = 0;
            parser->header.optional =
                ota_file_parser_get_optional(parser->header.mandatory.hdr_fc, (uint8_t *)&parser->header.optional);
        }
        goto exit;
    }

    /* Parse element */
    if (parser->offset < OTA_ELEMENT_HEADER_LEN) {
        written = ota_file_stream_format((uint8_t *)&parser->element, parser->offset, OTA_ELEMENT_HEADER_LEN, parser->in,
                                         parser->in_length);
        ota_file_parser_refresh(parser, written);
        parser->element.total += OTA_ELEMENT_HEADER_LEN;
        parser->element.length = 0;
        parser->element.val    = NULL;
        goto exit;
    }

    if (parser->offset < parser->element.total) {
        parser->element.length = MIN(parser->element.total - parser->offset, parser->in_length);
        parser->element.val    = parser->in;
        written                = parser->element.length;
        ota_file_parser_refresh(parser, written);
        parser->offset = parser->offset >= parser->element.total ? 0 : parser->offset;
        goto exit;
    }

exit:
    return parser->in_length ? ESP_ERR_NOT_FINISHED : ESP_OK;
}
