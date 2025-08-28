/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>

#include "esp_check.h"
#include "esp_zigbee_core.h"

#include "esp_zigbee_console.h"
#include "cli_cmd.h"

#define TAG "cli_cmd_nwk"

/* Implementation of "neighbor table" command */

static esp_err_t cli_neighbor_table(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    static const char *titles[] = {"Index", "Age", "NwkAddr", "MacAddr", "Type", "Rel", "Depth", "LQI", "Cost"};
    static const uint8_t widths[] = {5, 5, 8, 20, 5, 3, 5, 5, 6};
    static const char *dev_type_name[] = {
        [ESP_ZB_DEVICE_TYPE_COORDINATOR] = "ZC",
        [ESP_ZB_DEVICE_TYPE_ROUTER]      = "ZR",
        [ESP_ZB_DEVICE_TYPE_ED]          = "ZED",
        [ESP_ZB_DEVICE_TYPE_NONE]        = "UNK",
    };
    static const char rel_name[] = {
        [ESP_ZB_NWK_RELATIONSHIP_PARENT]                = 'P', /* Parent */
        [ESP_ZB_NWK_RELATIONSHIP_CHILD]                 = 'C', /* Child */
        [ESP_ZB_NWK_RELATIONSHIP_SIBLING]               = 'S', /* Sibling */
        [ESP_ZB_NWK_RELATIONSHIP_NONE_OF_THE_ABOVE]     = 'O', /* Others */
        [ESP_ZB_NWK_RELATIONSHIP_PREVIOUS_CHILD]        = 'c', /* Previous Child */
        [ESP_ZB_NWK_RELATIONSHIP_UNAUTHENTICATED_CHILD] = 'u', /* Unauthenticated Child */
    };
    esp_zb_nwk_info_iterator_t itor = ESP_ZB_NWK_INFO_ITERATOR_INIT;
    esp_zb_nwk_neighbor_info_t neighbor = {};

    cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
    while (ESP_OK == esp_zb_nwk_get_next_neighbor(&itor, &neighbor)) {
        cli_output("| %3d | %3d | 0x%04hx | 0x%016" PRIx64 " |",
                    itor, neighbor.age, neighbor.short_addr, *(uint64_t *)neighbor.ieee_addr);
        cli_output(" %3s | %c |", dev_type_name[neighbor.device_type], rel_name[neighbor.relationship]);
        cli_output(" %3d | %3d |  o:%d |", neighbor.depth, neighbor.lqi, neighbor.outgoing_cost);
        cli_output("\n");
    }

    return ESP_OK;
}

/* Implementation of "route table" command */

static esp_err_t cli_route_table(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    static const char *titles[] = {"Index", "DestAddr", "NextHop", "Expiry", "State", "Flags"};
    static const uint8_t widths[] = {5, 8, 8, 6, 8, 6};
    static const char *route_state_name[] = {
        [ESP_ZB_NWK_ROUTE_STATE_ACTIVE] = "Active",
        [ESP_ZB_NWK_ROUTE_STATE_DISCOVERY_UNDERWAY] = "Disc",
        [ESP_ZB_NWK_ROUTE_STATE_DISCOVERY_FAILED] = "Fail",
        [ESP_ZB_NWK_ROUTE_STATE_INACTIVE] = "Inactive",
    };
    esp_zb_nwk_info_iterator_t itor = ESP_ZB_NWK_INFO_ITERATOR_INIT;
    esp_zb_nwk_route_info_t route = {};

    cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
    while (ESP_OK == esp_zb_nwk_get_next_route(&itor, &route)) {
        cli_output("| %3d | 0x%04hx%c| 0x%04hx | %4d | %6s | 0x%02x |",
                    itor, route.dest_addr, route.flags.group_id ? 'g' : ' ', route.next_hop_addr,
                    route.expiry, route_state_name[route.flags.status], *(uint8_t *)&route.flags);
        cli_output("\n");
    }

    return ESP_OK;
}

/* Implementation of "sroute table" command */

static esp_err_t cli_sroute_table(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    char path_str[ESP_ZB_NWK_MAX_SOURCE_ROUTE * 7] = {0};
    static const char *titles[] = {"Index", "DestAddr", "Expiry", "Path"};
    static const uint8_t widths[] = {5, 8, 6, sizeof(path_str)};
    esp_zb_nwk_info_iterator_t itor = ESP_ZB_NWK_INFO_ITERATOR_INIT;
    esp_zb_nwk_route_record_info_t rrec = {};

    cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
    while (ESP_OK == esp_zb_nwk_get_next_route_record(&itor, &rrec)) {
        char *path = path_str;
        for (uint8_t i = 0; i < rrec.relay_count; i++) {
            path += sprintf(path, "0x%04hx:", rrec.path[i]);
        }
        *(path - 1) = '\0';

        cli_output("| %3d | 0x%04hx | %4d |%-*s|",
                    itor, rrec.dest_address, rrec.expiry, sizeof(path_str), path_str);
        cli_output("\n");
    }

    return ESP_OK;
}

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(neighbor, "Neighbor information",
    ESP_ZB_CLI_SUBCMD(table,    cli_neighbor_table, "Dump the neighbor table on current node."),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(route, "Route information",
    ESP_ZB_CLI_SUBCMD(table,    cli_route_table,    "Dump the route table in current node."),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(sroute, "Source Route information",
    ESP_ZB_CLI_SUBCMD(table,    cli_sroute_table,   "Dump the route record table in current node."),
);
