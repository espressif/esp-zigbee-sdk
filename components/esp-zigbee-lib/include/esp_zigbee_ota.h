/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_type.h"
#include "zcl/esp_zigbee_zcl_common.h"

/**
 * @brief The Zigbee ZCL OTA file header struct.
 *
 */
typedef struct esp_zb_ota_file_header_s {
    uint16_t manufacturer_code;                /*!< OTA header manufacturer code */
    uint16_t image_type;                       /*!< Image type value to distinguish the products */
    uint32_t file_version;                     /*!< File version represents the release and build number of the image’s application and stack */
    uint32_t image_size;                       /*!< Total image size in bytes transferred from the server to the client */
} esp_zb_ota_file_header_t;

/**
 * @brief The Zigbee ZCL OTA config struct for server initialize.
 *
 */
typedef struct esp_zb_ota_cfg_s {
    uint8_t endpoint;                                /*!< Server endpoint */
    uint32_t ota_upgrade_time;                       /*!< OTA Upgrade time */
    esp_zb_ota_file_header_t   ota_file_header;      /*!< Config OTA file header */
    uint8_t *ota_data;                               /*!< OTA app data */
} esp_zb_ota_cfg_t;

/********************* Declare functions **************************/

/**
 * @brief   Config OTA server parameters
 *
 * @param[in]  config  pointer to the OTA upgrade parameter @ref esp_zb_ota_upgrade_server_parameter_s
 *
 */
void *esp_zb_ota_server_parameter(esp_zb_ota_upgrade_server_parameter_t *config);

/**
 * @brief   Initialize OTA Upgrade cluster - server part
 *
 * @param[in]  esp_zb_ota_config  pointer to the OTA config @ref esp_zb_ota_cfg_s
 *
 */
void esp_zb_ota_server_init(esp_zb_ota_cfg_t *esp_zb_ota_config);

/**
 * @brief   Start OTA server
 *
 * @note After initialization of server part to insert OTA file to upgrade mechanism
 *
 */
void esp_zb_ota_server_start(void);

/**
 * @brief   Config OTA client parameters
 *
 * @param[in]  config  pointer to the OTA upgrade client parameter @ref esp_zb_ota_upgrade_client_parameter_s
 *
 * @note Currently set timer_counter to default value - to do first OTA request after 1 min
 *
 */
void *esp_zb_ota_client_parameter(esp_zb_ota_upgrade_client_parameter_t *config);

#ifdef __cplusplus
}
#endif
