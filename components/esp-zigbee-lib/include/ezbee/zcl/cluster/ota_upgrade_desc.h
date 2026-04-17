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
   OTA_UPGRADE Cluster Properties
 *-----------------------------------------------------------------------------------------------------------------------------*/

/** @brief Cluster Revision of the ota_upgrade cluster implementation */
#define EZB_ZCL_OTA_UPGRADE_CLUSTER_REVISION (4)

/**
 * @brief Attribute identifiers for the ota_upgrade server cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_OTA_UPGRADE_OTA_UPGRADE_FILE_TABLE_SIZE_ID = 0xeff0U, /*!< OTAUpgradeFileTableSize attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_OTA_UPGRADE_FILE_TABLE_ID      = 0xeff1U, /*!< OTAUpgradeFileTable attribute. */
} ezb_zcl_ota_upgrade_server_attr_t;

/**
 * @brief Configuration mandatory attributes for the OTAUpgrade server cluster.
 */
typedef struct ezb_zcl_ota_upgrade_cluster_server_config_s {
    uint8_t ota_upgrade_file_table_size; /*!< Configurable mandatory OTAUpgradeFileTableSize attribute */
} ezb_zcl_ota_upgrade_cluster_server_config_t;

/** @brief Default value of OTAUpgradeFileTableSize in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_OTA_UPGRADE_FILE_TABLE_SIZE_DEFAULT_VALUE (0x01)

/**
 * @brief Received Command identifiers for the OTAUpgrade cluster.
 */
typedef enum {
    EZB_ZCL_CMD_OTA_UPGRADE_QUERY_NEXT_IMAGE_REQUEST_ID           = 0x01U, /*!< QueryNextImageRequest command. */
    EZB_ZCL_CMD_OTA_UPGRADE_IMAGE_BLOCK_REQUEST_ID                = 0x03U, /*!< ImageBlockRequest command. */
    EZB_ZCL_CMD_OTA_UPGRADE_IMAGE_PAGE_REQUEST_ID                 = 0x04U, /*!< ImagePageRequest command. */
    EZB_ZCL_CMD_OTA_UPGRADE_UPGRADE_END_REQUEST_ID                = 0x06U, /*!< UpgradeEndRequest command. */
    EZB_ZCL_CMD_OTA_UPGRADE_QUERY_DEVICE_SPECIFIC_FILE_REQUEST_ID = 0x08U, /*!< QueryDeviceSpecificFileRequest command. */
} ezb_zcl_ota_upgrade_server_cmd_id_t;

/**
 * @brief Attribute identifiers for the ota_upgrade client cluster.
 */
typedef enum {
    EZB_ZCL_ATTR_OTA_UPGRADE_UPGRADE_SERVER_ID_ID               = 0x0000U, /*!< UpgradeServerID attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_FILE_OFFSET_ID                     = 0x0001U, /*!< FileOffset attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_CURRENT_FILE_VERSION_ID            = 0x0002U, /*!< CurrentFileVersion attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_CURRENT_ZIGBEE_STACK_VERSION_ID    = 0x0003U, /*!< CurrentZigbeeStackVersion attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_DOWNLOADED_FILE_VERSION_ID         = 0x0004U, /*!< DownloadedFileVersion attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_DOWNLOADED_ZIGBEE_STACK_VERSION_ID = 0x0005U, /*!< DownloadedZigbeeStackVersion attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_UPGRADE_STATUS_ID            = 0x0006U, /*!< ImageUpgradeStatus attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_MANUFACTURER_ID_ID                 = 0x0007U, /*!< ManufacturerID attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_TYPE_ID_ID                   = 0x0008U, /*!< ImageTypeID attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_MINIMUM_BLOCK_PERIOD_ID            = 0x0009U, /*!< MinimumBlockPeriod attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_STAMP_ID                     = 0x000aU, /*!< ImageStamp attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_UPGRADE_ACTIVATION_POLICY_ID       = 0x000bU, /*!< UpgradeActivationPolicy attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_UPGRADE_TIMEOUT_POLICY_ID          = 0x000cU, /*!< UpgradeTimeoutPolicy attribute. */
    EZB_ZCL_ATTR_OTA_UPGRADE_OTA_UPGRADE_DOWNLOADING_CONTEXT_ID = 0xeff0U, /*!< OTAUpgradeDownloadingContext attribute. */
} ezb_zcl_ota_upgrade_client_attr_t;

/**
 * @brief Configuration mandatory attributes for the OTAUpgrade client cluster.
 */
