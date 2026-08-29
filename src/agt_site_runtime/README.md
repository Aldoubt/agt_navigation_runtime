# agt_site_runtime

`agt_site_runtime` is the Runtime owner for already-deployed Site Packages. It discovers exact `sites_root/<site_id>/<revision>/manifest.yaml` candidates, validates them through the installed `agt_runtime_contracts` package, and exposes an explicit active-Site selection without mutating map assets.

## Runtime API

- `/agt/maps/active` — authoritative `agt_interfaces/MapVersionSummary`, RELIABLE + TRANSIENT_LOCAL, depth 1.
- `/agt/maps/list` — list and validate deployed revisions.
- `/agt/maps/validate` — validate one exact deployed revision.
- `/agt/maps/activate` — explicitly activate one valid revision.

There is no automatic selection and no fallback to another revision. A failed switch preserves the previous active Site. Startup restores only the persisted `site_id` and `revision`, performs full current validation again, and publishes an UNKNOWN tombstone if stale active authority must be revoked.

## Configuration

The launch file loads `config/site_runtime.yaml`. The four runtime inputs are `sites_root`, `state_root`, `vehicle_profile`, and `recent_request_limit`. Filesystem values support `~` expansion. Validation schemas are resolved from the installed `agt_runtime_contracts` package share directory.

The selection state is stored separately from the read-only Site Package tree. Only the selected identity is persisted; READY state, hashes, resolved paths, and validation results are never persisted.

## Boundary

This package does not generate map assets and does not own map-server or process lifecycle. Import, mutation, removal, retention and other asset-management operations are outside this package.

## Local verification

On ROS 2 Humble, build `agt_interfaces`, `agt_runtime_contracts`, `agt_site_runtime`, and `agt_system_manager`, then run their package tests. Runtime acceptance additionally checks no-selection fail-closed behavior, explicit activation, restart restoration, invalid restore tombstone behavior, and failed-switch preservation.
