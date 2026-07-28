"""Typed business operations over the existing experiment manager."""

from __future__ import annotations

from datetime import datetime, timezone
import json
from pathlib import Path
from typing import Any, Mapping

import yaml

from .manager import ExperimentError, ExperimentManager


STATE_NAMES = {
    0: None,
    1: "IDLE",
    2: "RECORDING",
    3: "PLAYING",
    4: "COMPLETED",
    5: "INTERRUPTED",
    6: "ERROR",
}
STATE_VALUES = {name: value for value, name in STATE_NAMES.items() if name}
EXPERIMENT_STATES = {
    0: None,
    1: "CREATED",
    2: "RUNNING",
    3: "COMPLETED",
    4: "INTERRUPTED",
    5: "INVALID",
}


def load_bag_profiles(path: str | Path) -> dict[str, Mapping[str, Any]]:
    try:
        with open(path, "r", encoding="utf-8") as stream:
            value = yaml.safe_load(stream) or {}
    except (OSError, UnicodeError, yaml.YAMLError) as exc:
        raise ExperimentError(f"bag profiles are unreadable: {exc}") from exc
    profiles = value.get("profiles", {})
    if not isinstance(profiles, Mapping):
        raise ExperimentError("bag profiles must contain a profiles mapping")
    result = {}
    for profile_id, profile in profiles.items():
        topics = profile.get("topics") if isinstance(profile, Mapping) else None
        if (
            not isinstance(profile_id, str)
            or not isinstance(topics, list)
            or not topics
            or any(not isinstance(topic, str) or not topic.startswith("/") for topic in topics)
            or "-a" in topics
        ):
            raise ExperimentError(f"bag profile is invalid: {profile_id}")
        result[profile_id] = profile
    return result


def _iso_mtime(path: str | Path) -> str:
    try:
        stamp = Path(path).stat().st_mtime
    except OSError:
        return ""
    return datetime.fromtimestamp(stamp, timezone.utc).isoformat(timespec="seconds")


def _snapshot_paths(values: Mapping[str, str]) -> list[Path]:
    result = []
    for name in ("platform_profile", "calibration_profile", "nav2_profile"):
        raw = str(values.get(name, "")).strip()
        if not raw:
            continue
        path = Path(raw).expanduser().resolve()
        if not path.is_file():
            raise ExperimentError(f"{name} does not identify an existing file")
        result.append(path)
    return result


