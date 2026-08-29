from agt_operator_gateway.state_store import GatewayStateStore


def payload(tag):
    return {
        'robot_snapshot': {'identity': {'id': tag}},
        'navigation': {'robotPose': {'x': 1.0, 'y': 2.0, 'yawRad': 0.0}},
        'mission': {'id': tag},
    }


def test_empty_store_is_disconnected_and_has_no_snapshot():
    store = GatewayStateStore(freshness_ms=1500, now_ms=lambda: 1000)
    assert store.snapshot() is None
    assert store.is_runtime_connected() is False
    assert store.age_ms() is None


def test_update_assigns_monotonic_gateway_revision():
    now = [1000]
    store = GatewayStateStore(freshness_ms=1500, now_ms=lambda: now[0])
    first = store.update(**payload('r1'), source_revision=10)
    now[0] = 1100
    second = store.update(**payload('r2'), source_revision=10)
    assert first.gateway_revision == 1
    assert second.gateway_revision == 2
    assert second.source_revision == 10
    assert second.received_at_ms == 1100


def test_snapshot_is_copy_isolated_from_callers():
    store = GatewayStateStore(freshness_ms=1500, now_ms=lambda: 1000)
    store.update(**payload('r1'), source_revision=1)
    snap = store.snapshot()
    snap.robot_snapshot['identity']['id'] = 'mutated'
    assert store.snapshot().robot_snapshot['identity']['id'] == 'r1'


def test_runtime_freshness_expires_without_new_update():
    now = [1000]
    store = GatewayStateStore(freshness_ms=1500, now_ms=lambda: now[0])
    store.update(**payload('r1'), source_revision=1)
    now[0] = 2499
    assert store.is_runtime_connected() is True
    assert store.age_ms() == 1499
    now[0] = 2501
    assert store.is_runtime_connected() is False
    assert store.age_ms() == 1501


def test_freshness_must_be_positive():
    try:
        GatewayStateStore(freshness_ms=0)
    except ValueError as exc:
        assert 'freshness_ms' in str(exc)
    else:
        raise AssertionError('expected ValueError')
