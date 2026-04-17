/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/zcl_common.h>
#include <ezbee/zcl/zcl_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------------------------------------------*
   COLOR_CONTROL Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the color_control cluster implementation */
#define EZB_ZCL_COLOR_CONTROL_CLUSTER_REVISION (3)

/**
 * @brief Attribute identifiers for the color_control server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_COLOR_CONTROL_CURRENT_HUE_ID                    = 0x0000U, /*!< CurrentHue attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_CURRENT_SATURATION_ID             = 0x0001U, /*!< CurrentSaturation attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_REMAINING_TIME_ID                 = 0x0002U, /*!< RemainingTime attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_CURRENT_X_ID                      = 0x0003U, /*!< CurrentX attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_CURRENT_Y_ID                      = 0x0004U, /*!< CurrentY attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_DRIFT_COMPENSATION_ID             = 0x0005U, /*!< DriftCompensation attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COMPENSATION_TEXT_ID              = 0x0006U, /*!< CompensationText attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_TEMPERATURE_MIREDS_ID       = 0x0007U, /*!< ColorTemperatureMireds attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_MODE_ID                     = 0x0008U, /*!< ColorMode attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_OPTIONS_ID                        = 0x000fU, /*!< Options attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_ENHANCED_CURRENT_HUE_ID           = 0x4000U, /*!< EnhancedCurrentHue attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_ENHANCED_COLOR_MODE_ID            = 0x4001U, /*!< EnhancedColorMode attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_LOOP_ACTIVE_ID              = 0x4002U, /*!< ColorLoopActive attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_LOOP_DIRECTION_ID           = 0x4003U, /*!< ColorLoopDirection attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_LOOP_TIME_ID                = 0x4004U, /*!< ColorLoopTime attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_LOOP_START_ENHANCED_HUE_ID  = 0x4005U, /*!< ColorLoopStartEnhancedHue attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_LOOP_STORED_ENHANCED_HUE_ID = 0x4006U, /*!< ColorLoopStoredEnhancedHue attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_CAPABILITIES_ID             = 0x400aU, /*!< ColorCapabilities attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_TEMP_PHYSICAL_MIN_MIREDS_ID = 0x400bU, /*!< ColorTempPhysicalMinMireds attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_TEMP_PHYSICAL_MAX_MIREDS_ID = 0x400cU, /*!< ColorTempPhysicalMaxMireds attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COUPLE_COLOR_TEMP_TO_LEVEL_MIN_MIREDS_ID =
        0x400dU, /*!< CoupleColorTempToLevelMinMireds attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_START_UP_COLOR_TEMPERATURE_MIREDS_ID = 0x4010U, /*!< StartUpColorTemperatureMireds attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_NUMBER_OF_PRIMARIES_ID               = 0x0010U, /*!< NumberOfPrimaries attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY1_X_ID                        = 0x0011U, /*!< Primary1X attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY1_Y_ID                        = 0x0012U, /*!< Primary1Y attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY1_INTENSITY_ID                = 0x0013U, /*!< Primary1Intensity attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY2_X_ID                        = 0x0015U, /*!< Primary2X attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY2_Y_ID                        = 0x0016U, /*!< Primary2Y attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY2_INTENSITY_ID                = 0x0017U, /*!< Primary2Intensity attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY3_X_ID                        = 0x0019U, /*!< Primary3X attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY3_Y_ID                        = 0x001aU, /*!< Primary3Y attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY3_INTENSITY_ID                = 0x001bU, /*!< Primary3Intensity attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY4_X_ID                        = 0x0020U, /*!< Primary4X attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY4_Y_ID                        = 0x0021U, /*!< Primary4Y attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY4_INTENSITY_ID                = 0x0022U, /*!< Primary4Intensity attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY5_X_ID                        = 0x0024U, /*!< Primary5X attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY5_Y_ID                        = 0x0025U, /*!< Primary5Y attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY5_INTENSITY_ID                = 0x0026U, /*!< Primary5Intensity attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY6_X_ID                        = 0x0028U, /*!< Primary6X attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY6_Y_ID                        = 0x0029U, /*!< Primary6Y attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_PRIMARY6_INTENSITY_ID                = 0x002aU, /*!< Primary6Intensity attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_WHITE_POINT_X_ID                     = 0x0030U, /*!< WhitePointX attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_WHITE_POINT_Y_ID                     = 0x0031U, /*!< WhitePointY attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_POINT_RX_ID                    = 0x0032U, /*!< ColorPointRX attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_POINT_RY_ID                    = 0x0033U, /*!< ColorPointRY attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_POINT_R_INTENSITY_ID           = 0x0034U, /*!< ColorPointRIntensity attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_POINT_GX_ID                    = 0x0036U, /*!< ColorPointGX attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_POINT_GY_ID                    = 0x0037U, /*!< ColorPointGY attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_POINT_G_INTENSITY_ID           = 0x0038U, /*!< ColorPointGIntensity attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_POINT_BX_ID                    = 0x003aU, /*!< ColorPointBX attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_POINT_BY_ID                    = 0x003bU, /*!< ColorPointBY attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_COLOR_POINT_B_INTENSITY_ID           = 0x003cU, /*!< ColorPointBIntensity attribute. */
    EZB_ZCL_ATTR_COLOR_CONTROL_CVC_CONTEXT_ID                       = 0xeff0U, /*!< CVCContext attribute. */
} ezb_zcl_color_control_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the ColorControl server cluster.
 */
