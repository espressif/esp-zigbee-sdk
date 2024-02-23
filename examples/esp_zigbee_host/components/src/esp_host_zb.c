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

#include "esp_host_main.h"
#include "esp_host_zb.h"

#include "zb_config_platform.h"
#include "esp_zigbee_core.h"
#include "esp_zigbee_zcl_command.h"

typedef struct {
    esp_zb_ieee_addr_t  extendedPanId;                      /*!< The network's extended PAN identifier */
    uint16_t            panId;                              /*!< The network's PAN identifier */
    uint8_t             radioChannel;                       /*!< A radio channel */
} esp_host_zb_network_t;

/**
 * @brief Type to represent the sync event between the host and BUS.
 *
 */
typedef struct {
    uint16_t        id;                                     /*!< The frame ID */
    uint16_t        size;                                   /*!< Data size on the event */
    void            *data;                                  /*!< Data on the event */
} esp_host_zb_ctx_t;

static esp_host_zb_network_t        s_host_zb_network;
static QueueHandle_t                output_queue;           /*!< The queue handler for wait response */
static QueueHandle_t                notify_queue;           /*!< The queue handler for wait notification */
static SemaphoreHandle_t            lock_semaphore;

static esp_err_t esp_host_zb_form_network_fn(const uint8_t *input, uint16_t inlen)
{
    typedef struct {
        esp_zb_ieee_addr_t  extendedPanId;                  /*!< The network's extended PAN identifier */
        uint16_t            panId;                          /*!< The network's PAN identifier */
        uint8_t             radioChannel;                   /*!< A radio channel */
    } ESP_ZNSP_ZB_PACKED_STRUCT esp_zb_form_network_t;

    esp_zb_form_network_t *form_network = (esp_zb_form_network_t *)input;
    esp_zb_app_signal_msg_t signal_msg = {
        .signal = ESP_ZB_BDB_SIGNAL_FORMATION,
        .msg = NULL,
    };

    esp_zb_app_signal_t app_signal = {
        .p_app_signal = (uint32_t *)&signal_msg,
        .esp_err_status = ESP_OK,
    };

    memcpy(s_host_zb_network.extendedPanId, form_network->extendedPanId, sizeof(esp_zb_ieee_addr_t));
    s_host_zb_network.panId = form_network->panId;
    s_host_zb_network.radioChannel = form_network->radioChannel;

    esp_zb_app_signal_handler(&app_signal);

    return ESP_OK;
}

static esp_err_t esp_host_zb_joining_network_fn(const uint8_t *input, uint16_t inlen)
{
    esp_zb_app_signal_msg_t signal_msg = {
        .signal = ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE,
        .msg = (const char *)input,
    };

    esp_zb_app_signal_t app_signal = {
        .p_app_signal = (uint32_t *)&signal_msg,
        .esp_err_status = ESP_OK,
    };

    esp_zb_app_signal_handler(&app_signal);

    return ESP_OK;
}

static esp_err_t esp_host_zb_permit_joining_fn(const uint8_t *input, uint16_t inlen)
{
    esp_zb_app_signal_msg_t signal_msg = {
        .signal = ESP_ZB_NWK_SIGNAL_PERMIT_JOIN_STATUS,
        .msg = (const char *)input,
    };

    esp_zb_app_signal_t app_signal = {
        .p_app_signal = (uint32_t *)&signal_msg,
        .esp_err_status = ESP_OK,
    };

    esp_zb_app_signal_handler(&app_signal);

    return ESP_OK;
}

static esp_err_t esp_host_zb_leave_network_fn(const uint8_t *input, uint16_t inlen)
{
    esp_zb_app_signal_msg_t signal_msg = {
        .signal = ESP_ZB_ZDO_SIGNAL_LEAVE,
        .msg = (const char *)input,
    };

    esp_zb_app_signal_t app_signal = {
        .p_app_signal = (uint32_t *)&signal_msg,
        .esp_err_status = ESP_OK,
    };

    esp_zb_app_signal_handler(&app_signal);

    return ESP_OK;
}

static esp_err_t esp_host_zb_set_bind_fn(const uint8_t *input, uint16_t inlen)
{
    typedef struct {
        esp_zb_zdp_status_t    zdo_status;
        esp_zb_user_cb_t       bind_usr;                   /*!< A ZDO bind desc request callback */
    } ESP_ZNSP_ZB_PACKED_STRUCT esp_zb_zdo_bind_desc_t;

    esp_zb_zdo_bind_desc_t *zdo_bind_desc = (esp_zb_zdo_bind_desc_t *)input;
    if (zdo_bind_desc->bind_usr.user_cb) {
        esp_zb_zdo_bind_callback_t zdo_bind_desc_callback = (esp_zb_zdo_bind_callback_t)zdo_bind_desc->bind_usr.user_cb;
        zdo_bind_desc_callback(zdo_bind_desc->zdo_status, (void *)zdo_bind_desc->bind_usr.user_ctx);
    }

    return ESP_OK;
}

static esp_err_t esp_host_zb_set_unbind_fn(const uint8_t *input, uint16_t inlen)
{
    typedef struct {
        esp_zb_zdp_status_t    zdo_status;
        esp_zb_user_cb_t       bind_usr;                   /*!< A ZDO bind desc request callback */
    } ESP_ZNSP_ZB_PACKED_STRUCT esp_zb_zdo_unbind_desc_t;

    esp_zb_zdo_unbind_desc_t *zdo_bind_desc = (esp_zb_zdo_unbind_desc_t *)input;
    if (zdo_bind_desc->bind_usr.user_cb) {
        esp_zb_zdo_bind_callback_t zdo_bind_desc_callback = (esp_zb_zdo_bind_callback_t)zdo_bind_desc->bind_usr.user_cb;
        zdo_bind_desc_callback(zdo_bind_desc->zdo_status, (void *)zdo_bind_desc->bind_usr.user_ctx);
    }

    return ESP_OK;
}

