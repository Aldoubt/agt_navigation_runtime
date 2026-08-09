cmake_minimum_required(VERSION 3.8)
project(agt_localization)

find_package(ament_cmake REQUIRED)
find_package(agt_interfaces REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PCL REQUIRED COMPONENTS common)
find_package(pcl_conversions REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcl_interfaces REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(relocalization_core REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(yaml-cpp REQUIRED)

add_library(agt_localization_candidates src/candidate_provider.cpp)
target_compile_features(agt_localization_candidates PUBLIC cxx_std_17)
target_include_directories(agt_localization_candidates PUBLIC include)
target_link_libraries(agt_localization_candidates yaml-cpp)

add_library(agt_localization_quality src/quality_validator.cpp)
target_compile_features(agt_localization_quality PUBLIC cxx_std_17)
target_include_directories(agt_localization_quality PUBLIC include)

add_library(agt_localization_supervisor src/localization_supervisor.cpp)
target_compile_features(agt_localization_supervisor PUBLIC cxx_std_17)
target_include_directories(agt_localization_supervisor PUBLIC include)

add_library(agt_localization_map_readiness src/map_readiness.cpp)
target_compile_features(agt_localization_map_readiness PUBLIC cxx_std_17)
target_include_directories(agt_localization_map_readiness PUBLIC include)
target_link_libraries(agt_localization_map_readiness yaml-cpp OpenSSL::Crypto)

add_library(agt_localization_global_correction src/global_correction_core.cpp)
target_compile_features(agt_localization_global_correction PUBLIC cxx_std_17)
target_include_directories(agt_localization_global_correction PUBLIC include)
target_link_libraries(agt_localization_global_correction Eigen3::Eigen)

add_library(agt_localization_recovery_trigger src/recovery_trigger_policy.cpp)
target_compile_features(agt_localization_recovery_trigger PUBLIC cxx_std_17)
target_include_directories(agt_localization_recovery_trigger PUBLIC include)

add_executable(relocalization_node src/relocalization_node.cpp)
target_compile_features(relocalization_node PRIVATE cxx_std_17)
target_include_directories(relocalization_node PRIVATE include ${PCL_INCLUDE_DIRS})
ament_target_dependencies(relocalization_node
  agt_interfaces geometry_msgs pcl_conversions rclcpp rcl_interfaces rclcpp_action
  relocalization_core sensor_msgs std_msgs tf2 tf2_ros
)
target_link_libraries(
  relocalization_node
  Eigen3::Eigen
  agt_localization_candidates
  agt_localization_quality
  agt_localization_supervisor
  agt_localization_map_readiness
  relocalization_core::relocalization_core
  ${PCL_LIBRARIES}
)

add_executable(global_correction_manager src/global_correction_manager.cpp)
target_compile_features(global_correction_manager PRIVATE cxx_std_17)
target_include_directories(global_correction_manager PRIVATE include)
ament_target_dependencies(global_correction_manager
  agt_interfaces geometry_msgs rclcpp std_msgs tf2 tf2_ros
)
target_link_libraries(
  global_correction_manager
  Eigen3::Eigen
  agt_localization_global_correction
)

add_executable(recovery_trigger_manager src/recovery_trigger_manager.cpp)
target_compile_features(recovery_trigger_manager PRIVATE cxx_std_17)
target_include_directories(recovery_trigger_manager PRIVATE include)
ament_target_dependencies(recovery_trigger_manager
  agt_interfaces rclcpp rclcpp_action
)
target_link_libraries(
  recovery_trigger_manager
  agt_localization_recovery_trigger
)

install(TARGETS
  agt_localization_candidates
  agt_localization_quality
  agt_localization_supervisor
  agt_localization_map_readiness
  agt_localization_global_correction
  agt_localization_recovery_trigger
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib
)

install(PROGRAMS scripts/reference_map_publisher.py scripts/v25_10_realbag_validation.py
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/
  DESTINATION include
)

install(TARGETS
  relocalization_node
  global_correction_manager
  recovery_trigger_manager
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch config rviz
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_gtest(test_candidate_provider test/test_candidate_provider.cpp)
  target_link_libraries(test_candidate_provider agt_localization_candidates)
  ament_add_gtest(test_quality_validator test/test_quality_validator.cpp)
  target_link_libraries(test_quality_validator agt_localization_quality)
  ament_add_gtest(test_localization_supervisor test/test_localization_supervisor.cpp)
  target_link_libraries(test_localization_supervisor agt_localization_supervisor)
  ament_add_gtest(test_map_readiness test/test_map_readiness.cpp)
  target_link_libraries(test_map_readiness agt_localization_map_readiness)
  ament_add_gtest(test_localization_timing test/test_localization_timing.cpp)
  target_include_directories(test_localization_timing PRIVATE include)
  target_link_libraries(test_localization_timing agt_localization_quality Eigen3::Eigen)
  ament_add_gtest(test_tracking_validation test/test_tracking_validation.cpp)
  target_include_directories(test_tracking_validation PRIVATE include)
  ament_target_dependencies(test_tracking_validation agt_interfaces)
  target_link_libraries(
    test_tracking_validation agt_localization_supervisor Eigen3::Eigen)
  ament_add_gtest(test_global_correction_core test/test_global_correction_core.cpp)
  target_link_libraries(
    test_global_correction_core agt_localization_global_correction Eigen3::Eigen)
  ament_add_gtest(test_recovery_trigger_policy test/test_recovery_trigger_policy.cpp)
  target_link_libraries(
    test_recovery_trigger_policy agt_localization_recovery_trigger
  )
  ament_add_pytest_test(
    test_relocalization_config
    test/test_relocalization_config.py
  )
  ament_add_pytest_test(
    test_global_correction_config
    test/test_global_correction_config.py
  )
  ament_add_pytest_test(
    test_v25_10_validation_contract
    test/test_v25_10_validation_contract.py
  )
endif()

ament_package()
