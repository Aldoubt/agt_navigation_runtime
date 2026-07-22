"""Atomic, auditable experiment session manager."""

from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import re
import signal
import subprocess
from typing import Any, Callable, Mapping
from uuid import uuid4

import yaml


class ExperimentError(RuntimeError):
    pass


def _timestamp() -> str:
    return datetime.now(timezone.utc).isoformat(timespec="seconds")


def _file_hash(path: Path) -> str:
    digest = hashlib.sha256()
    with open(path, "rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return "sha256:" + digest.hexdigest()


def _atomic_yaml(path: Path, value: Mapping[str, Any]) -> None:
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_text(yaml.safe_dump(dict(value), sort_keys=False), encoding="utf-8")
    os.replace(temporary, path)


def _atomic_json(path: Path, value: Any) -> None:
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_text(json.dumps(value, indent=2, ensure_ascii=False), encoding="utf-8")
    os.replace(temporary, path)


class ExperimentManager:
    """Own the experiment directory and any rosbag child it starts."""

    def __init__(
        self,
        root: str | Path,
        *,
        repository_root: str | Path | None = None,
        popen_factory: Callable[..., Any] = subprocess.Popen,
    ) -> None:
        self.root = Path(root).expanduser().resolve()
        self.root.mkdir(parents=True, exist_ok=True)
        self.repository_root = Path(repository_root).expanduser().resolve() if repository_root else None
        self._popen = popen_factory
        self._bag_process = None
        self._bag_log = None
        self._bag_profile = ""

    @staticmethod
    def _slug(value: str) -> str:
        slug = re.sub(r"[^a-z0-9_-]+", "-", str(value).lower()).strip("-")
        return slug[:48] or "experiment"

    def _path(self, experiment_id: str) -> Path:
        path = self.root / experiment_id
        if not path.is_dir():
            raise ExperimentError(f"unknown experiment: {experiment_id}")
        return path

    def _manifest(self, experiment_id: str) -> tuple[Path, dict[str, Any]]:
        path = self._path(experiment_id) / "manifest.yaml"
        try:
            with open(path, "r", encoding="utf-8") as stream:
                return path, yaml.safe_load(stream) or {}
        except (OSError, yaml.YAMLError) as error:
            raise ExperimentError(f"manifest unreadable: {error}") from error

    def create(
        self,
        *,
        title: str,
        objective: str = "",
        hypothesis: str = "",
        tags: list[str] | None = None,
        operator_note: str = "",
        platform_profile: str = "",
        active_map: Mapping[str, Any] | None = None,
        launch_profile: str = "",
        launch_arguments: Mapping[str, Any] | None = None,
    ) -> str:
        experiment_id = datetime.now(timezone.utc).strftime("exp_%Y%m%d_%H%M%S") + f"_{self._slug(title)}_{uuid4().hex[:6]}"
        path = self.root / experiment_id
        path.mkdir(parents=True, exist_ok=False)
        for name in ("parameters", "config_snapshot", "rosbag", "logs"):
            (path / name).mkdir()
        manifest = {
            "schema_version": 1,
            "experiment_id": experiment_id,
            "title": title,
            "objective": objective,
            "hypothesis": hypothesis,
            "tags": list(tags or []),
            "operator_note": operator_note,
            "state": "CREATED",
            "created_at": _timestamp(),
            "start_time": None,
            "end_time": None,
            "result_status": "NOT_STARTED",
            "repository": self._repository_snapshot(),
            "ros_distro": os.environ.get("ROS_DISTRO", "unknown"),
            "platform_profile": platform_profile,
            "active_map": dict(active_map or {}),
            "launch_profile": launch_profile,
            "launch_arguments": dict(launch_arguments or {}),
            "config_files": [],
            "health_start": "health_start.json",
            "health_end": "health_end.json",
            "rosbag": None,
            "algorithm_parameters": {},
            "localization_results": "localization_results.jsonl",
            "navigation_summary": {},
            "manual_intervention_count": 0,
            "emergency_stop_count": 0,
            "report_path": "report.md",
        }
        _atomic_yaml(path / "manifest.yaml", manifest)
        (path / "events.jsonl").touch()
        (path / "localization_results.jsonl").touch()
        _atomic_json(path / "summary.json", {"state": "CREATED", "experiment_id": experiment_id})
        return experiment_id

    def _repository_snapshot(self) -> dict[str, Any]:
        if self.repository_root is None:
            return {"path": None, "branch": None, "commit": None, "dirty": None}

        def run(*args: str) -> str | None:
            try:
                return subprocess.check_output(
                    ["git", "-C", str(self.repository_root), *args],
                    text=True,
                    stderr=subprocess.DEVNULL,
                ).strip()
            except (OSError, subprocess.CalledProcessError):
                return None

        status = run("status", "--porcelain")
        return {
            "path": str(self.repository_root),
            "branch": run("branch", "--show-current"),
            "commit": run("rev-parse", "HEAD"),
            "dirty": bool(status) if status is not None else None,
        }

    def start(self, experiment_id: str, health: Mapping[str, Any] | None = None) -> dict[str, Any]:
        path, manifest = self._manifest(experiment_id)
        if manifest.get("state") not in ("CREATED", "INTERRUPTED"):
            raise ExperimentError(f"experiment cannot start from {manifest.get('state')}")
        now = _timestamp()
        manifest["state"] = "RUNNING"
        manifest["result_status"] = "RUNNING"
        manifest["start_time"] = manifest.get("start_time") or now
        manifest["end_time"] = None
        _atomic_yaml(path, manifest)
        _atomic_json(path.parent / "health_start.json", dict(health or {}))
        self.add_event(experiment_id, "experiment_started", {"time": now})
        return manifest

    def add_event(self, experiment_id: str, event_type: str, data: Mapping[str, Any] | None = None) -> None:
        path = self._path(experiment_id) / "events.jsonl"
        event = {"time": _timestamp(), "type": str(event_type), "data": dict(data or {})}
        with open(path, "a", encoding="utf-8") as stream:
            stream.write(json.dumps(event, ensure_ascii=False, sort_keys=True) + "\n")
            stream.flush()
            os.fsync(stream.fileno())

    def record_localization_result(self, experiment_id: str, result: Mapping[str, Any]) -> None:
        _path, manifest = self._manifest(experiment_id)
        if manifest.get("state") != "RUNNING":
            raise ExperimentError("localization results require a running experiment")
        output = self._path(experiment_id) / "localization_results.jsonl"
        with open(output, "a", encoding="utf-8") as stream:
            stream.write(json.dumps({"time": _timestamp(), **dict(result)}, ensure_ascii=False, sort_keys=True) + "\n")
            stream.flush()
            os.fsync(stream.fileno())

    def snapshot_health(self, experiment_id: str, name: str, health: Mapping[str, Any]) -> None:
        if name not in ("health_start", "health_end"):
            raise ExperimentError("health snapshot name is invalid")
        _atomic_json(self._path(experiment_id) / f"{name}.json", dict(health))

    def snapshot_config(self, experiment_id: str, paths: list[str | Path]) -> list[dict[str, str]]:
        manifest_path, manifest = self._manifest(experiment_id)
        destination = manifest_path.parent / "config_snapshot"
        records = []
        for source_value in paths:
            source = Path(source_value).expanduser().resolve()
            if not source.is_file():
                raise ExperimentError(f"config snapshot source is missing: {source}")
            target = destination / source.name
            target.write_bytes(source.read_bytes())
            records.append({"path": str(source), "snapshot": str(target.relative_to(manifest_path.parent)), "sha256": _file_hash(source)})
        manifest["config_files"] = records
        _atomic_yaml(manifest_path, manifest)
        return records

    def start_bag(self, experiment_id: str, profile_id: str, profile: Mapping[str, Any]) -> Path:
        _path, manifest = self._manifest(experiment_id)
        if manifest.get("state") != "RUNNING":
            raise ExperimentError("bag recording requires a running experiment")
        if self._bag_process is not None and self._bag_process.poll() is None:
            raise ExperimentError("a bag is already recording")
        topics = profile.get("topics")
        if not isinstance(topics, list) or not topics:
            raise ExperimentError("bag profile must contain an explicit non-empty topic list")
        if any(not isinstance(topic, str) or not topic.startswith("/") for topic in topics):
            raise ExperimentError("bag profile contains an invalid topic")
        bag_dir = self._path(experiment_id) / "rosbag" / f"{profile_id}_{datetime.now(timezone.utc).strftime('%Y%m%d_%H%M%S')}"
        bag_dir.parent.mkdir(exist_ok=True)
        log_path = self._path(experiment_id) / "logs" / "rosbag.log"
        self._bag_log = open(log_path, "ab", buffering=0)
        command = ["ros2", "bag", "record", "--storage", "sqlite3", "--output", str(bag_dir), *topics]
        try:
            self._bag_process = self._popen(
                command,
                stdin=subprocess.DEVNULL,
                stdout=self._bag_log,
                stderr=subprocess.STDOUT,
                start_new_session=True,
            )
        except Exception:
            self._bag_log.close()
            self._bag_log = None
            raise
        self._bag_profile = profile_id
        manifest["rosbag"] = {"profile": profile_id, "path": str(bag_dir.relative_to(self._path(experiment_id))), "command": command}
        _atomic_yaml(self._path(experiment_id) / "manifest.yaml", manifest)
        self.add_event(experiment_id, "bag_started", {"profile": profile_id, "path": str(bag_dir)})
        return bag_dir

    def stop_bag(self, experiment_id: str, grace_sec: float = 30.0) -> None:
        if self._bag_process is None:
            return
        process = self._bag_process
        if process.poll() is None:
            try:
                os.killpg(os.getpgid(process.pid), signal.SIGINT)
            except ProcessLookupError:
                pass
            try:
                process.wait(timeout=grace_sec)
            except subprocess.TimeoutExpired:
                try:
                    os.killpg(os.getpgid(process.pid), signal.SIGTERM)
                except ProcessLookupError:
                    pass
                process.wait(timeout=5.0)
        if self._bag_log is not None:
            self._bag_log.close()
        self.add_event(experiment_id, "bag_stopped", {"profile": self._bag_profile, "returncode": process.returncode})
        self._bag_process = None
        self._bag_log = None
        self._bag_profile = ""

    def bag_status(self) -> dict[str, Any]:
        process = self._bag_process
        return {
            "recording": process is not None and process.poll() is None,
            "profile": self._bag_profile,
            "pid": int(process.pid) if process is not None else 0,
            "returncode": process.poll() if process is not None else None,
        }

    def finalize(self, experiment_id: str, health: Mapping[str, Any] | None = None, result_status: str = "COMPLETED") -> dict[str, Any]:
        manifest_path, manifest = self._manifest(experiment_id)
        if manifest.get("state") != "RUNNING":
            raise ExperimentError("only a running experiment can be finalized")
        self.stop_bag(experiment_id)
        now = _timestamp()
        self.snapshot_health(experiment_id, "health_end", health or {})
        manifest["state"] = "COMPLETED" if result_status == "COMPLETED" else "INVALID"
        manifest["result_status"] = result_status
        manifest["end_time"] = now
        _atomic_yaml(manifest_path, manifest)
        summary = self._summary(experiment_id, manifest)
        _atomic_json(manifest_path.parent / "summary.json", summary)
        (manifest_path.parent / "report.md").write_text(self._report(summary, manifest), encoding="utf-8")
        self.add_event(experiment_id, "experiment_finalized", {"status": result_status})
        return summary

    def mark_invalid(self, experiment_id: str, reason: str) -> None:
        manifest_path, manifest = self._manifest(experiment_id)
        if manifest.get("state") == "RUNNING":
            self.stop_bag(experiment_id)
        manifest["state"] = "INVALID"
        manifest["result_status"] = "INVALID"
        manifest["invalid_reason"] = reason
        manifest["end_time"] = _timestamp()
        _atomic_yaml(manifest_path, manifest)
        self.add_event(experiment_id, "experiment_invalid", {"reason": reason})

    def recover_interrupted(self) -> list[str]:
        recovered = []
        for manifest_path in sorted(self.root.glob("*/manifest.yaml")):
            try:
                with open(manifest_path, "r", encoding="utf-8") as stream:
                    manifest = yaml.safe_load(stream) or {}
            except (OSError, yaml.YAMLError):
                continue
            if manifest.get("state") == "RUNNING":
                manifest["state"] = "INTERRUPTED"
                manifest["result_status"] = "INTERRUPTED"
                manifest["end_time"] = _timestamp()
                _atomic_yaml(manifest_path, manifest)
                recovered.append(str(manifest.get("experiment_id", manifest_path.parent.name)))
        return recovered

    def list(self, *, state: str | None = None) -> list[dict[str, Any]]:
        result = []
        for manifest_path in sorted(self.root.glob("*/manifest.yaml"), reverse=True):
            try:
                with open(manifest_path, "r", encoding="utf-8") as stream:
                    manifest = yaml.safe_load(stream) or {}
            except (OSError, yaml.YAMLError):
                continue
            if state and manifest.get("state") != state.upper():
                continue
            result.append(manifest)
        return result

    def inspect(self, experiment_id: str) -> dict[str, Any]:
        _path, manifest = self._manifest(experiment_id)
        return manifest

    def _summary(self, experiment_id: str, manifest: Mapping[str, Any]) -> dict[str, Any]:
        path = self._path(experiment_id)
        events = [json.loads(line) for line in (path / "events.jsonl").read_text(encoding="utf-8").splitlines() if line]
        localization = [json.loads(line) for line in (path / "localization_results.jsonl").read_text(encoding="utf-8").splitlines() if line]
        successes = [item for item in localization if item.get("success") is True]
        return {
            "schema_version": 1,
            "experiment_id": experiment_id,
            "state": manifest.get("state"),
            "result_status": manifest.get("result_status"),
            "start_time": manifest.get("start_time"),
            "end_time": manifest.get("end_time"),
            "event_count": len(events),
            "manual_intervention_count": sum(item.get("type") == "manual_intervention" for item in events),
            "emergency_stop_count": sum(item.get("type") == "emergency_stop" for item in events),
            "localization_attempts": len(localization),
            "localization_successes": len(successes),
            "localization_success_rate": len(successes) / len(localization) if localization else None,
            "map_identity": manifest.get("active_map", {}),
        }

    @staticmethod
    def _report(summary: Mapping[str, Any], manifest: Mapping[str, Any]) -> str:
        return "\n".join([
            f"# Experiment {summary['experiment_id']}",
            "",
            f"- State: `{summary['state']}`",
            f"- Result: `{summary['result_status']}`",
            f"- Start: `{summary.get('start_time')}`",
            f"- End: `{summary.get('end_time')}`",
            f"- Localization attempts: `{summary['localization_attempts']}`",
            f"- Localization success rate: `{summary['localization_success_rate']}`",
            f"- Events: `{summary['event_count']}`",
            f"- Active map: `{json.dumps(manifest.get('active_map', {}), ensure_ascii=False)}`",
            "",
            "This report is generated from the versioned experiment manifest, event stream, and localization result stream.",
            "",
        ])
