/*
 * SPDX-FileCopyrightText: 2022-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_zigbee_type.h"

#if CONFIG_ZB_SDK_1xx

#warning "This file is deprecated, please include "ezbee/zcl.h" instead!"

#include <ezbee/zcl.h>
#include "zcl/esp_zigbee_zcl_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Break Change: Not supported */
#define esp_zb_commissioning_cluster_create(commissioning_cfg) NULL
#define esp_zb_ias_zone_cluster_create(ias_zone_cfg) NULL
#define esp_zb_ias_ace_cluster_create(ias_ace_cfg) NULL
#define esp_zb_ias_wd_cluster_create(ias_wd_cfg) NULL
#define esp_zb_electrical_meas_cluster_create(electrical_cfg) NULL
#define esp_zb_ota_cluster_create(ota_cfg) NULL
#define esp_zb_diagnostics_cluster_create(diag_cfg) NULL
#define esp_zb_drlc_cluster_create(drlc_cfg) NULL
#define esp_zb_cluster_list_add_commissioning_cluster(cluster_list, attr_list, role_mask) ESP_ERR_NOT_SUPPORTED
#define esp_zb_cluster_list_add_ias_zone_cluster(cluster_list, attr_list, role_mask) ESP_ERR_NOT_SUPPORTED
#define esp_zb_cluster_list_add_ias_ace_cluster(cluster_list, attr_list, role_mask) ESP_ERR_NOT_SUPPORTED
#define esp_zb_cluster_list_add_ias_wd_cluster(cluster_list, attr_list, role_mask) ESP_ERR_NOT_SUPPORTED
#define esp_zb_cluster_list_add_electrical_meas_cluster(cluster_list, attr_list, role_mask) ESP_ERR_NOT_SUPPORTED
#define esp_zb_cluster_list_add_ota_cluster(cluster_list, attr_list, role_mask) ESP_ERR_NOT_SUPPORTED
#define esp_zb_cluster_list_add_diagnostics_cluster(cluster_list, attr_list, role_mask) ESP_ERR_NOT_SUPPORTED
#define esp_zb_cluster_list_add_drlc_cluster(cluster_list, attr_list, role_mask) ESP_ERR_NOT_SUPPORTED

typedef ezb_zcl_basic_cluster_server_config_t                      esp_zb_basic_cluster_cfg_t;
typedef ezb_zcl_identify_cluster_server_config_t                   esp_zb_identify_cluster_cfg_t;
typedef ezb_zcl_on_off_cluster_server_config_t                     esp_zb_on_off_cluster_cfg_t;
typedef ezb_zcl_level_cluster_server_config_t                      esp_zb_level_cluster_cfg_t;
typedef ezb_zcl_time_cluster_server_config_t                       esp_zb_time_cluster_cfg_t;
typedef ezb_zcl_shade_config_cluster_server_config_t               esp_zb_shade_config_cluster_cfg_t;
typedef ezb_zcl_binary_input_cluster_server_config_t               esp_zb_binary_input_cluster_cfg_t;
typedef ezb_zcl_binary_output_cluster_server_config_t              esp_zb_binary_output_cluster_cfg_t;
typedef ezb_zcl_binary_value_cluster_server_config_t               esp_zb_binary_value_cluster_cfg_t;
typedef ezb_zcl_analog_input_cluster_server_config_t               esp_zb_analog_input_cluster_cfg_t;
typedef ezb_zcl_analog_output_cluster_server_config_t              esp_zb_analog_output_cluster_cfg_t;
typedef ezb_zcl_analog_value_cluster_server_config_t               esp_zb_analog_value_cluster_cfg_t;
typedef ezb_zcl_multistate_input_cluster_server_config_t           esp_zb_multistate_input_cluster_cfg_t;
typedef ezb_zcl_multistate_output_cluster_server_config_t          esp_zb_multistate_output_cluster_cfg_t;
typedef ezb_zcl_multistate_value_cluster_server_config_t           esp_zb_multistate_value_cluster_cfg_t;
typedef ezb_zcl_door_lock_cluster_server_config_t                  esp_zb_door_lock_cluster_cfg_t;
typedef ezb_zcl_pressure_measurement_cluster_server_config_t       esp_zb_pressure_meas_cluster_cfg_t;
typedef ezb_zcl_flow_measurement_cluster_server_config_t           esp_zb_flow_meas_cluster_cfg_t;
typedef ezb_zcl_touchlink_commissioning_cluster_config_t           esp_zb_touchlink_commissioning_cfg_t;
typedef ezb_zcl_fan_control_cluster_server_config_t                esp_zb_fan_control_cluster_cfg_t;
typedef ezb_zcl_thermostat_ui_config_cluster_server_config_t       esp_zb_thermostat_ui_config_cluster_cfg_t;
typedef ezb_zcl_ec_measurement_cluster_server_config_t             esp_zb_ec_measurement_cluster_cfg_t;
typedef ezb_zcl_ph_measurement_cluster_server_config_t             esp_zb_ph_measurement_cluster_cfg_t;
typedef ezb_zcl_wind_speed_measurement_cluster_server_config_t     esp_zb_wind_speed_measurement_cluster_cfg_t;
typedef ezb_zcl_carbon_dioxide_measurement_cluster_server_config_t esp_zb_carbon_dioxide_measurement_cluster_cfg_t;
typedef ezb_zcl_pm2_5_measurement_cluster_server_config_t          esp_zb_pm2_5_measurement_cluster_cfg_t;
typedef ezb_zcl_price_cluster_config_t                             esp_zb_price_cluster_cfg_t;
typedef ezb_zcl_dehumidification_control_cluster_server_config_t   esp_zb_dehumidification_control_cluster_cfg_t;
typedef ezb_zcl_device_temp_config_cluster_server_config_t         esp_zb_device_temp_config_cluster_cfg_t;
typedef ezb_zcl_alarms_cluster_server_config_t                     esp_zb_alarms_cluster_cfg_t;
typedef ezb_zcl_electrical_measurement_cluster_server_config_t     esp_zb_electrical_meas_cluster_cfg_t;
typedef ezb_zcl_color_control_cluster_server_config_t              esp_zb_color_control_cluster_cfg_t;