typedef struct ezb_zcl_color_control_cluster_server_config_s {
    uint16_t current_x;           /*!< Configurable mandatory CurrentX attribute */
    uint16_t current_y;           /*!< Configurable mandatory CurrentY attribute */
    uint8_t  color_mode;          /*!< Configurable mandatory ColorMode attribute */
    uint8_t  options;             /*!< Configurable mandatory Options attribute */
    uint8_t  enhanced_color_mode; /*!< Configurable mandatory EnhancedColorMode attribute */
    uint16_t color_capabilities;  /*!< Configurable mandatory ColorCapabilities attribute */
    uint8_t  number_of_primaries; /*!< Configurable mandatory NumberOfPrimaries attribute */
} ezb_zcl_color_control_cluster_server_config_t;

/**
 * @brief Enumeration for ZCL DriftCompensation attribute of ColorControl.
 */
typedef enum {
    EZB_ZCL_COLOR_CONTROL_DRIFT_COMPENSATION_NONE                   = 0x00U, /*!< None */
    EZB_ZCL_COLOR_CONTROL_DRIFT_COMPENSATION_OTHER_OR_UNKNOWN       = 0x01U, /*!< OtherOrUnknown */
    EZB_ZCL_COLOR_CONTROL_DRIFT_COMPENSATION_TEMPERATURE_MONITORING = 0x02U, /*!< TemperatureMonitoring */
    EZB_ZCL_COLOR_CONTROL_DRIFT_COMPENSATION_OPTICAL_LUMINANCE_MONITORING_AND_FEEDBACK =
        0x03U, /*!< OpticalLuminanceMonitoringAndFeedback */
    EZB_ZCL_COLOR_CONTROL_DRIFT_COMPENSATION_OPTICAL_COLOR_MONITORING_AND_FEEDBACK =
        0x04U, /*!< OpticalColorMonitoringAndFeedback */
} ezb_zcl_color_control_server_drift_compensation_t;

/**
 * @brief Enumeration for ZCL ColorMode attribute of ColorControl.
 */
typedef enum {
    EZB_ZCL_COLOR_CONTROL_COLOR_MODE_CURRENT_HUE_AND_CURRENT_SATURATION = 0x00U, /*!< CurrentHueAndCurrentSaturation */
    EZB_ZCL_COLOR_CONTROL_COLOR_MODE_CURRENT_X_AND_CURRENT_Y            = 0x01U, /*!< CurrentXAndCurrentY */
    EZB_ZCL_COLOR_CONTROL_COLOR_MODE_COLOR_TEMPERATURE_MIREDS           = 0x02U, /*!< ColorTemperatureMireds */
} ezb_zcl_color_control_server_color_mode_t;

/**
 * @brief Enumeration for ZCL EnhancedColorMode attribute of ColorControl.
 */
