cmake_minimum_required(VERSION 3.8)
project(agt_hardware_bringup)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

install(PROGRAMS
  scripts/socketcan_preflight.py
  scripts/vehicle_preflight.py
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_socketcan_preflight test/test_socketcan_preflight.py)
  ament_add_pytest_test(test_sensor_profiles test/test_sensor_profiles.py)
  ament_add_pytest_test(test_bringup_launch_contract test/test_bringup_launch_contract.py)
  ament_add_pytest_test(test_vehicle_preflight test/test_vehicle_preflight.py)
  ament_add_pytest_test(test_package_contract test/test_package_contract.py)
endif()

ament_package()
