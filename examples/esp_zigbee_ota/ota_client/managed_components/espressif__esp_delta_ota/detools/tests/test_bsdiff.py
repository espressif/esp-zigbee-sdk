import unittest
import struct

import detools.bsdiff


def read_file(filename):
    with open(filename, 'rb') as fin:
        return fin.read()


def suffix_array_list_to_bytearray(suffix_array):
    return bytearray().join([
        struct.pack('=i', value) for value in suffix_array
    ])


class DetoolsBsdiffTest(unittest.TestCase):

    def test_bsdiff(self):
        datas = [
            (
                [0],
                b'',
                b'',
                []
            ),
            (
                [1, 0],
                b'1',
                b'12',
                [
                    b'\x01', b'\x00', b'\x01', b'2', b'\x41'
                ]
            ),
            (
                [4, 0, 1, 2, 3],
                b'1234',
                b'29990812398409812',
                [
                    b'\x00', b'', b'\x11', b'29990812398409812', b'\x01'
                ]
            ),
            (
                [
                    41, 28, 32, 29, 34, 31, 37, 33, 38, 35,
                    30, 36,  5,  4,  0, 10,  1, 13, 23, 12,
                    39, 25, 40, 17, 27,  3, 16,  6,  7,  8,
                    26,  9, 11, 14, 15,  2, 22, 21, 20, 19,
                    18, 24
                ],
                b'adska9kkkoaofeopkjvuuuuewflk-0920314923fg',
                b'adska9kkkoaofeopkjvuuuuewflk-0920314923fg1',
                [
                    b'\x29',
                    b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
                    b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
                    b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00',
                    b'\x01',
                    b'1',
                    b'\x47'
                ]
            )
        ]

        for suffix_array, from_data, to_data, chunks in datas:
            suffix_array = suffix_array_list_to_bytearray(suffix_array)
            self.assertEqual(
                detools.bsdiff.create_patch(suffix_array,
                                            from_data,
                                            to_data,
                                            bytearray(4 * (len(from_data) + 1))),
                chunks)


if __name__ == '__main__':
    unittest.main()
