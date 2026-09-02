cmake_minimum_required(VERSION 3.8)
project(agt_field_commissioning)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

# The RTAB-Map projector is retained only as an opt-in experiment. The field
# delivery flow uses the lightweight map path and must not be blocked by RTAB-Map
# ABI/API differences on Humble.
option(AGT_ENABLE_RTABMAP_GRID_PROJECTOR "Build archived RTAB-Map grid projector" OFF)
if(AGT_ENABLE_RTABMAP_GRID_PROJECTOR)
  find_package(RTABMap REQUIRED)
  find_package(PCL REQUIRED COMPONENTS common io)
  if(NOT TARGET rtabmap::core)
    message(FATAL_ERROR "AGT_ENABLE_RTABMAP_GRID_PROJECTOR=ON requires rtabmap::core")
  endif()
  add_executable(rtabmap_grid_projector src/rtabmap_grid_projector.cpp)
  target_compile_features(rtabmap_grid_projector PRIVATE cxx_std_17)
  target_include_directories(rtabmap_grid_projector PRIVATE ${PCL_INCLUDE_DIRS})
  target_compile_options(rtabmap_grid_projector PRIVATE ${PCL_DEFINITIONS})
  target_link_libraries(rtabmap_grid_projector PRIVATE rtabmap::core ${PCL_LIBRARIES})
  install(TARGETS rtabmap_grid_projector DESTINATION lib/${PROJECT_NAME})
  message(STATUS "agt_field_commissioning: archived RTAB-Map projector enabled explicitly")
else()
  message(STATUS "agt_field_commissioning: RTAB-Map projector archived/off by default")
endif()

# `colcon build --symlink-install` preserves permissions of the symlink target.
# Repository files written through GitHub may be mode 0644, so stage executable
# build-tree copies before installing ROS 2 CLI entry points.
set(AGT_FIELD_COMMISSIONING_GENERATED_SCRIPT_DIR
  "${CMAKE_CURRENT_BINARY_DIR}/generated_scripts"
)
file(MAKE_DIRECTORY "${AGT_FIELD_COMMISSIONING_GENERATED_SCRIPT_DIR}")
file(COPY
  "${CMAKE_CURRENT_SOURCE_DIR}/scripts/finalize_mapping_run.py"
  "${CMAKE_CURRENT_SOURCE_DIR}/scripts/project_navigation_map.py"
  "${CMAKE_CURRENT_SOURCE_DIR}/scripts/publish_site_revision.py"
  "${CMAKE_CURRENT_SOURCE_DIR}/scripts/raycast_free_space_node.py"
  "${CMAKE_CURRENT_SOURCE_DIR}/scripts/compare_commissioning_maps.py"
  "${CMAKE_CURRENT_SOURCE_DIR}/scripts/edit_navigation_map.py"
  DESTINATION "${AGT_FIELD_COMMISSIONING_GENERATED_SCRIPT_DIR}"
  FILE_PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

install(PROGRAMS
  "${AGT_FIELD_COMMISSIONING_GENERATED_SCRIPT_DIR}/finalize_mapping_run.py"
  "${AGT_FIELD_COMMISSIONING_GENERATED_SCRIPT_DIR}/project_navigation_map.py"
  "${AGT_FIELD_COMMISSIONING_GENERATED_SCRIPT_DIR}/publish_site_revision.py"
  "${AGT_FIELD_COMMISSIONING_GENERATED_SCRIPT_DIR}/raycast_free_space_node.py"
  "${AGT_FIELD_COMMISSIONING_GENERATED_SCRIPT_DIR}/compare_commissioning_maps.py"
  "${AGT_FIELD_COMMISSIONING_GENERATED_SCRIPT_DIR}/edit_navigation_map.py"
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  rviz
  config
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
endif()

ament_package()
