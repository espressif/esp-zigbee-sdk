/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#include "esp_zigbee_type.h"
#include "esp_zigbee_zcl_common.h"

/** Enum of the Zigbee ZCL address mode
 * @note Defined the ZCL command of address_mode.
 * @anchor esp_zb_zcl_address_mode_t
 */
typedef enum {
    ESP_ZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT =        0x0,            /*!< DstAddress and DstEndpoint not present */
    ESP_ZB_APS_ADDR_MODE_16_GROUP_ENDP_NOT_PRESENT  =       0x1,            /*!< 16-bit group address for DstAddress; DstEndpoint not present */
    ESP_ZB_APS_ADDR_MODE_16_ENDP_PRESENT =                  0x2,            /*!< 16-bit address for DstAddress and DstEndpoint present */
    ESP_ZB_APS_ADDR_MODE_64_ENDP_PRESENT =                  0x3,            /*!< 64-bit extended address for DstAddress and DstEndpoint present */
} esp_zb_zcl_address_mode_t;

/**
 * @brief The Zigbee ZCL basic command info
 *
 */
typedef struct esp_zb_zcl_basic_cmd_s {
    esp_zb_addr_u dst_addr_u;                   /*!< Single short address or group address */
    uint8_t  dst_endpoint;                      /*!< Destination endpoint */
    uint8_t  src_endpoint;                      /*!< Source endpoint */
} esp_zb_zcl_basic_cmd_t;

/**
 * @brief The Zigbee ZCL read attribute command struct
 *
 */
typedef struct esp_zb_zcl_read_attr_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;           /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;         /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t clusterID;                             /*!< Cluster ID to read */
    uint16_t attributeID;                           /*!< Attribute ID to read*/
} esp_zb_zcl_read_attr_cmd_t;

/**
 * @brief The Zigbee ZCL write attribute command struct
 *
 */
typedef struct esp_zb_zcl_write_attr_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;           /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;         /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t clusterID;                             /*!< Cluster ID to write */
    uint16_t attributeID;                           /*!< Attribute ID to write */
    uint8_t  attrType;                              /*!< Attribute type to write refer to zb_zcl_common.h zcl_attr_type */
    uint8_t  *attrVal;                              /*!< Attribute value to write */
} esp_zb_zcl_write_attr_cmd_t;

/**
 * @brief The Zigbee ZCL configure report command struct
 *
 */
typedef struct esp_zb_zcl_config_report_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;           /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;         /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t clusterID;                             /*!< Cluster ID to report */
    uint16_t attributeID;                           /*!< Attribute ID to report */
    uint8_t  attrType;                              /*!< Attribute type to report refer to zb_zcl_common.h zcl_attr_type */
    uint16_t  min_interval;                         /*!< Minimum reporting interval */
    uint16_t  max_interval;                         /*!< Maximum reporting interval */
    void* reportable_change;                     /*!< Minimum change to attribute will result in report */
} esp_zb_zcl_config_report_cmd_t;

/**
 * @brief The Zigbee ZCL report attribute command struct
 *
 */
typedef struct esp_zb_zcl_report_attr_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;           /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;         /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t clusterID;                             /*!< Cluster ID to report */
    uint8_t cluster_role;                           /*!< Cluster role */
    uint16_t attributeID;                           /*!< Attribute ID to report */
} esp_zb_zcl_report_attr_cmd_t;

/* ZCL basic cluster */

/**
 * @brief The Zigbee ZCL basic reset factory default command struct
 *
 */
typedef struct esp_zb_zcl_basic_fact_reset_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;           /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;         /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
} esp_zb_zcl_basic_fact_reset_cmd_t;

/* ZCL on/off cluster */

/**
 * @brief The Zigbee ZCL on-off command struct
 *
 */
typedef struct esp_zb_zcl_on_off_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;           /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;         /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t  on_off_cmd_id;                         /*!< command id for the on-off cluster command */
} esp_zb_zcl_on_off_cmd_t;

/* ZCL identify cluster */

/**
 * @brief The Zigbee ZCL identify command struct
 *
 */
typedef struct esp_zb_zcl_identify_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;           /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;         /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t identify_time;                         /*!< identify itself for specific time */
} esp_zb_zcl_identify_cmd_t;

/**
 * @brief The Zigbee ZCL identify query command struct
 *
 */
typedef struct esp_zb_zcl_identify_query_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;           /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;         /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
} esp_zb_zcl_identify_query_cmd_t;

/* ZCL level cluster */

/**
 * @brief The Zigbee ZCL level move to level command struct
 *
 */
typedef struct esp_zb_zcl_move_to_level_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t level;                                      /*!< level wants to move to */
    uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
} esp_zb_zcl_move_to_level_cmd_t;

/**
 * @brief The Zigbee ZCL level move command struct
 *
 */
typedef struct esp_zb_zcl_level_move_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t move_mode;                                  /*!< move mode either up or down */
    uint8_t rate;                                       /*!< move rate wants to movement in units per second */
} esp_zb_zcl_level_move_cmd_t;

/**
 * @brief The Zigbee ZCL level step command struct
 *
 */
typedef struct esp_zb_zcl_level_step_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t step_mode;                                  /*!< step mode either up or down */
    uint8_t step_size;                                  /*!< step size wants to change*/
    uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
} esp_zb_zcl_level_step_cmd_t;

/**
 * @brief The Zigbee ZCL level stop command struct
 *
 */
typedef struct esp_zb_zcl_level_stop_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
} esp_zb_zcl_level_stop_cmd_t;

/* ZCL color cluster */

/**
 * @brief The Zigbee ZCL color move to hue command struct
 *
 */
