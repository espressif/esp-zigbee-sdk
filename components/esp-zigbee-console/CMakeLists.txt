if (CONFIG_ZB_ZED)
    message(FATAL_ERROR "${COMPONENT_NAME} doesn't support CONFIG_ZB_ZED=y")
endif()

idf_component_register(SRC_DIRS "src" "src/zb_data" "src/zb_data/zb_custom_clusters"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES esp-zigbee-lib console esp_timer
                       LDFRAGMENTS linker.lf
                       WHOLE_ARCHIVE)
