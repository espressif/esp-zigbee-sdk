/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * Zigbee delta OTA Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define DELTA_OTA_UPGRADE_IMAGE_HEADER_SIZE       sizeof(esp_image_header_t)
#define DELTA_OTA_UPGRADE_PATCH_HEADER_SIZE       64
#define DELTA_OTA_UPGRADE_DIGEST_SIZE             32
#define DELTA_OTA_UPGRADE_MAGIC                   0xfccdde10

typedef struct esp_delta_ota_ctx_s {
    char *header_data;
    int  header_data_read;
    bool verify_patch_flag;
    bool chip_id_verified;
} esp_delta_ota_ctx_t;

/**
 * @brief   Commence a Delta OTA update writing to the specified partition.

 * The specified partition is erased to the specified image size.
 *
 * If image size is not yet known, pass OTA_SIZE_UNKNOWN which will
 * cause the entire partition to be erased.
 *
 * On success, this function allocates memory that remains in use
 * until esp_delta_ota_end() is called with the returned handle.
 *
 * Note: If the rollback option is enabled and the running application has the ESP_OTA_IMG_PENDING_VERIFY state then
 * it will lead to the ESP_ERR_OTA_ROLLBACK_INVALID_STATE error. Confirm the running app before to run download a new app,
 * use esp_ota_mark_app_valid_cancel_rollback() function for it (this should be done as early as possible when you first download a new application).
 *
 * @param partition Pointer to info for partition which will receive the OTA update. Required.
 * @param image_size Size of new OTA app image. Partition will be erased in order to receive this size of image. If 0 or OTA_SIZE_UNKNOWN, the entire partition is erased.
 * @param out_handle On success, returns a handle which should be used for subsequent esp_ota_write() and esp_delta_ota_end() calls.

 * @return
 *    - ESP_OK: OTA operation commenced successfully.
 *    - ESP_ERR_INVALID_ARG: partition or out_handle arguments were NULL, or partition doesn't point to an OTA app partition.
 *    - ESP_ERR_NO_MEM: Cannot allocate memory for OTA operation.
 *    - ESP_ERR_OTA_PARTITION_CONFLICT: Partition holds the currently running firmware, cannot update in place.
 *    - ESP_ERR_NOT_FOUND: Partition argument not found in partition table.
 *    - ESP_ERR_OTA_SELECT_INFO_INVALID: The OTA data partition contains invalid data.
 *    - ESP_ERR_INVALID_SIZE: Partition doesn't fit in configured flash size.
 *    - ESP_ERR_FLASH_OP_TIMEOUT or ESP_ERR_FLASH_OP_FAIL: Flash write failed.
 *    - ESP_ERR_OTA_ROLLBACK_INVALID_STATE: If the running app has not confirmed state. Before performing an update, the application must be valid.
 */
esp_err_t esp_delta_ota_begin(const esp_partition_t *partition, size_t image_size, esp_ota_handle_t *out_handle);

/**
 * @brief   Write Delta OTA update data to partition
 *
 * This function can be called multiple times as
 * data is received during the OTA operation. Data is written
 * sequentially to the partition.
 *
 * @param handle  Handle obtained from esp_ota_begin
 * @param data    Data buffer to write
 * @param size    Size of data buffer in bytes.
 *
 * @return
 *    - ESP_OK: Data was written to flash successfully, or size = 0
 *    - ESP_ERR_INVALID_ARG: handle is invalid.
 *    - ESP_ERR_OTA_VALIDATE_FAILED: First byte of image contains invalid app image magic byte.
 *    - ESP_ERR_FLASH_OP_TIMEOUT or ESP_ERR_FLASH_OP_FAIL: Flash write failed.
 *    - ESP_ERR_OTA_SELECT_INFO_INVALID: OTA data partition has invalid contents
 */
esp_err_t esp_delta_ota_write(esp_ota_handle_t handle, uint8_t *data, int size);

/**
 * @brief Finish Delta OTA update and validate newly written app image.
 *
 * @param handle  Handle obtained from esp_delta_ota_begin().
 *
 * @note After calling esp_delta_ota_end(), the handle is no longer valid and any memory associated with it is freed (regardless of result).
 *
 * @return
 *    - ESP_OK: Newly written OTA app image is valid.
 *    - ESP_ERR_NOT_FOUND: OTA handle was not found.
 *    - ESP_ERR_INVALID_ARG: Handle was never written to.
 *    - ESP_ERR_OTA_VALIDATE_FAILED: OTA image is invalid (either not a valid app image, or - if secure boot is enabled - signature failed to verify.)
 *    - ESP_ERR_INVALID_STATE: If flash encryption is enabled, this result indicates an internal error writing the final encrypted bytes to flash.
 */
esp_err_t esp_delta_ota_end(esp_ota_handle_t handle);

#ifdef __cplusplus
}
#endif