typedef struct ezb_zcl_ota_upgrade_cluster_client_config_s {
    uint64_t upgrade_server_id;    /*!< Configurable mandatory UpgradeServerID attribute */
    uint32_t file_offset;          /*!< Configurable mandatory FileOffset attribute */
    uint8_t  image_upgrade_status; /*!< Configurable mandatory ImageUpgradeStatus attribute */
    uint16_t manufacturer_id;      /*!< Configurable mandatory ManufacturerID attribute */
    uint16_t image_type_id;        /*!< Configurable mandatory ImageTypeID attribute */
} ezb_zcl_ota_upgrade_cluster_client_config_t;

/**
 * @brief Enumeration for ZCL ImageUpgradeStatus attribute of OTAUpgrade.
 */
typedef enum {
    EZB_ZCL_OTA_UPGRADE_IMAGE_UPGRADE_STATUS_NORMAL               = 0x00U, /*!< Normal */
    EZB_ZCL_OTA_UPGRADE_IMAGE_UPGRADE_STATUS_DOWNLOAD_IN_PROGRESS = 0x01U, /*!< DownloadInProgress */
    EZB_ZCL_OTA_UPGRADE_IMAGE_UPGRADE_STATUS_DOWNLOAD_COMPLETE    = 0x02U, /*!< DownloadComplete */
    EZB_ZCL_OTA_UPGRADE_IMAGE_UPGRADE_STATUS_WAITING_TO_UPGRADE   = 0x03U, /*!< WaitingToUpgrade */
    EZB_ZCL_OTA_UPGRADE_IMAGE_UPGRADE_STATUS_COUNT_DOWN           = 0x04U, /*!< CountDown */
    EZB_ZCL_OTA_UPGRADE_IMAGE_UPGRADE_STATUS_WAIT_FOR_MORE        = 0x05U, /*!< WaitForMore */
    EZB_ZCL_OTA_UPGRADE_IMAGE_UPGRADE_STATUS_WAITING_TO_UPGRADE_VIA_EXTERNAL_EVENT =
        0x06U, /*!< WaitingToUpgradeViaExternalEvent */
} ezb_zcl_ota_upgrade_client_image_upgrade_status_t;

/**
 * @brief Enumeration for ZCL UpgradeActivationPolicy attribute of OTAUpgrade.
 */
typedef enum {
    EZB_ZCL_OTA_UPGRADE_UPGRADE_ACTIVATION_POLICY_OTA_SERVER_ACTIVATION_ALLOWED = 0x00U, /*!< OTAServerActivationAllowed */
    EZB_ZCL_OTA_UPGRADE_UPGRADE_ACTIVATION_POLICY_OUT_OF_BAND_ACTIVATION_ONLY   = 0x01U, /*!< OutOfBandActivationOnly */
} ezb_zcl_ota_upgrade_client_upgrade_activation_policy_t;

/**
 * @brief Enumeration for ZCL UpgradeTimeoutPolicy attribute of OTAUpgrade.
 */
typedef enum {
    EZB_ZCL_OTA_UPGRADE_UPGRADE_TIMEOUT_POLICY_APPLY_UPGRADE_AFTER_TIMEOUT        = 0x00U, /*!< ApplyUpgradeAfterTimeout */
    EZB_ZCL_OTA_UPGRADE_UPGRADE_TIMEOUT_POLICY_DO_NOT_APPLY_UPGRADE_AFTER_TIMEOUT = 0x01U, /*!< DoNotApplyUpgradeAfterTimeout */
} ezb_zcl_ota_upgrade_client_upgrade_timeout_policy_t;

