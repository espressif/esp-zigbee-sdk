import io
import time
import logging
import tempfile
import mmap
import lzma
from bz2 import BZ2Compressor
from io import BytesIO
import struct
import bitstruct
from humanfriendly import format_timespan
from humanfriendly import format_size
from .errors import Error
from .compression.crle import CrleCompressor
from .compression.none import NoneCompressor
from .compression.heatshrink import HeatshrinkCompressor
from .compression.zstd import ZstdCompressor
from .compression.lz4 import Lz4Compressor
from .common import PATCH_TYPE_SEQUENTIAL
from .common import PATCH_TYPE_IN_PLACE
from .common import PATCH_TYPE_HDIFFPATCH
from .common import DATA_FORMATS
from .common import PATCH_TYPES
from .common import format_bad_compression_string
from .common import compression_string_to_number
from .common import div_ceil
from .common import file_size
from .common import file_read
from .common import pack_size
from .common import DataSegment
from .common import unpack_size_bytes
from .data_format import encode as data_format_encode
from .suffix_array import sais
from .suffix_array import divsufsort
from . import bsdiff
from . import hdiffpatch


LOGGER = logging.getLogger(__name__)


def pack_header(patch_type, compression):
    return bitstruct.pack('p1u3u4', patch_type, compression)


def create_compressor(compression,
                      heatshrink_window_sz2,
                      heatshrink_lookahead_sz2):
    if compression == 'lzma':
        compressor = lzma.LZMACompressor(format=lzma.FORMAT_ALONE)
    elif compression == 'bz2':
        compressor = BZ2Compressor()
    elif compression == 'none':
        compressor = NoneCompressor()
    elif compression == 'crle':
        compressor = CrleCompressor()
    elif compression == 'heatshrink':
        compressor = HeatshrinkCompressor(heatshrink_window_sz2,
                                          heatshrink_lookahead_sz2)
    elif compression == 'zstd':
        compressor = ZstdCompressor()
    elif compression == 'lz4':
        compressor = Lz4Compressor()
    else:
        raise Error(format_bad_compression_string(compression))

    return compressor


def create_suffix_array(suffix_array, data, suffix_array_algorithm):
    if suffix_array_algorithm == 'sais':
        sais(data, suffix_array)
    elif suffix_array_algorithm == 'divsufsort':
        divsufsort(data, suffix_array)
    else:
        raise Error('Bad suffix array algorithm {}.'.format(suffix_array_algorithm))


def temporary_file(size):
    fp = tempfile.TemporaryFile()
    fp.truncate(size)
    fp.flush()
    fp.seek(0)

    return fp


def mmap_read_only(fin):
    return mmap.mmap(fin.fileno(), 0, access=mmap.ACCESS_READ)


def mmap_read_write(fin):
    return mmap.mmap(fin.fileno(), 0)


def create_chunks_mmap(ffrom, fto, suffix_array_algorithm):
    LOGGER.debug('Creating chunks using mmap.')

    suffix_array_size = 4 * (file_size(ffrom) + 1)

    with mmap_read_only(ffrom) as from_mmap:
        with mmap_read_only(fto) as to_mmap:
            with temporary_file(suffix_array_size) as fsuffix_array:
                with mmap_read_write(fsuffix_array) as suffix_array_mmap:
                    start_time = time.time()
                    create_suffix_array(suffix_array_mmap,
                                        from_mmap,
                                        suffix_array_algorithm)

                    LOGGER.info('Suffix array of %s created in %s using mmap.',
                                format_size(suffix_array_size),
                                format_timespan(time.time() - start_time))

                    with temporary_file(file_size(fto) + 1) as fde:
                        with mmap_read_write(fde) as fde_mmap:
                            start_time = time.time()
                            chunks = bsdiff.create_patch(suffix_array_mmap,
                                                         from_mmap,
                                                         to_mmap,
                                                         fde_mmap)

                            LOGGER.info(
                                'Bsdiff algorithm completed in %s using mmap.',
                                format_timespan(time.time() - start_time))

    return chunks


