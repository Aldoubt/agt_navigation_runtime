cmake_minimum_required(VERSION 3.8)
project(agt_mission_manager)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

# GitHub contents writes may leave Python entry points at mode 0644. Under
# colcon --symlink-install that can expose a non-executable libexec target.
# Stage an executable build-tree copy, matching the proven agt_inspection path.
set(AGT_MISSION_MANAGER_GENERATED_SCRIPT_DIR
  "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts"
)
file(MAKE_DIRECTORY "${AGT_MISSION_MANAGER_GENERATED_SCRIPT_DIR}")
file(COPY
  "${CMAKE_CURRENT_SOURCE_DIR}/scripts/mission_manager_node.py"
  DESTINATION "${AGT_MISSION_MANAGER_GENERATED_SCRIPT_DIR}"
  FILE_PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

install(PROGRAMS
  "${AGT_MISSION_MANAGER_GENERATED_SCRIPT_DIR}/mission_manager_node.py"
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY config launch
  DESTINATION share/${PROJECT_NAME}
)

# Source fixtures remain under test/ for repository organization, while mock
# launch consumes the installed copy as a package asset.
install(DIRECTORY test/fixtures/
  DESTINATION share/${PROJECT_NAME}/fixtures
  OPTIONAL
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_mission_schema test/test_mission_schema.py)
  ament_add_pytest_test(test_inspection_mission_step test/test_inspection_mission_step.py)
  ament_add_pytest_test(test_return_home_mission test/test_return_home_mission.py)
  ament_add_pytest_test(test_mission_report test/test_mission_report.py)
  ament_add_pytest_test(test_return_home_ros_contract test/test_return_home_ros_contract.py)
  ament_add_pytest_test(test_mission_fsm test/test_mission_fsm.py)
  ament_add_pytest_test(test_mission_executor test/test_mission_executor.py)
  ament_add_pytest_test(test_inspection_mission_executor test/test_inspection_mission_executor.py)
  ament_add_pytest_test(test_mission_storage test/test_mission_storage.py)
  ament_add_pytest_test(test_bt_mission_executor test/test_bt_mission_executor.py)
  ament_add_pytest_test(test_bt_backend_contract test/test_bt_backend_contract.py)
endif()

ament_package()
