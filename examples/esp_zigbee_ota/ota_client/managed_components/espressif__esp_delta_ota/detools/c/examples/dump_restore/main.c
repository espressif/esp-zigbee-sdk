/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2019, Erik Moqvist
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define _XOPEN_SOURCE 500

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../../detools.h"

static FILE *from_file_p;
static FILE *patch_file_p;
static FILE *to_file_p;
static FILE *state_file_p;

static void remove_state(void)
{
    printf("Removing state 'state.bin'.\n");
    remove("state.bin");
}

static void clean_and_exit(void)
{
    remove_state();
    exit(1);
}

static void print_usage_and_exit(const char *name_p)
{
    printf("Usage: %s <from-file> <patch-file> <to-file> <size> <size-after-dump\n",
           name_p);
    clean_and_exit();
}

static FILE *open_file(const char *filename_p,
                       const char *mode_p)
{
    FILE *file_p;

    file_p = fopen(filename_p, mode_p);

    if (file_p == NULL) {
        printf("error: Failed to open '%s' with '%s'.\n",
               filename_p,
               strerror(errno));
        clean_and_exit();
    }

    return (file_p);
}

static int parse_non_negative_integer(const char *value_p)
{
    int value;

    value = atoi(value_p);

    if (value < 0) {
        printf("error: Non-negative integer expected.\n");
        clean_and_exit();
    }

    return (value);
}

static size_t file_size(FILE *file_p)
{
    int res;
    long size;

    res = fseek(file_p, 0, SEEK_END);

    if (res != 0) {
        printf("error: Seek failed.\n");
        clean_and_exit();
    }

    size = ftell(file_p);

    if (size <= 0) {
        printf("error: Tell failed.\n");
        clean_and_exit();
    }

    res = fseek(file_p, 0, SEEK_SET);

    if (res != 0) {
        printf("error: Seek failed.\n");
        clean_and_exit();
    }

    return ((size_t)size);
}

static int from_read(void *arg_p, uint8_t *buf_p, size_t size)
{
    (void)arg_p;

    int res;

    res = 0;

    if (size > 0) {
        if (fread(buf_p, size, 1, from_file_p) != 1) {
            res = -1;
        }
    }

    return (res);
}

static int from_seek(void *arg_p, int offset)
{
    (void)arg_p;

    return (fseek(from_file_p, offset, SEEK_CUR));
}

static int to_write(void *arg_p, const uint8_t *buf_p, size_t size)
{
    (void)arg_p;

    int res;

    res = 0;

    if (size > 0) {
        if (fwrite(buf_p, size, 1, to_file_p) != 1) {
            res = -1;
        }
    }

    return (res);
}

static void *read_file(FILE *file_p, int offset, int size)
{
    void *buf_p;

    buf_p = malloc(size);

    if (buf_p == NULL) {
        printf("error: Alloc failed.\n");
        clean_and_exit();
    }

    if (fseek(file_p, offset, SEEK_SET) != 0) {
        printf("error: Seek failed.\n");
        clean_and_exit();
    }

    if (fread(buf_p, size, 1, file_p) != 1) {
        printf("error: Read failed.\n");
        clean_and_exit();
    }

    return (buf_p);
}

static void parse_args(int argc,
                       const char *argv[],
                       FILE **from_file_pp,
                       FILE **patch_file_pp,
                       FILE **to_file_pp,
                       int *size_p,
                       int *size_after_dump_p)
{
    if (argc != 6) {
        print_usage_and_exit(argv[0]);
    }

    *from_file_pp = open_file(argv[1], "rb");
    *patch_file_pp = open_file(argv[2], "rb");
    *to_file_pp = open_file(argv[3], "ab");
    *size_p = parse_non_negative_integer(argv[4]);
    *size_after_dump_p = parse_non_negative_integer(argv[5]);
}

