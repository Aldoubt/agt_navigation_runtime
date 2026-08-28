cmake_minimum_required(VERSION 3.8)
project(agt_system_manager)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

# Files written through repository APIs may arrive with mode 0644. Under
# colcon --symlink-install, installing the source script directly can leave a
# libexec symlink whose target is not executable, so ros2 run/launch reports
# "executable ... not found". Materialize the entry point in the build tree
# with explicit executable permissions and install that generated copy.
set(AGT_SYSTEM_MANAGER_GENERATED_SCRIPT_DIR
  "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts"
)
file(MAKE_DIRECTORY "${AGT_SYSTEM_MANAGER_GENERATED_SCRIPT_DIR}")

file(COPY
  "${CMAKE_CURRENT_SOURCE_DIR}/scripts/system_manager_node.py"
  DESTINATION "${AGT_SYSTEM_MANAGER_GENERATED_SCRIPT_DIR}"
  FILE_PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

install(PROGRAMS
  "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts/system_manager_node.py"
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  config
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(
    test_readiness_core
    test/test_readiness_core.py
  )
endif()

ament_package()
