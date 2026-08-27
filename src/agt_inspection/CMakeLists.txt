cmake_minimum_required(VERSION 3.8)
project(agt_inspection)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_inspection_schema test/test_schema.py)
  ament_add_pytest_test(test_inspection_repository test/test_repository.py)
endif()

ament_package()
