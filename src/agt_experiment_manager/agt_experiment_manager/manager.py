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
    temporary.write_text(
        json.dumps(value, indent=2, ensure_ascii=False, allow_nan=False),
        encoding="utf-8",
    )
    os.replace(temporary, path)


def _atomic_text(path: Path, value: str) -> None:
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_text(value, encoding="utf-8")
    os.replace(temporary, path)


class ExperimentManager:
    """Own the experiment directory and any rosbag child it starts."""

    _PLAYBACK_TOPICS = {
        "mapping_inputs": (
            "/clock",
            "/tf_static",
            "/agt/sensors/lidar/custom",
            "/agt/sensors/imu/data",
        ),
        "localization_inputs": (
            "/clock",
            "/tf_static",
            "/agt/mapping/registered_points_lidar",
            "/agt/sensors/imu/data",
        ),
    }

    def __init__(
        self,
        root: str | Path,
        *,
        repository_root: str | Path | None = None,
        rosbag_root: str | Path | None = None,
        popen_factory: Callable[..., Any] = subprocess.Popen,
    ) -> None:
        self.root = Path(root).expanduser().resolve()
        self.root.mkdir(parents=True, exist_ok=True)
        self.repository_root = Path(repository_root).expanduser().resolve() if repository_root else None
        self.rosbag_root = Path(rosbag_root).expanduser().resolve() if rosbag_root else self.root.parent / "rosbag"
        self.rosbag_root.mkdir(parents=True, exist_ok=True)
        self._popen = popen_factory
        self._bag_process = None
        self._bag_log = None
        self._bag_profile = ""
        self._bag_experiment_id = ""
        self._bag_path: Path | None = None
        self._playback_process = None
        self._playback_log = None
        self._playback_id = ""
        self._playback_profile = ""
        self._playback_rate = 0.0

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
            "teach_repeat_runs": [],
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

    def record_teach_repeat_result(
        self,
        experiment_id: str,
        *,
        demo_id: str,
        run_id: str,
        teach_manifest: str,
        reference_path_hash: str,
        map_identity: Mapping[str, Any],
        repeatability_metrics: Mapping[str, Any],
        localization_summary: Mapping[str, Any],
        execution_result: Mapping[str, Any],
        failure_case: Mapping[str, Any] | None = None,
    ) -> Path:
        """Attach one immutable teach-repeat result to a running experiment."""
        manifest_path, manifest = self._manifest(experiment_id)
        if manifest.get("state") != "RUNNING":
            raise ExperimentError("teach-repeat results require a running experiment")
        for name, value in (("demo_id", demo_id), ("run_id", run_id)):
            if not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9_.-]{0,95}", str(value)):
                raise ExperimentError(f"{name} is invalid")
        teach_manifest_path = Path(teach_manifest).expanduser().resolve()
        if not teach_manifest_path.is_file():
            raise ExperimentError("teach manifest is missing")
        repository = self._repository_snapshot()
        if repository.get("commit") is None and manifest.get("repository"):
            repository = dict(manifest["repository"])
        record = {
            "schema_version": 1,
            "time": _timestamp(),
            "demo_id": str(demo_id),
            "run_id": str(run_id),
            "teach_manifest": str(teach_manifest_path),
            "teach_manifest_sha256": _file_hash(teach_manifest_path),
            "reference_path_hash": str(reference_path_hash),
            "map_identity": dict(map_identity),
            "repeatability_metrics": dict(repeatability_metrics),
            "localization_summary": dict(localization_summary),
            "execution_result": dict(execution_result),
            "failure_case": dict(failure_case) if failure_case else None,
            "repository": repository,
            "config_files": list(manifest.get("config_files", [])),
        }
        json.dumps(record, allow_nan=False)
        output = self._path(experiment_id) / "teach_repeat" / str(demo_id) / str(run_id)
        output.mkdir(parents=True, exist_ok=False)
        _atomic_json(output / "result.json", record)
        runs = list(manifest.get("teach_repeat_runs", []))
        runs.append(
            {
                "demo_id": str(demo_id),
                "run_id": str(run_id),
                "path": str((output / "result.json").relative_to(manifest_path.parent)),
                "reference_path_hash": str(reference_path_hash),
                "map_identity": dict(map_identity),
            }
        )
        manifest["teach_repeat_runs"] = runs
        _atomic_yaml(manifest_path, manifest)
        self.add_event(
            experiment_id,
            "teach_repeat_result",
            {"demo_id": str(demo_id), "run_id": str(run_id)},
        )
        return output / "result.json"

    def record_failure_case(
        self,
        experiment_id: str,
        *,
        demo_id: str,
        run_id: str,
        category: str,
        robot_pose: Mapping[str, Any] | None = None,
        reference_progress: float = 0.0,
        lateral_error_m: float = 0.0,
        localization_status: Mapping[str, Any] | None = None,
        navigation_status: Mapping[str, Any] | None = None,
        safety_status: Mapping[str, Any] | None = None,
        operator_note: str = "",
    ) -> dict[str, Any]:
        """Append a durable machine-readable field failure case."""
        _path, manifest = self._manifest(experiment_id)
        if manifest.get("state") != "RUNNING":
            raise ExperimentError("failure cases require a running experiment")
        for name, value in (("demo_id", demo_id), ("run_id", run_id)):
            if not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9_.-]{0,95}", str(value)):
                raise ExperimentError(f"{name} is invalid")
        if not re.fullmatch(r"[A-Z][A-Z0-9_]{1,63}", str(category)):
            raise ExperimentError("failure category is invalid")
        repository = self._repository_snapshot()
        if repository.get("commit") is None and manifest.get("repository"):
            repository = dict(manifest["repository"])
        record = {
            "time": _timestamp(),
            "demo_id": str(demo_id),
            "run_id": str(run_id),
            "category": str(category),
            "robot_pose": dict(robot_pose or {}),
            "reference_progress": float(reference_progress),
            "lateral_error_m": float(lateral_error_m),
            "localization_status": dict(localization_status or {}),
            "navigation_status": dict(navigation_status or {}),
            "safety_status": dict(safety_status or {}),
            "operator_note": str(operator_note),
            "repository": repository,
            "active_map": dict(manifest.get("active_map", {})),
        }
        json.dumps(record, allow_nan=False)
        output = self._path(experiment_id) / "failure_cases.jsonl"
        with open(output, "a", encoding="utf-8") as stream:
            stream.write(json.dumps(record, ensure_ascii=False, sort_keys=True, allow_nan=False) + "\n")
            stream.flush()
            os.fsync(stream.fileno())
        self.add_event(
            experiment_id,
            "failure_case",
            {"demo_id": str(demo_id), "run_id": str(run_id), "category": str(category)},
        )
        return record

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
        self._bag_experiment_id = experiment_id
        self._bag_path = bag_dir
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
        self._bag_experiment_id = ""
        self._bag_path = None

    def bag_status(self) -> dict[str, Any]:
        process = self._bag_process
        return {
            "recording": process is not None and process.poll() is None,
            "profile": self._bag_profile,
            "experiment_id": self._bag_experiment_id,
            "path": str(self._bag_path) if self._bag_path is not None else "",
            "pid": int(process.pid) if process is not None else 0,
            "returncode": process.poll() if process is not None else None,
        }

    def list_bags(self) -> list[dict[str, Any]]:
        """List only self-contained bags below the configured runtime root."""
        result = []
        metadata_paths = list(self.rosbag_root.glob("*/metadata.yaml"))
        metadata_paths.extend(self.root.glob("*/rosbag/*/metadata.yaml"))
        for metadata_path in sorted(metadata_paths, reverse=True):
            bag_path = metadata_path.parent.resolve()
            try:
                if bag_path.is_relative_to(self.rosbag_root):
                    bag_id = str(bag_path.relative_to(self.rosbag_root))
                    experiment_id = ""
                else:
                    relative = bag_path.relative_to(self.root)
                    if len(relative.parts) != 3 or relative.parts[1] != "rosbag":
                        continue
                    experiment_id = relative.parts[0]
                    bag_id = str(Path("experiments") / relative)
            except ValueError:
                continue
            try:
                with open(metadata_path, "r", encoding="utf-8") as stream:
                    metadata = yaml.safe_load(stream) or {}
                information = metadata.get("rosbag2_bagfile_information", {})
                topic_records = information.get("topics_with_message_count", [])
                topic_names = sorted(
                    str(item.get("topic_metadata", {}).get("name", ""))
                    for item in topic_records
                    if isinstance(item, Mapping)
                    and isinstance(item.get("topic_metadata"), Mapping)
                    and item.get("topic_metadata", {}).get("name")
                )
                topic_set = set(topic_names)
                bag_input_topics = set(self._PLAYBACK_TOPICS["mapping_inputs"]) - {"/clock"}
                result.append({
                    "bag_id": bag_id,
                    "experiment_id": experiment_id,
                    "path": str(bag_path),
                    "duration_nanoseconds": int(information.get("duration", {}).get("nanoseconds", 0)),
                    "message_count": int(information.get("message_count", 0)),
                    "storage_identifier": str(information.get("storage_identifier", "")),
                    "topic_names": topic_names,
                    "mapping_input_ready": bag_input_topics.issubset(topic_set),
                    "contains_mapping_outputs": bool(
                        {"/agt/mapping/odometry", "/agt/mapping/registered_points_lidar"} & topic_set
                    ),
                    "contains_navigation_outputs": bool(
                        {
                            "/agt/navigation/cmd_vel",
                            "/agt/navigation/cmd_vel_raw",
                            "/agt/map/global_occupancy",
                            "/global_costmap/costmap",
                        }
                        & topic_set
                    ),
                })
            except (OSError, TypeError, ValueError, yaml.YAMLError):
                continue
        return result

    def _resolve_bag_path(self, bag_id: str) -> Path:
        if not isinstance(bag_id, str) or not bag_id or Path(bag_id).is_absolute():
            raise ExperimentError("bag_id must be a relative configured bag identifier")
        relative = Path(bag_id)
        if ".." in relative.parts:
            raise ExperimentError("bag_id is outside the configured runtime root")
        if relative.parts and relative.parts[0] == "experiments":
            if len(relative.parts) != 4 or relative.parts[2] != "rosbag":
                raise ExperimentError("experiment bag_id is malformed")
            bag_path = (self.root.parent / relative).resolve()
            allowed_root = self.root
        else:
            bag_path = (self.rosbag_root / relative).resolve()
            allowed_root = self.rosbag_root
        try:
            bag_path.relative_to(allowed_root)
        except ValueError as error:
            raise ExperimentError("bag_id is outside the configured runtime root") from error
        return bag_path

    def start_playback(
        self,
        bag_id: str,
        *,
        rate: float = 1.0,
        playback_profile: str = "all",
    ) -> dict[str, Any]:
        if self._playback_process is not None and self._playback_process.poll() is None:
            raise ExperimentError("a bag is already playing")
        if self._playback_process is not None and self._playback_process.poll() is not None:
            if self._playback_log is not None:
                self._playback_log.close()
            self._playback_process = None
            self._playback_log = None
            self._playback_id = ""
            self._playback_profile = ""
            self._playback_rate = 0.0
        if self._bag_process is not None and self._bag_process.poll() is None:
            raise ExperimentError("stop bag recording before playback")
        bag_path = self._resolve_bag_path(bag_id)
        if not (bag_path.is_dir() and (bag_path / "metadata.yaml").is_file()):
            raise ExperimentError("bag_id does not identify a complete rosbag bundle")
        try:
            rate = float(rate)
        except (TypeError, ValueError) as error:
            raise ExperimentError("bag playback rate must be numeric") from error
        if not 0.1 <= rate <= 4.0:
            raise ExperimentError("bag playback rate must be between 0.1 and 4.0")
        playback_profile = str(playback_profile).strip() or "all"
        if playback_profile != "all" and playback_profile not in self._PLAYBACK_TOPICS:
            raise ExperimentError(f"unknown bag playback profile: {playback_profile}")
        log_path = self.rosbag_root.parent / "logs" / "rosbag_playback.log"
        log_path.parent.mkdir(parents=True, exist_ok=True)
        self._playback_log = open(log_path, "ab", buffering=0)
        replay_topics = list(self._PLAYBACK_TOPICS.get(playback_profile, ()))
        command = ["ros2", "bag", "play", "--clock", "--rate", f"{rate:g}", str(bag_path)]
        if replay_topics:
            command.extend(["--topics", *replay_topics])
        try:
            self._playback_process = self._popen(
                command,
                stdin=subprocess.DEVNULL,
                stdout=self._playback_log,
                stderr=subprocess.STDOUT,
                start_new_session=True,
            )
        except Exception:
            self._playback_log.close()
            self._playback_log = None
            raise
        self._playback_id = bag_id
        self._playback_profile = playback_profile
        self._playback_rate = rate
        return {
            "state": "PLAYING",
            "bag_id": bag_id,
            "path": str(bag_path),
            "pid": int(self._playback_process.pid),
            "playback_profile": playback_profile,
            "replayed_topics": replay_topics or None,
            "command": command,
        }

    def stop_playback(self, grace_sec: float = 10.0) -> None:
        if self._playback_process is None:
            return
        process = self._playback_process
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
        if self._playback_log is not None:
            self._playback_log.close()
        self._playback_process = None
        self._playback_log = None
        self._playback_id = ""
        self._playback_profile = ""
        self._playback_rate = 0.0

    def playback_status(self) -> dict[str, Any]:
        process = self._playback_process
        return {
            "playing": process is not None and process.poll() is None,
            "bag_id": self._playback_id,
            "playback_profile": self._playback_profile,
            "rate": self._playback_rate,
            "pid": int(process.pid) if process is not None else 0,
            "returncode": process.poll() if process is not None else None,
        }

    def close(self) -> None:
        self.stop_playback()
        if self._bag_process is not None and self._bag_process.poll() is None:
            # A normal Web shutdown must not leave a recorder orphaned.
            try:
                os.killpg(os.getpgid(self._bag_process.pid), signal.SIGINT)
                self._bag_process.wait(timeout=10.0)
            except (ProcessLookupError, subprocess.TimeoutExpired):
                pass
        if self._bag_log is not None:
            self._bag_log.close()
        self._bag_process = None
        self._bag_log = None
        self._bag_profile = ""
        self._bag_experiment_id = ""
        self._bag_path = None

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
        _atomic_text(manifest_path.parent / "report.md", self._report(summary, manifest))
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

    def interrupt(self, experiment_id: str, reason: str = "operator_requested") -> dict[str, Any]:
        manifest_path, manifest = self._manifest(experiment_id)
        if manifest.get("state") != "RUNNING":
            raise ExperimentError("only a running experiment can be interrupted")
        self.stop_bag(experiment_id)
        manifest["state"] = "INTERRUPTED"
        manifest["result_status"] = "INTERRUPTED"
        manifest["end_time"] = _timestamp()
        manifest["interrupt_reason"] = str(reason)
        _atomic_yaml(manifest_path, manifest)
        self.add_event(experiment_id, "experiment_interrupted", {"reason": reason})
        return manifest

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
        failure_path = path / "failure_cases.jsonl"
        failures = (
            [json.loads(line) for line in failure_path.read_text(encoding="utf-8").splitlines() if line]
            if failure_path.is_file()
            else []
        )
        successes = [item for item in localization if item.get("success") is True]
        teach_results = []
        for item in manifest.get("teach_repeat_runs", []):
            result_path = (path / str(item.get("path", ""))).resolve()
            try:
                result_path.relative_to(path.resolve())
                record = json.loads(result_path.read_text(encoding="utf-8"))
            except (OSError, ValueError, json.JSONDecodeError, TypeError):
                continue
            teach_results.append(
                {
                    "demo_id": record.get("demo_id"),
                    "run_id": record.get("run_id"),
                    "reference_path_hash": record.get("reference_path_hash"),
                    "map_identity": record.get("map_identity", {}),
                    "repository": record.get("repository", {}),
                    "config_files": record.get("config_files", []),
                    "execution_result": record.get("execution_result", {}),
                }
            )
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
            "teach_repeat_run_count": len(manifest.get("teach_repeat_runs", [])),
            "teach_repeat_results": teach_results,
            "failure_case_count": len(failures),
            "map_identity": manifest.get("active_map", {}),
        }

    @staticmethod
    def _report(summary: Mapping[str, Any], manifest: Mapping[str, Any]) -> str:
        lines = [
            f"# Experiment {summary['experiment_id']}",
            "",
            f"- State: `{summary['state']}`",
            f"- Result: `{summary['result_status']}`",
            f"- Start: `{summary.get('start_time')}`",
            f"- End: `{summary.get('end_time')}`",
            f"- Localization attempts: `{summary['localization_attempts']}`",
            f"- Localization success rate: `{summary['localization_success_rate']}`",
            f"- Events: `{summary['event_count']}`",
            f"- Teach-repeat runs: `{summary['teach_repeat_run_count']}`",
            f"- Failure cases: `{summary['failure_case_count']}`",
            f"- Active map: `{json.dumps(manifest.get('active_map', {}), ensure_ascii=False)}`",
            f"- Repository commit: `{manifest.get('repository', {}).get('commit')}`",
            f"- Config snapshots: `{json.dumps(manifest.get('config_files', []), ensure_ascii=False)}`",
            "",
            (
                "This report is generated from the versioned experiment manifest, "
                "event stream, and localization result stream."
            ),
            "",
        ]
        for result in summary.get("teach_repeat_results", []):
            lines.extend(
                [
                    f"## Teach repeat {result.get('demo_id')}/{result.get('run_id')}",
                    "",
                    f"- Reference path hash: `{result.get('reference_path_hash')}`",
                    f"- Map identity: `{json.dumps(result.get('map_identity', {}), ensure_ascii=False)}`",
                    f"- Repository commit: `{result.get('repository', {}).get('commit')}`",
                    f"- Config snapshots: `{json.dumps(result.get('config_files', []), ensure_ascii=False)}`",
                    f"- Execution result: `{json.dumps(result.get('execution_result', {}), ensure_ascii=False)}`",
                    "",
                ]
            )
        return "\n".join(lines)
