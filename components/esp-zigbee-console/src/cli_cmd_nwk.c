/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include "ezbee/nwk.h"
#include "ezbee/test_utils.h"

#include "cli_cmd.h"

#define TAG "cli_cmd_nwk"

/* Implementation of "neighbor table" command */

static ezb_err_t cli_neighbor_table(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    static const char *titles[] = {"Index", "Age", "NwkAddr", "MacAddr", "Type", "Rel", "Depth", "LQI", "Cost"};
    static const uint8_t widths[] = {5, 5, 8, 20, 5, 3, 5, 5, 6};
    static const char *dev_type_name[] = {
        [EZB_NWK_DEVICE_TYPE_COORDINATOR] = "ZC",
        [EZB_NWK_DEVICE_TYPE_ROUTER]      = "ZR",
        [EZB_NWK_DEVICE_TYPE_END_DEVICE]  = "ZED",
        [EZB_NWK_DEVICE_TYPE_NONE]        = "UNK",
    };
    static const char rel_name[] = {
        [EZB_NWK_RELATIONSHIP_PARENT]                = 'P', /* Parent */
        [EZB_NWK_RELATIONSHIP_CHILD]                 = 'C', /* Child */
        [EZB_NWK_RELATIONSHIP_SIBLING]               = 'S', /* Sibling */
        [EZB_NWK_RELATIONSHIP_NONE_OF_THE_ABOVE]     = 'O', /* Others */
    };
    ezb_nwk_info_iterator_t itor = EZB_NWK_INFO_ITERATOR_INIT;
    ezb_nwk_neighbor_info_t neighbor = {};

    uint16_t index = 0;
    cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
    while (EZB_ERR_NONE == ezb_nwk_get_next_neighbor(&itor, &neighbor)) {
        cli_output("| %3d | %3d | 0x%04hx | 0x%016" PRIx64 " |",
                    index++, neighbor.age, neighbor.short_addr, neighbor.ieee_addr.u64);
        cli_output(" %3s | %c |", dev_type_name[neighbor.device_type], rel_name[neighbor.relationship]);
        cli_output(" %3d | %3d |  o:%d |", neighbor.depth, neighbor.lqi, neighbor.outgoing_cost);
        cli_output("\n");
    }

    return EZB_ERR_NONE;
}

