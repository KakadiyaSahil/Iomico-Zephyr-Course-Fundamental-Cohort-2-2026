cmake_minimum_required(VERSION 3.20.0)

get_filename_component(IOMICO_WORKSPACE
    "${CMAKE_CURRENT_LIST_DIR}/../../.."
    ABSOLUTE
)

set(ZEPHYR_BASE
    "${IOMICO_WORKSPACE}/deps/zephyr"
)

set(ZEPHYR_TOOLCHAIN_VARIANT zephyr)

set(ZEPHYR_SDK_INSTALL_DIR
    "${IOMICO_WORKSPACE}/zephyr-sdk-0.17.2"
)

find_package(Zephyr REQUIRED HINTS "${ZEPHYR_BASE}")

project(hello_world)

target_sources(app PRIVATE src/main.cpp)