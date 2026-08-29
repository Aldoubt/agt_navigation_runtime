#!/usr/bin/env python3

from __future__ import annotations

import json

import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node

from agt_interfaces.action import AggregateInspectionViews


class MockViewAggregatorServer(Node):
    """Deterministic POINT_LOCAL baseline that intentionally performs no ID dedup."""

    def __init__(self) -> None:
        super().__init__("agt_mock_view_aggregator")
        self._server = ActionServer(
            self,
            AggregateInspectionViews,
            "/agt/vision/aggregate_views",
            execute_callback=self._execute,
            goal_callback=self._goal,
            cancel_callback=self._cancel,
            callback_group=ReentrantCallbackGroup(),
        )

    @staticmethod
    def _goal(request: AggregateInspectionViews.Goal) -> GoalResponse:
        required = (
            request.request_id,
            request.session_id,
            request.point_id,
            request.map_id,
            request.map_version_id,
            request.count_target,
            request.aggregation_profile,
        )
        return GoalResponse.ACCEPT if all(required) else GoalResponse.REJECT

    @staticmethod
    def _cancel(_goal_handle) -> CancelResponse:
        return CancelResponse.ACCEPT

    def _failure(self, goal_handle, code: int, message: str):
        result = AggregateInspectionViews.Result()
        result.success = False
        result.error_code = int(code)
        result.aggregator_id = "mock-passthrough-aggregator"
        result.aggregator_version = "1"
        result.message = message
        goal_handle.abort()
        return result

    def _execute(self, goal_handle):
        request = goal_handle.request
        if goal_handle.is_cancel_requested:
            result = AggregateInspectionViews.Result()
            result.success = False
            result.error_code = AggregateInspectionViews.Result.ERROR_CANCELED
            result.aggregator_id = "mock-passthrough-aggregator"
            result.aggregator_version = "1"
            result.message = "canceled"
            goal_handle.canceled()
            return result

        if len(request.views) < 2:
            return self._failure(
                goal_handle,
                AggregateInspectionViews.Result.ERROR_INSUFFICIENT_VIEWS,
                "POINT_LOCAL aggregation requires at least two views",
            )

        calibration_identity = None
        raw_count = 0
        for index, view in enumerate(request.views, start=1):
            if (
                view.map_id != request.map_id
                or view.map_version_id != request.map_version_id
                or view.point_id != request.point_id
            ):
                return self._failure(
                    goal_handle,
                    AggregateInspectionViews.Result.ERROR_MAP_MISMATCH,
                    "view map/point identity does not match aggregation goal",
                )
            identity = (view.camera_calibration_id, view.camera_calibration_sha256)
            if calibration_identity is None:
                calibration_identity = identity
            elif identity != calibration_identity:
                return self._failure(
                    goal_handle,
                    AggregateInspectionViews.Result.ERROR_CALIBRATION_MISMATCH,
                    "views use different camera calibration identities",
                )
            raw_count += int(view.raw_instance_count)
            feedback = AggregateInspectionViews.Feedback()
            feedback.stage = "VALIDATING_VIEWS"
            feedback.current_view = index
            feedback.total_views = len(request.views)
            feedback.progress = float(index) / float(len(request.views))
            goal_handle.publish_feedback(feedback)

        result_json = {
            "schema_version": 1,
            "aggregation_scope": "POINT_LOCAL",
            "aggregator_id": "mock-passthrough-aggregator",
            "aggregator_version": "1",
            "dedup_applied": False,
            "raw_instance_count": raw_count,
            "unique_instance_count": raw_count,
            "ambiguous_instance_count": 0,
            "global_instances": [],
            "warnings": ["MOCK_NO_DEDUP"],
        }

        result = AggregateInspectionViews.Result()
        result.success = True
        result.error_code = AggregateInspectionViews.Result.ERROR_NONE
        result.aggregator_id = "mock-passthrough-aggregator"
        result.aggregator_version = "1"
        result.raw_instance_count = raw_count
        result.unique_instance_count = raw_count
        result.ambiguous_instance_count = 0
        result.association_confidence = 0.0
        result.result_uri = ""
        result.result_json = json.dumps(result_json, separators=(",", ":"), sort_keys=True)
        result.message = "mock baseline completed without cross-view ID deduplication"
        goal_handle.succeed()
        return result

    def destroy_node(self):
        self._server.destroy()
        return super().destroy_node()


def main(args=None) -> None:
    rclpy.init(args=args)
    node = MockViewAggregatorServer()
    executor = MultiThreadedExecutor(num_threads=2)
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