def create_chunks_heap(ffrom, fto, suffix_array_algorithm):
    LOGGER.debug('Creating chunks using the heap.')

    from_data = file_read(ffrom)
    start_time = time.time()
    suffix_array = bytearray(4 * (len(from_data) + 1))
    create_suffix_array(suffix_array, from_data, suffix_array_algorithm)

    LOGGER.info('Suffix array of %s created in %s.',
                format_size(len(suffix_array)),
                format_timespan(time.time() - start_time))

    start_time = time.time()
    chunks = bsdiff.create_patch(suffix_array,
                                 from_data,
                                 file_read(fto),
                                 bytearray(file_size(fto) + 1))

    LOGGER.info('Bsdiff algorithm completed in %s.',
                format_timespan(time.time() - start_time))

    return chunks


def create_chunks(ffrom, fto, suffix_array_algorithm, use_mmap):
    if not use_mmap:
        return create_chunks_heap(ffrom, fto, suffix_array_algorithm)

    try:
        return create_chunks_mmap(ffrom, fto, suffix_array_algorithm)
    except (io.UnsupportedOperation, ValueError):
        return create_chunks_heap(ffrom, fto, suffix_array_algorithm)


def create_patch_sequential_data(ffrom,
                                 fto,
                                 fpatch,
                                 compression,
                                 suffix_array_algorithm,
                                 data_format,
                                 data_segment,
                                 use_mmap,
                                 heatshrink_window_sz2,
                                 heatshrink_lookahead_sz2):
    to_size = file_size(fto)

    if to_size == 0:
        return

    compressor = create_compressor(compression,
                                   heatshrink_window_sz2,
                                   heatshrink_lookahead_sz2)

    if data_format is None:
        dfpatch = pack_size(0)
    else:
        ffrom, fto, patch = data_format_encode(
            ffrom,
            fto,
            data_format,
            data_segment)

        dfpatch = pack_size(len(patch))
        dfpatch += pack_size(DATA_FORMATS[data_format])
        dfpatch += patch

    fpatch.write(compressor.compress(dfpatch))
    chunks = create_chunks(ffrom, fto, suffix_array_algorithm, use_mmap)
    start_time = time.time()

    for chunk in chunks:
        fpatch.write(compressor.compress(chunk))

    fpatch.write(compressor.flush())

    LOGGER.info('Compression (%s) completed in %s.',
                compression,
                format_timespan(time.time() - start_time))


def create_patch_sequential(ffrom,
                            fto,
                            fpatch,
                            compression,
                            suffix_array_algorithm,
                            data_format,
                            data_segment,
                            use_mmap,
                            heatshrink_window_sz2,
                            heatshrink_lookahead_sz2):
    fpatch.write(pack_header(PATCH_TYPE_SEQUENTIAL,
                             compression_string_to_number(compression)))
    fpatch.write(pack_size(file_size(fto)))
    create_patch_sequential_data(ffrom,
                                 fto,
                                 fpatch,
                                 compression,
                                 suffix_array_algorithm,
                                 data_format,
                                 data_segment,
                                 use_mmap,
                                 heatshrink_window_sz2,
                                 heatshrink_lookahead_sz2)


def calc_shift(memory_size, segment_size, minimum_shift_size, from_size):
    """Shift from data as many segments as possible.

    """

    memory_segments = div_ceil(memory_size, segment_size)
    from_segments = div_ceil(from_size, segment_size)

    shift_segments = (memory_segments - from_segments)
    shift_size = (shift_segments * segment_size)

    if shift_size < minimum_shift_size:
        shift_size = minimum_shift_size

    return shift_size


