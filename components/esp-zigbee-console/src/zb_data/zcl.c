/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "esp_zigbee_core.h"

#include "../cli_util.h"

#include "zb_custom_clusters/custom_common.h"

typedef esp_err_t (*register_fn_t)(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask);
typedef esp_zb_attribute_list_t* (*create_fn_t)(void *);
typedef esp_err_t (*add_attr_fn_t)(esp_zb_attribute_list_t *attr_list, uint16_t attr_id, void *value_p);

typedef struct esp_zcl_cluster_fn_s {
    const char *cluster_name;
    uint16_t    cluster_id;
    register_fn_t register_fn;  /*!< function to add cluster (attribute list) to cluster list */
    create_fn_t create_fn;      /*!< function to create default cluster (attribute list) with mandatory attributes */
    add_attr_fn_t add_attr_fn;  /*!< function to add attibute to cluster (attribute list)  */
} esp_zcl_cluster_fn_t;

/**
 * @brief Define a cluster fn entry in the table
 *
 * @param name Common name of the cluster
 * @param cluster_id ID of the cluster
 *
 */
#define CLUSTER_FN_ENTRY(name, cluster_id)                  \
    {                                                       \
        #name, cluster_id,                                  \
        esp_zb_cluster_list_add_ ## name ## _cluster,       \
        (create_fn_t)esp_zb_ ## name ## _cluster_create,    \
        esp_zb_ ## name ## _cluster_add_attr,               \
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
        #name, cluster_id,                                  \
        esp_zb_cluster_list_add_ ## name ## _cluster,       \
        (create_fn_t)esp_zb_ ## name ## _cluster_create,    \
        NULL,                                               \
    }

/**
 * @brief Define a cluster (not support) fn entry in the table
 *
 * @param name Common name of the cluster
 * @param cluster_id ID of the cluster
 *
 */
#define CLUSTER_NON_SUPPORT_FN_ENTRY(name, cluster_id)      \
    {                                                       \
        #name, cluster_id,                                  \
        NULL, NULL, NULL,                                   \
    }

/* The table contains the information of clusters supported by esp-zigbee-sdk.
 *
 * Note: The entries in the table MUST be arranged in ascending order of cluster ID.
 */
