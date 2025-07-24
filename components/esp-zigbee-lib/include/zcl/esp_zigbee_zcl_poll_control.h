/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_type.h"

/** @brief Poll Control cluster attribute identifiers
 */
typedef enum {
    ESP_ZB_ZCL_ATTR_POLL_CONTROL_CHECK_IN_INTERVAL_ID       = 0x0000U, /*!< Represents the default amount of time between check-ins by the poll control server with the poll control client. */
    ESP_ZB_ZCL_ATTR_POLL_CONTROL_LONG_POLL_INTERVAL_ID      = 0x0001U, /*!< Defines the frequency of polling that an end device does when it is NOT in fast poll mode. */
    ESP_ZB_ZCL_ATTR_POLL_CONTROL_SHORT_POLL_INTERVAL_ID     = 0x0002U, /*!< Represents the number of quarter-seconds that an end device waits between MAC Data Requests to its parent when it is expecting data */
    ESP_ZB_ZCL_ATTR_POLL_CONTROL_FAST_POLL_TIMEOUT_ID       = 0x0003U, /*!< Represents the number of quarter-seconds that an end device will stay in fast poll mode by default. */
    ESP_ZB_ZCL_ATTR_POLL_CONTROL_MIN_CHECK_IN_INTERVAL_ID   = 0x0004U, /*!< The Poll Control Server MAY optionally provide its own minimum value for the Check-inInterval */
    ESP_ZB_ZCL_ATTR_POLL_CONTROL_LONG_POLL_MIN_INTERVAL_ID  = 0x0005U, /*!< The Poll Control Server MAY optionally provide its own minimum value for the LongPollInterval */
    ESP_ZB_ZCL_ATTR_POLL_CONTROL_FAST_POLL_MAX_TIMEOUT_ID   = 0x0006U, /*!< The Poll Control Server MAY optionally provide its own maximum value for the FastPollTimeout*/
} esp_zb_zcl_poll_control_attr_t;

/** @brief Default values for Poll Control cluster attributes */
#define ESP_ZB_ZCL_POLL_CONTROL_CHECK_IN_INTERVAL_DEFAULT_VALUE       ((uint32_t)0x3840U)
/** @brief Default value for Long Poll Interval attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_LONG_POLL_INTERVAL_DEFAULT_VALUE      ((uint32_t)0x0014U)
/** @brief Default value for Short Poll Interval attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_SHORT_POLL_INTERVAL_DEFAULT_VALUE     ((uint16_t)0x0002U)
/** @brief Default value for Fast Poll Timeout attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_FAST_POLL_TIMEOUT_DEFAULT_VALUE       ((uint16_t)0x0028U)
/** @brief Default value for Check-in Interval Min attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_MIN_CHECK_IN_INTERVAL_DEFAULT_VALUE   ((uint32_t)0x0000U)
/** @brief Default value for Long Poll Interval Min attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_LONG_POLL_MIN_INTERVAL_DEFAULT_VALUE  ((uint32_t)0x0000U)
/** @brief Default value for Fast Poll Timeout Max attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_FAST_POLL_MAX_TIMEOUT_DEFAULT_VALUE   ((uint16_t)0x0000U)

/** @brief Minimum and maximum values for Poll Control cluster attributes */
#define ESP_ZB_ZCL_POLL_CONTROL_CHECK_IN_INTERVAL_MIN_VALUE       ((uint32_t)0x0000U)
/** @brief Maximum value for Check-in Interval attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_CHECK_IN_INTERVAL_MAX_VALUE       ((uint32_t)0x6e0000U)
/** @brief Minimum value for Long Poll Interval attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_LONG_POLL_INTERVAL_MIN_VALUE      ((uint32_t)0x0004U)   /* 4 quarter seconds = 1 second */
/** @brief Maximum value for Long Poll Interval attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_LONG_POLL_INTERVAL_MAX_VALUE      ((uint32_t)0x6e0000U)
/** @brief Minimum value for Short Poll Interval attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_SHORT_POLL_INTERVAL_MIN_VALUE     ((uint16_t)0x0001U)   /* 1 quarter second */
/** @brief Maximum value for Short Poll Interval attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_SHORT_POLL_INTERVAL_MAX_VALUE     ((uint16_t)0xffffU)
/** @brief Minimum value for Fast Poll Timeout attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_FAST_POLL_TIMEOUT_MIN_VALUE       ((uint16_t)0x0001U)
/** @brief Maximum value for Fast Poll Timeout attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_FAST_POLL_TIMEOUT_MAX_VALUE       ((uint16_t)0xffffU)
/** @brief Minimum value for Fast Poll Timeout Max attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_FAST_POLL_MAX_TIMEOUT_MIN_VALUE   ((uint16_t)0x0001U)
/** @brief Maximum value for Fast Poll Timeout Max attribute */
#define ESP_ZB_ZCL_POLL_CONTROL_FAST_POLL_MAX_TIMEOUT_MAX_VALUE   ((uint16_t)0xffffU)

/** @brief Poll Control cluster client generated command identifiers */
typedef enum {
    ESP_ZB_ZCL_CMD_POLL_CONTROL_CHECK_IN_RESPONSE_ID        = 0x00, /*!< Check-in Response command */
    ESP_ZB_ZCL_CMD_POLL_CONTROL_FAST_POLL_STOP_ID           = 0x01, /*!< Fast Poll Stop command */
    ESP_ZB_ZCL_CMD_POLL_CONTROL_SET_LONG_POLL_INTERVAL_ID   = 0x02, /*!< Set Long Poll Interval command */
    ESP_ZB_ZCL_CMD_POLL_CONTROL_SET_SHORT_POLL_INTERVAL_ID  = 0x03, /*!< Set Short Poll Interval command */
} esp_zb_zcl_poll_control_cli_cmd_id_t;

/** @brief Poll Control cluster server generated command identifiers */
typedef enum {
    ESP_ZB_ZCL_CMD_POLL_CONTROL_CHECK_IN_ID                 = 0x00, /*!< Check-in command */
} esp_zb_zcl_poll_control_srv_cmd_id_t;


#ifdef __cplusplus
}
#endif
