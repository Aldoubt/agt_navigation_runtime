import json
import math
from pathlib import Path
import sys

import pytest

PACKAGE_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PACKAGE_ROOT))

from agt_navigation.task_group import (  # noqa: E402
    MapBinding,
    TaskGroup,
    TaskGroupError,
    TaskRepository,
    Waypoint,
    compare_map_binding,
    load_map_snapshot,
    load_qt_task_chain,
    validate_task_group,
)


def _write_map(tmp_path, pixels="\xff\xff\xff\xff"):
    image = tmp_path / "map.pgm"
    image.write_bytes(b"P5\n# fixture\n2 2\n255\n" + pixels.encode("latin1"))
    yaml_path = tmp_path / "map.yaml"
    yaml_path.write_text(
        "\n".join(
            (
                "image: map.pgm",
                "resolution: 1.0",
                "origin: [10.0, 20.0, 0.0]",
                "negate: 0",
                "occupied_thresh: 0.65",
                "free_thresh: 0.196",
            )
        ),
        encoding="utf-8",
    )
    return yaml_path


def _task(binding, points=None):
    return TaskGroup(
        task_group_id="inspection_v01",
        name="巡检任务",
        description="测试",
        created_at="2026-07-25T00:00:00+00:00",
        updated_at="2026-07-25T00:00:00+00:00",
        map_binding=binding,
        points=points or [Waypoint("wp_0001", "入口", 10.5, 20.5, 0.0)],
    )


def test_model_normalizes_yaw_and_serializes_unicode():
    binding = MapBinding("site", "v1", resolution=1.0, width=2, height=2)
    task = _task(binding, [Waypoint("wp_1", "入口", 0.0, 0.0, 3 * math.pi)])
    task.validate()
    assert task.to_dict()["points"][0]["yaw"] == pytest.approx(-math.pi)
    assert json.dumps(task.to_dict(), ensure_ascii=False).find("入口") >= 0


@pytest.mark.parametrize(
    "mutator, message",
    [
        (lambda value: value.pop("schema_version"), "schema_version"),
        (lambda value: value.__setitem__("frame_id", "odom"), "frame_id must be map"),
        (lambda value: value["points"][0].__setitem__("x", float("nan")), "non-finite"),
        (lambda value: value.__setitem__("points", []), "no waypoints"),
        (lambda value: value["execution"].__setitem__("loop_count", 0), "loop_count"),
    ],
)
def test_rejects_invalid_task_groups(mutator, message):
    binding = MapBinding("site", "v1", resolution=1.0, width=2, height=2)
    value = _task(binding).to_dict()
    mutator(value)
    with pytest.raises(TaskGroupError, match=message):
        TaskGroup.from_dict(value)


@pytest.mark.parametrize(
    "mutator, message",
    [
        (lambda value: value.__setitem__("unexpected", True), "unsupported field"),
        (lambda value: value.__setitem__("description", 1), "description must be a string"),
        (lambda value: value["points"][0].__setitem__("enabled", 1), "enabled must be boolean"),
        (lambda value: value["map_binding"].__setitem__("width", 2.5), "width must be an integer"),
    ],
)
def test_schema_shape_rejects_unknown_fields_and_type_coercion(mutator, message):
    binding = MapBinding("site", "v1", resolution=1.0, width=2, height=2)
    value = _task(binding).to_dict()
    mutator(value)
    with pytest.raises(TaskGroupError, match=message):
        TaskGroup.from_dict(value)


def test_rejects_duplicate_and_repeated_paths():
    binding = MapBinding("site", "v1", resolution=1.0, width=2, height=2)
    with pytest.raises(TaskGroupError, match="preceding"):
        _task(binding, [Waypoint("a", "A", 0.0, 0.0, 0.0), Waypoint("b", "B", 0.0, 0.0, 0.0)]).validate()
    points = [
        Waypoint("a", "A", 0.0, 0.0, 0.0),
        Waypoint("b", "B", 1.0, 0.0, 0.0),
        Waypoint("c", "A", 0.0, 0.0, 0.0),
        Waypoint("d", "B", 1.0, 0.0, 0.0),
    ]
    with pytest.raises(TaskGroupError, match="repeated pattern"):
        _task(binding, points).validate()


