/*
 * SPDX-FileCopyrightText: 2022-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "esp_check.h"
#include "esp_err.h"
#include "esp_log.h"
#include "nvs_flash.h"

#ifdef CONFIG_PM_ENABLE
#include "esp_pm.h"
#include "esp_sleep.h"
#endif

#if CONFIG_ESP_SLEEP_DEBUG
#include "esp_private/esp_pmu.h"
#include "esp_private/esp_sleep_internal.h"
#endif

#if SOC_RTCIO_INPUT_OUTPUT_SUPPORTED
#include "driver/rtc_io.h"
#endif

#include "switch_driver.h"
#include "alarm_timer.h"

#include "esp_zigbee.h"
#include "ezbee/zha.h"

#include "light_sleep_end_device.h"

static const char *TAG = "LIGHT_SLEEP_END_DEVICE";

static void button_event_handler(switch_driver_handle_t handle)
{
    ESP_RETURN_ON_FALSE(handle != SWITCH_INV_HANDLE, , TAG, "Invalid switch handle");

    ezb_zcl_on_off_cmd_t cmd_req = {
        .cmd_ctrl =
            {
                .dst_addr.addr_mode = EZB_ADDR_MODE_NONE,
                .src_ep             = ESP_ZIGBEE_HA_ON_OFF_SWITCH_EP_ID,
            },
    };
    esp_zigbee_lock_acquire(portMAX_DELAY);
    ezb_zcl_on_off_toggle_cmd_req(&cmd_req);
    esp_zigbee_lock_release();
    ESP_EARLY_LOGI(TAG, "Toggle ZCL On/Off");
}

static esp_err_t deferred_driver_init(void)
{
    static bool is_inited = false;

    ESP_RETURN_ON_FALSE(!is_inited, ESP_OK, TAG, "Deferred driver already initialized");

    switch_driver_config_t config = {
        .gpio_num = CONFIG_GPIO_EXT1_WAKEUP_SOURCE,
        .event_cb = button_event_handler,
    };
    switch_driver_handle_t handle = switch_driver_init(&config);

    /* Configure the BOOT button on devkit to wake up the device */
    ESP_ERROR_CHECK(esp_sleep_enable_ext1_wakeup(BIT(CONFIG_GPIO_EXT1_WAKEUP_SOURCE), ESP_EXT1_WAKEUP_ANY_LOW));
    ESP_ERROR_CHECK(gpio_wakeup_enable(CONFIG_GPIO_EXT1_WAKEUP_SOURCE, GPIO_INTR_LOW_LEVEL));

#if SOC_RTCIO_INPUT_OUTPUT_SUPPORTED
    rtc_gpio_pulldown_dis(CONFIG_GPIO_EXT1_WAKEUP_SOURCE);
    rtc_gpio_pullup_en(CONFIG_GPIO_EXT1_WAKEUP_SOURCE);
#else
    gpio_pulldown_dis(CONFIG_GPIO_EXT1_WAKEUP_SOURCE);
    gpio_pullup_en(CONFIG_GPIO_EXT1_WAKEUP_SOURCE);
#endif

    is_inited = handle == SWITCH_INV_HANDLE ? false : true;

    return is_inited ? ESP_OK : ESP_FAIL;
}

static void zdo_bind_ha_light_device_result(const ezb_zdp_bind_req_result_t *result, void *user_ctx)
{
    assert(result);
    if (result->error == EZB_ERR_NONE) {
        if (result->rsp && result->rsp->status == EZB_ZDP_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "Bound HA light device successfully");
        } else {
            ESP_LOGE(TAG, "Failed to bind HA light device with status (0x%02x)", result->rsp->status);
        }
    } else {
        ESP_LOGE(TAG, "Failed to bind HA light device with error (0x%04x)", result->error);
    }
}

static ezb_err_t zdo_bind_ha_light_device(uint16_t dst_short_addr, uint8_t dst_ep)
{
    ezb_err_t          ret      = EZB_ERR_FAIL;
    ezb_zdo_bind_req_t bind_req = {
        .dst_nwk_addr = ezb_nwk_get_short_address(),
        .field =
            {
                .src_ep        = ESP_ZIGBEE_HA_ON_OFF_SWITCH_EP_ID,
                .cluster_id    = EZB_ZCL_CLUSTER_ID_ON_OFF,
                .dst_addr_mode = EZB_ADDR_MODE_EXT,
                .dst_ep        = dst_ep,
            },
        .cb       = zdo_bind_ha_light_device_result,
        .user_ctx = NULL,
    };
    ezb_nwk_get_extended_address(&bind_req.field.src_addr);

    ESP_RETURN_ON_ERROR(ezb_address_extended_by_short(dst_short_addr, &bind_req.field.dst_addr.extended_addr), TAG,
                        "Failed to get extended address for destination device(0x%04hx)", dst_short_addr);

    ret = ezb_zdo_bind_req(&bind_req);
    if (ret == EZB_ERR_NONE) {
        ESP_LOGI(TAG, "Attempt to bind HA light device (short address: 0x%04hx)", dst_short_addr);
    } else {
        ESP_LOGE(TAG, "Failed to bind HA light device (short address: 0x%04hx) with error(0x%04x)", dst_short_addr, ret);
    }
    return ret;
}

