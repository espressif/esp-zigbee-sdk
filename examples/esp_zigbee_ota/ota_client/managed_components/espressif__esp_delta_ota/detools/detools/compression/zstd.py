"""Zstandard wrapper.

"""

import os
from io import BytesIO
import zstandard
from ..errors import Error


class ZstdCompressor(object):

    def __init__(self):
        self._data = []

    def compress(self, data):
        self._data.append(data)

        return b''

    def flush(self):
        return zstandard.ZstdCompressor(level=22).compress(b''.join(self._data))


class ZstdDecompressor(object):

    def __init__(self, number_of_bytes):
        self._number_of_bytes_left = number_of_bytes
        self._output_offset = 0
        self._fout = BytesIO()
        decompressor = zstandard.ZstdDecompressor()
        self._decompressor = decompressor.stream_writer(self._fout)

    def decompress(self, data, size):
        if self.eof:
            raise Error('Already at end of stream.')

        self._number_of_bytes_left -= len(data)
        self._decompressor.write(data)

        self._fout.seek(self._output_offset, os.SEEK_SET)
        data = self._fout.read(size)
        self._output_offset += len(data)
        self._fout.seek(0, os.SEEK_END)

        return data

    @property
    def needs_input(self):
        return (self._output_offset == self._fout.tell()) and not self.eof

    @property
    def eof(self):
        return (self._number_of_bytes_left == 0
                and self._output_offset == self._fout.tell())
