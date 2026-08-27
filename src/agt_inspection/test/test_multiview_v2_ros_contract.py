from pathlib import Path


PACKAGE = Path(__file__).resolve().parents[1]


def _read(relative: str) -> str:
    return (PACKAGE / relative).read_text(encoding="utf-8")


def test_schema_v2_runtime_routes_through_multiview_executor_and_store():
    server = _read("scripts/inspection_task_server.py")

    assert "MultiviewInspectionExecutor" in server
    assert "InspectionEvidenceStore" in server
    assert "if task.schema_version == 2:" in server
    assert "evidence_store=InspectionEvidenceStore(self._evidence_root)" in server
    assert "aggregator=self._view_aggregator" in server
    assert "context_provider=self._view_context" in server


def test_multiview_ros_adapter_uses_capture_stamp_and_accepted_localization_history():
    adapter = _read("agt_inspection/ros_multiview.py")

    assert '"/agt/localization/status"' in adapter
    assert "self._history = deque" in adapter
    assert "capture_stamp(request_id)" in adapter
    assert "min(candidates, key=lambda item: abs(item[0] - capture_ns))" in adapter
    assert "STATE_TRACKING" in adapter
    assert "localization_accepted" in adapter
    assert "status_stale" in adapter
    assert '"/agt/vision/aggregate_views"' in adapter
    assert "InspectionViewObservation" in adapter


def test_mock_launch_is_hardware_free_and_uses_installed_fixture_assets():
    launch = _read("launch/mock_inspection.launch.py")
    cmake = _read("CMakeLists.txt")

    for executable in (
        "mock_runtime_context.py",
        "mock_waypoint_task_server.py",
        "mock_gimbal_server.py",
        "mock_camera_server.py",
        "mock_vision_server.py",
        "mock_view_aggregator_server.py",
        "inspection_task_server.py",
    ):
        assert executable in launch
        assert executable in cmake

    assert 'FindPackageShare("agt_inspection")' in launch
    assert '"fixtures", "runtime", "maps"' in launch
    assert "install(DIRECTORY test/fixtures/" in cmake
    assert "camera_calibration_id" in launch
    assert "camera_calibration_sha256" in launch


def test_mock_level1_contract_contains_raw_count_and_local_instance_ids():
    vision = _read("scripts/mock_vision_server.py")

    assert '"raw_count": 3' in vision
    assert '"local_instance_id": "I0001"' in vision
    assert '"local_instance_id": "I0002"' in vision
    assert '"local_instance_id": "I0003"' in vision
