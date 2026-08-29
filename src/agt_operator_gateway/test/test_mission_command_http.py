from __future__ import annotations

import asyncio
from threading import Event

from aiohttp.test_utils import TestClient, TestServer

from agt_operator_gateway.command_guard import CommandReplayStore
from agt_operator_gateway.mission_commands import MissionCommandResult
from agt_operator_gateway.server import create_app
from agt_operator_gateway.state_store import GatewayStateStore


class FakeMissionCommands:
    def __init__(self) -> None:
        self.calls: list[tuple[str, tuple[str, ...]]] = []
        self.result = MissionCommandResult.accepted_result('accepted')
        self.block_start: Event | None = None
        self.release_start: Event | None = None

    def start(self, mission_id: str, mission_version: str, expected_hash: str) -> MissionCommandResult:
        self.calls.append(('START', (mission_id, mission_version, expected_hash)))
        if self.block_start is not None:
            self.block_start.set()
        if self.release_start is not None:
            self.release_start.wait(timeout=2.0)
        return self.result

    def pause(self, mission_id: str) -> MissionCommandResult:
        self.calls.append(('PAUSE', (mission_id,)))
        return self.result

    def resume(self, mission_id: str) -> MissionCommandResult:
        self.calls.append(('RESUME', (mission_id,)))
        return self.result

    def cancel(self, mission_id: str) -> MissionCommandResult:
        self.calls.append(('CANCEL', (mission_id,)))
        return self.result


def _store(*, mission_id: str = 'inspection_001', mission_state: str = 'RUNNING') -> GatewayStateStore:
    store = GatewayStateStore(now_ms=lambda: 1000)
    store.update(
        robot_snapshot={'identity': {'id': 'agt-01'}},
        navigation={'robotPose': {'x': 0.0, 'y': 0.0, 'yawRad': 0.0}},
        mission={
            'id': mission_id,
            'name': mission_id,
            'state': mission_state,
            'currentStep': 1,
            'totalSteps': 3,
            'progress': 1 / 3,
            'route': [],
            'loop': {'enabled': False, 'count': 1},
        },
        received_at_ms=1000,
    )
    return store


def _headers(token: str = 'secret-token') -> dict[str, str]:
    return {
        'Authorization': f'Bearer {token}',
        'Content-Type': 'application/json',
        'Origin': 'http://operator.local:5173',
    }


def _start_body(request_id: str = 'req-start-1', mission_id: str = 'inspection_001') -> dict[str, str]:
    return {
        'clientRequestId': request_id,
        'missionId': mission_id,
        'missionVersion': 'v1',
        'expectedContentSha256': 'sha256:abc',
    }


async def _client(
    commands: FakeMissionCommands | None,
    *,
    store: GatewayStateStore | None = None,
    write_api_enabled: bool = True,
    token: str = 'secret-token',
) -> TestClient:
    app = create_app(
        store or _store(),
        now_ms=lambda: 1000,
        mission_commands=commands,
        write_api_enabled=write_api_enabled,
        command_token=token,
        command_replay_store=CommandReplayStore(now_ms=lambda: 1000, ttl_ms=60_000, max_entries=16),
        allowed_origins=('http://operator.local:5173',),
    )
    server = TestServer(app)
    client = TestClient(server)
    await client.start_server()
    return client


def test_write_api_is_disabled_by_default_even_if_a_command_port_exists() -> None:
    async def run() -> None:
        commands = FakeMissionCommands()
        app = create_app(_store(), now_ms=lambda: 1000, mission_commands=commands, command_token='secret-token')
        client = TestClient(TestServer(app))
        await client.start_server()
        try:
            response = await client.post('/api/v1/mission/start', headers=_headers(), json=_start_body())
            payload = await response.json()
            assert response.status == 403
            assert payload['code'] == 'WRITE_API_DISABLED'
            assert commands.calls == []
        finally:
            await client.close()

    asyncio.run(run())


def test_write_api_rejects_missing_or_invalid_bearer_token() -> None:
    async def run() -> None:
        commands = FakeMissionCommands()
        client = await _client(commands)
        try:
            missing = await client.post('/api/v1/mission/start', json=_start_body())
            invalid = await client.post('/api/v1/mission/start', headers=_headers('wrong'), json=_start_body('req-2'))
            assert missing.status == 401
            assert invalid.status == 401
            assert commands.calls == []
        finally:
            await client.close()

    asyncio.run(run())


def test_start_validates_required_nonempty_fields_before_dispatch() -> None:
    async def run() -> None:
        commands = FakeMissionCommands()
        client = await _client(commands)
        try:
            response = await client.post(
                '/api/v1/mission/start',
                headers=_headers(),
                json={'clientRequestId': 'req', 'missionId': '', 'missionVersion': 'v1'},
            )
            payload = await response.json()
            assert response.status == 400
            assert payload['code'] == 'INVALID_COMMAND_REQUEST'
            assert commands.calls == []
        finally:
            await client.close()

    asyncio.run(run())


