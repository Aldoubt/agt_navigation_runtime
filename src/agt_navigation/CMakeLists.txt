cmake_minimum_required(VERSION 3.8)
project(agt_navigation)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

# Files written through repository APIs may arrive with mode 0644. Under
# colcon --symlink-install, installing source scripts directly can therefore
# leave libexec symlinks whose targets are not executable, and ros2 run/launch
# will report "executable ... not found". Materialize every ROS entry point in
# the build tree with explicit executable permissions, then install only those
# generated copies.
set(AGT_NAVIGATION_GENERATED_SCRIPT_DIR
  "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts"
)
file(MAKE_DIRECTORY "${AGT_NAVIGATION_GENERATED_SCRIPT_DIR}")

set(AGT_NAVIGATION_ENTRYPOINTS
  differential_drive_simulator.py
  execute_waypoint_task.py
  goal_pose_bridge.py
  navigation_capability_server.py
  route_controller_smoke.py
  route_system_smoke.py
  route_system_smoke_fixture.py
  start_waypoint_preview_rviz.sh
  task_registry_node.py
  waypoint_task_server.py
  waypoint_preview_planner.py
)

foreach(_script IN LISTS AGT_NAVIGATION_ENTRYPOINTS)
  file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/${_script}"
    DESTINATION "${AGT_NAVIGATION_GENERATED_SCRIPT_DIR}"
    FILE_PERMISSIONS
      OWNER_READ OWNER_WRITE OWNER_EXECUTE
      GROUP_READ GROUP_EXECUTE
      WORLD_READ WORLD_EXECUTE
  )
endforeach()

set(AGT_NAVIGATION_GENERATED_ENTRYPOINTS "")
foreach(_script IN LISTS AGT_NAVIGATION_ENTRYPOINTS)
  list(APPEND AGT_NAVIGATION_GENERATED_ENTRYPOINTS
    "${AGT_NAVIGATION_GENERATED_SCRIPT_DIR}/${_script}"
  )
endforeach()

install(PROGRAMS
  ${AGT_NAVIGATION_GENERATED_ENTRYPOINTS}
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
