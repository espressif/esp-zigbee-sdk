/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ha.h"

#include <string.h>

#include "cli_util.h"
#include "zb_custom_clusters/custom_common.h"

typedef ezb_af_ep_desc_t (*ep_create_fn_t)(uint8_t, void *);

typedef struct ezb_ha_device_s {
    const char    *device_name;
    uint16_t       device_id;
    ep_create_fn_t create_fn;
} ezb_ha_device_t;

/**
 * @brief Define an HA device entry in the table
 *
 * @param name Type name of the HA device
 * @param device_id ID of the HA device type
 *
 */
#define HA_DEVICE_ENTRY(name, device_id)                          \
    {                                                             \
        #name, device_id, (ep_create_fn_t)ezb_zha_create_##name,  \
    }

/**
 * @brief Define an HA device (not support) entry in the table
 *
 * @param name Type name of the HA device
 * @param device_id ID of the HA device type
 *
 */
#define HA_DEVICE_ENTRY_UNSUPPORTED(name, device_id) \
    {                                                \
        #name, device_id, NULL,                      \
    }

/* The table contains the information of HA standard device supported by esp-zigbee-sdk.
 *
 * Note: The entries in the table MUST be arranged in ascending order of device type ID.
 */
static const ezb_ha_device_t s_ha_device_table[] = {
    HA_DEVICE_ENTRY(on_off_switch, EZB_ZHA_ON_OFF_SWITCH_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(level_control_switch, EZB_ZHA_LEVEL_CONTROL_SWITCH_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(on_off_output, EZB_ZHA_ON_OFF_OUTPUT_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(level_controllable_output, EZB_ZHA_LEVEL_CONTROLLABLE_OUTPUT_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(scene_selector, EZB_ZHA_SCENE_SELECTOR_DEVICE_ID),
    HA_DEVICE_ENTRY(configuration_tool, EZB_ZHA_CONFIGURATION_TOOL_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(remote_control, EZB_ZHA_REMOTE_CONTROL_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(combined_interface, EZB_ZHA_COMBINED_INTERFACE_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(range_extender, EZB_ZHA_RANGE_EXTENDER_DEVICE_ID),
    HA_DEVICE_ENTRY(mains_power_outlet, EZB_ZHA_MAINS_POWER_OUTLET_DEVICE_ID),
    HA_DEVICE_ENTRY(door_lock, EZB_ZHA_DOOR_LOCK_DEVICE_ID),
    HA_DEVICE_ENTRY(door_lock_controller, EZB_ZHA_DOOR_LOCK_CONTROLLER_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(simple_sensor, EZB_ZHA_SIMPLE_SENSOR_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(consumption_awareness, EZB_ZHA_CONSUMPTION_AWARENESS_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(home_gateway, EZB_ZHA_HOME_GATEWAY_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(smart_plug, EZB_ZHA_SMART_PLUG_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(white_goods, EZB_ZHA_WHITE_GOODS_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(meter_interface, EZB_ZHA_METER_INTERFACE_DEVICE_ID),
    HA_DEVICE_ENTRY(on_off_light, EZB_ZHA_ON_OFF_LIGHT_DEVICE_ID),
    HA_DEVICE_ENTRY(dimmable_light, EZB_ZHA_DIMMABLE_LIGHT_DEVICE_ID),
    HA_DEVICE_ENTRY(color_dimmable_light, EZB_ZHA_COLOR_DIMMABLE_LIGHT_DEVICE_ID),
    HA_DEVICE_ENTRY(dimmer_switch, EZB_ZHA_DIMMER_SWITCH_DEVICE_ID),
    HA_DEVICE_ENTRY(color_dimmer_switch, EZB_ZHA_COLOR_DIMMER_SWITCH_DEVICE_ID),
    HA_DEVICE_ENTRY(light_sensor, EZB_ZHA_LIGHT_SENSOR_DEVICE_ID),
    HA_DEVICE_ENTRY(shade, EZB_ZHA_SHADE_DEVICE_ID),
    HA_DEVICE_ENTRY(shade_controller, EZB_ZHA_SHADE_CONTROLLER_DEVICE_ID),
    HA_DEVICE_ENTRY(window_covering, EZB_ZHA_WINDOW_COVERING_DEVICE_ID),
    HA_DEVICE_ENTRY(window_covering_controller, EZB_ZHA_WINDOW_COVERING_CONTROLLER_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(heating_cooling_unit, EZB_ZHA_HEATING_COOLING_UNIT_DEVICE_ID),
    HA_DEVICE_ENTRY(thermostat, EZB_ZHA_THERMOSTAT_DEVICE_ID),
    HA_DEVICE_ENTRY(temperature_sensor, EZB_ZHA_TEMPERATURE_SENSOR_DEVICE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(ias_control_indicating, EZB_ZHA_IAS_CONTROL_INDICATING_EQUIPMENT_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(ias_ancillary_control, EZB_ZHA_IAS_ANCILLARY_CONTROL_EQUIPMENT_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(ias_zone, EZB_ZHA_IAS_ZONE_ID),
    HA_DEVICE_ENTRY_UNSUPPORTED(ias_warning, EZB_ZHA_IAS_WARNING_DEVICE_ID),
    HA_DEVICE_ENTRY(custom_gateway, EZB_ZHA_CUSTOM_GATEWAY_DEVICE_ID),
    HA_DEVICE_ENTRY(custom_test_tool, EZB_ZHA_CUSTOM_TEST_TOOL_DEVICE_ID),
};

static const ezb_ha_device_t *device_table_get_by_idx(uint16_t idx)
{
    if (idx < ARRAY_SIZE(s_ha_device_table)) {
        return &s_ha_device_table[idx];
    } else {
        return NULL;
    }
}

static const ezb_ha_device_t *device_table_get_by_id(uint16_t device_id)
{
    const ezb_ha_device_t *entry;
    uint16_t               left  = 0;
    uint16_t               right = ARRAY_SIZE(s_ha_device_table);

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

static const ezb_ha_device_t *device_table_get_by_name(const char *name)
{
    for (int idx = 0; idx < ARRAY_SIZE(s_ha_device_table); idx++) {
        if (!strcmp(s_ha_device_table[idx].device_name, name)) {
            return &s_ha_device_table[idx];
        }
    }

    return NULL;
}

const char *ezb_get_device_name_by_idx(uint16_t idx)
{
    const ezb_ha_device_t *ent = device_table_get_by_idx(idx);
    return ent == NULL ? "" : ent->device_name;
}

const char *ezb_get_device_name_by_id(uint16_t device_id)
{
    const ezb_ha_device_t *ent = device_table_get_by_id(device_id);
    return ent == NULL ? "" : ent->device_name;
}

uint16_t ezb_get_device_id_by_name(const char *name)
{
    const ezb_ha_device_t *ent = device_table_get_by_name(name);
    return ent == NULL ? 0xFFFF : ent->device_id;
}

uint16_t esp_zb_get_device_id_by_name(const char *name) { return ezb_get_device_id_by_name(name); }

bool ezb_is_device_supported(uint16_t device_id)
{
    const ezb_ha_device_t *ent = device_table_get_by_id(device_id);
    return ent != NULL && ent->create_fn != NULL;
}

ezb_af_ep_desc_t ezb_ep_create_ha_default(uint8_t ep_id, uint16_t ha_device_id)
{
    ezb_af_ep_desc_t      ep   = NULL;
    const ezb_ha_device_t *ent = device_table_get_by_id(ha_device_id);
    if (ent != NULL && ent->create_fn != NULL) {
        ep = ent->create_fn(ep_id, NULL);
    }
    return ep;
}
