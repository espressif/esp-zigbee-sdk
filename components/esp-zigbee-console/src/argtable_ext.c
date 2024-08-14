/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 *  This file implements the extensions of argtable3 used by esp-zigbee-console.
 */

#include <string.h>

#include "esp_check.h"

#include "cmdline_parser.h"

#include "argtable_ext.h"

static void arg_commom_resetfn(struct arg_lit* parent)
{
    parent->count = 0;
}

static esp_err_t arg_common_checkfn(struct arg_lit* parent)
{
    esp_err_t errorcode = (parent->count < parent->hdr.mincount) ? ESP_ERR_NOT_FOUND : ESP_OK;
    return errorcode;
}

static void arg_common_errorfn(struct arg_lit* parent, arg_dstr_t ds, int errorcode, const char* argval, const char* progname)
{
    const char* shortopts = parent->hdr.shortopts;
    const char* longopts = parent->hdr.longopts;
    const char* datatype = parent->hdr.datatype;

    /* make argval NULL safe */
    argval = argval ? argval : "";

    arg_dstr_catf(ds, "%s: ", progname);
    switch (errorcode) {
        case ESP_ERR_NOT_FOUND:
            arg_dstr_cat(ds, "missing option ");
            arg_print_option_ds(ds, shortopts, longopts, datatype, "\n");
            break;

        case ESP_ERR_INVALID_STATE:
            arg_dstr_cat(ds, "excess option ");
            arg_print_option_ds(ds, shortopts, longopts, argval, "\n");
            break;

        case ESP_ERR_INVALID_ARG:
            arg_dstr_catf(ds, "invalid argument \"%s\" to option ", argval);
            arg_print_option_ds(ds, shortopts, longopts, datatype, "\n");
            break;

        case ESP_ERR_INVALID_SIZE:
            arg_dstr_cat(ds, "invalid value size at option ");
            arg_print_option_ds(ds, shortopts, longopts, datatype, " ");
            arg_dstr_catf(ds, "(%s does not fit)\n", argval);
            break;
    }
}

static esp_err_t arg_u8_scanfn(arg_u8_t* parent, const char* argval)
{
    esp_err_t ret = ESP_OK;

    if (parent->count == parent->hdr.maxcount) {
        ret = ESP_ERR_INVALID_STATE;
    } else if (!argval) {
        parent->count++;
    } else {
        uint8_t val;
        ret = parse_u8(argval, &val);
        if (ret == ESP_OK) {
            parent->val[parent->count++] = val;
        }
    }

    return ret;
}

arg_u8_t *arg_u8n(const char* shortopts, const char* longopts, const char* datatype, int mincount, int maxcount, const char* glossary)
{
    size_t nbytes;
    arg_u8_t* result;

    /* foolproof things by ensuring maxcount is not less than mincount */
    maxcount = (maxcount < mincount) ? mincount : maxcount;

    nbytes = sizeof(arg_u8_t) + (size_t)maxcount * sizeof(uint8_t);

    result = (arg_u8_t*)malloc(nbytes);

    /* init the arg_hdr struct */
    result->hdr.flag = ARG_HASVALUE;
    result->hdr.shortopts = shortopts;
    result->hdr.longopts = longopts;
    result->hdr.datatype = datatype ? datatype : "<u8>";
    result->hdr.glossary = glossary;
    result->hdr.mincount = mincount;
    result->hdr.maxcount = maxcount;
    result->hdr.parent = result;
    result->hdr.resetfn = (arg_resetfn*)arg_commom_resetfn;
    result->hdr.scanfn = (arg_scanfn*)arg_u8_scanfn;
    result->hdr.checkfn = (arg_checkfn*)arg_common_checkfn;
    result->hdr.errorfn = (arg_errorfn*)arg_common_errorfn;

    result->val = (uint8_t*)(result + 1);
    result->count = 0;

    return result;
}

static esp_err_t arg_u16_scanfn(arg_u16_t* parent, const char* argval)
{
    esp_err_t ret = ESP_OK;

    if (parent->count == parent->hdr.maxcount) {
        ret = ESP_ERR_INVALID_STATE;
    } else if (!argval) {
        parent->count++;
    } else {
        uint16_t val;
        ret = parse_u16(argval, &val);
        if (ret == ESP_OK) {
            parent->val[parent->count++] = val;
        }
    }

    return ret;
}

