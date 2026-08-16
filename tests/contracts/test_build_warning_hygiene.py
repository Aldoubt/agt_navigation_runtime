from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]


def read(path: str) -> str:
    return (ROOT / path).read_text(encoding="utf-8")


def test_fast_livo_selects_cmp0074_new_behavior() -> None:
    cmake = read("third_party/fast_livo2_ros2/CMakeLists.txt")
    assert "cmake_policy(SET CMP0074 NEW)" in cmake


def test_ndt_omp_requests_only_required_pcl_components() -> None:
    cmake = read("third_party/ndt_omp_ros2/CMakeLists.txt")
    assert "find_package(PCL 1.12 REQUIRED COMPONENTS" in cmake
    assert "registration" in cmake
    assert "filters" in cmake
    assert "find_package(PCL 1.12 REQUIRED)" not in cmake


def test_livox_apr_messages_are_status_output() -> None:
    cmake = read("third_party/livox_ros_driver2/CMakeLists.txt")
    assert "message(${APR_INCLUDE_DIRS})" not in cmake
    assert "message(${APR_LIBRARIES})" not in cmake
    assert "message(STATUS \"APR include dirs: ${APR_INCLUDE_DIRS}\")" in cmake
    assert "message(STATUS \"APR libraries: ${APR_LIBRARIES}\")" in cmake


def test_vikit_cpu_message_is_status_output() -> None:
    cmake = read("third_party/rpg_vikit_ros2_fisheye/vikit_common/CMakeLists.txt")
    assert "message(STATUS \"Current CPU architecture: ${CMAKE_SYSTEM_PROCESSOR}\")" in cmake
    assert "message(\"Current CPU archtecture: ${CMAKE_SYSTEM_PROCESSOR}\")" not in cmake


def test_relocalization_declares_pcl_io_optional_backend_dependencies() -> None:
    package_xml = read("third_party/relocalization_core/package.xml")
    assert "<depend>libpcap</depend>" in package_xml
    assert "<depend>libpng-dev</depend>" in package_xml
