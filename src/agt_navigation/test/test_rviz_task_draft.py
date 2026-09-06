from agt_navigation.rviz_task_draft import DraftStateError, RvizTaskDraft
from agt_navigation.task_group import MapBinding, TaskGroup
import pytest


def _binding():
    return MapBinding(
        map_id="orchard",
        map_version_id="map_v1",
        map_yaml_path="map/navigation.yaml",
        map_yaml_sha256="sha256:" + "1" * 64,
        map_image_sha256="sha256:" + "2" * 64,
        localization_pcd_sha256="sha256:" + "3" * 64,
        resolution=0.05,
        width=200,
        height=120,
        origin=(-1.0, -2.0, 0.0),
    )


def test_draft_add_undo_clear_keeps_ordered_numbered_points():
    draft = RvizTaskDraft()

    first = draft.add(1.0, 2.0, 0.25)
    second = draft.add(3.0, 4.0, -0.5)

    assert first.id == "P01"
    assert first.name == "P01"
    assert second.id == "P02"
    assert [(p.x, p.y, p.yaw) for p in draft.points] == [
        (1.0, 2.0, 0.25),
        (3.0, 4.0, -0.5),
    ]
    assert draft.dirty is True

    assert draft.undo() is True
    assert [point.id for point in draft.points] == ["P01"]
    assert draft.undo() is True
    assert draft.undo() is False

    draft.add(5.0, 6.0, 1.0)
    draft.clear()
    assert draft.points == ()
    assert draft.dirty is True


def test_build_task_reuses_task_group_v1_contract_and_content_hash():
    draft = RvizTaskDraft()
    draft.add(1.0, 2.0, 0.25)
    draft.add(3.0, 4.0, -0.5)

    task = draft.build_task(
        map_binding=_binding(),
        task_group_id="inspection_main",
        name="Inspection Main",
        description="RViz acceptance route",
        revision=1,
        created_at="2026-08-31T00:00:00+00:00",
        updated_at="2026-08-31T00:01:00+00:00",
    )

    task.validate()
    assert task.to_dict()["schema_version"] == 1
    assert task.content_sha256 == task.canonical_hash()
    assert task.map_binding == _binding()
    assert [point.id for point in task.points] == ["P01", "P02"]


def test_loaded_task_is_clean_and_new_edit_blocks_start_until_saved():
    draft = RvizTaskDraft()
    draft.add(1.0, 2.0, 0.0)
    stored = draft.build_task(
        map_binding=_binding(),
        task_group_id="inspection_main",
        name="Inspection Main",
        description="",
        revision=3,
        created_at="2026-08-31T00:00:00+00:00",
        updated_at="2026-08-31T00:03:00+00:00",
    )
    draft.mark_saved(stored)

    saved = draft.execution_ref()
    assert saved.task_group_id == "inspection_main"
    assert saved.revision == 3
    assert saved.content_sha256 == stored.content_sha256
    assert draft.dirty is False

    draft.add(7.0, 8.0, 0.75)
    assert draft.dirty is True
    with pytest.raises(DraftStateError, match="save"):
        draft.execution_ref()

    loaded = RvizTaskDraft()
    loaded.load_task(TaskGroup.from_dict(stored.to_dict()))
    assert loaded.dirty is False
    assert [point.id for point in loaded.points] == ["P01"]
    assert loaded.execution_ref().revision == 3


def test_draft_rejects_nonfinite_pose_and_empty_task_build():
    draft = RvizTaskDraft()
    with pytest.raises(ValueError, match="finite"):
        draft.add(float("nan"), 0.0, 0.0)
    with pytest.raises(DraftStateError, match="no waypoints"):
        draft.build_task(
            map_binding=_binding(),
            task_group_id="inspection_main",
            name="Inspection Main",
            description="",
            revision=1,
        )
