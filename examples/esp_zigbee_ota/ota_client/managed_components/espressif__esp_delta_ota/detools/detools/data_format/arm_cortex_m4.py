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

    _CF_BW = bitstruct.compile('u5u1u4u6u2u1u1u1u11')
    _CF_BL = bitstruct.compile('u5u1u10u2u1u1u1u11')

    def __init__(self,
                 ffrom,
                 to_size,
                 bw,
                 bl,
                 ldr,
                 ldr_w,
                 data_pointers,
                 code_pointers,
                 bw_blocks,
                 bl_blocks,
                 ldr_blocks,
                 ldr_w_blocks,
                 data_pointers_blocks,
                 code_pointers_blocks):
        super().__init__(ffrom, to_size)
        self._write_s32_values_to_to(ldr_blocks, ldr)
        self._write_s32_values_to_to(ldr_w_blocks, ldr_w)
        self._write_bl_values_to_to(bl_blocks, bl)
        self._write_bw_values_to_to(bw_blocks, bw)

        if data_pointers_blocks is not None:
            self._write_s32_values_to_to(data_pointers_blocks, data_pointers)

        if code_pointers_blocks is not None:
            self._write_s32_values_to_to(code_pointers_blocks, code_pointers)

        self._fdiff.seek(0)

    def _write_bw_values_to_to(self, bw_blocks, bw):
        self._write_values_to_to_with_callback(bw_blocks, bw, self._pack_bw)

    def _write_bl_values_to_to(self, bl_blocks, bl):
        self._write_values_to_to_with_callback(bl_blocks, bl, self._pack_bl)

    def _pack_bw(self, value):
        if value < 0:
            value += (1 << 25)

        t = (value & 0x1)
        cond = ((value >> 1) & 0xf)
        imm32 = (value >> 5)
        s = (imm32 >> 19)
        j2 = ((imm32 >> 18) & 0x1)
        j1 = ((imm32 >> 17) & 0x1)
        imm6 = ((imm32 >> 11) & 0x3f)
        imm11 = (imm32 & 0x7ff)
        value = self._CF_BW.pack(0b11110, s, cond, imm6, 0b10, j1, t, j2, imm11)

        return bitstruct.byteswap('22', value)

    def _pack_bl(self, imm32):
        if imm32 < 0:
            imm32 += (1 << 24)

        s = (imm32 >> 23)
        i1 = ((imm32 >> 22) & 0x1)
        i2 = ((imm32 >> 21) & 0x1)
        j1 = -((i1 ^ s) - 1)
        j2 = -((i2 ^ s) - 1)
        imm10 = ((imm32 >> 11) & 0x3ff)
        imm11 = (imm32 & 0x7ff)
        value = self._CF_BL.pack(0b11110, s, imm10, 0b11, j1, 0b1, j2, imm11)

        return bitstruct.byteswap('22', value)


class FromReader(UtilsFromReader):

    def __init__(self,
                 ffrom,
                 bw,
                 bl,
                 ldr,
                 ldr_w,
                 data_pointers,
                 code_pointers,
                 bw_blocks,
                 bl_blocks,
                 ldr_blocks,
                 ldr_w_blocks,
                 data_pointers_blocks,
                 code_pointers_blocks):
        super().__init__(ffrom)
        self._write_zeros_to_from(bw_blocks, bw)
        self._write_zeros_to_from(bl_blocks, bl)
        self._write_zeros_to_from(ldr_blocks, ldr)
        self._write_zeros_to_from(ldr_w_blocks, ldr_w)

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


def unpack_bw(upper_16, lower_16):
    s = ((upper_16 & 0x400) >> 10)
    cond = ((upper_16 & 0x3c0) >> 6)
    imm6 = (upper_16 & 0x3f)
    imm11 = (lower_16 & 0x7ff)
    j1 = ((lower_16 & 0x2000) >> 13)
    t = ((lower_16 & 0x1000) >> 12)
    j2 = ((lower_16 & 0x800) >> 11)
    value = (s << 24)
    value |= (j2 << 23)
    value |= (j1 << 22)
    value |= (imm6 << 16)
    value |= (imm11 << 5)
    value |= (cond << 1)
    value |= t

    if s == 1:
        value -= (1 << 25)

    return value


def unpack_bl(upper_16, lower_16):
    s = ((upper_16 & 0x400) >> 10)
    imm10 = (upper_16 & 0x3ff)
    imm11 = (lower_16 & 0x7ff)
    j1 = ((lower_16 & 0x2000) >> 13)
    j2 = ((lower_16 & 0x800) >> 11)
    i1 = -((j1 ^ s) - 1)
    i2 = -((j2 ^ s) - 1)
    value = (s << 23)
    value |= (i1 << 22)
    value |= (i2 << 21)
    value |= (imm10 << 11)
    value |= imm11

    if s == 1:
        value -= (1 << 24)

    return value


def disassemble_bw_bl(reader, address, bw, bl, upper_16):
    data = reader.read(2)

    if len(data) != 2:
        LOGGER.debug('Failed to read 2 bw/bl bytes at address 0x%x.',
                     address + 2)
        return

    lower_16 = struct.unpack('<H', data)[0]

    if (lower_16 & 0xd000) == 0xd000:
        bl[address] = unpack_bl(upper_16, lower_16)
    elif (lower_16 & 0xc000) == 0x8000:
        bw[address] = unpack_bw(upper_16, lower_16)


def disassemble_ldr_common(reader, address, ldr, imm):
    if (address % 4) == 2:
        address -= 2

    address += imm
    position = reader.tell()
    reader.seek(address)
    data = reader.read(4)
    reader.seek(position)

    if len(data) != 4:
        LOGGER.debug('Failed to read 4 ldr common bytes at address 0x%x.',
                     address)
        return

    ldr[address] = struct.unpack('<i', data)[0]


