cmake_minimum_required(VERSION 3.16)

if (CONFIG_ZB_ENABLED)
    set(src_dirs "")
    set(include_dirs include)
endif()

if(CONFIG_ZB_RADIO_SPINEL_UART)
    list(APPEND src_dirs src/radio_spinel)
    list(APPEND include_dirs include/radio_spinel)
endif()

idf_component_register(SRC_DIRS "${src_dirs}"
                       INCLUDE_DIRS "${include_dirs}"
                       REQUIRES driver vfs ieee802154 openthread espressif__esp-zboss-lib
)

if(CONFIG_ZB_ENABLED)

    set(ESP_ZIGBEE_API_LIBS "")
    set(zboss_port_type ".native")
    set(zboss_port_mode "")

    if(CONFIG_ZB_ZCZR)
        if(CONFIG_ZB_DEBUG_MODE)
            add_prebuilt_library(esp_zigbee_api_lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/${idf_target}/libesp_zb_api.zczr.debug.a" REQUIRES espressif__esp-zboss-lib)
        else()
            add_prebuilt_library(esp_zigbee_api_lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/${idf_target}/libesp_zb_api.zczr.a" REQUIRES espressif__esp-zboss-lib)
        endif()
    elseif(CONFIG_ZB_ZED)
        if(CONFIG_ZB_DEBUG_MODE)
            add_prebuilt_library(esp_zigbee_api_lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/${idf_target}/libesp_zb_api.ed.debug.a" REQUIRES espressif__esp-zboss-lib)
        else()
            add_prebuilt_library(esp_zigbee_api_lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/${idf_target}/libesp_zb_api.ed.a" REQUIRES espressif__esp-zboss-lib)
        endif()
    elseif(CONFIG_ZB_ZGPD)
        add_prebuilt_library(esp_zigbee_api_lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/${idf_target}/libesp_zb_api.gpd.a" REQUIRES espressif__esp-zboss-lib)
    endif()

    if (CONFIG_ZB_RADIO_SPINEL_UART)
        set(zboss_port_type ".remote")
    endif()
    if(CONFIG_ZB_DEBUG_MODE)
        set(zboss_port_mode ".debug")
    endif()

    add_prebuilt_library(zboss_port_lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/${idf_target}/libzboss_port${zboss_port_type}${zboss_port_mode}.a"
                         PRIV_REQUIRES ieee802154 efuse esp_system esp_hw_support
                         REQUIRES driver)

    list(APPEND ESP_ZIGBEE_API_LIBS esp_zigbee_api_lib zboss_port_lib)

    target_link_libraries(${COMPONENT_LIB} INTERFACE ${ESP_ZIGBEE_API_LIBS})
    target_compile_options(${COMPONENT_LIB} INTERFACE $<$<COMPILE_LANGUAGE:C>:-Wno-strict-prototypes>)

    if (CONFIG_ZB_RADIO_SPINEL_UART)
        idf_component_get_property(openthread_lib openthread COMPONENT_LIB)
        idf_component_get_property(zigbee_lib espressif__esp-zigbee-lib COMPONENT_LIB)
        target_link_libraries(${COMPONENT_LIB} INTERFACE zboss_port_lib $<TARGET_FILE:${zigbee_lib}> $<TARGET_FILE:${openthread_lib}> zboss_port_lib)
    endif()
endif()
