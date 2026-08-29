cmake_minimum_required(VERSION 3.8)
project(agt_runtime_contracts)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

set(AGT_RUNTIME_SCHEMA_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../schemas")
install(FILES
  "${AGT_RUNTIME_SCHEMA_ROOT}/site_package.schema.json"
  "${AGT_RUNTIME_SCHEMA_ROOT}/vehicle_profile.schema.json"
  DESTINATION share/${PROJECT_NAME}/schemas
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(
    test_validator
    test/test_validator.py
  )
endif()

ament_package()
