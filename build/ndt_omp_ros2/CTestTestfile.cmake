# CMake generated Testfile for 
# Source directory: /home/yangxuan/agt_navigation_runtime/third_party/ndt_omp_ros2
# Build directory: /home/yangxuan/agt_navigation_runtime/build/ndt_omp_ros2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_ndt_thread_count "/usr/bin/python3" "-u" "/opt/ros/humble/share/ament_cmake_test/cmake/run_test.py" "/home/yangxuan/agt_navigation_runtime/build/ndt_omp_ros2/test_results/ndt_omp_ros2/test_ndt_thread_count.gtest.xml" "--package-name" "ndt_omp_ros2" "--output-file" "/home/yangxuan/agt_navigation_runtime/build/ndt_omp_ros2/ament_cmake_gtest/test_ndt_thread_count.txt" "--command" "/home/yangxuan/agt_navigation_runtime/build/ndt_omp_ros2/test_ndt_thread_count" "--gtest_output=xml:/home/yangxuan/agt_navigation_runtime/build/ndt_omp_ros2/test_results/ndt_omp_ros2/test_ndt_thread_count.gtest.xml")
set_tests_properties(test_ndt_thread_count PROPERTIES  LABELS "gtest" REQUIRED_FILES "/home/yangxuan/agt_navigation_runtime/build/ndt_omp_ros2/test_ndt_thread_count" TIMEOUT "60" WORKING_DIRECTORY "/home/yangxuan/agt_navigation_runtime/build/ndt_omp_ros2" _BACKTRACE_TRIPLES "/opt/ros/humble/share/ament_cmake_test/cmake/ament_add_test.cmake;125;add_test;/opt/ros/humble/share/ament_cmake_gtest/cmake/ament_add_gtest_test.cmake;86;ament_add_test;/opt/ros/humble/share/ament_cmake_gtest/cmake/ament_add_gtest.cmake;93;ament_add_gtest_test;/home/yangxuan/agt_navigation_runtime/third_party/ndt_omp_ros2/CMakeLists.txt;92;ament_add_gtest;/home/yangxuan/agt_navigation_runtime/third_party/ndt_omp_ros2/CMakeLists.txt;0;")
subdirs("gtest")
