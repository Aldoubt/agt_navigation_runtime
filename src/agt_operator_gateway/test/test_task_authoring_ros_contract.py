from pathlib import Path
import json

import pytest


ROOT = Path(__file__).resolve().parents[1]
RUNTIME_SRC = ROOT.parent


def read(relative: str) -> str:
    return (ROOT / relative).read_text(encoding="utf-8")


def test_task_authoring_adapter_uses_planner_and_task_registry_only() -> None:
    source = read("agt_operator_gateway/task_authoring_ros_adapter.py")
    for token in (
        "from nav2_msgs.action import ComputePathToPose",
        "from agt_interfaces.srv import PutTaskGroup",
        "ActionClient(",
        "'/compute_path_to_pose'",
        "'/agt/navigation/tasks/put'",
    ):
        assert token in source

    for forbidden in (
        "NavigateToPose",
        "FollowWaypoints",
        "FollowPath",
        "/cmd_vel",
        "/agt/chassis",
    ):
        assert forbidden not in source


def test_task_authoring_model_binds_exact_site_and_rejects_unpersisted_dwell(tmp_path) -> None:
    from agt_operator_gateway.task_authoring_model import ActiveTaskSite, build_task_document

    image = tmp_path / "navigation.pgm"
    image.write_bytes(b"P5\n2 2\n255\n" + bytes((254, 254, 254, 254)))
    yaml_path = tmp_path / "navigation.yaml"
    yaml_path.write_text(
        "\n".join(
            (
                "image: navigation.pgm",
                "resolution: 0.5",
                "origin: [1.0, 2.0, 0.0]",
                "negate: 0",
                "occupied_thresh: 0.65",
                "free_thresh: 0.196",
            )
        ),
        encoding="utf-8",
    )
    pcd = tmp_path / "localization_map.pcd"
    pcd.write_bytes(b"pcd")
    site = ActiveTaskSite.from_files(
        site_id="orchard_a",
        site_revision="r01",
        navigation_yaml=yaml_path,
        localization_pcd=pcd,
    )

    payload = {
        "taskId": "inspection_01",
        "siteId": "orchard_a",
        "siteRevision": "r01",
        "expectedRevision": 0,
        "loop": False,
        "loopCount": 1,
        "waypoints": [
            {"id": "P01", "x": 1.25, "y": 2.25, "yaw": 0.0, "dwellS": 0.0},
            {"id": "P02", "x": 1.75, "y": 2.25, "yaw": 0.2, "dwellS": 0.0},
        ],
    }
    task = build_task_document(site, payload)
    document = task.to_dict()
    assert task.revision == 1
    assert document["map_binding"]["map_id"] == "orchard_a"
    assert document["map_binding"]["map_version_id"] == "r01"
    assert document["map_binding"]["resolution"] == pytest.approx(0.5)
    assert document["map_binding"]["width"] == 2
    assert document["map_binding"]["height"] == 2
    assert document["map_binding"]["origin"] == [1.0, 2.0, 0.0]
    assert document["content_sha256"].startswith("sha256:")
    assert json.loads(json.dumps(document, allow_nan=False))["task_group_id"] == "inspection_01"

    changed_site = dict(payload)
    changed_site["siteRevision"] = "r02"
    with pytest.raises(ValueError, match="active Site"):
        build_task_document(site, changed_site)

    with_dwell = {**payload, "waypoints": [dict(item) for item in payload["waypoints"]]}
    with_dwell["waypoints"][0]["dwellS"] = 1.0
    with pytest.raises(ValueError, match="dwellS"):
        build_task_document(site, with_dwell)


def test_update_revision_is_derived_from_expected_revision(tmp_path) -> None:
    from agt_operator_gateway.task_authoring_model import ActiveTaskSite, build_task_document

    image = tmp_path / "map.pgm"
    image.write_bytes(b"P5\n2 1\n255\n" + bytes((254, 254)))
    yaml_path = tmp_path / "map.yaml"
    yaml_path.write_text(
        "image: map.pgm\nresolution: 1.0\norigin: [0.0, 0.0, 0.0]\nnegate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\n",
        encoding="utf-8",
    )
    site = ActiveTaskSite.from_files(
        site_id="site",
        site_revision="r01",
        navigation_yaml=yaml_path,
        localization_pcd=None,
    )
    payload = {
        "taskId": "inspection",
        "siteId": "site",
        "siteRevision": "r01",
        "expectedRevision": 3,
        "loop": True,
        "loopCount": 2,
        "waypoints": [
            {"id": "P01", "x": 0.25, "y": 0.25, "yaw": 0.0, "dwellS": 0.0}
        ],
    }
    task = build_task_document(site, payload)
    assert task.revision == 4
    assert task.loop is True
    assert task.loop_count == 2


def test_field_navigation_binds_task_authoring_to_same_frozen_site_assets() -> None:
    launch = (RUNTIME_SRC / "agt_field_commissioning" / "launch" / "field_navigation.launch.py").read_text(encoding="utf-8")
    node = read("scripts/operator_delivery_gateway_node.py")

    for token in (
        '"task_authoring_enabled": True',
        '"task_authoring_site_id": assets.site_id',
        '"task_authoring_site_revision": assets.site_revision',
        '"task_authoring_navigation_yaml": str(assets.navigation_yaml)',
        '"task_authoring_localization_pcd": str(assets.localization_pcd)',
    ):
        assert token in launch

    assert "TaskAuthoringRosAdapter" in node
    assert "task_authoring = None" in node
    assert "if task_authoring_enabled:" in node
    assert "task_authoring=task_authoring" in node
