from __future__ import annotations

import asyncio
import math
from collections.abc import Mapping
from typing import Any

from aiohttp import web

from .command_guard import verify_bearer_token
from .contract import GATEWAY_API_VERSION
from .delivery_ports import InspectionAuthoringPort, RunControlPort, TaskAuthoringPort


def _error(status: int, code: str, message: str) -> web.Response:
    return web.json_response(
        {
            "apiVersion": GATEWAY_API_VERSION,
            "code": code,
            "message": message,
        },
        status=status,
    )


def _require_write(request: web.Request, *, write_api_enabled: bool, command_token: str) -> web.Response | None:
    if not write_api_enabled or not command_token:
        return _error(403, "WRITE_API_DISABLED", "delivery write API is disabled")
    if not verify_bearer_token(request.headers.get("Authorization"), command_token):
        return _error(401, "UNAUTHORIZED", "invalid command authorization")
    return None


def _required_string(payload: Mapping[str, Any], key: str) -> str:
    value = payload.get(key)
    if not isinstance(value, str) or not value.strip():
        raise ValueError(f"{key} must be a non-empty string")
    if len(value.strip()) > 256:
        raise ValueError(f"{key} exceeds maximum length 256")
    return value.strip()


def _finite_number(value: Any, label: str) -> float:
    if not isinstance(value, (int, float)) or isinstance(value, bool):
        raise ValueError(f"{label} must be a finite number")
    result = float(value)
    if not math.isfinite(result):
        raise ValueError(f"{label} must be a finite number")
    return result


def _nonnegative_revision(value: Any, label: str) -> int:
    if isinstance(value, bool) or not isinstance(value, int) or value < 0:
        raise ValueError(f"{label} must be a non-negative integer")
    return value


def _validate_task_payload(raw: Any) -> dict[str, Any]:
    if not isinstance(raw, Mapping):
        raise ValueError("request body must be a JSON object")
    payload = dict(raw)
    payload["taskId"] = _required_string(payload, "taskId")
    payload["siteId"] = _required_string(payload, "siteId")
    payload["siteRevision"] = _required_string(payload, "siteRevision")

    expected_revision = _nonnegative_revision(payload.get("expectedRevision", 0), "expectedRevision")
    payload["expectedRevision"] = expected_revision

    loop = payload.get("loop", False)
    loop_count = payload.get("loopCount", 1)
    if not isinstance(loop, bool):
        raise ValueError("loop must be boolean")
    if isinstance(loop_count, bool) or not isinstance(loop_count, int) or loop_count <= 0:
        raise ValueError("loopCount must be a positive integer")
    payload["loop"] = loop
    payload["loopCount"] = loop_count

    waypoints = payload.get("waypoints")
    if not isinstance(waypoints, list) or not waypoints:
        raise ValueError("waypoints must be a non-empty array")
    normalized_waypoints: list[dict[str, Any]] = []
    seen_ids: set[str] = set()
    for index, raw_waypoint in enumerate(waypoints):
        if not isinstance(raw_waypoint, Mapping):
            raise ValueError(f"waypoints[{index}] must be an object")
        waypoint = dict(raw_waypoint)
        waypoint_id = _required_string(waypoint, "id")
        if waypoint_id in seen_ids:
            raise ValueError(f"duplicate waypoint id: {waypoint_id}")
        seen_ids.add(waypoint_id)
        x = _finite_number(waypoint.get("x"), f"waypoints[{index}].x")
        y = _finite_number(waypoint.get("y"), f"waypoints[{index}].y")
        yaw = _finite_number(waypoint.get("yaw"), f"waypoints[{index}].yaw")
        dwell_s = _finite_number(waypoint.get("dwellS", 0.0), f"waypoints[{index}].dwellS")
        if dwell_s < 0.0:
            raise ValueError(f"waypoints[{index}].dwellS must be >= 0")
        normalized_waypoints.append(
            {"id": waypoint_id, "x": x, "y": y, "yaw": yaw, "dwellS": dwell_s}
        )
    payload["waypoints"] = normalized_waypoints
    return payload