def test_start_dispatches_once_and_exact_retry_replays_stored_result() -> None:
    async def run() -> None:
        commands = FakeMissionCommands()
        client = await _client(commands)
        try:
            first = await client.post('/api/v1/mission/start', headers=_headers(), json=_start_body())
            first_payload = await first.json()
            replay = await client.post('/api/v1/mission/start', headers=_headers(), json=_start_body())
            replay_payload = await replay.json()

            assert first.status == 202
            assert replay.status == 202
            assert first_payload == replay_payload
            assert first_payload['state'] == 'ACCEPTED'
            assert first_payload['command'] == 'START'
            assert commands.calls == [('START', ('inspection_001', 'v1', 'sha256:abc'))]
        finally:
            await client.close()

    asyncio.run(run())


def test_same_request_id_with_different_payload_is_conflict_without_second_dispatch() -> None:
    async def run() -> None:
        commands = FakeMissionCommands()
        client = await _client(commands)
        try:
            first = await client.post('/api/v1/mission/start', headers=_headers(), json=_start_body())
            conflicting = await client.post(
                '/api/v1/mission/start',
                headers=_headers(),
                json=_start_body(mission_id='inspection_002'),
            )
            payload = await conflicting.json()
            assert first.status == 202
            assert conflicting.status == 409
            assert payload['code'] == 'IDEMPOTENCY_CONFLICT'
            assert len(commands.calls) == 1
        finally:
            await client.close()

    asyncio.run(run())


def test_inflight_retry_returns_in_progress_without_second_dispatch() -> None:
    async def run() -> None:
        commands = FakeMissionCommands()
        commands.block_start = Event()
        commands.release_start = Event()
        client = await _client(commands)
        try:
            first_task = asyncio.create_task(
                client.post('/api/v1/mission/start', headers=_headers(), json=_start_body())
            )
            await asyncio.to_thread(commands.block_start.wait, 1.0)

            duplicate = await client.post('/api/v1/mission/start', headers=_headers(), json=_start_body())
            duplicate_payload = await duplicate.json()
            assert duplicate.status == 202
            assert duplicate_payload['state'] == 'IN_PROGRESS'
            assert len(commands.calls) == 1

            commands.release_start.set()
            first = await first_task
            assert first.status == 202
        finally:
            commands.release_start.set()
            await client.close()

    asyncio.run(run())


def test_pause_resume_map_command_results_and_runtime_failures_to_http_status() -> None:
    async def run() -> None:
        commands = FakeMissionCommands()
        client = await _client(commands)
        try:
            pause = await client.post(
                '/api/v1/mission/pause',
                headers=_headers(),
                json={'clientRequestId': 'pause-1', 'missionId': 'inspection_001'},
            )
            assert pause.status == 200

            commands.result = MissionCommandResult.rejected_result(17, 'runtime rejected')
            resume = await client.post(
                '/api/v1/mission/resume',
                headers=_headers(),
                json={'clientRequestId': 'resume-1', 'missionId': 'inspection_001'},
            )
            assert resume.status == 409

            commands.result = MissionCommandResult.unavailable_result('service unavailable')
            unavailable = await client.post(
                '/api/v1/mission/pause',
                headers=_headers(),
                json={'clientRequestId': 'pause-2', 'missionId': 'inspection_001'},
            )
            assert unavailable.status == 503

            commands.result = MissionCommandResult.timeout_result('runtime timeout')
            timeout = await client.post(
                '/api/v1/mission/resume',
                headers=_headers(),
                json={'clientRequestId': 'resume-2', 'missionId': 'inspection_001'},
            )
            assert timeout.status == 504
        finally:
            await client.close()

    asyncio.run(run())


def test_cancel_requires_fresh_authoritative_matching_mission_before_cancel_all_adapter() -> None:
    async def run() -> None:
        commands = FakeMissionCommands()
        client = await _client(commands, store=_store(mission_id='inspection_002'))
        try:
            mismatch = await client.post(
                '/api/v1/mission/cancel',
                headers=_headers(),
                json={'clientRequestId': 'cancel-wrong', 'missionId': 'inspection_001'},
            )
            payload = await mismatch.json()
            assert mismatch.status == 409
            assert payload['code'] == 'ACTIVE_MISSION_MISMATCH'
            assert commands.calls == []
        finally:
            await client.close()

        matching = FakeMissionCommands()
        client = await _client(matching, store=_store(mission_id='inspection_001'))
        try:
            response = await client.post(
                '/api/v1/mission/cancel',
                headers=_headers(),
                json={'clientRequestId': 'cancel-ok', 'missionId': 'inspection_001'},
            )
            assert response.status == 200
            assert matching.calls == [('CANCEL', ('inspection_001',))]
        finally:
            await client.close()

    asyncio.run(run())


def test_cors_preflight_allows_authorization_and_content_type_for_command_routes() -> None:
    async def run() -> None:
        client = await _client(FakeMissionCommands())
        try:
            response = await client.options(
                '/api/v1/mission/start',
                headers={
                    'Origin': 'http://operator.local:5173',
                    'Access-Control-Request-Method': 'POST',
                    'Access-Control-Request-Headers': 'authorization,content-type',
                },
            )
            assert response.status == 204
            assert response.headers['Access-Control-Allow-Origin'] == 'http://operator.local:5173'
            assert 'POST' in response.headers['Access-Control-Allow-Methods']
            allowed_headers = response.headers['Access-Control-Allow-Headers'].lower()
            assert 'authorization' in allowed_headers
            assert 'content-type' in allowed_headers
        finally:
            await client.close()

    asyncio.run(run())