typedef enum {
    EZB_ZCL_COLOR_CONTROL_ENHANCED_COLOR_MODE_CURRENT_HUE_AND_CURRENT_SATURATION = 0x00U, /*!< CurrentHueAndCurrentSaturation */
    EZB_ZCL_COLOR_CONTROL_ENHANCED_COLOR_MODE_CURRENT_X_AND_CURRENT_Y            = 0x01U, /*!< CurrentXAndCurrentY */
    EZB_ZCL_COLOR_CONTROL_ENHANCED_COLOR_MODE_COLOR_TEMPERATURE_MIREDS           = 0x02U, /*!< ColorTemperatureMireds */
    EZB_ZCL_COLOR_CONTROL_ENHANCED_COLOR_MODE_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION =
        0x03U, /*!< EnhancedCurrentHueAndCurrentSaturation */
} ezb_zcl_color_control_server_enhanced_color_mode_t;

/**
 * @brief Enumeration for ZCL ColorLoopActive attribute of ColorControl.
 */
typedef enum {
    EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_ACTIVE_COLOR_LOOP_INACTIVE = 0x00U, /*!< ColorLoopInactive */
    EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_ACTIVE_COLOR_LOOP_ACTIVE   = 0x01U, /*!< ColorLoopActive */
} ezb_zcl_color_control_server_color_loop_active_t;

/**
 * @brief Bitmap for ZCL ColorCapabilities attribute of ColorControl.
 */
typedef enum {
    EZB_ZCL_COLOR_CONTROL_COLOR_CAPABILITIES_HUE_SATURATION_SUPPORTED    = 0x0001U, /*!< HueSaturationSupported */
    EZB_ZCL_COLOR_CONTROL_COLOR_CAPABILITIES_ENHANCED_HUE_SUPPORTED      = 0x0002U, /*!< EnhancedHueSupported */
    EZB_ZCL_COLOR_CONTROL_COLOR_CAPABILITIES_COLOR_LOOP_SUPPORTED        = 0x0004U, /*!< ColorLoopSupported */
    EZB_ZCL_COLOR_CONTROL_COLOR_CAPABILITIES_XY_SUPPORTED                = 0x0008U, /*!< XYSupported */
    EZB_ZCL_COLOR_CONTROL_COLOR_CAPABILITIES_COLOR_TEMPERATURE_SUPPORTED = 0x0010U, /*!< ColorTemperatureSupported */
} ezb_zcl_color_control_server_color_capabilities_t;

