#
# Based on the implementation in bsdiff.c.
#
# Copyright 2003-2005 Colin Percival
# Copyright (c) 2019, Erik Moqvist
# All rights reserved
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted providing that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

def matchlen(from_data, to_data):
    length = min(len(from_data), len(to_data))

    for i in range(length):
        if from_data[i] != to_data[i]:
            return i

    return length


def memcmp(b1, b2):
    for a, b in zip(b1, b2):
        if a > b:
            return 1
        elif a < b:
            return -1

    return 0


def search(suffix_array, from_data, to_data, st, en):
    if en - st < 2:
        x = matchlen(from_data[suffix_array[st]:], to_data)
        y = matchlen(from_data[suffix_array[en]:], to_data)

        if x > y:
            return x, suffix_array[st]
        else:
            return y, suffix_array[en]

    x = (st + (en - st) // 2)
    length = min(len(from_data) - suffix_array[x], len(to_data))

    if memcmp(from_data[suffix_array[x]:suffix_array[x] + length], to_data[:length]) < 0:
        return search(suffix_array, from_data, to_data, x, en)
    else:
        return search(suffix_array, from_data, to_data, st, x)


def pack_size(value):
    packed = bytearray()

    if value == 0:
        packed.append(0)
    elif value < 0x8000000000000000:
        if value > 0:
            packed.append(0)
        else:
            packed.append(0x40)
            value *= -1

        packed[0] |= (0x80 | (value & 0x3f))
        value >>= 6

        while value > 0:
            packed.append(0x80 | (value & 0x7f))
            value >>= 7
    else:
        raise Exception('Size too big.')

    packed[-1] &= 0x7f

    return packed


def append_buffer(chunks, buf):
    chunks.append(pack_size(len(buf)))
    chunks.append(buf)


def create_patch(suffix_array, from_data, to_data):
    """Return chunks of data.

    """

    scan = 0
    length = 0
    last_scan = 0
    last_pos = 0
    last_offset = 0
    pos = 0
    chunks = []

    while scan < len(to_data):
        from_score = 0
        scsc = scan
        scan += length

        while scan < len(to_data):
            length, pos = search(suffix_array,
                                 from_data,
                                 to_data[scan:],
                                 0,
                                 len(from_data))

            while scsc < scan + length:
                if ((scsc + last_offset < len(from_data))
                    and (from_data[scsc + last_offset] == to_data[scsc])):
                    from_score += 1

                scsc += 1

            if ((length == from_score) and (length != 0)) or (length > from_score + 8):
                break

            if ((scan + last_offset < len(from_data))
                and (from_data[scan + last_offset] == to_data[scan])):
                from_score -= 1

            scan += 1

        if (length != from_score) or (scan == len(to_data)):
            s = 0
            sf = 0
            lenf = 0
            i = 0

            while (last_scan + i < scan) and (last_pos + i < len(from_data)):
                if from_data[last_pos + i] == to_data[last_scan + i]:
                    s += 1

                i += 1

                if s * 2 - i > sf * 2 - lenf:
                    sf = s
                    lenf = i

            lenb = 0

            if scan < len(to_data):
                s = 0
                sb = 0
                i = 1

                while (scan >= last_scan + i) and (pos >= i):
                    if from_data[pos - i] == to_data[scan - i]:
                        s += 1

                    if s * 2 - i > sb * 2 - lenb:
                        sb = s
                        lenb = i

                    i += 1

            if last_scan + lenf > scan - lenb:
                overlap = (last_scan + lenf) - (scan - lenb)
                s = 0
                ss = 0
                lens = 0

                for i in range(overlap):
                    if (to_data[last_scan + lenf - overlap + i]
                        == from_data[last_pos + lenf - overlap + i]):
                        s += 1

                    if to_data[scan - lenb + i] == from_data[pos - lenb + i]:
                        s -= 1

                    if s > ss:
                        ss = s
                        lens = (i + 1)

                lenf += (lens - overlap)
                lenb -= lens

            db = bytearray(
                to_data[last_scan + i] - from_data[last_pos + i]
                for i in range(lenf)
            )

            eb = bytearray(
                to_data[last_scan + lenf + i]
                for i in range((scan - lenb) - (last_scan + lenf))
            )


            # Diff, extra and adjustment.
            append_buffer(chunks, db)
            append_buffer(chunks, eb)
            chunks.append(pack_size((pos - lenb) - (last_pos + lenf)))

            last_scan = (scan - lenb)
            last_pos = (pos - lenb)
            last_offset = (pos - scan)

    return chunks
