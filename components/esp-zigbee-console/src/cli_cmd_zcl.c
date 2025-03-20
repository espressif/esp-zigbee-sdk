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
#include "cmdline_parser.h"
#include "zb_data/zcl.h"
#include "cli_cmd_aps.h"
#include "zb_data/zb_custom_clusters/custom_common.h"

#define TAG "cli_cmd_zcl"

#define cli_output_callback_info(name, info) \
    ESP_LOGI(TAG, "%s: endpoint(%d) cluster(0x%04x)", (name), (info)->dst_endpoint, (info)->cluster);

static void cli_output_attribute(esp_zb_zcl_attribute_t *attr)
{
    uint16_t attr_size = attr->data.size;
    ESP_LOGI(TAG, "- attribute(0x%04x), type(0x%x)", attr->id, attr->data.type);
    ESP_LOG_BUFFER_HEXDUMP(TAG, attr->data.value, attr_size, ESP_LOG_INFO);
}

static esp_err_t zcl_set_attr_value_handler(esp_zb_zcl_set_attr_value_message_t *message)
{
    cli_output_callback_info("Set attribute value", &message->info);

    cli_output_attribute(&message->attribute);

    return ESP_OK;
}

static esp_err_t zcl_read_attr_resp_handler(const esp_zb_zcl_cmd_read_attr_resp_message_t *message)
{
    cli_output_callback_info("Read attribute response", &message->info);

    for (esp_zb_zcl_read_attr_resp_variable_t *variables = message->variables; variables != NULL; variables = variables->next) {
        if (variables->status == ESP_ZB_ZCL_STATUS_SUCCESS) {
            cli_output_attribute(&variables->attribute);
        } else {
            ESP_LOGI(TAG, "- attribute(0x%04x), status(0x%x)", variables->attribute.id, variables->status);
        }
    }

    return ESP_OK;
}

static esp_err_t zcl_report_attr_handler(esp_zb_zcl_report_attr_message_t *message)
{
    cli_output_callback_info("Report attribute", message);

    cli_output_attribute(&message->attribute);

    return ESP_OK;
}

static esp_err_t zcl_write_attr_resp_handler(const esp_zb_zcl_cmd_write_attr_resp_message_t *message)
{
    cli_output_callback_info("Write attribute response", &message->info);

    for (esp_zb_zcl_write_attr_resp_variable_t *variables = message->variables; variables != NULL; variables = variables->next) {
        ESP_LOGI(TAG, "- attribute(0x%04x), status(0x%x)", variables->attribute_id, variables->status);
    }

    return ESP_OK;
}

static esp_err_t zcl_report_cfg_resp_handler(const esp_zb_zcl_cmd_config_report_resp_message_t *message)
{
    cli_output_callback_info("Config report response", &message->info);

    for (esp_zb_zcl_config_report_resp_variable_t *variables = message->variables; variables != NULL; variables = variables->next) {
        ESP_LOGI(TAG, "- attribute(0x%04x), status(0x%x)", variables->attribute_id, variables->status);
    }

    return ESP_OK;
}

static esp_err_t zcl_read_report_cfg_resp_handler(const esp_zb_zcl_cmd_read_report_config_resp_message_t *message)
{
    cli_output_callback_info("Read report configure response", &message->info);

    for (esp_zb_zcl_read_report_config_resp_variable_t *variables = message->variables; variables != NULL; variables = variables->next) {
        ESP_LOGI(TAG, "- attribute(0x%04x), status(0x%x)", variables->attribute_id, variables->status);
        if (variables->status == ESP_ZB_ZCL_STATUS_SUCCESS) {
            if (variables->report_direction == ESP_ZB_ZCL_REPORT_DIRECTION_SEND) {
                /* TODO: support printing varible length of delta */
                ESP_LOGI(TAG, "  min(%d), max(%d), delta(%d)", variables->client.min_interval, variables->client.max_interval, variables->client.delta[0]);
            } else {
                ESP_LOGI(TAG, "  timeout(%d)", variables->server.timeout);
            }
        }
    }
    return ESP_OK;
}

static esp_err_t zcl_disc_attr_resp_handler(const esp_zb_zcl_cmd_discover_attributes_resp_message_t *message)
{
    cli_output_callback_info("Discover attribute response", &message->info);

    for (esp_zb_zcl_disc_attr_variable_t *variables = message->variables; variables != NULL; variables = variables->next) {
        ESP_LOGI(TAG, "- attribute(0x%04x), type(0x%02x)", variables->attr_id, variables->data_type);
    }

    return ESP_OK;
}

static esp_err_t zcl_default_resp_handler(esp_zb_zcl_cmd_default_resp_message_t *message)
{
    cli_output_callback_info("Default response", &message->info);

    ESP_LOGI(TAG, "- command(0x%02x), status(0x%x)", message->resp_to_cmd, message->status_code);

    return ESP_OK;
}

