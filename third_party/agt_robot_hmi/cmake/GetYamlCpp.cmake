include(FetchContent)
message(STATUS "get yaml-cpp ...")

if(AGT_HMI_USE_SYSTEM_DEPS)
    find_package(yaml-cpp CONFIG QUIET)
    if(TARGET yaml-cpp::yaml-cpp)
        message(STATUS "using system yaml-cpp")
        return()
    endif()
    # Ubuntu 22.04 exports the imported target as `yaml-cpp` (without a
    # namespace), while the HMI links the namespaced target used upstream.
    if(TARGET yaml-cpp AND NOT TARGET yaml-cpp::yaml-cpp)
        add_library(yaml-cpp::yaml-cpp ALIAS yaml-cpp)
        message(STATUS "using system yaml-cpp target alias")
        return()
    endif()
endif()

set(yaml-cpp_GIT_REPOSITORY
    "https://github.com/jbeder/yaml-cpp.git"
    CACHE STRING "yaml-cpp git repository")

FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY ${yaml-cpp_GIT_REPOSITORY}
    GIT_TAG "0.8.0"
    GIT_SHALLOW TRUE)

FetchContent_GetProperties(yaml-cpp)
if(NOT yaml-cpp_POPULATED)
    # 禁用不需要的组件以加快构建速度
    set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
    set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "" FORCE)
    set(YAML_CPP_FORMAT_SOURCE OFF CACHE BOOL "" FORCE)
    
    # 启用安装
    set(YAML_CPP_INSTALL ON CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(yaml-cpp)
endif()

# target: yaml-cpp::yaml-cpp
