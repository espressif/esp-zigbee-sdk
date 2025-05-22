import os
import logging
import struct
from io import BytesIO
from io import StringIO
from contextlib import redirect_stdout
from ..common import file_size
from ..common import file_read
from .utils import Blocks
from .utils import DiffReader as UtilsDiffReader
from .utils import FromReader as UtilsFromReader
from .utils import create_patch_block
from .utils import load_blocks
from .utils import format_instruction
from .utils import format_pointers
from .utils import create_data_pointers_patch_block
from .utils import create_code_pointers_patch_block
from .utils import unpack_pointers_header
from .utils import unpack_pointers_blocks
from .utils import unpack_pointers_blocks_with_length


LOGGER = logging.getLogger(__name__)


class DiffReader(UtilsDiffReader):

    def __init__(self,
                 ffrom,
                 to_size,
                 call0,
                 data_pointers,
                 code_pointers,
                 call0_blocks,
                 data_pointers_blocks,
                 code_pointers_blocks):
        super().__init__(ffrom, to_size)
        self._write_call0_values_to_to(call0_blocks, call0)

        if data_pointers_blocks is not None:
            self._write_s32_values_to_to(data_pointers_blocks, data_pointers)

        if code_pointers_blocks is not None:
            self._write_s32_values_to_to(code_pointers_blocks, code_pointers)

        self._fdiff.seek(0)

    def _write_call0_values_to_to(self, blocks, from_dict):
        self._write_values_to_to_with_callback(blocks, from_dict, self._pack_u24)

    def _pack_u24(self, value):
        return struct.pack('<i', value)[:3]


class FromReader(UtilsFromReader):

    def __init__(self,
                 ffrom,
                 call0,
                 data_pointers,
                 code_pointers,
                 call0_blocks,
                 data_pointers_blocks,
                 code_pointers_blocks):
        super().__init__(ffrom)
        self._write_zeros_to_from(call0_blocks, call0, overwrite_size=3)

        if data_pointers_blocks is not None:
            self._write_zeros_to_from(data_pointers_blocks, data_pointers)

        if code_pointers_blocks is not None:
            self._write_zeros_to_from(code_pointers_blocks, code_pointers)


def disassemble_data(reader,
                     address,
                     data_begin,
                     data_end,
                     code_begin,
                     code_end,
                     data_pointers,
                     code_pointers):
    data = reader.read(4)

    if len(data) != 4:
        LOGGER.debug('Failed to read 4 data bytes at address 0x%x.',
                     address)
        return

    value = struct.unpack('<I', data)[0]

    if data_begin <= value < data_end:
        data_pointers[address] = value
    elif code_begin <= value < code_end:
        code_pointers[address] = value


def disassemble(reader,
                data_offset_begin,
                data_offset_end,
                data_begin,
                data_end,
                code_begin,
                code_end):
    """Disassembles given data and returns address-value pairs of data
    pointers and code pointers.

    """

    length = file_size(reader)
    call0 = {}
    data_pointers = {}
    code_pointers = {}

    while reader.tell() < length:
        address = reader.tell()

        if data_offset_begin <= address < data_offset_end:
            disassemble_data(reader,
                             address,
                             data_begin,
                             data_end,
                             code_begin,
                             code_end,
                             data_pointers,
                             code_pointers)
        else:
            data = reader.read(1)

            if len(data) != 1:
                LOGGER.debug('Failed to read 1 bytes at address 0x%x.',
                             address)
                continue

            lower_8 = data[0]

            if (lower_8 & 0x3f) == 0x05:
                disassemble_call0(reader, address, call0)
            elif lower_8 == 0x66:
                disassemble_bnei(reader, address, lower_8)
            elif (lower_8 & 0xf) == 0x01:
                reader.read(2)
                # print(hex(address), 'l32r')
            elif (lower_8 & 0xf) == 0x04:
                reader.read(1)
                # print(hex(address), 'l32i.n')

    return call0, data_pointers, code_pointers


def disassemble_bnei(reader, address, lower_8):
    data = reader.read(2)

    if len(data) != 2:
        LOGGER.debug('Failed to read 2 bytes at address 0x%x.',
                     address)
        return

    value = struct.unpack('<H', data)[0]
    #print(hex(address), hex((value << 8) + lower_8))


def disassemble_call0(reader, address, call0):
    reader.seek(-1, os.SEEK_CUR)
    data = reader.read(3)

    if len(data) != 3:
        LOGGER.debug('Failed to read 3 bytes at address 0x%x.',
                     address)
        return

    call0[address] = struct.unpack('<i',  data + b'\x00')[0]