def test_repository_round_trip_does_not_append_and_updates_index(tmp_path):
    binding = MapBinding("site", "v1", resolution=1.0, width=2, height=2)
    repository = TaskRepository(tmp_path / "runtime" / "maps", "site", "v1")
    task = _task(binding)
    path = repository.save(task)
    path.write_text(path.read_text(encoding="utf-8") + "\n", encoding="utf-8")
    repository.save(task)
    loaded = repository.load("inspection_v01")
    assert len(loaded.points) == 1
    index = json.loads((path.parent / "task_index.json").read_text(encoding="utf-8"))
    assert index["tasks"][0]["task_group_id"] == "inspection_v01"
    assert index["tasks"][0]["validation_state"] == "VALID"
    assert (path.parent / "inspection_v01.json.bak.1").is_file()


def test_repository_copy_and_archive_keep_index_consistent(tmp_path):
    binding = MapBinding("site", "v1", resolution=1.0, width=2, height=2)
    repository = TaskRepository(tmp_path / "maps", "site", "v1")
    repository.save(_task(binding))
    copied = repository.copy("inspection_v01", "inspection_copy")
    assert copied.task_group_id == "inspection_copy"
    with pytest.raises(TaskGroupError, match="already exists"):
        repository.copy("inspection_v01", "inspection_copy")
    archived = repository.archive("inspection_copy")
    assert archived.is_file()
    assert not repository.path_for("inspection_copy").exists()
    index = json.loads(
        (repository.directory / "task_index.json").read_text(encoding="utf-8")
    )
    assert [item["task_group_id"] for item in index["tasks"]] == [
        "inspection_v01"
    ]


def test_atomic_failure_keeps_previous_file(tmp_path, monkeypatch):
    binding = MapBinding("site", "v1", resolution=1.0, width=2, height=2)
    repository = TaskRepository(tmp_path / "maps", "site", "v1")
    task = _task(binding)
    path = repository.save(task)
    before = path.read_bytes()

    def fail_replace(*_args):
        raise OSError("simulated rename failure")

    monkeypatch.setattr("agt_navigation.task_group.os.replace", fail_replace)
    task.description = "changed"
    before_revision = task.revision
    before_updated_at = task.updated_at
    before_hash = task.content_sha256
    with pytest.raises(TaskGroupError, match="atomically write"):
        repository.save(task)
    assert path.read_bytes() == before
    assert task.revision == before_revision
    assert task.updated_at == before_updated_at
    assert task.content_sha256 == before_hash


def test_legacy_import_keeps_compatibility_and_assigns_ids(tmp_path):
    legacy = tmp_path / "old.json"
    legacy.write_text(
        json.dumps({"points": [{"name": "P1", "x": 0, "y": 0, "theta": 3.5}]}),
        encoding="utf-8",
    )
    loaded = load_qt_task_chain(legacy)
    assert loaded[0].name == "P1"
    assert loaded[0].yaw == pytest.approx(3.5 - 2 * math.pi)

    binding = MapBinding("site", "v1", resolution=1.0, width=2, height=2)
    repository = TaskRepository(tmp_path / "maps", "site", "v1")
    task = repository.import_legacy(legacy, task_group_id="imported", name="Imported", map_binding=binding)
    assert task.points[0].id == "wp_0001"
    assert task.points[0].yaw == pytest.approx(3.5 - 2 * math.pi)
    repository.save(task)
    with pytest.raises(TaskGroupError, match="already exists"):
        repository.import_legacy(
            legacy,
            task_group_id="imported",
            name="Imported again",
            map_binding=binding,
        )


def test_binding_states_distinguish_content_and_geometry(tmp_path):
    yaml_path = _write_map(tmp_path)
    snapshot = load_map_snapshot(yaml_path, map_id="site", map_version_id="v1")
    matched = compare_map_binding(snapshot.binding(), snapshot.binding())
    changed = MapBinding(**{**snapshot.binding().__dict__, "map_image_sha256": "sha256:" + "0" * 64})
    geometry = MapBinding(**{**snapshot.binding().__dict__, "origin": (11.0, 20.0, 0.0)})
    assert matched == "MATCHED"
    assert compare_map_binding(changed, snapshot.binding()) == "CONTENT_CHANGED"
    version_changed = MapBinding(
        **{**snapshot.binding().__dict__, "map_version_id": "v2"}
    )
    assert compare_map_binding(version_changed, snapshot.binding()) == "CONTENT_CHANGED"
    assert compare_map_binding(geometry, snapshot.binding()) == "GEOMETRY_MISMATCH"


