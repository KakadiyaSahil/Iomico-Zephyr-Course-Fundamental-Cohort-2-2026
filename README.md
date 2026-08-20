# Iomico Zephyr Course

A structured Zephyr RTOS development workspace for the Iomico Embedded Systems course.

> **Platform:** Windows 10 / Windows 11  
> **Shell:** Windows PowerShell  
> **Environment:** Python virtual environment + West + Zephyr RTOS + Zephyr SDK  
> **Target:** ESP32 / Espressif boards specially - ESP32-Wroom-32 https://documentation.espressif.com/esp32-wroom-32_datasheet_en.pdf

This README documents the commands used to set up, build, flash, debug, and manage the Iomico Zephyr course repository.

## Repository Structure

```text
Iomico-Zephyr-Course/
│
├── Fundamental-Cohort-2-2026/
│   └── Examples/
│       ├── app/
│       │   ├── CMakeLists.txt
│       │   └── src/
│       │       └── main.cpp
│       │
│       ├── hello_world/
│       │   ├── CMakeLists.txt
│       │   └── src/
│       │       └── main.cpp
│       │
│       └── LED_blinky/
│           ├── CMakeLists.txt
│           ├── src/
│           │   └── main.cpp
│           └── boards_overlay/
│
├── Intermediate-Cohort-1-2026/
│
├── manifest_file/
│   └── west.yml
│
├── .gitignore
└── README.md
```

---

# 1. Prerequisites

Install the following:

- Git
- Python 3
- Python virtual environment
- West
- CMake
- Ninja
- Zephyr SDK
- Required board/toolchain dependencies

For the current workspace, the Zephyr SDK is:

```text
zephyr-sdk-0.17.2
```

---

# 2. Create Python Virtual Environment

From the repository root:

```powershell
python -m venv .venv
```

Activate it on Windows PowerShell:

```powershell
.venv\Scripts\Activate.ps1
```

Verify Python:

```powershell
python --version
```

Verify West:

```powershell
west --version
```

If West is not installed:

```powershell
pip install west
```

---

# 3. Initialize the West Workspace

The repository contains a local West manifest.

From the repository root:

```powershell
west init -l .
```

This creates the `.west` directory and configures the current repository as the manifest repository.

Verify:

```powershell
west topdir
```

You should get the repository workspace path.

---

# 4. Download / Update Zephyr Dependencies

Run:

```powershell
west update
```

This uses the manifest to download and synchronize Zephyr and its required modules.

After updating, verify:

```powershell
west list
```

---

# 5. Check the West Manifest

The manifest is located in:

```text
manifest_file/west.yml
```

To inspect the manifest:

```powershell
type manifest_file\west.yml
```

Or:

```powershell
Get-Content manifest_file\west.yml
```

---

# 6. Set Up Zephyr Environment

If required by the installation, export the Zephyr environment:

```powershell
west zephyr-export
```

Check the Zephyr installation:

```powershell
west list zephyr
```

---

# 7. Zephyr Workspace Configuration

The current projects use the following workspace structure:

```text
Iomico-Zephyr-Course/
├── deps/
├── zephyr-sdk-0.17.2/
├── .west/
└── Fundamental-Cohort-2-2026/
```

The application CMake files locate Zephyr relative to the workspace:

```cmake
get_filename_component(
    IOMICO_WORKSPACE
    "${CMAKE_CURRENT_LIST_DIR}/../../.."
    ABSOLUTE
)

set(ZEPHYR_BASE
    "${IOMICO_WORKSPACE}/deps/zephyr"
)
```

This allows the examples to use the same workspace-level Zephyr installation.

---

# 8. Build a Zephyr Application

General syntax:

```powershell
west build -b <board> <application_directory>
```

Example:

```powershell
west build -b esp32_devkitc/esp32/procpu .\Fundamental-Cohort-2-2026\Examples\app
```

Another example:

```powershell
west build -b esp32_devkitc/esp32/procpu .\Fundamental-Cohort-2-2026\Examples\hello_world
```

