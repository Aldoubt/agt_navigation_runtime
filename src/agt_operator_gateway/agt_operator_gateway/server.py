from __future__ import annotations

import asyncio
from datetime import datetime, timezone
from time import time
from typing import Callable, Iterable

from aiohttp import WSMsgType, web

from .contract import GATEWAY_API_VERSION, GATEWAY_STREAM_SCHEMA, build_capabilities
from .state_store import GatewayRuntimeSnapshot, GatewayStateStore


def _utc_timestamp() -> str:
    return datetime.now(timezone.utc).isoformat().replace('+00:00', 'Z')


def _normalize_allowed_origins(values: Iterable[str]) -> tuple[str, ...]:
    normalized = tuple(dict.fromkeys(str(value).strip() for value in values if str(value).strip()))
    return normalized


def create_app(
    store: GatewayStateStore,
    *,
    started_at_ms: int | None = None,
    now_ms: Callable[[], int] | None = None,
    stream_poll_s: float = 0.05,
    offline_after_ms: int = 5000,
    allowed_origins: Iterable[str] = ('*',),
) -> web.Application:
    if stream_poll_s <= 0.0:
        raise ValueError('stream_poll_s must be > 0')
    if offline_after_ms <= 0:
        raise ValueError('offline_after_ms must be > 0')

    origins = _normalize_allowed_origins(allowed_origins)
    allow_all_origins = '*' in origins
    clock = now_ms or (lambda: int(time() * 1000))
    started = int(clock() if started_at_ms is None else started_at_ms)

    @web.middleware
    async def origin_guard(request: web.Request, handler):
        origin = request.headers.get('Origin')
        if origin and not allow_all_origins and origin not in origins:
            raise web.HTTPForbidden(text='CORS_ORIGIN_DENIED', content_type='text/plain')
        return await handler(request)

    async def add_cors_headers(request: web.Request, response: web.StreamResponse) -> None:
        origin = request.headers.get('Origin')
        if not origin:
            return
        if allow_all_origins:
            response.headers['Access-Control-Allow-Origin'] = '*'
        elif origin in origins:
            response.headers['Access-Control-Allow-Origin'] = origin
            response.headers['Vary'] = 'Origin'

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
                incoming = await asyncio.wait_for(ws.receive(), timeout=stream_poll_s)
            except asyncio.TimeoutError:
                continue

            if incoming.type in (WSMsgType.CLOSE, WSMsgType.CLOSED, WSMsgType.ERROR):
                break

        return ws

    app.router.add_get('/api/v1/health', health)
    app.router.add_get('/api/v1/capabilities', capabilities)
    app.router.add_get('/api/v1/robot', robot)
    app.router.add_get('/api/v1/mission', mission)
    app.router.add_get('/api/v1/stream', stream)
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
