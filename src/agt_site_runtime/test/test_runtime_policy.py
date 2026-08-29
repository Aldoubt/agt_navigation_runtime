from __future__ import annotations

from dataclasses import replace
from pathlib import Path

from agt_site_runtime.activation_store import ActivationStoreError
from agt_site_runtime.models import (
    ActiveSelection,
    SiteCandidate,
    SiteKey,
    SiteSummary,
    SiteValidation,
)
from agt_site_runtime.runtime_policy import (
    ERROR_INTERNAL,
    ERROR_INVALID_REQUEST,
    ERROR_NONE,
    ERROR_NOT_FOUND,
    ERROR_VALIDATION_FAILED,
    SiteRuntimePolicy,
)
from agt_site_runtime.summary_builder import STATE_INVALID, STATE_READY


class FakeRegistry:
    def __init__(self, candidates):
        self.candidates = {candidate.key: candidate for candidate in candidates}

    def scan(self):
        return tuple(sorted(self.candidates.values(), key=lambda item: item.key))

    def resolve(self, key):
        return self.candidates.get(key)


class FakeValidator:
    def __init__(self, valid_by_key):
        self.valid_by_key = dict(valid_by_key)
        self.calls = []

    def validate(self, candidate):
        self.calls.append(candidate.key)
        valid = self.valid_by_key[candidate.key]
        if valid:
            return SiteValidation(candidate=candidate, valid=True, checks=("fixture",))
        return SiteValidation(
            candidate=candidate,
            valid=False,
            blocker_codes=("SITE_HASH_MISMATCH",),
            blocker_messages=("hash mismatch",),
        )


class FakeStore:
    def __init__(self, selection=None):
        self.selection = selection
        self.saved = []
        self.fail_save = False
        self.fail_load = False

    def load(self):
        if self.fail_load:
            raise ActivationStoreError("broken persisted state")
        return self.selection

    def save(self, selection):
        if self.fail_save:
            raise ActivationStoreError("simulated persist failure")
        self.selection = selection
        self.saved.append(selection)


def candidate(site_id, revision):
    root = Path("/deployed") / site_id / revision
    return SiteCandidate(SiteKey(site_id, revision), root, root / "manifest.yaml")


def fake_summary_builder(candidate, validation, *, active):
    if not validation.valid:
        return SiteSummary(
            map_id=candidate.key.site_id,
            map_version_id=candidate.key.revision,
            state=STATE_INVALID,
            active=False,
            valid=False,
            validation_errors=validation.blocker_messages,
        )
    return SiteSummary(
        map_id=candidate.key.site_id,
        map_version_id=candidate.key.revision,
        state=STATE_READY,
        active=active,
        valid=True,
        map_hash=f"hash:{candidate.key.site_id}:{candidate.key.revision}",
    )


def make_policy(valid_by_key, *, selection=None, recent_request_limit=4):
    candidates = [candidate(key.site_id, key.revision) for key in valid_by_key]
    store = FakeStore(selection)
    validator = FakeValidator(valid_by_key)
    policy = SiteRuntimePolicy(
        FakeRegistry(candidates),
        validator,
        store,
        recent_request_limit=recent_request_limit,
        summary_builder=fake_summary_builder,
    )
    return policy, store, validator


def test_policy_never_auto_selects_a_ready_site():
    key = SiteKey("greenhouse_a", "r01")
    policy, store, validator = make_policy({key: True})

    assert policy.active_summary is None
    versions = policy.list_versions()

    assert len(versions) == 1
    assert versions[0].state == STATE_READY
    assert not versions[0].active
    assert store.saved == []
    assert validator.calls == [key]


def test_valid_activation_persists_before_becoming_active():
    key = SiteKey("greenhouse_a", "r01")
    policy, store, _ = make_policy({key: True})

    result = policy.activate(key, "ui-req-1")

    assert result.success
    assert result.error_code == ERROR_NONE
    assert result.summary is not None and result.summary.active
    assert policy.active_summary == result.summary
    assert store.saved == [ActiveSelection("greenhouse_a", "r01")]
    assert not result.revoke_active


def test_failed_switch_preserves_previous_active_and_persisted_selection():
    good = SiteKey("greenhouse_a", "r01")
    bad = SiteKey("orchard_b", "r02")
    policy, store, _ = make_policy({good: True, bad: False})
    first = policy.activate(good, "req-good")
    previous = first.summary
    previous_selection = store.selection

    failed = policy.activate(bad, "req-bad")

    assert not failed.success
    assert failed.error_code == ERROR_VALIDATION_FAILED
    assert "SITE_HASH_MISMATCH" in failed.blocker_codes
    assert policy.active_summary == previous
    assert store.selection == previous_selection
    assert store.saved == [ActiveSelection("greenhouse_a", "r01")]
    assert not failed.revoke_active


def test_persistence_failure_preserves_previous_active():
    first = SiteKey("greenhouse_a", "r01")
    second = SiteKey("greenhouse_a", "r02")
    policy, store, _ = make_policy({first: True, second: True})
    assert policy.activate(first, "req-1").success
    previous = policy.active_summary
    store.fail_save = True

    result = policy.activate(second, "req-2")

    assert not result.success
    assert result.error_code == ERROR_INTERNAL
    assert result.blocker_codes == ("ACTIVE_SELECTION_PERSIST_FAILED",)
    assert policy.active_summary == previous
    assert store.selection == ActiveSelection("greenhouse_a", "r01")
    assert not result.revoke_active


