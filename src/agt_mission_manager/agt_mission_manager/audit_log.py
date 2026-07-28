from __future__ import annotations

from datetime import datetime, timezone
import json
import os
from pathlib import Path
from typing import Any, Mapping


class AuditLog:
    def __init__(self, path: str | Path) -> None:
        self.path = Path(path)

    def append(self, event: str, values: Mapping[str, Any] | None = None) -> None:
        record = {
            "timestamp": datetime.now(timezone.utc).isoformat(),
            "event": str(event),
            **dict(values or {}),
        }
        self.path.parent.mkdir(parents=True, exist_ok=True)
        existing = self.path.read_bytes() if self.path.exists() else b""
        line = json.dumps(record, ensure_ascii=False, sort_keys=True).encode("utf-8") + b"\n"
        temporary = self.path.with_suffix(self.path.suffix + ".tmp")
        with open(temporary, "wb") as stream:
            stream.write(existing)
            stream.write(line)
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary, self.path)

