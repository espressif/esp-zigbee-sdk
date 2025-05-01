/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "esp_host_zb.h"

#include "esp_zigbee_core.h"
#include "esp_zigbee_zcl_command.h"

esp_err_t esp_zb_bdb_start_top_level_commissioning(uint8_t mode_mask)
{
    return ESP_OK;
}

void esp_zb_scheduler_alarm(esp_zb_callback_t cb, uint8_t param, uint32_t time)
{

}

esp_err_t esp_zb_set_primary_network_channel_set(uint32_t channel_mask)
{
    uint8_t output = 0;
    uint16_t outlen = sizeof(uint8_t);

    esp_host_zb_output(ESP_ZNSP_NETWORK_PRIMARY_CHANNEL_SET, &channel_mask, sizeof(uint32_t), &output, &outlen);

    return ESP_OK;
}

void esp_zb_init(esp_zb_cfg_t *nwk_cfg)
{
    uint8_t output = 0;
    uint16_t outlen = sizeof(uint8_t);

    esp_host_zb_output(ESP_ZNSP_NETWORK_INIT, NULL, 0, &output, &outlen);
    esp_zb_app_signal_msg_t signal_msg = {
        .signal = ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP,
        .msg = NULL,
    };

    esp_zb_app_signal_t app_signal = {
        .p_app_signal = (uint32_t *)&signal_msg,
        .esp_err_status = (output == ESP_ZNSP_SUCCESS) ? ESP_OK : ESP_ERR_INVALID_ARG,
    };

    esp_zb_app_signal_handler(&app_signal);

    esp_host_zb_output(ESP_ZNSP_NETWORK_FORMNETWORK, nwk_cfg, sizeof(esp_zb_cfg_t), &output, &outlen);
}

esp_err_t esp_zb_start(bool autostart)
{
    uint8_t output = 0;
    uint16_t outlen = sizeof(uint8_t);

    esp_host_zb_output(ESP_ZNSP_NETWORK_START, &autostart, sizeof(bool), &output, &outlen);

    return ESP_OK;
}

uint16_t esp_zb_get_short_address(void)
{
    uint16_t output = 0;
    uint16_t outlen = sizeof(uint16_t);
    
    esp_host_zb_output(ESP_ZNSP_NETWORK_SHORT_ADDRESS_GET, NULL, 0, &output, &outlen);

    return output;
}

void esp_zb_get_long_address(esp_zb_ieee_addr_t addr)
{
    uint16_t outlen = sizeof(esp_zb_ieee_addr_t);

    esp_host_zb_output(ESP_ZNSP_NETWORK_LONG_ADDRESS_GET, NULL, 0, addr, &outlen);
}

uint16_t esp_zb_address_short_by_ieee(esp_zb_ieee_addr_t address)
{
    uint16_t output = 0;
    uint16_t outlen = sizeof(uint16_t);

    esp_host_zb_output(ESP_ZNSP_NETWORK_IEEE_TO_SHORT, address, sizeof(esp_zb_ieee_addr_t), &output, &outlen);

    return output;
}

esp_err_t esp_zb_ieee_address_by_short(uint16_t short_addr, uint8_t *ieee_addr)
{
    uint16_t outlen = sizeof(esp_zb_ieee_addr_t);

    esp_host_zb_output(ESP_ZNSP_NETWORK_SHORT_TO_IEEE, &short_addr, sizeof(uint16_t), ieee_addr, &outlen);

    return ESP_OK;
}

uint16_t esp_zb_get_pan_id(void)
{
    uint16_t output = 0;
    uint16_t outlen = sizeof(uint16_t);

    esp_host_zb_output(ESP_ZNSP_NETWORK_PAN_ID_GET, NULL, 0, &output, &outlen);

    return output;
}

void esp_zb_get_extended_pan_id(esp_zb_ieee_addr_t ext_pan_id)
{
    uint16_t outlen = sizeof(esp_zb_ieee_addr_t);

    esp_host_zb_output(ESP_ZNSP_NETWORK_EXTENDED_PAN_ID_GET, NULL, 0, ext_pan_id, &outlen);
}

uint8_t esp_zb_get_current_channel(void)
{
    uint8_t output = 0;
    uint16_t outlen = sizeof(uint8_t);

    esp_host_zb_output(ESP_ZNSP_NETWORK_CHANNEL_GET, NULL, 0, &output, &outlen);

    return output;
}
