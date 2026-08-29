cmake_minimum_required(VERSION 3.8)
project(pantilt_camera_serial)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(geometry_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/PantiltAngleInfo.msg"
  "msg/PantiltStatus.msg"
  "srv/PantiltCommand.srv"
  "action/MovePantilt.action"
  DEPENDENCIES std_msgs
)

add_executable(pantilt_camera_serial_node src/pantilt_serial_control.cpp)
target_include_directories(pantilt_camera_serial_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
ament_target_dependencies(pantilt_camera_serial_node
  geometry_msgs
  rclcpp
  rclcpp_action
  std_msgs
)
target_link_libraries(pantilt_camera_serial_node Boost::system)

# Humble: link the executable against interfaces generated in this same package.
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(pantilt_camera_serial_node "${cpp_typesupport_target}")

install(TARGETS pantilt_camera_serial_node
  DESTINATION lib/${PROJECT_NAME}
)
install(DIRECTORY include/
  DESTINATION include
)
install(DIRECTORY launch rviz
  DESTINATION share/${PROJECT_NAME}
  OPTIONAL
)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
