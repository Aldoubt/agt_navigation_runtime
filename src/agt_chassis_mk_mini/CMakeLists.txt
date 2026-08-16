cmake_minimum_required(VERSION 3.8)
project(agt_chassis_mk_mini)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

install(PROGRAMS
  scripts/mk_mini_adapter.py
  scripts/mk_mini_can_backend.py
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(
    test_ackermann_math
    test/test_ackermann_math.py
  )
  ament_add_pytest_test(
    test_mk_mini_can_core
    test/test_mk_mini_can_core.py
  )
endif()

ament_package()
