/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee customized server Example
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
#include "esp_HA_customized_light.h"
#include "esp_zigbee_api_HA_standard.h"

static const char *TAG = "ESP_HA_ON_OFF_LIGHT";
/********************* Define functions **************************/
static void bdb_start_top_level_commissioning_cb(zb_uint8_t mode_mask)
{
    ESP_ERROR_CHECK(esp_zb_bdb_start_top_level_commissioning(mode_mask));
}

/**
 * @brief Zigbee stack event signal handler.
 *
 * @param bufid   Zigbee stack buffer id used to pass signal.
 */
void zboss_signal_handler(zb_bufid_t bufid)
{
    /* Read signal description out of memory buffer. */
    zb_zdo_app_signal_hdr_t *p_sg_p       = NULL;
    zb_ret_t                  status      = ZB_GET_APP_SIGNAL_STATUS(bufid);
    zb_zdo_app_signal_type_t sig = zb_get_app_signal(bufid, &p_sg_p);
    zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;
    switch (sig) {
    case ZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Zigbee stack initialized");
        esp_zb_bdb_start_top_level_commissioning(ZB_BDB_INITIALIZATION);
        break;
    case ZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case ZB_BDB_SIGNAL_DEVICE_REBOOT:
        if (status == RET_OK) {
            ESP_LOGI(TAG, "Start network formation");
            esp_zb_bdb_start_top_level_commissioning(ZB_BDB_NETWORK_FORMATION);
        } else {
            ESP_LOGE(TAG, "Failed to initialize Zigbee stack (status: %d)", status);
        }
        break;
    case ZB_BDB_SIGNAL_FORMATION:
        if (status == RET_OK) {
            zb_ext_pan_id_t extended_pan_id;
            esp_zb_get_extended_pan_id(extended_pan_id);
            ESP_LOGI(TAG, "Formed network successfully (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx)",
                     extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4],
                     extended_pan_id[3], extended_pan_id[2], extended_pan_id[1], extended_pan_id[0],
                     ZB_PIBCACHE_PAN_ID());
            esp_zb_bdb_start_top_level_commissioning(ZB_BDB_NETWORK_STEERING);
        } else {
            ESP_LOGI(TAG, "Restart network formation (status: %d)", status);
            ZB_SCHEDULE_APP_ALARM((zb_callback_t)bdb_start_top_level_commissioning_cb, ZB_BDB_NETWORK_FORMATION, ZB_TIME_ONE_SECOND);
        }
        break;

    case ZB_BDB_SIGNAL_STEERING:
        if (status == RET_OK) {
            ESP_LOGI(TAG, "Network steering started");
        }
        break;

    case ZB_ZDO_SIGNAL_DEVICE_ANNCE:
        dev_annce_params = ZB_ZDO_SIGNAL_GET_PARAMS(p_sg_p, zb_zdo_signal_device_annce_params_t);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->device_short_addr);
        break;
    case ZB_ZDO_SIGNAL_LEAVE_INDICATION:
        zb_zdo_signal_leave_indication_params_t *leave_ind_params = ZB_ZDO_SIGNAL_GET_PARAMS(p_sg_p, zb_zdo_signal_leave_indication_params_t);
        if (!leave_ind_params->rejoin) {
            esp_zb_ieee_addr_t leave_addr;
            memcpy(leave_addr, leave_ind_params->device_addr, sizeof(esp_zb_ieee_addr_t));
            ESP_LOGI(TAG, "Zigbee Node is leaving network: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x)",
                     leave_addr[7], leave_addr[6], leave_addr[5], leave_addr[4],
                     leave_addr[3], leave_addr[2], leave_addr[1], leave_addr[0]);
        }
        break;
    default:
        ESP_LOGI(TAG, "status: %d", status);
        break;
    }
    /* All callbacks should either reuse or free passed buffers. If bufid == 0, the buffer is invalid (not passed) */
    if (bufid) {
        zb_buf_free(bufid);
    }
}

void attr_cb(uint8_t status, uint8_t endpoint, uint16_t cluster_id, uint16_t attr_id, void *new_value)
{
    if (cluster_id == ZB_ZCL_CLUSTER_ID_ON_OFF) {
        uint8_t value = *(uint8_t *)new_value;
        if (attr_id == ZB_ZCL_ATTR_ON_OFF_ON_OFF_ID) {
            /* implemented light on/off control */
            ESP_LOGI(TAG, "on/off light set to %hd", value);
            light_driver_set_power((zb_bool_t)value);
        }
    } else {
        /* Implement some actions if needed when other cluster changed */
        ESP_LOGI(TAG, "cluster:0x%x, attribute:0x%x changed ", cluster_id, attr_id);
    }
}