esp_err_t cli_zcl_core_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
{
    esp_err_t ret = ESP_OK;
    switch (callback_id) {
        case ESP_ZB_CORE_SET_ATTR_VALUE_CB_ID:
            ret = zcl_set_attr_value_handler((esp_zb_zcl_set_attr_value_message_t *)message);
            break;
        case ESP_ZB_CORE_CMD_READ_ATTR_RESP_CB_ID:
            ret = zcl_read_attr_resp_handler((esp_zb_zcl_cmd_read_attr_resp_message_t *)message);
            break;
        case ESP_ZB_CORE_REPORT_ATTR_CB_ID:
            ret = zcl_report_attr_handler((esp_zb_zcl_report_attr_message_t *)message);
            break;
        case ESP_ZB_CORE_CMD_WRITE_ATTR_RESP_CB_ID:
            ret = zcl_write_attr_resp_handler((esp_zb_zcl_cmd_write_attr_resp_message_t *)message);
            break;
        case ESP_ZB_CORE_CMD_REPORT_CONFIG_RESP_CB_ID:
            ret = zcl_report_cfg_resp_handler((esp_zb_zcl_cmd_config_report_resp_message_t *)message);
            break;
        case ESP_ZB_CORE_CMD_READ_REPORT_CFG_RESP_CB_ID:
            ret = zcl_read_report_cfg_resp_handler((esp_zb_zcl_cmd_read_report_config_resp_message_t *)message);
            break;
        case ESP_ZB_CORE_CMD_DISC_ATTR_RESP_CB_ID:
            ret = zcl_disc_attr_resp_handler((esp_zb_zcl_cmd_discover_attributes_resp_message_t *)message);
            break;
        case ESP_ZB_CORE_CMD_DEFAULT_RESP_CB_ID:
            ret = zcl_default_resp_handler((esp_zb_zcl_cmd_default_resp_message_t *)message);
            break;
        case ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_RESP_CB_ID:
        case ESP_ZB_CORE_CMD_CUSTOM_CLUSTER_REQ_CB_ID:
            ret = esp_zb_custom_clusters_command_handler((esp_zb_zcl_custom_cluster_command_message_t *)message);
            break;
        default:
            break;
    }
    return ret;
}

/* Implementation of ``dm add`` command */

typedef struct attribute_config_s {
    uint16_t attr_id;
    uint8_t  attr_type;
    uint8_t  attr_access;
    uint16_t manuf_code;
    void*    attr_value_p;
} attribute_config_t;

typedef struct cluster_config_s {
    uint16_t cluster_id;
    uint16_t role_mask;
    uint16_t manuf_code;
    attribute_config_t *attr_cfg;
} cluster_config_t;

typedef struct endpoint_config_s {
    uint8_t ep_id;
    uint8_t device_ver;
    uint16_t profile_id;
    uint16_t device_id;
    cluster_config_t *cluster_cfg;
} endpoint_config_t;

typedef struct cli_zcl_add_params_s {
    bool force;
    endpoint_config_t *endpoint_cfg;
} cli_zcl_add_params_t;

static esp_err_t zcl_add_attribute(esp_zb_attribute_list_t *attr_list, attribute_config_t* attr_cfg, bool force)
{
    esp_err_t ret = ESP_OK;
    EXIT_ON_FALSE(attr_cfg, ESP_OK); /* Exit with success, do thing */
    EXIT_ON_FALSE(attr_cfg->attr_id != 0xFFFF, ESP_ERR_INVALID_ARG);
    EXIT_ON_FALSE(attr_list, ESP_ERR_INVALID_ARG);
    EXIT_ON_FALSE(attr_cfg->attr_value_p, ESP_ERR_INVALID_ARG, cli_output_line("Invalid attribute value"));

    EXIT_ON_ERROR(force ? esp_zb_cluster_add_manufacturer_attr(attr_list, attr_list->next->cluster_id, attr_cfg->attr_id, attr_cfg->manuf_code,
                                                               attr_cfg->attr_type, attr_cfg->attr_access, attr_cfg->attr_value_p)
                        : esp_zb_cluster_add_std_attr(attr_list, attr_cfg->attr_id, attr_cfg->attr_value_p),
                  cli_output_line("Fail to add attribute"));

exit:
    return ret;
}

static esp_err_t zcl_add_cluster(esp_zb_cluster_list_t *cluster_list, cluster_config_t *cluster_cfg, bool force)
{
    esp_err_t ret = ESP_OK;
    esp_zb_attribute_list_t *attr_list = NULL;
    bool new_created = false;

    EXIT_ON_FALSE(cluster_cfg, ESP_OK); /* Exit with success, do thing */
    EXIT_ON_FALSE(cluster_cfg->cluster_id != 0xFFFF, ESP_ERR_INVALID_ARG);
    EXIT_ON_FALSE(cluster_list, ESP_ERR_INVALID_ARG);

    attr_list = esp_zb_cluster_list_get_cluster(cluster_list, cluster_cfg->cluster_id, cluster_cfg->role_mask);

    if (attr_list == NULL) {
        attr_list = force ? esp_zb_zcl_attr_list_create(cluster_cfg->cluster_id)
                          : esp_zb_cluster_create_default(cluster_cfg->cluster_id);
        new_created = true;
    }

    EXIT_ON_ERROR(zcl_add_attribute(attr_list, cluster_cfg->attr_cfg, force));

    if (new_created) {
        EXIT_ON_ERROR(esp_zb_cluster_register(cluster_list, attr_list, cluster_cfg->role_mask),
                      cli_output_line("Fail to add created cluster"));
    }

    return ESP_OK;

exit:
    if (new_created && attr_list) {
        free(attr_list);
    }
    return ret;
}

