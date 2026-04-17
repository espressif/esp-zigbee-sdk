idf_build_get_property(idf_target IDF_TARGET)

if (CONFIG_ZB_ENABLED)
    set(src_dirs "src/utils")
    set(include_dirs include)
    if (CONFIG_ZB_SDK_1xx)
        list(APPEND include_dirs include/compat)
    endif()
endif()

if(CONFIG_ZB_RADIO_SPINEL_UART)
    list(APPEND src_dirs src/radio_spinel)
    list(APPEND include_dirs)
endif()

idf_component_register(SRC_DIRS "${src_dirs}"
                       INCLUDE_DIRS "${include_dirs}"
                       REQUIRES driver vfs ieee802154 mbedtls openthread
                       WHOLE_ARCHIVE
)

if(CONFIG_ZB_ENABLED)

    set(target_lib_dir "${CMAKE_CURRENT_SOURCE_DIR}/lib/${idf_target}")

    if (NOT IS_DIRECTORY "${target_lib_dir}")
        message(FATAL_ERROR "target ${idf_target} is not supported")
    endif()

    set(ESP_ZIGBEE_LIBS "")

    if(CONFIG_ZB_RADIO_SPINEL_UART)
        set(radio_mode ".remote")
    elseif(CONFIG_ZB_RADIO_NATIVE)
        set(radio_mode ".native")
    else()
        message(FATAL_ERROR "Invalid radio mode configuration")
    endif()

    if(CONFIG_ZB_ZCZR)
        set(device_mode ".zczr")
    elseif(CONFIG_ZB_ZED)
        set(device_mode ".zed")
    else()
        message(FATAL_ERROR "Invalid device mode configuration")
    endif()

    if(CONFIG_ZB_DEBUG_MODE)
        set(build_mode ".debug")
    else()
        set(build_mode ".release")
    endif()

    # Add esp-zigbee library
    add_prebuilt_library(esp_zigbee_lib "${target_lib_dir}/libesp-zigbee${build_mode}.a")
    list(APPEND ESP_ZIGBEE_LIBS esp_zigbee_lib)

    # Add esp-zigbee-core library
    add_prebuilt_library(esp_zigbee_core_lib "${target_lib_dir}/libesp-zigbee-core${device_mode}${build_mode}.a")
    list(APPEND ESP_ZIGBEE_LIBS esp_zigbee_core_lib)

    # Add esp-zigbee-idf library
    add_prebuilt_library(esp_zigbee_idf_lib "${target_lib_dir}/libesp-zigbee-idf${radio_mode}${build_mode}.a"
                         PRIV_REQUIRES esp_timer vfs ieee802154 openthread mbedtls nvs_flash)
    list(APPEND ESP_ZIGBEE_LIBS esp_zigbee_idf_lib)

    target_link_libraries(${COMPONENT_LIB} INTERFACE ${ESP_ZIGBEE_LIBS})

endif()
