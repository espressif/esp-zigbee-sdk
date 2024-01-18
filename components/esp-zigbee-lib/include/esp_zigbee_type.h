/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include <math.h>
#include <stdint.h>
#include "stdbool.h"

#define ESP_ZB_PACKED_STRUCT __attribute__ ((packed))

typedef uint8_t esp_zb_64bit_addr_t[8];
typedef esp_zb_64bit_addr_t esp_zb_ieee_addr_t;
typedef void (*esp_zb_zcl_cluster_init_t)(void);
typedef void (*esp_zb_callback_t)(uint8_t param);

/**
 * @brief The Zigbee address union consist of 16 bit short address and 64 bit long address.
 *
 */
typedef union {
    uint16_t  addr_short;                           /*!< Zigbee short address */
    esp_zb_ieee_addr_t addr_long;                   /*!< Zigbee long address */
} esp_zb_addr_u;

/** Definition of the Zigbee ZCL address type
 * @brief Possible address types of devices from which ZCL message is received.
 * @anchor esp_zb_zcl_address_type_t
 */
#define ESP_ZB_ZCL_ADDR_TYPE_SHORT           0U
#define ESP_ZB_ZCL_ADDR_TYPE_IEEE_GPD        1U
#define ESP_ZB_ZCL_ADDR_TYPE_SRC_ID_GPD      2U
#define ESP_ZB_ZCL_ADDR_TYPE_IEEE            3U
#define ESP_ZB_CCM_KEY_SIZE                  16U

/**
 * @brief Type to represent source address of ZCL message
 * @note Address type refer @ref esp_zb_zcl_address_type_t
 */
