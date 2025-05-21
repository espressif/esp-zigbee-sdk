"""LZ4 wrapper.

"""

import os
from io import BytesIO
import lz4.frame
from ..errors import Error


class Lz4Compressor(object):

    def __init__(self):
        self._compressor = lz4.frame.LZ4FrameCompressor(
            compression_level=lz4.frame.COMPRESSIONLEVEL_MAX)
        self._header = self._compressor.begin()

    def compress(self, data):
        compressed = self._compressor.compress(data)

        if self._header is not None:
            compressed = (self._header + compressed)
            self._header = None

        return compressed

    def flush(self):
        return self._compressor.flush()


class Lz4Decompressor(lz4.frame.LZ4FrameDecompressor):

    pass
