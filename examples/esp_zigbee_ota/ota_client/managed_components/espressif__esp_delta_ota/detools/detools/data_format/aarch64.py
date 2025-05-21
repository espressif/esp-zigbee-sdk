import os
import logging
import struct
from io import BytesIO
from io import StringIO
from contextlib import redirect_stdout
import bitstruct
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

    _CF_ADD = bitstruct.compile('u8u2u12u5u5')
    _CF_ADRP = bitstruct.compile('u1u2u5u19u5')

    def __init__(self,
                 ffrom,
                 to_size,
                 b,
                 bl,
                 add,
                 add_generic,
                 ldr,
                 adrp,
                 str_,
                 str_imm_64,
                 data_pointers,
                 code_pointers,
                 b_blocks,
                 bl_blocks,
                 add_blocks,
                 add_generic_blocks,
                 ldr_blocks,
                 adrp_blocks,
                 str_blocks,
                 str_imm_64_blocks,
                 data_pointers_blocks,
                 code_pointers_blocks):
        super().__init__(ffrom, to_size)
        self._write_s32_values_to_to(b_blocks, b)
        self._write_s32_values_to_to(bl_blocks, bl)
        self._write_add_values_to_to(add_blocks, add)
        self._write_s32_values_to_to(add_generic_blocks, add_generic)
        self._write_s32_values_to_to(ldr_blocks, ldr)
        self._write_adrp_values_to_to(adrp_blocks, adrp)
        self._write_s32_values_to_to(str_blocks, str_)
        self._write_s32_values_to_to(str_imm_64_blocks, str_imm_64)

        if data_pointers_blocks is not None:
            self._write_u64_values_to_to(data_pointers_blocks, data_pointers)

        if code_pointers_blocks is not None:
            self._write_u64_values_to_to(code_pointers_blocks, code_pointers)

        self._fdiff.seek(0)

    def _write_add_values_to_to(self, blocks, from_dict):
        self._write_values_to_to_with_callback(blocks, from_dict, self._pack_add)

    def _write_adrp_values_to_to(self, blocks, from_dict):
        self._write_values_to_to_with_callback(blocks, from_dict, self._pack_adrp)

    def _pack_add(self, value):
        imm12 = (value & 0xfff)
        shift = ((value >> 12) & 0x3)
        r = ((value >> 14) & 0x1f)
        value = self._CF_ADD.pack(0b10010001, shift, imm12, r, r)

        return value[::-1]

    def _pack_adrp(self, value):
        immlo = (value & 0x3)
        immhi = ((value >> 2) & 0x7ffff)
        rd = ((value >> 21) & 0x1f)
        value = self._CF_ADRP.pack(0b1, immlo, 0b10000, immhi, rd)

        return value[::-1]


class FromReader(UtilsFromReader):

    def __init__(self,
                 ffrom,
                 b,
                 bl,
                 add,
                 add_generic,
                 ldr,
                 adrp,
                 str_,
                 str_imm_64,
                 data_pointers,
                 code_pointers,
                 b_blocks,
                 bl_blocks,
                 add_blocks,
                 add_generic_blocks,
                 ldr_blocks,
                 adrp_blocks,
                 str_blocks,
                 str_imm_64_blocks,
                 data_pointers_blocks,
                 code_pointers_blocks):
        super().__init__(ffrom)
        self._write_zeros_to_from(b_blocks, b)
        self._write_zeros_to_from(bl_blocks, bl)
        self._write_zeros_to_from(add_blocks, add)
        self._write_zeros_to_from(add_generic_blocks, add_generic)
        self._write_zeros_to_from(ldr_blocks, ldr)
        self._write_zeros_to_from(adrp_blocks, adrp)
        self._write_zeros_to_from(str_blocks, str_)
        self._write_zeros_to_from(str_imm_64_blocks, str_imm_64)

        if data_pointers_blocks is not None:
            self._write_zeros_to_from(data_pointers_blocks,
                                      data_pointers,
                                      overwrite_size=8)

        if code_pointers_blocks is not None:
            self._write_zeros_to_from(code_pointers_blocks,
                                      code_pointers,
                                      overwrite_size=8)


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

    data += reader.read(4)

    if len(data) == 4:
        return
    elif len(data) != 8:
        LOGGER.debug('Failed to read 8 data bytes at address 0x%x.',
                     address)
        return

    value = struct.unpack('<Q', data)[0]

    if data_begin <= value < data_end:
        data_pointers[address] = value
    elif code_begin <= value < code_end:
        code_pointers[address] = value
    else:
        reader.seek(-4, os.SEEK_CUR)


def disassemble_b(reader, address, b):
    reader.seek(-4, os.SEEK_CUR)
    data = reader.read(4)
    b[address] = struct.unpack('<i', data)[0]


def disassemble_bl(reader, address, bl):
    reader.seek(-4, os.SEEK_CUR)
    data = reader.read(4)
    bl[address] = struct.unpack('<i', data)[0]


