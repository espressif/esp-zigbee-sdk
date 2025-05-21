#!/usr/bin/env bash

PYTHON="${PYTHON:-python3}"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"

echo "Python: $PYTHON"

export PYTHONPATH=$SCRIPT_DIR/..

function create_patch() {
    echo "================= $1 ================="
    \time -f "RSS=%M elapsed=%E" \
          $PYTHON -m detools create_patch $1 $from_file $to_file $2 \
          > /dev/null
    ls -lh $2
}

function apply_patch() {
    echo "================= $1 ================="
    \time -f "RSS=%M elapsed=%E" \
          $PYTHON -m detools apply_patch $from_file $1 Python.tar \
          > /dev/null
    cmp Python.tar $to_file
    \time -f "RSS=%M elapsed=%E" \
          c/detools apply_patch $from_file $1 Python.tar
    cmp Python.tar $to_file
}

function print_files() {
    echo "***************************************************************"
    echo "* From: $from_file"
    echo "* To:   $to_file"
    echo "***************************************************************"
}

if [ ! -e Python-3.7.3.tar ] ; then
    wget https://www.python.org/ftp/python/3.7.3/Python-3.7.3.tgz
    gunzip Python-3.7.3.tgz
fi

if [ ! -e Python-3.8.1.tar ] ; then
    wget https://www.python.org/ftp/python/3.8.1/Python-3.8.1.tgz
    gunzip Python-3.8.1.tgz
fi

from_file=Python-3.7.3.tar
to_file=Python-3.8.1.tar

print_files

for algorithm in bsdiff hdiffpatch match-blocks ; do
    for patch_type in sequential hdiffpatch ; do
        for compression in lzma none ; do
            create_patch \
                "-a $algorithm -t $patch_type -c $compression" \
                "$algorithm-$patch_type-$compression.patch"
        done
    done
done

for algorithm in bsdiff hdiffpatch match-blocks ; do
    for patch_type in sequential hdiffpatch ; do
        for compression in lzma none ; do
            apply_patch "$algorithm-$patch_type-$compression.patch"
        done
    done
done

from_file=tests/files/micropython/esp8266-20180511-v1.9.4.bin
to_file=tests/files/micropython/esp8266-20190125-v1.10.bin

print_files

for algorithm in bsdiff hdiffpatch match-blocks ; do
    for patch_type in sequential hdiffpatch ; do
        for compression in lzma none ; do
            create_patch \
                "-a $algorithm -t $patch_type -c $compression" \
                "$algorithm-$patch_type-$compression.patch"
        done
    done
done

for algorithm in bsdiff hdiffpatch match-blocks ; do
    for patch_type in sequential hdiffpatch ; do
        for compression in lzma none ; do
            apply_patch "$algorithm-$patch_type-$compression.patch"
        done
    done
done

exit 0
