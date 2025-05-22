from collections import defaultdict
from operator import itemgetter

from elftools.elf.sections import SymbolTableSection

from ..errors import Error


class AddressRange(object):

    def __init__(self, begin=0, end=0, section_index=None):
        self.begin = begin
        self.end = end
        self.section_index = section_index

    @property
    def size(self):
        return self.end - self.begin

    def __str__(self):
        return 'Range: 0x{:08x}-0x{:08x} ({}) ({})'.format(
            self.begin,
            self.end,
            self.size,
            self.section_index)


def find_data_and_code_addresses_per_section(elffile):
    """Returns data and code address ranges found in given ELF file by
    examining the symbols table.

    """

    # Find all function and object symbols.
    symbols_per_section = defaultdict(list)

    for section in elffile.iter_sections():
        if not isinstance(section, SymbolTableSection):
            continue

        if section['sh_entsize'] == 0:
            continue

        for symbol in section.iter_symbols():
            if symbol['st_info']['type'] not in ['STT_FUNC', 'STT_OBJECT']:
                continue

            if symbol['st_size'] == 0:
                continue

            section_index = find_section_index_for_symbol(elffile, symbol)
            symbols_per_section[section_index].append(symbol)

    # Find all consecutive function and object ranges per section.
    for symbols in symbols_per_section.values():
        symbols.sort(key=itemgetter('st_value'))

    func_ranges_per_section = defaultdict(list)
    obj_ranges_per_section = defaultdict(list)

    for section_index, symbols in symbols_per_section.items():
        symbol = symbols[0]
        block_type = symbol['st_info']['type']
        block_begin = symbol['st_value']
        block_end = symbol['st_size']

        for symbol in symbols:
            if symbol['st_info']['type'] != block_type:
                address_range = AddressRange(block_begin,
                                             block_end,
                                             section_index)

                if block_type == 'STT_FUNC':
                    func_ranges_per_section[section_index].append(address_range)
                else:
                    obj_ranges_per_section[section_index].append(address_range)

                block_type = symbol['st_info']['type']
                block_begin = symbol['st_value']

            block_end = symbol['st_value'] + symbol['st_size']

        address_range = AddressRange(block_begin,
                                     block_end,
                                     section_index)

        if block_type == 'STT_FUNC':
            func_ranges_per_section[section_index].append(address_range)
        else:
            obj_ranges_per_section[section_index].append(address_range)

    return func_ranges_per_section, obj_ranges_per_section


def find_section_index_for_symbol(elffile, symbol):
    address = symbol['st_value']

    for index, section in enumerate(elffile.iter_sections()):
        begin = section['sh_addr']
        size = section['sh_size']

        if begin <= address < begin + size:
            return index

    raise Error("Symbol '{}' not part of any section.".format(symbol.name))


def create_code_range(code_ranges_per_section):
    largest_range = AddressRange()

    for code_ranges in code_ranges_per_section.values():
        code_range = AddressRange(code_ranges[0].begin,
                                  code_ranges[-1].end,
                                  code_ranges[0].section_index)

        if code_range.size > largest_range.size:
            largest_range = code_range

    return largest_range


def create_data_range(data_ranges_per_section, code_range):
    largest_range = AddressRange()

    for data_ranges in data_ranges_per_section.values():
        for data_range in data_ranges:
            if data_range.begin < code_range.begin < data_range.end:
                left_data_range = AddressRange(data_range.begin,
                                               code_range.begin,
                                               data_range.section_index)
            else:
                left_data_range = None

            if data_range.begin < code_range.end < data_range.end:
                right_data_range = AddressRange(code_range.end,
                                                data_range.end,
                                                data_range.section_index)
            else:
                right_data_range = None

            if left_data_range is not None and right_data_range is not None:
                if left_data_range.size > right_data_range.size:
                    data_range = left_data_range
                else:
                    data_range = right_data_range
            elif left_data_range is not None:
                data_range = left_data_range
            elif right_data_range is not None:
                data_range = right_data_range

            if data_range.size > largest_range.size:
                largest_range = data_range

    return largest_range


def from_file(elffile):
    """Returns data format parameters by examining given ELF file.

    """

    (code_ranges_per_section,
     data_ranges_per_section) = find_data_and_code_addresses_per_section(
         elffile)
    code_range = create_code_range(code_ranges_per_section)
    data_range = create_data_range(data_ranges_per_section, code_range)

    return (code_range, data_range)
