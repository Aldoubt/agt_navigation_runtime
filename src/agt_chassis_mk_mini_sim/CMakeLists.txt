cmake_minimum_required(VERSION 3.8)
project(agt_chassis_mk_mini_sim)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(
    test_vcu_protocol
    test/test_vcu_protocol.py
  )
endif()

ament_package()
