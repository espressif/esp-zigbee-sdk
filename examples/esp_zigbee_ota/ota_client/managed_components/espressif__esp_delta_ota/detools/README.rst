|nala|_

About
=====

Binary `delta encoding`_ in Python 3.6+ and C.

Based on http://www.daemonology.net/bsdiff/ and `HDiffPatch`_, with
the following features:

- bsdiff, hdiffpatch and match-blocks algorithms.

- `sequential`_, hdiffpatch or `in-place`_ (resumable) patch types.

- BZ2, LZ4, LZMA, `Zstandard`_, `heatshrink`_ or CRLE compression.

- Sequential patches allow streaming.

- Maximum file size is 2 GB for the bsdiff algorithm. There is
  practically no limit for the hdiffpatch and match-blocks algorithms.

- `Incremental apply patch`_ implemented in C, suitable for memory
  constrained embedded devices. Only the sequential patch type is
  supported.

- `SA-IS`_ or divsufsort instead of qsufsort for bsdiff.

- Optional experimental data format aware algorithm for potentially
  smaller patches. I don't recommend anyone to use this functionality
  as the gain is small in relation to memory usage and code
  complexity!

  There is a risk this functionality uses patent
  https://patents.google.com/patent/EP1988455B1/en. Anyway, this
  patent expires in August 2019 as I understand it.

  Supported data formats:

  - ARM Cortex-M4

  - AArch64

Project homepage: https://github.com/eerimoq/detools

Documentation: http://detools.readthedocs.org/en/latest

Installation
============

.. code-block:: python

    pip install detools

Statistics
==========

Patch sizes, memory usage (RSS) and elapsed times when creating a
patch from Python-3.7.3.tar (79M) to Python-3.8.1.tar (84M) for
various algorithm, patch type and compression combinations.

See `tests/benchmark.sh`_ for details on how the data was collected.

+--------------+------------+--------+------------+------+---------+
| Algorithm    | Patch type | Compr. | Patch size |  RSS |    Time |
+==============+============+========+============+======+=========+
| bsdiff       | sequential | lzma   |       3,5M | 662M | 0:24.29 |
+--------------+------------+--------+------------+------+---------+
| bsdiff       | sequential | none   |        86M | 646M | 0:15.20 |
+--------------+------------+--------+------------+------+---------+
| hdiffpatch   | hdiffpatch | lzma   |       2,4M | 523M | 0:13.74 |
+--------------+------------+--------+------------+------+---------+
| hdiffpatch   | hdiffpatch | none   |       7,2M | 523M | 0:10.24 |
+--------------+------------+--------+------------+------+---------+
| match-blocks | sequential | lzma   |       2,9M | 273M | 0:08.57 |
+--------------+------------+--------+------------+------+---------+
| match-blocks | sequential | none   |        84M | 273M | 0:01.72 |
+--------------+------------+--------+------------+------+---------+
| match-blocks | hdiffpatch | lzma   |       2,6M | 212M | 0:06.07 |
+--------------+------------+--------+------------+------+---------+
| match-blocks | hdiffpatch | none   |       9,7M | 212M | 0:01.30 |
+--------------+------------+--------+------------+------+---------+

Same as above, but for MicroPython ESP8266 binary releases (from 604k
to 615k).

+--------------+------------+--------+------------+------+---------+
| Algorithm    | Patch type | Compr. | Patch size |  RSS |    Time |
+==============+============+========+============+======+=========+
| bsdiff       | sequential | lzma   |        71K |  46M | 0:00.64 |
+--------------+------------+--------+------------+------+---------+
| bsdiff       | sequential | none   |       609K |  27M | 0:00.33 |
+--------------+------------+--------+------------+------+---------+
| hdiffpatch   | hdiffpatch | lzma   |        65K |  42M | 0:00.37 |
+--------------+------------+--------+------------+------+---------+
| hdiffpatch   | hdiffpatch | none   |       123K |  25M | 0:00.32 |
+--------------+------------+--------+------------+------+---------+
| match-blocks | sequential | lzma   |       194K |  46M | 0:00.44 |
+--------------+------------+--------+------------+------+---------+
| match-blocks | sequential | none   |       606K |  25M | 0:00.22 |
+--------------+------------+--------+------------+------+---------+
| match-blocks | hdiffpatch | lzma   |       189K |  43M | 0:00.38 |
+--------------+------------+--------+------------+------+---------+
| match-blocks | hdiffpatch | none   |       313K |  24M | 0:00.19 |
+--------------+------------+--------+------------+------+---------+

Example usage
=============

Examples in C are found in `c`_.

Command line tool
-----------------

The create patch subcommand
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Create a patch ``foo.patch`` from ``tests/files/foo/old`` to
``tests/files/foo/new``.

.. code-block:: text

   $ detools create_patch tests/files/foo/old tests/files/foo/new foo.patch
   Successfully created 'foo.patch' in 0.01 seconds!
   $ ls -l foo.patch
   -rw-rw-r-- 1 erik erik 127 feb  2 10:35 foo.patch

Create the same patch as above, but without compression.

.. code-block:: text

   $ detools create_patch --compression none \
         tests/files/foo/old tests/files/foo/new foo-no-compression.patch
   Successfully created 'foo-no-compression.patch' in 0 seconds!
   $ ls -l foo-no-compression.patch
   -rw-rw-r-- 1 erik erik 2792 feb  2 10:35 foo-no-compression.patch

Create a hdiffpatch patch ``foo-hdiffpatch.patch``.

.. code-block:: text

   $ detools create_patch --algorithm hdiffpatch --patch-type hdiffpatch \
         tests/files/foo/old tests/files/foo/new foo-hdiffpatch.patch
   Successfully created patch 'foo-hdiffpatch.patch' in 0.01 seconds!
   $ ls -l foo-hdiffpatch.patch
   -rw-rw-r-- 1 erik erik 146 feb  2 10:37 foo-hdiffpatch.patch

