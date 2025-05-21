import os
import struct
from io import BytesIO
from io import StringIO
import difflib
import textwrap
from contextlib import redirect_stdout
from ..common import file_read
from ..common import pack_size
from ..common import unpack_size
from ..common import pack_usize
from ..common import unpack_usize


class Blocks(object):

    def __init__(self):
        self._blocks = []

    def __len__(self):
        return len(self._blocks)

    def __iter__(self):
        for block in self._blocks:
            yield block

    def append(self, from_offset, to_address, values):
        self._blocks.append((from_offset, to_address, values))

    def to_bytes(self):
        header = [pack_size(len(self._blocks))]
        data = []

        for from_offset, to_address, values in self._blocks:
            header.append(pack_size(from_offset))
            header.append(pack_size(to_address))
            header.append(pack_size(len(values)))

        for from_offset, to_address, values in self._blocks:
            data.extend([pack_size(value) for value in values])

        return b''.join(header), b''.join(data)

    @staticmethod
    def unpack_header(fpatch):
        header = []
        number_of_blocks = unpack_size(fpatch)

        for _ in range(number_of_blocks):
            from_offset = unpack_size(fpatch)
            to_address = unpack_size(fpatch)
            number_of_values = unpack_size(fpatch)
            header.append((from_offset, to_address, number_of_values))

        return header

    @classmethod
    def from_fpatch(cls, header, fpatch):
        blocks = cls()

        for from_offset, to_address, number_of_values in header:
            values = [unpack_size(fpatch) for _ in range(number_of_values)]
            blocks.append(from_offset, to_address, values)

        return blocks

    def __repr__(self):
        fout = StringIO()

        with redirect_stdout(fout):
            blocks = []

            for from_offset, to_address, values in self._blocks:
                blocks.append(
                    'Block(from_offset={}, to_address={}, '
                    'number_of_values={})'.format(
                        from_offset,
                        to_address,
                        len(values)))

            print(
                'Blocks(number_of_blocks={}, blocks=[{}])'.format(
                    len(self._blocks),
                    ', '.join(blocks)),
                end='')

        return fout.getvalue()


class DiffReader(object):

    def __init__(self, ffrom, to_size):
        self._ffrom = ffrom
        # ToDo: Calculate in read() for less memory usage.
        self._fdiff = BytesIO(b'\x00' * to_size)

    def read(self, size=-1):
        return self._fdiff.read(size)

    def _write_values_to_to_with_callback(self, blocks, from_dict, pack_callback):
        from_sorted = sorted(from_dict.items())

        for from_offset, to_address, values in blocks:
            from_address_base = from_sorted[from_offset][0]

            for i, value in enumerate(values):
                from_address, from_value = from_sorted[from_offset + i]
                self._fdiff.seek(to_address + from_address - from_address_base)
                self._fdiff.write(pack_callback(from_value - value))

    def _write_s32_values_to_to(self, blocks, from_dict):
        self._write_values_to_to_with_callback(blocks,
                                               from_dict,
                                               self._pack_s32)

    def _write_u64_values_to_to(self, blocks, from_dict):
        self._write_values_to_to_with_callback(blocks,
                                               from_dict,
                                               self._pack_u64)

    def _pack_s32(self, value):
        return struct.pack('<i', value)

    def _pack_u64(self, value):
        return struct.pack('<Q', value)


class FromReader(object):

    def __init__(self, ffrom):
        # ToDo: Calculate in read() for less memory usage.
        self._ffrom = BytesIO(file_read(ffrom))

    def read(self, size=-1):
        return self._ffrom.read(size)

    def seek(self, position, whence=os.SEEK_SET):
        self._ffrom.seek(position, whence)

    def _write_zeros_to_from(self, blocks, from_dict, overwrite_size=4):
        from_sorted = sorted(from_dict.items())

        for from_offset, _, values in blocks:
            for i in range(len(values)):
                from_address = from_sorted[from_offset + i][0]
                self._ffrom.seek(from_address)
                self._ffrom.write(overwrite_size * b'\x00')