static esp_err_t esp_host_zb_find_match_fn(const uint8_t *input, uint16_t inlen)
{
    typedef struct {
        esp_zb_zdp_status_t zdo_status;
        uint16_t            addr;
        uint8_t             endpoint;
        esp_zb_user_cb_t    find_usr;
    } ESP_ZNSP_ZB_PACKED_STRUCT esp_zb_zdo_match_desc_t;

    esp_zb_zdo_match_desc_t *zdo_match_desc = (esp_zb_zdo_match_desc_t *)input;

    if (zdo_match_desc->find_usr.user_cb) {
        esp_zb_zdo_match_desc_callback_t zdo_match_desc_callback = (esp_zb_zdo_match_desc_callback_t)zdo_match_desc->find_usr.user_cb;
        zdo_match_desc_callback(zdo_match_desc->zdo_status, zdo_match_desc->addr, zdo_match_desc->endpoint, (void *)zdo_match_desc->find_usr.user_ctx);
    }

    return ESP_OK;
}

static const esp_host_zb_func_t host_zb_func_table[] = {
    {ESP_ZNSP_NETWORK_FORMNETWORK, esp_host_zb_form_network_fn},
    {ESP_ZNSP_NETWORK_JOINNETWORK, esp_host_zb_joining_network_fn},
    {ESP_ZNSP_NETWORK_PERMIT_JOINING, esp_host_zb_permit_joining_fn},
    {ESP_ZNSP_NETWORK_LEAVENETWORK, esp_host_zb_leave_network_fn},
    {ESP_ZNSP_ZDO_BIND_SET, esp_host_zb_set_bind_fn},
    {ESP_ZNSP_ZDO_UNBIND_SET, esp_host_zb_set_unbind_fn},
    {ESP_ZNSP_ZDO_FIND_MATCH, esp_host_zb_find_match_fn},
};

esp_err_t esp_host_zb_input(esp_host_header_t *host_header, const void *buffer, uint16_t len)
{
    QueueHandle_t queue = (host_header->flags.type == ESP_ZNSP_TYPE_NOTIFY) ? notify_queue : output_queue;
    BaseType_t ret = 0;
    esp_host_zb_ctx_t host_ctx = {
        .id = host_header->id,
        .size = len,
    };

    if (buffer) {
        host_ctx.data = calloc(1, len);
        memcpy(host_ctx.data, buffer, len);
    }

    if (xPortInIsrContext() == pdTRUE) {
        ret = xQueueSendFromISR(queue, &host_ctx, NULL);
    } else {
        ret = xQueueSend(queue, &host_ctx, 0);
    }
    return (ret == pdTRUE) ? ESP_OK : ESP_FAIL ;
}

esp_err_t esp_host_zb_output(uint16_t id, const void *buffer, uint16_t len, void *output, uint16_t *outlen)
{
    esp_host_header_t data_header = {
        .id = id,
        .sn = esp_random() % 0xFF,
        .len = len,
        .flags = {
            .version = 0,
        }
    };
    data_header.flags.type = ESP_ZNSP_TYPE_REQUEST;

    xSemaphoreTakeRecursive(lock_semaphore, portMAX_DELAY);
    esp_host_frame_output(&data_header, buffer, len);

    esp_host_zb_ctx_t host_ctx;
    xQueueReceive(output_queue, &host_ctx, portMAX_DELAY);
    if (host_ctx.data) {
        if ((host_ctx.id == id)) {
            if (output) {
                memcpy(output, host_ctx.data, host_ctx.size);
            }

            if (outlen) {
                *outlen = host_ctx.size;
            }
        }

        free(host_ctx.data);
        host_ctx.data = NULL;
    }
    xSemaphoreGiveRecursive(lock_semaphore);

    return  ESP_OK;
}

void *esp_zb_app_signal_get_params(uint32_t *signal_p)
{
    esp_zb_app_signal_msg_t *app_signal_msg = (esp_zb_app_signal_msg_t *)signal_p;

    return app_signal_msg ? (void *)app_signal_msg->msg : (void *)app_signal_msg;
}

void esp_zb_main_loop_iteration(void)
{
    esp_host_zb_ctx_t host_ctx;
    while (1) {
       if (xQueueReceive(notify_queue, &host_ctx, pdMS_TO_TICKS(100)) != pdTRUE) {
            continue;
       }

       for (int i = 0; i <= sizeof(host_zb_func_table) / sizeof(host_zb_func_table[0]); i ++) {
            if (host_ctx.id != host_zb_func_table[i].id) {
                continue;
            }

            host_zb_func_table[i].set_func(host_ctx.data, host_ctx.size);
            break;
        }

        if (host_ctx.data) {
            free(host_ctx.data);
            host_ctx.data = NULL;
        }
    }
}

esp_err_t esp_zb_device_register(esp_zb_ep_list_t *ep_list)
{
    return ESP_OK;
}

esp_err_t esp_zb_platform_config(esp_zb_platform_config_t *config)
{
    ESP_ERROR_CHECK(esp_host_init(config->host_config.host_mode));
    ESP_ERROR_CHECK(esp_host_start());

    output_queue = xQueueCreate(HOST_EVENT_QUEUE_LEN, sizeof(esp_host_zb_ctx_t));
    notify_queue = xQueueCreate(HOST_EVENT_QUEUE_LEN, sizeof(esp_host_zb_ctx_t));
    lock_semaphore = xSemaphoreCreateRecursiveMutex();

    return ESP_OK;
}