class ExperimentBusinessFacade:
    def __init__(
        self, manager: ExperimentManager, bag_profiles: Mapping[str, Mapping[str, Any]]
    ) -> None:
        self.manager = manager
        self.bag_profiles = dict(bag_profiles)

    def running_experiment(self) -> dict[str, Any] | None:
        running = self.manager.list(state="RUNNING")
        return running[0] if running else None

    def status(self) -> dict[str, Any]:
        recording = self.manager.bag_status()
        playback = self.manager.playback_status()
        if recording.get("recording"):
            path = str(recording.get("path", ""))
            try:
                bag_id = str(Path(path).resolve().relative_to(self.manager.root.parent))
            except (OSError, ValueError):
                bag_id = ""
            return {
                "state": "RECORDING",
                "bag_id": bag_id,
                "experiment_id": str(recording.get("experiment_id", "")),
                "profile_id": str(recording.get("profile", "")),
                "relative_uri": bag_id,
                "complete": False,
                "simulation": False,
                "playback_rate": float(playback.get("rate", 0.0)),
                "storage_bytes": 0,
                "started_at": _iso_mtime(path),
                "updated_at": _iso_mtime(path),
                "message": "bag recording is active",
                "process_id": int(recording.get("pid", 0)),
            }
        if recording.get("returncode") is not None:
            path = str(recording.get("path", ""))
            try:
                bag_id = str(Path(path).resolve().relative_to(self.manager.root.parent))
            except (OSError, ValueError):
                bag_id = ""
            return {
                "state": "ERROR",
                "bag_id": bag_id,
                "experiment_id": str(recording.get("experiment_id", "")),
                "profile_id": str(recording.get("profile", "")),
                "relative_uri": bag_id,
                "complete": False,
                "simulation": False,
                "playback_rate": 0.0,
                "storage_bytes": 0,
                "started_at": _iso_mtime(path),
                "updated_at": _iso_mtime(path),
                "message": f"bag recorder exited with {recording['returncode']}",
                "process_id": int(recording.get("pid", 0)),
            }
        if playback.get("playing"):
            bag_id = str(playback.get("bag_id", ""))
            return {
                "state": "PLAYING",
                "bag_id": bag_id,
                "experiment_id": "",
                "profile_id": str(playback.get("playback_profile", "")),
                "relative_uri": bag_id,
                "complete": True,
                "simulation": True,
                "playback_rate": float(playback.get("rate", 0.0)),
                "storage_bytes": 0,
                "started_at": "",
                "updated_at": "",
                "message": "bag playback is active",
                "process_id": int(playback.get("pid", 0)),
            }
        if playback.get("returncode") is not None:
            return {
                "state": "ERROR",
                "bag_id": str(playback.get("bag_id", "")),
                "experiment_id": "",
                "profile_id": str(playback.get("playback_profile", "")),
                "relative_uri": str(playback.get("bag_id", "")),
                "complete": True,
                "simulation": True,
                "playback_rate": float(playback.get("rate", 0.0)),
                "storage_bytes": 0,
                "started_at": "",
                "updated_at": "",
                "message": f"bag playback exited with {playback['returncode']}",
                "process_id": int(playback.get("pid", 0)),
            }
        active = self.running_experiment()
        return {
            "state": "IDLE",
            "bag_id": "",
            "experiment_id": str(active.get("experiment_id", "")) if active else "",
            "profile_id": "",
            "relative_uri": "",
            "complete": False,
            "simulation": False,
            "playback_rate": 0.0,
            "storage_bytes": 0,
            "started_at": "",
            "updated_at": "",
            "message": "no active bag process",
            "process_id": 0,
        }

    def list_sessions(self, *, state: int = 0, experiment_id: str = "") -> list[dict[str, Any]]:
        if state not in STATE_NAMES:
            raise ValueError(f"unsupported bag state filter: {state}")
        result = []
        for bag in self.manager.list_bags():
            if experiment_id and str(bag.get("experiment_id", "")) != experiment_id:
                continue
            path = Path(str(bag["path"]))
            storage_bytes = sum(
                item.stat().st_size for item in path.rglob("*") if item.is_file()
            )
            item = {
                "state": "COMPLETED",
                "bag_id": str(bag["bag_id"]),
                "experiment_id": str(bag.get("experiment_id", "")),
                "profile_id": "",
                "relative_uri": str(bag["bag_id"]),
                "complete": True,
                "simulation": False,
                "playback_rate": 0.0,
                "storage_bytes": storage_bytes,
                "started_at": _iso_mtime(path),
                "updated_at": _iso_mtime(path / "metadata.yaml"),
                "message": f"{int(bag.get('message_count', 0))} messages",
                "process_id": 0,
                "message_count": int(bag.get("message_count", 0)),
                "storage_identifier": str(bag.get("storage_identifier", "")),
                "mapping_input_ready": bool(bag.get("mapping_input_ready", False)),
                "contains_mapping_outputs": bool(
                    bag.get("contains_mapping_outputs", False)
                ),
                "contains_navigation_outputs": bool(
                    bag.get("contains_navigation_outputs", False)
                ),
            }
            if state and STATE_NAMES[state] != item["state"]:
                continue
            result.append(item)
        current = self.status()
        if current["state"] in {"RECORDING", "PLAYING", "ERROR"}:
            if (not state or STATE_NAMES[state] == current["state"]) and (
                not experiment_id or current["experiment_id"] == experiment_id
            ):
                result.insert(0, current)
        return result

    def create_experiment(
        self, values: Mapping[str, str], *, start: bool = False
    ) -> dict[str, Any]:
        if self.running_experiment() is not None:
            raise ExperimentError("a running experiment already exists")
        title = str(values.get("experiment_title") or values.get("experiment_id") or "").strip()
        if not title:
            raise ExperimentError("experiment_title is required")
        raw_tags = str(values.get("tags_json", "")).strip()
        try:
            tags = json.loads(raw_tags) if raw_tags else []
        except json.JSONDecodeError as exc:
            raise ExperimentError(f"tags_json is invalid: {exc}") from exc
        if not isinstance(tags, list) or any(not isinstance(item, str) for item in tags):
            raise ExperimentError("tags_json must encode a string array")
        snapshots = _snapshot_paths(values)
        experiment_id = self.manager.create(
            title=title,
            objective=str(values.get("objective", "")),
            hypothesis=str(values.get("hypothesis", "")),
            tags=tags,
            operator_note=str(values.get("operator_note", "")),
            platform_profile=str(values.get("platform_profile", "")),
            active_map={
                "map_id": str(values.get("map_id", "")),
                "map_version_id": str(values.get("map_version_id", "")),
                "manifest_sha256": str(values.get("map_sha256", "")),
            },
            launch_profile=str(
                values.get("launch_profile", values.get("nav2_profile", ""))
            ),
            launch_arguments={
                "mission_id": str(values.get("mission_id", "")),
                "mission_version": str(values.get("mission_version", "")),
                "mission_sha256": str(values.get("mission_sha256", "")),
                "calibration_profile": str(values.get("calibration_profile", "")),
            },
        )
        if snapshots:
            self.manager.snapshot_config(experiment_id, snapshots)
        if start:
            return self.manager.start(experiment_id)
        return self.manager.inspect(experiment_id)

    def list_experiments(self, *, state: int = 0) -> list[dict[str, Any]]:
        if state not in EXPERIMENT_STATES:
            raise ValueError(f"unsupported experiment state filter: {state}")
        return self.manager.list(state=EXPERIMENT_STATES[state])

    def manage(self, operation: int, values: Mapping[str, Any]) -> dict[str, Any]:
        if operation == 0:
            return self.status()
        experiment_id = str(values.get("experiment_id", "")).strip()
        if operation == 1:
            if not experiment_id:
                raise ExperimentError("experiment_id is required for recording")
            profile_id = str(values.get("profile_id", "")).strip()
            if profile_id not in self.bag_profiles:
                raise ExperimentError(f"unknown bag profile: {profile_id}")
            path = self.manager.start_bag(
                experiment_id, profile_id, self.bag_profiles[profile_id]
            )
            return {**self.status(), "relative_uri": str(path.relative_to(self.manager.root.parent))}
        if operation == 2:
            recording = self.manager.bag_status()
            owner = str(recording.get("experiment_id", ""))
            if experiment_id and owner and experiment_id != owner:
                raise ExperimentError("recording belongs to another experiment")
            self.manager.stop_bag(experiment_id or owner)
            return self.status()
        if operation == 3:
            self.manager.start_playback(
                str(values.get("bag_id", "")),
                rate=float(values.get("playback_rate", 1.0) or 1.0),
                playback_profile=str(values.get("profile_id", "all")) or "all",
            )
            result = self.status()
            result["playback_rate"] = float(values.get("playback_rate", 1.0) or 1.0)
            return result
        if operation == 4:
            self.manager.stop_playback()
            return self.status()
        if operation == 5:
            created = self.create_experiment(
                {key: str(value) for key, value in values.items()},
                start=bool(values.get("start_experiment", False)),
            )
            return {
                **self.status(),
                "experiment_id": str(created.get("experiment_id", "")),
                "message": f"experiment is {str(created.get('state', 'CREATED')).lower()}",
            }
        if operation == 6:
            if not experiment_id:
                raise ExperimentError("experiment_id is required")
            self.manager.finalize(
                experiment_id,
                result_status=str(values.get("result_status", "")).strip()
                or "COMPLETED",
            )
            return self.status()
        if operation == 7:
            if not experiment_id:
                raise ExperimentError("experiment_id is required")
            self.manager.interrupt(
                experiment_id,
                str(values.get("reason", "")).strip() or "operator_requested",
            )
            return self.status()
        if operation == 8:
            if not experiment_id:
                raise ExperimentError("experiment_id is required")
            current = self.manager.inspect(experiment_id)
            if current.get("state") != "RUNNING":
                current = self.manager.start(experiment_id)
            return {
                **self.status(),
                "experiment_id": experiment_id,
                "message": f"experiment is {str(current.get('state', 'RUNNING')).lower()}",
            }
        if operation == 9:
            if not experiment_id:
                raise ExperimentError("experiment_id is required")
            self.manager.mark_invalid(
                experiment_id,
                str(values.get("reason", "")).strip() or "operator marked invalid",
            )
            return self.status()
        if operation == 10:
            if not experiment_id:
                raise ExperimentError("experiment_id is required")
            event_type = str(values.get("event_type", "")).strip() or "operator_event"
            raw_metadata = str(values.get("metadata_json", "")).strip()
            try:
                metadata = json.loads(raw_metadata) if raw_metadata else {}
            except json.JSONDecodeError as exc:
                raise ValueError(f"metadata_json is invalid: {exc}") from exc
            if not isinstance(metadata, Mapping):
                raise ValueError("metadata_json must encode an object")
            self.manager.add_event(experiment_id, event_type, metadata)
            return {
                **self.status(),
                "experiment_id": experiment_id,
                "message": "experiment event recorded",
            }
        raise ValueError(f"unsupported bag operation: {operation}")
