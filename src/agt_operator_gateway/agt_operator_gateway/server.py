from __future__ import annotations

import asyncio
from datetime import datetime, timezone
import json
from time import time
from typing import Any, Callable, Iterable

from aiohttp import WSMsgType, web

from .command_guard import (
    CommandReplayStore,
    ReplayKind,
    canonical_fingerprint,
    verify_bearer_token,
)
from .contract import GATEWAY_API_VERSION, GATEWAY_STREAM_SCHEMA, build_capabilities
from .mission_commands import MissionCommandPort, MissionCommandResult
from .state_store import GatewayRuntimeSnapshot, GatewayStateStore


def _utc_timestamp() -> str:
    return datetime.now(timezone.utc).isoformat().replace('+00:00', 'Z')


def _normalize_allowed_origins(values: Iterable[str]) -> tuple[str, ...]:
    return tuple(
        dict.fromkeys(str(value).strip() for value in values if str(value).strip())
    )


def _json_error(
    status: int,
    code: str,
    message: str,
    *,
    client_request_id: str = '',
) -> web.Response:
    return web.json_response(
        {
            'apiVersion': GATEWAY_API_VERSION,
            'code': code,
            'message': message,
            'clientRequestId': client_request_id,
        },
        status=status,
    )


def _required_string(
    payload: dict[str, Any],
    key: str,
    *,
    maximum_length: int = 256,
) -> str:
    value = payload.get(key)
    if not isinstance(value, str) or not value.strip():
        raise ValueError(f'{key} must be a non-empty string')
    normalized = value.strip()
    if len(normalized) > maximum_length:
        raise ValueError(f'{key} exceeds maximum length {maximum_length}')
    return normalized


def _optional_string(
    payload: dict[str, Any],
    key: str,
    *,
    maximum_length: int = 256,
) -> str:
    value = payload.get(key, '')
    if value is None:
        return ''
    if not isinstance(value, str):
        raise ValueError(f'{key} must be a string')
    normalized = value.strip()
    if len(normalized) > maximum_length:
        raise ValueError(f'{key} exceeds maximum length {maximum_length}')
    return normalized


def _command_http_result(
    *,
    command: str,
    client_request_id: str,
    mission_id: str,
    result: MissionCommandResult,
) -> tuple[int, dict[str, Any]]:
    if result.timed_out:
        status = 504
        state = 'REJECTED'
    elif result.unavailable:
        status = 503
        state = 'REJECTED'
    elif result.accepted:
        status = 202 if command == 'START' else 200
        state = 'ACCEPTED'
    else:
        status = 409
        state = 'REJECTED'
    return status, {
        'apiVersion': GATEWAY_API_VERSION,
        'clientRequestId': client_request_id,
        'command': command,
        'state': state,
        'missionId': mission_id,
        'errorCode': int(result.error_code),
        'message': str(result.message),
    }


