cmake_minimum_required(VERSION 3.8)
project(agt_sensor_adapters)

find_package(ament_cmake REQUIRED)
find_package(diagnostic_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(livox_ros_driver2 REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(urdf REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(yaml-cpp REQUIRED)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(agt_sensor_filter_geometry
  src/self_filter_geometry.cpp
  src/urdf_self_filter_geometry.cpp
)
target_compile_features(agt_sensor_filter_geometry PUBLIC cxx_std_17)
target_include_directories(agt_sensor_filter_geometry PUBLIC include)
ament_target_dependencies(agt_sensor_filter_geometry urdf)
target_link_libraries(agt_sensor_filter_geometry yaml-cpp)

add_executable(livox_custom_self_filter src/livox_custom_self_filter.cpp)
target_compile_features(livox_custom_self_filter PRIVATE cxx_std_17)
target_include_directories(livox_custom_self_filter PRIVATE include)
ament_target_dependencies(livox_custom_self_filter
  diagnostic_msgs geometry_msgs livox_ros_driver2 rclcpp sensor_msgs std_msgs tf2
  tf2_geometry_msgs tf2_ros visualization_msgs
)
target_link_libraries(livox_custom_self_filter agt_sensor_filter_geometry)

add_executable(navsat_fix_adapter src/navsat_fix_adapter.cpp)
target_compile_features(navsat_fix_adapter PRIVATE cxx_std_17)
target_include_directories(navsat_fix_adapter PRIVATE include)
ament_target_dependencies(navsat_fix_adapter rclcpp sensor_msgs)

install(TARGETS agt_sensor_filter_geometry
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install(TARGETS livox_custom_self_filter navsat_fix_adapter DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)

install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
  PATTERN "__pycache__" EXCLUDE
)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_self_filter_geometry test/test_self_filter_geometry.cpp)
  ament_target_dependencies(test_self_filter_geometry livox_ros_driver2)
  target_link_libraries(test_self_filter_geometry agt_sensor_filter_geometry)

  ament_add_gtest(test_urdf_self_filter_geometry test/test_urdf_self_filter_geometry.cpp)
  ament_target_dependencies(test_urdf_self_filter_geometry urdf)
  target_link_libraries(test_urdf_self_filter_geometry agt_sensor_filter_geometry)

  ament_add_gtest(test_navsat_fix_adapter_core test/test_navsat_fix_adapter_core.cpp)
  target_include_directories(test_navsat_fix_adapter_core PRIVATE include)
  ament_target_dependencies(test_navsat_fix_adapter_core sensor_msgs)
endif()

ament_package()
