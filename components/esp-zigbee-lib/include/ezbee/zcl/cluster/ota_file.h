/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/core_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief File identifier for the ZCL OTA File.
 */
#define EZB_ZCL_OTA_FILE_IDENTIFIER 0x0BEEF11E

/**
 * @brief Header version for the ZCL OTA File.
 */
#define EZB_ZCL_OTA_FILE_HEADER_VERSION 0x0100

/**
 * @brief Enumeration bitmask for the ZCL OTA File header field control.
 *
 * Indicates which optional fields are present in the OTA file header.
 */
typedef enum {
    EZB_ZCL_OTA_FILE_HEADER_FC_SECURITY_CREDENTIAL_VERSION_PRESENT = 1U << 0, /*!< Security credential version present. */
    EZB_ZCL_OTA_FILE_HEADER_FC_DEVICE_SPECIFIC                     = 1U << 1, /*!< Device specific. */
    EZB_ZCL_OTA_FILE_HEADER_FC_HW_VERSION_PRESENT                  = 1U << 2, /*!< Hardware version. */
} ezb_zcl_ota_file_header_fc_t;

/**
 * @brief Enumeration for the ZCL OTA File image type.
 *
 * Standard types for security credentials, configuration, log; wild card for any type.
 */
typedef enum {
    EZB_ZCL_OTA_FILE_IMAGE_TYPE_CLIENT_SECURITY_CREDENTIALS = 0xffc0U, /*!< Client security credentials. */
    EZB_ZCL_OTA_FILE_IMAGE_TYPE_CLIENT_CONFIGURATION        = 0xffc1U, /*!< Client configuration. */
    EZB_ZCL_OTA_FILE_IMAGE_TYPE_SERVER_LOG                  = 0xffc2U, /*!< Server log. */
    EZB_ZCL_OTA_FILE_IMAGE_TYPE_PICTURE                     = 0xffc3U, /*!< Picture. */
    EZB_ZCL_OTA_FILE_IMAGE_TYPE_WILD_CARD                   = 0xffffU, /*!< Wild card. */
} ezb_zcl_ota_file_image_type_t;

/**
 * @brief Get the ZCL OTA File file version components.
 */
#define EZB_ZCL_OTA_FILE_VERSION_GET_APP_RELEASE(v)   ((v >> 24) & 0xff) /*!< App release. */
#define EZB_ZCL_OTA_FILE_VERSION_GET_APP_BUILD(v)     ((v >> 16) & 0xff) /*!< App build. */
#define EZB_ZCL_OTA_FILE_VERSION_GET_STACK_RELEASE(v) ((v >> 8) & 0xff)  /*!< Stack release. */
#define EZB_ZCL_OTA_FILE_VERSION_GET_STACK_BUILD(v)   ((v)&0xff)         /*!< Stack build. */

/**
 * @brief Set the ZCL OTA File file version components.
 */
#define EZB_ZCL_OTA_FILE_VERSION_SET_APP_RELEASE(v, a)   (((v) & ~(0xffU << 24)) | ((a & 0xffU) << 24)) /*!< App release. */
#define EZB_ZCL_OTA_FILE_VERSION_SET_APP_BUILD(v, a)     (((v) & ~(0xffU << 16)) | ((a & 0xffU) << 16)) /*!< App build. */
#define EZB_ZCL_OTA_FILE_VERSION_SET_STACK_RELEASE(v, a) (((v) & ~(0xffU << 8)) | ((a & 0xffU) << 8))   /*!< Stack release. */
#define EZB_ZCL_OTA_FILE_VERSION_SET_STACK_BUILD(v, a)   (((v) & ~(0xffU)) | ((a & 0xffU)))             /*!< Stack build. */

/**
 * @brief Enumeration for the ZCL OTA File stack version.
 */
typedef enum {
    EZB_ZCL_OTA_FILE_STACK_VERSION_2006 = 0x0000U, /*!< Zigbee Version 2006. */
    EZB_ZCL_OTA_FILE_STACK_VERSION_2007 = 0x0001U, /*!< Zigbee Version 2007. */
    EZB_ZCL_OTA_FILE_STACK_VERSION_PRO  = 0x0002U, /*!< Zigbee Version PRO. */
    EZB_ZCL_OTA_FILE_STACK_VERSION_IP   = 0x0003U, /*!< Zigbee Version IP. */
} ezb_zcl_ota_file_stack_version_t;

