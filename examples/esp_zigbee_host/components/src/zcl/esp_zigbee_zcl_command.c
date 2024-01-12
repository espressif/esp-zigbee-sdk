/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "esp_host_zb.h"

#include "esp_zigbee_zcl_command.h"

uint8_t esp_zb_zcl_custom_cluster_cmd_req(esp_zb_zcl_custom_cluster_cmd_t *cmd_req)
{
    typedef struct {
        esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                   /*!< Basic command info */
        uint8_t  address_mode;                                  /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
        uint16_t profile_id;                                    /*!< Profile id */
        uint16_t cluster_id;                                    /*!< Cluster id */
        uint16_t custom_cmd_id;                                 /*!< Custom command id */
        uint8_t  direction;                                     /*!< Direction of command */
        uint8_t  type;                                          /*!< The type of attribute, which can refer to esp_zb_zcl_attr_type_t */
        uint16_t size;                                          /*!< The value size of attribute  */
    } ESP_ZNSP_ZB_PACKED_STRUCT esp_host_zb_zcl_data_t;

    uint16_t data_len = sizeof(esp_host_zb_zcl_data_t);
    uint8_t *data = NULL;
    esp_host_zb_zcl_data_t zcl_data = {
        .zcl_basic_cmd = cmd_req->zcl_basic_cmd,
        .address_mode = cmd_req->address_mode,
        .profile_id = cmd_req->profile_id,
        .cluster_id = cmd_req->cluster_id,
        .custom_cmd_id = cmd_req->custom_cmd_id,
        .direction = cmd_req->direction,
        .type = cmd_req->data.type,
        .size = 0,
    };

    switch (cmd_req->data.type) {
        case ESP_ZB_ZCL_ATTR_TYPE_NULL:
            break;
        case ESP_ZB_ZCL_ATTR_TYPE_8BIT:
        case ESP_ZB_ZCL_ATTR_TYPE_BOOL:
        case ESP_ZB_ZCL_ATTR_TYPE_8BITMAP:
        case ESP_ZB_ZCL_ATTR_TYPE_U8:
            zcl_data.size = 1;
            break;
        default:
            break;
    }

    data = calloc(1, data_len + zcl_data.size);
    memcpy(data, &zcl_data, data_len);
    if (cmd_req->data.value && zcl_data.size) {
        memcpy(data + data_len, cmd_req->data.value, zcl_data.size);
        data_len += zcl_data.size;
    }

    uint8_t output = 0;
    uint16_t outlen = sizeof(uint8_t);

    esp_host_zb_output(ESP_ZNSP_ZCL_WRITE, data, data_len, &output, &outlen);
    if (data) {
        free(data);
        data = NULL;
    }

    return ESP_OK;
}
