#pragma once

static const char *TAG = "ESP32_RANGE_EXTENDER";

#define ESP_ZB_DEFAULT_RADIO_CONFIG()                                               \
{                                                                                   \
    .radio_mode = ZB_RADIO_MODE_NATIVE,                                             \
}
#define ESP_ZB_DEFAULT_HOST_CONFIG()                                                \
{                                                                                   \
    .host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE,                           \
}

#define ESP_ZB_ZR_CONFIG()                                                          \
{                                                                                   \
    .esp_zb_role = ESP_ZB_DEVICE_TYPE_ROUTER,                                       \
    .install_code_policy = false,                                                   \
    .nwk_cfg.zczr_cfg = {                                                           \
    .max_children = 10,                                                             \
    },                                                                              \
}

#define ESP_ZP_EP_CONFIG()                                                          \
{                                                                                   \
    .endpoint = 1,                                                                  \
    .app_profile_id = ESP_ZB_AF_HA_PROFILE_ID,                                      \
    .app_device_id = ESP_ZB_HA_RANGE_EXTENDER_DEVICE_ID,                            \
    .app_device_version = 0                                                         \
}