/**
 * @brief Enumeration for the ZCL OTA File security credential version.
 */
typedef enum {
    EZB_ZCL_OTA_FILE_SECURITY_CREDENTIAL_VERSION_SE1_0 = 0x00U, /*!< Security credential version SE1.0 */
    EZB_ZCL_OTA_FILE_SECURITY_CREDENTIAL_VERSION_SE1_1 = 0x01U, /*!< Security credential version SE1.1 */
    EZB_ZCL_OTA_FILE_SECURITY_CREDENTIAL_VERSION_SE2_0 = 0x02U, /*!< Security credential version SE2.0 */
    EZB_ZCL_OTA_FILE_SECURITY_CREDENTIAL_VERSION_SE1_2 = 0x03U, /*!< Security credential version SE1.2 */
} ezb_zcl_ota_file_security_credential_version_t;

/**
 * @brief Enumeration tag ID for the ZCL OTA File sub-element.
 *
 * Tags 0xf000–0xffff are manufacturer-specific.
 */
typedef enum {
    EZB_ZCL_OTA_FILE_TAG_ID_UPGRADE_IMAGE                   = 0x0000U, /*!< Upgrade image */
    EZB_ZCL_OTA_FILE_TAG_ID_ECDSA_SIGNATURE_CS1             = 0x0001U, /*!< ECDSA signature (Crypto Suite 1) */
    EZB_ZCL_OTA_FILE_TAG_ID_ECDSA_SIGNATURE_CERTIFICATE_CS1 = 0x0002U, /*!< ECDSA signature certificate (Crypto Suite 1) */
    EZB_ZCL_OTA_FILE_TAG_ID_IMAGE_INTEGRITY_CODE            = 0x0003U, /*!< Image integrity code */
    EZB_ZCL_OTA_FILE_TAG_ID_PICTURE_DATA                    = 0x0004U, /*!< Picture data */
    EZB_ZCL_OTA_FILE_TAG_ID_ECDSA_SIGNATURE_CS2             = 0x0005U, /*!< ECDSA signature (Crypto Suite 2) */
    EZB_ZCL_OTA_FILE_TAG_ID_ECDSA_SIGNATURE_CERTIFICATE_CS2 = 0x0006U, /*!< ECDSA signature certificate (Crypto Suite 2) */
    EZB_ZCL_OTA_FILE_TAG_ID_MANUF_SPECIFIC_MIN              = 0xf000U, /*!< Manufacturer specific min */
    EZB_ZCL_OTA_FILE_TAG_ID_MANUF_HEADER                    = 0xf001U, /*!< Manufacturer header */
    EZB_ZCL_OTA_FILE_TAG_ID_MANUF_SPECIFIC_MAX              = 0xffffU, /*!< Manufacturer specific max */
} ezb_zcl_ota_file_tag_id_t;

/**
 * @brief Structure for the ZCL OTA File sub-element.
 */
EZB_PACKED_BEGIN
typedef struct ezb_zcl_ota_file_sub_element_header_s {
    uint16_t tag_id; /*!< Tag ID */
    uint32_t length; /*!< Length in bytes */
} EZB_PACKED_END ezb_zcl_ota_file_sub_element_header_t;

/**
 * @brief Structure for the ZCL OTA File image information.
 */
EZB_PACKED_BEGIN
typedef struct ezb_zcl_ota_file_image_s {
    ezb_zcl_ota_file_sub_element_header_t hdr;     /*!< Header of the image sub-element */
    uint8_t                               image[]; /*!< Data of the image sub-element */
} EZB_PACKED_END ezb_zcl_ota_file_image_t;

/**
 * @brief Structure for the ZCL OTA File ECDSA signature sub-element.
 */
EZB_PACKED_BEGIN
typedef struct ezb_zcl_ota_file_ecdsa_signature_s {
    ezb_zcl_ota_file_sub_element_header_t hdr;           /*!< Header of the ECDSA signature sub-element */
    ezb_extaddr_t                         address;       /*!< Extended address */
    uint8_t                               signature[42]; /*!< ECDSA signature data (42 bytes) */
} EZB_PACKED_END ezb_zcl_ota_file_ecdsa_signature_t;

