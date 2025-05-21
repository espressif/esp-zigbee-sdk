CFLAGS += -std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -g
CFLAGS += -I../../heatshrink

SRC += ../../detools.c
SRC += main.c
SRC += ../../heatshrink/heatshrink_decoder.c

all:
	gcc $(CFLAGS) $(SRC) -llzma -o dump-restore
	rm -f state.bin
	@echo
	./dump-restore \
	    ../../../tests/files/foo/old \
	    ../../../tests/files/foo/heatshrink.patch \
	    foo.new \
	    10 25
	@echo
	./dump-restore \
	    ../../../tests/files/foo/old \
	    ../../../tests/files/foo/heatshrink.patch \
	    foo.new \
	    90 20
	@echo
	./dump-restore \
	    ../../../tests/files/foo/old \
	    ../../../tests/files/foo/heatshrink.patch \
	    foo.new \
	    25 0
	@echo
	cmp foo.new ../../../tests/files/foo/new
