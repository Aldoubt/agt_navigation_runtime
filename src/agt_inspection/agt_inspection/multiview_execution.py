from __future__ import annotations

import asyncio
from dataclasses import dataclass, replace
import json
from typing import Any, Awaitable, Callable, Mapping, Protocol

from .execution import (
    CaptureResult,
    InspectionErrorCode,
    InspectionExecutor,
    InspectionResult,
    VisionResult,
)
from .model import InspectionPoint, InspectionTask, InspectionView


@dataclass(frozen=True)
class AggregationResult:
    success: bool
    error_code: int = 0
    message: str = ""
    aggregator_id: str = ""
    aggregator_version: str = ""
    raw_instance_count: int = 0
    unique_instance_count: int = 0
    ambiguous_instance_count: int = 0
    association_confidence: float = 0.0
    result_json: str = "{}"
    canceled: bool = False
    cancel_confirmed: bool = False


class ViewAggregator(Protocol):
    async def aggregate(
        self,
        task: InspectionTask,
        point: InspectionPoint,
        observations: list[Mapping[str, Any]],
    ) -> AggregationResult: ...

    async def cancel(self) -> bool: ...


class ViewContextProvider(Protocol):
    def snapshot(
        self,
        task: InspectionTask,
        point: InspectionPoint,
        view: InspectionView,
        request_id: str,
    ) -> Mapping[str, Any]: ...


class MultiviewEvidenceStore(Protocol):
    def start_session(self, session: Mapping[str, Any]): ...

    def write_view(
        self,
        point_id: str,
        view_id: str,
        observation: Mapping[str, Any],
        *,
        image_bytes: bytes = b"",
        overlay_bytes: bytes = b"",
        mask_bytes: bytes = b"",
        image_suffix: str = ".bin",
        overlay_suffix: str = ".bin",
        mask_suffix: str = ".bin",
    ) -> str: ...

    def write_aggregation(self, point_id: str, aggregation: Mapping[str, Any], **kwargs) -> str: ...

    def write_aggregation_failure(
        self, point_id: str, *, error_code: int, message: str
    ) -> str: ...

    def build_report(self) -> str: ...

    def finish_session(
        self,
        *,
        success: bool,
        error_code: int,
        message: str,
        canceled: bool = False,
        report_uri: str = "",
    ) -> None: ...


class _UnusedLegacyEvidence:
    """Sentinel required only because v2 reuses leaf helpers from InspectionExecutor."""

    def start_session(self, *_args, **_kwargs):
        raise RuntimeError("legacy evidence path must not be used by schema v2")

    persist_capture = start_session
    finish_session = start_session


