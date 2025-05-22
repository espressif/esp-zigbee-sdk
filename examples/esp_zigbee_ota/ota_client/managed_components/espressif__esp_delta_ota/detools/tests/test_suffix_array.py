import unittest
import struct

import detools.sais


def read_file(filename):
    with open(filename, 'rb') as fin:
        return fin.read()


def suffix_array_list_to_bytearray(suffix_array):
    return bytearray().join([
        struct.pack('=i', value) for value in suffix_array
    ])


class DetoolsSuffixArrayTest(unittest.TestCase):

    def test_suffix_array(self):
        datas = [
            (
                b'',
                [0]
            ),
            (
                b'1',
                [1, 0]
            ),
            (
                b'1234',
                [4, 0, 1, 2, 3]
            ),
            (
                b'55555555',
                [8, 7, 6, 5, 4, 3, 2, 1, 0]
            ),
            (
                b'adska9kkkoaofeopkjvuuuuewflk-0920314923fg',
                [
                    41, 28, 32, 29, 34, 31, 37, 33, 38, 35,
                    30, 36,  5,  4,  0, 10,  1, 13, 23, 12,
                    39, 25, 40, 17, 27,  3, 16,  6,  7,  8,
                    26,  9, 11, 14, 15,  2, 22, 21, 20, 19,
                    18, 24
                ]
            )
        ]

        for data, expected in datas:
            expected = suffix_array_list_to_bytearray(expected)
            suffix_array = bytearray(len(expected))

            detools.suffix_array.sais(data, suffix_array)
            self.assertEqual(suffix_array, expected)

            detools.suffix_array.divsufsort(data, suffix_array)
            self.assertEqual(suffix_array, expected)


if __name__ == '__main__':
    unittest.main()
