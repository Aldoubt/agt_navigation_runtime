# CMake generated Testfile for 
# Source directory: /home/yangxuan/agt_navigation_runtime/third_party/fast_livo2_ros2
# Build directory: /home/yangxuan/agt_navigation_runtime/build/fast_livo
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_incremental_voxel_map "/usr/bin/python3" "-u" "/opt/ros/humble/share/ament_cmake_test/cmake/run_test.py" "/home/yangxuan/agt_navigation_runtime/build/fast_livo/test_results/fast_livo/test_incremental_voxel_map.gtest.xml" "--package-name" "fast_livo" "--output-file" "/home/yangxuan/agt_navigation_runtime/build/fast_livo/ament_cmake_gtest/test_incremental_voxel_map.txt" "--command" "/home/yangxuan/agt_navigation_runtime/build/fast_livo/test_incremental_voxel_map" "--gtest_output=xml:/home/yangxuan/agt_navigation_runtime/build/fast_livo/test_results/fast_livo/test_incremental_voxel_map.gtest.xml")
set_tests_properties(test_incremental_voxel_map PROPERTIES  LABELS "gtest" REQUIRED_FILES "/home/yangxuan/agt_navigation_runtime/build/fast_livo/test_incremental_voxel_map" TIMEOUT "60" WORKING_DIRECTORY "/home/yangxuan/agt_navigation_runtime/build/fast_livo" _BACKTRACE_TRIPLES "/opt/ros/humble/share/ament_cmake_test/cmake/ament_add_test.cmake;125;add_test;/opt/ros/humble/share/ament_cmake_gtest/cmake/ament_add_gtest_test.cmake;86;ament_add_test;/opt/ros/humble/share/ament_cmake_gtest/cmake/ament_add_gtest.cmake;93;ament_add_gtest_test;/home/yangxuan/agt_navigation_runtime/third_party/fast_livo2_ros2/CMakeLists.txt;196;ament_add_gtest;/home/yangxuan/agt_navigation_runtime/third_party/fast_livo2_ros2/CMakeLists.txt;0;")
subdirs("gtest")
