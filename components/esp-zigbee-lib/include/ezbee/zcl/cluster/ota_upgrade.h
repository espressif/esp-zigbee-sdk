/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/ota_upgrade_desc.h>
#include <ezbee/zcl/cluster/ota_file.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Maximum image block size in bytes.
 */
#define EZB_ZCL_OTA_UPGRADE_MAX_BLOCK_SIZE 254U

/**
 * @brief Default image block size in bytes when not configured.
 */
#define EZB_ZCL_OTA_UPGRADE_DEFAULT_BLOCK_SIZE_DEFAULT 48U

/**
 * @brief Maximum query jitter value for Image Notify (0–255).
 */
#define EZB_ZCL_OTA_UPGRADE_MAX_QUERY_JITTER_VALUE 100U

/**
 * @brief Wild card: any manufacturer code when querying or matching.
 */
#define EZB_ZCL_OTA_UPGRADE_MANUF_CODE_WILD_CARD 0xffffU

/**
 * @brief Wild card: any file version when querying or matching.
 */
#define EZB_ZCL_OTA_UPGRADE_FILE_VERSION_WILD_CARD 0xffffffffU

/**
 * @brief Default upgrade time (e.g. when server has no specific time).
 */
#define EZB_ZCL_OTA_UPGRADE_DEFAULT_UPGRADE_TIME 0xffffffffU

/**
 * @brief Enumeration for the ZCL OTA Upgrade status codes.
 */
enum {
    EZB_ZCL_OTA_UPGRADE_STATUS_CODE_SUCCESS            = EZB_ZCL_STATUS_SUCCESS,            /*!< Success. */
    EZB_ZCL_OTA_UPGRADE_STATUS_CODE_ABORT              = EZB_ZCL_STATUS_ABORT,              /*!< Abort. */
    EZB_ZCL_OTA_UPGRADE_STATUS_CODE_NOT_AUTHORIZED     = EZB_ZCL_STATUS_NOT_AUTHORIZED,     /*!< Not authorized. */
    EZB_ZCL_OTA_UPGRADE_STATUS_CODE_INVALID_IMAGE      = EZB_ZCL_STATUS_INVALID_IMAGE,      /*!< Invalid image. */
    EZB_ZCL_OTA_UPGRADE_STATUS_CODE_WAIT_FOR_DATA      = EZB_ZCL_STATUS_WAIT_FOR_DATA,      /*!< Wait for data. */
    EZB_ZCL_OTA_UPGRADE_STATUS_CODE_NO_IMAGE_AVAILABLE = EZB_ZCL_STATUS_NO_IMAGE_AVAILABLE, /*!< No image available. */
    EZB_ZCL_OTA_UPGRADE_STATUS_CODE_REQUIRE_MORE_IMAGE = EZB_ZCL_STATUS_REQUIRE_MORE_IMAGE, /*!< Require more image. */
    EZB_ZCL_OTA_UPGRADE_STATUS_CODE_MALFORMED_CMD      = EZB_ZCL_STATUS_MALFORMED_CMD,      /*!< Malformed command. */
    EZB_ZCL_OTA_UPGRADE_STATUS_CODE_UNSUP_CMD          = EZB_ZCL_STATUS_UNSUP_CMD,          /*!< Unsupported command. */
};

/**
 * @brief Type for the ZCL OTA Upgrade status code.
 * @anchor ezb_zcl_ota_upgrade_status_code_t
 */
typedef ezb_zcl_status_t ezb_zcl_ota_upgrade_status_code_t;

/**
 * @brief Enumeration for the ZCL OTA Upgrade image notify payload type.
 * @anchor ezb_zcl_ota_upgrade_image_notify_payload_type_t
 */
typedef enum {
    EZB_ZCL_OTA_UPGRADE_IMAGE_NOTIFY_PAYLOAD_TYPE_JITTER                    = 0x00U, /*!< Jitter */
    EZB_ZCL_OTA_UPGRADE_IMAGE_NOTIFY_PAYLOAD_TYPE_JITTER_CODE               = 0x01U, /*!< Jitter code */
    EZB_ZCL_OTA_UPGRADE_IMAGE_NOTIFY_PAYLOAD_TYPE_JITTER_CODE_IMAGE         = 0x02U, /*!< Jitter code image */
    EZB_ZCL_OTA_UPGRADE_IMAGE_NOTIFY_PAYLOAD_TYPE_JITTER_CODE_IMAGE_VERSION = 0x03U, /*!< Jitter code image version */
} ezb_zcl_ota_upgrade_image_notify_payload_type_t;

