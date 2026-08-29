import asyncio

from aiohttp.test_utils import TestClient, TestServer

from agt_operator_gateway.server import create_app
from agt_operator_gateway.state_store import GatewayStateStore


def _store() -> GatewayStateStore:
    store = GatewayStateStore(now_ms=lambda: 1000)
    store.update(
        robot_snapshot={'identity': {'id': 'agt-01'}},
        navigation={'robotPose': {'x': 0.0, 'y': 0.0, 'yawRad': 0.0}},
        mission={'id': '__none__'},
        received_at_ms=1000,
    )
    return store


def test_default_readonly_p0_cors_allows_cross_origin_browser_get() -> None:
    async def run() -> None:
        server = TestServer(create_app(_store(), now_ms=lambda: 1000))
        client = TestClient(server)
        await client.start_server()
        try:
            response = await client.get(
                '/api/v1/robot',
                headers={'Origin': 'http://operator-laptop.local:5173'},
            )
            assert response.status == 200
            assert response.headers['Access-Control-Allow-Origin'] == '*'
            assert 'Access-Control-Allow-Credentials' not in response.headers
        finally:
            await client.close()

    asyncio.run(run())


def test_restricted_cors_echoes_allowed_origin_and_rejects_other_origin() -> None:
    async def run() -> None:
        app = create_app(
            _store(),
            now_ms=lambda: 1000,
            allowed_origins=('http://agt-operator.local:8080',),
        )
        server = TestServer(app)
        client = TestClient(server)
        await client.start_server()
        try:
            allowed = await client.get(
                '/api/v1/health',
                headers={'Origin': 'http://agt-operator.local:8080'},
            )
            assert allowed.status == 200
            assert allowed.headers['Access-Control-Allow-Origin'] == 'http://agt-operator.local:8080'
            assert allowed.headers['Vary'] == 'Origin'

            rejected = await client.get(
                '/api/v1/health',
                headers={'Origin': 'http://unexpected.local:9999'},
            )
            assert rejected.status == 403
        finally:
            await client.close()

    asyncio.run(run())


def test_same_origin_request_without_origin_header_remains_allowed() -> None:
    async def run() -> None:
        app = create_app(
            _store(),
            now_ms=lambda: 1000,
            allowed_origins=('http://agt-operator.local:8080',),
        )
        server = TestServer(app)
        client = TestClient(server)
        await client.start_server()
        try:
            response = await client.get('/api/v1/health')
            assert response.status == 200
            assert 'Access-Control-Allow-Origin' not in response.headers
        finally:
            await client.close()

    asyncio.run(run())
