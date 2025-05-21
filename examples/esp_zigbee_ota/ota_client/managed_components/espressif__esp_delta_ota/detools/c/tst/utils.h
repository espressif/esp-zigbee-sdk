#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

struct files_t {
    struct {
        FILE *file_p;
    } from;
    struct {
        FILE *file_p;
        char *buf_p;
        size_t size;
        int offset;
        int saved_offset;
    } to;
    struct {
        FILE *file_p;
        char *buf_p;
        size_t size;
    } state;
    struct {
        const uint8_t *buf_p;
        size_t size;
    } patch;
    struct {
        const uint8_t *buf_p;
        size_t size;
    } expected_new;
};

extern struct files_t utils_files;

int utils_from_read(void *arg_p, uint8_t *buf_p, size_t size);

int utils_from_seek(void *arg_p, int offset);

int utils_to_write(void *arg_p, const uint8_t *buf_p, size_t size);

int utils_state_write(void *arg_p, const void *buf_p, size_t size);

int utils_state_read(void *arg_p, void *buf_p, size_t size);

const uint8_t *utils_read_file(const char *filename_p, size_t *size_p);

void utils_files_init(const char *from_filename_p,
                      const char *patch_filename_p,
                      const char *expected_new_filename_p);

void utils_files_destroy(void);

void utils_files_assert_and_destroy(void);

void utils_files_reopen_from(void);

#endif
