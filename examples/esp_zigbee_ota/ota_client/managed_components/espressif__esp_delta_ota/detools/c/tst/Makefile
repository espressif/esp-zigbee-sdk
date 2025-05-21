TESTS += test_detools.c
TESTS += test_dump_restore.c
TESTS += test_command_line.c
TESTS += test_fuzzer.c
INC += ../heatshrink
SRC += ../detools.c
SRC += ../heatshrink/heatshrink_decoder.c
SRC += utils.c
LIBS += lzma

default:
	$(MAKE) -C .. OPT=-O0 CFLAGS_EXTRA="-coverage"
	$(MAKE) all

FUZZER_CFLAGS += -fprofile-instr-generate
FUZZER_CFLAGS += -g
FUZZER_CFLAGS += -fcoverage-mapping
FUZZER_CFLAGS += -fsanitize=address,fuzzer
FUZZER_CFLAGS += -fsanitize=signed-integer-overflow
FUZZER_CFLAGS += -fno-sanitize-recover=all
FUZZER_CFLAGS += $(INC:%=-I%)
FUZZER_CFLAGS += -I..
FUZZER_CFLAGS += -Wall
FUZZER_EXECUTION_TIME ?= 30
FUZZER_EXE = fuzzer-corrupt-patch

fuzz-corpus-patch:
	mkdir -p corpus
	clang $(FUZZER_CFLAGS) \
	    ../detools.c \
	    ../heatshrink/heatshrink_decoder.c \
	    fuzzer_corrupt_patch.c \
	    -l lzma -o $(FUZZER_EXE)
	rm -f $(FUZZER_EXE).profraw
	LLVM_PROFILE_FILE="$(FUZZER_EXE).profraw" \
	    ./$(FUZZER_EXE) \
	    -max_total_time=$(FUZZER_EXECUTION_TIME) \
	    -print_final_stats \
	    -rss_limit_mb=0 \
	    corpus
	llvm-profdata merge \
	    -sparse $(FUZZER_EXE).profraw \
	    -o $(FUZZER_EXE).profdata
	llvm-cov show ./$(FUZZER_EXE) \
	    -instr-profile=$(FUZZER_EXE).profdata

include test.mk
