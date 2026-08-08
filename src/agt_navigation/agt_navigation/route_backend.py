"""Internal ROUTE backend runner used by ExecuteWaypointTask.

This layer bridges the pure RouteNavigationCore to a Nav2 FollowPath tracker. It
never requests a global path and never owns TF; a snapshot provider supplies the
currently authoritative map->odom transform at segment boundaries.
"""

from __future__ import annotations

import asyncio
from dataclasses import dataclass
import threading
from typing import Callable

from .nav2_follow_path_adapter import Nav2FollowPathTrackerAdapter
from .route_runtime import (
    MapOdomSnapshot,
    RouteAsset,
    RouteNavigationCore,
    RouteRuntimeError,
    SegmentCompletion,
    TrackerFeedback,
)


@dataclass(frozen=True)
class RouteBackendResult:
    success: bool
    canceled: bool
    failure_reason: str
    completions: tuple[SegmentCompletion, ...]
    global_planner_requests: int


class RouteBackendExecutor:
    """Run one Route Asset using only FollowPath segment tracking."""

    def __init__(
        self,
        *,
        action_client,
        asset: RouteAsset,
        snapshot_provider: Callable[[], MapOdomSnapshot],
        controller_id_forward: str = "",
        controller_id_reverse: str = "",
        goal_checker_id: str = "",
        progress_checker_id: str = "",
        wait_timeout_sec: float = 2.0,
        progress_sink: Callable[[TrackerFeedback, int, int], None] | None = None,
        completion_sink: Callable[[SegmentCompletion, int, int], None] | None = None,
    ):
        self.asset = asset
        self._action_client = action_client
        self._snapshot_provider = snapshot_provider
        self._controller_forward = str(controller_id_forward)
        self._controller_reverse = str(controller_id_reverse)
        self._goal_checker_id = str(goal_checker_id)
        self._progress_checker_id = str(progress_checker_id)
        self._wait_timeout = float(wait_timeout_sec)
        self._progress_sink = progress_sink
        self._completion_sink = completion_sink
        self._lock = threading.RLock()
        self._core: RouteNavigationCore | None = None
        self._failure_reason = ""

    def cancel(self) -> None:
        with self._lock:
            core = self._core
        if core is not None:
            core.cancel()

    def fail(self, reason: str) -> None:
        with self._lock:
            self._failure_reason = str(reason)
            core = self._core
        if core is not None:
            core.fail()

    async def run(
        self,
        *,
        loop_count: int,
        cancel_requested: Callable[[], bool],
    ) -> RouteBackendResult:
        if int(loop_count) <= 0:
            raise RouteRuntimeError("route_loop_count_invalid", "loop_count must be positive")
        completions: list[SegmentCompletion] = []
        total_global_planner_requests = 0

        for loop_index in range(int(loop_count)):
            if cancel_requested():
                return RouteBackendResult(False, True, "task canceled", tuple(completions), total_global_planner_requests)

            done = threading.Event()
            local_failure = {"reason": ""}
            tracker = Nav2FollowPathTrackerAdapter(
                action_client=self._action_client,
                controller_id_forward=self._controller_forward,
                controller_id_reverse=self._controller_reverse,
                goal_checker_id=self._goal_checker_id,
                progress_checker_id=self._progress_checker_id,
                wait_timeout_sec=self._wait_timeout,
            )
            core = RouteNavigationCore(self.asset, tracker)
            segment_indices = {
                segment.segment_id: index for index, segment in enumerate(self.asset.segments)
            }

            def sink(feedback: TrackerFeedback) -> None:
                try:
                    status = str(feedback.status).upper()
                    if status == "FAILED" and feedback.failure_reason:
                        local_failure["reason"] = str(feedback.failure_reason)
                    active = core.active_segment
                    if (
                        status == "SUCCEEDED"
                        and active is not None
                        and segment_indices[active.segment_id] + 1 < len(self.asset.segments)
                    ):
                        # Freeze a fresh authoritative alignment only for the next
                        # segment. The current RuntimePath has already completed.
                        core.update_global_alignment(self._snapshot_provider())

                    completion = core.handle_tracker_feedback(feedback)
                    index = segment_indices.get(feedback.active_segment_id, 0)
                    if self._progress_sink is not None:
                        self._progress_sink(feedback, loop_index, index)
                    if completion is not None:
                        completions.append(completion)
                        if self._completion_sink is not None:
                            self._completion_sink(completion, loop_index, index)
                    if core.state in {"COMPLETED", "FAILED", "CANCELED"}:
                        done.set()
                except Exception as exc:
                    local_failure["reason"] = str(exc)
                    core.fail()
                    done.set()

            tracker.set_feedback_sink(sink)
            with self._lock:
                self._core = core
                self._failure_reason = ""
            try:
                core.start(self._snapshot_provider())
            except Exception:
                with self._lock:
                    self._core = None
                raise

            while not done.is_set():
                if cancel_requested():
                    core.cancel()
                    done.set()
                    break
                with self._lock:
                    external_failure = self._failure_reason
                if external_failure:
                    core.fail()
                    done.set()
                    break
                await asyncio.sleep(0.01)

            total_global_planner_requests += core.metrics.global_planner_requests
            with self._lock:
                external_failure = self._failure_reason
                self._core = None
            failure_reason = external_failure or local_failure["reason"]
            if cancel_requested() or core.state == "CANCELED":
                return RouteBackendResult(False, True, "task canceled", tuple(completions), total_global_planner_requests)
            if core.state != "COMPLETED":
                return RouteBackendResult(
                    False,
                    False,
                    failure_reason or "Route FollowPath tracking failed",
                    tuple(completions),
                    total_global_planner_requests,
                )

        return RouteBackendResult(True, False, "", tuple(completions), total_global_planner_requests)
