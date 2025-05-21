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
#include "../../detools.h"

/* Helper functions. */
static int flash_read(void *arg_p, void *dst_p, uintptr_t src, size_t size)
{
    return (0);
}

static int flash_write(void *arg_p, uintptr_t dst, void *src_p, size_t size)
{
    return (0);
}

static int flash_erase(void *arg_p, uintptr_t addr, size_t size)
{
    return (0);
}

static int step_set(void *arg_p, int step)
{
    return (0);
}

static int step_get(void *arg_p, int *step_p)
{
    return (0);
}

static int serial_read(uint8_t *buf_p, size_t size)
{
    return (0);
}

static int verify_written_data(int to_size, uint32_t to_crc)
{
    return (0);
}

static int update(size_t patch_size, uint32_t to_crc)
{
    struct detools_apply_patch_in_place_t apply_patch;
    uint8_t buf[256];
    size_t left;
    int res;

    /* Initialize the in-place apply patch object. */
    res = detools_apply_patch_in_place_init(&apply_patch,
                                            flash_read,
                                            flash_write,
                                            flash_erase,
                                            step_set,
                                            step_get,
                                            patch_size,
                                            NULL);

    if (res != 0) {
        return (res);
    }

    left = patch_size;

    /* Incrementally process patch data until the whole patch has been
       applied or an error occurrs. */
    while ((left > 0) && (res == 0)) {
        res = serial_read(&buf[0], sizeof(buf));

        if (res > 0) {
            left -= res;
            res = detools_apply_patch_in_place_process(&apply_patch,
                                                       &buf[0],
                                                       res);
        }
    }

    /* Finalize patching and verify written data. */
    if (res == 0) {
        res = detools_apply_patch_in_place_finalize(&apply_patch);

        if (res >= 0) {
            res = verify_written_data(res, to_crc);
        }
    } else {
        (void)detools_apply_patch_in_place_finalize(&apply_patch);
    }

    return (res);
}

int main(int argc, const char *argv[])
{
    return (update(atoi(argv[1]), atoi(argv[2])));
}
