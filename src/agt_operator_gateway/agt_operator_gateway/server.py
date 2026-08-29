from __future__ import annotations

import asyncio
from datetime import datetime, timezone
from time import time
from typing import Callable

from aiohttp import WSMsgType, web

from .contract import GATEWAY_API_VERSION, GATEWAY_STREAM_SCHEMA, build_capabilities
from .state_store import GatewayRuntimeSnapshot, GatewayStateStore


def _utc_timestamp() -> str:
    return datetime.now(timezone.utc).isoformat().replace('+00:00', 'Z')


def create_app(
    store: GatewayStateStore,
    *,
    started_at_ms: int | None = None,
    now_ms: Callable[[], int] | None = None,
    stream_poll_s: float = 0.05,
    offline_after_ms: int = 5000,
) -> web.Application:
    if stream_poll_s <= 0.0:
        raise ValueError('stream_poll_s must be > 0')
    if offline_after_ms <= 0:
        raise ValueError('offline_after_ms must be > 0')

    clock = now_ms or (lambda: int(time() * 1000))
    started = int(clock() if started_at_ms is None else started_at_ms)
    app = web.Application()

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