Lower memory usage with ``--algorithm match-blocks`` algorithm. Mainly
useful for big files. Creates slightly bigger patches than ``bsdiff``
and ``hdiffpatch``.

.. code-block:: text

   $ detools create_patch --algorithm match-blocks \
         tests/files/foo/old tests/files/foo/new foo-hdiffpatch-64.patch
   Successfully created patch 'foo-hdiffpatch-64.patch' in 0.01 seconds!
   $ ls -l foo-hdiffpatch-64.patch
   -rw-rw-r-- 1 erik erik 404 feb  8 11:03 foo-hdiffpatch-64.patch

Non-sequential but smaller patch with ``--patch-type hdiffpatch``.

.. code-block:: text

   $ detools create_patch \
         --algorithm match-blocks --patch-type hdiffpatch \
         tests/files/foo/old tests/files/foo/new foo-hdiffpatch-sequential.patch
   Successfully created 'foo-hdiffpatch-sequential.patch' in 0.01 seconds!
   $ ls -l foo-hdiffpatch-sequential.patch
   -rw-rw-r-- 1 erik erik 389 feb  8 11:05 foo-hdiffpatch-sequential.patch

The create in-place patch subcommand
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Create an in-place patch ``foo-in-place.patch``.

.. code-block:: text

   $ detools create_patch_in_place --memory-size 3000 --segment-size 500 \
         tests/files/foo/old tests/files/foo/new foo-in-place.patch
   Successfully created 'foo-in-place.patch' in 0.01 seconds!
   $ ls -l foo-in-place.patch
   -rw-rw-r-- 1 erik erik 672 feb  2 10:36 foo-in-place.patch

The create bsdiff patch subcommand
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Create a bsdiff patch ``foo-bsdiff.patch``, compatible with the
original bsdiff program.

.. code-block:: text

   $ detools create_patch_bsdiff \
         tests/files/foo/old tests/files/foo/new foo-bsdiff.patch
   Successfully created 'foo-bsdiff.patch' in 0 seconds!
   $ ls -l foo-bsdiff.patch
   -rw-rw-r-- 1 erik erik 261 feb  2 10:36 foo-bsdiff.patch

The apply patch subcommand
^^^^^^^^^^^^^^^^^^^^^^^^^^

Apply the patch ``foo.patch`` to ``tests/files/foo/old`` to create
``foo.new``.

.. code-block:: text

   $ detools apply_patch tests/files/foo/old foo.patch foo.new
   Successfully created 'foo.new' in 0 seconds!
   $ ls -l foo.new
   -rw-rw-r-- 1 erik erik 2780 feb  2 10:38 foo.new

The in-place apply patch subcommand
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Apply the in-place patch ``foo-in-place.patch`` to ``foo.mem``.

.. code-block:: text

   $ cp tests/files/foo/in-place-3000-500.mem foo.mem
   $ detools apply_patch_in_place foo.mem foo-in-place.patch
   Successfully created 'foo.mem' in 0 seconds!
   $ ls -l foo.mem
   -rw-rw-r-- 1 erik erik 3000 feb  2 10:40 foo.mem

The bsdiff apply patch subcommand
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Apply the patch ``foo-bsdiff.patch`` to ``tests/files/foo/old`` to
create ``foo.new``.

.. code-block:: text

   $ detools apply_patch_bsdiff tests/files/foo/old foo-bsdiff.patch foo.new
   Successfully created 'foo.new' in 0 seconds!
   $ ls -l foo.new
   -rw-rw-r-- 1 erik erik 2780 feb  2 10:41 foo.new

The patch info subcommand
^^^^^^^^^^^^^^^^^^^^^^^^^

Print information about the patch ``foo.patch``.

.. code-block:: text

   $ detools patch_info foo.patch
   Type:               sequential
   Patch size:         127 bytes
   To size:            2.71 KiB
   Patch/to ratio:     4.6 % (lower is better)
   Diff/extra ratio:   9828.6 % (higher is better)
   Size/data ratio:    0.3 % (lower is better)
   Compression:        lzma

   Number of diffs:    2
   Total diff size:    2.69 KiB
   Average diff size:  1.34 KiB
   Median diff size:   1.34 KiB

   Number of extras:   2
   Total extra size:   28 bytes
   Average extra size: 14 bytes
   Median extra size:  14 bytes

Contributing
============

#. Fork the repository.

#. Install prerequisites.

   .. code-block:: text

      pip install -r requirements.txt

#. Implement the new feature or bug fix.

#. Implement test case(s) to ensure that future changes do not break
   legacy.

#. Run the tests.

   .. code-block:: text

      make test

#. Create a pull request.

.. |nala| image:: https://img.shields.io/badge/nala-test-blue.svg
.. _nala: https://github.com/eerimoq/nala

.. _SA-IS: https://sites.google.com/site/yuta256/sais

.. _HDiffPatch: https://github.com/sisong/HDiffPatch

.. _Incremental apply patch: https://github.com/eerimoq/detools/tree/master/c

.. _delta encoding: https://en.wikipedia.org/wiki/Delta_encoding

.. _heatshrink: https://github.com/atomicobject/heatshrink

.. _Zstandard: https://facebook.github.io/zstd

.. _sequential: https://detools.readthedocs.io/en/latest/#id1

.. _in-place: https://detools.readthedocs.io/en/latest/#id3

.. _c: https://github.com/eerimoq/detools/tree/master/c

.. _tests/benchmark.sh: https://github.com/eerimoq/detools/tree/master/tests/benchmark.sh