def test_restore_without_selection_revokes_any_stale_consumer_authority():
    key = SiteKey("greenhouse_a", "r01")
    policy, store, _ = make_policy({key: True}, selection=None)

    result = policy.restore()

    assert result.success
    assert result.error_code == ERROR_NONE
    assert result.summary is None
    assert result.revoke_active
    assert policy.active_summary is None
    assert store.saved == []


def test_valid_restore_revalidates_and_does_not_rewrite_selection():
    key = SiteKey("greenhouse_a", "r01")
    policy, store, validator = make_policy(
        {key: True}, selection=ActiveSelection("greenhouse_a", "r01")
    )

    result = policy.restore()

    assert result.success
    assert result.summary is not None and result.summary.active
    assert result.summary.state == STATE_READY
    assert policy.active_summary == result.summary
    assert validator.calls == [key]
    assert store.saved == []
    assert not result.revoke_active


def test_invalid_restore_does_not_fallback_to_another_valid_revision():
    selected = SiteKey("greenhouse_a", "r02")
    fallback = SiteKey("greenhouse_a", "r01")
    policy, store, validator = make_policy(
        {fallback: True, selected: False},
        selection=ActiveSelection("greenhouse_a", "r02"),
    )

    result = policy.restore()

    assert not result.success
    assert result.error_code == ERROR_VALIDATION_FAILED
    assert result.revoke_active
    assert policy.active_summary is None
    assert validator.calls == [selected]
    assert store.selection == ActiveSelection("greenhouse_a", "r02")
    assert store.saved == []


def test_missing_selected_site_restore_is_fail_closed_without_fallback():
    key = SiteKey("greenhouse_a", "r01")
    policy, store, _ = make_policy({key: True})
    store.selection = ActiveSelection("missing", "r99")

    result = policy.restore()

    assert not result.success
    assert result.error_code == ERROR_NOT_FOUND
    assert result.blocker_codes == ("SITE_NOT_FOUND",)
    assert result.revoke_active
    assert policy.active_summary is None


def test_malformed_persisted_selection_is_fail_closed():
    key = SiteKey("greenhouse_a", "r01")
    policy, store, _ = make_policy({key: True})
    store.fail_load = True

    result = policy.restore()

    assert not result.success
    assert result.error_code == ERROR_INTERNAL
    assert result.revoke_active
    assert policy.active_summary is None


def test_same_request_id_same_target_is_idempotent_without_repeating_save():
    key = SiteKey("greenhouse_a", "r01")
    policy, store, validator = make_policy({key: True})

    first = policy.activate(key, "req-1")
    second = policy.activate(key, "req-1")

    assert second == first
    assert store.saved == [ActiveSelection("greenhouse_a", "r01")]
    assert validator.calls == [key]


def test_same_request_id_different_target_is_rejected():
    first = SiteKey("greenhouse_a", "r01")
    second = SiteKey("greenhouse_a", "r02")
    policy, store, _ = make_policy({first: True, second: True})
    assert policy.activate(first, "req-shared").success

    result = policy.activate(second, "req-shared")

    assert not result.success
    assert result.error_code == ERROR_INVALID_REQUEST
    assert result.blocker_codes == ("INVALID_REQUEST",)
    assert policy.active_summary.map_version_id == "r01"
    assert store.saved == [ActiveSelection("greenhouse_a", "r01")]


def test_invalid_client_request_id_is_rejected_before_validation_or_persistence():
    key = SiteKey("greenhouse_a", "r01")
    policy, store, validator = make_policy({key: True})

    result = policy.activate(key, "bad request with spaces")

    assert not result.success
    assert result.error_code == ERROR_INVALID_REQUEST
    assert result.blocker_codes == ("INVALID_REQUEST",)
    assert store.saved == []
    assert validator.calls == []


def test_recent_request_cache_is_bounded():
    keys = [SiteKey("greenhouse_a", f"r0{index}") for index in range(1, 5)]
    policy, _, _ = make_policy(
        {key: True for key in keys}, recent_request_limit=2
    )

    for index, key in enumerate(keys, start=1):
        assert policy.activate(key, f"req-{index}").success

    assert policy.recent_request_count == 2


def test_validate_missing_and_invalid_candidates_return_coarse_service_errors():
    valid = SiteKey("greenhouse_a", "r01")
    invalid = SiteKey("greenhouse_a", "r02")
    policy, _, _ = make_policy({valid: True, invalid: False})

    missing = policy.validate(SiteKey("missing", "r99"))
    bad = policy.validate(invalid)

    assert not missing.success and missing.error_code == ERROR_NOT_FOUND
    assert missing.blocker_codes == ("SITE_NOT_FOUND",)
    assert not bad.success and bad.error_code == ERROR_VALIDATION_FAILED
    assert bad.summary is not None and bad.summary.state == STATE_INVALID


def test_list_filters_by_map_id_and_state_without_changing_active_state():
    a1 = SiteKey("greenhouse_a", "r01")
    a2 = SiteKey("greenhouse_a", "r02")
    b1 = SiteKey("orchard_b", "r01")
    policy, _, _ = make_policy({a1: True, a2: False, b1: True})

    only_a = policy.list_versions(map_id="greenhouse_a")
    only_invalid = policy.list_versions(state=STATE_INVALID)

    assert [(item.map_id, item.map_version_id) for item in only_a] == [
        ("greenhouse_a", "r01"),
        ("greenhouse_a", "r02"),
    ]
    assert [(item.map_id, item.map_version_id) for item in only_invalid] == [
        ("greenhouse_a", "r02")
    ]
    assert policy.active_summary is None
