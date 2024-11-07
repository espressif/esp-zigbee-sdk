#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
ESP_ZIGBEE_SDK="$(realpath ${SCRIPT_DIR}/../..)"

declare -A LIB_COMPONENTS=(
    ["espressif__esp-zigbee-lib"]="${ESP_ZIGBEE_SDK}/components/esp-zigbee-lib"
    ["espressif__esp-zboss-lib"]="${IDF_PATH}/../esp-zboss-lib"
)

set -ex
shopt -s globstar # Allow ** for recursive matches

update_dependency(){
    # Remove the dependencies on managed LIB components.
    #   for examples in ESP-ZIGBEE-SDK
    sed -i "/\besp-zboss-lib\b/d;/\besp-zigbee-lib\b/d" "${ESP_ZIGBEE_SDK}"/examples/**/main/idf_component.yml
    #   for components in ESP-ZIGBEE-SDK
    sed -i "/\besp-zboss-lib\b/d;/\besp-zigbee-lib\b/d" "${ESP_ZIGBEE_SDK}"/components/*/idf_component.yml

    # Link the local LIB components to the components directory of ESP-IDF
    for component in "${!LIB_COMPONENTS[@]}"; do
        local link_name="${IDF_PATH}/components/${component}"
        local link_target="${LIB_COMPONENTS[${component}]}"
        if [ ! -e "${link_name}" ]; then
            ln -s "${link_target}" "${link_name}"
        fi
        echo "create link ${link_name} -> ${link_target}"
    done
}

main() {
    pushd "$(pwd)"

    update_dependency

    popd
}

main