---

# 9. Clean Build

If you changed the board, Device Tree, CMake configuration, or other build configuration, use:

```powershell
west build -b esp32_devkitc/esp32/procpu .\Fundamental-Cohort-2-2026\Examples\app -p always
```

Or remove the build directory and rebuild:

```powershell
west build -t pristine
```

Then:

```powershell
west build -b esp32_devkitc/esp32/procpu .\Fundamental-Cohort-2-2026\Examples\app
```

---

# 10. Build Directory

A typical build directory contains generated files such as:

```text
build/
├── CMakeCache.txt
├── CMakeFiles/
├── zephyr/
└── ...
```

Build output should normally not be committed to Git.

The `.gitignore` excludes generated build/environment files.

---

# 11. Device Tree Overlays

Device Tree overlays can be used to customize board hardware configuration.

Example:

```text
Fundamental-Cohort-2-2026/
└── Examples/
    └── app/
        └── boards_overlay/
            └── Espressif/
                └── esp32_devkitc_esp32_procpu.overlay
```

The CMake configuration can explicitly select the overlay:

```cmake
set(DTC_OVERLAY_FILE
    "${CMAKE_CURRENT_LIST_DIR}/boards_overlay/Espressif/esp32_devkitc_esp32_procpu.overlay"
)
```

This allows the application to use a custom Device Tree configuration without modifying the board files inside Zephyr.

---

# 12. Application CMakeLists.txt

A basic Zephyr application can use:

```cmake
cmake_minimum_required(VERSION 3.20.0)

find_package(
    Zephyr
    REQUIRED
    HINTS "${ZEPHYR_BASE}"
)

project(app)

target_sources(
    app
    PRIVATE
        src/main.cpp
)
```

Application sources can also be conditionally added:

```cmake
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

    target_sources(
        app
        PRIVATE
            src/main.cpp
    )

endif()
```

Include directories can similarly be checked:

```cmake
if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include")

    target_include_directories(
        app
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

endif()
```

---

# 13. ESP32 Configuration

For ESP32 applications, the workspace uses the Espressif HAL:

```text
deps/modules/hal/espressif/
```

The ESP32 flashing tool is:

```text
tools/esptool_py/esptool.py
```

The CMake configuration can locate it using:

```cmake
set(ESPRESSIF_HAL_PATH
    "${IOMICO_WORKSPACE}/deps/modules/hal/espressif"
)

set(ESPTOOL
    "${ESPRESSIF_HAL_PATH}/tools/esptool_py/esptool.py"
)
```

---

# 14. Flash the Application

After a successful build:

```powershell
west flash
```

For the ESP32 board:

```powershell
west flash
```

If multiple boards/devices are connected, specify the required runner/device options as appropriate.

---

# 15. View Serial Output

After flashing, connect to the board's serial console.

Typical Zephyr applications use:

```text
UART
```

For example, use a serial terminal such as:

```text
115200 baud
8 data bits
No parity
1 stop bit
```

The exact COM port depends on the connected board.

On Windows, check available COM ports with:

```powershell
Get-CimInstance Win32_SerialPort
```

---

# 16. Build and Flash Workflow

The normal development workflow is:

```powershell
west build -b <board> <application>
west flash
```

Example:

```powershell
west build -b esp32_devkitc/esp32/procpu .\Fundamental-Cohort-2-2026\Examples\hello_world
west flash
```

For a clean rebuild:

```powershell
west build -b esp32_devkitc/esp32/procpu .\Fundamental-Cohort-2-2026\Examples\hello_world -p always
west flash
```

---

# 17. Useful West Commands

Show West version:

```powershell
west --version
```

Show workspace root:

```powershell
west topdir
```

Show all West projects:

```powershell
west list
```

Update repositories:

```powershell
west update
```

Build:

```powershell
west build
```

Flash:

```powershell
west flash
```

Run pristine build:

```powershell
west build -t pristine
```

Export Zephyr environment:

```powershell
west zephyr-export
```

---

