/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
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

/* Zigbee configuration */
#define MAX_CHILDREN                  10                                                    /* The max amount of connected devices */
#define INSTALLCODE_POLICY_ENABLE     false                                                 /* Enable the install code policy for security */
#define ESP_OTA_SERVER_ENDPOINT       5                                                     /* OTA Server endpoint identifier */
/* Zigbee OTA Configuration */
#define OTA_UPGRADE_INDEX             0                                                     /* The index of OTA upgrade image */
#define OTA_UPGRADE_FILE_VERSION      0x01010110                                            /* The test file version of the running firmware image on the device */
#define OTA_UPGRADE_MANUFACTURER      0x1001                                                /* The test value for the manufacturer of the device */
#define OTA_UPGRADE_IMAGE_TYPE        0x1011                                                /* The image type of the file that the client is currently downloading */
#define OTA_UPGRADE_TIME              OTA_UPGRADE_CURRENT_TIME + OTA_UPGRADE_OFFSET_TIME    /* Upgrade time indicates the time that the client shall upgrade to running new image, offset time value is of 5 seconds */
#define OTA_UPGRADE_QUERY_JITTER      0x64                                                  /* Query jitter indicates whether the client receiving Image Notify Command */
#define OTA_UPGRADE_CURRENT_TIME      0x12345                                               /* Test current time of ota server, currently zcl time cluster is not supported */
#define OTA_UPGRADE_IMAGE_COUNT       1                                                     /* The number of OTA image for OTA server */
#define OTA_UPGRADE_OFFSET_TIME       5                                                     /* Offset time value in seconds, use as upgrade delay.*/
#define ESP_ZB_PRIMARY_CHANNEL_MASK     (1l << 13)                                          /* Zigbee primary channel mask use in the example */

/* ota_file.bin */
extern const uint8_t ota_file_start[] asm("_binary_ota_file_bin_start");                    /* ota_file corresponds to filename and bin corresponds to filetype */
extern const uint8_t ota_file_end[]   asm("_binary_ota_file_bin_end");                      /* ota_file corresponds to filename and bin corresponds to filetype */

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
