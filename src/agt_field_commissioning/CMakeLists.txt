cmake_minimum_required(VERSION 3.8)
project(agt_field_commissioning)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

ament_python_install_package(${PROJECT_NAME})

# The delivery projector is optional at generic Runtime build time. A physical
# commissioning image that enables rtabmap_grid must install RTAB-Map core and
# PCL; target-Humble acceptance verifies that this executable was built.
find_package(RTABMap QUIET)
find_package(PCL QUIET COMPONENTS common io)

if(RTABMap_FOUND AND PCL_FOUND AND TARGET rtabmap::core)
  add_executable(rtabmap_grid_projector src/rtabmap_grid_projector.cpp)
  target_compile_features(rtabmap_grid_projector PRIVATE cxx_std_17)
  target_include_directories(rtabmap_grid_projector PRIVATE ${PCL_INCLUDE_DIRS})
  target_compile_options(rtabmap_grid_projector PRIVATE ${PCL_DEFINITIONS})
  target_link_libraries(rtabmap_grid_projector PRIVATE rtabmap::core ${PCL_LIBRARIES})
  install(TARGETS rtabmap_grid_projector DESTINATION lib/${PROJECT_NAME})
  message(STATUS "agt_field_commissioning: RTAB-Map grid projector enabled")
else()
  message(STATUS "agt_field_commissioning: RTAB-Map grid projector disabled (RTABMap/PCL/rtabmap::core unavailable)")
endif()

install(PROGRAMS
  scripts/finalize_mapping_run.py
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
