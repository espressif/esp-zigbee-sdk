/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_system.h"
#include "esp_random.h"

#include "esp_zigbee_core.h"
#include "zdo/esp_zigbee_zdo_command.h"
#include "zcl/esp_zigbee_zcl_common.h"
#include "aps/esp_zigbee_aps.h"

#include "esp_ncp_bus.h"
#include "esp_ncp_frame.h"
#include "esp_ncp_main.h"
#include "esp_ncp_zb.h"
#include "esp_zb_ncp.h"

static const char *TAG = "ESP_NCP_ZB";

static bool s_init_flag = false;
static bool s_start_flag = false;
static uint32_t s_primary_channel = 0;
static QueueHandle_t s_aps_data_confirm;    /*!< The queue handler for sync between the host and NCP */
static QueueHandle_t s_aps_data_indication; /*!< The queue handler for sync between the host and NCP */

#define ESP_NCP_ZB_STATUS()                 \
{                                           \
    *output = calloc(1, sizeof(uint8_t));   \
    if (*output) {                          \
        *outlen = sizeof(uint8_t);          \
        memcpy(*output, &status, *outlen);  \
    } else {                                \
        ret = ESP_ERR_NO_MEM;               \
    }                                       \
}                                           \

typedef struct {
    uint16_t  cluster_id;
    esp_err_t (*add_cluster_fn)(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);
    esp_err_t (*del_cluster_fn)(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);
} esp_ncp_zb_cluster_fn_t;

typedef struct {
    uint16_t        id;                     /*!< Frame id on the event */
    uint16_t        size;                   /*!< Data size on the event */
    void            *data;                  /*!< Data on the event */
} esp_ncp_zb_ctx_t;

static esp_err_t esp_ncp_zb_aps_data_handle(uint16_t id, const void *buffer, uint16_t len)
{
    QueueHandle_t event_queue = (id == ESP_NCP_APS_DATA_CONFIRM) ? s_aps_data_confirm : s_aps_data_indication;
    if (event_queue) {
        BaseType_t ret = 0;
        esp_ncp_zb_ctx_t ncp_ctx = {
            .id = id,
            .size = len,
        };

        if (buffer) {
            ncp_ctx.data = calloc(1, len);
            memcpy(ncp_ctx.data, buffer, len);
        }

        if (xPortInIsrContext() == pdTRUE) {
            ret = xQueueSendFromISR(event_queue, &ncp_ctx, NULL);
        } else {
            ret = xQueueSend(event_queue, &ncp_ctx, 0);
        }
        return (ret == pdTRUE) ? ESP_OK : ESP_FAIL ;
    } else {
        esp_ncp_header_t ncp_header = {
            .sn = esp_random() % 0xFF,
            .id = id,
        };
        return esp_ncp_noti_input(&ncp_header, buffer, len);
    }
}

static bool esp_ncp_zb_aps_data_indication_handler(esp_zb_apsde_data_ind_t ind)
{
    typedef struct {
        uint8_t states;                     /*!< The states of the device */
        uint8_t dst_addr_mode;              /*!< Reserved, the addressing mode for the destination address used in this primitive and of the APDU that has been received.*/
        esp_zb_addr_u dst_addr;             /*!< The individual device address or group address to which the ASDU is directed.*/
        uint8_t dst_endpoint;               /*!< The target endpoint on the local entity to which the ASDU is directed.*/
        uint8_t src_addr_mode;              /*!< Reserved, The addressing mode for the source address used in this primitive and of the APDU that has been received.*/
        esp_zb_addr_u src_addr;             /*!< The individual device address of the entity from which the ASDU has been received.*/
        uint8_t src_endpoint;               /*!< The number of the individual endpoint of the entity from which the ASDU has been received.*/
        uint16_t profile_id;                /*!< The identifier of the profile from which this frame originated.*/
        uint16_t cluster_id;                /*!< The identifier of the received object.*/
        uint8_t indication_status;          /*!< The status of the incoming frame processing, 0: on success */
        uint8_t security_status;            /*!< UNSECURED if the ASDU was received without any security. SECURED_NWK_KEY if the received ASDU was secured with the NWK key.*/
        uint8_t lqi;                        /*!< The link quality indication delivered by the NLDE.*/
        int rx_time;                        /*!< Reserved, a time indication for the received packet based on the local clock */
        uint32_t asdu_length;               /*!< The number of octets comprising the ASDU being indicated by the APSDE.*/
    } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_aps_data_ind_t;

    uint16_t outlen = sizeof(esp_ncp_zb_aps_data_ind_t) + ind.asdu_length;
    uint8_t *output = calloc(1, outlen);
    if (!output) {
        return false;
    }

    esp_ncp_zb_aps_data_ind_t *aps_data = (esp_ncp_zb_aps_data_ind_t *)output;
    aps_data->dst_addr_mode = ind.dst_addr_mode;
    if (ind.dst_addr_mode == ESP_ZB_APS_ADDR_MODE_64_ENDP_PRESENT) {
        memcpy(aps_data->dst_addr.addr_long, &ind.dst_short_addr, sizeof(esp_zb_ieee_addr_t));
    } else {
        aps_data->dst_addr.addr_short = ind.dst_short_addr;
    }
    aps_data->dst_endpoint = ind.dst_endpoint;

    aps_data->src_addr_mode = ind.src_addr_mode;
    if (ind.src_addr_mode == ESP_ZB_APS_ADDR_MODE_64_ENDP_PRESENT) {
        memcpy(aps_data->src_addr.addr_long, &ind.src_short_addr, sizeof(esp_zb_ieee_addr_t));
    } else {
        aps_data->src_addr.addr_short = ind.src_short_addr;
    }
    aps_data->src_endpoint = ind.src_endpoint;

    aps_data->states = ESP_NCP_INDICATION;
    aps_data->profile_id = ind.profile_id;
    aps_data->cluster_id = ind.cluster_id;

    aps_data->indication_status = ind.status;
    aps_data->security_status   = ind.security_status;
    aps_data->lqi = ind.lqi;
    aps_data->rx_time = ind.rx_time;

    aps_data->asdu_length = ind.asdu_length;
    if (ind.asdu && ind.asdu_length) {
        memcpy(output + sizeof(esp_ncp_zb_aps_data_ind_t), ind.asdu, ind.asdu_length);
    }

    esp_ncp_zb_aps_data_handle(ESP_NCP_APS_DATA_INDICATION, output, outlen);
    free(output);
    output = NULL;

    ESP_LOGI(TAG, "%s %d", __func__, __LINE__);
    return s_aps_data_indication ? true : false;
}

static void esp_ncp_zb_aps_data_confirm_handler(esp_zb_apsde_data_confirm_t confirm)
{
    typedef struct {
        uint8_t states;                     /*!< The states of the device */
        uint8_t dst_addr_mode;              /*!< The addressing mode for the destination address used in this primitive and of the APDU to be transferred.*/
        esp_zb_zcl_basic_cmd_t basic_cmd;   /*!< Basic command info */
        int tx_time;                        /*!< Reserved */
        uint8_t  confirm_status;            /*!< The status of data confirm. 0: success, otherwise failed */
        uint32_t asdu_length;               /*!< The length of ASDU*/
    } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_aps_data_confirm_t;

    uint16_t outlen = sizeof(esp_ncp_zb_aps_data_confirm_t) + confirm.asdu_length;
    uint8_t *output = calloc(1, outlen);
    if (!output) {
        return;
    }

    esp_ncp_zb_aps_data_confirm_t *aps_data = (esp_ncp_zb_aps_data_confirm_t *)output;
    memcpy(&aps_data->basic_cmd.dst_addr_u, &confirm.dst_addr, sizeof(esp_zb_addr_u));
    aps_data->basic_cmd.dst_endpoint = confirm.dst_endpoint;
    aps_data->basic_cmd.src_endpoint = confirm.src_endpoint;
    aps_data->dst_addr_mode = confirm.dst_addr_mode;

    aps_data->states = ESP_NCP_CONFIRM;
    aps_data->tx_time = confirm.tx_time;
    aps_data->confirm_status = confirm.status;
    aps_data->asdu_length = confirm.asdu_length;

    if (confirm.asdu && confirm.asdu_length) {
        memcpy(output + sizeof(esp_ncp_zb_aps_data_confirm_t), confirm.asdu, confirm.asdu_length);
    }

    esp_ncp_zb_aps_data_handle(ESP_NCP_APS_DATA_CONFIRM, output, outlen);
    free(output);
    output = NULL;

    ESP_LOGI(TAG, "%s %d", __func__, __LINE__);
}

static void esp_ncp_zb_bdb_start_top_level_commissioning_cb(uint8_t mode_mask)
{
    ESP_RETURN_ON_FALSE(esp_zb_bdb_start_top_level_commissioning(mode_mask) == ESP_OK, , TAG, "Failed to start Zigbee bdb commissioning");
}