def get_matching_blocks(from_addresses, to_addresses):
    """Returns matching blocks based on address differences.

    """

    from_offsets = []
    to_offsets = []

    for i in range(len(from_addresses) - 1):
        from_offsets.append(from_addresses[i + 1] - from_addresses[i])

    for i in range(len(to_addresses) - 1):
        to_offsets.append(to_addresses[i + 1] - to_addresses[i])

    sm = difflib.SequenceMatcher(None, from_offsets, to_offsets)

    return sm.get_matching_blocks()[:-1]


def create_patch_block(ffrom, fto, from_dict, to_dict, overwrite_size=4):
    """Returns a bytes object of blocks.

    """

    blocks = Blocks()

    if not from_dict or not to_dict:
        return blocks.to_bytes()

    from_sorted = sorted(from_dict.items())
    to_sorted = sorted(to_dict.items())
    from_addresses, from_values = zip(*from_sorted)
    to_addresses, to_values = zip(*to_sorted)
    matching_blocks = get_matching_blocks(from_addresses, to_addresses)

    for from_offset, to_offset, size in matching_blocks:
        # Skip small blocks as the block overhead is too big.
        if size < 8:
            continue

        size += 1
        from_slice = from_values[from_offset:from_offset + size]
        to_slice = to_values[to_offset:to_offset + size]
        diffs = [fv - tv for fv, tv in zip(from_slice, to_slice)]

        # Skip similar blocks as the block overhead is too big.
        number_of_non_zero_elements = len(diffs) - diffs.count(0)

        if number_of_non_zero_elements < 8:
            continue

        blocks.append(from_offset,
                      to_addresses[to_offset],
                      diffs)

        # Overwrite blocks with zeros.
        for address in from_addresses[from_offset:from_offset + size]:
            ffrom.seek(address)
            ffrom.write(overwrite_size * b'\x00')

        for address in to_addresses[to_offset:to_offset + size]:
            fto.seek(address)
            fto.write(overwrite_size * b'\x00')

    return blocks.to_bytes()


def load_blocks(header, fpatch):
    position = fpatch.tell()
    blocks = Blocks.from_fpatch(header, fpatch)
    blocks_size = fpatch.tell() - position

    return blocks, blocks_size


def format_blocks(blocks, blocks_size, fsize):
    print('Number of blocks:   {}'.format(len(blocks)))
    print('Size:               {}'.format(fsize(blocks_size)))
    print()

    for i, (from_offset, to_address, values) in enumerate(blocks):
        print('------------------- Block {} -------------------'.format(i + 1))
        print()
        print('From offset:        {}'.format(from_offset))
        print('To address:         0x{:x}'.format(to_address))
        print('Number of values:   {}'.format(len(values)))
        print('Values:')
        lines = textwrap.wrap(' '.join([str(value) for value in values]))
        lines = ['  ' + line for line in lines]
        print('\n'.join(lines))
        print()


def format_instruction(name, blocks, blocks_size, fsize):
    print('Instruction:        {}'.format(name))
    format_blocks(blocks, blocks_size, fsize)


def format_pointers(data_pointers_blocks_present,
                    from_data_offset,
                    from_data_begin,
                    from_data_end,
                    data_pointers_blocks,
                    data_pointers_blocks_size,
                    code_pointers_blocks_present,
                    from_code_begin,
                    from_code_end,
                    code_pointers_blocks,
                    code_pointers_blocks_size,
                    fsize):
    if data_pointers_blocks_present:
        print('Kind:               data-pointers')
        print('From data offset:   0x{:x}'.format(from_data_offset))
        print('From data begin:    0x{:x}'.format(from_data_begin))
        print('From data end:      0x{:x}'.format(from_data_end))
        format_blocks(data_pointers_blocks,
                      data_pointers_blocks_size,
                      fsize)

    if code_pointers_blocks_present:
        print('Kind:               code-pointers')
        print('From code begin:    0x{:x}'.format(from_code_begin))
        print('From code end:      0x{:x}'.format(from_code_end))
        format_blocks(code_pointers_blocks,
                      code_pointers_blocks_size,
                      fsize)


