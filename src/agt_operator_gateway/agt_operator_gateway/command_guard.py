from __future__ import annotations

import copy
from dataclasses import dataclass
from enum import Enum
from hashlib import sha256
import hmac
import json
from threading import RLock
from time import time
from typing import Any, Callable


class ReplayKind(Enum):
    NEW = 'NEW'
    IN_PROGRESS = 'IN_PROGRESS'
    REPLAY = 'REPLAY'
    CONFLICT = 'CONFLICT'
    CAPACITY = 'CAPACITY'


@dataclass(frozen=True)
class ReplayDecision:
    kind: ReplayKind
    status_code: int | None = None
    payload: dict[str, Any] | None = None


@dataclass
class _ReplayEntry:
    fingerprint: str
    created_at_ms: int
    completed_at_ms: int | None = None
    status_code: int | None = None
    payload: dict[str, Any] | None = None

    @property
    def completed(self) -> bool:
        return self.completed_at_ms is not None


def verify_bearer_token(header: str | None, expected_token: str) -> bool:
    expected = str(expected_token)
    if not expected or not header or not header.startswith('Bearer '):
        return False
    supplied = header[len('Bearer '):]
    return bool(supplied) and hmac.compare_digest(supplied, expected)


def canonical_fingerprint(command: str, payload: dict[str, Any]) -> str:
    canonical = json.dumps(
        {'command': str(command), 'payload': payload},
        ensure_ascii=False,
        sort_keys=True,
        separators=(',', ':'),
    )
    return sha256(canonical.encode('utf-8')).hexdigest()


class CommandReplayStore:
    """Bounded in-memory idempotency store that never evicts in-flight work."""

    def __init__(
        self,
        *,
        now_ms: Callable[[], int] | None = None,
        ttl_ms: int = 300_000,
        max_entries: int = 256,
    ) -> None:
        if ttl_ms <= 0:
            raise ValueError('ttl_ms must be > 0')
        if max_entries <= 0:
            raise ValueError('max_entries must be > 0')
        self._now_ms = now_ms or (lambda: int(time() * 1000))
        self._ttl_ms = int(ttl_ms)
        self._max_entries = int(max_entries)
        self._entries: dict[str, _ReplayEntry] = {}
        self._lock = RLock()

    def _prune_expired_completed(self, now: int) -> None:
        expired = [
            request_id
            for request_id, entry in self._entries.items()
            if entry.completed
            and entry.completed_at_ms is not None
            and now - entry.completed_at_ms > self._ttl_ms
        ]
        for request_id in expired:
            self._entries.pop(request_id, None)

    def _evict_oldest_completed(self) -> bool:
        completed = [
            (entry.completed_at_ms or entry.created_at_ms, request_id)
            for request_id, entry in self._entries.items()
            if entry.completed
        ]
        if not completed:
            return False
        _, request_id = min(completed)
        self._entries.pop(request_id, None)
        return True

    def begin(self, request_id: str, fingerprint: str) -> ReplayDecision:
        request_id = str(request_id).strip()
        fingerprint = str(fingerprint).strip()
        if not request_id:
            raise ValueError('request_id must not be empty')
        if not fingerprint:
            raise ValueError('fingerprint must not be empty')

        now = int(self._now_ms())
        with self._lock:
            self._prune_expired_completed(now)
            existing = self._entries.get(request_id)
            if existing is not None:
                if existing.fingerprint != fingerprint:
                    return ReplayDecision(ReplayKind.CONFLICT)
                if existing.completed:
                    return ReplayDecision(
                        ReplayKind.REPLAY,
                        status_code=existing.status_code,
                        payload=copy.deepcopy(existing.payload),
                    )
                return ReplayDecision(ReplayKind.IN_PROGRESS)

            while len(self._entries) >= self._max_entries:
                if not self._evict_oldest_completed():
                    return ReplayDecision(ReplayKind.CAPACITY)

            self._entries[request_id] = _ReplayEntry(
                fingerprint=fingerprint,
                created_at_ms=now,
            )
            return ReplayDecision(ReplayKind.NEW)

    def complete(
        self,
        request_id: str,
        fingerprint: str,
        *,
        status_code: int,
        payload: dict[str, Any],
    ) -> None:
        request_id = str(request_id).strip()
        fingerprint = str(fingerprint).strip()
        with self._lock:
            entry = self._entries.get(request_id)
            if entry is None:
                raise KeyError(request_id)
            if entry.fingerprint != fingerprint:
                raise ValueError('fingerprint does not match in-flight request')
            entry.completed_at_ms = int(self._now_ms())
            entry.status_code = int(status_code)
            entry.payload = copy.deepcopy(payload)
