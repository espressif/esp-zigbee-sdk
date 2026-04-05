if(CONFIG_ZB_CONSOLE_ENABLED)
    if(CONFIG_ZB_ZED)
        message(FATAL_ERROR "${COMPONENT_NAME} doesn't support CONFIG_ZB_ZED=y")
    endif()

    set(src_dirs "src" "src/zb_data" "src/zb_data/zb_custom_clusters")
    set(inc_dirs "include")
    set(priv_inc_dirs "src")
    set(linker_script "linker.lf")
endif()


idf_component_register(SRC_DIRS ${src_dirs}
                       INCLUDE_DIRS ${inc_dirs}
                       PRIV_INCLUDE_DIRS ${priv_inc_dirs}
                       PRIV_REQUIRES console esp_timer
                       LDFRAGMENTS ${linker_script}
                       WHOLE_ARCHIVE)
