import unittest
from elftools.elf.elffile import ELFFile

from detools.data_format.utils import Blocks
from detools.data_format import elf


class DetoolsDataFormatTest(unittest.TestCase):

    def test_blocks(self):
        blocks = Blocks()

        self.assertEqual(
            repr(blocks),
            'Blocks(number_of_blocks=0, blocks=[])')

        blocks.append(0, 1, [2, 3, 4])

        self.assertEqual(
            repr(blocks),
            'Blocks(number_of_blocks=1, blocks=[Block(from_offset=0, '
            'to_address=1, number_of_values=3)])')

        self.assertEqual(blocks.to_bytes(),
                         (b'\x01\x00\x01\x03', b'\x02\x03\x04'))

    def test_from_elf_file(self):
        filename = 'tests/files/micropython/esp8266-20180511-v1.9.4.elf'

        with open(filename, 'rb') as fin:
            elffile = ELFFile(fin)
            (code_range, data_range) = elf.from_file(elffile)

        self.assertEqual(code_range.begin, 0x40209040)
        self.assertEqual(code_range.end, 0x4027b365)
        self.assertEqual(data_range.begin, 0x4027b368)
        self.assertEqual(data_range.end, 0x40293ab8)


if __name__ == '__main__':
    unittest.main()
