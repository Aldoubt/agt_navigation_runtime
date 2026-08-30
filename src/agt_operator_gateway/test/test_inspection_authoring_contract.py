from pathlib import Path

import pytest


ROOT = Path(__file__).resolve().parents[1]
RUNTIME_SRC = ROOT.parent


def read(relative: str) -> str:
    return (ROOT / relative).read_text(encoding="utf-8")


def test_inspection_save_uses_single_point_taskgroups_and_schema_v2_only() -> None:
    source = read("agt_operator_gateway/inspection_authoring.py")
    for token in (
        "schema_version",
        '"count_target": "litchi_flower"',
        '"execution_mode": "DEFERRED"',
        '"capture_count": 1',
        '"view_center"',
        "build_single_point_task",
        "InspectionAuthoringRepository",
    ):
        assert token in source
    assert "INLINE" not in source
    assert "x\":" not in source


def test_inspection_document_binds_exact_point_task_revisions_and_hashes(tmp_path) -> None:
    from agt_operator_gateway.inspection_authoring import (
        FrozenInspectionDefaults,
        build_inspection_document,
    )
    from agt_operator_gateway.task_authoring_model import ActiveTaskSite
    from agt_inspection.schema import parse_inspection_task

    image = tmp_path / "navigation.pgm"
    image.write_bytes(b"P5\n2 2\n255\n" + bytes((254, 254, 254, 254)))
    yaml_path = tmp_path / "navigation.yaml"
    yaml_path.write_text(
        "image: navigation.pgm\nresolution: 0.5\norigin: [1.0, 2.0, 0.0]\nnegate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\n",
        encoding="utf-8",
    )
    pcd = tmp_path / "localization_map.pcd"
    pcd.write_bytes(b"pcd")
    site = ActiveTaskSite.from_files(
        site_id="orchard_a",
        site_revision="r01",
        site_hash="sha256:" + "a" * 64,
        navigation_yaml=yaml_path,
        localization_pcd=pcd,
    )
    bindings = [
        {"pointId": "P01", "taskGroupId": "inspect-P01-nav", "revision": 1, "contentSha256": "sha256:" + "1" * 64},
        {"pointId": "P02", "taskGroupId": "inspect-P02-nav", "revision": 1, "contentSha256": "sha256:" + "2" * 64},
    ]
    document = build_inspection_document(
        site=site,
        inspection_task_id="inspect",
        expected_revision=0,
        point_bindings=bindings,
        defaults=FrozenInspectionDefaults(),
    )
    parsed = parse_inspection_task(document)
    assert parsed.schema_version == 2
    assert parsed.revision == 1
    assert parsed.map_binding.manifest_sha256 == "sha256:" + "a" * 64
    assert [point.navigation.task_group_id for point in parsed.points] == ["inspect-P01-nav", "inspect-P02-nav"]
    assert [point.navigation.task_revision for point in parsed.points] == [1, 1]
    assert all(point.vision.execution_mode == "DEFERRED" for point in parsed.points)
    assert all(len(point.views) == 1 and point.views[0].id == "view_center" for point in parsed.points)


def test_inspection_authoring_repository_is_revision_guarded_and_atomic(tmp_path) -> None:
    from agt_inspection.authoring_repository import InspectionAuthoringRepository
    from agt_inspection.schema import canonical_hash

    root = tmp_path / "maps"
    repo = InspectionAuthoringRepository(root, "map_a", "r01")
    document = {
        "schema_version": 2,
        "inspection_task_id": "inspect",
        "name": "inspect",
        "description": "",
        "revision": 1,
        "content_sha256": "sha256:" + "0" * 64,
        "count_target": "litchi_flower",
        "map_binding": {"map_id": "map_a", "map_version_id": "r01", "manifest_sha256": "sha256:" + "a" * 64},
        "points": [{
            "id": "P01",
            "navigation": {"task_group_id": "inspect-P01-nav", "task_revision": 1, "expected_content_sha256": "sha256:" + "1" * 64},
            "stabilization": {"linear_velocity_max_mps": 0.02, "angular_velocity_max_radps": 0.03, "stable_duration_s": 0.8, "timeout_s": 5.0},
            "camera": {"camera_id": "inspection_camera", "capture_count": 1, "capture_interval_s": 0.0},
            "vision": {"task_id": "litchi_flower_instance_seg", "model_profile": "default", "minimum_confidence": 0.6, "timeout_s": 10.0, "execution_mode": "DEFERRED"},
            "retry": {"navigation": 1, "gimbal": 1, "capture": 2, "inference": 1},
            "aggregation": {"enabled": False, "aggregation_profile": "default"},
            "views": [{"id": "view_center", "gimbal": {"pan_rad": 0.0, "tilt_rad": -0.1745, "timeout_s": 5.0, "settle_duration_s": 0.5}}],
        }],
    }
    document["content_sha256"] = canonical_hash(document)
    stored = repo.put_document(document, expected_revision=0)
    assert stored.revision == 1
    assert repo.path_for("inspect").is_file()
    with pytest.raises(Exception, match="revision"):
        repo.put_document(document, expected_revision=0)


