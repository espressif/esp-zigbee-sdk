#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "esp_zigbee_type.h"

/** @brief MultiState Input cluster attribute identifiers. */
typedef enum {
    ESP_ZB_ZCL_ATTR_MULTI_INPUT_STATE_TEXT_ID         = 0x000EU, /*!< StateText attribute */
    ESP_ZB_ZCL_ATTR_MULTI_INPUT_DESCRIPTION_ID        = 0x001CU, /*!< Description attribute */
    ESP_ZB_ZCL_ATTR_MULTI_INPUT_NUMBER_OF_STATES_ID   = 0x004AU, /*!< Number of states attribute */
    ESP_ZB_ZCL_ATTR_MULTI_INPUT_OUT_OF_SERVICE_ID     = 0x0051U, /*!< OutOfService attribute */
    ESP_ZB_ZCL_ATTR_MULTI_INPUT_PRESENT_VALUE_ID      = 0x0055U, /*!< PresentValue attribute */
    ESP_ZB_ZCL_ATTR_MULTI_INPUT_RELIABILITY_ID        = 0x0067U, /*!< Reliability attribute */
    ESP_ZB_ZCL_ATTR_MULTI_INPUT_STATUS_FLAGS_ID       = 0x006FU, /*!< StatusFlag attribute */
    ESP_ZB_ZCL_ATTR_MULTI_INPUT_APPLICATION_TYPE_ID   = 0x0100U, /*!< Application type attribute */
} esp_zb_zcl_multi_input_attr_t;

/** @brief Default value for StateText attribute */
#define ESP_ZB_ZCL_MULTI_INPUT_STATE_TEXT_DEFAULT_VALUE           {0}

/** @brief Default value for Description attribute */
#define ESP_ZB_ZCL_MULTI_INPUT_DESCRIPTION_DEFAULT_VALUE          {0}

/** @brief Default value for Number of states attribute */
#define ESP_ZB_ZCL_MULTI_INPUT_NUMBER_OF_STATES_DEFAULT_VALUE     (0)

/** @brief Default value for OutOfService attribute */
#define ESP_ZB_ZCL_MULTI_INPUT_OUT_OF_SERVICE_DEFAULT_VALUE       false

/** @brief Default value for PresentValue attribute */
#define ESP_ZB_ZCL_MULTI_INPUT_PRESENT_VALUE_DEFAULT_VALUE        0

/** @brief Default value for Reliability attribute */
#define ESP_ZB_ZCL_MULTI_INPUT_RELIABILITY_DEFAULT_VALUE          0

/** @brief Default value for StatusFlag attribute */
#define ESP_ZB_ZCL_MULTI_INPUT_STATUS_FLAGS_DEFAULT_VALUE         0

/** @brief Default value for Application type attribute */
#define ESP_ZB_ZCL_MULTI_INPUT_APPLICATION_TYPE_DEFAULT_VALUE     0

/** @brief StatusFlag attribute minimum value */
#define ESP_ZB_ZCL_MULTI_INPUT_STATUS_FLAGS_MIN_VALUE             0x00U

/** @brief StatusFlag attribute maximum value */    
#define ESP_ZB_ZCL_MULTI_INPUT_STATUS_FLAGS_MAX_VALUE             0x0FU

/** @brief Values for StatusFlags attribute */
typedef enum {
    ESP_ZB_ZCL_MULTI_INPUT_STATUS_FLAG_NORMAL         = 0x00, /*!< Normal (default) state. */
    ESP_ZB_ZCL_MULTI_INPUT_STATUS_FLAG_IN_ALARM       = 0x01, /*!< In alarm bit. */
    ESP_ZB_ZCL_MULTI_INPUT_STATUS_FLAG_FAULT          = 0x02, /*!< Fault bit. */
    ESP_ZB_ZCL_MULTI_INPUT_STATUS_FLAG_OVERRIDDEN     = 0x04, /*!< Overridden bit. */
    ESP_ZB_ZCL_MULTI_INPUT_STATUS_FLAG_OUT_OF_SERVICE = 0x08, /*!< Out of service bit. */
} esp_zb_zcl_multi_input_status_flags_value_t;

/** @brief Values for Reliability attribute */
typedef enum {
    ESP_ZB_ZCL_MULTI_INPUT_RELIABILITY_NO_FAULT_DETECTED   = 0x00, /*!< No fault detected */
    ESP_ZB_ZCL_MULTI_INPUT_RELIABILITY_NO_SENSOR           = 0x01, /*!< No sensor */
    ESP_ZB_ZCL_MULTI_INPUT_RELIABILITY_OVER_RANGE          = 0x02, /*!< Over range */
    ESP_ZB_ZCL_MULTI_INPUT_RELIABILITY_UNDER_RANGE         = 0x03, /*!< Under range */
    ESP_ZB_ZCL_MULTI_INPUT_RELIABILITY_OPEN_LOOP           = 0x04, /*!< Open loop */
    ESP_ZB_ZCL_MULTI_INPUT_RELIABILITY_SHORTED_LOOP        = 0x05, /*!< Shorted loop */
    ESP_ZB_ZCL_MULTI_INPUT_RELIABILITY_NO_OUTPUT           = 0x06, /*!< No output */
    ESP_ZB_ZCL_MULTI_INPUT_RELIABILITY_UNRELIABLE_OTHER    = 0x07, /*!< Unreliable other */
    ESP_ZB_ZCL_MULTI_INPUT_RELIABILITY_PROCESS_ERROR       = 0x08, /*!< Process error */
    /* 0x09 is for multistate clusters only */
    ESP_ZB_ZCL_MULTI_INPUT_RELIABILITY_CONFIGURATION_ERROR = 0x0a, /*!< Configuration error */
} esp_zb_zcl_multi_input_reliability_value_t;

