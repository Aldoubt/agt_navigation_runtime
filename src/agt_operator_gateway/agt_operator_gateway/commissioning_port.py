from __future__ import annotations

from typing import Any, Protocol

from agt_field_commissioning.service import CommissioningService


class CommissioningPort(Protocol):
    def status(self) -> dict[str, Any]: ...
    def map_descriptor(self) -> dict[str, Any]: ...
    def map_bytes(self) -> bytes: ...
    def project(self, options: dict[str, Any]) -> dict[str, Any]: ...
    def edit(self, kind: str, cells: list[int]) -> dict[str, Any]: ...
    def undo(self) -> dict[str, Any]: ...
    def redo(self) -> dict[str, Any]: ...
    def reset(self) -> dict[str, Any]: ...
    def save(self, revision: str) -> dict[str, Any]: ...
    def activate(self, revision: str) -> dict[str, Any]: ...


class FilesystemCommissioningPort:
    def __init__(self, service: CommissioningService, site_id: str, run_id: str) -> None:
        self.service = service
        self.site_id = str(site_id)
        self.run_id = str(run_id)

    def status(self) -> dict[str, Any]:
        return self.service.status(self.site_id, self.run_id)

    def map_descriptor(self) -> dict[str, Any]:
        return self.service.map_descriptor(self.site_id, self.run_id)

    def map_bytes(self) -> bytes:
        return self.service.current_map_bytes(self.site_id, self.run_id)

    def project(self, options: dict[str, Any]) -> dict[str, Any]:
        allowed = {
            'resolution_m',
            'max_ground_angle_deg',
            'normal_k',
            'min_ground_height_m',
            'max_ground_height_m',
            'max_obstacle_height_m',
        }
        unexpected = set(options) - allowed
        if unexpected:
            raise ValueError(f'unsupported projection options: {sorted(unexpected)}')
        return self.service.project(self.site_id, self.run_id, **options)

    def edit(self, kind: str, cells: list[int]) -> dict[str, Any]:
        return self.service.apply_map_edit(self.site_id, self.run_id, kind, cells)

    def undo(self) -> dict[str, Any]:
        self.service.undo_map_edit(self.site_id, self.run_id)
        return self.service.map_descriptor(self.site_id, self.run_id)

    def redo(self) -> dict[str, Any]:
        self.service.redo_map_edit(self.site_id, self.run_id)
        return self.service.map_descriptor(self.site_id, self.run_id)

    def reset(self) -> dict[str, Any]:
        return self.service.reset_map_edit(self.site_id, self.run_id)

    def save(self, revision: str) -> dict[str, Any]:
        return self.service.save_review(self.site_id, self.run_id, revision)

    def activate(self, revision: str) -> dict[str, Any]:
        return self.service.activate_revision(self.site_id, revision)