def create_app(
    store: GatewayStateStore,
    *,
    started_at_ms: int | None = None,
    now_ms: Callable[[], int] | None = None,
    stream_poll_s: float = 0.05,
    offline_after_ms: int = 5000,
    allowed_origins: Iterable[str] = ('*',),
    mission_commands: MissionCommandPort | None = None,
    write_api_enabled: bool = False,
    command_token: str = '',
    command_replay_store: CommandReplayStore | None = None,
) -> web.Application:
    if stream_poll_s <= 0.0:
        raise ValueError('stream_poll_s must be > 0')
    if offline_after_ms <= 0:
        raise ValueError('offline_after_ms must be > 0')

    origins = _normalize_allowed_origins(allowed_origins)
    allow_all_origins = '*' in origins
    clock = now_ms or (lambda: int(time() * 1000))
    started = int(clock() if started_at_ms is None else started_at_ms)
    replay_store = command_replay_store or CommandReplayStore(now_ms=clock)
    command_token = str(command_token)

    @web.middleware
    async def origin_guard(request: web.Request, handler):
        origin = request.headers.get('Origin')
        if origin and not allow_all_origins and origin not in origins:
            raise web.HTTPForbidden(text='CORS_ORIGIN_DENIED', content_type='text/plain')
        return await handler(request)

    async def add_cors_headers(
        request: web.Request,
        response: web.StreamResponse,
    ) -> None:
        origin = request.headers.get('Origin')
        if not origin:
            return
        if allow_all_origins:
            response.headers['Access-Control-Allow-Origin'] = '*'
        elif origin in origins:
            response.headers['Access-Control-Allow-Origin'] = origin
            response.headers['Vary'] = 'Origin'
        response.headers['Access-Control-Allow-Methods'] = 'GET, POST, OPTIONS'
        response.headers['Access-Control-Allow-Headers'] = 'Authorization, Content-Type'

    app = web.Application(middlewares=[origin_guard])
    app.on_response_prepare.append(add_cors_headers)

    def require_fresh_snapshot() -> GatewayRuntimeSnapshot:
        snapshot = store.snapshot()
        if snapshot is None or not store.is_runtime_connected(clock()):
            raise web.HTTPServiceUnavailable(
                text='RUNTIME_STATE_UNAVAILABLE',
                content_type='text/plain',
            )
        return snapshot

    async def health(_request: web.Request) -> web.Response:
        connected = store.is_runtime_connected(clock())
        return web.json_response({
            'apiVersion': GATEWAY_API_VERSION,
            'timestampMs': int(clock()),
            'gateway': {
                'state': 'OK' if connected else 'WARN',
                'startedAtMs': started,
            },
            'runtime': {
                'connected': connected,
                'adapter': 'agt_system_manager',
            },
        })

    async def capabilities(_request: web.Request) -> web.Response:
        return web.json_response({
            'apiVersion': GATEWAY_API_VERSION,
            'capabilities': build_capabilities(),
        })

    async def robot(_request: web.Request) -> web.Response:
        snapshot = require_fresh_snapshot()
        return web.json_response({
            'apiVersion': GATEWAY_API_VERSION,
            'snapshot': snapshot.robot_snapshot,
            'navigation': snapshot.navigation,
        })

    async def mission(_request: web.Request) -> web.Response:
        snapshot = require_fresh_snapshot()
        return web.json_response({
            'apiVersion': GATEWAY_API_VERSION,
            'mission': snapshot.mission,
        })

    async def command_options(_request: web.Request) -> web.Response:
        return web.Response(status=204)

    async def mission_command(request: web.Request) -> web.Response:
        command = request.match_info['command'].upper()
        if command not in {'START', 'PAUSE', 'RESUME', 'CANCEL'}:
            return _json_error(404, 'UNKNOWN_COMMAND', 'unknown mission command')
        if not write_api_enabled or not command_token:
            return _json_error(
                403,
                'WRITE_API_DISABLED',
                'mission write API is disabled',
            )
        if mission_commands is None:
            return _json_error(
                503,
                'COMMAND_ADAPTER_UNAVAILABLE',
                'mission command adapter is unavailable',
            )
        if not verify_bearer_token(
            request.headers.get('Authorization'),
            command_token,
        ):
            return _json_error(401, 'UNAUTHORIZED', 'invalid command authorization')

        try:
            raw = await request.json()
            if not isinstance(raw, dict):
                raise ValueError('request body must be a JSON object')
            client_request_id = _required_string(
                raw,
                'clientRequestId',
                maximum_length=128,
            )
            mission_id = _required_string(raw, 'missionId')
            if command == 'START':
                mission_version = _required_string(raw, 'missionVersion')
                expected_hash = _optional_string(raw, 'expectedContentSha256', maximum_length=512)
                fingerprint_payload = {
                    'missionId': mission_id,
                    'missionVersion': mission_version,
                    'expectedContentSha256': expected_hash,
                }
            else:
                mission_version = ''
                expected_hash = ''
                fingerprint_payload = {'missionId': mission_id}
        except (ValueError, TypeError, json.JSONDecodeError) as exc:
            return _json_error(
                400,
                'INVALID_COMMAND_REQUEST',
                str(exc),
            )

        try:
            snapshot = require_fresh_snapshot()
        except web.HTTPServiceUnavailable:
            return _json_error(
                503,
                'RUNTIME_STATE_UNAVAILABLE',
                'fresh Runtime state is unavailable',
                client_request_id=client_request_id,
            )

        if command == 'CANCEL':
            active_mission_id = str(snapshot.mission.get('id', '') or '')
            if active_mission_id != mission_id:
                return _json_error(
                    409,
                    'ACTIVE_MISSION_MISMATCH',
                    'requested mission does not match the active Runtime mission',
                    client_request_id=client_request_id,
                )

        fingerprint = canonical_fingerprint(command, fingerprint_payload)
        replay = replay_store.begin(client_request_id, fingerprint)
        if replay.kind is ReplayKind.CONFLICT:
            return _json_error(
                409,
                'IDEMPOTENCY_CONFLICT',
                'clientRequestId was already used for a different command payload',
                client_request_id=client_request_id,
            )
        if replay.kind is ReplayKind.CAPACITY:
            return _json_error(
                503,
                'IDEMPOTENCY_CAPACITY',
                'command replay cache is full with in-flight requests',
                client_request_id=client_request_id,
            )
        if replay.kind is ReplayKind.IN_PROGRESS:
            return web.json_response(
                {
                    'apiVersion': GATEWAY_API_VERSION,
                    'clientRequestId': client_request_id,
                    'command': command,
                    'state': 'IN_PROGRESS',
                    'missionId': mission_id,
                    'errorCode': 0,
                    'message': 'matching request is already in progress',
                },
                status=202,
            )
        if replay.kind is ReplayKind.REPLAY:
            return web.json_response(
                replay.payload or {},
                status=int(replay.status_code or 200),
            )

        try:
            if command == 'START':
                result = await asyncio.to_thread(
                    mission_commands.start,
                    mission_id,
                    mission_version,
                    expected_hash,
                )
            elif command == 'PAUSE':
                result = await asyncio.to_thread(mission_commands.pause, mission_id)
            elif command == 'RESUME':
                result = await asyncio.to_thread(mission_commands.resume, mission_id)
            else:
                result = await asyncio.to_thread(mission_commands.cancel, mission_id)
        except Exception as exc:
            result = MissionCommandResult.unavailable_result(
                f'mission command adapter failed: {exc}'
            )

        status_code, response_payload = _command_http_result(
            command=command,
            client_request_id=client_request_id,
            mission_id=mission_id,
            result=result,
        )
        replay_store.complete(
            client_request_id,
            fingerprint,
            status_code=status_code,
            payload=response_payload,
        )
        return web.json_response(response_payload, status=status_code)

    async def stream(request: web.Request) -> web.StreamResponse:
        require_fresh_snapshot()
        ws = web.WebSocketResponse(autoping=True)
        await ws.prepare(request)
        last_revision = 0
        seq = 0

        while not ws.closed:
            now = int(clock())
            snapshot = store.snapshot()
            age = store.age_ms(now)

            if snapshot is not None and store.is_runtime_connected(now):
                if snapshot.gateway_revision != last_revision:
                    envelopes = (
                        ('robot_snapshot', snapshot.robot_snapshot),
                        ('navigation_pose', snapshot.navigation['robotPose']),
                        ('mission_view', snapshot.mission),
                    )
                    for event_type, payload in envelopes:
                        seq += 1
                        await ws.send_json({
                            'schema': GATEWAY_STREAM_SCHEMA,
                            'seq': seq,
                            'timestamp': _utc_timestamp(),
                            'type': event_type,
                            'payload': payload,
                        })
                    last_revision = snapshot.gateway_revision
            elif age is not None and age >= offline_after_ms:
                await ws.close(code=1011, message=b'RUNTIME_STATE_EXPIRED')
                break

            try:
                incoming = await asyncio.wait_for(
                    ws.receive(),
                    timeout=stream_poll_s,
                )
            except asyncio.TimeoutError:
                continue

            if incoming.type in (
                WSMsgType.CLOSE,
                WSMsgType.CLOSED,
                WSMsgType.ERROR,
            ):
                break

        return ws

    app.router.add_get('/api/v1/health', health)
    app.router.add_get('/api/v1/capabilities', capabilities)
    app.router.add_get('/api/v1/robot', robot)
    app.router.add_get('/api/v1/mission', mission)
    app.router.add_get('/api/v1/stream', stream)
    for command_name in ('start', 'pause', 'resume', 'cancel'):
        path = f'/api/v1/mission/{command_name}'
        app.router.add_post(path, mission_command)
        app.router.add_options(path, command_options)
    return app


