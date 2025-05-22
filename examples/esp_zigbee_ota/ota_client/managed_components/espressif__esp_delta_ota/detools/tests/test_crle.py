import unittest

import detools
from detools.create import CrleCompressor
from detools.apply import CrleDecompressor


class DetoolsCrleTest(unittest.TestCase):

    def test_compress(self):
        datas = [
            (                       [b''], b'\x00\x00'),
            (                      [b'A'], b'\x00\x01A'),
            (                  [5 * b'A'], b'\x00\x05AAAAA'),
            (                  [6 * b'A'], b'\x01\x06A'),
            (         [b'ABBCC', b'CBBA'], b'\x00\x09ABBCCCBBA'),
            (     [126 * b'A', b'', b'A'], b'\x01\x7fA'),
            (                [128 * b'A'], b'\x01\x80\x01A'),
            (               [1000 * b'A'], b'\x01\xe8\x07A'),
            (        [69999 * b'A', b'A'], b'\x01\xf0\xa2\x04A'),
            ([10 * b'A', b'BC', 8 * b'A'], b'\x01\x0aA\x00\x02BC\x01\x08A'),
            (      [10 * b'A' + 8 * b'B'], b'\x01\x0aA\x01\x08B')
        ]

        for chunks, compressed in datas:
            compressor = CrleCompressor()
            data = b''

            for chunk in chunks:
                data += compressor.compress(chunk)

            data += compressor.flush()

            self.assertEqual(data, compressed)

    def test_decompress_no_data(self):
        compressed = b'\x00\x00'

        decompressor = CrleDecompressor(len(compressed))

        self.assertEqual(decompressor.needs_input, True)
        self.assertEqual(decompressor.decompress(compressed, 1), b'')
        self.assertEqual(decompressor.eof, True)

    def test_decompress(self):
        datas = [
            (                   [b'\x00\x01A'], b'A'),
            (             [b'\x00\x07AAAAAAA'], 7 * b'A'),
            (                   [b'\x01\x08A'], 8 * b'A'),
            (           [b'\x00\x09ABBCCCBBA'], b'ABBCCCBBA'),
            (              [b'\x01\x7f', b'A'], 127 * b'A'),
            (               [b'\x01\x80\x01A'], 128 * b'A'),
            (               [b'\x01\xe8\x07A'], 1000 * b'A'),
            (      [b'\x01\xf0', b'\xa2\x04A'], 70000 * b'A'),
            ([b'\x01\x0aA\x00\x02BC\x01\x08A'], 10 * b'A' + b'BC' + 8 * b'A'),
            (          [b'\x01\x0aA\x01\x08B'], 10 * b'A' + 8 * b'B')
        ]

        for chunks, decompressed in datas:
            decompressor = CrleDecompressor(sum([len(c) for c in chunks]))

            for chunk in chunks:
                self.assertEqual(decompressor.needs_input, True)
                self.assertEqual(decompressor.eof, False)
                decompressor.decompress(chunk, 0)

            self.assertEqual(decompressor.needs_input, False)

            data = b''

            while not decompressor.eof:
                data += decompressor.decompress(b'', 1)

            self.assertEqual(data, decompressed)

    def test_decompress_bad_kind(self):
        decompressor = CrleDecompressor(3)

        with self.assertRaises(detools.Error) as cm:
            decompressor.decompress(b'\x02\x01A', 1)

        self.assertEqual(
            str(cm.exception),
            'Expected kind scattered(0) or repeated(1), but got 2.')

    def test_decompress_at_eof(self):
        compressed = b'\x00\x01A'
        decompressor = CrleDecompressor(len(compressed))

        self.assertEqual(decompressor.decompress(compressed, 1), b'A')
        self.assertEqual(decompressor.eof, True)

        with self.assertRaises(detools.Error) as cm:
            decompressor.decompress(b'6', 1)

        self.assertEqual(str(cm.exception), 'Already at end of stream.')

        with self.assertRaises(detools.Error) as cm:
            decompressor.decompress(b'', 1)

        self.assertEqual(str(cm.exception), 'Already at end of stream.')

    def test_decompress_ignore_extra_data(self):
        compressed = b'\x00\x01A'
        decompressor = CrleDecompressor(len(compressed))

        self.assertEqual(decompressor.decompress(compressed + b'B', 1), b'A')
        self.assertEqual(decompressor.eof, True)


if __name__ == '__main__':
    unittest.main()