typedef struct esp_zb_commissioning_cluster_cfg_s {
    uint16_t           short_address;
    esp_zb_ieee_addr_t extended_panid;
    uint16_t           panid;
    uint32_t           channel_mask;
    uint8_t            protocol_version;
    uint8_t            stack_profile;
    uint8_t            startup_control;
    esp_zb_ieee_addr_t trust_center_address;
    uint8_t            network_key[16];
    bool               use_insecure_join;
    uint8_t            preconfigured_link_key[16];
    uint8_t            network_key_seq_num;
    uint8_t            network_key_type;
    uint16_t           network_manager_address;
} esp_zb_commissioning_cluster_cfg_t;

typedef struct esp_zb_zcl_ias_zone_int_ctx_s {
    void (*process_result_cb)(uint8_t param);
    void (*general_cb)(uint8_t param, uint16_t general_val);
    uint8_t restore_current_zone_sens_level;
    uint8_t new_current_zone_sens_level;
} esp_zb_zcl_ias_zone_int_ctx_t;

typedef struct esp_zb_ias_zone_cluster_cfg_s {
    uint8_t                       zone_state;
    uint16_t                      zone_type;
    uint16_t                      zone_status;
    esp_zb_ieee_addr_t            ias_cie_addr;
    uint8_t                       zone_id;
    esp_zb_zcl_ias_zone_int_ctx_t zone_ctx;
} esp_zb_ias_zone_cluster_cfg_t;

typedef struct esp_zb_ias_ace_cluster_cfg_s {
    uint8_t zone_table_length;
} esp_zb_ias_ace_cluster_cfg_t;

typedef struct esp_zb_ias_wd_cluster_cfg_s {
    uint16_t max_duration;
} esp_zb_ias_wd_cluster_cfg_t;

typedef struct esp_zb_ota_cluster_cfg_s {
    uint32_t           ota_upgrade_file_version;
    uint16_t           ota_upgrade_manufacturer;
    uint16_t           ota_upgrade_image_type;
    uint16_t           ota_min_block_reque;
    uint32_t           ota_upgrade_file_offset;
    uint32_t           ota_upgrade_downloaded_file_ver;
    esp_zb_ieee_addr_t ota_upgrade_server_id;
    uint8_t            ota_image_upgrade_status;
} esp_zb_ota_cluster_cfg_t;

typedef struct esp_zb_diagnostics_cluster_cfg_s {
} esp_zb_diagnostics_cluster_cfg_t;

typedef struct esp_zb_drlc_cluster_cfg_s {
    uint8_t  utility_enrollment_group;
    uint8_t  start_randomization_minutes;
    uint8_t  duration_randomization_minutes;
    uint16_t device_class_value;
} esp_zb_drlc_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for scenes cluster.
 *
 */
 typedef struct esp_zb_scenes_cluster_cfg_s {
    uint8_t  scenes_count;                      /*!<  The number of scenes currently in the scene table */
    uint8_t  current_scene;                     /*!<  Scene ID that invoked */
    uint16_t current_group;                     /*!<  Group ID that invoked */
    bool     scene_valid;                       /*!<  Indication of the associated with current scene and group valid or not*/
    uint8_t  name_support;                      /*!<  The indication of group names are supported or not */
    uint8_t  _reserved;
} esp_zb_scenes_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for illuminance measurement cluster
 *
 */
 typedef struct esp_zb_illuminance_meas_cluster_cfg_s {
    uint16_t measured_value;                     /*!<  The attribute indicates the illuminance from 0x0000 to 0xffff */
    uint16_t min_value;                          /*!<  The attribute indicates minimum value of the measured value */
    uint16_t max_value;                          /*!<  The attribute indicates maximum value of the measured value */
} esp_zb_illuminance_meas_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for power configuration cluster.
 *
 */
