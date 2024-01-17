/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <sys/select.h>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/stream_buffer.h"

#include "esp_log.h"
#include "driver/uart.h"

#include "esp_ncp_bus.h"
#include "esp_ncp_frame.h"
#include "esp_ncp_main.h"

static const char* TAG = "ESP_NCP_BUS";

static QueueHandle_t uart0_queue;
static esp_ncp_bus_t *s_ncp_bus;

static esp_err_t ncp_bus_read_hdl(void *buffer, uint16_t size)
{
    return ESP_FAIL;
}

static esp_err_t ncp_bus_write_hdl(void *buffer, uint16_t size)
{
    return (uart_write_bytes(CONFIG_NCP_BUS_UART_NUM, (const char*) buffer, size) == size) ? ESP_OK : ESP_ERR_INVALID_SIZE;
}

static esp_err_t ncp_bus_deinit_hdl(void)
{
    return uart_driver_delete(CONFIG_NCP_BUS_UART_NUM);
}

static esp_err_t ncp_bus_init_hdl(uint8_t transport)
{
    uart_config_t uart_config = {
        .baud_rate = CONFIG_NCP_BUS_UART_BAUD_RATE,
        .data_bits = CONFIG_NCP_BUS_UART_BYTE_SIZE,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = CONFIG_NCP_BUS_UART_STOP_BITS,
        .flow_ctrl = CONFIG_NCP_BUS_UART_FLOW_CONTROL,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_driver_install(CONFIG_NCP_BUS_UART_NUM, NCP_BUS_BUF_SIZE * 2, NCP_BUS_BUF_SIZE * 2, 20, &uart0_queue, 0);
    uart_param_config(CONFIG_NCP_BUS_UART_NUM, &uart_config);
    uart_set_pin(CONFIG_NCP_BUS_UART_NUM, CONFIG_NCP_BUS_UART_TX_PIN, CONFIG_NCP_BUS_UART_RX_PIN, CONFIG_NCP_BUS_UART_RTS_PIN, CONFIG_NCP_BUS_UART_CTS_PIN);

    return ESP_OK;
}

static void esp_ncp_bus_task(void *pvParameter)
{
    uart_event_t event;
    uint8_t *dtmp = (uint8_t*)malloc(NCP_BUS_BUF_SIZE);

    esp_ncp_bus_t *bus = (esp_ncp_bus_t *)pvParameter;
    bus->state = BUS_INIT_START;
    esp_ncp_ctx_t ncp_event = {
        .event = NCP_EVENT_OUTPUT,
    };

    while (bus->state == BUS_INIT_START) {
        if (xQueueReceive(uart0_queue, (void *)&event, (TickType_t)portMAX_DELAY)) {
            bzero(dtmp, NCP_BUS_BUF_SIZE);
            switch(event.type) {
                case UART_DATA:
                    ncp_event.size = uart_read_bytes(CONFIG_NCP_BUS_UART_NUM, dtmp, event.size, portMAX_DELAY);
                    xStreamBufferSend(bus->output_buf, dtmp, ncp_event.size, 0);
                    esp_ncp_send_event(&ncp_event);
                    break;
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG, "hw fifo overflow");
                    uart_flush_input(CONFIG_NCP_BUS_UART_NUM);
                    xQueueReset(uart0_queue);
                    break;
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full");
                    uart_flush_input(CONFIG_NCP_BUS_UART_NUM);
                    xQueueReset(uart0_queue);
                    break;
                default:
                    ESP_LOGI(TAG, "uart event type: %d", event.type);
                    break;
            }
        }
    }

    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}

esp_err_t esp_ncp_bus_input(const void *buffer, uint16_t len)
{
    if (buffer == NULL) {
        return ESP_FAIL;
    }

    esp_ncp_bus_t *bus = s_ncp_bus;
    esp_ncp_ctx_t ncp_event = {
        .event = NCP_EVENT_INPUT,
    };
    int count = NCP_BUS_RINGBUF_TIMEOUT_MS / 10;
    size_t ret_size = 0;

    if (bus->input_buf == NULL) {
        return ESP_FAIL;
    }

    while (xStreamBufferSpacesAvailable(bus->input_buf) < len) {
        if(count == 0) break;
        vTaskDelay(pdMS_TO_TICKS(10));
        count --;
    }

    if (count == 0) {
        ESP_LOGE(TAG, "input_buf not enough");
        return ESP_FAIL;
    }

    xSemaphoreTake(bus->input_sem, portMAX_DELAY);
    ret_size = xStreamBufferSend(bus->input_buf, buffer, len, 0);
    xSemaphoreGive(bus->input_sem);
    if (ret_size != len) {
        ESP_LOGE(TAG, "input_buf send error: size %d expect %d", ret_size, len);
        return ESP_FAIL;
    } else {
        ncp_event.size = len;
        return esp_ncp_send_event(&ncp_event);
    }
}