static ezb_err_t cli_neighbor_cost(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_addr_t *addr;
        arg_u8_t   *c_in;
        arg_u8_t   *c_out;
        arg_end_t  *end;
    } argtable = {
        .addr  = arg_addrn("t", "target", "<addr:ADDR>", 1, 1, "address of the target neighbor"),
        .c_in  = arg_u8n("i", "in", "<u8:COST>", 1, 1, "incoming cost of the neighbor"),
        .c_out = arg_u8n("o", "out", "<u8:COST>", 1, 1, "outgoing cost of the neighbor"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(argtable.addr->addr->addr_type == CLI_ADDR_TYPE_16BIT, EZB_ERR_INV_ARG,
                  cli_output("Only short address is supported\n"));

    ezb_cert_set_route_cost_policy(true, false, false);
    ret = ezb_nwk_set_neighbor_info(argtable.addr->addr->u.addr16, 0,
                                    argtable.c_out->val[0], argtable.c_in->val[0]);

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Implementation of "route table" command */

static ezb_err_t cli_route_table(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    static const char *titles[] = {"Index", "DestAddr", "NextHop", "Expiry", "State", "Flags"};
    static const uint8_t widths[] = {5, 8, 8, 6, 8, 6};
    static const char *route_state_name[] = {
        [EZB_NWK_ROUTE_STATE_ACTIVE] = "Active",
        [EZB_NWK_ROUTE_STATE_DISCOVERY_UNDERWAY] = "Disc",
        [EZB_NWK_ROUTE_STATE_DISCOVERY_FAILED] = "Fail",
        [EZB_NWK_ROUTE_STATE_INACTIVE] = "Inactive",
    };
    ezb_nwk_info_iterator_t itor = EZB_NWK_INFO_ITERATOR_INIT;
    ezb_nwk_route_info_t route = {};

    uint16_t index = 0;
    cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
    while (EZB_ERR_NONE == ezb_nwk_get_next_route(&itor, &route)) {
        cli_output("| %3d | 0x%04hx%c| 0x%04hx | %4d | %6s | 0x%02x |",
                    index++, route.dest_addr, ' ', route.next_hop_addr,
                    route.expiry, route_state_name[route.flags.status], *(uint8_t *)&route.flags);
        cli_output("\n");
    }

    return EZB_ERR_NONE;
}

static ezb_err_t cli_route_delete(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u16_t *dst_addr;
        arg_u16_t *next_hop;
        arg_end_t *end;
    } argtable = {
        .dst_addr = arg_u16n("d", "dst-addr", "<u16:SADDR>", 0, 1, "route to destination to delete"),
        .next_hop = arg_u16n("n", "next-hop", "<u16:SADDR>", 0, 1, "routes to next hop to delete"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.dst_addr->count > 0) {
        ezb_nwk_route_delete(argtable.dst_addr->val[0]);
    }

    if (argtable.next_hop->count > 0) {
        ezb_nwk_route_delete_by_link(argtable.next_hop->val[0]);
    }

exit:
    return ret;
}

/* Implementation of "sroute table" command */

static ezb_err_t cli_sroute_table(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    char path_str[EZB_NWK_MAX_SOURCE_ROUTE * 7] = {0};
    static const char *titles[] = {"Index", "DestAddr", "Expiry", "Path"};
    static const uint8_t widths[] = {5, 8, 6, sizeof(path_str)};
    ezb_nwk_info_iterator_t itor = EZB_NWK_INFO_ITERATOR_INIT;
    ezb_nwk_route_record_info_t rrec = {};

    uint16_t index = 0;
    cli_output_table_header(ARRAY_SIZE(widths), titles, widths);
    while (EZB_ERR_NONE == ezb_nwk_get_next_route_record(&itor, &rrec)) {
        char *path = path_str;
        for (uint8_t i = 0; i < rrec.relay_count; i++) {
            path += sprintf(path, "0x%04hx:", rrec.path[i]);
        }
        *(path - 1) = '\0';

        cli_output("| %3d | 0x%04hx | %4d |%-*s|",
                    index++, rrec.dest_address, rrec.expiry, sizeof(path_str), path_str);
        cli_output("\n");
    }

    return EZB_ERR_NONE;
}

/* Implementation of "concentrator" command */

static ezb_err_t cli_cnctr_start(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u8_t *radius;
        arg_u8_t *discovery_time;
        arg_u8_t *separation_time;
        arg_lit_t *help;
        arg_end_t *end;
    } argtable = {
        .radius = arg_u8n("r",  "radius",  "<u8:RADIUS>", 0, 1, "Discovery radius, default: 30"),
        .discovery_time = arg_u8n("M",  "discovery",  "<u8:TIMEOUT>", 0, 1, "Maximum period in sec to do discovery, default: 60"),
        .separation_time = arg_u8n("m",  "separation",  "<u8:TIMEOUT>", 0, 1, "Minimum period in sec to do discovery, default: 30"),
        .help = arg_lit0(NULL, "help", "Print this help message"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    uint8_t radius = 30;
    uint8_t discovery_time = 60;
    uint8_t separation_time = 30;

    if (argtable.radius->count > 0) {
        radius = argtable.radius->val[0];
    }
    if (argtable.discovery_time->count > 0) {
        discovery_time = argtable.discovery_time->val[0];
    }
    if (argtable.separation_time->count > 0) {
        separation_time = argtable.separation_time->val[0];
    }

    ret = ezb_nwk_concentrator_start(radius, separation_time, discovery_time);

exit:
    return ret;
}

static ezb_err_t cli_cnctr_advise(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    if (argc > 1) {
        return EZB_ERR_INV_ARG;
    }

    return ezb_nwk_concentrator_discovery();
}

static ezb_err_t cli_cnctr_stop(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    if (argc > 1) {
        return EZB_ERR_INV_ARG;
    }

    return ezb_nwk_concentrator_stop();
}

static ezb_err_t cli_nwk_leave_req(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_addr_t *dev_addr;
        arg_lit_t  *rejoin;
        arg_lit_t  *remove_child;
        arg_end_t  *end;
    } argtable = {
        .dev_addr = arg_addrn(NULL, NULL, "<EUI64>",  1, 1, "IEEE address of the device"),
        .rejoin = arg_lit0("r", NULL, "rejoin"),
        .remove_child = arg_lit0("c", NULL, "remove_child"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_FALSE(argtable.dev_addr->addr->addr_type == CLI_ADDR_TYPE_64BIT, EZB_ERR_INV_ARG,
                  cli_output_line("IEEE address is required."));

    ezb_nwk_leave_req_t req = {
        .device_address.u64 = argtable.dev_addr->addr->u.addr64,
        .rejoin = argtable.rejoin->count > 0,
        .remove_children = argtable.remove_child->count > 0,
    };
    ret = ezb_nwk_leave_request(&req);

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_nwk_ed_timeout(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u8_t  *timeout;
        arg_end_t *end;
    } argtable = {
        .timeout = arg_u8n(NULL, NULL, "<u8:TIMEOUT>", 0, 1, "Requested End device timeout value."),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.timeout->count > 0) {
        uint8_t v = argtable.timeout->val[0];
        EXIT_ON_FALSE(v <= EZB_NWK_ED_TIMEOUT_16384MIN, EZB_ERR_INV_ARG,
                      cli_output_line("Invalid timeout, see ezb_nwk_ed_timeout_e"));
        ezb_nwk_set_ed_timeout((ezb_nwk_ed_timeout_t)v);
    } else {
        cli_output("%u\n", ezb_nwk_get_ed_timeout());
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_nwk_keepalive_interval(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u32_t *interval;
        arg_end_t *end;
    } argtable = {
        .interval = arg_u32n(NULL, NULL, "<u32:INTERVAL>", 0, 1, "End device keepalive interval, in milliseconds"),
        .end = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (argtable.interval->count > 0) {
        ezb_nwk_set_keepalive_interval(argtable.interval->val[0]);
    } else {
        cli_output("%" PRIu32 " ms\n", ezb_nwk_get_keepalive_interval());
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(nwk, "Network management",
    ESP_ZB_CLI_SUBCMD(leave, cli_nwk_leave_req, "NLME-LEAVE.request (test only)"),
    ESP_ZB_CLI_SUBCMD(ed_timeout, cli_nwk_ed_timeout, "Get/Set End Device timeout (test only)"),
    ESP_ZB_CLI_SUBCMD(keepalive_interval, cli_nwk_keepalive_interval, "Get/Set Keepalive interval (test only)"),
);

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(neighbor, "Neighbor information",
    ESP_ZB_CLI_SUBCMD(table,    cli_neighbor_table, "Dump the neighbor table on current node."),
    ESP_ZB_CLI_SUBCMD(cost,     cli_neighbor_cost,  "Set the in/out cost of a neighbor. (test only)"),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(route, "Route information",
    ESP_ZB_CLI_SUBCMD(table,    cli_route_table,    "Dump the route table in current node."),
    ESP_ZB_CLI_SUBCMD(delete,   cli_route_delete,   "Delete route. (test only)"),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(sroute, "Source Route information",
    ESP_ZB_CLI_SUBCMD(table,    cli_sroute_table,   "Dump the route record table in current node."),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(concentrator, "NWK Concentrator function",
    ESP_ZB_CLI_SUBCMD(start,  cli_cnctr_start,  "Concentrator start"),
    ESP_ZB_CLI_SUBCMD(advise, cli_cnctr_advise, "Advise an MTO-RREQ"),
    ESP_ZB_CLI_SUBCMD(stop,   cli_cnctr_stop,   "Concentrator stop"),
);