typedef struct esp_zb_zcl_color_move_to_hue_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t hue;                                        /*!< current value of hue */
    uint8_t direction;                                  /*!< direction */
    uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
} esp_zb_zcl_color_move_to_hue_cmd_t;

/**
 * @brief The Zigbee ZCL color move hue command struct
 *
 */
typedef struct esp_zb_zcl_color_move_hue_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t move_mode;                                  /*!< move mode */
    uint8_t rate;                                       /*!< rate */
} esp_zb_zcl_color_move_hue_cmd_t;

/**
 * @brief The Zigbee ZCL color step hue command struct
 *
 */
typedef struct esp_zb_zcl_color_step_hue_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t step_mode;                                  /*!< step mode */
    uint8_t step_size;                                  /*!< step size */
    uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
} esp_zb_zcl_color_step_hue_cmd_t;

/**
 * @brief The Zigbee ZCL color move to saturation command struct
 *
 */
typedef struct esp_zb_zcl_color_move_to_saturation_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t saturation;                                 /*!< current value of saturation */
    uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
} esp_zb_zcl_color_move_to_saturation_cmd_t;

/**
 * @brief The Zigbee ZCL color move saturation command struct
 *
 */
typedef struct esp_zb_zcl_color_move_saturation_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t move_mode;                                  /*!< move mode */
    uint8_t rate;                                       /*!< rate */
} esp_zb_zcl_color_move_saturation_cmd_t;

/**
 * @brief The Zigbee ZCL color step saturation command struct
 *
 */
typedef struct esp_zb_zcl_color_step_saturation_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t step_mode;                                  /*!< step mode */
    uint8_t step_size;                                  /*!< step size */
    uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
} esp_zb_zcl_color_step_saturation_cmd_t;

/**
 * @brief The Zigbee ZCL color move to hue and saturation command struct
 *
 */
typedef struct esp_zb_color_move_to_hue_saturation_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t hue;                                        /*!< current value of hue */
    uint8_t saturation;                                 /*!< current value of saturation */
    uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
} esp_zb_color_move_to_hue_saturation_cmd_t;

/**
 * @brief The Zigbee ZCL color move to color command struct
 *
 */
typedef struct esp_zb_zcl_color_move_to_color_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t color_x;                                   /*!< current value of chromaticity value x from (0 ~ 1) to (0 ~ 65535)*/
    uint16_t color_y;                                   /*!< current value of chromaticity value y from (0 ~ 1) to (0 ~ 65535)*/
    uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
} esp_zb_zcl_color_move_to_color_cmd_t;

/**
 * @brief The Zigbee ZCL color move color command struct
 *
 */
typedef struct esp_zb_zcl_color_move_color_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t rate_x;                                    /*!< specifies the rate of movement in steps per second of color x */
    uint16_t rate_y;                                    /*!< specifies the rate of movement in steps per second of color y */
} esp_zb_zcl_color_move_color_cmd_t;

/**
 * @brief The Zigbee ZCL color step color command struct
 *
 */
typedef struct esp_zb_zcl_color_step_color_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    int16_t step_x;                                     /*!< specifies the change to be added to color x */
    int16_t step_y;                                     /*!< specifies the change to be added to color x */
    uint16_t transition_time;                           /*!< time wants to transition tenths of a second */
} esp_zb_zcl_color_step_color_cmd_t;

/**
 * @brief The Zigbee ZCL color stop command struct
 *
 */
typedef struct esp_zb_zcl_color_stop_move_step_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                   /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                 /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
} esp_zb_zcl_color_stop_move_step_cmd_t;

/**
 * @brief The Zigbee ZCL color move to color temperature command struct
 *
 */
typedef struct esp_zb_zcl_color_move_to_color_temperature_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;   /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode; /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t color_temperature;             /*!< The field indicates the  color-temperature value */
    uint16_t transition_time;               /*!< The time wants to transition tenths of a second */
} esp_zb_zcl_color_move_to_color_temperature_cmd_t;

/**
 * @brief The Zigbee ZCL color enhanced move to hue command struct
 *
 */
typedef struct esp_zb_zcl_color_enhanced_move_to_hue_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;   /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode; /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t enhanced_hue;                  /*!< The field specifies the target enhanced hue for the lamp */
    uint8_t direction;                      /*!< The direction */
    uint16_t transition_time;               /*!< The time wants to transition tenths of a second */
} esp_zb_zcl_color_enhanced_move_to_hue_cmd_t;

/**
 * @brief The Zigbee ZCL color enhanced move hue
 *
 */
typedef struct esp_zb_zcl_color_enhanced_move_hue_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;   /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode; /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t move_mode;                      /*!< The Move Mode, If the Move Mode field is equal to 0x00 (Stop), the Rate field SHALL be ignored */
    uint16_t rate;                          /*!< The field specifies the rate of movement in steps per second */
} esp_zb_zcl_color_enhanced_move_hue_cmd_t;

/**
 * @brief The Zigbee ZCL color enhanced step hue command struct
 *
 */
typedef struct esp_zb_zcl_color_enhanced_step_hue_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;   /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode; /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t step_mode;                      /*!< The Step Mode */
    uint16_t step_size;                     /*!< The Step Size specifies the change to be added to the current value of the device’s enhanced hue.*/
    uint16_t transition_time;               /*!< The time wants to transition tenths of a second  */
} esp_zb_zcl_color_enhanced_step_hue_cmd_t;

/**
 * @brief The Zigbee ZCL color enhanced move to hue saturation command struct
 *
 */
