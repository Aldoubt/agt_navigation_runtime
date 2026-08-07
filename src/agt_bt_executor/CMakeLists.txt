cmake_minimum_required(VERSION 3.8)
project(agt_bt_executor)

find_package(ament_cmake REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(agt_interfaces REQUIRED)
find_package(behaviortree_cpp REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)

add_library(${PROJECT_NAME} SHARED
  src/bt_factory.cpp
  src/is_task_ready.cpp
  src/relocalize_action.cpp
  src/execute_waypoint_task_action.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC include)
ament_target_dependencies(${PROJECT_NAME} PUBLIC ament_index_cpp agt_interfaces behaviortree_cpp rclcpp rclcpp_action)

add_executable(bt_smoke_runner src/bt_smoke_runner.cpp)
target_compile_features(bt_smoke_runner PRIVATE cxx_std_17)
target_link_libraries(bt_smoke_runner ${PROJECT_NAME})
ament_target_dependencies(bt_smoke_runner ament_index_cpp behaviortree_cpp rclcpp)

install(TARGETS ${PROJECT_NAME} bt_smoke_runner ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY behavior_trees config launch DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_gtest(test_bt_factory test/test_bt_factory.cpp)
  target_link_libraries(test_bt_factory ${PROJECT_NAME})
  ament_target_dependencies(test_bt_factory agt_interfaces behaviortree_cpp rclcpp rclcpp_action)
  ament_add_pytest_test(test_bt_contract test/test_bt_contract.py)
endif()
ament_package()
