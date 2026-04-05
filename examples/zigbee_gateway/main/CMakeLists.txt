idf_component_register(SRC_DIRS "."
                       PRIV_INCLUDE_DIRS "."
                       PRIV_REQUIRES vfs nvs_flash openthread spiffs esp_wifi)

idf_build_get_property(python PYTHON)
if(CONFIG_ZIGBEE_GW_AUTO_UPDATE_RCP)
    add_custom_target(rcp_image_generation ALL
    COMMAND ${python} ${CMAKE_CURRENT_SOURCE_DIR}/../generate_rcp_image.py
    --rcp-build-dir ${IDF_PATH}/examples/openthread/ot_rcp/build
    --target-file ${CMAKE_CURRENT_BINARY_DIR}/spiffs_image/ot_rcp_0/rcp_image
    )
    spiffs_create_partition_image(rcp_fw ${CMAKE_CURRENT_BINARY_DIR}/spiffs_image FLASH_IN_PROJECT
                                  DEPENDS rcp_image_generation)
endif()
