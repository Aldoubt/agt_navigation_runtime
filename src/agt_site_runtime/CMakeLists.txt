cmake_minimum_required(VERSION 3.8)
project(agt_site_runtime)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

# Keep ros2 run/launch executable under --symlink-install even when repository
# APIs create the source script with non-executable permissions.
set(AGT_SITE_RUNTIME_GENERATED_SCRIPT_DIR
  "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts"
)
file(MAKE_DIRECTORY "${AGT_SITE_RUNTIME_GENERATED_SCRIPT_DIR}")

file(COPY
  "${CMAKE_CURRENT_SOURCE_DIR}/scripts/site_runtime_node.py"
  DESTINATION "${AGT_SITE_RUNTIME_GENERATED_SCRIPT_DIR}"
  FILE_PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

install(PROGRAMS
  "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts/site_runtime_node.py"
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  config
  DESTINATION share/${PROJECT_NAME}
)

install(FILES
  README.md
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_registry test/test_registry.py)
  ament_add_pytest_test(test_validator test/test_validator.py)
  ament_add_pytest_test(test_activation_store test/test_activation_store.py)
  ament_add_pytest_test(test_summary_builder test/test_summary_builder.py)
  ament_add_pytest_test(test_runtime_policy test/test_runtime_policy.py)
endif()

ament_package()