def create_patch_in_place(ffrom,
                          fto,
                          fpatch,
                          compression,
                          suffix_array_algorithm,
                          memory_size,
                          segment_size,
                          minimum_shift_size,
                          data_format,
                          data_segment,
                          use_mmap,
                          heatshrink_window_sz2,
                          heatshrink_lookahead_sz2):
    if (memory_size % segment_size) != 0:
        raise Error(
            'Memory size {} is not a multiple of segment size {}.'.format(
                memory_size,
                segment_size))

    if minimum_shift_size is None:
        minimum_shift_size = 2 * segment_size

    if (minimum_shift_size % segment_size) != 0:
        raise Error(
            'Minimum shift size {} is not a multiple of segment size {}.'.format(
                minimum_shift_size,
                segment_size))

    from_data = ffrom.read()
    from_size = len(from_data)
    to_data = fto.read()
    to_size = len(to_data)
    shift_size = calc_shift(memory_size,
                            segment_size,
                            minimum_shift_size,
                            len(from_data))
    shifted_size = (memory_size - shift_size)
    from_data = from_data[:shifted_size]
    number_of_to_segments = div_ceil(to_size, segment_size)

    # Create a sequential patch for each segment.
    fsegments = BytesIO()

    for segment in range(number_of_to_segments):
        to_offset = (segment * segment_size)
        from_offset = max(to_offset + segment_size - shift_size, 0)
        fsegment = BytesIO()
        create_patch_sequential_data(
            BytesIO(from_data[from_offset:]),
            BytesIO(to_data[to_offset:to_offset + segment_size]),
            fsegment,
            'none',
            suffix_array_algorithm,
            data_format,
            data_segment,
            use_mmap,
            heatshrink_window_sz2,
            heatshrink_lookahead_sz2)
        fsegments.write(fsegment.getvalue())

    # Create the patch.
    fpatch.write(pack_header(PATCH_TYPE_IN_PLACE,
                             compression_string_to_number(compression)))
    fpatch.write(pack_size(memory_size))
    fpatch.write(pack_size(segment_size))
    fpatch.write(pack_size(shift_size))
    fpatch.write(pack_size(from_size))
    fpatch.write(pack_size(to_size))

    if to_size == 0:
        return

    compressor = create_compressor(compression,
                                   heatshrink_window_sz2,
                                   heatshrink_lookahead_sz2)
    fpatch.write(compressor.compress(fsegments.getvalue()))
    fpatch.write(compressor.flush())


def offtout(x):
    if x < 0:
        x *= -1
        x |= (1 << 63)

    return struct.pack('<Q', x)


def create_patch_bsdiff(ffrom, fto, fpatch):
    to_size = file_size(fto)
    from_data = file_read(ffrom)
    start_time = time.time()
    suffix_array = bytearray(4 * (len(from_data) + 1))
    divsufsort(from_data, suffix_array)
    chunks = bsdiff.create_patch(suffix_array,
                                 from_data,
                                 file_read(fto),
                                 bytearray(file_size(fto) + 1))

    LOGGER.info('Bsdiff algorithm completed in %s.',
                format_timespan(time.time() - start_time))

    fctrl = BytesIO()
    fdiff = BytesIO()
    fextra = BytesIO()

    start_time = time.time()

    ctrl_compressor = BZ2Compressor()
    diff_compressor = BZ2Compressor()
    extra_compressor = BZ2Compressor()

    for i in range(0, len(chunks), 5):
        size = offtout(unpack_size_bytes(chunks[i + 0]))
        fctrl.write(ctrl_compressor.compress(size))
        fdiff.write(diff_compressor.compress(chunks[i + 1]))
        size = offtout(unpack_size_bytes(chunks[i + 2]))
        fctrl.write(ctrl_compressor.compress(size))
        fextra.write(extra_compressor.compress(chunks[i + 3]))
        size = offtout(unpack_size_bytes(chunks[i + 4]))
        fctrl.write(ctrl_compressor.compress(size))

    fctrl.write(ctrl_compressor.flush())
    fdiff.write(diff_compressor.flush())
    fextra.write(extra_compressor.flush())

    LOGGER.info('Compression completed in %s.',
                format_timespan(time.time() - start_time))

    # Write everything to the patch file.
    fpatch.write(b'BSDIFF40')
    fpatch.write(offtout(fctrl.tell()))
    fpatch.write(offtout(fdiff.tell()))
    fpatch.write(offtout(to_size))
    fpatch.write(fctrl.getvalue())
    fpatch.write(fdiff.getvalue())
    fpatch.write(fextra.getvalue())


def create_patch_hdiffpatch_generic(ffrom,
                                    fto,
                                    match_score,
                                    match_block_size,
                                    patch_type,
                                    use_mmap):
    if use_mmap:
        with mmap_read_only(ffrom) as from_mmap:
            with mmap_read_only(fto) as to_mmap:
                return hdiffpatch.create_patch(from_mmap,
                                               to_mmap,
                                               match_score,
                                               match_block_size,
                                               patch_type)
    else:
        return hdiffpatch.create_patch(file_read(ffrom),
                                       file_read(fto),
                                       match_score,
                                       match_block_size,
                                       patch_type)


