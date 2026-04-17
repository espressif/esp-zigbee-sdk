/*
 * SPDX-FileCopyrightText: 2024-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "ezbee/af.h"
#include "ezbee/zcl.h"

#ifdef __cplusplus
extern "C" {
#endif

const char *ezb_get_cluster_name_by_idx(uint16_t idx);

const char *ezb_get_cluster_name_by_id(uint16_t cluster_id);

uint16_t ezb_get_cluster_id_by_name(const char *name);

ezb_zcl_cluster_desc_t ezb_cluster_desc_create_default(uint16_t cluster_id, uint8_t role_mask);

ezb_err_t ezb_cluster_desc_add_std_attr(uint16_t               cluster_id,
                                        ezb_zcl_cluster_desc_t cluster_desc,
                                        uint16_t                attr_id,
                                        void                   *value_p);

ezb_err_t ezb_cluster_desc_register(ezb_af_ep_desc_t       ep_desc,
                                    uint16_t               cluster_id,
                                    ezb_zcl_cluster_desc_t cluster_desc,
                                    uint8_t                role_mask);

#ifdef __cplusplus
}
#endif
