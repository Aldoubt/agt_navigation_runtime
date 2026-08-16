#!/usr/bin/env python3
"""Fail-closed V25-10 real-bag pipeline validation harness.

This is a system-test tool: it owns process orchestration and observation only;
Relocalize remains a project Action and map->odom remains manager-owned.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import signal
import subprocess
import sys
import threading
import time

import yaml


FAILURE_CODES = {
    "interface": "INTERFACE_TYPESUPPORT_UNAVAILABLE",
    "bag": "BAG_TOPIC_MISSING",
    "map": "REFERENCE_MAP_INVALID",
    "map_hash": "MAP_HASH_MISMATCH",
    "candidate": "CANDIDATE_IDENTITY_MISMATCH",
    "registered": "REGISTERED_POINTS_TIMEOUT",
    "odometry": "ODOMETRY_TIMEOUT",
    "fresh": "FRESH_CLOUD_TIMEOUT",
}

FRESH_CLOUD_MAX_AGE_S = 0.20
STALE_SCAN_ERROR_CODE = 113


class ValidationInterrupted(RuntimeError):
    pass


class ValidationEnvironmentInvalid(RuntimeError):
    def __init__(self, error):
        super().__init__(error["message"])
        self.error = error


def atomic_write(path, content):
    """Persist a report before replacing the visible file."""
    path = Path(path)
    temporary = path.with_name("." + path.name + ".tmp")
    with open(temporary, "w", encoding="utf-8") as stream:
        stream.write(content)
        stream.flush()
        os.fsync(stream.fileno())
    os.replace(temporary, path)


class DurableRunReport:
    def __init__(self, directory, run_id):
        self.directory = Path(directory)
        self.run_id = run_id
        self.data = {"run_id": run_id, "status": "RUNNING", "stages": [], "diagnostics": {}}
        self.update()

    def update(self):
        atomic_write(self.directory / "result.json", json.dumps(self.data, indent=2, sort_keys=True) + "\n")
        lines = ["# V25-10 Real-Bag Validation", "", "Status: **%s**" % self.data["status"], ""]
        for stage in self.data["stages"]:
            lines.append("- `%s`: **%s**" % (stage["name"], stage["status"]))
        if self.data.get("failure"):
            lines.extend(["", "Failure: `%s` — %s" % (self.data["failure"].get("code"), self.data["failure"].get("message"))])
        atomic_write(self.directory / "result.md", "\n".join(lines) + "\n")

    def stage(self, name, status, **details):
        entry = {"name": name, "status": status}
        if details:
            entry["details"] = details
        self.data["stages"] = [item for item in self.data["stages"] if item["name"] != name]
        self.data["stages"].append(entry)
        self.update()

    def fail(self, error):
        self.data["status"] = "ENVIRONMENT_INVALID" if error.get("code") == "ROS_TIME_ROLLBACK" else "FAIL"
        self.data["failure"] = error
        self.update()

    def interrupted(self, signal_name):
        self.data["status"] = "INTERRUPTED"
        self.data["interrupted_by"] = signal_name
        self.update()


class ClockMonotonicity:
    def __init__(self):
        self.previous_clock_ns = None
        self.rollback = None

    def observe(self, current_clock_ns, wall_time=None):
        previous = self.previous_clock_ns
        self.previous_clock_ns = current_clock_ns
        if previous is not None and current_clock_ns < previous:
            self.rollback = {"previous_clock_ns": previous, "current_clock_ns": current_clock_ns,
                              "rollback_ns": previous - current_clock_ns,
                              "wall_time": time.time() if wall_time is None else wall_time}
            return self.rollback
        return None


class SinglePlaybackGuard:
    def __init__(self):
        self.started = False

    def start(self):
        if self.started:
            raise RuntimeError("a validation run may start only one rosbag player")
        self.started = True


class TimeDiagnostics:
    def __init__(self, path):
        self.path = Path(path)
        self.path.touch()
        self.clock = ClockMonotonicity()
        self.latest_clock_ns = None
        self.latest_cloud_ns = None
        self.latest_odom_ns = None
        self.last_tf_ns = None

    def append(self, event, **data):
        payload = {"wall_time": time.time(), "event": event, **data}
        with open(self.path, "a", encoding="utf-8") as stream:
            stream.write(json.dumps(payload, sort_keys=True) + "\n")
            stream.flush()
            os.fsync(stream.fileno())

    def clock_message(self, stamp_ns):
        rollback = self.clock.observe(stamp_ns)
        self.latest_clock_ns = stamp_ns
        self.append("clock", clock_ros_time_ns=stamp_ns, rollback=rollback)
        return rollback

    def sensor_message(self, kind, stamp_ns):
        previous = self.latest_cloud_ns if kind == "registered_cloud" else self.latest_odom_ns
        if kind == "registered_cloud":
            self.latest_cloud_ns = stamp_ns
        else:
            self.latest_odom_ns = stamp_ns
        self.append(kind, clock_ros_time_ns=self.latest_clock_ns, sensor_stamp_ns=stamp_ns,
                    sensor_stamp_rollback=previous is not None and stamp_ns < previous,
                    sensor_age_s=None if self.latest_clock_ns is None else (self.latest_clock_ns - stamp_ns) * 1e-9)

    def tf_message(self, stamp_ns):
        previous = self.last_tf_ns
        self.last_tf_ns = stamp_ns
        self.append("tf", clock_ros_time_ns=self.latest_clock_ns, last_tf_stamp_ns=stamp_ns,
                    tf_stamp_rollback=previous is not None and stamp_ns < previous)


def clock_publisher_diagnostic(infos):
    publishers = []
    for info in infos:
        def value(attribute, fallback):
            return getattr(info, attribute) if hasattr(info, attribute) else info.get(fallback, "")
        publishers.append({"node_name": value("node_name", "node_name"),
                           "namespace": value("node_namespace", "namespace"),
                           "gid": value("endpoint_gid", "gid"),
                           "qos": str(value("qos_profile", "qos"))})
    return publishers


def clock_gate_code(count, before_playback=False):
    if before_playback:
        return None if count == 0 else "CLOCK_PUBLISHER_CONFLICT"
    if count == 0:
        return "CLOCK_NOT_AVAILABLE"
    if count > 1:
        return "MULTIPLE_CLOCK_PUBLISHERS"
    return None


class FreshCloudBarrier:
    """Validation-only barrier; it never changes relocalization thresholds."""

    def __init__(self, max_age_s=FRESH_CLOUD_MAX_AGE_S):
        self.max_age_s = max_age_s
        self.mapping_gate_last_cloud_stamp = None
        self.latest_stamp = None
        self.event = threading.Event()

    def observe(self, stamp):
        if self.latest_stamp is None or stamp > self.latest_stamp:
            self.latest_stamp = stamp
            self.event.set()

    def accept(self, ros_now):
        if self.mapping_gate_last_cloud_stamp is None or self.latest_stamp is None:
            return False
        age = ros_now - self.latest_stamp
        return (self.latest_stamp > self.mapping_gate_last_cloud_stamp and
                0.0 <= age <= self.max_age_s)


def classify_action_result(error_code, success):
    if success:
        return {"stage": "REGISTRATION", "code": "PASS", "registration_executed": True}
    if int(error_code) == STALE_SCAN_ERROR_CODE:
        return {"stage": "ACTION_INPUT_FRESHNESS", "code": "STALE_CLOUD_AT_ACTION",
                "registration_executed": False}
    return {"stage": "REGISTRATION", "code": "REGISTRATION_REJECTED",
            "registration_executed": True}


def playback_gate(playback_rate, formal_min_rate=5.0):
    if playback_rate == 1.0:
        return {"classification": "FORMAL", "minimum_wall_rate_hz": formal_min_rate,
                "pipeline_pass_allowed": True}
    return {"classification": "DEBUG_PLAYBACK_RATE",
            "minimum_wall_rate_hz": formal_min_rate * playback_rate,
            "pipeline_pass_allowed": False}


def wait_for_action_server(timeout_s):
    """Complete Action-server readiness before any bag clock or recorder starts."""
    import rclpy
    from agt_interfaces.action import Relocalize
    from rclpy.action import ActionClient
    from rclpy.node import Node
    rclpy.init()
    node = Node("v25_10_realbag_validation_action_ready")
    client = ActionClient(node, Relocalize, "/agt/localization/relocalize")
    try:
        return client.wait_for_server(timeout_sec=timeout_s)
    finally:
        node.destroy_node()
        rclpy.try_shutdown()


def query_clock_publishers(timeout_s=2.0):
    """Use an isolated rclpy context so graph probing cannot reuse TF state."""
    import rclpy
    from rclpy.node import Node
    context = rclpy.Context()
    rclpy.init(context=context)
    node = Node("v25_10_realbag_validation_clock_probe", context=context)
    try:
        deadline = time.monotonic() + timeout_s
        while time.monotonic() < deadline:
            infos = node.get_publishers_info_by_topic("/clock")
            if infos:
                return clock_publisher_diagnostic(infos)
            time.sleep(0.05)
        return clock_publisher_diagnostic(node.get_publishers_info_by_topic("/clock"))
    finally:
        node.destroy_node()
        context.try_shutdown()


def process_diagnostics():
    patterns = {
        "rosbag2_player": "rosbag2 play",
        "agt_relocalization": "agt_relocalization",
        "agt_global_correction_manager": "agt_global_correction_manager",
        "agt_recovery_trigger_manager": "agt_recovery_trigger_manager",
        "fast_livo2_backend": "fast_livo2_backend",
        "agt_odometry_fast_livo2_adapter": "agt_odometry_fast_livo2_adapter",
        "reference_map_publisher": "reference_map_publisher",
    }
    try:
        output = subprocess.run(["ps", "-eo", "pid=,args="], check=False, capture_output=True, text=True, timeout=5).stdout
    except (OSError, subprocess.SubprocessError) as error:
        return {"status": "unavailable", "error": str(error), "matches": {}}
    matches = {name: [] for name in patterns}
    for line in output.splitlines():
        text = line.strip()
        if not text:
            continue
        pid, _, command = text.partition(" ")
        for name, pattern in patterns.items():
            if pattern in command and "v25_10_realbag_validation" not in command:
                matches[name].append({"pid": pid, "command": command})
    return {"status": "available", "matches": matches}


def sha256(path):
    digest = hashlib.sha256()
    with open(path, "rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return "sha256:" + digest.hexdigest()


def failure(stage, code, message, evidence=None):
    return {"stage": stage, "code": code, "message": message, "evidence": evidence or {}}


def preflight(args):
    result = {"ros_distro": os.environ.get("ROS_DISTRO", ""), "checks": {}}
    if result["ros_distro"] != "humble":
        return result, failure("preflight", "INTERFACE_TYPESUPPORT_UNAVAILABLE", "ROS_DISTRO must be humble", result)
    try:
        from agt_interfaces.action import Relocalize  # noqa: F401
        from agt_interfaces.msg import LocalizationStatus  # noqa: F401
        result["checks"]["interface_typesupport"] = "PASS"
    except Exception as error:
        return result, failure("preflight", FAILURE_CODES["interface"], str(error), {
            "source_hint": ["source /opt/ros/humble/setup.bash", "source ~/agt_navigation_runtime/install/setup.bash"]
        })
    conflicts = {"fast_livo2_backend", "agt_odometry_fast_livo2_adapter", "agt_relocalization", "agt_global_correction_manager", "agt_recovery_trigger_manager", "reference_map_publisher"}
    result["checks"]["process_diagnostics"] = process_diagnostics()
    try:
        nodes = set(subprocess.run(["ros2", "node", "list"], check=False, capture_output=True, text=True, timeout=5).stdout.split())
        active = sorted(conflicts.intersection(nodes))
        active.extend(name for name, entries in result["checks"]["process_diagnostics"].get("matches", {}).items() if entries and name not in active)
        result["checks"]["process_isolation"] = {"active_conflicts": active}
        if active:
            return result, failure("preflight", "PROCESS_CONFLICT", "conflicting processes are already running; refusing to kill them", {"nodes": active, "process_diagnostics": result["checks"]["process_diagnostics"]})
    except (OSError, subprocess.SubprocessError) as error:
        result["checks"]["process_isolation"] = {"status": "unavailable", "error": str(error)}
    bag = Path(args.bag)
    metadata = bag / "metadata.yaml"
    if not metadata.exists():
        return result, failure("preflight", FAILURE_CODES["bag"], "metadata.yaml is missing", {"bag": str(bag)})
    bag_info = yaml.safe_load(metadata.read_text(encoding="utf-8")) or {}
    topics = {entry.get("topic_metadata", {}).get("name") for entry in bag_info.get("rosbag2_bagfile_information", {}).get("topics_with_message_count", [])}
    required = {"/agt/sensors/lidar/custom", "/agt/sensors/imu/data"}
    result["checks"]["bag_topics"] = {topic: topic in topics for topic in required}
    if not required.issubset(topics):
        return result, failure("preflight", FAILURE_CODES["bag"], "required input topic is missing", {"missing": sorted(required - topics)})
    pcd, record, candidates = map(Path, (args.global_map_pcd, args.processing_record, args.candidates))
    if not pcd.is_file() or not record.is_file() or not candidates.is_file():
        return result, failure("preflight", FAILURE_CODES["map"], "reference asset path is missing", {
            "global_map_pcd": str(pcd), "processing_record": str(record), "candidates": str(candidates)
        })
    record_data = yaml.safe_load(record.read_text(encoding="utf-8")) or {}
    actual_hash = sha256(pcd)
    map_ok = record_data.get("state") == "ready" and record_data.get("map_id") == args.map_id
    hash_ok = record_data.get("pcd_sha256") == actual_hash == args.map_hash
    candidate_data = yaml.safe_load(candidates.read_text(encoding="utf-8")) or {}
    candidate_ok = candidate_data.get("map_id") == args.map_id and candidate_data.get("map_hash") == args.map_hash
    result["checks"]["map_identity"] = {"state_ready": record_data.get("state") == "ready", "map_id": record_data.get("map_id"), "sha256": actual_hash}
    result["checks"]["candidate_identity"] = candidate_ok
    if not map_ok:
        return result, failure("preflight", FAILURE_CODES["map"], "processing record is not READY or map_id mismatches", result["checks"]["map_identity"])
    if not hash_ok:
        return result, failure("preflight", FAILURE_CODES["map_hash"], "PCD/record/CLI hash mismatch", {"actual": actual_hash, "record": record_data.get("pcd_sha256"), "cli": args.map_hash})
    if not candidate_ok:
        return result, failure("preflight", FAILURE_CODES["candidate"], "candidate map identity mismatches", {"map_id": candidate_data.get("map_id"), "map_hash": candidate_data.get("map_hash")})
    result["checks"]["map_identity"] = "PASS"
    result["checks"]["candidate_identity"] = "PASS"
    return result, None


def observe_runtime(directory, timeout, playback_rate, validation_mode, action_cancel_timeout_s, fresh_action_max_age_s, stop_event=None, stage_update=None, playback_process=None):
    """Run the gates in bag order while keeping the Action client alive."""
    import rclpy
    from agt_interfaces.action import Relocalize
    from agt_interfaces.msg import LocalizationStatus
    from rclpy.action import ActionClient
    from rclpy.node import Node
    from rclpy.parameter import Parameter
    from rclpy.qos import QoSProfile, ReliabilityPolicy, DurabilityPolicy
    from rosgraph_msgs.msg import Clock
    from sensor_msgs.msg import PointCloud2
    from nav_msgs.msg import Odometry
    from tf2_msgs.msg import TFMessage
    from tf2_ros import Buffer, TransformListener

    class Observer(Node):
        def __init__(self):
            super().__init__("v25_10_realbag_validation_observer")
            self.set_parameters([Parameter("use_sim_time", Parameter.Type.BOOL, True)])
            self.counts = {"registered_points": 0, "odometry": 0}
            self.first = {}
            self.last = {}
            self.latest = {}
            self.feedback = []
            self.feedback_path = Path(directory) / "action_feedback.jsonl"
            self.feedback_path.touch()
            self.first_feedback_seen = False
            self.events = {"evidence": [], "correction": []}
            self.barrier = FreshCloudBarrier(fresh_action_max_age_s)
            self.goal_handle = None
            self.goal_send_ros_time = None
            self.goal_send_wall_time = None
            self.goal_send_monotonic = None
            self.fresh_cloud_stamp = None
            self.last_action_stage = None
            self.time_diagnostics = TimeDiagnostics(directory / "time_diagnostics.jsonl")
            clock_qos = QoSProfile(depth=10)
            clock_qos.reliability = ReliabilityPolicy.BEST_EFFORT
            clock_qos.durability = DurabilityPolicy.VOLATILE
            self.create_subscription(Clock, "/clock", self.clock_seen, clock_qos)
            self.create_subscription(TFMessage, "/tf", self.tf_seen, 50)
            self.create_subscription(PointCloud2, "/agt/odometry/registered_points", lambda msg: self.seen("registered_points", msg), 10)
            self.create_subscription(Odometry, "/agt/odometry/odometry", lambda msg: self.seen("odometry", msg), 10)
            self.create_subscription(LocalizationStatus, "/agt/localization/evidence_status", lambda msg: self.status("evidence", msg), 10)
            self.create_subscription(LocalizationStatus, "/agt/localization/status", lambda msg: self.status("correction", msg), 10)
            self.action = ActionClient(self, Relocalize, "/agt/localization/relocalize")
            self.tf = Buffer()
            self.listener = TransformListener(self.tf, self)

        def seen(self, name, message):
            now = time.monotonic()
            self.counts[name] += 1
            self.first.setdefault(name, now)
            self.last[name] = now
            if name == "registered_points":
                stamp = float(message.header.stamp.sec) + message.header.stamp.nanosec * 1e-9
                self.barrier.observe(stamp)
                self.time_diagnostics.sensor_message("registered_cloud", int(stamp * 1e9))
            elif name == "odometry":
                stamp = float(message.header.stamp.sec) + message.header.stamp.nanosec * 1e-9
                self.time_diagnostics.sensor_message("odometry", int(stamp * 1e9))

        def clock_seen(self, message):
            stamp_ns = int(message.clock.sec) * 1000000000 + int(message.clock.nanosec)
            rollback = self.time_diagnostics.clock_message(stamp_ns)
            if rollback:
                self.clock_failure = failure("ROS_TIME", "ROS_TIME_ROLLBACK", "ROS /clock moved backwards", rollback)

        def tf_seen(self, message):
            for transform in message.transforms:
                stamp = transform.header.stamp
                self.time_diagnostics.tf_message(int(stamp.sec) * 1000000000 + int(stamp.nanosec))

        def status(self, name, message):
            data = {"state": int(message.state), "accepted": bool(message.localization_accepted), "pose_valid": bool(message.pose_valid), "correction_generation": int(message.correction_generation), "fitness": float(message.fitness_score), "error_code": int(message.error_code), "message": message.message}
            self.latest[name] = data
            self.events[name].append(data)

    def rate(node, name):
        duration = node.last.get(name, 0.0) - node.first.get(name, 0.0)
        return node.counts[name] / duration if duration > 0 else 0.0

    rclpy.init()
    node = Observer()
    node.clock_failure = None
    action_result = None
    try:
        def stage(name, status, **details):
            node.last_action_stage = name
            if stage_update:
                stage_update(name, status, **details)

        def spin(timeout_sec):
            if stop_event is not None and stop_event.is_set():
                raise ValidationInterrupted("signal")
            rclpy.spin_once(node, timeout_sec=timeout_sec)
            if node.clock_failure:
                raise ValidationEnvironmentInvalid(node.clock_failure)

        gate_deadline = time.monotonic() + timeout
        if not node.action.wait_for_server(timeout_sec=min(10.0, timeout)):
            return failure("relocalization", "RELOCALIZE_ACTION_UNAVAILABLE", "Relocalize action server unavailable", {})
        node.action_server_ready = True
        while time.monotonic() < gate_deadline and any(node.counts[name] < 20 for name in node.counts):
            spin(0.1)
        rates = {name: rate(node, name) for name in node.counts}
        rate_info = {"counts": node.counts, "rates_hz": rates, "playback": playback_gate(playback_rate)}
        (directory / "topic_rates.json").write_text(json.dumps(rate_info, indent=2), encoding="utf-8")
        if node.counts["registered_points"] < 20 or (playback_rate == 1.0 and rates["registered_points"] <= 5.0):
            return failure("mapping", "REGISTERED_POINTS_TIMEOUT", "registered cloud gate failed", rates)
        if node.counts["odometry"] < 20 or (playback_rate == 1.0 and rates["odometry"] <= 5.0):
            return failure("mapping", "LIKELY_ADAPTER_FRAME_GATE", "registered cloud passed but odometry gate failed", {"rates_hz": rates, "base_frame": "imu_link", "backend_body_frame": "imu_link"})
        stage("MAPPING_GATE", "PASS", rates=rates)
        node.barrier.mapping_gate_last_cloud_stamp = node.barrier.latest_stamp
        try:
            node.tf.lookup_transform("imu_link", "lidar_link", rclpy.time.Time())
        except Exception as error:
            return failure("tf", "IMU_LIDAR_TF_MISSING", str(error), {"target_frame": "imu_link", "source_frame": "lidar_link"})
        stage("IMU_LIDAR_TF_GATE", "PASS", target_frame="imu_link", source_frame="lidar_link")
        try:
            node.tf.lookup_transform("odom", "imu_link", rclpy.time.Time())
        except Exception as error:
            return failure("tf", "ODOM_BASE_TF_MISSING", str(error), {})
        try:
            node.tf.lookup_transform("map", "odom", rclpy.time.Time())
            return failure("tf", "UNEXPECTED_MAP_ODOM_AUTHORITY", "map->odom exists before correction", {})
        except Exception:
            pass
        stage("TF_GATE", "PASS")
        if validation_mode == "auto_recovery":
            recovery_deadline = min(gate_deadline, time.monotonic() + timeout)
            while time.monotonic() < recovery_deadline and not node.latest.get("correction", {}).get("accepted", False):
                spin(0.1)
            if not node.latest.get("correction", {}).get("accepted", False):
                return failure("recovery", "AUTO_RECOVERY_NOT_ACCEPTED", "Recovery trigger did not produce accepted correction", node.latest)
            stage("CORRECTION", "PASS", mode="auto_recovery")
            return None
        if playback_process is None or playback_process.poll() is not None:
            return failure("playback", "PLAYBACK_EXITED", "source bag playback ended before Action dispatch", {})
        fresh_deadline = min(gate_deadline, time.monotonic() + timeout)
        while time.monotonic() < fresh_deadline:
            now_s = node.get_clock().now().nanoseconds * 1e-9
            if node.barrier.accept(now_s):
                node.fresh_cloud_stamp = node.barrier.latest_stamp
                break
            node.barrier.event.clear()
            spin(0.05)
        if node.fresh_cloud_stamp is None:
            node.time_diagnostics.append("freshness_failure", mapping_gate_last_cloud_stamp=node.barrier.mapping_gate_last_cloud_stamp,
                                         latest_cloud_stamp=node.barrier.latest_stamp, fresh_action_max_age_s=node.barrier.max_age_s)
            return failure("relocalization", "FRESH_CLOUD_TIMEOUT", "no new registered cloud met the fresh action barrier", {
                "mapping_gate_last_cloud_stamp": node.barrier.mapping_gate_last_cloud_stamp,
                "latest_stamp": node.barrier.latest_stamp,
                "fresh_action_max_age_s": node.barrier.max_age_s})
        stage("FRESH_CLOUD", "PASS", fresh_cloud_stamp=node.fresh_cloud_stamp)
        fresh_cloud_time = rclpy.time.Time(nanoseconds=int(node.fresh_cloud_stamp * 1e9))
        try:
            node.tf.lookup_transform("odom", "lidar_link", fresh_cloud_time)
        except Exception as error:
            return failure("PRE_ACTION_TF", "ODOM_LIDAR_FRESH_STAMP_TF_MISSING", str(error), {
                "target_frame": "odom", "source_frame": "lidar_link",
                "fresh_cloud_stamp": node.fresh_cloud_stamp,
                "goal_not_dispatched": True})
        node.tf_gate_complete_wall_time = time.time()
        stage("PRE_ACTION_TF_GATE", "PASS", target_frame="odom", source_frame="lidar_link",
              fresh_cloud_stamp=node.fresh_cloud_stamp,
              tf_gate_complete_wall_time=node.tf_gate_complete_wall_time)
        goal = Relocalize.Goal()
        goal.mode = Relocalize.Goal.MODE_LOCAL_CANDIDATES
        goal.use_initial_pose = False
        goal.use_last_valid_pose = False
        goal.use_configured_candidates = True
        goal.use_external_coarse_pose = False
        goal.max_candidates = 64
        goal.publish_debug = True
        goal.timeout_s = 15.0
        node.goal_send_ros_time = node.get_clock().now().nanoseconds * 1e-9
        node.goal_send_wall_time = time.time()
        node.goal_send_monotonic = time.monotonic()
        node.cloud_age_at_goal_send_s = node.goal_send_ros_time - node.fresh_cloud_stamp
        if node.cloud_age_at_goal_send_s > fresh_action_max_age_s:
            return failure("ACTION_INPUT_FRESHNESS", "STALE_CLOUD_AT_ACTION",
                           "fresh cloud exceeded the action dispatch age limit", {
                               "fresh_cloud_stamp": node.fresh_cloud_stamp,
                               "goal_not_dispatched": True,
                               "cloud_age_at_goal_send_s": node.cloud_age_at_goal_send_s,
                               "fresh_action_max_age_s": fresh_action_max_age_s})
        def on_feedback(feedback_message):
            item = {"wall_time": time.time(), "ros_time": node.get_clock().now().nanoseconds * 1e-9,
                    "state": int(feedback_message.feedback.state),
                    "tested_candidates": int(feedback_message.feedback.tested_candidates),
                    "best_fitness_score": float(feedback_message.feedback.best_fitness_score),
                    "elapsed_s": float(feedback_message.feedback.elapsed_s)}
            node.feedback.append(item)
            with open(node.feedback_path, "a", encoding="utf-8") as stream:
                stream.write(json.dumps(item, sort_keys=True) + "\n")
                stream.flush()
                os.fsync(stream.fileno())
            if not node.first_feedback_seen:
                node.first_feedback_seen = True
                stage("FIRST_FEEDBACK", "PASS", elapsed_s=item["elapsed_s"],
                      tested_candidates=item["tested_candidates"])

        try:
            send = node.action.send_goal_async(goal, feedback_callback=on_feedback)
        except Exception as error:
            stage("ACTION_DISPATCHED", "FAIL", code="ACTION_DISPATCH_FAILED")
            return failure("relocalization", "ACTION_DISPATCH_FAILED", str(error), {
                "fresh_cloud_stamp": node.fresh_cloud_stamp, "goal_not_dispatched": True})
        stage("ACTION_DISPATCHED", "PASS", cloud_stamp=node.fresh_cloud_stamp,
              fresh_cloud_stamp=node.fresh_cloud_stamp,
              tf_gate_complete_wall_time=node.tf_gate_complete_wall_time,
              goal_send_wall_time=node.goal_send_wall_time,
              goal_send_ros_time=node.goal_send_ros_time,
              cloud_age_at_goal_send_s=node.cloud_age_at_goal_send_s)
        node.time_diagnostics.append("freshness_pass", fresh_cloud_stamp=node.fresh_cloud_stamp,
                                     goal_send_ros_time=node.goal_send_ros_time,
                                     cloud_age_at_goal_send_s=node.cloud_age_at_goal_send_s)
        goal_response_deadline = time.monotonic() + 5.0
        while not send.done() and time.monotonic() < goal_response_deadline:
            spin(0.1)
        if not send.done():
            return failure("relocalization", "ACTION_GOAL_RESPONSE_TIMEOUT",
                           "Relocalize goal response timed out", {
                               "last_action_stage": node.last_action_stage,
                               "feedback_count": len(node.feedback),
                               "fresh_cloud_stamp": node.fresh_cloud_stamp,
                               "goal_send_ros_time": node.goal_send_ros_time,
                               "elapsed_wall_s": time.monotonic() - (node.goal_send_monotonic or time.monotonic())})
        handle = send.result()
        if handle is None or not handle.accepted:
            stage("ACTION_GOAL_ACCEPTED", "FAIL")
            return failure("relocalization", "RELOCALIZE_REJECTED", "Relocalize goal was rejected", {})
        node.goal_handle = handle
        stage("ACTION_GOAL_ACCEPTED", "PASS")
        result_future = handle.get_result_async()
        action_result_deadline = time.monotonic() + goal.timeout_s + 5.0
        while not result_future.done() and time.monotonic() < action_result_deadline:
            spin(0.1)
        if not result_future.done():
            return failure("relocalization", "ACTION_RESULT_TIMEOUT", "Relocalize result timed out", {
                "last_action_stage": node.last_action_stage,
                "feedback_count": len(node.feedback),
                "last_feedback": node.feedback[-1] if node.feedback else None,
                "fresh_cloud_stamp": node.fresh_cloud_stamp,
                "goal_send_ros_time": node.goal_send_ros_time,
                "elapsed_wall_s": time.monotonic() - (node.goal_send_monotonic or time.monotonic())})
        action_result = result_future.result().result
        stage("ACTION_RESULT", "PASS" if action_result.success else "FAIL",
              success=bool(action_result.success), error_code=int(action_result.error_code))
        classification = classify_action_result(action_result.error_code, action_result.success)
        action_payload = {"success": action_result.success, "error_code": int(action_result.error_code), "failure_reason": action_result.failure_reason, **classification,
                          "fresh_cloud_stamp": node.fresh_cloud_stamp, "goal_send_ros_time": node.goal_send_ros_time,
                          "goal_send_wall_time": node.goal_send_wall_time, "cloud_age_at_goal_send_s": node.cloud_age_at_goal_send_s}
        (directory / "action_result.json").write_text(json.dumps(action_payload, indent=2), encoding="utf-8")
        if not action_result.success:
            return failure(classification["stage"].lower(), classification["code"], action_result.failure_reason, action_payload)
        stage("RELOCALIZE_ACTION", "PASS", registration_executed=True)
        evidence_deadline = time.monotonic() + min(20.0, max(1.0, timeout))
        while time.monotonic() < evidence_deadline and not node.latest.get("evidence", {}).get("accepted", False):
            spin(0.1)
        if not node.latest.get("evidence", {}).get("accepted", False):
            return failure("evidence", "EVIDENCE_NOT_ACCEPTED", "relocalization evidence was not accepted", node.latest)
        stage("EVIDENCE", "PASS")
        wait_deadline = time.monotonic() + min(20.0, max(1.0, timeout))
        while time.monotonic() < wait_deadline and not node.latest.get("correction", {}).get("accepted", False):
            spin(0.1)
        try:
            node.tf.lookup_transform("map", "odom", rclpy.time.Time())
        except Exception as error:
            return failure("correction", "MAP_ODOM_TF_MISSING", str(error), node.latest)
        canonical = node.latest.get("correction", {})
        if (not canonical.get("accepted") or canonical.get("state") != LocalizationStatus.STATE_TRACKING
                or canonical.get("correction_generation", 0) < 1 or not canonical.get("pose_valid")):
            return failure("correction", "CANONICAL_STATUS_INVALID", "canonical status is not TRACKING", canonical)
        stage("CORRECTION", "PASS", correction_generation=canonical.get("correction_generation"), state=canonical.get("state"))
        (directory / "localization_events.jsonl").write_text("\n".join(json.dumps(item) for item in node.events["evidence"]) + "\n", encoding="utf-8")
        (directory / "correction_events.jsonl").write_text("\n".join(json.dumps(item) for item in node.events["correction"]) + "\n", encoding="utf-8")
        return None
    finally:
        if node.goal_handle is not None and not action_result:
            cancel = node.goal_handle.cancel_goal_async()
            deadline = time.monotonic() + action_cancel_timeout_s
            while not cancel.done() and time.monotonic() < deadline:
                rclpy.spin_once(node, timeout_sec=0.05)
            if not cancel.done():
                node.cancel_timeout = True
            else:
                terminal = node.goal_handle.get_result_async()
                while not terminal.done() and time.monotonic() < deadline:
                    rclpy.spin_once(node, timeout_sec=0.05)
                if not terminal.done():
                    node.cancel_timeout = True
            (directory / "shutdown.json").write_text(json.dumps({
                "action_cancel_requested": True,
                "action_cancel_timeout": bool(getattr(node, "cancel_timeout", False)),
                "code": "ACTION_CANCEL_TIMEOUT" if getattr(node, "cancel_timeout", False) else "PASS"
            }, indent=2), encoding="utf-8")
        node.destroy_node()
        rclpy.try_shutdown()


def write_report(directory, preflight_result, error=None, summary=None):
    for name in ("bag_info.json", "process_manifest.json", "mapping.log", "localization.log", "playback.log", "action_feedback.jsonl", "action_result.json", "topic_rates.json", "tf_report.json", "localization_events.jsonl", "correction_events.jsonl", "shutdown.json", "time_diagnostics.jsonl"):
        path = directory / name
        if not path.exists():
            atomic_write(path, "{}\n" if path.suffix == ".json" else "")
    atomic_write(directory / "preflight.json", json.dumps(preflight_result, indent=2) + "\n")
    payload = summary or {}
    action_path = directory / "action_result.json"
    if action_path.exists():
        try:
            payload["action"] = json.loads(action_path.read_text(encoding="utf-8"))
        except json.JSONDecodeError:
            pass
    if error:
        payload["failure"] = error
    timeout_evidence = error.get("evidence", {}) if error else {}
    timeout_report = ""
    if error and error.get("code") in ("ACTION_GOAL_RESPONSE_TIMEOUT", "ACTION_RESULT_TIMEOUT"):
        timeout_report = (
            "\n## Action timeout diagnostics\n\n"
            "- `last_action_stage`: `%s`\n"
            "- `feedback_count`: `%s`\n"
            "- `last_feedback`: `%s`\n"
            "- `fresh_cloud_stamp`: `%s`\n"
            "- `goal_send_ros_time`: `%s`\n"
            "- `elapsed_wall_s`: `%s`\n"
            % (timeout_evidence.get("last_action_stage"), timeout_evidence.get("feedback_count"),
               json.dumps(timeout_evidence.get("last_feedback"), sort_keys=True),
               timeout_evidence.get("fresh_cloud_stamp"), timeout_evidence.get("goal_send_ros_time"),
               timeout_evidence.get("elapsed_wall_s"))
        )
    debug_rate = payload.get("playback", {}).get("classification") == "DEBUG_PLAYBACK_RATE"
    result_label = "DEBUG RUN COMPLETED" if debug_rate and not error else ("PASS" if not error else "FAIL")
    atomic_write(directory / "result.md",
        "# V25-10 Real-Bag Validation\n\n"
        "This is REAL-DATA PIPELINE validation, not positioning-accuracy validation.\n\n"
        "## Result\n\n" + result_label + "\n\n" +
        ("Failure: `%s` — %s\n" % (error["code"], error["message"]) if error else "All recorded gates passed.\n") +
        timeout_report +
        "\n## Validation evidence\n\n" +
        "```json\n" + json.dumps(payload, indent=2, sort_keys=True) + "\n```\n",
        )


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--bag", required=True)
    parser.add_argument("--global-map-pcd", required=True)
    parser.add_argument("--processing-record", required=True)
    parser.add_argument("--candidates", required=True)
    parser.add_argument("--map-id", required=True)
    parser.add_argument("--map-hash", required=True)
    parser.add_argument("--playback-rate", type=float, default=1.0)
    parser.add_argument("--validation-mode", choices=("manual_action", "auto_recovery"), default="manual_action")
    parser.add_argument("--fresh-action-max-age-s", type=float, default=FRESH_CLOUD_MAX_AGE_S)
    parser.add_argument("--action-cancel-timeout-s", type=float, default=3.0)
    parser.add_argument("--backend", default="ndt")
    parser.add_argument("--output-dir", default="runtime/validation/v25_10")
    parser.add_argument("--start-rviz", action="store_true")
    parser.add_argument("--no-rviz", action="store_true")
    parser.add_argument("--timeout", type=float, default=180.0)
    parser.add_argument("--preflight-only", action="store_true")
    args = parser.parse_args(argv)
    ros_log_dir = Path("/tmp/agt_v25_10_ros_logs")
    ros_log_dir.mkdir(parents=True, exist_ok=True)
    os.environ["ROS_LOG_DIR"] = str(ros_log_dir)
    run_id = time.strftime("%Y%m%d_%H%M%S")
    directory = Path(args.output_dir) / run_id
    directory.mkdir(parents=True, exist_ok=False)
    report = DurableRunReport(directory, run_id)
    atomic_write(directory / "process_manifest.json", json.dumps({"run_id": run_id, "processes": []}, indent=2) + "\n")
    (directory / "time_diagnostics.jsonl").touch()
    stop_event = threading.Event()

    def handle_signal(signum, _frame):
        stop_event.set()
        report.interrupted(signal.Signals(signum).name)

    signal.signal(signal.SIGINT, handle_signal)
    signal.signal(signal.SIGTERM, handle_signal)
    result, error = preflight(args)
    report.stage("PREFLIGHT", "FAIL" if error else "PASS", error=error)
    if error or args.preflight_only:
        write_report(directory, result, error)
        if error:
            report.fail(error)
        else:
            report.data["status"] = "PASS"
            report.update()
        print(json.dumps(error or {"stage": "preflight", "code": "PASS"}, indent=2))
        return 1 if error else 0
    try:
        clock_before = query_clock_publishers()
    except Exception as clock_probe_error:
        clock_before = []
        error = failure("CLOCK_PREFLIGHT", "CLOCK_NOT_AVAILABLE", "unable to inspect /clock publishers", {"exception": repr(clock_probe_error)})
        report.fail(error)
        write_report(directory, result, error)
        return 1
    result["checks"]["clock_preflight"] = {"publisher_count": len(clock_before), "publishers": clock_before}
    clock_error = clock_gate_code(len(clock_before), before_playback=True)
    report.stage("CLOCK_PREFLIGHT", "FAIL" if clock_error else "PASS", publisher_count=len(clock_before), publishers=clock_before)
    if clock_error:
        error = failure("CLOCK_PREFLIGHT", clock_error, "an external /clock publisher exists before playback", result["checks"]["clock_preflight"])
        report.fail(error)
        write_report(directory, result, error, {"clock_preflight": result["checks"]["clock_preflight"]})
        return 1
    # The complete runtime orchestration is deliberately subprocess-isolated;
    # action invocation and observations are implemented by the ROS observer in
    # a sourced runtime environment. No shell action CLI is used.
    command = ["ros2", "launch", "agt_localization", "v25_10_realbag_validation.launch.py",
               f"global_map_pcd:={Path(args.global_map_pcd).resolve()}",
               f"processing_record:={Path(args.processing_record).resolve()}",
               f"candidates:={Path(args.candidates).resolve()}", f"map_id:={args.map_id}", f"map_hash:={args.map_hash}", f"backend:={args.backend}",
               f"enable_recovery_trigger:={'true' if args.validation_mode == 'auto_recovery' else 'false'}"]
    log = open(directory / "localization.log", "w", encoding="utf-8")
    runtime_env = os.environ.copy()
    process = subprocess.Popen(command, stdout=log, stderr=subprocess.STDOUT, start_new_session=True, env=runtime_env)
    atomic_write(directory / "process_manifest.json", json.dumps({"run_id": run_id, "processes": [{"name": "launch_stack", "pid": process.pid}]}, indent=2) + "\n")
    report.stage("STACK_STARTED", "PASS", pid=process.pid)
    recorder = None
    playback = None
    rviz = None
    playback_guard = SinglePlaybackGuard()
    try:
        # All observers and visualization/recording processes are ready before
        # playback. This prevents startup work from aging the first usable scan.
        if not wait_for_action_server(min(30.0, args.timeout)):
            error = failure("relocalization", "RELOCALIZE_ACTION_UNAVAILABLE", "Relocalize action server unavailable before playback", {})
            report.fail(error)
            write_report(directory, result, error, {"validation_mode": args.validation_mode, "playback": playback_gate(args.playback_rate)})
            return 1
        report.stage("ACTION_SERVER_READY", "PASS")
        recorder = subprocess.Popen(["ros2", "bag", "record", "-o", str(directory / "result_bag"), "/clock", "/agt/odometry/odometry", "/agt/odometry/registered_points", "/agt/localization/evidence_status", "/agt/localization/status", "/agt/localization/candidate_pose", "/agt/localization/global_pose", "/agt/localization/aligned_points", "/agt/localization/initial_guess", "/agt/localization/aligned_candidate", "/agt/localization/global_correction_status", "/tf", "/tf_static"], stdout=open(directory / "record.log", "w"), stderr=subprocess.STDOUT)
        report.stage("RECORDER_STARTED", "PASS", pid=recorder.pid)
        if args.start_rviz and not args.no_rviz:
            from ament_index_python.packages import get_package_share_directory
            rviz_config = Path(get_package_share_directory("agt_localization")) / "rviz" / "v25_10_realbag_validation.rviz"
            rviz = subprocess.Popen(["rviz2", "-d", str(rviz_config)], stdout=open(directory / "rviz.log", "w"), stderr=subprocess.STDOUT, env=runtime_env)
            report.stage("RVIZ_STARTED", "PASS", pid=rviz.pid)
        playback_guard.start()
        playback = subprocess.Popen(["ros2", "bag", "play", str(Path(args.bag).resolve()), "--clock", "--rate", str(args.playback_rate)], stdout=open(directory / "playback.log", "w"), stderr=subprocess.STDOUT)
        report.stage("PLAYBACK_STARTED", "PASS", pid=playback.pid, rate=args.playback_rate)
        atomic_write(directory / "process_manifest.json", json.dumps({"run_id": run_id, "processes": [
            {"name": "launch_stack", "pid": process.pid}, {"name": "recorder", "pid": recorder.pid},
            {"name": "playback", "pid": playback.pid},
        ]}, indent=2) + "\n")
        try:
            clock_during = query_clock_publishers(timeout_s=5.0)
        except Exception as clock_probe_error:
            clock_during = []
            clock_probe_error = repr(clock_probe_error)
        else:
            clock_probe_error = None
        result["checks"]["clock_during_playback"] = {"publisher_count": len(clock_during), "publishers": clock_during}
        clock_error = "CLOCK_NOT_AVAILABLE" if clock_probe_error else clock_gate_code(len(clock_during), before_playback=False)
        report.stage("CLOCK_DURING_PLAYBACK", "FAIL" if clock_error else "PASS", publisher_count=len(clock_during), publishers=clock_during)
        if clock_error:
            evidence = result["checks"]["clock_during_playback"]
            if clock_probe_error:
                evidence["exception"] = clock_probe_error
            error = failure("ROS_TIME", clock_error, "playback did not provide exactly one /clock publisher", evidence)
            report.fail(error)
            write_report(directory, result, error, {"validation_mode": args.validation_mode, "playback": playback_gate(args.playback_rate)})
            return 1
        try:
            error = observe_runtime(directory, args.timeout, args.playback_rate, args.validation_mode, args.action_cancel_timeout_s, args.fresh_action_max_age_s, stop_event, report.stage, playback)
            summary = {"validation_mode": args.validation_mode, "playback": playback_gate(args.playback_rate),
                       "fresh_action_max_age_s": args.fresh_action_max_age_s,
                       "clock_preflight": result["checks"].get("clock_preflight"),
                       "clock_during_playback": result["checks"].get("clock_during_playback")}
            if args.playback_rate != 1.0 and error is None:
                summary["status"] = "DEBUG_PLAYBACK_RATE"
        except ValidationInterrupted:
            error = failure("shutdown", "INTERRUPTED", "validation interrupted by signal", {})
            report.interrupted("SIGINT/SIGTERM")
            summary = {"validation_mode": args.validation_mode, "playback": playback_gate(args.playback_rate)}
        except ValidationEnvironmentInvalid as environment_error:
            error = environment_error.error
            report.fail(error)
            summary = {"validation_mode": args.validation_mode, "playback": playback_gate(args.playback_rate)}
        except Exception as observer_error:
            error = failure("observer", "PROCESS_EXITED", "validation observer failed", {"exception": repr(observer_error)})
            summary = {"validation_mode": args.validation_mode, "playback": playback_gate(args.playback_rate)}
        if error is None:
            result["checks"]["runtime"] = "PASS"
        else:
            result["checks"]["runtime"] = "FAIL"
        if error:
            report.data["summary"] = summary
            if error.get("code") == "INTERRUPTED":
                report.data["failure"] = error
                report.update()
            else:
                report.fail(error)
        else:
            report.data["summary"] = summary
            report.data["status"] = "PASS" if args.playback_rate == 1.0 else "DEBUG RUN COMPLETED"
            report.update()
        write_report(directory, result, error, summary)
        return 1 if error else 0
    finally:
        for child in (locals().get("rviz"), locals().get("recorder"), locals().get("playback")):
            if child and child.poll() is None:
                child.send_signal(signal.SIGINT)
        if process.poll() is None:
            os.killpg(process.pid, signal.SIGINT)
        log.close()
        if not (directory / "result.md").exists():
            write_report(directory, result, failure("runtime", "PROCESS_EXITED", "validation process ended before writing its report", {"launch_returncode": process.poll()}))


if __name__ == "__main__":
    sys.exit(main())
