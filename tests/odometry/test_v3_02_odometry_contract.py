from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
RUNTIME_CONSUMER_DIRS = (
    "src/agt_localization",
    "src/agt_perception",
    "src/agt_navigation",
    "src/agt_experiment_manager",
)
TEXT_SUFFIXES = {".py", ".cpp", ".hpp", ".yaml", ".yml", ".md", ".rviz", ".xml"}


def text(path: str) -> str:
    return (ROOT / path).read_text(encoding="utf-8")


def runtime_text_files():
    for relative in RUNTIME_CONSUMER_DIRS:
        for path in (ROOT / relative).rglob("*"):
            if path.is_file() and path.suffix in TEXT_SUFFIXES:
                yield path


def test_odometry_package_exists():
    assert (ROOT / "src/agt_odometry/package.xml").is_file()


def test_odometry_package_declares_runtime_name():
    assert "<name>agt_odometry</name>" in text("src/agt_odometry/package.xml")


def test_runtime_launch_has_no_pcd_save_arguments():
    launch = text("src/agt_odometry/launch/fast_livo2_odometry.launch.py")
    assert 'DeclareLaunchArgument("save_pcd"' not in launch
    assert 'DeclareLaunchArgument("pcd_save_interval"' not in launch
    assert 'DeclareLaunchArgument("pcd_output_dir"' not in launch
    assert '"pcd_save.pcd_save_en": False' in launch


def test_canonical_topics_are_odometry_scoped():
    config = text("src/agt_odometry/config/fast_livo2_adapter.yaml")
    assert "/agt/odometry/odometry" in config
    assert "/agt/odometry/backend/registered_points" in config
    assert "/agt/odometry/registered_points" in config
    assert "/agt/mapping/" not in config


def test_runtime_consumers_do_not_use_mapping_topic_namespace():
    violations = []
    for path in runtime_text_files():
        if "/agt/mapping/" in path.read_text(encoding="utf-8", errors="ignore"):
            violations.append(str(path.relative_to(ROOT)))
    assert violations == []


def test_runtime_consumers_do_not_launch_agt_mapping():
    violations = []
    for path in runtime_text_files():
        content = path.read_text(encoding="utf-8", errors="ignore")
        if "agt_mapping" in content:
            violations.append(str(path.relative_to(ROOT)))
    assert violations == []


def test_legacy_mapping_package_is_removed():
    assert not (ROOT / "src/agt_mapping").exists()
