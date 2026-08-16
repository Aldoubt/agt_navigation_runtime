cmake_minimum_required(VERSION 3.8)
project(agt_safety)

find_package(ament_cmake REQUIRED)

install(PROGRAMS
  scripts/safety_controller.py
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(
    test_safety_controller
    test/test_safety_controller.py
  )
endif()

ament_package()