static esp_err_t zcl_add_endpoint(esp_zb_ep_list_t *ep_list, endpoint_config_t* endpoint_cfg, bool force)
{
    esp_err_t ret = ESP_OK;
    esp_zb_cluster_list_t *cluster_list = NULL;
    bool new_created = false;

    EXIT_ON_FALSE(endpoint_cfg, ESP_OK); /* Exit with success, do thing */
    EXIT_ON_FALSE(endpoint_cfg->ep_id != 0 && endpoint_cfg->ep_id != 0xFF, ESP_ERR_INVALID_ARG);
    EXIT_ON_FALSE(ep_list, ESP_ERR_INVALID_ARG);

    cluster_list = esp_zb_ep_list_get_ep(ep_list, endpoint_cfg->ep_id);

    if (cluster_list == NULL) {
        cluster_list = esp_zb_zcl_cluster_list_create();
        new_created = true;
    }

    EXIT_ON_ERROR(zcl_add_cluster(cluster_list, endpoint_cfg->cluster_cfg, force));

    if (new_created) {
        esp_zb_endpoint_config_t ep_config = {
            .endpoint = endpoint_cfg->ep_id,
            .app_profile_id = endpoint_cfg->profile_id,
            .app_device_id = endpoint_cfg->device_id,
            .app_device_version = endpoint_cfg->device_ver,
        };
        EXIT_ON_ERROR(esp_zb_ep_list_add_ep(ep_list, cluster_list, ep_config),
                      cli_output_line("Fail to add created endpoint"));
    }

    return ESP_OK;

exit:
    if (new_created && cluster_list) {
        free(cluster_list);
    }
    return ret;
}

