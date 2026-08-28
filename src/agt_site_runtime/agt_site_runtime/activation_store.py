from __future__ import annotations

from collections.abc import Mapping
import os
from pathlib import Path
import tempfile

import yaml

from .models import ActiveSelection


class ActivationStoreError(RuntimeError):
    pass


class ActivationStore:
    def __init__(self, state_root: Path):
        self.state_root = Path(state_root).expanduser()
        self._path = self.state_root / "active_site.yaml"

    @property
    def path(self) -> Path:
        return self._path

    def load(self) -> ActiveSelection | None:
        if not self.path.exists():
            return None

        try:
            document = yaml.safe_load(self.path.read_text(encoding="utf-8"))
        except (OSError, UnicodeError, yaml.YAMLError) as exc:
            raise ActivationStoreError(f"cannot read active selection: {exc}") from exc

        expected_keys = {"schema_version", "site_id", "revision"}
        if not isinstance(document, Mapping) or set(document.keys()) != expected_keys:
            raise ActivationStoreError(
                "active selection must contain exactly schema_version, site_id, revision"
            )
        if document.get("schema_version") != "1.0":
            raise ActivationStoreError("unsupported active selection schema_version")

        site_id = document.get("site_id")
        revision = document.get("revision")
        if not isinstance(site_id, str) or not site_id.strip():
            raise ActivationStoreError("active selection site_id must be a non-empty string")
        if not isinstance(revision, str) or not revision.strip():
            raise ActivationStoreError("active selection revision must be a non-empty string")

        return ActiveSelection(site_id=site_id, revision=revision)

    def save(self, selection: ActiveSelection) -> None:
        if not isinstance(selection.site_id, str) or not selection.site_id.strip():
            raise ActivationStoreError("active selection site_id must be a non-empty string")
        if not isinstance(selection.revision, str) or not selection.revision.strip():
            raise ActivationStoreError("active selection revision must be a non-empty string")

        document = {
            "schema_version": "1.0",
            "site_id": selection.site_id,
            "revision": selection.revision,
        }
        try:
            self.state_root.mkdir(parents=True, exist_ok=True)
        except OSError as exc:
            raise ActivationStoreError(f"cannot create state directory: {exc}") from exc

        temporary_path: Path | None = None
        try:
            with tempfile.NamedTemporaryFile(
                mode="w",
                encoding="utf-8",
                dir=self.state_root,
                prefix="active_site.",
                suffix=".tmp",
                delete=False,
            ) as stream:
                temporary_path = Path(stream.name)
                yaml.safe_dump(document, stream, sort_keys=False)
                stream.flush()
                os.fsync(stream.fileno())
            os.replace(temporary_path, self.path)
        except (OSError, yaml.YAMLError) as exc:
            if temporary_path is not None:
                try:
                    temporary_path.unlink(missing_ok=True)
                except OSError:
                    pass
            raise ActivationStoreError(f"cannot persist active selection: {exc}") from exc