typedef struct esp_zb_zcl_color_enhanced_move_to_hue_saturation_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;   /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode; /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t enhanced_hue;                  /*!< The Enhanced Hue specifies the target extended hue for the lamp */
    uint8_t saturation;                     /*!< The value of Saturation */
    uint16_t transition_time;               /*!< The time wants to transition tenths of a second */
} esp_zb_zcl_color_enhanced_move_to_hue_saturation_cmd_t;

/**
 * @brief The Zigbee ZCL color color loop set command struct
 *
 */
typedef struct esp_zb_zcl_color_color_loop_set_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;   /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode; /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t update_flags;                   /*!< The Update Flags field specifies which color loop attributes to update before the color loop is started */
    uint8_t action;                         /*!< The Action field specifies the action to take for the color loop,
                                                 if the Update Action sub-field of the Update Flags field is set to 1. */
    uint8_t direction;                      /*!< The Direction field of the color loop set command */
    uint16_t time;                          /*!< The Time field specifies the number of seconds over which to perform a full color loop,
                                                 if the Update Time field of the Update Flags field is set to 1. */
    uint16_t start_hue;                     /*!< The field specifies the starting hue to use for the color loop if the Update Start Hue field of the Update Flags field is set to 1 */
} esp_zb_zcl_color_color_loop_set_cmd_t;

/**
 * @brief The Zigbee ZCL color move color temperature command struct
 *
 */
typedef struct esp_zb_zcl_color_move_color_temperature_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;   /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode; /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t move_mode;                      /*!< The Move Mode field of the Move Hue command, if the Move Mode field is equal to 0x00, the Rate field SHALL be ignored. */
    uint16_t rate;                          /*!< The Rate filed specifies the rate of movement in steps per second */
    uint16_t color_temperature_minimum;     /*!< The field specifies a lower bound on the Color-Temperature attribute */
    uint16_t color_temperature_maximum;     /*!< The field specifies a upper bound on the Color-Temperature attribute */
} esp_zb_zcl_color_move_color_temperature_cmd_t;

/**
 * @brief The Zigbee ZCL color step color temperature command struct
 *
 */
typedef struct esp_zb_zcl_color_step_color_temperature_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;   /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode; /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t move_mode;                      /*!< The Move Mode field of the Step Hue command, If the Move Mode field is equal to 0x00, the Rate field SHALL be ignored. */
    uint16_t step_size;                     /*!< The Step Size field specifies the change to be added to (or subtracted from) the current
                                                 value of the device’s color temperature.*/
    uint16_t transition_time;               /*!< The time wants to transition tenths of a second  */
    uint16_t color_temperature_minimum;     /*!< The field specifies a lower bound on the Color-Temperature attribute*/
    uint16_t color_temperature_maximum;     /*!< The field specifies a upper bound on the Color-Temperature attribute*/
} esp_zb_zcl_color_step_color_temperature_cmd_t;

/**
 * @brief The Zigbee ZCL lock/unlock door command struct
 *
 */
typedef struct esp_zb_zcl_lock_unlock_door_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                   /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                 /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
} esp_zb_zcl_lock_unlock_door_cmd_t;

/**
 * @brief The Zigbee ZCL groups add group command struct
 *
 * @note Group name currently is not supported, put empty string, Support of group names is optional, @@see ZCL specification, subclause  3.6.2.2.2
 */
typedef struct esp_zb_zcl_groups_add_group_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                  /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                /*!< APS addressing mode constants @ref esp_zb_zcl_address_mode_t */
    uint16_t group_id;                                     /*!< Group id */
} esp_zb_zcl_groups_add_group_cmd_t;

/**
 * @brief The Zigbee ZCL groups remove all groups command struct
 *
 */
typedef struct esp_zb_zcl_groups_remove_all_groups_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                  /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                /*!< APS addressing mode constants @ref esp_zb_zcl_address_mode_t */
} esp_zb_zcl_groups_remove_all_groups_cmd_t;

/**
 * @brief The Zigbee ZCL groups get group membership command struct
 *
 * @note Get group membership will set enable ZCL response by default, later will support this feature
 *
 * @note Maximum group list size is 10.
 *
 */
typedef struct esp_zb_zcl_groups_get_group_membership_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                  /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                /*!< APS addressing mode constants @ref esp_zb_zcl_address_mode_t */
    uint8_t group_count;                                   /*!< Total group count */
    uint16_t group_list[10];                               /*!< Maximum group list */
} esp_zb_zcl_groups_get_group_membership_cmd_t;

/**
 * @brief The Zigbee ZCL scenes extension field struct
 *
 */
typedef struct esp_zb_zcl_scenes_extension_field_s {
    uint16_t cluster_id;                                   /*!< Cluster id */
    uint8_t length;                                        /*!< Length of scenes_extension_field */
    uint8_t *extension_field_attribute_value_list;         /*!< Extension field attribute value list */
    struct esp_zb_zcl_scenes_extension_field_s *next;      /*!< A pointer to next scenes extension field */
} esp_zb_zcl_scenes_extension_field_t;

/**
 * @brief The Zigbee ZCL scenes add scene command struct
 *
 * The maximum number of scenes capable of being stored in the table is 10.
 */
typedef struct esp_zb_zcl_scenes_add_scene_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                        /*!< Basic command info */
    uint16_t group_id;                                           /*!< Group id */
    uint8_t scene_id;                                            /*!< Scene id */
    uint16_t transition_time;                                    /*!< Time wants to transition tenths of a second */
    esp_zb_zcl_scenes_extension_field_t *extension_field;        /*!< The extension field list, please use 'NULL' as the end of list */
} esp_zb_zcl_scenes_add_scene_cmd_t;