typedef struct esp_zb_zcl_addr_s {
    uint8_t addr_type;                  /*!< address type see esp_zb_zcl_address_type_t */
    union {
        uint16_t short_addr;            /*!< Zigbee short address */
        uint32_t src_id;                /*!< Source ID of ZGPD */
        esp_zb_ieee_addr_t ieee_addr;   /*!< Full IEEE-address of ZGPD */
    } u;                                /*!< Union of the address */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_addr_t;

/**
 * @brief Type to represent header info callback of ZCL message
 */
typedef struct esp_zb_zcl_cmd_cb_s {
    esp_zb_zcl_addr_t zcl_addr_u;               /*!< ZCL command source node single short address, group address or ieee address */
    uint8_t  dst_endpoint;                      /*!< ZCL command destination endpoint */
    uint8_t  src_endpoint;                      /*!< ZCL command source endpoint */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_cmd_cb_t;

/**
 * @brief Type to represent ZCL attribute definition structure
 * @note Access define refer to zcl_attr_access
 */
typedef struct esp_zb_zcl_attr_s {
    uint16_t id;                        /*!< Attribute id */
    uint8_t type;                       /*!< Attribute type see zcl_attr_type */
    uint8_t access;                     /*!< Attribute access options according to zcl_attr_access */
    uint16_t manuf_code;                /*!< Manufacture specific id, refer to ESP_ZB_ZCL_NON_MANUFACTURER_SPECIFIC */
    void *data_p;                       /*!< Pointer to attribute data */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_attr_t;

/**
 * @brief Type to represent ZCL cluster definition structure
 * @note Cluster id refer to zcl_cluster_id and attribute define see @ref esp_zb_zcl_attr_s
 */
typedef struct esp_zb_zcl_cluster_s {
    uint16_t cluster_id;                        /*!< ZCL 16-bit cluster id. Refer zcl_cluster_id */
    uint16_t attr_count;                        /*!< Attributes number supported by the cluster */
    esp_zb_zcl_attr_t *attr_desc_list;          /*!< List of cluster attributes esp_zb_zcl_attr_t */
    uint8_t role_mask;                          /*!< Cluster role, refer to zcl_cluster_role */
    uint16_t manuf_code;                        /*!< Manufacturer code for cluster and its attributes */
    esp_zb_zcl_cluster_init_t cluster_init;     /*!< cluster init callback function */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_cluster_t;

/**
 * @brief Type to represent type signed int_24
 * @note Internal use
 */
typedef struct esp_zb_int24_s {
    uint16_t low;               /*!< Low 16-bit of the value */
    int8_t   high;              /*!< High 8-bit of the value with signed */
} ESP_ZB_PACKED_STRUCT
esp_zb_int24_t;

/**
 * @brief Type to represent type unsigned int_24
 * @note Internal use
 */
typedef struct esp_zb_uint24_s {
    uint16_t low;               /*!< Low 16-bit of the value */
    uint8_t high;               /*!< High 8-bit of the value */
} ESP_ZB_PACKED_STRUCT
esp_zb_uint24_t;

/**
 * @brief Type to represent type unsigned int_48
 * @note Internal use
 */
typedef struct esp_zb_uint48_s {
    uint32_t low;               /*!< Low 32-bit of the value */
    uint16_t high;              /*!< High 16-bit of the value */
} ESP_ZB_PACKED_STRUCT
esp_zb_uint48_t;

/**
 * @brief Type to represent type signed int_48
 * @note Internal use
 */
typedef struct esp_zb_int48_s {
    uint32_t low;               /*!< Low 32-bit of the value */
    int16_t high;               /*!< High 16-bit of the value with signed */
} ESP_ZB_PACKED_STRUCT
esp_zb_int48_t;

/**
 * @brief Union of the ZCL attribute value
 * @note Internal use
 */
union esp_zb_zcl_attr_var_u {
    uint8_t u8;         /*!< Unsigned 8-bit int of integer */
    int8_t s8;          /*!< Signed 8-bit int of integer */
    uint16_t u16;       /*!< Unsigned 16-bit of integer */
    int16_t s16;        /*!< Signed 16-bit of integer */
    esp_zb_uint24_t u24;/*!< Unsigned 24-bit of the integer */
    esp_zb_int24_t s24; /*!< Signed 24-bit of the integer */
    uint32_t u32;       /*!< Unsigned 32-bit of the integer */
    int32_t s32;        /*!< Signed 32-bit of the integer */
    esp_zb_uint48_t u48;/*!< Unsigned 48-bit of the integer */
    uint8_t data_buf[4];/*!< Data array */
};

/**
 * @brief Type to represent ZCL attribute reporting info structure
 * 
 */
typedef struct esp_zb_zcl_reporting_info_s {
    uint8_t direction;              /*!< Direction: report is send or received */
    uint8_t ep;                     /*!< Endpoint number */
    uint16_t cluster_id;            /*!< Cluster ID for reporting */
    uint8_t cluster_role;           /*!< Cluster rolo server/client */
    uint16_t attr_id;               /*!< Attribute ID for reporting */
    uint8_t flags;                  /*!< Flags to inform status of reporting */
    uint32_t run_time;              /*!< Time to run next reporting activity */
    union {
        struct {
            uint16_t min_interval; /*!< Actual minimum reporting interval */
            uint16_t max_interval; /*!< Actual maximum reporting interval */
            union esp_zb_zcl_attr_var_u delta; /*!< Actual reportable change */
            union esp_zb_zcl_attr_var_u reported_value; /*!< The last reported value */
            uint16_t def_min_interval; /*!< Default minimum reporting interval */
            uint16_t def_max_interval; /*!< Default maximum reporting interval */
        }
        send_info;  /*!< send_info is stored on cluster server side (as usual) and describes how
                  attribute should be reported */
        struct {
            uint16_t timeout; /*!< Timeout period */
        }
        recv_info; /*!< recv_info is stored on cluster client side (as usual) and describes how
                 attribute report is received */
    }
    u;            /*!< Union of the report info*/

    struct {
        uint16_t short_addr; /*!< Destination short address */
        uint8_t  endpoint;   /*!< Destination endpoint */
        uint16_t profile_id; /*!< Profile id */
    }
    dst;        /*!< Union of the ZCL destination */
    uint16_t manuf_code; /*!< Manufacturer specific code */
}
esp_zb_zcl_reporting_info_t;

/**
 * @brief Structure of Alarm variables
 * @note Internal use
 */
typedef struct esp_zb_zcl_cvc_alarm_variables_s {
    uint8_t endpoint_id;                /*!< Endpoint id */
    uint16_t cluster_id;                /*!< Cluster id */
    uint16_t attribute_id;              /*!< Attribute id */
    uint8_t alarm_buf_id;               /*!< Alarm buffer id */
    bool is_used;                       /*!< Is Used flag */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_cvc_alarm_variables_t;

/**
* @brief Struture of Node descriptor request of ZDO response
*/
typedef struct esp_zb_af_node_desc_s {
    uint16_t          node_desc_flags;            /*!< node description */
    uint8_t           mac_capability_flags;       /*!< mac capability */
    uint16_t          manufacturer_code;          /*!< Manufacturer code */
    uint8_t           max_buf_size;               /*!< Maximum buffer size */
    uint16_t          max_incoming_transfer_size; /*!< Maximum incoming transfer size */
    uint16_t          server_mask;                /*!< Server mask */
    uint16_t          max_outgoing_transfer_size; /*!< Maximum outgoing transfer size */
    uint8_t           desc_capability_field;      /*!< Descriptor capability field */
} ESP_ZB_PACKED_STRUCT
esp_zb_af_node_desc_t;

/**
* @brief Struture of network descriptor request of active scan response
*/
typedef struct esp_zb_network_descriptor_s{
    uint16_t short_pan_id;                      /*!< PAN id */
    bool     permit_joining;                    /*!< Indicates that at least one router / coordinator on the network currently permits joining */
    esp_zb_ieee_addr_t extended_pan_id;         /*!< Extended PAN id, the MAC address which forms the network */
}ESP_ZB_PACKED_STRUCT
esp_zb_network_descriptor_t;

/**
 * @brief Structure of simple descriptor request of ZCL command
 */
typedef struct esp_zb_af_simple_desc_1_1_s {
    uint8_t    endpoint;                        /*!< Endpoint */
    uint16_t   app_profile_id;                  /*!< Application profile identifier */
    uint16_t   app_device_id;                   /*!< Application device identifier */
    uint32_t    app_device_version: 4;          /*!< Application device version */
    uint32_t    reserved: 4;                    /*!< Reserved */
    uint8_t    app_input_cluster_count;         /*!< Application input cluster count */
    uint8_t    app_output_cluster_count;        /*!< Application output cluster count */
    uint16_t   app_cluster_list[2];             /*!< Application input and output cluster list */
} ESP_ZB_PACKED_STRUCT
esp_zb_af_simple_desc_1_1_t;

/**
 * @brief Type to represent ZCL endpoint definition structure
 * @note  The esp_zb_zcl_reporting_info_t defines see @ref esp_zb_zcl_reporting_info_s
* @note  The esp_zb_af_simple_desc_1_1_t defines see @ref esp_zb_af_simple_desc_1_1_s
 */
typedef struct esp_zb_endpoint_s {
    uint8_t ep_id;                              /*!< Endpoint ID */
    uint16_t profile_id;                        /*!< Application profile, which implemented on endpoint */
    esp_zb_callback_t device_handler;           /*!< endpoint specific callback, handles all commands for this endpoint. If set, it will be called to handle callback,like esp_zb_add_read_attr_resp_cb */
    esp_zb_callback_t identify_handler;         /*!< Identify notification callback. If set, it will be called on identification start and stop indicating start event with a non-zero argument*/
    uint8_t reserved_size;                      /*!< Unused parameter (reserved for future use) */
    void *reserved_ptr;                         /*!< Unused parameter (reserved for future use) */
    uint8_t cluster_count;                      /*!< Number of supported clusters */
    esp_zb_zcl_cluster_t *cluster_desc_list;    /*!< Supported clusters list */
    esp_zb_af_simple_desc_1_1_t *simple_desc;   /*!< Simple descriptor */
#if defined ZB_ENABLE_ZLL
    uint8_t group_id_count;                     /*!< Number of group id */
#endif /* defined ZB_ENABLE_ZLL */
    uint8_t rep_info_count;                     /*!< Number of reporting info slots */
    esp_zb_zcl_reporting_info_t *reporting_info; /*!< Attributes reporting information */
    uint8_t cvc_alarm_count;          /*!< Number of continuous value change alarm slots */
    esp_zb_zcl_cvc_alarm_variables_t *cvc_alarm_info;   /*!< pointer to the cvc alarm structure */
} ESP_ZB_PACKED_STRUCT
esp_zb_endpoint_t;

/******************* attribute list *******************/
/**
 * @brief The esp-zigbee data model of list of attribute.
 *
 * @note An attribute list groups up a single cluster.
 */
typedef struct esp_zb_attribute_list_s {
    esp_zb_zcl_attr_t   attribute;              /*!< A single attribute */
    uint16_t     cluster_id;                    /*!< A cluster id assigned to this attribute */
    struct esp_zb_attribute_list_s *next;       /*!< A pointer to next attribute */
} esp_zb_attribute_list_t;

/******************* cluster list *******************/
/**
 * @brief The esp-zigbee data model of list of cluster.
 *
 */
typedef struct esp_zb_cluster_list_s {
    esp_zb_zcl_cluster_t cluster;               /*!< A single cluster */
    struct esp_zb_cluster_list_s *next;         /*!< A pointer to next cluster */
} esp_zb_cluster_list_t;

/******************* endpoint list *******************/
/**
 * @brief The esp-zigbee data model of list of endpoint.
 *
 */
typedef struct esp_zb_ep_list_s {
    esp_zb_endpoint_t endpoint;                 /*!< A single endpoint */
    struct esp_zb_ep_list_s *next;              /*!< A pointer to next endpoint */
} esp_zb_ep_list_t;

/****************** standard clusters *********************/
/**
 * @brief Zigbee standard mandatory attribute for basic cluster.
 *
 */
typedef struct esp_zb_basic_cluster_cfg_s {
    uint8_t  zcl_version;                       /*!<  ZCL version */
    uint8_t  power_source;                      /*!<  The sources of power available to the device */
} esp_zb_basic_cluster_cfg_t;

/**
 * @brief Zigbee default attribute for power configuration cluster.
 *
 */
typedef struct esp_zb_power_config_cluster_cfg_s {
    uint16_t    main_voltage;                       /*!<  MainVoltage RMS voltage or DC voltage in units of 100mV */
    uint8_t     main_freq;                          /*!<  MainFrequency in value of 0.5 * measured frequency, DC supply is 0Hz */
    uint8_t     main_alarm_mask;                    /*!<  Main alram mask in bit */
    uint16_t    main_voltage_min;                   /*!<  Main voltage min threshold in unit of 100mV */
    uint16_t    main_voltage_max;                   /*!<  Main voltage max threshold in unit of 100mV */
    uint16_t    main_voltage_dwell;                 /*!<  Main voltage exist in seconds */
} esp_zb_power_config_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for identify cluster.
 *
 */
typedef struct esp_zb_identify_cluster_cfg_s {
    uint16_t  identify_time;                    /*!<  The remaining length of the time that identify itself */
} esp_zb_identify_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for groups cluster.
 *
 */
typedef struct esp_zb_groups_cluster_cfg_s {
    uint8_t  groups_name_support_id;            /*!<  The indication of group names are supported or not */
} esp_zb_groups_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for scenes cluster.
 *
 */
typedef struct esp_zb_scenes_cluster_cfg_s {
    uint8_t  scenes_count;                      /*!<  The number of scenes currently in the scene table */
    uint8_t  current_scene;                     /*!<  Scene ID that invoked */
    uint16_t current_group;                     /*!<  Group ID that invoked */
    bool  scene_valid;                          /*!<  Indication of the associated with current scene and group valid or not*/
    uint8_t  name_support;                      /*!<  The indication of group names are supported or not */
} esp_zb_scenes_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for on_off cluster.
 *
 */
typedef struct esp_zb_on_off_cluster_cfg_s {
    bool  on_off;                               /*!<  On Off state of the device */
} esp_zb_on_off_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for on_off switch configuration cluster.
 *
 */
typedef struct esp_zb_on_off_switch_cluster_cfg_s {
    uint8_t  switch_type;                               /*!<  On Off switch type */
    uint8_t  switch_action;                             /*!< On off switch action */
} esp_zb_on_off_switch_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for level cluster.
 *
 */
typedef struct esp_zb_level_cluster_cfg_s {
    uint8_t  current_level;                     /*!<  Current level of the device */
} esp_zb_level_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for color cluster.
 *
 */
typedef struct esp_zb_color_cluster_cfg_s {
    uint16_t current_x;                         /*!<  The current value of the normalized chromaticity value x */
    uint16_t current_y;                         /*!<  The current value of the normalized chromaticity value y */
    uint8_t  color_mode;                        /*!<  The mode which attribute determines the color of the device */
    uint8_t  options;                           /*!<  The bitmap determines behavior of some cluster commands */
    uint8_t  enhanced_color_mode;               /*!<  The enhanced-mode which attribute determines the color of the device */
    uint16_t color_capabilities;                /*!<  Specifying the color capabilities of the device support the color control cluster */
} esp_zb_color_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for time cluster.
 *
 */
typedef struct esp_zb_time_cluster_cfg_s {
    uint16_t time;                              /*!<  The time value of the a real time clock */
    uint16_t time_status;                       /*!<  The time status holds a number of bit field of status */
} esp_zb_time_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for shade config cluster.
 *
 */
typedef struct esp_zb_shade_config_cluster_cfg_s {
    uint8_t     status;                             /*!<  The status attribute indicates the status of a number of shade function */
    uint16_t    closed_limit;                       /*!<  The attribute indicates most closed position that shade can move to */
    uint8_t     mode;                               /*!<  The attribute indicates the current operating mode */
} esp_zb_shade_config_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for binary input (basic) cluster.
 *
 */
typedef struct esp_zb_binary_input_cluster_cfg_s {
    bool  out_of_service;                              /*!< Out of Service */
    uint8_t  status_flags;                             /*!< Status flags */
} esp_zb_binary_input_cluster_cfg_t;

/**
 * @brief The IAS zone application callback
 * 
 */
typedef void (* esp_zb_ias_zone_app_callback_t)(uint8_t param, uint16_t general_val);

/**
 * @brief Zigbee IAS zone application initialization context
 *
 */
typedef struct esp_zb_zcl_ias_zone_int_ctx_s {
  esp_zb_callback_t process_result_cb;              /*!< The callback will be active, when the IAS zone status change notification */
  esp_zb_ias_zone_app_callback_t general_cb;        /*!< The callback is for the IAS zone attribute */
  uint8_t restore_current_zone_sens_level;          /*!< The sensitivity of current IAS zone */
  uint8_t new_current_zone_sens_level;              /*!< The new sensitivity of IAS zone */
} esp_zb_zcl_ias_zone_int_ctx_t;

/**
 * @brief Zigbee standard mandatory attribute for ias zone cluster.
 *
 */
typedef struct esp_zb_ias_zone_cluster_cfg_s {
    uint8_t  zone_state;                             /*!< zone state */
    uint16_t zone_type;                              /*!< zone type */
    uint16_t zone_status;                            /*!< zone status */
    esp_zb_ieee_addr_t ias_cie_addr;                 /*!< IAS CIE Address that commands generated by server SHALL be sent to */
    uint8_t   zone_id;                               /*!< zone id */
    esp_zb_zcl_ias_zone_int_ctx_t zone_ctx;          /*!< zone context*/
} esp_zb_ias_zone_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for door lock cluster.
 *
 */
typedef struct esp_zb_door_lock_cluster_cfg_s {
    uint8_t lock_state;                         /*!<  The attribute indicates the state of lock */
    uint8_t lock_type;                          /*!<  The attribute indicates different type of the lock type */
    bool    actuator_enabled;                   /*!<  The attribute indicates if the lock is currently able (Enabled) or not able (Disabled) to process remote lock */
} esp_zb_door_lock_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for temperature measurement cluster.
 *
 */
typedef struct esp_zb_temperature_meas_cluster_cfg_s {
    int16_t measured_value;                     /*!<  The attribute indicates the temperature in degrees Celsius */
    int16_t min_value;                          /*!<  The attribute indicates minimum value of the measured value */
    int16_t max_value;                          /*!<  The attribute indicates maximum value of the measured value */
} esp_zb_temperature_meas_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for humidity measurement cluster.
 *
 */
typedef struct esp_zb_humidity_meas_cluster_cfg_s {
    uint16_t measured_value;                     /*!<  The attribute indicates the humidity in 100*percent */
    uint16_t min_value;                          /*!<  The attribute indicates minimum value of the measured value */
    uint16_t max_value;                          /*!<  The attribute indicates maximum value of the measured value */
} esp_zb_humidity_meas_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for OTA client cluster.
 *
 */
typedef struct esp_zb_ota_cluster_cfg_s {
    uint32_t ota_upgrade_file_version;            /*!<  The attribute indicates the file version of the running firmware image on the device */
    uint16_t ota_upgrade_manufacturer;            /*!<  The attribute indicates the value for the manufacturer of the device */
    uint16_t ota_upgrade_image_type;              /*!<  The attribute indicates the the image type of the file that the client is currently downloading */
    uint16_t ota_min_block_reque;                 /*!<  The attribute indicates the delay between Image Block Request commands in milliseconds */
    uint32_t ota_upgrade_file_offset;             /*!<  The attribute indicates the the current location in the OTA upgrade image. */
    uint32_t ota_upgrade_downloaded_file_ver;     /*!<  The attribute indicates the file version of the downloaded image on the device*/
    esp_zb_ieee_addr_t ota_upgrade_server_id;     /*!<  The attribute indicates the address of the upgrade server */
    uint8_t ota_image_upgrade_status;             /*!<  The attribute indicates the image upgrade status of the client device */
} esp_zb_ota_cluster_cfg_t;

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
 * @brief Zigbee standard mandatory attribute for pressure measurement cluster
 *
 */
typedef struct esp_zb_pressure_meas_cluster_cfg_s {
    int16_t measured_value;                     /*!<  The attribute indicates the pressure from 0x8000 to 0x7fff */
    int16_t min_value;                          /*!<  The attribute indicates minimum value of the measured value */
    int16_t max_value;                          /*!<  The attribute indicates maximum value of the measured value */
} esp_zb_pressure_meas_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for electrical measurement cluster
 *
 */
typedef struct esp_zb_electrical_meas_cluster_cfg_s {
    uint32_t measured_type;                     /*!<  This attribute indicates a device’s measurement type */
} esp_zb_electrical_meas_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for occupancy sensing cluster
 *
 */
typedef struct esp_zb_occupancy_sensing_cluster_cfg_s {
    uint8_t occupancy;                          /*!<  Bit 0 specifies the sensed occupancy as follows: 1 = occupied, 0 = unoccupied. */
    uint32_t sensor_type;                       /*!<  The attribute specifies the type of the occupancy sensor */
    uint8_t sensor_type_bitmap;                 /*!<  The attribute specifies the types of the occupancy sensor */
} esp_zb_occupancy_sensing_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for window covering cluster
 *
 */
typedef struct esp_zb_window_covering_cluster_cfg_s {
    uint8_t covering_type;                      /*!<  This attribute identifies the type of window covering being controlled by this endpoint */
    uint8_t covering_status;                    /*!<  This attribute makes configuration and status information available */
    uint8_t covering_mode;                      /*!<  This attribute allows configuration of the window covering */
} esp_zb_window_covering_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for thermostat cluster
 *
 */
typedef struct esp_zb_thermostat_cluster_cfg_s {
    int16_t local_temperature;             /*!< This attribute represents the temperature in degrees Celsius */
    int16_t occupied_cooling_setpoint;     /*!< This attribute specifies the cooling mode setpoint when the room is occupied */
    int16_t occupied_heating_setpoint;     /*!< This attribute specifies the heating mode setpoint when the room is occupied */
    uint8_t control_sequence_of_operation; /*!< This attribute specifies the overall operating environment and possible system modes */
    uint8_t system_mode;                   /*!< This attribute specifies the current operating mode */
} esp_zb_thermostat_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for fan control cluster
 *
 */
typedef struct esp_zb_fan_control_cluster_cfg_s {
    uint8_t fan_mode;          /*!< This attribute specifies the current speed of the fan */
    uint8_t fan_mode_sequence; /*!< This attribute specifies the possible fan speeds that the thermostat can set */
} esp_zb_fan_control_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for thermostat ui configuration cluster
 *
 */
typedef struct esp_zb_thermostat_ui_config_cluster_cfg_s {
    uint8_t temperature_display_mode; /*!< This attribute specifies the units of the temperature displayed on the thermostat sceen */
    uint8_t keypad_lockout;           /*!< This attribute specifies the level of functionality that is available to the user via the keypad */
} esp_zb_thermostat_ui_config_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for analog input cluster
 *
 */
typedef struct esp_zb_analog_input_cluster_cfg_s {
    bool out_of_service;   /*!< This attribute indicates whether or not the physical input that the cluster represents is in service */
    float_t present_value; /*!< This attribute indicates the current value of the input as appropriate for the cluster */
    uint8_t status_flags;  /*!< This attribute indicates the general “health” of the analog sensor */
} esp_zb_analog_input_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for analog output cluster
 *
 */
typedef struct esp_zb_analog_output_cluster_cfg_s {
    bool out_of_service;   /*!< This attribute indicates whether or not the physical output that the cluster represents is in service */
    float_t present_value; /*!< This attribute indicates the current value of the output as appropriate for the cluster */
    uint8_t status_flags;  /*!< This attribute indicates the general “health” of the analog sensor */
} esp_zb_analog_output_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for analog value cluster
 *
 */
typedef struct esp_zb_analog_value_cluster_cfg_s {
    bool out_of_service;   /*!< This attribute indicates whether or not the physical value that the cluster represents is in service */
    float_t present_value; /*!< This attribute indicates the current value as appropriate for the cluster */
    uint8_t status_flags;  /*!< This attribute indicates the general “health” of the analog sensor */
} esp_zb_analog_value_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for carbon dioxide measurement cluster
 *
 */
typedef struct esp_zb_carbon_dioxide_measurement_cluster_cfg_s {
    float_t measured_value;     /*!<  This attribute represents the carbon dioxide concentration as a fraction of one */
    float_t min_measured_value; /*!<  This attribute indicates the minimum value of measuredvalue that is capable of being measured */
    float_t max_measured_value; /*!<  This attribute indicates the maximum value of measuredvalue that is capable of being measured */
} esp_zb_carbon_dioxide_measurement_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for pm 2.5 measurement cluster
 *
 */
typedef struct esp_zb_pm2_5_measurement_cluster_cfg_s {
    float_t measured_value;     /*!<  This attribute represents the pm2.5 concentration as a fraction of one */
    float_t min_measured_value; /*!<  This attribute indicates the minimum value of measuredvalue that is capable of being measured */
    float_t max_measured_value; /*!<  This attribute indicates the maximum value of measuredvalue that is capable of being measured */
} esp_zb_pm2_5_measurement_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for multistate value cluster
 *
 */
typedef struct esp_zb_multistate_value_cluster_cfg_s {
    uint16_t number_of_states; /*!< This attribute defines the number of states that a multistate PresentValue MAY have */
    bool out_of_service;       /*!< This attribute indicates whether or not the physical value that the cluster represents is in service */
    uint16_t present_value;    /*!< This attribute indicates the current value as appropriate for the cluster */
    uint8_t status_flags;      /*!< This attribute indicates the general “health” of the analog sensor */
} esp_zb_multistate_value_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for metering cluster
 *
 */
typedef struct esp_zb_metering_cluster_cfg_s {
    esp_zb_uint48_t current_summation_delivered; /*!< This attribute represents the most recent summed value of Energy, Gas, or Water delivered and consumed in the premises */
    uint8_t status;                              /*!< This attribute provides indicators reflecting the current error conditions found by the metering device */
    uint8_t uint_of_measure;                     /*!< This attribute provides a label for the Energy, Gas, or Water being measured by the metering device.
                                                      refer to esp_zb_zcl_metering_unit_of_measure_t */
    uint8_t summation_formatting;                /*!< This attribute provides a method to properly decipher the number of digits and the decimal location of the values found in the Summation Information Set */
    uint8_t metering_device_type;                /*!< This attribute provides a label for identifying the type of metering device (Energy, Gas, Water, Thermal, Heat, Cooling, and mirrored metering devices).
                                                      refer to esp_zb_zcl_metering_device_type_t */
} esp_zb_metering_cluster_cfg_t;

/****************** standard device config *********************/
/**
 * @brief Zigbee HA standard on-off light device clusters.
 *
 */
typedef struct esp_zb_on_off_light_cfg_s {
    esp_zb_basic_cluster_cfg_t basic_cfg;       /*!<  Basic cluster configuration, @ref esp_zb_basic_cluster_cfg_s */
    esp_zb_identify_cluster_cfg_t identify_cfg; /*!<  Identify cluster configuration, @ref esp_zb_identify_cluster_cfg_s */
    esp_zb_groups_cluster_cfg_t groups_cfg;     /*!<  Groups cluster configuration, @ref esp_zb_groups_cluster_cfg_s */
    esp_zb_scenes_cluster_cfg_t scenes_cfg;     /*!<  Scenes cluster configuration, @ref esp_zb_scenes_cluster_cfg_s */
    esp_zb_on_off_cluster_cfg_t on_off_cfg;     /*!<  On off cluster configuration, @ref esp_zb_on_off_cluster_cfg_s */
} esp_zb_on_off_light_cfg_t;

/**
 * @brief Zigbee HA standard on-off switch device clusters.
 *
 */
typedef struct esp_zb_on_off_switch_cfg_s {
    esp_zb_basic_cluster_cfg_t basic_cfg;       /*!<  Basic cluster configuration, @ref esp_zb_basic_cluster_cfg_s */
    esp_zb_identify_cluster_cfg_t identify_cfg; /*!<  Identify cluster configuration, @ref esp_zb_identify_cluster_cfg_s */
} esp_zb_on_off_switch_cfg_t;

/**
 * @brief Zigbee HA standard color dimmable light device clusters.
 *
 */
typedef struct esp_zb_color_dimmable_light_cfg_s {
    esp_zb_basic_cluster_cfg_t basic_cfg;       /*!<  Basic cluster configuration, @ref esp_zb_basic_cluster_cfg_s */
    esp_zb_identify_cluster_cfg_t identify_cfg; /*!<  Identify cluster configuration, @ref esp_zb_identify_cluster_cfg_s */
    esp_zb_groups_cluster_cfg_t groups_cfg;     /*!<  Groups cluster configuration, @ref esp_zb_groups_cluster_cfg_s */
    esp_zb_scenes_cluster_cfg_t scenes_cfg;     /*!<  Scenes cluster configuration, @ref esp_zb_scenes_cluster_cfg_s */
    esp_zb_on_off_cluster_cfg_t on_off_cfg;     /*!<  On off cluster configuration, @ref esp_zb_on_off_cluster_cfg_s */
    esp_zb_level_cluster_cfg_t level_cfg;       /*!<  Level cluster configuration, @ref esp_zb_level_cluster_cfg_s */
    esp_zb_color_cluster_cfg_t color_cfg;       /*!<  Color cluster configuration, @ref esp_zb_color_cluster_cfg_s */
} esp_zb_color_dimmable_light_cfg_t;

/**
 * @brief Zigbee HA standard color dimmable switch device clusters.
 *
 */
typedef struct esp_zb_color_dimmable_switch_cfg_s {
    esp_zb_basic_cluster_cfg_t basic_cfg;       /*!<  Basic cluster configuration, @ref esp_zb_basic_cluster_cfg_s */
    esp_zb_identify_cluster_cfg_t identify_cfg; /*!<  Identify cluster configuration, @ref esp_zb_identify_cluster_cfg_s */
} esp_zb_color_dimmable_switch_cfg_t;

/**
 * @brief Zigbee HA standard mains power outlet clusters.
 *
 */
typedef struct esp_zb_mains_power_outlet_cfg_s {
    esp_zb_basic_cluster_cfg_t basic_cfg;       /*!<  Basic cluster configuration, @ref esp_zb_basic_cluster_cfg_s */
    esp_zb_identify_cluster_cfg_t identify_cfg; /*!<  Identify cluster configuration, @ref esp_zb_identify_cluster_cfg_s */
    esp_zb_groups_cluster_cfg_t groups_cfg;     /*!<  Groups cluster configuration, @ref esp_zb_groups_cluster_cfg_s */
    esp_zb_scenes_cluster_cfg_t scenes_cfg;     /*!<  Scenes cluster configuration, @ref esp_zb_scenes_cluster_cfg_s */
    esp_zb_on_off_cluster_cfg_t on_off_cfg;     /*!<  On off cluster configuration, @ref esp_zb_on_off_cluster_cfg_s */
} esp_zb_mains_power_outlet_cfg_t;

/**
 * @brief Zigbee HA standard shade clusters.
 *
 */
typedef struct esp_zb_shade_cfg_s {
    esp_zb_basic_cluster_cfg_t basic_cfg;        /*!<  Basic cluster configuration, @ref esp_zb_basic_cluster_cfg_s */
    esp_zb_identify_cluster_cfg_t identify_cfg;  /*!<  Identify cluster configuration, @ref esp_zb_identify_cluster_cfg_s */
    esp_zb_groups_cluster_cfg_t groups_cfg;      /*!<  Groups cluster configuration, @ref esp_zb_groups_cluster_cfg_s */
    esp_zb_scenes_cluster_cfg_t scenes_cfg;      /*!<  Scenes cluster configuration, @ref esp_zb_scenes_cluster_cfg_s */
    esp_zb_on_off_cluster_cfg_t on_off_cfg;      /*!<  On off cluster configuration, @ref esp_zb_on_off_cluster_cfg_s */
    esp_zb_level_cluster_cfg_t level_cfg;        /*!<  Level cluster configuration, @ref esp_zb_level_cluster_cfg_s */
    esp_zb_shade_config_cluster_cfg_t shade_cfg; /*!<  Shade config cluster configuration, @ref esp_zb_shade_config_cluster_cfg_s */
} esp_zb_shade_cfg_t;

/**
 * @brief Zigbee HA standard shade controller device clusters.
 *
 */
typedef struct esp_zb_shade_controller_cfg_s {
    esp_zb_basic_cluster_cfg_t basic_cfg;       /*!<  Basic cluster configuration, @ref esp_zb_basic_cluster_cfg_s */
    esp_zb_identify_cluster_cfg_t identify_cfg; /*!<  Identify cluster configuration, @ref esp_zb_identify_cluster_cfg_s */
} esp_zb_shade_controller_cfg_t;

/**
 * @brief Zigbee HA standard door lock clusters.
 *
 */
typedef struct esp_zb_door_lock_cfg_s {
    esp_zb_basic_cluster_cfg_t basic_cfg;         /*!<  Basic cluster configuration, @ref esp_zb_basic_cluster_cfg_s */
    esp_zb_identify_cluster_cfg_t identify_cfg;   /*!<  Identify cluster configuration, @ref esp_zb_identify_cluster_cfg_s */
    esp_zb_groups_cluster_cfg_t groups_cfg;       /*!<  Groups cluster configuration, @ref esp_zb_groups_cluster_cfg_s */
    esp_zb_scenes_cluster_cfg_t scenes_cfg;       /*!<  Scenes cluster configuration, @ref esp_zb_scenes_cluster_cfg_s */
    esp_zb_door_lock_cluster_cfg_t door_lock_cfg; /*!<  Door Lock cluster configuration, @ref esp_zb_door_lock_cluster_cfg_s */
} esp_zb_door_lock_cfg_t;

/**
 * @brief Zigbee HA standard door lock controller clusters.
 *
 */
typedef struct esp_zb_door_lock_controller_cfg_s {
    esp_zb_basic_cluster_cfg_t basic_cfg;       /*!<  Basic cluster configuration, @ref esp_zb_basic_cluster_cfg_s */
    esp_zb_identify_cluster_cfg_t identify_cfg; /*!<  Identify cluster configuration, @ref esp_zb_identify_cluster_cfg_s */
} esp_zb_door_lock_controller_cfg_t;

/**
 * @brief Zigbee HA standard temperature sensor clusters.
 *
 */
typedef struct esp_zb_temperature_sensor_cfg_s {
    esp_zb_basic_cluster_cfg_t basic_cfg;                /*!<  Basic cluster configuration, @ref esp_zb_basic_cluster_cfg_s */
    esp_zb_identify_cluster_cfg_t identify_cfg;          /*!<  Identify cluster configuration, @ref esp_zb_identify_cluster_cfg_s */
    esp_zb_temperature_meas_cluster_cfg_t temp_meas_cfg; /*!<  Temperature measurement cluster configuration, @ref esp_zb_temperature_meas_cluster_cfg_s */
} esp_zb_temperature_sensor_cfg_t;

/**
 * @brief Zigbee HA standard configuration tool clusters.
 *
 */
typedef struct esp_zb_configuration_tool_cfg_s {
    esp_zb_basic_cluster_cfg_t basic_cfg;       /*!<  Basic cluster configuration, @ref esp_zb_basic_cluster_cfg_s */
    esp_zb_identify_cluster_cfg_t identify_cfg; /*!<  Identify cluster configuration, @ref esp_zb_identify_cluster_cfg_s */
} esp_zb_configuration_tool_cfg_t;

/**
 * @brief Zigbee HA standard thermostat clusters.
 *
 */
typedef struct esp_zb_thermostat_cfg_s {
    esp_zb_basic_cluster_cfg_t basic_cfg;           /*!<  Basic cluster configuration, @ref esp_zb_basic_cluster_cfg_s */
    esp_zb_identify_cluster_cfg_t identify_cfg;     /*!<  Identify cluster configuration, @ref esp_zb_identify_cluster_cfg_s */
    esp_zb_thermostat_cluster_cfg_t thermostat_cfg; /*!<  Thermostat cluster configuration, @ref esp_zb_thermostat_cluster_cfg_s */
} esp_zb_thermostat_cfg_t;

#ifdef __cplusplus
}
#endif
