#!/usr/bin/env python3

"""ROS adapter that records structured localization results."""

import rclpy
from agt_interfaces.msg import LocalizationStatus
from rclpy.node import Node

from agt_experiment_manager.manager import ExperimentManager, ExperimentError


class ExperimentManagerNode(Node):
    def __init__(self) -> None:
        super().__init__("agt_experiment_manager")
        root = str(self.declare_parameter("experiments_dir", "runtime/experiments").value)
        self._experiment_id = str(self.declare_parameter("active_experiment_id", "").value)
        self._manager = ExperimentManager(root)
        self.create_subscription(LocalizationStatus, "/agt/localization/status", self._localization_callback, 10)

    def _localization_callback(self, message: LocalizationStatus) -> None:
        if not self._experiment_id:
            return
        try:
            self._manager.record_localization_result(self._experiment_id, {
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
            })
        except ExperimentError as error:
            self.get_logger().warning(str(error))


def main(args=None) -> None:
    rclpy.init(args=args)
    node = ExperimentManagerNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
