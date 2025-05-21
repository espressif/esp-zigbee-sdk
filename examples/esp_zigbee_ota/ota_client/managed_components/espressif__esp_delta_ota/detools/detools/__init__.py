import time
import logging
import sys
import argparse
from statistics import mean
from statistics import median
import binascii

from humanfriendly import format_size
from humanfriendly import parse_size
from humanfriendly import format_timespan
from elftools.elf.elffile import ELFFile

from .create import create_patch
from .create import create_patch_filenames
from .apply import apply_patch
from .apply import apply_patch_in_place
from .apply import apply_patch_bsdiff
from .apply import apply_patch_filenames
from .apply import apply_patch_in_place_filenames
from .apply import apply_patch_bsdiff_filenames
from .info import patch_info
from .info import patch_info_filename
from .errors import Error
from .version import __version__
from .common import DATA_FORMATS as _DATA_FORMATS
from .common import COMPRESSIONS as _COMPRESSIONS
from .data_format.elf import from_file as _data_format_elf_from_file


def _format_compression(compression, compression_info):
    info = None

    if compression == 'heatshrink':
        if compression_info:
            window_sz2 = compression_info['window-sz2']
            lookahead_sz2 = compression_info['lookahead-sz2']
            info = f'window-sz2: {window_sz2}, lookahead-sz2: {lookahead_sz2}'

    if info:
        compression += f' ({info})'

    return compression


def parse_integer(option, value):
    try:
        return int(value, 0)
    except ValueError:
        raise Error(
            "{}: Expected an integer, but got '{}'.".format(option, value))


def parse_integer_default(value, default=None):
    try:
        return int(value, 0)
    except Exception:
        return default


def parse_range(option, value):
    if value is None:
        return 0, 0

    values = value.split('-')

    if len(values) != 2:
        raise Error(
            "{}: Expected a range on the form <integer>-<integer>, but "
            "got '{}'.".format(
                option,
                value))

    begin = parse_integer(option, values[0])
    end = parse_integer(option, values[1])

    if end < begin:
        raise Error(
            '{}: End value {} is less than begin value {}.'.format(
                option,
                values[1],
                values[0]))

    return begin, end


def find_data_offset_into_binfile(option, elffile, binfile, data_range):
    """Find given data range data in the binary file and return its
    offset.

    """

    section = elffile.get_section(data_range.section_index)
    offset = data_range.begin - section['sh_addr']
    data = section.data()[offset:offset + data_range.size]

    with open(binfile, 'rb') as fin:
        try:
            return fin.read().index(data)
        except ValueError:
            data_string = binascii.hexlify(data[:16]).decode('ascii')

            if len(data) > 16:
                data_string += '...'

            raise Error(
                "Failed to calculate ELF offset. Use {} to manually give the "
                "offset. Data segment 0x{:x}-0x{:x} (data: {}) not found "
                "in '{}'.".format(option,
                                  data_range.begin,
                                  data_range.end,
                                  data_string,
                                  binfile))


def find_offset_for_address(elffile, address):
    sections = []

    for section in elffile.iter_sections():
        sections.append((section['sh_addr'],
                         section['sh_offset'],
                         section['sh_size']))

    for begin, offset, size in sorted(sections):
        if begin <= address < begin + size:
            return address - begin + offset

    raise Error('Symbol not part of any section.')


def data_format_from_files(option, elffile, binfile, offset):
    with open(elffile, 'rb') as fin:
        elffile = ELFFile(fin)
        code_range, data_range = _data_format_elf_from_file(elffile)

        if offset is None:
            offset = find_data_offset_into_binfile(option,
                                                   elffile,
                                                   binfile,
                                                   data_range)
        else:
            offset = find_offset_for_address(elffile, data_range.begin) - offset

    return (offset,
            offset + data_range.size,
            code_range.begin,
            code_range.end,
            data_range.begin,
            data_range.end)


