import logging
import unittest
from io import BytesIO

import detools
from detools.common import pack_size
from detools.common import unpack_size_bytes


class DetoolsTest(unittest.TestCase):

    def assert_create_patch(self,
                            from_filename,
                            to_filename,
                            patch_filename,
                            **kwargs):
        fpatch = BytesIO()

        with open(from_filename, 'rb') as ffrom:
            with open(to_filename, 'rb') as fto:
                detools.create_patch(ffrom, fto, fpatch, **kwargs)

        actual = fpatch.getvalue()
        # open(patch_filename, 'wb').write(actual)

        with open(patch_filename, 'rb') as fpatch:
            expected = fpatch.read()

        self.assertEqual(actual, expected)

    def assert_apply_patch(self,
                           from_filename,
                           to_filename,
                           patch_filename,
                           **kwargs):
        patch_type = kwargs.get('patch_type', 'sequential')

        if patch_type in ['sequential', 'hdiffpatch']:
            fto = BytesIO()

            with open(from_filename, 'rb') as ffrom:
                with open(patch_filename, 'rb') as fpatch:
                    to_size = detools.apply_patch(ffrom, fpatch, fto)

            actual = fto.getvalue()
        elif patch_type == 'in-place':
            memory_size = kwargs['memory_size']

            with open(from_filename, 'rb') as ffrom:
                data = ffrom.read()

            data += (memory_size - len(data)) * b'\xff'
            fmem = BytesIO(data)

            with open(patch_filename, 'rb') as fpatch:
                to_size = detools.apply_patch_in_place(fmem, fpatch)

            actual = fmem.getvalue()[:to_size]
        elif patch_type == 'bsdiff':
            fto = BytesIO()

            with open(from_filename, 'rb') as ffrom:
                with open(patch_filename, 'rb') as fpatch:
                    to_size = detools.apply_patch_bsdiff(ffrom, fpatch, fto)

            actual = fto.getvalue()
        else:
            raise Exception(patch_type)

        with open(to_filename, 'rb') as fto:
            expected = fto.read()

        # open('actual-to.bin', 'wb').write(actual)

        self.assertEqual(to_size, len(expected))
        self.assertEqual(len(actual), len(expected))
        self.assertEqual(actual, expected)

    def assert_create_and_apply_patch(self,
                                      from_filename,
                                      to_filename,
                                      patch_filename,
                                      **kwargs):
        self.assert_create_patch(from_filename,
                                 to_filename,
                                 patch_filename,
                                 **kwargs)
        self.assert_apply_patch(from_filename,
                                to_filename,
                                patch_filename,
                                **kwargs)

    def test_create_and_apply_patch_foo(self):
        self.assert_create_and_apply_patch('tests/files/foo/old',
                                           'tests/files/foo/new',
                                           'tests/files/foo/patch')

    def test_create_and_apply_patch_foo_backwards(self):
        self.assert_create_and_apply_patch('tests/files/foo/new',
                                           'tests/files/foo/old',
                                           'tests/files/foo/backwards.patch')

    def test_create_and_apply_patch_micropython(self):
        self.assert_create_and_apply_patch(
            'tests/files/micropython/esp8266-20180511-v1.9.4.bin',
            'tests/files/micropython/esp8266-20190125-v1.10.bin',
            'tests/files/micropython/esp8266-20180511-v1.9.4--20190125-v1.10.patch')

    def test_create_and_apply_patch_programmer(self):
        self.assert_create_and_apply_patch(
            'tests/files/programmer/0.8.0.bin',
            'tests/files/programmer/0.9.0.bin',
            'tests/files/programmer/0.8.0--0.9.0.patch')

    def test_create_and_apply_patch_programmer_arm_cortex_m4(self):
        self.assert_create_and_apply_patch(
            'tests/files/programmer/0.8.0.bin',
            'tests/files/programmer/0.9.0.bin',
            'tests/files/programmer/0.8.0--0.9.0-arm-cortex-m4.patch',
            data_format='arm-cortex-m4')

    def test_create_and_apply_patch_pybv11_v_1_10(self):
        self.assert_create_and_apply_patch(
            'tests/files/pybv11/v1.10/firmware1.bin',
            'tests/files/pybv11/1f5d945af-dirty/firmware1.bin',
            'tests/files/pybv11/v1.10--1f5d945af-dirty.patch')

    def test_create_and_apply_patch_pybv11_v_1_10_arm_cortex_m4(self):
        self.assert_create_and_apply_patch(
            'tests/files/pybv11/v1.10/firmware1.bin',
            'tests/files/pybv11/1f5d945af-dirty/firmware1.bin',
            'tests/files/pybv11/v1.10--1f5d945af-dirty-arm-cortex-m4.patch',
            data_format='arm-cortex-m4')

    def test_create_and_apply_patch_pybv11_1f5d945af(self):
        self.assert_create_and_apply_patch(
            'tests/files/pybv11/1f5d945af/firmware1.bin',
            'tests/files/pybv11/1f5d945af-dirty/firmware1.bin',
            'tests/files/pybv11/1f5d945af--1f5d945af-dirty.patch')

    def test_create_and_apply_patch_pybv11_1f5d945af_arm_cortex_m4(self):
        self.assert_create_and_apply_patch(
            'tests/files/pybv11/1f5d945af/firmware1.bin',
            'tests/files/pybv11/1f5d945af-dirty/firmware1.bin',
            'tests/files/pybv11/1f5d945af--1f5d945af-dirty-arm-cortex-m4.patch',
            data_format='arm-cortex-m4')

    def test_create_and_apply_patch_pybv11_data_and_code_sections(self):
        self.assert_create_and_apply_patch(
            'tests/files/pybv11/1f5d945af/firmware1.bin',
            'tests/files/pybv11/1f5d945af-dirty/firmware1.bin',
            'tests/files/pybv11/1f5d945af--'
            '1f5d945af-dirty-arm-cortex-m4-data-sections.patch',
            data_format='arm-cortex-m4',
            from_data_offset_begin=0x36f7c,
            from_data_offset_end=0x4e1f0,
            from_code_begin=0x8020000,
            from_code_end=0x08056deb,
            from_data_begin=0x8056f7c,
            from_data_end=0x806e1f0,
            to_data_offset_begin=0x36f54,
            to_data_offset_end=0x4e1d4,
            to_code_begin=0x8020000,
            to_code_end=0x08056dc3,
            to_data_begin=0x8056f54,
            to_data_end=0x806e1d4)

    def test_create_and_apply_patch_shell(self):
        self.assert_create_and_apply_patch('tests/files/shell/old',
                                           'tests/files/shell/new',
                                           'tests/files/shell/patch')

    def test_create_and_apply_patch_shell_crle_compression(self):
        self.assert_create_and_apply_patch('tests/files/shell/old',
                                           'tests/files/shell/new',
                                           'tests/files/shell/crle.patch',
                                           compression='crle')

    def test_create_and_apply_patch_shell_bz2_compression(self):
        self.assert_create_and_apply_patch('tests/files/shell/old',
                                           'tests/files/shell/new',
                                           'tests/files/shell/bz2.patch',
                                           compression='bz2')

    def test_create_and_apply_patch_shell_zstd_compression(self):
        self.assert_create_and_apply_patch('tests/files/shell/old',
                                           'tests/files/shell/new',
                                           'tests/files/shell/zstd.patch',
                                           compression='zstd')

    def test_create_and_apply_patch_shell_lz4_compression(self):
        self.assert_create_and_apply_patch('tests/files/shell/old',
                                           'tests/files/shell/new',
                                           'tests/files/shell/lz4.patch',
                                           compression='lz4')

    def test_create_and_apply_patch_shell_arm_cortex_m4(self):
        self.assert_create_and_apply_patch('tests/files/shell/old',
                                           'tests/files/shell/new',
                                           'tests/files/shell/arm-cortex-m4.patch',
                                           data_format='arm-cortex-m4')

    def test_create_and_apply_patch_shell_arm_cortex_m4_bz2_compression(self):
        self.assert_create_and_apply_patch(
            'tests/files/shell/old',
            'tests/files/shell/new',
            'tests/files/shell/arm-cortex-m4-bz2.patch',
            data_format='arm-cortex-m4',
            compression='bz2')

    def test_create_and_apply_patch_shell_arm_cortex_m4_crle_compression(self):
        self.assert_create_and_apply_patch(
            'tests/files/shell/old',
            'tests/files/shell/new',
            'tests/files/shell/arm-cortex-m4-crle.patch',
            data_format='arm-cortex-m4',
            compression='crle')

    def test_create_and_apply_patch_synthesizer_1_2(self):
        self.assert_create_and_apply_patch('tests/files/synthesizer/1.bin',
                                           'tests/files/synthesizer/2.bin',
                                           'tests/files/synthesizer/1--2.patch')

    def test_create_and_apply_patch_synthesizer_1_2_arm_cortex_m4(self):
        self.assert_create_and_apply_patch(
            'tests/files/synthesizer/1.bin',
            'tests/files/synthesizer/2.bin',
            'tests/files/synthesizer/1--2-arm-cortex-m4.patch',
            data_format='arm-cortex-m4')

    def test_create_and_apply_patch_synthesizer_1_3(self):
        self.assert_create_and_apply_patch('tests/files/synthesizer/1.bin',
                                           'tests/files/synthesizer/3.bin',
                                           'tests/files/synthesizer/1--3.patch')

    def test_create_and_apply_patch_synthesizer_1_3_arm_cortex_m4(self):
        self.assert_create_and_apply_patch(
            'tests/files/synthesizer/1.bin',
            'tests/files/synthesizer/3.bin',
            'tests/files/synthesizer/1--3-arm-cortex-m4.patch',
            data_format='arm-cortex-m4')

    def test_create_and_apply_patch_foo_none_compression(self):
        self.assert_create_and_apply_patch('tests/files/foo/old',
                                           'tests/files/foo/new',
                                           'tests/files/foo/none.patch',
                                           compression='none')

    def test_create_and_apply_patch_micropython_none_compression(self):
        self.assert_create_and_apply_patch(
            'tests/files/micropython/esp8266-20180511-v1.9.4.bin',
            'tests/files/micropython/esp8266-20190125-v1.10.bin',
            'tests/files/micropython/esp8266-20180511-v1.9.4--'
            '20190125-v1.10-none.patch',
            compression='none')

    def test_create_and_apply_patch_foo_crle_compression(self):
        self.assert_create_and_apply_patch('tests/files/foo/old',
                                           'tests/files/foo/new',
                                           'tests/files/foo/crle.patch',
                                           compression='crle')

    def test_create_and_apply_patch_foo_heatshrink_compression(self):
        self.assert_create_and_apply_patch('tests/files/foo/old',
                                           'tests/files/foo/new',
                                           'tests/files/foo/heatshrink.patch',
                                           compression='heatshrink')

    def test_create_and_apply_patch_foo_heatshrink_compression_custom(self):
        self.assert_create_and_apply_patch('tests/files/foo/old',
                                           'tests/files/foo/new',
                                           'tests/files/foo/heatshrink-10-5.patch',
                                           compression='heatshrink',
                                           heatshrink_window_sz2=10,
                                           heatshrink_lookahead_sz2=5)

    def test_create_and_apply_patch_foo_zstd_compression(self):
        self.assert_create_and_apply_patch('tests/files/foo/old',
                                           'tests/files/foo/new',
                                           'tests/files/foo/zstd.patch',
                                           compression='zstd')

    def test_create_and_apply_patch_micropython_zstd_compression(self):
        self.assert_create_and_apply_patch(
            'tests/files/micropython/esp8266-20180511-v1.9.4.bin',
            'tests/files/micropython/esp8266-20190125-v1.10.bin',
            'tests/files/micropython/esp8266-20180511-v1.9.4--'
            '20190125-v1.10-zstd.patch',
            compression='zstd')

    def test_create_and_apply_patch_foo_lz4_compression(self):
        self.assert_create_and_apply_patch('tests/files/foo/old',
                                           'tests/files/foo/new',
                                           'tests/files/foo/lz4.patch',
                                           compression='lz4')

    def test_create_and_apply_patch_micropython_lz4_compression(self):
        self.assert_create_and_apply_patch(
            'tests/files/micropython/esp8266-20180511-v1.9.4.bin',
            'tests/files/micropython/esp8266-20190125-v1.10.bin',
            'tests/files/micropython/esp8266-20180511-v1.9.4--'
            '20190125-v1.10-lz4.patch',
            compression='lz4')

    def test_create_and_apply_patch_micropython_crle_compression(self):
        self.assert_create_and_apply_patch(
            'tests/files/micropython/esp8266-20180511-v1.9.4.bin',
            'tests/files/micropython/esp8266-20190125-v1.10.bin',
            'tests/files/micropython/esp8266-20180511-v1.9.4--20190125-v1.10-crle.patch',
            compression='crle')

    def test_create_and_apply_patch_micropython_heatshrink_compression(self):
        self.assert_create_and_apply_patch(
            'tests/files/micropython/esp8266-20180511-v1.9.4.bin',
            'tests/files/micropython/esp8266-20190125-v1.10.bin',
            'tests/files/micropython/esp8266-20180511-v1.9.4--'
            '20190125-v1.10-heatshrink.patch',
            compression='heatshrink')

    def test_create_and_apply_patch_micropython_in_place(self):
        self.assert_create_and_apply_patch(
            'tests/files/micropython/esp8266-20180511-v1.9.4.bin',
            'tests/files/micropython/esp8266-20190125-v1.10.bin',
            'tests/files/micropython/esp8266-20180511-v1.9.4--'
            '20190125-v1.10-in-place.patch',
            patch_type='in-place',
            memory_size=2097152,
            segment_size=65536)

    def test_create_and_apply_patch_micropython_xtensa_lx106(self):
        self.assert_create_and_apply_patch(
            'tests/files/micropython/esp8266-20180511-v1.9.4.bin',
            'tests/files/micropython/esp8266-20190125-v1.10.bin',
            'tests/files/micropython/esp8266-20180511-v1.9.4--'
            '20190125-v1.10-xtensa-lx106.patch',
            data_format='xtensa-lx106')

    def test_create_and_apply_patch_micropython_data_and_code_sections(self):
        self.assert_create_and_apply_patch(
            'tests/files/micropython/esp8266-20180511-v1.9.4.bin',
            'tests/files/micropython/esp8266-20190125-v1.10.bin',
            'tests/files/micropython/esp8266-20180511-v1.9.4--'
            '20190125-v1.10-xtensa-lx106-data-sections.patch',
            data_format='xtensa-lx106',
            from_data_offset_begin=0x7b368,
            from_data_offset_end=0x93ab8,
            from_code_begin=0x40209040,
            from_code_end=0x4027b365,
            from_data_begin=0x4027b368,
            from_data_end=0x40293ab8,
            to_data_offset_begin=0x7d084,
            to_data_offset_end=0x963c4,
            to_code_begin=0x40209040,
            to_code_end=0x4027cffc,
            to_data_begin=0x4027d084,
            to_data_end=0x402963c4)

    def test_create_and_apply_patch_foo_in_place_3000_1500(self):
        self.assert_create_and_apply_patch(
            'tests/files/foo/old',
            'tests/files/foo/new',
            'tests/files/foo/in-place-3000-1500.patch',
            patch_type='in-place',
            memory_size=3000,
            segment_size=1500)

    def test_create_and_apply_patch_foo_in_place_3k_1_5k(self):
        self.assert_create_and_apply_patch('tests/files/foo/old',
                                           'tests/files/foo/new',
                                           'tests/files/foo/in-place-3k-1.5k.patch',
                                           patch_type='in-place',
                                           memory_size=3072,
                                           segment_size=1536)

    def test_create_and_apply_patch_foo_in_place_3000_1500_1500(self):
        self.assert_create_and_apply_patch('tests/files/foo/old',
                                           'tests/files/foo/new',
                                           'tests/files/foo/in-place-3000-1500-1500.patch',
                                           patch_type='in-place',
                                           memory_size=3000,
                                           segment_size=1500,
                                           minimum_shift_size=1500)

    def test_create_and_apply_patch_foo_in_place_3000_500(self):
        self.assert_create_and_apply_patch('tests/files/foo/old',
                                           'tests/files/foo/new',
                                           'tests/files/foo/in-place-3000-500.patch',
                                           patch_type='in-place',
                                           memory_size=3000,
                                           segment_size=500)

    def test_create_and_apply_patch_foo_in_place_3000_500_crle(self):
        self.assert_create_and_apply_patch(
            'tests/files/foo/old',
            'tests/files/foo/new',
            'tests/files/foo/in-place-3000-500-crle.patch',
            patch_type='in-place',
            compression='crle',
            memory_size=3000,
            segment_size=500)

    def test_create_and_apply_patch_foo_in_place_6000_1000_crle(self):
        self.assert_create_and_apply_patch(
            'tests/files/foo/old',
            'tests/files/foo/new',
            'tests/files/foo/in-place-6000-1000-crle.patch',
            patch_type='in-place',
            compression='crle',
            memory_size=6000,
            segment_size=1000)

    def test_create_and_apply_patch_foo_in_place_minimum_size(self):
        self.assert_create_and_apply_patch(
            'tests/files/foo/old',
            'tests/files/foo/new',
            'tests/files/foo/in-place-minimum-size.patch',
            patch_type='in-place',
            memory_size=3000,
            segment_size=500,
            minimum_shift_size=2000)

    def test_create_and_apply_patch_foo_in_place_many_segments(self):
        self.assert_create_and_apply_patch(
            'tests/files/foo/old',
            'tests/files/foo/new',
            'tests/files/foo/in-place-many-segments.patch',
            patch_type='in-place',
            memory_size=3000,
            segment_size=50)

    def test_create_and_apply_patch_bsdiff(self):
        self.assert_create_and_apply_patch(
            'tests/files/bsdiff.py',
            'tests/files/READ-ME.rst',
            'tests/files/bsdiff-READ-ME.patch')

    def test_create_and_apply_patch_sais(self):
        self.assert_create_and_apply_patch(
            'tests/files/sais.c',
            'tests/files/READ-ME.rst',
            'tests/files/sais-READ-ME.patch')

    def test_create_and_apply_patch_3f5531ba56182a807a5c358f04678b3b026d3a(self):
        self.assert_create_and_apply_patch(
            'tests/files/3f5531ba56182a807a5c358f04678b3b026d3a.bin',
            'tests/files/READ-ME.rst',
            'tests/files/3f5531ba56182a807a5c358f04678b3b026d3a-READ-ME.patch')

    def test_create_and_apply_patch_b2db59ab76ca36f67e61f720857021df8a660b(self):
        self.assert_create_and_apply_patch(
            'tests/files/b2db59ab76ca36f67e61f720857021df8a660b.bin',
            'tests/files/READ-ME.rst',
            'tests/files/b2db59ab76ca36f67e61f720857021df8a660b-READ-ME.patch')

    def test_create_and_apply_patch_d027a1e1f752f15b6a13d9f9d775f3914c83f7(self):
        self.assert_create_and_apply_patch(
            'tests/files/d027a1e1f752f15b6a13d9f9d775f3914c83f7.bin',
            'tests/files/READ-ME.rst',
            'tests/files/d027a1e1f752f15b6a13d9f9d775f3914c83f7-READ-ME.patch')

    def test_create_and_apply_patch_eb9ed88e9975028c4694e070cfaece2498e92d(self):
        self.assert_create_and_apply_patch(
            'tests/files/eb9ed88e9975028c4694e070cfaece2498e92d.bin',
            'tests/files/READ-ME.rst',
            'tests/files/eb9ed88e9975028c4694e070cfaece2498e92d-READ-ME.patch')

    def test_create_and_apply_patch_no_delta(self):
        self.assert_create_and_apply_patch('tests/files/foo/new',
                                           'tests/files/foo/new',
                                           'tests/files/foo/no-delta.patch')

    def test_create_and_apply_patch_empty(self):
        self.assert_create_and_apply_patch('tests/files/empty/old',
                                           'tests/files/empty/new',
                                           'tests/files/empty/patch')

    def test_create_and_apply_patch_empty_none_compression(self):
        self.assert_create_and_apply_patch('tests/files/empty/old',
                                           'tests/files/empty/new',
                                           'tests/files/empty/none.patch',
                                           compression='none')

    def test_create_and_apply_patch_empty_crle_compression(self):
        self.assert_create_and_apply_patch('tests/files/empty/old',
                                           'tests/files/empty/new',
                                           'tests/files/empty/crle.patch',
                                           compression='crle')

    def test_create_and_apply_patch_empty_heatshrink_compression(self):
        self.assert_create_and_apply_patch('tests/files/empty/old',
                                           'tests/files/empty/new',
                                           'tests/files/empty/heatshrink.patch',
                                           compression='heatshrink')

    def test_create_and_apply_patch_empty_in_place(self):
        self.assert_create_and_apply_patch('tests/files/empty/old',
                                           'tests/files/empty/new',
                                           'tests/files/empty/in-place.patch',
                                           patch_type='in-place',
                                           memory_size=30000,
                                           segment_size=500)

    def test_apply_patch_foo_empty(self):
        fnew = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/empty.patch', 'rb') as fpatch:
                with self.assertRaises(detools.Error) as cm:
                    detools.apply_patch(fold, fpatch, fnew)

                self.assertEqual(str(cm.exception),
                                 "Failed to read the patch header.")

    def test_apply_patch_foo_short(self):
        fnew = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/short.patch', 'rb') as fpatch:
                with self.assertRaises(detools.Error) as cm:
                    detools.apply_patch(fold, fpatch, fnew)

                self.assertEqual(str(cm.exception),
                                 "End of patch not found.")

    def test_apply_patch_foo_short_none_compression(self):
        fnew = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/short-none.patch', 'rb') as fpatch:
                with self.assertRaises(detools.Error) as cm:
                    detools.apply_patch(fold, fpatch, fnew)

                self.assertEqual(str(cm.exception), "Early end of patch data.")

    def test_apply_patch_foo_long(self):
        fnew = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/bad-lzma-end.patch', 'rb') as fpatch:
                with self.assertRaises(detools.Error) as cm:
                    detools.apply_patch(fold, fpatch, fnew)

                self.assertEqual(str(cm.exception),
                                 "Patch decompression failed.")

    def test_apply_patch_foo_diff_data_too_long(self):
        fnew = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/diff-data-too-long.patch', 'rb') as fpatch:
                with self.assertRaises(detools.Error) as cm:
                    detools.apply_patch(fold, fpatch, fnew)

                self.assertEqual(str(cm.exception),
                                 "Patch diff data too long.")

    def test_apply_patch_foo_extra_data_too_long(self):
        fnew = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/extra-data-too-long.patch', 'rb') as fpatch:
                with self.assertRaises(detools.Error) as cm:
                    detools.apply_patch(fold, fpatch, fnew)

                self.assertEqual(str(cm.exception),
                                 "Patch extra data too long.")

    def test_apply_patch_foo_bad_patch_type(self):
        fnew = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/bad-patch-type.patch', 'rb') as fpatch:
                with self.assertRaises(detools.Error) as cm:
                    detools.apply_patch(fold, fpatch, fnew)

                self.assertEqual(str(cm.exception), "Bad patch type 7.")

    def test_create_patch_foo_bad_patch_type(self):
        fpatch = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/new', 'rb') as fnew:
                with self.assertRaises(detools.Error) as cm:
                    detools.create_patch(fold, fnew, fpatch, patch_type='bad')

                self.assertEqual(
                    str(cm.exception),
                    "Bad algorithm (bsdiff) and patch type (bad) combination.")

    def test_apply_patch_foo_bad_compression(self):
        fnew = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/bad-compression.patch', 'rb') as fpatch:
                with self.assertRaises(detools.Error) as cm:
                    detools.apply_patch(fold, fpatch, fnew)

                self.assertEqual(
                    str(cm.exception),
                    "Expected compression none(0), lzma(1), crle(2), bz2(3), "
                    "heatshrink(4), zstd(5) or lz4(6), but got 15.")

    def test_create_patch_foo_bad_compression(self):
        fpatch = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/new', 'rb') as fnew:
                with self.assertRaises(detools.Error) as cm:
                    detools.create_patch(fold, fnew, fpatch, compression='bad')

                self.assertEqual(
                    str(cm.exception),
                    "Expected compression bz2, crle, heatshrink, lz4, lzma, "
                    "none or zstd, but got bad.")

    def test_apply_patch_one_byte(self):
        fnew = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/one-byte.patch', 'rb') as fpatch:
                with self.assertRaises(detools.Error) as cm:
                    detools.apply_patch(fold, fpatch, fnew)

                self.assertEqual(str(cm.exception),
                                 "Failed to read first size byte.")

    def test_apply_patch_short_to_size(self):
        fnew = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/short-to-size.patch', 'rb') as fpatch:
                with self.assertRaises(detools.Error) as cm:
                    detools.apply_patch(fold, fpatch, fnew)

                self.assertEqual(str(cm.exception),
                                 "Failed to read consecutive size byte.")

    def test_create_patch_in_place_bad_memory_and_segment_size_ratio(self):
        fpatch = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/new', 'rb') as fnew:
                with self.assertRaises(detools.Error) as cm:
                    detools.create_patch(fold,
                                         fnew,
                                         fpatch,
                                         patch_type='in-place',
                                         memory_size=3000,
                                         segment_size=501)

                self.assertEqual(
                    str(cm.exception),
                    "Memory size 3000 is not a multiple of segment size 501.")

    def test_create_patch_in_place_bad_minimum_shift_and_segment_size_ratio(self):
        fpatch = BytesIO()

        with open('tests/files/foo/old', 'rb') as fold:
            with open('tests/files/foo/new', 'rb') as fnew:
                with self.assertRaises(detools.Error) as cm:
                    detools.create_patch(fold,
                                         fnew,
                                         fpatch,
                                         patch_type='in-place',
                                         memory_size=3000,
                                         segment_size=500,
                                         minimum_shift_size=999)

                self.assertEqual(
                    str(cm.exception),
                    "Minimum shift size 999 is not a multiple of segment size 500.")

    def test_patch_info_bad_empty_header(self):
        with self.assertRaises(detools.Error) as cm:
            detools.patch_info_filename('tests/files/empty/old')

        self.assertEqual(str(cm.exception), "Failed to read the patch header.")

    def test_patch_info_bad_patch_type(self):
        with self.assertRaises(detools.Error) as cm:
            detools.patch_info_filename('tests/files/foo/bad-patch-type.patch')

        self.assertEqual(str(cm.exception), "Bad patch type 7.")

    def test_apply_patch_in_place_small_memory_size(self):
        with self.assertRaises(detools.Error) as cm:
            detools.apply_patch_in_place_filenames(
                'tests/files/foo/old',
                'tests/files/foo/in-place-3000-1500.patch')

        self.assertEqual(
            str(cm.exception),
            "Expected memory size of at least 3000 bytes, but got 2780.")

    def test_apply_patch_in_place_foo_retain_after_3000(self):
        with open('foo.mem', 'wb') as fmem:
            with open('tests/files/foo/old', 'rb') as fold:
                fmem.write(fold.read())
                fmem.write((3000 - 2780) * b'\xff')
                fmem.write(b'\x01\x02\x03')

        detools.apply_patch_in_place_filenames(
            'foo.mem',
            'tests/files/foo/in-place-3000-1500.patch')

        with open('foo.mem', 'rb') as fmem:
            data = fmem.read()

        self.assertEqual(len(data), 3003)
        self.assertEqual(data[-3:], b'\x01\x02\x03')

    def test_apply_patch_in_place_foo_bad_patch_type(self):
        with self.assertRaises(detools.Error) as cm:
            detools.apply_patch_in_place_filenames(
                'tests/files/foo/old',
                'tests/files/foo/patch')

        self.assertEqual(
            str(cm.exception),
            "Expected patch type 1, but got 0.")

    def test_apply_patch_in_place_foo_memory_size_missing(self):
        with self.assertRaises(detools.Error) as cm:
            detools.apply_patch_in_place_filenames(
                'tests/files/foo/old',
                'tests/files/foo/missing-in-place-memory-size.patch')

        self.assertEqual(
            str(cm.exception),
            "Failed to read first size byte.")

    def test_apply_patch_in_place_foo_segment_size_missing(self):
        with self.assertRaises(detools.Error) as cm:
            detools.apply_patch_in_place_filenames(
                'tests/files/foo/old',
                'tests/files/foo/missing-in-place-segment-size.patch')

        self.assertEqual(
            str(cm.exception),
            "Failed to read first size byte.")

    def test_apply_patch_in_place_foo_shift_size_missing(self):
        with self.assertRaises(detools.Error) as cm:
            detools.apply_patch_in_place_filenames(
                'tests/files/foo/old',
                'tests/files/foo/missing-in-place-shift-size.patch')

        self.assertEqual(
            str(cm.exception),
            "Failed to read first size byte.")

    def test_apply_patch_in_place_foo_from_size_missing(self):
        with self.assertRaises(detools.Error) as cm:
            detools.apply_patch_in_place_filenames(
                'tests/files/foo/old',
                'tests/files/foo/missing-in-place-from-size.patch')

        self.assertEqual(
            str(cm.exception),
            "Failed to read first size byte.")

    def test_create_and_apply_patch_foo_data_format_arm_cortex_m4(self):
        self.assert_create_and_apply_patch(
            'tests/files/foo/old',
            'tests/files/foo/new',
            'tests/files/foo/arm-cortex-m4.patch',
            data_format='arm-cortex-m4')

    def test_create_and_apply_patch_shell_pi_3(self):
        self.assert_create_and_apply_patch(
            'tests/files/shell-pi-3/1.bin',
            'tests/files/shell-pi-3/2.bin',
            'tests/files/shell-pi-3/1--2.patch')

    def test_create_and_apply_patch_shell_pi_3_data_format_aarch64(self):
        self.assert_create_and_apply_patch(
            'tests/files/shell-pi-3/1.bin',
            'tests/files/shell-pi-3/2.bin',
            'tests/files/shell-pi-3/1--2-aarch64.patch',
            data_format='aarch64')

    def test_create_and_apply_patch_shell_pi_3_data_and_code_sections(self):
        self.assert_create_and_apply_patch(
            'tests/files/shell-pi-3/1.bin',
            'tests/files/shell-pi-3/2.bin',
            'tests/files/shell-pi-3/1--2-aarch64-data-sections.patch',
            data_format='aarch64',
            from_data_offset_begin=0x15300,
            from_data_offset_end=0x30ab8,
            from_code_begin=0x0,
            from_code_end=0xd2e0,
            from_data_begin=0x40000000,
            from_data_end=0x4001b7b8,
            to_data_offset_begin=0x15300,
            to_data_offset_end=0x30ab8,
            to_code_begin=0x0,
            to_code_end=0xd2f0,
            to_data_begin=0x40000000,
            to_data_end=0x4001b7b8)

    def test_create_and_apply_patch_python3(self):
        self.assert_create_and_apply_patch(
            'tests/files/python3/aarch64/3.6.6-1/libpython3.6m.so.1.0',
            'tests/files/python3/aarch64/3.7.2-3/libpython3.7m.so.1.0',
            'tests/files/python3/aarch64/3.6.6-1--3.7.2-3.patch')

    def test_create_and_apply_patch_python3_aarch64(self):
        self.assert_create_and_apply_patch(
            'tests/files/python3/aarch64/3.6.6-1/libpython3.6m.so.1.0',
            'tests/files/python3/aarch64/3.7.2-3/libpython3.7m.so.1.0',
            'tests/files/python3/aarch64/3.6.6-1--3.7.2-3-aarch64.patch',
            data_format='aarch64')

    def test_create_and_apply_patch_python3_2(self):
        self.assert_create_and_apply_patch(
            'tests/files/python3/aarch64/3.7.2-3/libpython3.7m.so.1.0',
            'tests/files/python3/aarch64/3.7.3-1/libpython3.7m.so.1.0',
            'tests/files/python3/aarch64/3.7.2-3--3.7.3-1.patch')

    def test_create_and_apply_patch_python3_2_aarch64(self):
        self.assert_create_and_apply_patch(
            'tests/files/python3/aarch64/3.7.2-3/libpython3.7m.so.1.0',
            'tests/files/python3/aarch64/3.7.3-1/libpython3.7m.so.1.0',
            'tests/files/python3/aarch64/3.7.2-3--3.7.3-1-aarch64.patch',
            data_format='aarch64')

    def test_create_and_apply_patch_foo_bsdiff(self):
        self.assert_create_and_apply_patch('tests/files/foo/old',
                                           'tests/files/foo/new',
                                           'tests/files/foo/bsdiff.patch',
                                           patch_type='bsdiff')

    def test_create_and_apply_patch_micropython_bsdiff(self):
        self.assert_create_and_apply_patch(
            'tests/files/micropython/esp8266-20180511-v1.9.4.bin',
            'tests/files/micropython/esp8266-20190125-v1.10.bin',
            'tests/files/micropython/esp8266-20180511-v1.9.4--20190125-v1.10-'
            'bsdiff.patch',
            patch_type='bsdiff')

    def test_create_and_apply_patch_foo_hdiffpatch(self):
        self.assert_create_and_apply_patch('tests/files/foo/old',
                                           'tests/files/foo/new',
                                           'tests/files/foo/hdiffpatch.patch',
                                           algorithm='hdiffpatch',
                                           patch_type='hdiffpatch')

    def test_create_and_apply_patch_foo_match_blocks_sequential_none(self):
        self.assert_create_and_apply_patch(
            'tests/files/foo/old',
            'tests/files/foo/new',
            'tests/files/foo/match-blocks-sequential-none.patch',
            patch_type='sequential',
            algorithm='match-blocks',
            compression='none',
            match_block_size=8)

    def test_create_and_apply_patch_foo_match_blocks_sequential(self):
        self.assert_create_and_apply_patch(
            'tests/files/foo/old',
            'tests/files/foo/new',
            'tests/files/foo/match-blocks-sequential.patch',
            patch_type='sequential',
            algorithm='match-blocks',
            match_block_size=8)

    def test_create_and_apply_patch_random_match_blocks_sequential_none(self):
        self.assert_create_and_apply_patch(
            'tests/files/random/from.bin',
            'tests/files/random/to.bin',
            'tests/files/random/match-blocks-sequential-none.patch',
            compression='none',
            patch_type='sequential',
            algorithm='match-blocks',
            match_block_size=64)

    def test_create_and_apply_patch_random_match_blocks_hdiffpatch(self):
        self.assert_create_and_apply_patch(
            'tests/files/random/from.bin',
            'tests/files/random/to.bin',
            'tests/files/random/match-blocks-hdiffpatch.patch',
            patch_type='hdiffpatch',
            algorithm='match-blocks',
            match_block_size=64)

    def test_create_and_apply_patch_random_bsdiff(self):
        self.assert_create_and_apply_patch('tests/files/random/from.bin',
                                           'tests/files/random/to.bin',
                                           'tests/files/random/patch-bsdiff.bin',
                                           patch_type='bsdiff')

    def test_pack_unpack_size(self):
        datas = [
            (-16_000_000_000, b'\xc0\x80\xe5\x9aw'),
            ( -5_000_000_000, b'\xc0\xc8\xaf\xa0%'),
            ( -2_000_000_000, b'\xc0\xd0\xac\xf3\x0e'),
            (       -100_000, b'\xe0\x9a\x0c'),
            (             -5, b'E'),
            (              0, b'\x00'),
            (              5, b'\x05'),
            (        100_000, b'\xa0\x9a\x0c'),
            (  2_000_000_000, b'\x80\xd0\xac\xf3\x0e'),
            (  5_000_000_000, b'\x80\xc8\xaf\xa0%'),
            ( 16_000_000_000, b'\x80\x80\xe5\x9aw')
        ]

        for value, packed in datas:
            self.assertEqual(pack_size(value), packed)
            self.assertEqual(unpack_size_bytes(packed), value)


# This file is not '__main__' when executed via 'python setup.py3
# test'.
logging.basicConfig(level=logging.DEBUG)

if __name__ == '__main__':
    unittest.main()