def disassemble_add(reader, address, add, add_generic, value):
    rn = ((value >> 5) & 0x1f)
    rd = (value & 0x1f)

    if rn == rd:
        shift = ((value >> 22) & 0x3)
        imm12 = ((value >> 10) & 0xfff)
        value = imm12
        value |= (shift << 12)
        value |= (rn << 14)
        add[address] = value
    else:
        reader.seek(-4, os.SEEK_CUR)
        data = reader.read(4)
        add_generic[address] = struct.unpack('<i', data)[0]

def disassemble_ldr(reader, address, ldr):
    reader.seek(-4, os.SEEK_CUR)
    data = reader.read(4)
    ldr[address] = struct.unpack('<i', data)[0]


def disassemble_str(reader, address, str_):
    reader.seek(-4, os.SEEK_CUR)
    data = reader.read(4)
    str_[address] = struct.unpack('<i', data)[0]


def disassemble_str_imm_64(reader, address, str_imm_64):
    reader.seek(-4, os.SEEK_CUR)
    data = reader.read(4)
    str_imm_64[address] = struct.unpack('<i', data)[0]


def disassemble_adrp(address, adrp, value):
    rd = (value & 0x1f)
    immhi = ((value >> 5) & 0x7ffff)
    immlo = ((value >> 29) & 0x3)
    value = immlo
    value |= (immhi << 2)
    value |= (rd << 21)
    adrp[address] = value


def disassemble(reader,
                data_offset_begin,
                data_offset_end,
                data_begin,
                data_end,
                code_begin,
                code_end):
    """Disassembles given data and returns address-value pairs of b.w, bl,
    *ldr, *ldr.w, data pointers and code pointers.

    """

    length = file_size(reader)
    b = {}
    bl = {}
    add = {}
    add_generic = {}
    ldr = {}
    str_ = {}
    str_imm_64 = {}
    adrp = {}
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
            data = reader.read(4)

            if len(data) != 4:
                LOGGER.debug('Failed to read 4 upper bytes at address 0x%x.',
                             address)
                continue

            value = struct.unpack('<I', data)[0]

            if (value & 0xfc000000) == 0x94000000:
                disassemble_bl(reader, address, bl)
            elif (value & 0xff000000) == 0x91000000:
                disassemble_add(reader, address, add, add_generic, value)
            elif (value & 0xff000000) == 0x14000000:
                # disassemble_b(reader, address, b)
                pass
            elif (value & 0xffc00000) == 0xf9400000:
                disassemble_ldr(reader, address, ldr)
            elif (value & 0xffc00000) == 0xa9000000:
                disassemble_str(reader, address, str_)
            elif (value & 0x9f000000) == 0x90000000:
                disassemble_adrp(address, adrp, value)
            elif (value & 0xffc00000) == 0xb9400000:
                disassemble_ldr(reader, address, ldr)
            elif (value & 0xffc00000) == 0x39400000:
                # LDRB (immediate) Unsigned offset
                disassemble_ldr(reader, address, ldr)
            elif (value & 0xffc00000) == 0x39000000:
                # LDRB (immediate) Unsigned offset
                disassemble_ldr(reader, address, ldr)
            elif (value & 0xffc00000) == 0xb9000000:
                disassemble_str(reader, address, str_)
            elif (value & 0xffe00000) == 0xf8400000:
                # LDUR 64-bit
                disassemble_ldr(reader, address, ldr)
            elif (value & 0xffe00000) == 0xb8400000:
                # LDTR 64-bit
                disassemble_ldr(reader, address, ldr)
            elif (value & 0xffc00000) == 0xf9000000:
                disassemble_str_imm_64(reader, address, str_imm_64)

    return (b,
            bl,
            add,
            add_generic,
            ldr,
            adrp,
            str_,
            str_imm_64,
            data_pointers,
            code_pointers)


