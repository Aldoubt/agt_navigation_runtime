from pathlib import Path
import hashlib
import importlib.util
import json
import yaml


ROOT = Path(__file__).parents[1]
SCRIPT = ROOT / "scripts/v25_10_realbag_validation.py"
spec = importlib.util.spec_from_file_location("v25_10_validation", SCRIPT)
validation = importlib.util.module_from_spec(spec)
spec.loader.exec_module(validation)


def test_handheld_frames_and_tf_invariants():
    adapter = yaml.safe_load((Path(__file__).parents[2] / "agt_odometry/config/fast_livo2_adapter_handheld.yaml").read_text())["/**"]["ros__parameters"]
    relocalization = yaml.safe_load((ROOT / "config/relocalization_handheld_validation.yaml").read_text())["/**"]["ros__parameters"]
    correction = yaml.safe_load((ROOT / "config/global_correction_handheld_validation.yaml").read_text())["/**"]["ros__parameters"]
    assert adapter["base_frame"] == adapter["backend_body_frame"] == "imu_link"
    assert relocalization["base_frame"] == correction["base_frame"] == "imu_link"
    assert relocalization["publish_tf"] is False
    assert correction["canonical_status_topic"] == "/agt/localization/status"


def test_mapping_launch_wires_overridable_adapter_parameters():
    source = (Path(__file__).parents[2] / "agt_odometry/launch/fast_livo2_odometry.launch.py").read_text()
    assert '"adapter_params_file"' in source
    assert 'LaunchConfiguration("adapter_params_file")' in source


def test_rviz_references_validation_topics():
    rviz = (ROOT / "rviz/v25_10_realbag_validation.rviz").read_text()
    for topic in ("/agt/localization/reference_map", "/agt/odometry/registered_points", "/agt/localization/aligned_points", "/agt/localization/candidate_pose", "/agt/localization/global_pose", "/agt/odometry/odometry"):
        assert topic in rviz
    assert "Fixed Frame: map" in rviz


def test_validation_rviz_is_valid_yaml():
    rviz = yaml.safe_load((ROOT / "rviz/v25_10_realbag_validation.rviz").read_text())
    assert isinstance(rviz, dict)
    assert rviz["Visualization Manager"]["Fixed Frame"] == "map"


def test_processing_record_is_ready_and_hash_bound():
    asset = Path(__file__).parents[3] / "runtime/localization_validation/handheld_20260719"
    record = yaml.safe_load((asset / "processing_record.yaml").read_text())
    digest = hashlib.sha256((asset / "localization_map.pcd").read_bytes()).hexdigest()
    assert record["state"] == "ready"
    assert record["pcd_sha256"] == "sha256:" + digest


def test_fresh_cloud_barrier_accepts_new_fresh_stamp():
    barrier = validation.FreshCloudBarrier(0.20)
    barrier.mapping_gate_last_cloud_stamp = 10.0
    barrier.observe(10.1)
    assert barrier.accept(10.2)


def test_fresh_cloud_barrier_rejects_old_stamp():
    barrier = validation.FreshCloudBarrier(0.20)
    barrier.mapping_gate_last_cloud_stamp = 10.0
    barrier.observe(10.1)
    assert not barrier.accept(10.31)


def test_action_and_playback_classification_contract():
    stale = validation.classify_action_result(113, False)
    assert stale["code"] == "STALE_CLOUD_AT_ACTION"
    assert stale["stage"] == "ACTION_INPUT_FRESHNESS"
    assert stale["registration_executed"] is False
    assert validation.playback_gate(1.0)["pipeline_pass_allowed"]
    assert validation.playback_gate(0.5)["classification"] == "DEBUG_PLAYBACK_RATE"


def test_freshness_cli_parameter_controls_dispatch_check():
    source = SCRIPT.read_text(encoding="utf-8")
    assert "FreshCloudBarrier(fresh_action_max_age_s)" in source
    assert "node.cloud_age_at_goal_send_s > fresh_action_max_age_s" in source
    assert "node.cloud_age_at_goal_send_s > FRESH_CLOUD_MAX_AGE_S" not in source
    assert "max_cloud_age_s: 0.5" in (ROOT / "config/relocalization.yaml").read_text()


def test_validation_modes_and_launch_recovery_wiring():
    source = SCRIPT.read_text(encoding="utf-8")
    launch = (ROOT / "launch/v25_10_realbag_validation.launch.py").read_text(encoding="utf-8")
    assert 'choices=("manual_action", "auto_recovery")' in source
    assert 'validation_mode == "auto_recovery"' in source
    assert 'enable_recovery_trigger:={' in source
    assert 'DeclareLaunchArgument("enable_recovery_trigger", default_value="false")' in launch
    assert '"enabled": ParameterValue(' in (ROOT / "launch/relocalization.launch.py").read_text(encoding="utf-8")


