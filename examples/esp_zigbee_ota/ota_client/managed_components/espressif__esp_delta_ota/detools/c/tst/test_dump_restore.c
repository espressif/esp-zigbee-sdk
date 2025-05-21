#include <stdlib.h>
#include "nala.h"
#include "utils.h"
#include "../detools.h"

static void init(struct detools_apply_patch_t *apply_patch_p,
                 size_t patch_size)
{
    int res;

    /* Simulate program restart. */
    memset(apply_patch_p, 0, sizeof(*apply_patch_p));
    utils_files_reopen_from();

    res = detools_apply_patch_init(apply_patch_p,
                                   utils_from_read,
                                   utils_from_seek,
                                   patch_size,
                                   utils_to_write,
                                   NULL);
    ASSERT_EQ(res, DETOOLS_OK);
}

static void dump(struct detools_apply_patch_t *apply_patch_p)
{
    int res;

    res = detools_apply_patch_dump(apply_patch_p, utils_state_write);
    ASSERT_EQ(res, DETOOLS_OK);
    ASSERT_EQ(fseek(utils_files.state.file_p, 0, SEEK_SET), 0);
}

static size_t restore(struct detools_apply_patch_t *apply_patch_p)
{
    int res;

    res = detools_apply_patch_restore(apply_patch_p, utils_state_read);
    ASSERT_EQ(res, DETOOLS_OK);
    ASSERT_EQ(fseek(utils_files.state.file_p, 0, SEEK_SET), 0);
    ASSERT_EQ(fseek(utils_files.to.file_p,
                    detools_apply_patch_get_to_offset(apply_patch_p),
                    SEEK_SET), 0);

    return (detools_apply_patch_get_patch_offset(apply_patch_p));
}

static void process(struct detools_apply_patch_t *apply_patch_p,
                    const uint8_t *buf_p,
                    size_t size)
{
    int res;

    res = detools_apply_patch_process(apply_patch_p, buf_p, size);
    ASSERT_EQ(res, DETOOLS_OK);
}

static void finalize(struct detools_apply_patch_t *apply_patch_p,
                     size_t size)
{
    int res;

    res = detools_apply_patch_finalize(apply_patch_p);
    ASSERT_EQ(res, size);
}

TEST(foo_none_at_offset_0)
{
    struct detools_apply_patch_t apply_patch;

    utils_files_init("../../tests/files/foo/old",
                     "../../tests/files/foo/none.patch",
                     "../../tests/files/foo/new");

    /* Init and dump. */
    init(&apply_patch, utils_files.patch.size);
    dump(&apply_patch);

    /* Init again, restore and apply the patch. */
    init(&apply_patch, 0);
    ASSERT_EQ(restore(&apply_patch), 0);
    process(&apply_patch, &utils_files.patch.buf_p[0], utils_files.patch.size);
    finalize(&apply_patch, 2780);

    utils_files_assert_and_destroy();
}

TEST(foo_none_at_offset_100_and_2791)
{
    struct detools_apply_patch_t apply_patch;

    utils_files_init("../../tests/files/foo/old",
                     "../../tests/files/foo/none.patch",
                     "../../tests/files/foo/new");

    /* Init, process 100 bytes and dump. Process another 50 bytes,
       which will be "lost" when later restoring. */
    init(&apply_patch, utils_files.patch.size);
    process(&apply_patch, &utils_files.patch.buf_p[0], 100);
    dump(&apply_patch);
    process(&apply_patch, &utils_files.patch.buf_p[100], 50);

    /* Init again, restore, apply all but one byte and dump again. */
    init(&apply_patch, 0);
    ASSERT_EQ(restore(&apply_patch), 100);
    process(&apply_patch, &utils_files.patch.buf_p[100], 2691);
    dump(&apply_patch);

    /* Init once again, restore and apply the last byte. */
    init(&apply_patch, 0);
    ASSERT_EQ(restore(&apply_patch), 2791);
    process(&apply_patch, &utils_files.patch.buf_p[2791], 1);
    finalize(&apply_patch, 2780);

    utils_files_assert_and_destroy();
}

TEST(foo_none_one_byte_at_a_time)
{
    struct detools_apply_patch_t apply_patch;
    int i;

    utils_files_init("../../tests/files/foo/old",
                     "../../tests/files/foo/none.patch",
                     "../../tests/files/foo/new");

    /* Init, process 10 bytes and dump. */
    init(&apply_patch, utils_files.patch.size);
    process(&apply_patch, &utils_files.patch.buf_p[0], 10);
    dump(&apply_patch);

    /* Init again, restore, process one byte and dump again. */
    for (i = 10; i < 2792; i++) {
        init(&apply_patch, 0);
        ASSERT_EQ(restore(&apply_patch), i);
        process(&apply_patch, &utils_files.patch.buf_p[i], 1);
        dump(&apply_patch);
    }

    utils_files_assert_and_destroy();
}

