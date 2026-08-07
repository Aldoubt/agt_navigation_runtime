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
)

install(TARGETS agt_localization_candidates
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib
)

install(TARGETS agt_localization_supervisor
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib
)

install(TARGETS agt_localization_map_readiness
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib
)

install(DIRECTORY include/
  DESTINATION include
)
target_link_libraries(relocalization_node
  relocalization_core::relocalization_core ${PCL_LIBRARIES}
)

install(TARGETS relocalization_node DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch config
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
  ament_add_pytest_test(
    test_relocalization_config
    test/test_relocalization_config.py
  )
endif()

ament_package()
