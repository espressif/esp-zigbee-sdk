CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar

# Install prefix.
PREFIX ?= /usr/local

OPT ?= -O2
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wdouble-promotion
CFLAGS += -Wfloat-equal
CFLAGS += -Wformat=2
CFLAGS += -Wshadow
CFLAGS += -Werror
CFLAGS += -std=c99
CFLAGS += $(OPT)
CFLAGS += -Iheatshrink
CFLAGS += $(CFLAGS_EXTRA)

SRC += heatshrink/heatshrink_decoder.c
SRC += detools.c
SRC += main.c

all:
	$(CC) $(CFLAGS) $(SRC) -llzma -o detools

clean:
	rm -f detools detools.o libdetools.a esp8266-20190125-v1.10.bin

test: all
	./detools apply_patch \
	    ../tests/files/micropython/esp8266-20180511-v1.9.4.bin \
	    ../tests/files/micropython/esp8266-20180511-v1.9.4--20190125-v1.10-heatshrink.patch \
	    esp8266-20190125-v1.10.bin
	cmp \
	    esp8266-20190125-v1.10.bin \
	    ../tests/files/micropython/esp8266-20190125-v1.10.bin

library:
	$(CC) $(CFLAGS) detools.c -c -o detools.o
	$(AR) cr libdetools.a detools.o

install:
	mkdir -p $(PREFIX)/include
	install -c -m 644 detools.h $(PREFIX)/include
	mkdir -p $(PREFIX)/lib
	install -c -m 644 libdetools.a $(PREFIX)/lib