def test_fresh_barrier_precedes_manual_goal_and_ordered_cleanup_is_present():
    source = SCRIPT.read_text(encoding="utf-8")
    assert "node.barrier.accept(now_s)" in source
    assert "node.action.send_goal_async" in source
    assert source.index("node.barrier.accept(now_s)") < source.index("node.action.send_goal_async")
    assert "cancel_goal_async()" in source
    assert "action_cancel_timeout_s" in source
    assert "playback = subprocess.Popen" in source
    assert source.index("recorder = subprocess.Popen") < source.index("playback = subprocess.Popen")


def test_manual_action_never_pauses_clock_source():
    source = SCRIPT.read_text(encoding="utf-8")
    assert "signal.SIGSTOP" not in source
    assert "signal.SIGCONT" not in source
    assert source.index("node.barrier.accept(now_s)") < source.index("fresh_cloud_time")
    assert source.index("fresh_cloud_time") < source.index("node.action.send_goal_async")


def test_fresh_stamp_tf_gate_occurs_after_fresh_barrier():
    source = SCRIPT.read_text(encoding="utf-8")
    assert source.index('stage("FRESH_CLOUD"') < source.index("fresh_cloud_time")
    assert 'nanoseconds=int(node.fresh_cloud_stamp * 1e9)' in source
    assert '"odom", "lidar_link", fresh_cloud_time' in source


def test_fresh_stamp_tf_gate_precedes_action_dispatch():
    source = SCRIPT.read_text(encoding="utf-8")
    assert source.index('stage("PRE_ACTION_TF_GATE"') < source.index("node.action.send_goal_async")
    assert '"goal_not_dispatched": True' in source


def test_clock_preflight_requires_zero_publishers():
    assert validation.clock_gate_code(0, before_playback=True) is None
    assert validation.clock_gate_code(1, before_playback=True) == "CLOCK_PUBLISHER_CONFLICT"


def test_playback_requires_exactly_one_clock_publisher():
    assert validation.clock_gate_code(0) == "CLOCK_NOT_AVAILABLE"
    assert validation.clock_gate_code(1) is None
    assert validation.clock_gate_code(2) == "MULTIPLE_CLOCK_PUBLISHERS"


def test_monotonic_clock_accepts_forward_time_and_detects_rollback():
    clock = validation.ClockMonotonicity()
    assert clock.observe(10) is None
    assert clock.observe(20) is None
    rollback = clock.observe(15, wall_time=123.0)
    assert rollback["previous_clock_ns"] == 20
    assert rollback["current_clock_ns"] == 15
    assert rollback["rollback_ns"] == 5


def test_time_rollback_invalidates_algorithm_result():
    clock = validation.ClockMonotonicity()
    clock.observe(100)
    assert clock.observe(99) is not None
    assert validation.failure("ROS_TIME", "ROS_TIME_ROLLBACK", "rollback", clock.rollback)["code"] == "ROS_TIME_ROLLBACK"


def test_single_run_forbids_second_playback():
    guard = validation.SinglePlaybackGuard()
    guard.start()
    try:
        guard.start()
    except RuntimeError as error:
        assert "only one rosbag player" in str(error)
    else:
        assert False, "second playback was accepted"


def test_partial_result_exists_before_playback_and_updates_after_each_stage(tmp_path):
    report = validation.DurableRunReport(tmp_path, "run-test")
    assert (tmp_path / "result.md").exists()
    assert json.loads((tmp_path / "result.json").read_text())["status"] == "RUNNING"
    report.stage("CLOCK_PREFLIGHT", "PASS", publisher_count=0)
    data = json.loads((tmp_path / "result.json").read_text())
    assert data["stages"][-1]["name"] == "CLOCK_PREFLIGHT"
    assert "PASS" in (tmp_path / "result.md").read_text()


def test_sigterm_flushes_partial_report():
    source = SCRIPT.read_text(encoding="utf-8")
    assert "signal.signal(signal.SIGTERM" in source
    assert 'report.interrupted("SIGINT/SIGTERM")' in source
    assert 'self.data["status"] = "INTERRUPTED"' in source


def test_clock_observer_uses_rosbag_compatible_qos():
    source = SCRIPT.read_text(encoding="utf-8")
    assert "ReliabilityPolicy.BEST_EFFORT" in source
    assert "DurabilityPolicy.VOLATILE" in source
    assert "self.create_subscription(Clock, \"/clock\", self.clock_seen, clock_qos)" in source


def test_rviz_pointcloud_qos_matches_validation_publishers():
    rviz = (ROOT / "rviz/v25_10_realbag_validation.rviz").read_text(encoding="utf-8")
    publisher = (ROOT / "scripts/reference_map_publisher.py").read_text(encoding="utf-8")
    assert rviz.count("Reliability Policy: Best Effort") >= 2
    assert rviz.count("Durability Policy: Volatile") >= 2
    assert "DurabilityPolicy.TRANSIENT_LOCAL" in publisher
    assert "ReliabilityPolicy.RELIABLE" in publisher


