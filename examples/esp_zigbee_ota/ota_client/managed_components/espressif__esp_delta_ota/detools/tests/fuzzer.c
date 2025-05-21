#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "../c/detools.h"

#define membersof(v) (sizeof(v) / sizeof((v)[0]))

static void create_file(const char *name_p, const uint8_t *buf_p, size_t size)
{
    FILE *f_p;

    f_p = fopen(name_p, "wb");
    assert(f_p != NULL);

    if (size > 0) {
        assert(fwrite(buf_p, size, 1, f_p) == 1);
    }

    assert(fclose(f_p) == 0);
}

static void create_patch(const char *from_p,
                         const char *to_p,
                         const char *patch_p,
                         int compression)
{
    char command[128];
    static const char *compressions[] = {
        "none",
        "lzma"
    };

    snprintf(&command[0],
             sizeof(command),
             "python3 -m detools create_patch -c %s %s %s %s",
             compressions[compression],
             from_p,
             to_p,
             patch_p);
    command[membersof(command) - 1] = '\0';
    assert(system(command) == 0);
}

int LLVMFuzzerTestOneInput(const uint8_t *data_p, size_t size)
{
    const uint8_t *from_p;
    const uint8_t *to_p;
    size_t from_size;
    size_t to_size;

    if (size < 2) {
        return (0);
    }

    size -= 2;
    from_size = ((data_p[0] * size) / 255);
    to_size = (size - from_size);
    from_p = &data_p[2];
    to_p = &data_p[2 + from_size];

    create_file("fuzzer.old", from_p, from_size);
    create_file("fuzzer.new", to_p, to_size);

    create_patch("fuzzer.old", "fuzzer.new", "fuzzer.patch", data_p[1] % 2);
    assert(detools_apply_patch_filenames("fuzzer.old",
                                         "fuzzer.patch",
                                         "fuzzer-patched.new") == to_size);
    assert(system("cmp fuzzer.new fuzzer-patched.new") == 0);

    return (0);
}