arg_u16_t *arg_u16n(const char* shortopts, const char* longopts, const char* datatype, int mincount, int maxcount, const char* glossary)
{
    size_t nbytes;
    arg_u16_t* result;

    /* foolproof things by ensuring maxcount is not less than mincount */
    maxcount = (maxcount < mincount) ? mincount : maxcount;

    nbytes = sizeof(arg_u16_t) + (size_t)maxcount * sizeof(uint16_t);

    result = (arg_u16_t*)malloc(nbytes);

    /* init the arg_hdr struct */
    result->hdr.flag = ARG_HASVALUE;
    result->hdr.shortopts = shortopts;
    result->hdr.longopts = longopts;
    result->hdr.datatype = datatype ? datatype : "<u16>";
    result->hdr.glossary = glossary;
    result->hdr.mincount = mincount;
    result->hdr.maxcount = maxcount;
    result->hdr.parent = result;
    result->hdr.resetfn = (arg_resetfn*)arg_commom_resetfn;
    result->hdr.scanfn = (arg_scanfn*)arg_u16_scanfn;
    result->hdr.checkfn = (arg_checkfn*)arg_common_checkfn;
    result->hdr.errorfn = (arg_errorfn*)arg_common_errorfn;

    result->val = (uint16_t*)(result + 1);
    result->count = 0;

    return result;
}

static esp_err_t arg_u32_scanfn(arg_u32_t* parent, const char* argval)
{
    esp_err_t ret = ESP_OK;

    if (parent->count == parent->hdr.maxcount) {
        ret = ESP_ERR_INVALID_STATE;
    } else if (!argval) {
        parent->count++;
    } else {
        uint32_t val;
        ret = parse_u32(argval, &val);
        if (ret == ESP_OK) {
            parent->val[parent->count++] = val;
        }
    }

    return ret;
}

arg_u32_t *arg_u32n(const char* shortopts, const char* longopts, const char* datatype, int mincount, int maxcount, const char* glossary)
{
    size_t nbytes;
    arg_u32_t* result;

    /* foolproof things by ensuring maxcount is not less than mincount */
    maxcount = (maxcount < mincount) ? mincount : maxcount;

    nbytes = sizeof(arg_u32_t) + (size_t)maxcount * sizeof(uint32_t);

    result = (arg_u32_t*)malloc(nbytes);

    /* init the arg_hdr struct */
    result->hdr.flag = ARG_HASVALUE;
    result->hdr.shortopts = shortopts;
    result->hdr.longopts = longopts;
    result->hdr.datatype = datatype ? datatype : "<u32>";
    result->hdr.glossary = glossary;
    result->hdr.mincount = mincount;
    result->hdr.maxcount = maxcount;
    result->hdr.parent = result;
    result->hdr.resetfn = (arg_resetfn*)arg_commom_resetfn;
    result->hdr.scanfn = (arg_scanfn*)arg_u32_scanfn;
    result->hdr.checkfn = (arg_checkfn*)arg_common_checkfn;
    result->hdr.errorfn = (arg_errorfn*)arg_common_errorfn;

    result->val = (uint32_t*)(result + 1);
    result->count = 0;

    return result;
}

static esp_err_t arg_hex_scanfn(arg_hex_t* parent, const char* argval)
{
    esp_err_t ret = ESP_OK;

    if (parent->count == parent->hdr.maxcount) {
        ret = ESP_ERR_INVALID_STATE;
    } else if (!argval) {
        parent->count++;
    } else {
        size_t buffer_len = (strlen(argval) - 1) / 2;
        uint8_t *buffer = NULL;
        if (!(0 < buffer_len && buffer_len < UINT16_MAX)) {
            return ESP_ERR_INVALID_SIZE;
        }
        buffer = malloc(buffer_len);
        if (buffer == NULL){
            return ESP_ERR_NO_MEM;
        }
        ret = parse_hex_str(argval, buffer, buffer_len, &buffer_len);
        if (ret == ESP_OK) {
            parent->hsize[parent->count] = buffer_len;
            parent->hval[parent->count] = buffer;
            parent->count++;
        } else {
            free(buffer);
        }
    }

    return ret;
}

