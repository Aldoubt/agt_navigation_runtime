cmake_minimum_required(VERSION 3.8)
project(agt_sensor_monitor)

find_package(ament_cmake REQUIRED)
find_package(diagnostic_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
# Livox is an optional source-level backend. SOFTWARE_ONLY Gazebo validation can
# build and run with sensor_msgs/LaserScan even when livox_ros_driver2 is absent.
find_package(livox_ros_driver2 QUIET)

add_compile_options(-Wall -Wextra -Wpedantic)
add_library(stream_monitor src/stream_monitor.cpp)
target_compile_features(stream_monitor PUBLIC cxx_std_17)
target_include_directories(stream_monitor PUBLIC include)

add_executable(agt_sensor_monitor_node src/sensor_monitor_node.cpp)
target_compile_features(agt_sensor_monitor_node PRIVATE cxx_std_17)
target_include_directories(agt_sensor_monitor_node PRIVATE include)
set(AGT_SENSOR_MONITOR_DEPENDENCIES diagnostic_msgs rclcpp sensor_msgs)
if(livox_ros_driver2_FOUND)
  list(APPEND AGT_SENSOR_MONITOR_DEPENDENCIES livox_ros_driver2)
  target_compile_definitions(agt_sensor_monitor_node PRIVATE AGT_SENSOR_MONITOR_HAS_LIVOX=1)
  message(STATUS "agt_sensor_monitor: Livox CustomMsg backend enabled")
else()
  message(STATUS "agt_sensor_monitor: livox_ros_driver2 not found; LaserScan/standard sensor backends only")
endif()
ament_target_dependencies(agt_sensor_monitor_node ${AGT_SENSOR_MONITOR_DEPENDENCIES})
target_link_libraries(agt_sensor_monitor_node stream_monitor)

install(TARGETS stream_monitor agt_sensor_monitor_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include config launch DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_stream_monitor test/test_stream_monitor.cpp)
  target_link_libraries(test_stream_monitor stream_monitor)
  target_include_directories(test_stream_monitor PRIVATE include)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_sensor_monitor_contract test/test_sensor_monitor_contract.py)
endif()
ament_package()
