import json
from pathlib import Path

import pytest
import yaml

from agt_navigation.route_runtime import RouteRuntimeError
from agt_navigation.route_task_binding import RouteTaskResolver, sha256_file
from agt_navigation.task_group import MapBinding, TaskGroup, Waypoint


def _task(root: Path):
    maps_root = root / "maps"
    tasks_root = root / "tasks"
    version = maps_root / "site" / "versions" / "map_v1"
    task_version = tasks_root / "site" / "map_v1"
    task_version.mkdir(parents=True, exist_ok=True)
    (version / "routes" / "route_main" / "1").mkdir(parents=True, exist_ok=True)

    map_content = "sha256:" + "a" * 64
    (version / "manifest.yaml").write_text(
        yaml.safe_dump(
            {
                "schema_version": 1,
                "map_id": "site",
                "map_version_id": "map_v1",
                "state": "READY",
                "map_content_sha256": map_content,
            },
            sort_keys=False,
        ),
        encoding="utf-8",
    )

    task = TaskGroup(
        task_group_id="inspection",
        name="Inspection",
        description="",
        created_at="2026-08-08T00:00:00+00:00",
        updated_at="2026-08-08T00:00:00+00:00",
        revision=3,
        map_binding=MapBinding(
            "site",
            "map_v1",
            map_yaml_sha256="sha256:yaml",
            map_image_sha256="sha256:image",
            localization_pcd_sha256="sha256:pcd",
            resolution=0.05,
            width=100,
            height=100,
            origin=(0.0, 0.0, 0.0),
        ),
        points=[Waypoint("wp_1", "A", 0.0, 0.0, 0.0)],
    )
    task.content_sha256 = task.canonical_hash()
    (task_version / "inspection.json").write_text(
        json.dumps(task.to_dict(), ensure_ascii=False), encoding="utf-8"
    )

    route_dir = version / "routes" / "route_main" / "1"
    route_csv = route_dir / "route.csv"
    route_csv.write_text(
        "seq,segment_id,x,y,yaw,direction,v_ref,curvature,clearance,semantic_ref,event_ref\n"
        "0,s000,0.0,0.0,0.0,F,0.2,0.0,1.0,row_0,\n"
        "1,s000,1.0,0.0,0.0,F,0.2,0.0,1.0,row_0,stop_a\n",
        encoding="utf-8",
    )
    vehicle_hash = "sha256:" + "b" * 64
    route_manifest = {
        "schema_version": 1,
        "route_id": "route_main",
        "revision": 1,
        "frame_id": "map",
        "map_binding": {
            "map_id": "site",
            "map_version_id": "map_v1",
            "map_content_sha256": map_content,
        },
        "vehicle_binding": {
            "platform_id": "mk_mini",
            "platform_profile_sha256": vehicle_hash,
        },
        "route_csv_sha256": sha256_file(route_csv),
        "status": "READY",
    }
    route_yaml = route_dir / "route.yaml"
    route_yaml.write_text(yaml.safe_dump(route_manifest, sort_keys=False), encoding="utf-8")
    return task, maps_root, tasks_root, version, task_version, route_yaml, vehicle_hash


def _write_binding(task, task_version, route_yaml):
    binding = {
        "schema_version": 1,
        "status": "READY",
        "backend": "ROUTE",
        "task_binding": {
            "task_group_id": task.task_group_id,
            "task_revision": task.revision,
            "task_content_sha256": task.content_sha256,
        },
        "route_binding": {
            "route_id": "route_main",
            "revision": 1,
            "route_manifest_sha256": sha256_file(route_yaml),
        },
    }
    path = task_version / f"{task.task_group_id}.route.yaml"
    path.write_text(yaml.safe_dump(binding, sort_keys=False), encoding="utf-8")
    return path


