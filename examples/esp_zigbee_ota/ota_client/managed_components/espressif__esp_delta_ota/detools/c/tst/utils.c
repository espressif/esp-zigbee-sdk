#include "nala.h"
#include "utils.h"

struct files_t utils_files;

int utils_from_read(void *arg_p, uint8_t *buf_p, size_t size)
{
    (void)arg_p;

    size_t number_of_members_read;

    number_of_members_read = fread(buf_p, size, 1, utils_files.from.file_p);
    ASSERT_EQ(number_of_members_read, 1);

    return (0);
}

int utils_from_seek(void *arg_p, int offset)
{
    (void)arg_p;

    ASSERT_EQ(fseek(utils_files.from.file_p, offset, SEEK_CUR), 0);

    return (0);
}

int utils_to_write(void *arg_p, const uint8_t *buf_p, size_t size)
{
    (void)arg_p;

    size_t number_of_members_written;

    number_of_members_written = fwrite(buf_p, size, 1, utils_files.to.file_p);
    ASSERT_EQ(number_of_members_written, 1);
    utils_files.to.offset += size;

    return (0);
}

int utils_state_write(void *arg_p, const void *buf_p, size_t size)
{
    (void)arg_p;

    size_t number_of_members_written;

    number_of_members_written = fwrite(buf_p, size, 1, utils_files.state.file_p);
    ASSERT_EQ(number_of_members_written, 1);

    return (0);
}

int utils_state_read(void *arg_p, void *buf_p, size_t size)
{
    (void)arg_p;

    size_t number_of_members_read;

    number_of_members_read = fread(buf_p, size, 1, utils_files.state.file_p);
    ASSERT_EQ(number_of_members_read, 1);

    return (0);
}

const uint8_t *utils_read_file(const char *filename_p, size_t *size_p)
{
    FILE *file_p;
    char *buf_p;

    file_p = fopen(filename_p, "rb");
    ASSERT_NE(file_p, NULL);
    ASSERT_EQ(fseek(file_p, 0, SEEK_END), 0);
    *size_p = ftell(file_p);
    ASSERT_GT(*size_p, 0);
    buf_p = malloc(*size_p);
    ASSERT_NE(buf_p, NULL);
    ASSERT_EQ(fseek(file_p, 0, SEEK_SET), 0);
    ASSERT_EQ(fread(buf_p, *size_p, 1, file_p), 1);
    fclose(file_p);

    return ((const uint8_t *)buf_p);
}

void utils_files_init(const char *from_filename_p,
                      const char *patch_filename_p,
                      const char *expected_new_filename_p)
{
    utils_files.from.file_p = fopen(from_filename_p, "rb");
    ASSERT_NE(utils_files.from.file_p, NULL);
    utils_files.to.file_p = open_memstream(&utils_files.to.buf_p,
                                           &utils_files.to.size);
    ASSERT_NE(utils_files.to.file_p, NULL);
    utils_files.to.offset = 0;
    utils_files.to.saved_offset = -1;
    utils_files.state.file_p = open_memstream(&utils_files.state.buf_p,
                                              &utils_files.state.size);
    ASSERT_NE(utils_files.state.file_p, NULL);
    utils_files.patch.buf_p = utils_read_file(patch_filename_p,
                                              &utils_files.patch.size);
    utils_files.expected_new.buf_p = utils_read_file(
        expected_new_filename_p,
        &utils_files.expected_new.size);
}

void utils_files_destroy(void)
{
    fclose(utils_files.to.file_p);
    free((void *)utils_files.expected_new.buf_p);
    fclose(utils_files.from.file_p);
    free(utils_files.to.buf_p);
    fclose(utils_files.state.file_p);
    free(utils_files.state.buf_p);
    free((void *)utils_files.patch.buf_p);
}

void utils_files_assert_and_destroy(void)
{
    fflush(utils_files.to.file_p);

    ASSERT_EQ(utils_files.to.size, utils_files.expected_new.size);
    ASSERT_MEMORY_EQ(utils_files.to.buf_p,
                     utils_files.expected_new.buf_p,
                     utils_files.expected_new.size);

    utils_files_destroy();
}

void utils_files_reopen_from(void)
{
    ASSERT_EQ(fseek(utils_files.from.file_p, 0, SEEK_SET), 0);
}