def test_content_change_warns_but_requires_explicit_rebind(tmp_path):
    yaml_path = _write_map(tmp_path)
    snapshot = load_map_snapshot(yaml_path, map_id="site", map_version_id="v1")
    changed = MapBinding(
        **{**snapshot.binding().__dict__, "map_image_sha256": "sha256:" + "0" * 64}
    )
    report = validate_task_group(_task(changed), snapshot=snapshot)
    assert report.ok
    assert report.binding_state == "CONTENT_CHANGED"
    assert any("explicitly rebind" in item for item in report.warnings)


def test_snapshot_uses_version_relative_path_and_ready_manifest_pcd_hash(tmp_path):
    version = tmp_path / "runtime" / "maps" / "site" / "versions" / "map_v1"
    navigation = version / "navigation"
    pointcloud = version / "pointcloud"
    navigation.mkdir(parents=True)
    pointcloud.mkdir()
    yaml_path = _write_map(navigation)
    pcd = pointcloud / "localization_map.pcd"
    pcd.write_bytes(b"pcd fixture")
    declared = "sha256:" + "a" * 64
    (version / "manifest.yaml").write_text(
        "\n".join(
            (
                "schema_version: 1",
                "map_id: site",
                "map_version_id: map_v1",
                "state: READY",
                "assets:",
                "  localization_pcd:",
                "    path: pointcloud/localization_map.pcd",
                f"    sha256: {declared}",
            )
        ),
        encoding="utf-8",
    )
    snapshot = load_map_snapshot(yaml_path, map_id="site", map_version_id="map_v1")
    assert snapshot.binding().map_yaml_path == "navigation/map.yaml"
    assert snapshot.binding().localization_pcd_sha256 == declared


def test_offline_validation_checks_occupied_unknown_and_line(tmp_path):
    image = tmp_path / "fixture.pgm"
    # top row: free, occupied; bottom row: unknown, free.
    image.write_bytes(b"P5\n2 2\n255\n" + bytes((254, 0, 205, 254)))
    yaml_path = _write_map(tmp_path)
    yaml_path.write_text(yaml_path.read_text(encoding="utf-8").replace("map.pgm", image.name), encoding="utf-8")
    snapshot = load_map_snapshot(yaml_path, map_id="site", map_version_id="v1")
    binding = snapshot.binding()
    occupied = _task(binding, [Waypoint("occupied", "occupied", 11.5, 21.5, 0.0)])
    report = validate_task_group(occupied, snapshot=snapshot)
    assert not report.ok
    assert any("occupied" in item for item in report.errors)
    unknown = _task(binding, [Waypoint("unknown", "unknown", 10.5, 20.5, 0.0)])
    report = validate_task_group(unknown, snapshot=snapshot)
    assert any("unknown" in item for item in report.errors)
    warning = validate_task_group(
        unknown, snapshot=snapshot, unknown_cell_policy="warn"
    )
    assert warning.ok
    assert any("unknown" in item for item in warning.warnings)
    crossing = _task(binding, [Waypoint("a", "A", 10.5, 21.5, 0.0), Waypoint("b", "B", 11.5, 21.5, 0.0)])
    report = validate_task_group(crossing, snapshot=snapshot)
    assert any("occupied" in item for item in report.errors)

    free = _task(binding, [Waypoint("free", "free", 11.5, 20.5, 0.0)])
    assert validate_task_group(free, snapshot=snapshot).ok
    outside = _task(binding, [Waypoint("outside", "outside", 12.0, 20.5, 0.0)])
    assert any(
        "outside" in item
        for item in validate_task_group(outside, snapshot=snapshot).errors
    )


def test_point_limit_and_invalid_json_are_stable(tmp_path):
    binding = MapBinding("site", "v1", resolution=1.0, width=2, height=2)
    points = [
        Waypoint(f"wp_{index}", str(index), float(index), 0.0, 0.0)
        for index in range(3)
    ]
    with pytest.raises(TaskGroupError, match="limit is 2"):
        _task(binding, points).validate(maximum_points=2)
    broken = tmp_path / "broken.json"
    broken.write_text("{", encoding="utf-8")
    with pytest.raises(TaskGroupError, match="cannot read task group JSON"):
        TaskGroup.from_json(broken)
