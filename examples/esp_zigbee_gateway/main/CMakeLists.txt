idf_component_register(SRCS "esp_zigbee_gateway.c"
                    INCLUDE_DIRS ".")

if(CONFIG_ZIGBEE_GW_AUTO_UPDATE_RCP)
    add_custom_target(rcp_image_generation ALL
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../create_ota_image.py
    --rcp-build-dir ${CMAKE_SOURCE_DIR}/../esp_zigbee_rcp/build
    --target-file ${CMAKE_CURRENT_BINARY_DIR}/spiffs_image/ot_rcp_0/rcp_image
    )
    spiffs_create_partition_image(rcp_fw ${CMAKE_CURRENT_BINARY_DIR}/spiffs_image FLASH_IN_PROJECT
                              DEPENDS rcp_image_generation)
endif()