static void zdo_find_ha_light_device_result(const ezb_zdo_match_desc_req_result_t *result, void *user_ctx)
{
    assert(result);
    if (result->error == EZB_ERR_NONE) {
        if (result->rsp && result->rsp->status == EZB_ZDP_STATUS_SUCCESS && result->rsp->match_length > 0 &&
            result->rsp->match_list) {
            for (size_t i = 0; i < result->rsp->match_length; i++) {
                zdo_bind_ha_light_device(result->rsp->nwk_addr_of_interest, result->rsp->match_list[i]);
            }
        }
    } else {
        ESP_LOGE(TAG, "Failed to find HA light device in the network with error(0x%04x)", result->error);
    }
}

static ezb_err_t zdo_find_ha_light_device(void)
{
    ezb_err_t ret             = EZB_ERR_FAIL;
    uint16_t  cluster_list[1] = {EZB_ZCL_CLUSTER_ID_ON_OFF};

    ezb_zdo_match_desc_req_t req = {
        .dst_nwk_addr = 0xFFFD,
        .field =
            {
                .nwk_addr_of_interest = 0xFFFD,
                .profile_id           = EZB_AF_HA_PROFILE_ID,
                .num_in_clusters      = 1,
                .num_out_clusters     = 0,
                .cluster_list         = cluster_list,
            },
        .cb       = zdo_find_ha_light_device_result,
        .user_ctx = NULL,
    };
    ret = ezb_zdo_match_desc_req(&req);
    if (ret == EZB_ERR_NONE) {
        ESP_LOGI(TAG, "Attempt to find HA light device in the network");
    } else {
        ESP_LOGE(TAG, "Failed to find HA light device in the network with error(0x%04x)", ret);
    }
    return ret;
}

static void esp_zigbee_alarm_bdb_commissioning(alarm_timer_arg_t arg)
{
    esp_zigbee_lock_acquire(portMAX_DELAY);
    (void)ezb_bdb_start_top_level_commissioning(arg);
    esp_zigbee_lock_release();
}

