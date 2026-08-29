cmake_minimum_required(VERSION 3.8)
project(agt_inspection)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

# GitHub contents writes may leave source scripts at mode 0644. Under
# colcon --symlink-install, installing those source paths directly can expose
# non-executable libexec targets. Materialize executable build-tree copies, as
# already proven in agt_bringup.
set(AGT_INSPECTION_SCRIPT_NAMES
  inspection_task_server.py
  mock_runtime_context.py
  mock_waypoint_task_server.py
  mock_gimbal_server.py
  mock_camera_server.py
  mock_vision_server.py
  mock_view_aggregator_server.py
)
set(AGT_INSPECTION_GENERATED_SCRIPT_DIR
  "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts"
)
file(MAKE_DIRECTORY "${AGT_INSPECTION_GENERATED_SCRIPT_DIR}")
set(AGT_INSPECTION_GENERATED_SCRIPTS "")
foreach(script_name IN LISTS AGT_INSPECTION_SCRIPT_NAMES)
  # file(COPY ...) runs at configure time. Register each source script as a
  # configure dependency so an incremental colcon build re-runs CMake and
  # refreshes the executable build-tree copy whenever runtime source changes.
  set_property(
    DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/${script_name}"
  )
  file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/${script_name}"
    DESTINATION "${AGT_INSPECTION_GENERATED_SCRIPT_DIR}"
    FILE_PERMISSIONS
      OWNER_READ OWNER_WRITE OWNER_EXECUTE
      GROUP_READ GROUP_EXECUTE
      WORLD_READ WORLD_EXECUTE
  )
  list(APPEND AGT_INSPECTION_GENERATED_SCRIPTS
    "${AGT_INSPECTION_GENERATED_SCRIPT_DIR}/${script_name}"
  )
endforeach()

install(PROGRAMS
  ${AGT_INSPECTION_GENERATED_SCRIPTS}
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

# Source fixtures live under test/ for repository organization, but the
# installed hardware-free launch consumes them as package assets. Keep the
# install path independent of the source-side test/ directory name.
install(DIRECTORY test/fixtures/
  DESTINATION share/${PROJECT_NAME}/fixtures
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_inspection_schema test/test_schema.py)
  ament_add_pytest_test(test_inspection_schema_v2 test/test_schema_v2.py)
  ament_add_pytest_test(test_inspection_repository test/test_repository.py)
  ament_add_pytest_test(test_inspection_execution test/test_execution.py)
  ament_add_pytest_test(test_inspection_multiview_execution test/test_multiview_execution.py)
  ament_add_pytest_test(test_deferred_vision test/test_deferred_vision.py)
  ament_add_pytest_test(test_camera_gimbal_adapter test/test_camera_gimbal_adapter.py)
  ament_add_pytest_test(test_atomic_view_acquisition test/test_atomic_view_acquisition.py)
  ament_add_pytest_test(test_camera_gimbal_health test/test_camera_gimbal_health.py)
  ament_add_pytest_test(test_inspection_ros_contract test/test_ros_contract.py)
  ament_add_pytest_test(test_multiview_evidence test/test_multiview_evidence.py)
  ament_add_pytest_test(test_multiview_ros_contract test/test_multiview_ros_contract.py)
  ament_add_pytest_test(test_multiview_v2_ros_contract test/test_multiview_v2_ros_contract.py)
  ament_add_pytest_test(test_mock_action_executor_contract test/test_mock_action_executor_contract.py)
endif()

ament_package()