def disassemble_ldr(reader, address, ldr, upper_16):
    imm8 = 4 * (upper_16 & 0xff) + 4
    disassemble_ldr_common(reader, address, ldr, imm8)


def disassemble_ldr_w(reader, address, ldr_w):
    data = reader.read(2)

    if len(data) != 2:
        LOGGER.debug('Failed to read 2 ldr.w bytes at address 0x%x.',
                     address + 2)
        return

    lower_16 = struct.unpack('<H', data)[0]
    imm12 = (lower_16 & 0xfff) + 4
    disassemble_ldr_common(reader, address, ldr_w, imm12)


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
    bw = {}
    bl = {}
    ldr = {}
    ldr_w = {}
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
        elif address in ldr or address in ldr_w:
            if len(reader.read(4)) != 4:
                LOGGER.debug('Failed to read 4 ldr/ldr.w bytes at address 0x%x.',
                             address)
        else:
            data = reader.read(2)

            if len(data) != 2:
                LOGGER.debug('Failed to read 2 upper bytes at address 0x%x.',
                             address)
                continue

            upper_16 = struct.unpack('<H', data)[0]

            if (upper_16 & 0xf800) == 0xf000:
                disassemble_bw_bl(reader, address, bw, bl, upper_16)
            elif (upper_16 & 0xf800) == 0x4800:
                disassemble_ldr(reader, address, ldr, upper_16)
            elif (upper_16 & 0xffff) == 0xf8df:
                disassemble_ldr_w(reader, address, ldr_w)
            elif (upper_16 & 0xfff0) in [0xfbb0, 0xfb90, 0xf8d0, 0xf850]:
                reader.read(2)
            elif (upper_16 & 0xffe0) == 0xfa00:
                reader.read(2)
            elif (upper_16 & 0xffc0) == 0xe900:
                reader.read(2)

    return bw, bl, ldr, ldr_w, data_pointers, code_pointers


def encode(ffrom, fto, data_segment):
    ffrom = BytesIO(file_read(ffrom))
    fto = BytesIO(file_read(fto))
    (from_bw,
     from_bl,
     from_ldr,
     from_ldr_w,
     from_data_pointers,
     from_code_pointers) = disassemble(ffrom,
                                       data_segment.from_data_offset_begin,
                                       data_segment.from_data_offset_end,
                                       data_segment.from_data_begin,
                                       data_segment.from_data_end,
                                       data_segment.from_code_begin,
                                       data_segment.from_code_end)
    (to_bw,
     to_bl,
     to_ldr,
     to_ldr_w,
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
    bw = create_patch_block(ffrom, fto, from_bw, to_bw)
    bl = create_patch_block(ffrom, fto, from_bl, to_bl)
    ldr = create_patch_block(ffrom, fto, from_ldr, to_ldr)
    ldr_w = create_patch_block(ffrom, fto, from_ldr_w, to_ldr_w)
    headers, datas = zip(data_pointers, code_pointers, bw, bl, ldr, ldr_w)
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
    bw_header = Blocks.unpack_header(fpatch)
    bl_header = Blocks.unpack_header(fpatch)
    ldr_header = Blocks.unpack_header(fpatch)
    ldr_w_header = Blocks.unpack_header(fpatch)

    # Blocks.
    data_pointers_blocks, code_pointers_blocks = unpack_pointers_blocks(
        fpatch,
        data_pointers_blocks_present,
        code_pointers_blocks_present,
        data_pointers_header,
        code_pointers_header)
    bw_blocks = Blocks.from_fpatch(bw_header, fpatch)
    bl_blocks = Blocks.from_fpatch(bl_header, fpatch)
    ldr_blocks = Blocks.from_fpatch(ldr_header, fpatch)
    ldr_w_blocks = Blocks.from_fpatch(ldr_w_header, fpatch)
    (bw,
     bl,
     ldr,
     ldr_w,
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
                             bw,
                             bl,
                             ldr,
                             ldr_w,
                             data_pointers,
                             code_pointers,
                             bw_blocks,
                             bl_blocks,
                             ldr_blocks,
                             ldr_w_blocks,
                             data_pointers_blocks,
                             code_pointers_blocks)
    from_reader = FromReader(ffrom,
                             bw,
                             bl,
                             ldr,
                             ldr_w,
                             data_pointers,
                             code_pointers,
                             bw_blocks,
                             bl_blocks,
                             ldr_blocks,
                             ldr_w_blocks,
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
    bw_header = Blocks.unpack_header(fpatch)
    bl_header = Blocks.unpack_header(fpatch)
    ldr_header = Blocks.unpack_header(fpatch)
    ldr_w_header = Blocks.unpack_header(fpatch)

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
    bw_blocks, bw_blocks_size = load_blocks(bw_header, fpatch)
    bl_blocks, bl_blocks_size = load_blocks(bl_header, fpatch)
    ldr_blocks, ldr_blocks_size = load_blocks(ldr_header, fpatch)
    ldr_w_blocks, ldr_w_blocks_size = load_blocks(ldr_w_header, fpatch)
    fout = StringIO()

    with redirect_stdout(fout):
        format_instruction('b.w', bw_blocks, bw_blocks_size, fsize)
        format_instruction('bl', bl_blocks, bl_blocks_size, fsize)
        format_instruction('ldr', ldr_blocks, ldr_blocks_size, fsize)
        format_instruction('ldr.w', ldr_w_blocks, ldr_w_blocks_size, fsize)
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
