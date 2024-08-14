/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "ha/esp_zigbee_ha_standard.h"

#include "../cli_util.h"

typedef esp_zb_cluster_list_t* (*ep_create_fn_t)(void *);

typedef struct esp_zcl_ha_device_type_s {
    const char *device_name;
    uint16_t device_id;
    ep_create_fn_t create_fn;
} esp_zcl_ha_device_t;

/**
 * @brief Define an HA device entry in the table
 *
 * @param name Type name of the HA device
 * @param device_id ID of the HA device type
 *
 */
#define HA_DEVICE_ENTRY(name, device_id)                        \
    {                                                           \
        #name, device_id,                                       \
        (ep_create_fn_t)esp_zb_ ## name ## _clusters_create,    \
    }

/**
 * @brief Define an HA device (not support) entry in the table
 *
 * @param name Type name of the HA device
 * @param device_id ID of the HA device type
 *
 */
#define HA_DEVICE_ENTRY_UNSUPPORT(name, device_id)              \
    {                                                           \
        #name, device_id, NULL,                                 \
    }

/* The table contains the information of HA standard device supported by esp-zigbee-sdk.
 *
 * Note: The entries in the table MUST be arranged in ascending order of device type ID.
 */
static const esp_zcl_ha_device_t s_ha_device_table[] = {
    HA_DEVICE_ENTRY(on_off_switch, ESP_ZB_HA_ON_OFF_SWITCH_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(level_control_switch, ESP_ZB_HA_LEVEL_CONTROL_SWITCH_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(on_off_output, ESP_ZB_HA_ON_OFF_OUTPUT_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(level_controllable_output, ESP_ZB_HA_LEVEL_CONTROLLABLE_OUTPUT_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(scene_selector, ESP_ZB_HA_SCENE_SELECTOR_DEVICE_ID),
    HA_DEVICE_ENTRY(configuration_tool, ESP_ZB_HA_CONFIGURATION_TOOL_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(remote_control, ESP_ZB_HA_REMOTE_CONTROL_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(combined_interface, ESP_ZB_HA_COMBINED_INTERFACE_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(range_extender, ESP_ZB_HA_RANGE_EXTENDER_DEVICE_ID),
    HA_DEVICE_ENTRY(mains_power_outlet, ESP_ZB_HA_MAINS_POWER_OUTLET_DEVICE_ID),
    HA_DEVICE_ENTRY(door_lock, ESP_ZB_HA_DOOR_LOCK_DEVICE_ID),
    HA_DEVICE_ENTRY(door_lock_controller, ESP_ZB_HA_DOOR_LOCK_CONTROLLER_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(simple_sensor, ESP_ZB_HA_SIMPLE_SENSOR_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(consumption_awareness, ESP_ZB_HA_CONSUMPTION_AWARENESS_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(home_gateway, ESP_ZB_HA_HOME_GATEWAY_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(smart_plug, ESP_ZB_HA_SMART_PLUG_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(white_goods, ESP_ZB_HA_WHITE_GOODS_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(meter_interface, ESP_ZB_HA_METER_INTERFACE_DEVICE_ID),
    HA_DEVICE_ENTRY(on_off_light, ESP_ZB_HA_ON_OFF_LIGHT_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(dimmable_light, ESP_ZB_HA_DIMMABLE_LIGHT_DEVICE_ID),
    HA_DEVICE_ENTRY(color_dimmable_light, ESP_ZB_HA_COLOR_DIMMABLE_LIGHT_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(dimmable_switch, ESP_ZB_HA_DIMMER_SWITCH_DEVICE_ID),
    HA_DEVICE_ENTRY(color_dimmable_switch, ESP_ZB_HA_COLOR_DIMMER_SWITCH_DEVICE_ID),
    HA_DEVICE_ENTRY(light_sensor, ESP_ZB_HA_LIGHT_SENSOR_DEVICE_ID),
    HA_DEVICE_ENTRY(shade, ESP_ZB_HA_SHADE_DEVICE_ID),
    HA_DEVICE_ENTRY(shade_controller, ESP_ZB_HA_SHADE_CONTROLLER_DEVICE_ID),
    HA_DEVICE_ENTRY(window_covering, ESP_ZB_HA_WINDOW_COVERING_DEVICE_ID),
    HA_DEVICE_ENTRY(window_covering_controller, ESP_ZB_HA_WINDOW_COVERING_CONTROLLER_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(heating_cooling_unit, ESP_ZB_HA_HEATING_COOLING_UNIT_DEVICE_ID),
    HA_DEVICE_ENTRY(thermostat, ESP_ZB_HA_THERMOSTAT_DEVICE_ID),
    HA_DEVICE_ENTRY(temperature_sensor, ESP_ZB_HA_TEMPERATURE_SENSOR_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(ias_control_indicating, ESP_ZB_HA_IAS_CONTROL_INDICATING_EQUIPMENT_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(ias_ancillary_control, ESP_ZB_HA_IAS_ANCILLARY_CONTROL_EQUIPMENT_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(ias_zone, ESP_ZB_HA_IAS_ZONE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(ias_warning, ESP_ZB_HA_IAS_WARNING_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(test_device, ESP_ZB_HA_TEST_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(custom_tunnel, ESP_ZB_HA_CUSTOM_TUNNEL_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORT(custom_attr, ESP_ZB_HA_CUSTOM_ATTR_DEVICE_ID),
};

static const esp_zcl_ha_device_t* device_table_get_by_idx(uint16_t idx)
{
    if (idx < ARRAY_SIZE(s_ha_device_table)) {
        return &s_ha_device_table[idx];
    } else {
        return NULL;
    }
}

static const esp_zcl_ha_device_t* device_table_get_by_id(uint16_t device_id)
{
    const esp_zcl_ha_device_t *entry;
    uint16_t left  = 0;
    uint16_t right = ARRAY_SIZE(s_ha_device_table);

    while (left < right) {
        uint16_t middle = (left + right) / 2;

        entry = &s_ha_device_table[middle];

        if (entry->device_id == device_id) {
            return entry;
        } else if (entry->device_id < device_id) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return NULL;
}

static const esp_zcl_ha_device_t* device_table_get_by_name(const char *name)
{
    for (int idx = 0; idx < ARRAY_SIZE(s_ha_device_table); idx++) {
        if (!strcmp(s_ha_device_table[idx].device_name, name)) {
            return &s_ha_device_table[idx];
        }
    }

    return NULL;
}

const char* esp_zb_get_device_name_by_idx(uint16_t idx)
{
    const esp_zcl_ha_device_t *ent = device_table_get_by_idx(idx);
    return ent == NULL ? "" : ent->device_name;
}

const char* esp_zb_get_device_name_by_id(uint16_t device_id)
{
    const esp_zcl_ha_device_t *ent = device_table_get_by_id(device_id);
    return ent == NULL ? "" : ent->device_name;
}

uint16_t esp_zb_get_device_id_by_name(const char *name)
{
    const esp_zcl_ha_device_t *ent = device_table_get_by_name(name);
    return ent == NULL ? 0xFFFF : ent->device_id;
}

bool esp_zb_is_device_supported(uint16_t device_id)
{
    const esp_zcl_ha_device_t *ent = device_table_get_by_id(device_id);
    return ent != NULL && ent->create_fn != NULL;
}

esp_zb_cluster_list_t *esp_zb_ep_create_ha_default(uint16_t ha_device_id)
{
    esp_zb_cluster_list_t *ep = NULL;
    const esp_zcl_ha_device_t *ent = device_table_get_by_id(ha_device_id);
    if (ent != NULL && ent->create_fn != NULL) {
        ep = ent->create_fn(NULL);
    }
    return ep;
}
