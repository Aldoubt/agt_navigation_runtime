cmake_minimum_required(VERSION 3.8)
project(agt_navigation)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

install(PROGRAMS
  scripts/differential_drive_simulator.py
  scripts/execute_waypoint_task.py
  scripts/goal_pose_bridge.py
  scripts/start_waypoint_preview_rviz.sh
  scripts/task_registry_node.py
  scripts/waypoint_task_server.py
  scripts/waypoint_preview_planner.py
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
endif()

ament_package()
