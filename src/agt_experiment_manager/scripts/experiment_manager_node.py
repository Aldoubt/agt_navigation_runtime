#!/usr/bin/env python3

"""ROS facade for experiment lifecycle and configured rosbag operations."""

from __future__ import annotations

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from agt_interfaces.msg import BagSessionSummary, LocalizationStatus
from agt_interfaces.srv import ListBagSessions, ManageBagSession
import rclpy
from rclpy.callback_groups import MutuallyExclusiveCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy

from agt_experiment_manager.facade import (
    ExperimentBusinessFacade, STATE_VALUES, load_bag_profiles,
)
from agt_experiment_manager.manager import ExperimentError, ExperimentManager


class ExperimentManagerNode(Node):
    def __init__(self) -> None:
        super().__init__("agt_experiment_manager")
        runtime_dir = Path(
            str(self.declare_parameter("runtime_dir", "runtime").value)
        ).expanduser()
        experiments_value = str(
            self.declare_parameter("experiments_root", "").value
        ).strip()
        rosbag_value = str(self.declare_parameter("rosbag_root", "").value).strip()
        repository_value = str(
            self.declare_parameter("repository_root", "").value
        ).strip()
        profiles_default = str(
            Path(get_package_share_directory("agt_experiment_manager"))
            / "config"
            / "bag_profiles.yaml"
        )
        profiles_path = str(
            self.declare_parameter("bag_profiles_file", profiles_default).value
        )
        period = float(self.declare_parameter("publish_period_s", 1.0).value)
        if period <= 0.0:
            raise ValueError("publish_period_s must be positive")
        experiments_root = (
            Path(experiments_value).expanduser()
            if experiments_value
            else runtime_dir / "experiments"
        )
        rosbag_root = (
            Path(rosbag_value).expanduser()
            if rosbag_value
            else runtime_dir / "rosbag"
        )
        repository_root = (
            Path(repository_value).expanduser() if repository_value else None
        )
        self._manager = ExperimentManager(
            experiments_root,
            repository_root=repository_root,
            rosbag_root=rosbag_root,
        )
        recovered = self._manager.recover_interrupted()
        if recovered:
            self.get_logger().warning(
                "marked interrupted experiments after restart: " + ", ".join(recovered)
            )
        self._facade = ExperimentBusinessFacade(
            self._manager, load_bag_profiles(profiles_path)
        )
        group = MutuallyExclusiveCallbackGroup()
        latched = QoSProfile(depth=1)
        latched.reliability = ReliabilityPolicy.RELIABLE
        latched.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self._publisher = self.create_publisher(
            BagSessionSummary, "/agt/data/bags/status", latched
        )
        self.create_service(
            ListBagSessions,
            "/agt/data/bags/list",
            self._list_sessions,
            callback_group=group,
        )
        self.create_service(
            ManageBagSession,
            "/agt/data/bags/manage",
            self._manage_session,
            callback_group=group,
        )
        self.create_subscription(
            LocalizationStatus,
            "/agt/localization/status",
            self._localization_callback,
            10,
            callback_group=group,
        )
        self._timer = self.create_timer(
            period, self._publish_status, callback_group=group
        )
        self._publish_status()

    def _summary(self, value) -> BagSessionSummary:
        message = BagSessionSummary()
        message.header.stamp = self.get_clock().now().to_msg()
        message.state = int(
            STATE_VALUES.get(str(value.get("state", "UNKNOWN")).upper(), 0)
        )
        message.bag_id = str(value.get("bag_id", ""))
        message.experiment_id = str(value.get("experiment_id", ""))
        message.profile_id = str(value.get("profile_id", ""))
        message.relative_uri = str(value.get("relative_uri", ""))
        message.complete = bool(value.get("complete", False))
        message.simulation = bool(value.get("simulation", False))
        message.playback_rate = float(value.get("playback_rate", 0.0))
        message.storage_bytes = int(value.get("storage_bytes", 0))
        message.started_at = str(value.get("started_at", ""))
        message.updated_at = str(value.get("updated_at", ""))
        message.message = str(value.get("message", ""))
        return message

    def _publish_status(self) -> None:
        self._publisher.publish(self._summary(self._facade.status()))

    def _list_sessions(self, request, response):
        try:
            sessions = self._facade.list_sessions(
                state=int(request.state), experiment_id=str(request.experiment_id)
            )
            response.sessions = [self._summary(item) for item in sessions]
            response.success = True
            response.error_code = ListBagSessions.Response.ERROR_NONE
            response.message = f"listed {len(sessions)} bag sessions"
        except ValueError as exc:
            response.success = False
            response.error_code = ListBagSessions.Response.ERROR_INVALID_REQUEST
            response.message = str(exc)
        except Exception as exc:
            response.success = False
            response.error_code = ListBagSessions.Response.ERROR_INTERNAL
            response.message = str(exc)
        return response

    @staticmethod
    def _request_values(request) -> dict[str, object]:
        return {
            "bag_id": request.bag_id,
            "experiment_id": request.experiment_id,
            "experiment_title": request.experiment_title,
            "profile_id": request.profile_id,
            "playback_rate": request.playback_rate,
            "mission_id": request.mission_id,
            "mission_version": request.mission_version,
            "mission_sha256": request.mission_sha256,
            "map_id": request.map_id,
            "map_version_id": request.map_version_id,
            "map_sha256": request.map_sha256,
            "platform_profile": request.platform_profile,
            "calibration_profile": request.calibration_profile,
            "nav2_profile": request.nav2_profile,
        }

    def _manage_session(self, request, response):
        try:
            value = self._facade.manage(
                int(request.operation), self._request_values(request)
            )
            response.session = self._summary(value)
            response.success = True
            response.error_code = ManageBagSession.Response.ERROR_NONE
            response.message = str(value.get("message", "bag operation completed"))
            self._publish_status()
        except ExperimentError as exc:
            message = str(exc)
            response.success = False
            response.error_code = (
                ManageBagSession.Response.ERROR_PROFILE_INVALID
                if "profile" in message
                else ManageBagSession.Response.ERROR_CONFLICT
            )
            response.message = message
        except ValueError as exc:
            response.success = False
            response.error_code = ManageBagSession.Response.ERROR_INVALID_REQUEST
            response.message = str(exc)
        except Exception as exc:
            response.success = False
            response.error_code = ManageBagSession.Response.ERROR_INTERNAL
            response.message = str(exc)
        return response

    def _localization_callback(self, message: LocalizationStatus) -> None:
        active = self._facade.running_experiment()
        if active is None:
            return
        try:
            self._manager.record_localization_result(
                str(active["experiment_id"]),
                {
                    "state": int(message.state),
                    "pose_valid": bool(message.pose_valid),
                    "localization_accepted": bool(message.localization_accepted),
                    "has_converged": bool(message.has_converged),
                    "status_stale": bool(message.status_stale),
                    "error_code": int(message.error_code),
                    "map_id": message.map_id,
                    "map_hash": message.map_hash,
                    "fitness_score": message.fitness_score,
                    "runtime_ms": message.runtime_ms,
                    "candidate_source": message.candidate_source,
                    "candidate_id": message.candidate_id,
                },
            )
        except ExperimentError as exc:
            self.get_logger().warning(str(exc))

    def destroy_node(self):
        self._timer.cancel()
        self._manager.close()
        return super().destroy_node()


def main(args=None) -> None:
    rclpy.init(args=args)
    node = ExperimentManagerNode()
    executor = MultiThreadedExecutor(num_threads=3)
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        executor.shutdown()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