def data_format_args(args):
    from_data_offset_begin, from_data_offset_end = parse_range(
        '--from-data-offsets',
        args.from_data_offsets)
    from_code_begin, from_code_end = parse_range(
        '--from-code-addresses',
        args.from_code_addresses)
    from_data_begin, from_data_end = parse_range(
        '--from-data-addresses',
        args.from_data_addresses)
    to_data_offset_begin, to_data_offset_end = parse_range(
        '--from-data-offsets',
        args.to_data_offsets)
    to_code_begin, to_code_end = parse_range(
        '--to-code-addresses',
        args.to_code_addresses)
    to_data_begin, to_data_end = parse_range(
        '--to-data-addresses',
        args.to_data_addresses)

    if args.from_elf_file is not None:
        (from_data_offset_begin,
         from_data_offset_end,
         from_code_begin,
         from_code_end,
         from_data_begin,
         from_data_end) = data_format_from_files(
             '--from-elf-offset',
             args.from_elf_file,
             args.fromfile,
             parse_integer_default(args.from_elf_offset))

    if args.to_elf_file is not None:
        (to_data_offset_begin,
         to_data_offset_end,
         to_code_begin,
         to_code_end,
         to_data_begin,
         to_data_end) = data_format_from_files(
             '--to-elf-offset',
             args.to_elf_file,
             args.tofile,
             parse_integer_default(args.to_elf_offset))

    if args.data_format is not None:
        print('From data offsets:   0x{:08x}-0x{:08x}'.format(
            from_data_offset_begin,
            from_data_offset_end))
        print('From code addresses: 0x{:08x}-0x{:08x}'.format(
            from_code_begin,
            from_code_end))
        print('From data addresses: 0x{:08x}-0x{:08x}'.format(
            from_data_begin,
            from_data_end))
        print('To data offsets:     0x{:08x}-0x{:08x}'.format(
            to_data_offset_begin,
            to_data_offset_end))
        print('To code addresses:   0x{:08x}-0x{:08x}'.format(
            to_code_begin,
            to_code_end))
        print('To data addresses:   0x{:08x}-0x{:08x}'.format(
            to_data_begin,
            to_data_end))

    return {
        'data_format': args.data_format,
        'from_data_offset_begin': from_data_offset_begin,
        'from_data_offset_end': from_data_offset_end,
        'from_data_begin': from_data_begin,
        'from_data_end': from_data_end,
        'from_code_begin': from_code_begin,
        'from_code_end': from_code_end,
        'to_data_offset_begin': to_data_offset_begin,
        'to_data_offset_end': to_data_offset_end,
        'to_data_begin': to_data_begin,
        'to_data_end': to_data_end,
        'to_code_begin': to_code_begin,
        'to_code_end': to_code_end
    }


def heatshrink_args(args):
    return {
        'heatshrink_window_sz2': args.heatshrink_window_sz2,
        'heatshrink_lookahead_sz2': args.heatshrink_lookahead_sz2
    }


def print_successful(filename, start_time):
    print("Successfully created '{}' in {}!".format(
        filename,
        format_timespan(time.time() - start_time)))


def _do_create_patch(args):
    start_time = time.time()
    create_patch_filenames(args.fromfile,
                           args.tofile,
                           args.patchfile,
                           args.compression,
                           args.patch_type,
                           args.algorithm,
                           args.suffix_array_algorithm,
                           match_score=args.match_score,
                           match_block_size=args.match_block_size,
                           use_mmap=not args.no_mmap,
                           **heatshrink_args(args),
                           **data_format_args(args))
    print_successful(args.patchfile, start_time)


def _do_create_patch_in_place(args):
    start_time = time.time()
    create_patch_filenames(args.fromfile,
                           args.tofile,
                           args.patchfile,
                           args.compression,
                           'in-place',
                           'bsdiff',
                           args.suffix_array_algorithm,
                           args.memory_size,
                           args.segment_size,
                           args.minimum_shift_size,
                           use_mmap=not args.no_mmap,
                           **heatshrink_args(args),
                           **data_format_args(args))
    print_successful(args.patchfile, start_time)


