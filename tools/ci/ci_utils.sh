export ESP_IDF_HTTP="https://gitlab-ci-token:${CI_JOB_TOKEN}@${ESP_GITLAB}/espressif/esp-idf.git"
export ESP_ZIGBEE_SDK_HTTP="https://gitlab-ci-token:${CI_JOB_TOKEN}@${ESP_GITLAB}/espressif/esp-zigbee-sdk.git"

shopt -s globstar # Allow ** for recursive matches

function build_ot_rcp() {
    pushd $CI_PROJECT_DIR/esp-idf/examples/openthread/ot_rcp || exit 1
    echo "CONFIG_OPENTHREAD_NCP_VENDOR_HOOK=y" >> sdkconfig.defaults
    idf.py set-target esp32h2
    idf.py build
    popd
}

function setup_idf() {
    pushd $CI_PROJECT_DIR
    idf_ref="${CI_COMMIT_REF_NAME}"
    [ "$idf_ref" == "main" ] && idf_ref="${IDF_VERSION}"
    echo "Try to fetch ${idf_ref}"
    git clone --depth=1 -b ${idf_ref} ${ESP_IDF_HTTP} || git clone --depth=1 -b ${IDF_VERSION} ${ESP_IDF_HTTP}
    popd

    pushd esp-idf
    git config --global url."https://gitlab-ci-token:${CI_JOB_TOKEN}@${ESP_GITLAB}/".insteadOf "https://${ESP_GITLAB}/"
    git submodule update --init --depth=1
    # If IDF version is 5.3.4, download and apply patch
    if [ "${IDF_VERSION}" == "v5.3.4" ]; then
        commit_hash="b600b6a176f030b71780691d954c0f4feb9b0944"
        git fetch origin ${commit_hash} 2>/dev/null || true
        git cherry-pick ${commit_hash} || echo "Cherry-pick failed, continuing..."
    fi
    ./install.sh
    . ./export.sh
    popd

    build_ot_rcp
}

function setup_esp_zigbee_sdk() {
    git clone --depth=1 -b ${CI_COMMIT_REF_NAME} ${ESP_ZIGBEE_SDK_HTTP} || git clone --depth=1 -b dev/2.x ${ESP_ZIGBEE_SDK_HTTP}
    export ESP_ZB_SDK_PATH="${CI_PROJECT_DIR}/esp-zigbee-sdk"
    pushd esp-zigbee-sdk
    echo "Current checked out branch: $(git branch --show-current)"
    popd
}

function build_example() {
    # Arguments:
    # $1 -> example_dir: The path to the example directory to be built
    # $@ -> subsequent arguments: List of target platforms (e.g., esp32c6, esp32s3, etc.)
    local example_dir="$1"
    shift
    pushd $example_dir || exit 1
    for target in "$@"; do
        echo "build example: ${example_dir} for target: ${target}"
        idf.py -B build_${target}_default set-target ${target}
        idf.py -B build_${target}_default build
    done
    popd
}

function update_gateway_wifi_config() {
    local gateway_dir="$1"
    pushd "$gateway_dir" || exit 1

    sed -i '/^CONFIG_EXAMPLE_WIFI_SSID=.*/d' sdkconfig.defaults
    sed -i '/^CONFIG_EXAMPLE_WIFI_PASSWORD=.*/d' sdkconfig.defaults
    {
        echo "CONFIG_EXAMPLE_WIFI_SSID=\"zigbee_ci_1\""
        echo "CONFIG_EXAMPLE_WIFI_PASSWORD=\"espressif\""
    } >> sdkconfig.defaults
    popd
}

function build_rcp_gateway() {
    # Arguments:
    # $1 -> gateway_dir: Path to the Zigbee gateway example directory
    # $2 -> update_rcp: Boolean flag ("true" or "false") to enable RCP update configuration
    local gateway_dir="$1"
    local update_rcp="$2"
    update_gateway_wifi_config $gateway_dir

    pushd $gateway_dir
    if [ "$update_rcp" == "true" ]; then
        sed -i '/^CONFIG_ZIGBEE_GW_AUTO_UPDATE_RCP=.*/d' $gateway_dir/sdkconfig.defaults
        echo 'CONFIG_ZIGBEE_GW_AUTO_UPDATE_RCP=y' >> $gateway_dir/sdkconfig.defaults
    fi
    echo 'CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0=n' >> $gateway_dir/sdkconfig.defaults
    echo 'CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1=n' >> $gateway_dir/sdkconfig.defaults
    build_example $gateway_dir esp32s3
    popd
}

function update_lib_path() {
    find examples -type f -path "*/main/idf_component.yml" 2>/dev/null | while read -r f; do
        echo "Processing $f"
        sed -i '/espressif\/esp-zigbee-lib/ a\    path: "${CI_PROJECT_DIR}/components/esp-zigbee-lib"' "$f"
    done
    find components -type f -name "idf_component.yml" 2>/dev/null | while read -r f; do
        echo "Processing $f"
        sed -i '/espressif\/esp-zigbee-lib/ a\    path: "${CI_PROJECT_DIR}/components/esp-zigbee-lib"' "$f"
    done
}

