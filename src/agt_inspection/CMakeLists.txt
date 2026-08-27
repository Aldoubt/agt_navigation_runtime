cmake_minimum_required(VERSION 3.8)
project(agt_inspection)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

install(PROGRAMS
  scripts/inspection_task_server.py
  scripts/mock_gimbal_server.py
  scripts/mock_camera_server.py
  scripts/mock_vision_server.py
  scripts/mock_view_aggregator_server.py
  scripts/mock_runtime_context.py
  scripts/mock_waypoint_task_server.py
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

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
  ament_add_pytest_test(test_inspection_ros_contract test/test_ros_contract.py)
  ament_add_pytest_test(test_multiview_evidence test/test_multiview_evidence.py)
  ament_add_pytest_test(test_multiview_ros_contract test/test_multiview_ros_contract.py)
endif()

ament_package()
