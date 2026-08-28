#!/usr/bin/env python3
"""Run planner-only headland handoff smoke tests against Nav2."""

from __future__ import annotations

import argparse
import json
import math
import sys
import time
from pathlib import Path

import rclpy
import yaml
from action_msgs.msg import GoalStatus
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import ComputePathToPose
from rclpy.action import ActionClient
from rclpy.node import Node
from rclpy.utilities import remove_ros_args

from agt_navigation.headland_planner_smoke import (
    build_smoke_manifest,
    finalize_smoke_results,
    write_smoke_bundle,
)


def build_parser():
    parser = argparse.ArgumentParser(
        description=(
            "Run positive and negative-control ComputePathToPose requests from "
            "frozen headland planner artifacts without starting a motion stack."
        )
    )
    parser.add_argument("--planner-pairs", required=True)
    parser.add_argument("--gap-diagnostics", required=True)
    parser.add_argument("--map-yaml", required=True)
    parser.add_argument("--output", required=True)
    parser.add_argument("--planner-id", default="GridBased")
    parser.add_argument("--planner-action", default="/compute_path_to_pose")
    parser.add_argument("--server-timeout", type=float, default=30.0)
    parser.add_argument("--request-timeout", type=float, default=30.0)
    return parser


def _parse_cli_args(argv=None):
    raw_args = list(sys.argv) if argv is None else [sys.argv[0], *list(argv)]
    application_args = remove_ros_args(args=raw_args)
    return build_parser().parse_args(application_args[1:])


def _positive_timeout(value, name):
    value = float(value)
    if not math.isfinite(value) or value <= 0.0:
        raise ValueError(f"{name} must be a positive finite value")
    return value


def _load_payload(path):
    path = Path(path).expanduser().resolve()
    text = path.read_text(encoding="utf-8")
    if path.suffix.lower() in {".yaml", ".yml"}:
        payload = yaml.safe_load(text)
    else:
        payload = json.loads(text)
    if not isinstance(payload, dict):
        raise ValueError(f"artifact must contain an object: {path}")
    return path, payload


def _quaternion_from_yaw(yaw):
    half = 0.5 * float(yaw)
    return 0.0, 0.0, math.sin(half), math.cos(half)


def _pose_stamped(node, pose):
    message = PoseStamped()
    message.header.frame_id = "map"
    message.header.stamp = node.get_clock().now().to_msg()
    message.pose.position.x = float(pose["x"])
    message.pose.position.y = float(pose["y"])
    message.pose.position.z = 0.0
    qx, qy, qz, qw = _quaternion_from_yaw(pose["yaw"])
    message.pose.orientation.x = qx
    message.pose.orientation.y = qy
    message.pose.orientation.z = qz
    message.pose.orientation.w = qw
    return message


def _duration_ms(duration):
    if duration is None:
        return None
    seconds = float(getattr(duration, "sec", 0))
    nanoseconds = float(getattr(duration, "nanosec", 0))
    return 1000.0 * seconds + nanoseconds / 1_000_000.0


def _status_name(status):
    names = {
        GoalStatus.STATUS_UNKNOWN: "unknown",
        GoalStatus.STATUS_ACCEPTED: "accepted",
        GoalStatus.STATUS_EXECUTING: "executing",
        GoalStatus.STATUS_CANCELING: "canceling",
        GoalStatus.STATUS_SUCCEEDED: "succeeded",
        GoalStatus.STATUS_CANCELED: "canceled",
        GoalStatus.STATUS_ABORTED: "aborted",
    }
    return names.get(int(status), f"status_{int(status)}")


def _infrastructure_outcome(request, reason, wall_time_ms=None):
    return {
        "request_id": request["request_id"],
        "planner_success": False,
        "infrastructure_error": True,
        "path_xy": [],
        "planning_time_ms": None,
        "wall_time_ms": wall_time_ms,
        "error_code": None,
        "nav2_status": None,
        "failure_reason": str(reason),
    }


