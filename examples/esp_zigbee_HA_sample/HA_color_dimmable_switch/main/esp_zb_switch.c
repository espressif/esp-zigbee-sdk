/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee HA_color_dimmable_switch Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include "nvs_flash.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ha/esp_zigbee_ha_standard.h"
#include "esp_zb_switch.h"

/**
 * @note Make sure set idf.py menuconfig in zigbee component as zigbee coordinator device!
*/
#if defined ZB_ED_ROLE
#error Define ZB_COORDINATOR_ROLE in idf.py menuconfig to compile light switch source code.
#endif

/* define a single remote device struct for managing */
typedef struct light_bulb_device_params_s {
    esp_zb_ieee_addr_t ieee_addr;
    uint8_t  endpoint;
    uint16_t short_addr;
} light_bulb_device_params_t;

/* define Button function currently only 1 switch define */
static switch_func_pair_t button_func_pair[] = {
    {GPIO_INPUT_IO_TOGGLE_SWITCH, SWITCH_ONOFF_TOGGLE_CONTROL}
};

/* R, G, B of color x,y define table */
static uint16_t color_x_table[3] = {
    41942, 19660, 9830
};
static uint16_t color_y_table[3] = {
    21626, 38321, 3932
};

static const char *TAG = "ESP_ZB_COLOR_DIMM_SWITCH";

/* declare a remote device for recording and managing node info */
light_bulb_device_params_t color_light;

/********************* Define functions **************************/
/**
 * @brief Callback for button events, currently only toggle event available
 *
 * @param button_func_pair      Incoming event from the button_pair.
 */
static void esp_zb_buttons_handler(switch_func_pair_t *button_func_pair)
{
    uint8_t step = 10;
    static uint8_t level_value = 5;
    static uint8_t press_count = 0;
    if (button_func_pair->func == SWITCH_ONOFF_TOGGLE_CONTROL) {
        /* implemented light switch toggle functionality */
        uint16_t refer_x = color_x_table[press_count % 3];
        uint16_t refer_y = color_y_table[press_count % 3];
        if (press_count % 2 == 1) {
            /* changing the color control command by button pressed */
            esp_zb_zcl_color_move_to_color_cmd_t cmd_color;
            cmd_color.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
            cmd_color.color_x = refer_x;
            cmd_color.color_y = refer_y;
            cmd_color.transition_time = 0;
            cmd_color.zcl_basic_cmd.dst_addr_u.addr_short = color_light.short_addr;
            cmd_color.zcl_basic_cmd.dst_endpoint = color_light.endpoint;
            cmd_color.zcl_basic_cmd.src_endpoint = HA_COLOR_DIMMABLE_SWITCH_ENDPOINT;
            ESP_EARLY_LOGI(TAG, "send 'color move to color' command color_x:%d,color_y:%d", refer_x, refer_y);
            esp_zb_zcl_color_move_to_color_cmd_req(&cmd_color);
        } else {
            /* changing the level control command by button pressed */
            esp_zb_zcl_move_to_level_cmd_t cmd_level;
            cmd_level.zcl_basic_cmd.dst_addr_u.addr_short = color_light.short_addr;
            cmd_level.zcl_basic_cmd.dst_endpoint = color_light.endpoint;
            cmd_level.zcl_basic_cmd.src_endpoint = HA_COLOR_DIMMABLE_SWITCH_ENDPOINT;
            cmd_level.address_mode = ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT;
            cmd_level.level = level_value;
            cmd_level.transition_time = 0xffff;
            ESP_EARLY_LOGI(TAG, "send 'move to level' command:%d", level_value);
            esp_zb_zcl_level_move_to_level_with_onoff_cmd_req(&cmd_level);
            level_value += step;
        }
        press_count++;
    }
}

static void bdb_start_top_level_commissioning_cb(uint8_t mode_mask)
{
    ESP_ERROR_CHECK(esp_zb_bdb_start_top_level_commissioning(mode_mask));
}

void user_find_cb(esp_zb_zdp_status_t zdo_status, uint16_t addr, uint8_t endpoint, void *user_ctx)
{
    ESP_LOGI(TAG, "User find cb: response_status:%d, address:0x%x, endpoint:%d", zdo_status, addr, endpoint);
    if (zdo_status == ESP_ZB_ZDP_STATUS_SUCCESS) {
        color_light.endpoint = endpoint;
        color_light.short_addr = addr;
    }
}

