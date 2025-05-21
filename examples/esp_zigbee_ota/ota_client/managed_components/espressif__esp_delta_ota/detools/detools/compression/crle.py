"""Conditional Run Length Encoding (CRLE) compresses repeated bytes
with RLE, but leaves other data sequences as is.

It compresses diffs fairly well, but extras poorly. Not very useful in
general.

"""

import struct
from ..errors import Error


MINIMUM_REPEATED_SIZE = 6

SCATTERED = 0
REPEATED = 1


class CrleCompressor(object):

    def __init__(self):
        self._data = b''
        self._flushing = False
        self._number_of_compressed_bytes = 0

    def compress(self, data):
        """Compress `data` and return any compressed data.

        """

        self._data += data

        return self.compress_segment()

    def flush(self):
        """Compress and return remaining data.

        """

        if self._number_of_compressed_bytes == len(self._data) == 0:
            compressed = struct.pack('B', SCATTERED)
            compressed += pack_size(0)
        else:
            self._flushing = True
            compressed = []

            while True:
                chunk = self.compress_segment()

                if not chunk:
                    break

                compressed.append(chunk)

            compressed = b''.join(compressed)

        return compressed

    def find_repeated_segment(self):
        """Find the first repeated segment in the data and return its offset
        and length. Return ``(None, None)`` if no repeated segment was
        found.

        """

        for offset in range(len(self._data)):
            byte = self._data[offset]
            length = 0

            while ((offset + length < len(self._data))
                   and (byte == self._data[offset + length])):
                length += 1

            if length >= MINIMUM_REPEATED_SIZE:
                return offset, length

        return None, None

    def get_segment(self):
        """Get a segment of scattered or repeated data. Returns the segment
        kind and data. Returns ``(None, None)`` if no segment was
        found.

        """

        offset, length = self.find_repeated_segment()

        if offset is None:
            if self._flushing:
                kind = SCATTERED
                data = self._data
                self._data = b''
            else:
                kind = None
                data = None
        elif offset > 0:
            data = self._data[:offset]
            self._data = self._data[offset:]
            kind = SCATTERED
        elif offset + length < len(self._data) or self._flushing:
            data = self._data[:length]
            self._data = self._data[length:]
            kind = REPEATED
        else:
            kind = None
            data = None

        return kind, data

    def compress_segment(self):
        """Compress one segment and return it.

        """

        if len(self._data) == 0:
            return b''

        kind, data = self.get_segment()

        if kind is None:
            return b''

        compressed = struct.pack('B', kind)
        compressed += pack_size(len(data))

        if kind == SCATTERED:
            compressed += data
        else:
            compressed += data[:1]

        self._number_of_compressed_bytes += len(compressed)

        return compressed


class CrleDecompressor(object):

    def __init__(self, number_of_bytes):
        self._number_of_indata_bytes_left = number_of_bytes
        self._indata = b''
        self._outdata = b''
        self._number_of_scattered_bytes_left = 0

    def decompress(self, data, size):
        """Decompress up to size bytes.

        """

        if self.eof:
            raise Error('Already at end of stream.')

        if len(data) > self._number_of_indata_bytes_left:
            data = data[:self._number_of_indata_bytes_left]

        self._indata += data
        self._number_of_indata_bytes_left -= len(data)
        self._outdata += self.decompress_segments()
        data = self._outdata[:size]
        self._outdata = self._outdata[size:]

        return data

    @property
    def needs_input(self):
        return len(self._outdata) == 0 and not self.eof

    @property
    def eof(self):
        return (self._number_of_indata_bytes_left == 0
                and len(self._outdata) == 0
                and len(self._indata) == 0)

    def decompress_segments(self):
        segments = []

        try:
            while True:
                segments.append(self.decompress_segment())
        except IndexError:
            pass

        return b''.join(segments)

    def decompress_segment(self):
        """Try to decompress a segment. Raises IndexError if not enough data
        is available..

        """

        if self._number_of_scattered_bytes_left == 0:
            kind = self._indata[0]

            if kind == SCATTERED:
                length, offset = unpack_size(self._indata, 1)
                remaining = (offset + length - len(self._indata))

                if remaining > 0:
                    self._number_of_scattered_bytes_left = remaining
                    length -= remaining

                repetitions = 1
            elif kind == REPEATED:
                repetitions, offset = unpack_size(self._indata, 1)
                length = 1
            else:
                raise Error(
                    'Expected kind scattered(0) or repeated(1), but got {}.'.format(
                        kind))
        elif len(self._indata) > 0:
            length = min(len(self._indata), self._number_of_scattered_bytes_left)
            offset = 0
            repetitions = 1
            self._number_of_scattered_bytes_left -= length
        else:
            raise IndexError

        if len(self._indata) < offset + length:
            raise IndexError

        data = repetitions * self._indata[offset:offset + length]
        self._indata = self._indata[offset + length:]

        return data


def pack_size(value):
    if value >= 0x8000000000000000:
        raise Error('Size too big.')

    packed = bytearray()
    packed.append(0)
    packed[0] |= (0x80 | (value & 0x7f))
    value >>= 7

    while value > 0:
        packed.append(0x80 | (value & 0x7f))
        value >>= 7

    packed[-1] &= 0x7f

    return packed


def unpack_size(buf, position):
    byte = 0x80
    value = 0
    offset = 0

    while byte & 0x80:
        byte = buf[position]
        value |= ((byte & 0x7f) << offset)
        offset += 7
        position += 1

    return value, position
