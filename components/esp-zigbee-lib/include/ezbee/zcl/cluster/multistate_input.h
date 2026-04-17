/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/multistate_input_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

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

 /**
  * @brief Macros for Group ID of ZCL Multistate Input
  */
#define EZB_ZCL_MI_GROUP_ID 0x0D

/**
 * @brief Macros for ApplicationType attribute of ZCL Multistate Input
 */
#define EZB_ZCL_MI_SET_APP_TYPE_WITH_ID(_type, _id) (((EZB_ZCL_MI_GROUP_ID & 0xFF) << 24) | (((_type)&0xFF) << 16) | ((_id)&0xFFFF))

/** @brief Values for Multistate Input cluster HVAC application usages */
typedef enum {
    EZB_ZCL_MI_DOMAIN_HVAC_OFF_ON_AUTO =
        EZB_ZCL_MI_SET_APP_TYPE_WITH_ID(EZB_ZCL_MULTISTATE_INPUT_APPLICATION_TYPE_APP_DOMAIN_HVAC, 0x0000),   /*!< Off, On, Auto */
    EZB_ZCL_MI_DOMAIN_HVAC_OFF_LOW_MEDIUM_HIGH,                                                               /*!< Off, Low, Medium, High */
    EZB_ZCL_MI_DOMAIN_HVAC_AUTO_HEAT_COOL_OFF_EMERGENCY_FAN_MAX,                                              /*!< Auto, Heat, Cool, Off, Emergency Heat, Fan Only,
                                                                                                                   Max Heat */
    EZB_ZCL_MI_DOMAIN_HVAC_OCCUPIED_UNOCCUPIED_STANDBY_BYPASS,                                                /*!< Occupied, Unoccupied, Standby, Bypass */
    EZB_ZCL_MI_DOMAIN_HVAC_INACTIVE_ACTIVE_HOLD,                                                              /*!< Inactive, Active, Hold */
    EZB_ZCL_MI_DOMAIN_HVAC_AUTO_WARMUP_WATER_FLUSH_AUTOCAL_SHUTDOWNOPEN_SHUTDOWNCLOSED_LOWLIMIT_TEST_BALANCE, /*!< Auto, Warm-up, Water Flush, Autocalibration, Shutdown Open,
                                                                                                                   Shutdown Closed, Low Limit, Test and Balance */
    EZB_ZCL_MI_DOMAIN_HVAC_OFF_AUTO_HEAT_COOL_HEATONLY_COOLONLY_FAN_ONLY,                                     /*!< Off, Auto, Heat Cool, Heat Only, Cool Only, Fan Only */
    EZB_ZCL_MI_DOMAIN_HVAC_HIGH_NORMAL_LOW,                                                                   /*!< High, Normal, Low */
    EZB_ZCL_MI_DOMAIN_HVAC_OCCUPIED_UNOCCUPIED_STARTUP_SHUTDOWN,                                              /*!< Occupied, Unoccupied, Startup, Shutdown */
    EZB_ZCL_MI_DOMAIN_HVAC_NIGHT_DAY_HOLD,                                                                    /*!< Night, Day, Hold */
    EZB_ZCL_MI_DOMAIN_HVAC_OFF_COOL_HEAT_AUTO_EMERGENCY,                                                      /*!< Off, Cool, Heat, Auto, Emergency Heat */
    EZB_ZCL_MI_DOMAIN_HVAC_SHUTDOWNCLOSED_SHUTDOWNOPEN_SATISFIED_MIXING_COOLING_HEATING_SUPPLEMENTAL_HEAT,    /*!< Shutdown Closed, Shutdown Open, Satisfied, Mixing, Cooling,
                                                                                                                   Heating, Supplemental Heat */
    /* 0x0200 to 0xFFFE are Vendor defined */
    EZB_ZCL_MI_DOMAIN_HVAC_OTHER = EZB_ZCL_MI_SET_APP_TYPE_WITH_ID(EZB_ZCL_MULTISTATE_INPUT_APPLICATION_TYPE_APP_DOMAIN_HVAC, 0xFFFF)    /*!< Other */
} ezb_zcl_mi_domain_hvac_t;

#ifdef __cplusplus
} /*  extern "C" */
#endif