def create_data_pointers_patch_block(ffrom,
                                     fto,
                                     from_data_offset,
                                     from_data_begin,
                                     from_data_end,
                                     from_data_pointers,
                                     to_data_pointers,
                                     overwrite_size=4):
    if from_data_end == 0:
        header = b'\x00'
        data_pointers = (b'', b'')
    else:
        header = b'\x01'
        header += pack_usize(from_data_offset)
        header += pack_usize(from_data_begin)
        header += pack_usize(from_data_end)
        data_pointers = create_patch_block(ffrom,
                                           fto,
                                           from_data_pointers,
                                           to_data_pointers,
                                           overwrite_size)

    return header, data_pointers


def create_code_pointers_patch_block(ffrom,
                                     fto,
                                     from_code_begin,
                                     from_code_end,
                                     from_code_pointers,
                                     to_code_pointers,
                                     overwrite_size=4):
    if from_code_end == 0:
        header = b'\x00'
        code_pointers = (b'', b'')
    else:
        header = b'\x01'
        header += pack_usize(from_code_begin)
        header += pack_usize(from_code_end)
        code_pointers = create_patch_block(ffrom,
                                           fto,
                                           from_code_pointers,
                                           to_code_pointers,
                                           overwrite_size)

    return header, code_pointers


def unpack_pointers_header(fpatch):
    data_pointers_blocks_present = (fpatch.read(1) == b'\x01')

    if data_pointers_blocks_present:
        from_data_offset = unpack_usize(fpatch)
        from_data_begin = unpack_usize(fpatch)
        from_data_end = unpack_usize(fpatch)
    else:
        from_data_offset = 0
        from_data_begin = 0
        from_data_end = 0

    code_pointers_blocks_present = (fpatch.read(1) == b'\x01')

    if code_pointers_blocks_present:
        from_code_begin = unpack_usize(fpatch)
        from_code_end = unpack_usize(fpatch)
    else:
        from_code_begin = 0
        from_code_end = 0

    if data_pointers_blocks_present:
        data_pointers_header = Blocks.unpack_header(fpatch)
    else:
        data_pointers_header = None

    if code_pointers_blocks_present:
        code_pointers_header = Blocks.unpack_header(fpatch)
    else:
        code_pointers_header = None

    return (data_pointers_blocks_present,
            code_pointers_blocks_present,
            data_pointers_header,
            code_pointers_header,
            from_data_offset,
            from_data_begin,
            from_data_end,
            from_code_begin,
            from_code_end)


def unpack_pointers_blocks_with_length(fpatch,
                                       data_pointers_blocks_present,
                                       code_pointers_blocks_present,
                                       data_pointers_header,
                                       code_pointers_header):
    if data_pointers_blocks_present:
        data_pointers_blocks, data_pointers_blocks_size = load_blocks(
            data_pointers_header,
            fpatch)
    else:
        data_pointers_blocks = Blocks()
        data_pointers_blocks_size = 0

    if code_pointers_blocks_present:
        code_pointers_blocks, code_pointers_blocks_size = load_blocks(
            code_pointers_header,
            fpatch)
    else:
        code_pointers_blocks = Blocks()
        code_pointers_blocks_size = 0

    return (data_pointers_blocks,
            data_pointers_blocks_size,
            code_pointers_blocks,
            code_pointers_blocks_size)


def unpack_pointers_blocks(fpatch,
                           data_pointers_blocks_present,
                           code_pointers_blocks_present,
                           data_pointers_header,
                           code_pointers_header):
    (data_pointers_blocks,
     _,
     code_pointers_blocks,
     _) = unpack_pointers_blocks_with_length(
         fpatch,
         data_pointers_blocks_present,
         code_pointers_blocks_present,
         data_pointers_header,
         code_pointers_header)

    return data_pointers_blocks, code_pointers_blocks