static void esp_zb_task(void *pvParameters)
{
    /* initialize Zigbee stack with Zigbee coordinator config */
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZC_CONFIG();
    esp_zb_init(&zb_nwk_cfg);
    uint8_t test_attr, test_attr2;
    test_attr = 0;
    test_attr2 = 3;
    /* basic cluster create with fully customized */
    esp_zb_attribute_list_t *esp_zb_basic_cluster = esp_zb_zcl_attr_list_create(ZB_ZCL_CLUSTER_ID_BASIC);
    esp_zb_cluster_add_attr(esp_zb_basic_cluster, ZB_ZCL_ATTR_BASIC_ZCL_VERSION_ID, &test_attr);
    esp_zb_cluster_add_attr(esp_zb_basic_cluster, ZB_ZCL_ATTR_BASIC_POWER_SOURCE_ID, &test_attr);
    esp_zb_cluster_update_attr(esp_zb_basic_cluster, ZB_ZCL_ATTR_BASIC_ZCL_VERSION_ID, &test_attr2);
    /* identify cluster create with fully customized */
    esp_zb_attribute_list_t *esp_zb_identify_cluster = esp_zb_zcl_attr_list_create(ZB_ZCL_CLUSTER_ID_IDENTIFY);
    esp_zb_cluster_add_attr(esp_zb_identify_cluster, ZB_ZCL_ATTR_IDENTIFY_IDENTIFY_TIME_ID, &test_attr);
    /* group cluster create with fully customized */
    esp_zb_attribute_list_t *esp_zb_groups_cluster = esp_zb_zcl_attr_list_create(ZB_ZCL_CLUSTER_ID_GROUPS);
    esp_zb_cluster_add_attr(esp_zb_groups_cluster, ZB_ZCL_ATTR_GROUPS_NAME_SUPPORT_ID, &test_attr);
    /* scenes cluster create with standard cluster + customized */
    esp_zb_attribute_list_t *esp_zb_scenes_cluster = esp_zb_scenes_cluster_create(NULL);
    esp_zb_cluster_update_attr(esp_zb_scenes_cluster, ZB_ZCL_ATTR_SCENES_NAME_SUPPORT_ID, &test_attr);
    /* on-off cluster create with standard cluster config*/
    esp_zb_on_off_cluster_cfg_t on_off_cfg;
    on_off_cfg.on_off = ZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE;
    esp_zb_attribute_list_t *esp_zb_on_off_cluster = esp_zb_on_off_cluster_create(&on_off_cfg);
    /* create cluster lists for this endpoint */
    esp_zb_cluster_list_t *esp_zb_cluster_list = esp_zb_zcl_cluster_list_create();
    esp_zb_cluster_list_add_cluster(esp_zb_cluster_list, esp_zb_basic_cluster, ZB_ZCL_CLUSTER_SERVER_ROLE);
    /* update basic cluster in the existed cluster list */
    esp_zb_cluster_list_update_cluster(esp_zb_cluster_list, esp_zb_basic_cluster_create(NULL), ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_cluster(esp_zb_cluster_list, esp_zb_identify_cluster, ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_cluster(esp_zb_cluster_list, esp_zb_groups_cluster, ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_cluster(esp_zb_cluster_list, esp_zb_scenes_cluster, ZB_ZCL_CLUSTER_SERVER_ROLE);
    esp_zb_cluster_list_add_cluster(esp_zb_cluster_list, esp_zb_on_off_cluster, ZB_ZCL_CLUSTER_SERVER_ROLE);

    esp_zb_ep_list_t *esp_zb_ep_list = esp_zb_ep_list_create();
    /* add created endpoint (cluster_list) to endpoint list */
    esp_zb_ep_list_add_ep(esp_zb_ep_list, esp_zb_cluster_list, HA_ESP_LIGHT_ENDPOINT, ZB_AF_HA_PROFILE_ID, ZB_HA_ON_OFF_OUTPUT_DEVICE_ID);
    esp_zb_device_register(esp_zb_ep_list);
    esp_zb_device_add_set_attr_value_cb(attr_cb);
    ESP_ERROR_CHECK(esp_zb_start(false));
    esp_zb_main_loop_iteration();
}

void app_main(void)
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    /* load Zigbee platform config to initialization */
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    /* hardware related and device init */
    light_driver_init(LIGHT_DEFAULT_OFF);
    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
