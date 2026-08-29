import asyncio
import json

from aiohttp.test_utils import TestClient, TestServer

from agt_operator_gateway.server import create_app
from agt_operator_gateway.state_store import GatewayStateStore


def example_payload():
    return {
        'robot_snapshot': {
            'identity': {'id': 'agt-01', 'name': 'BUNKER'},
            'timestampMs': 1000,
        },
        'navigation': {
            'map': None,
            'robotPose': {'x': 1.0, 'y': 2.0, 'yawRad': 0.5},
            'globalPath': [],
            'localTrajectory': [],
            'localObstacles': [],
            'robotFootprint': [],
            'terrainProfile': [],
            'pointCloud': None,
        },
        'mission': {
            'id': '__none__',
            'name': 'No active mission',
            'state': 'READY',
            'currentStep': 0,
            'totalSteps': 0,
            'progress': 0.0,
            'route': [],
            'loop': {'enabled': False, 'count': 1},
        },
    }


async def with_client(store, scenario):
    app = create_app(
        store,
        started_at_ms=500,
        now_ms=lambda: 1000,
        stream_poll_s=0.01,
    )
    server = TestServer(app)
    client = TestClient(server)
    await client.start_server()
    try:
        await scenario(client)
    finally:
        await client.close()


def test_health_and_capabilities_are_available_before_runtime():
    async def scenario(client):
        health_response = await client.get('/api/v1/health')
        assert health_response.status == 200
        health = await health_response.json()
        assert health['apiVersion'] == 'agt.operator.gateway/v1'
        assert health['gateway']['state'] == 'WARN'
        assert health['runtime'] == {
            'connected': False,
            'adapter': 'agt_system_manager',
        }

        capabilities_response = await client.get('/api/v1/capabilities')
        assert capabilities_response.status == 200
        capabilities = await capabilities_response.json()
        assert capabilities['apiVersion'] == 'agt.operator.gateway/v1'
        assert capabilities['capabilities']['missionEdit'] is False

    asyncio.run(with_client(GatewayStateStore(now_ms=lambda: 1000), scenario))


def test_robot_and_mission_are_503_until_runtime_snapshot_exists():
    async def scenario(client):
        assert (await client.get('/api/v1/robot')).status == 503
        assert (await client.get('/api/v1/mission')).status == 503

    asyncio.run(with_client(GatewayStateStore(now_ms=lambda: 1000), scenario))


def test_robot_and_mission_hydrate_from_store():
    store = GatewayStateStore(now_ms=lambda: 1000)
    store.update(**example_payload(), source_revision=7, received_at_ms=1000)

    async def scenario(client):
        robot_response = await client.get('/api/v1/robot')
        assert robot_response.status == 200
        robot = await robot_response.json()
        assert robot['apiVersion'] == 'agt.operator.gateway/v1'
        assert robot['snapshot']['identity']['id'] == 'agt-01'
        assert robot['navigation']['robotPose']['x'] == 1.0

        mission_response = await client.get('/api/v1/mission')
        assert mission_response.status == 200
        mission = await mission_response.json()
        assert mission['mission']['id'] == '__none__'

    asyncio.run(with_client(store, scenario))


def test_stale_runtime_is_not_served_as_live_robot_state():
    now = [1000]
    store = GatewayStateStore(freshness_ms=1500, now_ms=lambda: now[0])
    store.update(**example_payload(), source_revision=7, received_at_ms=1000)
    now[0] = 2600

    async def run():
        app = create_app(
            store,
            started_at_ms=500,
            now_ms=lambda: now[0],
            stream_poll_s=0.01,
        )
        server = TestServer(app)
        client = TestClient(server)
        await client.start_server()
        try:
            assert (await client.get('/api/v1/robot')).status == 503
            health = await (await client.get('/api/v1/health')).json()
            assert health['runtime']['connected'] is False
        finally:
            await client.close()

    asyncio.run(run())


def test_websocket_emits_versioned_projection_envelopes_for_new_revision():
    store = GatewayStateStore(now_ms=lambda: 1000)
    store.update(**example_payload(), source_revision=7, received_at_ms=1000)

    async def scenario(client):
        ws = await client.ws_connect('/api/v1/stream')
        messages = []
        for _ in range(3):
            message = await asyncio.wait_for(ws.receive(), timeout=1.0)
            assert message.type.name == 'TEXT'
            messages.append(json.loads(message.data))
        assert [message['type'] for message in messages] == [
            'robot_snapshot',
            'navigation_pose',
            'mission_view',
        ]
        assert [message['seq'] for message in messages] == [1, 2, 3]
        assert all(
            message['schema'] == 'agt.operator.stream/v1' for message in messages
        )
        assert messages[1]['payload'] == {'x': 1.0, 'y': 2.0, 'yawRad': 0.5}
        await ws.close()

    asyncio.run(with_client(store, scenario))