static void esp_ncp_zb_bind_cb(esp_zb_zdp_status_t zdo_status, void *user_ctx)
{
    esp_ncp_header_t ncp_header = { 
        .sn = esp_random() % 0xFF,
        .id = ESP_NCP_ZDO_BIND_SET,
    };

    typedef struct {
        esp_zb_zdp_status_t    zdo_status;
        esp_ncp_zb_user_cb_t   zdo_cb;                   /*!< A ZDO match desc request callback */
    } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_bind_parameters_t;

    esp_ncp_zb_bind_parameters_t parameters = { 
        .zdo_status = zdo_status,
    };

    if (user_ctx) {
        memcpy(&parameters.zdo_cb, user_ctx, sizeof(esp_ncp_zb_user_cb_t));
        free(user_ctx);
    }

    esp_ncp_noti_input(&ncp_header, &parameters, sizeof(esp_ncp_zb_bind_parameters_t));
}

static void esp_ncp_zb_unbind_cb(esp_zb_zdp_status_t zdo_status, void *user_ctx)
{
    esp_ncp_header_t ncp_header = { 
        .sn = esp_random() % 0xFF,
        .id = ESP_NCP_ZDO_UNBIND_SET,
    };

    typedef struct {
        esp_zb_zdp_status_t    zdo_status;
        esp_ncp_zb_user_cb_t   zdo_cb;                   /*!< A ZDO match desc request callback */
    } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_unbind_parameters_t;

    esp_ncp_zb_unbind_parameters_t parameters = { 
        .zdo_status = zdo_status,
    };

    if (user_ctx) {
        memcpy(&parameters.zdo_cb, user_ctx, sizeof(esp_ncp_zb_user_cb_t));
        free(user_ctx);
    }

    esp_ncp_noti_input(&ncp_header, &parameters, sizeof(esp_ncp_zb_unbind_parameters_t));
}

static void esp_ncp_zb_find_match_cb(esp_zb_zdp_status_t zdo_status, uint16_t addr, uint8_t endpoint, void *user_ctx)
{
    esp_ncp_header_t ncp_header = {
        .sn = esp_random() % 0xFF,
        .id = ESP_NCP_ZDO_FIND_MATCH,
    };

    typedef struct {
        esp_zb_zdp_status_t    zdo_status;
        uint16_t               addr;
        uint8_t                endpoint;
        esp_ncp_zb_user_cb_t   zdo_cb;                   /*!< A ZDO match desc request callback */
    } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_find_parameters_t;

    esp_ncp_zb_find_parameters_t parameters = {
        .zdo_status = zdo_status,
        .addr = addr,
        .endpoint = endpoint,
    };

    if (user_ctx) {
        memcpy(&parameters.zdo_cb, user_ctx, sizeof(esp_ncp_zb_user_cb_t));
        free(user_ctx);
    }

    esp_ncp_noti_input(&ncp_header, &parameters, sizeof(esp_ncp_zb_find_parameters_t));
}

static void esp_ncp_zb_zdo_scan_complete_handler(esp_zb_zdp_status_t zdo_status, uint8_t count, esp_zb_network_descriptor_t *nwk_descriptor)
{
    esp_ncp_header_t ncp_header = {
        .sn = esp_random() % 0xFF,
        .id = ESP_NCP_NETWORK_SCAN_COMPLETE_HANDLER
    };

    typedef struct {
        esp_zb_zdp_status_t    zdo_status;
        uint8_t                count;
    } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_scan_parameters_t;

    uint16_t outlen = sizeof(esp_ncp_zb_scan_parameters_t) + (count * sizeof(esp_zb_network_descriptor_t));
    uint8_t *output = calloc(1, outlen);

    if (output) {
        esp_ncp_zb_scan_parameters_t *scan_data = (esp_ncp_zb_scan_parameters_t *)output;
        scan_data->zdo_status = zdo_status;
        scan_data->count = count;

        if (nwk_descriptor && count) {
            memcpy(scan_data + sizeof(esp_ncp_zb_scan_parameters_t), nwk_descriptor, (count * sizeof(esp_zb_network_descriptor_t)));
        }

        esp_ncp_noti_input(&ncp_header, output, outlen);
        free(output);
        output = NULL;
    }
}

static esp_err_t esp_ncp_zb_read_attr_resp_handler(const esp_zb_zcl_cmd_read_attr_resp_message_t *message, uint8_t **output, uint16_t *outlen)
{
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);
    ESP_LOGI(TAG, "Read attribute response: status(%d), cluster(0x%x)", message->info.status, message->info.cluster);
    
    uint16_t data_head_len = sizeof(esp_zb_zcl_cmd_info_t);
    uint16_t id_len = sizeof(uint16_t), TYPE_LEN = sizeof(esp_zb_zcl_attr_type_t), SIZE_LEN = sizeof(uint8_t);
    uint8_t index = 0;
    uint16_t length = (data_head_len + 1);
    uint8_t *outbuf = calloc(1, length);
    uint8_t *variables_data = NULL;
    uint8_t  variables_data_len = 0;
    uint8_t  variables_len = (id_len + TYPE_LEN + SIZE_LEN);

    if (outbuf) {
        memcpy(outbuf, &message->info, data_head_len);
        for (esp_zb_zcl_read_attr_resp_variable_t *variables = message->variables; variables != NULL; variables = variables->next) {
            ESP_LOGI(TAG, "attribute(0x%x), type(0x%x), value(%d)", variables->attribute.id, variables->attribute.data.type, variables->attribute.data.value ? *(uint8_t *)variables->attribute.data.value : 0);
            
            variables_data_len = (variables_len + variables->attribute.data.size);
            length += variables_data_len;
            
            outbuf = realloc(outbuf, length);
            variables_data = &outbuf[length - variables_data_len];

            memcpy(variables_data, &variables->attribute.id, variables_len);
            variables_data += variables_len;

            memcpy(variables_data, variables->attribute.data.value, variables->attribute.data.size);
            index ++;
        }
        outbuf[data_head_len] = index;
    }

    *output = outbuf;
    *outlen = length;

    return ESP_OK;
}

static esp_err_t esp_ncp_zb_write_attr_resp_handler(const esp_zb_zcl_cmd_write_attr_resp_message_t *message, uint8_t **output, uint16_t *outlen)
{
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);
    
    ESP_LOGI(TAG, "Write attribute response: status(%d), cluster(0x%x)", message->info.status, message->info.cluster);

    uint16_t data_head_len = sizeof(esp_zb_zcl_cmd_info_t);
    uint16_t id_len = sizeof(uint16_t), status_len = sizeof(esp_zb_zcl_status_t);
    uint8_t index = 0;
    uint16_t length = (data_head_len + 1);
    uint8_t *outbuf = calloc(1, length);
    uint8_t variables_data_len = (id_len + status_len);

    if (outbuf) {
        memcpy(outbuf, &message->info, data_head_len);
        for (esp_zb_zcl_write_attr_resp_variable_t *variables = message->variables; variables != NULL; variables = variables->next) {
            ESP_LOGI(TAG, "status(0x%x), attribute(0x%x)", variables->status, variables->attribute_id);
            length += variables_data_len;
            
            outbuf = realloc(outbuf, length);
            memcpy(&outbuf[length - variables_data_len], &variables->status, variables_data_len);

            index ++;
        }
        outbuf[data_head_len] = index;
    }

    *output = outbuf;
    *outlen = length;

    return ESP_OK;
}

static esp_err_t esp_ncp_zb_report_configure_resp_handler(const esp_zb_zcl_cmd_config_report_resp_message_t *message, uint8_t **output, uint16_t *outlen)
{
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);
    ESP_LOGI(TAG, "Configure report response: status(%d), cluster(0x%x)", message->info.status, message->info.cluster);

    uint16_t data_head_len = sizeof(esp_zb_zcl_cmd_info_t);
    uint16_t id_len = sizeof(uint16_t), status_len = sizeof(esp_zb_zcl_status_t), direction_len = sizeof(uint8_t);
    uint8_t index = 0;
    uint16_t length = (data_head_len + 1);
    uint8_t *outbuf = calloc(1, length);
    uint8_t variables_data_len = (status_len + direction_len + id_len);

    if (outbuf) {
        memcpy(outbuf, &message->info, data_head_len);
        for (esp_zb_zcl_config_report_resp_variable_t *variables = message->variables; variables != NULL; variables = variables->next) {
            ESP_LOGI(TAG, "status(0x%x), direction(%d), attribute(0x%x)", variables->status, variables->direction, variables->attribute_id);
            length += variables_data_len;

            outbuf = realloc(outbuf, length);
            memcpy(&outbuf[length - variables_data_len], &variables->status, variables_data_len);

            index ++;
        }
        outbuf[data_head_len] = index;
    }

    *output = outbuf;
    *outlen = length;

    return ESP_OK;
}

