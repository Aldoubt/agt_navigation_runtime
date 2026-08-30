cmake_minimum_required(VERSION 3.8)
project(agt_chassis_bunker)

find_package(ament_cmake REQUIRED)

install(PROGRAMS
  scripts/bunker_status_bridge.py
  scripts/bunker_rc_auto_permit.py
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