def _validate_inspection_payload(raw: Any) -> dict[str, Any]:
    if not isinstance(raw, Mapping):
        raise ValueError("request body must be a JSON object")
    payload = dict(raw)
    payload["inspectionTaskId"] = _required_string(payload, "inspectionTaskId")
    payload["siteId"] = _required_string(payload, "siteId")
    payload["siteRevision"] = _required_string(payload, "siteRevision")
    payload["expectedRevision"] = _nonnegative_revision(
        payload.get("expectedRevision", 0),
        "expectedRevision",
    )
    payload["expectedHomeTaskRevision"] = _nonnegative_revision(
        payload.get("expectedHomeTaskRevision", 0),
        "expectedHomeTaskRevision",
    )

    raw_points = payload.get("points")
    if not isinstance(raw_points, list) or not raw_points:
        raise ValueError("points must be a non-empty array")
    normalized_points: list[dict[str, Any]] = []
    seen_ids: set[str] = set()
    for index, raw_point in enumerate(raw_points):
        if not isinstance(raw_point, Mapping):
            raise ValueError(f"points[{index}] must be an object")
        point = dict(raw_point)
        point_id = _required_string(point, "id")
        if point_id in seen_ids or point_id.lower() == "home":
            raise ValueError(f"duplicate or reserved inspection point id: {point_id}")
        seen_ids.add(point_id)
        normalized_points.append(
            {
                "id": point_id,
                "x": _finite_number(point.get("x"), f"points[{index}].x"),
                "y": _finite_number(point.get("y"), f"points[{index}].y"),
                "yaw": _finite_number(point.get("yaw"), f"points[{index}].yaw"),
                "expectedTaskRevision": _nonnegative_revision(
                    point.get("expectedTaskRevision", 0),
                    f"points[{index}].expectedTaskRevision",
                ),
            }
        )
    payload["points"] = normalized_points

    raw_home = payload.get("home")
    if not isinstance(raw_home, Mapping):
        raise ValueError("home must be an explicit map pose")
    payload["home"] = {
        "x": _finite_number(raw_home.get("x"), "home.x"),
        "y": _finite_number(raw_home.get("y"), "home.y"),
        "yaw": _finite_number(raw_home.get("yaw"), "home.yaw"),
    }
    return payload


def _with_api_version(payload: Mapping[str, Any]) -> dict[str, Any]:
    return {"apiVersion": GATEWAY_API_VERSION, **dict(payload)}


