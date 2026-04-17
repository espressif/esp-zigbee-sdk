/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include "ezbee/zcl.h"

#include "esp_zigbee_console.h"
#include "cli_cmd.h"
#include "cli_cmd_aps.h"

#include "zb_data/zcl.h"
#include "zb_data/zb_custom_clusters/custom_common.h"

#define TAG "cli_cmd_zcl"

#define DEV_CTX() (CLI_CTX().ep_list)

#define cli_output_callback_info(name, info) \
    cli_output("%s: endpoint(%d) cluster(0x%04x)\n", (name), (info)->dst_ep, (info)->cluster_id);

static uint8_t zcl_get_attr_delta_str(uint8_t *delta, uint8_t attr_type, char *buf, uint8_t buf_len)
{
    uint8_t  dummy     = 0;
    uint8_t  str_len   = 0;
    uint16_t attr_size = ezb_zcl_get_attr_value_size(attr_type, &dummy);
    switch (attr_type) {
    case EZB_ZCL_ATTR_TYPE_UINT8:
    case EZB_ZCL_ATTR_TYPE_UINT16:
    case EZB_ZCL_ATTR_TYPE_UINT24:
    case EZB_ZCL_ATTR_TYPE_UINT32:
    case EZB_ZCL_ATTR_TYPE_UINT40:
    case EZB_ZCL_ATTR_TYPE_UINT48:
    case EZB_ZCL_ATTR_TYPE_UINT56:
    case EZB_ZCL_ATTR_TYPE_UINT64:
        uint64_t val = 0;
        memcpy(&val, delta, attr_size);
        str_len = snprintf(buf, buf_len, "%" PRIu64, val);
        break;
    case EZB_ZCL_ATTR_TYPE_INT8:
    case EZB_ZCL_ATTR_TYPE_INT16:
    case EZB_ZCL_ATTR_TYPE_INT24:
    case EZB_ZCL_ATTR_TYPE_INT32:
    case EZB_ZCL_ATTR_TYPE_INT40:
    case EZB_ZCL_ATTR_TYPE_INT48:
    case EZB_ZCL_ATTR_TYPE_INT56:
    case EZB_ZCL_ATTR_TYPE_INT64:
        int64_t sval = 0;
        memcpy(&sval, delta, attr_size);
        int shift = (8 * (sizeof(sval) - attr_size));
        sval      = (sval << shift) >> shift;
        str_len   = snprintf(buf, buf_len, "%" PRId64, sval);
        break;
    case EZB_ZCL_ATTR_TYPE_SINGLE:
        float f = 0.0;
        memcpy(&f, delta, attr_size);
        str_len = snprintf(buf, buf_len, "%.2f", f);
        break;
    case EZB_ZCL_ATTR_TYPE_DOUBLE:
        double d = 0.0;
        memcpy(&d, delta, attr_size);
        str_len = snprintf(buf, buf_len, "%.2f", d);
        break;
    case EZB_ZCL_ATTR_TYPE_TOD:
        str_len = snprintf(buf, buf_len, "%02u:%02u:%02u.%02u",
                           /* hour */ delta[0], /* minute */ delta[1], /* second */ delta[2], /* hundredth */ delta[3]);

        break;
    case EZB_ZCL_ATTR_TYPE_DATE:
        const char *week_str[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
        str_len                = snprintf(buf, buf_len, "%02u-%02u-%02u-%s",
                                          /* year */ delta[0], /* month */ delta[1], /* day_of_month */ delta[2],
                                          /* day_of_week */ week_str[delta[3] - 1]);
        break;
    case EZB_ZCL_ATTR_TYPE_UTC:
        uint32_t utc;
        memcpy(&utc, delta, attr_size);
        str_len = snprintf(buf, buf_len, "%lu", (unsigned long)utc);
        break;
    case EZB_ZCL_ATTR_TYPE_SEMI:
        str_len = snprintf(buf, buf_len, "0x%02X%02X", delta[0], delta[1]);
        break;
    default:
        break;
    }

    buf[str_len] = '\0';
    return str_len;
}

static void cli_output_attribute(ezb_zcl_attribute_t *attr)
{
    uint16_t attr_size = attr->data.size;
    cli_output("- attribute(0x%04x), type(0x%x)", attr->id, attr->data.type);
    cli_output_buffer(attr->data.value, attr_size);
}

static ezb_err_t zcl_set_attr_value_handler(ezb_zcl_set_attr_value_message_t *message)
{
    cli_output_callback_info("Set attribute value", &message->info);

    cli_output_attribute(&message->in.attribute);

    return EZB_ERR_NONE;
}

static ezb_err_t zcl_read_attr_rsp_handler(const ezb_zcl_cmd_read_attr_rsp_message_t *message)
{
    cli_output_callback_info("Read attribute response", &message->info);

    for (ezb_zcl_read_attr_rsp_variable_t *var = message->in.variables; var != NULL; var = var->next) {
        if (var->status == EZB_ZCL_STATUS_SUCCESS) {
            cli_output("- attribute(0x%04x), type(0x%x)", var->attr_id, var->attr_type);
            uint16_t size = ezb_zcl_get_attr_value_size(var->attr_type, var->attr_value);
            cli_output_buffer(var->attr_value, size != UINT16_MAX ? size : 0);
        } else {
            cli_output("- attribute(0x%04x), status(0x%x)\n", var->attr_id, var->status);
        }
    }

    return EZB_ERR_NONE;
}

static ezb_err_t zcl_report_attr_handler(ezb_zcl_cmd_report_attr_message_t *message)
{
    cli_output_callback_info("Report attribute", &message->info);

    for (ezb_zcl_report_attr_variable_t *var = message->in.variables; var != NULL; var = var->next) {
        cli_output("- attribute(0x%04x), type(0x%x)\n", var->attr_id, var->attr_type);
        uint16_t size = ezb_zcl_get_attr_value_size(var->attr_type, var->attr_value);
        cli_output_buffer(var->attr_value, size != UINT16_MAX ? size : 0);
    }
    return EZB_ERR_NONE;
}

static ezb_err_t zcl_write_attr_rsp_handler(const ezb_zcl_cmd_write_attr_rsp_message_t *message)
{
    cli_output_callback_info("Write attribute response", &message->info);

    for (ezb_zcl_write_attr_rsp_variable_t *var = message->in.variables; var != NULL; var = var->next) {
        cli_output("- attribute(0x%04x), status(0x%x)\n", var->attr_id, var->status);
    }

    return EZB_ERR_NONE;
}

static ezb_err_t zcl_report_cfg_rsp_handler(const ezb_zcl_cmd_config_report_rsp_message_t *message)
{
    cli_output_callback_info("Config report response", &message->info);

    for (ezb_zcl_config_report_rsp_variable_t *var = message->in.variables; var != NULL; var = var->next) {
        cli_output("- attribute(0x%04x), status(0x%x)\n", var->attr_id, var->status);
    }

    return EZB_ERR_NONE;
}

static ezb_err_t zcl_read_report_cfg_rsp_handler(const ezb_zcl_cmd_read_report_config_rsp_message_t *message)
{
#define ZCL_ATTR_DELTA_STR_MAX_LEN 64
    char delta_str[ZCL_ATTR_DELTA_STR_MAX_LEN] = {0};
    cli_output_callback_info("Read report configure response", &message->info);
    for (ezb_zcl_read_report_config_rsp_variable_t *var = message->in.variables; var != NULL; var = var->next) {
        cli_output("- attribute(0x%04x), status(0x%x)", var->attr_id, var->status);
        if (var->status == EZB_ZCL_STATUS_SUCCESS) {
            if (var->direction == EZB_ZCL_REPORTING_SEND) {
                zcl_get_attr_delta_str((uint8_t *)&var->client.delta, var->client.attr_type, delta_str,
                                       ZCL_ATTR_DELTA_STR_MAX_LEN);
                cli_output(": min(%d), max(%d), delta(%s)\n", var->client.min_interval, var->client.max_interval, delta_str);
            } else {
                cli_output(": timeout(%d)\n", var->server.timeout);
            }
        }
    }
    return EZB_ERR_NONE;
}

static ezb_err_t zcl_disc_attr_rsp_handler(const ezb_zcl_cmd_discover_attributes_rsp_message_t *message)
{
    cli_output_callback_info("Discover attribute response", &message->info);

    for (ezb_zcl_disc_attr_variable_t *var = message->in.variables; var != NULL; var = var->next) {
        cli_output("- attribute(0x%04x), type(0x%02x)\n", var->attr_id, var->attr_type);
    }

    return EZB_ERR_NONE;
}

static ezb_err_t zcl_default_rsp_handler(ezb_zcl_cmd_default_rsp_message_t *message)
{
    cli_output_callback_info("Default response", &message->info);

    cli_output("- command(0x%02x), status(0x%x)\n", message->in.rsp_to_cmd, message->in.status_code);

    return EZB_ERR_NONE;
}

void ezb_cli_zcl_general_action_handler(ezb_zcl_core_action_callback_id_t callback_id, void *message)
{
    ezb_err_t error = EZB_ERR_NONE;

    cli_output("Receive Zigbee action(0x%lx) callback\n", callback_id);

    switch (callback_id) {
    case EZB_ZCL_CORE_SET_ATTR_VALUE_CB_ID:
        error = zcl_set_attr_value_handler((ezb_zcl_set_attr_value_message_t *)message);
        break;
    case EZB_ZCL_CORE_READ_ATTR_RSP_CB_ID:
        error = zcl_read_attr_rsp_handler((ezb_zcl_cmd_read_attr_rsp_message_t *)message);
        break;
    case EZB_ZCL_CORE_REPORT_ATTR_CB_ID:
        error = zcl_report_attr_handler((ezb_zcl_cmd_report_attr_message_t *)message);
        break;
    case EZB_ZCL_CORE_WRITE_ATTR_RSP_CB_ID:
        error = zcl_write_attr_rsp_handler((ezb_zcl_cmd_write_attr_rsp_message_t *)message);
        break;
    case EZB_ZCL_CORE_CONFIG_REPORT_RSP_CB_ID:
        error = zcl_report_cfg_rsp_handler((ezb_zcl_cmd_config_report_rsp_message_t *)message);
        break;
    case EZB_ZCL_CORE_READ_REPORT_CONFIG_RSP_CB_ID:
        error = zcl_read_report_cfg_rsp_handler((ezb_zcl_cmd_read_report_config_rsp_message_t *)message);
        break;
    case EZB_ZCL_CORE_DISC_ATTR_RSP_CB_ID:
        error = zcl_disc_attr_rsp_handler((ezb_zcl_cmd_discover_attributes_rsp_message_t *)message);
        break;
    case EZB_ZCL_CORE_DEFAULT_RSP_CB_ID:
        error = zcl_default_rsp_handler((ezb_zcl_cmd_default_rsp_message_t *)message);
        break;
    default:
        error = EZB_ERR_NOT_SUPPORTED;
        break;
    }

    if (error != EZB_ERR_NONE) {
        cli_output("Failed to handle ZCL action(0x%lx) callback, error: 0x%x\n", callback_id, error);
    }

    return;
}

static const char  s_level_prefix[] = {'\0', ' ', ' ', ' ', '\0'};
static inline void zcl_attr_println(const ezb_zcl_attr_desc_t attr)
{
    cli_output("attr:0x%04x, type:0x%02x, access:0x%02x, manuf:0x%04x\n", ezb_zcl_attr_desc_get_id(attr),
               ezb_zcl_attr_desc_get_type(attr), ezb_zcl_attr_desc_get_access(attr), ezb_zcl_attr_desc_get_manuf_code(attr));
}

static inline void zcl_cluster_println(const ezb_zcl_cluster_desc_t cluster)
{
    cli_output("cluster:0x%04x, %c, manuf:0x%04x\n", ezb_zcl_cluster_desc_get_id(cluster),
               ezb_zcl_cluster_desc_get_role(cluster) == EZB_ZCL_CLUSTER_SERVER ? 'S' : 'C',
               ezb_zcl_cluster_desc_get_manuf_code(cluster));
}

static inline void zcl_ep_println(const ezb_af_ep_desc_t ep)
{
    const ezb_af_simple_desc_t *simple_desc = ezb_af_ep_desc_get_simple_desc(ep);
    cli_output("ep:%d, prfl:0x%04x, dev_id:0x%04x, dev_ver:%d\n", ezb_af_ep_desc_get_ep_id(ep),
               ezb_af_ep_desc_get_profile_id(ep), simple_desc ? simple_desc->app_device_id : 0,
               simple_desc ? simple_desc->app_device_version : 0);
}

static void dm_show_attr_desc(const ezb_zcl_cluster_desc_t cluster_desc, const char *prefix)
{
    ezb_zcl_attr_desc_t attr_desc = EZB_INVALID_ZCL_ATTR_DESC;

    while ((attr_desc = ezb_zcl_cluster_get_next_attr_desc(cluster_desc, attr_desc)) != EZB_INVALID_ZCL_ATTR_DESC) {
        cli_output("%s", prefix);
        if (ezb_zcl_cluster_get_next_attr_desc(cluster_desc, attr_desc) != EZB_INVALID_ZCL_ATTR_DESC) {
            cli_output("|-- ");
        } else {
            cli_output("+-- ");
        }
        zcl_attr_println(attr_desc);
    }
}

static void dm_show_cluster_desc(const ezb_af_ep_desc_t ep_desc, char *prefix)
{
    assert(prefix != NULL);
    int prefix_len = strlen(prefix);
    memcpy(prefix + prefix_len, s_level_prefix, sizeof(s_level_prefix));
    ezb_zcl_cluster_desc_t cluster_desc = EZB_INVALID_ZCL_CLUSTER_DESC;
    while ((cluster_desc = ezb_af_ep_desc_get_next_cluster_desc(ep_desc, cluster_desc)) != EZB_INVALID_ZCL_CLUSTER_DESC) {
        cli_output("%s", prefix);
        if (ezb_af_ep_desc_get_next_cluster_desc(ep_desc, cluster_desc) != EZB_INVALID_ZCL_CLUSTER_DESC) {
            prefix[prefix_len] = '|';
            cli_output("|-- ");
        } else {
            prefix[prefix_len] = ' ';
            cli_output("+-- ");
        }
        zcl_cluster_println(cluster_desc);
        dm_show_attr_desc(cluster_desc, prefix);
        prefix[prefix_len] = '\0';
    }
}

static void dm_show_device_desc(const ezb_af_device_desc_t dev_desc, char *prefix)
{
    assert(prefix != NULL);
    int prefix_len = strlen(prefix);
    memcpy(prefix + prefix_len, s_level_prefix, sizeof(s_level_prefix));
    ezb_af_ep_desc_t ep_desc = EZB_INVALID_AF_EP_DESC;
    while ((ep_desc = ezb_af_device_desc_get_next_endpoint_desc(dev_desc, ep_desc)) != EZB_INVALID_AF_EP_DESC) {
        cli_output("%s", prefix);
        if (ezb_af_device_desc_get_next_endpoint_desc(dev_desc, ep_desc) == EZB_INVALID_AF_EP_DESC) {
            prefix[prefix_len] = '|';
            cli_output("|-- ");
        } else {
            prefix[prefix_len] = ' ';
            cli_output("+-- ");
        }
        zcl_ep_println(ep_desc);
        dm_show_cluster_desc(ep_desc, prefix);
        prefix[prefix_len] = '\0';
    }
}

static ezb_err_t cli_dm_show(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    (void)(argv);

    ezb_err_t ret = EZB_ERR_NONE;
    EXIT_ON_FALSE(argc == 1, EZB_ERR_INV_ARG);

    EXIT_ON_FALSE(DEV_CTX(), EZB_ERR_INV_STATE);

    char prefix[10] = {0};
    dm_show_device_desc(DEV_CTX(), prefix);

exit:
    return ret;
}

typedef struct attribute_config_s {
    uint16_t attr_id;
    uint8_t  attr_type;
    uint8_t  attr_access;
    uint16_t manuf_code;
    void    *attr_value_p;
} attribute_config_t;

typedef struct cluster_config_s {
    uint16_t            cluster_id;
    uint16_t            role_mask;
    uint16_t            manuf_code;
    attribute_config_t *attr_cfg;
} cluster_config_t;

typedef struct endpoint_config_s {
    uint8_t           ep_id;
    uint8_t           device_ver;
    uint16_t          profile_id;
    uint16_t          device_id;
    cluster_config_t *cluster_cfg;
} endpoint_config_t;

typedef struct cli_zcl_add_params_s {
    bool               force;
    endpoint_config_t *endpoint_cfg;
} cli_zcl_add_params_t;

static ezb_err_t cli_dm_add_parse_params(int argc, char *argv[], cli_zcl_add_params_t *params)
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
        .force       = arg_lit0("f", "force", "force add, no checks"),
        .ep_id       = arg_u8n("e", "endpoint", "<u8:EID>", 0, 1, "EID, id of the operating endpoint"),
        .cluster_id  = arg_u16n("c", "cluster", "<u16:CID>", 0, 1, "CID, id of the operating cluster"),
        .attr_id     = arg_u16n("a", "attr", "<u16:AID>", 0, 1, "AID, id of the operating attribute"),
        .device_id   = arg_devidn(NULL, "device", "<u16:DID>", 0, 1, "set the device id (DID) of the endpoint"),
        .device_ver  = arg_u8n(NULL, "version", "<u8:VER>", 0, 1, "set the device version of the endpoint"),
        .profile_id  = arg_u16n(NULL, "profile", "<u16:PID>", 0, 1, "set the profile id (PID) of the endpoint"),
        .manuf_code  = arg_u16n(NULL, "manuf", "<u16:CODE>", 0, 1, "set CODE of the manufacture"),
        .role_mask   = arg_str0("r", "role", "<sc:C|S>", "set the role the cluster, default: S"),
        .attr_access = arg_str0(NULL, "access", "<mc:R|W|P|S>", "set access of the attribute, default: RW"),
        .attr_type   = arg_u8n(NULL, "type", "<u8:TID>", 0, 1, "TID, ZCL attribute type id"),
        .attr_value  = arg_hexn("v", "value", "<hex:value>", 0, 1, "set value of the attribute, raw data in HEX"),
        .end         = arg_end(2),
    };

    ezb_err_t           ret           = EZB_ERR_NONE;
    endpoint_config_t  *endpoint_cfg  = NULL;
    cluster_config_t   *cluster_cfg   = NULL;
    attribute_config_t *attribute_cfg = NULL;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    /* Endpoint related options */
    if (argtable.ep_id->count > 0) {
        endpoint_cfg              = malloc(sizeof(endpoint_config_t));
        endpoint_cfg->ep_id       = argtable.ep_id->val[0];
        endpoint_cfg->profile_id  = EZB_AF_HA_PROFILE_ID;
        endpoint_cfg->device_id   = 0;
        endpoint_cfg->device_ver  = 0;
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
            cluster_cfg               = malloc(sizeof(cluster_config_t));
            cluster_cfg->cluster_id   = argtable.cluster_id->val[0];
            cluster_cfg->manuf_code   = EZB_ZCL_STD_MANUF_CODE;
            cluster_cfg->role_mask    = EZB_ZCL_CLUSTER_SERVER;
            cluster_cfg->attr_cfg     = NULL;
            endpoint_cfg->cluster_cfg = cluster_cfg;
        }
    }
    if (argtable.role_mask->count > 0) {
        if (cluster_cfg) {
            switch (argtable.role_mask->sval[0][0]) {
            case 'C':
            case 'c':
                cluster_cfg->role_mask = EZB_ZCL_CLUSTER_CLIENT;
                break;
            case 'S':
            case 's':
                cluster_cfg->role_mask = EZB_ZCL_CLUSTER_SERVER;
                break;
            default:
                EXIT_ON_ERROR(EZB_ERR_INV_ARG, cli_output_line("zcl add: invalid argument to option --role"));
                break;
            }
        }
    }

    /* Attribute related options */
    if (argtable.attr_id->count > 0) {
        if (cluster_cfg) {
            attribute_cfg               = malloc(sizeof(attribute_config_t));
            attribute_cfg->attr_id      = argtable.attr_id->val[0];
            attribute_cfg->attr_type    = EZB_ZCL_ATTR_TYPE_UNK;
            attribute_cfg->attr_access  = EZB_ZCL_ATTR_ACCESS_READ_WRITE;
            attribute_cfg->manuf_code   = EZB_ZCL_STD_MANUF_CODE;
            attribute_cfg->attr_value_p = NULL;
            cluster_cfg->attr_cfg       = attribute_cfg;
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
            attribute_cfg->attr_value_p  = argtable.attr_value->hval[0];
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

static ezb_err_t zcl_add_attr_desc(uint16_t               cluster_id,
                                   ezb_zcl_cluster_desc_t cluster_desc,
                                   attribute_config_t    *attr_cfg,
                                   bool                   force)
{
    ezb_err_t ret = EZB_ERR_NONE;
    EXIT_ON_FALSE(attr_cfg, EZB_ERR_NONE); /* Exit with success, do thing */
    EXIT_ON_FALSE(attr_cfg->attr_id != 0xFFFF, EZB_ERR_INV_ARG);
    EXIT_ON_FALSE(cluster_desc, EZB_ERR_INV_ARG);
    EXIT_ON_FALSE(attr_cfg->attr_value_p, EZB_ERR_INV_ARG, cli_output_line("Invalid attribute value"));

    printf("attr_id, attr_type, attr_access, attr_manuf_code: %d, %d, %d, %d\n", attr_cfg->attr_id, attr_cfg->attr_type,
           attr_cfg->attr_access, attr_cfg->manuf_code);
    EXIT_ON_ERROR(force ? ezb_zcl_cluster_add_attr_desc(cluster_desc,
                                                        ezb_zcl_create_attr_desc(attr_cfg->attr_id, attr_cfg->attr_type,
                                                                                 attr_cfg->attr_access, attr_cfg->manuf_code,
                                                                                 attr_cfg->attr_value_p))
                        : ezb_cluster_desc_add_std_attr(cluster_id, cluster_desc, attr_cfg->attr_id, attr_cfg->attr_value_p),
                  cli_output_line("Fail to add attribute"));

exit:
    return ret;
}

static ezb_err_t zcl_add_cluster_desc(ezb_af_ep_desc_t ep_desc, cluster_config_t *cluster_cfg, bool force)
{
    ezb_err_t              ret         = EZB_ERR_NONE;
    ezb_zcl_cluster_desc_t cluster     = NULL;
    bool                   new_created = false;

    EXIT_ON_FALSE(cluster_cfg, EZB_ERR_NONE); /* Exit with success, do thing */
    EXIT_ON_FALSE(cluster_cfg->cluster_id != 0xFFFF, EZB_ERR_INV_ARG);
    EXIT_ON_FALSE(ep_desc, EZB_ERR_INV_ARG);

    cluster = ezb_af_endpoint_get_cluster_desc(ep_desc, cluster_cfg->cluster_id, cluster_cfg->role_mask);

    if (cluster == NULL) {
        cluster     = force ? NULL : ezb_cluster_desc_create_default(cluster_cfg->cluster_id, cluster_cfg->role_mask);
        new_created = true;
    }

    EXIT_ON_ERROR(zcl_add_attr_desc(cluster_cfg->cluster_id, cluster, cluster_cfg->attr_cfg, force));

    if (new_created) {
        EXIT_ON_ERROR(ezb_cluster_desc_register(ep_desc, cluster_cfg->cluster_id, cluster, cluster_cfg->role_mask),
                      cli_output_line("Fail to add created cluster"));
    }

    return EZB_ERR_NONE;

exit:
    if (new_created && cluster) {
        free(cluster);
    }
    return ret;
}

static ezb_err_t zcl_add_ep_desc(ezb_af_device_desc_t dev_desc, endpoint_config_t *endpoint_cfg, bool force)
{
    ezb_err_t        ret         = EZB_ERR_NONE;
    ezb_af_ep_desc_t ep_desc     = NULL;
    bool             new_created = false;

    EXIT_ON_FALSE(endpoint_cfg, EZB_ERR_NONE); /* Exit with success, do thing */
    EXIT_ON_FALSE(endpoint_cfg->ep_id != 0 && endpoint_cfg->ep_id != 0xFF, EZB_ERR_INV_ARG);
    EXIT_ON_FALSE(dev_desc, EZB_ERR_INV_ARG);

    ep_desc = ezb_af_device_get_endpoint_desc(dev_desc, endpoint_cfg->ep_id);

    if (ep_desc == NULL) {
        ezb_af_ep_config_t ep_config = {
            .ep_id              = endpoint_cfg->ep_id,
            .app_profile_id     = endpoint_cfg->profile_id,
            .app_device_id      = endpoint_cfg->device_id,
            .app_device_version = endpoint_cfg->device_ver,
        };
        ep_desc     = ezb_af_create_endpoint_desc(&ep_config);
        new_created = true;
    }

    EXIT_ON_ERROR(zcl_add_cluster_desc(ep_desc, endpoint_cfg->cluster_cfg, force));

    if (new_created) {
        EXIT_ON_ERROR(ezb_af_device_add_endpoint_desc(dev_desc, ep_desc), cli_output_line("Fail to add created endpoint"));
    }

    return EZB_ERR_NONE;

exit:
    if (new_created && ep_desc) {
        free(ep_desc);
    }
    return ret;
}

static ezb_err_t cli_dm_add(esp_zb_cli_cmd_t *self, int argc, char *argv[])
{
    ezb_err_t            ret    = EZB_ERR_NONE;
    cli_zcl_add_params_t params = {0};
    EXIT_ON_FALSE(DEV_CTX(), EZB_ERR_NOT_SUPPORTED, cli_output_line("Data model has been registered"));

    EXIT_ON_ERROR(cli_dm_add_parse_params(argc, argv, &params));
    EXIT_ON_ERROR(zcl_add_ep_desc(DEV_CTX(), params.endpoint_cfg, params.force));

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

static ezb_err_t cli_dm_register(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    (void)argv;
    ezb_err_t ret = EZB_ERR_NONE;
    EXIT_ON_FALSE(argc == 1, EZB_ERR_INV_ARG);

    EXIT_ON_FALSE(DEV_CTX(), EZB_ERR_NOT_SUPPORTED, cli_output_line("Data model has been registered"));
    /* We forbid registration after stack started for time being. */
    EXIT_ON_FALSE(!false, EZB_ERR_NOT_SUPPORTED, cli_output_line("Can not register after stack started"));
    EXIT_ON_ERROR(ezb_af_device_desc_register(DEV_CTX()), cli_output_line("Fail to register the ZCL data model"));
    ezb_zcl_core_action_handler_register(ezb_cli_zcl_general_action_handler);

exit:
    return ret;
}

static ezb_err_t cli_dm_read(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_u8_t  *ep_id;
        arg_u16_t *cluster_id;
        arg_u16_t *attr_id;
        arg_u16_t *manuf_code;
        arg_str_t *role_mask;
        arg_end_t *end;
    } argtable = {
        .ep_id      = arg_u8n("e", "endpoint", "<u8:EID>", 1, 1, "EID, id of the operating endpoint"),
        .cluster_id = arg_u16n("c", "cluster", "<u16:CID>", 1, 1, "CID, id of the operating cluster"),
        .attr_id    = arg_u16n("a", "attr", "<u16:AID>", 1, 1, "AID, id of the operating attribute"),
        .manuf_code = arg_u16n(NULL, "manuf", "<u16:CODE>", 0, 1, "manufacture code"),
        .role_mask  = arg_str0("r", "role", "<sc:C|S>", "role of the cluster, default: S"),
        .end        = arg_end(2),
    };
    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    uint16_t manuf_code = EZB_ZCL_STD_MANUF_CODE;
    uint8_t  role_mask  = EZB_ZCL_CLUSTER_SERVER;
    if (argtable.manuf_code->count > 0) {
        manuf_code = argtable.manuf_code->val[0];
    }
    if (argtable.role_mask->count > 0) {
        switch (argtable.role_mask->sval[0][0]) {
        case 'C':
        case 'c':
            role_mask = EZB_ZCL_CLUSTER_CLIENT;
            break;
        case 'S':
        case 's':
            role_mask = EZB_ZCL_CLUSTER_SERVER;
            break;
        default:
            EXIT_ON_ERROR(EZB_ERR_INV_ARG, cli_output("%s: invalid argument to option --role\n", argv[0]));
            break;
        }
    }

    ezb_zcl_attr_desc_t attr = ezb_zcl_get_attr_desc(argtable.ep_id->val[0], argtable.cluster_id->val[0], role_mask,
                                                     argtable.attr_id->val[0], manuf_code);
    EXIT_ON_FALSE(attr, EZB_ERR_NOT_FOUND, cli_output_line("Attribute not found"));
    ezb_zcl_attr_type_t attr_type = ezb_zcl_attr_desc_get_type(attr);
    uint16_t            size      = (ezb_zcl_attr_type_is_analog(attr_type) || ezb_zcl_attr_type_is_discrete(attr_type))
                                        ? 8
                                        : ezb_zcl_attr_desc_get_value_size(attr);
   uint8_t *value = NULL;
   value = malloc(size);
   ezb_zcl_attr_desc_get_value(attr, value);
   cli_output_buffer(value, size);
   free(value);

exit:
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_dm_write(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        arg_lit_t *force;
        arg_u8_t  *ep_id;
        arg_u16_t *cluster_id;
        arg_u16_t *attr_id;
        arg_u16_t *manuf_code;
        arg_str_t *role_mask;
        arg_hex_t *attr_value;
        arg_end_t *end;
    } argtable = {
        .force      = arg_lit0("f", "force", "force add, no checks"),
        .ep_id      = arg_u8n("e", "endpoint", "<u8:EID>", 1, 1, "EID, id of the operating endpoint"),
        .cluster_id = arg_u16n("c", "cluster", "<u16:CID>", 1, 1, "CID, id of the operating cluster"),
        .attr_id    = arg_u16n("a", "attr", "<u16:AID>", 1, 1, "AID, id of the operating attribute"),
        .manuf_code = arg_u16n(NULL, "manuf", "<u16:CODE>", 0, 1, "manufacture code"),
        .role_mask  = arg_str0("r", "role", "<sc:C|S>", "role of the cluster, default: S"),
        .attr_value = arg_hexn("v", "value", "<hex:VALUE>", 1, 1, "value of the attribute, raw data in HEX"),
        .end        = arg_end(2),
    };

    ezb_err_t ret = EZB_ERR_NONE;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    uint16_t manuf_code = EZB_ZCL_STD_MANUF_CODE;
    uint8_t  role_mask  = EZB_ZCL_CLUSTER_SERVER;
    if (argtable.manuf_code->count > 0) {
        manuf_code = argtable.manuf_code->val[0];
    }
    if (argtable.role_mask->count > 0) {
        switch (argtable.role_mask->sval[0][0]) {
        case 'C':
        case 'c':
            role_mask = EZB_ZCL_CLUSTER_CLIENT;
            break;
        case 'S':
        case 's':
            role_mask = EZB_ZCL_CLUSTER_SERVER;
            break;
        default:
            EXIT_ON_ERROR(EZB_ERR_INV_ARG, cli_output("%s: invalid argument to option --role\n", argv[0]));
            break;
        }
    }

    ezb_zcl_status_t result =
        ezb_zcl_set_attr_value(argtable.ep_id->val[0], argtable.cluster_id->val[0], role_mask, argtable.attr_id->val[0],
                               manuf_code, argtable.attr_value->hval[0], !(argtable.force->count > 0));

    EXIT_ON_FALSE(result == EZB_ZCL_STATUS_SUCCESS, EZB_ERR_FAIL, cli_output("Fail to write attribute: %d\n", result));

exit:
    arg_hex_free(argtable.attr_value);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_zcl_parse_aps_argtable(esp_zb_cli_aps_argtable_t *parsed_argtable, ezb_zcl_cmd_ctrl_t *cmd_ctrl)
{
    return esp_zb_cli_parse_aps_dst(parsed_argtable, &cmd_ctrl->dst_addr,
                                    &cmd_ctrl->dst_ep, &cmd_ctrl->src_ep,
                                    &cmd_ctrl->cluster_id, NULL);
}

static ezb_err_t cli_zcl_attr_cmd(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        esp_zb_cli_aps_argtable_t aps;
        arg_str_t                *peer_role;
        arg_u16_t                *attr_id;
        arg_u16_t                *manuf_code;
        arg_u8_t                 *attr_type;
        arg_hex_t                *attr_value;
        arg_u16_t                *min_interval;
        arg_u16_t                *max_interval;
        arg_hex_t                *reportable_change;
        arg_end_t                *end;
    } argtable = {
        .peer_role         = arg_strn("r", "role", "<sc:C|S>", 0, 1, "role of the peer cluster, default: S"),
        .attr_id           = arg_u16n("a", "attr", "<u16:AID>", 0, 1, "id of the operating attribute"),
        .manuf_code        = arg_u16n(NULL, "manuf", "<u16:CODE>", 0, 1, "set CODE of the manufacture"),
        .attr_type         = arg_u8n("t", "type", "<u8:TID>", 0, 1, "ZCL attribute type id"),
        .attr_value        = arg_hexn("v", "value", "<hex:DATA>", 0, 1, "value of the attribute, raw data in HEX"),
        .min_interval      = arg_u16n(NULL, "min", "<u16:MIN>", 0, 1, "min reporting interval in seconds, default: 0"),
        .max_interval      = arg_u16n(NULL, "max", "<u16:MAX>", 0, 1, "max reporting interval in seconds, default: 30"),
        .reportable_change = arg_hexn(NULL, "delta", "<hex:DATA>", 0, 1, "min change of attribute report in HEX"),
        .end               = arg_end(2),
    };
    esp_zb_cli_fill_aps_argtable(&argtable.aps);

    ezb_err_t   ret = EZB_ERR_NONE;
    const char *cmd = self->name;

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    /* Default request settings */
    union {
        ezb_zcl_cmd_ctrl_t               cmd_ctrl;
        ezb_zcl_read_attr_cmd_t          read_req;
        ezb_zcl_write_attr_cmd_t         write_req;
        ezb_zcl_report_attr_cmd_t        report_req;
        ezb_zcl_config_report_cmd_t      config_report_req;
        ezb_zcl_read_report_config_cmd_t read_report_config_req;
        ezb_zcl_disc_attr_cmd_t          disc_attr;
    } req_params = {
        .cmd_ctrl.dst_addr.addr_mode = EZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT,
        .cmd_ctrl.fc.direction       = EZB_ZCL_CMD_DIRECTION_TO_SRV,
        .cmd_ctrl.fc.dis_default_rsp = false,
        .cmd_ctrl.fc.manuf_specific  = 0,
        .cmd_ctrl.cnf_ctx            = {NULL, NULL},
    };

    EXIT_ON_ERROR(cli_zcl_parse_aps_argtable(&argtable.aps, &req_params.cmd_ctrl));

    if (argtable.peer_role->count > 0) {
        switch (argtable.peer_role->sval[0][0]) {
        case 'C':
        case 'c':
            req_params.cmd_ctrl.fc.direction = EZB_ZCL_CMD_DIRECTION_TO_CLI;
            break;
        case 'S':
        case 's':
            req_params.cmd_ctrl.fc.direction = EZB_ZCL_CMD_DIRECTION_TO_SRV;
            break;
        default:
            EXIT_ON_ERROR(EZB_ERR_INV_ARG, cli_output_line("invalid argument to option -r"));
            break;
        }
    }

    if (argtable.manuf_code->count > 0) {
        if (argtable.manuf_code->val[0] != EZB_ZCL_STD_MANUF_CODE) {
            req_params.cmd_ctrl.fc.manuf_specific = 1;
            req_params.cmd_ctrl.manuf_code        = argtable.manuf_code->val[0];
        }
    }

    if (!strcmp(cmd, "read")) {
        req_params.read_req.payload.attr_number = argtable.attr_id->count;
        req_params.read_req.payload.attr_field  = argtable.attr_id->val;
        ret                                     = ezb_zcl_read_attr_cmd_req(&req_params.read_req);
    } else if (!strcmp(cmd, "write")) {
        int                 n = argtable.attr_id->count;
        ezb_zcl_attribute_t attr_field[n]; /* VLA */
        EXIT_ON_FALSE(n == argtable.attr_type->count && n == argtable.attr_value->count, EZB_ERR_INV_ARG,
                      cli_output("%s: unbalanced options of --attr, --type, --value\n", cmd));
        for (int i = 0; i < n; i++) {
            attr_field[i].id         = argtable.attr_id->val[i];
            attr_field[i].data.type  = argtable.attr_type->val[i];
            attr_field[i].data.value = argtable.attr_value->hval[i];
            attr_field[i].data.size  = argtable.attr_value->hsize[i];
        }
        req_params.write_req.payload.attr_number = n;
        req_params.write_req.payload.attr_field  = attr_field;
        ret                                      = ezb_zcl_write_attr_cmd_req(&req_params.write_req);
    } else if (!strcmp(cmd, "report")) {
        EXIT_ON_FALSE(argtable.attr_id->count > 0, EZB_ERR_INV_ARG, cli_output("%s: -a <u16:AID> is required\n", cmd));
        req_params.report_req.payload.attr_id = argtable.attr_id->val[0];
        ret                                   = ezb_zcl_report_attr_cmd_req(&req_params.report_req);
    } else if (!strcmp(cmd, "config_rp")) {
        int                            n             = argtable.attr_id->count;
        uint64_t                       report_change = 0;
        ezb_zcl_config_report_record_t rprt_cfg_records[n];
        EXIT_ON_FALSE(n == argtable.attr_type->count, EZB_ERR_INV_ARG,
                      cli_output("%s: unbalanced options of --attr and --type\n", cmd));
        for (int i = 0; i < n; i++) {
            rprt_cfg_records[i].direction           = EZB_ZCL_REPORTING_SEND;
            rprt_cfg_records[i].attr_id             = argtable.attr_id->val[i];
            rprt_cfg_records[i].client.attr_type    = argtable.attr_type->val[i];
            rprt_cfg_records[i].client.min_interval = (argtable.min_interval->count > i) ? argtable.min_interval->val[i] : 0;
            rprt_cfg_records[i].client.max_interval = (argtable.max_interval->count > i) ? argtable.max_interval->val[i] : 30;
            if (argtable.reportable_change->count > i) {
                uint8_t copy_size = argtable.reportable_change->hsize[i];
                if (copy_size > sizeof(rprt_cfg_records[i].client.reportable_change.data)) {
                    copy_size = sizeof(rprt_cfg_records[i].client.reportable_change.data);
                }
                memcpy(rprt_cfg_records[i].client.reportable_change.data, argtable.reportable_change->hval[i], copy_size);
            } else {
                rprt_cfg_records[i].client.reportable_change.u64 = report_change;
            }
        }
        req_params.config_report_req.payload.record_number = n;
        req_params.config_report_req.payload.record_field  = rprt_cfg_records;
        ret                                                = ezb_zcl_config_report_cmd_req(&req_params.config_report_req);
    } else if (!strcmp(cmd, "read_rp_cfg")) {
        int                                 n = argtable.attr_id->count;
        ezb_zcl_read_report_config_record_t attr_records[n]; /* VLA */
        for (int i = 0; i < n; i++) {
            attr_records[i].report_direction = EZB_ZCL_REPORTING_SEND;
            attr_records[i].attr_id          = argtable.attr_id->val[i];
        }
        req_params.read_report_config_req.payload.record_number = n;
        req_params.read_report_config_req.payload.record_field  = attr_records;
        ret = ezb_zcl_read_report_config_cmd_req(&req_params.read_report_config_req);
    } else if (!strcmp(cmd, "disc_attr")) {
        req_params.disc_attr.payload.start_attr_id   = 0x0000;
        req_params.disc_attr.payload.max_attr_number = 30;
        ret                                          = ezb_zcl_disc_attr_cmd_req(&req_params.disc_attr);
    } else {
        ret = EZB_ERR_NOT_SUPPORTED;
    }

exit:
    arg_hex_free(argtable.attr_value);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

static ezb_err_t cli_zcl_send_raw(esp_zb_cli_cmd_t *self, int argc, char **argv)
{
    struct {
        esp_zb_cli_aps_argtable_t aps;
        arg_str_t                *peer_role;
        arg_u8_t                 *command;
        arg_u16_t                *manuf_code;
        arg_hex_t                *payload;
        arg_lit_t                *dry_run;
        arg_end_t                *end;
    } argtable = {
        .peer_role  = arg_strn("r", "role", "<sc:C|S>", 0, 1, "role of the peer cluster, default: S"),
        .command    = arg_u8n(NULL, "cmd", "<u8:CMD_ID>", 1, 1, "identifier of the command"),
        .manuf_code = arg_u16n(NULL, "manuf", "<u16:CODE>", 0, 1, "set manufacturer's code"),
        .payload    = arg_hexn("p", "payload", "<hex:DATA>", 0, 1, "ZCL payload of the command, raw HEX data"),
        .dry_run    = arg_lit0("n", "dry-run", "print the request being sent"),
        .end        = arg_end(2),
    };
    esp_zb_cli_fill_aps_argtable(&argtable.aps);

    ezb_err_t ret = EZB_ERR_NONE;
    /* Default request settings */
    ezb_zcl_custom_cmd_t req_params = {
        .cmd_ctrl.dst_addr.addr_mode = EZB_APS_ADDR_MODE_DST_ADDR_ENDP_NOT_PRESENT,
        .cmd_ctrl.fc.direction       = EZB_ZCL_CMD_DIRECTION_TO_SRV,
        .cmd_ctrl.fc.dis_default_rsp = false,
        .cmd_ctrl.fc.manuf_specific  = 0,
        .cmd_ctrl.cnf_ctx            = {NULL, NULL},
    };

    /* Parse command line arguments */
    EXIT_ON_FALSE(argc > 1, EZB_ERR_NONE, arg_print_help((void **)&argtable, argv[0]));
    int nerrors = arg_parse(argc, argv, (void **)&argtable);
    EXIT_ON_FALSE(nerrors == 0, EZB_ERR_INV_ARG, arg_print_errors(stdout, argtable.end, argv[0]));

    EXIT_ON_ERROR(cli_zcl_parse_aps_argtable(&argtable.aps, &req_params.cmd_ctrl));

    if (argtable.manuf_code->count > 0) {
        if (argtable.manuf_code->val[0] != EZB_ZCL_STD_MANUF_CODE) {
            req_params.cmd_ctrl.fc.manuf_specific = 1;
            req_params.cmd_ctrl.manuf_code        = argtable.manuf_code->val[0];
        }
    }

    if (argtable.peer_role->count > 0) {
        switch (argtable.peer_role->sval[0][0]) {
        case 'C':
        case 'c':
            req_params.cmd_ctrl.fc.direction = EZB_ZCL_CMD_DIRECTION_TO_CLI;
            break;
        case 'S':
        case 's':
            req_params.cmd_ctrl.fc.direction = EZB_ZCL_CMD_DIRECTION_TO_SRV;
            break;
        default:
            EXIT_ON_ERROR(EZB_ERR_INV_ARG, cli_output_line("invalid argument to option -r"));
            break;
        }
    }
    if (argtable.payload->count > 0) {
        req_params.data        = argtable.payload->hval[0];
        req_params.data_length = argtable.payload->hsize[0];
    }

    /* DO NOT need a check, this option is mandatory */
    req_params.cmd_id = argtable.command->val[0];

    if (argtable.dry_run->count == 0) {
        ret = ezb_zcl_custom_cmd_req(&req_params);
    } else {
        cli_output_line("Send request:");
        cli_output("Mode[%d]: e:%d -> e:%d, ", req_params.cmd_ctrl.dst_addr.addr_mode, req_params.cmd_ctrl.src_ep,
                   req_params.cmd_ctrl.dst_ep);
        if (req_params.cmd_ctrl.dst_addr.addr_mode == EZB_APS_ADDR_MODE_64_ENDP_PRESENT) {
            cli_output("addr:0x%016" PRIx64, *(uint64_t *)(&req_params.cmd_ctrl.dst_addr.u.extended_addr));
        } else {
            cli_output("addr:0x%04" PRIx16, req_params.cmd_ctrl.dst_addr.u.short_addr);
        }
        cli_output_line("");
        cli_output("c:0x%04x, dir:%c, cmd:0x%02x\n", req_params.cmd_ctrl.cluster_id,
                   req_params.cmd_ctrl.fc.direction == EZB_ZCL_CMD_DIRECTION_TO_SRV ? 'S' : 'C', req_params.cmd_id);
        if (req_params.cmd_ctrl.fc.manuf_specific == 1) {
            cli_output("manuf_specific: yes, with manuf_code: 0x%04x\n", req_params.cmd_ctrl.manuf_code);
        } else {
            cli_output("manuf_specific: no\n");
        }
        if (req_params.data) {
            cli_output_buffer(req_params.data, req_params.data_length);
        }
        cli_output_line("");
    }

exit:
    arg_hex_free(argtable.payload);
    ESP_ZB_CLI_FREE_ARGSTRUCT(&argtable);
    return ret;
}

/** TODO: Use the device desc instead device list */
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(dm, "ZigBee Cluster Library data model management",
    ESP_ZB_CLI_SUBCMD(show, cli_dm_show, "Show current data model"),
    ESP_ZB_CLI_SUBCMD(add, cli_dm_add, "Add items in ZCL data model"),
    ESP_ZB_CLI_SUBCMD(register, cli_dm_register, "Register current data model"),
    ESP_ZB_CLI_SUBCMD(read, cli_dm_read, "Read attribute value in data model"),
    ESP_ZB_CLI_SUBCMD(write, cli_dm_write, "Write value to attribute in data model"),
);

DECLARE_ESP_ZB_CLI_SUBCMD_LIST(zcl_send_gen,
    ESP_ZB_CLI_SUBCMD(read, cli_zcl_attr_cmd, "Read attribute"),
    ESP_ZB_CLI_SUBCMD(write, cli_zcl_attr_cmd, "Write attribute"),
    ESP_ZB_CLI_SUBCMD(report, cli_zcl_attr_cmd, "Report attribute"),
    ESP_ZB_CLI_SUBCMD(config_rp, cli_zcl_attr_cmd, "Configure reporting"),
    ESP_ZB_CLI_SUBCMD(read_rp_cfg, cli_zcl_attr_cmd, "Read reporting configuration"),
    ESP_ZB_CLI_SUBCMD(disc_attr, cli_zcl_attr_cmd, "Discover attributes"),
);
DECLARE_ESP_ZB_CLI_CMD_WITH_SUB(zcl, "ZigBee Cluster Library management",
    ESP_ZB_CLI_CMD_WITH_SUB(send_gen, zcl_send_gen, "Send general command"),
    ESP_ZB_CLI_SUBCMD(send_raw, cli_zcl_send_raw, "Send cluster specific raw command"),
);