typedef struct esp_zb_power_config_cluster_cfg_s {
    uint16_t main_voltage;       /*!<  MainVoltage RMS voltage or DC voltage in units of 100mV */
    uint16_t main_voltage_min;   /*!<  Main voltage min threshold in unit of 100mV */
    uint16_t main_voltage_max;   /*!<  Main voltage max threshold in unit of 100mV */
    uint16_t main_voltage_dwell; /*!<  Main voltage exist in seconds */
    uint8_t  main_freq;          /*!<  MainFrequency in value of 0.5 * measured frequency, DC supply is 0Hz */
    uint8_t  main_alarm_mask;    /*!<  Main alram mask in bit */
} esp_zb_power_config_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for groups cluster.
 *
 */
typedef struct esp_zb_groups_cluster_cfg_s {
    uint8_t groups_name_support_id; /*!<  The indication of group names are supported or not */
} esp_zb_groups_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for on-off switch configuration cluster.
 *
 */
typedef struct esp_zb_on_off_switch_cluster_cfg_s {
    uint8_t switch_type;   /*!<  On Off switch type */
    uint8_t switch_action; /*!< On off switch action */
} esp_zb_on_off_switch_cluster_cfg_t;
typedef esp_zb_on_off_switch_cluster_cfg_t esp_zb_on_off_switch_config_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for color control cluster.
 *
 */
typedef struct esp_zb_color_cluster_cfg_s {
    uint16_t current_x;           /*!<  The current value of the normalized chromaticity value x */
    uint16_t current_y;           /*!<  The current value of the normalized chromaticity value y */
    uint8_t  color_mode;          /*!<  The mode which attribute determines the color of the device */
    uint8_t  options;             /*!<  The bitmap determines behavior of some cluster commands */
    uint8_t  enhanced_color_mode; /*!<  The enhanced-mode which attribute determines the color of the device */
    uint16_t color_capabilities;  /*!<  Specifying the color capabilities of the device support the color control cluster */
    uint8_t  _reserved;
} esp_zb_color_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for temperature measurement cluster.
 *
 */
typedef struct esp_zb_temperature_meas_cluster_cfg_s {
    int16_t measured_value; /*!<  The attribute indicates the temperature in degrees Celsius */
    int16_t min_value;      /*!<  The attribute indicates minimum value of the measured value */
    int16_t max_value;      /*!<  The attribute indicates maximum value of the measured value */
} esp_zb_temperature_meas_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for humidity measurement cluster.
 *
 */
typedef struct esp_zb_humidity_meas_cluster_cfg_s {
    uint16_t measured_value; /*!<  The attribute indicates the humidity in 100*percent */
    uint16_t min_value;      /*!<  The attribute indicates minimum value of the measured value */
    uint16_t max_value;      /*!<  The attribute indicates maximum value of the measured value */
} esp_zb_humidity_meas_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for occupancy sensing cluster
 *
 */
typedef struct esp_zb_occupancy_sensing_cluster_cfg_s {
    uint8_t occupancy;          /*!<  Bit 0 specifies the sensed occupancy as follows: 1 = occupied, 0 = unoccupied. */
    uint8_t sensor_type;        /*!<  The attribute specifies the type of the occupancy sensor */
    uint8_t sensor_type_bitmap; /*!<  The attribute specifies the types of the occupancy sensor */
} esp_zb_occupancy_sensing_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for window covering cluster
 *
 */
typedef struct esp_zb_window_covering_cluster_cfg_s {
    uint8_t covering_type;   /*!<  This attribute identifies the type of window covering being controlled by this endpoint */
    uint8_t covering_status; /*!<  This attribute makes configuration and status information available */
    uint8_t covering_mode;   /*!<  This attribute allows configuration of the window covering */
} esp_zb_window_covering_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for thermostat cluster
 *
 */
typedef struct esp_zb_thermostat_cluster_cfg_s {
    int16_t local_temperature;             /*!< This attribute represents the temperature in degrees Celsius */
    uint8_t control_sequence_of_operation; /*!< This attribute specifies the overall operating environment and possible system modes */
    uint8_t system_mode;                   /*!< This attribute specifies the current operating mode */
    int16_t occupied_cooling_setpoint;     /*!< This attribute specifies the cooling mode setpoint when the room is occupied */
    int16_t occupied_heating_setpoint;     /*!< This attribute specifies the heating mode setpoint when the room is occupied */
} esp_zb_thermostat_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for metering cluster
 *
 */
typedef struct esp_zb_metering_cluster_cfg_s {
    esp_zb_uint48_t current_summation_delivered; /*!< This attribute represents the most recent summed value of Energy, Gas, or
                                                    Water delivered and consumed in the premises */
    uint8_t
        status; /*!< This attribute provides indicators reflecting the current error conditions found by the metering device */
    uint8_t uint_of_measure; /*!< This attribute provides a label for the Energy, Gas, or Water being measured by the metering
                                device. refer to esp_zb_zcl_metering_unit_of_measure_t */
    uint8_t summation_formatting; /*!< This attribute provides a method to properly decipher the number of digits and the
                                     decimal location of the values found in the Summation Information Set */
    uint8_t metering_device_type; /*!< This attribute provides a label for identifying the type of metering device (Energy, Gas,
                                     Water, Thermal, Heat, Cooling, and mirrored metering devices). refer to
                                     esp_zb_zcl_metering_device_type_t */
} esp_zb_metering_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for meter identification cluster
 *
 */