const static esp_zcl_cluster_fn_t s_cluster_fn_table[] = {
    CLUSTER_FN_ENTRY(basic, ESP_ZB_ZCL_CLUSTER_ID_BASIC),
    CLUSTER_FN_ENTRY(power_config, ESP_ZB_ZCL_CLUSTER_ID_POWER_CONFIG),
    CLUSTER_NON_SUPPORT_FN_ENTRY(device_temp_config, ESP_ZB_ZCL_CLUSTER_ID_DEVICE_TEMP_CONFIG),
    CLUSTER_FN_ENTRY(identify, ESP_ZB_ZCL_CLUSTER_ID_IDENTIFY),
    CLUSTER_FN_ENTRY(groups, ESP_ZB_ZCL_CLUSTER_ID_GROUPS),
    CLUSTER_FN_ENTRY(scenes, ESP_ZB_ZCL_CLUSTER_ID_SCENES),
    CLUSTER_FN_ENTRY(on_off, ESP_ZB_ZCL_CLUSTER_ID_ON_OFF),
    CLUSTER_FN_ENTRY(on_off_switch_config, ESP_ZB_ZCL_CLUSTER_ID_ON_OFF_SWITCH_CONFIG),
    CLUSTER_FN_ENTRY(level, ESP_ZB_ZCL_CLUSTER_ID_LEVEL_CONTROL),
    CLUSTER_NON_SUPPORT_FN_ENTRY(alarms, ESP_ZB_ZCL_CLUSTER_ID_ALARMS),
    CLUSTER_FN_ENTRY(time, ESP_ZB_ZCL_CLUSTER_ID_TIME),
    CLUSTER_NON_SUPPORT_FN_ENTRY(rssi_location, ESP_ZB_ZCL_CLUSTER_ID_RSSI_LOCATION),
    CLUSTER_FN_ENTRY(analog_input, ESP_ZB_ZCL_CLUSTER_ID_ANALOG_INPUT),
    CLUSTER_FN_ENTRY(analog_output, ESP_ZB_ZCL_CLUSTER_ID_ANALOG_OUTPUT),
    CLUSTER_FN_ENTRY(analog_value, ESP_ZB_ZCL_CLUSTER_ID_ANALOG_VALUE),
    CLUSTER_FN_ENTRY(binary_input, ESP_ZB_ZCL_CLUSTER_ID_BINARY_INPUT),
    CLUSTER_NON_SUPPORT_FN_ENTRY(binary_output, ESP_ZB_ZCL_CLUSTER_ID_BINARY_OUTPUT),
    CLUSTER_NON_SUPPORT_FN_ENTRY(binary_value, ESP_ZB_ZCL_CLUSTER_ID_BINARY_VALUE),
    CLUSTER_NON_SUPPORT_FN_ENTRY(multistate_input, ESP_ZB_ZCL_CLUSTER_ID_MULTI_INPUT),
    CLUSTER_NON_SUPPORT_FN_ENTRY(multistate_output, ESP_ZB_ZCL_CLUSTER_ID_MULTI_OUTPUT),
    CLUSTER_FN_ENTRY(multistate_value, ESP_ZB_ZCL_CLUSTER_ID_MULTI_VALUE),
    CLUSTER_FN_ENTRY(commissioning, ESP_ZB_ZCL_CLUSTER_ID_COMMISSIONING),
    CLUSTER_FN_ENTRY(ota, ESP_ZB_ZCL_CLUSTER_ID_OTA_UPGRADE),
    CLUSTER_NON_SUPPORT_FN_ENTRY(poll_control, ESP_ZB_ZCL_CLUSTER_ID_POLL_CONTROL),
    CLUSTER_NON_SUPPORT_FN_ENTRY(green_power, ESP_ZB_ZCL_CLUSTER_ID_GREEN_POWER), /* No API provided */
    CLUSTER_NON_SUPPORT_FN_ENTRY(keep_alive, ESP_ZB_ZCL_CLUSTER_ID_KEEP_ALIVE),
    CLUSTER_FN_ENTRY(shade_config, ESP_ZB_ZCL_CLUSTER_ID_SHADE_CONFIG),
    CLUSTER_FN_ENTRY(door_lock, ESP_ZB_ZCL_CLUSTER_ID_DOOR_LOCK),
    CLUSTER_FN_ENTRY(window_covering, ESP_ZB_ZCL_CLUSTER_ID_WINDOW_COVERING),
    CLUSTER_NON_SUPPORT_FN_ENTRY(pump_config_control, ESP_ZB_ZCL_CLUSTER_ID_PUMP_CONFIG_CONTROL),
    CLUSTER_FN_ENTRY(thermostat, ESP_ZB_ZCL_CLUSTER_ID_THERMOSTAT),
    CLUSTER_FN_ENTRY(fan_control, ESP_ZB_ZCL_CLUSTER_ID_FAN_CONTROL),
    CLUSTER_FN_ENTRY(dehumidification_control, ESP_ZB_ZCL_CLUSTER_ID_DEHUMIDIFICATION_CONTROL),
    CLUSTER_FN_ENTRY(thermostat_ui_config, ESP_ZB_ZCL_CLUSTER_ID_THERMOSTAT_UI_CONFIG),
    CLUSTER_FN_ENTRY(color_control, ESP_ZB_ZCL_CLUSTER_ID_COLOR_CONTROL),
    CLUSTER_NON_SUPPORT_FN_ENTRY(ballast_config, ESP_ZB_ZCL_CLUSTER_ID_BALLAST_CONFIG),
    CLUSTER_FN_ENTRY(illuminance_meas, ESP_ZB_ZCL_CLUSTER_ID_ILLUMINANCE_MEASUREMENT),
    CLUSTER_FN_ENTRY(temperature_meas, ESP_ZB_ZCL_CLUSTER_ID_TEMP_MEASUREMENT),
    CLUSTER_FN_ENTRY(pressure_meas, ESP_ZB_ZCL_CLUSTER_ID_PRESSURE_MEASUREMENT),
    CLUSTER_FN_ENTRY(flow_meas, ESP_ZB_ZCL_CLUSTER_ID_FLOW_MEASUREMENT),
    CLUSTER_FN_ENTRY(humidity_meas, ESP_ZB_ZCL_CLUSTER_ID_REL_HUMIDITY_MEASUREMENT),
    CLUSTER_FN_ENTRY(occupancy_sensing, ESP_ZB_ZCL_CLUSTER_ID_OCCUPANCY_SENSING),
    CLUSTER_FN_ENTRY(ph_measurement, ESP_ZB_ZCL_CLUSTER_ID_PH_MEASUREMENT),
    CLUSTER_FN_ENTRY(ec_measurement, ESP_ZB_ZCL_CLUSTER_ID_EC_MEASUREMENT),
    CLUSTER_FN_ENTRY(wind_speed_measurement, ESP_ZB_ZCL_CLUSTER_ID_WIND_SPEED_MEASUREMENT),
    CLUSTER_FN_ENTRY(carbon_dioxide_measurement, ESP_ZB_ZCL_CLUSTER_ID_CARBON_DIOXIDE_MEASUREMENT),
    CLUSTER_FN_ENTRY(pm2_5_measurement, ESP_ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT),
    CLUSTER_FN_ENTRY(ias_zone, ESP_ZB_ZCL_CLUSTER_ID_IAS_ZONE),
    CLUSTER_NO_ATTR_FN_ENTRY(ias_ace, ESP_ZB_ZCL_CLUSTER_ID_IAS_ACE),   /* Only have zone table internal */
    CLUSTER_FN_ENTRY(ias_wd, ESP_ZB_ZCL_CLUSTER_ID_IAS_WD),
    CLUSTER_NO_ATTR_FN_ENTRY(price, ESP_ZB_ZCL_CLUSTER_ID_PRICE),       /* Too many attributes */
    CLUSTER_NO_ATTR_FN_ENTRY(metering, ESP_ZB_ZCL_CLUSTER_ID_METERING), /* Too many attributes */
    CLUSTER_FN_ENTRY(meter_identification, ESP_ZB_ZCL_CLUSTER_ID_METER_IDENTIFICATION),
    CLUSTER_FN_ENTRY(electrical_meas, ESP_ZB_ZCL_CLUSTER_ID_ELECTRICAL_MEASUREMENT),
    CLUSTER_FN_ENTRY(diagnostics, ESP_ZB_ZCL_CLUSTER_ID_DIAGNOSTICS),
    CLUSTER_NO_ATTR_FN_ENTRY(touchlink_commissioning, 0x1000),
    CLUSTER_FN_ENTRY(ping_iperf_test, ESP_ZB_ZCL_CLUSTER_ID_PING_IPERF_TEST),
};

