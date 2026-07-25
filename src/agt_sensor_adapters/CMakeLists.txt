cmake_minimum_required(VERSION 3.8)
project(agt_sensor_adapters)

find_package(ament_cmake REQUIRED)
find_package(diagnostic_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(livox_ros_driver2 REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(yaml-cpp REQUIRED)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(agt_sensor_filter_geometry src/self_filter_geometry.cpp)
target_compile_features(agt_sensor_filter_geometry PUBLIC cxx_std_17)
target_include_directories(agt_sensor_filter_geometry PUBLIC include)
target_link_libraries(agt_sensor_filter_geometry yaml-cpp)

add_executable(livox_custom_self_filter src/livox_custom_self_filter.cpp)
target_compile_features(livox_custom_self_filter PRIVATE cxx_std_17)
target_include_directories(livox_custom_self_filter PRIVATE include)
ament_target_dependencies(livox_custom_self_filter
  diagnostic_msgs geometry_msgs livox_ros_driver2 rclcpp sensor_msgs tf2
  tf2_geometry_msgs tf2_ros visualization_msgs
)
target_link_libraries(livox_custom_self_filter agt_sensor_filter_geometry)

install(TARGETS agt_sensor_filter_geometry
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install(TARGETS livox_custom_self_filter DESTINATION lib/${PROJECT_NAME})
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
endif()

ament_package()
