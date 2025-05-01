/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "freertos/stream_buffer.h"

#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_system.h"

#include "esp_host_bus.h"
#include "esp_host_main.h"

#include "zb_config_platform.h"

static const char *TAG = "ESP_ZNSP_MAIN";

static esp_host_dev_t s_host_dev = {
    .run = false,
};

esp_err_t esp_host_send_event(esp_host_ctx_t *host_event)
{
    if (!s_host_dev.run || !s_host_dev.queue) {
        return ESP_FAIL;
    }

    BaseType_t ret = pdTRUE;
    if (xPortInIsrContext() == pdTRUE) {
        ret = xQueueSendFromISR(s_host_dev.queue, host_event, NULL);
    } else {
        ret = xQueueSend(s_host_dev.queue, host_event, 0);
    }
	
    return (ret == pdTRUE) ? ESP_OK : ESP_FAIL ;
}

static esp_err_t esp_host_process_event(esp_host_dev_t *dev, esp_host_ctx_t *ctx)
{
    esp_host_bus_t *bus = dev->bus;
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
        case HOST_EVENT_OUTPUT:
            recv_size = xStreamBufferReceive(bus->output_buf, buffer, ctx->size, pdMS_TO_TICKS(HOST_TIMEOUT_MS));
            if (recv_size != ctx->size) {
                ESP_LOGE(TAG, "Output buffer receive error: size %d expect %d!", recv_size, ctx->size);
            } else {
                ESP_LOGD(TAG, "Bus write len %d", ctx->size);
                ret = bus->write(buffer, ctx->size);
            }
            break;
        case HOST_EVENT_INPUT:
            recv_size = xStreamBufferReceive(bus->input_buf, buffer, ctx->size, pdMS_TO_TICKS(HOST_TIMEOUT_MS));
            if (recv_size != ctx->size) {
                ESP_LOGE(TAG, "Input buffer receive error: size %d expect %d!", recv_size, ctx->size);
            } else {
                ret = esp_host_bus_input(buffer, ctx->size);
            }
            break;
        case HOST_EVENT_RESET:
            esp_restart();
            break;
        default:
            break;
    }
    free(buffer);

    return ret;
}

static void esp_host_main_task(void *pv) 
{
    esp_host_dev_t *dev = (esp_host_dev_t *)pv;
    esp_host_ctx_t host_ctx;

    dev->run = true;
    esp_host_bus_start(dev->bus);
    dev->queue = xQueueCreate(HOST_EVENT_QUEUE_LEN, sizeof(esp_host_ctx_t));
    
    while (dev->run) {
        if (xQueueReceive(dev->queue, &host_ctx, portMAX_DELAY) != pdTRUE) {
            continue;
        }

        if (esp_host_process_event(dev, &host_ctx) != ESP_OK) {
            ESP_LOGE(TAG, "Process event fail");
            break;
        }
    }

    esp_host_bus_stop(dev->bus);
    vQueueDelete(dev->queue);
    dev->queue = NULL;

    vTaskDelete(NULL);
}

esp_err_t esp_host_init(esp_host_connection_mode_t mode)
{
    esp_host_bus_t *bus = NULL;
    esp_err_t ret = esp_host_bus_init(&bus);

    s_host_dev.bus = bus;

    return (bus && bus->init) ? bus->init(mode) : ret;
}

esp_err_t esp_host_deinit(void)
{
    esp_host_bus_t *bus = s_host_dev.bus;

    if (!bus) {
        return ESP_OK;
    }

    if (bus->deinit) {
        bus->deinit();
    }

    esp_host_bus_deinit(bus);
    s_host_dev.bus = NULL;

    return ESP_OK;
}

esp_err_t esp_host_start(void)
{
    if (s_host_dev.run) {
        return ESP_ERR_INVALID_ARG;
    }

    return (xTaskCreate(esp_host_main_task, "esp_host_main_task", HOST_TASK_STACK, &s_host_dev, HOST_TASK_PRIORITY, NULL) == pdTRUE) ? ESP_OK : ESP_FAIL;
}

esp_err_t esp_host_stop(void)
{
    s_host_dev.run = false;

    return ESP_OK;
}