def test_missing_route_binding_preserves_map_backend(tmp_path):
    task, maps_root, tasks_root, _version, _task_version, _route_yaml, vehicle_hash = _task(tmp_path)
    resolved = RouteTaskResolver(maps_root, tasks_root).resolve(
        task, expected_vehicle_profile_sha256=vehicle_hash
    )
    assert resolved is None


def test_exact_task_revision_resolves_ready_route(tmp_path):
    task, maps_root, tasks_root, _version, task_version, route_yaml, vehicle_hash = _task(tmp_path)
    binding = _write_binding(task, task_version, route_yaml)

    resolved = RouteTaskResolver(maps_root, tasks_root).resolve(
        task, expected_vehicle_profile_sha256=vehicle_hash
    )

    assert resolved is not None
    assert resolved.binding_path == binding
    assert resolved.asset.route_id == "route_main"
    assert resolved.asset.revision == 1
    assert resolved.asset.segments[0].event_refs == ("stop_a",)


def test_legacy_map_tasks_route_binding_is_not_an_implicit_fallback(tmp_path):
    task, maps_root, tasks_root, version, _task_version, route_yaml, vehicle_hash = _task(tmp_path)
    legacy_tasks = version / "tasks"
    legacy_tasks.mkdir(parents=True, exist_ok=True)
    _write_binding(task, legacy_tasks, route_yaml)

    resolved = RouteTaskResolver(maps_root, tasks_root).resolve(
        task, expected_vehicle_profile_sha256=vehicle_hash
    )

    assert resolved is None


def test_stale_task_binding_fails_closed(tmp_path):
    task, maps_root, tasks_root, _version, task_version, route_yaml, vehicle_hash = _task(tmp_path)
    binding_path = _write_binding(task, task_version, route_yaml)
    binding = yaml.safe_load(binding_path.read_text(encoding="utf-8"))
    binding["task_binding"]["task_revision"] = task.revision - 1
    binding_path.write_text(yaml.safe_dump(binding, sort_keys=False), encoding="utf-8")

    with pytest.raises(RouteRuntimeError) as exc:
        RouteTaskResolver(maps_root, tasks_root).resolve(
            task, expected_vehicle_profile_sha256=vehicle_hash
        )
    assert exc.value.code == "route_task_binding_mismatch"


def test_route_manifest_change_invalidates_execution_binding(tmp_path):
    task, maps_root, tasks_root, _version, task_version, route_yaml, vehicle_hash = _task(tmp_path)
    _write_binding(task, task_version, route_yaml)
    route_yaml.write_text(route_yaml.read_text(encoding="utf-8") + "notes: changed\n", encoding="utf-8")

    with pytest.raises(RouteRuntimeError) as exc:
        RouteTaskResolver(maps_root, tasks_root).resolve(
            task, expected_vehicle_profile_sha256=vehicle_hash
        )
    assert exc.value.code == "route_binding_manifest_hash_mismatch"


def test_vehicle_profile_mismatch_fails_closed(tmp_path):
    task, maps_root, tasks_root, _version, task_version, route_yaml, _vehicle_hash = _task(tmp_path)
    _write_binding(task, task_version, route_yaml)

    with pytest.raises(RouteRuntimeError) as exc:
        RouteTaskResolver(maps_root, tasks_root).resolve(
            task, expected_vehicle_profile_sha256="sha256:" + "c" * 64
        )
    assert exc.value.code == "route_vehicle_binding_mismatch"


def test_task_binding_identity_symlink_fails_closed(tmp_path):
    task, maps_root, tasks_root, _version, task_version, route_yaml, vehicle_hash = _task(tmp_path)
    _write_binding(task, task_version, route_yaml)
    real_site = tasks_root / "site"
    moved_site = tasks_root / "site_real"
    real_site.rename(moved_site)
    real_site.symlink_to(moved_site, target_is_directory=True)

    with pytest.raises(RouteRuntimeError) as exc:
        RouteTaskResolver(maps_root, tasks_root).resolve(
            task, expected_vehicle_profile_sha256=vehicle_hash
        )
    assert exc.value.code == "route_binding_path_escape"