/** Multistate Input cluster application types
 *      The ApplicationType attribute indicates the specific application usage
 *      for the cluster. ApplicationType is subdivided into Group, Type and
 *      an Index number, as follows:
 *
 *      Group = Bits 24 to 31
 *        An indication of the cluster this attribute is part of. Multistate Input
 *        clusters have Group = 0x00.
 *
 *      Type = Bits 16 to 23
 *        The physical quantity that the PresentValue attribute of the cluster
 *        represents.
 *
 *      Index = Bits 0 to 15
 *        The specific application usage of the cluster.
 */
/** @brief Macros for ApplicationType attribute */
/** @brief Macros for ApplicationType attribute */
#define ESP_ZB_ZCL_MI_GROUP_ID 0x0D
#define ESP_ZB_ZCL_MI_SET_APP_TYPE_WITH_ID(_type, _id) (((ESP_ZB_ZCL_MI_GROUP_ID & 0xFF) << 24) | (((_type)&0xFF) << 16) | ((_id)&0xFFFF))

/** @brief Values for Multistate Input cluster application types (Type field, bits 16-23) */
typedef enum {
    ESP_ZB_ZCL_MI_APP_TYPE_DOMAIN_HVAC = 0x00, /*!< Application Domain HVAC */
    /* 0x01 to 0xFE are reserved */
    ESP_ZB_ZCL_MI_APP_TYPE_OTHER       = 0xFF /*!< Other */
} esp_zb_zcl_mi_application_types_t;

/** @brief Values for Multistate Input cluster HVAC application usages */
typedef enum {
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_OFF_ON_AUTO = ESP_ZB_ZCL_MI_SET_APP_TYPE_WITH_ID(ESP_ZB_ZCL_MI_APP_TYPE_DOMAIN_HVAC, 0x0000), /*!< Off, On, Auto */
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_OFF_LOW_MEDIUM_HIGH,                                                                          /*!< Off, Low, Medium, High */
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_AUTO_HEAT_COOL_OFF_EMERGENCY_FAN_MAX,                                                         /*!< Auto, Heat, Cool, Off, Emergency Heat, Fan Only,
                                                                                                                               Max Heat */
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_OCCUPIED_UNOCCUPIED_STANDBY_BYPASS,                                                           /*!< Occupied, Unoccupied, Standby, Bypass */
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_INACTIVE_ACTIVE_HOLD,                                                                         /*!< Inactive, Active, Hold */
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_AUTO_WARMUP_WATER_FLUSH_AUTOCAL_SHUTDOWNOPEN_SHUTDOWNCLOSED_LOWLIMIT_TEST_BALANCE,            /*!< Auto, Warm-up, Water Flush, Autocalibration, Shutdown Open,
                                                                                                                                 Shutdown Closed, Low Limit, Test and Balance */
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_OFF_AUTO_HEAT_COOL_HEATONLY_COOLONLY_FAN_ONLY,                                                /*!< Off, Auto, Heat Cool, Heat Only, Cool Only, Fan Only */
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_HIGH_NORMAL_LOW,                                                                              /*!< High, Normal, Low */
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_OCCUPIED_UNOCCUPIED_STARTUP_SHUTDOWN,                                                         /*!< Occupied, Unoccupied, Startup, Shutdown */
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_NIGHT_DAY_HOLD,                                                                               /*!< Night, Day, Hold */
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_OFF_COOL_HEAT_AUTO_EMERGENCY,                                                                 /*!< Off, Cool, Heat, Auto, Emergency Heat */
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_SHUTDOWNCLOSED_SHUTDOWNOPEN_SATISFIED_MIXING_COOLING_HEATING_SUPPLEMENTAL_HEAT,               /*!< Shutdown Closed, Shutdown Open, Satisfied, Mixing, Cooling,
                                                                                                                                 Heating, Supplemental Heat */
    /* 0x0200 to 0xFFFE are Vendor defined */
    ESP_ZB_ZCL_MI_DOMAIN_HVAC_OTHER = ESP_ZB_ZCL_MI_SET_APP_TYPE_WITH_ID(ESP_ZB_ZCL_MI_APP_TYPE_DOMAIN_HVAC, 0xFFFF) /*!< Other */
} esp_zb_zcl_mi_domain_hvac_t;

void esp_zb_zcl_multi_input_init_server(void);
void esp_zb_zcl_multi_input_init_client(void);

#define ESP_ZB_ZCL_CLUSTER_ID_MULTI_INPUT_SERVER_ROLE_INIT esp_zb_zcl_multi_input_init_server
#define ESP_ZB_ZCL_CLUSTER_ID_MULTI_INPUT_CLIENT_ROLE_INIT esp_zb_zcl_multi_input_init_client

#ifdef __cplusplus
}
#endif
