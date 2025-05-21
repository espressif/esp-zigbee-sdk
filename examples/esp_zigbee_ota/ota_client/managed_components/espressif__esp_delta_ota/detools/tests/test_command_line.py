import os
import unittest
from unittest.mock import patch
from io import StringIO

import detools


def read_file(filename):
    with open(filename, 'rb') as fin:
        return fin.read()


class DetoolsCommandLineTest(unittest.TestCase):

    def execute_and_assert(self, argv, actual_file, expected_file):
        if os.path.exists(actual_file):
            os.remove(actual_file)

        with patch('sys.argv', argv):
            detools._main()

        self.assertEqual(read_file(actual_file), read_file(expected_file))

    def test_create_patch_foo(self):
        foo_patch = 'foo.patch'
        argv = [
            'detools',
            'create_patch',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        self.execute_and_assert(argv, foo_patch, 'tests/files/foo/patch')

    def test_create_patch_foo_heatshrink(self):
        foo_patch = 'foo.patch'
        argv = [
            'detools',
            'create_patch',
            '-c', 'heatshrink',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        self.execute_and_assert(argv, foo_patch, 'tests/files/foo/heatshrink.patch')

    def test_create_patch_foo_heatshrink_custom(self):
        foo_patch = 'foo.patch'
        argv = [
            'detools',
            'create_patch',
            '-c', 'heatshrink',
            '--heatshrink-window-sz2', '10',
            '--heatshrink-lookahead-sz2', '5',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        self.execute_and_assert(argv, foo_patch, 'tests/files/foo/heatshrink-10-5.patch')

    def test_create_patch_foo_hdiffpatch_no_mmap(self):
        foo_patch = 'foo.patch'
        argv = [
            'detools',
            'create_patch',
            '-a', 'hdiffpatch',
            '-t', 'hdiffpatch',
            '--no-mmap',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        self.execute_and_assert(argv, foo_patch, 'tests/files/foo/hdiffpatch.patch')

    def test_create_patch_foo_no_mmap(self):
        foo_patch = 'foo.patch'
        argv = [
            'detools',
            'create_patch',
            '--no-mmap',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        self.execute_and_assert(argv, foo_patch, 'tests/files/foo/patch')

    def test_create_patch_empty_from_non_empty_to_mmap(self):
        nonempty_patch = 'nonempty.patch'
        argv = [
            'detools',
            'create_patch',
            'tests/files/empty/old',
            'tests/files/empty/nonempty.bin',
            nonempty_patch
        ]

        self.execute_and_assert(argv,
                                nonempty_patch,
                                'tests/files/empty/nonempty.patch')

    def test_create_patch_foo_sais(self):
        foo_patch = 'foo.patch'
        argv = [
            'detools',
            'create_patch',
            '--suffix-array-algorithm', 'sais',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        self.execute_and_assert(argv, foo_patch, 'tests/files/foo/patch')

    def test_apply_patch_foo(self):
        foo_new = 'foo.new'
        argv = [
            'detools',
            '--debug',
            'apply_patch',
            'tests/files/foo/old',
            'tests/files/foo/patch',
            foo_new
        ]

        self.execute_and_assert(argv, foo_new, 'tests/files/foo/new')

    def test_patch_info_foo(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/foo/patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(stdout.getvalue(),
                         'Type:               sequential\n'
                         'Patch size:         127 bytes\n'
                         'To size:            2.71 KiB\n'
                         'Patch/to ratio:     4.6 % (lower is better)\n'
                         'Diff/extra ratio:   9828.6 % (higher is better)\n'
                         'Size/data ratio:    0.3 % (lower is better)\n'
                         'Compression:        lzma\n'
                         'Data format size:   0 bytes\n'
                         '\n'
                         'Number of diffs:    2\n'
                         'Total diff size:    2.69 KiB\n'
                         'Average diff size:  1.34 KiB\n'
                         'Median diff size:   1.34 KiB\n'
                         '\n'
                         'Number of extras:   2\n'
                         'Total extra size:   28 bytes\n'
                         'Average extra size: 14 bytes\n'
                         'Median extra size:  14 bytes\n')

    def test_patch_info_foo_heatshrink_empty(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/empty/heatshrink.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(
            stdout.getvalue(),
            'Type:               sequential\n'
            'Patch size:         2 bytes\n'
            'To size:            0 bytes\n'
            'Patch/to ratio:     inf % (lower is better)\n'
            'Diff/extra ratio:   inf % (higher is better)\n'
            'Size/data ratio:    inf % (lower is better)\n'
            'Compression:        heatshrink\n'
            'Data format size:   0 bytes\n'
            '\n'
            'Number of diffs:    0\n'
            'Total diff size:    0 bytes\n'
            'Average diff size:  -\n'
            'Median diff size:   -\n'
            '\n'
            'Number of extras:   0\n'
            'Total extra size:   0 bytes\n'
            'Average extra size: -\n'
            'Median extra size:  -\n')

    def test_patch_info_foo_no_delta(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/foo/no-delta.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(stdout.getvalue(),
                         'Type:               sequential\n'
                         'Patch size:         49 bytes\n'
                         'To size:            2.71 KiB\n'
                         'Patch/to ratio:     1.8 % (lower is better)\n'
                         'Diff/extra ratio:   inf % (higher is better)\n'
                         'Size/data ratio:    0.2 % (lower is better)\n'
                         'Compression:        lzma\n'
                         'Data format size:   0 bytes\n'
                         '\n'
                         'Number of diffs:    1\n'
                         'Total diff size:    2.71 KiB\n'
                         'Average diff size:  2.71 KiB\n'
                         'Median diff size:   2.71 KiB\n'
                         '\n'
                         'Number of extras:   1\n'
                         'Total extra size:   0 bytes\n'
                         'Average extra size: 0 bytes\n'
                         'Median extra size:  0 bytes\n')

    def test_patch_info_foo_none_compression(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/foo/none.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(stdout.getvalue(),
                         'Type:               sequential\n'
                         'Patch size:         2.73 KiB\n'
                         'To size:            2.71 KiB\n'
                         'Patch/to ratio:     100.4 % (lower is better)\n'
                         'Diff/extra ratio:   9828.6 % (higher is better)\n'
                         'Size/data ratio:    0.3 % (lower is better)\n'
                         'Compression:        none\n'
                         'Data format size:   0 bytes\n'
                         '\n'
                         'Number of diffs:    2\n'
                         'Total diff size:    2.69 KiB\n'
                         'Average diff size:  1.34 KiB\n'
                         'Median diff size:   1.34 KiB\n'
                         '\n'
                         'Number of extras:   2\n'
                         'Total extra size:   28 bytes\n'
                         'Average extra size: 14 bytes\n'
                         'Median extra size:  14 bytes\n')

    def test_patch_info_foo_crle_compression(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/foo/crle.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(stdout.getvalue(),
                         'Type:               sequential\n'
                         'Patch size:         190 bytes\n'
                         'To size:            2.71 KiB\n'
                         'Patch/to ratio:     6.8 % (lower is better)\n'
                         'Diff/extra ratio:   9828.6 % (higher is better)\n'
                         'Size/data ratio:    0.3 % (lower is better)\n'
                         'Compression:        crle\n'
                         'Data format size:   0 bytes\n'
                         '\n'
                         'Number of diffs:    2\n'
                         'Total diff size:    2.69 KiB\n'
                         'Average diff size:  1.34 KiB\n'
                         'Median diff size:   1.34 KiB\n'
                         '\n'
                         'Number of extras:   2\n'
                         'Total extra size:   28 bytes\n'
                         'Average extra size: 14 bytes\n'
                         'Median extra size:  14 bytes\n')

    def test_create_patch_foo_in_place(self):
        foo_patch = 'foo-in-place-3000-1500.patch'
        argv = [
            'detools',
            'create_patch_in_place',
            '--memory-size', '3000',
            '--segment-size', '1500',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        self.execute_and_assert(argv,
                                foo_patch,
                                'tests/files/foo/in-place-3000-1500.patch')

    def test_apply_patch_foo_in_place(self):
        foo_mem = 'foo.mem'
        argv = [
            'detools',
            '--debug',
            'apply_patch_in_place',
            foo_mem,
            'tests/files/foo/in-place-3000-1500.patch'
        ]

        with open(foo_mem, 'wb') as fmem:
            with open('tests/files/foo/old', 'rb') as fold:
                fmem.write(fold.read() + (3000 - 2780) * b'\xff')

        with patch('sys.argv', argv):
            detools._main()

        self.assertEqual(
            read_file(foo_mem),
            read_file('tests/files/foo/new') + (3000 - 2780) * b'\xff')

    def test_patch_info_foo_in_place(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/foo/in-place-3000-1500.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(
            stdout.getvalue(),
            'Type:               in-place\n'
            'Patch size:         1.92 KiB\n'
            'Memory size:        2.93 KiB\n'
            'Segment size:       1.46 KiB\n'
            'From shift size:    2.93 KiB\n'
            'From size:          2.71 KiB\n'
            'To size:            2.71 KiB\n'
            'Patch/to ratio:     70.8 % (lower is better)\n'
            'Number of segments: 2\n'
            'Compression:        lzma\n'
            '\n'
            '------------------- Segment 1 -------------------\n'
            '\n'
            'From range:         0 bytes - 0 bytes\n'
            'To range:           0 bytes - 1.46 KiB\n'
            'Diff/extra ratio:   0.0 % (higher is better)\n'
            'Size/data ratio:    0.3 % (lower is better)\n'
            'Data format size:   0 bytes\n'
            '\n'
            'Number of diffs:    1\n'
            'Total diff size:    0 bytes\n'
            'Average diff size:  0 bytes\n'
            'Median diff size:   0 bytes\n'
            '\n'
            'Number of extras:   1\n'
            'Total extra size:   1.46 KiB\n'
            'Average extra size: 1.46 KiB\n'
            'Median extra size:  1.46 KiB\n'
            '\n'
            '------------------- Segment 2 -------------------\n'
            '\n'
            'From range:         0 bytes - 0 bytes\n'
            'To range:           1.46 KiB - 2.71 KiB\n'
            'Diff/extra ratio:   0.0 % (higher is better)\n'
            'Size/data ratio:    0.3 % (lower is better)\n'
            'Data format size:   0 bytes\n'
            '\n'
            'Number of diffs:    1\n'
            'Total diff size:    0 bytes\n'
            'Average diff size:  0 bytes\n'
            'Median diff size:   0 bytes\n'
            '\n'
            'Number of extras:   1\n'
            'Total extra size:   1.25 KiB\n'
            'Average extra size: 1.25 KiB\n'
            'Median extra size:  1.25 KiB\n'
            '\n')

    def test_patch_info_foo_in_place_no_human(self):
        argv = [
            'detools',
            'patch_info',
            '--no-human',
            'tests/files/foo/in-place-3000-1500.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(
            stdout.getvalue(),
            'Type:               in-place\n'
            'Patch size:         1967 bytes\n'
            'Memory size:        3000 bytes\n'
            'Segment size:       1500 bytes\n'
            'From shift size:    3000 bytes\n'
            'From size:          2780 bytes\n'
            'To size:            2780 bytes\n'
            'Patch/to ratio:     70.8 % (lower is better)\n'
            'Number of segments: 2\n'
            'Compression:        lzma\n'
            '\n'
            '------------------- Segment 1 -------------------\n'
            '\n'
            'From range:         0 bytes - 0 bytes\n'
            'To range:           0 bytes - 1500 bytes\n'
            'Diff/extra ratio:   0.0 % (higher is better)\n'
            'Size/data ratio:    0.3 % (lower is better)\n'
            'Data format size:   0 bytes\n'
            '\n'
            'Number of diffs:    1\n'
            'Total diff size:    0 bytes\n'
            'Average diff size:  0 bytes\n'
            'Median diff size:   0 bytes\n'
            '\n'
            'Number of extras:   1\n'
            'Total extra size:   1500 bytes\n'
            'Average extra size: 1500 bytes\n'
            'Median extra size:  1500 bytes\n'
            '\n'
            '------------------- Segment 2 -------------------\n'
            '\n'
            'From range:         0 bytes - 0 bytes\n'
            'To range:           1500 bytes - 2780 bytes\n'
            'Diff/extra ratio:   0.0 % (higher is better)\n'
            'Size/data ratio:    0.3 % (lower is better)\n'
            'Data format size:   0 bytes\n'
            '\n'
            'Number of diffs:    1\n'
            'Total diff size:    0 bytes\n'
            'Average diff size:  0 bytes\n'
            'Median diff size:   0 bytes\n'
            '\n'
            'Number of extras:   1\n'
            'Total extra size:   1280 bytes\n'
            'Average extra size: 1280 bytes\n'
            'Median extra size:  1280 bytes\n'
            '\n')

    def test_create_patch_foo_in_place_size_units(self):
        foo_patch = 'foo-in-place-3k-1.5k.patch'
        argv = [
            'detools',
            'create_patch_in_place',
            '--memory-size', '3k',
            '--segment-size', '1.5k',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        if os.path.exists(foo_patch):
            os.remove(foo_patch)

        with patch('sys.argv', argv):
            detools._main()

        self.assertEqual(read_file(foo_patch),
                         read_file('tests/files/foo/in-place-3k-1.5k.patch'))

    def test_apply_patch_foo_in_place_size_units(self):
        foo_mem = 'foo.mem'
        argv = [
            'detools',
            '--debug',
            'apply_patch_in_place',
            foo_mem,
            'tests/files/foo/in-place-3k-1.5k.patch'
        ]

        with open(foo_mem, 'wb') as fmem:
            with open('tests/files/foo/old', 'rb') as fold:
                fmem.write(fold.read() + (3072 - 2780) * b'\xff')

        with patch('sys.argv', argv):
            detools._main()

        self.assertEqual(
            read_file(foo_mem),
            read_file('tests/files/foo/new') + (3072 - 2780) * b'\xff')

    def test_patch_info_foo_in_place_size_units(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/foo/in-place-3k-1.5k.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(
            stdout.getvalue(),
            'Type:               in-place\n'
            'Patch size:         1.92 KiB\n'
            'Memory size:        3 KiB\n'
            'Segment size:       1.5 KiB\n'
            'From shift size:    3 KiB\n'
            'From size:          2.71 KiB\n'
            'To size:            2.71 KiB\n'
            'Patch/to ratio:     70.6 % (lower is better)\n'
            'Number of segments: 2\n'
            'Compression:        lzma\n'
            '\n'
            '------------------- Segment 1 -------------------\n'
            '\n'
            'From range:         0 bytes - 0 bytes\n'
            'To range:           0 bytes - 1.5 KiB\n'
            'Diff/extra ratio:   0.0 % (higher is better)\n'
            'Size/data ratio:    0.3 % (lower is better)\n'
            'Data format size:   0 bytes\n'
            '\n'
            'Number of diffs:    1\n'
            'Total diff size:    0 bytes\n'
            'Average diff size:  0 bytes\n'
            'Median diff size:   0 bytes\n'
            '\n'
            'Number of extras:   1\n'
            'Total extra size:   1.5 KiB\n'
            'Average extra size: 1.5 KiB\n'
            'Median extra size:  1.5 KiB\n'
            '\n'
            '------------------- Segment 2 -------------------\n'
            '\n'
            'From range:         0 bytes - 0 bytes\n'
            'To range:           1.5 KiB - 2.71 KiB\n'
            'Diff/extra ratio:   0.0 % (higher is better)\n'
            'Size/data ratio:    0.3 % (lower is better)\n'
            'Data format size:   0 bytes\n'
            '\n'
            'Number of diffs:    1\n'
            'Total diff size:    0 bytes\n'
            'Average diff size:  0 bytes\n'
            'Median diff size:   0 bytes\n'
            '\n'
            'Number of extras:   1\n'
            'Total extra size:   1.21 KiB\n'
            'Average extra size: 1.21 KiB\n'
            'Median extra size:  1.21 KiB\n'
            '\n')

    def test_patch_info_empty(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/empty/patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(
            stdout.getvalue(),
            'Type:               sequential\n'
            'Patch size:         2 bytes\n'
            'To size:            0 bytes\n'
            'Patch/to ratio:     inf % (lower is better)\n'
            'Diff/extra ratio:   inf % (higher is better)\n'
            'Size/data ratio:    inf % (lower is better)\n'
            'Compression:        lzma\n'
            'Data format size:   0 bytes\n'
            '\n'
            'Number of diffs:    0\n'
            'Total diff size:    0 bytes\n'
            'Average diff size:  -\n'
            'Median diff size:   -\n'
            '\n'
            'Number of extras:   0\n'
            'Total extra size:   0 bytes\n'
            'Average extra size: -\n'
            'Median extra size:  -\n')

    def test_patch_info_empty_in_place(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/empty/in-place.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(
            stdout.getvalue(),
            'Type:               in-place\n'
            'Patch size:         11 bytes\n'
            'Memory size:        29.3 KiB\n'
            'Segment size:       500 bytes\n'
            'From shift size:    29.3 KiB\n'
            'From size:          0 bytes\n'
            'To size:            0 bytes\n'
            'Patch/to ratio:     inf % (lower is better)\n'
            'Number of segments: 0\n'
            'Compression:        lzma\n'
            '\n')

    def test_patch_info_shell(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/shell/patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(
            stdout.getvalue(),
            'Type:               sequential\n'
            'Patch size:         1.7 KiB\n'
            'To size:            138.48 KiB\n'
            'Patch/to ratio:     1.2 % (lower is better)\n'
            'Diff/extra ratio:   138919.6 % (higher is better)\n'
            'Size/data ratio:    0.0 % (lower is better)\n'
            'Compression:        lzma\n'
            'Data format size:   0 bytes\n'
            '\n'
            'Number of diffs:    12\n'
            'Total diff size:    138.38 KiB\n'
            'Average diff size:  11.53 KiB\n'
            'Median diff size:   176 bytes\n'
            '\n'
            'Number of extras:   12\n'
            'Total extra size:   102 bytes\n'
            'Average extra size: 8 bytes\n'
            'Median extra size:  0 bytes\n')

    def test_patch_info_shell_arm_cortex_m4(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/shell/arm-cortex-m4.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(
            stdout.getvalue(),
            'Type:               sequential\n'
            'Patch size:         925 bytes\n'
            'To size:            138.48 KiB\n'
            'Patch/to ratio:     0.7 % (lower is better)\n'
            'Diff/extra ratio:   144593.9 % (higher is better)\n'
            'Size/data ratio:    0.0 % (lower is better)\n'
            'Compression:        lzma\n'
            'Data format size:   2.78 KiB\n'
            'Data format:        arm-cortex-m4\n'
            '\n'
            'Number of diffs:    12\n'
            'Total diff size:    138.38 KiB\n'
            'Average diff size:  11.53 KiB\n'
            'Median diff size:   178 bytes\n'
            '\n'
            'Number of extras:   12\n'
            'Total extra size:   98 bytes\n'
            'Average extra size: 8 bytes\n'
            'Median extra size:  0 bytes\n')

    def test_patch_info_shell_bz2(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/shell/bz2.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(
            stdout.getvalue(),
            'Type:               sequential\n'
            'Patch size:         1.55 KiB\n'
            'To size:            138.48 KiB\n'
            'Patch/to ratio:     1.1 % (lower is better)\n'
            'Diff/extra ratio:   138919.6 % (higher is better)\n'
            'Size/data ratio:    0.0 % (lower is better)\n'
            'Compression:        bz2\n'
            'Data format size:   0 bytes\n'
            '\n'
            'Number of diffs:    12\n'
            'Total diff size:    138.38 KiB\n'
            'Average diff size:  11.53 KiB\n'
            'Median diff size:   176 bytes\n'
            '\n'
            'Number of extras:   12\n'
            'Total extra size:   102 bytes\n'
            'Average extra size: 8 bytes\n'
            'Median extra size:  0 bytes\n')

    def test_create_patch_pybv11_arm_cortex_m4(self):
        pybv11_patch = 'pybv11-aarch64.patch'
        argv = [
            'detools',
            'create_patch',
            '--data-format', 'arm-cortex-m4',
            'tests/files/pybv11/1f5d945af/firmware1.bin',
            'tests/files/pybv11/1f5d945af-dirty/firmware1.bin',
            pybv11_patch
        ]

        if os.path.exists(pybv11_patch):
            os.remove(pybv11_patch)

        with patch('sys.argv', argv):
            detools._main()

        self.assertEqual(
            read_file(pybv11_patch),
            read_file('tests/files/pybv11/1f5d945af--1f5d945af-dirty-'
                      'arm-cortex-m4.patch'))

    def test_create_patch_pybv11_data_sections(self):
        pybv11_patch = 'pybv11-data-format-with-data-sections.patch'
        argv = [
            'detools',
            'create_patch',
            '--data-format', 'arm-cortex-m4',
            '--from-data-offsets', '0x36f7c-0x4e1f0',
            '--from-code-addresses', '0x8020000-0x08056deb',
            '--from-data-addresses', '0x8056f7c-0x806e1f0',
            '--to-data-offsets', '0x36f54-0x4e1d4',
            '--to-code-addresses', '0x8020000-0x08056dc3',
            '--to-data-addresses', '0x8056f54-0x806e1d4',
            'tests/files/pybv11/1f5d945af/firmware1.bin',
            'tests/files/pybv11/1f5d945af-dirty/firmware1.bin',
            pybv11_patch
        ]

        if os.path.exists(pybv11_patch):
            os.remove(pybv11_patch)

        with patch('sys.argv', argv):
            detools._main()

        self.assertEqual(
            read_file(pybv11_patch),
            read_file('tests/files/pybv11/1f5d945af--1f5d945af-dirty-'
                      'arm-cortex-m4-data-sections.patch'))

    def test_create_patch_pybv11_elf_data_sections(self):
        pybv11_patch = 'pybv11-data-format-with-elf-data-sections.patch'
        argv = [
            'detools',
            'create_patch',
            '--data-format', 'arm-cortex-m4',
            '--from-elf-file', 'tests/files/pybv11/1f5d945af/firmware.elf',
            '--to-elf-file', 'tests/files/pybv11/1f5d945af-dirty/firmware.elf',
            'tests/files/pybv11/1f5d945af/firmware1.bin',
            'tests/files/pybv11/1f5d945af-dirty/firmware1.bin',
            pybv11_patch
        ]

        self.execute_and_assert(argv,
                                pybv11_patch,
                                'tests/files/pybv11/1f5d945af--1f5d945af-dirty-'
                                'arm-cortex-m4-elf-data-sections.patch')

    def test_create_patch_pybv11_swapped_elfs_error(self):
        argv = [
            'detools',
            'create_patch',
            '--data-format', 'arm-cortex-m4',
            '--from-elf-file', 'tests/files/pybv11/1f5d945af-dirty/firmware.elf',
            '--to-elf-file', 'tests/files/pybv11/1f5d945af/firmware.elf',
            'tests/files/pybv11/1f5d945af/firmware1.bin',
            'tests/files/pybv11/1f5d945af-dirty/firmware1.bin',
            'none.patch'
        ]

        with patch('sys.argv', argv):
            with self.assertRaises(SystemExit) as cm:
                detools._main()

            self.assertEqual(
                str(cm.exception),
                "error: Failed to calculate ELF offset. Use --from-elf-offset "
                "to manually give the offset. Data segment 0x8056f54-0x806e1d4 "
                "(data: 00000000000000000a00000012050000...) not found in "
                "'tests/files/pybv11/1f5d945af/firmware1.bin'.")

    def test_create_patch_pybv11_elf_data_sections_offsets(self):
        pybv11_patch = 'pybv11-data-format-with-elf-data-sections-offsets.patch'
        argv = [
            'detools',
            'create_patch',
            '--data-format', 'arm-cortex-m4',
            '--from-elf-file', 'tests/files/pybv11/1f5d945af/firmware.elf',
            '--to-elf-file', 'tests/files/pybv11/1f5d945af-dirty/firmware.elf',
            '--from-elf-offset', '0x20000',
            '--to-elf-offset', '0x20000',
            'tests/files/pybv11/1f5d945af/firmware1.bin',
            'tests/files/pybv11/1f5d945af-dirty/firmware1.bin',
            pybv11_patch
        ]

        self.execute_and_assert(argv,
                                pybv11_patch,
                                'tests/files/pybv11/1f5d945af--1f5d945af-dirty-'
                                'arm-cortex-m4-elf-data-sections.patch')

    def test_apply_patch_pybv11_elf_data_sections(self):
        pybv11_new = 'pybv11-elf-data-sections.new'
        argv = [
            'detools',
            '--debug',
            'apply_patch',
            'tests/files/pybv11/1f5d945af/firmware1.bin',
            'tests/files/pybv11/1f5d945af--1f5d945af-dirty-'
            'arm-cortex-m4-elf-data-sections.patch',
            pybv11_new
        ]

        self.execute_and_assert(argv,
                                pybv11_new,
                                'tests/files/pybv11/1f5d945af-dirty/firmware1.bin')

    def test_parse_range_errors(self):
        with self.assertRaises(detools.Error) as cm:
            detools.parse_range('--option', '')

        self.assertEqual(
            str(cm.exception),
            "--option: Expected a range on the form <integer>-<integer>, but "
            "got ''.")

        with self.assertRaises(detools.Error) as cm:
            detools.parse_range('--option', '-1-3')

        self.assertEqual(
            str(cm.exception),
            "--option: Expected a range on the form <integer>-<integer>, but "
            "got '-1-3'.")

        with self.assertRaises(detools.Error) as cm:
            detools.parse_range('--option', '2-1')

        self.assertEqual(
            str(cm.exception),
            "--option: End value 1 is less than begin value 2.")

        with self.assertRaises(detools.Error) as cm:
            detools.parse_range('--option', '1-b')

        self.assertEqual(
            str(cm.exception),
            "--option: Expected an integer, but got 'b'.")

        with self.assertRaises(detools.Error) as cm:
            detools.parse_range('--option', 'a-1')

        self.assertEqual(
            str(cm.exception),
            "--option: Expected an integer, but got 'a'.")

    def test_patch_info_pybv11_data_sections_detailed(self):
        argv = [
            'detools',
            'patch_info',
            '--detailed',
            'tests/files/pybv11/1f5d945af--1f5d945af-dirty-'
            'arm-cortex-m4-data-sections.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(
            stdout.getvalue(),
            'Type:               sequential\n'
            'Patch size:         3 KiB\n'
            'To size:            312.49 KiB\n'
            'Patch/to ratio:     1.0 % (lower is better)\n'
            'Diff/extra ratio:   84329.6 % (higher is better)\n'
            'Size/data ratio:    0.0 % (lower is better)\n'
            'Compression:        lzma\n'
            'Data format size:   15.66 KiB\n'
            'Data format:        arm-cortex-m4\n'
            '\n'
            'Number of diffs:    31\n'
            'Total diff size:    312.12 KiB\n'
            'Average diff size:  10.07 KiB\n'
            'Median diff size:   74 bytes\n'
            '\n'
            'Number of extras:   31\n'
            'Total extra size:   379 bytes\n'
            'Average extra size: 12 bytes\n'
            'Median extra size:  6 bytes\n'
            '\n'
            'Data format details:\n'
            '\n'
            'Instruction:        b.w\n'
            'Number of blocks:   2\n'
            'Size:               602 bytes\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        608\n'
            'To address:         0x17bca\n'
            'Number of values:   13\n'
            'Values:\n'
            '  0 0 0 352 640 672 0 736 448 448 640 640 672\n'
            '\n'
            '------------------- Block 2 -------------------\n'
            '\n'
            'From offset:        663\n'
            'To address:         0x18ba4\n'
            'Number of values:   514\n'
            'Values:\n'
            '  0 0 -640 -640 -640 -640 -640 -640 -640 -640 -640 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 -640 -640 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 -640 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -640 -640 0 -640 0 0 -640\n'
            '  -640 -640 -640 -640 -640 -640 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 -640 -640 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -640\n'
            '  -640 -640 -640 -640 0 0 0 0 0 0 0 0 0 0 0 0 -640 0 0 -640 -640 0 -640\n'
            '  0 0 0 -640 0 -640 -640 -640 0 0 -640 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 -640 -640 0 0 0 0 0 0 0 0 0 0 0 0 0 -640 0 0 0 0 0 0 0 -640 0\n'
            '  0 0 -640 0 0 0 0 0 0 0 0 -640 -640 0 0 -640 0 0 -640 -640 -640 0 -640\n'
            '  -640 0 -640 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -640 0 0 0 0 0\n'
            '  0 0 -640 0 0 0 0 -640 -640 -640 -640 0 -640 0 -640 -640 -640 0 -640\n'
            '  -640 -640 -640 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '\n'
            'Instruction:        bl\n'
            'Number of blocks:   5\n'
            'Size:               6.39 KiB\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        0\n'
            'To address:         0x4c\n'
            'Number of values:   3314\n'
            'Values:\n'
            '  20 0 0 0 0 0 0 0 0 20 20 0 0 0 0 0 0 0 0 0 0 0 0 0 20 20 20 0 0 0 0 20\n'
            '  0 0 20 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 20 0 0 20 0 0 0 0 0 0 0 0 20\n'
            '  0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 20 0 0 0 0 0 0 0 20 0 0 0\n'
            '  0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 20 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 20 0 0 0\n'
            '  0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 20 0 0 0 0\n'
            '  20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 20 0 0 20 0 0 0 0 0 0 0 0 0 20 20 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0\n'
            '  0 0 0 0 0 20 20 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 20 0 0 20 20 0 20 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20\n'
            '  0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 20 0 20 0\n'
            '  20 20 0 0 20 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 20 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 20 0 0 20 0 0 0 0 0 0 0 0 20 20 20 20 20 0 0 0 20 0 0 0 0 0 0\n'
            '  0 20 20 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 20 20 0 0 20 20 0 0 0 20 0\n'
            '  0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 20 0 20 20 20 20 20 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 20 0 0 0 0 0 0 20 0 0 0 20 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 20 20 0 20 20 0 0 0 0 0 0 0 0\n'
            '  0 20 20 0 20 0 0 0 0 0 0 0 0 0 0 0 20 20 20 0 20 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 20 20 20 0 0 0 20 0 0 20 20 20 0 20 20 0 20 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 20 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0\n'
            '  0 0 0 0 0 0 0 20 20 0 0 0 0 0 20 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0\n'
            '  0 0 0 20 20 20 20 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 20 20 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 20 0 20 0 0 0 0 20 20 0 0 0 0 0 0 0 0 0 0 20 0 20 20 20\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 20 0 20 20 0 0 0 0 0 20 0 0 0 20 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 20 20 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 20 20 0\n'
            '  0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 20 20 0 0 0 0 0 0 0 0 0 20 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 20 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20\n'
            '  0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 20\n'
            '  0 20 0 0 0 0 0 20 0 0 0 20 0 0 0 20 0 20 0 0 20 0 0 20 0 0 0 0 0 0 20\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 20 0 0 0 0 20 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 20 20 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 20 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0 20\n'
            '  0 0 20 0 0 0 0 0 20 0 20 0 0 0 0 20 0 20 0 0 0 0 0 0 0 0 0 20 0 0 20 0\n'
            '  20 20 20 20 0 0 20 20 20 20 0 0 20 20 20 20 0 0 20 20 0 0 20 20 0 0 20\n'
            '  20 20 0 0 0 20 20 0 20 0 0 20 0 20 0 0 0 0 0 0 0 0 20 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 20 0 0 0 20 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0\n'
            '\n'
            '------------------- Block 2 -------------------\n'
            '\n'
            'From offset:        3314\n'
            'To address:         0x17ba6\n'
            'Number of values:   13\n'
            'Values:\n'
            '  18 -2 -2 -2 -2 18 18 18 18 -2 -2 -2 -2\n'
            '\n'
            '------------------- Block 3 -------------------\n'
            '\n'
            'From offset:        3335\n'
            'To address:         0x17fec\n'
            'Number of values:   13\n'
            'Values:\n'
            '  -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4\n'
            '\n'
            '------------------- Block 4 -------------------\n'
            '\n'
            'From offset:        3396\n'
            'To address:         0x18a6a\n'
            'Number of values:   1366\n'
            'Values:\n'
            '  0 0 0 0 -20 -20 -20 -20 -20 -20 -20 -20 -20 0 -20 0 -20 0 0 0 0 0 0 0\n'
            '  0 -20 -20 -20 -20 -20 0 -20 0 -20 0 -20 -20 -20 -20 -20 0 0 0 0 0 -20\n'
            '  -20 -20 -20 -20 -20 0 -20 -20 -20 -20 -20 0 -20 -20 -20 0 0 0 -20 -20\n'
            '  -20 0 -20 -20 -20 0 -20 -20 0 -20 0 0 -20 -20 0 0 -20 -20 -20 -20 -20\n'
            '  -20 -20 -20 0 -20 -20 0 0 -20 -20 -20 0 0 0 0 0 0 0 0 0 0 0 0 0 -20 0\n'
            '  0 -20 -20 -20 0 -20 -20 -20 -20 -20 -20 -20 0 -20 0 -20 -20 -20 -20\n'
            '  -20 -20 -20 -20 0 -20 -20 -20 -20 -20 0 0 0 0 -20 -20 -20 -20 0 0 0 0\n'
            '  0 0 0 0 0 -20 0 -20 -20 -20 0 0 -20 0 0 0 0 0 -20 -20 0 0 -20 0 0 0 0\n'
            '  -20 -20 -20 -20 0 0 -20 -20 -20 -20 -20 -20 -20 0 0 -20 -20 -20 -20\n'
            '  -20 -20 -20 -20 -20 -20 -20 -20 0 -20 -20 -20 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -20 -20 -20\n'
            '  0 0 -20 0 -20 -20 0 0 0 0 0 0 0 -20 -20 0 -20 0 -20 0 -20 -20 -20 -20\n'
            '  -20 -20 -20 -20 0 0 0 -20 0 0 -20 -20 0 -20 -20 -20 0 -20 -20 -20 -20\n'
            '  -20 0 -20 0 0 -20 0 -20 -20 0 0 0 0 0 -20 0 -20 -20 -20 -20 -20 -20\n'
            '  -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 0 0 -20 0\n'
            '  0 0 -20 -20 0 -20 -20 -20 0 0 -20 0 -20 0 0 0 0 0 0 0 0 0 -20 -20 0 0\n'
            '  0 -20 -20 -20 -20 0 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20\n'
            '  -20 -20 -20 -20 -20 -20 0 -20 -20 -20 -20 -20 0 -20 -20 0 0 0 0 0 -20\n'
            '  0 0 0 0 0 0 0 -20 -20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -20 0\n'
            '  -20 -20 0 -20 0 -20 0 -20 -20 -20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -20\n'
            '  -20 -20 0 0 -20 -20 -20 0 0 -20 0 -20 -20 -20 0 0 -20 0 -20 0 0 0 0 0\n'
            '  0 -20 -20 0 -20 0 0 0 0 0 -20 -20 0 -20 -20 0 -20 -20 0 -20 0 -20 0\n'
            '  -20 -20 -20 -20 0 -20 -20 0 -20 -20 -20 0 -20 -20 -20 -20 -20 -20 -20\n'
            '  -20 -20 0 -20 -20 -20 -20 0 0 -20 -20 -20 0 0 -20 0 -20 0 -20 -20 -20\n'
            '  -20 -20 0 0 0 0 0 -20 -20 -20 0 0 -20 -20 -20 0 -20 0 -20 0 -20 -20\n'
            '  -20 -20 -20 -20 -20 -20 -20 -20 0 0 -20 -20 -20 0 -20 -20 -20 -20 -20\n'
            '  0 0 0 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 0 0 0 0 -20\n'
            '  -20 -20 -20 0 -20 -20 -20 -20 0 -20 -20 -20 -20 -20 0 -20 -20 0 -20\n'
            '  -20 -20 0 -20 -20 0 -20 -20 0 -20 0 0 -20 0 -20 -20 -20 -20 0 -20 -20\n'
            '  -20 0 -20 -20 -20 -20 0 -20 0 -20 -20 0 -20 0 -20 -20 0 0 0 0 0 -20\n'
            '  -20 0 0 -20 -20 -20 -20 0 -20 -20 0 0 0 0 0 0 -20 0 0 0 0 -20 0 0 0\n'
            '  -20 0 -20 0 -20 -20 0 -20 -20 -20 -20 -20 -20 0 -20 0 -20 -20 -20 -20\n'
            '  -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 0 -20 -20 -20 0 -20 -20 -20\n'
            '  -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 0 -20 0 -20 -20 -20 -20\n'
            '  -20 -20 -20 -20 -20 -20 -20 -20 0 -20 -20 -20 -20 -20 -20 -20 -20 -20\n'
            '  -20 0 -20 -20 -20 0 -20 0 -20 -20 0 0 0 0 -20 -20 -20 -20 -20 -20 -20\n'
            '  -20 0 -20 -20 -20 -20 -20 0 0 0 -20 -20 -20 0 0 -20 0 0 0 0 -20 0 -20\n'
            '  0 0 0 0 0 0 -20 0 -20 -20 0 -20 0 -20 0 0 0 -20 -20 -20 -20 -20 -20 0\n'
            '  0 0 0 0 0 0 0 0 -20 0 -20 -20 -20 -20 -20 0 -20 0 0 0 0 0 0 -20 -20\n'
            '  -20 -20 -20 -20 0 0 -20 0 -20 0 0 0 -20 -20 0 0 -20 0 0 -20 0 -20 -20\n'
            '  0 0 0 0 -20 -20 0 0 -20 0 -20 0 0 0 0 0 0 -20 0 0 -20 0 0 0 0 -20 0 0\n'
            '  -20 0 -20 0 0 -20 0 0 0 0 -20 -20 -20 -20 -20 -20 -20 0 -20 -20 -20\n'
            '  -20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -20 0\n'
            '  0 0 0 -20 0 0 -20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -20\n'
            '  -20 0 0 0 0 0 0 0 0 -20 -20 0 -20 0 0 -20 -20 -20 -20 -20 -20 -20 -20\n'
            '  -20 -20 -20 0 0 0 -20 -20 0 0 -20 -20 -20 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 -20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 -20 -20 -20 -20 -20 -20 -20 0 0 0 0 0 0 0 0 0 -20 0 -20 -20 -20\n'
            '  -20 -20 0 -20 -20 -20 -20 0 0 0 0 0 0 0 0 0 0 -20 0 0 0 0 0 0 0 0 0\n'
            '  -20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 -20 0 0 -20 0 0 0 0 0 0 0 0 0 -20 -20 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 -20 0 0 0 0 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20\n'
            '  -20 -20 0 0 -20 -20 -20 -20 0 0 -20 -20 -20 0 0 -20 -20 -20 0 -20 -20\n'
            '  0 -20 0 -20 -20 0 0 0 0 0 0\n'
            '\n'
            '------------------- Block 5 -------------------\n'
            '\n'
            'From offset:        4768\n'
            'To address:         0x24fa8\n'
            'Number of values:   1842\n'
            'Values:\n'
            '  0 0 0 0 0 0 0 0 0 0 0 -20 -20 -20 0 -20 -20 0 0 -20 0 0 0 0 0 -20 0\n'
            '  -20 -20 -20 0 0 0 0 -20 -20 -20 -20 -20 0 -20 0 0 -20 -20 -20 -20 -20\n'
            '  -20 0 0 0 0 0 0 0 0 -20 -20 -20 -20 0 0 0 0 0 0 0 0 -20 0 -20 -20 -20\n'
            '  -20 0 -20 0 0 0 0 -20 -20 -20 -20 -20 -20 0 -20 0 -20 -20 0 0 0 -20 0\n'
            '  -20 -20 -20 0 -20 0 -20 -20 -20 0 -20 0 -20 0 0 0 -20 0 -20 0 0 0 -20\n'
            '  0 -20 -20 -20 -20 0 -20 0 0 0 -20 -20 -20 -20 -20 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -20 -20 0 -20 -20 -20 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 -20 -20 0 0 0 0 0 0 0 0 -20 -20 0 0 0 0 0 0 0 0 -20\n'
            '  -20 0 0 -20 0 0 0 0 0 0 0 0 -20 -20 0 0 0 -20 0 0 0 0 0 0 0 0 0 -20 0\n'
            '  0 -20 -20 0 0 -20 -20 -20 -20 0 0 -20 0 0 -20 -20 -20 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -20 0 0 -20 -20 -20 -20\n'
            '  -20 -20 -20 0 0 0 -20 -20 0 -20 -20 -20 0 -20 -20 0 0 -20 0 -20 0 -20\n'
            '  0 -20 0 -20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -20 0 0 -20 0 0 0 0\n'
            '  -20 0 -20 0 -20 0 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20\n'
            '  -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20\n'
            '  -20 -20 -20 -20 -20 0 -20 -20 0 -20 0 -20 -20 -20 -20 -20 0 -20 0 -20\n'
            '  0 0 0 -20 -20 -20 0 0 0 0 0 0 0 -20 -20 -20 0 -20 0 0 0 0 -20 -20 -20\n'
            '  -20 0 0 -20 -20 -20 -20 0 -20 0 0 -20 -20 -20 -20 -20 0 0 -20 -20 -20\n'
            '  0 -20 -20 0 -20 0 0 -20 -20 -20 0 0 -20 0 0 0 -20 -20 -20 -20 -20 -20\n'
            '  -20 -20 0 -20 -20 0 0 -20 -20 0 0 0 0 0 0 0 0 0 0 0 0 -20 0 -20 0 0 0\n'
            '  0 0 0 0 -20 -20 -20 -20 -20 -20 -20 0 -20 -20 -20 -20 -20 0 -20 -20\n'
            '  -20 -20 -20 0 0 -20 -20 -20 -20 0 0 -20 0 0 -20 0 -20 0 0 0 0 0 0 0 0\n'
            '  -20 0 0 -20 -20 0 -20 -20 -20 -20 0 0 0 0 -20 -20 -20 0 -20 -20 0 0\n'
            '  -20 -20 -20 -20 0 0 0 0 -20 0 -20 -20 -20 -20 0 0 -20 -20 -20 -20 -20\n'
            '  -20 -20 -20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -20 0 -20 0 0\n'
            '  0 0 0 -20 0 -20 -20 -20 0 0 0 0 0 0 0 0 0 0 -20 0 -20 0 -20 0 -20 -20\n'
            '  -20 -20 -20 -20 0 -20 0 -20 0 -20 0 -20 0 -20 0 -20 -20 -20 0 -20 0\n'
            '  -20 0 -20 0 -20 -20 0 -20 -20 0 0 0 -20 -20 -20 -20 -20 -20 -20 0 -20\n'
            '  0 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20\n'
            '  -20 0 -20 0 0 0 0 -20 -20 -20 -20 -20 -20 0 -20 -20 -20 -20 -20 -20 0\n'
            '  -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 0 -20 -20 -20 -20 -20\n'
            '  -20 -20 -20 -20 -20 -20 0 -20 -20 -20 -20 -20 -20 0 -20 -20 -20 0 0\n'
            '  -20 -20 0 0 -20 0 0 -20 -20 -20 0 0 0 0 0 0 0 0 0 -20 -20 -20 0 -20 0\n'
            '  0 0 0 0 0 -20 -20 0 -20 -20 0 0 0 0 -20 -20 -20 -20 -20 -20 0 0 -20\n'
            '  -20 -20 -20 0 -20 -20 0 0 0 0 0 -20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 0\n'
            '  -20 -20 -20 0 0 0 -20 -20 -20 0 -20 0 -20 0 0 -20 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 -20 0 0 -20 0 0 0 0 0 0 -20 -20 0 0 0 -20 -20 0\n'
            '  -20 -20 -20 -20 -20 0 0 0 0 0 0 0 0 0 0 0 0 -20 -20 0 -20 -20 0 -20\n'
            '  -20 -20 -20 0 0 -20 0 0 0 0 0 0 -20 -20 0 -20 -20 0 -20 -20 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 -20 0 0 0 -20 0 0 0 0 0 0 -20 -20 -20 -20 -20\n'
            '  -20 -20 -20 0 0 -20 -20 -20 0 0 0 0 0 0 -20 0 0 0 0 -20 0 0 -20 0 0\n'
            '  -20 -20 -20 0 -20 -20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 -20 -20 0 -20 0 0 -20 0 0 -20 0 0 -20 0 0 0 -20 -20 -20 0 0 0 0 -20\n'
            '  0 0 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20 -20\n'
            '  -20 -20 -20 -20 -20 0 0 0 0 -20 -20 0 -20 -20 0 -20 0 0 0 0 -20 -20\n'
            '  -20 0 0 0 -20 0 0 0 0 0 0 -20 0 0 0 0 0 0 -20 0 0 -20 0 0 0 0 0 -20 0\n'
            '  0 0 0 0 -20 -20 -20 -20 0 -20 -20 0 -20 -20 0 0 -20 -20 0 0 -20 -20 0\n'
            '  -20 0 0 0 0 0 0 -20 0 0 0 -20 0 0 0 0 0 -20 0 -20 -20 -20 -20 -20 -20\n'
            '  0 0 0 0 0 0 -20 0 -20 -20 0 -20 -20 -20 0 0 0 0 -20 -20 0 0 -20 -20\n'
            '  -20 -20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0\n'
            '\n'
            'Instruction:        ldr\n'
            'Number of blocks:   3\n'
            'Size:               2.9 KiB\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        0\n'
            'To address:         0xc\n'
            'Number of values:   1173\n'
            'Values:\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 40 40 40 0 40 40 40 40 0 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 0 0 40 0 0 0 0 0 40 40 40 40 0 40 40 40 40\n'
            '  40 40 40 40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 40 0 40 0 40 0 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 0 0 0 0 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 0 0 0 0 0 0 0 0 0 40 0 0 40\n'
            '  40 40 40 40 40 40 40 40 40 0 0 0 0 40 0 40 40 40 0 40 40 40 40 40 40 0\n'
            '  0 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 0 40 40 0 40 40\n'
            '  40 0 0 40 0 0 0 0 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 0 40 40 0 0 0 0 0 0 40 40 40 40 40 40 0 0 0\n'
            '  0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 0 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 0\n'
            '  40 40 40 40 40 28 40 40 40 40 40 40 28 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 0 0 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 28 40 40 40 40 40 40 40 40 40 40 40 40 40 0 0 40 40 0 0 40\n'
            '  40 40 40 0 40 0 0 40 40 0 40 0 0 0 0 40 30 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 0 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 0 40 40 40 40 0 40 40 0\n'
            '  40 40 0 40 40 40 40 40 0 40 40 40 40 0 0 0 40 40 40 40 40 40 40 40 40\n'
            '  40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 0 40 40 40 40 0 0 40 0 40 40 40 0 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 0 0 0 0 0 0 0 40 40 40 40 0 40 40 28 40 40 40 40 40 40 0 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 28 40 40 40 40 40 40 40 40 40\n'
            '  40 40 0 40 40 40 40 40 40 0 40 40 28 40 40 40 40 40 0 40 40 40 40 0 0\n'
            '  40 0 0 0 0 0 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 0 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 0 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 0 40 40 40 40 40 28\n'
            '  40 40 40 40 40 0 0 40 40 0 40 40 40 40 40 40 0 40 40 40 0 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 0 0 0 0 0 0 0 0 0 40 40 0 40 40 40 40 40 40\n'
            '  40 40 40 40 0 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 0 40 40 0 40 40 0 40 0 40 40 40 40 0 40 40 40 0 40 40 40 40 36\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 0 0 0 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 0 0\n'
            '  40 0 40 40 40 40 40 0 40 0 40 0 40 40 40 0 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40 0 40\n'
            '  40 40 40 40 0 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 0\n'
            '  40 40 40 40 40 40 36 0 40 40\n'
            '\n'
            '------------------- Block 2 -------------------\n'
            '\n'
            'From offset:        1184\n'
            'To address:         0x18a34\n'
            'Number of values:   661\n'
            'Values:\n'
            '  -4388 14412 -13776 3912 40 40 40 40 40 40 40 40 40 40 40 40 40 40 36\n'
            '  40 40 0 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 0 40 40 40 0 40 0 0 0 0 0 0 0 0 40 40 40 40 0 0\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 0\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 0 40 0 40 40 40 40 40 40 0 0\n'
            '  0 0 -20 0 0 40 0 0 40 40 40 40 40 0 40 40 0 40 40 40 40 40 40 40 40 40\n'
            '  0 0 40 40 40 40 40 40 40 40 40 40 40 0 40 0 40 40 40 0 40 40 40 0 40\n'
            '  40 0 40 40 40 0 40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 0 40 0 40 0 40 0 40 0 40 0\n'
            '  40 40 40 0 0 0 0 0 0 0 40 40 40 40 0 40 40 40 0 0 0 0 0 34 40 0 40 40\n'
            '  40 40 40 0 0 0 40 0 0 0 0 40 40 40 0 40 40 0 40 40 40 34 0 40 0 40 34\n'
            '  34 34 34 0 34 34 34 0 0 0 40 36 36 40 40 36 40 40 0 0 0 0 0 0 0 0 0 0\n'
            '  36 0 0 0 0 36 36 0 0 0 0 0 0 0 0 0 0 0 0 0 0 36 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 36 36 0 0 0 0 36 36 0 0 0 0 0 0 0 0\n'
            '  0 36 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 40 40\n'
            '  40 40 0 40 40 40 0 36 40 0 0 36 36 36 36 36 36 36 36 36 40 0 36 36 0\n'
            '  36 36 40 40 0 0 0 0 0 0 0 0 0 0 36 36 0 40 36 36 0 0 0 36 0 0 40 36 36\n'
            '  0 0 40 36 34 0 0 0 0 36 36 36 36 36 36 36 36 36 36 36 36 36 36 0 0 36\n'
            '  0 0 40 34 36 36 36 36 0 0 0 0 0 0 0 0 28 28 28 28 0 0 0 0 36 36 36 36\n'
            '  0 0 0 0 0 0 36 36 40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 36 0 0 34 0 0 0 0\n'
            '  40 40 40 40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 36 28 0 0 0 0 0 40 36 40\n'
            '  -1310720 40 40 40 36 36 40 36 36 40 40 36 40 0 40 40 40\n'
            '\n'
            '------------------- Block 3 -------------------\n'
            '\n'
            'From offset:        1882\n'
            'To address:         0x251ec\n'
            'Number of values:   1122\n'
            'Values:\n'
            '  40 36 40 -20 36 40 36 36 36 36 40 0 0 0 0 40 0 36 36 40 0 36 40 36 40\n'
            '  40 36 0 36 40 36 40 36 28 36 36 0 36 36 36 0 0 0 36 36 40 36 36 0 36\n'
            '  40 40 0 36 40 0 36 36 36 0 40 0 40 0 40 40 40 36 0 0 36 40 36 40 36 28\n'
            '  36 40 36 36 36 36 36 28 36 0 40 40 40 40 0 40 0 0 36 36 0 36 36 36 36\n'
            '  28 36 28 36 36 40 0 40 40 0 0 36 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 36 0 36 0 0 0 40 0 0 0 0 0 0 0 36 36 40 40 0 0 0 36 36 36 0 0 0 0 0\n'
            '  28 28 0 28 28 36 36 0 0 0 0 0 36 36 40 36 36 40 36 36 40 36 36 40 40\n'
            '  36 0 40 0 36 40 40 40 36 36 40 0 0 0 0 0 0 0 0 0 40 40 40 36 36 36 40\n'
            '  0 0 0 28 28 28 28 0 0 28 28 28 28 36 0 36 0 0 0 0 36 0 36 36 36 36 36\n'
            '  36 28 36 40 36 36 40 36 40 40 36 40 0 36 28 28 0 0 28 28 28 28 0 28 28\n'
            '  28 28 0 0 28 28 0 0 0 0 0 40 40 0 0 40 0 40 36 0 36 40 40 36 40 40 40\n'
            '  40 40 36 36 0 0 0 40 40 0 0 0 0 40 36 36 40 36 0 28 28 28 28 40 36 40\n'
            '  0 40 36 36 36 36 40 0 36 40 0 0 0 36 40 0 40 40 36 40 36 40 40 36 40\n'
            '  36 40 40 36 36 0 36 0 36 36 36 40 0 0 0 36 28 0 0 36 36 0 0 36 0 40 36\n'
            '  40 40 40 40 40 40 36 0 0 0 40 36 36 40 36 36 0 36 0 0 36 36 36 36 40\n'
            '  40 40 36 36 40 36 36 36 36 36 36 40 40 36 36 40 36 36 40 40 36 36 40\n'
            '  36 36 36 40 0 40 36 36 36 36 36 36 40 0 36 36 36 40 30 40 36 40 36 40\n'
            '  36 36 28 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 36 36 28 36 28 36 0 36 0 36 0\n'
            '  36 0 36 0 36 0 36 0 36 0 36 0 36 40 36 36 36 36 0 40 36 40 0 0 40 0 40\n'
            '  40 36 36 40 0 0 0 0 0 40 0 40 36 36 36 0 40 40 36 36 40 36 36 40 0 28\n'
            '  40 0 40 0 28 40 40 40 40 40 40 40 40 40 28 28 40 40 40 0 0 0 28 40 0\n'
            '  28 28 28 28 28 28 40 28 0 40 40 0 40 0 0 0 40 28 28 40 0 0 28 28 0 40\n'
            '  28 0 0 0 28 28 0 0 28 28 40 0 0 0 0 28 0 40 0 0 0 40 0 0 28 40 28 28 0\n'
            '  40 28 28 0 0 40 28 28 40 40 40 40 0 0 0 28 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 40 0 40 40 0 0 0 0 28 0 28 40 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 28 0 0 40 0 40 40 40 28 28 40 28 28 0 28 0 0 40 0 0 0 36 0\n'
            '  40 40 28 40 0 0 36 0 40 40 28 40 28 40 40 0 28 28 28 28 28 28 28 0 0 0\n'
            '  28 40 40 0 0 0 0 0 40 40 0 0 0 0 0 40 40 28 28 40 28 28 0 28 40 40 40\n'
            '  40 40 40 40 40 28 36 28 28 28 28 36 28 28 28 28 0 28 40 0 0 40 0 0 0 0\n'
            '  0 28 28 28 0 0 28 28 40 28 28 0 40 0 40 28 40 40 28 40 0 28 0 0 0 0 28\n'
            '  0 0 28 28 28 28 0 0 40 40 40 28 40 40 0 28 0 0 0 40 0 40 0 40 0 40 28\n'
            '  0 0 40 28 0 40 28 28 28 28 36 36 28 40 28 0 40 0 0 40 40 0 28 28 0 0 0\n'
            '  28 28 28 0 40 40 40 28 28 40 28 28 28 0 40 28 0 0 28 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 28 28 28 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  40 40 40 40 40 40 0 0 0 28 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 40 40 0 0 40 40 0 0 40 40 0 0 40 40 0 0\n'
            '  0 0 0 0 0 40 40 0 40 40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 28 0 0 0 28 0 0 28 0 0 0 0 0 0 0 0 0 40 40 40\n'
            '  40 40 40 40 40 40 40 40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 40 40 0 40\n'
            '  40 0 0 40 40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 28 28 28 28 0\n'
            '  0 28 28 28 0 0 0 0 0 0 0 0 40 40 40 40\n'
            '\n'
            'Instruction:        ldr.w\n'
            'Number of blocks:   2\n'
            'Size:               52 bytes\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        0\n'
            'To address:         0x474\n'
            'Number of values:   23\n'
            'Values:\n'
            '  0 0 40 40 40 40 40 40 40 40 40 40 40 0 40 40 40 40 40 0 40 40 40\n'
            '\n'
            '------------------- Block 2 -------------------\n'
            '\n'
            'From offset:        25\n'
            'To address:         0x19134\n'
            'Number of values:   29\n'
            'Values:\n'
            '  40 40 40 40 40 40 0 40 36 0 0 40 40 0 0 0 0 40 40 28 28 28 0 28 0 0 0\n'
            '  0 0\n'
            '\n'
            'Kind:               data-pointers\n'
            'From data offset:   0x36f7c\n'
            'From data begin:    0x8056f7c\n'
            'From data end:      0x806e1f0\n'
            'Number of blocks:   3\n'
            'Size:               4.19 KiB\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        0\n'
            'To address:         0x36f6c\n'
            'Number of values:   3018\n'
            'Values:\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 36 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 36 36 36 36 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 36 36 36 28 28 28 28 36 40 40 40 40 40 40 40 40 40 40 28 40 28 40\n'
            '  28 40 36 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 36 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 36 36 36 40 40 40 40 40 40 36 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40\n'
            '\n'
            '------------------- Block 2 -------------------\n'
            '\n'
            'From offset:        3018\n'
            'To address:         0x46ccc\n'
            'Number of values:   686\n'
            'Values:\n'
            '  40 36 40 40 40 40 40 40 40 40 36 40 36 36 40 36 40 36 36 40 36 36 36\n'
            '  36 40 40 40 40 36 36 36 40 36 40 40 36 40 36 36 36 36 36 36 40 40 40\n'
            '  36 40 40 40 40 36 36 40 40 40 40 36 40 36 36 36 36 36 36 36 36 36 36\n'
            '  36 36 36 36 40 40 40 40 40 36 40 40 36 40 36 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 36 40 36 36 28 36 28 36 28 36 28 40 40 40 40 36 36 36 36\n'
            '  40 40 40 40 40 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36\n'
            '  36 36 36 40 40 40 36 40 40 40 40 40 40 36 36 40 40 40 36 40 36 40 40\n'
            '  40 36 40 40 40 40 40 36 36 36 36 40 40 40 36 40 28 40 28 36 36 36 36\n'
            '  36 36 36 36 36 36 36 40 40 36 40 36 36 36 36 36 36 36 36 40 36 36 36\n'
            '  36 36 36 36 36 36 40 40 40 40 40 40 36 36 36 36 36 36 40 40 40 40 36\n'
            '  36 36 40 40 36 40 40 36 36 40 40 40 36 36 36 36 36 36 36 36 36 36 36\n'
            '  36 40 40 40 36 36 40 40 40 40 40 36 40 36 36 36 36 36 36 36 36 36 36\n'
            '  36 36 40 36 40 40 40 40 40 40 40 40 40 36 40 36 36 40 40 36 40 36 40\n'
            '  28 40 40 36 36 40 40 36 40 40 36 36 36 36 36 36 36 36 40 40 40 40 40\n'
            '  40 40 40 36 40 40 28 40 40 36 40 40 40 36 36 40 40 36 36 40 36 40 36\n'
            '  36 28 28 36 28 28 40 36 40 36 36 36 36 36 36 36 36 36 36 36 36 40 36\n'
            '  40 36 36 36 40 40 40 40 36 36 36 36 40 36 40 40 40 40 40 40 40 36 36\n'
            '  40 40 40 40 40 36 40 40 36 36 36 36 36 36 28 36 36 36 36 36 36 36 40\n'
            '  40 40 40 36 40 40 36 36 36 40 40 40 40 40 36 40 36 36 36 36 36 36 36\n'
            '  36 36 36 36 36 36 36 36 36 36 36 36 36 36 40 36 40 36 40 40 36 40 36\n'
            '  36 28 28 36 28 28 28 28 28 28 28 28 36 36 36 36 36 28 28 28 28 28 40\n'
            '  40 36 40 40 40 36 40 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36\n'
            '  40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 40 40 36 36 36 36\n'
            '  36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36\n'
            '  36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36 36\n'
            '  36 36 36 36 36 36 36 36 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36\n'
            '  40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40\n'
            '  36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36\n'
            '  40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40 36 40\n'
            '  36 40 36 40 36 40 40 40 36 40 28 36 36 28 36 36 40 30 40\n'
            '\n'
            '------------------- Block 3 -------------------\n'
            '\n'
            'From offset:        3704\n'
            'To address:         0x4bd64\n'
            'Number of values:   583\n'
            'Values:\n'
            '  40 36 40 40 40 28 40 40 40 40 40 40 40 40 40 40 40 36 28 28 40 40 40\n'
            '  40 40 40 28 40 28 40 40 40 28 28 28 28 40 40 40 40 40 40 40 40 40 28\n'
            '  40 28 28 40 40 28 40 40 40 40 40 40 28 28 40 40 40 28 40 28 40 40 40\n'
            '  40 40 40 28 28 28 28 28 28 28 28 28 28 28 28 40 28 40 28 40 40 40 40\n'
            '  40 28 28 28 28 28 28 40 40 28 40 40 28 40 28 40 28 40 28 28 40 28 40\n'
            '  40 40 40 28 28 28 28 28 40 28 40 28 40 28 40 40 40 40 28 28 28 40 28\n'
            '  40 28 40 28 40 40 40 28 40 40 28 40 40 40 40 28 28 28 28 28 28 28 28\n'
            '  28 40 40 28 40 40 28 28 28 28 28 28 28 28 28 40 40 40 40 40 40 28 40\n'
            '  40 40 40 40 28 40 28 40 40 40 40 40 28 28 28 28 28 28 28 40 40 28 40\n'
            '  40 40 40 28 28 28 28 40 40 28 40 40 28 40 40 40 40 40 28 28 28 28 28\n'
            '  28 28 40 40 40 28 40 40 28 40 40 40 28 28 28 28 40 40 40 28 40 40 40\n'
            '  40 28 28 28 28 28 28 36 36 36 36 36 36 36 36 36 36 36 36 28 36 36 28\n'
            '  36 36 36 28 36 36 28 36 28 36 36 36 36 36 36 36 36 36 28 36 36 36 36\n'
            '  36 36 36 28 36 28 36 28 36 36 36 36 36 36 36 36 36 36 28 28 28 28 28\n'
            '  28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28\n'
            '  28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 36 28\n'
            '  40 28 36 28 36 36 36 36 36 36 36 36 28 36 36 36 36 36 36 28 36 36 28\n'
            '  36 28 36 28 36 28 36 36 36 36 36 28 36 36 36 36 36 36 36 36 36 36 36\n'
            '  36 28 36 36 36 36 36 36 28 36 36 36 36 36 36 36 36 36 36 28 36 36 28\n'
            '  36 36 36 36 36 36 36 36 36 36 36 36 36 36 28 36 28 36 28 36 36 36 36\n'
            '  36 28 36 28 36 28 36 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28\n'
            '  28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28\n'
            '  28 28 28 28 28 28 28 28 28 36 36 36 36 36 36 28 36 28 36 36 36 36 36\n'
            '  36 36 36 36 36 36 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 28 36\n'
            '  28 36 28 40 28 36 36 36 28 36 36 36 36 36 28 36 28 36 36 36 36 28 36\n'
            '  28 36 36 36 36 36 36 28\n'
            '\n'
            'Kind:               code-pointers\n'
            'From code begin:    0x8020000\n'
            'From code end:      0x8056deb\n'
            'Number of blocks:   3\n'
            'Size:               1.41 KiB\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        0\n'
            'To address:         0x3c570\n'
            'Number of values:   1139\n'
            'Values:\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 40 40 40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 8 4 8 4 8\n'
            '  8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 12 12 4 4 4 4 12 12 12 12 12 12\n'
            '  12 14 16 24 4 4 4 24 26 4 4 26 24 24 24 4 26 24 4 4 4 4 4 4 4 4 24 24\n'
            '  4 24 24 4 24 30 28 20 20 4 26 4 4 4 22 22 26 26 26 26 26 26 2 0 0 4 4\n'
            '  4 4 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 20 20 20 20\n'
            '  4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4\n'
            '  4 4 4 4 4 4 4 4 4 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 0 0 0 0 40 40 40 40 40 40 40 40 40 0\n'
            '\n'
            '------------------- Block 2 -------------------\n'
            '\n'
            'From offset:        1139\n'
            'To address:         0x46cd0\n'
            'Number of values:   188\n'
            'Values:\n'
            '  40 40 0 0 40 0 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 0 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 0 0 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '\n'
            '------------------- Block 3 -------------------\n'
            '\n'
            'From offset:        1327\n'
            'To address:         0x4bd7c\n'
            'Number of values:   114\n'
            'Values:\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 0 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40\n'
            '  40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 40 0 0 0 0\n'
            '\n'
            '\n')

    def test_patch_info_shell_pi_3_aarch64_detailed(self):
        argv = [
            'detools',
            'patch_info',
            '--detailed',
            'tests/files/shell-pi-3/1--2-aarch64.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(
            stdout.getvalue(),
            'Type:               sequential\n'
            'Patch size:         619 bytes\n'
            'To size:            109.94 KiB\n'
            'Patch/to ratio:     0.5 % (lower is better)\n'
            'Diff/extra ratio:   288556.4 % (higher is better)\n'
            'Size/data ratio:    0.0 % (lower is better)\n'
            'Compression:        lzma\n'
            'Data format size:   1.89 KiB\n'
            'Data format:        aarch64\n'
            '\n'
            'Number of diffs:    4\n'
            'Total diff size:    109.9 KiB\n'
            'Average diff size:  27.47 KiB\n'
            'Median diff size:   24.59 KiB\n'
            '\n'
            'Number of extras:   4\n'
            'Total extra size:   39 bytes\n'
            'Average extra size: 9 bytes\n'
            'Median extra size:  0 bytes\n'
            '\n'
            'Data format details:\n'
            '\n'
            'Instruction:        b\n'
            'Number of blocks:   0\n'
            'Size:               0 bytes\n'
            '\n'
            'Instruction:        bl\n'
            'Number of blocks:   2\n'
            'Size:               926 bytes\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        0\n'
            'To address:         0x70\n'
            'Number of values:   421\n'
            'Values:\n'
            '  0 0 0 0 0 0 0 -4 0 0 -4 -4 -4 0 0 -4 -4 0 -4 -4 -4 -4 -4 -4 -4 -4 -4\n'
            '  -4 -4 -4 -4 -4 0 0 0 0 -4 -4 0 -4 0 0 0 0 0 -4 -4 -4 -4 0 -4 -4 -4 -4\n'
            '  -4 -4 -4 -4 -4 -4 0 -4 -4 -4 -4 -4 -4 -4 -4 -4 0 -4 -4 -4 -4 -4 0 0 -4\n'
            '  0 -4 -4 -4 0 0 0 -4 -4 -4 0 0 0 0 0 0 0 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4\n'
            '  -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 0 0 0 -4 0 -4 -4 -4 -4 -4\n'
            '  -4 -4 -4 -4 0 0 0 0 -4 -4 -4 -4 -4 -4 -4 0 0 0 -4 0 -4 -4 -4 -4 -4 0\n'
            '  -4 -4 -4 0 -4 -4 0 0 -4 0 0 0 0 -4 0 0 0 -4 0 0 0 -4 0 0 -4 0 0 -4 0 0\n'
            '  0 -4 0 0 -4 0 -4 0 0 -4 0 -4 0 0 -4 0 0 -4 -4 -4 -4 0 -4 0 0 0 -4 0 -4\n'
            '  0 -4 -4 -4 0 0 0 0 -4 -4 -4 0 0 -4 0 -4 0 -4 -4 -4 -4 -4 -4 -4 -4 -4\n'
            '  -4 0 0 0 -4 -4 0 0 0 0 0 0 -4 -4 -4 0 -4 -4 -4 0 -4 -4 0 0 0 -4 0 -4 0\n'
            '  0 0 -4 -4 -4 -4 -4 -4 0 -4 -4 -4 -4 0 0 -4 -4 -4 -4 -4 -4 -4 0 0 0 0\n'
            '  -4 0 0 -4 0 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4\n'
            '  -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4\n'
            '  -4 -4 -4 -4 0 -4 0 0 -4 0 0 0 0 0 0 -4 -4 -4 -4 -4 -4 0 -4 -4 -4 -4 -4\n'
            '  -4 -4 0 -4 -4 0 -4 0 -4 -4 -4 -4 -4 -4 -4 0 -4 0 0 0 -4 -4 -4 0 -4 -4\n'
            '  0 -4 -4 0 0 0 -4 -4 -4 -4 -4 0 0 -4 -4 -4 -4 -4 -4 -4 -4 -4 0 0\n'
            '\n'
            '------------------- Block 2 -------------------\n'
            '\n'
            'From offset:        421\n'
            'To address:         0x60c4\n'
            'Number of values:   505\n'
            'Values:\n'
            '  4 4 4 4 4 0 0 4 4 4 0 4 4 0 4 4 0 0 4 4 4 4 0 0 0 0 4 0 4 0 0 0 0 0 0\n'
            '  0 4 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 4 4 0 0 0 0 4 0 0 4\n'
            '  0 0 0 0 0 0 0 0 0 0 0 4 4 0 0 0 0 0 0 4 4 0 0 4 0 0 4 0 0 0 0 0 4 0 0\n'
            '  4 0 4 4 0 0 0 0 0 0 4 0 0 0 0 0 4 0 4 0 0 0 0 0 0 4 0 0 0 0 4 0 0 4 0\n'
            '  0 0 0 0 0 0 0 4 4 4 4 0 0 0 0 0 0 4 0 0 0 0 0 0 0 4 0 0 0 4 0 0 0 0 0\n'
            '  0 0 0 4 4 0 4 0 4 0 0 0 0 0 0 0 0 0 0 0 0 4 0 4 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 4 0 4 0 0 0 0 0 0 0 0 0 0 0 0 4 0 0 0 4 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 4 0 4 4 0 4 4 0 4 0 0 4 4 4 4 4 4 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 4 0 0 0 0 0 0 0 0 0 0 4 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 4 0 4 0 0 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 4 0 4 4 4 0 4 0 4 4 0 4\n'
            '  4 4 4 4 0 4 0 0 4 4 0 4 0 4 4 4 4 4 0 4 4 4 0 4 0 0 4 0 0 0 0 4 4 0 0\n'
            '  0 0 4 0 4 0 0 4 0 4 0 0 0 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4\n'
            '  4 0 0 0 0 0 0 0 0 0 0 0 4 0 4\n'
            '\n'
            'Instruction:        add\n'
            'Number of blocks:   2\n'
            'Size:               621 bytes\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        0\n'
            'To address:         0x20\n'
            'Number of values:   284\n'
            'Values:\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -8 0\n'
            '  -8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -16 0 -16 -8 0 0 0 0 0 -8 -8\n'
            '  0 0 0 -8 0 0 0 0 0 0 0 0 -8 0 -8 0 0 0 -16 -8 -8 -8 0 -8 0 0 0 0 0 -16\n'
            '  0 -8 0 -8 0 -8 0 -8 0 0 0 0 -8 -18296\n'
            '\n'
            '------------------- Block 2 -------------------\n'
            '\n'
            'From offset:        285\n'
            'To address:         0x60f0\n'
            'Number of values:   335\n'
            'Values:\n'
            '  0 -8 0 -8 -8 0 0 -8 -8 0 -8 -8 -8 0 -8 0 -8 -8 -8 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 -16 -8 -16 -8 0 -16 -16 -8 0 -8 -8 0 -8 -8 -8 0 -8 -8 -8\n'
            '  -8 -8 -8 -8 0 -16 -8 -16 -8 -16 -8 -16 -8 0 -8 -8 -8 0 -8 -8 -8 -8 0\n'
            '  -8 -8 -8 -8 -8 -8 -8 -8 -8 0 -8 -8 -8 0 0 -8 -8 -8 0 -8 -8 -8 -8 -8 -8\n'
            '  -8 -8 -8 -8 -8 0 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8\n'
            '  -8 0 0 -8 0 -8 -8 -8 -8 -8 -8 -8 0 0 -8 -8 -8 0 -8 -8 0 -8 -8 -8 0 0 0\n'
            '  0 0 0 -8 -8 -8 -8 -8 -8 -8 0 0 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8\n'
            '  0 -8 0 -8 0 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 0 -8 -8 -8 -8\n'
            '  -8 -8 -8 -8 -8 -8 -8 -8 -8 0 -8 -8 -8 -8 -8 0 -8 -8 -8 0 -8 -8 -8 -8\n'
            '  -8 -8 0 -8 -8 -16 -8 -16 -8 -16 -8 -16 -8 -16 -8 -16 -8 -16 -8 -16 -8\n'
            '  -16 -8 -16 -16 -16 -8 -8 -8 -8 -16 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 0\n'
            '  0 -8 -8 -8 -8 -8 -16 -16 -16 -16 -16 -8 -16 -16 -16 -16 -16 -8 -8 -8\n'
            '  -8 0 -8 0 0 0 -8 -16 0 0 -8 -16 -8 -8 -16 -8 -8 -8 -8 -8 -8 -8 0 0 0\n'
            '  -8 -8 -8 0 0 0 -8 -8 0 -8 -8 0 -8 -8 -8 -8 -8 -8 0\n'
            '\n'
            'Instruction:        add (generic)\n'
            'Number of blocks:   1\n'
            'Size:               352 bytes\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        208\n'
            'To address:         0x60f4\n'
            'Number of values:   330\n'
            'Values:\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 -8192 0 0 0 0 -8192 0 0 -8192 0 0 0 0 0 -8192 0\n'
            '  0 0 0 0 0 0 -8192 0 0 0 0 0 0 -8192 0 0 0 0 0 0 -8192 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 -8192 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 -8192 0 -8192 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  -8192 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0\n'
            '\n'
            'Instruction:        ldr\n'
            'Number of blocks:   0\n'
            'Size:               0 bytes\n'
            '\n'
            'Instruction:        adrp\n'
            'Number of blocks:   0\n'
            'Size:               0 bytes\n'
            '\n'
            'Instruction:        str\n'
            'Number of blocks:   0\n'
            'Size:               0 bytes\n'
            '\n'
            'Instruction:        str (imm 64)\n'
            'Number of blocks:   0\n'
            'Size:               0 bytes\n'
            '\n'
            '\n')

    def test_patch_info_shell_pi_3_data_sections_detailed(self):
        argv = [
            'detools',
            'patch_info',
            '--detailed',
            'tests/files/shell-pi-3/1--2-aarch64-data-sections.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(
            stdout.getvalue(),
            'Type:               sequential\n'
            'Patch size:         631 bytes\n'
            'To size:            109.94 KiB\n'
            'Patch/to ratio:     0.6 % (lower is better)\n'
            'Diff/extra ratio:   288556.4 % (higher is better)\n'
            'Size/data ratio:    0.0 % (lower is better)\n'
            'Compression:        lzma\n'
            'Data format size:   1.93 KiB\n'
            'Data format:        aarch64\n'
            '\n'
            'Number of diffs:    4\n'
            'Total diff size:    109.9 KiB\n'
            'Average diff size:  27.47 KiB\n'
            'Median diff size:   24.59 KiB\n'
            '\n'
            'Number of extras:   4\n'
            'Total extra size:   39 bytes\n'
            'Average extra size: 9 bytes\n'
            'Median extra size:  0 bytes\n'
            '\n'
            'Data format details:\n'
            '\n'
            'Instruction:        b\n'
            'Number of blocks:   0\n'
            'Size:               0 bytes\n'
            '\n'
            'Instruction:        bl\n'
            'Number of blocks:   2\n'
            'Size:               926 bytes\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        0\n'
            'To address:         0x70\n'
            'Number of values:   421\n'
            'Values:\n'
            '  0 0 0 0 0 0 0 -4 0 0 -4 -4 -4 0 0 -4 -4 0 -4 -4 -4 -4 -4 -4 -4 -4 -4\n'
            '  -4 -4 -4 -4 -4 0 0 0 0 -4 -4 0 -4 0 0 0 0 0 -4 -4 -4 -4 0 -4 -4 -4 -4\n'
            '  -4 -4 -4 -4 -4 -4 0 -4 -4 -4 -4 -4 -4 -4 -4 -4 0 -4 -4 -4 -4 -4 0 0 -4\n'
            '  0 -4 -4 -4 0 0 0 -4 -4 -4 0 0 0 0 0 0 0 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4\n'
            '  -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 0 0 0 -4 0 -4 -4 -4 -4 -4\n'
            '  -4 -4 -4 -4 0 0 0 0 -4 -4 -4 -4 -4 -4 -4 0 0 0 -4 0 -4 -4 -4 -4 -4 0\n'
            '  -4 -4 -4 0 -4 -4 0 0 -4 0 0 0 0 -4 0 0 0 -4 0 0 0 -4 0 0 -4 0 0 -4 0 0\n'
            '  0 -4 0 0 -4 0 -4 0 0 -4 0 -4 0 0 -4 0 0 -4 -4 -4 -4 0 -4 0 0 0 -4 0 -4\n'
            '  0 -4 -4 -4 0 0 0 0 -4 -4 -4 0 0 -4 0 -4 0 -4 -4 -4 -4 -4 -4 -4 -4 -4\n'
            '  -4 0 0 0 -4 -4 0 0 0 0 0 0 -4 -4 -4 0 -4 -4 -4 0 -4 -4 0 0 0 -4 0 -4 0\n'
            '  0 0 -4 -4 -4 -4 -4 -4 0 -4 -4 -4 -4 0 0 -4 -4 -4 -4 -4 -4 -4 0 0 0 0\n'
            '  -4 0 0 -4 0 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4\n'
            '  -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4 -4\n'
            '  -4 -4 -4 -4 0 -4 0 0 -4 0 0 0 0 0 0 -4 -4 -4 -4 -4 -4 0 -4 -4 -4 -4 -4\n'
            '  -4 -4 0 -4 -4 0 -4 0 -4 -4 -4 -4 -4 -4 -4 0 -4 0 0 0 -4 -4 -4 0 -4 -4\n'
            '  0 -4 -4 0 0 0 -4 -4 -4 -4 -4 0 0 -4 -4 -4 -4 -4 -4 -4 -4 -4 0 0\n'
            '\n'
            '------------------- Block 2 -------------------\n'
            '\n'
            'From offset:        421\n'
            'To address:         0x60c4\n'
            'Number of values:   505\n'
            'Values:\n'
            '  4 4 4 4 4 0 0 4 4 4 0 4 4 0 4 4 0 0 4 4 4 4 0 0 0 0 4 0 4 0 0 0 0 0 0\n'
            '  0 4 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 4 4 0 0 0 0 4 0 0 4\n'
            '  0 0 0 0 0 0 0 0 0 0 0 4 4 0 0 0 0 0 0 4 4 0 0 4 0 0 4 0 0 0 0 0 4 0 0\n'
            '  4 0 4 4 0 0 0 0 0 0 4 0 0 0 0 0 4 0 4 0 0 0 0 0 0 4 0 0 0 0 4 0 0 4 0\n'
            '  0 0 0 0 0 0 0 4 4 4 4 0 0 0 0 0 0 4 0 0 0 0 0 0 0 4 0 0 0 4 0 0 0 0 0\n'
            '  0 0 0 4 4 0 4 0 4 0 0 0 0 0 0 0 0 0 0 0 0 4 0 4 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 4 0 4 0 0 0 0 0 0 0 0 0 0 0 0 4 0 0 0 4 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 4 0 4 4 0 4 4 0 4 0 0 4 4 4 4 4 4 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 4 0 0 0 0 0 0 0 0 0 0 4 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 4 0 4 0 0 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 4 0 4 4 4 0 4 0 4 4 0 4\n'
            '  4 4 4 4 0 4 0 0 4 4 0 4 0 4 4 4 4 4 0 4 4 4 0 4 0 0 4 0 0 0 0 4 4 0 0\n'
            '  0 0 4 0 4 0 0 4 0 4 0 0 0 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4\n'
            '  4 0 0 0 0 0 0 0 0 0 0 0 4 0 4\n'
            '\n'
            'Instruction:        add\n'
            'Number of blocks:   2\n'
            'Size:               621 bytes\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        0\n'
            'To address:         0x20\n'
            'Number of values:   284\n'
            'Values:\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -8 0\n'
            '  -8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -16 0 -16 -8 0 0 0 0 0 -8 -8\n'
            '  0 0 0 -8 0 0 0 0 0 0 0 0 -8 0 -8 0 0 0 -16 -8 -8 -8 0 -8 0 0 0 0 0 -16\n'
            '  0 -8 0 -8 0 -8 0 -8 0 0 0 0 -8 -18296\n'
            '\n'
            '------------------- Block 2 -------------------\n'
            '\n'
            'From offset:        285\n'
            'To address:         0x60f0\n'
            'Number of values:   335\n'
            'Values:\n'
            '  0 -8 0 -8 -8 0 0 -8 -8 0 -8 -8 -8 0 -8 0 -8 -8 -8 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 -16 -8 -16 -8 0 -16 -16 -8 0 -8 -8 0 -8 -8 -8 0 -8 -8 -8\n'
            '  -8 -8 -8 -8 0 -16 -8 -16 -8 -16 -8 -16 -8 0 -8 -8 -8 0 -8 -8 -8 -8 0\n'
            '  -8 -8 -8 -8 -8 -8 -8 -8 -8 0 -8 -8 -8 0 0 -8 -8 -8 0 -8 -8 -8 -8 -8 -8\n'
            '  -8 -8 -8 -8 -8 0 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8\n'
            '  -8 0 0 -8 0 -8 -8 -8 -8 -8 -8 -8 0 0 -8 -8 -8 0 -8 -8 0 -8 -8 -8 0 0 0\n'
            '  0 0 0 -8 -8 -8 -8 -8 -8 -8 0 0 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8\n'
            '  0 -8 0 -8 0 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 0 -8 -8 -8 -8\n'
            '  -8 -8 -8 -8 -8 -8 -8 -8 -8 0 -8 -8 -8 -8 -8 0 -8 -8 -8 0 -8 -8 -8 -8\n'
            '  -8 -8 0 -8 -8 -16 -8 -16 -8 -16 -8 -16 -8 -16 -8 -16 -8 -16 -8 -16 -8\n'
            '  -16 -8 -16 -16 -16 -8 -8 -8 -8 -16 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 -8 0\n'
            '  0 -8 -8 -8 -8 -8 -16 -16 -16 -16 -16 -8 -16 -16 -16 -16 -16 -8 -8 -8\n'
            '  -8 0 -8 0 0 0 -8 -16 0 0 -8 -16 -8 -8 -16 -8 -8 -8 -8 -8 -8 -8 0 0 0\n'
            '  -8 -8 -8 0 0 0 -8 -8 0 -8 -8 0 -8 -8 -8 -8 -8 -8 0\n'
            '\n'
            'Instruction:        add (generic)\n'
            'Number of blocks:   1\n'
            'Size:               352 bytes\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        208\n'
            'To address:         0x60f4\n'
            'Number of values:   330\n'
            'Values:\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 -8192 0 0 0 0 -8192 0 0 -8192 0 0 0 0 0 -8192 0\n'
            '  0 0 0 0 0 0 -8192 0 0 0 0 0 0 -8192 0 0 0 0 0 0 -8192 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 -8192 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 -8192 0 -8192 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  -8192 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n'
            '  0 0\n'
            '\n'
            'Instruction:        ldr\n'
            'Number of blocks:   0\n'
            'Size:               0 bytes\n'
            '\n'
            'Instruction:        adrp\n'
            'Number of blocks:   0\n'
            'Size:               0 bytes\n'
            '\n'
            'Instruction:        str\n'
            'Number of blocks:   0\n'
            'Size:               0 bytes\n'
            '\n'
            'Instruction:        str (imm 64)\n'
            'Number of blocks:   0\n'
            'Size:               0 bytes\n'
            '\n'
            'Kind:               data-pointers\n'
            'From data offset:   0x15300\n'
            'From data begin:    0x40000000\n'
            'From data end:      0x4001b7b8\n'
            'Number of blocks:   1\n'
            'Size:               9 bytes\n'
            '\n'
            '------------------- Block 1 -------------------\n'
            '\n'
            'From offset:        14\n'
            'To address:         0x17f78\n'
            'Number of values:   9\n'
            'Values:\n'
            '  -8 -8 -8 -8 -8 -8 -8 -8 -8\n'
            '\n'
            'Kind:               code-pointers\n'
            'From code begin:    0x0\n'
            'From code end:      0xd2e0\n'
            'Number of blocks:   0\n'
            'Size:               0 bytes\n'
            '\n'
            '\n')

    def test_create_patch_foo_bsdiff(self):
        foo_patch = 'foo.patch'
        argv = [
            'detools',
            'create_patch_bsdiff',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        self.execute_and_assert(argv, foo_patch, 'tests/files/foo/bsdiff.patch')

    def test_apply_patch_foo_bsdiff(self):
        foo_new = 'foo.new'
        argv = [
            'detools',
            'apply_patch_bsdiff',
            'tests/files/foo/old',
            'tests/files/foo/bsdiff.patch',
            foo_new
        ]

        self.execute_and_assert(argv, foo_new, 'tests/files/foo/new')

    def test_create_patch_foo_hdiffpatch(self):
        foo_patch = 'foo.patch'
        argv = [
            'detools',
            'create_patch',
            '--patch-type', 'hdiffpatch',
            '--algorithm', 'hdiffpatch',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        self.execute_and_assert(argv, foo_patch, 'tests/files/foo/hdiffpatch.patch')

    def test_create_patch_foo_hdiffpatch_none(self):
        foo_patch = 'foo.patch'
        argv = [
            'detools',
            'create_patch',
            '-c', 'none',
            '-t', 'hdiffpatch',
            '-a', 'hdiffpatch',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        self.execute_and_assert(argv,
                                foo_patch,
                                'tests/files/foo/hdiffpatch-none.patch')

    def test_create_patch_foo_hdiffpatch_match_score_0(self):
        foo_patch = 'foo.patch'
        argv = [
            'detools',
            'create_patch',
            '-t', 'hdiffpatch',
            '-a', 'hdiffpatch',
            '--match-score', '0',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        self.execute_and_assert(argv,
                                foo_patch,
                                'tests/files/foo/hdiffpatch-match-score-0.patch')

    def test_create_patch_foo_hdiffpatch_match_block_size_64(self):
        foo_patch = 'foo.patch'
        argv = [
            'detools',
            'create_patch',
            '-t', 'hdiffpatch',
            '-a', 'match-blocks',
            '--match-block-size', '64',
            'tests/files/foo/old',
            'tests/files/foo/new',
            foo_patch
        ]

        self.execute_and_assert(
            argv,
            foo_patch,
            'tests/files/foo/hdiffpatch-match-block-size-64.patch')

    def test_apply_patch_foo_hdiffpatch(self):
        foo_new = 'foo.new'
        argv = [
            'detools',
            'apply_patch',
            'tests/files/foo/old',
            'tests/files/foo/hdiffpatch.patch',
            foo_new
        ]

        self.execute_and_assert(argv, foo_new, 'tests/files/foo/new')

    def test_apply_patch_foo_hdiffpatch_none(self):
        foo_new = 'foo.new'
        argv = [
            'detools',
            'apply_patch',
            'tests/files/foo/old',
            'tests/files/foo/hdiffpatch-none.patch',
            foo_new
        ]

        self.execute_and_assert(argv, foo_new, 'tests/files/foo/new')

    def test_patch_info_foo_hdiffpatch(self):
        argv = [
            'detools',
            'patch_info',
            'tests/files/foo/hdiffpatch.patch'
        ]
        stdout = StringIO()

        with patch('sys.argv', argv):
            with patch('sys.stdout', stdout):
                detools._main()

        self.assertEqual(stdout.getvalue(),
                         'Type:               hdiffpatch\n'
                         'Patch size:         146 bytes\n'
                         'To size:            2.71 KiB\n'
                         'Patch/to ratio:     5.3 % (lower is better)\n'
                         'Compression:        lzma\n')


if __name__ == '__main__':
    unittest.main()
