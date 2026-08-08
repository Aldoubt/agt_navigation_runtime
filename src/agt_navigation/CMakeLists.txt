cmake_minimum_required(VERSION 3.8)
project(agt_navigation)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

# Files created through the GitHub contents API may arrive with mode 0644.
# Under colcon --symlink-install, install(PROGRAMS) can otherwise leave a
# symlink whose target is not executable, so ros2 run will not discover it.
# Materialize newly added entry-point scripts into the build tree with explicit
# executable permissions before installing them.
set(AGT_NAVIGATION_GENERATED_SCRIPT_DIR
  "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts"
)
file(MAKE_DIRECTORY "${AGT_NAVIGATION_GENERATED_SCRIPT_DIR}")
file(COPY
  "${CMAKE_CURRENT_SOURCE_DIR}/scripts/route_controller_smoke.py"
  DESTINATION "${AGT_NAVIGATION_GENERATED_SCRIPT_DIR}"
  FILE_PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

install(PROGRAMS
  scripts/differential_drive_simulator.py
  scripts/execute_waypoint_task.py
  scripts/goal_pose_bridge.py
  scripts/navigation_capability_server.py
  scripts/start_waypoint_preview_rviz.sh
  scripts/task_registry_node.py
  scripts/waypoint_task_server.py
  scripts/waypoint_preview_planner.py
  "${AGT_NAVIGATION_GENERATED_SCRIPT_DIR}/route_controller_smoke.py"
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch config behavior_trees maps
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_qt_task_chain test/test_qt_task_chain.py)
  ament_add_pytest_test(test_task_group test/test_task_group.py)
  ament_add_pytest_test(test_task_registry test/test_task_registry.py)
  ament_add_pytest_test(
    test_navigation_session_manager test/test_navigation_session_manager.py
  )
  ament_add_pytest_test(
    test_waypoint_task_server test/test_waypoint_task_server.py
  )
  ament_add_pytest_test(
    test_waypoint_preview_planner test/test_waypoint_preview_planner.py
  )
  ament_add_pytest_test(
    test_waypoint_preview_launch test/test_waypoint_preview_launch.py
  )
  ament_add_pytest_test(test_route_runtime test/test_route_runtime.py)
  ament_add_pytest_test(
    test_nav2_follow_path_adapter test/test_nav2_follow_path_adapter.py
  )
  ament_add_pytest_test(
    test_route_task_binding test/test_route_task_binding.py
  )
  ament_add_pytest_test(
    test_navigation_capability_server test/test_navigation_capability_server.py
  )
  ament_add_pytest_test(
    test_navigation_capability_runtime_gates
    test/test_navigation_capability_runtime_gates.py
  )
endif()

ament_package()