/**
 * @brief Structure for the ZCL OTA File ECDSA signature certificate sub-element.
 */
EZB_PACKED_BEGIN
typedef struct ezb_zcl_ota_file_ecdsa_signature_certificate_s {
    ezb_zcl_ota_file_sub_element_header_t hdr;             /*!< Header of the ECDSA signature certificate sub-element */
    uint8_t                               certificate[48]; /*!< ECDSA certificate data (48 bytes) */
} EZB_PACKED_END ezb_zcl_ota_file_ecdsa_signature_certificate_t;

/**
 * @brief Structure for the ZCL OTA File ECDSA signature crypto suite 2 sub-element.
 */
EZB_PACKED_BEGIN
typedef struct ezb_zcl_ota_file_ecdsa_signature_crypto_suite2_s {
    ezb_zcl_ota_file_sub_element_header_t hdr;           /*!< Header of the ECDSA signature crypto suite 2 sub-element */
    ezb_extaddr_t                         address;       /*!< Extended address */
    uint8_t                               signature[72]; /*!< ECDSA signature data (72 bytes) */
} EZB_PACKED_END ezb_zcl_ota_file_ecdsa_signature_crypto_suite2_t;

/**
 * @brief Structure for the ZCL OTA File ECDSA signature certificate crypto suite 2 sub-element.
 */
typedef struct ezb_zcl_ota_file_ecdsa_signature_certificate_crypto_suite2_s {
    ezb_zcl_ota_file_sub_element_header_t hdr; /*!< Header of the ECDSA signature certificate crypto suite 2 sub-element */
    uint8_t                               certificate[74]; /*!< ECDSA certificate data (74 bytes) */
} EZB_PACKED_END ezb_zcl_ota_file_ecdsa_signature_certificate_crypto_suite2_t;

/**
 * @brief Structure for the ZCL OTA File image integrity code sub-element.
 */
EZB_PACKED_BEGIN
typedef struct ezb_zcl_ota_file_image_integrity_code_s {
    ezb_zcl_ota_file_sub_element_header_t hdr;                /*!< Header of the image integrity code sub-element */
    uint8_t                               integrity_code[16]; /*!< Image integrity code (16 bytes) */
} EZB_PACKED_END ezb_zcl_ota_file_image_integrity_code_t;

/**
 * @brief Structure for the ZCL OTA File picture data sub-element.
 */
EZB_PACKED_BEGIN
typedef struct ezb_zcl_ota_upgrade_picture_data_s {
    ezb_zcl_ota_file_sub_element_header_t hdr;              /*!< Header of the picture data sub-element */
    uint8_t                               picture_data[16]; /*!< Picture data (16 bytes) */
} EZB_PACKED_END ezb_zcl_ota_file_picture_data_t;

/**
 * @brief Structure for the ZCL OTA File header mandatory fields.
 *
 * Parsed from the first bytes of an OTA file; @p fc indicates which optional fields follow.
 */
EZB_PACKED_BEGIN
typedef struct ezb_zcl_ota_file_header_s {
    uint32_t file_id;           /*!< File identifier */
    uint16_t hdr_version;       /*!< Header version */
    uint16_t hdr_length;        /*!< Header length in bytes */
    uint16_t hdr_fc;            /*!< Header field control bitmask */
    uint16_t manufacturer_code; /*!< Manufacturer code */
    uint16_t image_type;        /*!< Image type */
    uint32_t file_version;      /*!< File version */
    uint16_t stack_version;     /*!< Stack version */
    char     hdr_string[32];    /*!< Header string */
    uint32_t total_image_size;  /*!< Total image size in bytes */
} EZB_PACKED_END ezb_zcl_ota_file_header_t;

/**
 * @brief Structure for the ZCL OTA File header optional fields.
 */
EZB_PACKED_BEGIN
typedef struct ezb_zcl_ota_file_header_optional_s {
    uint8_t       security_credential_version; /*!< Security credential version. */
    ezb_extaddr_t upgrade_file_destination;    /*!< Upgrade file destination extended address. */
    uint16_t      minimum_hardware_version;    /*!< Minimum hardware version. */
    uint16_t      maximum_hardware_version;    /*!< Maximum hardware version. */
} EZB_PACKED_END ezb_zcl_ota_file_header_optional_t;

#ifdef __cplusplus
} /* extern "C" */
#endif