static esp_err_t esp_ncp_zb_disc_attr_resp_handler(const esp_zb_zcl_cmd_discover_attributes_resp_message_t *message, uint8_t **output, uint16_t *outlen)
{
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->info.status);
    
    ESP_LOGI(TAG, "Discover attribute response: status(%d), cluster(0x%x)", message->info.status, message->info.cluster);

    uint16_t data_head_len = sizeof(esp_zb_zcl_cmd_info_t);
    uint16_t id_len = sizeof(uint16_t), status_len = sizeof(esp_zb_zcl_attr_type_t);
    uint8_t index = 0;
    uint16_t length = (data_head_len + 1);
    uint8_t *outbuf = calloc(1, length);
    uint8_t variables_data_len = (id_len + status_len);

    if (outbuf) {
        memcpy(outbuf, &message->info, data_head_len);
        for (esp_zb_zcl_disc_attr_variable_t *variables = message->variables; variables != NULL; variables = variables->next) {
            ESP_LOGI(TAG, "attribute(0x%x), data_type(0x%0x)", variables->attr_id, variables->data_type);
            length += variables_data_len;
            
            outbuf = realloc(outbuf, length);
            memcpy(&outbuf[length - variables_data_len], &variables->attr_id, variables_data_len);

            index ++;
        }
        outbuf[data_head_len] = index;
    }

    *output = outbuf;
    *outlen = length;

    return ESP_OK;
}

static esp_err_t esp_ncp_zb_report_attr_handler(const esp_zb_zcl_report_attr_message_t *message, uint8_t **output, uint16_t *outlen)
{
    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG, "Received message: error status(%d)",
                        message->status);
    ESP_LOGI(TAG, "Reveived report from address(0x%x) src endpoint(%d) to dst endpoint(%d) cluster(0x%x)", message->src_address.u.short_addr,
             message->src_endpoint, message->dst_endpoint, message->cluster);
    
    ESP_LOGI(TAG, "Received report information: attribute(0x%x), type(0x%x), value(%d)\n", message->attribute.id, message->attribute.data.type,
             message->attribute.data.value ? *(uint8_t *)message->attribute.data.value : 0);

    typedef struct {
        esp_zb_zcl_status_t status;       /*!< The status of the report attribute response, which can refer to esp_zb_zcl_status_t */
        esp_zb_zcl_addr_t src_address;    /*!< The struct of address contains short and ieee address, which can refer to esp_zb_zcl_addr_s */
        uint8_t src_endpoint;             /*!< The endpoint id which comes from report device */
        uint8_t dst_endpoint;             /*!< The destination endpoint id */
        uint16_t cluster;                 /*!< The cluster id that reported */
    } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_report_attr_t;

    typedef struct {
        uint16_t id;                                    /*!< The identify of attribute */
        uint8_t  type;                                  /*!< The type of attribute, which can refer to esp_zb_zcl_attr_type_t */
        uint8_t  size;                                  /*!< The value size of attribute  */
    } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_attr_data_t;

    uint16_t data_head_len = sizeof(esp_ncp_zb_report_attr_t);
    uint16_t attr_head_len = sizeof(esp_ncp_zb_attr_data_t);
    uint16_t length = data_head_len + attr_head_len + message->attribute.data.size;
    uint8_t *outbuf = calloc(1, length);

    if (outbuf) {
        memcpy(outbuf, message, data_head_len + attr_head_len);
        if (message->attribute.data.value) {
            memcpy(outbuf + data_head_len + attr_head_len, message->attribute.data.value, message->attribute.data.size);
        }
    }

    *output = outbuf;
    *outlen = length;

    return ESP_OK;
}

static esp_err_t esp_ncp_zb_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
{
    esp_err_t ret = ESP_OK;
    esp_ncp_header_t ncp_header = { 
        .sn = esp_random() % 0xFF,
    };
    uint8_t *output = NULL;
    uint16_t outlen = 0;

    switch (callback_id) {
        case ESP_ZB_CORE_CMD_READ_ATTR_RESP_CB_ID:
            ncp_header.id = ESP_NCP_ZCL_ATTR_READ;
            ret = esp_ncp_zb_read_attr_resp_handler((esp_zb_zcl_cmd_read_attr_resp_message_t *)message, &output, &outlen);
            break;
        case ESP_ZB_CORE_CMD_WRITE_ATTR_RESP_CB_ID:
            ncp_header.id = ESP_NCP_ZCL_ATTR_WRITE;
            ret = esp_ncp_zb_write_attr_resp_handler((esp_zb_zcl_cmd_write_attr_resp_message_t *)message, &output, &outlen);
            break;
        case ESP_ZB_CORE_CMD_REPORT_CONFIG_RESP_CB_ID:
            ncp_header.id = ESP_NCP_ZCL_REPORT_CONFIG;
            ret = esp_ncp_zb_report_configure_resp_handler((esp_zb_zcl_cmd_config_report_resp_message_t *)message, &output, &outlen);
            break;
        case ESP_ZB_CORE_CMD_DISC_ATTR_RESP_CB_ID:
            ncp_header.id = ESP_NCP_ZCL_ATTR_DISC;
            ret = esp_ncp_zb_disc_attr_resp_handler((esp_zb_zcl_cmd_discover_attributes_resp_message_t *)message, &output, &outlen);
            break;
        case ESP_ZB_CORE_REPORT_ATTR_CB_ID:
            ncp_header.id = ESP_NCP_ZCL_ATTR_REPORT;
            ret = esp_ncp_zb_report_attr_handler((esp_zb_zcl_report_attr_message_t *)message, &output, &outlen);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
    }

    if (output) {
        esp_ncp_noti_input(&ncp_header, output, outlen);
        free(output);
        output = NULL;
    }

    return ret;
}