# 18. Useful CMake Commands

Check CMake:

```powershell
cmake --version
```

Check Ninja:

```powershell
ninja --version
```

The application is configured through:

```cmake
cmake_minimum_required(VERSION 3.20.0)
```

---

# 19. Git Workflow

Check repository status:

```powershell
git status
```

See changed files:

```powershell
git diff
```

See staged changes:

```powershell
git diff --cached
```

Add all non-ignored changes:

```powershell
git add -A
```

Check staged files:

```powershell
git status
```

Commit:

```powershell
git commit -m "Your commit message"
```

Push:

```powershell
git push origin main
```

Pull latest changes:

```powershell
git pull origin main
```

---

# 20. Git Branches

Show current branch:

```powershell
git branch
```

Show all branches:

```powershell
git branch -a
```

Create a branch:

```powershell
git checkout -b feature/my-feature
```

Switch branches:

```powershell
git checkout main
```

Modern Git syntax:

```powershell
git switch main
```

Create and switch to a new branch:

```powershell
git switch -c feature/my-feature
```

Push a new branch:

```powershell
git push -u origin feature/my-feature
```

---

# 21. Git Tags

Tags are useful for creating stable course milestones.

List tags:

```powershell
git tag
```

Create an annotated tag:

```powershell
git tag -a v0.1.0 -m "Zephyr Fundamental Cohort 2 - Initial Examples"
```

Show tag information:

```powershell
git show v0.1.0
```

Push a specific tag:

```powershell
git push origin v0.1.0
```

Push all tags:

```powershell
git push origin --tags
```

Delete a local tag:

```powershell
git tag -d v0.1.0
```

Delete a remote tag:

```powershell
git push origin --delete v0.1.0
```

---

# 22. Recommended Versioning

Example milestones:

```text
v0.1.0    Initial Zephyr workspace
v0.2.0    Fundamental examples
v0.3.0    ESP32 examples
v0.4.0    Device Tree overlays
v1.0.0    Fundamental course complete
v2.0.0    Intermediate course release
```

Create a milestone:

```powershell
git add -A
git commit -m "Add ESP32 LED blinky example"

git tag -a v0.3.0 -m "ESP32 examples and Device Tree overlays"

git push origin main
git push origin v0.3.0
```

---

# 23. Check Commit History

Show commits:

```powershell
git log --oneline
```

Show a graphical history:

```powershell
git log --oneline --graph --decorate --all
```

Show the latest commit:

```powershell
git show HEAD
```

Check whether the local branch is ahead/behind:

```powershell
git status
```

---

# 24. Git Remote

Show configured remote repositories:

```powershell
git remote -v
```

The repository is hosted on GitHub:

```text
KakadiyaSahil/Iomico-Zephyr-Course
```

Push to the main branch:

```powershell
git push origin main
```

---

# 25. If Git Says the Branch Is Ahead

Example:

```text
Your branch is ahead of 'origin/main' by 3 commits.
```

This means the commits exist locally but have not been uploaded to GitHub.

Use:

```powershell
git push origin main
```

---

# 26. If You Accidentally Modified a File

Check what changed:

```powershell
git diff
```

Discard changes to a specific file:

```powershell
git restore <file>
```

Example:

```powershell
git restore .gitignore
```

Discard all unstaged changes:

```powershell
git restore .
```

**Warning:** this permanently removes your uncommitted modifications.

---

# 27. Check Ignored Files

To see ignored files:

```powershell
git status --ignored
```

This is useful for checking whether directories such as:

```text
.venv/
.west/
build/
CMakeFiles/
deps/
zephyr-sdk-*/
```

are correctly excluded.

---

# 28. Recommended Git Ignore

The repository should generally track source code, course material, manifests, configuration, and documentation.

Generated/local files should not be committed:

```gitignore
# Python
.venv/

# West
.west/

# CMake
CMakeFiles/
build/
cmake-build-*/

# Zephyr dependencies
deps/

# Zephyr SDK
zephyr-sdk-*/

# Python cache
__pycache__/
*.pyc
```

