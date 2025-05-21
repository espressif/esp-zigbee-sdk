/* #include <dbg.h> */
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "nala.h"
#include "../detools.h"

static const uint8_t from[256] = { 0, };

static void create_from_file(void)
{
    FILE *file_p;

    file_p = fopen("from", "wb");
    ASSERT_NE(file_p, NULL);
    ASSERT_EQ(fwrite(&from[0], sizeof(from), 1, file_p), 1);
    fclose(file_p);
}

static bool is_file(const char *path_p)
{
    struct stat statbuf;

    ASSERT_EQ(stat(path_p, &statbuf), 0);

    return (S_ISREG(statbuf.st_mode));
}

static void create_patch_file(const char *corpus_file_path_p)
{
    FILE *file_p;
    uint8_t size;
    uint8_t patch[256];

    /* Read corpus file. */
    file_p = fopen(corpus_file_path_p, "rb");
    ASSERT_NE(file_p, NULL);
    ASSERT_EQ(fread(&size, 1, 1, file_p), 1);

    if (size > 0) {
        ASSERT_EQ(fread(&patch[0], size, 1, file_p), 1);
        /* dbgh(&patch[0], size); */
    }

    fclose(file_p);

    /* Create patch file. */
    file_p = fopen("patch", "wb");
    ASSERT_NE(file_p, NULL);

    if (size > 0) {
        ASSERT_EQ(fwrite(&patch[0], size, 1, file_p), 1);
    }

    fclose(file_p);
}

TEST(all_ok)
{
    DIR *dir_p;
    struct dirent *item_p;
    char corpus_file_path[512];
    int res;

    dir_p = opendir("corpus");

    if (dir_p != NULL) {
        create_from_file();

        while ((item_p = readdir(dir_p)) != NULL) {
            sprintf(&corpus_file_path[0], "corpus/%s", item_p->d_name);

            if (!is_file(&corpus_file_path[0])) {
                continue;
            }

            printf("\n");
            printf("Corpus file:  '%s'\n", &corpus_file_path[0]);
            create_patch_file(&corpus_file_path[0]);
            res = detools_apply_patch_filenames("from", "patch", "to");
            printf("Patch result: %s (%d)\n", detools_error_as_string(res), res);
        }

        closedir(dir_p);
    }
}

static const uint8_t from_buf[256] = { 0, };
static int from_offset = 0;

static int from_read(void *arg_p, uint8_t *buf_p, size_t size)
{
    (void)arg_p;

    if (((size_t)from_offset + size) > 256) {
        return (-1);
    }

    memcpy(buf_p, &from_buf[from_offset], size);
    from_offset += size;

    return (0);
}

static int from_seek(void *arg_p, int offset)
{
    (void)arg_p;

    if ((from_offset + offset) < 0) {
        return (-1);
    }

    from_offset += offset;

    return (0);
}

static int to_write(void *arg_p, const uint8_t *buf_p, size_t size)
{
    (void)arg_p;
    (void)buf_p;
    (void)size;

    return (0);
}

static void test_one(const uint8_t *patch_buf_p,
                     size_t patch_size,
                     int process_res,
                     int finalize_res)
{
    struct detools_apply_patch_t apply_patch;
    int res;

    res = detools_apply_patch_init(&apply_patch,
                                   from_read,
                                   from_seek,
                                   patch_size,
                                   to_write,
                                   NULL);
    ASSERT_EQ(res, 0);

    res = detools_apply_patch_process(&apply_patch, patch_buf_p, patch_size);

    WITH_MESSAGE("Failed with '%s' (%d).", detools_error_as_string(res), res) {
        ASSERT_EQ(res, process_res);
    }

    res = detools_apply_patch_finalize(&apply_patch);

    WITH_MESSAGE("Failed with '%s' (%d).", detools_error_as_string(res), res) {
        ASSERT_EQ(res, finalize_res);
    }
}

TEST(size_overflow)
{
    const uint8_t patch[] = {
        0x04, 0x0c, 0x44, 0xfd, 0xff, 0x00, 0x00, 0x00, 0x5d, 0x00,
        0x2b, 0x06, 0x66
    };

    test_one(&patch[0],
             sizeof(patch),
             -DETOOLS_CORRUPT_PATCH_OVERFLOW,
             -DETOOLS_ALREADY_FAILED);
}

TEST(infinite_loop)
{
    const uint8_t patch[] = {
        0x02, 0x3a, 0x01, 0xce, 0xce, 0xce, 0xfe, 0xff, 0x00, 0x00,
        0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    test_one(&patch[0],
             sizeof(patch),
             -DETOOLS_CORRUPT_PATCH_OVERFLOW,
             -DETOOLS_ALREADY_FAILED);
}

TEST(lzma_decode_failure)
{
    const uint8_t patch[] = {
        0x01, 0x5b, 0x00, 0x00, 0x00, 0x00, 0xe2, 0xff, 0x8c, 0x8c,
        0x8c, 0x00, 0x00, 0x00, 0x0f, 0x02
    };

    test_one(&patch[0],
             sizeof(patch),
             -DETOOLS_LZMA_DECODE,
             -DETOOLS_ALREADY_FAILED);
}

TEST(corrupt_crle_idle_out_of_data)
{
    const uint8_t patch[] = {
        0x02, 0x7a
    };

    test_one(&patch[0], sizeof(patch), 0, -DETOOLS_NOT_ENOUGH_PATCH_DATA);
}

TEST(dfpatch_not_implemented)
{
    const uint8_t patch[] = {
        0x02, 0x08, 0x00, 0x40, 0x05, 0xfe
    };

    test_one(&patch[0],
             sizeof(patch),
             -DETOOLS_NOT_IMPLEMENTED,
             -DETOOLS_ALREADY_FAILED);
}

TEST(corrupt_crle_kind)
{
    const uint8_t patch[] = {
        0x02, 0x0a, 0x3d
    };

    test_one(&patch[0],
             sizeof(patch),
             -DETOOLS_CORRUPT_PATCH_CRLE_KIND,
             -DETOOLS_ALREADY_FAILED);
}

TEST(bad_from_read_error)
{
    const uint8_t patch[] = {
        0x04, 0xee, 0xee, 0x18, 0x44, 0x00, 0x00, 0x00, 0x04, 0x00,
        0x00, 0xce, 0xc1, 0x27, 0x28, 0x09, 0xcf, 0xee, 0xce, 0xc1,
        0x27, 0x28, 0x09, 0xcf
    };

    test_one(&patch[0],
             sizeof(patch),
             -DETOOLS_IO_FAILED,
             -DETOOLS_ALREADY_FAILED);
}

TEST(size_overflow_header)
{
    const uint8_t patch[] = {
        0x04, 0xfc, 0xf7, 0xfe, 0xfb, 0x04
    };

    test_one(&patch[0],
             sizeof(patch),
             -DETOOLS_CORRUPT_PATCH_OVERFLOW,
             -DETOOLS_ALREADY_FAILED);
}