static void esp_ncp_zb_task(void *pvParameters)
{
    esp_zb_core_action_handler_register(esp_ncp_zb_action_handler);
    esp_zb_main_loop_iteration();
    vTaskDelete(NULL);
}

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p       = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    esp_zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;
    esp_zb_zdo_signal_leave_indication_params_t *dev_leave_params = NULL;
    esp_ncp_header_t ncp_header = { 
        .sn = esp_random() % 0xFF,
    };
    switch (sig_type) {
        case ESP_ZB_ZDO_SIGNAL_DEFAULT_START:
            break;
        case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
            ESP_LOGI(TAG, "Initialize Zigbee stack");
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_INITIALIZATION);
            break;
        case ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE:
            dev_annce_params = (esp_zb_zdo_signal_device_annce_params_t *)esp_zb_app_signal_get_params(p_sg_p);
            ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->device_short_addr);
            ncp_header.id = ESP_NCP_NETWORK_JOINNETWORK;
            esp_ncp_noti_input(&ncp_header, dev_annce_params, sizeof(esp_zb_zdo_signal_device_annce_params_t));
            break;
        case ESP_ZB_ZDO_SIGNAL_LEAVE:
            dev_leave_params = (esp_zb_zdo_signal_leave_indication_params_t *)esp_zb_app_signal_get_params(p_sg_p);
            ESP_LOGI(TAG, "Leave Indication parameters (short: 0x%04hx)", dev_leave_params->short_addr);
            ncp_header.id = ESP_NCP_NETWORK_LEAVENETWORK;
            esp_ncp_noti_input(&ncp_header, dev_leave_params, sizeof(esp_zb_zdo_signal_leave_indication_params_t));
            break;
        case ESP_ZB_ZDO_SIGNAL_ERROR:
            break;
        case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
        case ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT:
            if (err_status == ESP_OK) {
                ESP_LOGI(TAG, "Start network formation");
                esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_FORMATION);
            } else {
                ESP_LOGE(TAG, "Failed to initialize Zigbee stack (status: %s)", esp_err_to_name(err_status));
            }
            break;
        case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_STARTED:
        case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK_JOINED_ROUTER:
        case ESP_ZB_BDB_SIGNAL_TOUCHLINK:
            break;
        case ESP_ZB_BDB_SIGNAL_STEERING:
            if (err_status == ESP_OK) {
                ESP_LOGI(TAG, "Network steering started");
            }
            break;
        case ESP_ZB_BDB_SIGNAL_FORMATION:
            if (err_status == ESP_OK) {
                esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_STEERING);

                typedef struct {
                    esp_zb_ieee_addr_t  extendedPanId;                      /*!< The network's extended PAN identifier */
                    uint16_t            panId;                              /*!< The network's PAN identifier */
                    uint8_t             radioChannel;                       /*!< A radio channel */
                } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_formnetwork_parameters_t;

                esp_ncp_zb_formnetwork_parameters_t parameters = { 
                    .panId = esp_zb_get_pan_id(),
                    .radioChannel = esp_zb_get_current_channel(),
                };
                esp_zb_get_extended_pan_id(parameters.extendedPanId);

                ESP_LOGI(TAG, "Formed network successfully (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, Channel:%d)",
                        parameters.extendedPanId[7], parameters.extendedPanId[6], parameters.extendedPanId[5], parameters.extendedPanId[4],
                        parameters.extendedPanId[3], parameters.extendedPanId[2], parameters.extendedPanId[1], parameters.extendedPanId[0],
                        parameters.panId, parameters.radioChannel);
                ncp_header.id = ESP_NCP_NETWORK_FORMNETWORK;
                esp_ncp_noti_input(&ncp_header, &parameters, sizeof(esp_ncp_zb_formnetwork_parameters_t));
            } else {
                ESP_LOGI(TAG, "Restart network formation (status: %s)", esp_err_to_name(err_status));
                esp_zb_scheduler_alarm((esp_zb_callback_t)esp_ncp_zb_bdb_start_top_level_commissioning_cb, ESP_ZB_BDB_MODE_NETWORK_FORMATION, 1000);
            }
            break;
        case ESP_ZB_BDB_SIGNAL_FINDING_AND_BINDING_TARGET_FINISHED:
        case ESP_ZB_BDB_SIGNAL_FINDING_AND_BINDING_INITIATOR_FINISHED:
        case ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET:
        case ESP_ZB_BDB_SIGNAL_TOUCHLINK_NWK:
        case ESP_ZB_BDB_SIGNAL_TOUCHLINK_TARGET_FINISHED:
        case ESP_ZB_BDB_SIGNAL_TOUCHLINK_ADD_DEVICE_TO_NWK:
        case ESP_ZB_NWK_SIGNAL_DEVICE_ASSOCIATED:
        case ESP_ZB_ZDO_SIGNAL_LEAVE_INDICATION:
        case ESP_ZB_BDB_SIGNAL_WWAH_REJOIN_STARTED:
        case ESP_ZB_ZGP_SIGNAL_COMMISSIONING:
        case ESP_ZB_COMMON_SIGNAL_CAN_SLEEP:
        case ESP_ZB_ZDO_SIGNAL_PRODUCTION_CONFIG_READY:
        case ESP_ZB_NWK_SIGNAL_NO_ACTIVE_LINKS_LEFT:
        case ESP_ZB_SE_SIGNAL_SKIP_JOIN:
        case ESP_ZB_SE_SIGNAL_REJOIN:
        case ESP_ZB_SE_SIGNAL_CHILD_REJOIN:
        case ESP_ZB_SE_TC_SIGNAL_CHILD_JOIN_CBKE:
        case ESP_ZB_SE_TC_SIGNAL_CHILD_JOIN_NON_CBKE:
        case ESP_ZB_SE_SIGNAL_CBKE_FAILED:
        case ESP_ZB_SE_SIGNAL_CBKE_OK:
        case ESP_ZB_SE_SIGNAL_SERVICE_DISCOVERY_START:
        case ESP_ZB_SE_SIGNAL_SERVICE_DISCOVERY_DO_BIND:
        case ESP_ZB_SE_SIGNAL_SERVICE_DISCOVERY_BIND_OK:
        case ESP_ZB_SE_SIGNAL_SERVICE_DISCOVERY_BIND_FAILED:
        case ESP_ZB_SE_SIGNAL_SERVICE_DISCOVERY_BIND_INDICATION:
        case ESP_ZB_SE_SIGNAL_SERVICE_DISCOVERY_OK:
        case ESP_ZB_SE_SIGNAL_SERVICE_DISCOVERY_FAILED:
        case ESP_ZB_SE_SIGNAL_APS_KEY_READY:
        case ESP_ZB_SE_SIGNAL_APS_KEY_FAIL:
        case ESP_ZB_SIGNAL_SUBGHZ_SUSPEND:
        case ESP_ZB_SIGNAL_SUBGHZ_RESUME:
        case ESP_ZB_MACSPLIT_DEVICE_BOOT:
        case ESP_ZB_MACSPLIT_DEVICE_READY_FOR_UPGRADE:
        case ESP_ZB_MACSPLIT_DEVICE_FW_UPGRADE_EVENT:
        case ESP_ZB_SIGNAL_NWK_INIT_DONE:
        case ESP_ZB_ZDO_SIGNAL_DEVICE_AUTHORIZED:
        case ESP_ZB_ZDO_SIGNAL_DEVICE_UPDATE:
        case ESP_ZB_NWK_SIGNAL_PANID_CONFLICT_DETECTED:
        case ESP_ZB_NLME_STATUS_INDICATION:
        case ESP_ZB_TCSWAP_DB_BACKUP_REQUIRED_SIGNAL:
        case ESP_ZB_TC_SWAPPED_SIGNAL:
        case ESP_ZB_BDB_SIGNAL_TC_REJOIN_DONE:
            break;
        case ESP_ZB_NWK_SIGNAL_PERMIT_JOIN_STATUS:
            if (err_status == ESP_OK) {
                uint8_t *parameters = esp_zb_app_signal_get_params(p_sg_p);
                if (*parameters) {
                    ESP_LOGI(TAG, "Network(0x%04hx) is open for %d seconds", esp_zb_get_pan_id(), *parameters);
                } else {
                    ESP_LOGW(TAG, "Network(0x%04hx) closed, devices joining not allowed.", esp_zb_get_pan_id());
                }
                ncp_header.id = ESP_NCP_NETWORK_PERMIT_JOINING;
                esp_ncp_noti_input(&ncp_header, parameters, sizeof(uint8_t));
            }
            break;
        case ESP_ZB_BDB_SIGNAL_STEERING_CANCELLED:
        case ESP_ZB_BDB_SIGNAL_FORMATION_CANCELLED:
        case ESP_ZB_SIGNAL_READY_TO_SHUT:
        case ESP_ZB_SIGNAL_INTERPAN_PREINIT:
        case ESP_ZB_ZGP_SIGNAL_MODE_CHANGE:
        case ESP_ZB_ZDO_DEVICE_UNAVAILABLE:
        case ESP_ZB_ZGP_SIGNAL_APPROVE_COMMISSIONING:
        case ESP_ZB_SIGNAL_END:
            break;
        default:
            ESP_LOGI(TAG, "ZDO signal: %s (0x%x), status: %s", esp_zb_zdo_signal_to_string(sig_type), sig_type, esp_err_to_name(err_status));
            break;
    }
}


