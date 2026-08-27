cmake_minimum_required(VERSION 3.8)
project(agt_experiment_manager)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

install(PROGRAMS scripts/experiment_manager_node.py DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_experiment_manager test/test_experiment_manager.py)
  ament_add_pytest_test(test_experiment_facade test/test_experiment_facade.py)
  ament_add_pytest_test(
    test_experiment_manager_node test/test_experiment_manager_node.py
  )
  ament_add_pytest_test(
    test_calibration_bag_profile test/test_calibration_bag_profile.py
  )
endif()

ament_package()
