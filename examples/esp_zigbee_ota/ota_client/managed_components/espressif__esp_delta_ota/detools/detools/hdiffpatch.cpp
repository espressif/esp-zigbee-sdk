/*
 * sais.c for sais-lite
 * Copyright (c) 2008-2010 Yuta Mori All Rights Reserved.
 * Copyright (c) 2019, Erik Moqvist (Python wrapper).
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <Python.h>
#include "HDiffPatch/libHDiffPatch/HDiff/diff.h"
#include "HDiffPatch/libHDiffPatch/HPatch/patch.h"
#include "HDiffPatch/file_for_patch.h"

static int parse_create_patch_args(PyObject *args_p,
                                   Py_buffer *from_view_p,
                                   Py_buffer *to_view_p,
                                   unsigned int *match_score_p,
                                   unsigned int *block_size_p,
                                   int *patch_type_p)
{
    int res;
    PyObject *from_p;
    PyObject *to_p;

    res = PyArg_ParseTuple(args_p,
                           "OOIIi",
                           &from_p,
                           &to_p,
                           match_score_p,
                           block_size_p,
                           patch_type_p);

    if (res == 0) {
        return (-1);
    }

    res = PyObject_GetBuffer(from_p, from_view_p, PyBUF_CONTIG_RO);

    if (res == -1) {
        return (res);
    }

    res = PyObject_GetBuffer(to_p, to_view_p, PyBUF_CONTIG_RO);

    if (res == -1) {
        goto err1;
    }

    return (res);

 err1:
    PyBuffer_Release(from_view_p);

    return (res);
}

static PyObject *create_patch_suffix_array(uint8_t *from_p,
                                           uint8_t *to_p,
                                           Py_ssize_t from_size,
                                           Py_ssize_t to_size,
                                           unsigned int match_score,
                                           int patch_type)
{
    std::vector<unsigned char> diff;

    try {
        create_compressed_diff(&to_p[0],
                               &to_p[to_size],
                               &from_p[0],
                               &from_p[from_size],
                               diff,
                               NULL,
                               match_score,
                               patch_type);
    } catch (const std::exception& e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());

        return (NULL);
    }

    return (PyByteArray_FromStringAndSize((const char *)diff.data(),
                                          diff.size()));
}

static PyObject *create_patch_match_blocks(uint8_t *from_p,
                                           uint8_t *to_p,
                                           Py_ssize_t from_size,
                                           Py_ssize_t to_size,
                                           unsigned int match_block_size,
                                           int patch_type)
{
    int res;
    hpatch_TStreamInput from_data;
    hpatch_TStreamInput to_data;
    hpatch_TFileStreamOutput patch_data;
    PyObject *byte_array_p;
    size_t members_read;

    mem_as_hStreamInput(&from_data, &from_p[0], &from_p[from_size]);
    mem_as_hStreamInput(&to_data, &to_p[0], &to_p[to_size]);
    hpatch_TFileStreamOutput_init(&patch_data);
    hpatch_TFileStreamOutput_tmpfile(&patch_data, ~(hpatch_StreamPos_t)0);

    create_compressed_diff_stream(&to_data,
                                  &from_data,
                                  &patch_data.base,
                                  NULL,
                                  match_block_size,
                                  patch_type);

    byte_array_p = PyByteArray_FromStringAndSize("", 1);

    if (byte_array_p == NULL) {
        goto out1;
    }

    res = PyByteArray_Resize(byte_array_p, (Py_ssize_t)patch_data.out_length);

    if (res != 0) {
        goto out2;
    }

    res = fseek(patch_data.m_file, 0, SEEK_SET);

    if (res != 0) {
        PyErr_SetString(PyExc_RuntimeError, "internal error: fseek failed");

        goto out2;
    }

    members_read = fread(PyByteArray_AsString(byte_array_p),
                         1,
                         (size_t)patch_data.out_length,
                         patch_data.m_file);
    hpatch_TFileStreamOutput_close(&patch_data);

    if (members_read != patch_data.out_length) {
        PyErr_SetString(PyExc_RuntimeError, "internal error: fread failed");

        goto out3;
    }

    return (byte_array_p);

 out1:
    hpatch_TFileStreamOutput_close(&patch_data);

    return (NULL);

 out2:
    hpatch_TFileStreamOutput_close(&patch_data);

 out3:
    Py_DECREF(byte_array_p);

    return (NULL);
}

/**
 * def create_patch(from_data,
 *                  to_data,
 *                  match_score,
 *                  match_block_size,
 *                  patch_type) -> patch_data
 */
static PyObject *m_create_patch(PyObject *self_p, PyObject* args_p)
{
    int res;
    Py_buffer from_view;
    Py_buffer to_view;
    unsigned int match_score;
    unsigned int match_block_size;
    int patch_type;
    PyObject *patch_p;

    res = parse_create_patch_args(args_p,
                                  &from_view,
                                  &to_view,
                                  &match_score,
                                  &match_block_size,
                                  &patch_type);

    if (res != 0) {
        return (NULL);
    }

    if (match_block_size == 0) {
        patch_p = create_patch_suffix_array((uint8_t *)from_view.buf,
                                            (uint8_t *)to_view.buf,
                                            from_view.len,
                                            to_view.len,
                                            match_score,
                                            patch_type);
    } else {
        patch_p = create_patch_match_blocks((uint8_t *)from_view.buf,
                                            (uint8_t *)to_view.buf,
                                            from_view.len,
                                            to_view.len,
                                            match_block_size,
                                            patch_type);
    }

    PyBuffer_Release(&from_view);
    PyBuffer_Release(&to_view);

    return (patch_p);
}

