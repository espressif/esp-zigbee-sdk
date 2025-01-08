export ESP_IDF_HTTP="https://gitlab-ci-token:${CI_JOB_TOKEN}@${ESP_GITLAB}/espressif/esp-idf.git"
export ESP_ZBOSS_LIB_HTTP="https://gitlab-ci-token:${CI_JOB_TOKEN}@${ESP_GITLAB}/espressif/esp-zboss-lib.git"

function setup_idf() {
    pushd $CI_PROJECT_DIR
    idf_ref="${CI_COMMIT_REF_NAME}"
    [ "$idf_ref" == "main" ] && idf_ref="${IDF_VERSION}"
    echo "Try to fetch ${idf_ref}"
    git clone --depth=1 -b ${idf_ref} ${ESP_IDF_HTTP} || git clone --depth=1 -b ${IDF_VERSION} ${ESP_IDF_HTTP}
    popd

    pushd esp-idf
    git submodule update --init --depth=1
    ./install.sh
    . ./export.sh
    popd
}

function setup_zboss_lib() {
    pushd $CI_PROJECT_DIR
    git clone --depth=1 -b $CI_COMMIT_REF_NAME ${ESP_ZBOSS_LIB_HTTP} || git clone --depth=1 -b master ${ESP_ZBOSS_LIB_HTTP}
    popd
}

function build_rcp_gateway() {
    mv $CI_PROJECT_DIR/examples/esp_zigbee_gateway/sdkconfig.defaults $CI_PROJECT_DIR/examples/esp_zigbee_gateway/sdkconfig.defaults.ori
    cp $CI_PROJECT_DIR/tools/ci/sdkconfig_for_gateway_ci.defaults $CI_PROJECT_DIR/examples/esp_zigbee_gateway/sdkconfig.defaults
  
    pushd $CI_PROJECT_DIR/esp-idf/examples/openthread/ot_rcp
    echo "CONFIG_OPENTHREAD_NCP_VENDOR_HOOK=y" >> sdkconfig.defaults
    idf.py set-target esp32h2
    idf.py build
    popd

    pushd $CI_PROJECT_DIR/examples/esp_zigbee_gateway
    idf.py set-target esp32s3
    idf.py build
    popd

    mv $CI_PROJECT_DIR/examples/esp_zigbee_gateway/sdkconfig.defaults.ori $CI_PROJECT_DIR/examples/esp_zigbee_gateway/sdkconfig.defaults
}