static int state_read(void *arg_p, void *buf_p, size_t size)
{
    (void)arg_p;

    size_t number_of_members_read;

    number_of_members_read = fread(buf_p, size, 1, state_file_p);

    if (number_of_members_read != 1) {
        return (-1);
    }

    return (0);
}

static int state_write(void *arg_p, const void *buf_p, size_t size)
{
    (void)arg_p;

    size_t number_of_members_written;

    number_of_members_written = fwrite(buf_p, size, 1, state_file_p);

    if (number_of_members_written != 1) {
        return (-1);
    }

    return (0);
}

static void init(struct detools_apply_patch_t *apply_patch_p,
                 size_t patch_size)
{
    int res;

    res = detools_apply_patch_init(apply_patch_p,
                                   from_read,
                                   from_seek,
                                   patch_size,
                                   to_write,
                                   NULL);

    if (res != 0) {
        printf("error: Init failed.\n");
        clean_and_exit();
    }
}

static void process(struct detools_apply_patch_t *apply_patch_p,
                    int offset,
                    int size)
{
    int res;
    void *buf_p;

    printf("Processing %d byte(s) patch data starting at offset %d.\n",
           size,
           offset);

    buf_p = read_file(patch_file_p, offset, size);

    res = detools_apply_patch_process(apply_patch_p, buf_p, size);

    if (res < 0) {
        printf("error: Process failed with '%s'.\n", detools_error_as_string(res));
        clean_and_exit();
    }

    free(buf_p);
}

static int finalize(struct detools_apply_patch_t *apply_patch_p)
{
    int res;

    res = detools_apply_patch_finalize(apply_patch_p);

    if (res < 0) {
        printf("error: Finalize failed with '%s'.\n",
               detools_error_as_string(res));
        clean_and_exit();
    }

    return (res);
}

static void dump(struct detools_apply_patch_t *apply_patch_p)
{
    int res;

    printf("Storing state in 'state.bin'.\n");

    state_file_p = open_file("state.bin", "wb");

    res = detools_apply_patch_dump(apply_patch_p, state_write);

    if (res != DETOOLS_OK) {
        printf("error: Dump failed with '%s'.\n", detools_error_as_string(res));
        clean_and_exit();
    }

    fclose(state_file_p);
}

static void try_restore(struct detools_apply_patch_t *apply_patch_p,
                        int *patch_offset_p)
{
    int res;

    state_file_p = fopen("state.bin", "rb");

    if (state_file_p != NULL) {
        printf("Restoring state from 'state.bin'.\n");

        res = detools_apply_patch_restore(apply_patch_p, state_read);

        if (res != DETOOLS_OK) {
            printf("error: Restore failed.\n");
            clean_and_exit();
        }

        fclose(state_file_p);
    } else {
        printf("No state to restore.\n");
    }

    *patch_offset_p = (int)detools_apply_patch_get_patch_offset(apply_patch_p);
    ftruncate(fileno(to_file_p),
              detools_apply_patch_get_to_offset(apply_patch_p));
}

int main(int argc, const char *argv[])
{
    int to_size;
    struct detools_apply_patch_t apply_patch;
    int offset;
    int size;
    int size_after_dump;
    size_t patch_size;

    parse_args(argc,
               argv,
               &from_file_p,
               &patch_file_p,
               &to_file_p,
               &size,
               &size_after_dump);
    patch_size = file_size(patch_file_p);

    init(&apply_patch, patch_size);
    try_restore(&apply_patch, &offset);
    process(&apply_patch, offset, size);

    if ((offset + size) == (int)patch_size) {
        to_size = finalize(&apply_patch);
        remove_state();
        printf("Patch successfully applied. To-file is %d bytes.\n", to_size);
    } else {
        dump(&apply_patch);

        if (size_after_dump > 0) {
            process(&apply_patch, offset + size, size_after_dump);
        }
    }

    fclose(from_file_p);
    fclose(patch_file_p);
    fclose(to_file_p);

    return (0);
}
