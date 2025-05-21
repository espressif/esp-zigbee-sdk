import os
from .errors import Error
from .apply import read_header_sequential
from .apply import read_header_in_place
from .apply import read_header_hdiffpatch
from .apply import PatchReader
from .common import PATCH_TYPE_SEQUENTIAL
from .common import PATCH_TYPE_IN_PLACE
from .common import PATCH_TYPE_HDIFFPATCH
from .common import file_size
from .common import unpack_size
from .common import unpack_size_with_length
from .common import data_format_number_to_string
from .common import peek_header_type
from .compression.heatshrink import HeatshrinkDecompressor
from .data_format import info as data_format_info


def _compression_info(patch_reader):
    info = None

    if patch_reader:
        decompressor = patch_reader.decompressor

        if isinstance(decompressor, HeatshrinkDecompressor):
            info = {
                'window-sz2': decompressor.window_sz2,
                'lookahead-sz2': decompressor.lookahead_sz2
            }

    return info


def patch_info_sequential_inner(patch_reader, to_size):
    to_pos = 0
    number_of_size_bytes = 0
    diff_sizes = []
    extra_sizes = []
    adjustment_sizes = []

    while to_pos < to_size:
        # Diff data.
        size, number_of_bytes = unpack_size_with_length(patch_reader)

        if to_pos + size > to_size:
            raise Error("Patch diff data too long.")

        diff_sizes.append(size)
        number_of_size_bytes += number_of_bytes
        patch_reader.decompress(size)
        to_pos += size

        # Extra data.
        size, number_of_bytes = unpack_size_with_length(patch_reader)
        number_of_size_bytes += number_of_bytes

        if to_pos + size > to_size:
            raise Error("Patch extra data too long.")

        extra_sizes.append(size)
        patch_reader.decompress(size)
        to_pos += size

        # Adjustment.
        size, number_of_bytes = unpack_size_with_length(patch_reader)
        number_of_size_bytes += number_of_bytes
        adjustment_sizes.append(size)

    return (to_size,
            diff_sizes,
            extra_sizes,
            adjustment_sizes,
            number_of_size_bytes)


def patch_info_sequential(fpatch, fsize):
    patch_size = file_size(fpatch)
    compression, to_size = read_header_sequential(fpatch)
    dfpatch_size = 0
    data_format = None
    dfpatch_info = None
    patch_reader = None

    if to_size == 0:
        info = (0, [], [], [], 0)
    else:
        patch_reader = PatchReader(fpatch, compression)
        dfpatch_size = unpack_size(patch_reader)

        if dfpatch_size > 0:
            data_format = unpack_size(patch_reader)
            patch = patch_reader.decompress(dfpatch_size)
            dfpatch_info = data_format_info(data_format, patch, fsize)
            data_format = data_format_number_to_string(data_format)

        info = patch_info_sequential_inner(patch_reader, to_size)

        if not patch_reader.eof:
            raise Error('End of patch not found.')

    return (patch_size,
            compression,
            _compression_info(patch_reader),
            dfpatch_size,
            data_format,
            dfpatch_info,
            *info)


def patch_info_in_place(fpatch):
    patch_size = file_size(fpatch)
    (compression,
     memory_size,
     segment_size,
     shift_size,
     from_size,
     to_size) = read_header_in_place(fpatch)
    segments = []
    patch_reader = None

    if to_size > 0:
        patch_reader = PatchReader(fpatch, compression)

        for to_pos in range(0, to_size, segment_size):
            segment_to_size = min(segment_size, to_size - to_pos)
            dfpatch_size = unpack_size(patch_reader)

            if dfpatch_size > 0:
                data_format = unpack_size(patch_reader)
                data_format = data_format_number_to_string(data_format)
                patch_reader.decompress(dfpatch_size)
            else:
                data_format = None

            info = patch_info_sequential_inner(patch_reader, segment_to_size)
            segments.append((dfpatch_size, data_format, info))

    return (patch_size,
            compression,
            _compression_info(patch_reader),
            memory_size,
            segment_size,
            shift_size,
            from_size,
            to_size,
            segments)


def patch_info_hdiffpatch(fpatch):
    patch_size = file_size(fpatch)
    compression, to_size, _ = read_header_hdiffpatch(fpatch)
    patch_reader = None

    if to_size > 0:
        patch_reader = PatchReader(fpatch, compression)

    return (patch_size,
            compression,
            _compression_info(patch_reader),
            to_size)


def patch_info(fpatch, fsize=None):
    """Get patch information from given file-like patch object `fpatch`.

    """

    if fsize is None:
        fsize = str

    patch_type = peek_header_type(fpatch)

    if patch_type == PATCH_TYPE_SEQUENTIAL:
        return 'sequential', patch_info_sequential(fpatch, fsize)
    elif patch_type == PATCH_TYPE_IN_PLACE:
        return 'in-place', patch_info_in_place(fpatch)
    elif patch_type == PATCH_TYPE_HDIFFPATCH:
        return 'hdiffpatch', patch_info_hdiffpatch(fpatch)
    else:
        raise Error('Bad patch type {}.'.format(patch_type))


def patch_info_filename(patchfile, fsize=None):
    """Same as :func:`~detools.patch_info()`, but with a filename instead
    of a file-like object.

    """

    with open(patchfile, 'rb') as fpatch:
        return patch_info(fpatch, fsize)