class GatewayHttpServer:
    def __init__(
        self,
        store: GatewayStateStore,
        *,
        host: str = '0.0.0.0',
        port: int = 8765,
        stream_poll_s: float = 0.05,
        offline_after_ms: int = 5000,
        allowed_origins: Iterable[str] = ('*',),
        mission_commands: MissionCommandPort | None = None,
        write_api_enabled: bool = False,
        command_token: str = '',
        command_replay_store: CommandReplayStore | None = None,
    ) -> None:
        from threading import Event, Thread

        if not host:
            raise ValueError('host must not be empty')
        if port <= 0 or port > 65535:
            raise ValueError('port must be in 1..65535')
        self._store = store
        self._host = host
        self._port = int(port)
        self._stream_poll_s = float(stream_poll_s)
        self._offline_after_ms = int(offline_after_ms)
        self._allowed_origins = _normalize_allowed_origins(allowed_origins)
        self._mission_commands = mission_commands
        self._write_api_enabled = bool(write_api_enabled)
        self._command_token = str(command_token)
        self._command_replay_store = command_replay_store
        self._stop_event = Event()
        self._started_event = Event()
        self._thread = Thread(
            target=self._thread_main,
            name='agt-operator-gateway-http',
            daemon=True,
        )
        self._startup_error: BaseException | None = None

    def start(self, timeout_s: float = 5.0) -> None:
        if self._thread.is_alive():
            return
        self._thread.start()
        if not self._started_event.wait(timeout_s):
            raise RuntimeError('operator gateway HTTP server startup timed out')
        if self._startup_error is not None:
            raise RuntimeError(
                f'operator gateway HTTP server failed: {self._startup_error}'
            ) from self._startup_error

    def stop(self, timeout_s: float = 3.0) -> None:
        self._stop_event.set()
        if self._thread.is_alive():
            self._thread.join(timeout_s)

    def _thread_main(self) -> None:
        try:
            asyncio.run(self._serve())
        except BaseException as exc:
            self._startup_error = exc
            self._started_event.set()

    async def _serve(self) -> None:
        runner = web.AppRunner(
            create_app(
                self._store,
                stream_poll_s=self._stream_poll_s,
                offline_after_ms=self._offline_after_ms,
                allowed_origins=self._allowed_origins,
                mission_commands=self._mission_commands,
                write_api_enabled=self._write_api_enabled,
                command_token=self._command_token,
                command_replay_store=self._command_replay_store,
            )
        )
        await runner.setup()
        try:
            site = web.TCPSite(runner, self._host, self._port)
            await site.start()
            self._started_event.set()
            while not self._stop_event.is_set():
                await asyncio.sleep(0.1)
        finally:
            await runner.cleanup()
