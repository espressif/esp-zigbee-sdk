idf_component_register(SRC_DIRS "src" "src/ha" "src/zcl" "src/zdo"
                       INCLUDE_DIRS "include" "include/ha" "include/zcl" "include/zdo"
                       PRIV_INCLUDE_DIRS "src/priv"
                       PRIV_REQUIRES nvs_flash driver)