def _do_create_patch_bsdiff(args):
    start_time = time.time()
    create_patch_filenames(args.fromfile,
                           args.tofile,
                           args.patchfile,
                           patch_type='bsdiff')
    print_successful(args.patchfile, start_time)


def _do_apply_patch(args):
    start_time = time.time()
    apply_patch_filenames(args.fromfile, args.patchfile, args.tofile)
    print_successful(args.tofile, start_time)


def _do_apply_patch_in_place(args):
    start_time = time.time()
    apply_patch_in_place_filenames(args.memfile, args.patchfile)
    print_successful(args.memfile, start_time)


def _do_apply_patch_bsdiff(args):
    start_time = time.time()
    apply_patch_bsdiff_filenames(args.fromfile, args.patchfile, args.tofile)
    print_successful(args.tofile, start_time)


def _format_size(value):
    return format_size(value, binary=True)


def _format_bytes(value):
    return '{} bytes'.format(value)


def _format_ratio(numerator, denominator):
    if denominator > 0:
        return round(100 * numerator / denominator, 1)
    else:
        return 'inf'


def _patch_info_in_place_segment(fsize,
                                 segment_index,
                                 from_offset_begin,
                                 from_offset_end,
                                 to_offset_begin,
                                 to_offset_end,
                                 dfpatch_size,
                                 data_format,
                                 to_size,
                                 diff_sizes,
                                 extra_sizes,
                                 adjustment_sizes,
                                 number_of_size_bytes):
    del to_size
    del adjustment_sizes

    number_of_diff_bytes = sum(diff_sizes)
    number_of_extra_bytes = sum(extra_sizes)
    number_of_data_bytes = (number_of_diff_bytes + number_of_extra_bytes)
    size_data_ratio = _format_ratio(number_of_size_bytes, number_of_data_bytes)
    diff_extra_ratio = _format_ratio(number_of_diff_bytes, number_of_extra_bytes)

    print('------------------- Segment {} -------------------'.format(
        segment_index))
    print()
    print('From range:         {} - {}'.format(fsize(from_offset_begin),
                                               fsize(from_offset_end)))
    print('To range:           {} - {}'.format(fsize(to_offset_begin),
                                               fsize(to_offset_end)))
    print('Diff/extra ratio:   {} % (higher is better)'.format(diff_extra_ratio))
    print('Size/data ratio:    {} % (lower is better)'.format(size_data_ratio))
    print('Data format size:   {}'.format(fsize(dfpatch_size)))

    if dfpatch_size > 0:
        print('Data format:        {}'.format(data_format))

    print()
    print('Number of diffs:    {}'.format(len(diff_sizes)))
    print('Total diff size:    {}'.format(fsize(sum(diff_sizes))))
    print('Average diff size:  {}'.format(fsize(int(mean(diff_sizes)))))
    print('Median diff size:   {}'.format(fsize(int(median(diff_sizes)))))
    print()
    print('Number of extras:   {}'.format(len(extra_sizes)))
    print('Total extra size:   {}'.format(fsize(sum(extra_sizes))))
    print('Average extra size: {}'.format(fsize(int(mean(extra_sizes)))))
    print('Median extra size:  {}'.format(fsize(int(median(extra_sizes)))))
    print()


