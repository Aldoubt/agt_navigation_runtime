cmake_minimum_required(VERSION 3.8)
project(agt_hardware_bringup)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

# `colcon build --symlink-install` preserves the permissions of the symlink
# target. The repository wrapper scripts are intentionally regular source files,
# so prepare executable build-tree copies and install those. This keeps the ROS 2
# CLI entry points executable for both normal install and symlink install without
# requiring developers to chmod the source tree or the generated install tree.
set(PREFLIGHT_SCRIPT_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/scripts")
file(MAKE_DIRECTORY "${PREFLIGHT_SCRIPT_BUILD_DIR}")
file(COPY
  scripts/socketcan_preflight.py
  scripts/vehicle_preflight.py
  scripts/acceptance_session.py
  DESTINATION "${PREFLIGHT_SCRIPT_BUILD_DIR}"
  FILE_PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

install(PROGRAMS
  "${PREFLIGHT_SCRIPT_BUILD_DIR}/socketcan_preflight.py"
  "${PREFLIGHT_SCRIPT_BUILD_DIR}/vehicle_preflight.py"
  "${PREFLIGHT_SCRIPT_BUILD_DIR}/acceptance_session.py"
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
  ament_add_pytest_test(test_environment_preflight test/test_environment_preflight.py)
  ament_add_pytest_test(test_description_preflight_contract test/test_description_preflight_contract.py)
  ament_add_pytest_test(test_package_contract test/test_package_contract.py)
  ament_add_pytest_test(test_visual_interface_contract test/test_visual_interface_contract.py)
  ament_add_pytest_test(test_acceptance_session test/test_acceptance_session.py)
endif()

ament_package()
