export ESP_ZIGBEE_SDK_HTTP="https://gitlab-ci-token:${CI_JOB_TOKEN}@${ESP_GITLAB}/espressif/esp-zigbee-sdk.git"
export ESP_IDF_HTTP="https://gitlab-ci-token:${CI_JOB_TOKEN}@${ESP_GITLAB}/espressif/esp-idf.git"
shopt -s globstar # Allow ** for recursive matches

function setup_idf() {
    idf_ref="${CI_COMMIT_REF_NAME}"
    [ "$idf_ref" == "master" ] && idf_ref="${IDF_VERSION}"
    echo "Try to fetch ${idf_ref}"
    git clone --depth=1 -b ${idf_ref} ${ESP_IDF_HTTP} || git clone --depth=1 -b ${IDF_VERSION} ${ESP_IDF_HTTP}

    pushd esp-idf
    git submodule update --init --depth=1
    ./install.sh
    . ./export.sh
    popd
}

function setup_esp_sdk() {
    git clone --depth=1 -b $CI_COMMIT_REF_NAME ${ESP_ZIGBEE_SDK_HTTP} || git clone --depth=1 -b main ${ESP_ZIGBEE_SDK_HTTP} 
}

function update_cmake_dependency() {
    echo ${IDF_PATH}
    cp -r $CI_PROJECT_DIR/esp-zigbee-sdk/components/esp-zigbee-lib ${IDF_PATH}/components/espressif__esp-zigbee-lib
    # copy esp-zboss-lib to esp-idf
    mkdir ${IDF_PATH}/components/espressif__esp-zboss-lib
    cp -r $CI_PROJECT_DIR/include ${IDF_PATH}/components/espressif__esp-zboss-lib
    cp -r $CI_PROJECT_DIR/lib ${IDF_PATH}/components/espressif__esp-zboss-lib
    cp $CI_PROJECT_DIR/idf_component.yml ${IDF_PATH}/components/espressif__esp-zboss-lib
    cp $CI_PROJECT_DIR/CMakeLists.txt ${IDF_PATH}/components/espressif__esp-zboss-lib
    ls -lf ${IDF_PATH}/components/espressif__esp-zboss-lib
    # end copy
    sed -i "/\besp-zboss-lib\b/d;/\besp-zigbee-lib\b/d" ${IDF_PATH}/examples/zigbee/**/main/idf_component.yml
    sed -i "/\besp-zboss-lib\b/d;/\besp-zigbee-lib\b/d" $CI_PROJECT_DIR/esp-zigbee-sdk/examples/**/main/idf_component.yml
    sed -i "/\besp-zboss-lib\b/d;/\besp-zigbee-lib\b/d" $CI_PROJECT_DIR/esp-zigbee-sdk/components/*/idf_component.yml
}

function build_rcp_gateway() {
    mv $CI_PROJECT_DIR/esp-zigbee-sdk/examples/esp_zigbee_gateway/sdkconfig.defaults $CI_PROJECT_DIR/esp-zigbee-sdk/examples/esp_zigbee_gateway/sdkconfig.defaults.ori
    cp $CI_PROJECT_DIR/esp-zigbee-sdk/tools/ci/sdkconfig_for_gateway_ci.defaults $CI_PROJECT_DIR/esp-zigbee-sdk/examples/esp_zigbee_gateway/sdkconfig.defaults

    pushd $CI_PROJECT_DIR/esp-idf/examples/openthread/ot_rcp
    echo "CONFIG_OPENTHREAD_NCP_VENDOR_HOOK=y" >> sdkconfig.defaults
    idf.py set-target esp32h2
    idf.py build
    popd

    pushd $CI_PROJECT_DIR/esp-zigbee-sdk/examples/esp_zigbee_gateway
    idf.py set-target esp32s3
    idf.py build
    popd

    mv $CI_PROJECT_DIR/esp-zigbee-sdk/examples/esp_zigbee_gateway/sdkconfig.defaults.ori $CI_PROJECT_DIR/esp-zigbee-sdk/examples/esp_zigbee_gateway/sdkconfig.defaults
}