/**
 * @brief The Zigbee ZCL scenes remove scene command struct
 *
 */
typedef struct esp_zb_zcl_scenes_remove_scene_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t group_id;                                  /*!< Group id */
    uint8_t scene_id;                                   /*!< Scene id */
} esp_zb_zcl_scenes_remove_scene_cmd_t;

/**
 * @brief The Zigbee ZCL scenes remove all scenes command struct
 *
 */
typedef struct esp_zb_zcl_scenes_remove_all_scenes_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t group_id;                                  /*!< Group id */
} esp_zb_zcl_scenes_remove_all_scenes_cmd_t;

/**
 * @brief The Zigbee ZCL scenes view scene command struct
 *
 */
typedef struct esp_zb_zcl_scenes_view_scene_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    uint16_t group_id;                                  /*!< Group id */
    uint8_t scene_id;                                   /*!< Scene id */
} esp_zb_zcl_scenes_view_scene_cmd_t;

/**
 * @brief The Zigbee ZCL scenes view scene response struct for users
 *
 */
typedef struct esp_zb_zcl_scenes_view_scene_resp_s {
    uint8_t status;                                  /*!< Command execution status refers to esp_zb_zcl_status_t */
    uint16_t group_id;                               /*!< Scene group identifier */
    uint8_t scene_id;                                /*!< Scene identifier */
    uint16_t transition_time;                        /*!< Scene transition time Valid if status is ESP_ZB_ZCL_STATUS_SUCCESS only */
    esp_zb_zcl_scenes_extension_field_t *field_data; /*!< Extension field, {{cluster_id, length, value}, ... , {cluster_id, length, value}} */
} esp_zb_zcl_scenes_view_scene_resp_t;

/**
 * @brief The Zigbee ZCL scenes store scene command struct
 *
 */
typedef struct esp_zb_zcl_scenes_store_scene_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                      /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                    /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t group_id;                                         /*!< Group id */
    uint8_t scene_id;                                          /*!< Scene id */
} esp_zb_zcl_scenes_store_scene_cmd_t;

/**
 * @brief The Zigbee ZCL scenes recall scene command struct
 *
 */
typedef struct esp_zb_zcl_scenes_recall_scene_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                 /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;               /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t group_id;                                    /*!< Group id */
    uint8_t scene_id;                                     /*!< Scene id */
} esp_zb_zcl_scenes_recall_scene_cmd_t;

/**
 * @brief The Zigbee ZCL scenes get scene membership command struct
 *
 */
typedef struct esp_zb_zcl_scenes_get_scene_membership_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;               /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;             /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t group_id;                                  /*!< Group id */
} esp_zb_zcl_scenes_get_scene_membership_cmd_t;

/**
 * @brief The Zigbee ZCL IAS zone enroll response command struct
 */
typedef struct esp_zb_zcl_ias_zone_enroll_response_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                      /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                    /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t enroll_rsp_code;                                   /*!< The enroll response code refer to `esp_zb_zcl_ias_zone_enroll_response_code_t` */
    uint8_t zone_id;                                           /*!< Zone ID is the index of table */
} esp_zb_zcl_ias_zone_enroll_response_cmd_t;

/**
 * @brief The Zigbee ZCL IAS zone Change Notification command struct
 */
typedef struct esp_zb_zcl_ias_zone_status_change_notif_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                       /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                     /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t zone_status;                                       /*!< Zone status shall be current value of the zone status attribute */
    uint8_t  extend_status;                                     /*!< Extended status for additional info */
    uint8_t  zone_id;                                           /*!< Zone ID is the index of table */
    uint16_t delay;                                             /*!< Delay in quarter-seconds */
} esp_zb_zcl_ias_zone_status_change_notif_cmd_t;

/**
 * @brief The Zigbee ZCL IAS zone enroll request command struct
 */
typedef struct esp_zb_zcl_ias_zone_enroll_request_cmd_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                      /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                    /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint16_t zone_type;                                        /*!< Zone type */
    uint16_t manuf_code;                                       /*!< Manufacturer code */
} esp_zb_zcl_ias_zone_enroll_request_cmd_t;

/**
 * @brief The Zigbee ZCL window covering send command struct
 *
 * @note value only support uint8_t, uint16_t data types for the Lift/Tilt value/percentage payload. If not, set to NULL
 *
 */
typedef struct esp_zb_zcl_window_covering_cluster_send_cmd_req_s{
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                       /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                     /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    void *value;                                                /*!< Pointer to value */
    uint16_t cluster_id;                                        /*!< Cluster id */
    uint8_t cmd_id;                                             /*!< Command id */
}esp_zb_zcl_window_covering_cluster_send_cmd_req_t;

/**
 * @brief The Zigbee ZCL electrical profile information response command struct
 */
typedef struct esp_zb_zcl_electrical_profile_info_cmd_resp_s{
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                       /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                     /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    esp_zb_electrical_measurement_profile_info_t profile_info;  /*!< Electrical profile info response command */
    uint16_t cluster_id;                                        /*!< Cluster id */
}esp_zb_zcl_electrical_profile_info_cmd_resp_t;

/**
 * @brief The Zigbee ZCL electrical profile response command struct
 */
typedef struct esp_zb_zcl_electrical_measurement_profile_cmd_resp_s{
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                        /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                      /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    esp_zb_electrical_measurement_profile_t profile;             /*!< Electrical profile response command */
    uint16_t cluster_id;                                         /*!< Cluster id */
}esp_zb_zcl_electrical_measurement_profile_cmd_resp_t;

