cmake_minimum_required(VERSION 3.8)
project(agt_interfaces)

find_package(ament_cmake REQUIRED)
find_package(action_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/ComponentHealth.msg"
  "msg/LocalizationStatus.msg"
  "msg/MissionStatus.msg"
  "msg/MissionEvent.msg"
  "msg/MapVersionSummary.msg"
  "msg/NavigationSessionStatus.msg"
  "msg/BagSessionSummary.msg"
  "msg/ExperimentSummary.msg"
  "msg/RobotState.msg"
  "msg/SemanticWaypoint.msg"
  "msg/SemanticWaypointArray.msg"
  "msg/SystemHealth.msg"
  "msg/TaskReadiness.msg"
  "srv/EvaluateTaskReadiness.srv"
  "srv/GetSystemHealth.srv"
  "srv/GetRobotState.srv"
  "srv/SetMissionRunState.srv"
  "srv/ActivateMapVersion.srv"
  "srv/ListMapVersions.srv"
  "srv/ManageMapVersion.srv"
  "srv/ListTaskGroups.srv"
  "srv/GetTaskGroup.srv"
  "srv/PutTaskGroup.srv"
  "srv/ArchiveTaskGroup.srv"
  "srv/GetNavigationSession.srv"
  "srv/ListBagSessions.srv"
  "srv/ListExperiments.srv"
  "srv/ManageBagSession.srv"
  "srv/SetLocalizationMode.srv"
  "action/Relocalize.action"
  "action/ChangeSystemMode.action"
  "action/ManageMappingSession.action"
  "action/ExecuteCoverageTask.action"
  "action/ExecuteWaypointTask.action"
  "action/OptimizeMap.action"
  "action/ExecuteMission.action"
  DEPENDENCIES action_msgs builtin_interfaces std_msgs geometry_msgs nav_msgs
)

ament_export_dependencies(rosidl_default_runtime)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  find_package(ament_cmake_pytest REQUIRED)

  ament_add_pytest_test(
    test_execute_coverage_task_serialization
    test/test_execute_coverage_task_serialization.py
  )
  ament_add_pytest_test(
    test_execute_waypoint_task_serialization
    test/test_execute_waypoint_task_serialization.py
  )
  ament_add_pytest_test(
    test_semantic_waypoint_interfaces
    test/test_semantic_waypoint_interfaces.py
  )
  ament_add_pytest_test(
    test_localization_interfaces
    test/test_localization_interfaces.py
  )
  ament_add_pytest_test(
    test_system_interfaces
    test/test_system_interfaces.py
  )
  ament_add_gtest(
    test_execute_coverage_task_cpp
    test/test_execute_coverage_task.cpp
  )
  ament_add_gtest(
    test_localization_interfaces_cpp
    test/test_localization_interfaces.cpp
  )
  ament_add_gtest(
    test_system_interfaces_cpp
    test/test_system_interfaces.cpp
  )
  rosidl_get_typesupport_target(
    cpp_typesupport_target
    ${PROJECT_NAME}
    rosidl_typesupport_cpp
  )
  target_link_libraries(
    test_execute_coverage_task_cpp
    "${cpp_typesupport_target}"
  )
  target_link_libraries(
    test_localization_interfaces_cpp
    "${cpp_typesupport_target}"
  )
  target_link_libraries(
    test_system_interfaces_cpp
    "${cpp_typesupport_target}"
  )
endif()

ament_package()