/**
 * @brief Enumeration for the ZCL OTA Upgrade progress type.
 * @anchor ezb_zcl_ota_upgrade_progress_t
 */
typedef enum {
    EZB_ZCL_OTA_UPGRADE_PROGRESS_START,     /*!< Progress: Start */
    EZB_ZCL_OTA_UPGRADE_PROGRESS_RECEIVING, /*!< Progress: Receiving */
    EZB_ZCL_OTA_UPGRADE_PROGRESS_SENDING,   /*!< Progress: Sending */
    EZB_ZCL_OTA_UPGRADE_PROGRESS_CHECK,     /*!< Progress: Check */
    EZB_ZCL_OTA_UPGRADE_PROGRESS_APPLY,     /*!< Progress: Apply */
    EZB_ZCL_OTA_UPGRADE_PROGRESS_FINISH,    /*!< Progress: Finish */
    EZB_ZCL_OTA_UPGRADE_PROGRESS_ABORT,     /*!< Progress: Abort */
} ezb_zcl_ota_upgrade_progress_t;

/**
 * @brief Structure for the ZCL OTA Upgrade client start progress information.
 */
typedef struct {
    uint16_t manuf_code;   /*!< Manufacturer code. */
    uint16_t image_type;   /*!< Image type. */
    uint32_t file_version; /*!< File version. */
    uint32_t image_size;   /*!< Image size in bytes. */
} ezb_zcl_ota_upgrade_client_progress_start_t;

/**
 * @brief Structure for the ZCL OTA Upgrade client receiving progress information.
 */
typedef struct {
    uint32_t file_offset; /*!< Current file offset in bytes. */
    uint8_t  block_size;  /*!< Block size in bytes. */
    uint8_t *block;       /*!< Pointer to the received block data. */
} ezb_zcl_ota_upgrade_client_progress_receiving_t;

/**
 * @brief Structure for the ZCL OTA Upgrade client check progress information.
 */
typedef struct {
    uint16_t manuf_code;   /*!< Manufacturer code */
    uint16_t image_type;   /*!< Image type */
    uint32_t file_version; /*!< File version */
} ezb_zcl_ota_upgrade_client_progress_check_t;

/**
 * @brief Structure for the ZCL OTA Upgrade client apply progress information.
 */
typedef struct {
    uint16_t manuf_code;   /*!< Manufacturer code */
    uint16_t image_type;   /*!< Image type */
    uint32_t file_version; /*!< File version */
} ezb_zcl_ota_upgrade_client_progress_apply_t;

/**
 * @brief Structure for the ZCL OTA Upgrade client finish progress information.
 */
typedef struct {
    uint32_t count_down_delay; /*!< Countdown delay in seconds before upgrade takes effect */
} ezb_zcl_ota_upgrade_client_progress_finish_t;

/**
 * @brief Message for the ZCL OTA Upgrade client progress message.
 */
typedef struct ezb_zcl_ota_upgrade_client_progress_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;         /*!< ZCL command header information.
                                                      See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ota_upgrade_progress_t progress; /*!< Progress; @ref ezb_zcl_ota_upgrade_progress_t.
                                                  * EZB_ZCL_OTA_UPGRADE_PROGRESS_START: Start OTA
                                                  * EZB_ZCL_OTA_UPGRADE_PROGRESS_RECEIVING: Receiving OTA image block
                                                  * EZB_ZCL_OTA_UPGRADE_PROGRESS_CHECK: Check completed OTA image
                                                  * EZB_ZCL_OTA_UPGRADE_PROGRESS_APPLY: Apply completed OTA image
                                                  * EZB_ZCL_OTA_UPGRADE_PROGRESS_FINISH: Finish OTA
                                                  * EZB_ZCL_OTA_UPGRADE_PROGRESS_ABORT: Abort OTA
                                                  */
        union {
            ezb_zcl_ota_upgrade_client_progress_start_t     start;     /*!< Start information. */
            ezb_zcl_ota_upgrade_client_progress_receiving_t receiving; /*!< Receiving information. */
            ezb_zcl_ota_upgrade_client_progress_check_t     check;     /*!< Check information. */
            ezb_zcl_ota_upgrade_client_progress_apply_t     apply;     /*!< Apply information. */
            ezb_zcl_ota_upgrade_client_progress_finish_t    finish;    /*!< Finish information. */
        };                                                             /*!< Union of progress information. */
    } in;                                                              /*!< Input: OTA upgrade client progress information. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ota_upgrade_client_progress_message_t;

/**
 * @brief Structure for the ZCL OTA Upgrade new image information.
 */
