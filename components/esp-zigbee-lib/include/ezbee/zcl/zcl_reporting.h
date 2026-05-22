/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/zcl_common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EZB_ZCL_MIN_REPORTING_INTERVAL_DEFAULT 0x0005U /**< Default minimum reporting interval (in seconds). */
#define EZB_ZCL_MAX_REPORTING_INTERVAL_DEFAULT 0x0000U /**< Default maximum reporting interval (0 means disabled). */

/**
 * @brief Handle for reporting information.
 */
typedef void *ezb_zcl_reporting_info_t;

#define EZB_ZCL_INVALID_REPORTING_INFO NULL

/**
 * @brief Find ZCL reporting information.
 *
 * @param ep_id Endpoint ID to which the reporting information belongs.
 * @param cluster_id Cluster ID used to match the reporting information.
 * @param role Cluster role used to match the reporting information.
 * @param attr_id Attribute ID used to match the reporting information.
 * @param manuf_code Manufacturer code used to match the reporting information.
 *
 * @return Matching reporting information handle. EZB_ZCL_INVALID_REPORTING_INFO if not found.
 */
ezb_zcl_reporting_info_t ezb_zcl_reporting_info_find(uint8_t  ep_id,
                                                     uint16_t cluster_id,
                                                     uint8_t  role,
                                                     uint16_t attr_id,
                                                     uint16_t manuf_code);

/**
 * @brief Start ZCL attribute reporting.
 *
 * @param info The handle of the reporting information.
 * @return ezb_err_t Error code.
 */
ezb_err_t ezb_zcl_reporting_start_attr_report(ezb_zcl_reporting_info_t info);

/**
 * @brief Stop ZCL attribute reporting.
 *
 * @param info The handle of the reporting information.
 * @return ezb_err_t Error code.
 */
ezb_err_t ezb_zcl_reporting_stop_attr_report(ezb_zcl_reporting_info_t info);

/**
 * @brief Update ZCL attribute reporting.
 *
 * @param info The handle of the reporting information.
 * @param min_interval Minimum reporting interval is set to (in seconds).
 * @param max_interval Maximum reporting interval is set to (in seconds).
 * @param delta Reportable change is set to.
 * @return ezb_err_t Error code.
 */
ezb_err_t ezb_zcl_reporting_info_update(ezb_zcl_reporting_info_t       info,
                                        uint16_t                       min_interval,
                                        uint16_t                       max_interval,
                                        const ezb_zcl_attr_variable_t *delta);

/**
 * @brief Update ZCL attribute reporting default interval.
 *
 * @param info The handle of the reporting information.
 * @param def_min_interval Default minimum reporting interval is set to (in seconds).
 * @param def_max_interval Default maximum reporting interval is set to (in seconds).
 * @return ezb_err_t Error code.
 */
ezb_err_t ezb_zcl_reporting_info_update_default_interval(ezb_zcl_reporting_info_t info,
                                                         uint16_t                 def_min_interval,
                                                         uint16_t                 def_max_interval);

/**
 * @brief Remove ZCL attribute reporting.
 *
 * @param info The handle of the reporting information.
 * @return ezb_err_t Error code.
 */
ezb_err_t ezb_zcl_reporting_info_remove(ezb_zcl_reporting_info_t info);

#ifdef __cplusplus
} /*  extern "C" */
#endif
