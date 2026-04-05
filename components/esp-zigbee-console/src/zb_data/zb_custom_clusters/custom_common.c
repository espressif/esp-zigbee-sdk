/*
 * SPDX-FileCopyrightText: 2025-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "custom_common.h"

#include "cli_util.h"
#include "ping_iperf_test.h"

#define TAG "custom_common"

ezb_af_ep_desc_t ezb_zha_create_custom_test_tool(uint8_t ep_id, void *cfg)
{
    ezb_ping_iperf_test_cluster_config_t *ping_iperf_cfg = (ezb_ping_iperf_test_cluster_config_t *)cfg;
    ezb_af_ep_config_t                    ep_config      = {
        .ep_id              = ep_id,
        .app_profile_id     = EZB_AF_HA_PROFILE_ID,
        .app_device_id      = EZB_ZHA_CUSTOM_TEST_TOOL_DEVICE_ID,
        .app_device_version = 0,
    };
    ezb_af_ep_desc_t ep_desc = ezb_af_create_endpoint_desc(&ep_config);
    ezb_af_endpoint_add_cluster_desc(ep_desc,
                                     ezb_zcl_ping_iperf_test_create_cluster_desc(ping_iperf_cfg, EZB_ZCL_CLUSTER_SERVER));
    ezb_af_endpoint_add_cluster_desc(ep_desc,
                                     ezb_zcl_ping_iperf_test_create_cluster_desc(ping_iperf_cfg, EZB_ZCL_CLUSTER_CLIENT));
    return ep_desc;
}
