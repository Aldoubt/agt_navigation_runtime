from __future__ import annotations

import asyncio

from aiohttp.test_utils import TestClient, TestServer

from agt_operator_gateway.delivery_server import create_delivery_app
from agt_operator_gateway.state_store import GatewayStateStore


class FakeTaskPort:
    def __init__(self) -> None:
        self.calls = []

    def preview(self, payload):
        self.calls.append(("preview", payload))
        return {
            "ok": True,
            "segments": [{"fromId": "P01", "toId": "P02", "ok": True}],
            "path": [{"x": 1.0, "y": 2.0}, {"x": 3.0, "y": 4.0}],
        }

    def save(self, task_id, payload):
        self.calls.append(("save", task_id, payload))
        return {"taskId": task_id, "state": "SAVED"}


class FakeRunPort:
    def __init__(self) -> None:
        self.calls = []

    def readiness(self):
        self.calls.append(("readiness",))
        return {
            "ready": False,
            "autoPermit": False,
            "siteReady": True,
            "localizationReady": True,
            "navigationReady": True,
            "lidarReady": True,
            "cameraGimbalReady": True,
            "blockers": ["AUTO_PERMIT"],
        }

    def relocalize(self):
        self.calls.append(("relocalize",))
        return {"accepted": True, "state": "REQUESTED", "message": "bounded relocalization requested"}


def _store() -> GatewayStateStore:
    store = GatewayStateStore(now_ms=lambda: 1000)
    store.update(
        robot_snapshot={"identity": {"id": "agt-01"}},
        navigation={"robotPose": {"x": 0.0, "y": 0.0, "yawRad": 0.0}},
        mission={
            "id": "",
            "name": "",
            "state": "IDLE",
            "currentStep": 0,
            "totalSteps": 0,
            "progress": 0.0,
            "route": [],
            "loop": {"enabled": False, "count": 1},
        },
        received_at_ms=1000,
    )
    return store


async def _client(task_port=None, run_port=None, *, write_api_enabled=True, token="secret"):
    app = create_delivery_app(
        _store(),
        now_ms=lambda: 1000,
        task_authoring=task_port,
        run_control=run_port,
        write_api_enabled=write_api_enabled,
        command_token=token,
    )
    client = TestClient(TestServer(app))
    await client.start_server()
    return client


def _task_payload():
    return {
        "taskId": "inspection-1",
        "siteId": "slope",
        "siteRevision": "r02",
        "waypoints": [
            {"id": "P01", "x": 1.0, "y": 2.0, "yaw": 0.0, "dwellS": 0.8},
            {"id": "P02", "x": 3.0, "y": 4.0, "yaw": 0.5, "dwellS": 0.8},
        ],
    }


def test_task_preview_and_save_are_site_bound_and_guarded() -> None:
    async def run():
        port = FakeTaskPort()
        client = await _client(task_port=port)
        try:
            response = await client.post("/api/v1/tasks/preview", json=_task_payload())
            assert response.status == 401
            assert port.calls == []

            headers = {"Authorization": "Bearer secret"}
            response = await client.post("/api/v1/tasks/preview", headers=headers, json=_task_payload())
            payload = await response.json()
            assert response.status == 200
            assert payload["apiVersion"] == "agt.operator.gateway/v1"
            assert payload["ok"] is True
            assert payload["path"][-1] == {"x": 3.0, "y": 4.0}

            response = await client.put(
                "/api/v1/tasks/inspection-1",
                headers=headers,
                json=_task_payload(),
            )
            payload = await response.json()
            assert response.status == 200
            assert payload["taskId"] == "inspection-1"
            assert port.calls[-1][0:2] == ("save", "inspection-1")
        finally:
            await client.close()

    asyncio.run(run())


def test_task_request_rejects_route_id_mismatch() -> None:
    async def run():
        port = FakeTaskPort()
        client = await _client(task_port=port)
        try:
            response = await client.put(
                "/api/v1/tasks/other",
                headers={"Authorization": "Bearer secret"},
                json=_task_payload(),
            )
            assert response.status == 400
            assert port.calls == []
        finally:
            await client.close()

    asyncio.run(run())


def test_run_readiness_is_read_only_and_relocalize_is_guarded() -> None:
    async def run():
        port = FakeRunPort()
        client = await _client(run_port=port)
        try:
            response = await client.get("/api/v1/run/readiness")
            payload = await response.json()
            assert response.status == 200
            assert payload["apiVersion"] == "agt.operator.gateway/v1"
            assert payload["ready"] is False
            assert payload["blockers"] == ["AUTO_PERMIT"]

            response = await client.post("/api/v1/run/relocalize", json={})
            assert response.status == 401
            assert port.calls == [("readiness",)]

            response = await client.post(
                "/api/v1/run/relocalize",
                headers={"Authorization": "Bearer secret"},
                json={},
            )
            payload = await response.json()
            assert response.status == 202
            assert payload["accepted"] is True
            assert payload["state"] == "REQUESTED"
        finally:
            await client.close()

    asyncio.run(run())


def test_delivery_capability_unavailable_is_explicit() -> None:
    async def run():
        client = await _client()
        try:
            response = await client.post(
                "/api/v1/tasks/preview",
                headers={"Authorization": "Bearer secret"},
                json=_task_payload(),
            )
            assert response.status == 503
            assert (await response.json())["code"] == "TASK_AUTHORING_UNAVAILABLE"

            response = await client.get("/api/v1/run/readiness")
            assert response.status == 503
            assert (await response.json())["code"] == "RUN_CONTROL_UNAVAILABLE"
        finally:
            await client.close()

    asyncio.run(run())
