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

#include <stdlib.h>
#include "detools.h"

static void print_usage_and_exit(const char *name_p)
{
    printf("Usage: %s {apply_patch, apply_patch_in_place}\n", name_p);
    exit(1);
}

static void print_apply_patch_usage_and_exit(const char *name_p)
{
    printf("Usage: %s apply_patch <from-file> <patch-file> <to-file>\n",
           name_p);
    exit(1);
}

static void print_apply_patch_in_place_usage_and_exit(const char *name_p)
{
    printf("Usage: %s apply_patch_in_place <memory-file> <patch-file>\n",
           name_p);
    exit(1);
}

int main(int argc, const char *argv[])
{
    int res;

    if (argc < 2) {
        print_usage_and_exit(argv[0]);
    }

    if (strcmp("apply_patch", argv[1]) == 0) {
        if (argc != 5) {
            print_apply_patch_usage_and_exit(argv[0]);
        }

        res = detools_apply_patch_filenames(argv[2], argv[3], argv[4]);
    } else if (strcmp("apply_patch_in_place", argv[1]) == 0) {
        if (argc != 4) {
            print_apply_patch_in_place_usage_and_exit(argv[0]);
        }

        res = detools_apply_patch_in_place_filenames(argv[2],
                                                     argv[3],
                                                     NULL,
                                                     NULL);
    } else {
        print_usage_and_exit(argv[0]);
    }

    if (res > 0) {
        res = 0;
    } else if (res < 0) {
        res *= -1;

        printf("error: %s (error code %d)\n",
               detools_error_as_string(res),
               res);
    }

    return (res);
}