static int parse_apply_patch_args(PyObject *args_p,
                                   char **from_pp,
                                   char **patch_pp,
                                   Py_ssize_t *from_size_p,
                                   Py_ssize_t *patch_size_p)
{
    int res;
    PyObject *from_bytes_p;
    PyObject *patch_bytes_p;

    res = PyArg_ParseTuple(args_p,
                           "OO",
                           &from_bytes_p,
                           &patch_bytes_p);

    if (res == 0) {
        return (-1);
    }

    res = PyBytes_AsStringAndSize(from_bytes_p, from_pp, from_size_p);

    if (res != 0) {
        return (-1);
    }

    res = PyBytes_AsStringAndSize(patch_bytes_p, patch_pp, patch_size_p);

    if (res != 0) {
        return (-1);
    }

    return (res);
}

#define PATCH_CACHE_SIZE_MIN       (1024 * 8)
#define PATCH_CACHE_SIZE_BEST_MIN  ((size_t)1 << 21)
#define PATCH_CACHE_SIZE_DEFAULT   ((size_t)1 << 26)
#define PATCH_CACHE_SIZE_BEST_MAX  ((size_t)1 << 30)

static uint8_t* get_patch_mem_cache(size_t patchCacheSize,
                                    hpatch_StreamPos_t oldDataSize,
                                    size_t* out_memCacheSize)
{
    uint8_t *temp_cache_p = NULL;
    size_t temp_cache_size;

    if (patchCacheSize < PATCH_CACHE_SIZE_MIN) {
        patchCacheSize = PATCH_CACHE_SIZE_MIN;
    }

    temp_cache_size = patchCacheSize;

    if (temp_cache_size > oldDataSize + PATCH_CACHE_SIZE_BEST_MIN) {
        temp_cache_size = (size_t)(oldDataSize + PATCH_CACHE_SIZE_BEST_MIN);
    }

    while (!temp_cache_p) {
        temp_cache_p = (uint8_t *)malloc(temp_cache_size);

        if ((!temp_cache_p) && (temp_cache_size >= PATCH_CACHE_SIZE_MIN * 2)) {
            temp_cache_size >>= 1;
        }
    }

    *out_memCacheSize = (temp_cache_p ? temp_cache_size : 0);

    return (temp_cache_p);
}

/**
 * def apply_patch(from_data, patch_data) -> to_data
 */
static PyObject *m_apply_patch(PyObject *self_p, PyObject* args_p)
{
    int res;
    uint8_t *from_p;
    uint8_t *patch_p;
    Py_ssize_t from_size;
    Py_ssize_t patch_size;
    hpatch_TStreamOutput to_data;
    hpatch_TStreamInput patch_data;
    hpatch_TStreamInput from_data;
    uint8_t *temp_cache_p;
    size_t temp_cache_size;
    hpatch_BOOL patch_result;
    hpatch_compressedDiffInfo patch_info;
    PyObject *byte_array_p;
    uint8_t *to_p;

    res = parse_apply_patch_args(args_p,
                                  (char **)&from_p,
                                  (char **)&patch_p,
                                  &from_size,
                                  &patch_size);

    if (res != 0) {
        return (NULL);
    }

    mem_as_hStreamInput(&from_data, &from_p[0], &from_p[from_size]);
    mem_as_hStreamInput(&patch_data, &patch_p[0], &patch_p[patch_size]);

    if (!getCompressedDiffInfo(&patch_info, &patch_data)){
        return (NULL);
    }

    if (from_data.streamSize != patch_info.oldDataSize){
        return (NULL);
    }

    byte_array_p = PyByteArray_FromStringAndSize("", 1);

    if (byte_array_p == NULL) {
        return (NULL);
    }

    res = PyByteArray_Resize(byte_array_p, (Py_ssize_t)patch_info.newDataSize);

    if (res != 0) {
        return (NULL);
    }

    to_p = (uint8_t *)PyByteArray_AsString(byte_array_p);
    mem_as_hStreamOutput(&to_data, &to_p[0], &to_p[patch_info.newDataSize]);
    temp_cache_p = get_patch_mem_cache(PATCH_CACHE_SIZE_DEFAULT,
                                       from_data.streamSize,
                                       &temp_cache_size);

    patch_result = patch_decompress_with_cache(&to_data,
                                               &from_data,
                                               &patch_data,
                                               NULL,
                                               &temp_cache_p[0],
                                               &temp_cache_p[temp_cache_size]);

    if (patch_result != 1) {
        exit(1);
    }

    free(temp_cache_p);

    return (byte_array_p);
}

static PyMethodDef module_methods[] = {
    { "create_patch", m_create_patch, METH_VARARGS },
    { "apply_patch", m_apply_patch, METH_VARARGS },
    { NULL }
};

static PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "hdiffpatch",
    NULL,
    -1,
    module_methods
};

PyMODINIT_FUNC PyInit_hdiffpatch(void)
{
    PyObject *m_p;

    /* Module creation. */
    m_p = PyModule_Create(&module);

    if (m_p == NULL) {
        return (NULL);
    }

    return (m_p);
}
