import unittest

import detools
from detools.create import NoneCompressor
from detools.apply import NoneDecompressor


class DetoolsNoneTest(unittest.TestCase):

    def test_compress(self):
        datas = [
            (                       [b''], b''),
            (                      [b'A'], b'A'),
            (         [b'ABBCC', b'CBBA'], b'ABBCCCBBA'),
            (     [126 * b'A', b'', b'A'], 127 * b'A')
        ]

        for chunks, compressed in datas:
            compressor = NoneCompressor()
            data = b''

            for chunk in chunks:
                data += compressor.compress(chunk)

            data += compressor.flush()

            self.assertEqual(data, compressed)

    def test_decompress_no_data(self):
        compressed = b''

        decompressor = NoneDecompressor(len(compressed))

        self.assertEqual(decompressor.needs_input, False)
        self.assertEqual(decompressor.eof, True)

    def test_decompress(self):
        datas = [
            (                   [b'A'], b'A'),
            (           [b'ABBCCCBBA'], b'ABBCCCBBA'),
            (             [127 * b'A'], 127 * b'A')
        ]

        for chunks, decompressed in datas:
            decompressor = NoneDecompressor(sum([len(c) for c in chunks]))

            for chunk in chunks:
                self.assertEqual(decompressor.needs_input, True)
                self.assertEqual(decompressor.eof, False)
                decompressor.decompress(chunk, 0)

            self.assertEqual(decompressor.needs_input, False)

            data = b''

            while not decompressor.eof:
                data += decompressor.decompress(b'', 1)

            self.assertEqual(data, decompressed)

    def test_decompress_at_eof(self):
        decompressor = NoneDecompressor(1)

        self.assertEqual(decompressor.decompress(b'5', 1), b'5')
        self.assertEqual(decompressor.eof, True)

        with self.assertRaises(detools.Error) as cm:
            decompressor.decompress(b'6', 1)

        self.assertEqual(str(cm.exception), 'Already at end of stream.')

        with self.assertRaises(detools.Error) as cm:
            decompressor.decompress(b'', 1)

        self.assertEqual(str(cm.exception), 'Already at end of stream.')

    def test_decompress_ignore_extra_data(self):
        compressed = b'A'
        decompressor = NoneDecompressor(len(compressed))

        self.assertEqual(decompressor.decompress(compressed + b'B', 1), b'A')
        self.assertEqual(decompressor.eof, True)


if __name__ == '__main__':
    unittest.main()
