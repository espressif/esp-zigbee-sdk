/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#pragma once

#include "stdbool.h"

#include "esp_err.h"

#include "ezbee/zcl/cluster/ota_upgrade.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OTA_ELEMENT_HEADER_LEN (sizeof(uint16_t) + sizeof(uint32_t))

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/**
 * @brief OTA element tag identifier enumeration
 */
typedef enum esp_ota_element_tag_id_e {
    UPGRADE_IMAGE = 0x0000, /*!< Upgrade image */
} esp_ota_element_tag_id_t;

/**
 * @brief OTA element parser structure
 *
 * Note: This is OTA-specific element format (Type(2B) + Length(4B) + Value),
 * not the Zigbee R23 TLV format (Tag(1B) + Length(1B) + Value).
 */
typedef struct esp_zb_ota_file_parser_s {
    uint32_t offset;           /*!< Byte offset within current element header/value being parsed.
                                    Used to track partial header across multiple data blocks.
                                    Reset to 0 when starting a new element. */
    uint32_t total_offset;     /*!< Total offset in bytes */
    uint32_t total_image_size; /*!< Total image size in bytes */
    uint16_t in_length;        /*!< Size of remaining input data to process (bytes) */
    uint8_t *in;               /*!< Pointer to current position in input buffer */

    /** OTA header fields */
    struct {
        ezb_zcl_ota_file_header_t          mandatory; /*!< Mandatory header fields */
        ezb_zcl_ota_file_header_optional_t optional;  /*!< Optional header fields */
    } __attribute__((packed)) header;

    /**
     * @brief OTA element fields
     */
    struct {
        uint16_t type;   /*!< Element Type field (2 bytes): Tag identifier (e.g., UPGRADE_IMAGE=0x0000) */
        uint32_t total;  /*!< Total element size in bytes */
        uint16_t length; /*!< length of parsed element data (bytes). */
        uint8_t *val;    /*!< Pointer to parsed value data.
                              Points directly into input buffer (zero-copy). */
    } __attribute__((packed)) element;
} esp_zb_ota_file_parser_t;

esp_zb_ota_file_parser_t *esp_zb_create_ota_file_parser(uint32_t total_image_size);

void esp_zb_free_ota_file_parser(esp_zb_ota_file_parser_t *parser);

void esp_zb_ota_file_parser_setup(esp_zb_ota_file_parser_t *parser, uint32_t block_size, uint8_t *block);

bool esp_zb_ota_file_parser_is_element_value(esp_zb_ota_file_parser_t *parser);

esp_err_t esp_zb_ota_file_parser_process(esp_zb_ota_file_parser_t *parser);

esp_err_t esp_zb_ota_file_parser_check(esp_zb_ota_file_parser_t *parser);

#ifdef __cplusplus
}
#endif