typedef struct esp_zb_meter_identification_cluster_cfg_s {
    char company_name[17]; /*!< This attribute provides the name of the meter manufacturer. (1 octet length + 16 octets data) */
    uint16_t meter_type_id;   /*!< This attribute provides a label to identify the installation features of the meter. */
    uint16_t data_quality_id; /*!< This attribute provides a label to identify the Meter Simple Metering information
                                 certification type. */
    char pod[17]; /*!< This attribute provides a unique identification ID of the premise connection point. (1 octet length + 16
                     octets data) */
    esp_zb_uint24_t available_power; /*!< This attribute represents the InstantaneousDemand that can be distributed to the
                                        customer without any risk of overload. */
    esp_zb_uint24_t power_threshold; /*!< This attribute represents a threshold of InstantaneousDemand distributed to the
                                        customer that will lead to an imminent risk of overload. */
} esp_zb_meter_identification_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory and server optional attributes for poll control cluster
 *
 */
typedef struct esp_zb_poll_control_cluster_cfg_s {
    uint32_t check_in_interval;  /*!< This attribute represents the default amount of time between check-ins by the poll control
                                    server with the poll control client. */
    uint32_t long_poll_interval; /*!< This attribute defines the frequency of polling that an end device does when it is NOT in
                                    fast poll mode. */
    uint16_t short_poll_interval; /*!< This attribute represents the number of quarter-seconds that an end device waits between
                                     MAC Data Requests to its parent when it is expecting data */
    uint16_t fast_poll_timeout;   /*!< This attribute represents the number of quarter-seconds that an end device will stay in
                                     fast poll mode by default. */
    uint32_t check_in_interval_min;  /*!< The Poll Control Server MAY optionally provide its own minimum value for the
                                        Check-inInterval */
    uint32_t long_poll_interval_min; /*!< The Poll Control Server MAY optionally provide its own minimum value for the
                                        LongPollInterval */
    uint16_t fast_poll_timeout_max;  /*!< The Poll Control Server MAY optionally provide its own maximum value for the
                                        FastPollTimeout*/
} esp_zb_poll_control_cluster_cfg_t;

/**
 * @brief  Create an empty cluster list.
 *
 * @note  This cluster list is ready to add / update cluster refer to esp_zb_cluster_list_add_xxx_cluster() and
 * esp_zb_cluster_list_update_xxx_cluster().
 * @return pointer to  @ref esp_zb_cluster_list_s
 *
 */
esp_zb_cluster_list_t *esp_zb_zcl_cluster_list_create(void);

/**
 * @brief  Get ZCL cluster descriptor.
 *
 * @note  Getting the local cluster from the specific endpoint.
 *
 * @param[in] endpoint The endpoint
 * @param[in] cluster_id The cluster id for attribute list refer to esp_zb_zcl_cluster_id
 * @param[in] cluster_role The cluster role of this cluster, either server or client role refer to esp_zb_zcl_cluster_role_t
 *
 * @return pointer to  @ref esp_zb_zcl_cluster_s
 *
 */
esp_zb_zcl_cluster_t *esp_zb_zcl_get_cluster(uint8_t endpoint, uint16_t cluster_id, uint8_t cluster_role);

/********************************* ZCL HA standard cluster ********************************/