arg_hex_t *arg_hexn(const char* shortopts, const char* longopts, const char* datatype, int mincount, int maxcount, const char* glossary)
{
    size_t nbytes;
    arg_hex_t* result;

    /* foolproof things by ensuring maxcount is not less than mincount */
    maxcount = (maxcount < mincount) ? mincount : maxcount;

    nbytes = sizeof(arg_hex_t) + (size_t)maxcount * (sizeof(uint16_t) + sizeof(uint8_t *));

    result = (arg_hex_t*)malloc(nbytes);

    /* init the arg_hdr struct */
    result->hdr.flag = ARG_HASVALUE;
    result->hdr.shortopts = shortopts;
    result->hdr.longopts = longopts;
    result->hdr.datatype = datatype ? datatype : "<HEX>";
    result->hdr.glossary = glossary;
    result->hdr.mincount = mincount;
    result->hdr.maxcount = maxcount;
    result->hdr.parent = result;
    result->hdr.resetfn = (arg_resetfn*)arg_commom_resetfn;
    result->hdr.scanfn = (arg_scanfn*)arg_hex_scanfn;
    result->hdr.checkfn = (arg_checkfn*)arg_common_checkfn;
    result->hdr.errorfn = (arg_errorfn*)arg_common_errorfn;

    result->hsize = (uint16_t *)(result + 1);
    result->hval  = (uint8_t **)(result->hsize + maxcount);
    result->count = 0;

    return result;
}

void arg_hex_free(arg_hex_t* parent)
{
    for (int i = 0; i < parent->count; i++) {
        if (parent->hval[i] != NULL) {
            free(parent->hval[i]);
        }
    }
}

static esp_err_t arg_devid_scanfn(arg_devid_t* parent, const char* argval)
{
    esp_err_t ret = arg_u16_scanfn(parent, argval);

    /* Try to parse the device name */
    if (ret == ESP_ERR_INVALID_ARG) {
        uint16_t esp_zb_get_device_id_by_name(const char *name);
        uint16_t device_id = esp_zb_get_device_id_by_name(argval);
        if (device_id != 0xFFFF) {
            parent->val[parent->count++] = device_id;
            ret = ESP_OK;
        }
    }

    return ret;
}

arg_devid_t *arg_devidn(const char* shortopts, const char* longopts, const char* datatype, int mincount, int maxcount, const char* glossary)
{
    arg_devid_t *result = (arg_devid_t*)arg_u16n(shortopts, longopts, datatype, mincount, maxcount, glossary);
    result->hdr.scanfn = (arg_scanfn*)arg_devid_scanfn;

    return result;
}

static esp_err_t arg_addr_scanfn(arg_addr_t* parent, const char* argval)
{
    esp_err_t ret = ESP_OK;

    if (parent->count == parent->hdr.maxcount) {
        ret = ESP_ERR_INVALID_STATE;
    } else if (!argval) {
        parent->count++;
    } else {
        ret = parse_zcl_addr(argval, &parent->addr[parent->count]);
        if (ret == ESP_OK) {
            parent->count++;
        }
    }

    return ret;
}

arg_addr_t* arg_addrn(const char* shortopts, const char* longopts, const char* datatype, int mincount, int maxcount, const char* glossary)
{
    size_t nbytes;
    arg_addr_t* result;

    /* foolproof things by ensuring maxcount is not less than mincount */
    maxcount = (maxcount < mincount) ? mincount : maxcount;

    nbytes = sizeof(arg_addr_t) + (size_t)maxcount * sizeof(esp_zb_zcl_addr_t);

    result = (arg_addr_t*)malloc(nbytes);

    /* init the arg_hdr struct */
    result->hdr.flag = ARG_HASVALUE;
    result->hdr.shortopts = shortopts;
    result->hdr.longopts = longopts;
    result->hdr.datatype = datatype ? datatype : "<ADDR>";
    result->hdr.glossary = glossary;
    result->hdr.mincount = mincount;
    result->hdr.maxcount = maxcount;
    result->hdr.parent = result;
    result->hdr.resetfn = (arg_resetfn*)arg_commom_resetfn;
    result->hdr.scanfn = (arg_scanfn*)arg_addr_scanfn;
    result->hdr.checkfn = (arg_checkfn*)arg_common_checkfn;
    result->hdr.errorfn = (arg_errorfn*)arg_common_errorfn;

    result->addr = (esp_zb_zcl_addr_t*)(result + 1);
    result->count = 0;

    return result;
}

void arg_print_help(void** argtable, const char *program)
{
    printf("Usage: %s", program);
    arg_print_syntax(stdout, argtable, "\n");
    arg_print_glossary(stdout, argtable, "  %-25s %s\n");
}
