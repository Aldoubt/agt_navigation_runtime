cmake_minimum_required(VERSION 3.8)
project(agt_site_navigation)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

set(AGT_SITE_NAVIGATION_GENERATED_SCRIPT_DIR
  "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts"
)
file(MAKE_DIRECTORY "${AGT_SITE_NAVIGATION_GENERATED_SCRIPT_DIR}")
file(COPY
  "${CMAKE_CURRENT_SOURCE_DIR}/scripts/site_navigation_binding_node.py"
  DESTINATION "${AGT_SITE_NAVIGATION_GENERATED_SCRIPT_DIR}"
  FILE_PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

install(PROGRAMS
  "${AGT_SITE_NAVIGATION_GENERATED_SCRIPT_DIR}/site_navigation_binding_node.py"
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(test_resolver test/test_resolver.py)
  ament_add_pytest_test(test_source_contract test/test_source_contract.py)
endif()

ament_package()