class HeadlandPlannerSmokeNode(Node):
    def __init__(self, planner_action):
        super().__init__("agt_headland_planner_smoke")
        self.client = ActionClient(self, ComputePathToPose, str(planner_action))

    def run_request(self, request, *, planner_id, timeout_s):
        started = time.perf_counter()
        goal = ComputePathToPose.Goal()
        goal.start = _pose_stamped(self, request["start"])
        goal.goal = _pose_stamped(self, request["goal"])
        goal.use_start = True
        goal.planner_id = str(planner_id)

        try:
            send_future = self.client.send_goal_async(goal)
        except Exception as exc:  # pragma: no cover - ROS transport boundary
            return _infrastructure_outcome(
                request,
                f"planner send error: {exc}",
                wall_time_ms=(time.perf_counter() - started) * 1000.0,
            )
        rclpy.spin_until_future_complete(self, send_future, timeout_sec=float(timeout_s))
        if not send_future.done():
            return _infrastructure_outcome(
                request,
                f"planner goal response timed out after {timeout_s:.1f}s",
                wall_time_ms=(time.perf_counter() - started) * 1000.0,
            )
        try:
            handle = send_future.result()
        except Exception as exc:  # pragma: no cover - ROS transport boundary
            return _infrastructure_outcome(
                request,
                f"planner goal response error: {exc}",
                wall_time_ms=(time.perf_counter() - started) * 1000.0,
            )
        if handle is None or not handle.accepted:
            return _infrastructure_outcome(
                request,
                "ComputePathToPose goal was rejected",
                wall_time_ms=(time.perf_counter() - started) * 1000.0,
            )

        result_future = handle.get_result_async()
        rclpy.spin_until_future_complete(self, result_future, timeout_sec=float(timeout_s))
        if not result_future.done():
            try:
                handle.cancel_goal_async()
            except Exception:
                pass
            return _infrastructure_outcome(
                request,
                f"planner result timed out after {timeout_s:.1f}s",
                wall_time_ms=(time.perf_counter() - started) * 1000.0,
            )
        try:
            wrapped = result_future.result()
        except Exception as exc:  # pragma: no cover - ROS transport boundary
            return _infrastructure_outcome(
                request,
                f"planner result error: {exc}",
                wall_time_ms=(time.perf_counter() - started) * 1000.0,
            )

        status = int(wrapped.status)
        result = wrapped.result
        path = getattr(result, "path", None)
        poses = list(getattr(path, "poses", []) or [])
        path_xy = [
            [float(item.pose.position.x), float(item.pose.position.y)] for item in poses
        ]
        error_code = int(getattr(result, "error_code", 0))
        planning_time_ms = _duration_ms(getattr(result, "planning_time", None))
        wall_time_ms = (time.perf_counter() - started) * 1000.0

        if status == GoalStatus.STATUS_SUCCEEDED and poses:
            success = True
            failure_reason = None
            infrastructure_error = False
        elif status == GoalStatus.STATUS_SUCCEEDED and not poses:
            success = False
            failure_reason = "planner succeeded but returned an empty path"
            infrastructure_error = True
        else:
            success = False
            failure_reason = f"planner {_status_name(status)} error_code={error_code}"
            infrastructure_error = False

        return {
            "request_id": request["request_id"],
            "planner_success": success,
            "infrastructure_error": infrastructure_error,
            "path_xy": path_xy,
            "planning_time_ms": planning_time_ms,
            "wall_time_ms": wall_time_ms,
            "error_code": error_code,
            "nav2_status": _status_name(status),
            "failure_reason": failure_reason,
        }


def _print_summary(result):
    summary = result["summary"]
    print("method:", result["method"])
    print("radius_m:", result["radius_m"])
    print("expected_requests:", summary["expected_request_count"])
    print("outcomes:", summary["outcome_count"])
    print("planner_success:", summary["planner_success"])
    print("planner_failure:", summary["planner_failure"])
    print("expectation_met:", summary["expectation_met"])
    print("expectation_mismatch:", summary["expectation_mismatch"])
    print("unexpected_success:", summary["unexpected_success"])
    print("unexpected_failure:", summary["unexpected_failure"])
    print("infrastructure_error:", summary["infrastructure_error"])
    if summary["expectation_mismatch"]:
        print("\nmismatches:")
        for item in result["results"]:
            if item["expectation_met"]:
                continue
            print(
                f"{item['request_id']}: {item['mismatch_type']} "
                f"success={item['planner_success']} reason={item['failure_reason']}"
            )


def main(argv=None):
    args = _parse_cli_args(argv)
    server_timeout = _positive_timeout(args.server_timeout, "server_timeout")
    request_timeout = _positive_timeout(args.request_timeout, "request_timeout")
    planner_pairs_path, planner_pairs = _load_payload(args.planner_pairs)
    gap_path, gap_diagnostics = _load_payload(args.gap_diagnostics)
    map_yaml = Path(args.map_yaml).expanduser().resolve()
    if not map_yaml.is_file():
        raise FileNotFoundError(map_yaml)
    output = Path(args.output).expanduser().resolve()
    manifest = build_smoke_manifest(planner_pairs, gap_diagnostics)

    rclpy.init(args=None)
    node = HeadlandPlannerSmokeNode(args.planner_action)
    outcomes = []
    try:
        if not node.client.wait_for_server(timeout_sec=server_timeout):
            reason = f"ComputePathToPose unavailable after {server_timeout:.1f}s"
            outcomes = [
                _infrastructure_outcome(request, reason)
                for request in manifest["requests"]
            ]
        else:
            for index, request in enumerate(manifest["requests"], start=1):
                node.get_logger().info(
                    f"[{index}/{len(manifest['requests'])}] {request['request_id']} "
                    f"expected_success={request['expected_success']}"
                )
                outcomes.append(
                    node.run_request(
                        request,
                        planner_id=args.planner_id,
                        timeout_s=request_timeout,
                    )
                )
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()

    result = finalize_smoke_results(manifest, outcomes)
    result["sources"] = {
        "planner_pairs": str(planner_pairs_path),
        "gap_diagnostics": str(gap_path),
        "map_yaml": str(map_yaml),
    }
    result["planner"] = {
        "planner_id": str(args.planner_id),
        "planner_action": str(args.planner_action),
        "allow_unknown": False,
        "motion_stack_started": False,
    }
    write_smoke_bundle(result, map_yaml, output)
    print("output:", output)
    _print_summary(result)
    return 0 if result["summary"]["all_expectations_met"] else 2


if __name__ == "__main__":
    sys.exit(main())