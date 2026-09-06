cmake_minimum_required(VERSION 3.8)
project(autolabor_c1_bringup)

find_package(ament_cmake REQUIRED)

install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)
install(PROGRAMS
  scripts/check_status.py
  scripts/test_gimbal.py
  scripts/test_capability.py
  scripts/test_expected_error.py
  scripts/test_capability_cancel.py
  scripts/fake_gimbal_camera.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