void esp_zb_app_signal_handler(esp_zb_app_signal_t *signal_struct)
{
    uint32_t *p_sg_p       = signal_struct->p_app_signal;
    esp_err_t err_status = signal_struct->esp_err_status;
    esp_zb_app_signal_type_t sig_type = *p_sg_p;
    esp_zb_zdo_signal_device_annce_params_t *dev_annce_params = NULL;
    switch (sig_type) {
    case ESP_ZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Zigbee stack initialized");
        esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_INITIALIZATION);
        break;
    case ESP_ZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case ESP_ZB_BDB_SIGNAL_DEVICE_REBOOT:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Start network formation");
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_FORMATION);
        } else {
            ESP_LOGE(TAG, "Failed to initialize Zigbee stack (status: %d)", err_status);
        }
        break;
    case ESP_ZB_BDB_SIGNAL_FORMATION:
        if (err_status == ESP_OK) {
            esp_zb_ieee_addr_t extended_pan_id;
            esp_zb_get_extended_pan_id(extended_pan_id);
            ESP_LOGI(TAG, "Formed network successfully (Extended PAN ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x, PAN ID: 0x%04hx, Channel:%d)",
                     extended_pan_id[7], extended_pan_id[6], extended_pan_id[5], extended_pan_id[4],
                     extended_pan_id[3], extended_pan_id[2], extended_pan_id[1], extended_pan_id[0],
                     esp_zb_get_pan_id(), esp_zb_get_current_channel());
            esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_STEERING);
        } else {
            ESP_LOGI(TAG, "Restart network formation (status: %d)", err_status);
            esp_zb_scheduler_alarm((esp_zb_callback_t)bdb_start_top_level_commissioning_cb, ESP_ZB_BDB_MODE_NETWORK_FORMATION, 1000);
        }
        break;
    case ESP_ZB_BDB_SIGNAL_STEERING:
        if (err_status == ESP_OK) {
            ESP_LOGI(TAG, "Network steering started");
        }
        break;
    case ESP_ZB_ZDO_SIGNAL_DEVICE_ANNCE:
        dev_annce_params = (esp_zb_zdo_signal_device_annce_params_t *)esp_zb_app_signal_get_params(p_sg_p);
        ESP_LOGI(TAG, "New device commissioned or rejoined (short: 0x%04hx)", dev_annce_params->device_short_addr);
        esp_zb_zdo_match_desc_req_param_t  cmd_req;
        cmd_req.dst_nwk_addr = dev_annce_params->device_short_addr;
        cmd_req.addr_of_interest = dev_annce_params->device_short_addr;
        /* find color dimmable light once device joining the network */
        esp_zb_zdo_find_color_dimmable_light(&cmd_req, user_find_cb, NULL);
        break;
    default:
        ESP_LOGI(TAG, "ZDO signal: %d, status: %d", sig_type, err_status);
        break;
    }
}

static void esp_zb_task(void *pvParameters)
{
    /* initialize Zigbee stack with Zigbee coordinator config */
    esp_zb_cfg_t zb_nwk_cfg = ESP_ZB_ZC_CONFIG();
    esp_zb_init(&zb_nwk_cfg);
    /* set the color dimmable switch device config */
    esp_zb_color_dimmable_switch_cfg_t switch_cfg = ESP_ZB_DEFAULT_COLOR_DIMMABLE_SWITCH_CONFIG();
    esp_zb_ep_list_t *esp_zb_color_dimm_switch_ep = esp_zb_color_dimmable_switch_ep_create(HA_COLOR_DIMMABLE_SWITCH_ENDPOINT, &switch_cfg);
    esp_zb_device_register(esp_zb_color_dimm_switch_ep);
    esp_zb_set_primary_network_channel_set(ESP_ZB_PRIMARY_CHANNEL_MASK);
    ESP_ERROR_CHECK(esp_zb_start(false));
    esp_zb_main_loop_iteration();
}

void app_main(void)
{
    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };
    ESP_ERROR_CHECK(nvs_flash_init());
    /* load Zigbee switch platform config to initialization */
    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
    /* hardware related and device init */
    switch_driver_init(button_func_pair, PAIR_SIZE(button_func_pair), esp_zb_buttons_handler);
    xTaskCreate(esp_zb_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