/**
 * @brief  Create a standard basic cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] basic_cfg  Configuration parameters for this cluster defined by @ref esp_zb_basic_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_basic_cluster_create(esp_zb_basic_cluster_cfg_t *basic_cfg);

/**
 * @brief  Create a power configuration cluster attribute list.
 *
 * @note  No mandatory attributes are requested by the ZCL specs, in current implementation main voltage and frequency are added
 * by default.
 * @param[in] power_cfg  Configuration parameters for this cluster defined by @ref esp_zb_power_config_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_power_config_cluster_create(esp_zb_power_config_cluster_cfg_t *power_cfg);

/**
 * @brief  Create a standard identify cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] identify_cfg  Configuration parameters for this cluster defined by @ref esp_zb_identify_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_identify_cluster_create(esp_zb_identify_cluster_cfg_t *identify_cfg);

/**
 * @brief  Create a standard group cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] group_cfg  Configuration parameters for this cluster defined by @ref esp_zb_groups_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_groups_cluster_create(esp_zb_groups_cluster_cfg_t *group_cfg);

/**
 * @brief  Create a standard scenes cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] scene_cfg  Configuration parameters for this cluster defined by @ref esp_zb_scenes_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_scenes_cluster_create(esp_zb_scenes_cluster_cfg_t *scene_cfg);

/**
 * @brief  Create a standard on-off cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] on_off_cfg  Configuration parameters for this cluster defined by @ref esp_zb_on_off_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_on_off_cluster_create(esp_zb_on_off_cluster_cfg_t *on_off_cfg);

/**
 * @brief  Create a standard on-off switch config cluster attribute list.
 *
 * @note  This only contains the mandatory attribute. Switch type attribute default set to 0. User could change it if necessary.
 * @param[in] on_off_switch_cfg  Configuration parameters for this cluster defined by @ref esp_zb_on_off_switch_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_on_off_switch_config_cluster_create(esp_zb_on_off_switch_cluster_cfg_t *on_off_switch_cfg);

/**
 * @brief  Create a standard level cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] level_cfg  Configuration parameters for this cluster defined by @ref esp_zb_level_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_level_cluster_create(esp_zb_level_cluster_cfg_t *level_cfg);

/**
 * @brief  Create a standard color cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] color_cfg  Configuration parameters for this cluster defined by @ref esp_zb_color_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_color_control_cluster_create(esp_zb_color_cluster_cfg_t *color_cfg);

/**
 * @brief  Create a standard time cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] time_cfg  Configuration parameters for this cluster defined by @ref esp_zb_time_cluster_cfg_s
 * @note time interface must be registered after the cluster is created. See ezb_zcl_time_server_interface_register() for more
 * details.
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_time_cluster_create(esp_zb_time_cluster_cfg_t *time_cfg);

/**
 * @brief  Create a standard shade config cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] shade_cfg  Configuration parameters for this cluster defined by @ref esp_zb_shade_config_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_shade_config_cluster_create(esp_zb_shade_config_cluster_cfg_t *shade_cfg);

/**
 * @brief  Create a standard binary input (basic) cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] binary_input_cfg  Configuration parameters for this cluster defined by @ref esp_zb_binary_input_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_binary_input_cluster_create(esp_zb_binary_input_cluster_cfg_t *binary_input_cfg);

/**
 * @brief  Create a standard door lock cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] lock_cfg  Configuration parameters for this cluster defined by @ref esp_zb_door_lock_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_door_lock_cluster_create(esp_zb_door_lock_cluster_cfg_t *lock_cfg);

/**
 * @brief  Create a standard temperature measurement cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] temperature_cfg  Configuration parameters for this cluster defined by @ref esp_zb_temperature_meas_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_temperature_meas_cluster_create(esp_zb_temperature_meas_cluster_cfg_t *temperature_cfg);

/**
 * @brief  Create a standard humidity measurement cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] humidity_cfg  Configuration parameters for this cluster defined by @ref esp_zb_humidity_meas_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_humidity_meas_cluster_create(esp_zb_humidity_meas_cluster_cfg_t *humidity_cfg);

/**
 * @brief Create a standard illuminance measurement cluster attribute list.
 *
 * @param[in] illuminance_cfg Configuration parameters for this cluster defined by @ref esp_zb_illuminance_meas_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_illuminance_meas_cluster_create(esp_zb_illuminance_meas_cluster_cfg_t *illuminance_cfg);

/**
 * @brief Create a standard pressure measurement cluster attribute list.
 *
 * @param[in] pressure_cfg Configuration parameters for this cluster defined by @ref esp_zb_pressure_meas_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_pressure_meas_cluster_create(esp_zb_pressure_meas_cluster_cfg_t *pressure_cfg);

/**
 * @brief Create a standard flow measurement cluster attribute list.
 *
 * @param[in] flow_meas_cfg Configuration parameters for this cluster defined by @ref esp_zb_flow_meas_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_flow_meas_cluster_create(esp_zb_flow_meas_cluster_cfg_t *flow_meas_cfg);

/**
 * @brief Create a standard occupancy sensor cluster attribute list.
 *
 * @param[in] sensing_cfg Configuration parameters for this cluster defined by @ref esp_zb_occupancy_sensing_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_occupancy_sensing_cluster_create(esp_zb_occupancy_sensing_cluster_cfg_t *sensing_cfg);

/**
 * @brief Create a standard window covering cluster attribute list.
 *
 * @param[in] covering_cfg Configuration parameters for this cluster defined by @ref esp_zb_window_covering_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_window_covering_cluster_create(esp_zb_window_covering_cluster_cfg_t *covering_cfg);

/**
 * @brief  Create a standard touchlink commissioning cluster attribute list
 *
 * @note  This only contains the `ZB_ZCL_ATTR_GLOBAL_CLUSTER_REVISION_ID` and touchlink commissioning cluster has no attributes.
 *
 * @param[in] tl_cfg  Configuration parameters for this cluster defined by @ref esp_zb_touchlink_commissioning_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_touchlink_commissioning_cluster_create(esp_zb_touchlink_commissioning_cfg_t *tl_cfg);

/**
 * @brief  Create a standard thermostat cluster attribute list
 *
 * @param[in] thermostat_cfg  Configuration parameters for this cluster defined by @ref esp_zb_thermostat_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_thermostat_cluster_create(esp_zb_thermostat_cluster_cfg_t *thermostat_cfg);

/**
 * @brief  Create a standard fan control attribute list
 *
 * @param[in] fan_control_cfg  Configuration parameters for this cluster defined by @ref esp_zb_fan_control_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_fan_control_cluster_create(esp_zb_fan_control_cluster_cfg_t *fan_control_cfg);

/**
 * @brief  Create a standard thermostat ui config attribute list
 *
 * @param[in] thermostat_ui_config_cfg  Configuration parameters for this cluster defined by @ref
 * esp_zb_thermostat_ui_config_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_thermostat_ui_config_cluster_create(
    esp_zb_thermostat_ui_config_cluster_cfg_t *thermostat_ui_config_cfg);

/**
 * @brief  Create a standard analog input attribute list
 *
 * @param[in] analog_input_cfg  Configuration parameters for this cluster defined by @ref esp_zb_analog_input_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_analog_input_cluster_create(esp_zb_analog_input_cluster_cfg_t *analog_input_cfg);

/**
 * @brief  Create a standard analog output attribute list
 *
 * @param[in] analog_output_cfg  Configuration parameters for this cluster defined by @ref esp_zb_analog_output_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_analog_output_cluster_create(esp_zb_analog_output_cluster_cfg_t *analog_output_cfg);

/**
 * @brief  Create a standard analog value attribute list
 *
 * @param[in] analog_value_cfg  Configuration parameters for this cluster defined by @ref esp_zb_analog_value_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_analog_value_cluster_create(esp_zb_analog_value_cluster_cfg_t *analog_value_cfg);

/**
 * @brief  Create a standard electrical conductivity measurement cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] ec_measurement_cfg  Configuration parameters for this cluster defined by @ref esp_zb_ec_measurement_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_ec_measurement_cluster_create(esp_zb_ec_measurement_cluster_cfg_t *ec_measurement_cfg);

/**
 * @brief  Create a standard pH measurement cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] ph_measurement_cfg  Configuration parameters for this cluster defined by @ref esp_zb_ph_measurement_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_ph_measurement_cluster_create(esp_zb_ph_measurement_cluster_cfg_t *ph_measurement_cfg);

/**
 * @brief  Create a standard wind speed measurement cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] wind_speed_measurement_cfg  Configuration parameters for this cluster defined by @ref
 * esp_zb_wind_speed_measurement_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_wind_speed_measurement_cluster_create(
    esp_zb_wind_speed_measurement_cluster_cfg_t *wind_speed_measurement_cfg);

/**
 * @brief  Create a standard carbon dioxide measurement attribute list
 *
 * @param[in] carbon_dioxide_measurement_cfg  Configuration parameters for this cluster defined by @ref
 * esp_zb_carbon_dioxide_measurement_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_carbon_dioxide_measurement_cluster_create(
    esp_zb_carbon_dioxide_measurement_cluster_cfg_t *carbon_dioxide_measurement_cfg);

/**
 * @brief  Create a standard pm2.5 measurement attribute list
 *
 * @param[in] pm2_5_measurement_cfg  Configuration parameters for this cluster defined by @ref
 * esp_zb_pm2_5_measurement_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_pm2_5_measurement_cluster_create(esp_zb_pm2_5_measurement_cluster_cfg_t *pm2_5_measurement_cfg);

/**
 * @brief  Create a standard multistate input cluster attribute list.
 *
 * @param[in] multistate_input_cfg  Configuration parameters for this cluster defined by @ref
 * esp_zb_multistate_input_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_multistate_input_cluster_create(esp_zb_multistate_input_cluster_cfg_t *multistate_input_cfg);

/**
 * @brief  Create a standard multistate output cluster attribute list.
 *
 * @param[in] multistate_output_cfg  Configuration parameters for this cluster defined by @ref
 * esp_zb_multistate_output_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_multistate_output_cluster_create(esp_zb_multistate_output_cluster_cfg_t *multistate_output_cfg);

/**
 * @brief  Create a standard multistate value attribute list
 *
 * @param[in] multistate_value_cfg  Configuration parameters for this cluster defined by @ref
 * esp_zb_multistate_value_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_multistate_value_cluster_create(esp_zb_multistate_value_cluster_cfg_t *multistate_value_cfg);

/**
 * @brief  Create a standard metering attribute list
 *
 * @param[in] metering_cfg  Configuration parameters for this cluster defined by @ref esp_zb_metering_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_metering_cluster_create(esp_zb_metering_cluster_cfg_t *metering_cfg);

/**
 * @brief  Create a standard metering attribute list
 *
 * @param[in] meter_identification_cfg  Configuration parameters for this cluster defined by @ref
 * esp_zb_meter_identification_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_meter_identification_cluster_create(
    esp_zb_meter_identification_cluster_cfg_t *meter_identification_cfg);

/**
 * @brief  Create a standard price attribute list
 *
 * @param[in] price_cfg Configuration parameters for this cluster defined by @ref esp_zb_price_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_price_cluster_create(esp_zb_price_cluster_cfg_t *price_cfg);

/**
 * @brief  Create a standard dehumidification control attribute list
 *
 * @param[in] dehumidification_cfg Configuration parameters for this cluster defined by @ref
 * esp_zb_dehumidification_control_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_dehumidification_control_cluster_create(
    esp_zb_dehumidification_control_cluster_cfg_t *dehumidification_cfg);

/**
 * @brief  Create a standard binary output (basic) cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] binary_output_cfg  Configuration parameters for this cluster defined by @ref esp_zb_binary_output_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_binary_output_cluster_create(esp_zb_binary_output_cluster_cfg_t *binary_output_cfg);

/**
 * @brief  Create a standard binary value cluster attribute list.
 *
 * @note  This only contains the mandatory attribute.
 * @param[in] binary_value_cfg  Configuration parameters for this cluster defined by @ref esp_zb_binary_value_cluster_cfg_s
 *
 * @return Pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_binary_value_cluster_create(esp_zb_binary_value_cluster_cfg_t *binary_value_cfg);

/**
 * @brief  Create a standard poll control attribute list
 *
 * @param[in] poll_control_cfg  Configuration parameters for this cluster defined by @ref esp_zb_poll_control_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_poll_control_cluster_create(esp_zb_poll_control_cluster_cfg_t *poll_control_cfg);

/**
 * @brief  Create a standard device temperature configuration attribute list
 *
 * @param[in] cfg  Configuration parameters for this cluster defined by @ref esp_zb_device_temp_config_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_device_temp_config_cluster_create(esp_zb_device_temp_config_cluster_cfg_t *cfg);

/**
 * @brief  Create a standard alarms attribute list
 *
 * If the alarm_table_size is not zero, the alarm_count attribute will be added by this function
 *
 * @param[in] cfg  Configuration parameters for this cluster defined by @ref esp_zb_alarms_cluster_cfg_s
 *
 * @return pointer to attribute list @ref esp_zb_attribute_list_s
 *
 */
