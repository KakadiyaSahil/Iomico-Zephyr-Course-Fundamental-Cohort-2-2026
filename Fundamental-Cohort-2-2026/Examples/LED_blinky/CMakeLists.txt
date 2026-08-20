cmake_minimum_required(VERSION 3.20.0)

# ============================================================
# Iomico Zephyr Application
# ============================================================


# ============================================================
# 1. Workspace Configuration
# ============================================================

get_filename_component(
    IOMICO_WORKSPACE
    "${CMAKE_CURRENT_LIST_DIR}/../../.."
    ABSOLUTE
)


# ============================================================
# 2. Zephyr Configuration
# ============================================================

set(ZEPHYR_BASE
    "${IOMICO_WORKSPACE}/deps/zephyr"
)

set(ZEPHYR_TOOLCHAIN_VARIANT
    zephyr
)

set(ZEPHYR_SDK_INSTALL_DIR
    "${IOMICO_WORKSPACE}/zephyr-sdk-0.17.2"
)


# ============================================================
# 3. ESP32 / Espressif Configuration
# ============================================================

set(ESPRESSIF_HAL_PATH
    "${IOMICO_WORKSPACE}/deps/modules/hal/espressif"
)

set(ESPTOOL
    "${ESPRESSIF_HAL_PATH}/tools/esptool_py/esptool.py"
)


# ============================================================
# 4. Device Tree Configuration
# ============================================================

set(DTC_OVERLAY_FILE
    "${CMAKE_CURRENT_LIST_DIR}/boards_overlay/Espressif/esp32_devkitc_esp32_procpu.overlay"
)


# ============================================================
# 5. Validate Workspace Paths
# ============================================================

message(STATUS "")
message(STATUS "============================================================")
message(STATUS " Workspace Validation")
message(STATUS "============================================================")


# ------------------------------------------------------------
# Workspace
# ------------------------------------------------------------

if(IS_DIRECTORY "${IOMICO_WORKSPACE}")
    message(STATUS "[OK]      Workspace : ${IOMICO_WORKSPACE}")
else()
    message(FATAL_ERROR
        "[ERROR] Workspace not found: ${IOMICO_WORKSPACE}"
    )
endif()


# ------------------------------------------------------------
# Zephyr
# ------------------------------------------------------------

if(IS_DIRECTORY "${ZEPHYR_BASE}")
    message(STATUS "[OK]      Zephyr    : ${ZEPHYR_BASE}")
else()
    message(FATAL_ERROR
        "[ERROR] Zephyr source not found: ${ZEPHYR_BASE}"
    )
endif()


# ------------------------------------------------------------
# Zephyr SDK
# ------------------------------------------------------------

if(IS_DIRECTORY "${ZEPHYR_SDK_INSTALL_DIR}")
    message(STATUS "[OK]      Zephyr SDK: ${ZEPHYR_SDK_INSTALL_DIR}")
else()
    message(FATAL_ERROR
        "[ERROR] Zephyr SDK not found: ${ZEPHYR_SDK_INSTALL_DIR}"
    )
endif()


# ------------------------------------------------------------
# Espressif HAL
# ------------------------------------------------------------

if(IS_DIRECTORY "${ESPRESSIF_HAL_PATH}")
    message(STATUS "[OK]      ESP HAL   : ${ESPRESSIF_HAL_PATH}")
else()
    message(FATAL_ERROR
        "[ERROR] Espressif HAL not found: ${ESPRESSIF_HAL_PATH}"
    )
endif()


# ------------------------------------------------------------
# esptool.py
# ------------------------------------------------------------

if(EXISTS "${ESPTOOL}")
    message(STATUS "[OK]      esptool   : ${ESPTOOL}")
else()
    message(FATAL_ERROR
        "[ERROR] esptool.py not found: ${ESPTOOL}"
    )
endif()


# ------------------------------------------------------------
# Device Tree Overlay
# ------------------------------------------------------------

if(EXISTS "${DTC_OVERLAY_FILE}")
    message(STATUS "[OK]      Overlay   : ${DTC_OVERLAY_FILE}")
else()
    message(FATAL_ERROR
        "[ERROR] Device Tree overlay not found: ${DTC_OVERLAY_FILE}"
    )
endif()


# ============================================================
# 6. Zephyr Initialization
# ============================================================

find_package(
    Zephyr
    REQUIRED
    HINTS "${ZEPHYR_BASE}"
)

project(LED_blinky)


# ============================================================
# 7. ESP32 Application Configuration
# ============================================================

set(BOARD_RUNNER_ARGS
    --esp-tool "${ESPTOOL}"
)


# ============================================================
# 8. Application Sources
# ============================================================

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

    target_sources(
        app
        PRIVATE
            src/main.cpp
    )

    message(STATUS "[OK]      Source    : src/main.cpp")

else()

    message(STATUS "[INFO]    Source    : src/main.cpp not found")

endif()


# ============================================================
# 9. Application Include Directory
# ============================================================

if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include")

    target_include_directories(
        app
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

    message(STATUS "[OK]      Include   : include/")

else()

    message(STATUS "[INFO]    Include   : include/ not found")

endif()


# ============================================================
# 10. Display Configuration
# ============================================================

message(STATUS "")
message(STATUS "============================================================")
message(STATUS " Iomico Zephyr Application")
message(STATUS "============================================================")
message(STATUS " Workspace        : ${IOMICO_WORKSPACE}")
message(STATUS " Zephyr           : ${ZEPHYR_BASE}")
message(STATUS " SDK              : ${ZEPHYR_SDK_INSTALL_DIR}")
message(STATUS " Toolchain        : ${ZEPHYR_TOOLCHAIN_VARIANT}")
message(STATUS " ESP HAL          : ${ESPRESSIF_HAL_PATH}")
message(STATUS " esptool.py       : ${ESPTOOL}")
message(STATUS " Device Tree      : ${DTC_OVERLAY_FILE}")
message(STATUS "============================================================")
message(STATUS "")