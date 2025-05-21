CFLAGS := \
	-Wall \
	-Wextra \
	-Wdouble-promotion \
	-Wfloat-equal \
	-Wformat=2 \
	-Wshadow \
	-Werror \
	-Wpedantic \
	-std=c99 \
	-g \
	--coverage \
	-Ic/heatshrink

FUZZER_CFLAGS = \
	-fprofile-instr-generate \
	-fcoverage-mapping \
	-Itests/files/c_source \
	-Ic/heatshrink \
	-g \
	-fsanitize=address,fuzzer \
	-fsanitize=signed-integer-overflow \
	-fno-sanitize-recover=all
FUZZER_EXECUTION_TIME ?= 30

test:
	env CFLAGS=--coverage python3 setup.py test
	$(MAKE) test-sdist
	$(MAKE) test-c
	find . -name "*.gcno" -exec gcov {} +
	$(MAKE) test-c-fuzzer FUZZER_EXECUTION_TIME=1
	$(MAKE) -C c/tst fuzz-corpus-patch FUZZER_EXECUTION_TIME=1

test-sdist:
	rm -rf dist
	python3 setup.py sdist
	cd dist && \
	mkdir test && \
	cd test && \
	tar xf ../*.tar.gz && \
	cd detools-* && \
	python3 setup.py test

test-c:
	$(MAKE) -C c/tst SANITIZE=yes
	$(CC) $(CFLAGS) -DDETOOLS_CONFIG_FILE_IO=0 -Ic/heatshrink \
	    -c c/detools.c -o detools.no-file-io.o
	$(CC) $(CFLAGS) -DDETOOLS_CONFIG_COMPRESSION_NONE=0 -Ic/heatshrink \
	    -c c/detools.c -o detools.no-none.o
	$(CC) $(CFLAGS) -DDETOOLS_CONFIG_COMPRESSION_LZMA=0 -Ic/heatshrink \
	    -c c/detools.c -o detools.no-lzma.o
	$(CC) $(CFLAGS) -DDETOOLS_CONFIG_COMPRESSION_CRLE=0 -Ic/heatshrink \
	    -c c/detools.c -o detools.no-crle.o
	$(CC) $(CFLAGS) -DDETOOLS_CONFIG_COMPRESSION_HEATSHRINK=0 -Ic/heatshrink \
	    -c c/detools.c -o detools.no-crle.o
	$(CC) $(CFLAGS) \
	    -DDETOOLS_CONFIG_COMPRESSION_NONE=0 \
	    -DDETOOLS_CONFIG_COMPRESSION_CRLE=0 \
	    -Ic/heatshrink -c c/detools.c -o detools.no-crle.o
	$(CC) $(CFLAGS) \
	    -DDETOOLS_CONFIG_COMPRESSION_NONE=0 \
	    -DDETOOLS_CONFIG_COMPRESSION_LZMA=0 \
	    -DDETOOLS_CONFIG_COMPRESSION_CRLE=0 \
	    -Ic/heatshrink -c c/detools.c -o detools.no-crle.o
	$(CC) $(CFLAGS) \
	    -DDETOOLS_CONFIG_COMPRESSION_NONE=0 \
	    -DDETOOLS_CONFIG_COMPRESSION_CRLE=0 \
	    -DDETOOLS_CONFIG_COMPRESSION_HEATSHRINK=0 \
	    -Ic/heatshrink -c c/detools.c -o detools.no-crle.o
	$(MAKE) -C c library
	$(MAKE) -C c/examples/in_place all
	$(MAKE) -C c/examples/in_place heatshrink
	$(MAKE) -C c/examples/in_place crle
	$(MAKE) -C c/examples/dump_restore
	$(MAKE) -C c clean
	$(MAKE) -C c test
	$(MAKE) -C c clean
	$(MAKE) -C c CFLAGS_EXTRA="-DHEATSHRINK_DYNAMIC_ALLOC=1" test

test-c-fuzzer:
	clang $(FUZZER_CFLAGS) \
	    c/detools.c \
	    c/heatshrink/heatshrink_decoder.c \
	    tests/fuzzer.c \
	    -l lzma -o fuzzer
	rm -f fuzzer.profraw
	LLVM_PROFILE_FILE="fuzzer.profraw" \
	    ./fuzzer \
	    -max_total_time=$(FUZZER_EXECUTION_TIME) \
	    -print_final_stats
	llvm-profdata merge \
	    -sparse fuzzer.profraw \
	    -o fuzzer.profdata
	llvm-cov show ./fuzzer \
	    -instr-profile=fuzzer.profdata

release-to-pypi:
	python3 setup.py sdist
	twine upload dist/*

benchmark:
	$(MAKE) -C c
	python3 setup.py test -s \
	    tests.test_detools.DetoolsTest.test_create_and_apply_patch_foo
	tests/benchmark.sh
