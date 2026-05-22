export ESP_IDF_HTTP="https://gitlab-ci-token:${CI_JOB_TOKEN}@${ESP_GITLAB}/espressif/esp-idf.git"
export ESP_ZIGBEE_SDK_HTTP="https://gitlab-ci-token:${CI_JOB_TOKEN}@${ESP_GITLAB}/espressif/esp-zigbee-sdk.git"
shopt -s globstar # Allow ** for recursive matches

function build_ot_rcp() {
    local target="$1"
    pushd $CI_PROJECT_DIR/esp-idf/examples/openthread/ot_rcp || exit 1
    rm -rf build dependencies.lock sdkconfig.old sdkconfig
    echo "CONFIG_OPENTHREAD_NCP_VENDOR_HOOK=y" >> sdkconfig.defaults
    idf.py set-target ${target}
    idf.py build
    popd
}

function init_ssh() {
    mkdir -p ~/.ssh
    chmod 700 ~/.ssh
    echo -n "${GITLAB_KEY}" >~/.ssh/id_rsa_base64
    base64 --decode --ignore-garbage ~/.ssh/id_rsa_base64 >~/.ssh/id_rsa
    chmod 600 ~/.ssh/id_rsa
    echo -e "Host gitlab.espressif.cn\n\tStrictHostKeyChecking no\n" >>~/.ssh/config
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
}

function sync_branch() {
    local source_branch="$1"
    local target_branch="$2"
    git config --global user.email "bot@espressif.com"
    git config --global user.name "BOT"
    git remote set-url --push origin "${ZIGBEE_SDK_REPO_URL}"
    git fetch origin
    git checkout -B ${source_branch} origin/${source_branch}
    git reset --hard origin/${target_branch}
    git push origin ${source_branch}
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

function update_lib_path() {
    pushd $CI_PROJECT_DIR
    find examples -type f -path "*/main/idf_component.yml" 2>/dev/null | while read -r f; do
        echo "Processing $f"
        sed -i '/espressif\/esp-zigbee-lib/ a\    path: "${CI_PROJECT_DIR}/components/esp-zigbee-lib"' "$f"
    done
    find components -type f -name "idf_component.yml" 2>/dev/null | while read -r f; do
        echo "Processing $f"
        sed -i '/espressif\/esp-zigbee-lib/ a\    path: "${CI_PROJECT_DIR}/components/esp-zigbee-lib"' "$f"
    done
    popd
}

function prepare_esp_zigbee_lib() {
    echo "UPSTREAM_JOB_ID: ${UPSTREAM_JOB_ID}"
    local url="${CI_API_V4_URL}/projects/${UPSTREAM_PROJECT_ID}/jobs/${UPSTREAM_JOB_ID}/artifacts"
    echo "prepare_esp_zigbee_lib: download artifacts from upstream job ${UPSTREAM_JOB_ID}"
    pushd ${CI_PROJECT_DIR}
    curl --location --fail --silent --show-error \
        --header "JOB-TOKEN: ${CI_JOB_TOKEN}" \
        "${url}" -o artifacts.zip
    ls -al
    unzip -o artifacts.zip
    cp -rf esp-zigbee-lib/* "${CI_PROJECT_DIR}/components/esp-zigbee-lib/"
    rm -f artifacts.zip
    popd
}
