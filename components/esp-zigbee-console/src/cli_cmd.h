/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"

#include "cli_util.h"
#include "argtable_ext.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct esp_zb_cli_cmd_s {
    const char *name;
    const char *help;
    esp_err_t (*operation)(struct esp_zb_cli_cmd_s *self, int argc, char **argv);
    struct esp_zb_cli_cmd_s *sub_cmds;
    int sub_cmd_count;
} esp_zb_cli_cmd_t;

#define _cmd_section(sec)           ".esp_zb_cli_cmd_desc." # sec
#define _section(sec)               __attribute__((__section__(sec)))
#define _used                       __attribute__((__used__))
#define ESP_ZB_CLI_CMD_DESC(cmd)    _used _section(_cmd_section(cmd))

/* Format: s_<cmd_name>_subcmd_list */
#define _subcmd_list_name(_name)    s_ ## _name ## _subcmd_list

/* Format: s_cmd_<cmd_name> */
#define _cmd_var_name(_name)        s_cmd_ ## _name

/* Expand `_macro` when `VA_ARG` is not empty. */
#define _expand_or_non(_macro, ...) __VA_OPT__(_macro(__VA_ARGS__))

#define ESP_ZB_CLI_CMD_SUBCMD_FIELDS(_sub)                                                      \
    .sub_cmds = _sub, .sub_cmd_count = ARRAY_SIZE(_sub),

#define ESP_ZB_CLI_CMD_OP_FIELDS(_op)                                                           \
    .operation = _op,

#define ESP_ZB_CLI_CMD(_name, _op, _sub, _help)                                                 \
    {                                                                                           \
        .name = #_name,                                                                         \
        .help = _help,                                                                          \
        _expand_or_non(ESP_ZB_CLI_CMD_OP_FIELDS, _op)                                           \
        _expand_or_non(ESP_ZB_CLI_CMD_SUBCMD_FIELDS, _sub)                                      \
    }

#define ESP_ZB_CLI_CMD_WITH_SUB(_name, _sub, _help) ESP_ZB_CLI_CMD(_name,, _subcmd_list_name(_sub), _help)
#define ESP_ZB_CLI_CMD_WITH_OP(_name, _op, _help)   ESP_ZB_CLI_CMD(_name, _op,, _help)
#define ESP_ZB_CLI_SUBCMD(_name, _op, _help)        ESP_ZB_CLI_CMD(_name, _op,, _help)

/**
 * @brief Declare sub-command list of parent command.
 *
 * @param _parent Name of the parent command.
 * @param ...     Sub-command definitions (should be valid initializer of `esp_zb_cli_cmd_t`).
 *
 */
#define DECLARE_ESP_ZB_CLI_SUBCMD_LIST(_parent, ...)                                            \
    static esp_zb_cli_cmd_t _subcmd_list_name(_parent)[] = {                                    \
        __VA_ARGS__                                                                             \
    }

/**
 * @brief Declare a cli command.
 *
 * @note The command structure will be placed in `.esp_zb_cli_cmd_desc.<cmd_name>` section.
 *
 * @param _name Name of the command.
 * @param _op   Operation function of the command.
 * @param _sub  Sub-command list.
 * @param _help Help string of command.
 *
 */
#define DECLARE_ESP_ZB_CLI_CMD(_name, _op, _sub, _help)                                         \
    static const esp_zb_cli_cmd_t _cmd_var_name(_name)                                          \
    ESP_ZB_CLI_CMD_DESC(_name)                                                                  \
    = ESP_ZB_CLI_CMD(_name, _op, _sub, _help)

/**
 * @brief Declare a cli command and its sub-commands list.
 *
 * @note The command structure will be placed in `.esp_zb_cli_cmd_desc.<cmd_name>` section.
 *
 * @param _name Name of the main command.
 * @param _help Help string of the main command.
 * @param ...   Sub-command definitions (should be valid initializer of `esp_zb_cli_cmd_t`).
 *
 */
#define DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(_name, _help, ...)                                      \
    DECLARE_ESP_ZB_CLI_SUBCMD_LIST(_name, __VA_ARGS__);                                         \
    static const esp_zb_cli_cmd_t _cmd_var_name(_name)                                          \
    ESP_ZB_CLI_CMD_DESC(_name)                                                                  \
    = ESP_ZB_CLI_CMD_WITH_SUB(_name, _name, _help)

esp_err_t esp_zb_cli_process_cmd(esp_zb_cli_cmd_t *cmd, int argc, char **argv);

#ifdef __cplusplus
}
#endif