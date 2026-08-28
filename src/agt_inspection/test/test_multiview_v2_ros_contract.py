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


def test_optional_aggregation_has_finite_result_and_cancel_timeouts():
    adapter = _read("agt_inspection/ros_multiview.py")

    assert "result_timeout_s: float = 10.0" in adapter
    assert "cancel_timeout_s: float = 1.0" in adapter
    assert "view aggregator timed out; Level-1 evidence remains authoritative" in adapter
    assert "_wait_future_timeout" in adapter


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
    assert "DESTINATION share/${PROJECT_NAME}/fixtures" in cmake
    assert "camera_calibration_id" in launch
    assert "camera_calibration_sha256" in launch


def test_ros_python_entries_are_staged_executable_for_symlink_install():
    cmake = _read("CMakeLists.txt")

    # GitHub contents writes can leave scripts at 0644. Installing source paths
    # directly under colcon --symlink-install can therefore expose a non-
    # executable libexec entry. Require the same build-tree staging pattern that
    # agt_bringup already uses successfully.
    assert "AGT_INSPECTION_GENERATED_SCRIPT_DIR" in cmake
    assert "AGT_INSPECTION_GENERATED_SCRIPTS" in cmake
    assert "file(COPY" in cmake
    assert "FILE_PERMISSIONS" in cmake
    assert "OWNER_EXECUTE" in cmake
    assert "GROUP_EXECUTE" in cmake
    assert "WORLD_EXECUTE" in cmake
    assert "install(PROGRAMS" in cmake


def test_mock_level1_contract_contains_raw_count_and_local_instance_ids():
    vision = _read("scripts/mock_vision_server.py")

    assert '"raw_count": 3' in vision
    assert '"local_instance_id": "I0001"' in vision
    assert '"local_instance_id": "I0002"' in vision
    assert '"local_instance_id": "I0003"' in vision


def test_level1_ros_adapter_validates_model_identity_and_encodes_visual_payloads():
    server = _read("scripts/inspection_task_server.py")

    assert "from agt_inspection.image_codec import encode_jpeg, encode_png" in server
    assert "parse_level1_result" in server
    assert "parse_level1_result(" in server
    assert "weights_sha256=str(result.weights_sha256)" in server
    assert "overlay_bytes=encode_jpeg(result.overlay_image)" in server
    assert "mask_bytes=encode_png(result.mask_image)" in server
    assert "result_json=json.dumps(validated.payload" in server