typedef struct {
    uint8_t       status;         /*!< Status; @ref ezb_zcl_ota_upgrade_status_code_t. */
    ezb_extaddr_t server_address; /*!< Server extended address. */
    uint8_t       ep_id;          /*!< Endpoint ID. */
    uint16_t      manuf_code;     /*!< Manufacturer code. */
    uint16_t      image_type;     /*!< Image type. */
    uint32_t      file_version;   /*!< File version. */
    uint32_t      size;           /*!< Image size in bytes. */
} ezb_zcl_ota_upgrade_new_image_t;

/**
 * @brief Message for the ZCL OTA Upgrade Query Next Image response message.
 */
typedef struct ezb_zcl_ota_upgrade_query_next_image_rsp_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;       /*!< ZCL command header information.
                                                    See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ota_upgrade_new_image_t image; /*!< New image information. */
    } in;                                      /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ota_upgrade_query_next_image_rsp_message_t;

/**
 * @brief Structure for the ZCL OTA Upgrade server start progress information.
 */
typedef struct {
    struct {
        uint16_t short_address; /*!< Client short address */
        uint8_t  ep_id;         /*!< Endpoint ID */
        uint16_t manuf_code;    /*!< Manufacturer code */
        uint16_t image_type;    /*!< Image type */
        uint32_t file_version;  /*!< File version */
        uint16_t hw_version;    /*!< Hardware version */
    } query;                    /*!< Query information. */
    struct {
        uint32_t file_version; /*!< File version for policy */
    } policy;                  /*!< Policy information. */
} ezb_zcl_ota_upgrade_server_progress_start_t;

/**
 * @brief Structure for the ZCL OTA Upgrade server sending progress information.
 */
typedef struct {
    uint16_t manuf_code;   /*!< Manufacturer code */
    uint16_t image_type;   /*!< Image type */
    uint32_t file_version; /*!< File version */
    uint32_t file_offset;  /*!< Current file offset in bytes */
    uint16_t block_delay;  /*!< Block delay in milliseconds before next request */
} ezb_zcl_ota_upgrade_server_progress_sending_t;

/**
 * @brief Structure for the ZCL OTA Upgrade server finish progress information.
 */
typedef struct {
    uint8_t  status;       /*!< Status code */
    uint16_t manuf_code;   /*!< Manufacturer code */
    uint16_t image_type;   /*!< Image type */
    uint32_t file_version; /*!< File version */
} ezb_zcl_ota_upgrade_server_progress_finish_t;

/**
 * @brief Structure for the ZCL OTA Upgrade server finish progress upgrade time information.
 */
typedef struct {
    uint16_t current_time; /*!< Current time (server) */
    uint16_t upgrade_time; /*!< Upgrade time (when upgrade is scheduled) */
} ezb_zcl_ota_upgrade_server_progress_upgrade_time_t;

/**
 * @brief Message for the ZCL OTA Upgrade server progress message.
 */
typedef struct ezb_zcl_ota_upgrade_server_progress_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;         /*!< ZCL command header information.
                                                      See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ota_upgrade_progress_t progress; /*!< Progress; @ref ezb_zcl_ota_upgrade_progress_t;
                                                  * EZB_ZCL_OTA_UPGRADE_PROGRESS_START: Start OTA;
                                                  * EZB_ZCL_OTA_UPGRADE_PROGRESS_SENDING: Sending OTA image block;
                                                  * EZB_ZCL_OTA_UPGRADE_PROGRESS_FINISH: Finish OTA; */
        union {
            ezb_zcl_ota_upgrade_server_progress_start_t   start;   /*!< Start information. */
            ezb_zcl_ota_upgrade_server_progress_sending_t sending; /*!< Sending information. */
            ezb_zcl_ota_upgrade_server_progress_finish_t  finish;  /*!< Finish information. */
        };                                                         /*!< Union of progress information. */
    } in;                                                          /*!< Input: OTA upgrade server progress information. */
    struct {
        ezb_zcl_status_t                                   result; /*!< Status of processing in application. */
        ezb_zcl_ota_upgrade_server_progress_upgrade_time_t finish; /*!< Upgrade time from Upgrade End response. */
    } out;                                                         /*!< Output: result to send back. */
} ezb_zcl_ota_upgrade_server_progress_message_t;

/**
 * @brief Enumeration bitmask for the field control for the Query Next Image Request.
 */
