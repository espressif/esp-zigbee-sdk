/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee customized server Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include "esp_zigbee_core.h"
#include "switch_driver.h"

/* Zigbee configuration */
#define MAX_CHILDREN                  10                                                    /* The max amount of connected devices */
#define INSTALLCODE_POLICY_ENABLE     false                                                 /* Enable the install code policy for security */
#define ESP_OTA_SERVER_ENDPOINT       5                                                     /* OTA Server endpoint identifier */
/* Zigbee OTA Configuration */
#define OTA_UPGRADE_INDEX             0                                                     /* The index of OTA upgrade image */
#define OTA_UPGRADE_TIME              OTA_UPGRADE_CURRENT_TIME + OTA_UPGRADE_OFFSET_TIME    /* Upgrade time indicates the time that the client shall upgrade to running new image, offset time value is of 5 seconds */
#define OTA_UPGRADE_QUERY_JITTER      0x64                                                  /* Query jitter indicates whether the client receiving Image Notify Command */
#define OTA_UPGRADE_CURRENT_TIME      0x12345                                               /* Test current time of ota server, currently zcl time cluster is not supported */
#define OTA_UPGRADE_IMAGE_COUNT       1                                                     /* The number of OTA images on OTA server */
#define OTA_UPGRADE_OFFSET_TIME       5                                                     /* Offset time value in seconds, use as upgrade delay.*/
#define ESP_ZB_PRIMARY_CHANNEL_MASK   (1l << 13)                                            /* Zigbee primary channel mask use in the example */

/* ota_file.bin */
extern const uint8_t ota_file_start[] asm("_binary_ota_file_bin_start");                    /* ota_file corresponds to filename and bin corresponds to filetype */
extern const uint8_t ota_file_end[]   asm("_binary_ota_file_bin_end");                      /* ota_file corresponds to filename and bin corresponds to filetype */

/* Basic manufacturer information */
#define ESP_MANUFACTURER_NAME "\x09""ESPRESSIF"      /* Customized manufacturer name */
#define ESP_MODEL_IDENTIFIER "\x07"CONFIG_IDF_TARGET /* Customized model identifier */

#define ESP_ZB_ZC_CONFIG()                                                  \
    {                                                                       \
        .esp_zb_role = ESP_ZB_DEVICE_TYPE_COORDINATOR,                      \
        .install_code_policy = INSTALLCODE_POLICY_ENABLE,                   \
        .nwk_cfg.zczr_cfg = {                                               \
            .max_children = MAX_CHILDREN,                                   \
        },                                                                  \
    }

#define ESP_ZB_DEFAULT_RADIO_CONFIG()                                       \
    {                                                                       \
        .radio_mode = ZB_RADIO_MODE_NATIVE,                                 \
    }

#define ESP_ZB_DEFAULT_HOST_CONFIG()                                        \
    {                                                                       \
        .host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE,               \
    }

#define ZB_OTA_FILE_HEADER_OPTIONAL(fileds, key, offset)                    \
{                                                                           \
    memcpy(&fileds.key, image_info, sizeof(fileds.key));                    \
    offset += sizeof(fileds.key);                                           \
}

#define OTA_UPGRADE_FILE_MAGIC_VALUE    0x0BEEF11E
#define OTA_UPGRADE_FILE_HEADER_VERSION 0x0100

typedef uint8_t HeaderString[32];

/**
 * @brief The Zigbee ZCL OTA file header struct.
 *
 */
typedef struct esp_zb_ota_image_header_s {
    uint32_t upgrade_file_id;
    uint16_t header_version;
    uint16_t header_length;
    uint16_t field_control;
    uint16_t manufacturer_id;
    uint16_t image_type;
    uint32_t file_version;
    uint16_t stack_version;
    HeaderString  header_string;
    uint32_t image_size;
} __attribute__ ((packed)) esp_zb_ota_image_header_t;

