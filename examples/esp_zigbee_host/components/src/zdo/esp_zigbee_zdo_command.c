
/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "esp_host_zb.h"

#include "esp_zigbee_zcl_common.h"
#include "esp_zigbee_zdo_command.h"

void esp_zb_zdo_device_bind_req(esp_zb_zdo_bind_req_param_t *cmd_req, esp_zb_zdo_bind_callback_t user_cb, void *user_ctx)
{
    uint8_t output = 0;
    uint16_t outlen = sizeof(uint8_t);

    typedef struct {
        esp_zb_zdo_bind_req_param_t bind_req;
        esp_zb_user_cb_t            bind_usr;
    } esp_zb_zdo_bind_req_t;

    esp_zb_zdo_bind_req_t zdo_data = {
        .bind_usr = {
            .user_ctx = (uint32_t)user_ctx,
            .user_cb = (uint32_t)user_cb,
        },
    };

    memcpy(&zdo_data.bind_req, cmd_req, sizeof(esp_zb_zdo_bind_req_param_t));
    esp_host_zb_output(ESP_ZNSP_ZDO_BIND_SET, &zdo_data, sizeof(esp_zb_zdo_bind_req_t), &output, &outlen);
}

void esp_zb_zdo_device_unbind_req(esp_zb_zdo_bind_req_param_t *cmd_req, esp_zb_zdo_bind_callback_t user_cb, void *user_ctx)
{
    uint8_t output = 0;
    uint16_t outlen = sizeof(uint8_t);

    typedef struct {
        esp_zb_zdo_bind_req_param_t bind_req;
        esp_zb_user_cb_t            bind_usr;
    } esp_zb_zdo_bind_req_t;

    esp_zb_zdo_bind_req_t zdo_data = {
        .bind_usr = {
            .user_ctx = (uint32_t)user_ctx,
            .user_cb = (uint32_t)user_cb,
        },
    };

    memcpy(&zdo_data.bind_req, cmd_req, sizeof(esp_zb_zdo_bind_req_param_t));
    esp_host_zb_output(ESP_ZNSP_ZDO_UNBIND_SET, &zdo_data, sizeof(esp_zb_zdo_bind_req_t), &output, &outlen);
}

void esp_zb_zdo_find_on_off_light(esp_zb_zdo_match_desc_req_param_t *cmd_req, esp_zb_zdo_match_desc_callback_t user_cb, void *user_ctx)
{
    uint16_t cluster_list[] = {ESP_ZB_ZCL_CLUSTER_ID_ON_OFF, ESP_ZB_ZCL_CLUSTER_ID_ON_OFF};
    esp_zb_zdo_match_desc_req_param_t on_off_req = {
        .dst_nwk_addr = cmd_req->dst_nwk_addr,
        .addr_of_interest = cmd_req->addr_of_interest,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .num_in_clusters = 1,
        .num_out_clusters = 1,
        .cluster_list = cluster_list,
    };

    esp_zb_zdo_match_cluster(&on_off_req, user_cb, user_ctx);
}

esp_err_t esp_zb_zdo_match_cluster(esp_zb_zdo_match_desc_req_param_t *param, esp_zb_zdo_match_desc_callback_t user_cb, void *user_ctx)
{
    uint8_t output = 0;
    uint16_t outlen = sizeof(uint8_t);

    typedef struct {
        esp_zb_user_cb_t find_usr;
        uint16_t dst_nwk_addr;              /*!< NWK address that request sent to */
        uint16_t addr_of_interest;          /*!< NWK address of interest */
        uint16_t profile_id;                /*!< Profile ID to be match at the destination which refers to esp_zb_af_profile_id_t */
        uint8_t num_in_clusters;            /*!< The number of input clusters provided for matching cluster server */
        uint8_t num_out_clusters;           /*!< The number of output clusters provided for matching cluster client */
    } __attribute__ ((packed)) esp_zb_zdo_match_desc_t;

    esp_zb_zdo_match_desc_t zdo_data = {
        .find_usr = {
            .user_cb = (uint32_t)user_cb,
            .user_ctx = (uint32_t)user_ctx,
        },
        .dst_nwk_addr = param->dst_nwk_addr,
        .addr_of_interest = param->addr_of_interest,
        .profile_id = param->profile_id,
        .num_in_clusters = param->num_in_clusters,
        .num_out_clusters = param->num_out_clusters,
    };
    uint16_t clusters_len = (param->num_in_clusters + param->num_out_clusters) * sizeof(uint16_t);
    uint16_t inlen = sizeof(esp_zb_zdo_match_desc_t) + clusters_len;
    uint8_t  *input = calloc(1, inlen);
    if (input) {
        memcpy(input, &zdo_data, sizeof(esp_zb_zdo_match_desc_t));
        if (param->cluster_list && clusters_len) {
            memcpy(input + sizeof(esp_zb_zdo_match_desc_t), param->cluster_list, clusters_len);
        }

        esp_host_zb_output(ESP_ZNSP_ZDO_FIND_MATCH, input, inlen, &output, &outlen);

        free(input);
        input = NULL;
    }

    return ESP_OK;
}

const char *esp_zb_zdo_signal_to_string(esp_zb_app_signal_type_t signal)
{
    return "The signal type of Zigbee";
}