typedef enum {
    EZB_ZCL_OTA_UPGRADE_QUERY_NEXT_IMAGE_FC_HW_VERSION_PRESENT = 1 << 0, /*!< Hardware version present */
} ezb_zcl_ota_upgrade_query_next_image_fc_t;

/**
 * @brief Enumeration bitmask for the field control for the Image Block Request.
 */
typedef enum {
    EZB_ZCL_OTA_UPGRADE_IMAGE_BLOCK_FC_NODE_ADDR_PRESENT = 1 << 0, /*!< Node address present */
    EZB_ZCL_OTA_UPGRADE_IMAGE_BLOCK_FC_DELAY_PRESENT     = 1 << 1, /*!< Delay present */
} ezb_zcl_ota_upgrade_image_block_fc_t;

/**
 * @brief Payload for the ZCL OTA Upgrade ImageNotify command.
 */
typedef struct ezb_zcl_ota_upgrade_image_notify_payload_s {
    uint8_t  type;         /*!< Payload type; see @ref ezb_zcl_ota_upgrade_image_notify_payload_type_t. */
    uint8_t  query_jitter; /*!< Query jitter value (0-255). */
    uint16_t manuf_code;   /*!< Manufacturer code. */
    uint16_t image_type;   /*!< Image type. */
    uint32_t file_version; /*!< File version. */
} ezb_zcl_ota_upgrade_image_notify_payload_t;

/**
 * @brief Structure for the ZCL OTA Upgrade ImageNotify command request.
 */
typedef struct ezb_zcl_ota_upgrade_image_notify_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                 cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_ota_upgrade_image_notify_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_ota_upgrade_image_notify_cmd_t;

/**
 * @brief Payload for the ZCL OTA Upgrade Query Next Image Request command.
 */
typedef struct ezb_zcl_ota_upgrade_query_next_image_req_payload_s {
    uint8_t  fc;           /*!< Field control. */
    uint16_t manuf_code;   /*!< Manufacturer code. */
    uint16_t image_type;   /*!< Image type. */
    uint32_t file_version; /*!< File version. */
    uint16_t hw_version;   /*!< Hardware version. */
} ezb_zcl_ota_upgrade_query_next_image_req_payload_t;

/**
 * @brief Structure for the ZCL OTA Upgrade Query Next Image Request command request.
 */
typedef struct ezb_zcl_ota_upgrade_query_next_image_req_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t                         cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_ota_upgrade_query_next_image_req_payload_t payload;  /*!< Payload of the command. */
} ezb_zcl_ota_upgrade_query_next_image_req_cmd_t;

/**
 * @brief Query Next Image Response payload (server response to Query Next Image).
 */
typedef struct ezb_zcl_ota_upgrade_query_next_image_rsp_payload_s {
    uint8_t  status;       /*!< Status code; @ref ezb_zcl_ota_upgrade_status_code_t */
    uint16_t manuf_code;   /*!< Manufacturer code */
    uint16_t image_type;   /*!< Image type */
    uint32_t file_version; /*!< File version */
    uint32_t image_size;   /*!< Image size in bytes */
} ezb_zcl_ota_upgrade_query_next_image_rsp_payload_t;

/**
 * @brief Image Block Request payload (client requests a block of image data).
 */
typedef struct {
    uint8_t       fc;            /*!< Field control */
    uint16_t      manuf_code;    /*!< Manufacturer code */
    uint16_t      image_type;    /*!< Image type */
    uint32_t      file_version;  /*!< File version */
    uint32_t      file_offset;   /*!< File offset in bytes */
    uint8_t       data_size_max; /*!< Maximum data size in bytes client can receive */
    ezb_extaddr_t node_addr;     /*!< Node extended address (optional) */
    uint16_t      block_delay;   /*!< Block delay in ms (optional) */
} ezb_zcl_ota_upgrade_image_block_req_payload_t;

/**
 * @brief Upgrade End Request payload (client signals download complete and status).
 */
typedef struct {
    uint8_t  status;       /*!< Status code */
    uint16_t manuf_code;   /*!< Manufacturer code */
    uint16_t image_type;   /*!< Image type */
    uint32_t file_version; /*!< File version */
} ezb_zcl_ota_upgrade_upgrade_end_req_payload_t;

/**
 * @brief Upgrade End Response payload (server responds with current/upgrade time).
 */
typedef struct {
    uint16_t manuf_code;   /*!< Manufacturer code */
    uint16_t image_type;   /*!< Image type */
    uint32_t file_version; /*!< File version */
    uint32_t current_time; /*!< Current time (server) */
    uint32_t upgrade_time; /*!< Upgrade time (when upgrade is scheduled) */
} ezb_zcl_ota_upgrade_upgrade_end_rsp_payload_t;