TEST(foo_none_dump_state_write_error)
{
    struct detools_apply_patch_t apply_patch;
    int res;

    utils_files_init("../../tests/files/foo/old",
                     "../../tests/files/foo/none.patch",
                     "../../tests/files/foo/new");

    init(&apply_patch, utils_files.patch.size);

    utils_state_write_mock_once(sizeof(apply_patch), -1);
    res = detools_apply_patch_dump(&apply_patch, utils_state_write);
    ASSERT_EQ(res, -DETOOLS_IO_FAILED);

    utils_files_destroy();
}

TEST(foo_crle_at_offset_100_101_164_and_189)
{
    struct detools_apply_patch_t apply_patch;

    utils_files_init("../../tests/files/foo/old",
                     "../../tests/files/foo/crle.patch",
                     "../../tests/files/foo/new");

    /* Init, process 100 bytes and dump. Process another 50 bytes,
       which will be "lost" when later restoring. */
    init(&apply_patch, utils_files.patch.size);
    process(&apply_patch, &utils_files.patch.buf_p[0], 100);
    dump(&apply_patch);
    process(&apply_patch, &utils_files.patch.buf_p[100], 50);

    /* Init again, restore, process one byte and dump again. */
    init(&apply_patch, 0);
    ASSERT_EQ(restore(&apply_patch), 100);
    process(&apply_patch, &utils_files.patch.buf_p[100], 1);
    dump(&apply_patch);

    /* Init again, restore, process 63 bytes and dump again. */
    init(&apply_patch, 0);
    ASSERT_EQ(restore(&apply_patch), 101);
    process(&apply_patch, &utils_files.patch.buf_p[101], 63);
    dump(&apply_patch);

    /* Init again, restore, apply all but one byte and dump again. */
    init(&apply_patch, 0);
    ASSERT_EQ(restore(&apply_patch), 164);
    process(&apply_patch, &utils_files.patch.buf_p[164], 25);
    dump(&apply_patch);

    /* Init once again, restore and apply the last byte. */
    init(&apply_patch, 0);
    ASSERT_EQ(restore(&apply_patch), 189);
    process(&apply_patch, &utils_files.patch.buf_p[189], 1);
    finalize(&apply_patch, 2780);

    utils_files_assert_and_destroy();
}

TEST(foo_crle_one_byte_at_a_time)
{
    struct detools_apply_patch_t apply_patch;
    int i;

    utils_files_init("../../tests/files/foo/old",
                     "../../tests/files/foo/crle.patch",
                     "../../tests/files/foo/new");

    /* Init, process 10 bytes and dump. */
    init(&apply_patch, utils_files.patch.size);
    process(&apply_patch, &utils_files.patch.buf_p[0], 10);
    dump(&apply_patch);

    /* Init again, restore, process one byte and dump again. */
    for (i = 10; i < 190; i++) {
        init(&apply_patch, 0);
        ASSERT_EQ(restore(&apply_patch), i);
        process(&apply_patch, &utils_files.patch.buf_p[i], 1);
        dump(&apply_patch);
    }

    utils_files_assert_and_destroy();
}

TEST(foo_heatshrink_at_offset_10_and_100)
{
    struct detools_apply_patch_t apply_patch;

    utils_files_init("../../tests/files/foo/old",
                     "../../tests/files/foo/heatshrink.patch",
                     "../../tests/files/foo/new");

    /* Init, process 10 bytes and dump. Process another 50 bytes,
       which will be "lost" when later restoring. */
    init(&apply_patch, utils_files.patch.size);
    process(&apply_patch, &utils_files.patch.buf_p[0], 10);
    dump(&apply_patch);
    process(&apply_patch, &utils_files.patch.buf_p[10], 50);

    /* Init again, restore, process 90 bytes and dump again. */
    init(&apply_patch, 0);
    ASSERT_EQ(restore(&apply_patch), 10);
    process(&apply_patch, &utils_files.patch.buf_p[10], 90);
    dump(&apply_patch);

    /* Init once again, restore and process remaining 25 bytes. */
    init(&apply_patch, 0);
    ASSERT_EQ(restore(&apply_patch), 100);
    process(&apply_patch, &utils_files.patch.buf_p[100], 26);
    finalize(&apply_patch, 2780);

    utils_files_assert_and_destroy();
}

TEST(foo_heatshrink_one_byte_at_a_time)
{
    struct detools_apply_patch_t apply_patch;
    int i;

    utils_files_init("../../tests/files/foo/old",
                     "../../tests/files/foo/heatshrink.patch",
                     "../../tests/files/foo/new");

    /* Init, process 10 bytes and dump. */
    init(&apply_patch, utils_files.patch.size);
    process(&apply_patch, &utils_files.patch.buf_p[0], 10);
    dump(&apply_patch);

    /* Init again, restore, process one byte and dump again. */
    for (i = 10; i < 125; i++) {
        init(&apply_patch, 0);
        ASSERT_EQ(restore(&apply_patch), i);
        process(&apply_patch, &utils_files.patch.buf_p[i], 1);
        dump(&apply_patch);
    }

    utils_files_assert_and_destroy();
}
