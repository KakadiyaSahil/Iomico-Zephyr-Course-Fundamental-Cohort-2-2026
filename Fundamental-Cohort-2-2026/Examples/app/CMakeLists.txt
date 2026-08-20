cmake_minimum_required(VERSION 3.20.0)

set(DTC_OVERLAY_FILE
    ${CMAKE_CURRENT_LIST_DIR}/../../boards/esp32_devkitc_esp32_procpu.overlay
)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(app)



target_sources(app PRIVATE src/main.cpp)