from __future__ import annotations

from pathlib import Path

import pytest
import yaml

from agt_site_runtime.activation_store import ActivationStore, ActivationStoreError
from agt_site_runtime.models import ActiveSelection


def test_missing_state_file_means_no_selection(tmp_path):
    store = ActivationStore(tmp_path / "state")
    assert store.load() is None
    assert store.path == tmp_path / "state" / "active_site.yaml"


def test_save_and_load_persists_only_selection_identity(tmp_path):
    store = ActivationStore(tmp_path / "state")
    selection = ActiveSelection("greenhouse_a", "r01")

    store.save(selection)

    assert store.load() == selection
    document = yaml.safe_load(store.path.read_text(encoding="utf-8"))
    assert document == {
        "schema_version": "1.0",
        "site_id": "greenhouse_a",
        "revision": "r01",
    }


@pytest.mark.parametrize(
    "document",
    [
        [],
        {},
        {"schema_version": "2.0", "site_id": "a", "revision": "r01"},
        {"schema_version": "1.0", "site_id": "", "revision": "r01"},
        {"schema_version": "1.0", "site_id": "a", "revision": ""},
        {"schema_version": "1.0", "site_id": "a", "revision": "r01", "valid": True},
    ],
)
def test_malformed_or_cached_validity_state_is_rejected(tmp_path, document):
    store = ActivationStore(tmp_path / "state")
    store.path.parent.mkdir(parents=True)
    store.path.write_text(yaml.safe_dump(document), encoding="utf-8")

    with pytest.raises(ActivationStoreError):
        store.load()


def test_atomic_replace_failure_preserves_previous_selection(tmp_path, monkeypatch):
    store = ActivationStore(tmp_path / "state")
    original = ActiveSelection("greenhouse_a", "r01")
    store.save(original)
    original_bytes = store.path.read_bytes()

    def fail_replace(_source, _destination):
        raise OSError("simulated replace failure")

    monkeypatch.setattr("agt_site_runtime.activation_store.os.replace", fail_replace)

    with pytest.raises(ActivationStoreError, match="replace failure"):
        store.save(ActiveSelection("orchard_b", "r02"))

    assert store.path.read_bytes() == original_bytes
    assert yaml.safe_load(store.path.read_text(encoding="utf-8"))["site_id"] == "greenhouse_a"
    assert list(store.path.parent.glob("*.tmp")) == []
