from pathlib import Path


PACKAGE = Path(__file__).resolve().parents[1]


def test_generated_ros_scripts_are_cmake_reconfigure_dependencies():
    cmake = (PACKAGE / "CMakeLists.txt").read_text(encoding="utf-8")

    # The package deliberately installs executable build-tree copies because
    # GitHub content writes may leave source scripts non-executable. Those
    # copies must be regenerated whenever any source script changes; otherwise
    # colcon --symlink-install can launch stale runtime code while source tests
    # still pass.
    loop_marker = "foreach(script_name IN LISTS AGT_INSPECTION_SCRIPT_NAMES)"
    assert loop_marker in cmake
    loop_body = cmake.split(loop_marker, 1)[1].split("endforeach()", 1)[0]

    # The actual contract is semantic: every script handled by the generation
    # loop must also be registered as a CMake configure dependency, and the
    # same source path must be copied into the executable build-tree staging
    # directory. Textual ordering inside one configure pass is not significant.
    assert "CMAKE_CONFIGURE_DEPENDS" in loop_body
    assert '"${CMAKE_CURRENT_SOURCE_DIR}/scripts/${script_name}"' in loop_body
    assert "file(COPY" in loop_body
