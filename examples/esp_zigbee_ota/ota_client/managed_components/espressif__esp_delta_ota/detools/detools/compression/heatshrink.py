"""Heatshrink wrapper.

"""

import bitstruct

from heatshrink2.core import Writer
from heatshrink2.core import Reader
from heatshrink2.core import Encoder


def pack_header(window_sz2, lookahead_sz2):
    return bitstruct.pack('u4u4', window_sz2 - 4, lookahead_sz2 - 3)


def unpack_header(data):
    window_sz2, lookahead_sz2 = bitstruct.unpack('u4u4', data)

    return window_sz2 + 4, lookahead_sz2 + 3


class HeatshrinkCompressor(object):

    def __init__(self, window_sz2, lookahead_sz2):
        self._data = pack_header(window_sz2, lookahead_sz2)
        self._encoder = Encoder(Writer(window_sz2=window_sz2,
                                       lookahead_sz2=lookahead_sz2))

    def compress(self, data):
        compressed = self._encoder.fill(data)

        if self._data:
            compressed = self._data + compressed
            self._data = b''

        return compressed

    def flush(self):
        return self._data + self._encoder.finish()


class HeatshrinkDecompressor(object):

    def __init__(self, number_of_bytes):
        self._number_of_bytes_left = number_of_bytes
        self._data = b''
        self._encoder = None
        self.window_sz2 = None
        self.lookahead_sz2 = None

    def decompress(self, data, size):
        if self._encoder is None:
            if not data:
                return b''

            self.window_sz2, self.lookahead_sz2 = unpack_header(data[:1])
            self._encoder = Encoder(Reader(window_sz2=self.window_sz2,
                                           lookahead_sz2=self.lookahead_sz2))
            data = data[1:]
            self._number_of_bytes_left -= 1

        if self._number_of_bytes_left > 0:
            self._data += self._encoder.fill(data)
            self._number_of_bytes_left -= len(data)

        if self._number_of_bytes_left == 0:
            self._data += self._encoder.finish()
            self._number_of_bytes_left = -1

        decompressed = self._data[:size]
        self._data = self._data[size:]

        return decompressed

    @property
    def needs_input(self):
        return self._data == b'' and not self.eof

    @property
    def eof(self):
        return self._number_of_bytes_left == -1 and self._data == b''
