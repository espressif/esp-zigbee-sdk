/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_TASKLET_H
#define ESP_ZIGBEE_TASKLET_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Process all queued tasklets.
 *
 */
void ezb_tasklet_process(void);

/**
 * @brief Check whether there is pending tasklet.
 *
 * @return TRUE  If there are pending tasklets.
 * @return FALSE If there are not pending tasklets.
 */
bool ezb_tasklet_has_pendings(void);

/**
 * @brief Called by Stack when the tasklet queue transitions from empty to non-empty.
 *        Implement this function to get notification when there are tasklets added.
 *
 */
extern void ezb_tasklet_signal_pending(void);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_TASKLET_H */
