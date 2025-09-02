/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "esp_check.h"
#include "esp_zigbee_core.h"
#include "zboss_api.h"

#include "esp_zigbee_console.h"
#include "cli_cmd.h"

#define TAG "cli_cmd_misc"

extern void mac_add_visible_device(zb_ieee_addr_t long_addr);
extern void mac_add_invisible_short(zb_uint16_t addr);
extern void mac_clear_filters(void);

static esp_err_t cli_factoryreset(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    if (argc > 1) {
        return ESP_ERR_INVALID_ARG;
    }
    cli_output("Erasing NVRAM of Zigbee stack ... ");
    esp_zb_zcl_reset_nvram_to_factory_default();
    cli_output_line("Done");
    cli_output_line("Reboot the device");
    esp_restart();

    /* Never reached, esp_restart are not expect to return. */
    return ESP_FAIL;
}

static esp_err_t cli_reboot(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    if (argc > 1) {
        return ESP_ERR_INVALID_ARG;
    }
    cli_output_line("Reboot the device");
    esp_restart();

    /* Never reached, esp_restart are not expect to return. */
    return ESP_FAIL;
}

static esp_err_t cli_start(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    if (argc > 1) {
        return ESP_ERR_INVALID_ARG;
    }
    cli_output_line("Start Zigbee stack");

    return esp_zb_start(false);
}

static esp_err_t cli_radio(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    return ESP_ERR_NOT_SUPPORTED;
}

static esp_err_t cli_trace(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    esp_err_t ret = ESP_ERR_NOT_SUPPORTED;
#if defined(CONFIG_ESP_ZB_TRACE_ENABLE) || defined (CONFIG_ZB_DEBUG_MODE)
    struct {
        arg_int_t *level;
        arg_u32_t *mask;
        arg_end_t *end;
    } argtable = {
        .level = arg_intn(NULL, NULL, "<LEVEL>", 1, 1, "trace log level"),
        .mask  = arg_u32n(NULL, NULL,  "<MASK>", 1, 1, "trace mask"),
        .end = arg_end(2),
    };

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    esp_zb_set_trace_level_mask(argtable.level->ival[0], argtable.mask->val[0]);
    ret = ESP_OK;

exit:
#endif
    return ret;
}

static esp_err_t cli_macfilter_add(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    struct {
        arg_lit_t  *invisible;
        arg_addr_t *addr;
        arg_end_t  *end;
    } argtable = {
        .invisible = arg_lit0("i", "invisible", "address is to be filtered out"),
        .addr = arg_addrn(NULL, NULL, "<addr:ADDR>", 1, 1, "device address for filtering"),
        .end = arg_end(2),
    };

    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    esp_zb_zcl_addr_t *addr = &argtable.addr->addr[0];
    /* only supports short address for invisible and ieee address for visible setting. */
    bool is_correct_addr_type = !((argtable.invisible->count > 0) ^ (addr->addr_type == ESP_ZB_ZCL_ADDR_TYPE_SHORT));
    EXIT_ON_FALSE(is_correct_addr_type, ESP_ERR_INVALID_ARG,
                  cli_output("Only %s address is supported!\n", argtable.invisible->count > 0 ? "short" : "ieee"));

    if (argtable.invisible->count > 0) {
        mac_add_invisible_short(addr->u.short_addr);
    } else {
        mac_add_visible_device(addr->u.ieee_addr);
    }

exit:
    return ret;
}

static esp_err_t cli_macfilter_clear(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    if (argc > 1) {
        return ESP_ERR_INVALID_ARG;
    }

    mac_clear_filters();

    return ESP_OK;
}

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

static esp_err_t cli_memory_diag(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_str_t *memory_type;
        arg_end_t *end;
    } argtable = {
        .memory_type = arg_strn(NULL, NULL, "<heap|stack>", 1, 1, "Memory type"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    if (!strcmp(argtable.memory_type->sval[0], "heap")) {
        cli_output("Cur Free Heap: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
        cli_output("Min Free Heap: %d bytes\n", heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT));
        cli_output("Max Free Heap: %d bytes\n", heap_caps_get_total_size(MALLOC_CAP_DEFAULT));
    } else if (!strcmp(argtable.memory_type->sval[0], "stack")) {
        const char *task_name = "Zigbee_main";
        TaskHandle_t task_handle;
        EXIT_ON_FALSE((task_handle = xTaskGetHandle(task_name)) != NULL, ESP_ERR_NOT_FOUND);
        cli_output("Min Free Stack: %d bytes\n", uxTaskGetStackHighWaterMark(task_handle));
    } else {
        EXIT_ON_ERROR(ESP_ERR_INVALID_ARG);
    }

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

DECLARE_ESP_ZB_CLI_CMD(factoryreset, cli_factoryreset,, "Reset the device to factory new immediately");
DECLARE_ESP_ZB_CLI_CMD(reboot,       cli_reboot,,       "Reboot the device immediately");
DECLARE_ESP_ZB_CLI_CMD(radio,        cli_radio,,        "Enable/Disable the radio");
DECLARE_ESP_ZB_CLI_CMD(start,        cli_start,,        "Start Zigbee stack");
DECLARE_ESP_ZB_CLI_CMD(trace,        cli_trace,,        "Configure Zigbee stack trace log");
DECLARE_ESP_ZB_CLI_CMD(memdiag,      cli_memory_diag,,  "Diagnose memory usages");
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(macfilter, "Zigbee stack mac filter management",
    ESP_ZB_CLI_SUBCMD(add,      cli_macfilter_add,      "Add device ieee addr for filter in"),
    ESP_ZB_CLI_SUBCMD(clear,    cli_macfilter_clear,    "Clear all entries in the filter"),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(neighbor, "Neighbor information",
    ESP_ZB_CLI_SUBCMD(table,    cli_neighbor_table,     "Dump the neighbor table on current node."),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(route, "Route information",
    ESP_ZB_CLI_SUBCMD(table,    cli_route_table,        "Dump the route table in current node."),
);