def test_action_lifecycle_and_feedback_are_durable():
    source = SCRIPT.read_text(encoding="utf-8")
    for stage in ("FRESH_CLOUD", "PRE_ACTION_TF_GATE", "ACTION_DISPATCHED", "ACTION_GOAL_ACCEPTED", "FIRST_FEEDBACK", "ACTION_RESULT"):
        assert 'stage("%s"' % stage in source
    assert 'os.fsync(stream.fileno())' in source
    assert 'action_feedback.jsonl' in source


def test_cloud_stamp_tf_gates_precede_action_dispatch():
    source = SCRIPT.read_text(encoding="utf-8")
    assert '"imu_link", "lidar_link"' in source
    assert '"odom", "lidar_link", fresh_cloud_time' in source
    assert source.index("ODOM_LIDAR_FRESH_STAMP_TF_MISSING") < source.index("ACTION_DISPATCHED")


def test_goal_and_result_have_independent_timeouts():
    source = SCRIPT.read_text(encoding="utf-8")
    assert "goal_response_deadline = time.monotonic() + 5.0" in source
    assert "action_result_deadline = time.monotonic() + goal.timeout_s + 5.0" in source
    assert "ACTION_GOAL_RESPONSE_TIMEOUT" in source
    assert "ACTION_RESULT_TIMEOUT" in source
    assert "ACTION_RESULT_TIMEOUT\", \"Relocalize result timed out" in source
    assert "RELOCALIZE_REJECTED\", \"Relocalize result timed out" not in source


def test_action_timeout_not_classified_as_relocalize_rejected():
    source = SCRIPT.read_text(encoding="utf-8")
    assert "ACTION_GOAL_RESPONSE_TIMEOUT" in source
    assert "ACTION_RESULT_TIMEOUT" in source
    assert 'failure("relocalization", "ACTION_RESULT_TIMEOUT"' in source
    assert 'failure("relocalization", "RELOCALIZE_REJECTED", "Relocalize result timed out"' not in source


def test_action_lifecycle_stages_are_durable():
    source = SCRIPT.read_text(encoding="utf-8")
    for stage in ("FRESH_CLOUD", "PRE_ACTION_TF_GATE", "ACTION_DISPATCHED",
                  "ACTION_GOAL_ACCEPTED", "FIRST_FEEDBACK", "ACTION_RESULT"):
        assert 'stage("%s"' % stage in source
    assert "self.data[\"stages\"]" in (ROOT / "scripts/v25_10_realbag_validation.py").read_text()


def test_optional_debug_cloud_contract():
    source = (ROOT / "src/relocalization_node.cpp").read_text(encoding="utf-8")
    rviz = (ROOT / "rviz/v25_10_realbag_validation.rviz").read_text(encoding="utf-8")
    assert 'publish_initial_guess_cloud", false' in source
    assert 'publish_aligned_candidate_cloud", false' in source
    assert "/agt/localization/initial_guess" in source
    assert "/agt/localization/aligned_candidate" in source
    assert "Value: /agt/localization/initial_guess" in rviz
    assert "Value: /agt/localization/aligned_candidate" in rviz


def test_localization_status_uses_correction_generation():
    message = (Path(__file__).parents[2] / "agt_interfaces/msg/LocalizationStatus.msg").read_text()
    assert "uint64 correction_generation" in message
    source = SCRIPT.read_text(encoding="utf-8")
    assert "message.correction_generation" in source
    assert 'getattr(message, "generation"' not in source


def test_handheld_debug_clouds_enabled():
    config = yaml.safe_load((ROOT / "config/relocalization_handheld_validation.yaml").read_text())["/**"]["ros__parameters"]
    assert config["publish_initial_guess_cloud"] is True
    assert config["publish_aligned_candidate_cloud"] is True


def test_initial_guess_published_before_backend_call():
    source = (ROOT / "src/relocalization_node.cpp").read_text(encoding="utf-8")
    assert source.index("initial_guess_cloud_pub_->publish") < source.index("relocalizer_.relocalize(request)")


def test_aligned_candidate_can_publish_before_final_acceptance():
    source = (ROOT / "src/relocalization_node.cpp").read_text(encoding="utf-8")
    candidate_publish = source.index("aligned_candidate_cloud_pub_->publish")
    final_quality = source.index("if (attempt.quality.accepted)")
    assert candidate_publish < final_quality


def test_rviz_enables_map_frame_debug_clouds():
    rviz = (ROOT / "rviz/v25_10_realbag_validation.rviz").read_text(encoding="utf-8")
    assert "Fixed Frame: map" in rviz
    assert "Name: Initial Guess\n" in rviz and "Name: Aligned Candidate\n" in rviz
    assert "Name: Current Registered Cloud (visible after map->odom)" in rviz