def register_task_run_routes(
    app: web.Application,
    *,
    task_authoring: TaskAuthoringPort | None,
    inspection_authoring: InspectionAuthoringPort | None = None,
    run_control: RunControlPort | None,
    write_api_enabled: bool,
    command_token: str,
) -> None:
    async def options(_request: web.Request) -> web.Response:
        return web.Response(status=204)

    async def task_context(_request: web.Request) -> web.Response:
        if task_authoring is None:
            return _error(503, "TASK_AUTHORING_UNAVAILABLE", "task authoring adapter is unavailable")
        try:
            result = await asyncio.to_thread(task_authoring.context)
        except Exception as exc:
            return _error(503, "TASK_AUTHORING_UNAVAILABLE", f"task context adapter failed: {exc}")
        return web.json_response(_with_api_version(result))

    async def task_map_image(_request: web.Request) -> web.Response:
        if task_authoring is None:
            return _error(503, "TASK_AUTHORING_UNAVAILABLE", "task authoring adapter is unavailable")
        try:
            image = await asyncio.to_thread(task_authoring.map_image)
        except Exception as exc:
            return _error(503, "TASK_AUTHORING_UNAVAILABLE", f"task map adapter failed: {exc}")
        return web.Response(body=image, content_type="image/x-portable-graymap")

    async def task_preview(request: web.Request) -> web.Response:
        guard = _require_write(
            request,
            write_api_enabled=write_api_enabled,
            command_token=command_token,
        )
        if guard is not None:
            return guard
        if task_authoring is None:
            return _error(503, "TASK_AUTHORING_UNAVAILABLE", "task authoring adapter is unavailable")
        try:
            payload = _validate_task_payload(await request.json())
        except Exception as exc:
            return _error(400, "INVALID_TASK_REQUEST", str(exc))
        try:
            result = await asyncio.to_thread(task_authoring.preview, payload)
        except ValueError as exc:
            return _error(409, "TASK_PREVIEW_REJECTED", str(exc))
        except Exception as exc:
            return _error(503, "TASK_AUTHORING_UNAVAILABLE", f"task preview adapter failed: {exc}")
        return web.json_response(_with_api_version(result))

    async def task_save(request: web.Request) -> web.Response:
        guard = _require_write(
            request,
            write_api_enabled=write_api_enabled,
            command_token=command_token,
        )
        if guard is not None:
            return guard
        if task_authoring is None:
            return _error(503, "TASK_AUTHORING_UNAVAILABLE", "task authoring adapter is unavailable")
        try:
            payload = _validate_task_payload(await request.json())
            task_id = request.match_info.get("task_id", "").strip()
            if not task_id or task_id != payload["taskId"]:
                raise ValueError("route task_id must match request taskId")
        except Exception as exc:
            return _error(400, "INVALID_TASK_REQUEST", str(exc))
        try:
            result = await asyncio.to_thread(task_authoring.save, task_id, payload)
        except ValueError as exc:
            return _error(409, "TASK_SAVE_REJECTED", str(exc))
        except Exception as exc:
            return _error(503, "TASK_AUTHORING_UNAVAILABLE", f"task save adapter failed: {exc}")
        return web.json_response(_with_api_version(result))

    async def save_inspection(request: web.Request) -> web.Response:
        guard = _require_write(
            request,
            write_api_enabled=write_api_enabled,
            command_token=command_token,
        )
        if guard is not None:
            return guard
        if inspection_authoring is None:
            return _error(
                503,
                "INSPECTION_AUTHORING_UNAVAILABLE",
                "inspection authoring adapter is unavailable",
            )
        try:
            payload = _validate_inspection_payload(await request.json())
            inspection_task_id = request.match_info.get("inspection_task_id", "").strip()
            if not inspection_task_id or inspection_task_id != payload["inspectionTaskId"]:
                raise ValueError(
                    "route inspection_task_id must match request inspectionTaskId"
                )
        except Exception as exc:
            return _error(400, "INVALID_INSPECTION_REQUEST", str(exc))
        try:
            result = await asyncio.to_thread(
                inspection_authoring.save,
                inspection_task_id,
                payload,
            )
        except ValueError as exc:
            return _error(409, "INSPECTION_SAVE_REJECTED", str(exc))
        except Exception as exc:
            return _error(
                503,
                "INSPECTION_AUTHORING_UNAVAILABLE",
                f"inspection save adapter failed: {exc}",
            )
        return web.json_response(_with_api_version(result))

    async def run_readiness(_request: web.Request) -> web.Response:
        if run_control is None:
            return _error(503, "RUN_CONTROL_UNAVAILABLE", "run control adapter is unavailable")
        try:
            result = await asyncio.to_thread(run_control.readiness)
        except Exception as exc:
            return _error(503, "RUN_CONTROL_UNAVAILABLE", f"run readiness adapter failed: {exc}")
        return web.json_response(_with_api_version(result))

    async def run_relocalize(request: web.Request) -> web.Response:
        guard = _require_write(
            request,
            write_api_enabled=write_api_enabled,
            command_token=command_token,
        )
        if guard is not None:
            return guard
        if run_control is None:
            return _error(503, "RUN_CONTROL_UNAVAILABLE", "run control adapter is unavailable")
        try:
            result = dict(await asyncio.to_thread(run_control.relocalize))
        except ValueError as exc:
            return _error(409, "RELOCALIZE_REJECTED", str(exc))
        except Exception as exc:
            return _error(503, "RUN_CONTROL_UNAVAILABLE", f"relocalization adapter failed: {exc}")
        status = 202 if bool(result.get("accepted", False)) else 409
        return web.json_response(_with_api_version(result), status=status)

    app.router.add_get("/api/v1/tasks/context", task_context)
    app.router.add_get("/api/v1/tasks/map/image", task_map_image)
    app.router.add_post("/api/v1/tasks/preview", task_preview)
    app.router.add_options("/api/v1/tasks/preview", options)
    app.router.add_put("/api/v1/tasks/{task_id}", task_save)
    app.router.add_options("/api/v1/tasks/{task_id}", options)
    app.router.add_put("/api/v1/inspections/{inspection_task_id}", save_inspection)
    app.router.add_options("/api/v1/inspections/{inspection_task_id}", options)
    app.router.add_get("/api/v1/run/readiness", run_readiness)
    app.router.add_post("/api/v1/run/relocalize", run_relocalize)
    app.router.add_options("/api/v1/run/relocalize", options)
