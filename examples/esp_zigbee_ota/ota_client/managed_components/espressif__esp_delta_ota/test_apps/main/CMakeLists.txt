idf_component_register(SRCS "esp_delta_ota_test_main.c" "test_esp_delta_ota.c"
                    PRIV_INCLUDE_DIRS "."
                    PRIV_REQUIRES unity
                    EMBED_FILES assets/base.bin assets/new.bin assets/patch.bin assets/bad_patch.bin
                    WHOLE_ARCHIVE)