def _patch_info_sequential(detailed,
                           fsize,
                           patch_size,
                           compression,
                           compression_info,
                           dfpatch_size,
                           data_format,
                           dfpatch_info,
                           to_size,
                           diff_sizes,
                           extra_sizes,
                           adjustment_sizes,
                           number_of_size_bytes):
    del adjustment_sizes

    number_of_diff_bytes = sum(diff_sizes)
    number_of_extra_bytes = sum(extra_sizes)
    number_of_data_bytes = (number_of_diff_bytes + number_of_extra_bytes)
    size_data_ratio = _format_ratio(number_of_size_bytes, number_of_data_bytes)
    patch_to_ratio = _format_ratio(patch_size, to_size)
    diff_extra_ratio = _format_ratio(number_of_diff_bytes, number_of_extra_bytes)
    compression = _format_compression(compression, compression_info)

    if diff_sizes:
        mean_diff_size = fsize(int(mean(diff_sizes)))
        median_diff_size = fsize(int(median(diff_sizes)))
    else:
        mean_diff_size = '-'
        median_diff_size = '-'

    if extra_sizes:
        mean_extra_size = fsize(int(mean(extra_sizes)))
        median_extra_size = fsize(int(median(extra_sizes)))
    else:
        mean_extra_size = '-'
        median_extra_size = '-'

    print('Type:               sequential')
    print('Patch size:         {}'.format(fsize(patch_size)))
    print('To size:            {}'.format(fsize(to_size)))
    print('Patch/to ratio:     {} % (lower is better)'.format(patch_to_ratio))
    print('Diff/extra ratio:   {} % (higher is better)'.format(diff_extra_ratio))
    print('Size/data ratio:    {} % (lower is better)'.format(size_data_ratio))
    print('Compression:        {}'.format(compression))
    print('Data format size:   {}'.format(fsize(dfpatch_size)))

    if dfpatch_size > 0:
        print('Data format:        {}'.format(data_format))

    print()
    print('Number of diffs:    {}'.format(len(diff_sizes)))
    print('Total diff size:    {}'.format(fsize(sum(diff_sizes))))
    print('Average diff size:  {}'.format(mean_diff_size))
    print('Median diff size:   {}'.format(median_diff_size))
    print()
    print('Number of extras:   {}'.format(len(extra_sizes)))
    print('Total extra size:   {}'.format(fsize(sum(extra_sizes))))
    print('Average extra size: {}'.format(mean_extra_size))
    print('Median extra size:  {}'.format(median_extra_size))

    if detailed and dfpatch_size > 0:
        print()
        print('Data format details:')
        print()
        print(dfpatch_info)


def _patch_info_in_place(fsize,
                         patch_size,
                         compression,
                         compression_info,
                         memory_size,
                         segment_size,
                         from_shift_size,
                         from_size,
                         to_size,
                         segments):
    patch_to_ratio = _format_ratio(patch_size, to_size)
    compression = _format_compression(compression, compression_info)

    print('Type:               in-place')
    print('Patch size:         {}'.format(fsize(patch_size)))
    print('Memory size:        {}'.format(fsize(memory_size)))
    print('Segment size:       {}'.format(fsize(segment_size)))
    print('From shift size:    {}'.format(fsize(from_shift_size)))
    print('From size:          {}'.format(fsize(from_size)))
    print('To size:            {}'.format(fsize(to_size)))
    print('Patch/to ratio:     {} % (lower is better)'.format(patch_to_ratio))
    print('Number of segments: {}'.format(len(segments)))
    print('Compression:        {}'.format(compression))
    print()

    for i, (dfpatch_size, data_format, sequential_info) in enumerate(segments):
        from_offset_begin = max(segment_size * (i + 1) - from_shift_size, 0)
        from_offset_end = min(from_size, memory_size - from_shift_size)
        to_offset_begin = (segment_size * i)
        to_offset_end = min(to_offset_begin + segment_size, to_size)
        _patch_info_in_place_segment(fsize,
                                     i + 1,
                                     from_offset_begin,
                                     from_offset_end,
                                     to_offset_begin,
                                     to_offset_end,
                                     dfpatch_size,
                                     data_format,
                                     *sequential_info)


def _patch_info_hdiffpatch(fsize,
                           patch_size,
                           compression,
                           compression_info,
                           to_size):
    patch_to_ratio = _format_ratio(patch_size, to_size)
    compression = _format_compression(compression, compression_info)

    print('Type:               hdiffpatch')
    print('Patch size:         {}'.format(fsize(patch_size)))
    print('To size:            {}'.format(fsize(to_size)))
    print('Patch/to ratio:     {} % (lower is better)'.format(patch_to_ratio))
    print('Compression:        {}'.format(compression))


