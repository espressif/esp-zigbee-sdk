/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee RCP Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "zb_scheduler.h"
#include "esp_zigbee_rcp.h"

#if (defined ZB_MACSPLIT_HOST && !defined ZB_MACSPLIT_DEVICE)
#error Only Zigbee rcp device should be defined
#endif
static const char *TAG = "ESP_ZB_RCP";

void zboss_signal_handler(zb_bufid_t bufid)
{
    zb_zdo_app_signal_hdr_t *sg_p = NULL;
    /* get application signal from the buffer */
    zb_zdo_app_signal_type_t sig =  zb_get_app_signal(bufid, &sg_p);

    if (ZB_GET_APP_SIGNAL_STATUS(bufid) == 0) {
        switch (sig) {
        case ZB_COMMON_SIGNAL_CAN_SLEEP:
#if defined(ZB_USE_SLEEP)
            zb_sleep_now();
#endif
            break;
        default: break;
        }
    } else if (sig == ZB_ZDO_SIGNAL_PRODUCTION_CONFIG_READY) {
        ESP_LOGI(TAG, "Production config is not present or invalid");
    } else {
        ESP_LOGI(TAG, "Device started FAILED status %d", ZB_GET_APP_SIGNAL_STATUS(bufid));
    }

    if (bufid) {
        zb_buf_free(bufid);
    }
}

static void esp_zb_task(void * pvParameters)
{
    ZB_INIT("esp_zigbee_rcp");
    while (1) {
        zb_sched_loop_iteration();
    }
}

void app_main(void)
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    /* load Zigbee rcp platform config to initialization */
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
