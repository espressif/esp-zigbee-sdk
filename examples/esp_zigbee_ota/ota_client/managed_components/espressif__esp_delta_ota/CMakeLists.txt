idf_component_register(SRCS "src/esp_delta_ota.c" "detools/c/detools.c" "detools/c/heatshrink/heatshrink_decoder.c"
                       INCLUDE_DIRS "include" 
                       PRIV_INCLUDE_DIRS "detools/c" "detools/c/heatshrink")

target_compile_options(${COMPONENT_LIB} PRIVATE "-DDETOOLS_CONFIG_FILE_IO=0")
target_compile_options(${COMPONENT_LIB} PRIVATE "-DDETOOLS_CONFIG_COMPRESSION_NONE=0")
target_compile_options(${COMPONENT_LIB} PRIVATE "-DDETOOLS_CONFIG_COMPRESSION_LZMA=0")
target_compile_options(${COMPONENT_LIB} PRIVATE "-DDETOOLS_CONFIG_COMPRESSION_CRLE=0")
