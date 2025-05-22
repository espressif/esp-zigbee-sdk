#!/usr/bin/env python3

import re
from setuptools import setup
from setuptools import find_packages
from setuptools import Extension


def find_version():
    return re.search(r"^__version__ = '(.*)'$",
                     open('detools/version.py', 'r').read(),
                     re.MULTILINE).group(1)

HDIFFPATCH_SOURCES = [
    "HDiff/diff.cpp",
    "HDiff/private_diff/compress_detect.cpp",
    "HDiff/private_diff/suffix_string.cpp",
    "HDiff/private_diff/libdivsufsort/divsufsort.c",
    "HDiff/private_diff/libdivsufsort/divsufsort64.c",
    "HDiff/private_diff/limit_mem_diff/stream_serialize.cpp",
    "HDiff/private_diff/limit_mem_diff/digest_matcher.cpp",
    "HDiff/private_diff/limit_mem_diff/adler_roll.c",
    "HDiff/private_diff/bytes_rle.cpp",
    "HPatch/patch.c",
]

HDIFFPATCH_SOURCES = [
    "detools/HDiffPatch/libHDiffPatch/" + source
    for source in HDIFFPATCH_SOURCES
]
HDIFFPATCH_SOURCES += ["detools/hdiffpatch.cpp"]
HDIFFPATCH_SOURCES += ["detools/HDiffPatch/file_for_patch.c"]

setup(name='detools',
      version=find_version(),
      description='Binary delta encoding tools.',
      long_description=open('README.rst', 'r').read(),
      author='Erik Moqvist',
      author_email='erik.moqvist@gmail.com',
      license='BSD',
      classifiers=[
          'License :: OSI Approved :: BSD License',
          'Programming Language :: Python :: 3',
      ],
      url='https://github.com/eerimoq/detools',
      packages=find_packages(exclude=['tests']),
      install_requires=[
          'humanfriendly',
          'bitstruct',
          'pyelftools',
          'zstandard',
          'lz4',
          'heatshrink2'
      ],
      ext_modules=[
          Extension(name="detools.suffix_array",
                    sources=[
                        "detools/suffix_array.c",
                        "detools/sais/sais.c",
                        "detools/libdivsufsort/divsufsort.c"
                    ]),
          Extension(name="detools.bsdiff", sources=["detools/bsdiff.c"]),
          Extension(name="detools.hdiffpatch", sources=HDIFFPATCH_SOURCES)
      ],
      test_suite="tests",
      entry_points={
          'console_scripts': ['detools=detools.__init__:_main']
      })
