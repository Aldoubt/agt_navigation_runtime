cmake_minimum_required(VERSION 3.8)
project(agt_chassis_mk_mini_sim)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

install(PROGRAMS
  scripts/mk_mini_vcu_sim.py
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_vcu_protocol test/test_vcu_protocol.py)
  ament_add_pytest_test(test_vcu_model test/test_vcu_model.py)
  ament_add_pytest_test(test_vcu_sim_source test/test_vcu_sim_source.py)
endif()

ament_package()
