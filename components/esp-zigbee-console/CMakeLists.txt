if (CONFIG_ZB_ZED)
    message(FATAL_ERROR "${COMPONENT_NAME} doesn't support CONFIG_ZB_ZED=y")
endif()

idf_component_register(SRC_DIRS "src" "src/zb_data"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES esp-zigbee-lib console
                       LDFRAGMENTS linker.lf
                       WHOLE_ARCHIVE)