static const esp_zcl_cluster_fn_t* cluster_fn_table_get_by_idx(uint16_t idx)
{
    if (idx < ARRAY_SIZE(s_cluster_fn_table)) {
        return &s_cluster_fn_table[idx];
    } else {
        return NULL;
    }
}

static const esp_zcl_cluster_fn_t* cluster_fn_table_get_by_id(uint16_t cluster_id)
{
    const esp_zcl_cluster_fn_t *entry;
    uint16_t left  = 0;
    uint16_t right = ARRAY_SIZE(s_cluster_fn_table);

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

static const esp_zcl_cluster_fn_t* cluster_fn_table_get_by_name(const char *name)
{
    for (int idx = 0; idx < ARRAY_SIZE(s_cluster_fn_table); idx++) {
        if (!strcmp(s_cluster_fn_table[idx].cluster_name, name)) {
            return &s_cluster_fn_table[idx];
        }
    }

    return NULL;
}

const char* esp_zb_get_cluster_name_by_idx(uint16_t idx)
{
    const esp_zcl_cluster_fn_t *ent = cluster_fn_table_get_by_idx(idx);
    return ent == NULL ? "" : ent->cluster_name;
}

const char* esp_zb_get_cluster_name_by_id(uint16_t cluster_id)
{
    const esp_zcl_cluster_fn_t *ent = cluster_fn_table_get_by_id(cluster_id);
    return ent == NULL ? "" : ent->cluster_name;
}

uint16_t esp_zb_get_cluster_id_by_name(const char *name)
{
    const esp_zcl_cluster_fn_t *ent = cluster_fn_table_get_by_name(name);
    return ent == NULL ? 0xFFFF : ent->cluster_id;
}

esp_zb_attribute_list_t *esp_zb_cluster_create_default(uint16_t cluster_id)
{
    esp_zb_attribute_list_t *cluster = NULL;
    const esp_zcl_cluster_fn_t *ent = cluster_fn_table_get_by_id(cluster_id);
    if (ent != NULL && ent->create_fn != NULL) {
        cluster = ent->create_fn(NULL);
    } else {
        cluster = esp_zb_zcl_attr_list_create(cluster_id);
    }
    return cluster;
}

esp_err_t esp_zb_cluster_add_std_attr(esp_zb_attribute_list_t *attr_list, uint16_t attr_id, void *value_p)
{
    esp_err_t ret = ESP_OK;
    const esp_zcl_cluster_fn_t *ent = cluster_fn_table_get_by_id(attr_list->next->cluster_id);
    if (ent != NULL && ent->add_attr_fn != NULL) {
        ret = ent->add_attr_fn(attr_list, attr_id, value_p);
    } else {
        ret = ESP_ERR_NOT_SUPPORTED;
    }
    return ret;
}

esp_err_t esp_zb_cluster_register(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list, uint8_t role_mask)
{
    esp_err_t ret = ESP_OK;
    const esp_zcl_cluster_fn_t *ent = cluster_fn_table_get_by_id(attr_list->next->cluster_id);
    if (ent != NULL && ent->register_fn != NULL) {
        ret = ent->register_fn(cluster_list, attr_list, role_mask);
    } else {
        ret = esp_zb_cluster_list_add_custom_cluster(cluster_list, attr_list, role_mask);
    }
    return ret;
}
