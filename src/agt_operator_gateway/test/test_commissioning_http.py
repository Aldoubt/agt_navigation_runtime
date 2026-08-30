from __future__ import annotations

import asyncio

from aiohttp.test_utils import TestClient, TestServer

from agt_operator_gateway.server import create_app
from agt_operator_gateway.state_store import GatewayStateStore


class FakeCommissioningPort:
    def __init__(self) -> None:
        self.calls = []
        self.revision = 0

    def status(self):
        return {'site_id': 'slope', 'run_id': 'run01', 'state': 'MAP_READY'}

    def map_descriptor(self):
        return {
            'site_id': 'slope', 'run_id': 'run01', 'revision': self.revision,
            'width': 3, 'height': 2, 'resolution': 0.1, 'origin': [1.0, 2.0, 0.0],
        }

    def map_bytes(self):
        return b'P5\n3 2\n255\n' + bytes([0, 205, 254, 254, 205, 0])

    def project(self, options):
        self.calls.append(('project', options))
        return self.map_descriptor()

    def edit(self, kind, cells):
        self.calls.append(('edit', kind, tuple(cells)))
        self.revision += 1
        return self.map_descriptor()

    def undo(self):
        self.calls.append(('undo',))
        self.revision = max(0, self.revision - 1)
        return self.map_descriptor()

    def redo(self):
        self.calls.append(('redo',))
        self.revision += 1
        return self.map_descriptor()

    def reset(self):
        self.calls.append(('reset',))
        self.revision = 0
        return self.map_descriptor()

    def save(self, revision):
        self.calls.append(('save', revision))
        return {'site_id': 'slope', 'revision': revision, 'validated': True}

    def activate(self, revision):
        self.calls.append(('activate', revision))
        return {'site_id': 'slope', 'revision': revision}


def _store():
    store = GatewayStateStore(now_ms=lambda: 1000)
    store.update(
        robot_snapshot={'identity': {'id': 'agt-01'}},
        navigation={'robotPose': {'x': 0.0, 'y': 0.0, 'yawRad': 0.0}},
        mission={'id': '', 'name': '', 'state': 'IDLE', 'currentStep': 0, 'totalSteps': 0,
                 'progress': 0.0, 'route': [], 'loop': {'enabled': False, 'count': 1}},
        received_at_ms=1000,
    )
    return store


async def _client(port, *, write_api_enabled=True, token='secret'):
    app = create_app(
        _store(), now_ms=lambda: 1000,
        commissioning=port,
        write_api_enabled=write_api_enabled,
        command_token=token,
    )
    client = TestClient(TestServer(app))
    await client.start_server()
    return client


def test_commissioning_reads_and_binary_map() -> None:
    async def run():
        client = await _client(FakeCommissioningPort())
        try:
            response = await client.get('/api/v1/commissioning/status')
            assert response.status == 200
            assert (await response.json())['state'] == 'MAP_READY'

            response = await client.get('/api/v1/commissioning/map')
            payload = await response.json()
            assert response.status == 200
            assert payload['apiVersion'] == 'agt.operator.gateway/v1'
            assert payload['imageUrl'] == '/api/v1/commissioning/map/image'
            assert payload['width'] == 3

            response = await client.get('/api/v1/commissioning/map/image')
            assert response.status == 200
            assert response.headers['Content-Type'].startswith('image/x-portable-graymap')
            assert (await response.read()).startswith(b'P5')
        finally:
            await client.close()
    asyncio.run(run())


def test_commissioning_writes_require_existing_write_guard_and_validate_edit() -> None:
    async def run():
        port = FakeCommissioningPort()
        client = await _client(port)
        try:
            response = await client.post('/api/v1/commissioning/map/edit', json={
                'kind': 'erase_to_free', 'cells': [0, 1]
            })
            assert response.status == 401
            assert port.calls == []

            headers = {'Authorization': 'Bearer secret'}
            response = await client.post('/api/v1/commissioning/map/edit', headers=headers, json={
                'kind': 'erase_to_free', 'cells': [0, 1]
            })
            assert response.status == 200
            assert port.calls[-1] == ('edit', 'erase_to_free', (0, 1))

            response = await client.post('/api/v1/commissioning/map/edit', headers=headers, json={
                'kind': 'bad', 'cells': [0]
            })
            assert response.status == 400
        finally:
            await client.close()
    asyncio.run(run())


def test_project_save_activate_and_history_routes() -> None:
    async def run():
        port = FakeCommissioningPort()
        client = await _client(port)
        headers = {'Authorization': 'Bearer secret'}
        try:
            response = await client.post('/api/v1/commissioning/project', headers=headers, json={
                'max_ground_angle_deg': 35.0
            })
            assert response.status == 200
            assert port.calls[-1][0] == 'project'

            for endpoint, expected in (
                ('undo', 'undo'), ('redo', 'redo'), ('reset', 'reset'),
            ):
                response = await client.post(f'/api/v1/commissioning/map/{endpoint}', headers=headers, json={})
                assert response.status == 200
                assert port.calls[-1][0] == expected

            response = await client.post('/api/v1/commissioning/map/save', headers=headers, json={'revision': 'r02'})
            payload = await response.json()
            assert response.status == 200
            assert payload['state'] == 'SAVED'
            assert payload['revision'] == 'r02'

            response = await client.post('/api/v1/commissioning/map/activate', headers=headers, json={'revision': 'r02'})
            payload = await response.json()
            assert response.status == 200
            assert payload['state'] == 'ACTIVE'
        finally:
            await client.close()
    asyncio.run(run())


def test_commissioning_unavailable_is_explicit() -> None:
    async def run():
        app = create_app(_store(), now_ms=lambda: 1000)
        client = TestClient(TestServer(app))
        await client.start_server()
        try:
            response = await client.get('/api/v1/commissioning/status')
            assert response.status == 503
            payload = await response.json()
            assert payload['code'] == 'COMMISSIONING_UNAVAILABLE'
        finally:
            await client.close()
    asyncio.run(run())
