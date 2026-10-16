cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

list(PREPEND SDKCONFIG_DEFAULTS "../utils/example_common/sdkconfig.mbedtls_minimal" "sdkconfig.defaults")

set(COMPONENTS main)

project(nvram_migration)
