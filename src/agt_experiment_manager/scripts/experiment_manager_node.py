#!/usr/bin/env python3

"""ROS facade for experiment lifecycle and configured rosbag operations."""

from __future__ import annotations

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from agt_interfaces.msg import BagSessionSummary, ExperimentSummary, LocalizationStatus
from agt_interfaces.srv import ListBagSessions, ListExperiments, ManageBagSession
import rclpy
from rclpy.callback_groups import MutuallyExclusiveCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy

from agt_experiment_manager.facade import (
    EXPERIMENT_STATES, ExperimentBusinessFacade, STATE_VALUES, load_bag_profiles,
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
        self.create_service(
            ListExperiments,
            "/agt/data/experiments/list",
            self._list_experiments,
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
        message.process_id = int(value.get("process_id", 0))
        message.message_count = int(value.get("message_count", 0))
        message.storage_identifier = str(value.get("storage_identifier", ""))
        message.mapping_input_ready = bool(value.get("mapping_input_ready", False))
        message.contains_mapping_outputs = bool(
            value.get("contains_mapping_outputs", False)
        )
        message.contains_navigation_outputs = bool(
            value.get("contains_navigation_outputs", False)
        )
        return message

    def _experiment_summary(self, value) -> ExperimentSummary:
        message = ExperimentSummary()
        message.header.stamp = self.get_clock().now().to_msg()
        state_values = {
            name: state for state, name in EXPERIMENT_STATES.items() if name is not None
        }
        message.state = int(state_values.get(str(value.get("state", "")).upper(), 0))
        message.experiment_id = str(value.get("experiment_id", ""))
        message.title = str(value.get("title", ""))
        message.created_at = str(value.get("created_at", ""))
        message.start_time = str(value.get("start_time") or "")
        message.end_time = str(value.get("end_time") or "")
        message.platform_profile = str(value.get("platform_profile", ""))
        active_map = value.get("active_map", {})
        if isinstance(active_map, dict):
            message.map_id = str(active_map.get("map_id", ""))
            message.map_version_id = str(active_map.get("map_version_id", ""))
            message.map_hash = str(
                active_map.get("map_hash", active_map.get("manifest_sha256", ""))
            )
        launch_arguments = value.get("launch_arguments", {})
        if isinstance(launch_arguments, dict):
            message.mission_id = str(launch_arguments.get("mission_id", ""))
            message.mission_version = str(launch_arguments.get("mission_version", ""))
            message.mission_sha256 = str(launch_arguments.get("mission_sha256", ""))
        message.launch_profile = str(value.get("launch_profile", ""))
        message.result_status = str(value.get("result_status", ""))
        config_files = value.get("config_files", [])
        message.config_snapshot_count = len(config_files) if isinstance(config_files, list) else 0
        message.message = f"experiment is {str(value.get('state', 'unknown')).lower()}"
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

    def _list_experiments(self, request, response):
        try:
            experiments = self._facade.list_experiments(state=int(request.state))
            response.experiments = [
                self._experiment_summary(item) for item in experiments
            ]
            response.success = True
            response.error_code = ListExperiments.Response.ERROR_NONE
            response.message = f"listed {len(experiments)} experiments"
        except ValueError as exc:
            response.success = False
            response.error_code = ListExperiments.Response.ERROR_INVALID_REQUEST
            response.message = str(exc)
        except Exception as exc:
            response.success = False
            response.error_code = ListExperiments.Response.ERROR_INTERNAL
            response.message = str(exc)
        return response

    @staticmethod
    def _request_values(request) -> dict[str, object]:
        return {
            "bag_id": request.bag_id,
            "experiment_id": request.experiment_id,
            "experiment_title": request.experiment_title,
            "objective": request.objective,
            "hypothesis": request.hypothesis,
            "tags_json": request.tags_json,
            "operator_note": request.operator_note,
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
            "launch_profile": request.launch_profile,
            "start_experiment": request.start_experiment,
            "event_type": request.event_type,
            "metadata_json": request.metadata_json,
            "result_status": request.result_status,
            "reason": request.reason,
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
