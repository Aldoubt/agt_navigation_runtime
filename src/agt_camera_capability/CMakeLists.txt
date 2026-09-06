cmake_minimum_required(VERSION 3.8)
project(agt_camera_capability)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
ament_python_install_package(${PROJECT_NAME})

install(PROGRAMS
  scripts/camera_capability_server.py
  DESTINATION lib/${PROJECT_NAME}
)
install(DIRECTORY config DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_camera_capability test/test_camera_capability.py)
  ament_add_pytest_test(test_capture_strategy test/test_capture_strategy.py)
endif()
ament_package()
