/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <ezbee/zcl/cluster/ias_wd_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Values of Warning Mode Field.
 */
typedef enum {
    EZB_ZCL_IAS_WD_WARNING_MODE_STOP            = 0x00, /*!< Stop. */
    EZB_ZCL_IAS_WD_WARNING_MODE_BURGLAR         = 0x01, /*!< Burglar. */
    EZB_ZCL_IAS_WD_WARNING_MODE_FIRE            = 0x02, /*!< Fire. */
    EZB_ZCL_IAS_WD_WARNING_MODE_EMERGENCY       = 0x03, /*!< Emergency. */
    EZB_ZCL_IAS_WD_WARNING_MODE_POLICE_PANIC    = 0x04, /*!< Police panic. */
    EZB_ZCL_IAS_WD_WARNING_MODE_FIRE_PANIC      = 0x05, /*!< Fire panic. */
    EZB_ZCL_IAS_WD_WARNING_MODE_EMERGENCY_PANIC = 0x06, /*!< Emergency panic (i.e., medical issue). */
} ezb_zcl_ias_wd_warning_mode_t;

/**
 * @brief Values of Strobe Field.
 */
typedef enum {
    EZB_ZCL_IAS_WD_STROBE_NO_STROBE  = 0x00, /*!< No strobe. */
    EZB_ZCL_IAS_WD_STROBE_USE_STROBE = 0x01, /*!< Use strobe in parallel to warning. */
} ezb_zcl_ias_wd_strobe_t;

/**
 * @brief Values of Siren Level Field.
 */
typedef enum {
    EZB_ZCL_IAS_WD_SIREN_LEVEL_LOW       = 0x00, /*!< Low level sound. */
    EZB_ZCL_IAS_WD_SIREN_LEVEL_MEDIUM    = 0x01, /*!< Medium level sound. */
    EZB_ZCL_IAS_WD_SIREN_LEVEL_HIGH      = 0x02, /*!< High level sound. */
    EZB_ZCL_IAS_WD_SIREN_LEVEL_VERY_HIGH = 0x03, /*!< Very high level sound. */
} ezb_zcl_ias_wd_siren_level_t;

/**
 * @brief Values of Strobe Level Field.
 */
typedef enum {
    EZB_ZCL_IAS_WD_STROBE_LEVEL_LOW       = 0x00, /*!< Low level strobe. */
    EZB_ZCL_IAS_WD_STROBE_LEVEL_MEDIUM    = 0x01, /*!< Medium level strobe. */
    EZB_ZCL_IAS_WD_STROBE_LEVEL_HIGH      = 0x02, /*!< High level strobe. */
    EZB_ZCL_IAS_WD_STROBE_LEVEL_VERY_HIGH = 0x03, /*!< Very high level strobe. */
} ezb_zcl_ias_wd_strobe_level_t;

/**
 * @brief Values of Squawk Mode Field.
 */
typedef enum {
    EZB_ZCL_IAS_WD_SQUAWK_MODE_ARMED    = 0x00, /*!< Notification sound for "System is armed". */
    EZB_ZCL_IAS_WD_SQUAWK_MODE_DISARMED = 0x01, /*!< Notification sound for "System is disarmed". */
} ezb_zcl_ias_wd_squawk_mode_t;

/**
 * @brief Values of Squawk Strobe Field.
 */
typedef enum {
    EZB_ZCL_IAS_WD_SQUAWK_STROBE_NO_STROBE  = 0x00, /*!< No strobe. */
    EZB_ZCL_IAS_WD_SQUAWK_STROBE_USE_STROBE = 0x01, /*!< Use strobe blink in parallel to squawk. */
} ezb_zcl_ias_wd_squawk_strobe_t;

/**
 * @brief Values of Squawk Level Field.
 */