esp_zb_attribute_list_t *esp_zb_alarms_cluster_create(esp_zb_alarms_cluster_cfg_t *cfg);

/**************************************** ADD CLUSTER ***********************************/
/**
 * @brief Add basic cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_basic_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                esp_zb_attribute_list_t *attr_list,
                                                uint8_t                  role_mask);

/**
 * @brief Add power configuration cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_power_config_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                       esp_zb_attribute_list_t *attr_list,
                                                       uint8_t                  role_mask);

/**
 * @brief Add identify cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_identify_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                   esp_zb_attribute_list_t *attr_list,
                                                   uint8_t                  role_mask);

/**
 * @brief Add groups cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_groups_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                 esp_zb_attribute_list_t *attr_list,
                                                 uint8_t                  role_mask);

/**
 * @brief Add scenes cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_scenes_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                 esp_zb_attribute_list_t *attr_list,
                                                 uint8_t                  role_mask);

/**
 * @brief Add on_off cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_on_off_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                 esp_zb_attribute_list_t *attr_list,
                                                 uint8_t                  role_mask);

/**
 * @brief Add on_off switch config cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_on_off_switch_config_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                               esp_zb_attribute_list_t *attr_list,
                                                               uint8_t                  role_mask);

/**
 * @brief Add level cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_level_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                esp_zb_attribute_list_t *attr_list,
                                                uint8_t                  role_mask);

/**
 * @brief Add color_control cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_color_control_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                        esp_zb_attribute_list_t *attr_list,
                                                        uint8_t                  role_mask);

/**
 * @brief Add Time cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_time_cluster(esp_zb_cluster_list_t   *cluster_list,
                                               esp_zb_attribute_list_t *attr_list,
                                               uint8_t                  role_mask);

/**
 * @brief Add Shade Config cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_shade_config_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                       esp_zb_attribute_list_t *attr_list,
                                                       uint8_t                  role_mask);

/**
 * @brief Add binary input (basic) cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_binary_input_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                       esp_zb_attribute_list_t *attr_list,
                                                       uint8_t                  role_mask);

/**
 * @brief Add binary output (basic) cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_binary_output_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                        esp_zb_attribute_list_t *attr_list,
                                                        uint8_t                  role_mask);

/**
 * @brief Add binary value cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_binary_value_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                       esp_zb_attribute_list_t *attr_list,
                                                       uint8_t                  role_mask);

/**
 * @brief Add Door Lock cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_door_lock_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                    esp_zb_attribute_list_t *attr_list,
                                                    uint8_t                  role_mask);

/**
 * @brief Add Temperature measurement cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_temperature_meas_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                           esp_zb_attribute_list_t *attr_list,
                                                           uint8_t                  role_mask);

/**
 * @brief Add Humidity measurement cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_humidity_meas_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                        esp_zb_attribute_list_t *attr_list,
                                                        uint8_t                  role_mask);

/**
 * @brief Add illuminance measurement cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_illuminance_meas_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                           esp_zb_attribute_list_t *attr_list,
                                                           uint8_t                  role_mask);

/**
 * @brief Add pressure measurement cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_pressure_meas_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                        esp_zb_attribute_list_t *attr_list,
                                                        uint8_t                  role_mask);

/**
 * @brief Add flow measurement cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_flow_meas_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                    esp_zb_attribute_list_t *attr_list,
                                                    uint8_t                  role_mask);

/**
 * @brief Add occupancy sensor cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_occupancy_sensing_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                            esp_zb_attribute_list_t *attr_list,
                                                            uint8_t                  role_mask);

/**
 * @brief Add window covering cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_window_covering_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                          esp_zb_attribute_list_t *attr_list,
                                                          uint8_t                  role_mask);

/**
 * @brief Add touchlink commissioning cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list An attribute list which wants to add
 * @param[in] role_mask A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @note The touchlink commissioning cluster id should not be same as already existing zcl cluster id refer to zb_zcl_common.h
 *
 * @return
 * - ESP_OK on success
 * - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_touchlink_commissioning_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                                  esp_zb_attribute_list_t *attr_list,
                                                                  uint8_t                  role_mask);

/**
 * @brief Add thermostat cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_thermostat_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                     esp_zb_attribute_list_t *attr_list,
                                                     uint8_t                  role_mask);

/**
 * @brief Add fan control cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_fan_control_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                      esp_zb_attribute_list_t *attr_list,
                                                      uint8_t                  role_mask);

/**
 * @brief Add thermostat ui config cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_thermostat_ui_config_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                               esp_zb_attribute_list_t *attr_list,
                                                               uint8_t                  role_mask);

/**
 * @brief Add analog input cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_analog_input_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                       esp_zb_attribute_list_t *attr_list,
                                                       uint8_t                  role_mask);

/**
 * @brief Add analog output cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_analog_output_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                        esp_zb_attribute_list_t *attr_list,
                                                        uint8_t                  role_mask);

/**
 * @brief Add analog value cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_analog_value_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                       esp_zb_attribute_list_t *attr_list,
                                                       uint8_t                  role_mask);

/**
 * @brief Add electrical conductivity measurement cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_ec_measurement_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                         esp_zb_attribute_list_t *attr_list,
                                                         uint8_t                  role_mask);

/**
 * @brief Add pH measurement cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_ph_measurement_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                         esp_zb_attribute_list_t *attr_list,
                                                         uint8_t                  role_mask);

/**
 * @brief Add wind speed measurement cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_wind_speed_measurement_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                                 esp_zb_attribute_list_t *attr_list,
                                                                 uint8_t                  role_mask);

/**
 * @brief Add carbon dioxide measurement cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_carbon_dioxide_measurement_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                                     esp_zb_attribute_list_t *attr_list,
                                                                     uint8_t                  role_mask);

/**
 * @brief Add pm2.5 measurement cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_pm2_5_measurement_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                            esp_zb_attribute_list_t *attr_list,
                                                            uint8_t                  role_mask);

/**
 * @brief Add MultiState Input cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_multistate_input_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                           esp_zb_attribute_list_t *attr_list,
                                                           uint8_t                  role_mask);

/**
 * @brief Add MultiState Output cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_multistate_output_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                            esp_zb_attribute_list_t *attr_list,
                                                            uint8_t                  role_mask);

/**
 * @brief Add multistate value cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_multistate_value_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                           esp_zb_attribute_list_t *attr_list,
                                                           uint8_t                  role_mask);

/**
 * @brief Add metering cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_metering_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                   esp_zb_attribute_list_t *attr_list,
                                                   uint8_t                  role_mask);

/**
 * @brief Add meter identification cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_meter_identification_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                               esp_zb_attribute_list_t *attr_list,
                                                               uint8_t                  role_mask);

/**
 * @brief Add price cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_price_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                esp_zb_attribute_list_t *attr_list,
                                                uint8_t                  role_mask);

/**
 * @brief Add dehumidification control cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_dehumidification_control_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                                   esp_zb_attribute_list_t *attr_list,
                                                                   uint8_t                  role_mask);

/**
 * @brief Add customized cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list An attribute list which wants to add
 * @param[in] role_mask A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @note The customized cluster id should not be same as already existing zcl cluster id refer to zb_zcl_common.h
 *
 * @return
 * - ESP_OK on success
 * - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_custom_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                 esp_zb_attribute_list_t *attr_list,
                                                 uint8_t                  role_mask);

/**
 * @brief Add poll control cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_poll_control_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                       esp_zb_attribute_list_t *attr_list,
                                                       uint8_t                  role_mask);

/**
 * @brief Add device temperature configuration cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_device_temp_config_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                             esp_zb_attribute_list_t *attr_list,
                                                             uint8_t                  role_mask);

/**
 * @brief Add device alarms (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to add
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_add_alarms_cluster(esp_zb_cluster_list_t   *cluster_list,
                                                 esp_zb_attribute_list_t *attr_list,
                                                 uint8_t                  role_mask);

/**
 * @brief Get cluster (attribute list) from a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] cluster_id The cluster id for attribute list refer to esp_zb_zcl_cluster_id
 * @param[in] role_mask A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - pointer to  @ref esp_zb_attribute_list_s, if the cluster is found in the cluster list
 *      - ``NULL`` if cluster is not found
 *
 */
esp_zb_attribute_list_t *esp_zb_cluster_list_get_cluster(const esp_zb_cluster_list_t *cluster_list,
                                                         uint16_t                     cluster_id,
                                                         uint8_t                      role_mask);

/**
 * @brief Update cluster (attribute list) in a cluster list.
 *
 * @param[in] cluster_list A pointer to cluster list @ref esp_zb_cluster_list_s
 * @param[in] attr_list  An attribute list which wants to update
 * @param[in] cluster_id The cluster id for attribute list refer to esp_zb_zcl_cluster_id
 * @param[in] role_mask  A role of server or client for this cluster (attribute list) refer to esp_zb_zcl_cluster_role_t
 *
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG if cluster list not initialized
 *
 */
esp_err_t esp_zb_cluster_list_update_cluster(esp_zb_cluster_list_t *cluster_list, esp_zb_attribute_list_t *attr_list,
                                             uint16_t cluster_id, uint8_t role_mask);

#ifdef __cplusplus
}
#endif

#else
#error "This file is for compatibility, please include "ezbee/zcl.h"!"
#endif
