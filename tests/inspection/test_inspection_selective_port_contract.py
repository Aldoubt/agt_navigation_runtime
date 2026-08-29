from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]


def test_inspection_package_and_public_interfaces_are_present():
    required = [
        ROOT / "src/agt_inspection/package.xml",
        ROOT / "src/agt_inspection/agt_inspection/schema.py",
        ROOT / "src/agt_interfaces/action/ExecuteInspectionTask.action",
        ROOT / "src/agt_interfaces/action/InspectImage.action",
        ROOT / "src/agt_interfaces/action/MoveGimbal.action",
        ROOT / "src/agt_interfaces/action/AggregateInspectionViews.action",
        ROOT / "src/agt_interfaces/msg/InspectionStatus.msg",
        ROOT / "src/agt_interfaces/msg/InspectionViewObservation.msg",
        ROOT / "src/agt_interfaces/srv/CaptureImage.srv",
    ]
    missing = [str(path.relative_to(ROOT)) for path in required if not path.is_file()]
    assert not missing, f"missing selective-port files: {missing}"


def test_inspection_package_does_not_reintroduce_navigation_or_tf_authority():
    package_root = ROOT / "src/agt_inspection"
    production_roots = [
        package_root / "agt_inspection",
        package_root / "scripts",
        package_root / "launch",
    ]
    missing = [str(path.relative_to(ROOT)) for path in production_roots if not path.exists()]
    assert not missing, f"missing production inspection roots: {missing}"

    forbidden_fragments = (
        "NavigateToPose",
        "nav2_msgs.action",
        "map -> odom",
        "odom -> base_footprint",
        "create_publisher(Twist",
        "/cmd_vel",
    )
    offenders = []
    for production_root in production_roots:
        for path in production_root.rglob("*.py"):
            source = path.read_text(encoding="utf-8")
            for fragment in forbidden_fragments:
                if fragment in source:
                    offenders.append(f"{path.relative_to(ROOT)}: {fragment}")
    assert not offenders, "inspection authority leak: " + "; ".join(offenders)
