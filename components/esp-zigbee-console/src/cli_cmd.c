/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "cli_cmd.h"

static void cli_output_cmd_help(uint8_t indent_size, esp_zb_cli_cmd_t *cmd)
{
    if ((cmd->help != NULL) && (strlen(cmd->help) != 0)) {
        if (cmd->sub_cmd_count == 0) {
            cli_output("%*s%-15s %s\n", indent_size, "", cmd->name, cmd->help);
        } else {
            cli_output("%*s%s: %s\n", indent_size, "", cmd->name, cmd->help);
        }
    }
    for (int i = 0; i < cmd->sub_cmd_count; i++) {
        cli_output_cmd_help(indent_size + 4, &cmd->sub_cmds[i]);
    }
}

esp_err_t esp_zb_cli_process_cmd(esp_zb_cli_cmd_t *cmd, int argc, char **argv)
{
    esp_err_t ret = ESP_FAIL;
    /* argv[0] is the name of main command */
    if (argc > 1 && argv[1][0] != '-') {
        /* We got sub commands */
        for (int i = 0; i < cmd->sub_cmd_count; i++) {
            esp_zb_cli_cmd_t *sub_cmd= cmd->sub_cmds + i;
            if (!strcmp(sub_cmd->name, argv[1])) {
                /* Construct 'program name' for the sub-command. */
                argv[1][-1] = ' ';
                argv[1] = argv[0];
                return esp_zb_cli_process_cmd(sub_cmd, argc - 1, &argv[1]);
            }
        }
    }

    /* It's not a sub command, process the main command */
    if (cmd->operation != NULL) {
        ret = cmd->operation(cmd, argc, argv);
    } else {
        cli_output_cmd_help(0, cmd);
        ret = ESP_OK;
    }

    return ret;
}
