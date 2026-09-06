cmake_minimum_required(VERSION 3.5)
project(agt_robot_hmi VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_MODULE_PATH}")
get_filename_component(PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=return-type")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-type")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

if(MSVC)
  add_compile_options(/utf-8)
endif()

# 依赖
include(Getnlohmann)
include(GetDockWidget)
include(GetYamlCpp)
include(GTestHelper)
find_package(Qt5 COMPONENTS Core Widgets Concurrent Svg REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(Eigen3 REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(fastcdr REQUIRED CONFIG)

# options
option(BUILD_WITH_CHANNEL_AUTO ON)
option(BUILD_WITH_CHANNEL_ROS1 OFF)
option(BUILD_WITH_CHANNEL_ROS2 ON)
option(BUILD_WITH_CHANNEL_ROSBRIDGE OFF)
option(BUILD_WITH_TEST OFF)
set(BUILD_WITH_CHANNEL_AUTO OFF)
enable_testing()

# modules
add_subdirectory(src)
add_subdirectory(install)
ament_package()
