cmake_minimum_required(VERSION 3.8)
project(agt_operator_gateway)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

install(PROGRAMS
  scripts/operator_gateway_node.py
  scripts/mock_robot_state_publisher.py
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY config launch
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_contract test/test_contract.py)
  ament_add_pytest_test(test_state_store test/test_state_store.py)
  ament_add_pytest_test(test_server_contract test/test_server_contract.py)
  ament_add_pytest_test(test_ros_contract test/test_ros_contract.py)
  ament_add_pytest_test(test_mock_gateway_contract test/test_mock_gateway_contract.py)
endif()

ament_package()