def test_delivery_http_exposes_explicit_inspection_save_not_generic_task_alias() -> None:
    source = read("agt_operator_gateway/task_run_http.py")
    assert '"/api/v1/inspections/{inspection_task_id}"' in source
    assert "save_inspection" in source
    assert '"home"' in source
    assert '"expectedHomeTaskRevision"' in source


def test_inspection_mission_is_exactly_inspection_then_return_home(tmp_path) -> None:
    from agt_mission_manager.mission_schema import parse_mission
    from agt_operator_gateway.mission_authoring import (
        MissionAuthoringRepository,
        build_inspection_mission_document,
    )
    from agt_operator_gateway.task_authoring_model import ActiveTaskSite

    image = tmp_path / "navigation.pgm"
    image.write_bytes(b"P5\n1 1\n255\n" + bytes((254,)))
    yaml_path = tmp_path / "navigation.yaml"
    yaml_path.write_text(
        "image: navigation.pgm\nresolution: 0.5\norigin: [0.0, 0.0, 0.0]\nnegate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\n",
        encoding="utf-8",
    )
    site = ActiveTaskSite.from_files(
        site_id="orchard_a",
        site_revision="r01",
        site_hash="sha256:" + "a" * 64,
        navigation_yaml=yaml_path,
    )
    document = build_inspection_mission_document(
        site=site,
        inspection_task_id="inspect_01",
        inspection_revision=2,
        inspection_content_sha256="sha256:" + "b" * 64,
        home_binding={
            "taskGroupId": "inspect_01-home-nav",
            "revision": 1,
            "contentSha256": "sha256:" + "c" * 64,
        },
    )
    parsed = parse_mission(document)
    assert [step.type.name for step in parsed.steps] == ["INSPECTION_TASK", "RETURN_HOME"]
    assert parsed.steps[0].inspection_task_id == "inspect_01"
    assert parsed.steps[-1].task_group_id == "inspect_01-home-nav"
    repo = MissionAuthoringRepository(tmp_path / "missions")
    stored = repo.put_document(document)
    assert stored.mission_id == "inspect_01-mission"
    assert repo.path_for(stored.mission_id, stored.mission_version).is_file()


def test_inspection_authoring_requires_explicit_home_and_returns_startable_mission(tmp_path) -> None:
    from agt_inspection.authoring_repository import InspectionAuthoringRepository
    from agt_operator_gateway.inspection_authoring import InspectionAuthoringAdapter
    from agt_operator_gateway.mission_authoring import MissionAuthoringRepository
    from agt_operator_gateway.task_authoring_model import ActiveTaskSite

    image = tmp_path / "navigation.pgm"
    image.write_bytes(b"P5\n1 1\n255\n" + bytes((254,)))
    yaml_path = tmp_path / "navigation.yaml"
    yaml_path.write_text(
        "image: navigation.pgm\nresolution: 0.5\norigin: [0.0, 0.0, 0.0]\nnegate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\n",
        encoding="utf-8",
    )
    site = ActiveTaskSite.from_files(
        site_id="orchard_a",
        site_revision="r01",
        site_hash="sha256:" + "a" * 64,
        navigation_yaml=yaml_path,
    )

    class FakeTaskAuthoring:
        def __init__(self):
            self.revision = 0
        def save(self, task_id, payload):
            self.revision += 1
            return {
                "taskId": task_id,
                "revision": self.revision,
                "contentSha256": "sha256:" + format(self.revision, "064x"),
            }

    adapter = InspectionAuthoringAdapter(
        active_site=site,
        task_authoring=FakeTaskAuthoring(),
        repository=InspectionAuthoringRepository(tmp_path / "maps", "orchard_a", "r01"),
        mission_repository=MissionAuthoringRepository(tmp_path / "missions"),
    )
    base = {
        "inspectionTaskId": "inspect_01",
        "siteId": "orchard_a",
        "siteRevision": "r01",
        "expectedRevision": 0,
        "points": [{"id": "P01", "x": 1.0, "y": 2.0, "yaw": 0.1, "expectedTaskRevision": 0}],
    }
    with pytest.raises(ValueError, match="home"):
        adapter.save("inspect_01", base)

    result = adapter.save(
        "inspect_01",
        {
            **base,
            "home": {"x": 0.0, "y": 0.0, "yaw": 0.0},
            "expectedHomeTaskRevision": 0,
        },
    )
    assert result["mission"]["missionId"] == "inspect_01-mission"
    assert result["mission"]["missionVersion"] == "r0001"
    assert result["homeBinding"]["taskGroupId"] == "inspect_01-home-nav"
    assert result["mission"]["contentSha256"].startswith("sha256:")
