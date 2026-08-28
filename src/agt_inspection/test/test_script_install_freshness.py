from pathlib import Path


PACKAGE = Path(__file__).resolve().parents[1]


def test_generated_ros_scripts_are_cmake_reconfigure_dependencies():
    cmake = (PACKAGE / "CMakeLists.txt").read_text(encoding="utf-8")

    # The package deliberately installs executable build-tree copies because
    # GitHub content writes may leave source scripts non-executable. Those
    # copies must be regenerated whenever any source script changes; otherwise
    # colcon --symlink-install can launch stale runtime code while source tests
    # still pass.
    assert "CMAKE_CONFIGURE_DEPENDS" in cmake
    assert '"${CMAKE_CURRENT_SOURCE_DIR}/scripts/${script_name}"' in cmake

    configure_depends = cmake.index("CMAKE_CONFIGURE_DEPENDS")
    copy_step = cmake.index("file(COPY")
    assert configure_depends < copy_step