/**
 * @brief The Zigbee ZCL custom cluster command struct
 *
 * @note Support only u8, s8, u16, s16, u32, s32, string  data types.
 *
 * @note For string data type, the first byte should be the length of string.
 *
 */
typedef struct esp_zb_zcl_custom_cluster_cmd_req_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                   /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                 /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    void *value;                                            /*!< Pointer to value */
    esp_zb_zcl_attr_type_t data_type;                       /*!< Data type to be used */
    uint16_t cluster_id;                                    /*!< Cluster id */
    uint16_t custom_cmd_id;                                 /*!< Custom command id */
} esp_zb_zcl_custom_cluster_cmd_req_t;

/**
 * @brief The Zigbee ZCL custom cluster command response struct
 *
 */
typedef struct esp_zb_zcl_custom_cluster_cmd_resp_s {
    esp_zb_zcl_basic_cmd_t zcl_basic_cmd;                   /*!< Basic command info */
    esp_zb_zcl_address_mode_t address_mode;                 /*!< APS addressing mode constants refer to esp_zb_zcl_address_mode_t */
    uint8_t status;                                         /*!< Status value */
    uint16_t cluster_id;                                    /*!< Cluster id */
    uint16_t custom_cmd_resp_id;                            /*!< Custom command response id */
} esp_zb_zcl_custom_cluster_cmd_resp_t;

/**
 * @brief The Zigbee zcl cluster command value struct
 *
 */