static esp_err_t cli_dm_add_parse_params(int argc, char *argv[], cli_zcl_add_params_t *params)
{
    struct {
        arg_lit_t   *force;
        arg_u8_t    *ep_id;
        arg_u16_t   *cluster_id;
        arg_u16_t   *attr_id;
        arg_devid_t *device_id;
        arg_u8_t    *device_ver;
        arg_u16_t   *profile_id;
        arg_u16_t   *manuf_code;
        arg_str_t   *role_mask;
        arg_str_t   *attr_access;
        arg_u8_t    *attr_type;
        arg_hex_t   *attr_value;
        arg_end_t   *end;
    } argtable = {
        .force       = arg_lit0("f",    "force",                         "force add, no checks"),
        .ep_id       = arg_u8n("e",     "endpoint", "<u8:EID>",    0, 1, "EID, id of the operating endpoint"),
        .cluster_id  = arg_u16n("c",    "cluster",  "<u16:CID>",   0, 1, "CID, id of the operating cluster"),
        .attr_id     = arg_u16n("a",    "attr",     "<u16:AID>",   0, 1, "AID, id of the operating attribute"),
        .device_id   = arg_devidn(NULL, "device",   "<u16:DID>",   0, 1, "set the device id (DID) of the endpoint"),
        .device_ver  = arg_u8n(NULL,    "version",  "<u8:VER>",    0, 1, "set the device version of the endpoint"),
        .profile_id  = arg_u16n(NULL,   "profile",  "<u16:PID>",   0, 1, "set the profile id (PID) of the endpoint"),
        .manuf_code  = arg_u16n(NULL,   "manuf",    "<u16:CODE>",  0, 1, "set CODE of the manufacture"),
        .role_mask   = arg_str0("r",    "role",     "<sc:C|S>",          "set the role the cluster, default: S"),
        .attr_access = arg_str0(NULL,   "access",   "<mc:R|W|P|S>",      "set access of the attribute, default: RW"),
        .attr_type   = arg_u8n(NULL,    "type",     "<u8:TID>",    0, 1, "TID, ZCL attribute type id"),
        .attr_value  = arg_hexn("v",    "value",    "<hex:value>", 0, 1, "set value of the attribute, raw data in HEX"),
        .end = arg_end(2),
    };

    esp_err_t ret = ESP_OK;
    endpoint_config_t *endpoint_cfg = NULL;
    cluster_config_t *cluster_cfg = NULL;
    attribute_config_t *attribute_cfg = NULL;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    /* Endpoint related options */
    if (argtable.ep_id->count > 0) {
        endpoint_cfg = malloc(sizeof(endpoint_config_t));
        endpoint_cfg->ep_id = argtable.ep_id->val[0];
        endpoint_cfg->profile_id = ESP_ZB_AF_HA_PROFILE_ID;
        endpoint_cfg->device_id = ESP_ZB_HA_TEST_DEVICE_ID;
        endpoint_cfg->device_ver = 0;
        endpoint_cfg->cluster_cfg = NULL;
    }
    if (argtable.device_id->count > 0) {
        if (endpoint_cfg) {
            endpoint_cfg->device_id = argtable.device_id->val[0];
        }
    }
    if (argtable.device_ver->count > 0) {
        if (endpoint_cfg) {
            endpoint_cfg->device_ver = argtable.device_ver->val[0];
        }
    }
    if (argtable.profile_id->count > 0) {
        if (endpoint_cfg) {
            endpoint_cfg->profile_id = argtable.profile_id->val[0];
        }
    }

    /* Cluster related options */
    if (argtable.cluster_id->count > 0) {
        if (endpoint_cfg) {
            cluster_cfg = malloc(sizeof(cluster_config_t));
            cluster_cfg->cluster_id = argtable.cluster_id->val[0];
            cluster_cfg->manuf_code = EZP_ZB_ZCL_CLUSTER_NON_MANUFACTURER_SPECIFIC;
            cluster_cfg->role_mask = ESP_ZB_ZCL_CLUSTER_SERVER_ROLE;
            cluster_cfg->attr_cfg = NULL;
            endpoint_cfg->cluster_cfg = cluster_cfg;
        }
    }
    if (argtable.role_mask->count > 0) {
        if (cluster_cfg) {
            switch (argtable.role_mask->sval[0][0]) {
                case 'C':
                case 'c':
                    cluster_cfg->role_mask = ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE;
                    break;
                case 'S':
                case 's':
                    cluster_cfg->role_mask = ESP_ZB_ZCL_CLUSTER_SERVER_ROLE;
                    break;
                default:
                    EXIT_ON_ERROR(ESP_ERR_INVALID_ARG, cli_output_line("zcl add: invalid argument to option --role"));
                    break;
            }
        }
    }

    /* Attribute related options */
    if (argtable.attr_id->count > 0) {
        if (cluster_cfg) {
            attribute_cfg = malloc(sizeof(attribute_config_t));
            attribute_cfg->attr_id = argtable.attr_id->val[0];
            attribute_cfg->attr_type = ESP_ZB_ZCL_ATTR_TYPE_INVALID;
            attribute_cfg->attr_access = ESP_ZB_ZCL_ATTR_ACCESS_READ_WRITE;
            attribute_cfg->manuf_code = ESP_ZB_ZCL_ATTR_NON_MANUFACTURER_SPECIFIC;
            attribute_cfg->attr_value_p = NULL;
            cluster_cfg->attr_cfg = attribute_cfg;
        }
    }
    if (argtable.attr_access->count > 0) {
        if (attribute_cfg) {
            EXIT_ON_ERROR(parse_attr_access(argtable.attr_access->sval[0], &attribute_cfg->attr_access),
                          cli_output_line("zcl add: invalid argument to option --access"));
        }
    }
    if (argtable.attr_type->count > 0) {
        if (attribute_cfg) {
            attribute_cfg->attr_type = argtable.attr_type->val[0];
        }
    }
    if (argtable.attr_value->count > 0) {
        if (attribute_cfg) {
            attribute_cfg->attr_value_p = argtable.attr_value->hval[0];
            argtable.attr_value->hval[0] = NULL;
        }
    }

    /* Other common options */
    if (argtable.manuf_code->count > 0) {
        if (cluster_cfg) {
            cluster_cfg->manuf_code = argtable.manuf_code->val[0];
        }
        if (attribute_cfg) {
            attribute_cfg->manuf_code = argtable.manuf_code->val[0];
        }
    }
    if (argtable.force->count > 0) {
        params->force = true;
    }

exit:
    params->endpoint_cfg = endpoint_cfg;
    arg_hex_free(argtable.attr_value);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_dm_add(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    esp_err_t ret = ESP_OK;
    cli_zcl_add_params_t params = { 0 };
    esp_zb_ep_list_t *ep_list = CLI_CTX().ep_list;
    EXIT_ON_FALSE(CLI_CTX().ep_list, ESP_ERR_NOT_SUPPORTED, cli_output_line("Data model has been registered"));

    EXIT_ON_ERROR(cli_dm_add_parse_params(argc, argv, &params));
    EXIT_ON_ERROR(zcl_add_endpoint(ep_list, params.endpoint_cfg, params.force));

exit:
    if (params.endpoint_cfg) {
        if (params.endpoint_cfg->cluster_cfg) {
            if (params.endpoint_cfg->cluster_cfg->attr_cfg) {
                if (params.endpoint_cfg->cluster_cfg->attr_cfg->attr_value_p) {
                    free(params.endpoint_cfg->cluster_cfg->attr_cfg->attr_value_p);
                }
                free(params.endpoint_cfg->cluster_cfg->attr_cfg);
            }
            free(params.endpoint_cfg->cluster_cfg);
        }
        free(params.endpoint_cfg);
    }
    return ret;
}

/* Implementation of ``dm show`` command */

#define LIST_ITERATE(head, node)                                               \
    for ((node) = (head); (node); (node) = (node)->next)

static const char s_level_prefix[] = {'\0', ' ', ' ', ' ', '\0'};

static inline void zcl_attr_println(const esp_zb_zcl_attr_t *attr)
{
    cli_output("attr:0x%04x, type:0x%02x, access:0x%02x, manuf:0x%04x\n", attr->id, attr->type, attr->access, attr->manuf_code);
}

static inline void zcl_cluster_println(const esp_zb_zcl_cluster_t *cluster)
{
    cli_output("cluster:0x%04x, %c, manuf:0x%04x\n",
               cluster->cluster_id, cluster->role_mask == 1 ? 'S' : 'C', cluster->manuf_code);
}

static inline void zcl_ep_println(const esp_zb_endpoint_t *ep)
{
    cli_output("ep:%d, prfl:0x%04x, dev_id:0x%04x, dev_ver:%d\n",
               ep->ep_id, ep->profile_id, ((esp_zb_endpoint_config_t*)(ep->reserved_ptr))->app_device_id,
               ((esp_zb_endpoint_config_t*)(ep->reserved_ptr))->app_device_version);
}

static void dm_show_attr_list(const esp_zb_attribute_list_t *attr_list, const char *prefix)
{
    LIST_ITERATE(attr_list->next, attr_list) {
        const esp_zb_zcl_attr_t *attr = &attr_list->attribute;
        cli_output(prefix);
        if (attr_list->next) {
            cli_output("|-- ");
        } else {
            cli_output("+-- ");
        }
        zcl_attr_println(attr);
    }
}

static void dm_show_cluster_list(const esp_zb_cluster_list_t *cluster_list, char *prefix)
{
    assert(prefix != NULL);
    int prefix_len = strlen(prefix);
    memcpy(prefix + prefix_len, s_level_prefix, sizeof(s_level_prefix));
    LIST_ITERATE(cluster_list->next, cluster_list) {
        const esp_zb_zcl_cluster_t *cluster = &cluster_list->cluster;
        cli_output(prefix);
        if (cluster_list->next) {
            prefix[prefix_len] = '|';
            cli_output("|-- ");
        } else {
            prefix[prefix_len] = ' ';
            cli_output("+-- ");
        }
        zcl_cluster_println(cluster);
        dm_show_attr_list(cluster->attr_list, prefix);
        prefix[prefix_len] = '\0';
    }
}

static void dm_show_ep_list(const esp_zb_ep_list_t *ep_list, char *prefix)
{
    assert(prefix != NULL);
    int prefix_len = strlen(prefix);
    memcpy(prefix + prefix_len, s_level_prefix, sizeof(s_level_prefix));
    LIST_ITERATE(ep_list->next, ep_list) {
        const esp_zb_endpoint_t *ep = &ep_list->endpoint;
        cli_output(prefix);
        if (ep_list->next) {
            prefix[prefix_len] = '|';
            cli_output("|-- ");
        } else {
            prefix[prefix_len] = ' ';
            cli_output("+-- ");
        }
        zcl_ep_println(ep);
        dm_show_cluster_list(ep->cluster_list, prefix);
        prefix[prefix_len] = '\0';
    }
}

/**
 * @brief Show current ZCL data model.
 *
 */
static esp_err_t cli_dm_show(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    ESP_UNUSED(argv);

    esp_err_t ret = ESP_OK;
    EXIT_ON_FALSE(argc == 1, ESP_ERR_INVALID_ARG);

    /* Dump the data model */
    esp_zb_ep_list_t *ep_list = CLI_CTX().ep_list;

    if (ep_list) {
        char prefix[10] = {0};
        dm_show_ep_list(ep_list, prefix);
    } else {
        /* TODO: Dump the registered data model */
    }

exit:
    return ret;
}

/* Implementation of ``dm register`` command */

/**
 * @brief Register current ZCL data model.
 *
 */
static esp_err_t cli_dm_register(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    (void)argv;
    esp_err_t ret = ESP_OK;
    EXIT_ON_FALSE(argc == 1, ESP_ERR_INVALID_ARG);

    EXIT_ON_FALSE(CLI_CTX().ep_list, ESP_ERR_NOT_SUPPORTED, cli_output_line("Data model has been registered"));
    /* We forbid registration after stack started for time being. */
    EXIT_ON_FALSE(!esp_zb_is_started(), ESP_ERR_NOT_SUPPORTED, cli_output_line("Can not register after stack started"));
    EXIT_ON_ERROR(esp_zb_device_register(CLI_CTX().ep_list), cli_output_line("Fail to register the ZCL data model"));
    CLI_CTX().ep_list = NULL;

exit:
    return ret;
}

static esp_err_t cli_dm_read(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u8_t    *ep_id;
        arg_u16_t   *cluster_id;
        arg_u16_t   *attr_id;
        arg_u16_t   *manuf_code;
        arg_str_t   *role_mask;
        arg_end_t   *end;
    } argtable = {
        .ep_id       = arg_u8n("e",   "endpoint", "<u8:EID>",   1, 1, "EID, id of the operating endpoint"),
        .cluster_id  = arg_u16n("c",  "cluster",  "<u16:CID>",  1, 1, "CID, id of the operating cluster"),
        .attr_id     = arg_u16n("a",  "attr",     "<u16:AID>",  1, 1, "AID, id of the operating attribute"),
        .manuf_code  = arg_u16n(NULL, "manuf",    "<u16:CODE>", 0, 1, "manufacture code"),
        .role_mask   = arg_str0("r",  "role",     "<sc:C|S>",         "role of the cluster, default: S"),
        .end = arg_end(2),
    };
    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    uint16_t manuf_code = ESP_ZB_ZCL_ATTR_NON_MANUFACTURER_SPECIFIC;
    uint8_t role_mask = ESP_ZB_ZCL_CLUSTER_SERVER_ROLE;
    if (argtable.manuf_code->count > 0) {
        manuf_code = argtable.manuf_code->val[0];
    }
    if (argtable.role_mask->count > 0) {
        switch (argtable.role_mask->sval[0][0]) {
            case 'C':
            case 'c':
                role_mask = ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE;
                break;
            case 'S':
            case 's':
                role_mask = ESP_ZB_ZCL_CLUSTER_SERVER_ROLE;
                break;
            default:
                EXIT_ON_ERROR(ESP_ERR_INVALID_ARG, cli_output("%s: invalid argument to option --role\n", argv[0]));
                break;
        }
    }

    EXIT_ON_FALSE(CLI_CTX().ep_list == NULL, ESP_ERR_INVALID_STATE, cli_output_line("Please register the data model first"));
    esp_zb_zcl_attr_t *attr = esp_zb_zcl_get_manufacturer_attribute(argtable.ep_id->val[0],
                                                                    argtable.cluster_id->val[0],
                                                                    role_mask,
                                                                    argtable.attr_id->val[0],
                                                                    manuf_code);
    EXIT_ON_FALSE(attr, ESP_ERR_NOT_FOUND, cli_output_line("Attribute not found"));
    cli_output_buffer(attr->data_p, esp_zb_zcl_get_attribute_size(attr->type, attr->data_p));

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static esp_err_t cli_dm_write(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_lit_t   *force;
        arg_u8_t    *ep_id;
        arg_u16_t   *cluster_id;
        arg_u16_t   *attr_id;
        arg_u16_t   *manuf_code;
        arg_str_t   *role_mask;
        arg_hex_t   *attr_value;
        arg_end_t   *end;
    } argtable = {
        .force       = arg_lit0("f",  "force",                         "force add, no checks"),
        .ep_id       = arg_u8n("e",   "endpoint", "<u8:EID>",    1, 1, "EID, id of the operating endpoint"),
        .cluster_id  = arg_u16n("c",  "cluster",  "<u16:CID>",   1, 1, "CID, id of the operating cluster"),
        .attr_id     = arg_u16n("a",  "attr",     "<u16:AID>",   1, 1, "AID, id of the operating attribute"),
        .manuf_code  = arg_u16n(NULL, "manuf",    "<u16:CODE>",  0, 1, "manufacture code"),
        .role_mask   = arg_str0("r",  "role",     "<sc:C|S>",          "role of the cluster, default: S"),
        .attr_value  = arg_hexn("v",  "value",    "<hex:VALUE>", 1, 1, "value of the attribute, raw data in HEX"),
        .end = arg_end(2),
    };

    esp_err_t ret = ESP_OK;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    uint16_t manuf_code = ESP_ZB_ZCL_ATTR_NON_MANUFACTURER_SPECIFIC;
    uint8_t role_mask = ESP_ZB_ZCL_CLUSTER_SERVER_ROLE;
    if (argtable.manuf_code->count > 0) {
        manuf_code = argtable.manuf_code->val[0];
    }
    if (argtable.role_mask->count > 0) {
        switch (argtable.role_mask->sval[0][0]) {
            case 'C':
            case 'c':
                role_mask = ESP_ZB_ZCL_CLUSTER_CLIENT_ROLE;
                break;
            case 'S':
            case 's':
                role_mask = ESP_ZB_ZCL_CLUSTER_SERVER_ROLE;
                break;
            default:
                EXIT_ON_ERROR(ESP_ERR_INVALID_ARG, cli_output("%s: invalid argument to option --role\n", argv[0]));
                break;
        }
    }

    EXIT_ON_FALSE(CLI_CTX().ep_list == NULL, ESP_ERR_INVALID_STATE, cli_output_line("Please register the data model first"));
    esp_zb_zcl_status_t result = esp_zb_zcl_set_manufacturer_attribute_val(argtable.ep_id->val[0],
                                                                           argtable.cluster_id->val[0],
                                                                           role_mask,
                                                                           manuf_code,
                                                                           argtable.attr_id->val[0],
                                                                           argtable.attr_value->hval[0],
                                                                           !(argtable.force->count > 0));

    EXIT_ON_FALSE(result == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_FAIL, cli_output("Fail to write attribute: %d\n", result));

exit:
    arg_hex_free(argtable.attr_value);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Implementation of ``zcl <general_cmd>`` commands */

static esp_err_t cli_zcl_attr_cmd(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        esp_zb_cli_aps_argtable_t aps;
        arg_str_t  *peer_role;
        arg_u16_t  *attr_id;
        arg_u16_t  *manuf_code;
        arg_u8_t   *attr_type;
        arg_hex_t  *attr_value;
        arg_end_t  *end;
    } argtable = {
        .peer_role  = arg_strn("r", "role",  "<sc:C|S>",    0, 1, "role of the peer cluster, default: S"),
        .attr_id    = arg_u16n("a", "attr",  "<u16:AID>",   0, 1, "id of the operating attribute"),
        .manuf_code = arg_u16n(NULL,"manuf", "<u16:CODE>",  0, 1, "set CODE of the manufacture"),
        .attr_type  = arg_u8n("t",  "type",  "<u8:TID>",    0, 1, "ZCL attribute type id"),
        .attr_value = arg_hexn("v", "value", "<hex:DATA>",  0, 1, "value of the attribute, raw data in HEX"),
        .end = arg_end(2),
    };
    esp_zb_cli_fill_aps_argtable(&argtable.aps);

    esp_err_t ret = ESP_OK;
    const char *cmd = self->name;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    /* Default request settings */
    union {
        struct {
            esp_zb_zcl_basic_cmd_t zcl_basic_cmd;
            esp_zb_zcl_address_mode_t address_mode;
            uint16_t cluster_id;
            struct {
                uint8_t manuf_specific   : 2;
                uint8_t direction        : 1;
                uint8_t dis_defalut_resp : 1;
            };
            uint16_t manuf_code;
        };
        esp_zb_zcl_read_attr_cmd_t          read_req;
        esp_zb_zcl_write_attr_cmd_t         write_req;
        esp_zb_zcl_report_attr_cmd_t        report_req;
        esp_zb_zcl_config_report_cmd_t      config_report_req;
        esp_zb_zcl_read_report_config_cmd_t read_report_config_req;
        esp_zb_zcl_disc_attr_cmd_t          disc_attr;
    } req_params = {
        .address_mode = ESP_ZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT,
    };

    EXIT_ON_ERROR(esp_zb_cli_parse_aps_dst(&argtable.aps,
                                           &req_params.zcl_basic_cmd.dst_addr_u,
                                           &req_params.zcl_basic_cmd.dst_endpoint,
                                           &req_params.address_mode,
                                           &req_params.zcl_basic_cmd.src_endpoint,
                                           &req_params.cluster_id, NULL));

    if (argtable.peer_role->count > 0) {
        switch (argtable.peer_role->sval[0][0]) {
            case 'C':
            case 'c':
                req_params.direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_CLI;
                break;
            case 'S':
            case 's':
                req_params.direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV;
                break;
            default:
                EXIT_ON_ERROR(ESP_ERR_INVALID_ARG, cli_output_line("invalid argument to option -r"));
                break;
        }
    }

    if (argtable.manuf_code->count > 0) {
        if (argtable.manuf_code->val[0] != ESP_ZB_ZCL_ATTR_NON_MANUFACTURER_SPECIFIC) {
            req_params.manuf_specific = 1;
            req_params.manuf_code = argtable.manuf_code->val[0];
        }
    }

    if (!strcmp(cmd, "read")) {
        req_params.read_req.attr_number = argtable.attr_id->count;
        req_params.read_req.attr_field = argtable.attr_id->val;
        esp_zb_zcl_read_attr_cmd_req(&req_params.read_req);
    } else if (!strcmp(cmd, "write")) {
        int n = argtable.attr_id->count;
        esp_zb_zcl_attribute_t attr_field[n]; /* VLA */
        EXIT_ON_FALSE(n == argtable.attr_type->count &&
                      n == argtable.attr_value->count, ESP_ERR_INVALID_ARG,
                      cli_output("%s: unbalanced options of --attr, --type, --value\n", cmd));
        for (int i = 0; i < n; i++) {
            attr_field[i].id = argtable.attr_id->val[i];
            attr_field[i].data.type = argtable.attr_type->val[i];
            attr_field[i].data.value = argtable.attr_value->hval[i];
            attr_field[i].data.size = argtable.attr_value->hsize[i];
        }
        req_params.write_req.attr_number = n;
        req_params.write_req.attr_field = attr_field;
        esp_zb_zcl_write_attr_cmd_req(&req_params.write_req);
    } else if (!strcmp(cmd, "report")) {
        EXIT_ON_FALSE(argtable.attr_id->count > 0, ESP_ERR_INVALID_ARG, cli_output("%s: -a <u16:AID> is required\n", cmd));
        req_params.report_req.attributeID = argtable.attr_id->val[0];
        ret = esp_zb_zcl_report_attr_cmd_req(&req_params.report_req);
    } else if (!strcmp(cmd, "config_rp")) {
        int n = argtable.attr_id->count;
        uint64_t report_change = 0;
        esp_zb_zcl_config_report_record_t rprt_cfg_records[n];
        EXIT_ON_FALSE(n == argtable.attr_type->count, ESP_ERR_INVALID_ARG,
                      cli_output("%s: unbalanced options of --attr and --type\n", cmd));
        for (int i = 0; i < n; i++) {
            rprt_cfg_records[i].direction = ESP_ZB_ZCL_REPORT_DIRECTION_SEND;
            rprt_cfg_records[i].attributeID = argtable.attr_id->val[i];
            rprt_cfg_records[i].attrType = argtable.attr_type->val[i];
            /* TODO: Support configuring the report intervals */
            rprt_cfg_records[i].min_interval = 0;
            rprt_cfg_records[i].max_interval = 30;
            rprt_cfg_records[i].reportable_change = &report_change;
        }
        req_params.config_report_req.record_number = n;
        req_params.config_report_req.record_field = rprt_cfg_records;
        esp_zb_zcl_config_report_cmd_req(&req_params.config_report_req);
    } else if (!strcmp(cmd, "read_rp_cfg")) {
        int n = argtable.attr_id->count;
        esp_zb_zcl_attribute_record_t attr_records[n]; /* VLA */
        for (int i = 0; i < n; i++) {
            attr_records[i].report_direction = ESP_ZB_ZCL_REPORT_DIRECTION_SEND;
            attr_records[i].attributeID = argtable.attr_id->val[i];
        }
        req_params.read_report_config_req.record_number = n;
        req_params.read_report_config_req.record_field = attr_records;
        esp_zb_zcl_read_report_config_cmd_req(&req_params.read_report_config_req);
    } else if (!strcmp(cmd, "disc_attr")) {
        req_params.disc_attr.start_attr_id = 0x0000;
        req_params.disc_attr.max_attr_number = 30;
        esp_zb_zcl_disc_attr_cmd_req(&req_params.disc_attr);
    } else {
        ret = ESP_ERR_NOT_SUPPORTED;
    }

exit:
    arg_hex_free(argtable.attr_value);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/* Implementation of ``zcl send_raw`` command */

static esp_err_t cli_zcl_send_raw(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        esp_zb_cli_aps_argtable_t aps;
        arg_str_t  *peer_role;
        arg_u8_t   *command;
        arg_hex_t  *payload;
        arg_lit_t  *dry_run;
        arg_end_t  *end;
    } argtable = {
        .peer_role = arg_strn("r",  "role",     "<sc:C|S>",    0, 1, "role of the peer cluster, default: S"),
        .command   = arg_u8n(NULL,  "cmd",      "<u8:CMD_ID>", 1, 1, "identifier of the command"),
        .payload   = arg_hexn("p",  "payload",  "<hex:DATA>",  0, 1, "ZCL payload of the command, raw HEX data"),
        .dry_run   = arg_lit0("n",  "dry-run", "print the request being sent"),
        .end = arg_end(2),
    };
    esp_zb_cli_fill_aps_argtable(&argtable.aps);

    esp_err_t ret = ESP_OK;
    /* Default request settings */
    esp_zb_zcl_custom_cluster_cmd_req_t req_params = {
        .address_mode = ESP_ZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT,
        .profile_id = ESP_ZB_AF_HA_PROFILE_ID,
        .direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
    };

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, ESP_OK, arg_print_help((void**)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void**)&argtable);
    EXIT_ON_FALSE(nerrors == 0, ESP_ERR_INVALID_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_ERROR(esp_zb_cli_parse_aps_dst(&argtable.aps,
                                           &req_params.zcl_basic_cmd.dst_addr_u,
                                           &req_params.zcl_basic_cmd.dst_endpoint,
                                           &req_params.address_mode,
                                           &req_params.zcl_basic_cmd.src_endpoint,
                                           &req_params.cluster_id,
                                           &req_params.profile_id));

    if (argtable.peer_role->count > 0) {
        switch (argtable.peer_role->sval[0][0]) {
            case 'C':
            case 'c':
                req_params.direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_CLI;
                break;
            case 'S':
            case 's':
                req_params.direction = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV;
                break;
            default:
                EXIT_ON_ERROR(ESP_ERR_INVALID_ARG, cli_output_line("invalid argument to option -r"));
                break;
        }
    }
    if (argtable.payload->count > 0) {
        req_params.data.value = argtable.payload->hval[0];
        req_params.data.size = argtable.payload->hsize[0];
        req_params.data.type = ESP_ZB_ZCL_ATTR_TYPE_SET; /* A workarround to send arbitrary data */
    }

    /* DO NOT need a check, this option is mandatory */
    req_params.custom_cmd_id = argtable.command->val[0];

    if (argtable.dry_run->count == 0) {
        esp_zb_zcl_custom_cluster_cmd_req(&req_params);
    } else {
        cli_output_line("Send request:");
        cli_output("Mode[%d]: e:%d -> e:%d, ",
                   req_params.address_mode,
                   req_params.zcl_basic_cmd.src_endpoint, req_params.zcl_basic_cmd.dst_endpoint);
        if(req_params.address_mode == ESP_ZB_APS_ADDR_MODE_64_ENDP_PRESENT) {
            cli_output("addr:0x%016" PRIx64, *(uint64_t*)(&req_params.zcl_basic_cmd.dst_addr_u.addr_long));
        } else {
            cli_output("addr:0x%04" PRIx16, req_params.zcl_basic_cmd.dst_addr_u.addr_short);
        }
        cli_output_line("");
        cli_output("prfl:0x%04x, c:0x%04x, dir:%c, cmd:0x%02x\n", req_params.profile_id, req_params.cluster_id,
                   req_params.direction == ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV ? 'S' : 'C',
                   req_params.custom_cmd_id);
        if (req_params.data.value) {
            cli_output_buffer(req_params.data.value, req_params.data.size);
        }
        cli_output_line("");
    }

exit:
    arg_hex_free(argtable.payload);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(dm, "ZigBee Cluster Library data model management",
    ESP_ZB_CLI_SUBCMD(show,     cli_dm_show,     "Show current data model"),
    ESP_ZB_CLI_SUBCMD(add,      cli_dm_add,      "Add items in ZCL data model"),
    ESP_ZB_CLI_SUBCMD(register, cli_dm_register, "Register current data model"),
    ESP_ZB_CLI_SUBCMD(read,     cli_dm_read,     "Read attribute value in data model"),
    ESP_ZB_CLI_SUBCMD(write,    cli_dm_write,    "Write value to attribute in data model"),
);

DECLARE_ESP_ZB_CLI_SUBCMD_LIST(zcl_send_gen,
    ESP_ZB_CLI_SUBCMD(read,        cli_zcl_attr_cmd, "Read attribute"),
    ESP_ZB_CLI_SUBCMD(write,       cli_zcl_attr_cmd, "Write attribute"),
    ESP_ZB_CLI_SUBCMD(report,      cli_zcl_attr_cmd, "Report attribute"),
    ESP_ZB_CLI_SUBCMD(config_rp,   cli_zcl_attr_cmd, "Configure reporting"),
    ESP_ZB_CLI_SUBCMD(read_rp_cfg, cli_zcl_attr_cmd, "Read reporting configuration"),
    ESP_ZB_CLI_SUBCMD(disc_attr,   cli_zcl_attr_cmd, "Discover attributes"),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(zcl, "ZigBee Cluster Library management",
    ESP_ZB_CLI_CMD_WITH_SUB(send_gen, zcl_send_gen,     "Send general command"),
    ESP_ZB_CLI_SUBCMD(send_raw,       cli_zcl_send_raw, "Send cluster specific raw command"),
);
