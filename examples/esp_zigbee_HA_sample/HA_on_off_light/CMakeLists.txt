# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)
set(EXTRA_COMPONENT_DIRS
    $ENV{IDF_PATH}/examples/common_components/led_strip
    ${CMAKE_CURRENT_SOURCE_DIR}/../../common/light_driver
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../components/esp-zigbee-lib
    )
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(on_off_light_bulb)
