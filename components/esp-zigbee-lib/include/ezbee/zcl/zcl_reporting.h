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
 * @param[in] ep_id      The identifier of the endpoint to which the reporting information belongs.
 * @param[in] cluster_id The identifier of the cluster to which the reporting information belongs.
 * @param[in] role       The role of the cluster to which the reporting information belongs.
 * @param[in] attr_id    The identifier of the attribute to which the reporting information belongs.
 * @param[in] manuf_code The manufacturer code to which the reporting information belongs.
 *
 * @return The handle of the matching reporting information. EZB_ZCL_INVALID_REPORTING_INFO if not found.
 */
ezb_zcl_reporting_info_t ezb_zcl_reporting_info_find(uint8_t  ep_id,
                                                     uint16_t cluster_id,
                                                     uint8_t  role,
                                                     uint16_t attr_id,
                                                     uint16_t manuf_code);

/**
 * @brief Start ZCL attribute reporting.
 *
 * @param[in] info The handle of the reporting information.
 * @return The error code. See @ref ezb_err_t.
 */
ezb_err_t ezb_zcl_reporting_start_attr_report(ezb_zcl_reporting_info_t info);

/**
 * @brief Stop ZCL attribute reporting.
 *
 * @param[in] info The handle of the reporting information.
 * @return The error code. See @ref ezb_err_t.
 */
ezb_err_t ezb_zcl_reporting_stop_attr_report(ezb_zcl_reporting_info_t info);

/**
 * @brief Update ZCL attribute reporting.
 *
 * @param[in] info         Handle of the reporting information.
 * @param[in] min_interval Minimum reporting interval in seconds.
 * @param[in] max_interval Maximum reporting interval in seconds.
 * @param[in] delta        Reportable change value.
 * @return The error code. See @ref ezb_err_t.
 */
ezb_err_t ezb_zcl_reporting_info_update(ezb_zcl_reporting_info_t       info,
                                        uint16_t                       min_interval,
                                        uint16_t                       max_interval,
                                        const ezb_zcl_attr_variable_t *delta);

/**
 * @brief Update ZCL attribute reporting default interval.
 *
 * @param[in] info             Handle of the reporting information.
 * @param[in] def_min_interval Default minimum reporting interval in seconds.
 * @param[in] def_max_interval Default maximum reporting interval in seconds.
 * @return The error code. See @ref ezb_err_t.
 */
ezb_err_t ezb_zcl_reporting_info_update_default_interval(ezb_zcl_reporting_info_t info,
                                                         uint16_t                 def_min_interval,
                                                         uint16_t                 def_max_interval);

/**
 * @brief Remove ZCL attribute reporting.
 *
 * @param[in] info The handle of the reporting information.
 * @return The error code. See @ref ezb_err_t.
 */
ezb_err_t ezb_zcl_reporting_info_remove(ezb_zcl_reporting_info_t info);

#ifdef __cplusplus
} /*  extern "C" */
#endif
