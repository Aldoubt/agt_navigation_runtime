cmake_minimum_required(VERSION 3.8)
project(camera_gimbal_msgs)

find_package(ament_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/GimbalState.msg"
  "action/AcquireView.action"
  DEPENDENCIES builtin_interfaces std_msgs
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_interfaces test/test_interfaces.py)
endif()

ament_export_dependencies(rosidl_default_runtime)
ament_package()
