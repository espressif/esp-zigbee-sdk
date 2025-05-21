from collections import defaultdict
from operator import itemgetter

from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection

from ..errors import Error
from ..common import DATA_FORMAT_AARCH64
from ..common import DATA_FORMAT_ARM_CORTEX_M4
from ..common import DATA_FORMAT_XTENSA_LX106
from ..common import format_bad_data_format
from ..common import format_bad_data_format_number
from . import aarch64
from . import arm_cortex_m4
from . import xtensa_lx106


def encode(ffrom, fto, data_format, data_segment):
    """Returns the new from-data and to-data, along with a patch that can
    be used to convert the new from-data to the original to-data later
    (by the diff and from readers).

    """

    if data_format == 'aarch64':
        return aarch64.encode(ffrom, fto, data_segment)
    elif data_format == 'arm-cortex-m4':
        return arm_cortex_m4.encode(ffrom, fto, data_segment)
    elif data_format == 'xtensa-lx106':
        return xtensa_lx106.encode(ffrom, fto, data_segment)
    else:
        raise Error(format_bad_data_format(data_format))


def create_readers(data_format, ffrom, patch, to_size):
    """Returns diff and from readers, used when applying a patch.

    """

    if data_format == DATA_FORMAT_AARCH64:
        return aarch64.create_readers(ffrom, patch, to_size)
    elif data_format == DATA_FORMAT_ARM_CORTEX_M4:
        return arm_cortex_m4.create_readers(ffrom, patch, to_size)
    elif data_format == DATA_FORMAT_XTENSA_LX106:
        return xtensa_lx106.create_readers(ffrom, patch, to_size)
    else:
        raise Error(format_bad_data_format_number(data_format))


def info(data_format, patch, fsize):
    """Returns an info string.

    """

    if data_format == DATA_FORMAT_AARCH64:
        return aarch64.info(patch, fsize)
    elif data_format == DATA_FORMAT_ARM_CORTEX_M4:
        return arm_cortex_m4.info(patch, fsize)
    elif data_format == DATA_FORMAT_XTENSA_LX106:
        return xtensa_lx106.info(patch, fsize)
    else:
        raise Error(format_bad_data_format_number(data_format))