class MultiviewInspectionExecutor(InspectionExecutor):
    """Schema-v2 executor: navigate once, collect ordered views, then best-effort dedup."""

    def __init__(
        self,
        *,
        navigation,
        gimbal,
        camera,
        vision,
        stationary,
        evidence_store: MultiviewEvidenceStore,
        aggregator: ViewAggregator | None,
        context_provider: ViewContextProvider,
        monotonic: Callable[[], float],
        sleep: Callable[[float], Awaitable[None]] = asyncio.sleep,
        stage_callback: Callable[[str, str], None] | None = None,
        poll_period_s: float = 0.05,
        stationary_freshness_s: float = 0.5,
    ) -> None:
        super().__init__(
            navigation=navigation,
            gimbal=gimbal,
            camera=camera,
            vision=vision,
            stationary=stationary,
            evidence=_UnusedLegacyEvidence(),
            monotonic=monotonic,
            sleep=sleep,
            stage_callback=stage_callback,
            poll_period_s=poll_period_s,
            stationary_freshness_s=stationary_freshness_s,
        )
        self._multiview_store = evidence_store
        self._aggregator = aggregator
        self._context_provider = context_provider

    @staticmethod
    def _session_document(task: InspectionTask, session_id: str) -> dict[str, Any]:
        return {
            "schema_version": 1,
            "session_id": session_id,
            "inspection_task_id": task.inspection_task_id,
            "task_revision": task.revision,
            "task_content_sha256": task.content_sha256,
            "map_id": task.map_binding.map_id,
            "map_version_id": task.map_binding.map_version_id,
            "map_manifest_sha256": task.map_binding.manifest_sha256,
            "count_target": task.count_target,
        }

    @staticmethod
    def _level1_payload(
        vision: VisionResult, *, expected_count_target: str
    ) -> tuple[int, dict[str, Any]]:
        try:
            payload = json.loads(vision.result_json)
        except (TypeError, json.JSONDecodeError) as exc:
            raise ValueError(f"Level-1 result_json is not valid JSON: {exc}") from exc
        if not isinstance(payload, dict):
            raise ValueError("Level-1 result_json must contain a JSON object")
        if payload.get("count_target") != expected_count_target:
            raise ValueError(
                "Level-1 result_json.count_target must match task count_target"
            )
        raw_count = payload.get("raw_count")
        if isinstance(raw_count, bool) or not isinstance(raw_count, int) or raw_count < 0:
            raise ValueError("Level-1 result_json.raw_count must be a non-negative integer")
        return raw_count, payload

    def _build_observation(
        self,
        task: InspectionTask,
        point: InspectionPoint,
        view: InspectionView,
        request_id: str,
        capture: CaptureResult,
        vision: VisionResult,
    ) -> dict[str, Any]:
        raw_count, payload = self._level1_payload(
            vision, expected_count_target=task.count_target
        )
        context = dict(self._context_provider.snapshot(task, point, view, request_id))
        for key in ("capture_stamp", "robot_pose_map", "gimbal", "camera"):
            if key not in context:
                raise ValueError(f"capture context is missing required field: {key}")
        observation = {
            "schema_version": 1,
            "view_id": view.id,
            "capture_id": request_id,
            "capture_stamp": context["capture_stamp"],
            "robot_pose_map": context["robot_pose_map"],
            "gimbal": context["gimbal"],
            "camera": context["camera"],
            "camera_pose_valid": bool(context.get("camera_pose_valid", False)),
            "camera_pose_map": context.get("camera_pose_map", {}),
            "evidence": {"image": capture.image_uri} if capture.image_uri else {},
            "vision": {
                "model_id": vision.model_id,
                "model_version": vision.model_version,
                "weights_sha256": vision.weights_sha256,
                "raw_count": raw_count,
                "inference_time_ms": vision.inference_time_ms,
                "primary_confidence": vision.primary_confidence,
                "result_json": payload,
            },
            "warnings": list(context.get("warnings", [])),
        }
        return observation

    async def _run_aggregator(
        self,
        task: InspectionTask,
        point: InspectionPoint,
        observations: list[Mapping[str, Any]],
    ) -> AggregationResult:
        if self._aggregator is None:
            return AggregationResult(False, error_code=1, message="view aggregator unavailable")
        child = asyncio.create_task(self._aggregator.aggregate(task, point, observations))
        while not child.done():
            if self._cancel_requested:
                request_confirmed = bool(await self._aggregator.cancel())
                result = await child
                if request_confirmed and result.canceled and result.cancel_confirmed:
                    return result
                return AggregationResult(
                    False,
                    error_code=int(InspectionErrorCode.INTERNAL),
                    message="aggregation child did not confirm cancellation",
                )
            await asyncio.sleep(0)
        return await child

    def _aggregation_document(self, result: AggregationResult) -> dict[str, Any]:
        try:
            payload = json.loads(result.result_json or "{}")
        except json.JSONDecodeError:
            payload = {}
        if not isinstance(payload, dict):
            payload = {}
        return {
            "schema_version": 1,
            "aggregation_scope": "POINT_LOCAL",
            "aggregator_id": result.aggregator_id,
            "aggregator_version": result.aggregator_version,
            "raw_instance_count": int(result.raw_instance_count),
            "unique_instance_count": int(result.unique_instance_count),
            "ambiguous_instance_count": int(result.ambiguous_instance_count),
            "association_confidence": float(result.association_confidence),
            "global_instances": list(payload.get("global_instances", [])),
            "warnings": list(payload.get("warnings", [])),
        }

    def _finish_v2(
        self,
        root: str,
        *,
        success: bool,
        error_code: int,
        message: str,
        canceled: bool = False,
    ) -> InspectionResult:
        report_uri = ""
        try:
            report_uri = self._multiview_store.build_report()
        except Exception:
            report_uri = ""
        self._multiview_store.finish_session(
            success=success,
            error_code=int(error_code),
            message=message,
            canceled=canceled,
            report_uri=report_uri,
        )
        return InspectionResult(success, int(error_code), message, root, canceled)

    async def execute(self, task: InspectionTask, *, session_id: str) -> InspectionResult:
        self._cancel_requested = False
        if task.schema_version != 2 or not task.count_target:
            return InspectionResult(
                False,
                int(InspectionErrorCode.INVALID_TASK),
                "MultiviewInspectionExecutor requires schema_version 2",
                "",
            )

        root = str(
            self._multiview_store.start_session(self._session_document(task, session_id))
        )
        try:
            for point in task.points:
                if self._cancel_requested:
                    return self._finish_v2(
                        root,
                        success=False,
                        error_code=InspectionErrorCode.CANCELED,
                        message="canceled",
                        canceled=True,
                    )

                navigation, stationary = await self._navigate_and_stabilize(point)
                if not stationary:
                    if navigation.canceled:
                        return self._finish_v2(
                            root,
                            success=False,
                            error_code=InspectionErrorCode.CANCELED,
                            message="canceled",
                            canceled=True,
                        )
                    code = (
                        InspectionErrorCode.INTERNAL
                        if navigation.error_code == int(InspectionErrorCode.INTERNAL)
                        else InspectionErrorCode.NOT_STATIONARY
                        if navigation.error_code == int(InspectionErrorCode.NOT_STATIONARY)
                        else InspectionErrorCode.NAVIGATION
                    )
                    return self._finish_v2(
                        root,
                        success=False,
                        error_code=code,
                        message=navigation.message or "navigation/stationary gate failed",
                    )

                observations: list[dict[str, Any]] = []
                for view in point.views:
                    view_point = replace(point, gimbal=view.gimbal)
                    gimbal = await self._retry_gimbal(view_point)
                    if gimbal.canceled:
                        return self._finish_v2(
                            root,
                            success=False,
                            error_code=InspectionErrorCode.CANCELED,
                            message="canceled",
                            canceled=True,
                        )
                    if not gimbal.success:
                        code = (
                            InspectionErrorCode.INTERNAL
                            if gimbal.error_code == int(InspectionErrorCode.INTERNAL)
                            else InspectionErrorCode.GIMBAL
                        )
                        return self._finish_v2(
                            root,
                            success=False,
                            error_code=code,
                            message=gimbal.message or "gimbal move failed",
                        )

                    self._stage("WAITING_GIMBAL_STABLE", view_point)
                    if not await self._sleep_cancelable(view.gimbal.settle_duration_s):
                        return self._finish_v2(
                            root,
                            success=False,
                            error_code=InspectionErrorCode.CANCELED,
                            message="canceled",
                            canceled=True,
                        )

                    request_id = f"{session_id}:{point.id}:{view.id}"
                    capture = await self._retry_capture(view_point, 1, request_id)
                    if self._cancel_requested or capture.error_code == int(InspectionErrorCode.CANCELED):
                        return self._finish_v2(
                            root,
                            success=False,
                            error_code=InspectionErrorCode.CANCELED,
                            message="canceled",
                            canceled=True,
                        )
                    if not capture.success:
                        return self._finish_v2(
                            root,
                            success=False,
                            error_code=InspectionErrorCode.CAPTURE,
                            message=capture.message or "capture failed",
                        )

                    vision = await self._retry_vision(view_point, capture, request_id)
                    if vision.canceled:
                        return self._finish_v2(
                            root,
                            success=False,
                            error_code=InspectionErrorCode.CANCELED,
                            message="canceled",
                            canceled=True,
                        )
                    if vision.error_code == int(InspectionErrorCode.INTERNAL):
                        return self._finish_v2(
                            root,
                            success=False,
                            error_code=InspectionErrorCode.INTERNAL,
                            message=vision.message,
                        )
                    if not vision.success or vision.primary_confidence < point.vision.minimum_confidence:
                        return self._finish_v2(
                            root,
                            success=False,
                            error_code=InspectionErrorCode.INFERENCE,
                            message=vision.message
                            or "single-view inference failed or below confidence threshold",
                        )

                    try:
                        observation = self._build_observation(
                            task, point, view, request_id, capture, vision
                        )
                    except ValueError as exc:
                        return self._finish_v2(
                            root,
                            success=False,
                            error_code=InspectionErrorCode.INFERENCE,
                            message=str(exc),
                        )

                    self._stage("SAVING_RESULT", view_point)
                    result_uri = self._multiview_store.write_view(
                        point.id,
                        view.id,
                        observation,
                        image_bytes=capture.image_bytes,
                        overlay_bytes=vision.overlay_bytes,
                        mask_bytes=vision.mask_bytes,
                        image_suffix=capture.image_suffix,
                        overlay_suffix=vision.overlay_suffix,
                        mask_suffix=vision.mask_suffix,
                    )
                    observation["single_view_result_uri"] = result_uri
                    observations.append(observation)

                if point.aggregation is not None and point.aggregation.enabled:
                    self._stage("AGGREGATING_VIEWS", point)
                    aggregation = await self._run_aggregator(task, point, observations)
                    if aggregation.canceled:
                        return self._finish_v2(
                            root,
                            success=False,
                            error_code=InspectionErrorCode.CANCELED,
                            message="canceled",
                            canceled=True,
                        )
                    if aggregation.success:
                        self._multiview_store.write_aggregation(
                            point.id, self._aggregation_document(aggregation)
                        )
                    else:
                        self._multiview_store.write_aggregation_failure(
                            point.id,
                            error_code=int(aggregation.error_code),
                            message=aggregation.message or "point-local aggregation failed",
                        )
                        self._stage("AGGREGATION_FAILED_NONBLOCKING", point)

            return self._finish_v2(
                root,
                success=True,
                error_code=InspectionErrorCode.NONE,
                message="multiview inspection completed",
            )
        except Exception as exc:
            return self._finish_v2(
                root,
                success=False,
                error_code=InspectionErrorCode.INTERNAL,
                message=f"multiview inspection failed unexpectedly: {exc}",
            )
