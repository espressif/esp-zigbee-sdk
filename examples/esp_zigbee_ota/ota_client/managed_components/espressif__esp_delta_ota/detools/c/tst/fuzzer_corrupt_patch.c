/* #include <dbg.h> */
#include <stdlib.h>
#include "detools.h"

static const uint8_t from_buf[256] = { 0, };
static int from_offset;

static int from_read(void *arg_p, uint8_t *buf_p, size_t size)
{
    if (((size_t)from_offset + size) > 256) {
        return (-1);
    }

    memcpy(buf_p, &from_buf[from_offset], size);
    from_offset += size;

    return (0);
}

static int from_seek(void *arg_p, int offset)
{
    if ((offset < 0) || (offset > 256)) {
        return (-1);
    }

    if ((from_offset + offset) < 0) {
        return (-1);
    }

    if ((from_offset + offset) > 256) {
        return (-1);
    }

    from_offset += offset;

    return (0);
}

static int to_write(void *arg_p, const uint8_t *buf_p, size_t size)
{
    return (0);
}

int LLVMFuzzerTestOneInput(const uint8_t *data_p, size_t size)
{
    struct detools_apply_patch_t apply_patch;
    const uint8_t *patch_buf_p;
    size_t patch_size;
    int res;

    if (size < 1) {
        return (0);
    }

    patch_size = data_p[0];
    size -= 1;

    if (size < patch_size) {
        return (0);
    }

    patch_buf_p = &data_p[1];
    from_offset = 0;
    /* dbgh(patch_buf_p, patch_size); */

    res = detools_apply_patch_init(&apply_patch,
                                   from_read,
                                   from_seek,
                                   patch_size,
                                   to_write,
                                   NULL);

    if (res != 0) {
        printf("detools_apply_patch_init() failed.\n");
        exit(1);
    }

    detools_apply_patch_process(&apply_patch, patch_buf_p, patch_size);
    detools_apply_patch_finalize(&apply_patch);

    return (0);
}