static esp_err_t esp_ncp_zb_network_init_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = ESP_OK;
    esp_ncp_status_t status = ESP_NCP_ERR_FATAL;

    if (!s_init_flag) {
        esp_zb_platform_config_t config = {
            .radio_config = {
                .radio_mode = ZB_RADIO_MODE_NATIVE,
            },
            .host_config = {
                .host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE,
            }
        };

        ret = esp_zb_platform_config(&config);
        if (ret == ESP_OK) {
            s_init_flag = true;
            status = ESP_NCP_SUCCESS;
        }
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_network_primary_channel_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? esp_zb_set_primary_network_channel_set(*(uint32_t *)input) : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    s_primary_channel = input ? (*(uint32_t *)input) : s_primary_channel;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_network_secondary_channel_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? esp_zb_set_secondary_network_channel_set(*(uint32_t *)input) : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_channel_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? esp_zb_set_channel_mask(*(uint32_t *)input) : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_tx_power_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;
    
    if (input) {
        esp_zb_set_tx_power(*input);
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_extended_pan_id_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    if (input) {
        esp_zb_set_extended_pan_id(input);
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_extended_pan_id_get_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(esp_zb_ieee_addr_t);
    *output = calloc(1, *outlen);
    
    if (*output) {
        esp_zb_get_extended_pan_id(*output);
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_pan_id_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    if (input) {
        esp_zb_set_pan_id(*(uint16_t *)input);
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_pan_id_get_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(uint16_t);
    *output = calloc(1, *outlen);
    
    if (*output) {
        uint16_t pan_id = esp_zb_get_pan_id();
        memcpy(*output, &pan_id, *outlen);
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_form_network_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    if (input) {
        esp_zb_init((esp_zb_cfg_t *)input);
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_start_scan_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = ESP_OK;
    esp_ncp_status_t status = ESP_NCP_ERR_FATAL;
    
    void esp_zb_zdo_active_scan_request(uint32_t channel_mask, uint8_t scan_duration, esp_zb_zdo_scan_complete_callback_t user_cb);
    esp_zb_zdo_active_scan_request(*(uint32_t *)(input), *(uint8_t *)(input + sizeof(uint32_t)), esp_ncp_zb_zdo_scan_complete_handler);

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_scan_complete_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    return ESP_OK;
}

static esp_err_t esp_ncp_zb_stop_scan_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    return ESP_OK;
}

static esp_err_t esp_ncp_zb_start_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? esp_zb_start(*(bool *)input) : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    if (!s_start_flag) {
        s_start_flag = true;
        xTaskCreate(esp_ncp_zb_task, "esp_ncp_zb_task", 4096, NULL, 5, NULL);
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_set_bind_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    if (input) {
        uint32_t *bind_req = calloc(1, sizeof(esp_ncp_zb_user_cb_t));
        if (bind_req) {
            memcpy(bind_req, input + (inlen - sizeof(esp_ncp_zb_user_cb_t)), sizeof(esp_ncp_zb_user_cb_t));
        }
        esp_zb_zdo_device_bind_req((esp_zb_zdo_bind_req_param_t *)input, esp_ncp_zb_bind_cb, (void *)bind_req);
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_set_unbind_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    if (input) {
        uint32_t *bind_req = calloc(1, sizeof(esp_ncp_zb_user_cb_t));
        if (bind_req) {
            memcpy(bind_req, input + (inlen - sizeof(esp_ncp_zb_user_cb_t)), sizeof(esp_ncp_zb_user_cb_t));
        }
        esp_zb_zdo_device_unbind_req((esp_zb_zdo_bind_req_param_t *)input, esp_ncp_zb_unbind_cb, (void *)bind_req);
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_network_state_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(uint8_t);
    *output = calloc(1, *outlen);
    
    if (*output) {
        *(*output) = ESP_NCP_CONNECTED;
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_stack_status_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_ncp_zb_cluster_fn_t cluster_list_fn_table[] = {
    { ESP_ZB_ZCL_CLUSTER_ID_BASIC                      , esp_zb_cluster_list_add_basic_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_POWER_CONFIG               , esp_zb_cluster_list_add_power_config_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_DEVICE_TEMP_CONFIG         , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_IDENTIFY                   , esp_zb_cluster_list_add_identify_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_GROUPS                     , esp_zb_cluster_list_add_groups_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_SCENES                     , esp_zb_cluster_list_add_scenes_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_ON_OFF                     , esp_zb_cluster_list_add_on_off_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_ON_OFF_SWITCH_CONFIG       , esp_zb_cluster_list_add_on_off_switch_config_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL              , esp_zb_cluster_list_add_level_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_ALARMS                     , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_TIME                       , esp_zb_cluster_list_add_time_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_RSSI_LOCATION              , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_ANALOG_INPUT               , esp_zb_cluster_list_add_analog_input_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_ANALOG_OUTPUT              , esp_zb_cluster_list_add_analog_output_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_ANALOG_VALUE               , esp_zb_cluster_list_add_analog_value_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_BINARY_INPUT               , esp_zb_cluster_list_add_binary_input_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_BINARY_OUTPUT              , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_BINARY_VALUE               , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_MULTI_INPUT                , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_MULTI_OUTPUT               , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_MULTI_VALUE                , esp_zb_cluster_list_add_multistate_value_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_COMMISSIONING              , esp_zb_cluster_list_add_touchlink_commissioning_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_OTA_UPGRADE                , esp_zb_cluster_list_add_ota_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_POLL_CONTROL               , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_GREEN_POWER                , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_KEEP_ALIVE                 , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_SHADE_CONFIG               , esp_zb_cluster_list_add_shade_config_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_DOOR_LOCK                  , esp_zb_cluster_list_add_door_lock_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_WINDOW_COVERING            , esp_zb_cluster_list_add_window_covering_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_PUMP_CONFIG_CONTROL        , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_THERMOSTAT                 , esp_zb_cluster_list_add_thermostat_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_FAN_CONTROL                , esp_zb_cluster_list_add_fan_control_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_DEHUMID_CONTROL            , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_THERMOSTAT_UI_CONFIG       , esp_zb_cluster_list_add_thermostat_ui_config_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL              , esp_zb_cluster_list_add_color_control_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_BALLAST_CONFIG             , esp_zb_cluster_list_add_custom_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_ILLUMINANCE_MEASUREMENT    , esp_zb_cluster_list_add_illuminance_meas_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT           , esp_zb_cluster_list_add_temperature_meas_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_PRESSURE_MEASUREMENT       , esp_zb_cluster_list_add_pressure_meas_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT   , esp_zb_cluster_list_add_humidity_meas_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_OCCUPANCY_SENSING          , esp_zb_cluster_list_add_occupancy_sensing_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_CARBON_DIOXIDE_MEASUREMENT , esp_zb_cluster_list_add_carbon_dioxide_measurement_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT          , esp_zb_cluster_list_add_pm2_5_measurement_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_IAS_ZONE                   , esp_zb_cluster_list_add_ias_zone_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_ELECTRICAL_MEASUREMENT     , esp_zb_cluster_list_add_electrical_meas_cluster , NULL },
    { ESP_ZB_ZCL_CLUSTER_ID_METERING                   , esp_zb_cluster_list_add_metering_cluster , NULL },
};

static esp_err_t esp_ncp_zb_add_endpoint_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    uint16_t data_head_len = sizeof(esp_ncp_zb_endpoint_t);
    esp_ncp_zb_endpoint_t *ncp_endpoint = (esp_ncp_zb_endpoint_t *)input;
    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_LOGI(TAG, "endpoint %0x, profileId %02x, deviceId %02x, appFlags %0x, inputClusterCount %0x, outputClusterCount %0x", 
                    ncp_endpoint->endpoint, ncp_endpoint->profileId, ncp_endpoint->deviceId,
                    ncp_endpoint->appFlags, ncp_endpoint->inputClusterCount, ncp_endpoint->outputClusterCount);

    if (inlen < data_head_len) {
        ret = ESP_FAIL;
    }

    if (s_start_flag && (ncp_endpoint->inputClusterCount || ncp_endpoint->outputClusterCount)) {
        uint16_t inputClusterLength = ncp_endpoint->inputClusterCount * sizeof(uint16_t);
        uint16_t outputClusterLength = ncp_endpoint->outputClusterCount * sizeof(uint16_t);
        uint16_t *inputClusterList = inputClusterLength ? calloc(1, inputClusterLength) : NULL;
        uint16_t *outputClusterList = outputClusterLength ? calloc(1, outputClusterLength) : NULL;

        esp_zb_cluster_list_t *esp_zb_cluster_list = esp_zb_zcl_cluster_list_create();

        if (inputClusterList) {
            memcpy(inputClusterList, input + data_head_len, inputClusterLength);
        }

        if (outputClusterList) {
            memcpy(outputClusterList, input + data_head_len + inputClusterLength, outputClusterLength);
        }

        for (int i = 0; i < ncp_endpoint->inputClusterCount; i ++) {
            esp_zb_attribute_list_t *esp_zb_cluster = esp_zb_zcl_attr_list_create(inputClusterList[i]);
            ESP_LOGI(TAG, "inputClusterList %02x", inputClusterList[i]);
            for (int j = 0; j < sizeof(cluster_list_fn_table) / sizeof(cluster_list_fn_table[0]); j ++) {
                if (inputClusterList[i] == cluster_list_fn_table[j].cluster_id) {
                    cluster_list_fn_table[j].add_cluster_fn(esp_zb_cluster_list, esp_zb_cluster, ESP_ZB_ZCL_CLUSTER_SERVER_ROLE);
                    break;
                }
            }
        }

        for (int i = 0; i < ncp_endpoint->outputClusterCount; i ++) {
            esp_zb_attribute_list_t *esp_zb_cluster = esp_zb_zcl_attr_list_create(outputClusterList[i]);
            ESP_LOGI(TAG, "outputClusterList %02x", outputClusterList[i]);
            for (int j = 0; j < sizeof(cluster_list_fn_table) / sizeof(cluster_list_fn_table[0]); j ++) {
                if (outputClusterList[i] == cluster_list_fn_table[j].cluster_id) {
                    cluster_list_fn_table[j].add_cluster_fn(esp_zb_cluster_list, esp_zb_cluster, ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE);
                    break;
                }
            }
        }

        esp_zb_ep_list_t *esp_zb_ep_list = esp_zb_ep_list_create();
        esp_zb_endpoint_config_t endpoint_config = {
            .endpoint = ncp_endpoint->endpoint,
            .app_profile_id = ncp_endpoint->profileId,
            .app_device_id = ncp_endpoint->deviceId,
            .app_device_version = 0
        };
        esp_zb_ep_list_add_ep(esp_zb_ep_list, esp_zb_cluster_list, endpoint_config);
        esp_zb_device_register(esp_zb_ep_list);

        if (inputClusterList) {
            free(inputClusterList);
            inputClusterList = NULL;
        }

        if (outputClusterList) {
            free(outputClusterList);
            outputClusterList = NULL;
        }
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_del_endpoint_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    return ESP_OK;
}

static esp_err_t esp_ncp_zb_read_attr_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    typedef struct {
        esp_zb_zcl_basic_cmd_t  zcl_basic_cmd;      /*!< Basic command info */
        uint8_t                 address_mode;       /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
        uint16_t                cluster_id;         /*!< Cluster ID to read */
        uint8_t                 attr_number;        /*!< Number of attribute in the attr_field */
    } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_read_attr_t;

    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    if (input) {
        esp_ncp_zb_read_attr_t *zb_read_attr = (esp_ncp_zb_read_attr_t *)input;
        uint16_t *attr_field = calloc(1, zb_read_attr->attr_number * sizeof(uint16_t));

        ESP_LOGI(TAG, "Read attr addr %02x, dst_endpoint %0x, src_endpoint %0x, address_mode %0x, cluster_id %02x",
                        zb_read_attr->zcl_basic_cmd.dst_addr_u.addr_short, zb_read_attr->zcl_basic_cmd.dst_endpoint, 
                        zb_read_attr->zcl_basic_cmd.src_endpoint, zb_read_attr->address_mode, zb_read_attr->cluster_id);

        if (attr_field) {
            memcpy(attr_field, input + sizeof(esp_ncp_zb_read_attr_t), zb_read_attr->attr_number * sizeof(uint16_t));

            esp_zb_zcl_read_attr_cmd_t read_req = {
                .zcl_basic_cmd = zb_read_attr->zcl_basic_cmd,
                .address_mode = zb_read_attr->address_mode,
                .clusterID = zb_read_attr->cluster_id,
                .attr_number = zb_read_attr->attr_number,
                .attr_field = attr_field,
            };
            
            esp_zb_zcl_read_attr_cmd_req(&read_req);
        } else {
            ret = ESP_ERR_NO_MEM;
            status = ESP_NCP_ERR_FATAL;
        }
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_write_attr_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    typedef struct {
        esp_zb_zcl_basic_cmd_t  zcl_basic_cmd;          /*!< Basic command info */
        uint8_t                 address_mode;           /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
        uint16_t                cluster_id;             /*!< Cluster ID to write */
        uint8_t                 attr_number;            /*!< Number of attribute in the attr_field  */
    } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_write_attr_t;

    typedef struct {
        uint16_t id;                                    /*!< The identify of attribute */
        uint8_t  type;                                  /*!< The type of attribute, which can refer to esp_zb_zcl_attr_type_t */
        uint8_t  size;                                  /*!< The value size of attribute  */
    } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_attr_data_t;

    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    if (input) {
        esp_ncp_zb_write_attr_t *zb_write_attr = (esp_ncp_zb_write_attr_t *)input;
        esp_zb_zcl_attribute_t *attr_field = zb_write_attr->attr_number ? calloc(1, (zb_write_attr->attr_number * sizeof(esp_zb_zcl_attribute_t))) : NULL;
        esp_ncp_zb_attr_data_t *attr_data = NULL;
        uint8_t data_head_len = sizeof(esp_ncp_zb_write_attr_t);
        uint8_t attr_head_len = sizeof(esp_ncp_zb_attr_data_t);
        uint16_t length = data_head_len;

        ESP_LOGI(TAG, "Write attr addr %02x, dst_endpoint %0x, src_endpoint %0x, address_mode %0x, cluster_id %02x",
                        zb_write_attr->zcl_basic_cmd.dst_addr_u.addr_short, zb_write_attr->zcl_basic_cmd.dst_endpoint, 
                        zb_write_attr->zcl_basic_cmd.src_endpoint, zb_write_attr->address_mode, zb_write_attr->cluster_id);
        
        if (attr_field) {
            for (int i = 0; i < zb_write_attr->attr_number; i ++) {
                attr_data = (esp_ncp_zb_attr_data_t *)(input + length);

                ESP_LOGI(TAG, "attributeId %0x, dataType %02x, dataLength %0x", attr_data->id, attr_data->type, attr_data->size);

                attr_field[i].id = attr_data->id;
                attr_field[i].data.type = attr_data->type;
                attr_field[i].data.size = attr_data->size;
                attr_field[i].data.value = calloc(1, attr_data->size);
                if (attr_field[i].data.value) {
                    memcpy(attr_field[i].data.value, attr_data + attr_head_len, attr_data->size);
                } else {
                    ret = ESP_ERR_NO_MEM;
                    status = ESP_NCP_ERR_FATAL;
                    break;
                }

                length += (attr_head_len + attr_data->size);
            }

            if (ret == ESP_OK) {
                esp_zb_zcl_write_attr_cmd_t write_req = {
                    .zcl_basic_cmd = zb_write_attr->zcl_basic_cmd,
                    .address_mode = zb_write_attr->address_mode,
                    .clusterID = zb_write_attr->cluster_id,
                    .attr_number = zb_write_attr->attr_number,
                    .attr_field = attr_field,
                };

                esp_zb_zcl_write_attr_cmd_req(&write_req);
            }

            for (int i = 0; i < zb_write_attr->attr_number; i ++) {
                if (attr_field[i].data.value) {
                    free(attr_field[i].data.value);
                    attr_field[i].data.value = NULL;
                }
            }
            free(attr_field);
            attr_field = NULL;
        } else {
            ret = ESP_ERR_NO_MEM;
            status = ESP_NCP_ERR_FATAL;
        }
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_report_attr_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    if (input) {
        esp_zb_zcl_report_attr_cmd_req((esp_zb_zcl_report_attr_cmd_t *)input);
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_disc_attr_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    if (input) {
        esp_zb_zcl_disc_attr_cmd_req((esp_zb_zcl_disc_attr_cmd_t *)input);
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_zcl_read_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    return ESP_OK;
}

static esp_err_t esp_ncp_zb_zcl_write_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
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
    } ESP_NCP_ZB_PACKED_STRUCT esp_ncp_zb_zcl_data_t;

    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;
    uint8_t *data_value = NULL;
    
    if (input) {
        esp_ncp_zb_zcl_data_t *zcl_data = (esp_ncp_zb_zcl_data_t *)input;
        ESP_LOGI(TAG, "addr %02x, dst_endpoint %0x, src_endpoint %0x, address_mode %0x, profile_id %02x, cluster_id %02x, cmd_id %02x, direction %02x",
                        zcl_data->zcl_basic_cmd.dst_addr_u.addr_short, zcl_data->zcl_basic_cmd.dst_endpoint, zcl_data->zcl_basic_cmd.src_endpoint, 
                        zcl_data->address_mode, zcl_data->profile_id, zcl_data->cluster_id, zcl_data->custom_cmd_id,  zcl_data->direction);

        esp_zb_zcl_custom_cluster_cmd_t cmd_req = {
            .zcl_basic_cmd = zcl_data->zcl_basic_cmd,
            .address_mode = zcl_data->address_mode,
            .profile_id = zcl_data->profile_id,
            .cluster_id = zcl_data->cluster_id,
            .custom_cmd_id = zcl_data->custom_cmd_id,
            .direction = zcl_data->direction,
            .data = {
                .type = zcl_data->type,
                .value = (void *)(input + sizeof(esp_ncp_zb_zcl_data_t)),
            }
        };

        switch (zcl_data->type) {
            case ESP_ZB_ZCL_ATTR_TYPE_ARRAY:
            case ESP_ZB_ZCL_ATTR_TYPE_16BIT_ARRAY:
            case ESP_ZB_ZCL_ATTR_TYPE_32BIT_ARRAY:
            case ESP_ZB_ZCL_ATTR_TYPE_STRUCTURE:
                data_value = calloc(1, 2 + zcl_data->size);
                memcpy(data_value, &zcl_data->size, 2);
                memcpy(data_value + 2, input + sizeof(esp_ncp_zb_zcl_data_t), zcl_data->size);
                cmd_req.data.value = data_value;
                break;
            default:
                cmd_req.data.value = (void *)(input + sizeof(esp_ncp_zb_zcl_data_t));
                break;
        }

        esp_zb_zcl_custom_cluster_cmd_req(&cmd_req);
        if (data_value) {
            free(data_value);
            data_value = NULL;
        }
    }

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_short_addr_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(uint16_t);
    *output = calloc(1, *outlen);
    
    if (*output) {
        uint16_t short_addr = esp_zb_get_short_address();
        memcpy(*output, &short_addr, *outlen);
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_long_addr_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(esp_zb_ieee_addr_t);
    *output = calloc(1, *outlen);
    
    if (*output) {
        esp_zb_get_long_address(*output);
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_current_channel_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(uint8_t);
    *output = calloc(1, *outlen);
    
    if (*output) {
        *(*output) = esp_zb_get_current_channel();
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_primary_channel_get_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(uint32_t);
    *output = calloc(1, *outlen);
    
    if (*output) {
        uint32_t primary_channel = s_primary_channel;
        memcpy(*output, &primary_channel, *outlen);
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_primary_key_get_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = ESP_OK;
    *outlen = 16;
    *output = calloc(1, *outlen);

    if (*output) {
        ret = esp_zb_secur_primary_network_key_get(*output);
    } else {
        ret = ESP_ERR_NO_MEM;
    }

    return ret;
}

static esp_err_t esp_ncp_zb_primary_key_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = (input && inlen == 16 ) ? esp_zb_secur_network_key_set((uint8_t *)input) : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_nwk_frame_counter_get_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(uint32_t);
    *output = calloc(1, *outlen);

    if (*output) {
        uint32_t counter = 0x00001388;
        memcpy(*output, &counter, *outlen);
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_nwk_frame_counter_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = (input && inlen == sizeof(uint32_t) ) ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_nwk_role_get_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(uint8_t);
    *output = calloc(1, *outlen);

    if (*output) {
        *(*output) = ESP_ZB_DEVICE_TYPE_COORDINATOR;
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_nwk_role_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = (input && inlen == sizeof(uint8_t) ) ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_short_addr_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = (input && inlen == sizeof(uint16_t) ) ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_long_addr_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = (input && inlen == sizeof(esp_zb_ieee_addr_t) ) ? esp_zb_set_long_address((uint8_t *)input) : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_nwk_update_id_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(uint8_t);
    *output = calloc(1, *outlen);

    if (*output) {
        *(*output) = 1;
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_nwk_update_id_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = (input && inlen == sizeof(uint8_t) ) ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_nwk_trust_center_addr_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(esp_zb_ieee_addr_t);
    *output = calloc(1, *outlen);

    if (*output) {
        esp_zb_ieee_addr_t addr = {0xab, 0x98, 0x09, 0xff, 0xff, 0x2e, 0x21, 0x00};
        memcpy(*output, addr, *outlen);
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_nwk_trust_center_addr_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = (input && inlen == sizeof(esp_zb_ieee_addr_t) ) ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_nwk_link_key_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(esp_zb_ieee_addr_t) + 16;
    *output = calloc(1, *outlen);

    if (*output) {
        esp_zb_ieee_addr_t addr;
        uint8_t key[16] = {0x5a, 0x69, 0x67, 0x42, 0x65, 0x65, 0x41, 0x6c, 0x6c, 0x69, 0x61, 0x6e, 0x63, 0x65, 0x30, 0x39};
        esp_zb_get_long_address(addr);
        memcpy(*output, addr, sizeof(esp_zb_ieee_addr_t));
        memcpy((*output) + sizeof(esp_zb_ieee_addr_t), key, 16);
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_nwk_link_key_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = (input && inlen == 16 ) ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_nwk_security_mode_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    *outlen = sizeof(uint8_t);
    *output = calloc(1, *outlen);

    if (*output) {
        *(*output) = ESP_NCP_NO_SECURITY;
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_nwk_security_mode_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = (input && inlen == sizeof(uint8_t) ) ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_use_predefined_nwk_panid_set_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = (input && inlen == sizeof(uint8_t) ) ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_address_short_by_ieee_get_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = (input && inlen == sizeof(esp_zb_ieee_addr_t)) ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    if (status == ESP_NCP_SUCCESS) {
        uint16_t shotr_addr = esp_zb_address_short_by_ieee((uint8_t *)input);

        *outlen = sizeof(uint16_t);
        *output = calloc(1, *outlen);

        if (*output) {
            memcpy(*output, &shotr_addr, *outlen);
        }
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_ieee_address_by_short_get_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = (input && inlen == sizeof(uint16_t) ) ? ESP_OK : ESP_ERR_INVALID_ARG;
    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    if (status == ESP_NCP_SUCCESS) {
        uint16_t shotr_addr = 0;
        esp_zb_ieee_addr_t ieee_addr;
        memcpy(&shotr_addr, input, inlen);

        esp_zb_ieee_address_by_short(shotr_addr, ieee_addr);

        *outlen = sizeof(esp_zb_ieee_addr_t);
        *output = calloc(1, *outlen);

        if (*output) {
            memcpy(*output, ieee_addr, *outlen);
        }
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_find_match_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = ESP_OK;

    typedef struct {
        esp_ncp_zb_user_cb_t user_ctx;      /*!< A ZDO match desc request callback */
        uint16_t dst_nwk_addr;              /*!< NWK address that request sent to */
        uint16_t addr_of_interest;          /*!< NWK address of interest */
        uint16_t profile_id;                /*!< Profile ID to be match at the destination which refers to esp_zb_af_profile_id_t */
        uint8_t num_in_clusters;            /*!< The number of input clusters provided for matching cluster server */
        uint8_t num_out_clusters;           /*!< The number of output clusters provided for matching cluster client */
    } __attribute__ ((packed)) esp_zb_zdo_match_desc_t;

    if (input) {
        esp_zb_zdo_match_desc_t *zdo_data = (esp_zb_zdo_match_desc_t *)input;
        esp_zb_zdo_match_desc_req_param_t desc_req = {
            .dst_nwk_addr = zdo_data->dst_nwk_addr,
            .addr_of_interest = zdo_data->addr_of_interest,
            .profile_id = zdo_data->profile_id,
            .num_in_clusters = zdo_data->num_in_clusters,
            .num_out_clusters = zdo_data->num_out_clusters,
            .cluster_list = (inlen != sizeof(esp_zb_zdo_match_desc_t)) ? (uint16_t *)(input + sizeof(esp_zb_zdo_match_desc_t)) : NULL,
        };

        uint32_t *user_ctx = calloc(1, sizeof(esp_ncp_zb_user_cb_t));
        if (user_ctx) {
            memcpy(user_ctx, input, sizeof(esp_ncp_zb_user_cb_t));
        }

        ret = esp_zb_zdo_match_cluster(&desc_req, esp_ncp_zb_find_match_cb, user_ctx);
    } else {
        ret = ESP_ERR_INVALID_ARG;
    }

    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_aps_data_request_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_err_t ret = input ? ESP_OK : ESP_ERR_INVALID_ARG;

    typedef struct {
        esp_zb_zcl_basic_cmd_t basic_cmd;                       /*!< Basic command info */
        uint8_t  dst_addr_mode;                                 /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
        uint16_t profile_id;                                    /*!< Profile id */
        uint16_t cluster_id;                                    /*!< Cluster id */
        uint8_t tx_options;                                     /*!< The transmission options for the ASDU to be transferred, refer to esp_zb_apsde_tx_opt_t */
        bool use_alias;                                         /*!< The next higher layer may use the UseAlias parameter to request alias usage by NWK layer for the current frame.*/
        esp_zb_addr_u alias_src_addr;                           /*!< The source address to be used for this NSDU. If the use_alias is true */
        uint8_t alias_seq_num;                                  /*!< The sequence number to be used for this NSDU. If the use_alias is true */
        uint8_t radius;                                         /*!< The distance, in hops, that a transmitted frame will be allowed to travel through the network.*/
        uint32_t asdu_length;                                   /*!< The number of octets comprising the ASDU to be transferred */
    } ESP_NCP_ZB_PACKED_STRUCT esp_zb_aps_data_t;

    if (input) {
        esp_zb_aps_data_t *aps_data = (esp_zb_aps_data_t *)input;
        esp_zb_apsde_data_req_t data_req = {
            .dst_addr_mode  = aps_data->dst_addr_mode,
            .dst_short_addr = aps_data->basic_cmd.dst_addr_u.addr_short,
            .dst_endpoint   = aps_data->basic_cmd.dst_endpoint,
            .src_endpoint   = aps_data->basic_cmd.src_endpoint,
            .profile_id     = aps_data->profile_id,
            .cluster_id     = aps_data->cluster_id,
            .tx_options     = aps_data->tx_options,
            .use_alias      = aps_data->use_alias,
            .alias_src_addr = aps_data->alias_src_addr.addr_short,
            .alias_seq_num  = aps_data->alias_seq_num,
            .radius         = aps_data->radius,
            .asdu_length    = aps_data->asdu_length,
            .asdu           = aps_data->asdu_length ? (uint8_t *)(input + sizeof(esp_zb_aps_data_t)) : NULL,
        };

        ESP_LOGI(TAG, "dst_addr_mode %0x, dst_short_addr %02x, dst_endpoint %0x, src_endpoint %0x, profile_id %02x, cluster_id %02x, tx_options %02x, use_alias %02x, radius %0x",
                        data_req.dst_addr_mode, data_req.dst_short_addr, data_req.dst_endpoint, data_req.src_endpoint, data_req.profile_id, data_req.cluster_id,
                        data_req.tx_options, data_req.use_alias, data_req.radius);

        if (data_req.asdu && data_req.asdu_length) {
            ESP_LOG_BUFFER_HEX_LEVEL(TAG, data_req.asdu, data_req.asdu_length, ESP_LOG_DEBUG);
        }

        esp_zb_aps_data_indication_handler_register(esp_ncp_zb_aps_data_indication_handler);
        esp_zb_aps_data_confirm_handler_register(esp_ncp_zb_aps_data_confirm_handler);
        ret = esp_zb_aps_data_request(&data_req);
    }

    esp_ncp_status_t status = (ret == ESP_OK) ? ESP_NCP_SUCCESS : ESP_NCP_ERR_FATAL;

    ESP_NCP_ZB_STATUS();

    return ret;
}

static esp_err_t esp_ncp_zb_aps_data_indication_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_ncp_zb_ctx_t ncp_ctx;

    if (!s_aps_data_indication) {
        s_aps_data_indication = xQueueCreate(NCP_EVENT_QUEUE_LEN, sizeof(esp_ncp_zb_ctx_t));
    }

    if (s_aps_data_indication && (xQueueReceive(s_aps_data_indication, &ncp_ctx, pdMS_TO_TICKS(100)) == pdTRUE)) {
        *outlen = ncp_ctx.size;
        *output = ncp_ctx.data;
    } else {
        *outlen = sizeof(uint8_t);
        *output = calloc(1, *outlen);
        if (*output) {
            *(*output) = ESP_NCP_CONNECTED;
        }
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t esp_ncp_zb_aps_data_confirm_fn(const uint8_t *input, uint16_t inlen, uint8_t **output, uint16_t *outlen)
{
    esp_ncp_zb_ctx_t ncp_ctx;

    if (!s_aps_data_confirm) {
        s_aps_data_confirm = xQueueCreate(NCP_EVENT_QUEUE_LEN, sizeof(esp_ncp_zb_ctx_t));
    }

    if (s_aps_data_confirm && xQueueReceive(s_aps_data_confirm, &ncp_ctx, pdMS_TO_TICKS(100)) == pdTRUE) {
        *outlen = ncp_ctx.size;
        *output = ncp_ctx.data;
    } else {
        *outlen = sizeof(uint8_t);
        *output = calloc(1, *outlen);
        if (*output) {
            *(*output) = ESP_NCP_CONNECTED;
        }
    }

    return (*output) ? ESP_OK : ESP_ERR_NO_MEM;
}

static const esp_ncp_zb_func_t ncp_zb_func_table[] = {
    {ESP_NCP_NETWORK_INIT, esp_ncp_zb_network_init_fn},
    {ESP_NCP_NETWORK_PAN_ID_SET, esp_ncp_zb_pan_id_set_fn},
    {ESP_NCP_NETWORK_PAN_ID_GET, esp_ncp_zb_pan_id_get_fn},
    {ESP_NCP_NETWORK_EXTENDED_PAN_ID_SET, esp_ncp_zb_extended_pan_id_set_fn},
    {ESP_NCP_NETWORK_EXTENDED_PAN_ID_GET, esp_ncp_zb_extended_pan_id_get_fn},
    {ESP_NCP_NETWORK_PRIMARY_CHANNEL_SET, esp_ncp_zb_network_primary_channel_set_fn},
    {ESP_NCP_NETWORK_SECONDARY_CHANNEL_SET, esp_ncp_zb_network_secondary_channel_set_fn},
    {ESP_NCP_NETWORK_CHANNEL_SET, esp_ncp_zb_channel_set_fn},
    {ESP_NCP_NETWORK_TXPOWER_SET, esp_ncp_zb_tx_power_set_fn},
    {ESP_NCP_NETWORK_FORMNETWORK, esp_ncp_zb_form_network_fn},
    {ESP_NCP_NETWORK_START_SCAN, esp_ncp_zb_start_scan_fn},
    {ESP_NCP_NETWORK_SCAN_COMPLETE_HANDLER, esp_ncp_zb_scan_complete_fn},
    {ESP_NCP_NETWORK_STOP_SCAN, esp_ncp_zb_stop_scan_fn},
    {ESP_NCP_NETWORK_START, esp_ncp_zb_start_fn},
    {ESP_NCP_NETWORK_STATE, esp_ncp_zb_network_state_fn},
    {ESP_NCP_NETWORK_STACK_STATUS_HANDLER, esp_ncp_zb_stack_status_fn},
    {ESP_NCP_NETWORK_JOINNETWORK, NULL},
    {ESP_NCP_NETWORK_PERMIT_JOINING, NULL},
    {ESP_NCP_NETWORK_LEAVENETWORK, NULL},
    {ESP_NCP_NETWORK_SHORT_ADDRESS_GET, esp_ncp_zb_short_addr_fn},
    {ESP_NCP_NETWORK_LONG_ADDRESS_GET, esp_ncp_zb_long_addr_fn},
    {ESP_NCP_NETWORK_CHANNEL_GET, esp_ncp_zb_current_channel_fn},
    {ESP_NCP_NETWORK_PRIMARY_CHANNEL_GET, esp_ncp_zb_primary_channel_get_fn},
    {ESP_NCP_NETWORK_PRIMARY_KEY_GET, esp_ncp_zb_primary_key_get_fn},
    {ESP_NCP_NETWORK_PRIMARY_KEY_SET, esp_ncp_zb_primary_key_set_fn},
    {ESP_NCP_NETWORK_FRAME_COUNT_GET, esp_ncp_zb_nwk_frame_counter_get_fn},
    {ESP_NCP_NETWORK_FRAME_COUNT_SET, esp_ncp_zb_nwk_frame_counter_set_fn},
    {ESP_NCP_NETWORK_ROLE_GET, esp_ncp_zb_nwk_role_get_fn},
    {ESP_NCP_NETWORK_ROLE_SET, esp_ncp_zb_nwk_role_set_fn},
    {ESP_NCP_NETWORK_SHORT_ADDRESS_SET, esp_ncp_zb_short_addr_set_fn},
    {ESP_NCP_NETWORK_LONG_ADDRESS_SET, esp_ncp_zb_long_addr_set_fn},
    {ESP_NCP_NETWORK_CHANNEL_MASKS_SET, esp_ncp_zb_network_primary_channel_set_fn},
    {ESP_NCP_NETWORK_UPDATE_ID_GET, esp_ncp_zb_nwk_update_id_fn},
    {ESP_NCP_NETWORK_UPDATE_ID_SET, esp_ncp_zb_nwk_update_id_set_fn},
    {ESP_NCP_NETWORK_TRUST_CENTER_ADDR_GET, esp_ncp_zb_nwk_trust_center_addr_fn},
    {ESP_NCP_NETWORK_TRUST_CENTER_ADDR_SET, esp_ncp_zb_nwk_trust_center_addr_set_fn},
    {ESP_NCP_NETWORK_LINK_KEY_GET, esp_ncp_zb_nwk_link_key_fn},
    {ESP_NCP_NETWORK_LINK_KEY_SET, esp_ncp_zb_nwk_link_key_set_fn},
    {ESP_NCP_NETWORK_SECURE_MODE_GET, esp_ncp_zb_nwk_security_mode_fn},
    {ESP_NCP_NETWORK_SECURE_MODE_SET, esp_ncp_zb_nwk_security_mode_set_fn},
    {ESP_NCP_NETWORK_PREDEFINED_PANID, esp_ncp_zb_use_predefined_nwk_panid_set_fn},
    {ESP_NCP_NETWORK_SHORT_TO_IEEE, esp_ncp_zb_ieee_address_by_short_get_fn},
    {ESP_NCP_NETWORK_IEEE_TO_SHORT, esp_ncp_zb_address_short_by_ieee_get_fn},
    {ESP_NCP_ZCL_ENDPOINT_ADD, esp_ncp_zb_add_endpoint_fn},
    {ESP_NCP_ZCL_ENDPOINT_DEL, esp_ncp_zb_del_endpoint_fn},
    {ESP_NCP_ZCL_ATTR_READ, esp_ncp_zb_read_attr_fn},
    {ESP_NCP_ZCL_ATTR_WRITE, esp_ncp_zb_write_attr_fn},
    {ESP_NCP_ZCL_ATTR_REPORT, esp_ncp_zb_report_attr_fn},
    {ESP_NCP_ZCL_ATTR_DISC, esp_ncp_zb_disc_attr_fn},
    {ESP_NCP_ZCL_READ, esp_ncp_zb_zcl_read_fn},
    {ESP_NCP_ZCL_WRITE, esp_ncp_zb_zcl_write_fn},
    {ESP_NCP_ZCL_REPORT_CONFIG, NULL},
    {ESP_NCP_ZDO_BIND_SET, esp_ncp_zb_set_bind_fn},
    {ESP_NCP_ZDO_UNBIND_SET, esp_ncp_zb_set_unbind_fn},
    {ESP_NCP_ZDO_FIND_MATCH, esp_ncp_zb_find_match_fn},
    {ESP_NCP_APS_DATA_REQUEST, esp_ncp_zb_aps_data_request_fn},
    {ESP_NCP_APS_DATA_INDICATION, esp_ncp_zb_aps_data_indication_fn},
    {ESP_NCP_APS_DATA_CONFIRM, esp_ncp_zb_aps_data_confirm_fn},
};

esp_err_t esp_ncp_zb_output(esp_ncp_header_t *ncp_header, const void *buffer, uint16_t len)
{
    uint8_t *output = NULL;
    uint16_t outlen = 0;
    esp_err_t ret = ESP_OK;

    for (int i = 0; i <= sizeof(ncp_zb_func_table) / sizeof(ncp_zb_func_table[0]); i ++) {
        if (ncp_header->id != ncp_zb_func_table[i].id) {
            continue;
        }

        if (ncp_zb_func_table[i].set_func) {
            ret = ncp_zb_func_table[i].set_func(buffer, len, &output, &outlen);
            if (ret == ESP_OK) {
                esp_ncp_resp_input(ncp_header, output, outlen);
            }
        } else {
            ret = ESP_ERR_INVALID_ARG;
        }
        break;
    }

    if (output) {
        free(output);
        output = NULL;
    }

    return ret;
}
