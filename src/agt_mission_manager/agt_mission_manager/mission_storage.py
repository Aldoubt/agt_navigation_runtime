from __future__ import annotations

import json
import os
from pathlib import Path
from typing import Any, Mapping

from .mission_model import Mission, MissionError, MissionState, validate_component
from .mission_schema import load_mission


class MissionStorage:
    def __init__(self, root: str | Path) -> None:
        self.root = Path(root).expanduser().resolve()

    def mission_path(self, mission_id: str, mission_version: str) -> Path:
        mission_id = validate_component(mission_id, "mission_id")
        mission_version = validate_component(mission_version, "mission_version")
        return self.root / mission_id / mission_version / "mission.yaml"

    def load(self, mission_id: str, mission_version: str, **limits: Any) -> Mission:
        path = self.mission_path(mission_id, mission_version)
        mission = load_mission(path, **limits)
        if mission.mission_id != mission_id or mission.mission_version != mission_version:
            raise MissionError("mission document identity does not match its storage path")
        return mission

    def execution_state_path(self) -> Path:
        return self.root / "execution_state.json"

    def write_execution_state(self, values: Mapping[str, Any]) -> None:
        target = self.execution_state_path()
        target.parent.mkdir(parents=True, exist_ok=True)
        temporary = target.with_suffix(".json.tmp")
        with open(temporary, "w", encoding="utf-8") as stream:
            json.dump(dict(values), stream, ensure_ascii=False, sort_keys=True, indent=2)
            stream.write("\n")
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary, target)

    def recover_interrupted(self) -> dict[str, Any] | None:
        path = self.execution_state_path()
        if not path.is_file():
            return None
        try:
            value = json.loads(path.read_text(encoding="utf-8"))
            state = MissionState(int(value.get("state", MissionState.IDLE)))
        except (OSError, UnicodeError, json.JSONDecodeError, TypeError, ValueError) as exc:
            raise MissionError(f"invalid persisted execution state: {exc}") from exc
        recovered = MissionState.INTERRUPTED if MissionState.IDLE != state and state.value < MissionState.SUCCEEDED else state
        if recovered == MissionState.INTERRUPTED:
            value["state"] = int(recovered)
            value["message"] = "mission manager restarted during an active mission"
            self.write_execution_state(value)
        return value
