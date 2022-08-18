/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "esp_zigbee_api_type.h"

/** Enum of the Zigbee secure install code type
 * @note It is formed with 6/8/12/16 bytes IC (install code) + 2 bytes of CRC
 * @anchor esp_zb_secur_ic_type_t
 */
typedef enum {
    ESP_ZB_IC_TYPE_48 =     0x0,                    /*!< Install code total of 8 bytes length */
    ESP_ZB_IC_TYPE_64  =    0x1,                    /*!< Install code total of 10 bytes length */
    ESP_ZB_IC_TYPE_96 =     0x2,                    /*!< Install code total of 14 bytes length */
    ESP_ZB_IC_TYPE_128 =    0x3,                    /*!< Install code total of 18 bytes length */
    ESP_ZB_IC_TYPE_MAX =    0x4                     /*!< Unknown type */
} esp_zb_secur_ic_type_t;
/********************* Declare functions **************************/

/**
 * @brief   Get the Zigbee install code from storage
 *
 * @warning  Only for the non-Trust Center device (non Zigbee coordinator)!
 * @note     Called only after esp_zb_start(), otherwise no install code has been set from
 * production config refer to tools/mfg_tool
 *
 * @param[out]  ic_type  A pointer of install code type @ref esp_zb_secur_ic_type_t
 *
 * @return A pointer to the install code
 *
 */
uint8_t *esp_zb_secur_ic_get(uint8_t *ic_type);

/**
 * @brief   Add the Zigbee install code from remote device
 *
 * @warning  Only for the Trust Center device (Zigbee coordinator)!
 *
 * @param[in]  address  A 64-bit ieee address of the remote device composed by array of zb_uint8_t
 * @param[in]  ic_str  A string of the install code
 *
 * @return -ESP_OK on success
 */
esp_err_t esp_zb_secur_ic_str_add(esp_zb_ieee_addr_t address, char *ic_str);

/**
 * @brief   Set the Zigbee install code from character string
 *
 * @note if user wants to manually set install code instead of from production config refer to esp-zigbee-sdk/tools/mfg_tool
 *
 * @warning  Only for the non-Trust Center device (non Zigbee coordinator)!
 *
 * @param[in]  ic_str  A string of the install code
 *
 * @return - ESP_OK on success
 *
 */
esp_err_t esp_zb_secur_ic_str_set(char *ic_str);

/**
 * @brief   Add the Zigbee install code of a remote device with type
 *
 * @warning  Only for the Trust Center device (Zigbee coordinator)!
 *
 * @param[in]  address  A 64-bit ieee address of the remote device composed by array of zb_uint8_t
 * @param[in]  ic_type A install code type @ref esp_zb_secur_ic_type_t
 * @param[in]  ic  A pointer of data array for install code
 *
 */
esp_err_t esp_zb_secur_ic_add(esp_zb_ieee_addr_t address, uint8_t ic_type, uint8_t *ic);

/**
 * @brief   Set the Zigbee install code for a Zigbee device with type
 *
 * @note if user wants to set install code with type manually instead of from production config check esp-zigbee-sdk/tools/mfg_tool
 *
 * @warning  Only for the non-Trust Center device (non Zigbee coordinator)!
 *
 * @param[in]  ic_type A install code type @ref esp_zb_secur_ic_type_t
 * @param[in]  ic  A pointer of data array for install code
 *
 * @return - ESP_OK on success
 *
 */
esp_err_t esp_zb_secur_ic_set(uint8_t ic_type, uint8_t *ic);

/**
 * @brief   remove the Zigbee install code of a specific device
 *
 * @warning  Only for the Trust Center device (Zigbee coordinator)!
 *
 * @param[in]  address device ieee addressing to remove ic
 * @return - ESP_OK on success
 */
esp_err_t esp_zb_secur_ic_remove_req(esp_zb_ieee_addr_t address);

/**
 * @brief   remove the Zigbee ALL install code
 *
 * @warning  Only for the Trust Center device (Zigbee coordinator)!
 *
 * @return - ESP_OK on success
 */
esp_err_t esp_zb_secur_ic_remove_all_req(void);

#ifdef __cplusplus
}
#endif