typedef enum {
    EZB_ZCL_IAS_WD_SQUAWK_LEVEL_LOW       = 0x00, /*!< Low level sound. */
    EZB_ZCL_IAS_WD_SQUAWK_LEVEL_MEDIUM    = 0x01, /*!< Medium level sound. */
    EZB_ZCL_IAS_WD_SQUAWK_LEVEL_HIGH      = 0x02, /*!< High level sound. */
    EZB_ZCL_IAS_WD_SQUAWK_LEVEL_VERY_HIGH = 0x03, /*!< Very high level sound. */
} ezb_zcl_ias_wd_squawk_level_t;

/**
 * @brief Payload for IAS WD Start Warning command request.
 */
typedef struct ezb_zcl_ias_wd_start_warning_payload_s {
    uint8_t  warning_mode : 4;  /*!< Warning Mode. */
    uint8_t  strobe : 2;        /*!< Strobe. */
    uint8_t  siren_level : 2;   /*!< Siren level. */
    uint16_t duration;          /*!< Duration. */
    uint8_t  strobe_duty_cycle; /*!< Strobe duty cycle. */
    uint8_t  strobe_level;      /*!< Strobe level. */
} ezb_zcl_ias_wd_start_warning_payload_t;

/**
 * @brief Payload for IAS WD Squawk command request.
 */
typedef struct ezb_zcl_ias_wd_squawk_payload_s {
    uint8_t squawk_level : 2; /*!< Squawk level. */
    uint8_t strobe : 2;       /*!< Strobe. */
    uint8_t squawk_mode : 4;  /*!< Squawk Mode. */
} ezb_zcl_ias_wd_squawk_payload_t;

/**
 * @brief structure for IAS WD Start Warning command.
 */
typedef struct ezb_zcl_ias_wd_start_warning_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t             cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_ias_wd_start_warning_payload_t payload;  /*!< Payload for the Start Warning command. */
} ezb_zcl_ias_wd_start_warning_cmd_t;

/**
 * @brief Structure for IAS WD Squawk command.
 */
typedef struct ezb_zcl_ias_wd_squawk_cmd_s {
    ezb_zcl_cluster_cmd_ctrl_t      cmd_ctrl; /*!< Control information for the ZCL command. */
    ezb_zcl_ias_wd_squawk_payload_t payload;  /*!< Payload for the Squawk command. */
} ezb_zcl_ias_wd_squawk_cmd_t;

/**
 * @brief Message for IAS WD Start Warning command message.
 */
typedef struct ezb_zcl_ias_wd_start_warning_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;                /*!< ZCL command header information.
                                                             See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_wd_start_warning_payload_t payload; /*!< Payload for the Start Warning command. */
    } in;                                               /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_wd_start_warning_message_t;

/**
 * @brief Message for IAS WD Squawk command message.
 */
typedef struct ezb_zcl_ias_wd_squawk_message_s {
    ezb_zcl_message_info_t info; /*!< Basic information about the ZCL message. */
    struct {
        const ezb_zcl_cmd_hdr_t *header;         /*!< ZCL command header information.
                                                      See @ref ezb_zcl_cmd_hdr_s. */
        ezb_zcl_ias_wd_squawk_payload_t payload; /*!< Payload for the Squawk command. */
    } in;                                        /*!< Input: parsed fields from the request. */
    struct {
        ezb_zcl_status_t result; /*!< Status of processing in application. */
    } out;                       /*!< Output: result to send back. */
} ezb_zcl_ias_wd_squawk_message_t;

/**
 * @brief Request to send an IAS WD Start Warning command request.
 *
 * @param cmd_req Pointer to the Start Warning command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_wd_start_warning_cmd_req(const ezb_zcl_ias_wd_start_warning_cmd_t *cmd_req);

/**
 * @brief Request to send an IAS WD Squawk command request.
 *
 * @param cmd_req Pointer to the Squawk command structure.
 * @return Error code.
 */
ezb_err_t ezb_zcl_ias_wd_squawk_cmd_req(const ezb_zcl_ias_wd_squawk_cmd_t *cmd_req);

#ifdef __cplusplus
} /* extern "C" */
#endif
