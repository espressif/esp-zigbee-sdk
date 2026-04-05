/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "zcl.h"

#include <string.h>

#include "cli_util.h"
#include "zb_custom_clusters/ping_iperf_test.h"

typedef ezb_err_t (*register_fn_t)(ezb_af_ep_desc_t ep_desc, ezb_zcl_cluster_desc_t cluster_desc);
typedef ezb_zcl_cluster_desc_t (*create_fn_t)(void *cluster_cfg, uint8_t role_mask);
typedef ezb_err_t (*add_attr_fn_t)(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

typedef struct ezb_zcl_cluster_fn_s {
    const char   *cluster_name;
    uint16_t      cluster_id;
    register_fn_t register_fn; /*!< function to add cluster (attribute list) to cluster list */
    create_fn_t   create_fn;   /*!< function to create default cluster (attribute list) with mandatory attributes */
    add_attr_fn_t add_attr_fn; /*!< function to add attribute to cluster (attribute list)  */
} ezb_zcl_cluster_fn_t;

/**
 * @brief Define a cluster fn entry in the table
 *
 * @param name Common name of the cluster
 * @param cluster_id ID of the cluster
 *
 */

#define CLUSTER_FN_ENTRY(name, cluster_id)                 \
    {                                                      \
        #name,                                             \
        cluster_id,                                        \
        ezb_af_endpoint_add_cluster_desc,                  \
        (create_fn_t)ezb_zcl_##name##_create_cluster_desc, \
        ezb_zcl_##name##_cluster_desc_add_attr,            \
    }

/**
 * @brief Define a cluster (with no attribute) fn entry in the table
 *
 * @param name Common name of the cluster
 * @param cluster_id ID of the cluster
 *
 */
#define CLUSTER_NO_ATTR_FN_ENTRY(name, cluster_id)          \
    {                                                       \
        #name,                                              \
        cluster_id,                                         \
        ezb_af_endpoint_add_cluster_desc,                   \
        (create_fn_t)ezb_zcl_##name##_create_cluster_desc,  \
        NULL,                                               \
    }

/**
 * @brief Define a cluster (not support) fn entry in the table
 *
 * @param name Common name of the cluster
 * @param cluster_id ID of the cluster
 *
 */
#define CLUSTER_NON_SUPPORT_FN_ENTRY(name, cluster_id) \
    {                                                  \
        #name, cluster_id, NULL, NULL, NULL,           \
    }

/* The table contains the information of clusters supported by esp-zigbee-sdk.
 *
 * Note: The entries in the table MUST be arranged in ascending order of cluster ID.
 */
const static ezb_zcl_cluster_fn_t s_cluster_fn_table[] = {
    CLUSTER_FN_ENTRY(basic, EZB_ZCL_CLUSTER_ID_BASIC),
    CLUSTER_FN_ENTRY(device_temp_config, EZB_ZCL_CLUSTER_ID_DEVICE_TEMP_CONFIG),
    CLUSTER_FN_ENTRY(power_config, EZB_ZCL_CLUSTER_ID_POWER_CONFIG),
    CLUSTER_FN_ENTRY(identify, EZB_ZCL_CLUSTER_ID_IDENTIFY),
    CLUSTER_FN_ENTRY(groups, EZB_ZCL_CLUSTER_ID_GROUPS),
    CLUSTER_FN_ENTRY(scenes, EZB_ZCL_CLUSTER_ID_SCENES),
    CLUSTER_FN_ENTRY(on_off, EZB_ZCL_CLUSTER_ID_ON_OFF),
    CLUSTER_FN_ENTRY(on_off_switch_config, EZB_ZCL_CLUSTER_ID_ON_OFF_SWITCH_CONFIG),
    CLUSTER_FN_ENTRY(alarms, EZB_ZCL_CLUSTER_ID_ALARMS),
    CLUSTER_FN_ENTRY(time, EZB_ZCL_CLUSTER_ID_TIME),
    CLUSTER_FN_ENTRY(level, EZB_ZCL_CLUSTER_ID_LEVEL),
    CLUSTER_NON_SUPPORT_FN_ENTRY(rssi_location, EZB_ZCL_CLUSTER_ID_RSSI_LOCATION),
    CLUSTER_FN_ENTRY(analog_input, EZB_ZCL_CLUSTER_ID_ANALOG_INPUT),
    CLUSTER_FN_ENTRY(analog_output, EZB_ZCL_CLUSTER_ID_ANALOG_OUTPUT),
    CLUSTER_FN_ENTRY(analog_value, EZB_ZCL_CLUSTER_ID_ANALOG_VALUE),
    CLUSTER_FN_ENTRY(binary_input, EZB_ZCL_CLUSTER_ID_BINARY_INPUT),
    CLUSTER_FN_ENTRY(binary_output, EZB_ZCL_CLUSTER_ID_BINARY_OUTPUT),
    CLUSTER_FN_ENTRY(binary_value, EZB_ZCL_CLUSTER_ID_BINARY_VALUE),
    CLUSTER_FN_ENTRY(multistate_input, EZB_ZCL_CLUSTER_ID_MULTISTATE_INPUT),
    CLUSTER_FN_ENTRY(multistate_output, EZB_ZCL_CLUSTER_ID_MULTISTATE_OUTPUT),
    CLUSTER_FN_ENTRY(multistate_value, EZB_ZCL_CLUSTER_ID_MULTISTATE_VALUE),
    CLUSTER_NON_SUPPORT_FN_ENTRY(commissioning, EZB_ZCL_CLUSTER_ID_COMMISSIONING),
    CLUSTER_FN_ENTRY(poll_control, EZB_ZCL_CLUSTER_ID_POLL_CONTROL),
    CLUSTER_FN_ENTRY(ota_upgrade, EZB_ZCL_CLUSTER_ID_OTA_UPGRADE),
    CLUSTER_NON_SUPPORT_FN_ENTRY(poll_control, EZB_ZCL_CLUSTER_ID_POLL_CONTROL),
    CLUSTER_NON_SUPPORT_FN_ENTRY(green_power, EZB_ZCL_CLUSTER_ID_GREEN_POWER), /* No API provided */
    CLUSTER_NON_SUPPORT_FN_ENTRY(keep_alive, EZB_ZCL_CLUSTER_ID_KEEP_ALIVE),
    CLUSTER_FN_ENTRY(shade_config, EZB_ZCL_CLUSTER_ID_SHADE_CONFIG),
    CLUSTER_FN_ENTRY(door_lock, EZB_ZCL_CLUSTER_ID_DOOR_LOCK),
    CLUSTER_FN_ENTRY(window_covering, EZB_ZCL_CLUSTER_ID_WINDOW_COVERING),
    CLUSTER_NON_SUPPORT_FN_ENTRY(pump_config_control, EZB_ZCL_CLUSTER_ID_PUMP_CONFIG_CONTROL),
    CLUSTER_FN_ENTRY(dehumidification_control, EZB_ZCL_CLUSTER_ID_DEHUMIDIFICATION_CONTROL),
    CLUSTER_FN_ENTRY(color_control, EZB_ZCL_CLUSTER_ID_COLOR_CONTROL),
    CLUSTER_FN_ENTRY(thermostat, EZB_ZCL_CLUSTER_ID_THERMOSTAT),
    CLUSTER_FN_ENTRY(fan_control, EZB_ZCL_CLUSTER_ID_FAN_CONTROL),
    CLUSTER_FN_ENTRY(thermostat_ui_config, EZB_ZCL_CLUSTER_ID_THERMOSTAT_UI_CONFIG),
    CLUSTER_NON_SUPPORT_FN_ENTRY(ballast_config, EZB_ZCL_CLUSTER_ID_BALLAST_CONFIG),
    CLUSTER_FN_ENTRY(illuminance_measurement, EZB_ZCL_CLUSTER_ID_ILLUMINANCE_MEASUREMENT),
    CLUSTER_FN_ENTRY(temperature_measurement, EZB_ZCL_CLUSTER_ID_TEMPERATURE_MEASUREMENT),
    CLUSTER_FN_ENTRY(pressure_measurement, EZB_ZCL_CLUSTER_ID_PRESSURE_MEASUREMENT),
    CLUSTER_FN_ENTRY(flow_measurement, EZB_ZCL_CLUSTER_ID_FLOW_MEASUREMENT),
    CLUSTER_FN_ENTRY(rel_humidity_measurement, EZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT),
    CLUSTER_FN_ENTRY(occupancy_sensing, EZB_ZCL_CLUSTER_ID_OCCUPANCY_SENSING),
    CLUSTER_FN_ENTRY(ph_measurement, EZB_ZCL_CLUSTER_ID_PH_MEASUREMENT),
    CLUSTER_FN_ENTRY(ec_measurement, EZB_ZCL_CLUSTER_ID_EC_MEASUREMENT),
    CLUSTER_FN_ENTRY(wind_speed_measurement, EZB_ZCL_CLUSTER_ID_WIND_SPEED_MEASUREMENT),
    CLUSTER_FN_ENTRY(carbon_dioxide_measurement, EZB_ZCL_CLUSTER_ID_CARBON_DIOXIDE_MEASUREMENT),
    CLUSTER_FN_ENTRY(pm2_5_measurement, EZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT),
    CLUSTER_FN_ENTRY(ias_zone, EZB_ZCL_CLUSTER_ID_IAS_ZONE),
    CLUSTER_FN_ENTRY(ias_ace, EZB_ZCL_CLUSTER_ID_IAS_ACE),
    CLUSTER_FN_ENTRY(ias_wd, EZB_ZCL_CLUSTER_ID_IAS_WD),
    CLUSTER_FN_ENTRY(price, EZB_ZCL_CLUSTER_ID_PRICE),
    CLUSTER_FN_ENTRY(metering, EZB_ZCL_CLUSTER_ID_METERING),
    CLUSTER_FN_ENTRY(meter_identification, EZB_ZCL_CLUSTER_ID_METER_IDENTIFICATION),
    CLUSTER_FN_ENTRY(electrical_measurement, EZB_ZCL_CLUSTER_ID_ELECTRICAL_MEASUREMENT),
    CLUSTER_NON_SUPPORT_FN_ENTRY(diagnostics, EZB_ZCL_CLUSTER_ID_DIAGNOSTICS),
    CLUSTER_FN_ENTRY(touchlink_commissioning, EZB_ZCL_CLUSTER_ID_TOUCHLINK_COMMISSIONING),
    CLUSTER_FN_ENTRY(ping_iperf_test, EZB_ZCL_CLUSTER_ID_PING_IPERF_TEST),
};

static const ezb_zcl_cluster_fn_t *cluster_fn_table_get_by_idx(uint16_t idx)
{
    if (idx < ARRAY_SIZE(s_cluster_fn_table)) {
        return &s_cluster_fn_table[idx];
    } else {
        return NULL;
    }
}

static const ezb_zcl_cluster_fn_t *cluster_fn_table_get_by_id(uint16_t cluster_id)
{
    const ezb_zcl_cluster_fn_t *entry;
    uint16_t                    left  = 0;
    uint16_t                    right = ARRAY_SIZE(s_cluster_fn_table);

    while (left < right) {
        uint16_t middle = (left + right) / 2;

        entry = &s_cluster_fn_table[middle];

        if (entry->cluster_id == cluster_id) {
            return entry;
        } else if (entry->cluster_id < cluster_id) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return NULL;
}

static const ezb_zcl_cluster_fn_t *cluster_fn_table_get_by_name(const char *name)
{
    for (int idx = 0; idx < ARRAY_SIZE(s_cluster_fn_table); idx++) {
        if (!strcmp(s_cluster_fn_table[idx].cluster_name, name)) {
            return &s_cluster_fn_table[idx];
        }
    }

    return NULL;
}

const char *ezb_get_cluster_name_by_idx(uint16_t idx)
{
    const ezb_zcl_cluster_fn_t *ent = cluster_fn_table_get_by_idx(idx);
    return ent == NULL ? "" : ent->cluster_name;
}

const char *ezb_get_cluster_name_by_id(uint16_t cluster_id)
{
    const ezb_zcl_cluster_fn_t *ent = cluster_fn_table_get_by_id(cluster_id);
    return ent == NULL ? "" : ent->cluster_name;
}

uint16_t ezb_get_cluster_id_by_name(const char *name)
{
    const ezb_zcl_cluster_fn_t *ent = cluster_fn_table_get_by_name(name);
    return ent == NULL ? 0xFFFF : ent->cluster_id;
}

ezb_zcl_cluster_desc_t ezb_cluster_desc_create_default(uint16_t cluster_id, uint8_t role_mask)
{
    ezb_zcl_cluster_desc_t     cluster_desc = NULL;
    const ezb_zcl_cluster_fn_t *ent          = cluster_fn_table_get_by_id(cluster_id);
    if (ent != NULL && ent->create_fn != NULL) {
        cluster_desc = ent->create_fn(NULL, role_mask);
    } else {
        cluster_desc = NULL;
    }
    return cluster_desc;
}

ezb_err_t ezb_cluster_desc_add_std_attr(uint16_t               cluster_id,
                                        ezb_zcl_cluster_desc_t cluster_desc,
                                        uint16_t               attr_id,
                                        void                   *value_p)
{
    ezb_err_t                   ret = EZB_ERR_NONE;
    const ezb_zcl_cluster_fn_t *ent = cluster_fn_table_get_by_id(cluster_id);
    if (ent != NULL && ent->add_attr_fn != NULL) {
        ret = ent->add_attr_fn(cluster_desc, attr_id, value_p);
    } else {
        ret = EZB_ERR_NOT_SUPPORTED;
    }
    return ret;
}

ezb_err_t ezb_cluster_desc_register(ezb_af_ep_desc_t       ep_desc,
                                    uint16_t               cluster_id,
                                    ezb_zcl_cluster_desc_t cluster_desc,
                                    uint8_t                role_mask)
{
    ezb_err_t                   ret = EZB_ERR_NONE;
    const ezb_zcl_cluster_fn_t *ent = cluster_fn_table_get_by_id(cluster_id);

    if (ent != NULL && ent->register_fn != NULL) {
        ret = ent->register_fn(ep_desc, cluster_desc);
    } else {
        ret = ezb_af_endpoint_add_cluster_desc(ep_desc, cluster_desc);
    }
    return ret;
}