/** @brief Default value of CurrentHue in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_CURRENT_HUE_DEFAULT_VALUE (0x00)

/** @brief Minimum value of CurrentHue in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_CURRENT_HUE_MIN_VALUE (0x00)

/** @brief Maximum value of CurrentHue in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_CURRENT_HUE_MAX_VALUE (0xfe)
/** @brief Default value of CurrentSaturation in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_CURRENT_SATURATION_DEFAULT_VALUE (0x00)

/** @brief Minimum value of CurrentSaturation in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_CURRENT_SATURATION_MIN_VALUE (0x00)

/** @brief Maximum value of CurrentSaturation in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_CURRENT_SATURATION_MAX_VALUE (0xfe)
/** @brief Default value of RemainingTime in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_REMAINING_TIME_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of RemainingTime in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_REMAINING_TIME_MIN_VALUE (0x0000)

/** @brief Maximum value of RemainingTime in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_REMAINING_TIME_MAX_VALUE (0xfffe)
/** @brief Default value of CurrentX in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_CURRENT_X_DEFAULT_VALUE (0x616b)

/** @brief Minimum value of CurrentX in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_CURRENT_X_MIN_VALUE (0x0000)

/** @brief Maximum value of CurrentX in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_CURRENT_X_MAX_VALUE (0xfeff)
/** @brief Default value of CurrentY in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_CURRENT_Y_DEFAULT_VALUE (0x607d)

/** @brief Minimum value of CurrentY in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_CURRENT_Y_MIN_VALUE (0x0000)

/** @brief Maximum value of CurrentY in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_CURRENT_Y_MAX_VALUE (0xfeff)

/** @brief Minimum value of DriftCompensation in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_DRIFT_COMPENSATION_MIN_VALUE (0x00)

/** @brief Maximum value of DriftCompensation in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_DRIFT_COMPENSATION_MAX_VALUE (0x04)

/** @brief Default value of ColorTemperatureMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_TEMPERATURE_MIREDS_DEFAULT_VALUE (0xfa)

/** @brief Minimum value of ColorTemperatureMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_TEMPERATURE_MIREDS_MIN_VALUE (0x00)

/** @brief Maximum value of ColorTemperatureMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_TEMPERATURE_MIREDS_MAX_VALUE (0xfeff)
/** @brief Default value of ColorMode in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_MODE_DEFAULT_VALUE (0x01)

/** @brief Minimum value of ColorMode in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_MODE_MIN_VALUE (0x00)

/** @brief Maximum value of ColorMode in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_MODE_MAX_VALUE (0x02)
/** @brief Default value of Options in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_OPTIONS_DEFAULT_VALUE (0x00)

/** @brief Default value of EnhancedCurrentHue in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_ENHANCED_CURRENT_HUE_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of EnhancedCurrentHue in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_ENHANCED_CURRENT_HUE_MIN_VALUE (0x0000)

/** @brief Maximum value of EnhancedCurrentHue in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_ENHANCED_CURRENT_HUE_MAX_VALUE (0xffff)
/** @brief Default value of EnhancedColorMode in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_ENHANCED_COLOR_MODE_DEFAULT_VALUE (0x01)

/** @brief Minimum value of EnhancedColorMode in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_ENHANCED_COLOR_MODE_MIN_VALUE (0x00)

/** @brief Maximum value of EnhancedColorMode in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_ENHANCED_COLOR_MODE_MAX_VALUE (0xff)
/** @brief Default value of ColorLoopActive in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_ACTIVE_DEFAULT_VALUE (0x00)

/** @brief Minimum value of ColorLoopActive in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_ACTIVE_MIN_VALUE (0x00)

/** @brief Maximum value of ColorLoopActive in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_ACTIVE_MAX_VALUE (0xff)
/** @brief Default value of ColorLoopDirection in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_DIRECTION_DEFAULT_VALUE (0x00)

/** @brief Minimum value of ColorLoopDirection in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_DIRECTION_MIN_VALUE (0x00)

/** @brief Maximum value of ColorLoopDirection in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_DIRECTION_MAX_VALUE (0xff)
/** @brief Default value of ColorLoopTime in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_TIME_DEFAULT_VALUE (0x0019)

/** @brief Minimum value of ColorLoopTime in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_TIME_MIN_VALUE (0x0000)

/** @brief Maximum value of ColorLoopTime in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_TIME_MAX_VALUE (0xffff)
/** @brief Default value of ColorLoopStartEnhancedHue in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_START_ENHANCED_HUE_DEFAULT_VALUE (0x2300)

/** @brief Minimum value of ColorLoopStartEnhancedHue in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_START_ENHANCED_HUE_MIN_VALUE (0x0000)

/** @brief Maximum value of ColorLoopStartEnhancedHue in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_START_ENHANCED_HUE_MAX_VALUE (0xffff)
/** @brief Default value of ColorLoopStoredEnhancedHue in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_STORED_ENHANCED_HUE_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of ColorLoopStoredEnhancedHue in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_STORED_ENHANCED_HUE_MIN_VALUE (0x0000)

/** @brief Maximum value of ColorLoopStoredEnhancedHue in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_LOOP_STORED_ENHANCED_HUE_MAX_VALUE (0xffff)
/** @brief Default value of ColorCapabilities in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_CAPABILITIES_DEFAULT_VALUE (0x0008)

/** @brief Minimum value of ColorCapabilities in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_CAPABILITIES_MIN_VALUE (0x0000)

/** @brief Maximum value of ColorCapabilities in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_CAPABILITIES_MAX_VALUE (0x001f)
/** @brief Default value of ColorTempPhysicalMinMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_TEMP_PHYSICAL_MIN_MIREDS_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of ColorTempPhysicalMinMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_TEMP_PHYSICAL_MIN_MIREDS_MIN_VALUE (0x0000)

/** @brief Maximum value of ColorTempPhysicalMinMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_TEMP_PHYSICAL_MIN_MIREDS_MAX_VALUE (0xfeff)
/** @brief Default value of ColorTempPhysicalMaxMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_TEMP_PHYSICAL_MAX_MIREDS_DEFAULT_VALUE (0xfeff)

/** @brief Minimum value of ColorTempPhysicalMaxMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_TEMP_PHYSICAL_MAX_MIREDS_MIN_VALUE (0x0000)

/** @brief Maximum value of ColorTempPhysicalMaxMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_TEMP_PHYSICAL_MAX_MIREDS_MAX_VALUE (0xfeff)

/** @brief Minimum value of CoupleColorTempToLevelMinMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COUPLE_COLOR_TEMP_TO_LEVEL_MIN_MIREDS_MIN_VALUE (ColorTempPhysicalMinMireds)

/** @brief Maximum value of CoupleColorTempToLevelMinMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COUPLE_COLOR_TEMP_TO_LEVEL_MIN_MIREDS_MAX_VALUE (𝐶𝑜𝑙𝑜𝑟𝑇𝑒𝑚𝑝𝑒𝑟𝑎𝑡𝑢𝑟𝑒𝑀𝑖𝑟𝑒𝑑)

/** @brief Minimum value of StartUpColorTemperatureMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_START_UP_COLOR_TEMPERATURE_MIREDS_MIN_VALUE (0x0000)

/** @brief Maximum value of StartUpColorTemperatureMireds in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_START_UP_COLOR_TEMPERATURE_MIREDS_MAX_VALUE (0xfeff)

/** @brief Minimum value of NumberOfPrimaries in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_NUMBER_OF_PRIMARIES_MIN_VALUE (0x00)

/** @brief Maximum value of NumberOfPrimaries in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_NUMBER_OF_PRIMARIES_MAX_VALUE (0x06)

/** @brief Minimum value of Primary1X in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY1_X_MIN_VALUE (0x0000)

/** @brief Maximum value of Primary1X in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY1_X_MAX_VALUE (0xfeff)

/** @brief Minimum value of Primary1Y in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY1_Y_MIN_VALUE (0x0000)

/** @brief Maximum value of Primary1Y in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY1_Y_MAX_VALUE (0xfeff)

/** @brief Minimum value of Primary1Intensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY1_INTENSITY_MIN_VALUE (0x00)

/** @brief Maximum value of Primary1Intensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY1_INTENSITY_MAX_VALUE (0xff)

/** @brief Minimum value of Primary2X in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY2_X_MIN_VALUE (0x0000)

/** @brief Maximum value of Primary2X in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY2_X_MAX_VALUE (0xfeff)

/** @brief Minimum value of Primary2Y in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY2_Y_MIN_VALUE (0x0000)

/** @brief Maximum value of Primary2Y in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY2_Y_MAX_VALUE (0xfeff)

/** @brief Minimum value of Primary2Intensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY2_INTENSITY_MIN_VALUE (0x00)

/** @brief Maximum value of Primary2Intensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY2_INTENSITY_MAX_VALUE (0xff)

/** @brief Minimum value of Primary3X in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY3_X_MIN_VALUE (0x0000)

/** @brief Maximum value of Primary3X in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY3_X_MAX_VALUE (0xfeff)

/** @brief Minimum value of Primary3Y in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY3_Y_MIN_VALUE (0x0000)

/** @brief Maximum value of Primary3Y in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY3_Y_MAX_VALUE (0xfeff)

/** @brief Minimum value of Primary3Intensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY3_INTENSITY_MIN_VALUE (0x00)

/** @brief Maximum value of Primary3Intensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY3_INTENSITY_MAX_VALUE (0xff)

/** @brief Minimum value of Primary4X in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY4_X_MIN_VALUE (0x0000)

/** @brief Maximum value of Primary4X in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY4_X_MAX_VALUE (0xfeff)

/** @brief Minimum value of Primary4Y in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY4_Y_MIN_VALUE (0x0000)

/** @brief Maximum value of Primary4Y in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY4_Y_MAX_VALUE (0xfeff)

/** @brief Minimum value of Primary4Intensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY4_INTENSITY_MIN_VALUE (0x00)

/** @brief Maximum value of Primary4Intensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY4_INTENSITY_MAX_VALUE (0xff)

/** @brief Minimum value of Primary5X in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY5_X_MIN_VALUE (0x0000)

/** @brief Maximum value of Primary5X in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY5_X_MAX_VALUE (0xfeff)

/** @brief Minimum value of Primary5Y in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY5_Y_MIN_VALUE (0x0000)

/** @brief Maximum value of Primary5Y in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY5_Y_MAX_VALUE (0xfeff)

/** @brief Minimum value of Primary5Intensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY5_INTENSITY_MIN_VALUE (0x00)

/** @brief Maximum value of Primary5Intensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY5_INTENSITY_MAX_VALUE (0xff)

/** @brief Minimum value of Primary6X in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY6_X_MIN_VALUE (0x0000)

/** @brief Maximum value of Primary6X in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY6_X_MAX_VALUE (0xfeff)

/** @brief Minimum value of Primary6Y in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY6_Y_MIN_VALUE (0x0000)

/** @brief Maximum value of Primary6Y in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY6_Y_MAX_VALUE (0xfeff)

/** @brief Minimum value of Primary6Intensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY6_INTENSITY_MIN_VALUE (0x00)

/** @brief Maximum value of Primary6Intensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_PRIMARY6_INTENSITY_MAX_VALUE (0xff)
/** @brief Default value of WhitePointX in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_WHITE_POINT_X_DEFAULT_VALUE (0x00)

/** @brief Minimum value of WhitePointX in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_WHITE_POINT_X_MIN_VALUE (0x0000)

/** @brief Maximum value of WhitePointX in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_WHITE_POINT_X_MAX_VALUE (0xfeff)

/** @brief Minimum value of WhitePointY in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_WHITE_POINT_Y_MIN_VALUE (0x0000)

/** @brief Maximum value of WhitePointY in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_WHITE_POINT_Y_MAX_VALUE (0xfeff)

/** @brief Minimum value of ColorPointRX in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_RX_MIN_VALUE (0x0000)

/** @brief Maximum value of ColorPointRX in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_RX_MAX_VALUE (0xfeff)

/** @brief Minimum value of ColorPointRY in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_RY_MIN_VALUE (0x0000)

/** @brief Maximum value of ColorPointRY in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_RY_MAX_VALUE (0xfeff)

/** @brief Minimum value of ColorPointRIntensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_R_INTENSITY_MIN_VALUE (0x00)

/** @brief Maximum value of ColorPointRIntensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_R_INTENSITY_MAX_VALUE (0xff)

/** @brief Minimum value of ColorPointGX in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_GX_MIN_VALUE (0x0000)

/** @brief Maximum value of ColorPointGX in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_GX_MAX_VALUE (0xfeff)

/** @brief Minimum value of ColorPointGY in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_GY_MIN_VALUE (0x0000)

/** @brief Maximum value of ColorPointGY in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_GY_MAX_VALUE (0xfeff)

/** @brief Minimum value of ColorPointGIntensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_G_INTENSITY_MIN_VALUE (0x00)

/** @brief Maximum value of ColorPointGIntensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_G_INTENSITY_MAX_VALUE (0xff)

/** @brief Minimum value of ColorPointBX in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_BX_MIN_VALUE (0x0000)

/** @brief Maximum value of ColorPointBX in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_BX_MAX_VALUE (0xfeff)

/** @brief Minimum value of ColorPointBY in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_BY_MIN_VALUE (0x0000)

/** @brief Maximum value of ColorPointBY in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_BY_MAX_VALUE (0xfeff)

/** @brief Minimum value of ColorPointBIntensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_B_INTENSITY_MIN_VALUE (0x00)

/** @brief Maximum value of ColorPointBIntensity in ColorControl cluster */
#define EZB_ZCL_COLOR_CONTROL_COLOR_POINT_B_INTENSITY_MAX_VALUE (0xff)

