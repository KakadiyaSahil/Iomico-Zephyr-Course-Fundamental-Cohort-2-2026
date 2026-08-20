cmake_minimum_required(VERSION 3.20.0)

# ============================================================
# Iomico Zephyr Application
# ============================================================

# ------------------------------------------------------------
# Workspace
#
# app/
#   -> Examples/
#   -> Fundamental-Cohort-2-2026/
#   -> Iomico-Zephyr-Course/
# ------------------------------------------------------------
get_filename_component(IOMICO_WORKSPACE
    "${CMAKE_CURRENT_LIST_DIR}/../../.."
    ABSOLUTE
)


# ------------------------------------------------------------
# Zephyr
# ------------------------------------------------------------
set(ZEPHYR_BASE
    "${IOMICO_WORKSPACE}/deps/zephyr"
)

# ------------------------------------------------------------
# Zephyr toolchain
# ------------------------------------------------------------
set(ZEPHYR_TOOLCHAIN_VARIANT zephyr)

# ------------------------------------------------------------
# Zephyr SDK
# ------------------------------------------------------------
set(ZEPHYR_SDK_INSTALL_DIR
    "${IOMICO_WORKSPACE}/zephyr-sdk-0.17.2"
)

# ------------------------------------------------------------
# Espressif HAL
# ------------------------------------------------------------
set(ESPRESSIF_HAL_PATH
    "${IOMICO_WORKSPACE}/deps/modules/hal/espressif"
)

# ------------------------------------------------------------
# ESP32 esptool
# ------------------------------------------------------------
set(ESPTOOL
    "${ESPRESSIF_HAL_PATH}/tools/esptool_py/esptool.py"
)

# ------------------------------------------------------------
# Device Tree overlay
# ------------------------------------------------------------
set(DTC_OVERLAY_FILE
    "${CMAKE_CURRENT_LIST_DIR}/boards_overlay/Espressif/esp32_devkitc_esp32_procpu.overlay"
)

# ------------------------------------------------------------
# Validate required paths
# ------------------------------------------------------------
if(NOT EXISTS "${ZEPHYR_BASE}")
    message(FATAL_ERROR
        "Zephyr source not found: ${ZEPHYR_BASE}"
    )
endif()

if(NOT EXISTS "${ZEPHYR_SDK_INSTALL_DIR}")
    message(FATAL_ERROR
        "Zephyr SDK not found: ${ZEPHYR_SDK_INSTALL_DIR}"
    )
endif()

if(NOT EXISTS "${ESPTOOL}")
    message(FATAL_ERROR
        "esptool.py not found: ${ESPTOOL}"
    )
endif()

if(NOT EXISTS "${DTC_OVERLAY_FILE}")
    message(FATAL_ERROR
        "Device Tree overlay not found: ${DTC_OVERLAY_FILE}"
    )
endif()

# ------------------------------------------------------------
# Find Zephyr
# ------------------------------------------------------------
find_package(
    Zephyr
    REQUIRED
    HINTS "${ZEPHYR_BASE}"
)

# ------------------------------------------------------------
# ESP32 flash tool
# ------------------------------------------------------------
set(ESPTOOL
    "${IOMICO_WORKSPACE}/deps/modules/hal/espressif/tools/esptool_py/esptool.py"
)

if(NOT EXISTS "${ESPTOOL}")
    message(FATAL_ERROR "esptool.py not found: ${ESPTOOL}")
endif()

set(BOARD_RUNNER_ARGS
    --esp-tool "${ESPTOOL}"
)

project(app)

# ------------------------------------------------------------
# Application source
# ------------------------------------------------------------
target_sources(
    app
    PRIVATE
        src/main.cpp
)

# ------------------------------------------------------------
# Application include directory
# ------------------------------------------------------------
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/include")
    target_include_directories(
        app
        PRIVATE
            "${CMAKE_CURRENT_LIST_DIR}/include"
    )
endif()

# ------------------------------------------------------------
# Display configuration
# ------------------------------------------------------------
message(STATUS "==========================================")
message(STATUS " Iomico Zephyr Application")
message(STATUS "==========================================")
message(STATUS "Workspace   : ${IOMICO_WORKSPACE}")
message(STATUS "Zephyr      : ${ZEPHYR_BASE}")
message(STATUS "SDK         : ${ZEPHYR_SDK_INSTALL_DIR}")
message(STATUS "Toolchain   : ${ZEPHYR_TOOLCHAIN_VARIANT}")
message(STATUS "HAL         : ${ESPRESSIF_HAL_PATH}")
message(STATUS "esptool.py  : ${ESPTOOL}")
message(STATUS "Overlay     : ${DTC_OVERLAY_FILE}")
message(STATUS "==========================================")