static bool esp_zigbee_app_signal_handler(const ezb_app_signal_t *app_signal)
{
    ezb_app_signal_type_t signal_type = ezb_app_signal_get_type(app_signal);

    switch (signal_type) {
    case EZB_ZDO_SIGNAL_SKIP_STARTUP:
        ESP_LOGI(TAG, "Initialize Zigbee stack");
        ezb_bdb_start_top_level_commissioning(EZB_BDB_MODE_INITIALIZATION);
        break;
    case EZB_BDB_SIGNAL_DEVICE_FIRST_START:
    case EZB_BDB_SIGNAL_DEVICE_REBOOT: {
        ezb_bdb_comm_status_t status = *((ezb_bdb_comm_status_t *)ezb_app_signal_get_params(app_signal));
        if (status == EZB_BDB_STATUS_SUCCESS) {
            ESP_LOGI(TAG, "Deferred driver initialization %s", deferred_driver_init() ? "failed" : "successful");
            ESP_LOGI(TAG, "Device started up in%s factory-reset mode", ezb_bdb_is_factory_new() ? "" : " non");
            if (ezb_bdb_is_factory_new()) {
                ezb_bdb_start_top_level_commissioning(EZB_BDB_MODE_NETWORK_STEERING);
            } else {
                ESP_LOGI(TAG, "Device reboot");
            }
        } else {
            ESP_LOGW(TAG, "%s failed with status(0x%02x), please retry", ezb_app_signal_to_string(signal_type), status);
            alarm_timer_schedule(esp_zigbee_alarm_bdb_commissioning, EZB_BDB_MODE_INITIALIZATION, 1000);
        }
    } break;
    case EZB_BDB_SIGNAL_STEERING: {
        ezb_bdb_comm_status_t status = *((ezb_bdb_comm_status_t *)ezb_app_signal_get_params(app_signal));
        if (status == EZB_BDB_STATUS_SUCCESS) {
            ezb_extpanid_t extended_pan_id;
            ezb_nwk_get_extended_panid(&extended_pan_id);
            ESP_LOGI(TAG, "Joined network successfully: PAN ID(0x%04hx, EXT: 0x%llx), Channel(%d), Short Address(0x%04hx)",
                     ezb_nwk_get_panid(), extended_pan_id.u64, ezb_nwk_get_current_channel(), ezb_nwk_get_short_address());
            zdo_find_ha_light_device();
        } else {
            ESP_LOGW(TAG, "Failed to join network with status(0x%02x)", status);
            alarm_timer_schedule(esp_zigbee_alarm_bdb_commissioning, EZB_BDB_MODE_NETWORK_STEERING, 1000);
        }
    } break;
    case EZB_ZDO_SIGNAL_LEAVE: {
        const ezb_zdo_signal_leave_params_t *leave_params = ezb_app_signal_get_params(app_signal);
        ESP_LOGI(TAG, "Left network successfully with type(0x%02x)", leave_params->leave_type);
    } break;
    case EZB_NWK_SIGNAL_PERMIT_JOIN_STATUS: {
        uint8_t duration = *(uint8_t *)ezb_app_signal_get_params(app_signal);
        if (duration) {
            ESP_LOGI(TAG, "Network(0x%04hx) is open for %d seconds", ezb_nwk_get_panid(), duration);
        } else {
            ESP_LOGW(TAG, "Network(0x%04hx) closed, devices joining not allowed.", ezb_nwk_get_panid());
        }
    } break;
    default:
        ESP_LOGI(TAG, "Zigbee APP Signal: %s(type: 0x%02x)", ezb_app_signal_to_string(signal_type), signal_type);
        break;
    }
    return true;
}

static void esp_zigbee_zcl_core_action_handler(ezb_zcl_core_action_callback_id_t callback_id, void *message)
{
    switch (callback_id) {
    case EZB_ZCL_CORE_DEFAULT_RSP_CB_ID: {
        ezb_zcl_cmd_default_rsp_message_t *default_rsp = (ezb_zcl_cmd_default_rsp_message_t *)message;
        ESP_LOGI(TAG, "Received ZCL Default Response with status(0x%02x)", default_rsp->in.status_code);
    } break;
    default:
        ESP_LOGW(TAG, "ZCL Core Action: ID(0x%04lx)", callback_id);
        break;
    }
}

esp_err_t esp_zigbee_create_sleepy_switch_device(void)
{
    ezb_af_device_desc_t           dev_desc   = ezb_af_create_device_desc();
    ezb_zha_on_off_switch_config_t switch_cfg = EZB_ZHA_ON_OFF_SWITCH_CONFIG();
    ezb_af_ep_desc_t               ep_desc    = ezb_zha_create_on_off_switch(ESP_ZIGBEE_HA_ON_OFF_SWITCH_EP_ID, &switch_cfg);
    ezb_zcl_cluster_desc_t         basic_desc = {0};

    basic_desc = ezb_af_endpoint_get_cluster_desc(ep_desc, EZB_ZCL_CLUSTER_ID_BASIC, EZB_ZCL_CLUSTER_SERVER);
    ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, (void *)ESP_MANUFACTURER_NAME);
    ezb_zcl_basic_cluster_desc_add_attr(basic_desc, EZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, (void *)ESP_MODEL_IDENTIFIER);
    ESP_ERROR_CHECK(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc));
    ESP_ERROR_CHECK(ezb_af_device_desc_register(dev_desc));

    ezb_zcl_core_action_handler_register(esp_zigbee_zcl_core_action_handler);

    return ESP_OK;
}

esp_err_t esp_zigbee_setup_commissioning(void)
{
    ezb_aps_secur_enable_distributed_security(false);
    ESP_ERROR_CHECK(ezb_bdb_set_primary_channel_set(ESP_ZIGBEE_PRIMARY_CHANNEL_MASK));
    ESP_ERROR_CHECK(ezb_bdb_set_secondary_channel_set(ESP_ZIGBEE_SECONDARY_CHANNEL_MASK));
    ESP_ERROR_CHECK(ezb_app_signal_add_handler(esp_zigbee_app_signal_handler));
    ezb_nwk_set_rx_on_when_idle(false);

    return ESP_OK;
}

