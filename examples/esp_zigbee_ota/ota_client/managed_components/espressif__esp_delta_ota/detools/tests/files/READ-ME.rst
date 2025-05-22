|buildstatus|_
|coverage|_
|codecov|_

About
=====

Binary delta encoding in Python 3, using C extensions.

Based on http://www.daemonology.net/bsdiff/, with the following
differences:

- LZMA compression instead of BZ2.

- Linear patch file access pattern to allow streaming.

- `SA-IS`_ instead of qsufsort.

- Variable length size fields.

Project homepage: https://github.com/eerimoq/detools

Documentation: http://detools.readthedocs.org/en/latest

Installation
============

.. code-block:: python

    pip install detools

Statistics
==========

`To compressed` is the size of `To file` compressed using ``lzma
--best``.

All sizes are in bytes.

+--------------------+-------------------+-----------+-----------+------------+---------------+
| From file          | To file           | From size |   To size | Patch size | To compressed |
+====================+===================+===========+===========+============+===============+
| micropython v1.9.4 | micropython v1.10 |    604872 |    615388 |      71868 |        367500 |
+--------------------+-------------------+-----------+-----------+------------+---------------+
| python 3.5         | python 3.6        |   4464400 |   4568920 |    1451788 |       1402663 |
+--------------------+-------------------+-----------+-----------+------------+---------------+
| foo.old            | foo.new           |      2780 |      2780 |        184 |          1934 |
+--------------------+-------------------+-----------+-----------+------------+---------------+

Example usage
=============

Command line tool
-----------------

The create patch subcommand
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Create a patch ``foo.patch`` from ``tests/files/foo.old`` to
``tests/files/foo.new``.

.. code-block:: text

   $ detools create_patch tests/files/foo.old tests/files/foo.new foo.patch
   $ ls -l foo.patch
   -rw-rw-r-- 1 erik erik 184 feb 21 07:28 foo.patch

The apply patch subcommand
^^^^^^^^^^^^^^^^^^^^^^^^^^

Apply the patch ``foo.patch`` to ``tests/files/foo.old`` to create
``foo.new``.

.. code-block:: text

   $ detools apply_patch tests/files/foo.old foo.patch foo.new
   $ ls -l foo.new
   -rw-rw-r-- 1 erik erik 2780 feb 21 07:30 foo.new

The patch info subcommand
^^^^^^^^^^^^^^^^^^^^^^^^^

Print information about the patch ``foo.patch``.

.. code-block:: text

   $ detools patch_info foo.patch
   Patch size:         184 bytes
   To size:            2.78 KB
   Patch/to ratio:     6.6 % (lower is better)
   Size/data ratio:    0.3 % (lower is better)

   Number of diffs:    2
   Total diff size:    2.75 KB
   Average diff size:  1.38 KB
   Median diff size:   1.38 KB

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

.. |buildstatus| image:: https://travis-ci.org/eerimoq/detools.svg?branch=master
.. _buildstatus: https://travis-ci.org/eerimoq/detools

.. |coverage| image:: https://coveralls.io/repos/github/eerimoq/detools/badge.svg?branch=master
.. _coverage: https://coveralls.io/github/eerimoq/detools

.. |codecov| image:: https://codecov.io/gh/eerimoq/detools/branch/master/graph/badge.svg
.. _codecov: https://codecov.io/gh/eerimoq/detools

.. _SA-IS: https://sites.google.com/site/yuta256/sais
