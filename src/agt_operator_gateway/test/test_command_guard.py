from __future__ import annotations

from agt_operator_gateway.command_guard import (
    CommandReplayStore,
    ControlLeaseStore,
    ReplayKind,
    canonical_fingerprint,
    verify_bearer_token,
)


def test_bearer_token_requires_nonempty_expected_token_and_exact_bearer_value() -> None:
    assert verify_bearer_token('Bearer secret-123', 'secret-123') is True
    assert verify_bearer_token('Bearer wrong', 'secret-123') is False
    assert verify_bearer_token(None, 'secret-123') is False
    assert verify_bearer_token('Basic secret-123', 'secret-123') is False
    assert verify_bearer_token('Bearer secret-123', '') is False


def test_canonical_fingerprint_is_order_independent_but_payload_sensitive() -> None:
    left = canonical_fingerprint('START', {'missionId': 'm1', 'missionVersion': 'v1'})
    same = canonical_fingerprint('START', {'missionVersion': 'v1', 'missionId': 'm1'})
    different = canonical_fingerprint('PAUSE', {'missionId': 'm1', 'missionVersion': 'v1'})
    assert left == same
    assert left != different


def test_replay_store_reports_new_then_in_progress_for_same_request() -> None:
    now = [1000]
    store = CommandReplayStore(now_ms=lambda: now[0], ttl_ms=60_000, max_entries=8)
    fingerprint = canonical_fingerprint('START', {'missionId': 'm1'})

    first = store.begin('req-1', fingerprint)
    second = store.begin('req-1', fingerprint)

    assert first.kind is ReplayKind.NEW
    assert second.kind is ReplayKind.IN_PROGRESS


def test_replay_store_replays_completed_response_without_new_dispatch() -> None:
    now = [1000]
    store = CommandReplayStore(now_ms=lambda: now[0], ttl_ms=60_000, max_entries=8)
    fingerprint = canonical_fingerprint('PAUSE', {'missionId': 'm1'})
    assert store.begin('req-2', fingerprint).kind is ReplayKind.NEW

    payload = {'state': 'ACCEPTED', 'missionId': 'm1'}
    store.complete('req-2', fingerprint, status_code=200, payload=payload)
    replay = store.begin('req-2', fingerprint)

    assert replay.kind is ReplayKind.REPLAY
    assert replay.status_code == 200
    assert replay.payload == payload
    assert replay.payload is not payload


def test_replay_store_rejects_same_request_id_with_different_payload() -> None:
    store = CommandReplayStore(now_ms=lambda: 1000, ttl_ms=60_000, max_entries=8)
    first = canonical_fingerprint('START', {'missionId': 'm1'})
    different = canonical_fingerprint('START', {'missionId': 'm2'})
    assert store.begin('req-3', first).kind is ReplayKind.NEW
    assert store.begin('req-3', different).kind is ReplayKind.CONFLICT


def test_completed_entries_expire_after_ttl_and_can_be_dispatched_again() -> None:
    now = [1000]
    store = CommandReplayStore(now_ms=lambda: now[0], ttl_ms=100, max_entries=8)
    fingerprint = canonical_fingerprint('RESUME', {'missionId': 'm1'})
    assert store.begin('req-4', fingerprint).kind is ReplayKind.NEW
    store.complete('req-4', fingerprint, status_code=200, payload={'state': 'ACCEPTED'})

    now[0] = 1101
    assert store.begin('req-4', fingerprint).kind is ReplayKind.NEW


def test_store_never_evicts_inflight_request_to_make_room() -> None:
    store = CommandReplayStore(now_ms=lambda: 1000, ttl_ms=60_000, max_entries=1)
    first = canonical_fingerprint('START', {'missionId': 'm1'})
    second = canonical_fingerprint('START', {'missionId': 'm2'})
    assert store.begin('req-a', first).kind is ReplayKind.NEW
    assert store.begin('req-b', second).kind is ReplayKind.CAPACITY
    assert store.begin('req-a', first).kind is ReplayKind.IN_PROGRESS


def test_completed_oldest_entry_is_evicted_when_cache_is_full() -> None:
    now = [1000]
    store = CommandReplayStore(now_ms=lambda: now[0], ttl_ms=60_000, max_entries=1)
    first = canonical_fingerprint('CANCEL', {'missionId': 'm1'})
    second = canonical_fingerprint('CANCEL', {'missionId': 'm2'})
    assert store.begin('req-a', first).kind is ReplayKind.NEW
    store.complete('req-a', first, status_code=200, payload={'state': 'ACCEPTED'})

    now[0] = 1001
    assert store.begin('req-b', second).kind is ReplayKind.NEW
    assert store.begin('req-a', first).kind is ReplayKind.CAPACITY


def test_control_lease_allows_only_one_controller_until_release() -> None:
    now = [1000]
    store = ControlLeaseStore(now_ms=lambda: now[0], ttl_ms=15_000)

    first = store.acquire('laptop-a')
    blocked = store.acquire('laptop-b')

    assert first.acquired is True
    assert first.controller_id == 'laptop-a'
    assert first.expires_at_ms == 16_000
    assert blocked.acquired is False
    assert blocked.controller_id == 'laptop-a'
    assert store.is_controller('laptop-a') is True
    assert store.is_controller('laptop-b') is False

    released = store.release('laptop-a')
    assert released.controller_id is None
    assert store.acquire('laptop-b').acquired is True


def test_control_lease_renew_extends_expiry_and_expired_owner_can_be_replaced() -> None:
    now = [1000]
    store = ControlLeaseStore(now_ms=lambda: now[0], ttl_ms=1000)

    store.acquire('robot-local')
    now[0] = 1500
    renewed = store.renew('robot-local')
    assert renewed.acquired is True
    assert renewed.expires_at_ms == 2500

    now[0] = 2501
    assert store.is_controller('robot-local') is False
    replacement = store.acquire('laptop-remote')
    assert replacement.acquired is True
    assert replacement.controller_id == 'laptop-remote'


def test_control_lease_non_owner_cannot_renew_or_release_current_owner() -> None:
    store = ControlLeaseStore(now_ms=lambda: 1000, ttl_ms=15_000)
    store.acquire('laptop-a')

    renew = store.renew('laptop-b')
    release = store.release('laptop-b')

    assert renew.acquired is False
    assert renew.controller_id == 'laptop-a'
    assert release.controller_id == 'laptop-a'
    assert store.is_controller('laptop-a') is True