#if CONFIG_PM_LIGHT_SLEEP_CALLBACKS
esp_err_t esp_pm_entry_light_sleep_cb(int64_t sleep_time_us, void *arg)
{
    ESP_EARLY_LOGI(TAG, "Enter Light Sleep");
    return ESP_OK;
}

esp_err_t esp_pm_exit_light_sleep_cb(int64_t sleep_time_us, void *arg)
{
    ESP_EARLY_LOGI(TAG, "Exit Light Sleep");
    return ESP_OK;
}

esp_pm_sleep_cbs_register_config_t s_sleep_cbs_config = {
    .enter_cb          = esp_pm_entry_light_sleep_cb,
    .exit_cb           = esp_pm_exit_light_sleep_cb,
    .enter_cb_user_arg = NULL,
    .exit_cb_user_arg  = NULL,
    .enter_cb_prior    = 0,
    .exit_cb_prior     = 0,
};
#endif /* CONFIG_PM_LIGHT_SLEEP_CALLBACKS */

#ifdef CONFIG_PM_ENABLE

#if CONFIG_ESP_SLEEP_DEBUG
static esp_sleep_context_t s_sleep_ctx;
static TimerHandle_t       s_sleep_debug_timer;

static void sleep_debug_timer_cb(TimerHandle_t xTimer)
{
    assert(xTimer);

    ESP_EARLY_LOGI(TAG, "sleep_flags 0x%08lx, trigger: 0x%08lx", s_sleep_ctx.sleep_flags, s_sleep_ctx.wakeup_triggers);
    ESP_EARLY_LOGI(TAG, "PMU_SLEEP_PD_TOP: %s", (s_sleep_ctx.sleep_flags & PMU_SLEEP_PD_TOP) ? "True" : "False");
    ESP_EARLY_LOGI(TAG, "PMU_SLEEP_PD_MODEM: %s", (s_sleep_ctx.sleep_flags & PMU_SLEEP_PD_MODEM) ? "True" : "False");
    ESP_EARLY_LOGI(TAG, "Wakeup source: %d", esp_sleep_get_wakeup_cause());
}
#endif /* CONFIG_ESP_SLEEP_DEBUG */

static esp_err_t esp_pm_light_sleep_config(void)
{
    esp_err_t rc = ESP_OK;
#if CONFIG_FREERTOS_USE_TICKLESS_IDLE
    int             cur_cpu_freq_mhz = CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ;
    esp_pm_config_t pm_config        = {
               .max_freq_mhz       = cur_cpu_freq_mhz,
               .min_freq_mhz       = cur_cpu_freq_mhz,
               .light_sleep_enable = true,
    };
    rc = esp_pm_configure(&pm_config);
#endif /* CONFIG_FREERTOS_USE_TICKLESS_IDLE */

#if CONFIG_ESP_SLEEP_DEBUG
    esp_sleep_set_sleep_context(&s_sleep_ctx);
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    s_sleep_debug_timer = xTimerCreate("Sleep_xTimer", pdMS_TO_TICKS(20000), pdTRUE, NULL, sleep_debug_timer_cb);
    xTimerStart(s_sleep_debug_timer, 0);
#endif /* CONFIG_ESP_SLEEP_DEBUG */

#if CONFIG_PM_LIGHT_SLEEP_CALLBACKS
    rc == ESP_OK ? esp_pm_light_sleep_register_cbs(&s_sleep_cbs_config) : rc;
#endif /* CONFIG_PM_LIGHT_SLEEP_CALLBACKS */
    return rc;
}
#endif /* CONFIG_PM_ENABLE */

static void esp_zigbee_stack_main_task(void *pvParameters)
{
    esp_zigbee_config_t config = ESP_ZIGBEE_DEFAULT_CONFIG();

    ESP_ERROR_CHECK(esp_zigbee_init(&config));

    ESP_ERROR_CHECK(esp_zigbee_setup_commissioning());

    ESP_ERROR_CHECK(esp_zigbee_create_sleepy_switch_device());

    ESP_ERROR_CHECK(esp_zigbee_start(false));

    esp_zigbee_launch_mainloop();

    esp_zigbee_deinit();

    vTaskDelete(NULL);
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(nvs_flash_init_partition(ESP_ZIGBEE_STORAGE_PARTITION_NAME));

#ifdef CONFIG_PM_ENABLE
    ESP_ERROR_CHECK(esp_pm_light_sleep_config());
#endif

    ESP_LOGI(TAG, "Start ESP Zigbee Stack");
    xTaskCreate(esp_zigbee_stack_main_task, "Zigbee_main", 4096, NULL, 5, NULL);
}