/**
 * @brief Received Command identifiers for the ColorControl cluster.
 */
typedef enum {
    EZB_ZCL_CMD_COLOR_CONTROL_MOVE_TO_HUE_ID                         = 0x00U, /*!< MoveToHue command. */
    EZB_ZCL_CMD_COLOR_CONTROL_MOVE_HUE_ID                            = 0x01U, /*!< MoveHue command. */
    EZB_ZCL_CMD_COLOR_CONTROL_STEP_HUE_ID                            = 0x02U, /*!< StepHue command. */
    EZB_ZCL_CMD_COLOR_CONTROL_MOVE_TO_SATURATION_ID                  = 0x03U, /*!< MoveToSaturation command. */
    EZB_ZCL_CMD_COLOR_CONTROL_MOVE_SATURATION_ID                     = 0x04U, /*!< MoveSaturation command. */
    EZB_ZCL_CMD_COLOR_CONTROL_STEP_SATURATION_ID                     = 0x05U, /*!< StepSaturation command. */
    EZB_ZCL_CMD_COLOR_CONTROL_MOVE_TO_HUE_AND_SATURATION_ID          = 0x06U, /*!< MoveToHueAndSaturation command. */
    EZB_ZCL_CMD_COLOR_CONTROL_MOVE_TO_COLOR_ID                       = 0x07U, /*!< MoveToColor command. */
    EZB_ZCL_CMD_COLOR_CONTROL_MOVE_COLOR_ID                          = 0x08U, /*!< MoveColor command. */
    EZB_ZCL_CMD_COLOR_CONTROL_STEP_COLOR_ID                          = 0x09U, /*!< StepColor command. */
    EZB_ZCL_CMD_COLOR_CONTROL_MOVE_TO_COLOR_TEMPERATURE_ID           = 0x0AU, /*!< MoveToColorTemperature command. */
    EZB_ZCL_CMD_COLOR_CONTROL_ENHANCED_MOVE_TO_HUE_ID                = 0x40U, /*!< EnhancedMoveToHue command. */
    EZB_ZCL_CMD_COLOR_CONTROL_ENHANCED_MOVE_HUE_ID                   = 0x41U, /*!< EnhancedMoveHue command. */
    EZB_ZCL_CMD_COLOR_CONTROL_ENHANCED_STEP_HUE_ID                   = 0x42U, /*!< EnhancedStepHue command. */
    EZB_ZCL_CMD_COLOR_CONTROL_ENHANCED_MOVE_TO_HUE_AND_SATURATION_ID = 0x43U, /*!< EnhancedMoveToHueAndSaturation command. */
    EZB_ZCL_CMD_COLOR_CONTROL_COLOR_LOOP_SET_ID                      = 0x44U, /*!< ColorLoopSet command. */
    EZB_ZCL_CMD_COLOR_CONTROL_STOP_MOVE_STEP_ID                      = 0x47U, /*!< StopMoveStep command. */
    EZB_ZCL_CMD_COLOR_CONTROL_MOVE_COLOR_TEMPERATURE_ID              = 0x4BU, /*!< MoveColorTemperature command. */
    EZB_ZCL_CMD_COLOR_CONTROL_STEP_COLOR_TEMPERATURE_ID              = 0x4CU, /*!< StepColorTemperature command. */
} ezb_zcl_color_control_server_cmd_id_t;

typedef ezb_zcl_color_control_cluster_server_config_t ezb_zcl_color_control_cluster_config_t;

/**
 * @brief Add an attribute to an color_control cluster descriptor.
 *
 * @param cluster_desc Pointer to the color_control cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_color_control_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an color_control cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the color_control cluster configuration structure, refer to
 * ezb_zcl_color_control_cluster_server_config_t or ezb_zcl_color_control_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_color_control_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the ColorControl cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_color_control_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the ColorControl cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_color_control_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_COLOR_CONTROL_CLIENT_ROLE_INIT ezb_zcl_color_control_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_COLOR_CONTROL_SERVER_ROLE_INIT ezb_zcl_color_control_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