---

# 29. Complete New-Project Workflow

From a fresh workspace:

```powershell
python -m venv .venv

.venv\Scripts\Activate.ps1

pip install west

west init -l .

west update

west zephyr-export
```

Then build an application:

```powershell
west build -b esp32_devkitc/esp32/procpu .\Fundamental-Cohort-2-2026\Examples\hello_world
```

Flash:

```powershell
west flash
```

Check Git:

```powershell
git status
```

Commit:

```powershell
git add -A
git commit -m "Add new Zephyr example"
```

Push:

```powershell
git push origin main
```

Create a release/milestone tag:

```powershell
git tag -a v0.1.0 -m "Zephyr course milestone"
git push origin v0.1.0
```

---

# 30. Typical Development Workflow

For normal development, the workflow is:

```text
┌───────────────────────────┐
│ Modify Zephyr application │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│ west build                │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│ Fix build / DT errors     │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│ west flash                │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│ Test on hardware          │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│ git status                │
└─────────────┬─────────────┘
              │
              ▼
┌───────────────────────────┐
│ git add -A                │
│ git commit                │
│ git push                  │
└───────────────────────────┘
```

---

# 31. Troubleshooting

### West cannot find the manifest

Check:

```powershell
west topdir
```

If the workspace has not been initialized:

```powershell
west init -l .
```

Then:

```powershell
west update
```

---

### Zephyr cannot be found

Check:

```powershell
Test-Path .\deps\zephyr
```

If it returns:

```text
True
```

the Zephyr source exists.

Otherwise run:

```powershell
west update
```

---

### Zephyr SDK cannot be found

Check:

```powershell
Test-Path .\zephyr-sdk-0.17.2
```

If it returns `False`, verify that the SDK is installed in the expected workspace location.

---

### Overlay cannot be found

Check the overlay path:

```powershell
Test-Path .\Fundamental-Cohort-2-2026\Examples\app\boards_overlay\Espressif\esp32_devkitc_esp32_procpu.overlay
```

If it returns:

```text
False
```

verify the directory and filename.

---

### CMake is using an old configuration

Use a pristine build:

```powershell
west build -t pristine
```

or:

```powershell
west build -b <board> <application> -p always
```

---

# 32. Important Repository Principle

This repository should contain the **course source and configuration**, not the complete local development environment.

Track:

```text
Source code
CMakeLists.txt
Device Tree overlays
Kconfig files
West manifest
Course material
README/documentation
.gitignore
```

Do not normally track:

```text
.venv/
.west/
build/
CMakeFiles/
deps/
zephyr-sdk-*/
```

The West manifest and SDK version provide the information required to recreate the development environment.

---

# 33. Quick Command Reference

| Task | Command |
|---|---|
| Activate Python | `.venv\Scripts\Activate.ps1` |
| Initialize West | `west init -l .` |
| Update dependencies | `west update` |
| Export Zephyr | `west zephyr-export` |
| List West projects | `west list` |
| Build | `west build -b <board> <app>` |
| Clean build | `west build -t pristine` |
| Force pristine | `west build -p always` |
| Flash | `west flash` |
| Git status | `git status` |
| Git diff | `git diff` |
| Stage everything | `git add -A` |
| Commit | `git commit -m "message"` |
| Push | `git push origin main` |
| Pull | `git pull origin main` |
| List branches | `git branch -a` |
| Create branch | `git switch -c <branch>` |
| List tags | `git tag` |
| Create tag | `git tag -a vX.Y.Z -m "message"` |
| Push tag | `git push origin vX.Y.Z` |
| Push all tags | `git push origin --tags` |
| Commit history | `git log --oneline` |
| Git remotes | `git remote -v` |
| Ignored files | `git status --ignored` |

---

## Iomico Zephyr Course

**Repository:** `Iomico-Zephyr-Course`

**Focus:** Zephyr RTOS • Embedded Systems • ESP32 • Device Tree • CMake • West • Firmware Development
