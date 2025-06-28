idf_component_register(
    SRCS "src/create_endpoints.c" "src/esp_zigbee_aps_nwk.c" "src/main.c"
    SRC_DIRS "src" "../../common/zcl_utility/src"
    INCLUDE_DIRS "include" "../../common/zcl_utility/include" 
    )