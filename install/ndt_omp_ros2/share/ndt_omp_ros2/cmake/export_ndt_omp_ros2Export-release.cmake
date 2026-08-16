#----------------------------------------------------------------
# Generated CMake target import file for configuration "RELEASE".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ndt_omp_ros2::ndt_omp" for configuration "RELEASE"
set_property(TARGET ndt_omp_ros2::ndt_omp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ndt_omp_ros2::ndt_omp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libndt_omp.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS ndt_omp_ros2::ndt_omp )
list(APPEND _IMPORT_CHECK_FILES_FOR_ndt_omp_ros2::ndt_omp "${_IMPORT_PREFIX}/lib/libndt_omp.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
