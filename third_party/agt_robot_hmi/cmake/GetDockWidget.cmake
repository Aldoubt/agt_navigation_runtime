include(FetchContent)
message(STATUS "get dockwidget ...")

set(AGT_HMI_DOCKWIDGET_SOURCE_DIR "" CACHE PATH
    "Local Qt Advanced Docking System source directory for offline builds")

if(AGT_HMI_DOCKWIDGET_SOURCE_DIR)
    if(NOT EXISTS "${AGT_HMI_DOCKWIDGET_SOURCE_DIR}/CMakeLists.txt")
        message(FATAL_ERROR "AGT_HMI_DOCKWIDGET_SOURCE_DIR has no CMakeLists.txt: ${AGT_HMI_DOCKWIDGET_SOURCE_DIR}")
    endif()
    set(QT_VERSION_MAJOR 5 CACHE STRING "Qt version major" FORCE)
    set(BUILD_STATIC TRUE CACHE BOOL "Build static library" FORCE)
    set(ADS_VERSION "4.4.0" CACHE STRING "Version" FORCE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)
    add_subdirectory("${AGT_HMI_DOCKWIDGET_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/qt-advanced-docking-system")
    if(TARGET qtadvanceddocking-qt${QT_VERSION_MAJOR})
        add_library(dockwidget::dockwidget ALIAS "qtadvanceddocking-qt${QT_VERSION_MAJOR}")
    endif()
    return()
endif()

set(dockwidget_GIT_REPOSITORY
    "https://github.com/githubuser0xFFFF/Qt-Advanced-Docking-System.git"
    CACHE STRING "dockwidget git repository")

FetchContent_Declare(
    dockwidget
    GIT_REPOSITORY ${dockwidget_GIT_REPOSITORY}
    GIT_TAG "4.4.0"
    GIT_SHALLOW TRUE)

FetchContent_GetProperties(dockwidget)
if(NOT dockwidget_POPULATED)
    set(QT_VERSION_MAJOR 5 CACHE STRING "Qt version major" FORCE)
    set(BUILD_STATIC TRUE CACHE BOOL "Build static library" FORCE)
    set(ADS_VERSION "4.4.0" CACHE STRING "Version" FORCE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)
    FetchContent_MakeAvailable(dockwidget)
    add_library(dockwidget::dockwidget ALIAS "qtadvanceddocking-qt${QT_VERSION_MAJOR}")
endif()

# target: dockwidget::dockwidget