esp_err_t esp_ncp_bus_output(const void *buffer, uint16_t len)
{
    return esp_ncp_frame_output(buffer, len);
}

esp_err_t esp_ncp_bus_init(esp_ncp_bus_t **bus)
{
    esp_ncp_bus_t *bus_handle = calloc(1, sizeof(esp_ncp_bus_t));

    if (!bus_handle) {
        return ESP_ERR_NO_MEM;
    }

    bus_handle->input_buf = xStreamBufferCreate(NCP_BUS_RINGBUF_SIZE, 8);
    if (bus_handle->input_buf == NULL) {
        ESP_LOGE(TAG, "Input buffer create error");
        esp_ncp_bus_deinit(bus_handle);
        return ESP_ERR_NO_MEM;
    }

    bus_handle->output_buf = xStreamBufferCreate(NCP_BUS_RINGBUF_SIZE, 8);
    if (bus_handle->output_buf == NULL) {
        ESP_LOGE(TAG, "Out buffer create error");
        esp_ncp_bus_deinit(bus_handle);
        return ESP_ERR_NO_MEM;
    }

    bus_handle->input_sem = xSemaphoreCreateMutex();
    if (bus_handle->input_sem == NULL) {
        ESP_LOGE(TAG, "Input semaphore create error");
        esp_ncp_bus_deinit(bus_handle);
        return ESP_ERR_NO_MEM;
    }

    bus_handle->init = ncp_bus_init_hdl;
    bus_handle->deinit = ncp_bus_deinit_hdl;
    bus_handle->read = ncp_bus_read_hdl;
    bus_handle->write = ncp_bus_write_hdl;

    *bus = bus_handle;
    s_ncp_bus = bus_handle;

    return ESP_OK;
}

esp_err_t esp_ncp_bus_start(esp_ncp_bus_t *bus)
{
    if (!bus) {
        ESP_LOGE(TAG, "Invalid handle when start bus");
        return ESP_ERR_INVALID_ARG;
    }

    if (bus->state == BUS_INIT_START) {
        ESP_LOGE(TAG, "Invalid state %d when start bus", bus->state);
        return ESP_FAIL;
    }

    return (xTaskCreate(esp_ncp_bus_task, "esp_ncp_bus_task", NCP_BUS_TASK_STACK, bus, NCP_BUS_TASK_PRIORITY, NULL) == pdTRUE) ? ESP_OK : ESP_FAIL;
}

esp_err_t esp_ncp_bus_stop(esp_ncp_bus_t *bus)
{
    if (!bus) {
        ESP_LOGE(TAG, "Invalid handle when stop bus");
        return ESP_ERR_INVALID_ARG;
    }

    if (bus->state != BUS_INIT_START) {
        ESP_LOGE(TAG, "Invalid state %d when stop bus", bus->state);
        return ESP_FAIL;
    }

    bus->state = BUS_INIT_STOP;

    return ESP_OK;
}

esp_err_t esp_ncp_bus_deinit(esp_ncp_bus_t *bus)
{
    if (!bus) {
        ESP_LOGE(TAG, "Invalid handle when deinit");
        return ESP_ERR_INVALID_ARG;
    }

    if (bus->output_buf) {
        vStreamBufferDelete(bus->output_buf);
        bus->output_buf = NULL;

    }

    if (bus->input_buf) {
        vStreamBufferDelete(bus->input_buf);
        bus->input_buf = NULL;
    }

    if (bus->input_sem) {
        vSemaphoreDelete(bus->input_sem);
        bus->input_sem = NULL;
    }

    free(bus);
    s_ncp_bus = NULL;

    return ESP_OK;
}


