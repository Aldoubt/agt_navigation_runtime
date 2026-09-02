from __future__ import annotations

import json
from typing import Any

from aiohttp import web

from .command_guard import verify_bearer_token
from .commissioning_port import CommissioningPort
from .contract import GATEWAY_API_VERSION


_PUBLIC_KEY_MAP = {
    'site_id': 'siteId',
    'run_id': 'runId',
    'projection_backend': 'projectionBackend',
    'site_root': 'siteRoot',
}


def _error(status: int, code: str, message: str) -> web.Response:
    return web.json_response(
        {'apiVersion': GATEWAY_API_VERSION, 'code': code, 'message': message},
        status=status,
    )


def _public_payload(payload: dict[str, Any]) -> dict[str, Any]:
    """Translate filesystem/service naming into the browser Gateway contract."""
    return {
        _PUBLIC_KEY_MAP.get(key, key): value
        for key, value in payload.items()
    }


def _with_api(payload: dict[str, Any]) -> dict[str, Any]:
    return {'apiVersion': GATEWAY_API_VERSION, **_public_payload(payload)}


def _map_payload(payload: dict[str, Any]) -> dict[str, Any]:
    return _with_api({**payload, 'imageUrl': '/api/v1/commissioning/map/image'})


def register_commissioning_routes(
    app: web.Application,
    *,
    commissioning: CommissioningPort | None,
    write_api_enabled: bool,
    command_token: str,
) -> None:
    def available() -> CommissioningPort:
        if commissioning is None:
            raise RuntimeError('commissioning adapter is unavailable')
        return commissioning

    def authorized(request: web.Request) -> web.Response | None:
        if not write_api_enabled or not command_token:
            return _error(403, 'WRITE_API_DISABLED', 'commissioning write API is disabled')
        if not verify_bearer_token(request.headers.get('Authorization'), command_token):
            return _error(401, 'UNAUTHORIZED', 'invalid command authorization')
        return None

    async def body(request: web.Request) -> dict[str, Any]:
        try:
            payload = await request.json()
        except (json.JSONDecodeError, ValueError) as exc:
            raise ValueError(f'invalid JSON body: {exc}') from exc
        if not isinstance(payload, dict):
            raise ValueError('request body must be a JSON object')
        return payload

    async def status(_request: web.Request) -> web.Response:
        try:
            return web.json_response(_with_api(available().status()))
        except RuntimeError as exc:
            return _error(503, 'COMMISSIONING_UNAVAILABLE', str(exc))

    async def map_descriptor(_request: web.Request) -> web.Response:
        try:
            return web.json_response(_map_payload(available().map_descriptor()))
        except RuntimeError as exc:
            if commissioning is None:
                return _error(503, 'COMMISSIONING_UNAVAILABLE', str(exc))
            return _error(409, 'MAP_NOT_READY', str(exc))

    async def map_image(_request: web.Request) -> web.Response:
        try:
            return web.Response(
                body=available().map_bytes(),
                content_type='image/x-portable-graymap',
            )
        except RuntimeError as exc:
            if commissioning is None:
                return _error(503, 'COMMISSIONING_UNAVAILABLE', str(exc))
            return _error(409, 'MAP_NOT_READY', str(exc))

    async def project(request: web.Request) -> web.Response:
        denial = authorized(request)
        if denial is not None:
            return denial
        try:
            payload = await body(request)
            return web.json_response(_map_payload(available().project(payload)))
        except ValueError as exc:
            return _error(400, 'INVALID_PROJECTION_REQUEST', str(exc))
        except RuntimeError as exc:
            return _error(409, 'PROJECTION_FAILED', str(exc))

    async def edit(request: web.Request) -> web.Response:
        denial = authorized(request)
        if denial is not None:
            return denial
        try:
            payload = await body(request)
            kind = payload.get('kind')
            cells = payload.get('cells')
            if kind not in {'erase_to_free', 'paint_occupied'}:
                raise ValueError('kind must be erase_to_free or paint_occupied')
            if not isinstance(cells, list) or not all(isinstance(cell, int) and not isinstance(cell, bool) for cell in cells):
                raise ValueError('cells must be an integer array')
            return web.json_response(_map_payload(available().edit(kind, cells)))
        except ValueError as exc:
            return _error(400, 'INVALID_MAP_EDIT', str(exc))
        except RuntimeError as exc:
            return _error(409, 'MAP_EDIT_FAILED', str(exc))

    def history_handler(operation: str):
        async def handler(request: web.Request) -> web.Response:
            denial = authorized(request)
            if denial is not None:
                return denial
            try:
                port = available()
                result = getattr(port, operation)()
                return web.json_response(_map_payload(result))
            except RuntimeError as exc:
                return _error(409, 'MAP_EDIT_FAILED', str(exc))
        return handler

    async def save(request: web.Request) -> web.Response:
        denial = authorized(request)
        if denial is not None:
            return denial
        try:
            payload = await body(request)
            revision = payload.get('revision')
            if not isinstance(revision, str) or not revision.strip():
                raise ValueError('revision must be a non-empty string')
            result = available().save(revision.strip())
            return web.json_response(_with_api({**result, 'state': 'SAVED'}))
        except ValueError as exc:
            return _error(400, 'INVALID_SITE_REVISION', str(exc))
        except RuntimeError as exc:
            return _error(409, 'SITE_SAVE_FAILED', str(exc))

    async def activate(request: web.Request) -> web.Response:
        denial = authorized(request)
        if denial is not None:
            return denial
        try:
            payload = await body(request)
            revision = payload.get('revision')
            if not isinstance(revision, str) or not revision.strip():
                raise ValueError('revision must be a non-empty string')
            result = available().activate(revision.strip())
            return web.json_response(_with_api({**result, 'state': 'ACTIVE'}))
        except ValueError as exc:
            return _error(400, 'INVALID_SITE_REVISION', str(exc))
        except RuntimeError as exc:
            return _error(409, 'SITE_ACTIVATION_FAILED', str(exc))

    app.router.add_get('/api/v1/commissioning/status', status)
    app.router.add_get('/api/v1/commissioning/map', map_descriptor)
    app.router.add_get('/api/v1/commissioning/map/image', map_image)
    app.router.add_post('/api/v1/commissioning/project', project)
    app.router.add_post('/api/v1/commissioning/map/edit', edit)
    app.router.add_post('/api/v1/commissioning/map/undo', history_handler('undo'))
    app.router.add_post('/api/v1/commissioning/map/redo', history_handler('redo'))
    app.router.add_post('/api/v1/commissioning/map/reset', history_handler('reset'))
    app.router.add_post('/api/v1/commissioning/map/save', save)
    app.router.add_post('/api/v1/commissioning/map/activate', activate)
