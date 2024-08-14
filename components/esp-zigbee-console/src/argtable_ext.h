/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 *  This file includes the extensions of argtable3 used by esp-zigbee-console.
 */

#pragma once

#include <stdint.h>

#include "argtable3/argtable3.h"
#include "esp_zigbee_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_ZB_CLI_FREE_ARGSTRUCT(p_args) arg_freetable((void**)p_args, sizeof(*p_args) / sizeof(void*))

typedef struct arg_u8 {
    struct arg_hdr hdr; /* The mandatory argtable header struct */
    int count;          /* Number of matching command line args */
    uint8_t* val;       /* Array of parsed argument values */
} arg_u8_t;

typedef struct arg_u16 {
    struct arg_hdr hdr; /* The mandatory argtable header struct */
    int count;          /* Number of matching command line args */
    uint16_t* val;      /* Array of parsed argument values */
} arg_u16_t;

typedef struct arg_u32 {
    struct arg_hdr hdr; /* The mandatory argtable header struct */
    int count;          /* Number of matching command line args */
    uint32_t* val;      /* Array of parsed argument values */
} arg_u32_t;

typedef struct arg_hex {
    struct arg_hdr hdr; /* The mandatory argtable header struct */
    int count;          /* Number of matching command line args */
    uint16_t *hsize;    /* length of the hex in bytes */
    uint8_t **hval;     /* Array of parsed argument values */
} arg_hex_t;

typedef struct arg_addr {
    struct arg_hdr hdr;         /* The mandatory argtable header struct */
    int count;                  /* Number of matching command line args */
    esp_zb_zcl_addr_t* addr;    /* Array of parsed argument values */
} arg_addr_t;

typedef arg_u16_t arg_devid_t;

arg_u8_t *arg_u8n(const char* shortopts, const char* longopts, const char* datatype, int mincount, int maxcount, const char* glossary);
arg_u16_t *arg_u16n(const char* shortopts, const char* longopts, const char* datatype, int mincount, int maxcount, const char* glossary);
arg_u32_t *arg_u32n(const char* shortopts, const char* longopts, const char* datatype, int mincount, int maxcount, const char* glossary);
arg_hex_t *arg_hexn(const char* shortopts, const char* longopts, const char* datatype, int mincount, int maxcount, const char* glossary);
void arg_hex_free(arg_hex_t* parent);
arg_devid_t *arg_devidn(const char* shortopts, const char* longopts, const char* datatype, int mincount, int maxcount, const char* glossary);
arg_addr_t *arg_addrn(const char* shortopts, const char* longopts, const char* datatype, int mincount, int maxcount, const char* glossary);

void arg_print_help(void** argtable, const char *program);

#ifdef __cplusplus
}
#endif