/** @brief Default value of UpgradeServerID in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_UPGRADE_SERVER_ID_DEFAULT_VALUE (0xffffffffffffffff)

/** @brief Default value of FileOffset in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_FILE_OFFSET_DEFAULT_VALUE (0xffffffff)

/** @brief Default value of CurrentFileVersion in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_CURRENT_FILE_VERSION_DEFAULT_VALUE (0xffffffff)

/** @brief Default value of CurrentZigbeeStackVersion in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_CURRENT_ZIGBEE_STACK_VERSION_DEFAULT_VALUE (0xffff)

/** @brief Default value of DownloadedFileVersion in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_DOWNLOADED_FILE_VERSION_DEFAULT_VALUE (0xffffffff)

/** @brief Default value of DownloadedZigbeeStackVersion in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_DOWNLOADED_ZIGBEE_STACK_VERSION_DEFAULT_VALUE (0xffff)

/** @brief Default value of ImageUpgradeStatus in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_IMAGE_UPGRADE_STATUS_DEFAULT_VALUE (0x00)

/** @brief Default value of MinimumBlockPeriod in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_MINIMUM_BLOCK_PERIOD_DEFAULT_VALUE (0x0000)

/** @brief Minimum value of MinimumBlockPeriod in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_MINIMUM_BLOCK_PERIOD_MIN_VALUE (0x0000)

/** @brief Maximum value of MinimumBlockPeriod in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_MINIMUM_BLOCK_PERIOD_MAX_VALUE (0xfffe)

/** @brief Default value of UpgradeActivationPolicy in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_UPGRADE_ACTIVATION_POLICY_DEFAULT_VALUE (0x00)

/** @brief Minimum value of UpgradeActivationPolicy in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_UPGRADE_ACTIVATION_POLICY_MIN_VALUE (0x00)

/** @brief Maximum value of UpgradeActivationPolicy in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_UPGRADE_ACTIVATION_POLICY_MAX_VALUE (0x01)
/** @brief Default value of UpgradeTimeoutPolicy in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_UPGRADE_TIMEOUT_POLICY_DEFAULT_VALUE (0x00)

/** @brief Minimum value of UpgradeTimeoutPolicy in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_UPGRADE_TIMEOUT_POLICY_MIN_VALUE (0x00)

/** @brief Maximum value of UpgradeTimeoutPolicy in OTAUpgrade cluster */
#define EZB_ZCL_OTA_UPGRADE_UPGRADE_TIMEOUT_POLICY_MAX_VALUE (0x01)

/**
 * @brief Received Command identifiers for the OTAUpgrade cluster.
 */
typedef enum {
    EZB_ZCL_CMD_OTA_UPGRADE_IMAGE_NOTIFY_ID                        = 0x00U, /*!< ImageNotify command. */
    EZB_ZCL_CMD_OTA_UPGRADE_QUERY_NEXT_IMAGE_RESPONSE_ID           = 0x02U, /*!< QueryNextImageResponse command. */
    EZB_ZCL_CMD_OTA_UPGRADE_IMAGE_BLOCK_RESPONSE_ID                = 0x05U, /*!< ImageBlockResponse command. */
    EZB_ZCL_CMD_OTA_UPGRADE_UPGRADE_END_RESPONSE_ID                = 0x07U, /*!< UpgradeEndResponse command. */
    EZB_ZCL_CMD_OTA_UPGRADE_QUERY_DEVICE_SPECIFIC_FILE_RESPONSE_ID = 0x09U, /*!< QueryDeviceSpecificFileResponse command. */
} ezb_zcl_ota_upgrade_client_cmd_id_t;

typedef ezb_zcl_ota_upgrade_cluster_server_config_t ezb_zcl_ota_upgrade_cluster_config_t;

/**
 * @brief Add an attribute to an ota_upgrade cluster descriptor.
 *
 * @param cluster_desc Pointer to the ota_upgrade cluster descriptor, see ezb_zcl_cluster_desc_t.
 * @param attr_id      Attribute identifier.
 * @param value        Pointer to the attribute value.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ota_upgrade_cluster_desc_add_attr(ezb_zcl_cluster_desc_t cluster_desc, uint16_t attr_id, const void *value);

/**
 * @brief Create an ota_upgrade cluster descriptor.
 *
 * @param cluster_cfg  Pointer to the ota_upgrade cluster configuration structure, refer to
 * ezb_zcl_ota_upgrade_cluster_server_config_t or ezb_zcl_ota_upgrade_cluster_client_config_t or NULL (default config)
 * @param role_mask Role mask (server/client).
 * @return Created cluster descriptor.
 */
ezb_zcl_cluster_desc_t ezb_zcl_ota_upgrade_create_cluster_desc(const void *cluster_cfg, uint8_t role_mask);

/**
 * @brief Initialize the OTAUpgrade cluster client role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_ota_upgrade_cluster_client_init(uint8_t ep_id);

/**
 * @brief Initialize the OTAUpgrade cluster server role for a given endpoint.
 *
 * @param ep_id Endpoint ID.
 */
void ezb_zcl_ota_upgrade_cluster_server_init(uint8_t ep_id);

#define EZB_ZCL_CLUSTER_ID_OTA_UPGRADE_CLIENT_ROLE_INIT ezb_zcl_ota_upgrade_cluster_client_init
#define EZB_ZCL_CLUSTER_ID_OTA_UPGRADE_SERVER_ROLE_INIT ezb_zcl_ota_upgrade_cluster_server_init

#ifdef __cplusplus
} /*  extern "C" */
#endif