def encode(ffrom, fto, data_segment):
    ffrom = BytesIO(file_read(ffrom))
    fto = BytesIO(file_read(fto))
    (from_call0,
     from_data_pointers,
     from_code_pointers) = disassemble(ffrom,
                                       data_segment.from_data_offset_begin,
                                       data_segment.from_data_offset_end,
                                       data_segment.from_data_begin,
                                       data_segment.from_data_end,
                                       data_segment.from_code_begin,
                                       data_segment.from_code_end)
    (to_call0,
     to_data_pointers,
     to_code_pointers) = disassemble(fto,
                                     data_segment.to_data_offset_begin,
                                     data_segment.to_data_offset_end,
                                     data_segment.to_data_begin,
                                     data_segment.to_data_end,
                                     data_segment.to_code_begin,
                                     data_segment.to_code_end)
    data_pointers_header, data_pointers = create_data_pointers_patch_block(
        ffrom,
        fto,
        data_segment.from_data_offset_begin,
        data_segment.from_data_begin,
        data_segment.from_data_end,
        from_data_pointers,
        to_data_pointers)
    code_pointers_header, code_pointers = create_code_pointers_patch_block(
        ffrom,
        fto,
        data_segment.from_code_begin,
        data_segment.from_code_end,
        from_code_pointers,
        to_code_pointers)
    call0 = create_patch_block(ffrom,
                               fto,
                               from_call0,
                               to_call0,
                               overwrite_size=3)
    headers, datas = zip(data_pointers, code_pointers, call0)
    patch = b''.join([data_pointers_header, code_pointers_header]
                     + list(headers)
                     + list(datas))

    return ffrom, fto, patch


def create_readers(ffrom, patch, to_size):
    """Return diff and from readers, used when applying a patch.

    """

    fpatch = BytesIO(patch)

    # Headers.
    (data_pointers_blocks_present,
     code_pointers_blocks_present,
     data_pointers_header,
     code_pointers_header,
     from_data_offset,
     from_data_begin,
     from_data_end,
     from_code_begin,
     from_code_end) = unpack_pointers_header(fpatch)
    call0_header = Blocks.unpack_header(fpatch)

    # Blocks.
    data_pointers_blocks, code_pointers_blocks = unpack_pointers_blocks(
        fpatch,
        data_pointers_blocks_present,
        code_pointers_blocks_present,
        data_pointers_header,
        code_pointers_header)
    call0_blocks = Blocks.from_fpatch(call0_header, fpatch)
    (call0,
     data_pointers,
     code_pointers) = disassemble(
         ffrom,
         from_data_offset,
         from_data_offset + from_data_end - from_data_begin,
         from_data_begin,
         from_data_end,
         from_code_begin,
         from_code_end)

    # Diff and from readers.
    diff_reader = DiffReader(ffrom,
                             to_size,
                             call0,
                             data_pointers,
                             code_pointers,
                             call0_blocks,
                             data_pointers_blocks,
                             code_pointers_blocks)
    from_reader = FromReader(ffrom,
                             call0,
                             data_pointers,
                             code_pointers,
                             call0_blocks,
                             data_pointers_blocks,
                             code_pointers_blocks)

    return diff_reader, from_reader


def info(patch, fsize):
    fpatch = BytesIO(patch)

    # Headers.
    (data_pointers_blocks_present,
     code_pointers_blocks_present,
     data_pointers_header,
     code_pointers_header,
     from_data_offset,
     from_data_begin,
     from_data_end,
     from_code_begin,
     from_code_end) = unpack_pointers_header(fpatch)
    call0_header = Blocks.unpack_header(fpatch)

    # Blocks.
    (data_pointers_blocks,
     data_pointers_blocks_size,
     code_pointers_blocks,
     code_pointers_blocks_size) = unpack_pointers_blocks_with_length(
         fpatch,
         data_pointers_blocks_present,
         code_pointers_blocks_present,
         data_pointers_header,
         code_pointers_header)
    call0_blocks, call0_blocks_size = load_blocks(call0_header, fpatch)
    fout = StringIO()

    with redirect_stdout(fout):
        format_instruction('call0', call0_blocks, call0_blocks_size, fsize)
        format_pointers(data_pointers_blocks_present,
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
                        fsize)

    return fout.getvalue()