def create_patch_hdiffpatch(ffrom,
                            fto,
                            fpatch,
                            compression,
                            match_score,
                            use_mmap,
                            heatshrink_window_sz2,
                            heatshrink_lookahead_sz2):
    start_time = time.time()
    patch = create_patch_hdiffpatch_generic(ffrom,
                                            fto,
                                            match_score,
                                            0,
                                            PATCH_TYPE_HDIFFPATCH,
                                            use_mmap)

    LOGGER.info('Hdiffpatch algorithm completed in %s.',
                format_timespan(time.time() - start_time))

    start_time = time.time()
    compressor = create_compressor(compression,
                                   heatshrink_window_sz2,
                                   heatshrink_lookahead_sz2)

    fpatch.write(pack_header(PATCH_TYPE_HDIFFPATCH,
                             compression_string_to_number(compression)))
    fpatch.write(pack_size(file_size(fto)))
    fpatch.write(pack_size(len(patch)))
    fpatch.write(compressor.compress(patch))
    fpatch.write(compressor.flush())

    LOGGER.info('Compression completed in %s.',
                format_timespan(time.time() - start_time))


def create_patch_match_blocks(ffrom,
                              fto,
                              fpatch,
                              compression,
                              patch_type,
                              match_block_size,
                              use_mmap,
                              heatshrink_window_sz2,
                              heatshrink_lookahead_sz2):
    start_time = time.time()
    patch = create_patch_hdiffpatch_generic(ffrom,
                                            fto,
                                            0,
                                            match_block_size,
                                            PATCH_TYPES[patch_type],
                                            use_mmap)

    LOGGER.info('Match blocks algorithm completed in %s.',
                format_timespan(time.time() - start_time))

    start_time = time.time()
    compressor = create_compressor(compression,
                                   heatshrink_window_sz2,
                                   heatshrink_lookahead_sz2)

    if patch_type == 'hdiffpatch':
        fpatch.write(pack_header(PATCH_TYPE_HDIFFPATCH,
                                 compression_string_to_number(compression)))
        fpatch.write(pack_size(file_size(fto)))
        fpatch.write(pack_size(len(patch)))
    elif patch_type == 'sequential':
        fpatch.write(pack_header(PATCH_TYPE_SEQUENTIAL,
                                 compression_string_to_number(compression)))
        fpatch.write(pack_size(file_size(fto)))
        fpatch.write(compressor.compress(pack_size(0)))
    else:
        raise Error('Bad patch type {}.'.format(patch_type))

    fpatch.write(compressor.compress(patch))
    fpatch.write(compressor.flush())

    LOGGER.info('Compression completed in %s.',
                format_timespan(time.time() - start_time))


