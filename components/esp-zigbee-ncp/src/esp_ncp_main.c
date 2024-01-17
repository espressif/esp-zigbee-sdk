/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nvs_flash.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "freertos/stream_buffer.h"
#include "sys/queue.h"

#include "esp_ncp_bus.h"
#include "esp_ncp_main.h"
#include "esp_ncp_frame.h"

#include "esp_zb_ncp.h"

static const char *TAG = "ESP_NCP_MAIN";

static esp_ncp_dev_t s_ncp_dev = {
    .run = false,
};

esp_err_t esp_ncp_send_event(esp_ncp_ctx_t *ncp_event)
{
    if (!s_ncp_dev.run || !s_ncp_dev.queue) {
        return ESP_FAIL;
    }

    BaseType_t ret = pdTRUE;
    if (xPortInIsrContext() == pdTRUE) {
        ret = xQueueSendFromISR(s_ncp_dev.queue, ncp_event, NULL);
    } else {
        ret = xQueueSend(s_ncp_dev.queue, ncp_event, 0);
    }
	
    return (ret == pdTRUE) ? ESP_OK : ESP_FAIL ;
}

static esp_err_t esp_ncp_process_event(esp_ncp_dev_t *dev, esp_ncp_ctx_t *ctx)
{
    esp_ncp_bus_t *bus = dev->bus;
    uint8_t *buffer = NULL;
    uint16_t recv_size = 0;
    esp_err_t ret = ESP_OK;

    if (!bus || !bus->input_buf || !bus->output_buf || !bus->read || !bus->write) {
        return ESP_FAIL;
    }

    buffer = calloc(1, ctx->size);
    if (buffer == NULL) {
        ESP_LOGE(TAG, "Process event out of memory");
        return ESP_ERR_NO_MEM;
    }

    switch (ctx->event) {
        case NCP_EVENT_INPUT:
            recv_size = xStreamBufferReceive(bus->input_buf, buffer, ctx->size, pdMS_TO_TICKS(NCP_TIMEOUT_MS));
            if (recv_size != ctx->size) {
                ESP_LOGE(TAG, "Input buffer receive error: size %d expect %d!", recv_size, ctx->size);
            } else {
                ESP_LOGD(TAG, "Bus write len %d", ctx->size);
                ret = bus->write(buffer, ctx->size);
            }
            break;
        case NCP_EVENT_OUTPUT:
            recv_size = xStreamBufferReceive(bus->output_buf, buffer, ctx->size, pdMS_TO_TICKS(NCP_TIMEOUT_MS));
            if (recv_size != ctx->size) {
                ESP_LOGE(TAG, "Output buffer receive error: size %d expect %d!", recv_size, ctx->size);
            } else {
                ret = esp_ncp_bus_output(buffer, ctx->size);
            }
            break;
        case NCP_EVENT_RESET:
            esp_restart();
            break;
        default:
            break;
    }
    free(buffer);

    return ret;
}

static void esp_ncp_main_task(void *pv) 
{
    esp_ncp_dev_t *dev = (esp_ncp_dev_t *)pv;
    esp_ncp_ctx_t ncp_ctx;

    dev->run = true;
    esp_ncp_bus_start(dev->bus);
    dev->queue = xQueueCreate(NCP_EVENT_QUEUE_LEN, sizeof(esp_ncp_ctx_t));

    while (dev->run) {
        if (xQueueReceive(dev->queue, &ncp_ctx, portMAX_DELAY) != pdTRUE) {
            continue;
        }

        if (esp_ncp_process_event(dev, &ncp_ctx) != ESP_OK) {
            ESP_LOGE(TAG, "Process event fail");
            break;
        }
    }

    esp_ncp_bus_stop(dev->bus);
    vQueueDelete(dev->queue);
    dev->queue = NULL;

    vTaskDelete(NULL);
}

esp_err_t esp_ncp_init(esp_ncp_host_connection_mode_t mode)
{
    esp_ncp_bus_t *bus = NULL;
    esp_err_t ret = esp_ncp_bus_init(&bus);

    s_ncp_dev.bus = bus;

    return (bus && bus->init) ? bus->init(mode) : ret;
}

esp_err_t esp_ncp_deinit(void)
{
    esp_ncp_bus_t *bus = s_ncp_dev.bus;

    if (!bus) {
        return ESP_OK;
    }

    if (bus->deinit) {
        bus->deinit();
    }

    esp_ncp_bus_deinit(bus);
    s_ncp_dev.bus = NULL;

    return ESP_OK;
}

esp_err_t esp_ncp_start(void)
{
    if (s_ncp_dev.run) {
        return ESP_ERR_INVALID_ARG;
    }

    return (xTaskCreate(esp_ncp_main_task, "esp_ncp_main_task", NCP_TASK_STACK, &s_ncp_dev, NCP_TASK_PRIORITY, NULL) == pdTRUE) ? ESP_OK : ESP_FAIL;
}

esp_err_t esp_ncp_stop(void)
{
    s_ncp_dev.run = false;

    return ESP_OK;
}