typedef struct {
    esp_zb_zcl_attr_type_t type;                /*!< Data type to be used */
    uint8_t length;                             /*!< Length of string data type, first byte should be the length of string */
    void *value;                                /*!< Supported data types u8, s8, u16, s16, u32, s32, char string */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_cluster_command_value_t;

/**
 * @brief The Zigbee zcl cluster received command application information struct
 *
 */
typedef struct esp_zb_zcl_cmd_info_s {
    uint8_t status;                                 /*!< Parse the status of command */
    esp_zb_zcl_addr_t zcl_addr_u;                   /*!< Type to represent source address of ZCL message */
    uint8_t  dst_endpoint;                          /*!< The destination enpoint of command */
    uint8_t  src_endpoint;                          /*!< The source enpoint of command */
    uint16_t cluster_id;                            /*!< The cluster id for command */
    uint16_t command_id;                            /*!< The command id to be used */
    esp_zb_zcl_cluster_command_value_t req;         /*!< The request data for command id */
} esp_zb_zcl_cmd_info_t;

/********************* Declare functions **************************/

/* read attribute, write attribute, config report and more general command will support later */

/**
 * @brief   Send read attribute command
 *
 * @param[in]  cmd_req  pointer to the read_attribute command @ref esp_zb_zcl_read_attr_cmd_s
 *
 */
void esp_zb_zcl_read_attr_cmd_req(esp_zb_zcl_read_attr_cmd_t *cmd_req);

/**
 * @brief   Send write attribute command
 *
 * @param[in]  cmd_req  pointer to the write attribute command @ref esp_zb_zcl_write_attr_cmd_s
 *
 */
void esp_zb_zcl_write_attr_cmd_req(esp_zb_zcl_write_attr_cmd_t *cmd_req);

/**
 * @brief   Send report attribute command
 *
 * @param[in]  cmd_req  pointer to the report attribute command @ref esp_zb_zcl_report_attr_cmd_s
 * @note Currently it supports ZCL specs defined attributes with type 8,16,32,64 bit or string.
 * @return - ESP_OK on success
 *
 */
esp_err_t esp_zb_zcl_report_attr_cmd_req(esp_zb_zcl_report_attr_cmd_t *cmd_req);

/**
 * @brief   Send config report command
 *
 * @param[in]  cmd_req  pointer to the config report command @ref esp_zb_zcl_config_report_cmd_s
 *
 */
void esp_zb_zcl_config_report_cmd_req(esp_zb_zcl_config_report_cmd_t *cmd_req);

/* ZCL basic cluster list command */

/**
 * @brief   Send ZCL basic reset to factory default command
 *
 * @param[in]  cmd_req  pointer to the basic command @ref esp_zb_zcl_basic_fact_reset_cmd_s
 *
 */
void esp_zb_zcl_basic_factory_reset_cmd_req(esp_zb_zcl_basic_fact_reset_cmd_t *cmd_req);

/* ZCL on off cluster list command */

/**
 * @brief   Send on-off command
 *
 * @param[in]  cmd_req  pointer to the on-off command @ref esp_zb_zcl_on_off_cmd_s
 *
 */
void esp_zb_zcl_on_off_cmd_req(esp_zb_zcl_on_off_cmd_t *cmd_req);

/* ZCL identify cluster list command */

/**
 * @brief   Send identify command
 *
 * @param[in]  cmd_req  pointer to the identify command @ref esp_zb_zcl_identify_cmd_s
 *
 */
void esp_zb_zcl_identify_cmd_req(esp_zb_zcl_identify_cmd_t *cmd_req);

/**
 * @brief   Send identify query command
 *
 * @param[in]  cmd_req  pointer to the identify query command @ref esp_zb_zcl_identify_query_cmd_s
 *
 */
void esp_zb_zcl_identify_query_cmd_req(esp_zb_zcl_identify_query_cmd_t *cmd_req);

/* ZCL level control cluster list command */

/**
 * @brief   Send move to level command
 *
 * @param[in]  cmd_req  pointer to the move to level command @ref esp_zb_zcl_move_to_level_cmd_s
 *
 */
void esp_zb_zcl_level_move_to_level_cmd_req(esp_zb_zcl_move_to_level_cmd_t *cmd_req);

/**
 * @brief   Send move to level with on/off effect command
 *
 * @param[in]  cmd_req  pointer to the move to level command @ref esp_zb_zcl_move_to_level_cmd_s
 *
 */
void esp_zb_zcl_level_move_to_level_with_onoff_cmd_req(esp_zb_zcl_move_to_level_cmd_t *cmd_req);

/**
 * @brief   Send move level command
 *
 * @param[in]  cmd_req  pointer to the move level command @ref esp_zb_zcl_level_move_cmd_s
 *
 */
void esp_zb_zcl_level_move_cmd_req(esp_zb_zcl_level_move_cmd_t *cmd_req);

/**
 * @brief   Send move level with on/off effect command
 *
 * @param[in]  cmd_req  pointer to the move level command @ref esp_zb_zcl_level_move_cmd_s
 *
 */
void esp_zb_zcl_level_move_with_onoff_cmd_req(esp_zb_zcl_level_move_cmd_t *cmd_req);

/**
 * @brief   Send step level command
 *
 * @param[in]  cmd_req  pointer to the step level command @ref esp_zb_zcl_level_step_cmd_s
 *
 */
void esp_zb_zcl_level_step_cmd_req(esp_zb_zcl_level_step_cmd_t *cmd_req);

/**
 * @brief   Send step level with on/off effect command
 *
 * @param[in]  cmd_req  pointer to the step level command @ref esp_zb_zcl_level_step_cmd_s
 *
 */
void esp_zb_zcl_level_step_with_onoff_cmd_req(esp_zb_zcl_level_step_cmd_t *cmd_req);

/**
 * @brief   Send stop level command
 *
 * @param[in]  cmd_req  pointer to the stop level command @ref esp_zb_zcl_level_stop_cmd_s
 *
 */
void esp_zb_zcl_level_stop_cmd_req(esp_zb_zcl_level_stop_cmd_t *cmd_req);

/* ZCL color control cluster list command */

/**
 * @brief   Send color move to hue command
 *
 * @param[in]  cmd_req  pointer to the move to hue command @ref esp_zb_zcl_color_move_to_hue_cmd_s
 *
 */
void esp_zb_zcl_color_move_to_hue_cmd_req(esp_zb_zcl_color_move_to_hue_cmd_t *cmd_req);

/**
 * @brief   Send color move hue command
 *
 * @param[in]  cmd_req  pointer to the move hue command @ref esp_zb_zcl_color_move_hue_cmd_s
 *
 */
void esp_zb_zcl_color_move_hue_cmd_req(esp_zb_zcl_color_move_hue_cmd_t *cmd_req);

/**
 * @brief   Send color step hue command
 *
 * @param[in]  cmd_req  pointer to the step hue command @ref esp_zb_zcl_color_step_hue_cmd_s
 *
 */
void esp_zb_zcl_color_step_hue_cmd_req(esp_zb_zcl_color_step_hue_cmd_t *cmd_req);

/**
 * @brief   Send color move to saturation command
 *
 * @param[in]  cmd_req  pointer to the move to saturation command @ref esp_zb_zcl_color_move_to_saturation_cmd_s
 *
 */
void esp_zb_zcl_color_move_to_saturation_cmd_req(esp_zb_zcl_color_move_to_saturation_cmd_t *cmd_req);

/**
 * @brief   Send color move saturation command
 *
 * @param[in]  cmd_req  pointer to the move saturation command @ref esp_zb_zcl_color_move_saturation_cmd_s
 *
 */
void esp_zb_zcl_color_move_saturation_cmd_req(esp_zb_zcl_color_move_saturation_cmd_t *cmd_req);

/**
 * @brief   Send color step saturation command
 *
 * @param[in]  cmd_req  pointer to the step saturation command @ref esp_zb_zcl_color_step_saturation_cmd_s
 *
 */
void esp_zb_zcl_color_step_saturation_cmd_req(esp_zb_zcl_color_step_saturation_cmd_t *cmd_req);

/**
 * @brief   Send color move to hue and saturation command
 *
 * @param[in]  cmd_req  pointer to the move to hue and saturation command @ref esp_zb_color_move_to_hue_saturation_cmd_s
 *
 */
void esp_zb_zcl_color_move_to_hue_and_saturation_cmd_req(esp_zb_color_move_to_hue_saturation_cmd_t *cmd_req);


/**
 * @brief   Send color move to color command
 *
 * @param[in]  cmd_req  pointer to the move to color command @ref esp_zb_zcl_color_move_to_color_cmd_s
 *
 */
void esp_zb_zcl_color_move_to_color_cmd_req(esp_zb_zcl_color_move_to_color_cmd_t *cmd_req);

/**
 * @brief   Send color move color command
 *
 * @param[in]  cmd_req  pointer to the move color command @ref esp_zb_zcl_color_move_color_cmd_s
 *
 */
void esp_zb_zcl_color_move_color_cmd_req(esp_zb_zcl_color_move_color_cmd_t *cmd_req);

/**
 * @brief   Send color step color command
 *
 * @param[in]  cmd_req  pointer to the step color command @ref esp_zb_zcl_color_step_color_cmd_s
 *
 */
void esp_zb_zcl_color_step_color_cmd_req(esp_zb_zcl_color_step_color_cmd_t *cmd_req);

/**
 * @brief   Send color stop color command
 *
 * @param[in]  cmd_req  pointer to the stop color command @ref esp_zb_zcl_color_stop_move_step_cmd_s
 *
 */
void esp_zb_zcl_color_stop_move_step_cmd_req(esp_zb_zcl_color_stop_move_step_cmd_t *cmd_req);

/**
 * @brief   Send color control move to color temperature command(0x0a)
 *
 * @param[in]  cmd_req  pointer to the move to color temperature command @ref esp_zb_zcl_color_move_to_color_temperature_cmd_s
 *
 */
void esp_zb_zcl_color_move_to_color_temperature_cmd_req(esp_zb_zcl_color_move_to_color_temperature_cmd_t *cmd_req);

/**
 * @brief   Send color control enhanced move to hue command(0x40)
 *
 * @param[in]  cmd_req  pointer to the enhanced move to hue command @ref esp_zb_zcl_color_enhanced_move_to_hue_cmd_s
 *
 */
void esp_zb_zcl_color_enhanced_move_to_hue_cmd_req(esp_zb_zcl_color_enhanced_move_to_hue_cmd_t *cmd_req);

/**
 * @brief   Send color control enhanced move hue command(0x41)
 *
 * @param[in]  cmd_req  pointer to the enhanced move hue command @ref esp_zb_zcl_color_enhanced_move_hue_cmd_s
 *
 */
void esp_zb_zcl_color_enhanced_move_hue_cmd_req(esp_zb_zcl_color_enhanced_move_hue_cmd_t *cmd_req);

/**
 * @brief   Send color control enhanced step hue command(0x42)
 *
 * @param[in]  cmd_req  pointer to the enhanced step hue command @ref esp_zb_zcl_color_enhanced_step_hue_cmd_s
 *
 */
void esp_zb_zcl_color_enhanced_step_hue_cmd_req(esp_zb_zcl_color_enhanced_step_hue_cmd_t *cmd_req);

/**
 * @brief   Send color control move to hue and saturation command(0x43)
 *
 * @param[in]  cmd_req  pointer to the enhanced move to hue saturation command @ref esp_zb_zcl_color_enhanced_move_to_hue_saturation_cmd_s
 *
 */
void esp_zb_zcl_color_enhanced_move_to_hue_saturation_cmd_req(esp_zb_zcl_color_enhanced_move_to_hue_saturation_cmd_t *cmd_req);

/**
 * @brief   Send color control color loop set command(0x44)
 *
 * @param[in]  cmd_req  pointer to the color loop set command @ref esp_zb_zcl_color_color_loop_set_cmd_s
 *
 */
void esp_zb_zcl_color_color_loop_set_cmd_req(esp_zb_zcl_color_color_loop_set_cmd_t *cmd_req);

/**
 * @brief   Send color control move color temperature command(0x4b)
 *
 * @param[in]  cmd_req  pointer to the move color temperature command @ref esp_zb_zcl_color_move_color_temperature_cmd_s
 *
 */
void esp_zb_zcl_color_move_color_temperature_cmd_req(esp_zb_zcl_color_move_color_temperature_cmd_t *cmd_req);

/**
 * @brief   Send color control step color temperature command(0x4c)
 *
 * @param[in]  cmd_req  pointer to the step color temperature command @ref esp_zb_zcl_color_step_color_temperature_cmd_s
 *
 */
void esp_zb_zcl_color_step_color_temperature_cmd_req(esp_zb_zcl_color_step_color_temperature_cmd_t *cmd_req);

/**
 * @brief   Send lock door command
 *
 * @param[in]  cmd_req  pointer to the unlock door command @ref esp_zb_zcl_lock_unlock_door_cmd_s
 *
 */
void esp_zb_zcl_lock_door_cmd_req(esp_zb_zcl_lock_unlock_door_cmd_t *cmd_req);

/**
 * @brief   Send unlock door command
 *
 * @param[in]  cmd_req  pointer to the unlock door command @ref esp_zb_zcl_lock_unlock_door_cmd_s
 *
 */
void esp_zb_zcl_unlock_door_cmd_req(esp_zb_zcl_lock_unlock_door_cmd_t *cmd_req);

/**
 * @brief   Send add group command
 *
 * @param[in]  cmd_req  pointer to the add group command @ref esp_zb_zcl_groups_add_group_cmd_s
 *
 */
void esp_zb_zcl_groups_add_group_cmd_req(esp_zb_zcl_groups_add_group_cmd_t *cmd_req);

/**
 * @brief   Send remove group command
 *
 * @param[in]  cmd_req  pointer to the add group command @ref esp_zb_zcl_groups_add_group_cmd_s
 *
 */
void esp_zb_zcl_groups_remove_group_cmd_req(esp_zb_zcl_groups_add_group_cmd_t *cmd_req);

/**
 * @brief   Send remove all groups command
 *
 * @param[in]  cmd_req  pointer to the remove all group command @ref esp_zb_zcl_groups_remove_all_groups_cmd_s
 *
 */
void esp_zb_zcl_groups_remove_all_groups_cmd_req(esp_zb_zcl_groups_remove_all_groups_cmd_t *cmd_req);

/**
 * @brief   Send view group command
 *
 * @param[in]  cmd_req  pointer to the add group command @ref esp_zb_zcl_groups_add_group_cmd_s
 *
 */
void esp_zb_zcl_groups_view_group_cmd_req(esp_zb_zcl_groups_add_group_cmd_t *cmd_req);

/**
 * @brief   Send get group memebership command
 *
 * @param[in]  cmd_req  pointer to the get group memebership command @ref esp_zb_zcl_groups_get_group_membership_cmd_s
 *
 */
void esp_zb_zcl_groups_get_group_membership_cmd_req(esp_zb_zcl_groups_get_group_membership_cmd_t *cmd_req);

/**
 * @brief   Send add scene command
 *
 * @param[in]  cmd_req  pointer to the add scene command  @ref esp_zb_zcl_scenes_add_scene_cmd_s
 *
 */
void esp_zb_zcl_scenes_add_scene_cmd_req(esp_zb_zcl_scenes_add_scene_cmd_t *cmd_req);

/**
 * @brief   Send remove scene command
 *
 * @param[in]  cmd_req  pointer to the remove scene command  @ref esp_zb_zcl_scenes_remove_scene_cmd_s
 *
 */
void esp_zb_zcl_scenes_remove_scene_cmd_req(esp_zb_zcl_scenes_remove_scene_cmd_t *cmd_req);

/**
 * @brief   Send remove all scenes command
 *
 * @param[in]  cmd_req  pointer to the add scenes command  @ref esp_zb_zcl_scenes_remove_all_scenes_cmd_s
 *
 */
void esp_zb_zcl_scenes_remove_all_scenes_cmd_req(esp_zb_zcl_scenes_remove_all_scenes_cmd_t *cmd_req);

/**
 * @brief   Send view scene command
 *
 * @param[in]  cmd_req  pointer to the view scene command  @ref esp_zb_zcl_scenes_view_scene_cmd_s
 *
 */
void esp_zb_zcl_scenes_view_scene_cmd_req(esp_zb_zcl_scenes_view_scene_cmd_t *cmd_req);

/**
 * @brief   Send store scene command
 *
 * @param[in]  cmd_req  pointer to the store scene command  @ref esp_zb_zcl_scenes_store_scene_cmd_s
 *
 */
void esp_zb_zcl_scenes_store_scene_cmd_req(esp_zb_zcl_scenes_store_scene_cmd_t *cmd_req);

/**
 * @brief   Send recall scene command
 *
 * @param[in]  cmd_req  pointer to the recall scene command  @ref esp_zb_zcl_scenes_recall_scene_cmd_s
 *
 */
void esp_zb_zcl_scenes_recall_scene_cmd_req(esp_zb_zcl_scenes_recall_scene_cmd_t *cmd_req);

/**
 * @brief   Send get scene membership command
 *
 * @param[in]  cmd_req  pointer to the get scene membership command  @ref esp_zb_zcl_scenes_get_scene_membership_cmd_s
 *
 */
void esp_zb_zcl_scenes_get_scene_membership_cmd_req(esp_zb_zcl_scenes_get_scene_membership_cmd_t *cmd_req);

/**
 * @brief   Send IAS zone enroll response command
 * @note Type 2 cluster from client to server
 * @param[in]  cmd_resp  pointer to the zone enroll response command  @ref esp_zb_zcl_ias_zone_enroll_response_cmd_s
 *
 */
void esp_zb_zcl_ias_zone_enroll_cmd_resp(esp_zb_zcl_ias_zone_enroll_response_cmd_t *cmd_resp);

/**
 * @brief   Send IAS zone status change notification command
 * @note Type 2 cluster from server to client
 * @param[in]  cmd_req  pointer to the ias zone status change notification command  @ref esp_zb_zcl_ias_zone_status_change_notif_cmd_s
 *
 */
void esp_zb_zcl_ias_zone_status_change_notif_cmd_req(esp_zb_zcl_ias_zone_status_change_notif_cmd_t *cmd_req);

/**
 * @brief   Send IAS zone enroll request command
 * @note Type 2 cluster from server to client
 * @param[in]  cmd_req  pointer to the ias zone enroll request command @ref esp_zb_zcl_ias_zone_enroll_request_cmd_s
 *
 */
void esp_zb_zcl_ias_zone_enroll_cmd_req(esp_zb_zcl_ias_zone_enroll_request_cmd_t *cmd_req);

/**
 * @brief   Send window covering cluster command request
 *
 * @param[in]  cmd_req  pointer to the send custom cluster command request @ref esp_zb_zcl_window_covering_cluster_send_cmd_req_s
 *
 */
void esp_zb_zcl_window_covering_cluster_send_cmd_req(esp_zb_zcl_window_covering_cluster_send_cmd_req_t *cmd_req);

/**
 * @brief   Get electrical measurement cluster profile info response
 *
 * @param[in]  cmd_req  pointer to the send custom cluster command response @ref esp_zb_zcl_electrical_profile_info_cmd_resp_s
 *
 */
void esp_zb_zcl_electrical_measurement_cluster_get_profile_info_resp(esp_zb_zcl_electrical_profile_info_cmd_resp_t *cmd_req);

/**
 * @brief   Get electrical measurement cluster measurement profile response
 *
 * @param[in]  cmd_req  pointer to the send custom cluster command response @ref esp_zb_zcl_electrical_measurement_profile_cmd_resp_s
 *
 */
void esp_zb_zcl_electrical_measurement_cluster_get_measurement_profile_resp(esp_zb_zcl_electrical_measurement_profile_cmd_resp_t *cmd_req);

/**
 * @brief   Send custom cluster command request
 *
 * @param[in]  cmd_req  pointer to the send custom cluster command request @ref esp_zb_zcl_custom_cluster_cmd_req_s
 *
 */
void esp_zb_zcl_custom_cluster_cmd_req(esp_zb_zcl_custom_cluster_cmd_req_t *cmd_req);

/**
 * @brief   Send custom cluster command response
 *
 * @param[in]  cmd_req  pointer to the send custom cluster command response @ref esp_zb_zcl_custom_cluster_cmd_resp_s
 *
 */
void esp_zb_zcl_custom_cluster_cmd_resp(esp_zb_zcl_custom_cluster_cmd_resp_t *cmd_req);

#ifdef __cplusplus
}
#endif
