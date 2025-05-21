FLAGS := \
	-Os \
	-ffunction-sections \
	-fdata-sections \
	-Wl,--gc-sections \
	-std=c99 \
	-I../../heatshrink

SRC := \
	../../detools.c \
	main.c

all:
	gcc $(FLAGS) $(SRC) \
	    ../../heatshrink/heatshrink_decoder.c \
	    -llzma \
	    -o in-place
	size in-place

heatshrink:
	gcc $(FLAGS) $(SRC) \
	    ../../heatshrink/heatshrink_decoder.c \
	    -DDETOOLS_CONFIG_FILE_IO=0 \
	    -DDETOOLS_CONFIG_COMPRESSION_NONE=0 \
	    -DDETOOLS_CONFIG_COMPRESSION_LZMA=0 \
	    -DDETOOLS_CONFIG_COMPRESSION_CRLE=0 \
	    -DDETOOLS_CONFIG_COMPRESSION_HEATSHRINK=1 \
	    -o in-place-heatshrink
	size in-place-heatshrink

crle:
	gcc $(FLAGS) $(SRC) \
	    -DDETOOLS_CONFIG_FILE_IO=0 \
	    -DDETOOLS_CONFIG_COMPRESSION_NONE=0 \
	    -DDETOOLS_CONFIG_COMPRESSION_LZMA=0 \
	    -DDETOOLS_CONFIG_COMPRESSION_CRLE=1 \
	    -DDETOOLS_CONFIG_COMPRESSION_HEATSHRINK=0 \
	    -o in-place-crle
	size in-place-crle
