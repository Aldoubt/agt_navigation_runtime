cmake_minimum_required(VERSION 3.8)
project(camera_capture_manager)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(camera_gimbal_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(pantilt_camera_serial REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(camera_capture_manager src/camera_capture_manager_node.cpp)
ament_target_dependencies(camera_capture_manager
  camera_gimbal_msgs cv_bridge pantilt_camera_serial rclcpp rclcpp_action sensor_msgs)
target_link_libraries(camera_capture_manager ${OpenCV_LIBRARIES})

install(TARGETS camera_capture_manager DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})
ament_package()
