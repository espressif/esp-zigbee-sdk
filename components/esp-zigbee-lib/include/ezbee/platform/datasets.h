/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifndef ESP_ZIGBEE_PLATFORM_DATASETS_H
#define ESP_ZIGBEE_PLATFORM_DATASETS_H

#include <stdint.h>
#include <ezbee/error.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Defines the keys of datasets */
enum {
    EZB_DATASETS_KEY_COMMON_DATA    = 0x0001, /*!< Operational common data */

    /* 0x0002 Reserved */

    EZB_DATASETS_KEY_PARENT_INFO    = 0x0003, /*!< Parent information. */
    EZB_DATASETS_KEY_CHILD_INFO     = 0x0004, /*!< Child information. */
    EZB_DATASETS_KEY_GROUP_INFO     = 0x0005, /*!< Group information. */
    EZB_DATASETS_KEY_BIND_INFO      = 0x0006, /*!< Binding information. */
    EZB_DATASETS_KEY_IC_INFO        = 0x0007, /*!< Install code. */
    EZB_DATASETS_KEY_NIB_CNTR       = 0x0008, /*!< NIB counter. */
    EZB_DATASETS_KEY_APS_KEY_PAIR   = 0x0009, /*!< APS Device key pair. */
    EZB_DATASETS_KEY_ZCL_REPORTING_INFO = 0x000A, /*!< ZCL Reporting information. */
    EZB_DATASETS_KEY_ZCL_SCENE_INFO     = 0x000B, /*!< ZCL Scene information. */
    EZB_DATASETS_KEY_ALARM_LOG          = 0x000C, /*!< ZCL Alarms cluster alarm log. */
    EZB_DATASETS_KEY_IAS_ZONE_INFO      = 0x000D, /*!< IAS ACE zone table (CIE enrolled zones). */
};

/**
 * @brief Initialize the datasets subsystem, for non-volatile storage.
 */
void ezb_plat_datasets_init(void);

/**
 * @brief De-initialize the datasets subsystem.
 */
void ezb_plat_datasets_deinit(void);

/**
 * @brief Fetch the value of a dataset.
 *
 * @param[in]    key    The key associated with the requested dataset.
 * @param[in]    index  The index of the specific item to get.
 * @param[out]   value  A pointer to where the value of the dataset should be written. May be set to NULL if
 *                      just testing for the presence or length of a dataset.
 * @param[inout] length A pointer to the length of the value. This will be overwritten by the actual length of
 *                      data that writes to @p value
 *
 * @retval EZB_ERR_NONE             The given dataset was found and fetched successfully.
 * @retval EZB_ERR_NOT_FOUND        The given dataset was not found in the dataset storage.
 * @retval EZB_ERR_NOT_SUPPORTED    This function is not implemented on this platform.
 */
ezb_err_t ezb_plat_datasets_get(uint16_t key, int index, uint8_t *value, uint16_t *length);

/**
 * @brief Set or replace the value of a dataset.
 *
 * @param[in] key       The key associated with the requested dataset.
 * @param[in] value     A pointer to where the new value of the dataset should be read from.
 *                      MUST NOT be NULL if @p length is non-zero.
 * @param[in] length    The length of the data pointed to by aValue. May be zero.
 *
 * @retval EZB_ERR_NONE             The given dataset was changed or staged.
 * @retval EZB_ERR_NO_MEM           No space remaining to store the given dataset.
 * @retval EZB_ERR_NOT_SUPPORTED    This function is not implemented on this platform.
 */
ezb_err_t ezb_plat_datasets_set(uint16_t key, const uint8_t *value, uint16_t length);

/**
 * @brief Add a value to a dataset.
 *
 * Adds the value to a dataset identified by @p aKey, without replacing any existing values.
 *
 * @param[in] key    The key associated with the dataset to change.
 * @param[in] value  A pointer to where the new value of the dataset should be read from. MUST NOT be NULL
 *                   if @p aValueLength is non-zero.
 * @param[in] length The length of the data pointed to by @p aValue. May be zero.
 *
 * @retval EZB_ERR_NONE             The given dataset was changed or staged.
 * @retval EZB_ERR_NO_MEM           No space remaining to store the given dataset.
 * @retval EZB_ERR_NOT_SUPPORTED    This function is not implemented on this platform.
 */
ezb_err_t ezb_plat_datasets_add(uint16_t key, const uint8_t *value, uint16_t length);

/**
 * @brief Removes a dataset from the dataset storage.
 *
 * Deletes a specific value from the dataset identified by @p key from the datasets store.
 *
 * @param[in] key   The key associated with the requested dataset.
 * @param[in] index The index of the value to be removed.
 *                  If set to -1, all values for this @p key will be removed.
 *
 * @retval EZB_ERR_NONE             The given dataset was found and fetched successfully.
 * @retval EZB_ERR_NOT_FOUND        The given dataset was not found in the dataset storage.
 * @retval EZB_ERR_NOT_SUPPORTED    This function is not implemented on this platform.
 */
ezb_err_t ezb_plat_datasets_delete(uint16_t key, int index);

/**
 * @brief Removes all datasets from the dataset storage.
 *
 */
void ezb_plat_datasets_wipe(void);

#ifdef __cplusplus
} /*  extern "C" */
#endif

#endif /* ESP_ZIGBEE_PLATFORM_DATASETS_H */