def _do_patch_info(args):
    if args.no_human:
        fsize = _format_bytes
    else:
        fsize = _format_size

    patch_type, info = patch_info_filename(args.patchfile, fsize)

    if patch_type == 'sequential':
        _patch_info_sequential(args.detailed, fsize, *info)
    elif patch_type == 'in-place':
        _patch_info_in_place(fsize, *info)
    elif patch_type == 'hdiffpatch':
        _patch_info_hdiffpatch(fsize, *info)
    else:
        raise Error('Bad patch type {}.'.format(patch_type))


def to_binary_size(value):
    return parse_size(value, binary=True)


def add_data_format_args(subparser):
    subparser.add_argument(
        '--data-format',
        choices=sorted(_DATA_FORMATS),
        help='Data format to often create smaller patches.')
    subparser.add_argument(
        '--from-elf-file',
        help='From ELF file.')
    subparser.add_argument(
        '--from-elf-offset',
        help='From ELF offset.')
    subparser.add_argument(
        '--from-data-offsets',
        help='From file data segment offset ranges.')
    subparser.add_argument(
        '--from-code-addresses',
        help='From file code address ranges.')
    subparser.add_argument(
        '--from-data-addresses',
        help='From file data address ranges.')
    subparser.add_argument(
        '--to-elf-file',
        help='To ELF file.')
    subparser.add_argument(
        '--to-elf-offset',
        help='To ELF offset.')
    subparser.add_argument(
        '--to-data-offsets',
        help='To file data segment offset ranges.')
    subparser.add_argument(
        '--to-code-addresses',
        help='To file code address ranges.')
    subparser.add_argument(
        '--to-data-addresses',
        help='To file data address ranges.')


def add_heatshrink_args(subparser):
    subparser.add_argument(
        '--heatshrink-window-sz2',
        default=8,
        type=int,
        help='Heatshrink window sz2 setting (default: %(default)s).')
    subparser.add_argument(
        '--heatshrink-lookahead-sz2',
        default=7,
        type=int,
        help='Heatshrink lookahead sz2 setting (default: %(default)s).')


