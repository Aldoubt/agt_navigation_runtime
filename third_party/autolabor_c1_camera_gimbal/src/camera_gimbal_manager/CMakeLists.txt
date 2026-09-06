cmake_minimum_required(VERSION 3.8)
project(camera_gimbal_manager)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(camera_gimbal_msgs REQUIRED)
find_package(pantilt_camera_serial REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_library(gimbal_state_estimator src/gimbal_state_estimator.cpp)
target_include_directories(gimbal_state_estimator PUBLIC include)

add_executable(camera_gimbal_manager_node src/camera_gimbal_manager_node.cpp)
target_link_libraries(camera_gimbal_manager_node gimbal_state_estimator)
ament_target_dependencies(camera_gimbal_manager_node camera_gimbal_msgs pantilt_camera_serial rclcpp sensor_msgs)

install(TARGETS gimbal_state_estimator camera_gimbal_manager_node DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY config launch DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_gimbal_state_estimator test/test_gimbal_state_estimator.cpp)
  target_link_libraries(test_gimbal_state_estimator gimbal_state_estimator)
  target_include_directories(test_gimbal_state_estimator PRIVATE include)
endif()

ament_package()
