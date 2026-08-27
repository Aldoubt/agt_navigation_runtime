cmake_minimum_required(VERSION 3.8)
project(agt_bringup)

find_package(ament_cmake REQUIRED)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

# GitHub contents writes may leave source scripts at mode 0644. Under
# colcon --symlink-install, installing that source path directly can leave a
# non-executable libexec target. Materialize an executable build-tree copy.
set(AGT_BRINGUP_GENERATED_SCRIPT_DIR
  "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts"
)
file(MAKE_DIRECTORY "${AGT_BRINGUP_GENERATED_SCRIPT_DIR}")
file(COPY
  "${CMAKE_CURRENT_SOURCE_DIR}/scripts/localization_navigation_gate.py"
  DESTINATION "${AGT_BRINGUP_GENERATED_SCRIPT_DIR}"
  FILE_PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

install(PROGRAMS
  "${AGT_BRINGUP_GENERATED_SCRIPT_DIR}/localization_navigation_gate.py"
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(
    test_localization_navigation_gate
    test/test_localization_navigation_gate.py
  )
  ament_add_pytest_test(
    test_runtime_bringup_contract
    test/test_runtime_bringup_contract.py
  )
endif()

ament_package()