def _main():
    parser = argparse.ArgumentParser(description='Binary delta encoding utility.')

    parser.add_argument('-d', '--debug', action='store_true')
    parser.add_argument('-l', '--log-level',
                        default='error',
                        choices=[
                            'debug', 'info', 'warning', 'error', 'critical'
                        ],
                        help='Set the logging level (default: %(default)s).')
    parser.add_argument('--version',
                        action='version',
                        version=__version__,
                        help='Print version information and exit.')

    # Workaround to make the subparser required in Python 3.
    subparsers = parser.add_subparsers(title='subcommands',
                                       dest='subcommand')
    subparsers.required = True

    # Create sequential patch subparser.
    subparser = subparsers.add_parser('create_patch',
                                      description='Create a sequential patch.')
    subparser.add_argument(
        '-c', '--compression',
        choices=sorted(_COMPRESSIONS),
        default='lzma',
        help='Compression algorithm (default: %(default)s).')
    subparser.add_argument(
        '-t', '--patch-type',
        choices=('sequential', 'hdiffpatch'),
        default='sequential',
        help=('Patch type. Sequential is sequential, hdiffpatch smaller '
              '(default: %(default)s).'))
    subparser.add_argument(
        '-a', '--algorithm',
        choices=('bsdiff', 'hdiffpatch', 'match-blocks'),
        default='bsdiff',
        help='Diff algorithm (default: %(default)s).')
    subparser.add_argument(
        '-s', '--suffix-array-algorithm',
        choices=('sais', 'divsufsort'),
        default='divsufsort',
        help=('Suffix array algorithm used by bsdiff algorithm '
              '(default: %(default)s).'))
    subparser.add_argument(
        '--match-score',
        type=int,
        default=6,
        help='Match score used by hdiffpatch algorithm (default: %(default)s).')
    subparser.add_argument(
        '--match-block-size',
        type=to_binary_size,
        default=64,
        help=('Match block size used by match-blocks algorithm '
              '(default: %(default)s).'))
    subparser.add_argument('--no-mmap',
                           action='store_true',
                           help='Do not use mmap.')
    add_heatshrink_args(subparser)
    add_data_format_args(subparser)
    subparser.add_argument('fromfile', help='From file.')
    subparser.add_argument('tofile', help='To file.')
    subparser.add_argument('patchfile', help='Created patch file.')
    subparser.set_defaults(func=_do_create_patch)

    # Create in-place patch subparser.
    subparser = subparsers.add_parser('create_patch_in_place',
                                      description='Create an in-place patch.')
    subparser.add_argument('-c', '--compression',
                           choices=sorted(_COMPRESSIONS),
                           default='lzma',
                           help='Compression algorithm (default: %(default)s).')
    subparser.add_argument('-s', '--suffix-array-algorithm',
                           choices=('sais', 'divsufsort'),
                           default='divsufsort',
                           help='Suffix array algorithm (default: %(default)s).')
    subparser.add_argument('--memory-size',
                           required=True,
                           type=to_binary_size,
                           help='Target memory size.')
    subparser.add_argument(
        '--segment-size',
        required=True,
        type=to_binary_size,
        help='Segment size. Must be a multiple of the largest erase block size.')
    subparser.add_argument(
        '--minimum-shift-size',
        type=to_binary_size,
        help='Minimum shift size (default: 2 * segment size).')
    subparser.add_argument('--no-mmap',
                           action='store_true',
                           help='Do not use mmap.')
    add_heatshrink_args(subparser)
    add_data_format_args(subparser)
    subparser.add_argument('fromfile', help='From file.')
    subparser.add_argument('tofile', help='To file.')
    subparser.add_argument('patchfile', help='Created patch file.')
    subparser.set_defaults(func=_do_create_patch_in_place)

    # Create bsdiff patch subparser.
    subparser = subparsers.add_parser('create_patch_bsdiff',
                                      description='Create a bsdiff patch.')
    subparser.add_argument('fromfile', help='From file.')
    subparser.add_argument('tofile', help='To file.')
    subparser.add_argument('patchfile', help='Created patch file.')
    subparser.set_defaults(func=_do_create_patch_bsdiff)

    # Apply patch subparser.
    subparser = subparsers.add_parser(
        'apply_patch',
        description='Apply given sequential or hdiffpatch patch.')
    subparser.add_argument('fromfile', help='From file.')
    subparser.add_argument('patchfile', help='Patch file.')
    subparser.add_argument('tofile', help='Created to file.')
    subparser.set_defaults(func=_do_apply_patch)

    # In-place apply patch subparser.
    subparser = subparsers.add_parser('apply_patch_in_place',
                                      description='Apply given in-place patch.')
    subparser.add_argument('memfile', help='Memory file.')
    subparser.add_argument('patchfile', help='Patch file.')
    subparser.set_defaults(func=_do_apply_patch_in_place)

    # Bsdiff apply patch subparser.
    subparser = subparsers.add_parser('apply_patch_bsdiff',
                                      description='Apply given bsdiff patch.')
    subparser.add_argument('fromfile', help='From file.')
    subparser.add_argument('patchfile', help='Patch file.')
    subparser.add_argument('tofile', help='Created to file.')
    subparser.set_defaults(func=_do_apply_patch_bsdiff)

    # Patch info subparser.
    subparser = subparsers.add_parser('patch_info',
                                      description='Display patch info.')
    subparser.add_argument('--no-human',
                           action='store_true',
                           help='Print sizes without units.')
    subparser.add_argument('--detailed',
                           action='store_true',
                           help='Print detailed information.')
    subparser.add_argument('patchfile', help='Patch file.')
    subparser.set_defaults(func=_do_patch_info)

    args = parser.parse_args()

    level = logging.getLevelName(args.log_level.upper())
    logging.basicConfig(level=level, format='%(asctime)s %(message)s')

    if args.debug:
        args.func(args)
    else:
        try:
            args.func(args)
        except BaseException as e:
            sys.exit('error: ' + str(e))
