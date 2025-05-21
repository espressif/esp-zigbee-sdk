#include <stdlib.h>
#include "nala.h"

TEST(apply_patch_foo)
{
    ASSERT_EQ(system("../detools apply_patch "
                     "../../tests/files/foo/old "
                     "../../tests/files/foo/patch "
                     "build/foo.new"),
              0);
    ASSERT_FILE_EQ("build/foo.new", "../../tests/files/foo/new");
}

TEST(apply_patch_foo_heatshrink)
{
    ASSERT_EQ(system("../detools apply_patch "
                     "../../tests/files/foo/old "
                     "../../tests/files/foo/heatshrink.patch "
                     "build/heatshrink.foo.new"),
              0);
    ASSERT_FILE_EQ("build/heatshrink.foo.new", "../../tests/files/foo/new");
}

TEST(apply_patch_in_place_foo)
{
    ASSERT_EQ(system("cp ../../tests/files/foo/old build/foo.mem"), 0);
    ASSERT_EQ(system("../detools apply_patch_in_place "
                     "build/foo.mem "
                     "../../tests/files/foo/in-place-3000-500.patch"), 0);
    ASSERT_FILE_EQ("build/foo.mem",
                   "../../tests/files/foo/in-place-3000-500.mem");
}

TEST(usage)
{
    CAPTURE_OUTPUT(output, errput) {
        ASSERT_EQ(system("../detools"), 256);
    }

    ASSERT_EQ(output, "Usage: ../detools {apply_patch, apply_patch_in_place}\n");
    ASSERT_EQ(errput, "");
}

TEST(usage_apply_patch)
{
    CAPTURE_OUTPUT(output, errput) {
        ASSERT_EQ(system("../detools apply_patch"), 256);
    }

    ASSERT_EQ(output,
              "Usage: ../detools apply_patch <from-file> <patch-file> <to-file>\n");
    ASSERT_EQ(errput, "");
}

TEST(usage_apply_patch_missing_to_file)
{
    CAPTURE_OUTPUT(output, errput) {
        ASSERT_EQ(system("../detools apply_patch "
                         "../../tests/files/foo/old "
                         "../../tests/files/foo/patch"),
                  256);
    }

    ASSERT_EQ(output,
              "Usage: ../detools apply_patch <from-file> <patch-file> <to-file>\n");
    ASSERT_EQ(errput, "");
}

TEST(usage_apply_patch_in_place)
{
    CAPTURE_OUTPUT(output, errput) {
        ASSERT_EQ(system("../detools apply_patch_in_place"), 256);
    }

    ASSERT_EQ(output,
              "Usage: ../detools apply_patch_in_place <memory-file> <patch-file>\n");
    ASSERT_EQ(errput, "");
}

TEST(usage_apply_patch_in_place_missing_mem_file)
{
    CAPTURE_OUTPUT(output, errput) {
        ASSERT_EQ(system("../detools apply_patch_in_place tests/files/foo/old"),
                  256);
    }

    ASSERT_EQ(output,
              "Usage: ../detools apply_patch_in_place <memory-file> <patch-file>\n");
    ASSERT_EQ(errput, "");
}