/**
 * @brief Image Block Response payload (server sends block data or Wait For Data).
 */
typedef struct {
    uint8_t status; /*!< Status; @ref ezb_zcl_ota_upgrade_status_code_t. */
    union {
        struct {
            uint16_t manuf_code;   /*!< Manufacturer code */
            uint16_t image_type;   /*!< Image type */
            uint32_t file_version; /*!< File version */
            uint32_t file_offset;  /*!< File offset in bytes */
            uint8_t  data_size;    /*!< Data size in bytes */
            uint8_t *image_data;   /*!< Pointer to image data */
        } success;                 /*!< Success information. */
        struct {
            uint32_t current_time; /*!< Current time */
            uint32_t request_time; /*!< Request time */
            uint16_t block_delay;  /*!< Block delay in milliseconds */
        } wait_for_data;           /*!< Wait for data information. */
    };                             /*!< Union of response information. */

} ezb_zcl_ota_upgrade_image_block_rsp_payload_t;

/**
 * @brief Type for the OTA upgrade file.
 * @anchor ezb_zcl_ota_file_handle_t
 */
typedef void *ezb_zcl_ota_file_handle_t;

/**
 * @brief Invalid OTA file handle.
 */
#define EZB_ZCL_OTA_FILE_INVALID_HANDLE NULL

/**
 * @brief Send ZCL OTA Upgrade ImageNotify command request.
 *
 * @param cmd_req Pointer to the ImageNotify command request structure, @ref ezb_zcl_ota_upgrade_image_notify_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ota_upgrade_image_notify_cmd_req(const ezb_zcl_ota_upgrade_image_notify_cmd_t *cmd_req);

/**
 * @brief Add an OTA image file to the OTA server.
 *
 * This function adds an OTA image file to the OTA server, making it available for OTA upgrades.
 *
 * @param ep_id Endpoint ID of the OTA server.
 * @param image Pointer to the image data (complete OTA file, including header).
 * @param image_size Size of the image in bytes.
 *
 * @return Handle of the OTA file (@ref ezb_zcl_ota_file_handle_t).
 */
ezb_zcl_ota_file_handle_t ezb_zcl_ota_upgrade_add_ota_file(uint8_t ep_id, const void *image, uint32_t image_size);

/**
 * @brief Remove an OTA file from the OTA server.
 *
 * This function removes an OTA file previously added by
 * ezb_zcl_ota_upgrade_add_ota_file() from the OTA server.
 *
 * @param ep_id Endpoint ID of the OTA server.
 * @param ota_file Handle of the OTA file (@ref ezb_zcl_ota_file_handle_t) to be removed.
 *
 */
void ezb_zcl_ota_upgrade_remove_ota_file(uint8_t ep_id, ezb_zcl_ota_file_handle_t ota_file);

/**
 * @brief Send ZCL OTA Upgrade Query Next Image Request command request.
 *
 * @param cmd_req Pointer to the Query Next Image Request command request structure, @ref
 * ezb_zcl_ota_upgrade_query_next_image_req_cmd_s.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ota_upgrade_query_next_image_cmd_req(const ezb_zcl_ota_upgrade_query_next_image_req_cmd_t *cmd_req);

/**
 * @brief Set the maximum block size that the OTA client can receive.
 *
 * It specifies the MaximumDataSize field of the ImageBlockRequest, indicating the maximum number of bytes the client
 * can receive at once,.
 *
 * @param ep_id Endpoint ID of the OTA client.
 * @param allowed_block_size Maximum allowed block size in bytes (default: EZB_ZCL_OTA_UPGRADE_DEFAULT_BLOCK_SIZE_DEFAULT).
 *
 * @return Error code.
 */
ezb_err_t ezb_zcl_ota_upgrade_set_download_block_size(uint8_t ep_id, uint8_t allowed_block_size);

/**
 * @brief Set the hardware version on OTA client.
 *
 * If it is set, the QueryNextImageRequest will be sent with hardware version to response the ImageNotify command.
 *
 * @param ep_id Endpoint ID of the OTA client.
 * @param hw_version Hardware version (zero means no hardware version is set).
 * @return Error code.
 */
ezb_err_t ezb_zcl_ota_upgrade_set_hw_version(uint8_t ep_id, uint16_t hw_version);

#ifdef __cplusplus
} /* extern "C" */
#endif
