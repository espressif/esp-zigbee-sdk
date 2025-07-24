/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_type.h"

/** @brief Binary Value cluster attribute identifiers. */
typedef enum {
    ESP_ZB_ZCL_ATTR_BINARY_VALUE_ACTIVE_TEXT_ID        = 0x0004U, /*!< Human readable description of the ACTIVE state. */
    ESP_ZB_ZCL_ATTR_BINARY_VALUE_DESCRIPTION_ID        = 0x001CU, /*!< Description of the usage. */
    ESP_ZB_ZCL_ATTR_BINARY_VALUE_INACTIVE_TEXT_ID      = 0x002EU, /*!< Human readable description of the INACTIVE state. */
    ESP_ZB_ZCL_ATTR_BINARY_VALUE_MIN_OFF_TIME_ID       = 0x0042U, /*!< Minimum Off Time. */
    ESP_ZB_ZCL_ATTR_BINARY_VALUE_MIN_ON_TIME_ID        = 0x0043U, /*!< Minimum On Time. */
    ESP_ZB_ZCL_ATTR_BINARY_VALUE_OUT_OF_SERVICE_ID     = 0x0051U, /*!< OutOfService attribute. */
    ESP_ZB_ZCL_ATTR_BINARY_VALUE_PRESENT_VALUE_ID      = 0x0055U, /*!< PresentValue attribute. */
    /** TODO: support PriorityArray Attribute */
    // ESP_ZB_ZCL_ATTR_BINARY_VALUE_PRIORITY_ARRAY_ID     = 0x0057U, /*!< Priority Array attribute. */
    ESP_ZB_ZCL_ATTR_BINARY_VALUE_RELIABILITY_ID        = 0x0067U, /*!< Reliability. */
    ESP_ZB_ZCL_ATTR_BINARY_VALUE_RELINQUISH_DEFAULT_ID = 0x0068U, /*!< Relinquish default. */
    ESP_ZB_ZCL_ATTR_BINARY_VALUE_STATUS_FLAGS_ID       = 0x006FU, /*!< StatusFlag attribute. */
    ESP_ZB_ZCL_ATTR_BINARY_VALUE_APPLICATION_TYPE_ID   = 0x0100U, /*!< ApplicationType attribute. */
} esp_zb_zcl_binary_value_attr_t;

/** @brief Default value for ActiveText attribute */
#define ESP_ZB_ZCL_BINARY_VALUE_ACTIVE_TEXT_DEFAULT_VALUE         {0}
/** @brief Default value for Description attribute */
#define ESP_ZB_ZCL_BINARY_VALUE_DESCRIPTION_DEFAULT_VALUE         {0}
/** @brief Default value for InactiveText attribute */
#define ESP_ZB_ZCL_BINARY_VALUE_INACTIVE_TEXT_DEFAULT_VALUE       {0}
/** @brief Default value for MinOffTime attribute */
#define ESP_ZB_ZCL_BINARY_VALUE_MIN_OFF_TIME_DEFAULT_VALUE        ESP_ZB_ZCL_VALUE_U32_FF
/** @brief Default value for MinOnTime attribute */
#define ESP_ZB_ZCL_BINARY_VALUE_MIN_ON_TIME_DEFAULT_VALUE         ESP_ZB_ZCL_VALUE_U32_FF
/** @brief OutOfService attribute default value */
#define ESP_ZB_ZCL_BINARY_VALUE_OUT_OF_SERVICE_DEFAULT_VALUE      false
/** @brief Default value for PresentValue attribute */
#define ESP_ZB_ZCL_BINARY_VALUE_PRESENT_VALUE_DEFAULT_VALUE       false
/** @brief Default value for Reliability attribute */
#define ESP_ZB_ZCL_BINARY_VALUE_RELIABILITY_DEFAULT_VALUE         ((uint8_t)0)
/** @brief Default value for RelinquishDefault attribute */
#define ESP_ZB_ZCL_BINARY_VALUE_RELINQUISH_DEFAULT_DEFAULT_VALUE  false
/** @brief Default value for StatusFlag attribute */
#define ESP_ZB_ZCL_BINARY_VALUE_STATUS_FLAGS_DEFAULT_VALUE         0
/** @brief StatusFlag attribute minimum value */
#define ESP_ZB_ZCL_BINARY_VALUE_STATUS_FLAGS_MIN_VALUE             0x00U
/** @brief StatusFlag attribute maximum value */
#define ESP_ZB_ZCL_BINARY_VALUE_STATUS_FLAGS_MAX_VALUE             0x0FU
/** @brief Default value for ApplicationType attribute */
#define ESP_ZB_ZCL_BINARY_VALUE_APPLICATION_TYPE_DEFAULT_VALUE    0

