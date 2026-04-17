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

typedef void *ezb_zcl_reporting_info_t;

ezb_zcl_reporting_info_t ezb_zcl_reporting_info_find(uint8_t  ep_id,
                                                     uint16_t cluster_id,
                                                     uint8_t  role,
                                                     uint16_t attr_id,
                                                     uint16_t manuf_code);

ezb_err_t ezb_zcl_reporting_start_attr_report(ezb_zcl_reporting_info_t info);

ezb_err_t ezb_zcl_reporting_stop_attr_report(ezb_zcl_reporting_info_t info);

ezb_err_t ezb_zcl_reporting_info_update(ezb_zcl_reporting_info_t       info,
                                        uint16_t                       min_interval,
                                        uint16_t                       max_interval,
                                        const ezb_zcl_attr_variable_t *delta);

ezb_err_t ezb_zcl_reporting_info_remove(ezb_zcl_reporting_info_t info);

#ifdef __cplusplus
} /*  extern "C" */
#endif