def encode(ffrom, fto, data_segment):
    ffrom = BytesIO(file_read(ffrom))
    fto = BytesIO(file_read(fto))
    (from_b,
     from_bl,
     from_add,
     from_add_generic,
     from_ldr,
     from_adrp,
     from_str,
     from_str_imm_64,
     from_data_pointers,
     from_code_pointers) = disassemble(ffrom,
                                       data_segment.from_data_offset_begin,
                                       data_segment.from_data_offset_end,
                                       data_segment.from_data_begin,
                                       data_segment.from_data_end,
                                       data_segment.from_code_begin,
                                       data_segment.from_code_end)
    (to_b,
     to_bl,
     to_add,
     to_add_generic,
     to_ldr,
     to_adrp,
     to_str,
     to_str_imm_64,
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
        to_data_pointers,
        overwrite_size=8)
    code_pointers_header, code_pointers = create_code_pointers_patch_block(
        ffrom,
        fto,
        data_segment.from_code_begin,
        data_segment.from_code_end,
        from_code_pointers,
        to_code_pointers,
        overwrite_size=8)
    b = create_patch_block(ffrom, fto, from_b, to_b)
    bl = create_patch_block(ffrom, fto, from_bl, to_bl)
    add = create_patch_block(ffrom, fto, from_add, to_add)
    add_generic = create_patch_block(ffrom,
                                     fto,
                                     from_add_generic,
                                     to_add_generic)
    ldr = create_patch_block(ffrom, fto, from_ldr, to_ldr)
    adrp = create_patch_block(ffrom, fto, from_adrp, to_adrp)
    str_ = create_patch_block(ffrom, fto, from_str, to_str)
    str_imm_64 = create_patch_block(ffrom,
                                    fto,
                                    from_str_imm_64,
                                    to_str_imm_64)
    headers, datas = zip(data_pointers,
                         code_pointers,
                         b,
                         bl,
                         add,
                         add_generic,
                         ldr,
                         adrp,
                         str_,
                         str_imm_64)
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
    b_header = Blocks.unpack_header(fpatch)
    bl_header = Blocks.unpack_header(fpatch)
    add_header = Blocks.unpack_header(fpatch)
    add_generic_header = Blocks.unpack_header(fpatch)
    ldr_header = Blocks.unpack_header(fpatch)
    adrp_header = Blocks.unpack_header(fpatch)
    str_header = Blocks.unpack_header(fpatch)
    str_imm_64_header = Blocks.unpack_header(fpatch)

    # Blocks.
    data_pointers_blocks, code_pointers_blocks = unpack_pointers_blocks(
        fpatch,
        data_pointers_blocks_present,
        code_pointers_blocks_present,
        data_pointers_header,
        code_pointers_header)
    b_blocks = Blocks.from_fpatch(b_header, fpatch)
    bl_blocks = Blocks.from_fpatch(bl_header, fpatch)
    add_blocks = Blocks.from_fpatch(add_header, fpatch)
    add_generic_blocks = Blocks.from_fpatch(add_generic_header, fpatch)
    ldr_blocks = Blocks.from_fpatch(ldr_header, fpatch)
    adrp_blocks = Blocks.from_fpatch(adrp_header, fpatch)
    str_blocks = Blocks.from_fpatch(str_header, fpatch)
    str_imm_64_blocks = Blocks.from_fpatch(str_imm_64_header, fpatch)
    (b,
     bl,
     add,
     add_generic,
     ldr,
     adrp,
     str_,
     str_imm_64,
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
                             b,
                             bl,
                             add,
                             add_generic,
                             ldr,
                             adrp,
                             str_,
                             str_imm_64,
                             data_pointers,
                             code_pointers,
                             b_blocks,
                             bl_blocks,
                             add_blocks,
                             add_generic_blocks,
                             ldr_blocks,
                             adrp_blocks,
                             str_blocks,
                             str_imm_64_blocks,
                             data_pointers_blocks,
                             code_pointers_blocks)
    from_reader = FromReader(ffrom,
                             b,
                             bl,
                             add,
                             add_generic,
                             ldr,
                             adrp,
                             str_,
                             str_imm_64,
                             data_pointers,
                             code_pointers,
                             b_blocks,
                             bl_blocks,
                             add_blocks,
                             add_generic_blocks,
                             ldr_blocks,
                             adrp_blocks,
                             str_blocks,
                             str_imm_64_blocks,
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
    b_header = Blocks.unpack_header(fpatch)
    bl_header = Blocks.unpack_header(fpatch)
    add_header = Blocks.unpack_header(fpatch)
    add_generic_header = Blocks.unpack_header(fpatch)
    ldr_header = Blocks.unpack_header(fpatch)
    adrp_header = Blocks.unpack_header(fpatch)
    str_header = Blocks.unpack_header(fpatch)
    str_imm_64_header = Blocks.unpack_header(fpatch)

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
    b_blocks, b_blocks_size = load_blocks(b_header, fpatch)
    bl_blocks, bl_blocks_size = load_blocks(bl_header, fpatch)
    add_blocks, add_blocks_size = load_blocks(add_header, fpatch)
    add_generic_blocks, add_generic_blocks_size = load_blocks(add_generic_header,
                                                              fpatch)
    ldr_blocks, ldr_blocks_size = load_blocks(ldr_header, fpatch)
    adrp_blocks, adrp_blocks_size = load_blocks(adrp_header, fpatch)
    str_blocks, str_blocks_size = load_blocks(str_header, fpatch)
    str_imm_64_blocks, str_imm_64_blocks_size = load_blocks(str_imm_64_header,
                                                            fpatch)
    fout = StringIO()

    with redirect_stdout(fout):
        format_instruction('b', b_blocks, b_blocks_size, fsize)
        format_instruction('bl', bl_blocks, bl_blocks_size, fsize)
        format_instruction('add', add_blocks, add_blocks_size, fsize)
        format_instruction(
            'add (generic)', add_generic_blocks, add_generic_blocks_size, fsize)
        format_instruction('ldr', ldr_blocks, ldr_blocks_size, fsize)
        format_instruction('adrp', adrp_blocks, adrp_blocks_size, fsize)
        format_instruction('str', str_blocks, str_blocks_size, fsize)
        format_instruction(
            'str (imm 64)', str_imm_64_blocks, str_imm_64_blocks_size, fsize)
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
