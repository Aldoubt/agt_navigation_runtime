from __future__ import annotations

import asyncio

from aiohttp.test_utils import TestClient, TestServer

from agt_operator_gateway.command_guard import ControlLeaseStore
from agt_operator_gateway.mission_commands import MissionCommandResult
from agt_operator_gateway.server import create_app
from agt_operator_gateway.state_store import GatewayStateStore


class FakeMissionCommands:
    def __init__(self) -> None:
        self.calls: list[tuple[str, tuple[str, ...]]] = []

    def start(self, mission_id: str, mission_version: str, expected_hash: str) -> MissionCommandResult:
        self.calls.append(('START', (mission_id, mission_version, expected_hash)))
        return MissionCommandResult.accepted_result('accepted')

    def pause(self, mission_id: str) -> MissionCommandResult:
        self.calls.append(('PAUSE', (mission_id,)))
        return MissionCommandResult.accepted_result('accepted')

    def resume(self, mission_id: str) -> MissionCommandResult:
        self.calls.append(('RESUME', (mission_id,)))
        return MissionCommandResult.accepted_result('accepted')

    def cancel(self, mission_id: str) -> MissionCommandResult:
        self.calls.append(('CANCEL', (mission_id,)))
        return MissionCommandResult.accepted_result('accepted')


def _store() -> GatewayStateStore:
    store = GatewayStateStore(now_ms=lambda: 1000)
    store.update(
        robot_snapshot={'identity': {'id': 'agt-01'}},
        navigation={'robotPose': {'x': 0.0, 'y': 0.0, 'yawRad': 0.0}},
        mission={
            'id': 'inspection_001',
            'name': 'inspection_001',
            'state': 'READY',
            'currentStep': 0,
            'totalSteps': 3,
            'progress': 0.0,
            'route': [],
            'loop': {'enabled': False, 'count': 1},
        },
        received_at_ms=1000,
    )
    return store


def _headers() -> dict[str, str]:
    return {
        'Authorization': 'Bearer secret-token',
        'Content-Type': 'application/json',
        'Origin': 'http://operator.local',
    }


async def _client(
    commands: FakeMissionCommands,
    lease_store: ControlLeaseStore,
) -> TestClient:
    app = create_app(
        _store(),
        now_ms=lambda: 1000,
        mission_commands=commands,
        write_api_enabled=True,
        command_token='secret-token',
        control_lease_required=True,
        control_lease_store=lease_store,
        allowed_origins=('http://operator.local',),
    )
    client = TestClient(TestServer(app))
    await client.start_server()
    return client


def test_control_lease_http_allows_one_controller_and_owner_can_release() -> None:
    async def run() -> None:
        commands = FakeMissionCommands()
        lease_store = ControlLeaseStore(now_ms=lambda: 1000, ttl_ms=15_000)
        client = await _client(commands, lease_store)
        try:
            acquired = await client.post(
                '/api/v1/control/acquire',
                headers=_headers(),
                json={'clientId': 'laptop-a'},
            )
            acquired_payload = await acquired.json()
            assert acquired.status == 200
            assert acquired_payload['acquired'] is True
            assert acquired_payload['controllerId'] == 'laptop-a'
            assert acquired_payload['expiresAtMs'] == 16_000

            blocked = await client.post(
                '/api/v1/control/acquire',
                headers=_headers(),
                json={'clientId': 'laptop-b'},
            )
            blocked_payload = await blocked.json()
            assert blocked.status == 409
            assert blocked_payload['code'] == 'CONTROL_LEASE_HELD'
            assert blocked_payload['controllerId'] == 'laptop-a'

            status = await client.get('/api/v1/control')
            status_payload = await status.json()
            assert status.status == 200
            assert status_payload['controllerId'] == 'laptop-a'

            released = await client.post(
                '/api/v1/control/release',
                headers=_headers(),
                json={'clientId': 'laptop-a'},
            )
            assert released.status == 200
            assert (await released.json())['controllerId'] is None
        finally:
            await client.close()

    asyncio.run(run())


def test_mission_writes_require_client_id_and_active_control_lease() -> None:
    async def run() -> None:
        commands = FakeMissionCommands()
        lease_store = ControlLeaseStore(now_ms=lambda: 1000, ttl_ms=15_000)
        client = await _client(commands, lease_store)
        try:
            missing_client = await client.post(
                '/api/v1/mission/start',
                headers=_headers(),
                json={
                    'clientRequestId': 'req-1',
                    'missionId': 'inspection_001',
                    'missionVersion': 'v1',
                },
            )
            assert missing_client.status == 400

            no_lease = await client.post(
                '/api/v1/mission/start',
                headers=_headers(),
                json={
                    'clientId': 'laptop-a',
                    'clientRequestId': 'req-2',
                    'missionId': 'inspection_001',
                    'missionVersion': 'v1',
                },
            )
            no_lease_payload = await no_lease.json()
            assert no_lease.status == 409
            assert no_lease_payload['code'] == 'CONTROL_LEASE_REQUIRED'
            assert commands.calls == []

            acquired = await client.post(
                '/api/v1/control/acquire',
                headers=_headers(),
                json={'clientId': 'laptop-a'},
            )
            assert acquired.status == 200

            start = await client.post(
                '/api/v1/mission/start',
                headers=_headers(),
                json={
                    'clientId': 'laptop-a',
                    'clientRequestId': 'req-3',
                    'missionId': 'inspection_001',
                    'missionVersion': 'v1',
                },
            )
            assert start.status == 202
            assert commands.calls == [('START', ('inspection_001', 'v1', ''))]
        finally:
            await client.close()

    asyncio.run(run())