def create_patch(ffrom,
                 fto,
                 fpatch,
                 compression='lzma',
                 patch_type='sequential',
                 algorithm='bsdiff',
                 suffix_array_algorithm='divsufsort',
                 memory_size=None,
                 segment_size=None,
                 minimum_shift_size=None,
                 data_format=None,
                 from_data_offset_begin=0,
                 from_data_offset_end=0,
                 from_data_begin=0,
                 from_data_end=0,
                 from_code_begin=0,
                 from_code_end=0,
                 to_data_offset_begin=0,
                 to_data_offset_end=0,
                 to_data_begin=0,
                 to_data_end=0,
                 to_code_begin=0,
                 to_code_end=0,
                 match_score=6,
                 match_block_size=64,
                 use_mmap=True,
                 heatshrink_window_sz2=8,
                 heatshrink_lookahead_sz2=7):
    """Create a patch from `ffrom` to `fto` and write it to `fpatch`. All
    three arguments are file-like objects.

    `compression` must be ``'bz2'``, ``'crle'``, ``'lzma'``,
    ``'zstd'``, ``'lz4'`` or ``'none'``.

    `patch_type` must be ``'sequential'``, ``'in-place'`` or
    ``'bsdiff'``.

    `algorithm` must be ``'sequential'`` or ``'hdiffpatch'``.

    `suffix_array_algorithm` must be ``'sais'`` or ``'divsufsort'``.

    `memory_size`, `segment_size` and `minimum_shift_size` are used
    when creating an in-place patch.

    `match_score` is used by the hdiffpatch algorithm. Default
    6. Recommended 0-4 for binary files and 4-9 for text files.

    `match_block_size` is used by the match-blocks algorithm. Default
    64. Less memory is needed to create the patch, but the patch will
    be bigger.

    >>> ffrom = open('foo.old', 'rb')
    >>> fto = open('foo.new', 'rb')
    >>> fpatch = open('foo.patch', 'wb')
    >>> create_patch(ffrom, fto, fpatch)

    """

    data_segment = DataSegment(from_data_offset_begin,
                               from_data_offset_end,
                               from_data_begin,
                               from_data_end,
                               from_code_begin,
                               from_code_end,
                               to_data_offset_begin,
                               to_data_offset_end,
                               to_data_begin,
                               to_data_end,
                               to_code_begin,
                               to_code_end)

    if algorithm == 'bsdiff' and patch_type == 'sequential':
        create_patch_sequential(ffrom,
                                fto,
                                fpatch,
                                compression,
                                suffix_array_algorithm,
                                data_format,
                                data_segment,
                                use_mmap,
                                heatshrink_window_sz2,
                                heatshrink_lookahead_sz2)
    elif algorithm == 'bsdiff' and patch_type == 'in-place':
        create_patch_in_place(ffrom,
                              fto,
                              fpatch,
                              compression,
                              suffix_array_algorithm,
                              memory_size,
                              segment_size,
                              minimum_shift_size,
                              data_format,
                              data_segment,
                              use_mmap,
                              heatshrink_window_sz2,
                              heatshrink_lookahead_sz2)
    elif algorithm == 'bsdiff' and patch_type == 'bsdiff':
        create_patch_bsdiff(ffrom, fto, fpatch)
    elif algorithm == 'hdiffpatch' and patch_type == 'hdiffpatch':
        create_patch_hdiffpatch(ffrom,
                                fto,
                                fpatch,
                                compression,
                                match_score,
                                use_mmap,
                                heatshrink_window_sz2,
                                heatshrink_lookahead_sz2)
    elif algorithm == 'match-blocks':
        create_patch_match_blocks(ffrom,
                                  fto,
                                  fpatch,
                                  compression,
                                  patch_type,
                                  match_block_size,
                                  use_mmap,
                                  heatshrink_window_sz2,
                                  heatshrink_lookahead_sz2)
    else:
        raise Error(
            "Bad algorithm ({}) and patch type ({}) combination.".format(
                algorithm,
                patch_type))


def create_patch_filenames(fromfile,
                           tofile,
                           patchfile,
                           compression='lzma',
                           patch_type='sequential',
                           algorithm='bsdiff',
                           suffix_array_algorithm='divsufsort',
                           memory_size=None,
                           segment_size=None,
                           minimum_shift_size=None,
                           data_format=None,
                           from_data_offset_begin=0,
                           from_data_offset_end=0,
                           from_data_begin=0,
                           from_data_end=0,
                           from_code_begin=0,
                           from_code_end=0,
                           to_data_offset_begin=0,
                           to_data_offset_end=0,
                           to_data_begin=0,
                           to_data_end=0,
                           to_code_begin=0,
                           to_code_end=0,
                           match_score=6,
                           match_block_size=64,
                           use_mmap=True,
                           heatshrink_window_sz2=8,
                           heatshrink_lookahead_sz2=7):
    """Same as :func:`~detools.create_patch()`, but with filenames instead
    of file-like objects.

    >>> create_patch_filenames('foo.old', 'foo.new', 'foo.patch')

    """

    with open(fromfile, 'rb') as ffrom:
        with open(tofile, 'rb') as fto:
            with open(patchfile, 'wb') as fpatch:
                create_patch(ffrom,
                             fto,
                             fpatch,
                             compression,
                             patch_type,
                             algorithm,
                             suffix_array_algorithm,
                             memory_size,
                             segment_size,
                             minimum_shift_size,
                             data_format,
                             from_data_offset_begin,
                             from_data_offset_end,
                             from_data_begin,
                             from_data_end,
                             from_code_begin,
                             from_code_end,
                             to_data_offset_begin,
                             to_data_offset_end,
                             to_data_begin,
                             to_data_end,
                             to_code_begin,
                             to_code_end,
                             match_score,
                             match_block_size,
                             use_mmap,
                             heatshrink_window_sz2,
                             heatshrink_lookahead_sz2)
