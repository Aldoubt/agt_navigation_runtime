from __future__ import annotations

from collections import OrderedDict
from dataclasses import dataclass, replace
import re
import threading
from typing import Callable

from .activation_store import ActivationStoreError
from .models import ActiveSelection, SiteKey, SiteSummary
from .summary_builder import build_site_summary


ERROR_NONE = 0
ERROR_INVALID_REQUEST = 1
ERROR_NOT_FOUND = 2
ERROR_VALIDATION_FAILED = 3
ERROR_INTERNAL = 255

_REQUEST_ID_RE = re.compile(r"^[A-Za-z0-9][A-Za-z0-9._:-]{0,127}$")


@dataclass(frozen=True)
class ActivationResult:
    success: bool
    error_code: int
    summary: SiteSummary | None = None
    blocker_codes: tuple[str, ...] = ()
    blocker_messages: tuple[str, ...] = ()
    message: str = ""
    revoke_active: bool = False


class SiteRuntimePolicy:
    """Pure, serialized policy for deployed-site validation and explicit activation."""

    def __init__(
        self,
        registry,
        validator,
        store,
        *,
        recent_request_limit: int = 128,
        summary_builder: Callable = build_site_summary,
    ) -> None:
        if recent_request_limit <= 0:
            raise ValueError("recent_request_limit must be positive")
        self._registry = registry
        self._validator = validator
        self._store = store
        self._summary_builder = summary_builder
        self._recent_request_limit = int(recent_request_limit)
        self._recent_requests: OrderedDict[str, tuple[SiteKey, ActivationResult]] = OrderedDict()
        self._active_summary: SiteSummary | None = None
        self._lock = threading.RLock()

    @property
    def active_summary(self) -> SiteSummary | None:
        with self._lock:
            return self._active_summary

    @property
    def recent_request_count(self) -> int:
        with self._lock:
            return len(self._recent_requests)

    def _remember(self, request_id: str, key: SiteKey, result: ActivationResult) -> None:
        self._recent_requests[request_id] = (key, result)
        self._recent_requests.move_to_end(request_id)
        while len(self._recent_requests) > self._recent_request_limit:
            self._recent_requests.popitem(last=False)

    @staticmethod
    def _not_found(*, revoke_active: bool = False) -> ActivationResult:
        return ActivationResult(
            success=False,
            error_code=ERROR_NOT_FOUND,
            blocker_codes=("SITE_NOT_FOUND",),
            blocker_messages=("requested deployed site version was not found",),
            message="site version not found",
            revoke_active=revoke_active,
        )

    def _validate_candidate(self, key: SiteKey) -> ActivationResult:
        candidate = self._registry.resolve(key)
        if candidate is None:
            return self._not_found()

        validation = self._validator.validate(candidate)
        summary = self._summary_builder(candidate, validation, active=False)
        if not validation.valid:
            return ActivationResult(
                success=False,
                error_code=ERROR_VALIDATION_FAILED,
                summary=summary,
                blocker_codes=validation.blocker_codes,
                blocker_messages=validation.blocker_messages,
                message="site version validation failed",
            )
        return ActivationResult(
            success=True,
            error_code=ERROR_NONE,
            summary=summary,
            message="site version is valid",
        )

    def list_versions(self, map_id: str = "", state: int = 0) -> tuple[SiteSummary, ...]:
        with self._lock:
            active_key = None
            if self._active_summary is not None:
                active_key = SiteKey(
                    self._active_summary.map_id,
                    self._active_summary.map_version_id,
                )

            summaries: list[SiteSummary] = []
            for candidate in self._registry.scan():
                if map_id and candidate.key.site_id != map_id:
                    continue
                validation = self._validator.validate(candidate)
                summary = self._summary_builder(
                    candidate,
                    validation,
                    active=(candidate.key == active_key),
                )
                if state and summary.state != state:
                    continue
                summaries.append(summary)
            return tuple(summaries)

    def validate(self, key: SiteKey) -> ActivationResult:
        with self._lock:
            return self._validate_candidate(key)

    def activate(self, key: SiteKey, client_request_id: str) -> ActivationResult:
        with self._lock:
            if not _REQUEST_ID_RE.fullmatch(client_request_id or ""):
                return ActivationResult(
                    success=False,
                    error_code=ERROR_INVALID_REQUEST,
                    blocker_codes=("INVALID_REQUEST",),
                    blocker_messages=("client_request_id is missing or malformed",),
                    message="invalid client request id",
                )

            cached = self._recent_requests.get(client_request_id)
            if cached is not None:
                cached_key, cached_result = cached
                if cached_key == key:
                    self._recent_requests.move_to_end(client_request_id)
                    return cached_result
                return ActivationResult(
                    success=False,
                    error_code=ERROR_INVALID_REQUEST,
                    blocker_codes=("INVALID_REQUEST",),
                    blocker_messages=(
                        "client_request_id was already used for a different site version",
                    ),
                    message="request id target mismatch",
                )

            validated = self._validate_candidate(key)
            if not validated.success or validated.summary is None:
                self._remember(client_request_id, key, validated)
                return validated

            active_summary = replace(validated.summary, active=True)
            try:
                self._store.save(ActiveSelection(key.site_id, key.revision))
            except ActivationStoreError as exc:
                result = ActivationResult(
                    success=False,
                    error_code=ERROR_INTERNAL,
                    blocker_codes=("ACTIVE_SELECTION_PERSIST_FAILED",),
                    blocker_messages=(str(exc),),
                    message="failed to persist active site selection",
                )
                self._remember(client_request_id, key, result)
                return result

            self._active_summary = active_summary
            result = ActivationResult(
                success=True,
                error_code=ERROR_NONE,
                summary=active_summary,
                message="site version activated",
            )
            self._remember(client_request_id, key, result)
            return result

    def restore(self) -> ActivationResult:
        with self._lock:
            self._active_summary = None
            try:
                selection = self._store.load()
            except ActivationStoreError as exc:
                return ActivationResult(
                    success=False,
                    error_code=ERROR_INTERNAL,
                    blocker_codes=("ACTIVE_SELECTION_LOAD_FAILED",),
                    blocker_messages=(str(exc),),
                    message="failed to load persisted active site selection",
                    revoke_active=True,
                )

            if selection is None:
                return ActivationResult(
                    success=True,
                    error_code=ERROR_NONE,
                    message="no persisted active site selection",
                    revoke_active=True,
                )

            key = SiteKey(selection.site_id, selection.revision)
            candidate = self._registry.resolve(key)
            if candidate is None:
                return self._not_found(revoke_active=True)

            validation = self._validator.validate(candidate)
            summary = self._summary_builder(candidate, validation, active=False)
            if not validation.valid:
                return ActivationResult(
                    success=False,
                    error_code=ERROR_VALIDATION_FAILED,
                    summary=summary,
                    blocker_codes=validation.blocker_codes,
                    blocker_messages=validation.blocker_messages,
                    message="persisted site selection failed revalidation",
                    revoke_active=True,
                )

            active_summary = replace(summary, active=True)
            self._active_summary = active_summary
            return ActivationResult(
                success=True,
                error_code=ERROR_NONE,
                summary=active_summary,
                message="persisted site selection restored",
            )