/** @brief Values for StatusFlags attribute */
typedef enum {
    ESP_ZB_ZCL_BINARY_VALUE_STATUS_FLAG_NORMAL         = 0x00, /*!< Normal (default) state. */
    ESP_ZB_ZCL_BINARY_VALUE_STATUS_FLAG_IN_ALARM       = 0x01, /*!< In alarm bit. */
    ESP_ZB_ZCL_BINARY_VALUE_STATUS_FLAG_FAULT          = 0x02, /*!< Fault bit. */
    ESP_ZB_ZCL_BINARY_VALUE_STATUS_FLAG_OVERRIDDEN     = 0x04, /*!< Overridden bit. */
    ESP_ZB_ZCL_BINARY_VALUE_STATUS_FLAG_OUT_OF_SERVICE = 0x08, /*!< Out of service bit. */
} esp_zb_zcl_binary_value_status_flags_value_t;

/** @brief Values for Reliability attribute */
typedef enum {
    ESP_ZB_ZCL_BINARY_VALUE_RELIABILITY_NO_FAULT_DETECTED = 0x00, /*!< No fault detected */
    ESP_ZB_ZCL_BINARY_VALUE_RELIABILITY_NO_SENSOR         = 0x01, /*!< No sensor */
    ESP_ZB_ZCL_BINARY_VALUE_RELIABILITY_OVER_RANGE        = 0x02, /*!< Over range */
    ESP_ZB_ZCL_BINARY_VALUE_RELIABILITY_UNDER_RANGE       = 0x03, /*!< Under range */
    ESP_ZB_ZCL_BINARY_VALUE_RELIABILITY_OPEN_LOOP         = 0x04, /*!< Open loop */
    ESP_ZB_ZCL_BINARY_VALUE_RELIABILITY_SHORTED_LOOP      = 0x05, /*!< Shorted loop */
    ESP_ZB_ZCL_BINARY_VALUE_RELIABILITY_NO_OUTPUT         = 0x06, /*!< No output */
    ESP_ZB_ZCL_BINARY_VALUE_RELIABILITY_UNRELIABLE_OTHER  = 0x07, /*!< Unreliable other */
    ESP_ZB_ZCL_BINARY_VALUE_RELIABILITY_PROCESS_ERROR     = 0x08, /*!< Process error */
    /* 0x09 is for multistate clusters only */
    ESP_ZB_ZCL_BINARY_VALUE_RELIABILITY_CONFIGURATION_ERROR = 0x0a, /*!< Configuration error */
} esp_zb_zcl_binary_value_reliability_value_t;

/** @brief Macros for ApplicationType attribute */
#define ESP_ZB_ZCL_BV_GROUP_ID 0x05
#define ESP_ZB_ZCL_BV_SET_APP_TYPE_WITH_ID(_type, _id) (((ESP_ZB_ZCL_BV_GROUP_ID & 0xFF) << 24) | (((_type) & 0xFF) << 16) | ((_id) & 0xFFFF))

void esp_zb_zcl_binary_value_init_server(void);
void esp_zb_zcl_binary_value_init_client(void);

#define ESP_ZB_ZCL_CLUSTER_ID_BINARY_VALUE_SERVER_ROLE_INIT esp_zb_zcl_binary_value_init_server
#define ESP_ZB_ZCL_CLUSTER_ID_BINARY_VALUE_CLIENT_ROLE_INIT esp_zb_zcl_binary_value_init_client

#ifdef __cplusplus
}
#endif
